#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <gst/gst.h>
#include <clutter/clutter.h>
#include <clutter-gst/clutter-gst.h>

void pycluttergst_register_classes (PyObject *d);
extern PyMethodDef pycluttergst_functions[];

DL_EXPORT (void)
init_gst (void)
{
        PyObject *m, *d;

        init_pygobject ();

        if (PyImport_ImportModule ("clutter") == NULL) {
                PyErr_SetString (PyExc_ImportError,
                                 "could not import clutter");
                return;
        }

        m = Py_InitModule ("_gst", pycluttergst_functions);
        d = PyModule_GetDict (m);

        pycluttergst_register_classes (d);

        if (PyErr_Occurred ()) {
                Py_FatalError ("unable to initialise cluttergst module");
        }
}
