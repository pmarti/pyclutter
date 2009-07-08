#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pyclutter.h"

struct _PyClutterCallback
{
        PyObject *func;
        PyObject *data;

        gint n_params;
        GType *param_types;
};

PyClutterCallback *
pyclutter_callback_new (PyObject *func,
                        PyObject *data,
                        gint      n_params,
                        GType     param_types[])
{
        PyClutterCallback *retval;

        g_return_val_if_fail (func != NULL, NULL);

        retval = g_new0 (PyClutterCallback, 1);
        
        retval->func = func;
        Py_INCREF (retval->func);
        
        if (data) {
                retval->data = data;
                Py_INCREF (retval->data);
        }

        retval->n_params = n_params;
        if (retval->n_params) {
                if (!param_types) {
                        g_warning ("n_params is %d but param_types is "
                                   "NULL in pyclutter_callback_new()",
                                   n_params);
                        retval->n_params = 0;
                }
                else {
                        retval->param_types = g_new (GType, n_params);
                        memcpy (retval->param_types, param_types,
                                n_params * sizeof (GType));
                }
        }

        return retval;
}

void
pyclutter_callback_free (PyClutterCallback *cb)
{
        if (G_LIKELY (cb)) {
                if (cb->func) {
                        Py_DECREF (cb->func);
                        cb->func = NULL;
                }

                if (cb->data) {
                        Py_DECREF (cb->data);
                        cb->data = NULL;
                }

                if (cb->param_types) {
                        g_free (cb->param_types);
                        cb->n_params = 0;
                        cb->param_types = NULL;
                }

                g_free (cb);
        }
}

PyObject *
pyclutter_callback_invoke (PyClutterCallback *cb,
                           ...)
{
        va_list var_args;
        int i;
        PyObject *args;
        PyObject *retobj;

        if (G_UNLIKELY (!cb)) {
                g_warning ("Invalid callback set");
                return NULL;
        }

        args = PyTuple_New (cb->n_params + 1);

        va_start (var_args, cb);

        if (cb->n_params) {
                for (i = 0; i < cb->n_params; i++) {
                        PyObject *param = va_arg (var_args, PyObject*);
                        
                        PyTuple_SetItem (args, i, param);
			Py_INCREF (param);
                }
        }
        else {
                i = 0;
        }
        
        va_end (var_args);
        
        /* append the data */
        if (cb->data) {
                PyTuple_SetItem (args, i, cb->data);
                Py_INCREF (cb->data);
        }

        retobj = PyObject_CallObject (cb->func, args);

	Py_XDECREF (args);
	
        return retobj;
}

gboolean
pyclutter_geometry_from_pyobject (PyObject        *object,
                                  ClutterGeometry *geometry)
{
        g_return_val_if_fail (geometry != NULL, FALSE);

        if (pyg_boxed_check (object, CLUTTER_TYPE_GEOMETRY)) {
                *geometry = *pyg_boxed_get (object, ClutterGeometry);
                return TRUE;
        }

        if (PyTuple_Check (object) && (PyTuple_Size (object) == 4)) {
                int i;

                for (i = 0; i < 4; i++) {
                        PyObject *comp = PyTuple_GetItem (object, i);

                        if (!PyInt_Check (comp))
                                goto out;

                        switch (i) {
                        case 0: geometry->x      = PyInt_AsLong (comp); break;
                        case 1: geometry->y      = PyInt_AsLong (comp); break;
                        case 2: geometry->width  = PyInt_AsLong (comp); break;
                        case 3: geometry->height = PyInt_AsLong (comp); break;
                        default:
                                g_assert_not_reached ();
                                break;
                        }
                }

                return TRUE;
        }

out:
        PyErr_Clear ();
        PyErr_SetString (PyExc_TypeError, "could not convert to ClutterGeometry");

        return FALSE;
}

gboolean
pyclutter_color_from_pyobject (PyObject     *object,
                               ClutterColor *color)
{
        g_return_val_if_fail (color != NULL, FALSE);

        if (pyg_boxed_check (object, CLUTTER_TYPE_COLOR)) {
                *color = *pyg_boxed_get (object, ClutterColor);
                return TRUE;
        }

        if (PyTuple_Check (object) && (PyTuple_Size (object) == 4)) {
                int i;

                for (i = 0; i < 4; i++) {
                        PyObject *comp = PyTuple_GetItem (object, i);

                        if (!PyInt_Check (comp))
                                goto out;

                        switch (i) {
                        case 0: color->red   = PyInt_AsLong (comp); break;
                        case 1: color->green = PyInt_AsLong (comp); break;
                        case 2: color->blue  = PyInt_AsLong (comp); break;
                        case 3: color->alpha = PyInt_AsLong (comp); break;
                        default:
                                g_assert_not_reached ();
                                break;
                        }
                }

                return TRUE;
        }

out:
        PyErr_Clear ();
        PyErr_SetString (PyExc_TypeError, "could not convert to ClutterColor");

        return FALSE;
}

