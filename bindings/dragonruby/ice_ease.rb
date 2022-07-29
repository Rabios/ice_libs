$gtk.ffi_misc.gtk_dlopen("ice_ease")
include FFI::CExt

# Defines
ICE_EASE_PI             = 3.1415926535897932384626433832795 # Pi
ICE_EASE_TAU            = 6.283185307179586476925286766559  # Tau (Double Pi)
ICE_EASE_HALF_PI        = 1.5707963267948966192313216916398 # Half of Pi

# Easing Types
ICE_EASE_TYPE_PROGRESS  = 0
ICE_EASE_TYPE_PENNER    = 1