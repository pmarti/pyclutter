#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>

void clutter_register_classes (PyObject *dict);
void clutter_add_constants (PyObject *module, const gchar *prefix);

extern PyMethodDef clutter_functions[];

DL_EXPORT (void)
init_clutter (void)
{
  PyObject *m, *d;

  init_pygobject ();

  m = Py_InitModule ("_clutter", clutter_functions);
  PyModule_AddObject (m, "__version__",
		      Py_BuildValue ("(iii)",
			             PYCLUTTER_MAJOR_VERSION,
				     PYCLUTTER_MINOR_VERSION,
				     PYCLUTTER_MICRO_VERSION));
  d = PyModule_GetDict (m);

  clutter_add_constants (m, "CLUTTER_");
  clutter_register_classes (d);

  if (PyErr_Occurred ()) 
    {
      Py_FatalError ("can't initialise module clutter");
    }
  else
    clutter_init (NULL, NULL);
}
