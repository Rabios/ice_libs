/*
ice_time.h, Single-Header Cross-Platform C library for working with Time!


================================== Full Overview ==================================

ice_time.h is Single-Header Cross-Platform C library for time functionality!

To use it #define ICE_TIME_IMPL then #include "ice_time.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

#define ICE_TIME_IMPL
#include "ice_time.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Fetch time info
    ice_time_info curr_time = ice_time_status();

    // Print time fetched as string
    printf("Current Time: %s\n", curr_time.string);

    return 0;
}


=================================== Library API ===================================

// Typedef for very long integers
typedef unsigned long int ice_time_ulong;

// Enumeration for week days
typedef enum ice_time_day {
    ICE_TIME_DAY_SUNDAY = 1,
    ICE_TIME_DAY_MONDAY,
    ICE_TIME_DAY_TUESDAY,
    ICE_TIME_DAY_WEDNESDAY,
    ICE_TIME_DAY_THURSDAY,
    ICE_TIME_DAY_FRIDAY,
    ICE_TIME_DAY_SATURDAY
} ice_time_day;

// Enumeration for year months
typedef enum ice_time_month {
    ICE_TIME_MONTH_JANUARY = 1,
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

// Enumeration for seasons (helpful?)
typedef enum ice_time_season {
    ICE_TIME_SEASON_WINTER = 1,
    ICE_TIME_SEASON_SPRING,
    ICE_TIME_SEASON_SUMMER,
    ICE_TIME_SEASON_AUTUMN
} ice_time_season;

// Struct that contains patched current time info, Including ticks
typedef struct ice_time_info {
    char* string;                   // Time as string
    ice_time_ulong clock_ticks;     // Clock Ticks (Nanoseconds)
    ice_time_ulong system_ticks;    // Ticks since system started (Milliseconds)
    ice_time_ulong epoch;           // Unix timestamp
    ice_time_ulong nanoseconds;
    ice_time_ulong microseconds;
    ice_time_ulong milliseconds;
    unsigned second;
    unsigned minute;
    unsigned hour;
    ice_time_day week_day;          // (ICE_TIME_DAY_SUNDAY - ICE_TIME_DAY_SATURDAY)
    unsigned month_day;             // (1 - Month last day number)
    unsigned year_day;              // (1 - 365
    ice_time_month month;
    ice_time_season season;         // (ICE_TIME_SEASON_WINTER - ICE_TIME_SEASON_AUTUMN)
    unsigned year;
} ice_time_info;

// Returns difference between 2 ticks, The 2 ticks are acquired by via clock_ticks from 2 times
ice_time_ulong ice_time_diff(ice_time_info t1, ice_time_info t2);

// Returns Delta Time between 2 ticks, The 2 ticks are acquired by via clock_ticks from 2 times
double ice_time_dt(ice_time_info t1, ice_time_info t2);

// Returns current time info (eg. Ticks, Seconds, Days, Months, Year, Month, etc...)
ice_time_error ICE_TIME_CALLCONV ice_time_get_status(ice_time_info* time_info);

// Sleeps thread/program for milliseconds
void ice_time_sleep(ice_time_ulong ms);


================================== Linking Flags ==================================

1. Microsoft Windows        =>  -lkernel32
2. Nintendo 3DS (libctru)   =>  -lctru
3. Raspberry Pi Pico        =>  -lpico_time -lpico_util -lhardware_timer -lhardware_rtc

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragma(s)


================================= Usable #define(s) ===============================

// Define the implementation, This should be #define(d) before including ice_time.h in the code...
#define ICE_TIME_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_TIME_VECTORCALL     // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_TIME_FASTCALL       // fastcall
#define ICE_TIME_STDCALL        // stdcall
#define ICE_TIME_CDECL          // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_TIME_MICROSOFT      // Microsoft platforms
#define ICE_TIME_APPLE          // Apple platforms
#define ICE_TIME_UNIX           // Unix and Unix-like
#define ICE_TIME_RPI_PICO       // Raspberry Pi Pico
#define ICE_TIME_3DS            // Nintendo 3DS (libctru)
#define ICE_TIME_WEB            // Web (Emscripten)

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_TIME_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_TIME_DLLEXPORT      // Export the symbols to build as shared library
#define ICE_TIME_DLLIMPORT      // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_TIME_INLINE         // inlines library functions (Only works on C99 Standard and above)
#define ICE_TIME_EXTERN         // externs library functions
#define ICE_TIME_STATIC         // statics library functions

// NOTE: ICE_TIME_EXTERN and ICE_TIME_STATIC cannot be #define(d) together in the code...


============================== Implementation Resources ===========================

1. https://docs.microsoft.com/en-us/windows/win32/sysinfo/time-functions
2. https://libctru.devkitpro.org/svc_8h.html
3. https://en.cppreference.com/w/c/chrono
4. https://emscripten.org/docs/api_reference/emscripten.h.html#sleeping
5. https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__rtc.html
6. https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__timer.html
7. https://raspberrypi.github.io/pico-sdk-doxygen/group__pico__time.html
8. https://raspberrypi.github.io/pico-sdk-doxygen/group__util__datetime.html


================================= Support ice_libs ================================

ice_time.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_TIME_H
#define ICE_TIME_H 1

/* Disable security warnings for MSVC compiler, We don't want to force using C11! */
#ifdef _MSC_VER
#  ifndef _CRT_SECURE_NO_DEPRECATE
#    define _CRT_SECURE_NO_DEPRECATE 1
#  endif
#  ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS 1
#  endif
#  pragma warning(disable:4996)
#endif

