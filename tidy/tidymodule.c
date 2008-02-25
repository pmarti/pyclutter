#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>
#include <tidy/tidy.h>

void pytidy_add_constants (PyObject *module, const gchar *prefix);
void pytidy_register_classes (PyObject *d);

extern PyMethodDef pytidy_functions[];

static void
sink_tidycellrenderer (GObject *object)
{
  if (g_object_is_floating (object))
    g_object_ref_sink (object);
}

static void
sink_tidylistcolumn (GObject *object)
{
  if (g_object_is_floating (object))
    g_object_ref_sink (object);
}

DL_EXPORT (void)
inittidy (void)
{
  PyObject *m, *d;

  init_pygobject ();

  if (PyImport_ImportModule ("clutter") == NULL) {
    PyErr_SetString (PyExc_ImportError, "could not import clutter");
    return;
  }

  pygobject_register_sinkfunc (TIDY_TYPE_CELL_RENDERER, sink_tidycellrenderer);
  pygobject_register_sinkfunc (TIDY_TYPE_LIST_COLUMN, sink_tidylistcolumn);

  m = Py_InitModule ("tidy", pytidy_functions);
  d = PyModule_GetDict (m);

  pytidy_add_constants (m, "TIDY_");
  pytidy_register_classes (d);

  if (PyErr_Occurred ())
    Py_FatalError ("unable to initialise tidy module");
}
