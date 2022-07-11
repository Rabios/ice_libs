/*

ice_time.h, Single-Header Cross-Platform C library for working with Time!


================================== Full Overview ==================================

ice_time.h is Single-Header Cross-Platform C library for working with time, It provides functions for fetching time info and time units conversion and sleep...

To use it #define ICE_TIME_IMPL then #include "ice_time.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

// Define the implementation of the library and include it
#define ICE_TIME_IMPL 1
#include "ice_time.h"

#include <stdio.h>

// Helper
#define trace(fname, str) (void) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(void) {
    // Struct that contains Time information
    ice_time_info current_time;
    
    // Fetch time information and store it in the struct
    ice_time_error res = ice_time_get_info(&current_time);

    // If the function failed to fetch time information, Trace error then terminate the program!
    if (res != ICE_TIME_ERROR_OK) {
        trace("ice_time_get_info", "ERROR: failed to get time info!");
        return -1;
    }

    // Print current time!
    (void) printf("Current Time: %s\n", current_time.str);

    return 0;
}


=================================== Library API ===================================

// Typedef for very unsigned long integers
typedef unsigned long ice_time_ulong;

// Enumeration for week days
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

// Enumeration for year months
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

// Enumeration for seasons
typedef enum ice_time_season {
    ICE_TIME_SEASON_UNKNOWN = 0,
    ICE_TIME_SEASON_WINTER,
    ICE_TIME_SEASON_SPRING,
    ICE_TIME_SEASON_SUMMER,
    ICE_TIME_SEASON_AUTUMN
} ice_time_season;

// Struct that contains patched current time info, Including ticks
typedef struct ice_time_info {
    const char *str;                // Time as string
    ice_time_ulong clock_ticks;     // Clock Ticks (Nanoseconds)
    ice_time_ulong uptime;          // Ticks since system started (Milliseconds)
    ice_time_ulong epoch;           // Unix timestamp
    unsigned seconds;
    unsigned minutes;
    unsigned hour;
    ice_time_day week_day;          // (ICE_TIME_DAY_SUNDAY - ICE_TIME_DAY_SATURDAY)
    unsigned month_day;             // (1 - Month last day number)
    unsigned year_day;              // (1 - 365)
    ice_time_month month;           // (ICE_TIME_MONTH_JANUARY - ICE_TIME_MONTH_DECEMBER)
    ice_time_season season;         // (ICE_TIME_SEASON_WINTER - ICE_TIME_SEASON_AUTUMN)
    unsigned year;
} ice_time_info;

// Enumeration for errors that may occur
typedef enum ice_time_error {
    ICE_TIME_ERROR_OK = 0,          // OK - no errors
    ICE_TIME_ERROR_UNKNOWN_TIME,    // Occurs when time() function fails
    ICE_TIME_ERROR_UNKNOWN_CLOCK,   // Occurs when clock_gettime() function fails (Linux/Unix only)
    ICE_TIME_ERROR_SYSCALL_FAILURE, // Occurs when platform-specific call fails
    ICE_TIME_ERROR_INVALID_POINTER  // Occurs when passing NULL (Zero) as argument to ice_time_get_info()
} ice_time_error;

// Returns difference between 2 clock ticks, Each one can be acquired from the pointer to ice_time_info struct
ice_time_ulong ice_time_diff(const ice_time_info *t1, const ice_time_info *t2);

// Returns difference between clock tick of current time and clock time of specific time, t is passed as pointer to ice_time_info struct for the specific time
ice_time_ulong ice_time_since(const ice_time_info *t);

// Returns Delta Time between 2 clock ticks, Each one can be acquired from the pointer to ice_time_info struct
double ice_time_dt(const ice_time_info *t1, const ice_time_info *t2);

// Retrieves current time info (eg. Ticks, Seconds, Days, Months, Year, Month, etc...) and stores info in ice_time_info struct by pointing to, Returns ICE_TIME_ERROR_OK on success or any other values from ice_time_error enum on failure!
ice_time_error ice_time_get_info(ice_time_info *time_info);

// Sleeps thread/program for Milliseconds
void ice_time_sleep(ice_time_ulong ms);

// Converts: Attoseconds -> Nanoseconds
double ice_time_as_to_ns(ice_time_ulong as);

// Converts: Attoseconds -> Microseconds
double ice_time_as_to_us(ice_time_ulong as);

// Converts: Attoseconds -> Milliseconds
double ice_time_as_to_ms(ice_time_ulong as);

// Converts: Attoseconds -> Seconds
double ice_time_as_to_sec(ice_time_ulong as);

// Converts: Nanoseconds -> Attoseconds
double ice_time_ns_to_as(ice_time_ulong ns);

// Converts: Nanoseconds -> Microseconds
double ice_time_ns_to_us(ice_time_ulong ns);

// Converts: Nanoseconds -> Milliseconds
double ice_time_ns_to_ms(ice_time_ulong ns);

// Converts: Nanoseconds -> Seconds
double ice_time_ns_to_sec(ice_time_ulong ns);

// Converts: Microseconds -> Attoseconds
double ice_time_us_to_as(ice_time_ulong us);

// Converts: Microseconds -> Nanoseconds
double ice_time_us_to_ns(ice_time_ulong us);

// Converts: Microseconds -> Milliseconds
double ice_time_us_to_ms(ice_time_ulong us);

// Converts: Microseconds -> Seconds
double ice_time_us_to_sec(ice_time_ulong us);

// Converts: Milliseconds -> Attoseconds
double ice_time_ms_to_as(ice_time_ulong ms);

// Converts: Milliseconds -> Nanoseconds
double ice_time_ms_to_ns(ice_time_ulong ms);

// Converts: Milliseconds -> Microseconds
double ice_time_ms_to_us(ice_time_ulong ms);

// Converts: Milliseconds -> Seconds
double ice_time_ms_to_sec(ice_time_ulong ms);

// Converts: Seconds -> Attoseconds
double ice_time_sec_to_as(ice_time_ulong sec);

// Converts: Seconds -> Nanoseconds
double ice_time_sec_to_ns(ice_time_ulong sec);

// Converts: Seconds -> Microseconds
double ice_time_sec_to_us(ice_time_ulong sec);

// Converts: Seconds -> Milliseconds
double ice_time_sec_to_ms(ice_time_ulong sec);


================================== Linking Flags ==================================

1. Microsoft Windows        =>  -lkernel32
2. Microsoft Windows Phone  =>  -lWindowsPhoneCore
3. Nintendo 3DS (libctru)   =>  -lctru -lc
4. Raspberry Pi Pico        =>  -lpico_time -lpico_util -lhardware_timer -lhardware_rtc -lc
5. Linux, BSD               =>  -lc

// NOTES:
// 1. When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragma preprocessor
// 2. Linking against "Standard C library" using flag -lc in most times automatically done...


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_time.h in the code...
#define ICE_TIME_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_TIME_VECTORCALL     // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_TIME_FASTCALL       // fastcall
#define ICE_TIME_STDCALL        // stdcall
#define ICE_TIME_CDECL          // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_TIME_MICROSOFT      // Microsoft Platforms
#define ICE_TIME_APPLE          // Apple Platforms
#define ICE_TIME_LINUX          // Linux
#define ICE_TIME_RPI_PICO       // Raspberry Pi Pico
#define ICE_TIME_3DS            // Nintendo 3DS (libctru)
#define ICE_TIME_BSD            // BSD (FreeBSD, DragonFly BSD, NetBSD, OpenBSD)
#define ICE_TIME_BLACKBERRY     // BlackBerry (QNX, QNX Neutrino, BlackBerry PlayBook, BlackBerry 10)

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_TIME_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_TIME_DLLEXPORT      // Export the symbols to build as shared library
#define ICE_TIME_DLLIMPORT      // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_TIME_INLINE         // inlines library functions (Only works on C99 Standard and above)
#define ICE_TIME_EXTERN         // externs library functions
#define ICE_TIME_STATIC         // statics library functions

// NOTE: You cannot #define both ICE_TIME_EXTERN and ICE_TIME_STATIC together in the code...


============================== Implementation Resources ===========================

1. https://docs.microsoft.com/en-us/windows/win32/sysinfo/time-functions
2. https://www.linux.it/~rubini/docs/sysctl
3. https://libctru.devkitpro.org/svc_8h.html
4. https://en.cppreference.com/w/c/chrono
5. https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__rtc.html
6. https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__timer.html
7. https://raspberrypi.github.io/pico-sdk-doxygen/group__pico__time.html
8. https://raspberrypi.github.io/pico-sdk-doxygen/group__util__datetime.html


================================= Support ice_libs ================================

ice_time.h is one of libraries that ice_libs project provide...

You can support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star (and/or fork) the repo on GitHub: https://github.com/Rabios/ice_libs
7. Share ice_libs Everywhere!
8. Join the Discord Server: https://discord.gg/KfkwXjCW


*/

