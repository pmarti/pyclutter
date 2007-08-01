#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <cairo/cairo.h>
#include <pycairo.h>
#include <clutter/clutter.h>
#include <clutter-cairo/clutter-cairo.h>

void pycluttercairo_register_classes (PyObject *d);
extern PyMethodDef pycluttercairo_functions[];

#if 0
extern PyTypeObject PyClutterCairoContext_Type;
#endif

Pycairo_CAPI_t *Pycairo_CAPI;

DL_EXPORT(void)
initcluttercairo (void)
{
    PyObject *m, *d;
    
    init_pygobject ();
    
    Pycairo_IMPORT;
    if (Pycairo_CAPI == NULL)
        return;

    if (PyImport_ImportModule ("clutter") == NULL) {
        PyErr_SetString (PyExc_ImportError,
                         "could not import clutter");
        return;
    }

    /* perform any initialisation required by the library here */

    m = Py_InitModule ("cluttercairo", pycluttercairo_functions);
    d = PyModule_GetDict (m);

#if 0
    PyClutterCairoContext_Type.tp_base = &PycairoContext_Type;
    if (PyType_Ready(&PyClutterCairoContext_Type) < 0) {
        g_return_if_reached ();
    }
#endif

    pycluttercairo_register_classes (d);

#if 0
    Py_INCREF (&PyClutterCairoContext_Type);
    PyModule_AddObject (m, "CairoContext",
                        (PyObject *) &PyClutterCairoContext_Type)
;
#endif

    if (PyErr_Occurred ()) {
        Py_FatalError ("unable to initialise cluttercairo module");
    }
}
