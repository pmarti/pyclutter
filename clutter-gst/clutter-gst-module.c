#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>
#include <clutter-gst/clutter-gst.h>
#include <pyclutter.h>

void pyclutter_gst_register_classes (PyObject *dict);
void pyclutter_gst_add_constants (PyObject *module, const char *prefix);

extern PyMethodDef pyclutter_gst_functions[];

DL_EXPORT (void)
init_clutter_gst (void)
{
  PyObject *m, *d;

  init_pygobject ();

  m = Py_InitModule ("_clutter.gst", pyclutter_gst_functions);
  d = PyModule_GetDict (m);

  pyclutter_gst_add_constants (m, "CLUTTER_GST_");
  pyclutter_gst_register_classes (d);

  if (PyErr_Occurred ())
    {
      Py_FatalError ("can't initialise module clutter.gst");
    }
}