#if !defined(ICE_TIME_H)
#define ICE_TIME_H 1

/* Disable security warnings for MSVC compiler to not force usage of secure versions of various C functions (Which requires C11) */
#if defined(_MSC_VER)
#  define _CRT_SECURE_NO_DEPRECATE 1
#  define _CRT_SECURE_NO_WARNINGS 1
#  pragma warning(disable:4996)
#endif

/* Allow to use calling convention if desired... */
#if defined(ICE_TIME_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_TIME_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_TIME_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_TIME_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_TIME_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_TIME_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_TIME_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_TIME_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_TIME_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_TIME_CDECL)
#  if defined(_MSC_VER)
#    define ICE_TIME_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_TIME_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_TIME_CALLCONV
#endif

#if !(defined(ICE_TIME_MICROSOFT) || defined(ICE_TIME_3DS) || defined(ICE_TIME_APPLE) || defined(ICE_TIME_LINUX) || defined(ICE_TIME_BSD) || defined(ICE_TIME_BLACKBERRY) || defined(ICE_TIME_RPI_PICO))
#  define ICE_TIME_AUTODETECT_PLATFORM 1
#endif

/* Platform Detection */
#if defined(ICE_TIME_AUTODETECT_PLATFORM)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_TIME_MICROSOFT 1
#  elif defined(__APPLE__) || defined(__DARWIN__) || defined(__MACH__)
#    define ICE_TIME_APPLE 1
#  elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__)
#    define ICE_TIME_BSD 1
#  elif defined(__BLACKBERRY10__) || defined(__BB10__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__PLAYBOOK__)
#    define ICE_TIME_BLACKBERRY 1
#  elif defined(_3DS) || defined(__3DS__)
#    define ICE_TIME_3DS 1
#  elif defined(RASPBERRYPI_PICO)               ||  defined(RASPBERRYPI_VGABOARD)           || \
        defined(PIMORONI_INTERSTATE75)          ||  defined(PIMORONI_KEYBOW2040)            || \
        defined(PIMORONI_PGA2040)               ||  defined(PIMORONI_PICOLIPO_4MB)          || \
        defined(PIMORONI_PICOLIPO_16MB)         ||  defined(PIMORONI_PICOSYSTEM)            || \
        defined(PIMORONI_PLASMA2040)            ||  defined(PIMORONI_TINY2040)              || \
        defined(PYBSTICK26_RP2040)              ||  defined(SPARKFUN_MICROMOD)              || \
        defined(SPARKFUN_PROMICRO)              ||  defined(SPARKFUN_THINGPLUS)             || \
        defined(WAVESHARE_RP2040_LCD_0_96)      ||  defined(WAVESHARE_RP2040_PLUS_4MB)      || \
        defined(WAVESHARE_RP2040_PLUS_16MB)     ||  defined(ADAFRUIT_FEATHER_RP2040)        || \
        defined(WAVESHARE_RP2040_ZERO)          ||  defined(ADAFRUIT_ITSYBITSY_RP2040)      || \
        defined(ADAFRUIT_QTPY_RP2040)           ||  defined(ADAFRUIT_TRINKEY_QT2040)        || \
        defined(ARDUINO_NANO_RP2040_CONNECT)    ||  defined(MELOPERO_SHAKE_RP2040)
