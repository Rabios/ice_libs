local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef

ffi_cdef([[
/* ============================== Data Types ============================== */

/* Typedef for very unsigned long integers */
typedef unsigned long ice_time_ulong;

/* Enumeration for week days */
typedef enum ice_time_day {
    ICE_TIME_DAY_UNKNOWN = 0,
    ICE_TIME_DAY_SUNDAY,
    ICE_TIME_DAY_MONDAY,
    ICE_TIME_DAY_TUESDAY,
    ICE_TIME_DAY_WEDNESDAY,
    ICE_TIME_DAY_THURSDAY,
    ICE_TIME_DAY_FRIDAY,
    ICE_TIME_DAY_SATURDAY
} ice_time_day;

/* Enumeration for year months */
typedef enum ice_time_month {
    ICE_TIME_MONTH_UNKNOWN = 0,
    ICE_TIME_MONTH_JANUARY,
    ICE_TIME_MONTH_FEBRUARY,
    ICE_TIME_MONTH_MARCH,
    ICE_TIME_MONTH_APRIL,
    ICE_TIME_MONTH_MAY,
    ICE_TIME_MONTH_JUNE,
    ICE_TIME_MONTH_JULY,
    ICE_TIME_MONTH_AUGUST,
    ICE_TIME_MONTH_SEPTEMBER,
    ICE_TIME_MONTH_OCTOBER,
    ICE_TIME_MONTH_NOVEMBER,
    ICE_TIME_MONTH_DECEMBER
} ice_time_month;

/* Enumeration for seasons */
typedef enum ice_time_season {
    ICE_TIME_SEASON_UNKNOWN = 0,
    ICE_TIME_SEASON_WINTER,
    ICE_TIME_SEASON_SPRING,
    ICE_TIME_SEASON_SUMMER,
    ICE_TIME_SEASON_AUTUMN
} ice_time_season;

/* Struct that contains patched current time info, Including ticks */
typedef struct ice_time_info {
    const char *str;                /* Time as string */
    ice_time_ulong clock_ticks;     /* Clock Ticks (Nanoseconds) */
    ice_time_ulong uptime;          /* Ticks since system started (Milliseconds) */
    ice_time_ulong epoch;           /* Unix timestamp */
    unsigned seconds;
    unsigned minutes;
    unsigned hour;
    ice_time_day week_day;          /* (ICE_TIME_DAY_SUNDAY - ICE_TIME_DAY_SATURDAY) */
    unsigned month_day;             /* (1 - Month last day number) */
    unsigned year_day;              /* (1 - 365) */
    ice_time_month month;           /* (ICE_TIME_MONTH_JANUARY - ICE_TIME_MONTH_DECEMBER) */
    ice_time_season season;         /* (ICE_TIME_SEASON_WINTER - ICE_TIME_SEASON_AUTUMN) */
    unsigned year;
} ice_time_info;

/* Enumeration for errors that may occur */
typedef enum ice_time_error {
    ICE_TIME_ERROR_OK = 0,          /* OK - no errors */
    ICE_TIME_ERROR_UNKNOWN_TIME,    /* Occurs when time() function fails */
    ICE_TIME_ERROR_UNKNOWN_CLOCK,   /* Occurs when retrieving uptime function fails (Only given on Linux and BSD) */
    ICE_TIME_ERROR_SYSCALL_FAILURE, /* Occurs when platform-specific call fails */
    ICE_TIME_ERROR_INVALID_POINTER  /* Occurs when passing NULL (Zero) as argument to ice_time_get_info() */
} ice_time_error;

/* ============================== Functions ============================== */

/* Returns difference between 2 clock ticks, Each one can be acquired from the pointer to ice_time_info struct */
ice_time_ulong ice_time_diff(const ice_time_info *t1, const ice_time_info *t2);

/* Returns difference between clock tick of current time and clock time of specific time, t is passed as pointer to ice_time_info struct for the specific time */
ice_time_ulong ice_time_since(const ice_time_info *t);

/* Returns Delta Time between 2 clock ticks, Each one can be acquired from the pointer to ice_time_info struct */
double ice_time_dt(const ice_time_info *t1, const ice_time_info *t2);

/* Retrieves current time info (eg. Ticks, Seconds, Days, Months, Year, Month, etc...) and stores info in ice_time_info struct by pointing to, Returns ICE_TIME_ERROR_OK on success or any other values from ice_time_error enum on failure! */
ice_time_error ice_time_get_info(ice_time_info *time_info);

/* Sleeps thread/program for Milliseconds */
void ice_time_sleep(ice_time_ulong ms);

/* Converts: Attoseconds -> Nanoseconds */
double ice_time_as_to_ns(ice_time_ulong as);

/* Converts: Attoseconds -> Microseconds */
double ice_time_as_to_us(ice_time_ulong as);

/* Converts: Attoseconds -> Milliseconds */
double ice_time_as_to_ms(ice_time_ulong as);

/* Converts: Attoseconds -> Seconds */
double ice_time_as_to_sec(ice_time_ulong as);

/* Converts: Nanoseconds -> Attoseconds */
double ice_time_ns_to_as(ice_time_ulong ns);

/* Converts: Nanoseconds -> Microseconds */
double ice_time_ns_to_us(ice_time_ulong ns);

/* Converts: Nanoseconds -> Milliseconds */
double ice_time_ns_to_ms(ice_time_ulong ns);

/* Converts: Nanoseconds -> Seconds */
double ice_time_ns_to_sec(ice_time_ulong ns);

/* Converts: Microseconds -> Attoseconds */
double ice_time_us_to_as(ice_time_ulong us);

/* Converts: Microseconds -> Nanoseconds */
double ice_time_us_to_ns(ice_time_ulong us);

/* Converts: Microseconds -> Milliseconds */
double ice_time_us_to_ms(ice_time_ulong us);

/* Converts: Microseconds -> Seconds */
double ice_time_us_to_sec(ice_time_ulong us);

/* Converts: Milliseconds -> Attoseconds */
double ice_time_ms_to_as(ice_time_ulong ms);

/* Converts: Milliseconds -> Nanoseconds */
double ice_time_ms_to_ns(ice_time_ulong ms);

/* Converts: Milliseconds -> Microseconds */
double ice_time_ms_to_us(ice_time_ulong ms);

/* Converts: Milliseconds -> Seconds */
double ice_time_ms_to_sec(ice_time_ulong ms);

/* Converts: Seconds -> Attoseconds */
double ice_time_sec_to_as(ice_time_ulong sec);

/* Converts: Seconds -> Nanoseconds */
double ice_time_sec_to_ns(ice_time_ulong sec);

/* Converts: Seconds -> Microseconds */
double ice_time_sec_to_us(ice_time_ulong sec);

/* Converts: Seconds -> Milliseconds */
double ice_time_sec_to_ms(ice_time_ulong sec);
]])

return ffi_load("ice_time")
