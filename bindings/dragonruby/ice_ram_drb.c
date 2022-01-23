#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>

#define ICE_RAM_IMPL 1
#include "ice_ram.h"

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
static ice_ram_bool drb_ffi__ZTS12ice_ram_bool_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS12ice_ram_bool_ToRuby(mrb_state *state, ice_ram_bool value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSP12ice_ram_info {
    drb_foreign_object_kind kind;
    ice_ram_info *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP12ice_ram_info = {"ice_ram_info*", drb_free_foreign_object_indirect};
static ice_ram_info *drb_ffi__ZTSP12ice_ram_info_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_RAM_INFO_PTR");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSP12ice_ram_info);
    return ((struct drb_foreign_object_ZTSP12ice_ram_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP12ice_ram_info_ToRuby(mrb_state *state, ice_ram_info *value) {
    struct drb_foreign_object_ZTSP12ice_ram_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP12ice_ram_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_RAM_INFO_PTR");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP12ice_ram_info);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS12ice_ram_info {
    drb_foreign_object_kind kind;
    ice_ram_info value;
};
static mrb_data_type ForeignObjectType_ZTS12ice_ram_info = {"ICE_RAM_INFO", drb_free_foreign_object_indirect};
static ice_ram_info drb_ffi__ZTS12ice_ram_info_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_RAM_INFO");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTS12ice_ram_info);
    return ((struct drb_foreign_object_ZTS12ice_ram_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS12ice_ram_info_ToRuby(mrb_state *state, ice_ram_info value) {
    struct drb_foreign_object_ZTS12ice_ram_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS12ice_ram_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_RAM_INFO");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS12ice_ram_info);
    return mrb_obj_value(rdata);
}
static ice_ram_bytes drb_ffi__ZTSy_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSy_ToRuby(mrb_state *state, ice_ram_bytes value) {
    return mrb_fixnum_value(value);
}
static mrb_value drb_ffi__ZTSP12ice_ram_info_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP12ice_ram_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP12ice_ram_info));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(ice_ram_info));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "ICE_RAM_INFO_PTR");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP12ice_ram_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP12ice_ram_info_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS12ice_ram_info_ToRuby(mrb, *drb_ffi__ZTSP12ice_ram_info_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP12ice_ram_info_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP12ice_ram_info_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP12ice_ram_info_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS12ice_ram_info_ToRuby(mrb, drb_ffi__ZTSP12ice_ram_info_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP12ice_ram_info_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ice_ram_info new_value = drb_ffi__ZTS12ice_ram_info_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP12ice_ram_info_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS12ice_ram_info_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS12ice_ram_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS12ice_ram_info *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_RAM_INFO");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS12ice_ram_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS12ice_ram_info_free_Get(mrb_state *state, mrb_value self) {
    ice_ram_info record = drb_ffi__ZTS12ice_ram_info_FromRuby(state, self);
    return drb_ffi__ZTSy_ToRuby(state, record.free);
}
static mrb_value drb_ffi__ZTS12ice_ram_info_free_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_ram_bytes new_value = drb_ffi__ZTSy_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ice_ram_info *)DATA_PTR(self))->value)->free = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS12ice_ram_info_used_Get(mrb_state *state, mrb_value self) {
    ice_ram_info record = drb_ffi__ZTS12ice_ram_info_FromRuby(state, self);
    return drb_ffi__ZTSy_ToRuby(state, record.used);
}
static mrb_value drb_ffi__ZTS12ice_ram_info_used_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_ram_bytes new_value = drb_ffi__ZTSy_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ice_ram_info *)DATA_PTR(self))->value)->used = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS12ice_ram_info_total_Get(mrb_state *state, mrb_value self) {
    ice_ram_info record = drb_ffi__ZTS12ice_ram_info_FromRuby(state, self);
    return drb_ffi__ZTSy_ToRuby(state, record.total);
}
static mrb_value drb_ffi__ZTS12ice_ram_info_total_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_ram_bytes new_value = drb_ffi__ZTSy_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ice_ram_info *)DATA_PTR(self))->value)->total = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_ram_get_info_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_ram_get_info': wrong number of arguments (%d for 1)", argc);
    ice_ram_info *ram_info_0 = drb_ffi__ZTSP12ice_ram_info_FromRuby(state, args[0]);
    ice_ram_bool ret_val = ice_ram_get_info(ram_info_0);
    return drb_ffi__ZTS12ice_ram_bool_ToRuby(state, ret_val);
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *));
DRB_FFI_EXPORT
void drb_register_c_extensions(void *(*lookup)(const char *), mrb_state *state, struct RClass *FFI) {
    if (drb_ffi_init_indirect_functions(lookup))
        return;
    struct RClass *module = mrb_define_module_under_f(state, FFI, "CExt");
    struct RClass *object_class = state->object_class;
    mrb_define_module_function_f(state, module, "ice_ram_get_info", drb_ffi_ice_ram_get_info_Binding, MRB_ARGS_REQ(1));
    struct RClass *ice_ram_info_ptr_class = mrb_define_class_under_f(state, module, "ICE_RAM_INFO_PTR", object_class);
    mrb_define_class_method_f(state, ice_ram_info_ptr_class, "new", drb_ffi__ZTSP12ice_ram_info_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_ram_info_ptr_class, "value", drb_ffi__ZTSP12ice_ram_info_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_ram_info_ptr_class, "[]", drb_ffi__ZTSP12ice_ram_info_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_ram_info_ptr_class, "[]=", drb_ffi__ZTSP12ice_ram_info_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, ice_ram_info_ptr_class, "nil?", drb_ffi__ZTSP12ice_ram_info_IsNil, MRB_ARGS_REQ(0));
    struct RClass *ice_ram_info_class = mrb_define_class_under_f(state, module, "ICE_RAM_INFO", object_class);
    mrb_define_class_method_f(state, ice_ram_info_class, "new", drb_ffi__ZTS12ice_ram_info_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_ram_info_class, "free", drb_ffi__ZTS12ice_ram_info_free_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_ram_info_class, "free=", drb_ffi__ZTS12ice_ram_info_free_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_ram_info_class, "used", drb_ffi__ZTS12ice_ram_info_used_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_ram_info_class, "used=", drb_ffi__ZTS12ice_ram_info_used_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_ram_info_class, "total", drb_ffi__ZTS12ice_ram_info_total_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_ram_info_class, "total=", drb_ffi__ZTS12ice_ram_info_total_Set, MRB_ARGS_REQ(1));
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