#    define ICE_TIME_RPI_PICO 1
#  elif defined(__linux__) || defined(__linux)
#    define ICE_TIME_LINUX 1
#  else
#    error "ice_time.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_TIME_EXTERN) && defined(ICE_TIME_STATIC))
#  define ICE_TIME_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_TIME_EXTERN)
#  define ICE_TIME_APIDEF extern
#elif defined(ICE_TIME_STATIC)
#  define ICE_TIME_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_TIME_INLINE to enable inline functionality.
*/
#if defined(ICE_TIME_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_TIME_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_TIME_INLINEDEF inline
#  endif
#else
#  define ICE_TIME_INLINEDEF
#endif

/*
Allow to build DLL via ICE_TIME_DLLEXPORT or ICE_TIME_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_TIME_MICROSOFT)
#  if defined(ICE_TIME_DLLEXPORT)
#    define ICE_TIME_API __declspec(dllexport) ICE_TIME_INLINEDEF
#  elif defined(ICE_TIME_DLLIMPORT)
#    define ICE_TIME_API __declspec(dllimport) ICE_TIME_INLINEDEF
#  else
#    define ICE_TIME_API ICE_TIME_APIDEF ICE_TIME_INLINEDEF
#  endif
#else
#  define ICE_TIME_API ICE_TIME_APIDEF ICE_TIME_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

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
ICE_TIME_API ice_time_ulong ICE_TIME_CALLCONV ice_time_diff(const ice_time_info *t1, const ice_time_info *t2);

/* Returns difference between clock tick of current time and clock time of specific time, t is passed as pointer to ice_time_info struct for the specific time */
ICE_TIME_API ice_time_ulong ICE_TIME_CALLCONV ice_time_since(const ice_time_info *t);

