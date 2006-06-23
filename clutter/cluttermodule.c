#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>

void clutter_register_classes (PyObject *d);
extern PyMethodDef clutter_functions[];

DL_EXPORT (void)
initclutter (void)
{
  PyObject *m, *d;

  init_pygobject ();
  /* init_pygtk(); */

  m = Py_InitModule ("clutter", clutter_functions);
  d = PyModule_GetDict (m);

  clutter_register_classes (d);

  if (PyErr_Occurred ()) 
    {
      Py_FatalError ("can't initialise module clutter");
    }
  else
    clutter_init (NULL, NULL);
}
