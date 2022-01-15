#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>

#define ICE_BATT_IMPL 1
#include "ice_batt.h"

// MRuby `typedef`s mrb_int in the mruby/value.h
// Then `#define`s mrb_int in mruby.h
// We need to undo the macro and avoid it's usage
// FIXME: I'm surely doing something wrong
#ifdef mrb_int
#undef mrb_int
#endif

void *(*drb_symbol_lookup)(const char *sym) = NULL;

static void (*drb_free_foreign_object_f)(mrb_state *, void *);
static void (*drb_typecheck_float_f)(mrb_state *, mrb_value);
static void (*drb_typecheck_int_f)(mrb_state *, mrb_value);
static void (*drb_typecheck_bool_f)(mrb_state *, mrb_value);
static void (*drb_typecheck_aggregate_f)(mrb_state *, mrb_value, struct RClass *, mrb_data_type *);
static struct RClass *(*mrb_module_get_f)(mrb_state *, const char *);
static mrb_int (*mrb_get_args_f)(mrb_state *, mrb_args_format, ...);
static struct RClass *(*mrb_module_get_under_f)(mrb_state *, struct RClass *, const char *);
static struct RClass *(*mrb_class_get_under_f)(mrb_state *, struct RClass *, const char *);
static struct RClass *(*mrb_define_module_under_f)(mrb_state *, struct RClass *, const char *);
static void (*mrb_define_module_function_f)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
static struct RClass *(*mrb_define_class_under_f)(mrb_state *, struct RClass *, const char *, struct RClass *);
static void (*mrb_define_method_f)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
static void (*mrb_define_class_method_f)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
static struct RData *(*mrb_data_object_alloc_f)(mrb_state *, struct RClass *, void *, const mrb_data_type *);
static mrb_value (*mrb_str_new_cstr_f)(mrb_state *, const char *);
static void (*mrb_raise_f)(mrb_state *, struct RClass *, const char *);
static void (*mrb_raisef_f)(mrb_state *, struct RClass *, const char *, ...);
static mrb_value (*drb_float_value_f)(mrb_state *, mrb_float);
static struct RClass *(*drb_getruntime_error_f)(mrb_state *);
static struct RClass *(*drb_getargument_error_f)(mrb_state *);
static void drb_free_foreign_object_indirect(mrb_state *state, void *pointer) {
    drb_free_foreign_object_f(state, pointer);
}
static int drb_ffi__ZTSi_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSi_ToRuby(mrb_state *state, int value) {
    return mrb_fixnum_value(value);
}
static ice_batt_error drb_ffi__ZTS14ice_batt_error_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS14ice_batt_error_ToRuby(mrb_state *state, ice_batt_error value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSP13ice_batt_info {
    drb_foreign_object_kind kind;
    ice_batt_info *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP13ice_batt_info = {"ice_batt_info*", drb_free_foreign_object_indirect};
static ice_batt_info *drb_ffi__ZTSP13ice_batt_info_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_batt_infoPointer");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSP13ice_batt_info);
    return ((struct drb_foreign_object_ZTSP13ice_batt_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP13ice_batt_info_ToRuby(mrb_state *state, ice_batt_info *value) {
    struct drb_foreign_object_ZTSP13ice_batt_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP13ice_batt_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_batt_infoPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP13ice_batt_info);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS13ice_batt_info {
    drb_foreign_object_kind kind;
    ice_batt_info value;
};
static mrb_data_type ForeignObjectType_ZTS13ice_batt_info = {"ice_batt_info", drb_free_foreign_object_indirect};
static ice_batt_info drb_ffi__ZTS13ice_batt_info_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_batt_info");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTS13ice_batt_info);
    return ((struct drb_foreign_object_ZTS13ice_batt_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS13ice_batt_info_ToRuby(mrb_state *state, ice_batt_info value) {
    struct drb_foreign_object_ZTS13ice_batt_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS13ice_batt_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_batt_info");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS13ice_batt_info);
    return mrb_obj_value(rdata);
}
static ice_batt_bool drb_ffi__ZTS13ice_batt_bool_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS13ice_batt_bool_ToRuby(mrb_state *state, ice_batt_bool value) {
    return mrb_fixnum_value(value);
}
static unsigned int drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, unsigned int value) {
    return mrb_fixnum_value(value);
}
static mrb_value drb_ffi__ZTSP13ice_batt_info_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP13ice_batt_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP13ice_batt_info));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(ice_batt_info));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "Ice_batt_infoPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP13ice_batt_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP13ice_batt_info_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS13ice_batt_info_ToRuby(mrb, *drb_ffi__ZTSP13ice_batt_info_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP13ice_batt_info_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP13ice_batt_info_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP13ice_batt_info_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS13ice_batt_info_ToRuby(mrb, drb_ffi__ZTSP13ice_batt_info_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP13ice_batt_info_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ice_batt_info new_value = drb_ffi__ZTS13ice_batt_info_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP13ice_batt_info_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_batt_info_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS13ice_batt_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS13ice_batt_info *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_batt_info");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS13ice_batt_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS13ice_batt_info_exists_Get(mrb_state *state, mrb_value self) {
    ice_batt_info record = drb_ffi__ZTS13ice_batt_info_FromRuby(state, self);
    return drb_ffi__ZTS13ice_batt_bool_ToRuby(state, record.exists);
}
static mrb_value drb_ffi__ZTS13ice_batt_info_exists_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_batt_bool new_value = drb_ffi__ZTS13ice_batt_bool_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_batt_info *)DATA_PTR(self))->value)->exists = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_batt_info_charging_Get(mrb_state *state, mrb_value self) {
    ice_batt_info record = drb_ffi__ZTS13ice_batt_info_FromRuby(state, self);
    return drb_ffi__ZTS13ice_batt_bool_ToRuby(state, record.charging);
}
static mrb_value drb_ffi__ZTS13ice_batt_info_charging_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_batt_bool new_value = drb_ffi__ZTS13ice_batt_bool_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_batt_info *)DATA_PTR(self))->value)->charging = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_batt_info_level_Get(mrb_state *state, mrb_value self) {
    ice_batt_info record = drb_ffi__ZTS13ice_batt_info_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.level);
}
static mrb_value drb_ffi__ZTS13ice_batt_info_level_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_batt_info *)DATA_PTR(self))->value)->level = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_batt_get_info_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_batt_get_info': wrong number of arguments (%d for 1)", argc);
    ice_batt_info *batt_info_0 = drb_ffi__ZTSP13ice_batt_info_FromRuby(state, args[0]);
    ice_batt_error ret_val = ice_batt_get_info(batt_info_0);
    return drb_ffi__ZTS14ice_batt_error_ToRuby(state, ret_val);
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *));
DRB_FFI_EXPORT
void drb_register_c_extensions(void *(*lookup)(const char *), mrb_state *state, struct RClass *FFI) {
    if (drb_ffi_init_indirect_functions(lookup))
        return;
    struct RClass *module = mrb_define_module_under_f(state, FFI, "CExt");
    struct RClass *object_class = state->object_class;
    mrb_define_module_function_f(state, module, "ice_batt_get_info", drb_ffi_ice_batt_get_info_Binding, MRB_ARGS_REQ(1));
    struct RClass *Ice_batt_infoPointerClass = mrb_define_class_under_f(state, module, "Ice_batt_infoPointer", object_class);
    mrb_define_class_method_f(state, Ice_batt_infoPointerClass, "new", drb_ffi__ZTSP13ice_batt_info_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_batt_infoPointerClass, "value", drb_ffi__ZTSP13ice_batt_info_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_batt_infoPointerClass, "[]", drb_ffi__ZTSP13ice_batt_info_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_batt_infoPointerClass, "[]=", drb_ffi__ZTSP13ice_batt_info_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, Ice_batt_infoPointerClass, "nil?", drb_ffi__ZTSP13ice_batt_info_IsNil, MRB_ARGS_REQ(0));
    struct RClass *Ice_batt_infoClass = mrb_define_class_under_f(state, module, "Ice_batt_info", object_class);
    mrb_define_class_method_f(state, Ice_batt_infoClass, "new", drb_ffi__ZTS13ice_batt_info_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_batt_infoClass, "exists", drb_ffi__ZTS13ice_batt_info_exists_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_batt_infoClass, "exists=", drb_ffi__ZTS13ice_batt_info_exists_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_batt_infoClass, "charging", drb_ffi__ZTS13ice_batt_info_charging_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_batt_infoClass, "charging=", drb_ffi__ZTS13ice_batt_info_charging_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_batt_infoClass, "level", drb_ffi__ZTS13ice_batt_info_level_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_batt_infoClass, "level=", drb_ffi__ZTS13ice_batt_info_level_Set, MRB_ARGS_REQ(1));
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *fnname)) {
  drb_symbol_lookup = lookup;
  if (!(drb_float_value_f = (mrb_value (*)(mrb_state *, mrb_float)) lookup("drb_float_value"))) return -1;
  if (!(drb_free_foreign_object_f = (void (*)(mrb_state *, void *)) lookup("drb_free_foreign_object"))) return -1;
  if (!(drb_getargument_error_f = (struct RClass *(*)(mrb_state *)) lookup("drb_getargument_error"))) return -1;
  if (!(drb_getruntime_error_f = (struct RClass *(*)(mrb_state *)) lookup("drb_getruntime_error"))) return -1;
  if (!(drb_typecheck_aggregate_f = (void (*)(mrb_state *, mrb_value, struct RClass *, mrb_data_type *)) lookup("drb_typecheck_aggregate"))) return -1;
  if (!(drb_typecheck_bool_f = (void (*)(mrb_state *, mrb_value)) lookup("drb_typecheck_bool"))) return -1;
  if (!(drb_typecheck_float_f = (void (*)(mrb_state *, mrb_value)) lookup("drb_typecheck_float"))) return -1;
  if (!(drb_typecheck_int_f = (void (*)(mrb_state *, mrb_value)) lookup("drb_typecheck_int"))) return -1;
  if (!(mrb_class_get_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_class_get_under"))) return -1;
  if (!(mrb_data_object_alloc_f = (struct RData *(*)(mrb_state *, struct RClass *, void *, const mrb_data_type *)) lookup("mrb_data_object_alloc"))) return -1;
  if (!(mrb_define_class_method_f = (void (*)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec)) lookup("mrb_define_class_method"))) return -1;
  if (!(mrb_define_class_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *, struct RClass *)) lookup("mrb_define_class_under"))) return -1;
  if (!(mrb_define_method_f = (void (*)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec)) lookup("mrb_define_method"))) return -1;
  if (!(mrb_define_module_function_f = (void (*)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec)) lookup("mrb_define_module_function"))) return -1;
  if (!(mrb_define_module_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_define_module_under"))) return -1;
  if (!(mrb_get_args_f = (mrb_int (*)(mrb_state *, mrb_args_format, ...)) lookup("mrb_get_args"))) return -1;
  if (!(mrb_module_get_f = (struct RClass *(*)(mrb_state *, const char *)) lookup("mrb_module_get"))) return -1;
  if (!(mrb_module_get_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_module_get_under"))) return -1;
  if (!(mrb_raise_f = (void (*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_raise"))) return -1;
  if (!(mrb_raisef_f = (void (*)(mrb_state *, struct RClass *, const char *, ...)) lookup("mrb_raisef"))) return -1;
  if (!(mrb_str_new_cstr_f = (mrb_value (*)(mrb_state *, const char *)) lookup("mrb_str_new_cstr"))) return -1;
  return 0;
}
