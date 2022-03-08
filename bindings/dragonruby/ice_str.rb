$gtk.ffi_misc.gtk_dlopen("ice_str")
include FFI::CExt

# Boolean Enum, To avoid including stdbool.h
ICE_STR_FALSE   = -1
ICE_STR_TRUE    = 0
