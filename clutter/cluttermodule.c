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
void pycogl_add_constants (PyObject *module, const gchar *prefix);

extern PyMethodDef pyclutter_functions[];
extern PyMethodDef pycogl_functions[];

static PyObject *PyClutterDeprecationWarning;
PyObject *PyClutterWarning;
PyObject *PyClutterException;

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

static void
pyclutter_register_exceptions (PyObject *dict)
{
  PyClutterDeprecationWarning =
    PyErr_NewException ("clutter.DeprecationWarning",
                        PyExc_DeprecationWarning,
                        NULL);
  PyDict_SetItemString (dict, "DeprecationWarning", PyClutterDeprecationWarning);

  PyClutterWarning =
    PyErr_NewException ("clutter.Warning",
                        PyExc_Warning,
                        NULL);
  PyDict_SetItemString (dict, "Warning", PyClutterWarning);

  PyClutterException =
    PyErr_NewException ("clutter.Exception",
                        PyExc_Exception,
                        NULL);
  PyDict_SetItemString (dict, "Exception", PyClutterException);

  if (PyErr_Occurred ())
    PyErr_Print ();
}

static void
pycogl_add_gl_constants (PyObject *module)
{
  /* we add only the values Clutter uses internally or explicitly
   * names in the documentation; if you need something else you
   * should also be loading PyOpenGL, which exposes all the
   * enumeration values
   */
  PyModule_AddObject (module, "NEVER", Py_BuildValue ("i", CGL_NEVER));
  PyModule_AddObject (module, "LESS", Py_BuildValue ("i", CGL_LESS));
  PyModule_AddObject (module, "LEQUAL", Py_BuildValue ("i", CGL_LEQUAL));
  PyModule_AddObject (module, "EQUAL", Py_BuildValue ("i", CGL_EQUAL));
  PyModule_AddObject (module, "NOTEQUAL", Py_BuildValue ("i", CGL_NOTEQUAL));
  PyModule_AddObject (module, "GEQUAL", Py_BuildValue ("i", CGL_GEQUAL));
  PyModule_AddObject (module, "GREATER", Py_BuildValue ("i", CGL_GREATER));
  PyModule_AddObject (module, "ALWAYS", Py_BuildValue ("i", CGL_ALWAYS));

  PyModule_AddObject (module, "SRC_ALPHA", Py_BuildValue ("i", CGL_SRC_ALPHA));
  PyModule_AddObject (module, "ONE_MINUS_SRC_ALPHA", Py_BuildValue ("i", CGL_ONE_MINUS_SRC_ALPHA));

  PyModule_AddObject (module, "VERTEX_SHADER", Py_BuildValue ("i", CGL_VERTEX_SHADER));
  PyModule_AddObject (module, "FRAGMENT_SHADER", Py_BuildValue ("i", CGL_FRAGMENT_SHADER));
  PyModule_AddObject (module, "OBJECT_COMPILE_STATUS", Py_BuildValue ("i", CGL_OBJECT_COMPILE_STATUS));

  PyModule_AddObject (module, "NEAREST", Py_BuildValue ("i", CGL_NEAREST));
  PyModule_AddObject (module, "LINEAR", Py_BuildValue ("i", CGL_LINEAR));
  PyModule_AddObject (module, "LINEAR_MIPMAP_LINEAR", Py_BuildValue ("i", CGL_LINEAR_MIPMAP_LINEAR));

  if (PyErr_Occurred ())
    PyErr_Print ();
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
  pyclutter_register_exceptions (d);
  pyclutter_add_constants (m, "CLUTTER_");

  /* namespace cogl under clutter.cogl */
  m = Py_InitModule ("clutter.cogl", pycogl_functions);
  d = PyModule_GetDict (m);

  pycogl_register_classes (d);
  pycogl_add_constants (m, "COGL_");
  pycogl_add_gl_constants (m);

  if (PyErr_Occurred ()) 
    Py_FatalError ("can't initialise module clutter");
}