gboolean
pycogl_color_from_pyobject (PyObject  *object,
                            CoglColor *color)
{
        g_return_val_if_fail (color != NULL, FALSE);

        if (pyg_boxed_check (object, CLUTTER_TYPE_COLOR))
          {
            ClutterColor *c = pyg_boxed_get (object, ClutterColor);
            cogl_color_set_from_4ub (color, c->red, c->green, c->blue, c->alpha);
            return TRUE;
          }

        if (PyTuple_Check (object) && (PyTuple_Size (object) == 4))
          {
            int i;
            float red, green, blue, alpha;
            red = green = blue = alpha = 0;

            for (i = 0; i < 4; i++)
              {
                float value;
                PyObject *comp = PyTuple_GetItem (object, i);

                if (PyInt_Check (comp))
                  value = (float) (255.0 / PyInt_AsLong (comp));
                else
                  value = PyFloat_AsDouble (comp);

                switch (i)
                  {
                  case 0: red = value; break;
                  case 1: green = value; break;
                  case 2: blue = value; break;
                  case 3: alpha = value; break;
                  default:
                          g_assert_not_reached ();
                          break;
                  }
              }

            cogl_color_set_from_4f (color, red, green, blue, alpha);

            return TRUE;
          }

        PyErr_Clear ();
        PyErr_SetString (PyExc_TypeError, "could not convert to CoglColor");

        return FALSE;
}

gboolean
pyclutter_actor_box_from_pyobject (PyObject        *object,
                                   ClutterActorBox *box)
{
        g_return_val_if_fail (box != NULL, FALSE);

        if (pyg_boxed_check (object, CLUTTER_TYPE_ACTOR_BOX)) {
                *box = *pyg_boxed_get (object, ClutterActorBox);
                return TRUE;
        }

        if (PyTuple_Check (object) && (PyTuple_Size (object) == 4)) {
                int i;

                for (i = 0; i < 4; i++) {
                        PyObject *comp = PyTuple_GetItem (object, i);

                        if (!PyInt_Check (comp))
                                goto out;

                        switch (i) {
                        case 0: box->x1 = PyInt_AsLong (comp); break;
                        case 1: box->y1 = PyInt_AsLong (comp); break;
                        case 2: box->x2 = PyInt_AsLong (comp); break;
                        case 3: box->y2 = PyInt_AsLong (comp); break;
                        default:
                                g_assert_not_reached ();
                                break;
                        }
                }

                return TRUE;
        }

out:
        PyErr_Clear ();
        PyErr_SetString (PyExc_TypeError, "could not convert to ClutterActorBox");

        return FALSE;
}

gdouble
pyclutter_alpha_func (ClutterAlpha *alpha,
                      gpointer      data)
{
        PyClutterCallback *pycb = data;
        PyGILState_STATE state;
        PyObject *py_alpha, *retobj;
        gdouble retval = 0.0;

        state = pyg_gil_state_ensure ();

        py_alpha = pygobject_new ((GObject *) alpha);
        retobj = pyclutter_callback_invoke (pycb, py_alpha);
        if (retobj == NULL)
                PyErr_Print ();

        if (PyFloat_Check (retobj)) {
                retval = (gdouble) PyFloat_AsDouble (retobj);
        } else {
                PyErr_SetString (PyExc_TypeError,
                                 "returned value is not an integer");
        }

        Py_XDECREF (retobj);
	Py_XDECREF (py_alpha);

        pyg_gil_state_release (state);
        
        return retval;
}


