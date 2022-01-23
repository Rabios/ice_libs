local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef

ffi_cdef([[
/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_batt_bool {
    ICE_BATT_FALSE  = -1,
    ICE_BATT_TRUE   = 0
} ice_batt_bool;
    
/* Struct that contains battery status (Exists?, Charging?, Battery Level) */
typedef struct ice_batt_info {
    ice_batt_bool exists, charging;
    unsigned level;
} ice_batt_info;
    
/* Enumeration for errors that may occur */
typedef enum ice_batt_error {
    ICE_BATT_ERROR_OK = 0,          /* OK - no errors */
    ICE_BATT_ERROR_UNKNOWN_STATUS,  /* Occurs when failed to get battery status, Or if battery status is undefined, Or device doesn't have battery */
    ICE_BATT_ERROR_SYSCALL_FAILURE  /* Occurs when platform-specific function fails */
} ice_batt_error;
    
/* ============================== Functions ============================== */
    
/* [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_batt on Android, This Should be called first before other ice_batt.h functions */
void ice_batt_use_native_activity(void *activity);
    
/* Fetches battery info and stores info into ice_batt_info struct by pointing to, Returns ICE_BATT_ERROR_OK on success or any other values from ice_batt_error enum on failure! */
ice_batt_error ice_batt_get_info(ice_batt_info *batt_info);
]])

return ffi_load("ice_batt")