/* Define C interface for Windows libraries! ;) */
#ifndef CINTERFACE
#  define CINTERFACE 1
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

#if !(defined(ICE_TIME_MICROSOFT) || defined(ICE_TIME_3DS) || defined(ICE_TIME_UNIX))
#  define ICE_TIME_AUTODETECT_PLATFORM 1
#endif

/* Platform Detection */
#if defined(ICE_TIME_AUTODETECT_PLATFORM)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_TIME_MICROSOFT 1
#  elif defined(__APPLE__) || defined(__DARWIN__) || defined(__MACH__)
#    define ICE_TIME_APPLE 1
#  elif defined(_3DS) || defined(__3DS__)
#    define ICE_TIME_3DS 1
#  elif defined(RASPBERRYPI_PICO)               ||  defined(RASPBERRYPI_VGABOARD)           ||
        defined(PIMORONI_INTERSTATE75)          ||  defined(PIMORONI_KEYBOW2040)            ||
        defined(PIMORONI_PGA2040)               ||  defined(PIMORONI_PICOLIPO_4MB)          ||
        defined(PIMORONI_PICOLIPO_16MB)         ||  defined(PIMORONI_PICOSYSTEM)            ||
        defined(PIMORONI_PLASMA2040)            ||  defined(PIMORONI_TINY2040)              ||
        defined(PYBSTICK26_RP2040)              ||  defined(SPARKFUN_MICROMOD)              ||
        defined(SPARKFUN_PROMICRO)              ||  defined(SPARKFUN_THINGPLUS)             ||
        defined(WAVESHARE_RP2040_LCD_0_96)      ||  defined(WAVESHARE_RP2040_PLUS_4MB)      ||
        defined(WAVESHARE_RP2040_PLUS_16MB)     ||  defined(ADAFRUIT_FEATHER_RP2040)        ||
        defined(WAVESHARE_RP2040_ZERO)          ||  defined(ADAFRUIT_ITSYBITSY_RP2040)      ||
        defined(ADAFRUIT_QTPY_RP2040)           ||  defined(ADAFRUIT_TRINKEY_QT2040)        ||
        defined(ARDUINO_NANO_RP2040_CONNECT)    ||  defined(MELOPERO_SHAKE_RP2040)
#    define ICE_TIME_RPI_PICO 1
#  elif defined(__unix__) || defined(__unix)
#    define ICE_TIME_UNIX 1
#  elif defined(__EMSCRIPTEN__)
#    define ICE_TIME_WEB 1
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

/* =============================== Macros =============================== */

#ifndef CLOCKS_PER_SEC
#  define CLOCKS_PER_SEC 1000000
#endif

/* ============================== Data Types ============================== */

/* Typedef for very long integers */
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

/* Enumeration for seasons (helpful?) */
typedef enum ice_time_season {
    ICE_TIME_SEASON_UNKNOWN = 0,
    ICE_TIME_SEASON_WINTER,
    ICE_TIME_SEASON_SPRING,
    ICE_TIME_SEASON_SUMMER,
    ICE_TIME_SEASON_AUTUMN
} ice_time_season;