/* Returns Delta Time between 2 clock ticks, Each one can be acquired from the pointer to ice_time_info struct */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_dt(const ice_time_info *t1, const ice_time_info *t2);

/* Retrieves current time info (eg. Ticks, Seconds, Days, Months, Year, Month, etc...) and stores info in ice_time_info struct by pointing to, Returns ICE_TIME_ERROR_OK on success or any other values from ice_time_error enum on failure! */
ICE_TIME_API ice_time_error ICE_TIME_CALLCONV ice_time_get_info(ice_time_info *time_info);

/* Sleeps thread/program for Milliseconds */
ICE_TIME_API void ICE_TIME_CALLCONV ice_time_sleep(ice_time_ulong ms);

/* Converts: Attoseconds -> Nanoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_as_to_ns(ice_time_ulong as);

/* Converts: Attoseconds -> Microseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_as_to_us(ice_time_ulong as);

/* Converts: Attoseconds -> Milliseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_as_to_ms(ice_time_ulong as);

/* Converts: Attoseconds -> Seconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_as_to_sec(ice_time_ulong as);

/* Converts: Nanoseconds -> Attoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_as(ice_time_ulong ns);

/* Converts: Nanoseconds -> Microseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_us(ice_time_ulong ns);

/* Converts: Nanoseconds -> Milliseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_ms(ice_time_ulong ns);

/* Converts: Nanoseconds -> Seconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_sec(ice_time_ulong ns);

/* Converts: Microseconds -> Attoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_us_to_as(ice_time_ulong us);

/* Converts: Microseconds -> Nanoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_us_to_ns(ice_time_ulong us);

/* Converts: Microseconds -> Milliseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_us_to_ms(ice_time_ulong us);

/* Converts: Microseconds -> Seconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_us_to_sec(ice_time_ulong us);

/* Converts: Milliseconds -> Attoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_as(ice_time_ulong ms);

/* Converts: Milliseconds -> Nanoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_ns(ice_time_ulong ms);

/* Converts: Milliseconds -> Microseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_us(ice_time_ulong ms);

/* Converts: Milliseconds -> Seconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_sec(ice_time_ulong ms);

/* Converts: Seconds -> Attoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_sec_to_as(ice_time_ulong sec);

/* Converts: Seconds -> Nanoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_sec_to_ns(ice_time_ulong sec);

/* Converts: Seconds -> Microseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_sec_to_us(ice_time_ulong sec);

/* Converts: Seconds -> Milliseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_sec_to_ms(ice_time_ulong sec);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_TIME_IMPL)

/* Implementation of bool */
#if !defined(__STDC_VERSION__)
typedef enum bool { false, true } bool;
#else
#  if (!(defined(_STDBOOL_H) && defined(__cplusplus) && defined(bool)) && __STDC_VERSION__ >= 199901L)
#    include <stdbool.h>
#  endif
#endif

#include <time.h>

