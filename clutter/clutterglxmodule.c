#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>
#include <clutter/glx/clutter-glx.h>

void pyclutterglx_register_classes (PyObject *d);
extern PyMethodDef pyclutterglx_functions[];


DL_EXPORT (void)
initglx (void)
{
  PyObject *m, *d;

  init_pygobject ();

  m = Py_InitModule ("glx", pyclutterglx_functions);
  d = PyModule_GetDict (m);

  pyclutterglx_register_classes (d);

  if (PyErr_Occurred ())
    Py_FatalError ("unable to initialise clutter.glx module");
}