/* Struct that contains patched current time info, Including ticks */
typedef struct ice_time_info {
    const char* str;                /* Time as string */
    ice_time_ulong clock_ticks;     /* Clock Ticks (Nanoseconds) */
    ice_time_ulong system_ticks;    /* Ticks since system started (Milliseconds) */
    ice_time_ulong epoch;           /* Unix timestamp */
    ice_time_ulong nanoseconds;
    ice_time_ulong microseconds;
    ice_time_ulong milliseconds;
    unsigned second;
    unsigned minute;
    unsigned hour;
    ice_time_day week_day;          /* (ICE_TIME_DAY_SUNDAY - ICE_TIME_DAY_SATURDAY) */
    unsigned month_day;             /* (1 - Month last day number) */
    unsigned year_day;              /* (1 - 365) */
    ice_time_month month;
    ice_time_season season;         /* (ICE_TIME_SEASON_WINTER - ICE_TIME_SEASON_AUTUMN) */
    unsigned year;
} ice_time_info;

/* Enumeration for errors that may occur */
typedef enum ice_time_error {
    ICE_TIME_ERROR_OK = 0,          /* OK - no errors */
    ICE_TIME_ERROR_UNKNOWN_TIME,    /* Occurs when time() function fails */
    ICE_TIME_ERROR_UNKNOWN_CLOCK    /* Occurs when clock_gettime() function fails (Linux/Unix only) */
} ice_time_error;

/* ============================== Functions ============================== */

/* Returns difference between 2 ticks, The 2 ticks are acquired by via clock_ticks from 2 times */
ICE_TIME_API ice_time_ulong ICE_TIME_CALLCONV ice_time_diff(ice_time_info t1, ice_time_info t2);

/* Returns Delta Time between 2 ticks, The 2 ticks are acquired by via clock_ticks from 2 times */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_dt(ice_time_info t1, ice_time_info t2);

/* Returns current time info (eg. Ticks, Seconds, Days, Months, Year, Month, etc...) */
ICE_TIME_API ice_time_error ICE_TIME_CALLCONV ice_time_get_status(ice_time_info* time_info);

/* Sleeps thread/program for milliseconds */
ICE_TIME_API void ICE_TIME_CALLCONV ice_time_sleep(ice_time_ulong ms);

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
#elif defined(ICE_TIME_APPLE)
#  include <mach/mach.h>
#  if _POSIX_C_SOURCE < 199309L
#    include <unistd.h>
#  endif
#elif defined(ICE_TIME_RPI_PICO)
#  include "pico/types.h"
#  include "pico/time.h"
#  include "hardware/timer.h"
#  include "hardware/rtc.h"
#  include "pico/util/datetime.h"
#elif defined(ICE_TIME_UNIX)
#  if _POSIX_C_SOURCE < 199309L
#    include <unistd.h>
#  endif
#elif defined(ICE_TIME_3DS)
#  include <3ds.h>
#elif defined(ICE_TIME_WEB)
#  include <emscripten/emscripten.h>
#endif

/* Returns difference between 2 ticks, The 2 ticks are acquired by via clock_ticks from 2 times */
ICE_TIME_API ice_time_ulong ICE_TIME_CALLCONV ice_time_diff(ice_time_info t1, ice_time_info t2) {
    return (t1.clock_ticks - t2.clock_ticks);
}

/* Returns Delta Time between 2 ticks, The 2 ticks are acquired by via clock_ticks from 2 times */
ICE_TIME_API double ICE_TIME_CALLCONV ice_time_dt(ice_time_info t1, ice_time_info t2) {
    return (double)((t1.clock_ticks - t2.clock_ticks) / CLOCKS_PER_SEC);
}

