#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>

#define ICE_CPU_IMPL 1
#include "ice_cpu.h"

static drb_api_t *drb_api;

static void drb_free_foreign_object_indirect(mrb_state *state, void *pointer) {
    drb_api->drb_free_foreign_object(state, pointer);
}
static int drb_ffi__ZTSi_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSi_ToRuby(mrb_state *state, int value) {
    return mrb_fixnum_value(value);
}
static ice_cpu_bool drb_ffi__ZTS12ice_cpu_bool_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS12ice_cpu_bool_ToRuby(mrb_state *state, ice_cpu_bool value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSP12ice_cpu_info {
    drb_foreign_object_kind kind;
    ice_cpu_info *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP12ice_cpu_info = {"ice_cpu_info*", drb_free_foreign_object_indirect};
static ice_cpu_info *drb_ffi__ZTSP12ice_cpu_info_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_CPU_INFO_PTR");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSP12ice_cpu_info);
    return ((struct drb_foreign_object_ZTSP12ice_cpu_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP12ice_cpu_info_ToRuby(mrb_state *state, ice_cpu_info *value) {
    struct drb_foreign_object_ZTSP12ice_cpu_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP12ice_cpu_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_CPU_INFO_PTR");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSP12ice_cpu_info);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS12ice_cpu_info {
    drb_foreign_object_kind kind;
    ice_cpu_info value;
};
static mrb_data_type ForeignObjectType_ZTS12ice_cpu_info = {"ice_cpu_info", drb_free_foreign_object_indirect};
static ice_cpu_info drb_ffi__ZTS12ice_cpu_info_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_CPU_INFO");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS12ice_cpu_info);
    return ((struct drb_foreign_object_ZTS12ice_cpu_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS12ice_cpu_info_ToRuby(mrb_state *state, ice_cpu_info value) {
    struct drb_foreign_object_ZTS12ice_cpu_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS12ice_cpu_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_CPU_INFO");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS12ice_cpu_info);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSPc {
    drb_foreign_object_kind kind;
    char *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPc = {"char*", drb_free_foreign_object_indirect};
static char *drb_ffi__ZTSPc_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    if (mrb_type(self) == MRB_TT_STRING)
        return RSTRING_PTR(self);
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "CharPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSPc);
    return ((struct drb_foreign_object_ZTSPc *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPc_ToRuby(mrb_state *state, char *value) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "CharPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSPc);
    return mrb_obj_value(rdata);
}
static unsigned int drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, unsigned int value) {
    return mrb_fixnum_value(value);
}
static char drb_ffi__ZTSc_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSc_ToRuby(mrb_state *state, char value) {
    return mrb_fixnum_value(value);
}
static mrb_value drb_ffi__ZTSP12ice_cpu_info_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP12ice_cpu_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP12ice_cpu_info));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(ice_cpu_info));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "ICE_CPU_INFO_PTR");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSP12ice_cpu_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP12ice_cpu_info_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS12ice_cpu_info_ToRuby(mrb, *drb_ffi__ZTSP12ice_cpu_info_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP12ice_cpu_info_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP12ice_cpu_info_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP12ice_cpu_info_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS12ice_cpu_info_ToRuby(mrb, drb_ffi__ZTSP12ice_cpu_info_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP12ice_cpu_info_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ice_cpu_info new_value = drb_ffi__ZTS12ice_cpu_info_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP12ice_cpu_info_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPc_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(char));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "CharPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSPc);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPc_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSc_ToRuby(mrb, *drb_ffi__ZTSPc_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPc_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPc_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPc_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSc_ToRuby(mrb, drb_ffi__ZTSPc_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPc_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    char new_value = drb_ffi__ZTSc_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPc_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPc_GetString(mrb_state *state, mrb_value self) {
    return drb_api->mrb_str_new_cstr(state, drb_ffi__ZTSPc_FromRuby(state, self));
}
static mrb_value drb_ffi__ZTS12ice_cpu_info_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS12ice_cpu_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS12ice_cpu_info *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_CPU_INFO");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS12ice_cpu_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS12ice_cpu_info_name_Get(mrb_state *state, mrb_value self) {
    ice_cpu_info record = drb_ffi__ZTS12ice_cpu_info_FromRuby(state, self);
    return drb_ffi__ZTSPc_ToRuby(state, record.name);
}
static mrb_value drb_ffi__ZTS12ice_cpu_info_name_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    char *new_value = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ice_cpu_info *)DATA_PTR(self))->value)->name = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS12ice_cpu_info_cores_Get(mrb_state *state, mrb_value self) {
    ice_cpu_info record = drb_ffi__ZTS12ice_cpu_info_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.cores);
}
static mrb_value drb_ffi__ZTS12ice_cpu_info_cores_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ice_cpu_info *)DATA_PTR(self))->value)->cores = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_cpu_get_info_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_cpu_get_info': wrong number of arguments (%d for 1)", argc);
    ice_cpu_info *cpu_info_0 = drb_ffi__ZTSP12ice_cpu_info_FromRuby(state, args[0]);
    ice_cpu_bool ret_val = ice_cpu_get_info(cpu_info_0);
    return drb_ffi__ZTS12ice_cpu_bool_ToRuby(state, ret_val);
}
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "CExt");
    struct RClass *object_class = state->object_class;
    drb_api->mrb_define_module_function(state, module, "ice_cpu_get_info", drb_ffi_ice_cpu_get_info_Binding, MRB_ARGS_REQ(1));
    struct RClass *ice_cpu_info_ptr_class = drb_api->mrb_define_class_under(state, module, "ICE_CPU_INFO_PTR", object_class);
    drb_api->mrb_define_class_method(state, ice_cpu_info_ptr_class, "new", drb_ffi__ZTSP12ice_cpu_info_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_cpu_info_ptr_class, "value", drb_ffi__ZTSP12ice_cpu_info_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_cpu_info_ptr_class, "[]", drb_ffi__ZTSP12ice_cpu_info_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ice_cpu_info_ptr_class, "[]=", drb_ffi__ZTSP12ice_cpu_info_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, ice_cpu_info_ptr_class, "nil?", drb_ffi__ZTSP12ice_cpu_info_IsNil, MRB_ARGS_REQ(0));
    struct RClass *CharPointerClass = drb_api->mrb_define_class_under(state, module, "CharPointer", object_class);
    drb_api->mrb_define_class_method(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *ice_cpu_info_class = drb_api->mrb_define_class_under(state, module, "ICE_CPU_INFO", object_class);
    drb_api->mrb_define_class_method(state, ice_cpu_info_class, "new", drb_ffi__ZTS12ice_cpu_info_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_cpu_info_class, "name", drb_ffi__ZTS12ice_cpu_info_name_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_cpu_info_class, "name=", drb_ffi__ZTS12ice_cpu_info_name_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ice_cpu_info_class, "cores", drb_ffi__ZTS12ice_cpu_info_cores_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_cpu_info_class, "cores=", drb_ffi__ZTS12ice_cpu_info_cores_Set, MRB_ARGS_REQ(1));
}
