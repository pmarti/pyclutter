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

#ifdef COGL_TYPE_HANDLE
#define PYCOGL_TYPE_HANDLE      COGL_TYPE_HANDLE
#else
#define PYCOGL_TYPE_HANDLE      (pycogl_handle_get_type ())
GType pycogl_handle_get_type (void) G_GNUC_CONST;
#endif

#ifdef COGL_TYPE_PIXEL_FORMAT
#define PYCOGL_TYPE_PIXEL_FORMAT        COGL_TYPE_PIXEL_FORMAT
#else
#define PYCOGL_TYPE_PIXEL_FORMAT        (pycogl_pixel_format_get_type ())
GType pycogl_pixel_format_get_type (void) G_GNUC_CONST;
#endif

#ifdef COGL_TYPE_FEATURE_FLAGS
#define PYCOGL_TYPE_FEATURE_FLAGS       COGL_TYPE_FEATURE_FLAGS
#else
#define PYCOGL_TYPE_FEATURE_FLAGS       (pycogl_feature_flags_get_type ())
GType pycogl_feature_flags_get_type (void) G_GNUC_CONST;
#endif

#endif /* __PYCLUTTER_PRIVATE_H__ */
