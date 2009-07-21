#ifndef __PYCLUTTER_PRIVATE_H__
#define __PYCLUTTER_PRIVATE_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __PYCLUTTER_H__
#error "Do not include pyclutter.h and pyclutter-private.h together."
#endif

#define __PYCLUTTER_H_INSIDE__
#include "pyclutter.h"

#ifdef COGL_TYPE_MATRIX
#define PYCOGL_TYPE_MATRIX              COGL_TYPE_MATRIX
#else
#define PYCOGL_TYPE_MATRIX              (pycogl_matrix_get_type ())
GType pycogl_matrix_get_type (void) G_GNUC_CONST;
#endif

#ifdef COGL_TYPE_COLOR
#define PYCOGL_TYPE_COLOR      COGL_TYPE_COLOR
#else
#define PYCOGL_TYPE_COLOR      (pycogl_color_get_type ())
GType pycogl_color_get_type (void) G_GNUC_CONST;
#endif

typedef struct {
    PyObject_HEAD
    CoglHandle handle;
    PyObject *base;
} PyCoglHandle;

#define PyCoglTexture      PyCoglHandle

#endif /* __PYCLUTTER_PRIVATE_H__ */
