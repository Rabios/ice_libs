// Written by Rabia Alhaffar in 9/April/2021
// ice_time.h
// Single-Header Cross-Platform C library for working with Time!
// Updated: 25/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_time.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_time is cross-platform single-header C library for working with Time!

It can be used to get current second, hour, month, year, day, week, And also time as string!

[2] USAGE:
Define ICE_TIME_IMPL then include ice_time.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_time
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_time by possibly one of following things:
//
// 1. Test ice_time on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_time LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_time is dual-licensed, Choose the one you prefer!

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
Copyright (c) 2021 - 2022 Rabia Alhaffar

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

#ifndef ICE_TIME_H
#define ICE_TIME_H

// Disable security warnings for MSVC compiler, We don't want to force using C11!
#ifdef _MSC_VER
#  define _CRT_SECURE_NO_DEPRECATE
#  define _CRT_SECURE_NO_WARNINGS
#  pragma warning(disable:4996)
#endif

// Define C interface for Windows libraries! ;)
#ifndef CINTERFACE
#  define CINTERFACE
#endif

// Allow to use calling convention if desired...
#if defined(__GNUC__) || defined(__GNUG__)
#  if defined(ICE_TIME_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_TIME_CALLCONV_FASTCALL)
#    define ICE_TIME_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_TIME_CALLCONV_STDCALL)
#    define ICE_TIME_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_TIME_CALLCONV_CDECL)
#    define ICE_TIME_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_TIME_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_TIME_CALLCONV_VECTORCALL)
#    define ICE_TIME_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_TIME_CALLCONV_FASTCALL)
#    define ICE_TIME_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_TIME_CALLCONV_STDCALL)
#    define ICE_TIME_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_TIME_CALLCONV_CDECL)
#    define ICE_TIME_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_TIME_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_TIME_CALLCONV_VECTORCALL)
#    define ICE_TIME_CALLCONV __vectorcall
#  elif defined(ICE_TIME_CALLCONV_FASTCALL)
#    define ICE_TIME_CALLCONV __fastcall
#  elif defined(ICE_TIME_CALLCONV_STDCALL)
#    define ICE_TIME_CALLCONV __stdcall
#  elif defined(ICE_TIME_CALLCONV_CDECL)
#    define ICE_TIME_CALLCONV __cdecl
#  else
#    define ICE_TIME_CALLCONV
#  endif
#else
#  define ICE_TIME_CALLCONV
#endif

// Detect Windows to allow building DLLs
#if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#  define ICE_TIME_MICROSOFT
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_TIME_EXTERN) && defined(ICE_TIME_STATIC))
#  define ICE_TIME_EXTERN
#endif

#if defined(ICE_TIME_EXTERN)
#  define ICE_TIME_APIDEF extern
#elif defined(ICE_TIME_STATIC)
#  define ICE_TIME_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_TIME_INLINE to enable inline functionality.
#if defined(ICE_TIME_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_TIME_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_TIME_INLINEDEF inline
#  endif
#else
#  define ICE_TIME_INLINEDEF
#endif

// Allow to build DLL via ICE_TIME_DLLEXPORT or ICE_TIME_DLLIMPORT if desired!
// Else, Just define API as extern C code!
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

///////////////////////////////////////////////////////////////////////////////////////////
// ice_time DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_TIME_SUNDAY = 1,
    ICE_TIME_MONDAY,
    ICE_TIME_TUESDAY,
    ICE_TIME_WEDNESDAY,
    ICE_TIME_THURSDAY,
    ICE_TIME_FRIDAY,
    ICE_TIME_SATURDAY,
} ice_time_day;

typedef enum {
    ICE_TIME_JANUARY = 1,
    ICE_TIME_FEBRUARY,
    ICE_TIME_MARCH,
    ICE_TIME_APRIL,
    ICE_TIME_MAY,
    ICE_TIME_JUNE,
    ICE_TIME_JULY,
    ICE_TIME_AUGUST,
    ICE_TIME_SEPTEMBER,
    ICE_TIME_OCTOBER,
    ICE_TIME_NOVEMBER,
    ICE_TIME_DECEMBER,
} ice_time_month;