GType
pycogl_pixel_format_get_type (void)
{
  static GType enum_type = 0;

  if (G_UNLIKELY (enum_type == 0))
    {
      static const GEnumValue values[] = {
        { COGL_PIXEL_FORMAT_ANY, "COGL_PIXEL_FORMAT_ANY", "any" },
        { COGL_PIXEL_FORMAT_A_8, "COGL_PIXEL_FORMAT_A_8", "a-8" },
        { COGL_PIXEL_FORMAT_RGB_565, "COGL_PIXEL_FORMAT_RGB_565", "rgb-565" },
        { COGL_PIXEL_FORMAT_RGBA_4444, "COGL_PIXEL_FORMAT_RGBA_4444", "rgba-4444" },
        { COGL_PIXEL_FORMAT_RGBA_5551, "COGL_PIXEL_FORMAT_RGBA_5551", "rgba-5551" },
        { COGL_PIXEL_FORMAT_YUV, "COGL_PIXEL_FORMAT_YUV", "yuv" },
        { COGL_PIXEL_FORMAT_G_8, "COGL_PIXEL_FORMAT_G_8", "g-8" },
        { COGL_PIXEL_FORMAT_RGB_888, "COGL_PIXEL_FORMAT_RGB_888", "rgb-888" },
        { COGL_PIXEL_FORMAT_BGR_888, "COGL_PIXEL_FORMAT_BGR_888", "bgr-888" },
        { COGL_PIXEL_FORMAT_RGBA_8888, "COGL_PIXEL_FORMAT_RGBA_8888", "rgba-8888" },
        { COGL_PIXEL_FORMAT_BGRA_8888, "COGL_PIXEL_FORMAT_BGRA_8888", "bgra-8888" },
        { COGL_PIXEL_FORMAT_ARGB_8888, "COGL_PIXEL_FORMAT_ARGB_8888", "argb-8888" },
        { COGL_PIXEL_FORMAT_ABGR_8888, "COGL_PIXEL_FORMAT_ABGR_8888", "abgr-8888" },
        { COGL_PIXEL_FORMAT_RGBA_8888_PRE, "COGL_PIXEL_FORMAT_RGBA_8888_PRE", "rgba-8888-pre" },
        { COGL_PIXEL_FORMAT_BGRA_8888_PRE, "COGL_PIXEL_FORMAT_BGRA_8888_PRE", "bgra-8888-pre" },
        { COGL_PIXEL_FORMAT_ARGB_8888_PRE, "COGL_PIXEL_FORMAT_ARGB_8888_PRE", "argb-8888-pre" },
        { COGL_PIXEL_FORMAT_ABGR_8888_PRE, "COGL_PIXEL_FORMAT_ABGR_8888_PRE", "abgr-8888-pre" },
        { COGL_PIXEL_FORMAT_RGBA_4444_PRE, "COGL_PIXEL_FORMAT_RGBA_4444_PRE", "rgba-4444-pre" },
        { COGL_PIXEL_FORMAT_RGBA_5551_PRE, "COGL_PIXEL_FORMAT_RGBA_5551_PRE", "rgba-5551-pre" },
        { 0, NULL, NULL }
      };

      enum_type = g_enum_register_static (g_intern_string ("CoglPixelFormat"),
                                          values);
    }

  return enum_type;
}

GType
pycogl_feature_flags_get_type (void)
{
  static GType flags_type = 0;

  if (G_UNLIKELY (flags_type == 0))
    {
      const GFlagsValue values[] = {
        { COGL_FEATURE_TEXTURE_RECTANGLE, "COGL_FEATURE_TEXTURE_RECTANGLE", "texture-rectangle" },
        { COGL_FEATURE_TEXTURE_NPOT, "COGL_FEATURE_TEXTURE_NPOT", "texture-npot" },
        { COGL_FEATURE_TEXTURE_YUV, "COGL_FEATURE_TEXTURE_YUV", "yuv" },
        { COGL_FEATURE_TEXTURE_READ_PIXELS, "COGL_FEATURE_TEXTURE_READ_PIXELS", "read-pixels" },
        { COGL_FEATURE_SHADERS_GLSL, "COGL_FEATURE_SHADERS_GLSL", "shaders-glsl" },
        { COGL_FEATURE_OFFSCREEN, "COGL_FEATURE_OFFSCREEN", "offscreen" },
        { COGL_FEATURE_OFFSCREEN_MULTISAMPLE, "COGL_FEATURE_OFFSCREEN_MULTISAMPLE", "offscreen-multisample" },
        { COGL_FEATURE_OFFSCREEN_BLIT, "COGL_FEATURE_OFFSCREEN_BLIT", "offscreen-blit" },
        { COGL_FEATURE_FOUR_CLIP_PLANES, "COGL_FEATURE_FOUR_CLIP_PLANES", "four-clip-planes" },
        { COGL_FEATURE_STENCIL_BUFFER, "COGL_FEATURE_STENCIL_BUFFER", "stencil-buffer" },
        { 0, NULL, NULL }
      };

      flags_type = g_flags_register_static (g_intern_static_string ("CoglFeatureFlags"), values);
    }

  return flags_type;
}
