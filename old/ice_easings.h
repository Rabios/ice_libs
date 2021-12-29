// Written by Rabia Alhaffar in 2/April/2021
// ice_easings.h
// Single-Header Cross-Platform C library for easings!
// Updated: 25/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_easings.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_easings is cross-platform single-header C library for working with easings, Based on
Robert Penner's easings!

[2] USAGE:
Define ICE_EASINGS_IMPL then include ice_easings.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_easings
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_easings by possibly one of following things:
//
// 1. Test ice_easings on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_easings LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_easings is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_EASINGS_H
#define ICE_EASINGS_H

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

// Allow to use calling conventions if desired...
#if defined(__GNUC__) || defined(__GNUG__)
#  if defined(ICE_EASINGS_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_EASINGS_CALLCONV_FASTCALL)
#    define ICE_EASINGS_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_EASINGS_CALLCONV_STDCALL)
#    define ICE_EASINGS_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_EASINGS_CALLCONV_CDECL)
#    define ICE_EASINGS_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_EASINGS_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_EASINGS_CALLCONV_VECTORCALL)
#    define ICE_EASINGS_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_EASINGS_CALLCONV_FASTCALL)
#    define ICE_EASINGS_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_EASINGS_CALLCONV_STDCALL)
#    define ICE_EASINGS_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_EASINGS_CALLCONV_CDECL)
#    define ICE_EASINGS_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_EASINGS_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_EASINGS_CALLCONV_VECTORCALL)
#    define ICE_EASINGS_CALLCONV __vectorcall
#  elif defined(ICE_EASINGS_CALLCONV_FASTCALL)
#    define ICE_EASINGS_CALLCONV __fastcall
#  elif defined(ICE_EASINGS_CALLCONV_STDCALL)
#    define ICE_EASINGS_CALLCONV __stdcall
#  elif defined(ICE_EASINGS_CALLCONV_CDECL)
#    define ICE_EASINGS_CALLCONV __cdecl
#  else
#    define ICE_EASINGS_CALLCONV
#  endif
#else
#  define ICE_EASINGS_CALLCONV
#endif

// Detect Windows to allow building DLLs
#if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#  define ICE_EASINGS_MICROSOFT
#endif

// We can let our functions static instead of extern if desired.
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_EASINGS_EXTERN) && defined(ICE_EASINGS_STATIC))
#  define ICE_EASINGS_EXTERN
#endif

#if defined(ICE_EASINGS_EXTERN)
#  define ICE_EASINGS_APIDEF extern
#elif defined(ICE_EASINGS_STATIC)
#  define ICE_EASINGS_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_EASINGS_INLINE to enable inline functionality.
#if defined(ICE_EASINGS_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_EASINGS_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_EASINGS_INLINEDEF inline
#  endif
#else
#  define ICE_EASINGS_INLINEDEF
#endif

// Allow to build DLL via ICE_EASINGS_DLLEXPORT or ICE_EASINGS_DLLIMPORT if desired!
// Else, Just define API as extern C code!
#if defined(ICE_EASINGS_MICROSOFT)
#  if defined(ICE_EASINGS_DLLEXPORT)
#    define ICE_EASINGS_API __declspec(dllexport) ICE_EASINGS_INLINEDEF
#  elif defined(ICE_EASINGS_DLLIMPORT)
#    define ICE_EASINGS_API __declspec(dllimport) ICE_EASINGS_INLINEDEF
#  else
#    define ICE_EASINGS_API ICE_EASINGS_APIDEF ICE_EASINGS_INLINEDEF
#  endif
#else
#  define ICE_EASINGS_API ICE_EASINGS_APIDEF ICE_EASINGS_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_easings DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
#define ICE_EASINGS_PI 3.14159265358979323846