typedef enum {
    ICE_TIME_WINTER = 1,
    ICE_TIME_SPRING,
    ICE_TIME_SUMMER,
    ICE_TIME_AUTUMN,
} ice_time_season;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_time FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
// Time Control
ICE_TIME_API  double           ICE_TIME_CALLCONV  ice_time_tick(void);
ICE_TIME_API  double           ICE_TIME_CALLCONV  ice_time_diff(double t1, double t2);
ICE_TIME_API  double           ICE_TIME_CALLCONV  ice_time_fps(double t1, double t2);
ICE_TIME_API  double           ICE_TIME_CALLCONV  ice_time_dt(double t1, double t2);
ICE_TIME_API  char*            ICE_TIME_CALLCONV  ice_time_string(void);
ICE_TIME_API  int              ICE_TIME_CALLCONV  ice_time_current_second(void);
ICE_TIME_API  int              ICE_TIME_CALLCONV  ice_time_current_minute(void);
ICE_TIME_API  int              ICE_TIME_CALLCONV  ice_time_current_hour(void);
ICE_TIME_API  int              ICE_TIME_CALLCONV  ice_time_current_month_day(void);
ICE_TIME_API  ice_time_month   ICE_TIME_CALLCONV  ice_time_current_month(void);
ICE_TIME_API  int              ICE_TIME_CALLCONV  ice_time_current_year(void);
ICE_TIME_API  int              ICE_TIME_CALLCONV  ice_time_current_year_day(void);
ICE_TIME_API  ice_time_day     ICE_TIME_CALLCONV  ice_time_current_week_day(void);
ICE_TIME_API  ice_time_season  ICE_TIME_CALLCONV  ice_time_get_season(void);
ICE_TIME_API  void             ICE_TIME_CALLCONV  ice_time_sleep(unsigned int ms);

// Time Conversion
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_ms(double ns);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_sec(double ns);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_min(double ns);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_hour(double ns);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_day(double ns);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_week(double ns);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_month(double ns);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_year(double ns);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_decade(double ns);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ns_to_century(double ns);

ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_ns(double ms);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_sec(double ms);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_min(double ms);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_hour(double ms);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_day(double ms);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_week(double ms);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_month(double ms);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_year(double ms);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_decade(double ms);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_ms_to_century(double ms);

ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_ns(double min);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_ms(double min);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_sec(double min);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_hour(double min);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_day(double min);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_week(double min);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_month(double min);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_year(double min);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_decade(double min);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_min_to_century(double min);

ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_ns(double hr);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_ms(double hr);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_sec(double hr);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_min(double hr);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_day(double hr);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_week(double hr);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_month(double hr);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_year(double hr);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_decade(double hr);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_hour_to_century(double hr);

ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_ns(double day);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_ms(double day);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_sec(double day);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_min(double day);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_hour(double day);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_week(double day);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_month(double day);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_year(double day);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_decade(double day);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_day_to_century(double day);

ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_ns(double week);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_ms(double week);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_sec(double week);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_min(double week);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_hour(double week);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_day(double week);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_month(double week);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_year(double week);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_decade(double week);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_week_to_century(double week);

ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_ns(double month);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_ms(double month);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_sec(double month);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_min(double month);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_hour(double month);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_day(double month);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_week(double month);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_year(double month);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_decade(double month);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_month_to_century(double month);

ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_ns(double year);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_ms(double year);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_sec(double year);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_min(double year);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_hour(double year);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_day(double year);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_week(double year);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_month(double year);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_decade(double year);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_year_to_century(double year);

ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_ns(double decade);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_ms(double decade);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_sec(double decade);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_min(double decade);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_hour(double decade);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_day(double decade);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_week(double decade);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_month(double decade);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_year(double decade);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_decade_to_century(double decade);

ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_ns(double century);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_ms(double century);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_sec(double century);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_min(double century);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_hour(double century);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_day(double century);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_week(double century);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_month(double century);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_year(double century);
ICE_TIME_API  double  ICE_TIME_CALLCONV  ice_time_century_to_decade(double century);

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_time IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_TIME_IMPL)

#include <time.h>

