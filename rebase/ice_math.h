/*
ice_math.h, Single-Header Cross-Platform C library for working with Math!

TODO: Complete...


================================== Full Overview ==================================

ice_math.h is Single-Header Cross-Platform C library for working with Math, It provides functions for working with mathematical stuff...

Also it has custom implementation of math.h functions, So ice_math.h does not rely on math.h

To use it #define ICE_MATH_IMPL then #include "ice_math.h" in your C/C++ code!


================================== Usage Example ==================================



=================================== Library API ===================================


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_math.h in the code...
#define ICE_MATH_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_MATH_VECTORCALL      // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_MATH_FASTCALL        // fastcall
#define ICE_MATH_STDCALL         // stdcall
#define ICE_MATH_CDECL           // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_MATH_MICROSOFT       // Microsoft platforms
#define ICE_MATH_NON_MICROSOFT   // Non-Microsoft platforms

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_MATH_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_MATH_DLLEXPORT       // Export the symbols to build as shared library
#define ICE_MATH_DLLIMPORT       // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_MATH_INLINE          // inlines library functions (Only works on C99 Standard and above)
#define ICE_MATH_EXTERN          // externs library functions
#define ICE_MATH_STATIC          // statics library functions

// NOTE: ICE_MATH_EXTERN and ICE_MATH_STATIC cannot be #defined together in the code...


================================= Support ice_libs ================================

ice_math.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_MATH_H
#define ICE_MATH_H 1

/* Allow to use calling conventions if desired... */
#if defined(ICE_MATH_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_MATH_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_MATH_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_MATH_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_MATH_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_MATH_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_MATH_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_MATH_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_MATH_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_MATH_CDECL)
#  if defined(_MSC_VER)
#    define ICE_MATH_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_MATH_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_MATH_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_MATH_MICROSOFT) || defined(ICE_MATH_NON_MICROSOFT))
#  define ICE_MATH_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
#if defined(ICE_MATH_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_MATH_MICROSOFT 1
#  else
#    define ICE_MATH_NON_MICROSOFT 1
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_MATH_EXTERN) && defined(ICE_MATH_STATIC))
#  define ICE_MATH_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_MATH_EXTERN)
#  define ICE_MATH_APIDEF extern
#elif defined(ICE_MATH_STATIC)
#  define ICE_MATH_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_MATH_INLINE to enable inline functionality.
*/
#if defined(ICE_MATH_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_MATH_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_MATH_INLINEDEF inline
#  endif
#else
#  define ICE_MATH_INLINEDEF
#endif

/*
Allow to build DLL via ICE_MATH_DLLEXPORT or ICE_MATH_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
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

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Definitions ============================== */

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

#define ICE_MATH_FLT_RADIX              2

/* ============================== Functions ============================== */

