#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>
#include <tidy/tidy.h>

void pytidy_add_constants (PyObject *module, const gchar *prefix);
void pytidy_register_classes (PyObject *d);

extern PyMethodDef pytidy_functions[];

DL_EXPORT (void)
inittidy (void)
{
        PyObject *m, *d;

        init_pygobject ();

        if (PyImport_ImportModule ("clutter") == NULL) {
                PyErr_SetString (PyExc_ImportError,
                                 "could not import clutter");
                return;
        }

        m = Py_InitModule ("tidy", pytidy_functions);
        d = PyModule_GetDict (m);

        pytidy_register_classes (d);

        if (PyErr_Occurred ()) {
                Py_FatalError ("unable to initialise tidy module");
        }
}
