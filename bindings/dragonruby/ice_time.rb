$gtk.ffi_misc.gtk_dlopen("ice_time")
include FFI::CExt

# Enumeration for week days
ICE_TIME_DAY_UNKNOWN            = 0
ICE_TIME_DAY_SUNDAY             = 1
ICE_TIME_DAY_MONDAY             = 2
ICE_TIME_DAY_TUESDAY            = 3
ICE_TIME_DAY_WEDNESDAY          = 4
ICE_TIME_DAY_THURSDAY           = 5
ICE_TIME_DAY_FRIDAY             = 6
ICE_TIME_DAY_SATURDAY           = 7

# Enumeration for year months
ICE_TIME_MONTH_UNKNOWN          = 0
ICE_TIME_MONTH_JANUARY          = 1
ICE_TIME_MONTH_FEBRUARY         = 2
ICE_TIME_MONTH_MARCH            = 3
ICE_TIME_MONTH_APRIL            = 4
ICE_TIME_MONTH_MAY              = 5
ICE_TIME_MONTH_JUNE             = 6
ICE_TIME_MONTH_JULY             = 7
ICE_TIME_MONTH_AUGUST           = 8
ICE_TIME_MONTH_SEPTEMBER        = 9
ICE_TIME_MONTH_OCTOBER          = 10
ICE_TIME_MONTH_NOVEMBER         = 11
ICE_TIME_MONTH_DECEMBER         = 12

# Enumeration for seasons
ICE_TIME_SEASON_UNKNOWN         = 0
ICE_TIME_SEASON_WINTER          = 1
ICE_TIME_SEASON_SPRING          = 2
ICE_TIME_SEASON_SUMMER          = 3
ICE_TIME_SEASON_AUTUMN          = 4

# Enumeration for errors that may occur
ICE_TIME_ERROR_OK               = 0     # OK - no errors
ICE_TIME_ERROR_UNKNOWN_TIME     = 1     # Occurs when time() function fails
ICE_TIME_ERROR_UNKNOWN_CLOCK    = 2     # Occurs when retrieving uptime function fails (Only given on Linux and BSD)
ICE_TIME_ERROR_SYSCALL_FAILURE  = 3     # Occurs when platform-specific call fails
ICE_TIME_ERROR_INVALID_POINTER  = 4     # Occurs when passing NULL (Zero) as argument to ice_time_get_info()
