#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>
#include "pyclutter.h"

#include <pycairo.h>
Pycairo_CAPI_t *Pycairo_CAPI;

void pyclutter_register_classes (PyObject *dict);
void pyclutter_add_constants (PyObject *module, const gchar *prefix);
void pycogl_register_classes (PyObject *dict);
void pycogl_add_constants (PyObject *module, const gchar *prefix);

extern PyMethodDef pyclutter_functions[];
extern PyMethodDef pycogl_functions[];
extern PyTypeObject PyCoglHandle_Type;
extern PyTypeObject PyCoglTexture_Type;
extern PyTypeObject PyCoglMaterial_Type;
extern PyTypeObject PyCoglMatrix_Type;
extern PyTypeObject PyCoglShader_Type;
extern PyTypeObject PyCoglProgram_Type;
extern PyTypeObject PyCoglOffscreen_Type;

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
sink_clutterpath (GObject *object)
{
    if (g_object_is_floating (object)) {
        g_object_ref_sink (object);
    }
}

static void
sink_clutterinterval (GObject *object)
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
pycogl_register_handle_classes (PyObject *m)
{
  /* cogl.Handle */
  PyCoglHandle_Type.tp_base = &PyBaseObject_Type;
  if (PyType_Ready (&PyCoglHandle_Type) < 0)
    return;
  Py_INCREF (&PyCoglHandle_Type);
  PyModule_AddObject (m, "Handle", (PyObject *)&PyCoglHandle_Type);

  /* cogl.Texture */
  PyCoglTexture_Type.tp_base = &PyCoglHandle_Type;
  if (PyType_Ready (&PyCoglTexture_Type) < 0)
    return;
  Py_INCREF (&PyCoglTexture_Type);
  PyModule_AddObject (m, "Texture", (PyObject *)&PyCoglTexture_Type);

  /* cogl.Material */
  PyCoglMaterial_Type.tp_base = &PyCoglHandle_Type;
  if (PyType_Ready (&PyCoglMaterial_Type) < 0)
    return;
  Py_INCREF (&PyCoglMaterial_Type);
  PyModule_AddObject (m, "Material", (PyObject *)&PyCoglMaterial_Type);

  /* cogl.Shader */
  PyCoglShader_Type.tp_base = &PyCoglHandle_Type;
  if (PyType_Ready (&PyCoglShader_Type) < 0)
    return;
  Py_INCREF (&PyCoglShader_Type);
  PyModule_AddObject (m, "Shader", (PyObject *)&PyCoglShader_Type);

  /* cogl.Program */
  PyCoglProgram_Type.tp_base = &PyCoglHandle_Type;
  if (PyType_Ready (&PyCoglProgram_Type) < 0)
    return;
  Py_INCREF (&PyCoglProgram_Type);
  PyModule_AddObject (m, "Program", (PyObject *)&PyCoglProgram_Type);

  /* cogl.Offscreen */
  PyCoglOffscreen_Type.tp_base = &PyCoglHandle_Type;
  if (PyType_Ready (&PyCoglOffscreen_Type) < 0)
    return;
  Py_INCREF (&PyCoglOffscreen_Type);
  PyModule_AddObject (m, "Offscreen", (PyObject *)&PyCoglOffscreen_Type);

  /* cogl.Matrix */
  PyCoglMatrix_Type.tp_base = &PyBaseObject_Type;
  if (PyType_Ready (&PyCoglMatrix_Type) < 0)
    return;
  Py_INCREF (&PyCoglMatrix_Type);
  PyModule_AddObject (m, "Matrix", (PyObject *)&PyCoglMatrix_Type);
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

  PyModule_AddObject (module, "OBJECT_COMPILE_STATUS", Py_BuildValue ("i", CGL_OBJECT_COMPILE_STATUS));

  if (PyErr_Occurred ())
    PyErr_Print ();
}

DL_EXPORT (void)
init_clutter (void)
{
  PyObject *m, *d;

  init_pygobject_check (2, 12, 0);
  g_assert (pygobject_register_class != NULL);

  Pycairo_IMPORT;
  if (Pycairo_CAPI == NULL)
    return;

  clutter_base_init ();

  pygobject_register_sinkfunc (CLUTTER_TYPE_ACTOR, sink_clutteractor);
  pygobject_register_sinkfunc (CLUTTER_TYPE_ALPHA, sink_clutteralpha);
  pygobject_register_sinkfunc (CLUTTER_TYPE_PATH, sink_clutterpath);
  pygobject_register_sinkfunc (CLUTTER_TYPE_INTERVAL, sink_clutterinterval);

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

  pyclutter_register_classes (d);
  pyclutter_register_exceptions (d);
  pyclutter_add_constants (m, "CLUTTER_");

  /* namespace cogl under clutter.cogl */
  m = Py_InitModule ("clutter.cogl", pycogl_functions);
  d = PyModule_GetDict (m);

  pycogl_register_handle_classes (m);
  pycogl_register_classes (d);
  pycogl_add_constants (m, "COGL_");
  pycogl_add_gl_constants (m);

  if (PyErr_Occurred ()) 
    Py_FatalError ("can't initialise module clutter");
}
