#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>
#include "pyclutter.h"

#ifdef HAVE_PYCAIRO
# include <pycairo.h>
Pycairo_CAPI_t *Pycairo_CAPI;
#endif

void pyclutter_register_classes (PyObject *dict);
void pyclutter_add_constants (PyObject *module, const gchar *prefix);
void pycogl_register_classes (PyObject *dict);

extern PyMethodDef pyclutter_functions[];
extern PyMethodDef pycogl_functions[];

static PyObject *PyClutterDeprecationWarning;
PyObject *PyClutterWarning;

static void
sink_clutteractor (GObject *object)
{
    if (g_object_is_floating (object)) {
        g_object_ref_sink (object);
    }
}

static void
sink_clutteralpha (GObject *object)
{
    if (g_object_is_floating (object)) {
        g_object_ref_sink (object);
    }
}

DL_EXPORT (void)
init_clutter (void)
{
  PyObject *m, *d;

  init_pygobject_check (2, 12, 0);
  g_assert (pygobject_register_class != NULL);

#ifdef HAVE_PYCAIRO
  {
    Pycairo_IMPORT;
    if (Pycairo_CAPI == NULL)
      return;
  }
#endif

  clutter_base_init ();

  pygobject_register_sinkfunc (CLUTTER_TYPE_ACTOR, sink_clutteractor);
  pygobject_register_sinkfunc (CLUTTER_TYPE_ALPHA, sink_clutteralpha);

  m = Py_InitModule ("_clutter", pyclutter_functions);
  d = PyModule_GetDict (m);

  /* pyclutter version */
  PyModule_AddObject (m, "__version__",
		      Py_BuildValue ("(iii)",
			             PYCLUTTER_MAJOR_VERSION,
				     PYCLUTTER_MINOR_VERSION,
				     PYCLUTTER_MICRO_VERSION));

  /* the version of Clutter we were compiled against */
  PyModule_AddObject (m, "clutter_version",
                      Py_BuildValue ("(iii)",
                                     CLUTTER_MAJOR_VERSION,
                                     CLUTTER_MINOR_VERSION,
                                     CLUTTER_MICRO_VERSION));

  PyModule_AddObject (m, "MAX_ALPHA",
                      Py_BuildValue ("i", CLUTTER_ALPHA_MAX_ALPHA));

  pyclutter_register_classes (d);
  pyclutter_add_constants (m, "CLUTTER_");

  PyClutterDeprecationWarning =
    PyErr_NewException ("clutter.DeprecationWarning",
                        PyExc_DeprecationWarning,
                        NULL);
  PyDict_SetItemString (d, "DeprecationWarning", PyClutterDeprecationWarning);

  PyClutterWarning = PyErr_NewException ("clutter.Warning", PyExc_Warning, NULL);
  PyDict_SetItemString (d, "Warning", PyClutterWarning);

  /* namespace cogl under clutter.cogl */
  m = Py_InitModule ("clutter.cogl", pycogl_functions);
  d = PyModule_GetDict (m);

  pycogl_register_classes (d);

  if (PyErr_Occurred ()) 
    Py_FatalError ("can't initialise module clutter");
}
