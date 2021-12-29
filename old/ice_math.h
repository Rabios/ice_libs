// Written by Rabia Alhaffar in 4/April/2021
// ice_math.h
// Single-Header Cross-Platform C library for working with Math!
// Updated: 25/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_math.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_math is cross-platform single-header C library for working with math, It Includes 
functions working with Matrices, Vectors, Quaternions, and also with Vertices,
Plus some functions for algorithms and formulas were added!

Also, It includes made-from-zero implementation of C math library functions! (ice_math doesn't need math.h)

[2] USAGE:
Define ICE_MATH_IMPL then include ice_math.h in your C/C++ code!

[3] NOTE:
Portions of this uses Ramon Santamaria's raymath (for Quaternions, Vectors, Matrices), Which has license.
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_math
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_math by possibly one of following things:
//
// 1. Test ice_math on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_math LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_math is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_MATH_H
#define ICE_MATH_H

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
#  if defined(ICE_MATH_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_MATH_CALLCONV_FASTCALL)
#    define ICE_MATH_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_MATH_CALLCONV_STDCALL)
#    define ICE_MATH_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_MATH_CALLCONV_CDECL)
#    define ICE_MATH_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_MATH_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_MATH_CALLCONV_VECTORCALL)
#    define ICE_MATH_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_MATH_CALLCONV_FASTCALL)
#    define ICE_MATH_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_MATH_CALLCONV_STDCALL)
#    define ICE_MATH_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_MATH_CALLCONV_CDECL)
#    define ICE_MATH_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_MATH_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_MATH_CALLCONV_VECTORCALL)
#    define ICE_MATH_CALLCONV __vectorcall
#  elif defined(ICE_MATH_CALLCONV_FASTCALL)
#    define ICE_MATH_CALLCONV __fastcall
#  elif defined(ICE_MATH_CALLCONV_STDCALL)
#    define ICE_MATH_CALLCONV __stdcall
#  elif defined(ICE_MATH_CALLCONV_CDECL)
#    define ICE_MATH_CALLCONV __cdecl
#  else
#    define ICE_MATH_CALLCONV
#  endif
#else
#  define ICE_MATH_CALLCONV
#endif

// Detect Windows to allow building DLLs
#if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#  define ICE_MATH_MICROSOFT
#endif

// We can let our functions static instead of extern if desired.
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_MATH_EXTERN) && defined(ICE_MATH_STATIC))
#  define ICE_MATH_EXTERN
#endif

#if defined(ICE_MATH_EXTERN)
#  define ICE_MATH_APIDEF extern
#elif defined(ICE_MATH_STATIC)
#  define ICE_MATH_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_MATH_INLINE to enable inline functionality.
#if defined(ICE_MATH_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_MATH_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_MATH_INLINEDEF inline
#  endif
#else
#  define ICE_MATH_INLINEDEF
#endif

// Allow to build DLL via ICE_MATH_DLLEXPORT or ICE_MATH_DLLIMPORT if desired!
// Else, Just define API as extern C code!
#if defined(ICE_MATH_MICROSOFT)
#  if defined(ICE_MATH_DLLEXPORT)
#    define ICE_MATH_API __declspec(dllexport) ICE_MATH_INLINEDEF
#  elif defined(ICE_MATH_DLLIMPORT)
#    define ICE_MATH_API __declspec(dllimport) ICE_MATH_INLINEDEF
#  else
#    define ICE_MATH_API ICE_MATH_APIDEF ICE_MATH_INLINEDEF
#  endif
#else
#  define ICE_MATH_API ICE_MATH_APIDEF ICE_MATH_INLINEDEF
#endif

// Custom memory allocators
#ifndef ICE_MATH_MALLOC
#  define ICE_MATH_MALLOC(sz) malloc(sz)
#endif
#ifndef ICE_MATH_CALLOC
#  define ICE_MATH_CALLOC(n, sz) calloc(n, sz)
#endif
#ifndef ICE_MATH_REALLOC
#  define ICE_MATH_REALLOC(ptr, sz) realloc(ptr, sz)
#endif
#ifndef ICE_MATH_FREE
#  define ICE_MATH_FREE(ptr) free(ptr)
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_math DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
#define ICE_MATH_PI                     3.14159265358979323846
#define ICE_MATH_E                      2.7182818284590452354
#define ICE_MATH_EPSILON                2.2204460492503130808472633361816
#define ICE_MATH_PI_2                   1.57079632679489661923
#define ICE_MATH_PI_4                   0.78539816339744830962
#define ICE_MATH_1_PI                   0.31830988618379067154
#define ICE_MATH_2_PI                   0.63661977236758134308
#define ICE_MATH_2_SQRTPI               1.12837916709551257390
#define ICE_MATH_LN2                    0.69314718055994530942
#define ICE_MATH_LN10                   2.30258509299404568402
#define ICE_MATH_LOG2E                  1.4426950408889634074
#define ICE_MATH_LOG10E                 0.43429448190325182765
#define ICE_MATH_SQRT2                  1.41421356237309504880
#define ICE_MATH_SQRT1_2                0.70710678118654752440
#define ICE_MATH_INFINITY               1 / 0
#define ICE_MATH_NAN                    7ff8000000000000
#define ICE_MATH_FLT_RADIX              2
#define ICE_MATH_TAU                    ICE_MATH_PI * 2
#define ICE_MATH_UNDEFINED              NULL

#define ICE_MATH_SIN_0_RADIANS          0
#define ICE_MATH_SIN_30_RADIANS         ICE_MATH_PI / 6
#define ICE_MATH_SIN_45_RADIANS         ICE_MATH_PI / 4
#define ICE_MATH_SIN_60_RADIANS         ICE_MATH_PI / 3
#define ICE_MATH_SIN_90_RADIANS         ICE_MATH_PI / 2
#define ICE_MATH_SIN_120_RADIANS        (2 * ICE_MATH_PI) / 3
#define ICE_MATH_SIN_135_RADIANS        (3 * ICE_MATH_PI) / 4
#define ICE_MATH_SIN_150_RADIANS        (5 * ICE_MATH_PI) / 6
#define ICE_MATH_SIN_180_RADIANS        ICE_MATH_PI
#define ICE_MATH_SIN_210_RADIANS        (7 * ICE_MATH_PI) / 6
#define ICE_MATH_SIN_225_RADIANS        (5 * ICE_MATH_PI) / 4
#define ICE_MATH_SIN_240_RADIANS        (4 * ICE_MATH_PI) / 3
#define ICE_MATH_SIN_270_RADIANS        (3 * ICE_MATH_PI) / 2
#define ICE_MATH_SIN_300_RADIANS        (5 * ICE_MATH_PI) / 3
#define ICE_MATH_SIN_315_RADIANS        (7 * ICE_MATH_PI) / 4
#define ICE_MATH_SIN_330_RADIANS        (11 * ICE_MATH_PI) / 6
#define ICE_MATH_SIN_360_RADIANS        ICE_MATH_PI * 2

#define ICE_MATH_SIN_0                  0
#define ICE_MATH_COS_0                  1
#define ICE_MATH_TAN_0                  0
#define ICE_MATH_COT_0                  ICE_MATH_UNDEFINED
#define ICE_MATH_SEC_0                  1
#define ICE_MATH_CSC_0                  ICE_MATH_UNDEFINED

#define ICE_MATH_SIN_30                 1 / 2
#define ICE_MATH_COS_30                 0.8660254037844386
#define ICE_MATH_TAN_30                 0.5773502691896258
#define ICE_MATH_COT_30                 1.7320508075688772
#define ICE_MATH_SEC_30                 1.1547005383792517
#define ICE_MATH_CSC_30                 2

#define ICE_MATH_SIN_45                 0.7071067811865475
#define ICE_MATH_COS_45                 0.7071067811865475
#define ICE_MATH_TAN_45                 1
#define ICE_MATH_COT_45                 1
#define ICE_MATH_SEC_45                 1.4142135623730951
#define ICE_MATH_CSC_45                 1.4142135623730951

#define ICE_MATH_SIN_60                 0.8660254037844386
#define ICE_MATH_COS_60                 1 / 2
#define ICE_MATH_TAN_60                 1.7320508075688772
#define ICE_MATH_COT_60                 0.5773502691896258
#define ICE_MATH_SEC_60                 2
#define ICE_MATH_CSC_60                 0.47140452079103173

#define ICE_MATH_SIN_90                 1
#define ICE_MATH_COS_90                 0
#define ICE_MATH_TAN_90                 ICE_MATH_UNDEFINED
#define ICE_MATH_COT_90                 1
#define ICE_MATH_SEC_90                 ICE_MATH_UNDEFINED
#define ICE_MATH_CSC_90                 0

#define ICE_MATH_SIN_120                0.8660254037844386
#define ICE_MATH_COS_120                -(1 / 2)
#define ICE_MATH_TAN_120                -1.7320508075688772
#define ICE_MATH_COT_120                -1.1547005383792517
#define ICE_MATH_SEC_120                -2
#define ICE_MATH_CSC_120                -0.47140452079103173

#define ICE_MATH_SIN_135                0.7071067811865475
#define ICE_MATH_COS_135                -0.7071067811865475
#define ICE_MATH_TAN_135                -1
#define ICE_MATH_COT_135                -1
#define ICE_MATH_SEC_135                -1.4142135623730951
#define ICE_MATH_CSC_135                1.4142135623730951

#define ICE_MATH_SIN_150                1 / 2
#define ICE_MATH_COS_150                1.7320508075688772
#define ICE_MATH_TAN_150                -0.5773502691896258
#define ICE_MATH_COT_150                -1.7320508075688772
#define ICE_MATH_SEC_150                -1.1547005383792517
#define ICE_MATH_CSC_150                2

#define ICE_MATH_SIN_180                0
#define ICE_MATH_COS_180                -1
#define ICE_MATH_TAN_180                0
#define ICE_MATH_COT_180                ICE_MATH_UNDEFINED
#define ICE_MATH_SEC_180                -1
#define ICE_MATH_CSC_180                ICE_MATH_UNDEFINED

#define ICE_MATH_SIN_210                -(1 / 2)
#define ICE_MATH_COS_210                -1.7320508075688772
#define ICE_MATH_TAN_210                0.5773502691896258
#define ICE_MATH_COT_210                1.7320508075688772
#define ICE_MATH_SEC_210                -1.1547005383792517
#define ICE_MATH_CSC_210                -2

#define ICE_MATH_SIN_225                -0.7071067811865475
#define ICE_MATH_COS_225                -0.7071067811865475
#define ICE_MATH_TAN_225                1
#define ICE_MATH_COT_225                1
#define ICE_MATH_SEC_225                -1.4142135623730951
#define ICE_MATH_CSC_225                -1.4142135623730951

#define ICE_MATH_SIN_240                -0.8660254037844386
#define ICE_MATH_COS_240                -(1 / 2)
#define ICE_MATH_TAN_240                1.7320508075688772
#define ICE_MATH_COT_240                1.1547005383792517
#define ICE_MATH_SEC_240                -2
#define ICE_MATH_CSC_240                -0.47140452079103173

#define ICE_MATH_SIN_270                -1
#define ICE_MATH_COS_270                0
#define ICE_MATH_TAN_270                ICE_MATH_UNDEFINED
#define ICE_MATH_COT_270                0
#define ICE_MATH_SEC_270                ICE_MATH_UNDEFINED
#define ICE_MATH_CSC_270                -1

#define ICE_MATH_SIN_300                -0.8660254037844386
#define ICE_MATH_COS_300                1 / 2
#define ICE_MATH_TAN_300                -1.7320508075688772
#define ICE_MATH_COT_300                -1.1547005383792517
#define ICE_MATH_SEC_300                2
#define ICE_MATH_CSC_300                -0.47140452079103173

#define ICE_MATH_SIN_315                -0.7071067811865475
#define ICE_MATH_COS_315                0.7071067811865475
#define ICE_MATH_TAN_315                -1
#define ICE_MATH_COT_315                -1
#define ICE_MATH_SEC_315                1.4142135623730951
#define ICE_MATH_CSC_315                -1.4142135623730951

#define ICE_MATH_SIN_330                -(1 / 2)
#define ICE_MATH_COS_330                1.7320508075688772
#define ICE_MATH_TAN_330                -0.5773502691896258
#define ICE_MATH_COT_330                -1.7320508075688772
#define ICE_MATH_SEC_330                1.1547005383792517
#define ICE_MATH_CSC_330                -2

#define ICE_MATH_SIN_360                0
#define ICE_MATH_COS_360                1
#define ICE_MATH_TAN_360                0
#define ICE_MATH_COT_360                ICE_MATH_UNDEFINED
#define ICE_MATH_SEC_360                1
#define ICE_MATH_CSC_360                ICE_MATH_UNDEFINED

#define ICE_MATH_UPPER_MASK             0x80000000
#define ICE_MATH_LOWER_MASK             0x7fffffff
#define ICE_MATH_TEMPERING_MASK_B       0x9d2c5680
#define ICE_MATH_TEMPERING_MASK_C       0xefc60000
#define ICE_MATH_STATE_VECTOR_LENGTH    624
#define ICE_MATH_STATE_VECTOR_M         397         // changes to ICE_MATH_STATE_VECTOR_LENGTH also require changes to this

typedef enum {
    ICE_MATH_TRUE   = 0,
    ICE_MATH_FALSE  = -1,
} ice_math_bool;

typedef struct ice_math_vec2 {
    double x;
    double y;
} ice_math_vec2;

typedef struct ice_math_vec3 {
    double x;
    double y;
    double z;
} ice_math_vec3;

typedef struct ice_math_vec4 {
    double x;
    double y;
    double z;
    double w;
} ice_math_vec4;

typedef ice_math_vec4 ice_math_quat;

typedef struct ice_math_rect {
    double x;
    double y;
    double w;
    double h;
} ice_math_rect;

typedef struct ice_math_mat {
    double m0;
    double m1;
    double m2;
    double m3;
    
    double m4;
    double m5;
    double m6;
    double m7;
    
    double m8;
    double m9;
    double m10;
    double m11;
    
    double m12;
    double m13;
    double m14;
    double m15;
} ice_math_mat;