#if defined(ICE_TIME_MICROSOFT)
#  if defined(_MSC_VER)
#    include <windows.h>
#    if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#      pragma comment(lib, "WindowsPhoneCore.lib")
#    else
#      pragma comment(lib, "kernel32.lib")
#    endif
#  else
#    include <sysinfoapi.h>
#    include <synchapi.h>
#  endif
#elif defined(ICE_TIME_BSD) || defined(ICE_TIME_APPLE) || defined(ICE_TIME_BLACKBERRY) || defined(ICE_TIME_LINUX)
#  include <sys/resource.h>
#  include <sys/sysinfo.h>
#  if !defined(ICE_TIME_LINUX)
#    include <stddef.h>
#    if defined(__FreeBSD__) || defined(__DragonFly__) || defined(ICE_TIME_APPLE)
#      include <sys/types.h>
#    elif defined(__NetBSD__) || defined(__OpenBSD__) || defined(ICE_TIME_BLACKBERRY)
#      include <sys/param.h>
#    endif
#    include <sys/sysctl.h>
#  elif defined(ICE_TIME_LINUX)
#    include <sys/time.h>
#  endif
#elif defined(ICE_TIME_RPI_PICO)
#  include "pico/types.h"
#  include "pico/time.h"
#  include "hardware/timer.h"
#  include "hardware/rtc.h"
#  include "pico/util/datetime.h"
#elif defined(ICE_TIME_3DS)
#  include <3ds.h>
#endif

/* Returns difference between 2 clock ticks, Each one can be acquired from the pointer to ice_time_info struct */
ICE_TIME_API ice_time_ulong ICE_TIME_CALLCONV ice_time_diff(const ice_time_info *t1, const ice_time_info *t2) {
    long diff;
    if ((t1 == 0) || (t2 == 0)) return 0;
    diff = t1->clock_ticks - t2->clock_ticks;
    return (ice_time_ulong)((diff < 0) ? 1 : diff);
}

/* Returns difference between clock tick of current time and clock time of specific time, t is passed as pointer to ice_time_info struct for the specific time */
ICE_TIME_API ice_time_ulong ICE_TIME_CALLCONV ice_time_since(const ice_time_info *t) {
    ice_time_info current_time;
    ice_time_error error; 
    long diff;

    if (t == 0) return 0;

    error = ice_time_get_info(&current_time);

    if (error != ICE_TIME_ERROR_OK) return 0;
    diff = t->clock_ticks - current_time.clock_ticks;
    
    return (ice_time_ulong)((diff < 0) ? 1 : diff);
}

/* Returns Delta Time between 2 clock ticks, Each one can be acquired from the pointer to ice_time_info struct */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_dt(const ice_time_info *t1, const ice_time_info *t2) {
    double dt;
    if ((t1 == 0) || (t2 == 0)) return 0;
    dt = (double)((t1->clock_ticks - t2->clock_ticks) / 1000000.0);
    return dt;
}

