#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>

#define ICE_FS_IMPL 1
#include "ice_fs.h"

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
static unsigned long drb_ffi__ZTSm_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
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
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "CharPointer");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSPc);
    return ((struct drb_foreign_object_ZTSPc *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPc_ToRuby(mrb_state *state, char *value) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "CharPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPc);
    return mrb_obj_value(rdata);
}
static ice_fs_bool drb_ffi__ZTS11ice_fs_bool_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS11ice_fs_bool_ToRuby(mrb_state *state, ice_fs_bool value) {
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
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "CharPointerPointer");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSPPc);
    return ((struct drb_foreign_object_ZTSPPc *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPPc_ToRuby(mrb_state *state, char **value) {
    struct drb_foreign_object_ZTSPPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPPc));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "CharPointerPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPPc);
    return mrb_obj_value(rdata);
}
static char drb_ffi__ZTSc_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSc_ToRuby(mrb_state *state, char value) {
    return mrb_fixnum_value(value);
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
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Unsigned_longPointer");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSPm);
    return ((struct drb_foreign_object_ZTSPm *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPm_ToRuby(mrb_state *state, unsigned long *value) {
    struct drb_foreign_object_ZTSPm *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPm));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Unsigned_longPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPm);
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
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Unsigned_longPointerPointer");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSPPm);
    return ((struct drb_foreign_object_ZTSPPm *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPPm_ToRuby(mrb_state *state, unsigned long **value) {
    struct drb_foreign_object_ZTSPPm *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPPm));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Unsigned_longPointerPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPPm);
    return mrb_obj_value(rdata);
}
static ice_fs_object_type drb_ffi__ZTS18ice_fs_object_type_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS18ice_fs_object_type_ToRuby(mrb_state *state, ice_fs_object_type value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTS10ice_fs_dir {
    drb_foreign_object_kind kind;
    ice_fs_dir value;
};
static mrb_data_type ForeignObjectType_ZTS10ice_fs_dir = {"ice_fs_dir", drb_free_foreign_object_indirect};
static ice_fs_dir drb_ffi__ZTS10ice_fs_dir_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DIR");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTS10ice_fs_dir);
    return ((struct drb_foreign_object_ZTS10ice_fs_dir *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS10ice_fs_dir_ToRuby(mrb_state *state, ice_fs_dir value) {
    struct drb_foreign_object_ZTS10ice_fs_dir *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS10ice_fs_dir));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DIR");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS10ice_fs_dir);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSP10ice_fs_dir {
    drb_foreign_object_kind kind;
    ice_fs_dir *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP10ice_fs_dir = {"ice_fs_dir*", drb_free_foreign_object_indirect};
static ice_fs_dir *drb_ffi__ZTSP10ice_fs_dir_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DIR_PTR");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSP10ice_fs_dir);
    return ((struct drb_foreign_object_ZTSP10ice_fs_dir *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP10ice_fs_dir_ToRuby(mrb_state *state, ice_fs_dir *value) {
    struct drb_foreign_object_ZTSP10ice_fs_dir *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP10ice_fs_dir));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DIR_PTR");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP10ice_fs_dir);
    return mrb_obj_value(rdata);
}
static ice_fs_date_type drb_ffi__ZTS16ice_fs_date_type_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS16ice_fs_date_type_ToRuby(mrb_state *state, ice_fs_date_type value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSP11ice_fs_date {
    drb_foreign_object_kind kind;
    ice_fs_date *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP11ice_fs_date = {"ice_fs_date*", drb_free_foreign_object_indirect};
static ice_fs_date *drb_ffi__ZTSP11ice_fs_date_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DATE_PTR");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSP11ice_fs_date);
    return ((struct drb_foreign_object_ZTSP11ice_fs_date *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP11ice_fs_date_ToRuby(mrb_state *state, ice_fs_date *value) {
    struct drb_foreign_object_ZTSP11ice_fs_date *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP11ice_fs_date));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DATE_PTR");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP11ice_fs_date);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSP13ice_fs_object {
    drb_foreign_object_kind kind;
    ice_fs_object *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP13ice_fs_object = {"ice_fs_object*", drb_free_foreign_object_indirect};
static ice_fs_object *drb_ffi__ZTSP13ice_fs_object_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_OBJECT_PTR");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSP13ice_fs_object);
    return ((struct drb_foreign_object_ZTSP13ice_fs_object *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP13ice_fs_object_ToRuby(mrb_state *state, ice_fs_object *value) {
    struct drb_foreign_object_ZTSP13ice_fs_object *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP13ice_fs_object));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_OBJECT_PTR");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP13ice_fs_object);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS11ice_fs_date {
    drb_foreign_object_kind kind;
    ice_fs_date value;
};
static mrb_data_type ForeignObjectType_ZTS11ice_fs_date = {"ice_fs_date", drb_free_foreign_object_indirect};
static ice_fs_date drb_ffi__ZTS11ice_fs_date_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DATE");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTS11ice_fs_date);
    return ((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS11ice_fs_date_ToRuby(mrb_state *state, ice_fs_date value) {
    struct drb_foreign_object_ZTS11ice_fs_date *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS11ice_fs_date));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DATE");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS11ice_fs_date);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS13ice_fs_object {
    drb_foreign_object_kind kind;
    ice_fs_object value;
};
static mrb_data_type ForeignObjectType_ZTS13ice_fs_object = {"ice_fs_object", drb_free_foreign_object_indirect};
static ice_fs_object drb_ffi__ZTS13ice_fs_object_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_OBJECT");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTS13ice_fs_object);
    return ((struct drb_foreign_object_ZTS13ice_fs_object *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS13ice_fs_object_ToRuby(mrb_state *state, ice_fs_object value) {
    struct drb_foreign_object_ZTS13ice_fs_object *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS13ice_fs_object));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_OBJECT");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS13ice_fs_object);
    return mrb_obj_value(rdata);
}
static unsigned int drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, unsigned int value) {
    return mrb_fixnum_value(value);
}
static ice_fs_date_day drb_ffi__ZTS15ice_fs_date_day_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS15ice_fs_date_day_ToRuby(mrb_state *state, ice_fs_date_day value) {
    return mrb_fixnum_value(value);
}
static ice_fs_date_month drb_ffi__ZTS17ice_fs_date_month_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS17ice_fs_date_month_ToRuby(mrb_state *state, ice_fs_date_month value) {
    return mrb_fixnum_value(value);
}
static ice_fs_date_season drb_ffi__ZTS18ice_fs_date_season_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS18ice_fs_date_season_ToRuby(mrb_state *state, ice_fs_date_season value) {
    return mrb_fixnum_value(value);
}
static mrb_value drb_ffi__ZTSPc_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(char));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "CharPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPc);
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
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSc_ToRuby(mrb, drb_ffi__ZTSPc_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPc_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    char new_value = drb_ffi__ZTSc_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPc_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPc_GetString(mrb_state *state, mrb_value self) {
    return mrb_str_new_cstr_f(state, drb_ffi__ZTSPc_FromRuby(state, self));
}
static mrb_value drb_ffi__ZTSPPc_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPPc));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(char *));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "CharPointerPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPPc);
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
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSPc_ToRuby(mrb, drb_ffi__ZTSPPc_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPPc_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
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
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "Unsigned_longPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPm);
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
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSm_ToRuby(mrb, drb_ffi__ZTSPm_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPm_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    unsigned long new_value = drb_ffi__ZTSm_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPm_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPPm_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPPm *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPPm));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(unsigned long *));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "Unsigned_longPointerPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPPm);
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
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSPm_ToRuby(mrb, drb_ffi__ZTSPPm_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPPm_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    unsigned long *new_value = drb_ffi__ZTSPm_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPPm_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSP10ice_fs_dir_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP10ice_fs_dir *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP10ice_fs_dir));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(ice_fs_dir));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "ICE_FS_DIR_PTR");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP10ice_fs_dir);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP10ice_fs_dir_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS10ice_fs_dir_ToRuby(mrb, *drb_ffi__ZTSP10ice_fs_dir_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP10ice_fs_dir_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP10ice_fs_dir_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP10ice_fs_dir_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS10ice_fs_dir_ToRuby(mrb, drb_ffi__ZTSP10ice_fs_dir_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP10ice_fs_dir_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ice_fs_dir new_value = drb_ffi__ZTS10ice_fs_dir_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP10ice_fs_dir_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSP11ice_fs_date_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP11ice_fs_date *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP11ice_fs_date));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(ice_fs_date));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "ICE_FS_DATE_PTR");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP11ice_fs_date);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP11ice_fs_date_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS11ice_fs_date_ToRuby(mrb, *drb_ffi__ZTSP11ice_fs_date_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP11ice_fs_date_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP11ice_fs_date_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP11ice_fs_date_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS11ice_fs_date_ToRuby(mrb, drb_ffi__ZTSP11ice_fs_date_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP11ice_fs_date_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ice_fs_date new_value = drb_ffi__ZTS11ice_fs_date_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP11ice_fs_date_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSP13ice_fs_object_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP13ice_fs_object *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP13ice_fs_object));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(ice_fs_object));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "ICE_FS_OBJECT_PTR");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP13ice_fs_object);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP13ice_fs_object_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS13ice_fs_object_ToRuby(mrb, *drb_ffi__ZTSP13ice_fs_object_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP13ice_fs_object_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP13ice_fs_object_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP13ice_fs_object_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS13ice_fs_object_ToRuby(mrb, drb_ffi__ZTSP13ice_fs_object_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP13ice_fs_object_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ice_fs_object new_value = drb_ffi__ZTS13ice_fs_object_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP13ice_fs_object_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS10ice_fs_dir_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS10ice_fs_dir *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS10ice_fs_dir *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DIR");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS10ice_fs_dir);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS10ice_fs_dir_items_Get(mrb_state *state, mrb_value self) {
    ice_fs_dir record = drb_ffi__ZTS10ice_fs_dir_FromRuby(state, self);
    return drb_ffi__ZTSP13ice_fs_object_ToRuby(state, record.items);
}
static mrb_value drb_ffi__ZTS10ice_fs_dir_items_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_fs_object *new_value = drb_ffi__ZTSP13ice_fs_object_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS10ice_fs_dir *)DATA_PTR(self))->value)->items = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS10ice_fs_dir_items_count_Get(mrb_state *state, mrb_value self) {
    ice_fs_dir record = drb_ffi__ZTS10ice_fs_dir_FromRuby(state, self);
    return drb_ffi__ZTSm_ToRuby(state, record.items_count);
}
static mrb_value drb_ffi__ZTS10ice_fs_dir_items_count_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned long new_value = drb_ffi__ZTSm_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS10ice_fs_dir *)DATA_PTR(self))->value)->items_count = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS11ice_fs_date *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS11ice_fs_date *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_DATE");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS11ice_fs_date);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_str_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTSPc_ToRuby(state, record.str);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_str_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    char *new_value = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->str = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_epoch_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTSm_ToRuby(state, record.epoch);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_epoch_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned long new_value = drb_ffi__ZTSm_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->epoch = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_seconds_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.seconds);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_seconds_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->seconds = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_minutes_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.minutes);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_minutes_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->minutes = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_hour_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.hour);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_hour_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->hour = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_week_day_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTS15ice_fs_date_day_ToRuby(state, record.week_day);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_week_day_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_fs_date_day new_value = drb_ffi__ZTS15ice_fs_date_day_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->week_day = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_month_day_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.month_day);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_month_day_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->month_day = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_year_day_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.year_day);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_year_day_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->year_day = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_month_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTS17ice_fs_date_month_ToRuby(state, record.month);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_month_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_fs_date_month new_value = drb_ffi__ZTS17ice_fs_date_month_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->month = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_season_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTS18ice_fs_date_season_ToRuby(state, record.season);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_season_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_fs_date_season new_value = drb_ffi__ZTS18ice_fs_date_season_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->season = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS11ice_fs_date_year_Get(mrb_state *state, mrb_value self) {
    ice_fs_date record = drb_ffi__ZTS11ice_fs_date_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.year);
}
static mrb_value drb_ffi__ZTS11ice_fs_date_year_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS11ice_fs_date *)DATA_PTR(self))->value)->year = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_fs_object_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS13ice_fs_object *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS13ice_fs_object *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ICE_FS_OBJECT");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS13ice_fs_object);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS13ice_fs_object_name_Get(mrb_state *state, mrb_value self) {
    ice_fs_object record = drb_ffi__ZTS13ice_fs_object_FromRuby(state, self);
    return drb_ffi__ZTSPc_ToRuby(state, record.name);
}
static mrb_value drb_ffi__ZTS13ice_fs_object_name_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    char *new_value = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_fs_object *)DATA_PTR(self))->value)->name = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_fs_object_type_Get(mrb_state *state, mrb_value self) {
    ice_fs_object record = drb_ffi__ZTS13ice_fs_object_FromRuby(state, self);
    return drb_ffi__ZTS18ice_fs_object_type_ToRuby(state, record.type);
}
static mrb_value drb_ffi__ZTS13ice_fs_object_type_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_fs_object_type new_value = drb_ffi__ZTS18ice_fs_object_type_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_fs_object *)DATA_PTR(self))->value)->type = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_fs_str_len_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_len': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long ret_val = ice_fs_str_len(str_0);
    return drb_ffi__ZTSm_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_starts_with_slash_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_starts_with_slash': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_bool ret_val = ice_fs_str_starts_with_slash(str_0);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_ends_with_slash_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_ends_with_slash': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_bool ret_val = ice_fs_str_ends_with_slash(str_0);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_slashes_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_slashes': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long ret_val = ice_fs_str_slashes(str_0);
    return drb_ffi__ZTSm_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_dots_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_dots': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long ret_val = ice_fs_str_dots(str_0);
    return drb_ffi__ZTSm_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_same_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_same': wrong number of arguments (%d for 2)", argc);
    char *str1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_fs_bool ret_val = ice_fs_str_same(str1_0, str2_1);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_sub_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 3)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_sub': wrong number of arguments (%d for 3)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long from_idx_1 = drb_ffi__ZTSm_FromRuby(state, args[1]);
    unsigned long to_idx_2 = drb_ffi__ZTSm_FromRuby(state, args[2]);
    char *ret_val = ice_fs_str_sub(str_0, from_idx_1, to_idx_2);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_copy_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_copy': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_fs_str_copy(str_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_split_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 3)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_split': wrong number of arguments (%d for 3)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char delim_1 = drb_ffi__ZTSc_FromRuby(state, args[1]);
    unsigned long *arrlen_2 = drb_ffi__ZTSPm_FromRuby(state, args[2]);
    char **ret_val = ice_fs_str_split(str_0, delim_1, arrlen_2);
    return drb_ffi__ZTSPPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_splitlines_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_splitlines': wrong number of arguments (%d for 2)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long *arrlen_1 = drb_ffi__ZTSPm_FromRuby(state, args[1]);
    char **ret_val = ice_fs_str_splitlines(str_0, arrlen_1);
    return drb_ffi__ZTSPPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_str_matches_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 3)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_str_matches': wrong number of arguments (%d for 3)", argc);
    char *str1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    unsigned long **idxs_2 = drb_ffi__ZTSPPm_FromRuby(state, args[2]);
    unsigned long ret_val = ice_fs_str_matches(str1_0, str2_1, idxs_2);
    return drb_ffi__ZTSm_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_free_str_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_free_str': wrong number of arguments (%d for 1)", argc);
    char *str_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_free_str(str_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_fs_free_strarr_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_free_strarr': wrong number of arguments (%d for 2)", argc);
    char **strs_0 = drb_ffi__ZTSPPc_FromRuby(state, args[0]);
    unsigned long arrlen_1 = drb_ffi__ZTSm_FromRuby(state, args[1]);
    ice_fs_free_strarr(strs_0, arrlen_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_fs_root_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_root': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_fs_root(path_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_is_root_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_is_root': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_bool ret_val = ice_fs_is_root(path_0);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_concat_path_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_concat_path': wrong number of arguments (%d for 2)", argc);
    char *path1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *path2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    char *ret_val = ice_fs_concat_path(path1_0, path2_1);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_filename_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_filename': wrong number of arguments (%d for 2)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_bool with_ext_1 = drb_ffi__ZTS11ice_fs_bool_FromRuby(state, args[1]);
    char *ret_val = ice_fs_filename(path_0, with_ext_1);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_ext_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_ext': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_fs_ext(path_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_is_ext_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_is_ext': wrong number of arguments (%d for 2)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ext_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_fs_bool ret_val = ice_fs_is_ext(path_0, ext_1);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_prev_path_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_prev_path': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_fs_prev_path(path_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_path_parents_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_path_parents': wrong number of arguments (%d for 2)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long *results_1 = drb_ffi__ZTSPm_FromRuby(state, args[1]);
    char **ret_val = ice_fs_path_parents(path_0, results_1);
    return drb_ffi__ZTSPPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_path_exists_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_path_exists': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_bool ret_val = ice_fs_path_exists(path_0);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_cwd_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 0)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_cwd': wrong number of arguments (%d for 0)", argc);
    char *ret_val = ice_fs_cwd();
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_home_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 0)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_home': wrong number of arguments (%d for 0)", argc);
    char *ret_val = ice_fs_home();
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_format_path_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_format_path': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_fs_format_path(path_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_fullpath_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_fullpath': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_fs_fullpath(path_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_link_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 3)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_link': wrong number of arguments (%d for 3)", argc);
    char *path1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *path2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_fs_bool hard_link_2 = drb_ffi__ZTS11ice_fs_bool_FromRuby(state, args[2]);
    ice_fs_bool ret_val = ice_fs_link(path1_0, path2_1, hard_link_2);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_readlink_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_readlink': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *ret_val = ice_fs_readlink(path_0);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_type_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_type': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_object_type ret_val = ice_fs_type(path_0);
    return drb_ffi__ZTS18ice_fs_object_type_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_file_content_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_file_content': wrong number of arguments (%d for 2)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long *file_size_1 = drb_ffi__ZTSPm_FromRuby(state, args[1]);
    char *ret_val = ice_fs_file_content(path_0, file_size_1);
    return drb_ffi__ZTSPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_file_write_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 3)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_file_write': wrong number of arguments (%d for 3)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *content_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_fs_bool append_2 = drb_ffi__ZTS11ice_fs_bool_FromRuby(state, args[2]);
    ice_fs_bool ret_val = ice_fs_file_write(path_0, content_1, append_2);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_file_lines_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_file_lines': wrong number of arguments (%d for 2)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    unsigned long *lines_1 = drb_ffi__ZTSPm_FromRuby(state, args[1]);
    char **ret_val = ice_fs_file_lines(path_0, lines_1);
    return drb_ffi__ZTSPPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_chdir_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_chdir': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_bool ret_val = ice_fs_chdir(path_0);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_dir_content_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_dir_content': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_dir ret_val = ice_fs_dir_content(path_0);
    return drb_ffi__ZTS10ice_fs_dir_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_free_dir_content_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_free_dir_content': wrong number of arguments (%d for 1)", argc);
    ice_fs_dir *dir_0 = drb_ffi__ZTSP10ice_fs_dir_FromRuby(state, args[0]);
    ice_fs_free_dir_content(dir_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_fs_dir_search_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 3)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_dir_search': wrong number of arguments (%d for 3)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *str_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    unsigned long *results_2 = drb_ffi__ZTSPm_FromRuby(state, args[2]);
    char **ret_val = ice_fs_dir_search(path_0, str_1, results_2);
    return drb_ffi__ZTSPPc_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_create_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_create': wrong number of arguments (%d for 2)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_object_type type_1 = drb_ffi__ZTS18ice_fs_object_type_FromRuby(state, args[1]);
    ice_fs_bool ret_val = ice_fs_create(path_0, type_1);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_remove_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_remove': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_bool ret_val = ice_fs_remove(path_0);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_clear_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_clear': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_bool ret_val = ice_fs_clear(path_0);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_copy_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_copy': wrong number of arguments (%d for 2)", argc);
    char *path1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *path2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_fs_bool ret_val = ice_fs_copy(path1_0, path2_1);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_move_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_move': wrong number of arguments (%d for 2)", argc);
    char *path1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *path2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_fs_bool ret_val = ice_fs_move(path1_0, path2_1);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_rename_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_rename': wrong number of arguments (%d for 2)", argc);
    char *path1_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    char *path2_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    ice_fs_bool ret_val = ice_fs_rename(path1_0, path2_1);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_is_empty_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_is_empty': wrong number of arguments (%d for 1)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_bool ret_val = ice_fs_is_empty(path_0);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_fs_get_date_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 3)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_fs_get_date': wrong number of arguments (%d for 3)", argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    ice_fs_date_type date_type_1 = drb_ffi__ZTS16ice_fs_date_type_FromRuby(state, args[1]);
    ice_fs_date *info_2 = drb_ffi__ZTSP11ice_fs_date_FromRuby(state, args[2]);
    ice_fs_bool ret_val = ice_fs_get_date(path_0, date_type_1, info_2);
    return drb_ffi__ZTS11ice_fs_bool_ToRuby(state, ret_val);
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *));
DRB_FFI_EXPORT
void drb_register_c_extensions(void *(*lookup)(const char *), mrb_state *state, struct RClass *FFI) {
    if (drb_ffi_init_indirect_functions(lookup))
        return;
    struct RClass *module = mrb_define_module_under_f(state, FFI, "CExt");
    struct RClass *object_class = state->object_class;
    mrb_define_module_function_f(state, module, "ice_fs_str_len", drb_ffi_ice_fs_str_len_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_str_starts_with_slash", drb_ffi_ice_fs_str_starts_with_slash_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_str_ends_with_slash", drb_ffi_ice_fs_str_ends_with_slash_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_str_slashes", drb_ffi_ice_fs_str_slashes_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_str_dots", drb_ffi_ice_fs_str_dots_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_str_same", drb_ffi_ice_fs_str_same_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_str_sub", drb_ffi_ice_fs_str_sub_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "ice_fs_str_copy", drb_ffi_ice_fs_str_copy_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_str_split", drb_ffi_ice_fs_str_split_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "ice_fs_str_splitlines", drb_ffi_ice_fs_str_splitlines_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_str_matches", drb_ffi_ice_fs_str_matches_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "ice_fs_free_str", drb_ffi_ice_fs_free_str_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_free_strarr", drb_ffi_ice_fs_free_strarr_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_root", drb_ffi_ice_fs_root_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_is_root", drb_ffi_ice_fs_is_root_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_concat_path", drb_ffi_ice_fs_concat_path_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_filename", drb_ffi_ice_fs_filename_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_ext", drb_ffi_ice_fs_ext_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_is_ext", drb_ffi_ice_fs_is_ext_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_prev_path", drb_ffi_ice_fs_prev_path_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_path_parents", drb_ffi_ice_fs_path_parents_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_path_exists", drb_ffi_ice_fs_path_exists_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_cwd", drb_ffi_ice_fs_cwd_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "ice_fs_home", drb_ffi_ice_fs_home_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "ice_fs_format_path", drb_ffi_ice_fs_format_path_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_fullpath", drb_ffi_ice_fs_fullpath_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_link", drb_ffi_ice_fs_link_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "ice_fs_readlink", drb_ffi_ice_fs_readlink_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_type", drb_ffi_ice_fs_type_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_file_content", drb_ffi_ice_fs_file_content_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_file_write", drb_ffi_ice_fs_file_write_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "ice_fs_file_lines", drb_ffi_ice_fs_file_lines_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_chdir", drb_ffi_ice_fs_chdir_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_dir_content", drb_ffi_ice_fs_dir_content_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_free_dir_content", drb_ffi_ice_fs_free_dir_content_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_dir_search", drb_ffi_ice_fs_dir_search_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "ice_fs_create", drb_ffi_ice_fs_create_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_remove", drb_ffi_ice_fs_remove_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_clear", drb_ffi_ice_fs_clear_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_copy", drb_ffi_ice_fs_copy_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_move", drb_ffi_ice_fs_move_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_rename", drb_ffi_ice_fs_rename_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_fs_is_empty", drb_ffi_ice_fs_is_empty_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_fs_get_date", drb_ffi_ice_fs_get_date_Binding, MRB_ARGS_REQ(3));
    struct RClass *CharPointerClass = mrb_define_class_under_f(state, module, "CharPointer", object_class);
    mrb_define_class_method_f(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *CharPointerPointerClass = mrb_define_class_under_f(state, module, "CharPointerPointer", object_class);
    mrb_define_class_method_f(state, CharPointerPointerClass, "new", drb_ffi__ZTSPPc_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerPointerClass, "value", drb_ffi__ZTSPPc_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerPointerClass, "[]", drb_ffi__ZTSPPc_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, CharPointerPointerClass, "[]=", drb_ffi__ZTSPPc_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, CharPointerPointerClass, "nil?", drb_ffi__ZTSPPc_IsNil, MRB_ARGS_REQ(0));
    struct RClass *Unsigned_longPointerClass = mrb_define_class_under_f(state, module, "Unsigned_longPointer", object_class);
    mrb_define_class_method_f(state, Unsigned_longPointerClass, "new", drb_ffi__ZTSPm_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_longPointerClass, "value", drb_ffi__ZTSPm_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_longPointerClass, "[]", drb_ffi__ZTSPm_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Unsigned_longPointerClass, "[]=", drb_ffi__ZTSPm_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, Unsigned_longPointerClass, "nil?", drb_ffi__ZTSPm_IsNil, MRB_ARGS_REQ(0));
    struct RClass *Unsigned_longPointerPointerClass = mrb_define_class_under_f(state, module, "Unsigned_longPointerPointer", object_class);
    mrb_define_class_method_f(state, Unsigned_longPointerPointerClass, "new", drb_ffi__ZTSPPm_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_longPointerPointerClass, "value", drb_ffi__ZTSPPm_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_longPointerPointerClass, "[]", drb_ffi__ZTSPPm_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Unsigned_longPointerPointerClass, "[]=", drb_ffi__ZTSPPm_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, Unsigned_longPointerPointerClass, "nil?", drb_ffi__ZTSPPm_IsNil, MRB_ARGS_REQ(0));
    struct RClass *ice_fs_dir_ptr_class = mrb_define_class_under_f(state, module, "ICE_FS_DIR_PTR", object_class);
    mrb_define_class_method_f(state, ice_fs_dir_ptr_class, "new", drb_ffi__ZTSP10ice_fs_dir_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_dir_ptr_class, "value", drb_ffi__ZTSP10ice_fs_dir_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_dir_ptr_class, "[]", drb_ffi__ZTSP10ice_fs_dir_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_dir_ptr_class, "[]=", drb_ffi__ZTSP10ice_fs_dir_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, ice_fs_dir_ptr_class, "nil?", drb_ffi__ZTSP10ice_fs_dir_IsNil, MRB_ARGS_REQ(0));
    struct RClass *ice_fs_date_ptr_class = mrb_define_class_under_f(state, module, "ICE_FS_DATE_PTR", object_class);
    mrb_define_class_method_f(state, ice_fs_date_ptr_class, "new", drb_ffi__ZTSP11ice_fs_date_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_ptr_class, "value", drb_ffi__ZTSP11ice_fs_date_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_ptr_class, "[]", drb_ffi__ZTSP11ice_fs_date_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_ptr_class, "[]=", drb_ffi__ZTSP11ice_fs_date_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, ice_fs_date_ptr_class, "nil?", drb_ffi__ZTSP11ice_fs_date_IsNil, MRB_ARGS_REQ(0));
    struct RClass *ice_fs_object_ptr_class = mrb_define_class_under_f(state, module, "ICE_FS_OBJECT_PTR", object_class);
    mrb_define_class_method_f(state, ice_fs_object_ptr_class, "new", drb_ffi__ZTSP13ice_fs_object_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_object_ptr_class, "value", drb_ffi__ZTSP13ice_fs_object_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_object_ptr_class, "[]", drb_ffi__ZTSP13ice_fs_object_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_object_ptr_class, "[]=", drb_ffi__ZTSP13ice_fs_object_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, ice_fs_object_ptr_class, "nil?", drb_ffi__ZTSP13ice_fs_object_IsNil, MRB_ARGS_REQ(0));
    struct RClass *ice_fs_dir_class = mrb_define_class_under_f(state, module, "ICE_FS_DIR", object_class);
    mrb_define_class_method_f(state, ice_fs_dir_class, "new", drb_ffi__ZTS10ice_fs_dir_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_dir_class, "items", drb_ffi__ZTS10ice_fs_dir_items_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_dir_class, "items=", drb_ffi__ZTS10ice_fs_dir_items_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_dir_class, "items_count", drb_ffi__ZTS10ice_fs_dir_items_count_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_dir_class, "items_count=", drb_ffi__ZTS10ice_fs_dir_items_count_Set, MRB_ARGS_REQ(1));
    struct RClass *ice_fs_date_class = mrb_define_class_under_f(state, module, "ICE_FS_DATE", object_class);
    mrb_define_class_method_f(state, ice_fs_date_class, "new", drb_ffi__ZTS11ice_fs_date_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "str", drb_ffi__ZTS11ice_fs_date_str_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "str=", drb_ffi__ZTS11ice_fs_date_str_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "epoch", drb_ffi__ZTS11ice_fs_date_epoch_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "epoch=", drb_ffi__ZTS11ice_fs_date_epoch_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "seconds", drb_ffi__ZTS11ice_fs_date_seconds_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "seconds=", drb_ffi__ZTS11ice_fs_date_seconds_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "minutes", drb_ffi__ZTS11ice_fs_date_minutes_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "minutes=", drb_ffi__ZTS11ice_fs_date_minutes_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "hour", drb_ffi__ZTS11ice_fs_date_hour_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "hour=", drb_ffi__ZTS11ice_fs_date_hour_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "week_day", drb_ffi__ZTS11ice_fs_date_week_day_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "week_day=", drb_ffi__ZTS11ice_fs_date_week_day_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "month_day", drb_ffi__ZTS11ice_fs_date_month_day_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "month_day=", drb_ffi__ZTS11ice_fs_date_month_day_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "year_day", drb_ffi__ZTS11ice_fs_date_year_day_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "year_day=", drb_ffi__ZTS11ice_fs_date_year_day_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "month", drb_ffi__ZTS11ice_fs_date_month_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "month=", drb_ffi__ZTS11ice_fs_date_month_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "season", drb_ffi__ZTS11ice_fs_date_season_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "season=", drb_ffi__ZTS11ice_fs_date_season_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_date_class, "year", drb_ffi__ZTS11ice_fs_date_year_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_date_class, "year=", drb_ffi__ZTS11ice_fs_date_year_Set, MRB_ARGS_REQ(1));
    struct RClass *ice_fs_object_class = mrb_define_class_under_f(state, module, "ICE_FS_OBJECT", object_class);
    mrb_define_class_method_f(state, ice_fs_object_class, "new", drb_ffi__ZTS13ice_fs_object_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_object_class, "name", drb_ffi__ZTS13ice_fs_object_name_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_object_class, "name=", drb_ffi__ZTS13ice_fs_object_name_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ice_fs_object_class, "type", drb_ffi__ZTS13ice_fs_object_type_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ice_fs_object_class, "type=", drb_ffi__ZTS13ice_fs_object_type_Set, MRB_ARGS_REQ(1));
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
