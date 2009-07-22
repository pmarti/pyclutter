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
#define PyCoglOffscreen    PyCoglHandle

#endif /* __PYCLUTTER_PRIVATE_H__ */
