#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>

#define ICE_BATT_IMPL 1
#include "ice_batt.h"

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
struct drb_foreign_object_ZTSPv {
    drb_foreign_object_kind kind;
    void *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPv = {"void*", drb_free_foreign_object_indirect};
static void *drb_ffi__ZTSPv_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "VoidPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSPv);
    return ((struct drb_foreign_object_ZTSPv *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPv_ToRuby(mrb_state *state, void *value) {
    struct drb_foreign_object_ZTSPv *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPv));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "VoidPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSPv);
    return mrb_obj_value(rdata);
}
static ice_batt_error drb_ffi__ZTS14ice_batt_error_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
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
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_BATT_INFO_PTR");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSP13ice_batt_info);
    return ((struct drb_foreign_object_ZTSP13ice_batt_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP13ice_batt_info_ToRuby(mrb_state *state, ice_batt_info *value) {
    struct drb_foreign_object_ZTSP13ice_batt_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP13ice_batt_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_BATT_INFO_PTR");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSP13ice_batt_info);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS13ice_batt_info {
    drb_foreign_object_kind kind;
    ice_batt_info value;
};
static mrb_data_type ForeignObjectType_ZTS13ice_batt_info = {"ice_batt_info", drb_free_foreign_object_indirect};
static ice_batt_info drb_ffi__ZTS13ice_batt_info_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_BATT_INFO");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS13ice_batt_info);
    return ((struct drb_foreign_object_ZTS13ice_batt_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS13ice_batt_info_ToRuby(mrb_state *state, ice_batt_info value) {
    struct drb_foreign_object_ZTS13ice_batt_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS13ice_batt_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_BATT_INFO");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS13ice_batt_info);
    return mrb_obj_value(rdata);
}
static ice_batt_bool drb_ffi__ZTS13ice_batt_bool_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS13ice_batt_bool_ToRuby(mrb_state *state, ice_batt_bool value) {
    return mrb_fixnum_value(value);
}
static unsigned int drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
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
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "ICE_BATT_INFO_PTR");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSP13ice_batt_info);
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
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS13ice_batt_info_ToRuby(mrb, drb_ffi__ZTSP13ice_batt_info_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP13ice_batt_info_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ice_batt_info new_value = drb_ffi__ZTS13ice_batt_info_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP13ice_batt_info_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_batt_info_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS13ice_batt_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS13ice_batt_info *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_BATT_INFO");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS13ice_batt_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS13ice_batt_info_exists_Get(mrb_state *state, mrb_value self) {
    ice_batt_info record = drb_ffi__ZTS13ice_batt_info_FromRuby(state, self);
    return drb_ffi__ZTS13ice_batt_bool_ToRuby(state, record.exists);
}
static mrb_value drb_ffi__ZTS13ice_batt_info_exists_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
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
    drb_api->mrb_get_args(state, "*", &args, &argc);
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
    drb_api->mrb_get_args(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_batt_info *)DATA_PTR(self))->value)->level = new_value;
    return mrb_nil_value();
}
#if defined(ICE_BATT_ANDROID)
static mrb_value drb_ffi_ice_batt_use_native_activity_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_batt_use_native_activity': wrong number of arguments (%d for 1)", argc);
    void *activity_0 = drb_ffi__ZTSPv_FromRuby(state, args[0]);
    ice_batt_use_native_activity(activity_0);
    return mrb_nil_value();
}
#endif
static mrb_value drb_ffi_ice_batt_get_info_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_batt_get_info': wrong number of arguments (%d for 1)", argc);
    ice_batt_info *batt_info_0 = drb_ffi__ZTSP13ice_batt_info_FromRuby(state, args[0]);
    ice_batt_error ret_val = ice_batt_get_info(batt_info_0);
    return drb_ffi__ZTS14ice_batt_error_ToRuby(state, ret_val);
}
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "CExt");
    struct RClass *object_class = state->object_class;
    #if defined(ICE_BATT_ANDROID)
    drb_api->mrb_define_module_function(state, module, "ice_batt_use_native_activity", drb_ffi_ice_batt_use_native_activity_Binding, MRB_ARGS_REQ(1));
    #endif
    drb_api->mrb_define_module_function(state, module, "ice_batt_get_info", drb_ffi_ice_batt_get_info_Binding, MRB_ARGS_REQ(1));
    struct RClass *VoidPointerClass = drb_api->mrb_define_class_under(state, module, "VoidPointer", object_class);
    struct RClass *ice_batt_info_ptr_class = drb_api->mrb_define_class_under(state, module, "ICE_BATT_INFO_PTR", object_class);
    drb_api->mrb_define_class_method(state, ice_batt_info_ptr_class, "new", drb_ffi__ZTSP13ice_batt_info_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_batt_info_ptr_class, "value", drb_ffi__ZTSP13ice_batt_info_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_batt_info_ptr_class, "[]", drb_ffi__ZTSP13ice_batt_info_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ice_batt_info_ptr_class, "[]=", drb_ffi__ZTSP13ice_batt_info_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, ice_batt_info_ptr_class, "nil?", drb_ffi__ZTSP13ice_batt_info_IsNil, MRB_ARGS_REQ(0));
    struct RClass *ice_batt_info_class = drb_api->mrb_define_class_under(state, module, "ICE_BATT_INFO", object_class);
    drb_api->mrb_define_class_method(state, ice_batt_info_class, "new", drb_ffi__ZTS13ice_batt_info_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_batt_info_class, "exists", drb_ffi__ZTS13ice_batt_info_exists_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_batt_info_class, "exists=", drb_ffi__ZTS13ice_batt_info_exists_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ice_batt_info_class, "charging", drb_ffi__ZTS13ice_batt_info_charging_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_batt_info_class, "charging=", drb_ffi__ZTS13ice_batt_info_charging_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ice_batt_info_class, "level", drb_ffi__ZTS13ice_batt_info_level_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_batt_info_class, "level=", drb_ffi__ZTS13ice_batt_info_level_Set, MRB_ARGS_REQ(1));
}
