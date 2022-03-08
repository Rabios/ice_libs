$gtk.ffi_misc.gtk_dlopen("ice_cpu")
include FFI::CExt

# Boolean Enum, To avoid including stdbool.h
ICE_CPU_FALSE   = -1
ICE_CPU_TRUE    = 0
