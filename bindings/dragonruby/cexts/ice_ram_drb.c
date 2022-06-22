#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>

#define ICE_RAM_IMPL 1
#include "ice_ram.h"

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
static ice_ram_bool drb_ffi__ZTS12ice_ram_bool_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
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
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_RAM_INFO_PTR");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSP12ice_ram_info);
    return ((struct drb_foreign_object_ZTSP12ice_ram_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP12ice_ram_info_ToRuby(mrb_state *state, ice_ram_info *value) {
    struct drb_foreign_object_ZTSP12ice_ram_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP12ice_ram_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_RAM_INFO_PTR");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSP12ice_ram_info);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS12ice_ram_info {
    drb_foreign_object_kind kind;
    ice_ram_info value;
};
static mrb_data_type ForeignObjectType_ZTS12ice_ram_info = {"ice_ram_info", drb_free_foreign_object_indirect};
static ice_ram_info drb_ffi__ZTS12ice_ram_info_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_RAM_INFO");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTS12ice_ram_info);
    return ((struct drb_foreign_object_ZTS12ice_ram_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS12ice_ram_info_ToRuby(mrb_state *state, ice_ram_info value) {
    struct drb_foreign_object_ZTS12ice_ram_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS12ice_ram_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_RAM_INFO");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS12ice_ram_info);
    return mrb_obj_value(rdata);
}
static ice_ram_bytes drb_ffi__ZTSy_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
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
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "ICE_RAM_INFO_PTR");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSP12ice_ram_info);
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
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS12ice_ram_info_ToRuby(mrb, drb_ffi__ZTSP12ice_ram_info_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP12ice_ram_info_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ice_ram_info new_value = drb_ffi__ZTS12ice_ram_info_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP12ice_ram_info_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS12ice_ram_info_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS12ice_ram_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS12ice_ram_info *));
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "ICE_RAM_INFO");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTS12ice_ram_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS12ice_ram_info_free_Get(mrb_state *state, mrb_value self) {
    ice_ram_info record = drb_ffi__ZTS12ice_ram_info_FromRuby(state, self);
    return drb_ffi__ZTSy_ToRuby(state, record.free);
}
static mrb_value drb_ffi__ZTS12ice_ram_info_free_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
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
    drb_api->mrb_get_args(state, "*", &args, &argc);
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
    drb_api->mrb_get_args(state, "*", &args, &argc);
    ice_ram_bytes new_value = drb_ffi__ZTSy_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ice_ram_info *)DATA_PTR(self))->value)->total = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_ram_get_info_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_ram_get_info': wrong number of arguments (%d for 1)", argc);
    ice_ram_info *ram_info_0 = drb_ffi__ZTSP12ice_ram_info_FromRuby(state, args[0]);
    ice_ram_bool ret_val = ice_ram_get_info(ram_info_0);
    return drb_ffi__ZTS12ice_ram_bool_ToRuby(state, ret_val);
}
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "CExt");
    struct RClass *object_class = state->object_class;
    drb_api->mrb_define_module_function(state, module, "ice_ram_get_info", drb_ffi_ice_ram_get_info_Binding, MRB_ARGS_REQ(1));
    struct RClass *ice_ram_info_ptr_class = drb_api->mrb_define_class_under(state, module, "ICE_RAM_INFO_PTR", object_class);
    drb_api->mrb_define_class_method(state, ice_ram_info_ptr_class, "new", drb_ffi__ZTSP12ice_ram_info_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_ram_info_ptr_class, "value", drb_ffi__ZTSP12ice_ram_info_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_ram_info_ptr_class, "[]", drb_ffi__ZTSP12ice_ram_info_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ice_ram_info_ptr_class, "[]=", drb_ffi__ZTSP12ice_ram_info_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, ice_ram_info_ptr_class, "nil?", drb_ffi__ZTSP12ice_ram_info_IsNil, MRB_ARGS_REQ(0));
    struct RClass *ice_ram_info_class = drb_api->mrb_define_class_under(state, module, "ICE_RAM_INFO", object_class);
    drb_api->mrb_define_class_method(state, ice_ram_info_class, "new", drb_ffi__ZTS12ice_ram_info_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_ram_info_class, "free", drb_ffi__ZTS12ice_ram_info_free_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_ram_info_class, "free=", drb_ffi__ZTS12ice_ram_info_free_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ice_ram_info_class, "used", drb_ffi__ZTS12ice_ram_info_used_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_ram_info_class, "used=", drb_ffi__ZTS12ice_ram_info_used_Set, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, ice_ram_info_class, "total", drb_ffi__ZTS12ice_ram_info_total_Get, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, ice_ram_info_class, "total=", drb_ffi__ZTS12ice_ram_info_total_Set, MRB_ARGS_REQ(1));
}