#if defined(ICE_TIME_MICROSOFT)
#  include <windows.h>
#endif

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_tick(void) {
    return clock();
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_diff(double t1, double t2) {
    return (t1 - t2);
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_fps(double t1, double t2) {
    return 1000 / (ice_time_diff(t1, t2) / 1000);
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_dt(double t1, double t2) {
    return ice_time_diff(t1, t2) / 1000;
}

ICE_TIME_API char* ICE_TIME_CALLCONV ice_time_string(void) {
    time_t t = time(NULL);
    
    if (t == ((time_t) -1)) {
        return NULL;
    }
    
    return ctime(&t);
}

ICE_TIME_API int ICE_TIME_CALLCONV ice_time_current_second(void) {
    time_t t = time(NULL);
    
    if (t == ((time_t) -1)) {
        return NULL;
    }
    
    struct tm* pt;
    pt = localtime(&t);
    return pt->tm_sec;
}

ICE_TIME_API int ICE_TIME_CALLCONV ice_time_current_minute(void) {
    time_t t = time(NULL);
    
    if (t == ((time_t) -1)) {
        return NULL;
    }
    
    struct tm* pt;
    pt = localtime(&t);
    return pt->tm_min;
}

ICE_TIME_API int ICE_TIME_CALLCONV ice_time_current_hour(void) {
    time_t t = time(NULL);
    
    if (t == ((time_t) -1)) {
        return NULL;
    }
    
    struct tm* pt;
    pt = localtime(&t);
    return pt->tm_hour;
}

ICE_TIME_API int ICE_TIME_CALLCONV ice_time_current_month_day(void) {
    time_t t = time(NULL);
    
    if (t == ((time_t) -1)) {
        return NULL;
    }
    
    struct tm* pt;
    pt = localtime(&t);
    return pt->tm_mday;
}

ICE_TIME_API ice_time_month ICE_TIME_CALLCONV ice_time_current_month(void) {
    time_t t = time(NULL);
    
    if (t == ((time_t) -1)) {
        return ICE_TIME_JANUARY;
    }
    
    struct tm* pt;
    pt = localtime(&t);
    return pt->tm_mon + 1;
}

ICE_TIME_API int ICE_TIME_CALLCONV ice_time_current_year(void) {
    time_t t = time(NULL);
    
    if (t == ((time_t) -1)) {
        return NULL;
    }
    
    struct tm* pt;
    pt = localtime(&t);
    return 1900 + pt->tm_year;
}

ICE_TIME_API int ICE_TIME_CALLCONV ice_time_current_year_day(void) {
    time_t t = time(NULL);
    
    if (t == ((time_t) -1)) {
        return NULL;
    }
    
    struct tm* pt;
    pt = localtime(&t);
    return pt->tm_yday + 1;
}

ICE_TIME_API ice_time_day ICE_TIME_CALLCONV ice_time_current_week_day(void) {
    time_t t = time(NULL);
    
    if (t == ((time_t) -1)) {
        return ICE_TIME_SUNDAY;
    }
    
    struct tm* pt;
    pt = localtime(&t);
    return pt->tm_wday + 1;
}

ICE_TIME_API ice_time_season ICE_TIME_CALLCONV ice_time_get_season(void) {
    ice_time_month m = ice_time_current_month();
    
    if (m == ICE_TIME_DECEMBER || m == ICE_TIME_JANUARY || m == ICE_TIME_FEBRUARY) {
        return ICE_TIME_WINTER;
    } else if (m == ICE_TIME_MARCH || m == ICE_TIME_APRIL || m == ICE_TIME_MAY) {
        return ICE_TIME_SPRING;
    } else if (m == ICE_TIME_JUNE || m == ICE_TIME_JULY || m == ICE_TIME_AUGUST) {
        return ICE_TIME_SUMMER;
    } else if (m == ICE_TIME_SEPTEMBER || m == ICE_TIME_OCTOBER || m == ICE_TIME_NOVEMBER) {
        return ICE_TIME_AUTUMN;
    }
}

ICE_TIME_API void ICE_TIME_CALLCONV ice_time_sleep(unsigned int ms) {
#if defined(ICE_TIME_MICROSOFT)
Sleep(ms);

#else
struct timespec t;

t.tv_sec = ms / 1000;
t.tv_nsec = (ms % 1000) * 1000000;

nanosleep(&t, &t);

#endif
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_ms(double ns) {
    return ns / 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_sec(double ns) {
    return ns / 1000000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_min(double ns) {
    return ns / 1000000 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_hour(double ns) {
    return ns / 1000000 * (60 * 60);
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_day(double ns) {
    return ns / 1000000 * 24 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_week(double ns) {
    return ns / 1000000 * 24 * 7 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_month(double ns) {
    return ns / 1000000 * 24 * 30 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_year(double ns) {
    return ns / 1000000 * 24 * 365 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_decade(double ns) {
    return ns / 1000000 * 24 * 365 * 60 * 60 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ns_to_century(double ns) {
    return ns / 1000000 * 24 * 365 * 60 * 60 * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_ns(double ms) {
    return ms * 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_sec(double ms) {
    return ms / 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_min(double ms) {
    return ms / 1000 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_hour(double ms) {
    return ms / 1000 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_day(double ms) {
    return ms / 1000 * 60 * 60 * 24;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_week(double ms) {
    return ms / 1000 * 60 * 60 * 24 * 7;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_month(double ms) {
    return ms / 1000 * 60 * 60 * 24 * 30;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_year(double ms) {
    return ms / 1000 * 60 * 60 * 24 * 365;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_decade(double ms) {
    return ms / 1000 * 60 * 60 * 24 * 365 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_ms_to_century(double ms) {
    return ms / 1000 * 60 * 60 * 24 * 365 * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_ns(double min) {
    return min * 60 * 1000000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_ms(double min) {
    return min * 60 * 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_sec(double min) {
    return min * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_hour(double min) {
    return min / 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_day(double min) {
    return min / 60 * 24;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_week(double min) {
    return min / 60 * 24 * 7;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_month(double min) {
    return min / 60 * 24 * 30;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_year(double min) {
    return min / 60 * 24 * 365;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_decade(double min) {
    return min / 60 * 24 * 365 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_min_to_century(double min) {
    return min / 60 * 24 * 365 * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_ns(double hr) {
    return hr * 60 * 60 * 1000000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_ms(double hr) {
    return hr * 60 * 60 * 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_sec(double hr) {
    return hr * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_min(double hr) {
    return hr * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_day(double hr) {
    return hr / 24;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_week(double hr) {
    return hr / 24 * 7;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_month(double hr) {
    return hr / 24 * 30;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_year(double hr) {
    return hr / 24 * 356;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_decade(double hr) {
    return hr / 24 * 356 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_hour_to_century(double hr) {
    return hr / 24 * 356 * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_ns(double day) {
    return day * 24 * 60 * 60 * 1000000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_ms(double day) {
    return day * 24 * 60 * 60 * 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_sec(double day) {
    return day * 24 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_min(double day) {
    return day * 24 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_hour(double day) {
    return day * 24;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_week(double day) {
    return day / 7;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_month(double day) {
    return day / 31;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_year(double day) {
    return day / 356;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_decade(double day) {
    return day / 356 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_day_to_century(double day) {
    return day / 356 * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_ns(double week) {
    return week * 24 * 7 * 60 * 60 * 1000000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_ms(double week) {
    return week * 24 * 7 * 60 * 60 * 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_sec(double week) {
    return week * 24 * 7 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_min(double week) {
    return week * 24 * 7 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_hour(double week) {
    return week * 24 * 7;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_day(double week) {
    return week * 24;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_month(double week) {
    return (int) week / 4.4;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_year(double week) {
    return (int) week / 4.4 * 12;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_decade(double week) {
    return (int) week / 4.4 * 12 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_week_to_century(double week) {
    return (int) week / 4.4 * 12 * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_ns(double month) {
    return month * 30 * 24 * 60 * 60 * 1000000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_ms(double month) {
    return month * 30 * 24 * 60 * 60 * 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_sec(double month) {
    return month * 30 * 24 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_min(double month) {
    return month * 30 * 24 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_hour(double month) {
    return month * 30 * 24;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_day(double month) {
    return month * 30;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_week(double month) {
    return month * 5;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_year(double month) {
    return month / 12;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_decade(double month) {
    return month / 12 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_month_to_century(double month) {
    return month / 12 * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_ns(double year) {
    return year * 30 * 12 * 24 * 60 * 60 * 1000000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_ms(double year) {
    return year * 30 * 12 * 24 * 60 * 60 * 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_sec(double year) {
    return year * 30 * 12 * 24 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_min(double year) {
    return year * 30 * 12 * 24 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_hour(double year) {
    return year * 30 * 12 * 24;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_day(double year) {
    return year * 365;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_week(double year) {
    return year / 7 * 4.4 * 12;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_month(double year) {
    return year * 30;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_decade(double year) {
    return year / 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_year_to_century(double year) {
    return year / 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_ns(double decade) {
    return decade * 30 * 12 * 10 * 24 * 60 * 60 * 1000000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_ms(double decade) {
    return decade * 30 * 12 * 10 * 24 * 60 * 60 * 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_sec(double decade) {
    return decade * 30 * 12 * 10 * 24 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_min(double decade) {
    return decade * 30 * 12 * 10 * 24 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_hour(double decade) {
    return decade * 30 * 12 * 10 * 24;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_day(double decade) {
    return decade * 30 * 12 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_week(double decade) {
    return decade / 7 * 4.4 * 12 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_month(double decade) {
    return decade * 12 * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_year(double decade) {
    return decade * 10;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_decade_to_century(double decade) {
    return decade / 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_ns(double century) {
    return century * 30 * 12 * 100 * 24 * 60 * 60 * 1000000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_ms(double century) {
    return century * 30 * 12 * 10 * 24 * 60 * 60 * 1000;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_sec(double century) {
    return century * 30 * 12 * 10 * 24 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_min(double century) {
    return century * 30 * 12 * 10 * 24 * 60 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_hour(double century) {
    return century * 30 * 12 * 10 * 24 * 60;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_day(double century) {
    return century * 30 * 12 * 10 * 24;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_week(double century) {
    return century / 7 * 4.4 * 12 * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_month(double century) {
    return century * 12 * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_year(double century) {
    return century * 100;
}

ICE_TIME_API double ICE_TIME_CALLCONV ice_time_century_to_decade(double century) {
    return century * 10;
}

#endif  // ICE_TIME_IMPL
#endif  // ICE_TIME_H