/* Retrieves current time info (eg. Ticks, Seconds, Days, Months, Year, Month, etc...) and stores info in ice_time_info struct by pointing to, Returns ICE_TIME_ERROR_OK on success or any other values from ice_time_error enum on failure! */
ICE_TIME_API ice_time_error ICE_TIME_CALLCONV ice_time_get_info(ice_time_info *time_info) {
    ice_time_error error = ICE_TIME_ERROR_OK;
    ice_time_ulong systicks;
    ice_time_season season;
    ice_time_month month;

#if !defined(ICE_TIME_RPI_PICO)
    time_t t;
    struct tm *pt;
    char *tm_str;

#if defined(ICE_TIME_BSD) || defined(ICE_TIME_APPLE) || defined(ICE_TIME_BLACKBERRY)
    struct timeval tv;
    size_t len;
    int res, mib[2] = { CTL_KERN, KERN_BOOTTIME };
#elif defined(ICE_TIME_LINUX)
    struct sysinfo info;
    int sysinfo_res;
#endif

#else
    datetime_t t;
    char tm_str_buf[128], *tm_str = &tm_str_buf[0];
    unsigned i, year_day = 0, year_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    absolute_time_t pico_time;
#endif
    
    if (time_info == 0) {
        error = ICE_TIME_ERROR_INVALID_POINTER;
        return error;
    }

#if defined(ICE_TIME_MICROSOFT)
#if defined(_WIN32)
    systicks = (ice_time_ulong) GetTickCount();
#elif defined(_WIN64)
    systicks = (ice_time_ulong) GetTickCount64();
#endif
#elif defined(ICE_TIME_BSD) || defined(ICE_TIME_APPLE) || defined(ICE_TIME_BLACKBERRY)
    len = sizeof(tv);
    res = sysctl(mib, 2, &tv, &len, 0, 0);
    if (res != 0) {
        error = ICE_TIME_ERROR_SYSCALL_FAILURE;
        goto failure;
    }

    systicks = (ice_time_ulong) ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
#elif defined(ICE_TIME_3DS)
    systicks = (ice_time_ulong) (svcGetSystemTick() / 1000);
#elif defined(ICE_TIME_LINUX)
    sysinfo_res = sysinfo(&info);

    if (sysinfo_res != 0) {
        error = ICE_TIME_ERROR_SYSCALL_FAILURE;
        goto failure;
    }

    systicks = (ice_time_ulong)(info.uptime * 1000);

#elif defined(ICE_TIME_RPI_PICO)
    pico_time = get_absolute_time();
    systicks = (ice_time_ulong) to_ms_since_boot(pico_time);
#endif

#if !defined(ICE_TIME_RPI_PICO)
    t = time(0);
    
    if (t == (time_t)(-1)) {
        error = ICE_TIME_ERROR_UNKNOWN_TIME;
        goto failure;
    }

    pt = localtime(&t);
    tm_str = ctime(&t);
    
    month = pt->tm_mon + 1;
    
    if (month == 12 || month == 1 || month == 2) {
        season = ICE_TIME_SEASON_WINTER;
    } else if (month == 3 || month == 4 || month == 5) {
        season = ICE_TIME_SEASON_SPRING;
    } else if (month == 6 || month == 7 || month == 8) {
        season = ICE_TIME_SEASON_SUMMER;
    } else if (month == 9 || month == 10 || month == 11) {
        season = ICE_TIME_SEASON_AUTUMN;
    } else {
        season = ICE_TIME_SEASON_UNKNOWN;
    }

    time_info->str = tm_str;
    time_info->clock_ticks = (ice_time_ulong) clock();
    time_info->uptime = systicks;
    time_info->epoch = (ice_time_ulong) t;
    time_info->seconds = pt->tm_sec;
    time_info->minutes = pt->tm_min;
    time_info->hour = pt->tm_hour;
    time_info->week_day = pt->tm_wday + 1;
    time_info->month_day = pt->tm_mday;
    time_info->year_day = pt->tm_yday;
    time_info->month = month;
    time_info->season = season;
    time_info->year = (pt->tm_year + 1900);
#else
    if (!rtc_running()) rtc_init();
    if (!rtc_get_datetime(&t)) {
        error = ICE_TIME_ERROR_UNKNOWN_TIME;
        goto failure;
    }

    datetime_to_str(tm_str, sizeof(tm_str_buf), &t);

    month = t.month;

    if (month == 12 || month == 1 || month == 2) {
        season = ICE_TIME_SEASON_WINTER;
    } else if (month == 3 || month == 4 || month == 5) {
        season = ICE_TIME_SEASON_SPRING;
    } else if (month == 6 || month == 7 || month == 8) {
        season = ICE_TIME_SEASON_SUMMER;
    } else if (month == 9 || month == 10 || month == 11) {
        season = ICE_TIME_SEASON_AUTUMN;
    } else {
        season = ICE_TIME_SEASON_UNKNOWN;
    }
    
    if ((t.year % 4) == 0) year_days[1] = 29;

    for (i = 0; i < (month - 1); i++) year_day += year_days[i];

    time_info->str = tm_str;
    time_info->clock_ticks = (ice_time_ulong) (time_us_64() * 1000);
    time_info->uptime = systicks;
    time_info->epoch = (ice_time_ulong) pico_time;
    time_info->seconds = (ice_time_ulong) t.sec;
    time_info->minutes =(ice_time_ulong) t.min;
    time_info->hour = (ice_time_ulong) t.hour;
    time_info->week_day = t.dotw + 1;
    time_info->month_day = t.day;
    time_info->year_day = year_day;
    time_info->month = month;
    time_info->season = season;
    time_info->year = t->year;
#endif

    return error;

failure:
    time_info->str = 0;
    time_info->clock_ticks = 0;
    time_info->uptime = 0;
    time_info->epoch = 0;
    time_info->seconds = 0;
    time_info->minutes = 0;
    time_info->hour = 0;
    time_info->week_day = ICE_TIME_DAY_UNKNOWN;
    time_info->month_day = 0;
    time_info->year_day = 0;
    time_info->month = ICE_TIME_MONTH_UNKNOWN;
    time_info->season = ICE_TIME_SEASON_UNKNOWN;
    time_info->year = 0;

    return error;
}

