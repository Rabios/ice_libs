#define ICE_EASE_IMPL 1
#include "ice_ease.h"

#include <dragonruby.h>

static drb_api_t *drb_api;

#define drb_load_numeric_argument(name, idx, errmsg)                                \
        val = args[idx];                                                            \
        valtype = mrb_type(val);                                                    \
                                                                                    \
        if (valtype == MRB_TT_FLOAT) {                                              \
            name = mrb_float(val);                                                  \
        } else if (valtype == MRB_TT_FIXNUM) {                                      \
            name = mrb_fixnum(val);                                                 \
        } else {                                                                    \
            drb_api->mrb_raise(mrb, drb_api->drb_getruntime_error(mrb), errmsg);    \
        }                                                                           \

#define drb_bind_ease_func(fname)                                                                                                                   \
static mrb_value drb_##fname(mrb_state *mrb, mrb_value self) {                                                                                    \
    int ease_type = -1;                                                                                                                             \
    double res = 0;                                                                                                                                 \
    mrb_value *args = 0;                                                                                                                            \
    mrb_int argc = 0;                                                                                                                               \
    mrb_value val;                                                                                                                                  \
    enum mrb_vtype valtype;                                                                                                                         \
    drb_api->mrb_get_args(mrb, "*", &args, &argc);                                                                                                  \
                                                                                                                                                    \
    if ((argc != 2) && (argc != 5)) {                                                                                                               \
        drb_api->mrb_raise(mrb, drb_api->drb_getruntime_error(mrb), "Missing number of arguments (Must be 2 or 5)");                                \
    }                                                                                                                                               \
                                                                                                                                                    \
    val = args[0];                                                                                                                                  \
    valtype = mrb_type(val);                                                                                                                        \
                                                                                                                                                    \
    if (valtype != MRB_TT_FIXNUM) {                                                                                                                 \
        drb_api->mrb_raise(mrb, drb_api->drb_getruntime_error(mrb), "Easing type must be integer (Fixnum)");                                        \
    }                                                                                                                                               \
                                                                                                                                                    \
    ease_type = mrb_fixnum(val);                                                                                                                    \
                                                                                                                                                    \
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {                                                                                                      \
        double x = 0;                                                                                                                               \
        drb_load_numeric_argument(x, 1, "Argument x must be numeric!");                                                                             \
        res = fname(ease_type, x);                                                                                                                  \
                                                                                                                                                    \
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {                                                                                                 \
        double t = 0, b = 0, c = 0, d = 0;                                                                                                          \
                                                                                                                                                    \
        drb_load_numeric_argument(t, 1, "Argument t must be numeric!")                                                                              \
        drb_load_numeric_argument(b, 2, "Argument b must be numeric!")                                                                              \
        drb_load_numeric_argument(c, 3, "Argument c must be numeric!")                                                                              \
        drb_load_numeric_argument(d, 4, "Argument d must be numeric!")                                                                              \
                                                                                                                                                    \
        res = fname(ease_type, t, b, c, d);                                                                                                         \
                                                                                                                                                    \
    } else {                                                                                                                                        \
        drb_api->mrb_raise(mrb, drb_api->drb_getruntime_error(mrb), "Unknown easing type (Use ICE_EASE_TYPE_PROGRESS or ICE_EASE_TYPE_PENNER)");    \
    }                                                                                                                                               \
                                                                                                                                                    \
    return drb_api->drb_float_value(mrb, res);                                                                                                      \
}

#define drb_load_func(name) drb_api->mrb_define_module_function(state, module, #name, drb_##name, MRB_ARGS_REQ(1));

drb_bind_ease_func(ice_ease_linear)

drb_bind_ease_func(ice_ease_sine_in)
drb_bind_ease_func(ice_ease_sine_out)
drb_bind_ease_func(ice_ease_sine_in_out)

drb_bind_ease_func(ice_ease_quad_in)
drb_bind_ease_func(ice_ease_quad_out)
drb_bind_ease_func(ice_ease_quad_in_out)

drb_bind_ease_func(ice_ease_cubic_in)
drb_bind_ease_func(ice_ease_cubic_out)
drb_bind_ease_func(ice_ease_cubic_in_out)

drb_bind_ease_func(ice_ease_quart_in)
drb_bind_ease_func(ice_ease_quart_out)
drb_bind_ease_func(ice_ease_quart_in_out)

drb_bind_ease_func(ice_ease_quint_in)
drb_bind_ease_func(ice_ease_quint_out)
drb_bind_ease_func(ice_ease_quint_in_out)

drb_bind_ease_func(ice_ease_expo_in)
drb_bind_ease_func(ice_ease_expo_out)
drb_bind_ease_func(ice_ease_expo_in_out)

drb_bind_ease_func(ice_ease_circ_in)
drb_bind_ease_func(ice_ease_circ_out)
drb_bind_ease_func(ice_ease_circ_in_out)

drb_bind_ease_func(ice_ease_elastic_in)
drb_bind_ease_func(ice_ease_elastic_out)
drb_bind_ease_func(ice_ease_elastic_in_out)

drb_bind_ease_func(ice_ease_back_in)
drb_bind_ease_func(ice_ease_back_out)
drb_bind_ease_func(ice_ease_back_in_out)

drb_bind_ease_func(ice_ease_bounce_in)
drb_bind_ease_func(ice_ease_bounce_out)
drb_bind_ease_func(ice_ease_bounce_in_out)

DRB_FFI_EXPORT void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "CExt");
    struct RClass *base = state->object_class;
    
    drb_load_func(ice_ease_linear)
    
    drb_load_func(ice_ease_sine_in)
    drb_load_func(ice_ease_sine_out)
    drb_load_func(ice_ease_sine_in_out)
    
    drb_load_func(ice_ease_quad_in)
    drb_load_func(ice_ease_quad_out)
    drb_load_func(ice_ease_quad_in_out)
    
    drb_load_func(ice_ease_cubic_in)
    drb_load_func(ice_ease_cubic_out)
    drb_load_func(ice_ease_cubic_in_out)
    
    drb_load_func(ice_ease_quart_in)
    drb_load_func(ice_ease_quart_out)
    drb_load_func(ice_ease_quart_in_out)
    
    drb_load_func(ice_ease_quint_in)
    drb_load_func(ice_ease_quint_out)
    drb_load_func(ice_ease_quint_in_out)
    
    drb_load_func(ice_ease_expo_in)
    drb_load_func(ice_ease_expo_out)
    drb_load_func(ice_ease_expo_in_out)
    
    drb_load_func(ice_ease_circ_in)
    drb_load_func(ice_ease_circ_out)
    drb_load_func(ice_ease_circ_in_out)
    
    drb_load_func(ice_ease_elastic_in)
    drb_load_func(ice_ease_elastic_out)
    drb_load_func(ice_ease_elastic_in_out)
    
    drb_load_func(ice_ease_back_in)
    drb_load_func(ice_ease_back_out)
    drb_load_func(ice_ease_back_in_out)
    
    drb_load_func(ice_ease_bounce_in)
    drb_load_func(ice_ease_bounce_out)
    drb_load_func(ice_ease_bounce_in_out)
}
