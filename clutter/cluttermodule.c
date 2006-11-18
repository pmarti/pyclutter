#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>
#include "pyclutter.h"

void pyclutter_register_classes (PyObject *dict);
void pyclutter_add_constants (PyObject *module, const gchar *prefix);

extern PyMethodDef pyclutter_functions[];

DL_EXPORT (void)
init_clutter (void)
{
  PyObject *m, *d;

  init_pygobject ();

  m = Py_InitModule ("_clutter", pyclutter_functions);
  PyModule_AddObject (m, "__version__",
		      Py_BuildValue ("(iii)",
			             PYCLUTTER_MAJOR_VERSION,
				     PYCLUTTER_MINOR_VERSION,
				     PYCLUTTER_MICRO_VERSION));
  d = PyModule_GetDict (m);

  pyclutter_add_constants (m, "CLUTTER_");
  pyclutter_register_classes (d);

  if (PyErr_Occurred ()) 
    {
      Py_FatalError ("can't initialise module clutter");
    }
  else
    clutter_init (NULL, NULL);
}
