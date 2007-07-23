#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#include <Python.h>
#include <pygobject.h>

#include <pango/pangocairo.h>
#include <pycairo.h>

void pycluttercairo_register_classes (PyObject *d);
void pycluttercairo_add_constants (PyObject *module, const gchar *strip_prefix);

extern PyMethodDef pycluttercairo_functions[];
extern PyTypeObject PyClutterCairoContext_Type;

Pycairo_CAPI_t *Pycairo_CAPI;

DL_EXPORT(void)
initcluttercairo (void)
{
    PyObject *m, *d;

    /* perform any initialisation required by the library here */

    m = Py_InitModule ("cluttercairo", pycluttercairo_functions);
    d = PyModule_GetDict (m);

    Pycairo_IMPORT;
    if (Pycairo_CAPI == NULL)
        return;

    PyClutterCairoContext_Type.tp_base = &PycairoContext_Type;
    if (PyType_Ready(&PyClutterCairoContext_Type) < 0) {
        g_return_if_reached ();
    }

    init_pygobject ();

    pycluttercairo_register_classes (d);

    Py_INCREF (&PyClutterCairoContext_Type);
    PyModule_AddObject (m, "CairoContext",
                        (PyObject *) &PyClutterCairoContext_Type)
;
}