///////////////////////////////////////////////////////////////////////////////////////////
// ice_easings FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_linear_none(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_linear_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_linear_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_linear_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_sine_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_sine_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_sine_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_cubic_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_cubic_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_cubic_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_quint_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_quint_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_quint_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_circ_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_circ_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_circ_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_elastic_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_elastic_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_elastic_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_quad_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_quad_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_quad_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_quart_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_quart_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_quart_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_expo_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_expo_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_expo_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_back_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_back_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_back_in_out(double t, double b, double c, double d);

ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_bounce_in(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_bounce_out(double t, double b, double c, double d);
ICE_EASINGS_API  double  ICE_EASINGS_CALLCONV  ice_easings_bounce_in_out(double t, double b, double c, double d);

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_easings IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_EASINGS_IMPL)
#include <math.h>

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_linear_none(double t, double b, double c, double d) {
    return c * t / d + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_linear_in(double t, double b, double c, double d) {
    return c * t / d + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_linear_out(double t, double b, double c, double d) {
    return c * t / d + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_linear_in_out(double t, double b, double c, double d) {
    return c * t / d + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_sine_in(double t, double b, double c, double d) {
    return -c * cos(t / d * (ICE_EASINGS_PI / 2)) + c + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_sine_out(double t, double b, double c, double d) {
    return c * sin(t / d * (ICE_EASINGS_PI / 2)) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_sine_in_out(double t, double b, double c, double d) {
    return -c / 2 * (cos(ICE_EASINGS_PI * t / d) - 1) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_cubic_in(double t, double b, double c, double d) {
    return c * (t /= d) * t * t + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_cubic_out(double t, double b, double c, double d) {
    return c *((t = t / d - 1) * t * t + 1) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_cubic_in_out(double t, double b, double c, double d) {
    if ((t /= d / 2) < 1) return c / 2 * t * t * t + b;
    return c / 2 * ((t -= 2) * t * t + 2) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_quint_in(double t, double b, double c, double d) {
    return c * (t /= d) * t * t * t * t + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_quint_out(double t, double b, double c, double d) {
    return c * ((t = t / d - 1) * t * t * t * t + 1) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_quint_in_out(double t, double b, double c, double d) {
    if ((t /= d / 2) < 1) return c / 2 * t * t * t * t * t + b;
    return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_circ_in(double t, double b, double c, double d) {
    return -c * (sqrt(1 - (t /= d) * t) - 1) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_circ_out(double t, double b, double c, double d) {
    return c * sqrt(1 - (t = t / d - 1) * t) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_circ_in_out(double t, double b, double c, double d) {
    if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t * t) - 1) + b;
    return c / 2 * (sqrt(1 - (t -= 2) * t) + 1) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_elastic_in(double t, double b, double c, double d) {    
    if (t == 0) return b;
    if ((t /= d) == 1) return b + c;
    
    double p = d * 0.3;
    double a = c; 
    double s = p / 4;
    double postFix = a * pow(2, 10 * (t -= 1));
    
    return -(postFix * sin((t * d - s) * (2 * ICE_EASINGS_PI) / p)) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_elastic_out(double t, double b, double c, double d) {
    if (t == 0) return b;
    if ((t /= d) == 1) return b + c;
    
    double p = d * 0.3;
    double a = c; 
    double s = p / 4;
    
    if (t < 1) {
        double postFix = a * pow(2, 10 * (t -= 1));
        return -0.5 * (postFix * sin((t * d - s) * (2 * ICE_EASINGS_PI) / p)) + b;
	}
    
	double postFix = a * pow(2, -10 * (t -= 1));
	return postFix * sin((t * d - s) * (2 * ICE_EASINGS_PI) / p) * 0.5 + c + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_elastic_in_out(double t, double b, double c, double d) {
    if (t == 0) return b;
    if ((t /= d) == 1) return b + c;
    
    double p = d * (0.3 * 1.5);
    double a = c; 
    double s = p / 4;
    
    if (t < 1) {
        double postFix = a * pow(2, 10 * (t -= 1));
        return -0.5 * (postFix * sin((t * d - s) * (2 * ICE_EASINGS_PI) / p)) + b;
	}
    
	double postFix = a * pow(2, -10 * (t -= 1));
	return postFix * sin((t * d - s) * (2 * ICE_EASINGS_PI) / p) * 0.5 + c + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_quad_in(double t, double b, double c, double d) {
    return c * (t /= d) * t + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_quad_out(double t, double b, double c, double d) {
    return -c * (t /= d) * (t - 2) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_quad_in_out(double t, double b, double c, double d) {
    if ((t /= d / 2) < 1) return c / 2 * t * t + b;
    return -c / 2 * ((--t) * (t - 2) - 1) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_quart_in(double t, double b, double c, double d) {
    return c * (t /= d) * t * t * t + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_quart_out(double t, double b, double c, double d) {
    return -c * ((t = t / d - 1) * t * t * t - 1) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_quart_in_out(double t, double b, double c, double d) {
    if ((t /= d / 2) < 1) return c / 2 * t * t * t * t + b;
    return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_expo_in(double t, double b, double c, double d) {
    if (t == 0) return b;
    return c * pow(2, 10 * (t / d - 1)) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_expo_out(double t, double b, double c, double d) {
    if (t == d) return b + c;
    return c * (-pow(2, -10 * t / d) + 1) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_expo_in_out(double t, double b, double c, double d) {
    if (t == 0) return b;
    if (t == d) return b + c;
    if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
    return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_back_in(double t, double b, double c, double d) {
    static double s = 1.70158;
    return c * (t /= d) * t * ((s + 1) * t - s) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_back_out(double t, double b, double c, double d) {
    static double s = 1.70158;
    return c * ((t = t / d - 1) * t * ((s + 1) * t + s) + 1) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_back_in_out(double t, double b, double c, double d) {
    static double s = 1.70158;
    static double v = 1.525;
    if ((t /= d / 2) < 1) return c / 2 * (t * t * (((s *= v) + 1) * t - s)) + b;
    return c / 2 * ((t -= 2) * t * (((s *= v) + 1) * t + s) + 2) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_bounce_in(double t, double b, double c, double d) {
    return c - ice_easings_bounce_out(d - t, 0, c, d) + b;
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_bounce_out(double t, double b, double c, double d) {
    static double n1 = 7.5625;
    static double d1 = 2.75;
    
    if ((t /= d) < (1 / d1)) {
        return c * (n1 * t * t) + b;
    } else if (t < (2 / d1)) {
        return c * (n1 * (t -= (1.5 / d1)) * t + 0.75) + b;
    } else if (t < (2.5 / d1)) {
        return c * (n1 * (t -= (2.25 / d1)) * t + 0.9375) + b;
    } else {
        return c * (n1 * (t -= (2.625 / d1)) * t + 0.984375) + b;
    }
}

ICE_EASINGS_API double ICE_EASINGS_CALLCONV ice_easings_bounce_in_out(double t, double b, double c, double d) {
    if (t < d / 2) return ice_easings_bounce_in(t * 2, 0, c, d) * 0.5 + b;
    return ice_easings_bounce_out(t * 2 - d, 0, c, d) * 0.5 + c * 0.5 + b;
}

#endif  // ICE_EASINGS_IMPL
#endif  // ICE_EASINGS_H
