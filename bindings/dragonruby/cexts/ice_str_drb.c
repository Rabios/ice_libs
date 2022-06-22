#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>

#define ICE_STR_IMPL 1
#include "ice_str.h"

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
static unsigned long drb_ffi__ZTSm_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSm_ToRuby(mrb_state *state, unsigned long value) {
    return mrb_fixnum_value(value);
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
struct drb_foreign_object_ZTSPPm {
    drb_foreign_object_kind kind;
    unsigned long **value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPPm = {"unsigned long**", drb_free_foreign_object_indirect};
static unsigned long **drb_ffi__ZTSPPm_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Unsigned_longPointerPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSPPm);
    return ((struct drb_foreign_object_ZTSPPm *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPPm_ToRuby(mrb_state *state, unsigned long **value) {
    struct drb_foreign_object_ZTSPPm *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPPm));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Unsigned_longPointerPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSPPm);
    return mrb_obj_value(rdata);
}
static char drb_ffi__ZTSc_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSc_ToRuby(mrb_state *state, char value) {
    return mrb_fixnum_value(value);
}
static ice_str_bool drb_ffi__ZTS12ice_str_bool_FromRuby(mrb_state *state, mrb_value self) {
    drb_api->drb_typecheck_int(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS12ice_str_bool_ToRuby(mrb_state *state, ice_str_bool value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSPPc {
    drb_foreign_object_kind kind;
    char **value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPPc = {"char**", drb_free_foreign_object_indirect};
static char **drb_ffi__ZTSPPc_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "CharPointerPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSPPc);
    return ((struct drb_foreign_object_ZTSPPc *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPPc_ToRuby(mrb_state *state, char **value) {
    struct drb_foreign_object_ZTSPPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPPc));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "CharPointerPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSPPc);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSPm {
    drb_foreign_object_kind kind;
    unsigned long *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPm = {"unsigned long*", drb_free_foreign_object_indirect};
static unsigned long *drb_ffi__ZTSPm_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Unsigned_longPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSPm);
    return ((struct drb_foreign_object_ZTSPm *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPm_ToRuby(mrb_state *state, unsigned long *value) {
    struct drb_foreign_object_ZTSPm *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPm));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "Unsigned_longPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSPm);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSPi {
    drb_foreign_object_kind kind;
    int *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPi = {"int*", drb_free_foreign_object_indirect};
static int *drb_ffi__ZTSPi_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "IntPointer");
    drb_api->drb_typecheck_aggregate(state, self, klass, &ForeignObjectType_ZTSPi);
    return ((struct drb_foreign_object_ZTSPi *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPi_ToRuby(mrb_state *state, int *value) {
    struct drb_foreign_object_ZTSPi *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPi));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(state, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(state, module, "IntPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(state, klass, ptr, &ForeignObjectType_ZTSPi);
    return mrb_obj_value(rdata);
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
static mrb_value drb_ffi__ZTSPPm_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPPm *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPPm));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(unsigned long *));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "Unsigned_longPointerPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSPPm);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPPm_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSPm_ToRuby(mrb, *drb_ffi__ZTSPPm_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPPm_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPPm_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPPm_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSPm_ToRuby(mrb, drb_ffi__ZTSPPm_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPPm_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    unsigned long *new_value = drb_ffi__ZTSPm_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPPm_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPPc_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPPc));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(char *));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "CharPointerPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSPPc);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPPc_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSPc_ToRuby(mrb, *drb_ffi__ZTSPPc_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPPc_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPPc_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPPc_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSPc_ToRuby(mrb, drb_ffi__ZTSPPc_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPPc_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    char *new_value = drb_ffi__ZTSPc_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPPc_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPm_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPm *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPm));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(unsigned long));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "Unsigned_longPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSPm);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPm_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSm_ToRuby(mrb, *drb_ffi__ZTSPm_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPm_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPm_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPm_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSm_ToRuby(mrb, drb_ffi__ZTSPm_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPm_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    unsigned long new_value = drb_ffi__ZTSm_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPm_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPi_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPi *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPi));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(int));
    ptr->should_free = 1;
    struct RClass *FFI = drb_api->mrb_module_get(mrb, "FFI");
    struct RClass *module = drb_api->mrb_module_get_under(mrb, FFI, "CExt");
    struct RClass *klass = drb_api->mrb_class_get_under(mrb, module, "IntPointer");
    struct RData *rdata = drb_api->mrb_data_object_alloc(mrb, klass, ptr, &ForeignObjectType_ZTSPi);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPi_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSi_ToRuby(mrb, *drb_ffi__ZTSPi_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPi_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPi_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPi_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSi_ToRuby(mrb, drb_ffi__ZTSPi_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPi_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    int new_value = drb_ffi__ZTSi_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPi_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_str_len_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_len': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long ret_val = ice_str_len(str_0);
    return drb_ffi__ZTSm_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_sub_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_sub': wrong number of arguments (%d for 3)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long from_idx_1 = drb_ffi__ZTSm_FromRuby(state, args[1]);
    unsigned long to_idx_2 = drb_ffi__ZTSm_FromRuby(state, args[2]);
    char *ret_val = ice_str_sub(str_0, from_idx_1, to_idx_2);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_concat_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_concat': wrong number of arguments (%d for 2)", argc);
    char *str1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    char *ret_val = ice_str_concat(str1_0, str2_1);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_insert_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_insert': wrong number of arguments (%d for 3)", argc);
    char *str1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    unsigned long idx_2 = drb_ffi__ZTSm_FromRuby(state, args[2]);
    char *ret_val = ice_str_insert(str1_0, str2_1, idx_2);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_matches_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_matches': wrong number of arguments (%d for 3)", argc);
    char *str1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    unsigned long **idxs_2 = drb_ffi__ZTSPPm_FromRuby(state, args[2]);
    unsigned long ret_val = ice_str_matches(str1_0, str2_1, idxs_2);
    return drb_ffi__ZTSm_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_rep_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_rep': wrong number of arguments (%d for 3)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str1_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    char *str2_2 = drb_ffi__ZTSPc_FromRuby(state, args[2]);
    char *ret_val = ice_str_rep(str_0, str1_1, str2_2);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_dup_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_dup': wrong number of arguments (%d for 2)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long times_1 = drb_ffi__ZTSm_FromRuby(state, args[1]);
    char *ret_val = ice_str_dup(str_0, times_1);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_copy_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_copy': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_str_copy(str_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_rev_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_rev': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_str_rev(str_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_char_to_str_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_char_to_str': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    char *ret_val = ice_str_char_to_str(ch_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_same_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_same': wrong number of arguments (%d for 2)", argc);
    char *str1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_str_bool ret_val = ice_str_same(str1_0, str2_1);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_upper_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_upper': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_str_upper(str_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_lower_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_lower': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_str_lower(str_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_cap_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_cap': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_str_cap(str_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_split_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_split': wrong number of arguments (%d for 3)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char delim_1 = drb_ffi__ZTSc_FromRuby(state, args[1]);
    unsigned long *arrlen_2 = drb_ffi__ZTSPm_FromRuby(state, args[2]);
    char **ret_val = ice_str_split(str_0, delim_1, arrlen_2);
    return drb_ffi__ZTSPPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_splitlines_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_splitlines': wrong number of arguments (%d for 2)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long *arrlen_1 = drb_ffi__ZTSPm_FromRuby(state, args[1]);
    char **ret_val = ice_str_splitlines(str_0, arrlen_1);
    return drb_ffi__ZTSPPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_join_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 3)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_join': wrong number of arguments (%d for 3)", argc);
    char **strs_0 = drb_ffi__ZTSPPc_FromRuby(state, args[0]);
    unsigned long arrlen_1 = drb_ffi__ZTSm_FromRuby(state, args[1]);
    char delim_2 = drb_ffi__ZTSc_FromRuby(state, args[2]);
    char *ret_val = ice_str_join(strs_0, arrlen_1, delim_2);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_begins_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_begins': wrong number of arguments (%d for 2)", argc);
    char *str1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_str_bool ret_val = ice_str_begins(str1_0, str2_1);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_ends_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_ends': wrong number of arguments (%d for 2)", argc);
    char *str1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_str_bool ret_val = ice_str_ends(str1_0, str2_1);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_last_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_last_char': wrong number of arguments (%d for 2)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char ch_1 = drb_ffi__ZTSc_FromRuby(state, args[1]);
    ice_str_bool ret_val = ice_str_last_char(str_0, ch_1);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_to_bytes_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_to_bytes': wrong number of arguments (%d for 2)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long *arrlen_1 = drb_ffi__ZTSPm_FromRuby(state, args[1]);
    int *ret_val = ice_str_to_bytes(str_0, arrlen_1);
    return drb_ffi__ZTSPi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_from_bytes_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_from_bytes': wrong number of arguments (%d for 2)", argc);
    int *chars_0 = drb_ffi__ZTSPi_FromRuby(state, args[0]);
    unsigned long arrlen_1 = drb_ffi__ZTSm_FromRuby(state, args[1]);
    char *ret_val = ice_str_from_bytes(chars_0, arrlen_1);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_contains_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_contains_char': wrong number of arguments (%d for 2)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char ch_1 = drb_ffi__ZTSc_FromRuby(state, args[1]);
    ice_str_bool ret_val = ice_str_contains_char(str_0, ch_1);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_cmp_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_cmp': wrong number of arguments (%d for 2)", argc);
    char *str1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    int ret_val = ice_str_cmp(str1_0, str2_1);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_char_to_digit_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_char_to_digit': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    int ret_val = ice_str_char_to_digit(ch_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_alnum_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_alnum_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_alnum_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_alpha_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_alpha_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_alpha_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_lower_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_lower_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_lower_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_upper_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_upper_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_upper_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_digit_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_digit_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_digit_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_xdigit_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_xdigit_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_xdigit_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_cntrl_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_cntrl_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_cntrl_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_graph_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_graph_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_graph_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_space_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_space_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_space_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_blank_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_blank_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_blank_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_print_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_print_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_print_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_is_punct_char_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_is_punct_char': wrong number of arguments (%d for 1)", argc);
    char ch_0 = drb_ffi__ZTSc_FromRuby(state, args[0]);
    ice_str_bool ret_val = ice_str_is_punct_char(ch_0);
    return drb_ffi__ZTS12ice_str_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_str_free_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_free': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_str_free(str_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_str_free_bytes_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 1)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_free_bytes': wrong number of arguments (%d for 1)", argc);
    int *bytes_0 = drb_ffi__ZTSPi_FromRuby(state, args[0]);
    ice_str_free_bytes(bytes_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_str_free_arr_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    drb_api->mrb_get_args(state, "*", &args, &argc);
    if (argc != 2)
        drb_api->mrb_raisef(state, drb_api->drb_getargument_error(state), "'ice_str_free_arr': wrong number of arguments (%d for 2)", argc);
    char **arr_0 = drb_ffi__ZTSPPc_FromRuby(state, args[0]);
    unsigned long arrlen_1 = drb_ffi__ZTSm_FromRuby(state, args[1]);
    ice_str_free_arr(arr_0, arrlen_1);
    return mrb_nil_value();
}
DRB_FFI_EXPORT
void drb_register_c_extensions_with_api(mrb_state *state, struct drb_api_t *api) {
    drb_api = api;
    struct RClass *FFI = drb_api->mrb_module_get(state, "FFI");
    struct RClass *module = drb_api->mrb_define_module_under(state, FFI, "CExt");
    struct RClass *object_class = state->object_class;
    drb_api->mrb_define_module_function(state, module, "ice_str_len", drb_ffi_ice_str_len_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_sub", drb_ffi_ice_str_sub_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "ice_str_concat", drb_ffi_ice_str_concat_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_insert", drb_ffi_ice_str_insert_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "ice_str_matches", drb_ffi_ice_str_matches_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "ice_str_rep", drb_ffi_ice_str_rep_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "ice_str_dup", drb_ffi_ice_str_dup_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_copy", drb_ffi_ice_str_copy_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_rev", drb_ffi_ice_str_rev_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_char_to_str", drb_ffi_ice_str_char_to_str_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_same", drb_ffi_ice_str_same_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_upper", drb_ffi_ice_str_upper_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_lower", drb_ffi_ice_str_lower_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_cap", drb_ffi_ice_str_cap_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_split", drb_ffi_ice_str_split_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "ice_str_splitlines", drb_ffi_ice_str_splitlines_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_join", drb_ffi_ice_str_join_Binding, MRB_ARGS_REQ(3));
    drb_api->mrb_define_module_function(state, module, "ice_str_begins", drb_ffi_ice_str_begins_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_ends", drb_ffi_ice_str_ends_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_last_char", drb_ffi_ice_str_last_char_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_to_bytes", drb_ffi_ice_str_to_bytes_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_from_bytes", drb_ffi_ice_str_from_bytes_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_contains_char", drb_ffi_ice_str_contains_char_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_cmp", drb_ffi_ice_str_cmp_Binding, MRB_ARGS_REQ(2));
    drb_api->mrb_define_module_function(state, module, "ice_str_char_to_digit", drb_ffi_ice_str_char_to_digit_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_alnum_char", drb_ffi_ice_str_is_alnum_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_alpha_char", drb_ffi_ice_str_is_alpha_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_lower_char", drb_ffi_ice_str_is_lower_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_upper_char", drb_ffi_ice_str_is_upper_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_digit_char", drb_ffi_ice_str_is_digit_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_xdigit_char", drb_ffi_ice_str_is_xdigit_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_cntrl_char", drb_ffi_ice_str_is_cntrl_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_graph_char", drb_ffi_ice_str_is_graph_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_space_char", drb_ffi_ice_str_is_space_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_blank_char", drb_ffi_ice_str_is_blank_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_print_char", drb_ffi_ice_str_is_print_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_is_punct_char", drb_ffi_ice_str_is_punct_char_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_free", drb_ffi_ice_str_free_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_free_bytes", drb_ffi_ice_str_free_bytes_Binding, MRB_ARGS_REQ(1));
    drb_api->mrb_define_module_function(state, module, "ice_str_free_arr", drb_ffi_ice_str_free_arr_Binding, MRB_ARGS_REQ(2));
    struct RClass *CharPointerClass = drb_api->mrb_define_class_under(state, module, "CharPointer", object_class);
    drb_api->mrb_define_class_method(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *Unsigned_longPointerPointerClass = drb_api->mrb_define_class_under(state, module, "Unsigned_longPointerPointer", object_class);
    drb_api->mrb_define_class_method(state, Unsigned_longPointerPointerClass, "new", drb_ffi__ZTSPPm_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, Unsigned_longPointerPointerClass, "value", drb_ffi__ZTSPPm_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, Unsigned_longPointerPointerClass, "[]", drb_ffi__ZTSPPm_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, Unsigned_longPointerPointerClass, "[]=", drb_ffi__ZTSPPm_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, Unsigned_longPointerPointerClass, "nil?", drb_ffi__ZTSPPm_IsNil, MRB_ARGS_REQ(0));
    struct RClass *CharPointerPointerClass = drb_api->mrb_define_class_under(state, module, "CharPointerPointer", object_class);
    drb_api->mrb_define_class_method(state, CharPointerPointerClass, "new", drb_ffi__ZTSPPc_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerPointerClass, "value", drb_ffi__ZTSPPc_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, CharPointerPointerClass, "[]", drb_ffi__ZTSPPc_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, CharPointerPointerClass, "[]=", drb_ffi__ZTSPPc_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, CharPointerPointerClass, "nil?", drb_ffi__ZTSPPc_IsNil, MRB_ARGS_REQ(0));
    struct RClass *Unsigned_longPointerClass = drb_api->mrb_define_class_under(state, module, "Unsigned_longPointer", object_class);
    drb_api->mrb_define_class_method(state, Unsigned_longPointerClass, "new", drb_ffi__ZTSPm_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, Unsigned_longPointerClass, "value", drb_ffi__ZTSPm_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, Unsigned_longPointerClass, "[]", drb_ffi__ZTSPm_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, Unsigned_longPointerClass, "[]=", drb_ffi__ZTSPm_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, Unsigned_longPointerClass, "nil?", drb_ffi__ZTSPm_IsNil, MRB_ARGS_REQ(0));
    struct RClass *IntPointerClass = drb_api->mrb_define_class_under(state, module, "IntPointer", object_class);
    drb_api->mrb_define_class_method(state, IntPointerClass, "new", drb_ffi__ZTSPi_New, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, IntPointerClass, "value", drb_ffi__ZTSPi_GetValue, MRB_ARGS_REQ(0));
    drb_api->mrb_define_method(state, IntPointerClass, "[]", drb_ffi__ZTSPi_GetAt, MRB_ARGS_REQ(1));
    drb_api->mrb_define_method(state, IntPointerClass, "[]=", drb_ffi__ZTSPi_SetAt, MRB_ARGS_REQ(2));
    drb_api->mrb_define_method(state, IntPointerClass, "nil?", drb_ffi__ZTSPi_IsNil, MRB_ARGS_REQ(0));
}
