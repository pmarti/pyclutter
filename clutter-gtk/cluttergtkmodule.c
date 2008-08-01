#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/gtk-clutter-embed.h>

void pycluttergtk_register_classes (PyObject *d);
extern PyMethodDef pycluttergtk_functions[];

/* clutter-gtk requires its own initialization function, which calls the
 * equivalent functions from GTK+ and Clutter in the right order.
 */
static void
init_clutter_gtk (void)
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
            g_warning ("Invalid string object. This should not happen");
        }
    }
  else
    {
      argc = 0;
      argv = NULL;
    }

  if (!gtk_clutter_init (&argc, &argv))
    PyErr_SetString (PyExc_RuntimeError, "cluttergtk initialization error");

  /* set the LC_NUMERIC locale back to "C", as Python < 2.4 requires that
   * it be set that way. */
#if PY_VERSION_HEX < 0x020400F0
  setlocale(LC_NUMERIC, "C");
#endif

  if (argv != NULL)
    g_strfreev (argv);
}

DL_EXPORT (void)
init_cluttergtk (void)
{
  PyObject *m, *d;

  init_pygobject ();

  m = Py_InitModule ("_cluttergtk", pycluttergtk_functions);
  d = PyModule_GetDict (m);

  init_clutter_gtk ();
  pycluttergtk_register_classes (d);

  if (PyErr_Occurred ())
    Py_FatalError ("unable to initialise cluttergtk module");
}
