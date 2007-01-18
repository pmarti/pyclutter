#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <clutter/clutter.h>
#include <clutter-gst/clutter-gst.h>

void pycluttergst_register_classes (PyObject *d);
extern PyMethodDef pycluttergst_functions[];

DL_EXPORT (void)
initcluttergst (void)
{
        PyObject *m, *d;

        init_pygobject ();
        
        m = Py_InitModule ("cluttergst", pycluttergst_functions);
        d = PyModule_GetDict (m);

        pycluttergst_register_classes (d);
}