typedef struct ice_math_mtrand {
    unsigned long mt[ICE_MATH_STATE_VECTOR_LENGTH];
    int index;
} ice_math_mtrand;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_math FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
// Math Implementations (+ Extra Stuff)
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_rad(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_deg(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_abs(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_acos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_asin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_atan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_acot(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_asec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_acsc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_max(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_min(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_ceil(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_floor(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_round(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_imul(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sqr(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_pow(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_log2(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_exp(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_expm1(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_log(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_log10(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_log1p(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_exp2(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sqrt(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sinh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cosh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tanh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_coth(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sech(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_csch(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_trunc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sign(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_fib(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_fact(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cot(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_csc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin_sum(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin_diff(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos_sum(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos_diff(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan_sum(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan_diff(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin2(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos2(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan2(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin3(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos3(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan3(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin4(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos4(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan4(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin5(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos5(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan5(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_double_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_double_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_double_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_double_cot(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_double_sec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_double_csc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_double_sinh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_double_cosh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_double_tanh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_triple_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_triple_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_triple_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_triple_cot(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_triple_sec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_triple_csc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_triple_sinh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_triple_cosh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_triple_tanh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_quadruple_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_quadruple_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_quadruple_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_quadruple_sinh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_quadruple_cosh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_quadruple_tanh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_quintuple_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_quintuple_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_quintuple_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sextuple_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sextuple_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sextuple_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_hypot(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_atan2(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_asinh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_acosh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_atanh(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_acoth(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_asech(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_acsch(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cbrt(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_ldexp(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_scalbn(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_fma(double a, double b, double c);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_dim(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_logb(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin_to_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin_to_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin_to_cot(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin_to_sec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sin_to_csc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos_to_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos_to_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos_to_cot(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos_to_sec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cos_to_csc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan_to_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan_to_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan_to_cot(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan_to_sec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_tan_to_csc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cot_to_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cot_to_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cot_to_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cot_to_sec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_cot_to_csc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sec_to_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sec_to_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sec_to_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sec_to_cot(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_sec_to_csc(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_csc_to_sin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_csc_to_cos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_csc_to_tan(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_csc_to_cot(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_csc_to_sec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_co_angle(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_versin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_vercos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_coversin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_covercos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_haversin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_havercos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_hacoversin(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_hacovercos(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_exsec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_excosec(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_crd(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_mod(double a, double b);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_frexp(double n);
ICE_MATH_API  double  ICE_MATH_CALLCONV  ice_math_gamma(double n);

// Math Algorithms/Math Formulas
ICE_MATH_API  ice_math_bool  ICE_MATH_CALLCONV  ice_math_even(int n);
ICE_MATH_API  ice_math_bool  ICE_MATH_CALLCONV  ice_math_odd(int n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_discriminant(double a, double b, double c);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_trinomial(double a, double b);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_iter_log(double a, double b);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_avg(double a, double b, double c);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_birthday_paradox(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_parity(int n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_binceoff(double a, double b);
ICE_MATH_API  int            ICE_MATH_CALLCONV  ice_math_cassini(int n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_leonardo(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_double_fact(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_hexagonal(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_gcd(int a, int b);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_phi(double n);
ICE_MATH_API  ice_math_bool  ICE_MATH_CALLCONV  ice_math_sqrt_exist(int a, int b, int c);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_seq(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_pairwise_sum(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_ncr(double a, double b);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_dyckpaths(double n);
ICE_MATH_API  ice_math_bool  ICE_MATH_CALLCONV  ice_math_prime(int n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_rasphon(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_nth_group_sum(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_trajectory_time(double a, double b);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_catalan(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_pad(double n);
ICE_MATH_API  ice_math_bool  ICE_MATH_CALLCONV  ice_math_composite(int n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_nth_prime_factor(int a, int b);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_moser_seq(int n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_lrotate(int a, int b, int bits);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_rrotate(int a, int b, int bits);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_politness(int n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_multi_order(int a, int b);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_find_nth(double n);
ICE_MATH_API  int            ICE_MATH_CALLCONV  ice_math_perfect_square_min_number(int n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_sum(int n);
ICE_MATH_API  ice_math_bool  ICE_MATH_CALLCONV  ice_math_amicable(double a, double b);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_bisection(double a, double b);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_fermat(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_exact_prime_factor_count(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_abundance(double n);
ICE_MATH_API  ice_math_bool  ICE_MATH_CALLCONV  ice_math_abundant(double n);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_clamp(double value, double min, double max);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_lerp(double start, double end, double amount);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_norm(double value, double start, double end);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_remap(double value, double in_start, double in_end, double out_start, double out_end);

// Vectors
// Vector2
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_zero(void);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_one(void);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_neg(ice_math_vec2 v);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_reflect(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_add(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_add_num(ice_math_vec2 v, double n);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_sub(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_sub_num(ice_math_vec2 v, double n);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_mult(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_div(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_scale(ice_math_vec2 v, double scale);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec2_dot_product(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec2_cross_product(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_lerp(ice_math_vec2 v1, ice_math_vec2 v2, double x);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_norm(ice_math_vec2 v);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec2_len(ice_math_vec2 v);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec2_len_sqr(ice_math_vec2 v);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec2_angle(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec2_dist(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_rotate(ice_math_vec2 v, double n);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_vec2_move_towards(ice_math_vec2 v1, ice_math_vec2 v2, double max_dist);

// Vector3
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_zero(void);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_one(void);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_neg(ice_math_vec3 v);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_add(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_add_num(ice_math_vec3 v, double n);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_sub(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_sub_num(ice_math_vec3 v, double n);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_mult(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_div(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_scale(ice_math_vec3 v, double scale);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec3_dot_product(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_cross_product(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_triple_product(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_lerp(ice_math_vec3 v1, ice_math_vec3 v2, double x);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_norm(ice_math_vec3 v);
ICE_MATH_API  void           ICE_MATH_CALLCONV  ice_math_vec3_ortho_norm(ice_math_vec3* v1, ice_math_vec3* v2);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec3_len(ice_math_vec3 v);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec3_len_sqr(ice_math_vec3 v);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec3_angle(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec3_dist(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_perpendicular(ice_math_vec3 v);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_transform(ice_math_vec3 v, ice_math_mat m);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_rotate_by_quat(ice_math_vec3 v, ice_math_quat q);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_reflect(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_min(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_max(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_barycenter(ice_math_vec3 p, ice_math_vec3 a, ice_math_vec3 b, ice_math_vec3 c);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_vec3_unproj(ice_math_vec3 source, ice_math_mat projection, ice_math_mat view);

// Vector4
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_zero(void);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_one(void);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_neg(ice_math_vec4 v);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_add(ice_math_vec4 v1, ice_math_vec4 v2);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_add_num(ice_math_vec4 v, double n);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_sub(ice_math_vec4 v1, ice_math_vec4 v2);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_sub_num(ice_math_vec4 v, double n);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_mult(ice_math_vec4 v1, ice_math_vec4 v2);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_div(ice_math_vec4 v1, ice_math_vec4 v2);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_scale(ice_math_vec4 v, double scale);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec4_dot_product(ice_math_vec4 v1, ice_math_vec4 v2);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_lerp(ice_math_vec4 v1, ice_math_vec4 v2, double x);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_norm(ice_math_vec4 v);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec4_len(ice_math_vec4 v);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec4_len_sqr(ice_math_vec4 v);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_vec4_dist(ice_math_vec4 v1, ice_math_vec4 v2);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_min(ice_math_vec4 v1, ice_math_vec4 v2);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_vec4_max(ice_math_vec4 v1, ice_math_vec4 v2);

// Quaternions
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_add(ice_math_quat q1, ice_math_quat q2);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_add_num(ice_math_quat q, double n);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_sub(ice_math_quat q1, ice_math_quat q2);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_sub_num(ice_math_quat q, double n);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_identity(void);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_quat_len(ice_math_quat q);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_quat_len_sqr(ice_math_quat q);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_norm(ice_math_quat q);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_inv(ice_math_quat q);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_mult(ice_math_quat q1, ice_math_quat q2);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_scale(ice_math_quat q, double n);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_div(ice_math_quat q1, ice_math_quat q2);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_lerp(ice_math_quat q1, ice_math_quat q2, double n);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_nlerp(ice_math_quat q1, ice_math_quat q2, double n);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_slerp(ice_math_quat q1, ice_math_quat q2, double n);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_from_vec3_to_vec3(ice_math_vec3 from, ice_math_vec3 to);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_from_mat(ice_math_mat m);
ICE_MATH_API  ice_math_mat   ICE_MATH_CALLCONV  ice_math_quat_to_mat(ice_math_quat q);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_from_axis_angle(ice_math_vec3 axis, double angle);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_quat_from_quat_to_angle(ice_math_quat q);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_quat_from_quat_to_axis(ice_math_quat q);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_from_euler(double roll, double pitch, double yaw);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_quat_to_euler(ice_math_quat q);
ICE_MATH_API  ice_math_quat  ICE_MATH_CALLCONV  ice_math_quat_transform(ice_math_quat q, ice_math_mat m);

// Matrices
ICE_MATH_API  double        ICE_MATH_CALLCONV  ice_math_mat_determinant(ice_math_mat m);
ICE_MATH_API  double        ICE_MATH_CALLCONV  ice_math_mat_trace(ice_math_mat m);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_transpose(ice_math_mat m);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_inv(ice_math_mat m);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_norm(ice_math_mat m);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_identity(void);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_add(ice_math_mat left, ice_math_mat right);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_sub(ice_math_mat left, ice_math_mat right);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_translate(double x, double y, double z);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_rotate(ice_math_vec3 axis, double angle);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_rotate_xyz(ice_math_vec3 ang);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_rotate_zyx(ice_math_vec3 ang);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_rotate_x(double ang);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_rotate_y(double ang);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_rotate_z(double ang);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_scale(double x, double y, double z);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_mult(ice_math_mat left, ice_math_mat right);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_frustum(double left, double right, double bottom, double top, double near, double far);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_perspective(double fovy, double aspect, double near, double far);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_ortho(double left, double right, double bottom, double top, double near, double far);
ICE_MATH_API  ice_math_mat  ICE_MATH_CALLCONV  ice_math_mat_lookat(ice_math_vec3 eye, ice_math_vec3 target, ice_math_vec3 up);

// Vertices
// WARNING: They allocate memory, Consider freeing vertices with ice_math_free_vertices() when program finishes!
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_point2d_vertices(ice_math_vec2 v);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_line2d_vertices(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_rect2d_vertices(ice_math_rect r);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_circle2d_vertices(ice_math_vec2 pos, double r);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_triangle2d_vertices(ice_math_vec2 v1, ice_math_vec2 v2, ice_math_vec2 v3);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_polygon2d_vertices(ice_math_vec2 v, double size, int sides);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_tex2d_rect_vertices(ice_math_rect src, ice_math_rect dst, int width, int height);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_tex2d_tex_vertices(ice_math_rect src, ice_math_rect dst, int width, int height);

ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_cube_vertices(ice_math_vec3 v, double s);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_cuboid_vertices(ice_math_vec3 v, ice_math_vec3 s);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_sphere_vertices(ice_math_vec3 v, double s);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_point3d_vertices(ice_math_vec3 v);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_line3d_vertices(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_rect3d_vertices(ice_math_rect r, double z);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_circle3d_vertices(ice_math_vec3 pos, double r);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_triangle3d_vertices(ice_math_vec3 v1, ice_math_vec3 v2, ice_math_vec3 v3);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_polygon3d_vertices(ice_math_vec3 v, double size, int sides);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_tex3d_rect_vertices(ice_math_rect src, ice_math_rect dst, double z, int width, int height);
ICE_MATH_API  double*  ICE_MATH_CALLCONV  ice_math_tex3d_tex_vertices(ice_math_rect src, ice_math_rect dst, double z, int width, int height);

ICE_MATH_API  void     ICE_MATH_CALLCONV  ice_math_free_vertices(double* vertices);

// Distances
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_dist2d(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_dist2d_between(ice_math_vec2 v1, ice_math_vec2 v2);
ICE_MATH_API  ice_math_vec2  ICE_MATH_CALLCONV  ice_math_rotate_around2d(ice_math_vec2 v1, ice_math_vec2 v2, double angle);
ICE_MATH_API  ice_math_vec3  ICE_MATH_CALLCONV  ice_math_dist3d(ice_math_vec3 v1, ice_math_vec3 v2);
ICE_MATH_API  ice_math_vec4  ICE_MATH_CALLCONV  ice_math_dist4d(ice_math_vec4 v1, ice_math_vec4 v2);

ICE_MATH_API  double         ICE_MATH_CALLCONV  ice_math_rand(void);

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_math IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_MATH_IMPL)
#include <time.h>       // time(NULL), For random numbers seed

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_rad(double n) {
    return n * (ICE_MATH_PI / 180);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_deg(double n) {
    return n * (180 / ICE_MATH_PI);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_abs(double n) {
    return (n < 0) ? -n : n;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acos(double n) {
    return (-0.69813170079773212 * n * n - 0.87266462599716477) * n + 1.5707963267948966;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asin(double n) {
    return n + (1 / 2) * ((n * n * n) / 3) + ((1 * 3) / (2 * 4)) * ((n * n * n * n * n) / 5) + ((1 * 3 * 5) / (2 * 4 * 6)) * ((n * n * n * n * n * n * n) / 7);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_atan(double n) {
    return (ice_math_asin(n) / ice_math_acos(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_max(double a, double b) {
    return (a > b) ? a : b;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_min(double a, double b) {
    return (a < b) ? a : b;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_ceil(double n) {
    if (n < 0) {
        return n;
    } else {
        double diff = n - (int) n;
        return (diff > 0) ? (int) n + 1 : n;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_floor(double n) {
    if (n < 0) {
        return (int) n;
    } else {
        double diff = -n - (int) -n;
        return (diff >= 0.5) ? (int) n - 1 : n;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_round(double n) {
    if (n > 0) {
        double diff = n - (int) n;
        return (diff >= 0.5) ? (int)n + 1 : n;
    } else {
        double diff = -n - (int) -n;
        return (diff >= 0.6) ? (int) n - 1 : n;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_imul(double a, double b) {
    return (int) a * (int) b;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sqr(double n) {
    return n * n;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_pow(double a, double b) {
    if (b == 0) {
        return 1;
    } else if (a < 0 && (b < 1 && b > 0)) {
        return a;
    } else if (b == 1) {
        return a;
    } else if (b < 1 && b > 0) {
        return a * b;
    } else if (b < 0) {
        double n = a;
        for (int i = 0; i < -b - 1; i++) {
            n *= a;
        }
        return 1 / n;
    } else {
        double n = a;
        for (int i = 0; i < b - 1; i++) {
            n *= a;
        }
        return n;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log2(double n) {
    return (n > 1) ? 1 + ice_math_log2(n / 2) : 0;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_exp(double n) {
    return ice_math_pow(2.718281828459, n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_expm1(double n) {
    return ice_math_exp(n) - 1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log(double n) {
    return (ice_math_log2(n) / 2);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log10(double n) {
    return ice_math_log(n) / ice_math_log(10);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_exp2(double n) {
    return ice_math_exp(n * ice_math_log(2));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log1p(double n) {
    return ice_math_log(n + 1);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sqrt(double n) {
    double x = n / 2;
    double least = 0;
    
    while (x != least) { 
        least = x;
        x = (x + n / x) / 2; 
    }
    
    return x;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sinh(double n) {
    return (ice_math_pow(ICE_MATH_E, n) - ice_math_pow(ICE_MATH_E, -n)) / 2;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cosh(double n) {
    return (ice_math_pow(ICE_MATH_E, n) + ice_math_pow(ICE_MATH_E, -n)) / 2;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tanh(double n) {
    return (ice_math_pow(ICE_MATH_E, n) - ice_math_pow(ICE_MATH_E, -n)) / (ice_math_pow(ICE_MATH_E, n) + ice_math_pow(ICE_MATH_E, -n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_coth(double n) {
    return (ice_math_pow(ICE_MATH_E, n) + ice_math_pow(ICE_MATH_E, -n)) / (ice_math_pow(ICE_MATH_E, n) - ice_math_pow(ICE_MATH_E, -n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sech(double n) {
    return 1 / ice_math_cosh(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csch(double n) {
    return 1 / ice_math_sinh(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_trunc(double n) {
    return (int) n;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sign(double n) {
    if (n == 0) return 0;
    return (n > 0) ? 1 : -1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fib(double n) {
    return (n <= 2) ? (ice_math_fib(n - 1) + ice_math_fib(n - 2)) : 1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fact(double n) {
    double x = 1;
    
    for (int i = 2; i <= n; i++) {
        x = x * i;
    }
    
    return x;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos(double n) {
    return (1 - ((n * n) / (2 * 1)) + ((n * n * n * n) / (4 * 3 * 2 * 1)) - ((n * n * n * n * n * n) / (6 * 5 * 4 * 3 * 2 * 1)) + ((n * n * n * n * n * n * n * n) / (8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)) - ((n * n * n * n * n * n * n * n * n * n) / (10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)) + ((n * n * n * n * n * n * n * n * n * n * n * n) / (12 * 11 * 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin(double n) {
    return (n - ((n * n * n) / (3 * 2 * 1)) + ((n * n * n * n * n) / (5 * 4 * 3 * 2 * 1)) - ((n * n * n * n * n * n * n) / (7 * 6 * 5 * 4 * 3 * 2 * 1)) + ((n * n * n * n * n * n * n * n * n) / (9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)) - ((n * n * n * n * n * n * n * n * n * n * n) / (11 * 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)) + ((n * n * n * n * n * n * n * n * n * n * n * n * n) / (13 * 12 * 11 * 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan(double n) {
    return (ice_math_sin(n) / ice_math_cos(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot(double n) {
    return (ice_math_cos(n) / ice_math_sin(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec(double n) {
    return (1 / ice_math_cos(n)); 
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc(double n) {
    return (1 / ice_math_sin(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_sum(double a, double b) {
    return ((ice_math_sin(a) * ice_math_cos(b)) + (ice_math_sin(b) * ice_math_cos(a)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_diff(double a, double b) {
    return ((ice_math_sin(a) * ice_math_cos(b)) - (ice_math_sin(b) * ice_math_cos(a)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_sum(double a, double b) {
    return ((ice_math_cos(a) * ice_math_cos(b)) - (ice_math_sin(a) * ice_math_sin(b)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_diff(double a, double b) {
    return ((ice_math_cos(a) * ice_math_cos(b)) + (ice_math_sin(a) * ice_math_sin(b)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_sum(double a, double b) {
    return ((ice_math_tan(a) + ice_math_tan(b)) / (1 - (ice_math_tan(a) * ice_math_tan(b))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_diff(double a, double b) {
    return ((ice_math_tan(a) - ice_math_tan(b)) / (1 + (ice_math_tan(a) * ice_math_tan(b))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_sin(double n) {
    return (2 * ice_math_sin(n) * ice_math_cos(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_cos(double n) {
    return ((ice_math_cos(n) * ice_math_cos(n)) - (ice_math_sin(n) * ice_math_sin(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_tan(double n) {
    return ((2 * ice_math_tan(n)) / (1 - (ice_math_tan(n) * ice_math_tan(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_hypot(double a, double b) {
    return ice_math_sqrt(a * a + b * b);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_atan2(double a, double b) {
    if (b > 0) {
        return ice_math_atan(a / b);
    } else if (b < 0 && a >= 0) {
        return ice_math_atan(a / b) + ICE_MATH_PI;
    } else if (b < 0 && a < 0) {
        return ice_math_atan(a / b) - ICE_MATH_PI;
    } else if (b == 0 && a > 0) {
        return ICE_MATH_PI / 2;
    } else if (b == 0 && a < 0) {
        return -(ICE_MATH_PI / 2);
    } else if (a == 0 && b == 0) {
        return 0;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asinh(double n) {
    return ice_math_log(n + ice_math_sqrt((n * n) + 1));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acosh(double n) {
    return ice_math_log(n + ice_math_sqrt((n * n) - 1));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_atanh(double n) {
    return (1 / 2) * ice_math_log((1 + n) / (1 - n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acoth(double n) {
    return (1 / 2) * ice_math_log((n + 1) / (n - 1));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asech(double n) {
    return ice_math_log(1 + ice_math_sqrt((1 - (n * n)) / n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acsch(double n) {
    return ice_math_log(1 + ice_math_sqrt((1 + (n * n)) / n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cbrt(double n) {
    return ice_math_pow(n, 1 / 3);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_ldexp(double a, double b) {
    return a * ice_math_pow(2, b);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_scalbn(double a, double b) {
    return a * ice_math_pow(ICE_MATH_FLT_RADIX, b);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fma(double a, double b, double c) {
    return ((a * b) + c);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_dim(double a, double b) {
    if (a > b) {
        return a - b;
    } else if (a <= b) {
        return 0;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_logb(double n) {
    return ice_math_log2(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_to_cos(double n) {
    return ice_math_sqrt(1 - (ice_math_sin(n) * ice_math_sin(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_to_tan(double n) {
    return (ice_math_sin(n) / ice_math_sqrt(1 - (ice_math_sin(n) * ice_math_sin(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_to_cot(double n) {
    return (ice_math_sqrt(1 - (ice_math_sin(n) * ice_math_sin(n))) / ice_math_sin(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_to_sec(double n) {
    return (1 / (1 - (ice_math_sin(n) * ice_math_sin(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_to_csc(double n) {
    return 1 / ice_math_sin(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_to_sin(double n) {
    return ice_math_sqrt(1 - (ice_math_cos(n) * ice_math_cos(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_to_tan(double n) {
    return (ice_math_sqrt(1 - (ice_math_cos(n) * ice_math_cos(n))) / ice_math_cos(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_to_cot(double n) {
    return (ice_math_cos(n) / ice_math_sqrt(1 - (ice_math_cos(n) * ice_math_cos(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_to_sec(double n) {
    return 1 / ice_math_cos(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_to_csc(double n) {
    return (1 / (1 - (ice_math_cos(n) * ice_math_cos(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_to_sin(double n) {
    return (ice_math_tan(n) / (1 + (ice_math_tan(n) * ice_math_tan(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_to_cos(double n) {
    return (1 / (1 + (ice_math_tan(n) * ice_math_tan(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_to_cot(double n) {
    return 1 / ice_math_tan(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_to_sec(double n) {
    return ice_math_sqrt(1 + (ice_math_tan(n) * ice_math_tan(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_to_csc(double n) {
    return (ice_math_sqrt(1 + (ice_math_tan(n) * ice_math_tan(n))) / ice_math_tan(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_to_sin(double n) {
    return (1 / ice_math_sqrt(1 + (ice_math_cot(n) * ice_math_cot(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_to_cos(double n) {
    return (ice_math_cot(n) / ice_math_sqrt(1 + (ice_math_cot(n) * ice_math_cot(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_to_tan(double n) {
    return 1 / ice_math_cot(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_to_sec(double n) {
    return (ice_math_sqrt(1 + (ice_math_cot(n) * ice_math_cot(n))) / ice_math_cot(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_to_csc(double n) {
    return ice_math_sqrt(1 + (ice_math_cot(n) * ice_math_cot(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_to_sin(double n) {
    return (ice_math_sqrt((ice_math_sec(n) * ice_math_sec(n)) - 1) / ice_math_sec(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_to_cos(double n) {
    return 1 / ice_math_sec(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_to_tan(double n) {
    return ice_math_sqrt((ice_math_sec(n) * ice_math_sec(n)) - 1);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_to_cot(double n) {
    return (1 / ice_math_sqrt((ice_math_sec(n) * ice_math_sec(n)) - 1));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_to_csc(double n) {
    return (ice_math_sec(n) / ice_math_sqrt((ice_math_sec(n) * ice_math_sec(n)) - 1));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_to_sin(double n) {
    return 1 / ice_math_csc(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_to_cos(double n) {
    return (ice_math_sqrt((ice_math_csc(n) * ice_math_csc(n)) - 1) / ice_math_csc(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_to_tan(double n) {
    return (1 / ice_math_sqrt((ice_math_csc(n) * ice_math_csc(n)) - 1));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_to_cot(double n) {
    return ice_math_sqrt((ice_math_csc(n) * ice_math_csc(n)) - 1);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_to_sec(double n) {
    return (ice_math_csc(n) / ice_math_sqrt((ice_math_csc(n) * ice_math_csc(n)) - 1));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_co_angle(double n) {
    return (ICE_MATH_PI / 2) - n;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_versin(double n) {
    return 1 - ice_math_cos(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vercos(double n) {
    return 1 + ice_math_cos(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_coversin(double n) {
    return 1 - ice_math_sin(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_covercos(double n) {
    return 1 + ice_math_sin(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_haversin(double n) {
    return ((1 - ice_math_cos(n)) / 2);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_havercos(double n) {
    return ((1 + ice_math_cos(n)) / 2);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_hacoversin(double n) {
    return ((1 - ice_math_sin(n)) / 2);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_hacovercos(double n) {
    return ((1 + ice_math_sin(n)) / 2);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_exsec(double n) {
    return ice_math_sec(n) - 1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_excsc(double n) {
    return ice_math_csc(n) - 1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_crd(double n) {
    return 2 * ice_math_sin(n / 2);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_cot(double n) {
    return ((ice_math_cot(n) * ice_math_cot(n)) - 1 / (2 * ice_math_cot(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_sec(double n) {
    return ((ice_math_sec(n) * ice_math_sec(n)) / (2 - (ice_math_sec(n) * ice_math_sec(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_csc(double n) {
    return (ice_math_csc(n) * ice_math_csc(n)) / 2;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_sinh(double n) {
    return 2 * ice_math_sinh(n) * ice_math_cosh(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_cosh(double n) {
    return (ice_math_cosh(n) * ice_math_cosh(n)) + (ice_math_sinh(n) * ice_math_sinh(n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_tanh(double n) {
    return ice_math_double_sinh(n) / ice_math_double_cosh(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin2(double n) {
   return (1 - ice_math_double_sin(n)) / 2;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos2(double n) {
    return (1 + ice_math_double_cos(n)) / 2;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan2(double n) {
    return ice_math_double_sin(n) / ice_math_double_cos(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin3(double n) {
    return (((3 * ice_math_sin(n)) - ice_math_triple_sin(n)) / 4);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos3(double n) {
    return (((3 * ice_math_cos(n)) + ice_math_triple_cos(n)) / 4);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan3(double n) {
    return ice_math_sin3(n) / ice_math_cos3(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin4(double n) {
    return ((3 - ((4 * ice_math_double_cos(n)) + ice_math_quadruple_cos(n))) / 8);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos4(double n) {
    return ((3 + ((4 * ice_math_double_cos(n)) + ice_math_quadruple_cos(n))) / 8);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan4(double n) {
    return ice_math_sin4(n) / ice_math_cos4(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin5(double n) {
    return (((10 * ice_math_sin(n)) - (5 * ice_math_triple_sin(n)) + ice_math_quintuple_sin(n)) / 16);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos5(double n) {
    return (((10 * ice_math_cos(n)) - (5 * ice_math_triple_cos(n)) + ice_math_quintuple_cos(n)) / 16);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan5(double n) {
    return ice_math_sin5(n) / ice_math_cos5(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_triple_sin(double n) {
    return ((3 * ice_math_sin(n)) - (4 * (ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_triple_cos(double n) {
    return ((4 * (ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n))) - (3 * ice_math_cos(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_triple_tan(double n) {
    return (((3 * ice_math_tan(n)) - (ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n))) / (1 - (3 * ice_math_tan(n) * ice_math_tan(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_triple_cot(double n) {
    return (((3 * ice_math_cot(n)) - (ice_math_cot(n) * ice_math_cot(n) * ice_math_cot(n))) / (1 - (3 * ice_math_cot(n) * ice_math_cot(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_triple_sec(double n) {
    return ((ice_math_sec(n) * ice_math_sec(n) * ice_math_sec(n)) / (4 - (3 * ice_math_sec(n) * ice_math_sec(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_triple_csc(double n) {
    return ((ice_math_csc(n) * ice_math_csc(n) * ice_math_csc(n)) / ((3 * ice_math_csc(n) * ice_math_csc(n)) - 4));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_triple_sinh(double n) {
    return ((3 * ice_math_sinh(n)) + (4 * ice_math_sinh(n) * ice_math_sinh(n) * ice_math_sinh(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_triple_cosh(double n) {
    return ((4 * ice_math_cosh(n) * ice_math_cosh(n) * ice_math_cosh(n)) - (3 * ice_math_cosh(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_triple_tanh(double n) {
    return (((3 * ice_math_tanh(n)) + (ice_math_tanh(n) * ice_math_tanh(n) * ice_math_tanh(n))) / (1 + (3 * ice_math_tanh(n) * ice_math_tanh(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quadruple_sin(double n) {
    return ((4 * ice_math_sin(n) * ice_math_cos(n)) - ((8 * ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n)) * ice_math_cos(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quadruple_cos(double n) {
    return ((8 * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n)) - (8 * ice_math_cos(n) * ice_math_cos(n)) - 1);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quadruple_tan(double n) {
    return (((4 * ice_math_tan(n)) - (4 * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n))) / ((1 - (6 * ice_math_tan(n) * ice_math_tan(n))) + (ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quadruple_sinh(double n) {
    return (((8 * ice_math_sinh(n) * ice_math_sinh(n) * ice_math_sinh(n)) * ice_math_cosh(n)) + (4 * ice_math_sinh(n) * ice_math_cosh(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quadruple_cosh(double n) {
    return ((8 * ice_math_cosh(n) * ice_math_cosh(n) * ice_math_cosh(n) * ice_math_cosh(n)) - ((8 * ice_math_cosh(n) * ice_math_cosh(n)) + 1));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quadruple_tanh(double n) {
    return (((4 * ice_math_tanh(n)) + (4 * ice_math_tanh(n) * ice_math_tanh(n) * ice_math_tanh(n))) / (1 + (6 * ice_math_tanh(n) * ice_math_tanh(n)) + (ice_math_tanh(n) * ice_math_tanh(n) * ice_math_tanh(n) * ice_math_tanh(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quintuple_sin(double n) {
    return ((5 * ice_math_sin(n)) - (20 * ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n)) + (16 * ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quintuple_cos(double n) {
    return ((16 * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n)) - (20 * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n)) + (5 * ice_math_cos(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quintuple_tan(double n) {
    return (((ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n)) - (10 * ice_math_tan(n) * ice_math_tan(n)) + (5 * ice_math_tan(n))) / (1 - (10 * ice_math_tan(n) * ice_math_tan(n)) + (5 * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sextuple_sin(double n) {
    return ((6 * ice_math_sin(n) * ice_math_cos(n)) - ((32 * ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n)) + (32 * ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n) * ice_math_sin(n) * ice_math_cos(n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sextuple_cos(double n) {
    return ((32 * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n)) - (48 * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n) * ice_math_cos(n)) + (18 * ice_math_cos(n) * ice_math_cos(n)) - 1);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sextuple_tan(double n) {
    return (((6 * ice_math_tan(n)) - (20 * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n)) + (6 * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n))) / (1 - ((15 * ice_math_tan(n) * ice_math_tan(n)) + (15 * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n)) - (ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n) * ice_math_tan(n)))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acot(double n) {
    return ice_math_acos(n) / ice_math_asin(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asec(double n) {
    return 1 / ice_math_acos(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acsc(double n) {
    return 1 / ice_math_asin(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_mod(double a, double b) {
    double x = (a / b) * a;
    return (a - x);
}

ICE_MATH_API ice_math_bool ICE_MATH_CALLCONV ice_math_even(int n) {
    return (n % 2 == 0) ? ICE_MATH_TRUE : ICE_MATH_FALSE;
}

ICE_MATH_API ice_math_bool ICE_MATH_CALLCONV ice_math_odd(int n) {
    return (!(n % 2 == 0)) ? ICE_MATH_TRUE : ICE_MATH_FALSE;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_discriminant(double a, double b, double c) {
    return ((b * b) - (4 * a * c));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_trinomial(double a, double b) {
    if (a == 0 && b == 0) {
        return 1;
    } else if (b < -a || b > a) {
        return 0;
    } else {
        return (ice_math_trinomial(a - 1, b - 1) + ice_math_trinomial(a - 1, b) + ice_math_trinomial(a - 1, b + 1));
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_iter_log(double a, double b) {
    if (a > 1) {
        return 1 + ice_math_iter_log(ice_math_log(a) / ice_math_log(b), b);
    } else {
        return 0;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_avg(double a, double b, double c) {
    return (a * c + b) / (c + 1);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_birthday_paradox(double n) {
    return ice_math_ceil(ice_math_sqrt(2 * 365 * ice_math_log(1 / (1 - n))));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_parity(int n) {
    double p = 0;
    while (p) {
        p = (p == 0) ? 1 : 0;
        n = n & (n - 1);
    }
    return p;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_binceoff(double a, double b) {
    if (b > a) {
        return 0;
    } else if (a == 0 || b == 0) {
        return 0;
    } else {
        return ice_math_binceoff(a - 1, b - 1) + ice_math_binceoff(a - 1, b);
    }
}

ICE_MATH_API int ICE_MATH_CALLCONV ice_math_cassini(int n) {
    return (n & 1) ? -1 : 1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_leonardo(double n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return ice_math_leonardo(n - 1) + ice_math_leonardo(n - 2) + 1;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_double_fact(double n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * ice_math_double_fact(n - 2);
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_hexagonal(double n) {
    return n * (2 * n - 1);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_gcd(int a, int b) {
    if (a == 0) {
        return b;
    } else {
        return ice_math_gcd(b, a % b);
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_phi(double n) {
    double res = 1;
    
    for (int i = 2; i < n; i++) {
        if (ice_math_gcd(i, n) == 1) {
            res++;
        }
    }
    
    return res;
}

ICE_MATH_API ice_math_bool ICE_MATH_CALLCONV ice_math_sqrt_exist(int a, int b, int c) {
    a = a % b;
    
    for (int x = 2; x < b; x++) {
        if ((x * x) % b == c) {
            return ICE_MATH_TRUE;
        }
    }
    
    return ICE_MATH_FALSE;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_seq(double n) {
    if (n == 1 || n == 2) {
        return 1;
    } else {
        return ice_math_seq(ice_math_seq(n - 1)) + ice_math_seq(n - ice_math_seq(n - 1));
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_pairwise_sum(double n) {
   double sum = 0;
   
   for (int i = 1; i <= n; i++) {
     for (int j = i; j <= n; j++) {
        sum = sum + i * j;
     }
   }
   
   return sum;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_ncr(double a, double b) {
    return ice_math_fact(a) / (ice_math_fact(b) * ice_math_fact(a - b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_dyckpaths(double n) {
    int res = 1;
    
    for (int i = 0; i < n; ++i) {
        res *= (2 * n - i);
        res /= (i + 1);
    }
    
    return res / (n + 1);
}

ICE_MATH_API ice_math_bool ICE_MATH_CALLCONV ice_math_prime(int n) {
    if (n <= 1) {
        return ICE_MATH_FALSE;
    }
    
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return ICE_MATH_FALSE;
        }
    }
    
    return ICE_MATH_TRUE;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_rasphon(double n) {
    double x = (n * n * n - n * n + 2) / (3 * n * n - 2 * n);
    
    while (ice_math_abs(x) >= ICE_MATH_EPSILON) {
        x = (n * n * n - n * n + 2) / (3 * n * n - 2 * n);
        n = n - x;
    }
    
    return x;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_nth_group_sum(double n) {
    int cur = (n * (n - 1)) + 1;
    int sum = 0;
    
    while (n--) {
        sum += cur;
        cur += 2;
    }
  
    return sum;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_trajectory_time(double a, double b) {
    double x = 3 * b / 2;
    return a / x;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_catalan(double n) {
    if (n <= 1) {
        return 1;
    }
    
    int res = 0;
    
    for (int i = 0; i < n; i++) {
        res += ice_math_catalan(i) * ice_math_catalan(n - i - 1);
    }
    
    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_pad(double n) {
    int pPrevPrev = 1, pPrev = 1, pCurr = 1, pNext = 1;
  
    for (int i = 3; i <= n; i++) {
        pNext = pPrevPrev + pPrev;
        pPrevPrev = pPrev;
        pPrev = pCurr;
        pCurr = pNext;
    }
  
    return pNext;
}

ICE_MATH_API ice_math_bool ICE_MATH_CALLCONV ice_math_composite(int n) {
    if (n <= 1 || n <= 3) {
        return ICE_MATH_FALSE;
    } else if (n % 2 == 0 || n % 3 == 0) {
        return ICE_MATH_TRUE;
    } else {
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return ICE_MATH_TRUE;
            }
        }
        
        return ICE_MATH_FALSE;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_nth_prime_factor(int a, int b) {
    
    while (a % 2 == 0) {
        b--;
        a = a / 2;
        if (b == 0) {
          return 2;
        }
    }
    
    for (int i = 3; i <= ice_math_sqrt(a); i += 2) {
        while (a % i == 0) {
            if (b == 1) {
              return i;
            }
 
            b--;
            a /= i;
        }
    }
    
    if (a > 2 && b == 1) {
        return a;
    } else {
        return -1;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_moser_seq(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else if (n % 2 == 0) {
        return 4 * ice_math_moser_seq(n / 2);
    } else if (n % 2 == 1) {
        return 4 * ice_math_moser_seq(n / 2) + 1;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_lrotate(int a, int b, int bits) {
    return (a << b) | (a >> (32 - b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_rrotate(int a, int b, int bits) {
    return (a >> b) | (a << (32 - b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_politness(int n) {
    int result = 1;
    
    while (n % 2 == 0) {
        n /= 2;
    }
    
    for (int i = 3; i * i <= n; i += 2) {
        int divCount = 0;
        
        while (n % i == 0) {
            n /= i;
            ++divCount;
        }
 
        result *= divCount + 1;
    }
    
    if (n > 2) {
        result *= 2;
    }
    
    return result - 1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_multi_order(int a, int b) {
    if (ice_math_gcd(a, b) != 1) {
        return -1;
    }

    int result = 1;

    double x = 1;
    while (x < b) {

        result = (result * a) % b;

        if (result == 1) {
            return x;
        }

        x++;
    }

    return -1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_find_nth(double n) {
    double count = 0;
 
    for (int curr = 1;; curr++) {
        double sum = 0;
        
        for (int x = curr; x > 0; x /= 10) {
            sum = sum + x % 10;
        }
        
        if (sum == 10) {
            count++;
        }
        
        if (count == n) {
            return curr;
        }
    }
    
    return -1;
}

ICE_MATH_API int ICE_MATH_CALLCONV ice_math_perfect_square_min_number(int n) {
    int count = 0, ans = 1;
    
    while (n % 2 == 0) {
        count++;
        n /= 2;
    }
    
    if (count % 2) {
        ans *= 2;
    }
 
    for (int i = 3; i <= ice_math_sqrt(n); i += 2) {
        count = 0;
        
        while (n % i == 0) {
            count++;
            n /= i;
        }
        
        if (count % 2) {
            ans *= i;
        }
    }
 
    if (n > 2) {
        ans *= n;
    }
    
    return ans;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sum(int n) {
    double result = 0;
    
    for (int i = 2; i <= ice_math_sqrt(n); i++) {
        if (n % i == 0) {
            if (i == (n / i)) {
                result += i;
            } else {
                result += (i + n / i);
            }
        }
    }
    
    return (result + 1);
}

ICE_MATH_API ice_math_bool ICE_MATH_CALLCONV ice_math_amicable(double a, double b) {
    if (ice_math_sum(a) != b) {
       return ICE_MATH_FALSE;
    }
    
    return (ice_math_sum(b) == a) ? ICE_MATH_TRUE : ICE_MATH_FALSE;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_bisection(double a, double b) {
    if ((a * a * a - a * a + 2) * (b * b * b - b * b + 2) >= 0) {
        return 0;
    } else {
        double c = a;
        
        while ((b - a) >= ICE_MATH_EPSILON) {
            c = (a + b) / 2;
            
            if ((c * c * c - c * c + 2) == 0) {
                break;
            } else if ((c * c * c - c * c + 2) * (a * a * a - a * a + 2) < 0) {
                b = c;
            } else {
                a = c;
            }
        }
        
        return c;
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fermat(double n) {
    double p = ice_math_pow(2, n);
    return ice_math_pow(2, p) + 1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_exact_prime_factor_count(double n) {
    return ice_math_round(ice_math_log(ice_math_log(n)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_abundance(double n) {
    return ice_math_sum(n) - n;
}

ICE_MATH_API ice_math_bool ICE_MATH_CALLCONV ice_math_abundant(double n) {
    return (ice_math_sum(n) > n) ? ICE_MATH_TRUE : ICE_MATH_FALSE;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_frexp(double n) {
    double exp = (n == 0) ? 0 : (1 + ice_math_logb(n));
    return ice_math_scalbn(n, -exp);
}

// https://rosettacode.org/wiki/Gamma_function#C
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_gamma(double n) {
    const int a = 12;
    static double c_space[12];
    static double *c = NULL;
    int k;
    double accm;
 
    if (c == NULL) {
        double k1_factrl = 1; /* (k - 1)!*(-1)^k with 0!==1*/
        c = c_space;
        c[0] = ice_math_sqrt(2 * ICE_MATH_PI);
        
        for(k = 1; k < a; k++) {
            c[k] = ice_math_exp(a - k) * ice_math_pow(a - k, k - 0.5) / k1_factrl;
            k1_factrl *= -k;
        }
    }
    
    accm = c[0];
    
    for (k = 1; k < a; k++) {
        accm += c[k] / (n + k);
    }

    accm *= ice_math_exp(-(n + a)) * ice_math_pow(n + a, n + 0.5); /* Gamma(z+1) */
    return accm / n;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_clamp(double value, double min, double max) {
    double res = value < min ? min : value;
    return res > max ? max : res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_lerp(double start, double end, double amount) {
    return start + amount * (end - start);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_norm(double value, double start, double end) {
    return (value - start) / (end - start);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_remap(double value, double in_start, double in_end, double out_start, double out_end) {
    return (value - in_start) / (in_end - in_start) * (out_end - out_start) + out_start;
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_zero(void) {
    return (ice_math_vec2) { 0, 0 };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_one(void) {
    return (ice_math_vec2) { 1, 1 };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_neg(ice_math_vec2 v) {
    return (ice_math_vec2) { -v.x, -v.y };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_reflect(ice_math_vec2 v1, ice_math_vec2 v2) {
    ice_math_vec2 result = { 0 };

    double dotp = ice_math_vec2_dot_product(v1, v2);

    result.x = v1.x - (2 * v2.x) * dotp;
    result.y = v1.y - (2 * v2.y) * dotp;

    return result;
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_add(ice_math_vec2 v1, ice_math_vec2 v2) {
    return (ice_math_vec2) { v1.x + v2.x, v1.y + v2.y };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_add_num(ice_math_vec2 v, double n) {
    return (ice_math_vec2) { v.x + n, v.y + n };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_sub(ice_math_vec2 v1, ice_math_vec2 v2) {
    return (ice_math_vec2) { v1.x - v2.x, v1.y - v2.y };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_sub_num(ice_math_vec2 v, double n) {
    return (ice_math_vec2) { v.x - n, v.y - n };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_mult(ice_math_vec2 v1, ice_math_vec2 v2) {
    return (ice_math_vec2) { v1.x * v2.x, v1.y * v2.y };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_div(ice_math_vec2 v1, ice_math_vec2 v2) {
    return (ice_math_vec2) { v1.x / v2.x, v1.y / v2.y };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_scale(ice_math_vec2 v, double scale) {
    return (ice_math_vec2) { v.x * scale, v.y * scale };
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec2_dot_product(ice_math_vec2 v1, ice_math_vec2 v2) {
    return (v1.x * v2.x + v1.y * v2.y);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec2_cross_product(ice_math_vec2 v1, ice_math_vec2 v2) {
    return (v1.x * v2.y) - (v1.y * v2.x);
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_lerp(ice_math_vec2 v1, ice_math_vec2 v2, double x) {
    return (ice_math_vec2) {
        v1.x + x * (v2.x - v1.x),
        v1.y + x * (v2.y - v1.y)
    };
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_norm(ice_math_vec2 v) {
    return ice_math_vec2_scale(v, 1 / ice_math_vec2_len(v));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec2_len(ice_math_vec2 v) {
    return ice_math_sqrt((v.x * v.x) + (v.y * v.y));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec2_len_sqr(ice_math_vec2 v) {
    return ((v.x * v.x) + (v.y * v.y));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec2_angle(ice_math_vec2 v1, ice_math_vec2 v2) {
    double result = ice_math_atan2(v2.y - v1.y, v2.x - v1.x) * (180 / ICE_MATH_PI);
    if (result < 0) result += 360;
    return result;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec2_dist(ice_math_vec2 v1, ice_math_vec2 v2) {
    return ice_math_sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_rotate(ice_math_vec2 v, double n) {
    double rads = ice_math_rad(n);
    
    ice_math_vec2 result = (ice_math_vec2) {
        v.x * ice_math_cos(rads) - v.y * ice_math_sin(rads),
        v.x * ice_math_sin(rads) + v.y * ice_math_cos(rads)
    };
    
    return result;
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_move_towards(ice_math_vec2 v1, ice_math_vec2 v2, double max_dist) {
    ice_math_vec2 result = { 0 };
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;
    double value = (dx * dx) + (dy * dy);

    if ((value == 0) || ((max_dist >= 0) && (value <= max_dist * max_dist))) result = v2;

    double dist = ice_math_sqrt(value);

    result.x = v1.x + dx / dist * max_dist;
    result.y = v1.y + dy / dist * max_dist;

    return result;
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_min(ice_math_vec2 v1, ice_math_vec2 v2) {
    ice_math_vec2 result = { 0 };

    result.x = ice_math_min(v1.x, v2.x);
    result.y = ice_math_min(v1.y, v2.y);

    return result;
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_vec2_max(ice_math_vec2 v1, ice_math_vec2 v2) {
    ice_math_vec2 result = { 0 };

    result.x = ice_math_max(v1.x, v2.x);
    result.y = ice_math_max(v1.y, v2.y);

    return result;
}


ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_zero(void) {
    return (ice_math_vec3) { 0, 0, 0 };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_one(void) {
    return (ice_math_vec3) { 1, 1, 1 };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_neg(ice_math_vec3 v) {
    return (ice_math_vec3) { -v.x, -v.y, -v.z };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_add(ice_math_vec3 v1, ice_math_vec3 v2) {
    return (ice_math_vec3) { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_add_num(ice_math_vec3 v, double n) {
    return (ice_math_vec3) { v.x + n, v.y + n, v.z + n };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_sub(ice_math_vec3 v1, ice_math_vec3 v2) {
    return (ice_math_vec3) { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_sub_num(ice_math_vec3 v, double n) {
    return (ice_math_vec3) { v.x - n, v.y - n, v.z - n };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_mult(ice_math_vec3 v1, ice_math_vec3 v2) {
    return (ice_math_vec3) { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_div(ice_math_vec3 v1, ice_math_vec3 v2) {
    return (ice_math_vec3) { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_scale(ice_math_vec3 v, double scale) {
    return (ice_math_vec3) { v.x * scale, v.y * scale, v.z * scale };
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec3_dot_product(ice_math_vec3 v1, ice_math_vec3 v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_cross_product(ice_math_vec3 v1, ice_math_vec3 v2) {
    return (ice_math_vec3) { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_triple_product(ice_math_vec3 v1, ice_math_vec3 v2) {
    ice_math_vec3 result = { 0 };
    
    result.x = (v1.y * v2.z) - (v1.z * v2.y);
    result.y = (v1.z * v2.x) - (v1.x * v2.z);
    result.z = (v1.x * v2.y) - (v1.y * v2.x);
    
    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_lerp(ice_math_vec3 v1, ice_math_vec3 v2, double x) {
    return (ice_math_vec3) {
        v1.x + x * (v2.x - v1.x),
        v1.y + x * (v2.y - v1.y),
        v1.z + x * (v2.z - v1.z)
    };
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_norm(ice_math_vec3 v) {
    ice_math_vec3 result = v;

    double length, ilength;
    length = ice_math_vec3_len(v);
    if (length == 0) length = 1;
    ilength = 1 / length;

    result.x *= ilength;
    result.y *= ilength;
    result.z *= ilength;

    return result;
}

ICE_MATH_API void ICE_MATH_CALLCONV ice_math_vec3_ortho_norm(ice_math_vec3* v1, ice_math_vec3* v2) {
    *v1 = ice_math_vec3_norm(*v1);
    ice_math_vec3 vn = ice_math_vec3_cross_product(*v1, *v2);
    vn = ice_math_vec3_norm(vn);
    *v2 = ice_math_vec3_cross_product(vn, *v1);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec3_len(ice_math_vec3 v) {
    return ice_math_sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec3_len_sqr(ice_math_vec3 v) {
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec3_dist(ice_math_vec3 v1, ice_math_vec3 v2) {
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;
    double dz = v2.z - v1.z;
    double result = ice_math_sqrt(dx * dx + dy * dy + dz * dz);
    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_perpendicular(ice_math_vec3 v) {
    ice_math_vec3 result = { 0 };

    double min = ice_math_abs(v.x);
    ice_math_vec3 cardinalAxis = { 1, 0, 0 };

    if (ice_math_abs(v.y) < min) {
        min = ice_math_abs(v.y);
        ice_math_vec3 tmp = { 0, 1, 0 };
        cardinalAxis = tmp;
    }

    if (ice_math_abs(v.z) < min) {
        ice_math_vec3 tmp = { 0, 0, 1 };
        cardinalAxis = tmp;
    }

    result = ice_math_vec3_cross_product(v, cardinalAxis);

    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_transform(ice_math_vec3 v, ice_math_mat m) {
    ice_math_vec3 result = { 0 };
    double x = v.x;
    double y = v.y;
    double z = v.z;

    result.x = m.m0 * x + m.m4 * y + m.m8  * z + m.m12;
    result.y = m.m1 * x + m.m5 * y + m.m9  * z + m.m13;
    result.z = m.m2 * x + m.m6 * y + m.m10 * z + m.m14;
    
    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_rotate_by_quat(ice_math_vec3 v, ice_math_quat q) {
    ice_math_vec3 result = { 0 };

    result.x = v.x * (q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z) + v.y * (2 * q.x * q.y - 2 * q.w * q.z) + v.z * (2 * q.x * q.z + 2 * q.w * q.y);
    result.y = v.x * (2 * q.w * q.z + 2 * q.x * q.y) + v.y * (q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z) + v.z * (-2 * q.w * q.x + 2 * q.y * q.z);
    result.z = v.x * (-2 * q.w * q.y + 2 * q.x * q.z) + v.y * (2 * q.w * q.x + 2 * q.y * q.z) + v.z * (q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z);
    
    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_reflect(ice_math_vec3 v1, ice_math_vec3 v2) {
    ice_math_vec3 result = { 0 };

    double dotProduct = ice_math_vec3_dot_product(v1, v2);

    result.x = v1.x - (2 * v2.x) * dotProduct;
    result.y = v1.y - (2 * v2.y) * dotProduct;
    result.z = v1.z - (2 * v2.z) * dotProduct;

    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_min(ice_math_vec3 v1, ice_math_vec3 v2) {
    ice_math_vec3 result = { 0 };

    result.x = ice_math_min(v1.x, v2.x);
    result.y = ice_math_min(v1.y, v2.y);
    result.z = ice_math_min(v1.z, v2.z);

    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_max(ice_math_vec3 v1, ice_math_vec3 v2) {
    ice_math_vec3 result = { 0 };

    result.x = ice_math_max(v1.x, v2.x);
    result.y = ice_math_max(v1.y, v2.y);
    result.z = ice_math_max(v1.z, v2.z);

    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_barycenter(ice_math_vec3 p, ice_math_vec3 a, ice_math_vec3 b, ice_math_vec3 c) {
    ice_math_vec3 v0 = ice_math_vec3_sub(b, a);
    ice_math_vec3 v1 = ice_math_vec3_sub(c, a);
    ice_math_vec3 v2 = ice_math_vec3_sub(p, a);
    double d00 = ice_math_vec3_dot_product(v0, v0);
    double d01 = ice_math_vec3_dot_product(v0, v1);
    double d11 = ice_math_vec3_dot_product(v1, v1);
    double d20 = ice_math_vec3_dot_product(v2, v0);
    double d21 = ice_math_vec3_dot_product(v2, v1);

    double denom = d00 * d11 - d01 * d01;

    ice_math_vec3 result = { 0 };

    result.y = (d11 * d20 - d01 * d21) / denom;
    result.z = (d00 * d21 - d01 * d20) / denom;
    result.x = 1 - (result.z + result.y);

    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_vec3_unproj(ice_math_vec3 source, ice_math_mat projection, ice_math_mat view) {
    ice_math_vec3 result = { 0, 0, 1 };
    
    ice_math_mat matViewProj = ice_math_mat_mult(view, projection);
    matViewProj = ice_math_mat_inv(matViewProj);
    
    ice_math_quat quat = { source.x, source.y, source.z, 1 };
    
    quat = ice_math_quat_transform(quat, matViewProj);
    
    result.x = quat.x / quat.w;
    result.y = quat.y / quat.w;
    result.z = quat.z / quat.w;

    return result;
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_zero(void) {
    return (ice_math_vec4) { 0, 0, 0, 0 };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_one(void) {
    return (ice_math_vec4) { 1, 1, 1, 1 };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_neg(ice_math_vec4 v) {
    return (ice_math_vec4) { -v.x, -v.y, -v.z, -v.w };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_add(ice_math_vec4 v1, ice_math_vec4 v2) {
    return (ice_math_vec4) {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z,
        v1.w + v2.w
    };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_add_num(ice_math_vec4 v, double n) {
    return (ice_math_vec4) {
        v.x + n,
        v.y + n,
        v.z + n,
        v.w + n
    };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_sub(ice_math_vec4 v1, ice_math_vec4 v2) {
    return (ice_math_vec4) {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z,
        v1.w - v2.w
    };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_sub_num(ice_math_vec4 v, double n) {
    return (ice_math_vec4) {
        v.x - n,
        v.y - n,
        v.z - n,
        v.w - n
    };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_mult(ice_math_vec4 v1, ice_math_vec4 v2) {
    return (ice_math_vec4) {
        v1.x * v2.x,
        v1.y * v2.y,
        v1.z * v2.z,
        v1.w * v2.w
    };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_div(ice_math_vec4 v1, ice_math_vec4 v2) {
    return (ice_math_vec4) {
        v1.x / v2.x,
        v1.y / v2.y,
        v1.z / v2.z,
        v1.w / v2.w
    };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_scale(ice_math_vec4 v, double scale) {
    return (ice_math_vec4) {
        v.x * scale,
        v.y * scale,
        v.z * scale,
        v.w * scale
    };
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec4_dot_product(ice_math_vec4 v1, ice_math_vec4 v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_lerp(ice_math_vec4 v1, ice_math_vec4 v2, double x) {
    return (ice_math_vec4) {
        v1.x + x * (v2.x - v1.x),
        v1.y + x * (v2.y - v1.y),
        v1.z + x * (v2.z - v1.z),
        v1.w + x * (v2.w - v1.w)
    };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_norm(ice_math_vec4 v) {
    ice_math_vec4 result = v;

    double length, ilength;
    length = ice_math_vec4_len(v);
    if (length == 0) length = 1;
    ilength = 1 / length;

    result.x *= ilength;
    result.y *= ilength;
    result.z *= ilength;
    result.w *= ilength;

    return result;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec4_len(ice_math_vec4 v) {
    return ice_math_sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec4_len_sqr(ice_math_vec4 v) {
    return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_vec4_dist(ice_math_vec4 v1, ice_math_vec4 v2) {
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;
    double dz = v2.z - v1.z;
    double dw = v2.w - v1.w;
    double result = ice_math_sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
    return result;
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_min(ice_math_vec4 v1, ice_math_vec4 v2) {
    ice_math_vec4 result = { 0 };

    result.x = ice_math_min(v1.x, v2.x);
    result.y = ice_math_min(v1.y, v2.y);
    result.z = ice_math_min(v1.z, v2.z);
    result.w = ice_math_min(v1.w, v2.w);
    
    return result;
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_vec4_max(ice_math_vec4 v1, ice_math_vec4 v2) {
    ice_math_vec4 result = { 0 };

    result.x = ice_math_max(v1.x, v2.x);
    result.y = ice_math_max(v1.y, v2.y);
    result.z = ice_math_max(v1.z, v2.z);
    result.w = ice_math_max(v1.w, v2.w);

    return result;
}

// Quaternions
ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_add(ice_math_quat q1, ice_math_quat q2) {
    return (ice_math_quat) { q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w };
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_add_num(ice_math_quat q, double n) {
    return (ice_math_quat) { q.x + n, q.y + n, q.z + n, q.w + n };
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_sub(ice_math_quat q1, ice_math_quat q2) {
    return (ice_math_quat) { q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w };
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_sub_num(ice_math_quat q, double n) {
    return (ice_math_quat) { q.x - n, q.y - n, q.z - n, q.w - n };
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_identity(void) {
    return (ice_math_quat) { 0, 0, 0, 1 };
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quat_len(ice_math_quat q) {
    return ice_math_sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quat_len_sqr(ice_math_quat q) {
    return (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_norm(ice_math_quat q) {
    ice_math_quat result = { 0 };

    double length, ilength;
    length = ice_math_quat_len(q);
    if (length == 0) length = 1;
    ilength = 1 / length;

    result.x = q.x * ilength;
    result.y = q.y * ilength;
    result.z = q.z * ilength;
    result.w = q.w * ilength;

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_inv(ice_math_quat q) {
    ice_math_quat result = q;
    double length = ice_math_quat_len(q);
    double lengthSq = length * length;

    if (lengthSq != 0.0)
    {
        double i = 1 / lengthSq;

        result.x *= -i;
        result.y *= -i;
        result.z *= -i;
        result.w *= i;
    }

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_mult(ice_math_quat q1, ice_math_quat q2) {
    ice_math_quat result = { 0 };

    double qax = q1.x, qay = q1.y, qaz = q1.z, qaw = q1.w;
    double qbx = q2.x, qby = q2.y, qbz = q2.z, qbw = q2.w;

    result.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
    result.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
    result.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
    result.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_scale(ice_math_quat q, double n) {
    ice_math_quat result = { 0 };

    double qax = q.x, qay = q.y, qaz = q.z, qaw = q.w;

    result.x = qax * n + qaw * n + qay * n - qaz * n;
    result.y = qay * n + qaw * n + qaz * n - qax * n;
    result.z = qaz * n + qaw * n + qax * n - qay * n;
    result.w = qaw * n - qax * n - qay * n - qaz * n;

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_div(ice_math_quat q1, ice_math_quat q2) {
    return (ice_math_quat) { q1.x / q2.x, q1.y / q2.y, q1.z / q2.z, q1.w / q2.w };
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_lerp(ice_math_quat q1, ice_math_quat q2, double n) {
    ice_math_quat result = { 0 };

    result.x = q1.x + n * (q2.x - q1.x);
    result.y = q1.y + n * (q2.y - q1.y);
    result.z = q1.z + n * (q2.z - q1.z);
    result.w = q1.w + n * (q2.w - q1.w);

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_nlerp(ice_math_quat q1, ice_math_quat q2, double n) {
    ice_math_quat result = ice_math_quat_lerp(q1, q2, n);
    result = ice_math_quat_norm(result);

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_slerp(ice_math_quat q1, ice_math_quat q2, double n) {
    ice_math_quat result = { 0 };

    double cosHalfTheta =  q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

    if (ice_math_abs(cosHalfTheta) >= 1) result = q1;
    else if (cosHalfTheta > 0.95) result = ice_math_quat_nlerp(q1, q2, n);
    else
    {
        double halfTheta = ice_math_acos(cosHalfTheta);
        double sinHalfTheta = ice_math_sqrt(1 - cosHalfTheta * cosHalfTheta);

        if (ice_math_abs(sinHalfTheta) < 0.001)
        {
            result.x = (q1.x * 0.5 + q2.x * 0.5);
            result.y = (q1.y * 0.5 + q2.y * 0.5);
            result.z = (q1.z * 0.5 + q2.z * 0.5);
            result.w = (q1.w * 0.5 + q2.w * 0.5);
        }
        else
        {
            double ratioA = ice_math_sin((1 - n) * halfTheta) / sinHalfTheta;
            double ratioB = ice_math_sin(n * halfTheta) / sinHalfTheta;

            result.x = (q1.x * ratioA + q2.x * ratioB);
            result.y = (q1.y * ratioA + q2.y * ratioB);
            result.z = (q1.z * ratioA + q2.z * ratioB);
            result.w = (q1.w * ratioA + q2.w * ratioB);
        }
    }

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_from_vec3_to_vec3(ice_math_vec3 from, ice_math_vec3 to) {
    ice_math_quat result = { 0 };

    double cos2Theta = ice_math_vec3_dot_product(from, to);
    ice_math_vec3 cross = ice_math_vec3_cross_product(from, to);

    result.x = cross.x;
    result.y = cross.y;
    result.z = cross.z;
    result.w = 1 + cos2Theta;
    
    result = ice_math_quat_norm(result);

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_from_mat(ice_math_mat m) {
    ice_math_quat result = { 0 };

    if ((m.m0 > m.m5) && (m.m0 > m.m10))
    {
        double s = ice_math_sqrt(1 + m.m0 - m.m5 - m.m10) * 2;

        result.x = 0.25 * s;
        result.y = (m.m4 + m.m1) / s;
        result.z = (m.m2 + m.m8) / s;
        result.w = (m.m9 - m.m6) / s;
    }
    else if (m.m5 > m.m10)
    {
        double s = ice_math_sqrt(1 + m.m5 - m.m0 - m.m10) * 2;
        
        result.x = (m.m4 + m.m1) / s;
        result.y = 0.25 * s;
        result.z = (m.m9 + m.m6) / s;
        result.w = (m.m2 - m.m8) / s;
    }
    else
    {
        double s  = ice_math_sqrt(1 + m.m10 - m.m0 - m.m5) * 2;
        
        result.x = (m.m2 + m.m8) / s;
        result.y = (m.m9 + m.m6) / s;
        result.z = 0.25 * s;
        result.w = (m.m4 - m.m1) / s;
    }

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_quat_to_mat(ice_math_quat q) {
    ice_math_mat result = ice_math_mat_identity();

    double a2 = 2 * (q.x * q.x), b2 = 2 * (q.y * q.y), c2 = 2 * (q.z * q.z);
    double ab = 2 * (q.x * q.y), ac = 2 * (q.x * q.z), bc = 2 * (q.y * q.z);
    double ad = 2 * (q.x * q.w), bd = 2 * (q.y * q.w), cd = 2 * (q.z * q.w);

    result.m0 = 1 - b2 - c2;
    result.m1 = ab - cd;
    result.m2 = ac + bd;

    result.m4 = ab + cd;
    result.m5 = 1 - a2 - c2;
    result.m6 = bc - ad;

    result.m8 = ac - bd;
    result.m9 = bc + ad;
    result.m10 = 1 - a2 - b2;

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_from_axis_angle(ice_math_vec3 axis, double angle) {
    ice_math_quat result = { 0, 0, 0, 1 };

    if (ice_math_vec3_len(axis) != 0)

    angle *= 0.5;

    axis = ice_math_vec3_norm(axis);

    double sinres = ice_math_sin(angle);
    double cosres = ice_math_cos(angle);

    result.x = axis.x * sinres;
    result.y = axis.y * sinres;
    result.z = axis.z * sinres;
    result.w = cosres;

    result = ice_math_quat_norm(result);

    return result;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_quat_from_quat_to_angle(ice_math_quat q) {
    if (ice_math_abs(q.w) > 1) q = ice_math_quat_norm(q);
    return 2 * ice_math_acos(q.w);
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_quat_from_quat_to_axis(ice_math_quat q) {
    ice_math_vec3 axis = { 0 };
    
    if (ice_math_abs(q.w) > 1) q = ice_math_quat_norm(q);
    double den = ice_math_sqrt(1 - q.w * q.w);
    
    if (den > 0.0001)
    {
        axis.x = q.x / den;
        axis.y = q.y / den;
        axis.z = q.z / den;
    }
    else
    {
        axis.x = 1;
    }
    
    return axis;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_from_euler(double roll, double pitch, double yaw) {
    ice_math_quat q = { 0 };

    double x0 = ice_math_cos(roll * 0.5);
    double x1 = ice_math_sin(roll * 0.5);
    double y0 = ice_math_cos(pitch * 0.5);
    double y1 = ice_math_sin(pitch * 0.5);
    double z0 = ice_math_cos(yaw * 0.5);
    double z1 = ice_math_sin(yaw * 0.5);

    q.x = x1 * y0 * z0 - x0 * y1 * z1;
    q.y = x0 * y1 * z0 + x1 * y0 * z1;
    q.z = x0 * y0 * z1 - x1 * y1 * z0;
    q.w = x0 * y0 * z0 + x1 * y1 * z1;

    return q;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_quat_to_euler(ice_math_quat q) {
    ice_math_vec3 result = { 0 };
    
    double x0 = 2 * (q.w * q.x + q.y * q.z);
    double x1 = 1 - 2 * (q.x * q.x + q.y * q.y);
    result.x = ice_math_deg(ice_math_atan2(x0, x1));
    
    double y0 = 2 * (q.w * q.y - q.z * q.x);
    y0 = y0 > 1 ? 1 : y0;
    y0 = y0 < -1 ? -1 : y0;
    result.y = ice_math_deg(ice_math_asin(y0));

    double z0 = 2 * (q.w * q.z + q.x * q.y);
    double z1 = 1 - 2 * (q.y * q.y + q.z * q.z);
    result.z = ice_math_deg(ice_math_atan2(z0, z1));

    return result;
}

ICE_MATH_API ice_math_quat ICE_MATH_CALLCONV ice_math_quat_transform(ice_math_quat q, ice_math_mat m) {
    ice_math_quat result = { 0 };

    result.x = m.m0 * q.x + m.m4 * q.y + m.m8  * q.z + m.m12 * q.w;
    result.y = m.m1 * q.x + m.m5 * q.y + m.m9  * q.z + m.m13 * q.w;
    result.z = m.m2 * q.x + m.m6 * q.y + m.m10 * q.z + m.m14 * q.w;
    result.w = m.m3 * q.x + m.m7 * q.y + m.m11 * q.z + m.m15 * q.w;

    return result;
}


// Matrices
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_mat_determinant(ice_math_mat m) {
    double a00 = m.m0, a01 = m.m1, a02 = m.m2, a03 = m.m3;
    double a10 = m.m4, a11 = m.m5, a12 = m.m6, a13 = m.m7;
    double a20 = m.m8, a21 = m.m9, a22 = m.m10, a23 = m.m11;
    double a30 = m.m12, a31 = m.m13, a32 = m.m14, a33 = m.m15;

    double result = a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03 +
                   a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 +
                   a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
                   a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23 +
                   a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 +
                   a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;

    return result;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_mat_trace(ice_math_mat m) {
    return (m.m0 + m.m5 + m.m10 + m.m15);
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_transpose(ice_math_mat m) {
    ice_math_mat result = { 0 };

    result.m0 = m.m0;
    result.m1 = m.m4;
    result.m2 = m.m8;
    result.m3 = m.m12;
    result.m4 = m.m1;
    result.m5 = m.m5;
    result.m6 = m.m9;
    result.m7 = m.m13;
    result.m8 = m.m2;
    result.m9 = m.m6;
    result.m10 = m.m10;
    result.m11 = m.m14;
    result.m12 = m.m3;
    result.m13 = m.m7;
    result.m14 = m.m11;
    result.m15 = m.m15;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_inv(ice_math_mat m) {
    ice_math_mat result = { 0 };
    
    double a00 = m.m0, a01 = m.m1, a02 = m.m2, a03 = m.m3;
    double a10 = m.m4, a11 = m.m5, a12 = m.m6, a13 = m.m7;
    double a20 = m.m8, a21 = m.m9, a22 = m.m10, a23 = m.m11;
    double a30 = m.m12, a31 = m.m13, a32 = m.m14, a33 = m.m15;

    double b00 = a00 * a11 - a01 * a10;
    double b01 = a00 * a12 - a02 * a10;
    double b02 = a00 * a13 - a03 * a10;
    double b03 = a01 * a12 - a02 * a11;
    double b04 = a01 * a13 - a03 * a11;
    double b05 = a02 * a13 - a03 * a12;
    double b06 = a20 * a31 - a21 * a30;
    double b07 = a20 * a32 - a22 * a30;
    double b08 = a20 * a33 - a23 * a30;
    double b09 = a21 * a32 - a22 * a31;
    double b10 = a21 * a33 - a23 * a31;
    double b11 = a22 * a33 - a23 * a32;
    
    double invDet = 1 / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

    result.m0 = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
    result.m1 = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
    result.m2 = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
    result.m3 = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
    result.m4 = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
    result.m5 = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
    result.m6 = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
    result.m7 = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
    result.m8 = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
    result.m9 = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
    result.m10 = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
    result.m11 = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
    result.m12 = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
    result.m13 = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
    result.m14 = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
    result.m15 = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_norm(ice_math_mat m) {
    ice_math_mat result = { 0 };
    double det = ice_math_mat_determinant(m);

    result.m0 = m.m0 / det;
    result.m1 = m.m1 / det;
    result.m2 = m.m2 / det;
    result.m3 = m.m3 / det;
    result.m4 = m.m4 / det;
    result.m5 = m.m5 / det;
    result.m6 = m.m6 / det;
    result.m7 = m.m7 / det;
    result.m8 = m.m8 / det;
    result.m9 = m.m9 / det;
    result.m10 = m.m10 / det;
    result.m11 = m.m11 / det;
    result.m12 = m.m12 / det;
    result.m13 = m.m13 / det;
    result.m14 = m.m14 / det;
    result.m15 = m.m15 / det;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_identity(void) {
    return (ice_math_mat) { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_add(ice_math_mat left, ice_math_mat right) {
    ice_math_mat result = ice_math_mat_identity();

    result.m0 = left.m0 + right.m0;
    result.m1 = left.m1 + right.m1;
    result.m2 = left.m2 + right.m2;
    result.m3 = left.m3 + right.m3;
    result.m4 = left.m4 + right.m4;
    result.m5 = left.m5 + right.m5;
    result.m6 = left.m6 + right.m6;
    result.m7 = left.m7 + right.m7;
    result.m8 = left.m8 + right.m8;
    result.m9 = left.m9 + right.m9;
    result.m10 = left.m10 + right.m10;
    result.m11 = left.m11 + right.m11;
    result.m12 = left.m12 + right.m12;
    result.m13 = left.m13 + right.m13;
    result.m14 = left.m14 + right.m14;
    result.m15 = left.m15 + right.m15;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_sub(ice_math_mat left, ice_math_mat right) {
    ice_math_mat result = ice_math_mat_identity();

    result.m0 = left.m0 - right.m0;
    result.m1 = left.m1 - right.m1;
    result.m2 = left.m2 - right.m2;
    result.m3 = left.m3 - right.m3;
    result.m4 = left.m4 - right.m4;
    result.m5 = left.m5 - right.m5;
    result.m6 = left.m6 - right.m6;
    result.m7 = left.m7 - right.m7;
    result.m8 = left.m8 - right.m8;
    result.m9 = left.m9 - right.m9;
    result.m10 = left.m10 - right.m10;
    result.m11 = left.m11 - right.m11;
    result.m12 = left.m12 - right.m12;
    result.m13 = left.m13 - right.m13;
    result.m14 = left.m14 - right.m14;
    result.m15 = left.m15 - right.m15;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_translate(double x, double y, double z) {
    return (ice_math_mat) {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_rotate(ice_math_vec3 axis, double angle) {
    ice_math_mat result = { 0 };

    double x = axis.x, y = axis.y, z = axis.z;
    double length = ice_math_sqrt(x * x + y * y + z * z);

    if ((length != 1) && (length != 0))
    {
        length = 1 / length;
        x *= length;
        y *= length;
        z *= length;
    }

    double sinres = ice_math_sin(angle);
    double cosres = ice_math_cos(angle);
    double t = 1 - cosres;

    result.m0  = x * x * t + cosres;
    result.m1  = y * x * t + z * sinres;
    result.m2  = z * x * t - y * sinres;
    result.m3  = 0;

    result.m4  = x * y * t - z * sinres;
    result.m5  = y * y * t + cosres;
    result.m6  = z * y * t + x * sinres;
    result.m7  = 0;

    result.m8  = x * z * t + y * sinres;
    result.m9  = y * z * t - x * sinres;
    result.m10 = z * z * t + cosres;
    result.m11 = 0;

    result.m12 = 0;
    result.m13 = 0;
    result.m14 = 0;
    result.m15 = 1;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_rotate_xyz(ice_math_vec3 ang) {
    ice_math_mat result = ice_math_mat_identity();

    double cosz = ice_math_cos(-ang.z);
    double sinz = ice_math_sin(-ang.z);
    double cosy = ice_math_cos(-ang.y);
    double siny = ice_math_sin(-ang.y);
    double cosx = ice_math_cos(-ang.x);
    double sinx = ice_math_sin(-ang.x);

    result.m0 = cosz * cosy;
    result.m4 = (cosz * siny * sinx) - (sinz * cosx);
    result.m8 = (cosz * siny * cosx) + (sinz * sinx);

    result.m1 = sinz * cosy;
    result.m5 = (sinz * siny * sinx) + (cosz * cosx);
    result.m9 = (sinz * siny * cosx) - (cosz * sinx);

    result.m2 = -siny;
    result.m6 = cosy * sinx;
    result.m10 = cosy * cosx;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_rotate_zyx(ice_math_vec3 ang) {
    ice_math_mat result = ice_math_mat_rotate_z(ang.z);
    result = ice_math_mat_mult(result, ice_math_mat_rotate_y(ang.y));
    result = ice_math_mat_mult(result, ice_math_mat_rotate_x(ang.x));

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_rotate_x(double ang) {
    ice_math_mat result = ice_math_mat_identity();

    double cosres = ice_math_cos(ang);
    double sinres = ice_math_sin(ang);

    result.m5 = cosres;
    result.m6 = -sinres;
    result.m9 = sinres;
    result.m10 = cosres;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_rotate_y(double ang) {
    ice_math_mat result = ice_math_mat_identity();

    double cosres = ice_math_cos(ang);
    double sinres = ice_math_sin(ang);

    result.m0 = cosres;
    result.m2 = -sinres;
    result.m8 = sinres;
    result.m10 = cosres;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_rotate_z(double ang) {
    ice_math_mat result = ice_math_mat_identity();

    double cosres = ice_math_cos(ang);
    double sinres = ice_math_sin(ang);

    result.m0 = cosres;
    result.m1 = -sinres;
    result.m4 = sinres;
    result.m5 = cosres;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_scale(double x, double y, double z) {
    return (ice_math_mat) {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_mult(ice_math_mat left, ice_math_mat right) {
    ice_math_mat result = { 0 };

    result.m0 = left.m0 * right.m0 + left.m1 * right.m4 + left.m2 * right.m8 + left.m3 * right.m12;
    result.m1 = left.m0 * right.m1 + left.m1 * right.m5 + left.m2 * right.m9 + left.m3 * right.m13;
    result.m2 = left.m0 * right.m2 + left.m1 * right.m6 + left.m2 * right.m10 + left.m3 * right.m14;
    result.m3 = left.m0 * right.m3 + left.m1 * right.m7 + left.m2 * right.m11 + left.m3 * right.m15;
    result.m4 = left.m4 * right.m0 + left.m5 * right.m4 + left.m6 * right.m8 + left.m7 * right.m12;
    result.m5 = left.m4 * right.m1 + left.m5 * right.m5 + left.m6 * right.m9 + left.m7 * right.m13;
    result.m6 = left.m4 * right.m2 + left.m5 * right.m6 + left.m6 * right.m10 + left.m7 * right.m14;
    result.m7 = left.m4 * right.m3 + left.m5 * right.m7 + left.m6 * right.m11 + left.m7 * right.m15;
    result.m8 = left.m8 * right.m0 + left.m9 * right.m4 + left.m10 * right.m8 + left.m11 * right.m12;
    result.m9 = left.m8 * right.m1 + left.m9 * right.m5 + left.m10 * right.m9 + left.m11 * right.m13;
    result.m10 = left.m8 * right.m2 + left.m9 * right.m6 + left.m10 * right.m10 + left.m11 * right.m14;
    result.m11 = left.m8 * right.m3 + left.m9 * right.m7 + left.m10 * right.m11 + left.m11 * right.m15;
    result.m12 = left.m12 * right.m0 + left.m13 * right.m4 + left.m14 * right.m8 + left.m15 * right.m12;
    result.m13 = left.m12 * right.m1 + left.m13 * right.m5 + left.m14 * right.m9 + left.m15 * right.m13;
    result.m14 = left.m12 * right.m2 + left.m13 * right.m6 + left.m14 * right.m10 + left.m15 * right.m14;
    result.m15 = left.m12 * right.m3 + left.m13 * right.m7 + left.m14 * right.m11 + left.m15 * right.m15;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_frustum(double left, double right, double bottom, double top, double near, double far) {
    ice_math_mat result = { 0 };

    double rl = right - left;
    double tb = top - bottom;
    double fn = far - near;

    result.m0 = (near * 2) / rl;
    result.m1 = 0;
    result.m2 = 0;
    result.m3 = 0;

    result.m4 = 0;
    result.m5 = (near * 2) / tb;
    result.m6 = 0;
    result.m7 = 0;

    result.m8 = (right + left) / rl;
    result.m9 = (top + bottom) / tb;
    result.m10 = -(far + near) / fn;
    result.m11 = -1;

    result.m12 = 0;
    result.m13 = 0;
    result.m14 = -((far * near * 2) / fn);
    result.m15 = 0;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_perspective(double fovy, double aspect, double near, double far) {
    double top = near * ice_math_tan(fovy * 0.5);
    double right = top * aspect;
    ice_math_mat result = ice_math_mat_frustum(-right, right, -top, top, near, far);

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_ortho(double left, double right, double bottom, double top, double near, double far) {
    ice_math_mat result = { 0 };

    double rl = right - left;
    double tb = top - bottom;
    double fn = far - near;

    result.m0 = 2 / rl;
    result.m1 = 0;
    result.m2 = 0;
    result.m3 = 0;
    result.m4 = 0;
    result.m5 = 2 / tb;
    result.m6 = 0;
    result.m7 = 0;
    result.m8 = 0;
    result.m9 = 0;
    result.m10 = -2 / fn;
    result.m11 = 0;
    result.m12 = -(left + right) / rl;
    result.m13 = -(top + bottom) / tb;
    result.m14 = -(far + near) / fn;
    result.m15 = 1;

    return result;
}

ICE_MATH_API ice_math_mat ICE_MATH_CALLCONV ice_math_mat_lookat(ice_math_vec3 eye, ice_math_vec3 target, ice_math_vec3 up) {
    ice_math_mat result = { 0 };

    ice_math_vec3 z = ice_math_vec3_sub(eye, target);
    z = ice_math_vec3_norm(z);
    ice_math_vec3 x = ice_math_vec3_cross_product(up, z);
    x = ice_math_vec3_norm(x);
    ice_math_vec3 y = ice_math_vec3_cross_product(z, x);

    result.m0 = x.x;
    result.m1 = y.x;
    result.m2 = z.x;
    result.m3 = 0;
    result.m4 = x.y;
    result.m5 = y.y;
    result.m6 = z.y;
    result.m7 = 0;
    result.m8 = x.z;
    result.m9 = y.z;
    result.m10 = z.z;
    result.m11 = 0;
    result.m12 = -ice_math_vec3_dot_product(x, eye);
    result.m13 = -ice_math_vec3_dot_product(y, eye);
    result.m14 = -ice_math_vec3_dot_product(z, eye);
    result.m15 = 1;

    return result;
}

// Vertices
// WARNING: They allocate memory, Consider freeing vertices with ice_math_free_vertices() when program finishes!
ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_point2d_vertices(ice_math_vec2 v) {
    double* arr = (double*) ICE_MATH_MALLOC(2 * sizeof(double));
    
    arr[0] = v.x;
    arr[1] = v.y;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_line2d_vertices(ice_math_vec2 v1, ice_math_vec2 v2) {
    double* arr = (double*) ICE_MATH_MALLOC(4 * sizeof(double));
    arr[0] = v1.x;
    arr[1] = v1.y;
    arr[2] = v2.y;
    arr[3] = v2.y;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_rect2d_vertices(ice_math_rect r) {
    double* arr = (double*) ICE_MATH_MALLOC(8 * sizeof(double));
    
    arr[0] = r.x;
    arr[1] = r.y;
    arr[2] = r.x + r.w;
    arr[3] = r.y;
    arr[4] = r.x + r.w;
    arr[5] = r.y + r.h;
    arr[6] = r.x;
    arr[7] = r.y + r.h;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_circle2d_vertices(ice_math_vec2 pos, double r) {
    return ice_math_polygon2d_vertices(pos, r, r * 2);
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_triangle2d_vertices(ice_math_vec2 v1, ice_math_vec2 v2, ice_math_vec2 v3) {
    double* arr = (double*) ICE_MATH_MALLOC(6 * sizeof(double));
    
    arr[0] = v1.x;
    arr[1] = v1.y;
    arr[2] = v2.x;
    arr[3] = v2.y;
    arr[4] = v3.x;
    arr[5] = v3.y;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_polygon2d_vertices(ice_math_vec2 v, double size, int sides) {
    double* arr = (double*) ICE_MATH_MALLOC(sides + 2 * 2 * sizeof(double));
    
    arr[0] = v.x + size * ice_math_cos(0);
    arr[1] = v.y + size * ice_math_sin(0);
    
    for (int i = 0; i < sides; i += 2) {
        arr[2 + i] = v.x + size * ice_math_cos(2 * i * ICE_MATH_PI / sides);
        arr[2 + i + 1] = v.y + size * ice_math_sin(2 * i * ICE_MATH_PI / sides);
    }
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_tex2d_rect_vertices(ice_math_rect src, ice_math_rect dst, int width, int height) {
    double* arr = (double*) ICE_MATH_MALLOC(12 * sizeof(double));
    
    // e: sx, o: sy, l: sw, t: sh
    // r: dx, n: dy, c: dw, g: dh
    double p = dst.x;
    double y = dst.x + dst.w;
    double x = dst.y;
    double d = dst.y + dst.h;
    double u = src.x / width;
    double f = (src.x + src.w) / width;
    double s = src.y / height;
    double m = (src.y + src.h) / height;
    
    arr[0] = p;
    arr[1] = x;
    arr[2] = y;
    arr[3] = x;
    arr[4] = p;
    arr[5] = d;
    arr[6] = p;
    arr[7] = d;
    arr[8] = y;
    arr[9] = x;
    arr[10] = y;
    arr[11] = d;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_tex2d_tex_vertices(ice_math_rect src, ice_math_rect dst, int width, int height) {
    double* arr = (double*) ICE_MATH_MALLOC(12 * sizeof(double));
    
    // e: sx, o: sy, l: sw, t: sh
    // r: dx, n: dy, c: dw, g: dh
    double p = dst.x;
    double y = dst.x + dst.w;
    double x = dst.y;
    double d = dst.y + dst.h;
    double u = src.x / width;
    double f = (src.x + src.w) / width;
    double s = src.y / height;
    double m = (src.y + src.h) / height;
    
    arr[0] = u;
    arr[1] = s;
    arr[2] = f;
    arr[3] = s;
    arr[4] = u;
    arr[5] = m;
    arr[6] = u;
    arr[7] = m;
    arr[8] = f;
    arr[9] = s;
    arr[10] = f;
    arr[11] = m;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_cube_vertices(ice_math_vec3 v, double s) {
    return ice_math_cuboid_vertices(v, (ice_math_vec3) { s, s, s });
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_cuboid_vertices(ice_math_vec3 v, ice_math_vec3 s) {
    double* arr = (double*) ICE_MATH_MALLOC(72 * sizeof(double));
    
    arr[0] = v.x - s.x / 2;     arr[1] = v.y - s.y / 2;     arr[2] = v.z + s.z / 2;
    arr[3] = v.x + s.x / 2;     arr[4] = v.y - s.y / 2;     arr[5] = v.z + s.z / 2;
    arr[6] = v.x + s.x / 2;     arr[7] = v.y - s.y / 2;     arr[8] = v.z + s.z / 2;
    arr[9] = v.x + s.x / 2;     arr[10] = v.y + s.y / 2;    arr[11] = v.z + s.z / 2;
    arr[12] = v.x + s.x / 2;    arr[13] = v.y + s.y / 2;    arr[14] = v.z + s.z / 2;
    arr[15] = v.x - s.x / 2;    arr[16] = v.y + s.y / 2;    arr[17] = v.z + s.z / 2;
    arr[18] = v.x - s.x / 2;    arr[19] = v.y + s.y / 2;    arr[20] = v.z + s.z / 2;
    arr[21] = v.x - s.x / 2;    arr[22] = v.y - s.y / 2;    arr[23] = v.z + s.z / 2;
    
    arr[24] = v.x - s.x / 2;    arr[25] = v.y - s.y / 2;    arr[26] = v.z - s.z / 2;
    arr[27] = v.x + s.x / 2;    arr[28] = v.y - s.y / 2;    arr[29] = v.z - s.z / 2;
    arr[30] = v.x + s.x / 2;    arr[31] = v.y - s.y / 2;    arr[32] = v.z - s.z / 2;
    arr[33] = v.x + s.x / 2;    arr[34] = v.y + s.y / 2;    arr[35] = v.z - s.z / 2;
    arr[36] = v.x + s.x / 2;    arr[37] = v.y + s.y / 2;    arr[38] = v.z - s.z / 2;
    arr[39] = v.x - s.x / 2;    arr[40] = v.y + s.y / 2;    arr[41] = v.z - s.z / 2;
    arr[42] = v.x - s.x / 2;    arr[43] = v.y + s.y / 2;    arr[44] = v.z - s.z / 2;
    arr[45] = v.x - s.x / 2;    arr[46] = v.y - s.y / 2;    arr[47] = v.z - s.z / 2;
    
    arr[48] = v.x - s.x / 2;    arr[49] = v.y + s.y / 2;    arr[50] = v.z + s.z / 2;
    arr[51] = v.x - s.x / 2;    arr[52] = v.y + s.y / 2;    arr[53] = v.z - s.z / 2;
    arr[54] = v.x + s.x / 2;    arr[55] = v.y + s.y / 2;    arr[56] = v.z + s.z / 2;
    arr[57] = v.x + s.x / 2;    arr[58] = v.y + s.y / 2;    arr[59] = v.z - s.z / 2;
    
    arr[60] = v.x - s.x / 2;    arr[61] = v.y - s.y / 2;    arr[62] = v.z + s.z / 2;
    arr[63] = v.x - s.x / 2;    arr[64] = v.y - s.y / 2;    arr[65] = v.z - s.z / 2;
    arr[66] = v.x + s.x / 2;    arr[67] = v.y - s.y / 2;    arr[68] = v.z + s.z / 2;
    arr[69] = v.x + s.x / 2;    arr[70] = v.y - s.y / 2;    arr[71] = v.z - s.z / 2;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_sphere_vertices(ice_math_vec3 v, double s) {
    double* arr = (double*) ICE_MATH_MALLOC((s * (s + 2)) * sizeof(double));
    
    for (int i = 0; i < (s + 2); i++) {
        for (int j = 0; j < s; j++) {
            arr[(i * 18)] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * i)) * ice_math_sin(ice_math_rad(j * 360 / s));
            arr[(i * 18) + 1] = ice_math_sin(ice_math_rad(270 + (180 / (s + 1)) * i));
            arr[(i * 18) + 2] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * i)) * ice_math_cos(ice_math_rad(j * 360 / s));
            arr[(i * 18) + 3] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * (i + 1))) * ice_math_sin(ice_math_rad((j + 1) * 360 / s));
            arr[(i * 18) + 4] = ice_math_sin(ice_math_rad(270 + (180 / (s + 1)) * (i + 1)));
            arr[(i * 18) + 5] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * (i + 1))) * ice_math_cos(ice_math_rad((j + 1) * 360 / s));
            arr[(i * 18) + 6] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * (i + 1))) * ice_math_sin(ice_math_rad(j * 360 / s));
            arr[(i * 18) + 7] = ice_math_sin(ice_math_rad(270 + (180 / (s + 1)) * (i + 1)));
            arr[(i * 18) + 8] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * (i + 1))) * ice_math_cos(ice_math_rad(j * 360 / s));
            arr[(i * 18) + 9] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * i)) * ice_math_sin(ice_math_rad(j * 360 / s));
            arr[(i * 18) + 10] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * i)) * ice_math_sin(ice_math_rad(j * 360 / s));
            arr[(i * 18) + 11] = ice_math_sin(ice_math_rad(270 + (180 / (s + 1)) * i));
            arr[(i * 18) + 12] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * i)) * ice_math_cos(ice_math_rad(j * 360 / s));
            arr[(i * 18) + 13] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * (i))) * ice_math_sin(ice_math_rad((j + 1) * 360 / s));
            arr[(i * 18) + 14] = ice_math_sin(ice_math_rad(270 + (180 / (s + 1)) * (i)));
            arr[(i * 18) + 15] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * (i))) * ice_math_cos(ice_math_rad((j + 1) * 360 / s));
            arr[(i * 18) + 16] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * (i + 1))) * ice_math_sin(ice_math_rad((j + 1) * 360 / s));
            arr[(i * 18) + 17] = ice_math_sin(ice_math_rad(270 + (180 / (s + 1)) * (i + 1)));
            arr[(i * 18) + 18] = ice_math_cos(ice_math_rad(270 + (180 / (s + 1)) * (i + 1))) * ice_math_cos(ice_math_rad((j + 1) * 360 / s));
        }
    }
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_point3d_vertices(ice_math_vec3 v) {
    double* arr = (double*) ICE_MATH_MALLOC(3 * sizeof(double));
    
    arr[0] = v.x;
    arr[1] = v.y;
    arr[2] = v.z;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_line3d_vertices(ice_math_vec3 v1, ice_math_vec3 v2) {
    double* arr = (double*) ICE_MATH_MALLOC(6 * sizeof(double));
    
    arr[0] = v1.x;
    arr[1] = v1.y;
    arr[2] = v1.z;
    arr[3] = v2.x;
    arr[4] = v2.y;
    arr[5] = v2.z;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_rect3d_vertices(ice_math_rect r, double z) {
    double* arr = (double*) ICE_MATH_MALLOC(12 * sizeof(double));
    
    arr[0] = r.x;
    arr[1] = r.y;
    arr[2] = z;
    arr[3] = r.x + r.w;
    arr[4] = r.y;
    arr[5] = z;
    arr[6] = r.x + r.w;
    arr[7] = r.y + r.h;
    arr[8] = z;
    arr[9] = r.x;
    arr[10] = r.y + r.h;
    arr[11] = z;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_circle3d_vertices(ice_math_vec3 pos, double r) {
    return ice_math_polygon3d_vertices(pos, r, r * 2);
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_triangle3d_vertices(ice_math_vec3 v1, ice_math_vec3 v2, ice_math_vec3 v3) {
    double* arr = (double*) ICE_MATH_MALLOC(9 * sizeof(double));
    
    arr[0] = v1.x;
    arr[1] = v1.y;
    arr[2] = v1.z;
    arr[3] = v2.x;
    arr[4] = v2.y;
    arr[5] = v2.z;
    arr[6] = v3.x;
    arr[7] = v3.y;
    arr[8] = v3.z;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_polygon3d_vertices(ice_math_vec3 v, double size, int sides) {
    double* arr = (double*) ICE_MATH_MALLOC((sides + 3) * 3 * sizeof(double));
    
    arr[0] = v.x + size * ice_math_cos(0);
    arr[1] = v.y + size * ice_math_sin(0);
    arr[2] = v.z;
    
    for (int i = 0; i < sides; i += 3) {
        arr[3 + i] = v.x + size * ice_math_cos(2 * i * ICE_MATH_PI / sides);
        arr[3 + i + 1] = v.y + size * ice_math_sin(2 * i * ICE_MATH_PI / sides);
        arr[3 + i + 2] = v.z;
    }
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_tex3d_rect_vertices(ice_math_rect src, ice_math_rect dst, double z, int width, int height) {
    double* arr = (double*) ICE_MATH_MALLOC(18 * sizeof(double));
    
    // e: sx, o: sy, l: sw, t: sh
    // r: dx, n: dy, c: dw, g: dh
    double p = dst.x;
    double y = dst.x + dst.w;
    double x = dst.y;
    double d = dst.y + dst.h;
    double u = src.x / width;
    double f = (src.x + src.w) / width;
    double s = src.y / height;
    double m = (src.y + src.h) / height;
    
    arr[0] = p;
    arr[1] = x;
    arr[2] = z;
    arr[3] = y;
    arr[4] = x;
    arr[5] = z;
    arr[6] = p;
    arr[7] = d;
    arr[8] = z;
    arr[9] = p;
    arr[10] = d;
    arr[11] = z;
    arr[12] = y;
    arr[13] = x;
    arr[14] = z;
    arr[15] = y;
    arr[16] = d;
    arr[17] = z;
    
    return arr;
}

ICE_MATH_API double* ICE_MATH_CALLCONV ice_math_tex3d_tex_vertices(ice_math_rect src, ice_math_rect dst, double z, int width, int height) {
    double* arr = (double*) ICE_MATH_MALLOC(18 * sizeof(double));
    
    // e: sx, o: sy, l: sw, t: sh
    // r: dx, n: dy, c: dw, g: dh
    double p = dst.x;
    double y = dst.x + dst.w;
    double x = dst.y;
    double d = dst.y + dst.h;
    double u = src.x / width;
    double f = (src.x + src.w) / width;
    double s = src.y / height;
    double m = (src.y + src.h) / height;
    
    arr[0] = u;
    arr[1] = s;
    arr[2] = z;
    arr[3] = f;
    arr[4] = s;
    arr[5] = z;
    arr[6] = u;
    arr[7] = m;
    arr[8] = z;
    arr[9] = u;
    arr[10] = m;
    arr[11] = z;
    arr[12] = f;
    arr[13] = s;
    arr[14] = z;
    arr[15] = f;
    arr[16] = m;
    arr[17] = z;
    
    return arr;
}

ICE_MATH_API void ICE_MATH_CALLCONV ice_math_free_vertices(double* vertices) {
    ICE_MATH_FREE(vertices);
}

// Distances
ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_dist2d(ice_math_vec2 v1, ice_math_vec2 v2) {
    return (ice_math_vec2) {
        v2.x - v1.x,
        v2.y - v1.y
    };
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_dist2d_between(ice_math_vec2 v1, ice_math_vec2 v2) {
    return ice_math_hypot(v2.x - v1.x, v2.y - v1.y);
}

ICE_MATH_API ice_math_vec2 ICE_MATH_CALLCONV ice_math_rotate_around2d(ice_math_vec2 v1, ice_math_vec2 v2, double angle) {
    ice_math_vec2 result = { 0 };
    
    angle = ice_math_rad(angle);
    result.x = ice_math_cos(angle) * (v2.x - v1.x) - ice_math_sin(angle) * (v2.y - v1.y) + v1.x;
    result.y = ice_math_sin(angle) * (v2.x - v1.x) + ice_math_cos(angle) * (v2.y - v1.y) + v1.y;
    
    return result;
}

ICE_MATH_API ice_math_vec3 ICE_MATH_CALLCONV ice_math_dist3d(ice_math_vec3 v1, ice_math_vec3 v2) {
    return (ice_math_vec3) {
        v2.x - v1.x,
        v2.y - v1.y,
        v2.z - v1.z
    };
}

ICE_MATH_API ice_math_vec4 ICE_MATH_CALLCONV ice_math_dist4d(ice_math_vec4 v1, ice_math_vec4 v2) {
    return (ice_math_vec4) {
        v2.x - v1.x,
        v2.y - v1.y,
        v2.z - v1.z,
        v2.w - v1.w
    };
}

// Edit of https://github.com/ESultanik/mtwister for ice_math!
inline static void ice_math_mseed(ice_math_mtrand* rand, unsigned long seed) {
    rand->mt[0] = seed & 0xffffffff;
    for(rand->index = 1; rand->index < ICE_MATH_STATE_VECTOR_LENGTH; rand->index++) {
      rand->mt[rand->index] = (6069 * rand->mt[rand->index - 1]) & 0xffffffff;
    }
}

inline static ice_math_mtrand ice_math_mseed_rand(unsigned long seed) {
    ice_math_mtrand rand;
    ice_math_mseed(&rand, seed);
    return rand;
}

inline static unsigned long ice_math_randlong(ice_math_mtrand* rand) {
    unsigned long y;
    static unsigned long mag[2] = { 0x0, 0x9908b0df };
    
    if (rand->index >= ICE_MATH_STATE_VECTOR_LENGTH || rand->index < 0) {
        int kk;
      
        if(rand->index >= ICE_MATH_STATE_VECTOR_LENGTH + 1 || rand->index < 0) {
            ice_math_mseed(rand, 4357);
        }
    
        for (kk = 0; kk<ICE_MATH_STATE_VECTOR_LENGTH - ICE_MATH_STATE_VECTOR_M; kk++) {
            y = (rand->mt[kk] & ICE_MATH_UPPER_MASK) | (rand->mt[kk + 1] & ICE_MATH_LOWER_MASK);
            rand->mt[kk] = rand->mt[kk + ICE_MATH_STATE_VECTOR_M] ^ (y >> 1) ^ mag[y & 0x1];
        }
        
        for (; kk < ICE_MATH_STATE_VECTOR_LENGTH - 1; kk++) {
            y = (rand->mt[kk] & ICE_MATH_UPPER_MASK) | (rand->mt[kk + 1] & ICE_MATH_LOWER_MASK);
            rand->mt[kk] = rand->mt[kk + (ICE_MATH_STATE_VECTOR_M-ICE_MATH_STATE_VECTOR_LENGTH)] ^ (y >> 1) ^ mag[y & 0x1];
        }
        
        y = (rand->mt[ICE_MATH_STATE_VECTOR_LENGTH - 1] & ICE_MATH_UPPER_MASK) | (rand->mt[0] & ICE_MATH_LOWER_MASK);
        rand->mt[ICE_MATH_STATE_VECTOR_LENGTH - 1] = rand->mt[ICE_MATH_STATE_VECTOR_M - 1] ^ (y >> 1) ^ mag[y & 0x1];
        rand->index = 0;
    }
  
    y = rand->mt[rand->index++];
    y ^= (y >> 11);
    y ^= (y << 7) & ICE_MATH_TEMPERING_MASK_B;
    y ^= (y << 15) & ICE_MATH_TEMPERING_MASK_C;
    y ^= (y >> 18);
    return y;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_rand(void) {
    ice_math_mtrand rand = ice_math_mseed_rand(time(NULL));
    return (double)((double)ice_math_randlong(&rand) / (unsigned long) 0xffffffff);
}

#endif  // ICE_MATH_IMPL
#endif  // ICE_MATH_H