/* Returns current time info (eg. Ticks, Seconds, Days, Months, Year, Month, etc...) */
ICE_TIME_API ice_time_error ICE_TIME_CALLCONV ice_time_get_status(ice_time_info* time_info) {
    ice_time_error err = ICE_TIME_ERROR_OK;
    ice_time_ulong systicks = 0;
    ice_time_season season;
    ice_time_month month;

#if !defined(ICE_TIME_RPI_PICO)
    time_t t;
    struct tm* pt;
    char* tm_str;
#else
    datetime_t t;
    char tm_str_buf[128];
    char* tm_str = &tm_str[0];

    /* todo: change 28 to 29 if modulo of number is 0 */
    unsigned year_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    unsigned year_day = 0;
    unsigned i;
#endif
    
#if defined(ICE_TIME_MICROSOFT)

#if defined(_WIN64)
    systicks = (ice_time_ulong) GetTickCount64();
#else
    systicks = (ice_time_ulong) GetTickCount();
#endif

#elif defined(ICE_TIME_APPLE)
    systicks = (ice_time_ulong) (mach_continuous_approximate_time() / 1000);
#elif defined(ICE_TIME_3DS)
    systicks = (ice_time_ulong) (svcGetSystemTick() / 1000);
#elif defined(ICE_TIME_UNIX)
    struct timespec ts;
    int clockres = clock_gettime(CLOCK_MONOTONIC, &ts);
    
    if (clockres != 0) {
        err = ICE_TIME_ERROR_UNKNOWN_CLOCK;
        goto failure;
    }

    systicks = (ice_time_ulong) (ts.tv_nsec / 1000);
#elif defined(ICE_TIME_RPI_PICO)
    absolute_time_t pico_time = get_absolute_time();

    systicks = (ice_time_ulong) to_ms_since_boot(pico_time);
#elif defined(ICE_TIME_WEB)
    systicks = (ice_time_ulong) EM_ASM_INT({
        return (new Date().getTime());
    });
#endif

#if !defined(ICE_TIME_RPI_PICO)
    t = time(0);
    
    if (t == (time_t)(-1)) {
        err = ICE_TIME_ERROR_UNKNOWN_TIME;
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
    time_info->system_ticks = systicks;
    time_info->epoch = (ice_time_ulong) pico_time;
    time_info->nanoseconds = (ice_time_ulong) (systicks * 1000);
    time_info->microseconds = (ice_time_ulong) systicks;
    time_info->milliseconds = (ice_time_ulong) (systicks / 1000);
    time_info->second = pt->tm_sec;
    time_info->minute = pt->tm_min;
    time_info->hour = pt->tm_hour;
    time_info->week_day = pt->tm_wday + 1;
    time_info->month_day = pt->tm_mday;
    time_info->year_day = pt->tm_yday;
    time_info->month = month;
    time_info->season = season;
    time_info->year = (pt->tm_year + 1900);
#else
    if (!rtc_running()) rtc_init();
    if (!rtc_get_datetime(&t)) goto failure;

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
    time_info->system_ticks = systicks;
    time_info->epoch = (ice_time_ulong) pico_time;
    time_info->nanoseconds = (ice_time_ulong) (systicks * 1000);
    time_info->microseconds = (ice_time_ulong) systicks;
    time_info->milliseconds = (ice_time_ulong) (systicks / 1000);
    time_info->second = (ice_time_ulong) t.sec;
    time_info->minute =(ice_time_ulong) t.min;
    time_info->hour = (ice_time_ulong) t.hour;
    time_info->week_day = t.dotw + 1;
    time_info->month_day = t.day;
    time_info->year_day = year_day;
    time_info->month = month;
    time_info->season = season;
    time_info->year = (pt->tm_year + 1900);
#endif

    return err;

goto failure:
    time_info->str = 0;
    time_info->clock_ticks = 0;
    time_info->system_ticks = 0;
    time_info->epoch = 0;
    time_info->nanoseconds = 0;
    time_info->microseconds = 0;
    time_info->milliseconds = 0;
    time_info->second = 0;
    time_info->minute = 0;
    time_info->hour = 0;
    time_info->week_day = ICE_TIME_DAY_UNKNOWN;
    time_info->month_day = 0;
    time_info->year_day = 0;
    time_info->month = ICE_TIME_MONTH_UNKNOWN;
    time_info->season = ICE_TIME_SEASON_UNKNOWN;
    time_info->year = 0;

    return err;
}

/* Sleeps thread/program for milliseconds */
ICE_TIME_API void ICE_TIME_CALLCONV ice_time_sleep(ice_time_ulong ms) {
#if defined(ICE_TIME_MICROSOFT)
    Sleep(ms);
#elif defined(ICE_TIME_3DS)
    svcSleepThread(ms * 1000000);
#elif defined(ICE_TIME_UNIX) || defined(ICE_TIME_APPLE)

#if _POSIX_C_SOURCE < 199309L
    usleep(ms * 1000);
#else
    struct timespec t;

    t.tv_sec = ms / 1000;
    t.tv_nsec = (ms % 1000) * 1000000;

    nanosleep(&t, &t);
#endif

#elif defined(ICE_TIME_RPI_PICO)
    sleep_ms(ms);
#elif defined(ICE_TIME_WEB)
    emscripten_sleep(ms);
#endif
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
