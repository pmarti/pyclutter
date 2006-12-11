#ifndef __PY_CLUTTER_H__
#define __PY_CLUTTER_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>

#define NO_IMPORT_PYGOBJECT
#include <pygobject.h>
#include <Python.h>
#include <clutter/clutter.h>
#include <clutter/clutter-feature.h>

G_BEGIN_DECLS

typedef struct _PyClutterCallback       PyClutterCallback;

PyClutterCallback *pyclutter_callback_new    (PyObject          *function,
                                              PyObject          *data,
                                              gint               n_params,
                                              GType              param_types[]);
void               pyclutter_callback_free   (PyClutterCallback *cb);
PyObject *         pyclutter_callback_invoke (PyClutterCallback *cb,
                                              ...);

G_END_DECLS

#endif /* __PY_CLUTTER_H__ */
