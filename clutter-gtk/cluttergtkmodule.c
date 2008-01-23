#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pygobject.h>
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/gtk-clutter-embed.h>

void pycluttergtk_register_classes (PyObject *d);
extern PyMethodDef pycluttergtk_functions[];

DL_EXPORT (void)
initcluttergtk (void)
{
        PyObject *m, *d;

        init_pygobject ();

        if (PyImport_ImportModule ("clutter") == NULL) {
                PyErr_SetString (PyExc_ImportError,
                                 "could not import clutter");
                return;
        }

        if (PyImport_ImportModule ("gtk") == NULL) {
                PyErr_SetString (PyExc_ImportError,
                                 "could not import gtk");
                return;
        }

        m = Py_InitModule ("cluttergtk", pycluttergtk_functions);
        d = PyModule_GetDict (m);

        pycluttergtk_register_classes (d);

        if (PyErr_Occurred ()) {
                Py_FatalError ("unable to initialise cluttergtk module");
        }
}
