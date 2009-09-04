#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>
#include <clutter/x11/clutter-x11.h>

void pyclutterx11_register_classes (PyObject *d);
extern PyMethodDef pyclutterx11_functions[];


DL_EXPORT (void)
initx11 (void)
{
  PyObject *m, *d;

  init_pygobject ();

  m = Py_InitModule ("x11", pyclutterx11_functions);
  d = PyModule_GetDict (m);

  pyclutterx11_register_classes (d);

  if (PyErr_Occurred ())
    Py_FatalError ("unable to initialise clutter.x11 module");
}
