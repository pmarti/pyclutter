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

extern PyMethodDef pyclutter_functions[];

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

  PyModule_AddObject (m, "__version__",
		      Py_BuildValue ("(iii)",
			             PYCLUTTER_MAJOR_VERSION,
				     PYCLUTTER_MINOR_VERSION,
				     PYCLUTTER_MICRO_VERSION));
  PyModule_AddObject (m, "MAX_ALPHA",
                      Py_BuildValue ("i", CLUTTER_ALPHA_MAX_ALPHA));

  pyclutter_add_constants (m, "CLUTTER_");
  pyclutter_register_classes (d);

  PyClutterDeprecationWarning =
    PyErr_NewException ("clutter.DeprecationWarning",
                        PyExc_DeprecationWarning,
                        NULL);
  PyDict_SetItemString (d, "DeprecationWarning", PyClutterDeprecationWarning);

  PyClutterWarning = PyErr_NewException ("clutter.Warning", PyExc_Warning, NULL);
  PyDict_SetItemString (d, "Warning", PyClutterWarning);

  if (PyErr_Occurred ()) 
    Py_FatalError ("can't initialise module clutter");
}
