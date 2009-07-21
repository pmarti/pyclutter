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


typedef struct {
    PyObject_HEAD
    CoglHandle handle;
    PyObject *base;
} PyCoglHandle;

typedef struct {
    PyObject_HEAD
    CoglMatrix matrix;
} PyCoglMatrix;

#define PyCoglTexture      PyCoglHandle
#define PyCoglMaterial     PyCoglHandle
#define PyCoglShader       PyCoglHandle
#define PyCoglProgram      PyCoglHandle

#endif /* __PYCLUTTER_PRIVATE_H__ */