/* Sleeps thread/program for Milliseconds */
ICE_TIME_API void ICE_TIME_CALLCONV ice_time_sleep(ice_time_ulong ms) {
#if defined(ICE_TIME_MICROSOFT)
    Sleep(ms);
#elif defined(ICE_TIME_3DS)
    svcSleepThread(ms * 1000000);
#elif defined(ICE_TIME_LINUX) || defined(ICE_TIME_APPLE) || defined(ICE_TIME_BSD) || defined(ICE_TIME_BLACKBERRY)
    struct timeval tv;

    tv.tv_sec = (time_t)(ms / 1000);
    tv.tv_usec = (long)((ms % 1000) * 1000);
    
    select(0, 0, 0, 0, &tv);
#elif defined(ICE_TIME_RPI_PICO)
    sleep_ms(ms);
#endif
}

/* Converts: Attoseconds -> Nanoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_as_to_ns(ice_time_ulong as) {
    return ((double)(as / 1000000000.0));
}

/* Converts: Attoseconds -> Microseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_as_to_us(ice_time_ulong as) {
    return ((double)(as / 1000000000000.0));
}

/* Converts: Attoseconds -> Milliseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_as_to_ms(ice_time_ulong as) {
    return ((double)(as / 1000000000000000.0));
}

/* Converts: Attoseconds -> Seconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_as_to_sec(ice_time_ulong as) {
    return ((double)(as / 1000000000000000000.0));
}

/* Converts: Nanoseconds -> Attoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_as(ice_time_ulong ns) {
    return ((double)(ns * 1000000000.0));
}

/* Converts: Nanoseconds -> Microseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_us(ice_time_ulong ns) {
    return ((double)(ns / 1000.0));
}

/* Converts: Nanoseconds -> Milliseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_ms(ice_time_ulong ns) {
    return ((double)(ns / 1000000.0));
}

/* Converts: Nanoseconds -> Seconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_sec(ice_time_ulong ns) {
    return ((double)(ns / 1000000000.0));
}

/* Converts: Microseconds -> Attoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_us_to_as(ice_time_ulong us) {
    return ((double)(us * 1000000000000.0));
}

/* Converts: Microseconds -> Nanoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_us_to_ns(ice_time_ulong us) {
    return ((double)(us * 1000.0));
}

/* Converts: Microseconds -> Milliseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_us_to_ms(ice_time_ulong us) {
    return ((double)(us / 1000.0));
}

/* Converts: Microseconds -> Seconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_us_to_sec(ice_time_ulong us) {
    return ((double)(us / 1000000.0));
}

/* Converts: Milliseconds -> Attoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_as(ice_time_ulong ms) {
    return ((double)(ms * 1000000000000000.0));
}

/* Converts: Milliseconds -> Nanoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_ns(ice_time_ulong ms) {
    return ((double)(ms * 1000000.0));
}

/* Converts: Milliseconds -> Microseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_us(ice_time_ulong ms) {
    return ((double)(ms * 1000.0));
}

/* Converts: Milliseconds -> Seconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_sec(ice_time_ulong ms) {
    return ((double)(ms / 1000.0));
}

/* Converts: Seconds -> Attoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_sec_to_as(ice_time_ulong sec) {
    return ((double)(sec * 1000000000000000000.0));
}

/* Converts: Seconds -> Nanoseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_sec_to_ns(ice_time_ulong sec) {
    return ((double)(sec * 1000000000.0));
}

/* Converts: Seconds -> Microseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_sec_to_us(ice_time_ulong sec) {
    return ((double)(sec * 1000000.0));
}

/* Converts: Seconds -> Milliseconds */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_sec_to_ms(ice_time_ulong sec) {
    return ((double)(sec * 1000.0));
}

#endif  /* ICE_TIME_IMPL */
#endif  /* ICE_TIME_H */

/*
ice_time.h is dual-licensed, Choose the one you prefer!

------------------------------------------------------------------------
LICENSE A - PUBLIC DOMAIN LICENSE
------------------------------------------------------------------------
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

------------------------------------------------------------------------
LICENSE B - MIT LICENSE
------------------------------------------------------------------------
Copyright (c) 2021 - <Present> Rabia Alhaffar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
