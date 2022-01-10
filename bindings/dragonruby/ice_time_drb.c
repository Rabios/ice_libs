#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>

#define ICE_TIME_IMPL 1
#include "ice_time.h"

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
static ice_time_ulong drb_ffi__ZTSm_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSm_ToRuby(mrb_state *state, ice_time_ulong value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTS13ice_time_info {
    drb_foreign_object_kind kind;
    ice_time_info value;
};
static mrb_data_type ForeignObjectType_ZTS13ice_time_info = {"ice_time_info", drb_free_foreign_object_indirect};
static ice_time_info drb_ffi__ZTS13ice_time_info_FromRuby(mrb_state *state, mrb_value self) {
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_time_info");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTS13ice_time_info);
    return ((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS13ice_time_info_ToRuby(mrb_state *state, ice_time_info value) {
    struct drb_foreign_object_ZTS13ice_time_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS13ice_time_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_time_info");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS13ice_time_info);
    return mrb_obj_value(rdata);
}
static double drb_ffi__ZTSd_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_float_f(state, self);
    return mrb_float(self);
}
static mrb_value drb_ffi__ZTSd_ToRuby(mrb_state *state, double value) {
    return drb_float_value_f(state, value);
}
static ice_time_error drb_ffi__ZTS14ice_time_error_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS14ice_time_error_ToRuby(mrb_state *state, ice_time_error value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSP13ice_time_info {
    drb_foreign_object_kind kind;
    ice_time_info *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP13ice_time_info = {"ice_time_info*", drb_free_foreign_object_indirect};
static ice_time_info *drb_ffi__ZTSP13ice_time_info_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_time_infoPointer");
    drb_typecheck_aggregate_f(state, self, klass, &ForeignObjectType_ZTSP13ice_time_info);
    return ((struct drb_foreign_object_ZTSP13ice_time_info *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP13ice_time_info_ToRuby(mrb_state *state, ice_time_info *value) {
    struct drb_foreign_object_ZTSP13ice_time_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP13ice_time_info));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_time_infoPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP13ice_time_info);
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
static unsigned int drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, unsigned int value) {
    return mrb_fixnum_value(value);
}
static ice_time_day drb_ffi__ZTS12ice_time_day_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS12ice_time_day_ToRuby(mrb_state *state, ice_time_day value) {
    return mrb_fixnum_value(value);
}
static ice_time_month drb_ffi__ZTS14ice_time_month_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS14ice_time_month_ToRuby(mrb_state *state, ice_time_month value) {
    return mrb_fixnum_value(value);
}
static ice_time_season drb_ffi__ZTS15ice_time_season_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTS15ice_time_season_ToRuby(mrb_state *state, ice_time_season value) {
    return mrb_fixnum_value(value);
}
static char drb_ffi__ZTSc_FromRuby(mrb_state *state, mrb_value self) {
    drb_typecheck_int_f(state, self);
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSc_ToRuby(mrb_state *state, char value) {
    return mrb_fixnum_value(value);
}
static mrb_value drb_ffi__ZTSP13ice_time_info_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP13ice_time_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP13ice_time_info));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(ice_time_info));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "Ice_time_infoPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP13ice_time_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP13ice_time_info_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS13ice_time_info_ToRuby(mrb, *drb_ffi__ZTSP13ice_time_info_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP13ice_time_info_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP13ice_time_info_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP13ice_time_info_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS13ice_time_info_ToRuby(mrb, drb_ffi__ZTSP13ice_time_info_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP13ice_time_info_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ice_time_info new_value = drb_ffi__ZTS13ice_time_info_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP13ice_time_info_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
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
static mrb_value drb_ffi__ZTS13ice_time_info_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS13ice_time_info *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS13ice_time_info *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CExt");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Ice_time_info");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS13ice_time_info);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS13ice_time_info_str_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSPc_ToRuby(state, record.str);
}
static mrb_value drb_ffi__ZTS13ice_time_info_str_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    char *new_value = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->str = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_clock_ticks_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSm_ToRuby(state, record.clock_ticks);
}
static mrb_value drb_ffi__ZTS13ice_time_info_clock_ticks_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_time_ulong new_value = drb_ffi__ZTSm_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->clock_ticks = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_uptime_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSm_ToRuby(state, record.uptime);
}
static mrb_value drb_ffi__ZTS13ice_time_info_uptime_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_time_ulong new_value = drb_ffi__ZTSm_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->uptime = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_epoch_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSm_ToRuby(state, record.epoch);
}
static mrb_value drb_ffi__ZTS13ice_time_info_epoch_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_time_ulong new_value = drb_ffi__ZTSm_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->epoch = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_second_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.second);
}
static mrb_value drb_ffi__ZTS13ice_time_info_second_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->second = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_minute_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.minute);
}
static mrb_value drb_ffi__ZTS13ice_time_info_minute_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->minute = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_hour_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.hour);
}
static mrb_value drb_ffi__ZTS13ice_time_info_hour_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->hour = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_week_day_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTS12ice_time_day_ToRuby(state, record.week_day);
}
static mrb_value drb_ffi__ZTS13ice_time_info_week_day_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_time_day new_value = drb_ffi__ZTS12ice_time_day_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->week_day = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_month_day_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.month_day);
}
static mrb_value drb_ffi__ZTS13ice_time_info_month_day_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->month_day = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_year_day_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.year_day);
}
static mrb_value drb_ffi__ZTS13ice_time_info_year_day_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->year_day = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_month_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTS14ice_time_month_ToRuby(state, record.month);
}
static mrb_value drb_ffi__ZTS13ice_time_info_month_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_time_month new_value = drb_ffi__ZTS14ice_time_month_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->month = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_season_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTS15ice_time_season_ToRuby(state, record.season);
}
static mrb_value drb_ffi__ZTS13ice_time_info_season_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ice_time_season new_value = drb_ffi__ZTS15ice_time_season_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->season = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS13ice_time_info_year_Get(mrb_state *state, mrb_value self) {
    ice_time_info record = drb_ffi__ZTS13ice_time_info_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.year);
}
static mrb_value drb_ffi__ZTS13ice_time_info_year_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    unsigned int new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS13ice_time_info *)DATA_PTR(self))->value)->year = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_time_diff_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_diff': wrong number of arguments (%d for 2)", argc);
    ice_time_info t1_0 = drb_ffi__ZTS13ice_time_info_FromRuby(state, args[0]);
    ice_time_info t2_1 = drb_ffi__ZTS13ice_time_info_FromRuby(state, args[1]);
    ice_time_ulong ret_val = ice_time_diff(t1_0, t2_1);
    return drb_ffi__ZTSm_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_since_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_since': wrong number of arguments (%d for 1)", argc);
    ice_time_info t_0 = drb_ffi__ZTS13ice_time_info_FromRuby(state, args[0]);
    ice_time_ulong ret_val = ice_time_since(t_0);
    return drb_ffi__ZTSm_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_dt_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 2)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_dt': wrong number of arguments (%d for 2)", argc);
    ice_time_info t1_0 = drb_ffi__ZTS13ice_time_info_FromRuby(state, args[0]);
    ice_time_info t2_1 = drb_ffi__ZTS13ice_time_info_FromRuby(state, args[1]);
    double ret_val = ice_time_dt(t1_0, t2_1);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_get_info_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_get_info': wrong number of arguments (%d for 1)", argc);
    ice_time_info *time_info_0 = drb_ffi__ZTSP13ice_time_info_FromRuby(state, args[0]);
    ice_time_error ret_val = ice_time_get_info(time_info_0);
    return drb_ffi__ZTS14ice_time_error_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_sleep_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_sleep': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong ms_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    ice_time_sleep(ms_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_ice_time_as_to_ns_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_as_to_ns': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong as_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_as_to_ns(as_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_as_to_us_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_as_to_us': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong as_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_as_to_us(as_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_as_to_ms_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_as_to_ms': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong as_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_as_to_ms(as_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_as_to_sec_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_as_to_sec': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong as_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_as_to_sec(as_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_ns_to_as_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_ns_to_as': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong ns_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_ns_to_as(ns_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_ns_to_us_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_ns_to_us': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong ns_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_ns_to_us(ns_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_ns_to_ms_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_ns_to_ms': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong ns_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_ns_to_ms(ns_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_ns_to_sec_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_ns_to_sec': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong ns_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_ns_to_sec(ns_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_us_to_as_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_us_to_as': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong us_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_us_to_as(us_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_us_to_ns_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_us_to_ns': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong us_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_us_to_ns(us_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_us_to_ms_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_us_to_ms': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong us_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_us_to_ms(us_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_us_to_sec_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_us_to_sec': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong us_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_us_to_sec(us_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_ms_to_as_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_ms_to_as': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong ms_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_ms_to_as(ms_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_ms_to_ns_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_ms_to_ns': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong ms_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_ms_to_ns(ms_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_ms_to_us_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_ms_to_us': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong ms_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_ms_to_us(ms_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_ms_to_sec_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_ms_to_sec': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong ms_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_ms_to_sec(ms_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_sec_to_as_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_sec_to_as': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong sec_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_sec_to_as(sec_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_sec_to_ns_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_sec_to_ns': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong sec_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_sec_to_ns(sec_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_sec_to_us_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_sec_to_us': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong sec_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_sec_to_us(sec_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_ice_time_sec_to_ms_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    if (argc != 1)
        mrb_raisef_f(state, drb_getargument_error_f(state), "'ice_time_sec_to_ms': wrong number of arguments (%d for 1)", argc);
    ice_time_ulong sec_0 = drb_ffi__ZTSm_FromRuby(state, args[0]);
    double ret_val = ice_time_sec_to_ms(sec_0);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *));
DRB_FFI_EXPORT
void drb_register_c_extensions(void *(*lookup)(const char *), mrb_state *state, struct RClass *FFI) {
    if (drb_ffi_init_indirect_functions(lookup))
        return;
    struct RClass *module = mrb_define_module_under_f(state, FFI, "CExt");
    struct RClass *object_class = state->object_class;
    mrb_define_module_function_f(state, module, "ice_time_diff", drb_ffi_ice_time_diff_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_time_since", drb_ffi_ice_time_since_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_dt", drb_ffi_ice_time_dt_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "ice_time_get_info", drb_ffi_ice_time_get_info_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_sleep", drb_ffi_ice_time_sleep_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_as_to_ns", drb_ffi_ice_time_as_to_ns_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_as_to_us", drb_ffi_ice_time_as_to_us_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_as_to_ms", drb_ffi_ice_time_as_to_ms_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_as_to_sec", drb_ffi_ice_time_as_to_sec_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_ns_to_as", drb_ffi_ice_time_ns_to_as_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_ns_to_us", drb_ffi_ice_time_ns_to_us_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_ns_to_ms", drb_ffi_ice_time_ns_to_ms_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_ns_to_sec", drb_ffi_ice_time_ns_to_sec_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_us_to_as", drb_ffi_ice_time_us_to_as_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_us_to_ns", drb_ffi_ice_time_us_to_ns_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_us_to_ms", drb_ffi_ice_time_us_to_ms_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_us_to_sec", drb_ffi_ice_time_us_to_sec_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_ms_to_as", drb_ffi_ice_time_ms_to_as_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_ms_to_ns", drb_ffi_ice_time_ms_to_ns_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_ms_to_us", drb_ffi_ice_time_ms_to_us_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_ms_to_sec", drb_ffi_ice_time_ms_to_sec_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_sec_to_as", drb_ffi_ice_time_sec_to_as_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_sec_to_ns", drb_ffi_ice_time_sec_to_ns_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_sec_to_us", drb_ffi_ice_time_sec_to_us_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "ice_time_sec_to_ms", drb_ffi_ice_time_sec_to_ms_Binding, MRB_ARGS_REQ(1));
    struct RClass *Ice_time_infoPointerClass = mrb_define_class_under_f(state, module, "Ice_time_infoPointer", object_class);
    mrb_define_class_method_f(state, Ice_time_infoPointerClass, "new", drb_ffi__ZTSP13ice_time_info_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoPointerClass, "value", drb_ffi__ZTSP13ice_time_info_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoPointerClass, "[]", drb_ffi__ZTSP13ice_time_info_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoPointerClass, "[]=", drb_ffi__ZTSP13ice_time_info_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, Ice_time_infoPointerClass, "nil?", drb_ffi__ZTSP13ice_time_info_IsNil, MRB_ARGS_REQ(0));
    struct RClass *CharPointerClass = mrb_define_class_under_f(state, module, "CharPointer", object_class);
    mrb_define_class_method_f(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *Ice_time_infoClass = mrb_define_class_under_f(state, module, "Ice_time_info", object_class);
    mrb_define_class_method_f(state, Ice_time_infoClass, "new", drb_ffi__ZTS13ice_time_info_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "str", drb_ffi__ZTS13ice_time_info_str_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "str=", drb_ffi__ZTS13ice_time_info_str_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "clock_ticks", drb_ffi__ZTS13ice_time_info_clock_ticks_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "clock_ticks=", drb_ffi__ZTS13ice_time_info_clock_ticks_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "uptime", drb_ffi__ZTS13ice_time_info_uptime_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "uptime=", drb_ffi__ZTS13ice_time_info_uptime_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "epoch", drb_ffi__ZTS13ice_time_info_epoch_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "epoch=", drb_ffi__ZTS13ice_time_info_epoch_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "second", drb_ffi__ZTS13ice_time_info_second_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "second=", drb_ffi__ZTS13ice_time_info_second_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "minute", drb_ffi__ZTS13ice_time_info_minute_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "minute=", drb_ffi__ZTS13ice_time_info_minute_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "hour", drb_ffi__ZTS13ice_time_info_hour_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "hour=", drb_ffi__ZTS13ice_time_info_hour_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "week_day", drb_ffi__ZTS13ice_time_info_week_day_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "week_day=", drb_ffi__ZTS13ice_time_info_week_day_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "month_day", drb_ffi__ZTS13ice_time_info_month_day_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "month_day=", drb_ffi__ZTS13ice_time_info_month_day_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "year_day", drb_ffi__ZTS13ice_time_info_year_day_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "year_day=", drb_ffi__ZTS13ice_time_info_year_day_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "month", drb_ffi__ZTS13ice_time_info_month_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "month=", drb_ffi__ZTS13ice_time_info_month_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "season", drb_ffi__ZTS13ice_time_info_season_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "season=", drb_ffi__ZTS13ice_time_info_season_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Ice_time_infoClass, "year", drb_ffi__ZTS13ice_time_info_year_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Ice_time_infoClass, "year=", drb_ffi__ZTS13ice_time_info_year_Set, MRB_ARGS_REQ(1));
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
