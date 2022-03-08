$gtk.ffi_misc.gtk_dlopen("ice_ram")
include FFI::CExt

# Boolean Enum, To avoid including stdbool.h
ICE_RAM_FALSE   = -1
ICE_RAM_TRUE    = 0
