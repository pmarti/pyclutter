#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <gst/gst.h>
#include <clutter/clutter.h>
#include <clutter-gst/clutter-gst.h>

void pycluttergst_register_classes (PyObject *d);
extern PyMethodDef pycluttergst_functions[];

/* clutter-gst requires its own initialization function, which calls the
 * equivalent functions from GStreamer and Clutter in the right order.
 */
static void
init_clutter_gst (void)
{
  PyObject *av;
  int argc, i;
  char **argv;

  av = PySys_GetObject ("argv");
  if (!av)
    {
      if (!PyList_Check (av))
        {
	  PyErr_Warn (PyExc_Warning, "ignoring sys.argv: it must be a list of strings");
	  av = NULL;
        }
      else
        {
          argc = PyList_Size (av);
          for (i = 0; i < argc; i++)
            {
              if (!PyString_Check (PyList_GetItem (av, i)))
                {
		  PyErr_Warn (PyExc_Warning, "ignoring sys.argv: it must be a list of strings");
                  av = NULL;
                  break;
		}
            }
        }
    }

  if (av != NULL)
    {
      argv = g_new0 (char*, argc + 1);

      for (i = 0; i < argc; i++)
        {
          PyObject *arg = PyList_GetItem (av, i);

          if (arg && PyString_Check (arg))
            argv[i] = g_strdup (PyString_AsString (arg));
          else
            g_warning ("Invalid string. This should not happen.");
        }
    }
  else
    {
      argc = 0;
      argv = NULL;
    }

  if (!clutter_gst_init (&argc, &argv))
    PyErr_SetString (PyExc_RuntimeError, "cluttergst initialization error");

  /* set the LC_NUMERIC locale back to "C", as Python < 2.4 requires that
   * it be set that way. */
#if PY_VERSION_HEX < 0x020400F0
  setlocale(LC_NUMERIC, "C");
#endif

  if (argv != NULL)
    g_strfreev (argv);
}

DL_EXPORT (void)
init_cluttergst (void)
{
  PyObject *m, *d;

  init_pygobject ();

  m = Py_InitModule ("_cluttergst", pycluttergst_functions);
  d = PyModule_GetDict (m);

  init_clutter_gst ();
  pycluttergst_register_classes (d);

  if (PyErr_Occurred ())
    Py_FatalError ("unable to initialise cluttergst module");
}
