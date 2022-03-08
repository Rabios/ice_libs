$gtk.ffi_misc.gtk_dlopen("ice_fs")
include FFI::CExt

# Boolean Enum, To avoid including stdbool.h
ICE_FS_FALSE                    = -1
ICE_FS_TRUE                     = 0

# Type of object in path (File, Folder, etc...)
ICE_FS_OBJECT_TYPE_NONE         = -1    # Given if path does not exist
ICE_FS_OBJECT_TYPE_FILE         = 0     # File
ICE_FS_OBJECT_TYPE_DIR          = 1     # Directory

# Enumeration for week days
ICE_FS_DATE_DAY_UNKNOWN         = 0
ICE_FS_DATE_DAY_SUNDAY          = 1
ICE_FS_DATE_DAY_MONDAY          = 2
ICE_FS_DATE_DAY_TUESDAY         = 3
ICE_FS_DATE_DAY_WEDNESDAY       = 4
ICE_FS_DATE_DAY_THURSDAY        = 5
ICE_FS_DATE_DAY_FRIDAY          = 6
ICE_FS_DATE_DAY_SATURDAY        = 7

# Enumeration for year months
ICE_FS_DATE_MONTH_UNKNOWN       = 0
ICE_FS_DATE_MONTH_JANUARY       = 1
ICE_FS_DATE_MONTH_FEBRUARY      = 2
ICE_FS_DATE_MONTH_MARCH         = 3
ICE_FS_DATE_MONTH_APRIL         = 4
ICE_FS_DATE_MONTH_MAY           = 5
ICE_FS_DATE_MONTH_JUNE          = 6
ICE_FS_DATE_MONTH_JULY          = 7
ICE_FS_DATE_MONTH_AUGUST        = 8
ICE_FS_DATE_MONTH_SEPTEMBER     = 9
ICE_FS_DATE_MONTH_OCTOBER       = 10
ICE_FS_DATE_MONTH_NOVEMBER      = 11
ICE_FS_DATE_MONTH_DECEMBER      = 12

# Enumeration for seasons
ICE_FS_DATE_SEASON_UNKNOWN      = 0
ICE_FS_DATE_SEASON_WINTER       = 1
ICE_FS_DATE_SEASON_SPRING       = 2
ICE_FS_DATE_SEASON_SUMMER       = 3
ICE_FS_DATE_SEASON_AUTUMN       = 4

# Enumeration for dates for file/directory (Which can be retrieved)
ICE_FS_LAST_ACCESS_DATE         = 0     # Last access date of file/directory
ICE_FS_LAST_MODIFICATION_DATE   = 1     # Last modification date of file/directory
ICE_FS_LAST_STATUS_CHANGE_DATE  = 2     # Last status change date of file/directory
