$gtk.ffi_misc.gtk_dlopen("ice_batt")
include FFI::CExt

# Boolean Enum, To avoid including stdbool.h
ICE_BATT_FALSE  = -1
ICE_BATT_TRUE   = 0

# Enumeration for errors that may occur
ICE_BATT_ERROR_OK               = 0     # OK - no errors
ICE_BATT_ERROR_UNKNOWN_STATUS   = 1     # Occurs when failed to get battery status, Or if battery status is undefined, Or device doesn't have battery
ICE_BATT_ERROR_SYSCALL_FAILURE  = 2     # Occurs when platform-specific function fails
ICE_BATT_ERROR_INVALID_POINTER  = 3     # Occurs when passing NULL (Zero) as argument to ice_batt_get_info()