/* TODO: Simplify the API */
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_rad(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_deg(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_abs(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_max(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_min(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_ceil(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_floor(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_round(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_imul(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_idiv(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sqr(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_pow(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log2(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_exp(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_expm1(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log10(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log1p(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_exp2(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sqrt(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_trunc(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sign(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fib(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fact(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_clamp(double value, double min, double max);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_lerp(double start, double end, double amount);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_norm(double value, double start, double end);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_remap(double value, double in_start, double in_end, double out_start, double out_end);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_hypot(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_atan2(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cbrt(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_ldexp(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_scalbn(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fma(double a, double b, double c);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_logb(double n);

/*
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_erf(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_erfc(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_erfi(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_gamma(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_lgamma(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_j0(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_j1(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_jn(int b, double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_y0(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_y1(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_yn(int b, double n);
*/

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec(double n);

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sinh(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cosh(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tanh(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_coth(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csch(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sech(double n);

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asin(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acos(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_atan(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acot(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acsc(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asec(double n);

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asinh(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acosh(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_atanh(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acoth(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acsch(double n);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asech(double n);

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_sum(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_sum(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_sum(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_sum(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_sum(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_sum(double a, double b);

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_diff(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_diff(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_diff(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_diff(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_diff(double a, double b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_diff(double a, double b);

/* TODO: Can trigonometry angles power be negative? */
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_pow(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_pow(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_pow(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_pow(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_pow(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_pow(double a, unsigned b);

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_mult(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_mult(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_mult(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_mult(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_mult(double a, unsigned b);
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_mult(double a, unsigned b);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_MATH_IMPL)

/* Challenge: No math.h XD */

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_rad(double n) {
    return n * (ICE_MATH_PI / 180.0);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_deg(double n) {
    return n * (180.0 / ICE_MATH_PI);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_abs(double n) {
    return (n < 0) ? -n : n;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_max(double a, double b) {
    return (a > b) ? a : b;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_min(double a, double b) {
    return (a < b) ? a : b;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_ceil(double n) {
    double n_int = (int) n;
    
    if (n < 0) {
        return n_int;
    }
    
    return ((n - n_int) > 0) ? n_int + 1 : n_int;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_floor(double n) {
    double n_int = (int) n;
    
    if (n < 0) {
        return ((-n_int + n) > 0) ? n_int - 1 : n_int;
    }
    
    return n_int;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_round(double n) {
    double n_int = (int) n;
    
    if (n < 0) {
        return ((-n_int + n) > 0.5) ? n_int - 1 : n_int;
    }
    
    return ((n - n_int) >= 0.5) ? n_int + 1 : n_int;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_imul(double a, double b) {
    return (int)(a * b);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_idiv(double a, double b) {
    return (int)(a / b);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sqr(double n) {
    return n * n;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_pow(double a, double b) {
    if (b == 0) return 1;
    else if (b == 1) return a;
    
    double base_i = (int) b;
    
    if (base_i == b) {
        double res = a;
        double base = 0;
        unsigned i;
        
        if (b < 0) base = -b - 1;
        else if (b > 1) base = b - 1;
        
        for (i = 0; i < base; i++) {
            res *= a;
        }
        
        if (b < 0) return (1 / res);
        else if (b > 1) return res;
    
    } else {
        if (a < 0) {
            return ICE_MATH_NAN;
        } else if (a > 1 && b > 0) {
            int base = (int) 1 / b;
            double res = 1;
            unsigned i;
            
            for (i = 0; i < base; i++) {
                res *= ice_math_sqrt(a);
            }
            
            return res;
        }
    }
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log2(double n) {
    return (n > 1) ? 1 + ice_math_log2(n / 2) : 0;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_exp(double n) {
    return ice_math_pow(ICE_MATH_E, n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_expm1(double n) {
    return ice_math_exp(n) - 1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log(double n) {
    return ice_math_log2(n) / 2;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log10(double n) {
    return ice_math_log(n) / ice_math_log(10);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_log1p(double n) {
    return ice_math_log(n + 1);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_exp2(double n) {
    return ice_math_exp(n * ice_math_log(2));
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

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_trunc(double n) {
    return (int) n;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sign(double n) {
    if (n == 0) return 0;
    return (n > 0) ? 1 : -1;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fib(double n) {
    return (n <= 2) ? 1 : (ice_math_fib(n - 1) + ice_math_fib(n - 2));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fact(double n) {
    double x = 1;
    unsigned i;
    
    for (i = 2; i <= n; i++) {
        x = x * i;
    }
    
    return x;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_clamp(double value, double min, double max) {
    double result = (value < min)? min : value;
    
    if (result > max) result = max;
    
    return result;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_lerp(double start, double end, double amount) {
    return (start + amount * (end - start));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_norm(double value, double start, double end) {
    return ((value - start) / (end - start));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_remap(double value, double in_start, double in_end, double out_start, double out_end) {
    return ((value - in_start) / (in_end - in_start) * (out_end - out_start) + out_start);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_hypot(double a, double b) {
    return ice_math_sqrt((a * a) + (b * b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_atan2(double a, double b) {
    return ice_math_atan(a / b);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cbrt(double n) {
    return ice_math_pow(n, 1 / 3);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_ldexp(double a, double b) {
    return (a * ice_math_pow(ICE_MATH_FLT_RADIX, b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_scalbn(double a, double b) {
    return (a * ice_math_pow(ICE_MATH_FLT_RADIX, b))
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_fma(double a, double b, double c) {
    return (a * b + c);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_logb(double n) {
    return ice_math_log2(((n < 0) ? -n : n));
}

/* TODO: Complete */
/*
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_erf(double n) {}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_erfc(double n) {}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_erfi(double n) {}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_gamma(double n) {
    if (n == (int) n) return ice_math_fact(n - 1);
}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_lgamma(double n) {}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_j0(double n) {}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_j1(double n) {}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_jn(int b, double n) {}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_y0(double n) {}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_y1(double n) {}
ICE_MATH_API double ICE_MATH_CALLCONV ice_math_yn(int b, double n) {}
*/

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin(double n) {
    double res = n;
    int dec = -1;
    unsigned limit = 36;
    unsigned i;
    
    for (i = 3; i < limit; i += 2) {
        double v1 = 1;
        double v2 = 1;
        unsigned j;
        
        for (j = i; j > 0; j--) {
            v1 *= n;
            v2 *= j;
        }
        
        if (dec == -1) {
            res -= (v1 / v2);
            dec = 0;
        } else if (dec == 0) {
            res += (v1 / v2);
            dec = -1;
        }
    }
    
    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos(double n) {
    double res = 1;
    int dec = -1;
    unsigned limit = 35;
    unsigned i;

    for (i = 2; i < limit; i += 2) {
        double v1 = 1;
        double v2 = 1;
        unsigned j;
        
        for (j = i; j > 0; j--) {
            v1 *= n;
            v2 *= j;
        }
        
        if (dec == -1) {
            res -= (v1 / v2);
            dec = 0;
        } else if (dec == 0) {
            res += (v1 / v2);
            dec = -1;
        }
    }
    
    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan(double n) {
    return ice_math_sin(n) / ice_math_cos(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot(double n) {
    return ice_math_cos(n) / ice_math_sin(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc(double n) {
    return 1 / ice_math_sin(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec(double n) {
    return 1 / ice_math_cos(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sinh(double n) {
    double pow_n = ice_math_pow(ICE_MATH_E, n);
    double pow_neg_n = ice_math_pow(ICE_MATH_E, -n);
    
    return (pow_n - pow_neg_n) / 2;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cosh(double n) {
    double pow_n = ice_math_pow(ICE_MATH_E, n);
    double pow_neg_n = ice_math_pow(ICE_MATH_E, -n);
    
    return (pow_n + pow_neg_n) / 2;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tanh(double n) {
    return ice_math_sinh(n) / ice_math_cosh(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_coth(double n) {
    return ice_math_cosh(n) / ice_math_sinh(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csch(double n) {
    return 1 / ice_math_sinh(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sech(double n) {
    return 1 / ice_math_cosh(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asin(double n) {
    return n + (1 / 2) * ((n * n * n) / 3) + ((1 * 3) / (2 * 4)) * ((n * n * n * n * n) / 5) + ((1 * 3 * 5) / (2 * 4 * 6)) * ((n * n * n * n * n * n * n) / 7);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acos(double n) {
    return (-0.69813170079773212 * n * n - 0.87266462599716477) * n + 1.5707963267948966;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_atan(double n) {
    return ice_math_asin(n) / ice_math_acos(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acot(double n) {
    return ice_math_acos(n) / ice_math_asin(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acsc(double n) {
    return 1 / ice_math_asin(n);
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asec(double n) {
    return 1 / ice_math_acos(n);
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

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_acsch(double n) {
    return ice_math_log(1 + ice_math_sqrt((1 - (n * n)) / n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_asech(double n) {
    return ice_math_log(1 + ice_math_sqrt((1 + (n * n)) / n));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_sum(double a, double b) {
    double sin_a = ice_math_sin(a);
    double cos_a = ice_math_cos(a);
    
    double sin_b = ice_math_sin(b);
    double cos_b = ice_math_cos(b);

    return ((sin_a * cos_b) + (cos_a * sin_b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_sum(double a, double b) {
    double sin_a = ice_math_sin(a);
    double cos_a = ice_math_cos(a);
    
    double sin_b = ice_math_sin(b);
    double cos_b = ice_math_cos(b);

    return ((cos_a * cos_b) - (sin_a * sin_b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_sum(double a, double b) {
    double tan_a = ice_math_tan(a);
    double tan_b = ice_math_tan(b);

    return ((tan_a + tan_b) / (1 - (tan_a * tan_b)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_sum(double a, double b) {
    double cot_a = ice_math_cot(a);
    double cot_b = ice_math_cot(b);

    return (((cot_a * cot_b) - 1) / (cot_b + cot_a));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_sum(double a, double b) {
    double csc_a = ice_math_csc(a);
    double csc_b = ice_math_csc(b);

    double sec_a = ice_math_sec(a);
    double sec_b = ice_math_sec(b);

    return ((sec_a * sec_b * csc_a * csc_b) / ((sec_a * csc_b) + (csc_a * sec_b)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_sum(double a, double b) {
    double csc_a = ice_math_csc(a);
    double csc_b = ice_math_csc(b);

    double sec_a = ice_math_sec(a);
    double sec_b = ice_math_sec(b);

    return ((sec_a * sec_b * csc_a * csc_b) / ((csc_a * csc_b) - (sec_a * sec_b)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_diff(double a, double b) {
    double sin_a = ice_math_sin(a);
    double cos_a = ice_math_cos(a);
    
    double sin_b = ice_math_sin(b);
    double cos_b = ice_math_cos(b);

    return ((sin_a * cos_b) - (cos_a * sin_b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_diff(double a, double b) {
    double sin_a = ice_math_sin(a);
    double cos_a = ice_math_cos(a);
    
    double sin_b = ice_math_sin(b);
    double cos_b = ice_math_cos(b);

    return ((cos_a * cos_b) + (sin_a * sin_b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_diff(double a, double b) {
    double tan_a = ice_math_tan(a);
    double tan_b = ice_math_tan(b);

    return ((tan_a - tan_b) / (1 + (tan_a * tan_b)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_diff(double a, double b) {
    double cot_a = ice_math_cot(a);
    double cot_b = ice_math_cot(b);

    return (((cot_a * cot_b) + 1) / (cot_b - cot_a));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_diff(double a, double b) {
    double csc_a = ice_math_csc(a);
    double csc_b = ice_math_csc(b);

    double sec_a = ice_math_sec(a);
    double sec_b = ice_math_sec(b);

    return ((sec_a * sec_b * csc_a * csc_b) / ((sec_a * csc_b) - (csc_a * sec_b)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_diff(double a, double b) {
    double csc_a = ice_math_csc(a);
    double csc_b = ice_math_csc(b);

    double sec_a = ice_math_sec(a);
    double sec_b = ice_math_sec(b);

    return ((sec_a * sec_b * csc_a * csc_b) / ((csc_a * csc_b) + (sec_a * sec_b)));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_pow(double a, unsigned b) {
    double res = 1;
    unsigned i;

    for (i = 0; i < b; i++) {
        res *= ice_math_sin(a);
    }

    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_pow(double a, unsigned b) {
    double res = 1;
    unsigned i;

    for (i = 0; i < b; i++) {
        res *= ice_math_cos(a);
    }

    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_pow(double a, unsigned b) {
    double res = 1;
    unsigned i;

    for (i = 0; i < b; i++) {
        res *= ice_math_tan(a);
    }

    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_pow(double a, unsigned b) {
    double res = 1;
    unsigned i;

    for (i = 0; i < b; i++) {
        res *= ice_math_cot(a);
    }

    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_pow(double a, unsigned b) {
    double res = 1;
    unsigned i;

    for (i = 0; i < b; i++) {
        res *= ice_math_csc(a);
    }

    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_pow(double a, unsigned b) {
    double res = 1;
    unsigned i;

    for (i = 0; i < b; i++) {
        res *= ice_math_sec(a);
    }

    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sin_mult(double a, unsigned b) {
    double res = 0;
    unsigned k;

    for (k = 0; k <= b; k++) {
        double v1 = ice_math_cos_pow(a, k);
        double v2 = ice_math_sin_pow(a, b - k);
        double v3 = ice_math_sin((1 / 2) * (b - k)) * ICE_MATH_PI;

        res += (v1 * v2 * v3);
    }

    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cos_mult(double a, unsigned b) {
    double res = 0;
    unsigned k;

    for (k = 0; k <= b; k++) {
        double v1 = ice_math_cos_pow(a, k);
        double v2 = ice_math_sin_pow(a, b - k);
        double v3 = ice_math_cos((1 / 2) * (b - k) * ICE_MATH_PI);

        res += (v1 * v2 * v3);
    }

    return res;
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_tan_mult(double a, unsigned b) {
    return (ice_math_sin_mult(a, b) / ice_math_cos_mult(a, b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_cot_mult(double a, unsigned b) {
    return (ice_math_cos_mult(a, b) / ice_math_sin_mult(a, b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_csc_mult(double a, unsigned b) {
    return (1 / ice_math_sin_mult(a, b));
}

ICE_MATH_API double ICE_MATH_CALLCONV ice_math_sec_mult(double a, unsigned b) {
    return (1 / ice_math_cos_mult(a, b));
}

#endif  /* ICE_MATH_IMPL */
#endif  /* ICE_MATH_H */

/*
ice_math.h is dual-licensed, Choose the one you prefer!

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