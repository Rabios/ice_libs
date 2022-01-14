/*
ice_vecmath.h, Single-Header Cross-Platform C library for vector math!

TODO: Complete quat2 functions + Complete...


================================== Full Overview ==================================

ice_vecmath.h is Single-Header Cross-Platform C library for vector math, It provides functions for working with Vectors, Quaternions, and Matrices!

To use it #define ICE_VECMATH_IMPL then #include "ice_vecmath.h" in your C/C++ code!


================================== Usage Example ==================================



=================================== Library API ===================================



================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_vecmath.h in the code...
#define ICE_VECMATH_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_VECMATH_VECTORCALL      // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_VECMATH_FASTCALL        // fastcall
#define ICE_VECMATH_STDCALL         // stdcall
#define ICE_VECMATH_CDECL           // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_VECMATH_MICROSOFT       // Microsoft platforms
#define ICE_VECMATH_NON_MICROSOFT   // Non-Microsoft platforms

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_VECMATH_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_VECMATH_DLLEXPORT       // Export the symbols to build as shared library
#define ICE_VECMATH_DLLIMPORT       // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_VECMATH_INLINE          // inlines library functions (Only works on C99 Standard and above)
#define ICE_VECMATH_EXTERN          // externs library functions
#define ICE_VECMATH_STATIC          // statics library functions

// NOTE: ICE_VECMATH_EXTERN and ICE_VECMATH_STATIC cannot be #defined together in the code...


============================== Implementation Resources ===========================

1. https://glmatrix.net
2. https://github.com/raysan5/raylib/blob/master/src/raymath.h


================================= Support ice_libs ================================

ice_vecmath.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_VECMATH_H
#define ICE_VECMATH_H

/* Disable security warnings for MSVC compiler, We don't want to force using C11! */
#ifdef _MSC_VER
#  ifndef _CRT_SECURE_NO_DEPRECATE
#    define _CRT_SECURE_NO_DEPRECATE
#  endif
#  ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS
#  endif
#  pragma warning(disable:4996)
#endif

/* Define C interface for Windows libraries! ;) */
#ifndef CINTERFACE
#  define CINTERFACE
#endif

/* Allow to use calling conventions if desired... */
#if defined(ICE_VECMATH_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_VECMATH_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_VECMATH_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_VECMATH_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_VECMATH_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_VECMATH_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_VECMATH_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_VECMATH_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_VECMATH_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_VECMATH_CDECL)
#  if defined(_MSC_VER)
#    define ICE_VECMATH_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_VECMATH_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_VECMATH_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_VECMATH_MICROSOFT) || defined(ICE_VECMATH_NON_MICROSOFT))
#  define ICE_VECMATH_PLATFORM_AUTODETECTED
#endif

/* Platform Detection */
#if defined(ICE_VECMATH_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_VECMATH_MICROSOFT
#  else
#    define ICE_VECMATH_NON_MICROSOFT
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_VECMATH_EXTERN) && defined(ICE_VECMATH_STATIC))
#  define ICE_VECMATH_EXTERN
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_VECMATH_EXTERN)
#  define ICE_VECMATH_APIDEF extern
#elif defined(ICE_VECMATH_STATIC)
#  define ICE_VECMATH_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_VECMATH_INLINE to enable inline functionality.
*/
#if defined(ICE_VECMATH_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_VECMATH_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_VECMATH_INLINEDEF inline
#  endif
#else
#  define ICE_VECMATH_INLINEDEF
#endif

/*
Allow to build DLL via ICE_VECMATH_DLLEXPORT or ICE_VECMATH_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_VECMATH_MICROSOFT)
#  if defined(ICE_VECMATH_DLLEXPORT)
#    define ICE_VECMATH_API __declspec(dllexport) ICE_VECMATH_INLINEDEF
#  elif defined(ICE_VECMATH_DLLIMPORT)
#    define ICE_VECMATH_API __declspec(dllimport) ICE_VECMATH_INLINEDEF
#  else
#    define ICE_VECMATH_API ICE_VECMATH_APIDEF ICE_VECMATH_INLINEDEF
#  endif
#else
#  define ICE_VECMATH_API ICE_VECMATH_APIDEF ICE_VECMATH_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Data Types ============================== */

typedef enum ice_vecmath_bool {
    ICE_VECMATH_FALSE = -1,
    ICE_VECMATH_TRUE = 0
} ice_vecmath_bool;

typedef struct ice_vecmath_vec2 { double x, y; } ice_vecmath_vec2;
typedef struct ice_vecmath_vec3 { double x, y, z; } ice_vecmath_vec3;
typedef struct ice_vecmath_vec4 { double x, y, z, w; } ice_vecmath_vec4;
typedef struct ice_vecmath_quat { double data[4]; } ice_vecmath_quat;
typedef struct ice_vecmath_quat2 { double data[8]; } ice_vecmath_quat2;
typedef struct ice_vecmath_mat2 { double data[4]; } ice_vecmath_mat2;
typedef struct ice_vecmath_mat2d { double data[6]; } ice_vecmath_mat2d;
typedef struct ice_vecmath_mat3 { double data[9]; } ice_vecmath_mat3;
typedef struct ice_vecmath_mat4 { double data[16]; } ice_vecmath_mat4;

/*
typedef double ice_vecmath_quat[4], ice_vecmath_mat2[4];
typedef double ice_vecmath_quat2[8];
typedef double ice_vecmath_mat2d[6];
typedef double ice_vecmath_mat3[9];
typedef double ice_vecmath_mat4[16];
*/

/* ============================== module: util ============================== */

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_clamp(double value, double min, double max);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_lerp(double begin_value, double end_value, double amount);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_norm(double value, double begin_value, double end_value);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_remap(double value, double input_begin_value, double input_end_value, double output_begin_value, double output_end_value);


/* ============================== module: init ============================== */

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_create(double x, double y);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_create(double x, double y, double z);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_create(double x, double y, double z, double w);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_create(double q[4]);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_create(double q[8]);
ICE_VECMATH_API ice_vecmath_mat2 ICE_VECMATH_CALLCONV ice_vecmath_mat2_create(double m[4]);
ICE_VECMATH_API ice_vecmath_mat2d ICE_VECMATH_CALLCONV ice_vecmath_mat2d_create(double m[6]);
ICE_VECMATH_API ice_vecmath_mat3 ICE_VECMATH_CALLCONV ice_vecmath_mat3_create(double m[9]);
ICE_VECMATH_API ice_vecmath_mat4 ICE_VECMATH_CALLCONV ice_vecmath_mat4_create(double m[16]);


/* ============================== module: vec2 ============================== */

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_zero(void);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_one(void);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_add(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_addval(ice_vecmath_vec2 v, double n);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_sub(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_subval(ice_vecmath_vec2 v, double n);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_mul(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_div(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_scale(ice_vecmath_vec2 v, double scalar);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_scale_and_add(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2, double scalar);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_dot(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec2_cross(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
/* ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_rand(double scale); */
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_neg(ice_vecmath_vec2 v);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_inv(ice_vecmath_vec2 v);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_abs(ice_vecmath_vec2 v);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_ceil(ice_vecmath_vec2 v);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_floor(ice_vecmath_vec2 v);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_round(ice_vecmath_vec2 v);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_min(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_max(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_len(ice_vecmath_vec2 v);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_sqrlen(ice_vecmath_vec2 v);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_dist(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_sqrdist(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_angle(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_norm(ice_vecmath_vec2 v);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_lerp(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2, double amount);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_reflect(ice_vecmath_vec2 v, ice_vecmath_vec2 normal);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_rotate(ice_vecmath_vec2 v, double degs);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_towards(ice_vecmath_vec2 v, ice_vecmath_vec2 target, double maxdist);
ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_vec2_tostring(ice_vecmath_vec2 v);
ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_vec2_equ(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_transform_mat2(ice_vecmath_vec2 v, ice_vecmath_mat2 m);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_transform_mat2d(ice_vecmath_vec2 v, ice_vecmath_mat2d m);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_transform_mat3(ice_vecmath_vec2 v, ice_vecmath_mat3 m);
ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_transform_mat4(ice_vecmath_vec2 v, ice_vecmath_mat4 m);


/* ============================== module: vec3 ============================== */

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_zero(void);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_one(void);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_add(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_addval(ice_vecmath_vec3 v, double n);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_sub(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_subval(ice_vecmath_vec3 v, double n);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_mul(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_div(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_scale(ice_vecmath_vec3 v, double scalar);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_scale_and_add(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double scalar);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_dot(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_cross(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
/* ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rand(double scale); */
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_neg(ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_inv(ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_abs(ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_ceil(ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_floor(ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_round(ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_min(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_max(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_len(ice_vecmath_vec3 v);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_sqrlen(ice_vecmath_vec3 v);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_dist(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_sqrdist(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_angle(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_norm(ice_vecmath_vec3 v);
ICE_VECMATH_API void ICE_VECMATH_CALLCONV ice_vecmath_vec3_ortho_norm(ice_vecmath_vec3 *v1, ice_vecmath_vec3 *v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_lerp(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double amount);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_reflect(ice_vecmath_vec3 v, ice_vecmath_vec3 normal);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_perpendicular(ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_hermite(ice_vecmath_vec3 a, ice_vecmath_vec3 b, ice_vecmath_vec3 c, ice_vecmath_vec3 d, double t);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_bezier(ice_vecmath_vec3 a, ice_vecmath_vec3 b, ice_vecmath_vec3 c, ice_vecmath_vec3 d, double t);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_transform(ice_vecmath_vec3 v, ice_vecmath_mat4 m);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rotate_by_quat(ice_vecmath_vec3 v, ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rotate_x(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double rad);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rotate_y(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double rad);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rotate_z(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double rad);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_barycenter(ice_vecmath_vec3 p, ice_vecmath_vec3 a, ice_vecmath_vec3 b, ice_vecmath_vec3 c);
ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_vec3_tostring(ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_vec3_equ(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_transform_mat3(ice_vecmath_vec3 v, ice_vecmath_mat3 m);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_transform_mat4(ice_vecmath_vec3 v, ice_vecmath_mat4 m);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_transform_mat4(ice_vecmath_vec3 v, ice_vecmath_quat q);


/* ============================== module: vec4 ============================== */

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_zero(void);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_one(void);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_add(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_addval(ice_vecmath_vec4 v, double n);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_sub(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_subval(ice_vecmath_vec4 v, double n);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_mul(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_div(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_scale(ice_vecmath_vec4 v, double scalar);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_scale_and_add(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2, double scalar);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_dot(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_cross(ice_vecmath_vec4 a, ice_vecmath_vec4 b, ice_vecmath_vec4 c);
/* ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_rand(double scale); */
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_neg(ice_vecmath_vec4 v);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_inv(ice_vecmath_vec4 v);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_abs(ice_vecmath_vec4 v);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_ceil(ice_vecmath_vec4 v);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_floor(ice_vecmath_vec4 v);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_round(ice_vecmath_vec4 v);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_min(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_max(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_len(ice_vecmath_vec4 v);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_sqrlen(ice_vecmath_vec4 v);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_dist(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_sqrdist(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_angle(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_norm(ice_vecmath_vec4 v);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_lerp(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2, double amount);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_reflect(ice_vecmath_vec4 v, ice_vecmath_vec4 normal);
ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_vec4_tostring(ice_vecmath_vec4 v);
ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_vec4_equ(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_transform_mat4(ice_vecmath_vec4 v, ice_vecmath_mat4 m);
ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_transform_quat(ice_vecmath_vec4 v, ice_vecmath_quat q);


/* ============================== module: quat ============================== */

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_id(void);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_zero(void);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_one(void);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_add(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_addval(ice_vecmath_quat q, double n);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_sub(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_subval(ice_vecmath_quat q, double n);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_mul(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_div(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_scale(ice_vecmath_quat q, double scalar);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_scale_and_add(ice_vecmath_quat q, double add, double scalar);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_scale_and_add_quat(ice_vecmath_quat q1, ice_vecmath_quat q2, double scalar);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_calc_width(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_ln(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_exp(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_pow(ice_vecmath_quat q, double n);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_dot(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_cross(ice_vecmath_quat a, ice_vecmath_quat b, ice_vecmath_quat c);
/* ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rand(void); */
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_neg(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_inv(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_abs(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_ceil(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_floor(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_round(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_min(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_max(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_len(ice_vecmath_quat q);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_sqrlen(ice_vecmath_quat q);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_dist(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_sqrdist(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_angle(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_norm(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_lerp(ice_vecmath_quat q1, ice_vecmath_quat q2, double amount);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_nlerp(ice_vecmath_quat q1, ice_vecmath_quat q2, double amount);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_slerp(ice_vecmath_quat q1, ice_vecmath_quat q2, double t);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_sqlerp(ice_vecmath_quat a, ice_vecmath_quat b, ice_vecmath_quat c, ice_vecmath_quat d, double t);
ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_quat_tostring(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_quat_equ(ice_vecmath_quat q1, ice_vecmath_quat q2);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_conjugate(ice_vecmath_quat q);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_from_axis_angle(ice_vecmath_vec3 axis, double angle);
ICE_VECMATH_API void ICE_VECMATH_CALLCONV ice_vecmath_quat_to_axis_angle(ice_vecmath_quat q, ice_vecmath_vec3 *axis, double *angle);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_transform(ice_vecmath_quat q, ice_vecmath_mat4 m);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rotate_to(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rotate_x(ice_vecmath_quat q, double rad);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rotate_y(ice_vecmath_quat q, double rad);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rotate_z(ice_vecmath_quat q, double rad);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_vec3_to_vec3(ice_vecmath_vec3 from, ice_vecmath_vec3 to);
ICE_VECMATH_API void ICE_VECMATH_CALLCONV ice_vecmath_quat_set_axis(ice_vecmath_quat *q, ice_vecmath_vec3 view, ice_vecmath_vec3 right, ice_vecmath_vec3 up);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_from_mat3(ice_vecmath_mat3 m);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_from_mat4(ice_vecmath_mat4 m);
ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_from_euler(double pitch, double yaw, double roll);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_quat_to_euler(ice_vecmath_quat q);


/* ============================== module: quat2 ============================== */

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_id(void);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_zero(void);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_one(void);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_add(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_addval(ice_vecmath_quat2 q, double n);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_sub(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_subval(ice_vecmath_quat2 q, double n);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_mul(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_div(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_scale(ice_vecmath_quat2 q, double scalar);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_scale_and_add(ice_vecmath_quat2 q, double add, double scalar);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_scale_and_add_quat(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2, double scalar);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_calc_width(ice_vecmath_quat2 q);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_dot(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_neg(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_inv(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_abs(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_ceil(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_floor(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_round(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_min(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_max(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_len(ice_vecmath_quat2 q);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_sqrlen(ice_vecmath_quat2 q);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_dist(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_sqrdist(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_angle(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_norm(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_lerp(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2, double amount);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_nlerp(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2, double amount);
ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_quat2_tostring(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_quat2_equ(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_conjugate(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_from_axis_angle(ice_vecmath_quat q, ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_quat2_to_axis_angle(ice_vecmath_quat2 q);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_translate(ice_vecmath_quat2 q, ice_vecmath_vec3 v);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_rotate_by_quat_append(ice_vecmath_quat2 q1, ice_vecmath_quat q2);
ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_rotate_by_quat_prepend(ice_vecmath_quat q1, ice_vecmath_quat2 q2);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_VECMATH_IMPL)

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


/* ============================== module: util ============================== */

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_clamp(double value, double min, double max) {
    double res = ((value < min) ? min : value);
    
    return ((res > max) ? max : res);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_lerp(double begin_value, double end_value, double amount) {
    return (begin_value + amount * (end_value - begin_value));
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_norm(double value, double begin_value, double end_value) {
    return (double) ((value - begin_value) / (end_value - begin_value));
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_remap(double value, double input_begin_value, double input_end_value, double output_begin_value, double output_end_value) {
    return (double) ((value - input_begin_value) / (input_end_value - input_begin_value) * (output_end_value - output_begin_value) + output_begin_value);
}


/* ============================== module: init ============================== */

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_create(double x, double y) {
    ice_vecmath_vec2 res;

    res.x = x;
    res.y = y;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_create(double x, double y, double z) {
    ice_vecmath_vec3 res;

    res.x = x;
    res.y = y;
    res.z = z;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_create(double x, double y, double z, double w) {
    ice_vecmath_vec4 res;

    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_create(double q[4]) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) res.data[i] = q[i];

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_create(double q[8]) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) res.data[i] = q[i];

    return res;
}

ICE_VECMATH_API ice_vecmath_mat2 ICE_VECMATH_CALLCONV ice_vecmath_mat2_create(double m[4]) {
    ice_vecmath_mat2 res;
    unsigned i;

    for (i = 0; i < 4; i++) res.data[i] = m[i];

    return res;
}

ICE_VECMATH_API ice_vecmath_mat2d ICE_VECMATH_CALLCONV ice_vecmath_mat2d_create(double m[6]) {
    ice_vecmath_mat2d res;
    unsigned i;

    for (i = 0; i < 6; i++) res.data[i] = m[i];

    return res;
}

ICE_VECMATH_API ice_vecmath_mat3 ICE_VECMATH_CALLCONV ice_vecmath_mat3_create(double m[9]) {
    ice_vecmath_mat3 res;
    unsigned i;

    for (i = 0; i < 9; i++) res.data[i] = m[i];

    return res;
}

ICE_VECMATH_API ice_vecmath_mat4 ICE_VECMATH_CALLCONV ice_vecmath_mat4_create(double m[16]) {
    ice_vecmath_mat4 res;
    unsigned i;

    for (i = 0; i < 16; i++) res.data[i] = m[i];

    return res;
}


/* ============================== module: vec2 ============================== */

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_zero(void) {
    ice_vecmath_vec2 res;
    res.x = res.y = 0.0;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_one(void) {
    ice_vecmath_vec2 res;
    res.x = res.y = 1.0;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_add(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    ice_vecmath_vec2 res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_addval(ice_vecmath_vec2 v, double n) {
    ice_vecmath_vec2 res;

    res.x = v.x + n;
    res.y = v.y + n;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_sub(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    ice_vecmath_vec2 res;

    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_subval(ice_vecmath_vec2 v, double n) {
    ice_vecmath_vec2 res;

    res.x = v.x - n;
    res.y = v.y - n;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_mul(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    ice_vecmath_vec2 res;

    res.x = v1.x * v2.x;
    res.y = v1.y * v2.y;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_div(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    ice_vecmath_vec2 res;

    res.x = (double) (v1.x / v2.x);
    res.y = (double) (v1.y / v2.y);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_scale(ice_vecmath_vec2 v, double scalar) {
    ice_vecmath_vec2 res;

    res.x = v.x * scalar;
    res.y = v.y * scalar;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_scale_and_add(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2, double scalar) {
    ice_vecmath_vec2 res;

    res.x = (v1.x + v2.x) * scalar;
    res.y = (v1.y + v2.y) * scalar;

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_dot(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y);
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec2_cross(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    ice_vecmath_vec3 res;
    
    res.x = res.y = 0.0;
    res.z = (v1.x * v2.y) - (v1.y * v2.x);

    return res;
}

/* ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_rand(double scale) {} */

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_neg(ice_vecmath_vec2 v) {
    ice_vecmath_vec2 res;
    
    res.x = -v.x;
    res.y = -v.y;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_inv(ice_vecmath_vec2 v) {
    ice_vecmath_vec2 res;
    
    res.x = (double) (1.0 / v.x);
    res.y = (double) (1.0 / v.y);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_abs(ice_vecmath_vec2 v) {
    ice_vecmath_vec2 res;

    res.x = ((v.x < 0) ? -v.x : v.x);
    res.y = ((v.y < 0) ? -v.y : v.y);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_ceil(ice_vecmath_vec2 v) {
    ice_vecmath_vec2 res;

    res.x = ceil(v.x);
    res.y = ceil(v.y);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_floor(ice_vecmath_vec2 v) {
    ice_vecmath_vec2 res;

    res.x = floor(v.x);
    res.y = floor(v.y);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_round(ice_vecmath_vec2 v) {
    ice_vecmath_vec2 res;

    res.x = round(v.x);
    res.y = round(v.y);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_min(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    ice_vecmath_vec2 res;

    res.x = ((v1.x < v2.x) ? v1.x : v2.x);
    res.y = ((v1.y < v2.y) ? v1.y : v2.y);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_max(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    ice_vecmath_vec2 res;

    res.x = ((v1.x > v2.x) ? v1.x : v2.x);
    res.y = ((v1.y > v2.y) ? v1.y : v2.y);

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_len(ice_vecmath_vec2 v) {
    return sqrt((v.x * v.x) + (v.y * v.y));
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_sqrlen(ice_vecmath_vec2 v) {
    return (v.x * v.x) + (v.y * v.y);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_dist(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    double sqr_dist_x = ((v1.x - v2.x) * (v1.x - v2.x));
    double sqr_dist_y = ((v1.y - v2.y) * (v1.y - v2.y));

    return sqrt(sqr_dist_x + sqr_dist_y);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_sqrdist(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    double sqr_dist_x = ((v1.x - v2.x) * (v1.x - v2.x));
    double sqr_dist_y = ((v1.y - v2.y) * (v1.y - v2.y));

    return (sqr_dist_x + sqr_dist_y);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec2_angle(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    return atan2(v2.y - v1.y, v2.x - v1.x) * (180.0 / 3.14);
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_norm(ice_vecmath_vec2 v) {
    double len = ice_vecmath_vec2_len(v);

    if (len <= 0) return v;
    
    return ice_vecmath_vec2_scale(v, (double) (1.0 / len));
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_lerp(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2, double amount) {
    ice_math_vec2 res;

    res.x = v1.x + (amount * (v2.x - v1.x));
    res.y = v1.y + (amount * (v2.y - v1.y));

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_reflect(ice_vecmath_vec2 v, ice_vecmath_vec2 normal) {
    ice_vecmath_vec2 res;
    double dot = ice_math_vec2_dot(v, normal);

    res.x = v.x - ((2 * normal.x) * dot);
    res.y = v.y - ((2 * normal.y) * dot);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_rotate(ice_vecmath_vec2 v, double degs) {
    ice_vecmath_vec2 res;

    double rads = (double) (degs * (3.14 / 180.0));
    double rad_sin = sin(rads);
    double rad_cos = cos(rads);
    
    res.x = (v.x * rad_cos) - (v.y * rad_sin);
    res.y = (v.x * rad_sin) - (v.y * rad_cos);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_towards(ice_vecmath_vec2 v, ice_vecmath_vec2 target, double maxdist) {
    ice_vecmath_vec2 res;

    double dx = target.x - v.x;
    double dy = target.y - v.y;
    double dist_sqr = (dx * dx) + (dy * dy);
    double dist = sqrt(dist_sqr);
    double maxdist_sqr = (maxdist * maxdist);

    if ((dist_sqr == 0.0) || ((maxdist >= 0.0) && (dist_sqr <= maxdist_sqr))) {
        return target;
    }

    res.x = v.x + (double) (dx / (dist * maxdist));
    res.y = v.y + (double) (dy / (dist * maxdist));

    return res;
}

ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_vec2_tostring(ice_vecmath_vec2 v) {
    char buff[64];
    sprintf(buff, sizeof(buff), "vec2(%f, %f)", v.x, v.y);
    
    return buff;
}

ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_vec2_equ(ice_vecmath_vec2 v1, ice_vecmath_vec2 v2) {
    ice_vecmath_bool case1, case2;

    case1 = ((v1.x == v2.x) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);
    case2 = ((v1.y == v2.y) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);

    return ((case1 == case2) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_transform_mat2(ice_vecmath_vec2 v, ice_vecmath_mat2 m) {
    ice_vecmath_vec2 res;

    res.x = m[0] * v.x + m[2] * v.y;
    res.y = m[1] * v.x + m[3] * v.y;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_transform_mat2d(ice_vecmath_vec2 v, ice_vecmath_mat2d m) {
    ice_vecmath_vec2 res;

    res.x = m[0] * v.x + m[2] * v.y + m[4];
    res.y = m[1] * v.x + m[3] * v.y + m[5];

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_transform_mat3(ice_vecmath_vec2 v, ice_vecmath_mat3 m) {
    ice_vecmath_vec2 res;

    res.x = m[0] * v.x + m[3] * v.y + m[6];
    res.y = m[1] * v.x + m[4] * v.y + m[7];

    return res;
}

ICE_VECMATH_API ice_vecmath_vec2 ICE_VECMATH_CALLCONV ice_vecmath_vec2_transform_mat4(ice_vecmath_vec2 v, ice_vecmath_mat4 m) {
    ice_vecmath_vec2 res;

    res.x = m[0] * v.x + m[4] * v.y + m[12];
    res.y = m[1] * v.x + m[5] * v.y + m[13];

    return res;
}


/* ============================== module: vec3 ============================== */

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_zero(void) {
    ice_vecmath_vec3 res;
    res.x = res.y = res.z = 0.0;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_one(void) {
    ice_vecmath_vec3 res;
    res.x = res.y = res.z = 1.0;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_add(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    ice_vecmath_vec3 res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_addval(ice_vecmath_vec3 v, double n) {
    ice_vecmath_vec3 res;

    res.x = v.x + n;
    res.y = v.y + n;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_sub(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    ice_vecmath_vec3 res;

    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_subval(ice_vecmath_vec3 v, double n) {
    ice_vecmath_vec3 res;

    res.x = v.x - n;
    res.y = v.y - n;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_mul(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    ice_vecmath_vec3 res;

    res.x = v1.x * v2.x;
    res.y = v1.y * v2.y;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_div(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    ice_vecmath_vec3 res;

    res.x = (double) (v1.x / v2.x);
    res.y = (double) (v1.y / v2.y);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_scale(ice_vecmath_vec3 v, double scalar) {
    ice_vecmath_vec3 res;

    res.x = v.x * scalar;
    res.y = v.y * scalar;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_scale_and_add(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double scalar) {
    ice_vecmath_vec3 res;

    res.x = (v1.x + v2.x) * scalar;
    res.y = (v1.y + v2.y) * scalar;

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_dot(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_cross(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    ice_vecmath_vec3 res;

    res.x = (v1.y * v2.z) - (v1.z * v2.y);
    res.y = (v1.z * v2.x) - (v1.x * v2.z);
    res.z = (v1.x * v2.y) - (v1.y * v2.x);
    
    return res;
}

/* ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rand(double scale) {} */

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_neg(ice_vecmath_vec3 v) {
    ice_vecmath_vec3 res;
    
    res.x = -v.x;
    res.y = -v.y;
    res.z = -v.z;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_inv(ice_vecmath_vec3 v) {
    ice_vecmath_vec3 res;
    
    res.x = (double) (1.0 / v.x);
    res.y = (double) (1.0 / v.y);
    res.z = (double) (1.0 / v.z);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_abs(ice_vecmath_vec3 v) {
    ice_vecmath_vec3 res;

    res.x = ((v.x < 0) ? -v.x : v.x);
    res.y = ((v.y < 0) ? -v.y : v.y);
    res.z = ((v.z < 0) ? -v.z : v.z);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_ceil(ice_vecmath_vec3 v) {
    ice_vecmath_vec3 res;

    res.x = ceil(v.x);
    res.y = ceil(v.y);
    res.z = ceil(v.z);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_floor(ice_vecmath_vec3 v) {
    ice_vecmath_vec3 res;

    res.x = floor(v.x);
    res.y = floor(v.y);
    res.z = floor(v.z);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_round(ice_vecmath_vec3 v) {
    ice_vecmath_vec3 res;

    res.x = round(v.x);
    res.y = round(v.y);
    res.z = round(v.z);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_min(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    ice_vecmath_vec3 res;

    res.x = ((v1.x < v2.x) ? v1.x : v2.x);
    res.y = ((v1.y < v2.y) ? v1.y : v2.y);
    res.z = ((v1.z < v2.z) ? v1.z : v2.z);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_max(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    ice_vecmath_vec3 res;

    res.x = ((v1.x > v2.x) ? v1.x : v2.x);
    res.y = ((v1.y > v2.y) ? v1.y : v2.y);
    res.z = ((v1.z > v2.z) ? v1.z : v2.z);

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_len(ice_vecmath_vec3 v) {
    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_sqrlen(ice_vecmath_vec3 v) {
    return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_dist(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    double sqr_dist_x = ((v1.x - v2.x) * (v1.x - v2.x));
    double sqr_dist_y = ((v1.y - v2.y) * (v1.y - v2.y));
    double sqr_dist_z = ((v1.z - v2.z) * (v1.z - v2.z));

    return sqrt(sqr_dist_x + sqr_dist_y + sqr_dist_z);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_sqrdist(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    double sqr_dist_x = ((v1.x - v2.x) * (v1.x - v2.x));
    double sqr_dist_y = ((v1.y - v2.y) * (v1.y - v2.y));
    double sqr_dist_z = ((v1.z - v2.z) * (v1.z - v2.z));

    return (sqr_dist_x + sqr_dist_y + sqr_dist_z);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec3_angle(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    double v1_len = ice_vecmath_vec3_len(v1);
    double v2_len = ice_vecmath_vec3_len(v2);
    double dot = ice_vecmath_vec3_dot(v1, v2);
    
    return acos(dot / (v1_len * v2_len)) * (180.0 / 3.14);
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_norm(ice_vecmath_vec3 v) {
    double len = ice_vecmath_vec3_len(v);
    if (len == 0) len = 1.0;
    
    return ice_vecmath_vec3_scale(v, (double) (1.0 / len));
}

ICE_VECMATH_API void ICE_VECMATH_CALLCONV ice_vecmath_vec3_ortho_norm(ice_vecmath_vec3 *v1, ice_vecmath_vec3 *v2) {
    ice_vecmath_vec3 vn, vecross;
    
    *v1 = ice_vecmath_vec3_norm(*v1);
    vecross = ice_vecmath_vec3_cross(*v1, *v2);
    vn = ice_vecmath_vec3_norm(vecross);
    *v2 = ice_vecmath_vec3_cross(vn, *v1);
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_lerp(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double amount) {
    ice_vecmath_vec3 res;

    res.x = v1.x + amount * (v2.x - v1.x);
    res.y = v1.y + amount * (v2.y - v1.y);
    res.y = v1.z + amount * (v2.z - v1.z);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_reflect(ice_vecmath_vec3 v, ice_vecmath_vec3 normal) {
    ice_vecmath_vec3 res;
    double dot = ice_vecmath_vec3_dot(v, normal);

    res.x = v.x - (2.0 * normal.x) * dot;
    res.y = v.y - (2.0 * normal.y) * dot;
    res.z = v.z - (2.0 * normal.z) * dot;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_perpendicular(ice_vecmath_vec3 v) {
    ice_vecmath_vec3 vabs = ice_vecmath_vec3_abs(v);
    ice_vecmath_vec3 card_axis = ice_vecmath_vec3_create(1, 0, 0);

    if (vabs.y < vabs.x) {
        vabs.x = vabs.y;
        card_axis.x = card_axis.z = 0.0;
        card_axis.y = 1.0;
    }

    if (vabs.z < vabs.x) {
        card_axis.x = card_axis.y = 0.0;
        card_axis.z = 1.0;
    }

    return ice_vecmath_vec3_cross(v, card_axis);
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_hermite(ice_vecmath_vec3 a, ice_vecmath_vec3 b, ice_vecmath_vec3 c, ice_vecmath_vec3 d, double t) {
    ice_vecmath_vec3 res;

    double sqr_t = t * t;
    double f1 = sqr_t * (2.0 * t - 3.0) + 1.0;
    double f2 = sqr_t * (t - 2.0) + t;
    double f3 = sqr_t * (t - 1.0);
    double f4 = sqr_t * (3.0 - 2.0 * t);

    res.x = a.x * f1 + b.x * f2 + c.x * f3 + d.x * f4;
    res.y = a.y * f1 + b.y * f2 + c.y * f3 + d.y * f4;
    res.z = a.z * f1 + b.z * f2 + c.z * f3 + d.z * f4;
    
    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_bezier(ice_vecmath_vec3 a, ice_vecmath_vec3 b, ice_vecmath_vec3 c, ice_vecmath_vec3 d, double t) {
    ice_vecmath_vec3 res;

    double n = 1.0 - t;
    double f1 = n * n * n;
    double f2 = 3.0 * t * n * n;
    double f3 = 3.0 * (t * t) * n;
    double f4 = t * t * t;

    res.x = a.x * f1 + b.x * f2 + c.x * f3 + d.x * f4;
    res.y = a.y * f1 + b.y * f2 + c.y * f3 + d.y * f4;
    res.z = a.z * f1 + b.z * f2 + c.z * f3 + d.z * f4;
    
    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_transform(ice_vecmath_vec3 v, ice_vecmath_mat4 m) {
    ice_vecmath_vec3 res;

    res.x = (m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12]);
    res.y = (m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13]);
    res.z = (m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14]);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rotate_by_quat(ice_vecmath_vec3 v, ice_vecmath_quat q) {
    ice_vecmath_vec3 res;

    double sqr_q0 = q.data[0] * q.data[0];
    double sqr_q1 = q.data[1] * q.data[1];
    double sqr_q2 = q.data[2] * q.data[2];
    double sqr_q3 = q.data[3] * q.data[3];

    res.x = v.x * (sqr_q0 + sqr_q3 - sqr_q1 - sqr_q2) + v.y * (2.0 * (q.data[0] * q.data[1]) - 2.0 * (q.data[3] * q.data[2])) + v.z * (2.0 * (q.data[0] * q.data[2]) + 2.0 * (q.data[3] * q.data[1]));
    res.y = v.x * (2.0 * q.data[3] * q.data[2] + 2.0 * q.data[0] * q.data[1]) + v.y * (sqr_q3 - sqr_q0 + sqr_q1 - sqr_q2) + v.z * (-2.0 * q.data[3] * q.data[0] + 2.0 * q.data[1] * q.data[2]);
    res.z = v.x * (-2.0 * q.data[3] * q.data[1] + 2.0 * q.data[0] * q.data[2]) + v.y * (2.0 * q.data[3] * q.data[0] + 2 * q.data[1] * q.data[2]) + v.z * (sqr_q3 - sqr_q0 - sqr_q1 + sqr_q2);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rotate_x(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double rad) {
    ice_vecmath_vec3 res;
    ice_vecmath_vec3 sub = ice_vecmath_vec3_sub(v1, v2);

    double rad_sin = sin(rad);
    double rad_cos = cos(rad);

    res.x = sub.x + v2.x;
    res.y = (sub.y * rad_cos - sub.z * rad_sin) + v2.y;
    res.z = (sub.y * rad_sin - sub.z * rad_cos) + v2.z;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rotate_y(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double rad) {
    ice_vecmath_vec3 res;
    ice_vecmath_vec3 sub = ice_vecmath_vec3_sub(v1, v2);

    double rad_sin = sin(rad);
    double rad_cos = cos(rad);

    res.x = (sub.z * rad_sin + sub.x * rad_cos) + v2.x;
    res.y = sub.y + v2.y;
    res.z = (sub.z * rad_cos - sub.x * rad_sin) + v2.z;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_rotate_z(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2, double rad) {
    ice_vecmath_vec3 res;
    ice_vecmath_vec3 sub = ice_vecmath_vec3_sub(v1, v2);

    double rad_sin = sin(rad);
    double rad_cos = cos(rad);

    res.x = (sub.x * rad_cos - sub.y * rad_sin);
    res.y = (sub.x * rad_sin + sub.y * rad_cos);
    res.z = sub.z + v2.z;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_barycenter(ice_vecmath_vec3 p, ice_vecmath_vec3 a, ice_vecmath_vec3 b, ice_vecmath_vec3 c) {
    ice_vecmath_vec3 res;

    ice_vecmath_vec3 v0 = ice_vecmath_vec3_sub(b, a);
    ice_vecmath_vec3 v1 = ice_vecmath_vec3_sub(c, a);
    ice_vecmath_vec3 v2 = ice_vecmath_vec3_sub(p, a);

    double d00 = ice_vecmath_vec3_dot(v0, v0);
    double d01 = ice_vecmath_vec3_dot(v0, v1);
    double d11 = ice_vecmath_vec3_dot(v1, v1);
    double d20 = ice_vecmath_vec3_dot(v2, v0);
    double d21 = ice_vecmath_vec3_dot(v2, v1);
    double denom = d00 * d11 - d01 * d01;
    
    double d1 = (d00 * d21 - d01 * d20);
    double d2 = (d11 * d20 - d01 * d21);

    res.x = 1.0 - ((d1 / denom) + (d2 / denom));
    res.y = d2 / denom;
    res.z = d1 / denom;

    return res;
}

ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_vec3_tostring(ice_vecmath_vec3 v) {
    char buff[64];
    sprintf(buff, sizeof(buff), "vec3(%f, %f, %f)", v.x, v.y, v.z);
    
    return buff;
}

ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_vec3_equ(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    ice_vecmath_bool cond1 = ((v1.x == v2.x) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);
    ice_vecmath_bool cond2 = ((v1.y == v2.y) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);
    ice_vecmath_bool cond3 = ((v1.z == v2.z) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);

    ice_vecmath_bool res = ((cond1 == ICE_VECMATH_TRUE) &&
                            (cond2 == ICE_VECMATH_TRUE) &&
                            (cond3 == ICE_VECMATH_TRUE)) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE;
    
    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_transform_mat3(ice_vecmath_vec3 v, ice_vecmath_mat3 m) {
    ice_vecmath_vec3 res;

    res.x = v.x * m[0] + v.y * m[3] + v.z * m[6];
    res.y = v.x * m[1] + v.y * m[4] + v.z * m[7];
    res.z = v.x * m[2] + v.y * m[5] + v.z * m[8];

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_transform_mat4(ice_vecmath_vec3 v, ice_vecmath_mat4 m) {
    ice_vecmath_vec3 res;
    double w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15];

    res.x = (m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12]) / w;
    res.x = (m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13]) / w;
    res.x = (m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14]) / w;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_vec3_transform_mat4(ice_vecmath_vec3 v, ice_vecmath_quat q) {
    ice_vecmath_vec3 res;

    double uvx = (q.data[1] * v.z - q.data[2] * v.y) * (q.data[3] * 2.0);
    double uvy = (q.data[2] * v.x - q.data[0] * v.z) * (q.data[3] * 2.0);
    double uvz = (q.data[0] * v.y - q.data[1] * v.x) * (q.data[3] * 2.0);
    double uuvx = (q.data[1] * uvz - q.data[2] * uvy) * 2.0;
    double uuvy = (q.data[2] * uvx - q.data[0] * uvz) * 2.0;
    double uuvz = (q.data[0] * uvy - q.data[1] * uvx) * 2.0;

    res.x = v.x + uvx + uuvx;
    res.y = v.y + uvy + uuvy;
    res.z = v.z + uvz + uuvz;

    return res;
}


/* ============================== module: vec4 ============================== */

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_zero(void) {
    ice_vecmath_vec4 res;
    res.x = res.y = res.z = res.w = 0.0;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_one(void) {
    ice_vecmath_vec4 res;
    res.x = res.y = res.z = res.w = 1.0;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_add(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    ice_vecmath_vec4 res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    res.w = v1.w + v2.w;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_addval(ice_vecmath_vec4 v, double n) {
    ice_vecmath_vec4 res;

    res.x = v.x + n;
    res.y = v.y + n;
    res.z = v.z + n;
    res.w = v.w + n;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_sub(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    ice_vecmath_vec4 res;

    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    res.w = v1.w - v2.w;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_subval(ice_vecmath_vec4 v, double n) {
    ice_vecmath_vec4 res;

    res.x = v.x - n;
    res.y = v.y - n;
    res.z = v.z - n;
    res.w = v.w - n;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_mul(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    ice_vecmath_vec4 res;

    res.x = v1.x * v2.x;
    res.y = v1.y * v2.y;
    res.z = v1.z * v2.z;
    res.w = v1.w * v2.w;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_div(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    ice_vecmath_vec4 res;

    res.x = v1.x / v2.x;
    res.y = v1.y / v2.y;
    res.z = v1.z / v2.z;
    res.w = v1.w / v2.w;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_scale(ice_vecmath_vec4 v, double scalar) {
    ice_vecmath_vec4 res;

    res.x = v.x * scalar;
    res.y = v.y * scalar;
    res.z = v.z * scalar;
    res.w = v.w * scalar;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_scale_and_add(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2, double scalar) {
    ice_vecmath_vec4 res;

    res.x = (v1.x + v2.x) * scalar;
    res.y = (v1.y + v2.y) * scalar;
    res.z = (v1.z + v2.z) * scalar;
    res.w = (v1.w + v2.w) * scalar;

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_dot(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_cross(ice_vecmath_vec4 a, ice_vecmath_vec4 b, ice_vecmath_vec4 c) {
    ice_vecmath_vec4 res;

    double n1 = (b.z * c.w - b.w * c.z);
    double n2 = (b.y * c.w - b.w * c.y);
    double n3 = (b.y * c.z - b.z * c.y);
    double n4 = (b.x * c.w - b.w * c.x);
    double n5 = (b.x * c.z - b.z * c.x);
    double n6 = (b.x * c.y - b.y * c.x);

    res.x = a.y * n1 - a.z * n2 + a.w * n3;
    res.y = -(a.x * n1) + a.z * n4 - a.w * n5;
    res.z = a.x * n2 - a.y * n4 + a.w * n6;
    res.w = -(a.x * n3) + a.y * n5 - a.z * n6;
    
    return res;
}

/* ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_rand(double scale) {} */

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_neg(ice_vecmath_vec4 v) {
    ice_vecmath_vec4 res;

    res.x = -v.x;
    res.y = -v.y;
    res.z = -v.z;
    res.w = -v.w;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_inv(ice_vecmath_vec4 v) {
    ice_vecmath_vec4 res;

    res.x = (double) (1.0 / v.x);
    res.y = (double) (1.0 / v.y);
    res.z = (double) (1.0 / v.z);
    res.w = (double) (1.0 / v.w);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_abs(ice_vecmath_vec4 v) {
    ice_vecmath_vec4 res;

    res.x = ((v.x < 0) ? -v.x : v.x);
    res.y = ((v.y < 0) ? -v.y : v.y);
    res.z = ((v.z < 0) ? -v.z : v.z);
    res.w = ((v.w < 0) ? -v.w : v.w);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_ceil(ice_vecmath_vec4 v) {
    ice_vecmath_vec4 res;

    res.x = ceil(v.x);
    res.y = ceil(v.y);
    res.z = ceil(v.z);
    res.w = ceil(v.w);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_floor(ice_vecmath_vec4 v) {
    ice_vecmath_vec4 res;

    res.x = floor(v.x);
    res.y = floor(v.y);
    res.z = floor(v.z);
    res.w = floor(v.w);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_round(ice_vecmath_vec4 v) {
    ice_vecmath_vec4 res;

    res.x = round(v.x);
    res.y = round(v.y);
    res.z = round(v.z);
    res.w = round(v.w);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_min(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    ice_vecmath_vec4 res;

    res.x = ((v1.x < v2.x) ? v1.x : v2.x);
    res.y = ((v1.y < v2.y) ? v1.y : v2.y);
    res.z = ((v1.z < v2.z) ? v1.z : v2.z);
    res.w = ((v1.w < v2.w) ? v1.w : v2.w);

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_max(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    ice_vecmath_vec4 res;

    res.x = ((v1.x > v2.x) ? v1.x : v2.x);
    res.y = ((v1.y > v2.y) ? v1.y : v2.y);
    res.z = ((v1.z > v2.z) ? v1.z : v2.z);
    res.w = ((v1.w > v2.w) ? v1.w : v2.w);

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_len(ice_vecmath_vec4 v) {
    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_sqrlen(ice_vecmath_vec4 v) {
    return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_dist(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    double sqr_dist_x = (v1.x - v2.x) * (v1.x - v2.x);
    double sqr_dist_y = (v1.y - v2.y) * (v1.y - v2.y);
    double sqr_dist_z = (v1.z - v2.z) * (v1.z - v2.z);
    double sqr_dist_w = (v1.w - v2.w) * (v1.w - v2.w);

    return sqrt((sqr_dist_x + sqr_dist_y + sqr_dist_z + sqr_dist_w));
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_sqrdist(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    double sqr_dist_x = (v1.x - v2.x) * (v1.x - v2.x);
    double sqr_dist_y = (v1.y - v2.y) * (v1.y - v2.y);
    double sqr_dist_z = (v1.z - v2.z) * (v1.z - v2.z);
    double sqr_dist_w = (v1.w - v2.w) * (v1.w - v2.w);

    return ((sqr_dist_x + sqr_dist_y + sqr_dist_z + sqr_dist_w));
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_vec4_angle(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    double v1_len = ice_vecmath_vec4_len(v1);
    double v2_len = ice_vecmath_vec4_len(v2);
    double dot = ice_vecmath_vec4_dot(v1, v2);
    
    return acos(dot / (v1_len * v2_len)) * (180.0 / 3.14);
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_norm(ice_vecmath_vec4 v) {
    double len = ice_vecmath_vec4_len(v);
    if (len == 0) len = 1.0;
    
    return ice_vecmath_vec4_scale(v, (double) (1.0 / len));
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_lerp(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2, double amount) {
    ice_vecmath_vec4 res;

    res.x = v1.x + amount * (v2.x - v1.x);
    res.y = v1.y + amount * (v2.y - v1.y);
    res.z = v1.z + amount * (v2.z - v1.z);
    res.w = v1.w + amount * (v2.w - v1.w);
    
    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_reflect(ice_vecmath_vec4 v, ice_vecmath_vec4 normal) {
    ice_vecmath_vec4 res;
    double dot = ice_vecmath_vec4_dot(v, normal);

    res.x = v.x - (2.0 * normal.x) * dot;
    res.y = v.y - (2.0 * normal.y) * dot;
    res.z = v.z - (2.0 * normal.z) * dot;
    res.w = v.w - (2.0 * normal.w) * dot;

    return res;
}

ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_vec4_tostring(ice_vecmath_vec4 v) {
    char buff[64];
    sprintf(buff, sizeof(buff), "vec4(%f, %f, %f, %f)", v.x, v.y, v.z, v.w);
    
    return buff;
}

ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_vec4_equ(ice_vecmath_vec4 v1, ice_vecmath_vec4 v2) {
    ice_vecmath_bool cond1 = ((v1.x == v2.x) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);
    ice_vecmath_bool cond2 = ((v1.y == v2.y) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);
    ice_vecmath_bool cond3 = ((v1.z == v2.z) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);
    ice_vecmath_bool cond4 = ((v1.w == v2.w) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE);

    ice_vecmath_bool res = ((cond1 == ICE_VECMATH_TRUE) &&
                            (cond2 == ICE_VECMATH_TRUE) &&
                            (cond3 == ICE_VECMATH_TRUE) &&
                            (cond4 == ICE_VECMATH_TRUE)) ? ICE_VECMATH_TRUE : ICE_VECMATH_FALSE;
    
    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_transform_mat4(ice_vecmath_vec4 v, ice_vecmath_mat4 m) {
    ice_vecmath_vec4 res;

    res.x = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12] * v.w;
    res.y = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13] * v.w;
    res.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w;
    res.w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec4 ICE_VECMATH_CALLCONV ice_vecmath_vec4_transform_quat(ice_vecmath_vec4 v, ice_vecmath_quat q) {
    ice_vecmath_vec4 res;

    double ix = q.data[3] * v.x + q.data[1] * v.z - q.data[2] * v.y;
    double iy = q.data[3] * v.y + q.data[2] * v.x - q.data[0] * v.z;
    double iz = q.data[3] * v.z + q.data[0] * v.y - q.data[1] * v.x;
    double iw = -q.data[0] * v.x - q.data[1] * v.y - q.data[2] * v.z;

    res.x = ix * q.data[3] + iw * -q.data[0] + iy * -q.data[2] - iz * -q.data[1];
    res.y = iy * q.data[3] + iw * -q.data[1] + iz * -q.data[0] - ix * -q.data[2];
    res.z = iz * q.data[3] + iw * -q.data[2] + ix * -q.data[1] - iy * -q.data[0];
    res.w = v.w;

    return res;
}


/* ============================== module: quat ============================== */

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_id(void) {
    ice_vecmath_quat res;

    res.data[0] = res.data[1] = res.data[2] = 0.0;
    res.data[3] = 1.0;
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_zero(void) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res.data[i] = 0.0;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_one(void) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res.data[i] = 1.0;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_add(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res.data[i] = (q1.data[i] + q2.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_addval(ice_vecmath_quat q, double n) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res.data[i] = (q.data[i] + n);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_sub(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res.data[i] = (q1.data[i] - q2.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_subval(ice_vecmath_quat q, double n) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res.data[i] = (q.data[i] - n);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_mul(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    ice_vecmath_quat res;

    res.data[0] = q1.data[0] * q2.data[3] + q1.data[3] * q2.data[0] + q1.data[1] * q2.data[2] - q1.data[2] * q2.data[1];
    res.data[1] = q1.data[1] * q2.data[3] + q1.data[3] * q2.data[1] + q1.data[2] * q2.data[0] - q1.data[0] * q2.data[2];
    res.data[2] = q1.data[2] * q2.data[3] + q1.data[3] * q2.data[2] + q1.data[0] * q2.data[1] - q1.data[1] * q2.data[0];
    res.data[3] = q1.data[3] * q2.data[3] - q1.data[0] * q2.data[0] - q1.data[1] * q2.data[1] - q1.data[2] * q2.data[2];

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_div(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res.data[i] = (double) (q1.data[i] / q2.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_scale(ice_vecmath_quat q, double scalar) {
    ice_vecmath_quat res;

    double q0_scale = (q.data[0] * scalar);
    double q1_scale = (q.data[1] * scalar);
    double q2_scale = (q.data[2] * scalar);
    double q3_scale = (q.data[3] * scalar);
    
    res.data[0] = q0_scale + q3_scale + q1_scale - q2_scale;
    res.data[1] = q1_scale + q3_scale + q2_scale - q0_scale;
    res.data[2] = q2_scale + q3_scale + q0_scale - q1_scale;
    res.data[3] = q3_scale - q0_scale - q1_scale - q2_scale;

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_scale_and_add(ice_vecmath_quat q, double add, double scalar) {
    ice_vecmath_quat res;

    double q0_scale_add = (q.data[0] + add) * scalar;
    double q1_scale_add = (q.data[1] + add) * scalar;
    double q2_scale_add = (q.data[2] + add) * scalar;
    double q3_scale_add = (q.data[3] + add) * scalar;
    
    res.data[0] = q0_scale_add + q3_scale_add + q1_scale_add - q2_scale_add;
    res.data[1] = q1_scale_add + q3_scale_add + q2_scale_add - q0_scale_add;
    res.data[2] = q2_scale_add + q3_scale_add + q0_scale_add - q1_scale_add;
    res.data[3] = q3_scale_add - q0_scale_add - q1_scale_add - q2_scale_add;

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_scale_and_add_quat(ice_vecmath_quat q1, ice_vecmath_quat q2, double scalar) {
    ice_vecmath_quat res;

    double q0_scale_add = (q1.data[0] + q2.data[0]) * scalar;
    double q1_scale_add = (q1.data[1] + q2.data[1]) * scalar;
    double q2_scale_add = (q1.data[2] + q2.data[2]) * scalar;
    double q3_scale_add = (q1.data[3] + q2.data[3]) * scalar;
    
    res.data[0] = q0_scale_add + q3_scale_add + q1_scale_add - q2_scale_add;
    res.data[1] = q1_scale_add + q3_scale_add + q2_scale_add - q0_scale_add;
    res.data[2] = q2_scale_add + q3_scale_add + q0_scale_add - q1_scale_add;
    res.data[3] = q3_scale_add - q0_scale_add - q1_scale_add - q2_scale_add;

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_calc_width(ice_vecmath_quat q) {
    ice_vecmath_quat res;
    
    double n = (1.0 - q.data[0] * q.data[0] - q.data[1] * q.data[1] - q.data[2] * q.data[2]);
    n = ((n < 0) ? -n : n);

    res.data[0] = q.data[0];
    res.data[1] = q.data[1];
    res.data[2] = q.data[2];
    res.data[3] = sqrt(n);

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_ln(ice_vecmath_quat q) {
    ice_vecmath_quat res;

    double sqr_q0 = q.data[0] * q.data[0];
    double sqr_q1 = q.data[1] * q.data[1];
    double sqr_q2 = q.data[2] * q.data[2];
    double sqr_q3 = q.data[3] * q.data[3];

    double r = sqrt(sqr_q0 + sqr_q1 + sqr_q2);
    double t = ((r > 0) ? (atan2(r, q.data[3]) / r) : 0);

    res.data[0] = q.data[0] * t;
    res.data[1] = q.data[1] * t;
    res.data[2] = q.data[2] * t;
    res.data[3] = 0.5 * log(sqr_q0 + sqr_q1 + sqr_q2 + sqr_q3);

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_exp(ice_vecmath_quat q) {
    ice_vecmath_quat res;

    double sqr_q0 = q.data[0] * q.data[0];
    double sqr_q1 = q.data[1] * q.data[1];
    double sqr_q2 = q.data[2] * q.data[2];
    double sqr_q3 = q.data[3] * q.data[3];

    double r = sqrt(sqr_q0 + sqr_q1 + sqr_q2);
    double et = exp(q.data[3]);
    double s = ((r > 0) ? ((et * sin(r)) / r) : 0);

    res.data[0] = q.data[0] * s;
    res.data[1] = q.data[1] * s;
    res.data[2] = q.data[2] * s;
    res.data[3] = et * cos(r);
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_pow(ice_vecmath_quat q, double n) {
    ice_vecmath_quat res = ice_vecmath_quat_ln(q);
    res = ice_vecmath_quat_scale(res, n);
    res = ice_vecmath_quat_exp(res);

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_dot(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    double res = 0.0;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res += (q1.data[i] * q2.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_cross(ice_vecmath_quat a, ice_vecmath_quat b, ice_vecmath_quat c) {
    ice_vecmath_quat res;

    double n1 = (b.data[2] * c.data[3] - b.data[3] * c.data[2]);
    double n2 = (b.data[1] * c.data[3] - b.data[3] * c.data[1]);
    double n3 = (b.data[1] * c.data[2] - b.data[2] * c.data[1]);
    double n4 = (b.data[0] * c.data[3] - b.data[3] * c.data[0]);
    double n5 = (b.data[0] * c.data[2] - b.data[2] * c.data[0]);
    double n6 = (b.data[0] * c.data[1] - b.data[1] * c.data[0]);

    res.data[0] = a.data[1] * n1 - a.data[2] * n2 + a.data[3] * n3;
    res.data[1] = -(a.data[0] * n1) + a.data[2] * n4 - a.data[3] * n5;
    res.data[2] = a.data[0] * n2 - a.data[1] * n4 + a.data[3] * n6;
    res.data[3] = -(a.data[0] * n3) + a.data[1] * n5 - a.data[2] * n6;
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_neg(ice_vecmath_quat q) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res.data[i] = -q.data[i];
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_inv(ice_vecmath_quat q) {
    double len = ice_vecmath_quat_sqrlen(q);

    if (len != 0) {
        ice_vecmath_quat res;
        double neg_invlen = (double) -(1.0 / len);
        unsigned i;

        for (i = 0; i < 4; i++) {
            res.data[i] = q.data[i] * neg_invlen;
        }

        return res;
    }

    return q;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_abs(ice_vecmath_quat q) {
    ice_vecmath_quat res;
    unsigned i;
    
    for (i = 0; i < 4; i++) {
        res.data[i] = ((q.data[i] < 0) ? -q.data[i] : q.data[i]);
    }
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_ceil(ice_vecmath_quat q) {
    ice_vecmath_quat res;
    unsigned i;
    
    for (i = 0; i < 4; i++) {
        res.data[i] = ceil(q.data[i]);
    }
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_floor(ice_vecmath_quat q) {
    ice_vecmath_quat res;
    unsigned i;
    
    for (i = 0; i < 4; i++) {
        res.data[i] = floor(q.data[i]);
    }
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_round(ice_vecmath_quat q) {
    ice_vecmath_quat res;
    unsigned i;
    
    for (i = 0; i < 4; i++) {
        res.data[i] = round(q.data[i]);
    }
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_min(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    ice_vecmath_quat res;
    unsigned i;
    
    for (i = 0; i < 4; i++) {
        res.data[i] = ((q1.data[i] < q2.data[i]) ? q1.data[i] : q2.data[i]);
    }
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_max(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    ice_vecmath_quat res;
    unsigned i;
    
    for (i = 0; i < 4; i++) {
        res.data[i] = ((q1.data[i] > q2.data[i]) ? q1.data[i] : q2.data[i]);
    }
    
    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_len(ice_vecmath_quat q) {
    double len = 0.0;
    unsigned i;

    for (i = 0; i < 4; i++) {
        len += (q.data[i] * q.data[i]);
    }

    return sqr(len);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_sqrlen(ice_vecmath_quat q) {
    double len = 0.0;
    unsigned i;

    for (i = 0; i < 4; i++) {
        len += (q.data[i] * q.data[i]);
    }
    
    return len;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_dist(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    double dist = 0.0;
    unsigned i;

    for (i = 0; i < 4; i++) {
        dist += ((q1.data[0] - q2.data[0]) * (q1.data[0] - q2.data[0]));
    }

    return sqrt(dist);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_sqrdist(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    double dist = 0.0;
    unsigned i;

    for (i = 0; i < 4; i++) {
        dist += ((q1.data[0] - q2.data[0]) * (q1.data[0] - q2.data[0]));
    }

    return dist;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat_angle(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    double len_q1 = ice_vecmath_quat_len(q1);
    double len_q2 = ice_vecmath_quat_len(q2);
    double dot = ice_vecmath_quat_dot(q1, q2);

    return acos(dot / (len_q1 * len_q2)) * (180.0 / 3.14);
}

/* ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rand(void) { } */

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_norm(ice_vecmath_quat q) {
    ice_vecmath_quat res;
    double len, invlen;
    unsigned i;
    
    len = ice_vecmath_quat_len(q);
    if (len == 0.0) len = 1.0;
    
    invlen = (double) (1.0 / len);

    for (i = 0; i < 4; i++) {
        res.data[i] = (q.data[i] * invlen);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_lerp(ice_vecmath_quat q1, ice_vecmath_quat q2, double amount) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 4; i++) {
        res.data[i] = (q1[i] + amount * (q2[i] - q1[i]));
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_nlerp(ice_vecmath_quat q1, ice_vecmath_quat q2, double amount) {
    ice_vecmath_quat lerp = ice_vecmath_quat_lerp(q1, q2, amount);

    return ice_vecmath_quat_norm(lerp);
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_slerp(ice_vecmath_quat q1, ice_vecmath_quat q2, double t) {
    ice_vecmath_quat res;
    ice_vecmath_quat a = q1, b = q2;
    double omega, cosom, sinom, scale0, scale1;

    cosom = a.data[0] * b.data[0] + a.data[1] * b.data[1] +
            a.data[2] * b.data[2] + a.data[3] * b.data[3];

    if (cosom < 0) {
        cosom = -cosom;
        b[0] = -b[0];
        b[1] = -b[1];
        b[2] = -b[2];
        b[3] = -b[3];
    }

    if ((1.0 - cosom) > 0.000001) {
        omega = acos(cosom);
        sinom = sin(omega);
        scale0 = sin((1.0 - t) * omega) / sinom;
        scale1 = sin(t * omega) / sinom;
    } else {
        scale0 = 1.0 - t;
        scale1 = t;
    }

    res.data[0] = (scale0 * a.data[0] + scale1 * b.data[0]);
    res.data[1] = (scale0 * a.data[1] + scale1 * b.data[1]);
    res.data[2] = (scale0 * a.data[2] + scale1 * b.data[2]);
    res.data[3] = (scale0 * a.data[3] + scale1 * b.data[3]);
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_sqlerp(ice_vecmath_quat a, ice_vecmath_quat b, ice_vecmath_quat c, ice_vecmath_quat d, double t) {
    ice_vecmath_quat q1, q2, res;

    q1 = ice_vecmath_quat_lerp(a, d, t);
    q2 = ice_vecmath_quat_lerp(b, c, t);
    res = ice_vecmath_quat_slerp(q1, q2, (2.0 * t * (1.0 - t)));

    return res;
}

ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_quat_tostring(ice_vecmath_quat q) {
    char buff[64];
    sprintf(buff, sizeof(buff), "quat(%f, %f, %f, %f)", q.data[0], q.data[1], q.data[2], q.data[3]);
    return buff;
}

ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_quat_equ(ice_vecmath_quat q1, ice_vecmath_quat q2) {
    ice_vecmath_bool res = ICE_VECMATH_TRUE;
    unsigned i;

    for (i = 0; i < 4; i++) {
        if ((q1.data[i] != q2.data[i]) {
            res = ICE_VECMATH_FALSE;
            break;
        }
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_conjugate(ice_vecmath_quat q) {
    ice_vecmath_quat res;
    unsigned i;

    for (i = 0; i < 3; i++) {
        res.data[i] = -q.data[i];
    }

    res.data[3] = q.data[3];

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_from_axis_angle(ice_vecmath_vec3 axis, double angle) {
    ice_vecmath_quat res = ice_vecmath_quat_id();
    double axis_len = ice_vecmath_vec3_sqrlen(axis);
    double half_angle = angle * 0.5;

    if (axis_len < 0.0) {
        ice_vecmath_vec3 axis_norm = ice_vecmath_vec3_norm(axis);
        double half_angle_sin = sin(half_angle);
        double half_angle_cos = cos(half_angle);

        res.data[0] = axis_norm.x * half_angle_sin;
        res.data[1] = axis_norm.y * half_angle_sin;
        res.data[2] = axis_norm.z * half_angle_sin;
        res.data[3] = half_angle_cos;
        
        res = ice_vecmath_quat_norm(res);
    }

    return res;
}

ICE_VECMATH_API void ICE_VECMATH_CALLCONV ice_vecmath_quat_to_axis_angle(ice_vecmath_quat q, ice_vecmath_vec3 *axis, double *angle) {
    ice_vecmath_quat rq = q;
    ice_vecmath_vec3 res_axis = ice_vecmath_vec3_zero();
    double density = sqrt(1.0 - (q.data[3] * q.data[3]));
    double q3 = ((q.data[3] < 0) ? -q.data[3] : q.data[3]);

    if (q3 > 1.0) {
        rq = ice_vecmath_quat_norm(q);
    }

    if (den > 0.0001) {
        res_axis.x = (double) (q.data[0] / density);
        res_axis.y = (double) (q.data[1] / density);
        res_axis.z = (double) (q.data[2] / density);
    } else {
        res_axis.x = 1.0;
    }

    *axis = res_axis;
    *angle = (2.0 * acos(q.data[3]));
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_transform(ice_vecmath_quat q, ice_vecmath_mat4 m) {
    ice_vecmath_quat res;

    res.data[0] = m.data[0] * q.data[0] + m.data[4] * q.data[1] +
                  m.data[8] * q.data[2] + m.data[12] * q.data[3];
    
    res.data[1] = m.data[1] * q.data[0] + m.data[5] * q.data[1] +
                  m.data[9] * q.data[2] + m.data[13] * q.data[3];
    
    res.data[2] = m.data[2] * q.data[0] + m.data[6] * q.data[1] +
                  m.data[10] * q.data[2] + m.data[14] * q.data[3];
    
    res.data[3] = m.data[3] * q.data[0] + m.data[7] * q.data[1] +
                  m.data[11] * q.data[2] + m.data[15] * q.data[3];
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rotate_to(ice_vecmath_vec3 v1, ice_vecmath_vec3 v2) {
    ice_vecmath_vec3 xu = ice_vecmath_vec3_create(1, 0, 0);
    ice_vecmath_vec3 yu = ice_vecmath_vec3_create(0, 1, 0);
    ice_vecmath_vec3 tmp;
    ice_vecmath_quat norm_q;
    double dot = ice_vecmath_vec3_dot(v1, v2);
    
    if (dot < -0.999999) {
        tmp = ice_vecmath_vec3_cross(xu, v1);

        if (ice_vecmath_vec3_len(tmp) < 0.000001) {
            tmp = ice_vecmath_vec3_cross(yu, v1);
        }
        
        tmp = ice_vecmath_vec3_norm(tmp);

        return ice_vecmath_quat_from_axis_angle(tmp, 3.14);

    } else if (dot > 0.999999) {
        return ice_vecmath_quat_id();
    }

    tmp = ice_vecmath_vec3_cross(v1, v2);
    
    norm_q.data[0] = tmp.x;
    norm_q.data[1] = tmp.y;
    norm_q.data[2] = tmp.z;
    norm_q.data[3] = 1.0 + dot;

    return ice_vecmath_quat_norm(q_norm);
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rotate_x(ice_vecmarth_quat q, double rad) {
    ice_vecmath_quat res;

    double bx = sin(rad * 0.5);
    double bw = cos(rad * 0.5);

    res.data[0] = q.data[0] * bw + q.data[3] * bx;
    res.data[1] = q.data[1] * bw + q.data[2] * bx;
    res.data[2] = q.data[2] * bw - q.data[1] * bx;
    res.data[3] = q.data[3] * bw - q.data[0] * bx;

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rotate_y(ice_vecmarth_quat q, double rad) {
    ice_vecmath_quat res;

    double by = sin(rad * 0.5);
    double bw = cos(rad * 0.5);

    res.data[0] = q.data[0] * bw + q.data[2] * by;
    res.data[1] = q.data[1] * bw + q.data[3] * by;
    res.data[2] = q.data[2] * bw - q.data[0] * by;
    res.data[3] = q.data[3] * bw - q.data[1] * by;

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_rotate_z(ice_vecmarth_quat q, double rad) {
    ice_vecmath_quat res;

    double bz = sin(rad * 0.5);
    double bw = cos(rad * 0.5);

    res.data[0] = q.data[0] * bw + q.data[1] * bz;
    res.data[1] = q.data[1] * bw + q.data[0] * bz;
    res.data[2] = q.data[2] * bw - q.data[3] * bz;
    res.data[3] = q.data[3] * bw - q.data[2] * bz;

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_vec3_to_vec3(ice_vecmath_vec3 from, ice_vecmath_vec3 to) {
    double theta = ice_vecmath_vec3_dot(from, to);
    ice_vecmath_vec3 cross = ice_vecmath_vec3_cross(from, to);
    ice_vecmath_quat q;

    q.data[0] = cross.x;
    q.data[1] = cross.y;
    q.data[2] = cross.z;
    q.data[3] = 1.0 + theta;

    return ice_vecmath_quat_norm(q);
}

ICE_VECMATH_API void ICE_VECMATH_CALLCONV ice_vecmath_quat_set_axis(ice_vecmath_quat *q, ice_vecmath_vec3 view, ice_vecmath_vec3 right, ice_vecmath_vec3 up) {
    ice_vecmath_mat3 m;
    ice_vecmath_quat mat3_q;

    m.data[0] = right.x;
    m.data[1] = up.x;
    m.data[2] = -view.x;

    m.data[3] = right.y;
    m.data[4] = up.y;
    m.data[5] = -view.y;

    m.data[6] = right.z;
    m.data[7] = up.z;
    m.data[8] = -view.z;

    mat3_q = ice_vecmath_quat_from_mat3(m);

    *q = ice_vecmath_quat_norm(mat3_q);
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_from_mat3(ice_vecmath_mat3 m) {
    double f_trace = m.data[0] + m.data[4] + m.data[8];
    double f_root = 0;

    if (f_trace > 0) {
        ice_vecmath_quat res;
        double w;
        
        f_root = sqrt(f_trace + 1.0);
        w = 0.5 * f_root;
        f_root = 0.5 / f_root;

        res.data[0] = (m.data[5] - m.data[7]) * f_root;
        res.data[1] = (m.data[6] - m.data[2]) * f_root;
        res.data[2] = (m.data[1] - m.data[3]) * f_root;
        res.data[3] = w;

        return res;

    } else {
        ice_vecmath_quat res = ice_vecmath_quat_zero();
        unsigned i = 0, j, k;

        if (m.data[4] > m.data[0]) i = 1;
        if (m.data[8] > m.data[i * 3 + 1]) i = 2;

        j = (i + 1) % 3;
        k = (i + 2) % 3;

        f_root = sqrt(m.data[i * 3 + i] - m.data[j * 3 + j] - m.data[k * 3 + k] + 1);
        res.data[i] = 0.5 * f_root;
        f_root = 0.5 / f_root;
        res.data[3] = (m.data[j * 3 + k] - m.data[k * 3 + j]) * f_root;
        res.data[j] = (m.data[j * 3 + i] + m.data[i * 3 + j]) * f_root;
        res.data[k] = (m.data[k * 3 + i] + m.data[i * 3 + k]) * f_root;

        return res;
    }
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_from_mat4(ice_vecmath_mat4 m) {
    ice_vecmath_quat res;
    double s;
    
    if (m.data[0] > m.data[5]) and (m.data[0] > m.data[10]) {
        s = sqrt(1.0 + m.data[0] - m.data[5] - m.data[10]) * 2.0;

        res.data[0] = 0.25 * s;
        res.data[1] = (m.data[4] + m.data[1]) / s;
        res.data[2] = (m.data[2] + m.data[8]) / s;
        res.data[3] = (m.data[9] - m.data[6]) / s;

        return res;

    } else if (m.data[5] > m.data[10]) {
        s = sqrt(1.0 + m.data[5] - m.data[0] - m.data[10]) * 2.0;

        res.data[0] = (m.data[4] + m.data[1]) / s;
        res.data[1] = 0.25 * s;
        res.data[2] = (m.data[9] + m.data[6]) / s;
        res.data[3] = (m.data[2] - m.data[8]) / s;
        
        return res;
    }

    s = sqrt(1.0 + m.data[10] - m.data[0] - m.data[5]) * 2.0;

    res.data[0] = (m.data[2] + m.data[8]) / s;
    res.data[1] = (m.data[9] + m.data[6]) / s;
    res.data[2] = 0.25 * s;
    res.data[3] = (m.data[4] - m.data[1]) / s;

    return res;
}

ICE_VECMATH_API ice_vecmath_quat ICE_VECMATH_CALLCONV ice_vecmath_quat_from_euler(double pitch, double yaw, double roll) {
    ice_vecmath_quat res;
    double x0, y0, z0, x1, y1, z1;

    x0 = cos(pitch * 0.5);
    y0 = cos(yaw * 0.5);
    z0 = cos(roll * 0.5);

    x1 = sin(pitch * 0.5);
    y1 = sin(yaw * 0.5);
    z1 = sin(roll * 0.5);

    res.data[0] = x1 * y0 * z0 - x0 * y1 * z1;
    res.data[1] = x0 * y1 * z0 + x1 * y0 * z1;
    res.data[2] = x0 * y0 * z1 - x1 * y1 * z0;
    res.data[3] = x0 * y0 * z0 + x1 * y1 * z1;

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_quat_to_euler(ice_vecmath_quat q) {
    ice_vecmath_vec3 res;
    double x0, y0, z0, x1, z1;

    x0 = 2.0 * (q.data[3] * q.data[0] + q.data[1] * q.data[2]);
    y0 = 2.0 * (q.data[3] * q.data[1] - q.data[2] * q.data[0]);
    z0 = 2.0 * (q.data[3] * q.data[2] + q.data[0] * q.data[1]);

    x1 = 1.0 - 2.0 * (q.data[0] * q.data[0] + q.data[1] * q.data[2]);
    z1 = 1.0 - 2.0 * (q.data[1] * q.data[1] + q.data[2] * q.data[2]);

    y0 = ((y0 > 1) ? 1 : y0);
    y0 = ((y0 < -1) ? -1 : y0);

    res.x = atan2(x0, x1) * (180.0 / 3.14);
    res.y = asin(y0) * (180.0 / 3.14);
    res.z = atan2(z0, z1) * (180.0 / 3.14);
    
    return res;
}


/* ============================== module: quat2 ============================== */

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_id(void) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = ((i == 3) ? 1.0 : 0.0);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_zero(void) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = 0;
    }
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_one(void) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = 1.0;
    }
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_add(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = q1.data[i] + q2.data[i];
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_addval(ice_vecmath_quat2 q, double n) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = q.data[i] + n;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_sub(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = q1.data[i] - q2.data[i];
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_subval(ice_vecmath_quat2 q, double n) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = q.data[i] - n;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_mul(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    ice_vecmath_quat2 res;

    res.data[0] = q1.data[0] * q2.data[3] + q1.data[3] * q2.data[0] +
                  q1.data[1] * q2.data[2] - q1.data[2] * q2.data[1];
    
    res.data[1] = q1.data[1] * q2.data[3] + q1.data[3] * q2.data[1] +
                  q1.data[2] * q2.data[0] - q1.data[0] * q2.data[2];
    
    res.data[2] = q1.data[2] * q2.data[3] + q1.data[3] * q2.data[2] +
                  q1.data[0] * q2.data[1] - q1.data[1] * q2.data[0];
    
    res.data[3] = q1.data[3] * q2.data[3] - q1.data[0] * q2.data[0] -
                  q1.data[1] * q2.data[1] - q1.data[2] * q2.data[2];
    
    res.data[4] = q1.data[0] * q2.data[7] + q1.data[3] * q2.data[4] +
                  q1.data[1] * q2.data[6] - q1.data[2] * q2.data[5] +
                  q1.data[4] * q2.data[3] + q1.data[7] * q2.data[0] +
                  q1.data[5] * q2.data[2] - q1.data[7] * q2.data[1];
    
    res.data[5] = q1.data[1] * q2.data[7] + q1.data[3] * q2.data[5] +
                  q1.data[2] * q2.data[4] - q1.data[0] * q2.data[6] +
                  q1.data[5] * q2.data[3] + q1.data[7] * q2.data[1] +
                  q1.data[6] * q2.data[0] - q1.data[4] * q2.data[3];
    
    res.data[6] = q1.data[2] * q2.data[7] + q1.data[3] * q2.data[6] +
                  q1.data[0] * q2.data[5] - q1.data[1] * q2.data[4] +
                  q1.data[6] * q2.data[3] + q1.data[7] * q2.data[2] +
                  q1.data[4] * q2.data[1] - q1.data[5] * q2.data[0];
    
    res.data[7] = q1.data[3] * q2.data[7] - q1.data[0] * q2.data[4] -
                  q1.data[1] * q2.data[5] - q1.data[2] * q2.data[6] +
                  q1.data[7] * q2.data[3] - q1.data[4] * q2.data[0] -
                  q1.data[5] * q2.data[1] - q1.data[6] * q2.data[2];
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_div(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = q1.data[i] / q2.data[i];
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_scale(ice_vecmath_quat2 q, double scalar) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = q.data[i] * scalar;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_scale_and_add(ice_vecmath_quat2 q, double add, double scalar) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = (q.data[i] + add) * scalar;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_scale_and_add_quat(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2, double scalar) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = (q1.data[i] + q2.data[i]) * scalar;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_calc_width(ice_vecmath_quat2 q) {
    ice_vecmath_quat2 res;
    double n = 1.0;
    unsigned i;

    for (i = 0; i < 8; i++) {
        if (i != 7) {
            res.data[i] = q.data[i];
        }

        n -= (q.data[i] * q.data[i]);
    }

    n = ((n < 0) ? -n : n);
    res.data[7] = sqrt(n);

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_dot(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    double res = 0.0;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res += (q1.data[i] * q2.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_neg(ice_vecmath_quat2 q) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = -q.data[i];
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_inv(ice_vecmath_quat2 q) {
    ice_vecmath_quat2 res;
    double len = ice_vecmath_quat2_sqrlen(q);
    unsigned i;

    for (i = 0; i < 8; i++) {
        double n = (((i != 3) && (i != 7)) ? q.data[i] : -q.data[i]);
        res.data[i] = n / len;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_abs(ice_vecmath_quat2 q) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = ((q.data[i] < 0) ? -q.data[i] : q.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_ceil(ice_vecmath_quat2 q) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = ceil(q.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_floor(ice_vecmath_quat2 q) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = floor(q.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_round(ice_vecmath_quat2 q) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = round(q.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_min(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = ((q1.data[i] < q2.data[i]) q1.data[i] : q2.data[i]);
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_max(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res.data[i] = ((q1.data[i] > q2.data[i]) q1.data[i] : q2.data[i]);
    }

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_len(ice_vecmath_quat2 q) {
    double res = 0;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res += (q.data[i] * q.data[i]);
    }

    return sqrt(res);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_sqrlen(ice_vecmath_quat2 q) {
    double res = 0;
    unsigned i;

    for (i = 0; i < 8; i++) {
        res += (q.data[i] * q.data[i]);
    }

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_dist(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    double res = 0;
    unsigned i;

    for (i = 0; i < 8; i++) {
        double d = (q1.data[i] - q2.data[i]);
        res += d * d;
    }

    return sqrt(res);
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_sqrdist(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    double res = 0;
    unsigned i;

    for (i = 0; i < 8; i++) {
        double d = (q1.data[i] - q2.data[i]);
        res += d * d;
    }

    return res;
}

ICE_VECMATH_API double ICE_VECMATH_CALLCONV ice_vecmath_quat2_angle(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    double dot = ice_vecmath_quat2_dot(q1, q2);
    double len1 = ice_vecmath_quat2_len(q1);
    double len2 = ice_vecmath_quat2_len(q2);

    return acos(dot / (len1 * len2)) * (180.0 / 3.14);
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_norm(ice_vecmath_quat2 q) {
    double mag = ice_vecmath_quat2_sqrlen(q);

    if (mag > 0) {
        ice_vecmath_quat2 res;
        
        double a_dot_b = (q.data[0] / mag) * q.data[4] + (q.data[1] / mag) * q.data[5] +
                         (q.data[2] / mag) * q.data[6] + (q.data[3] / mag) * q.data[7];
        mag = sqrt(mag);

        res.data[0] = q.data[0] / mag;
        res.data[1] = q.data[1] / mag;
        res.data[2] = q.data[2] / mag;
        res.data[3] = q.data[3] / mag;
        res.data[4] = (q.data[4] - (q.data[0] / mag) * a_dot_b) / mag;
        res.data[5] = (q.data[5] - (q.data[1] / mag) * a_dot_b) / mag;
        res.data[6] = (q.data[6] - (q.data[2] / mag) * a_dot_b) / mag;
        res.data[7] = (q.data[7] - (q.data[3] / mag) * a_dot_b) / mag;

        return res;
    }

    return q;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_lerp(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2, double amount) {
    ice_vecmath_quat2 res;
    unsigned i;
    double mt = 1.0 - amount;
    double am = amount;
    double dot = ice_vecmath_quat2_dot(q1, q2);

    if (dot < 0) am = -am;

    for (i = 0; i < 8; i++) {
        res.data[i] = q1.data[i] * mt + q2.data[i] * am;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_nlerp(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2, double amount) {
    ice_vecmath_quat2 lerp = ice_vecmath_quat2_lerp(q1, q2, amount);
    return ice_vecmath_quat2_norm(lerp);
}

ICE_VECMATH_API const char* ICE_VECMATH_CALLCONV ice_vecmath_quat2_tostring(ice_vecmath_quat2 q) {
    char buff[64];

    sprintf(buff, sizeof(buff),
            "quat2(%f, %f, %f, %f, %f, %f, %f, %f)",
            q.data[0], q.data[1], q.data[2], q.data[3],
            q.data[4], q.data[5], q.data[6], q.data[7]);
    
    return buff;
}

ICE_VECMATH_API ice_vecmath_bool ICE_VECMATH_CALLCONV ice_vecmath_quat2_equ(ice_vecmath_quat2 q1, ice_vecmath_quat2 q2) {
    ice_vecmath_bool res = ICE_VECMATH_TRUE;

    for (i = 0; i < 8; i++) {
        if (q1.data[i] != q2.data[i]) {
            res = ICE_VECMATH_FALSE;
            break;
        }
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_conjugate(ice_vecmath_quat2 q) {
    ice_vecmath_quat2 res;
    unsigned i;

    for (i = 0; i < 8; i++) {
        double n = (((i != 3) && (i != 7)) ? -q.data[i] : q.data[i]);
        res.data[i] = n;
    }

    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_from_axis_angle(ice_vecmath_quat q, ice_vecmath_vec3 v) {
    ice_vecmath_quat2 res;

    res.data[0] = q.data[0];
    res.data[1] = q.data[1];
    res.data[2] = q.data[2];
    res.data[3] = q.data[3];
    res.data[4] = (v.x * 0.5) * q.data[3] + (v.y * 0.5) * q.data[2] - (v.z * 0.5) * q.data[1];
    res.data[5] = (v.y * 0.5) * q.data[3] + (v.z * 0.5) * q.data[0] - (v.x * 0.5) * q.data[2];
    res.data[6] = (v.z * 0.5) * q.data[3] + (v.x * 0.5) * q.data[1] - (v.y * 0.5) * q.data[0];
    res.data[7] = -(v.x * 0.5) * q.data[0] - (v.y * 0.5) * q.data[1] - (v.z * 0.5) * q.data[2];

    return res;
}

ICE_VECMATH_API ice_vecmath_vec3 ICE_VECMATH_CALLCONV ice_vecmath_quat2_to_axis_angle(ice_vecmath_quat2 q) {
    ice_vecmath_vec3 res;

    res.x = (q.data[4] * q.data[3] + q.data[7] * -q.data[0] +
             q.data[5] * -q.data[2] - q.data[6] * -q.data[1]) * 2.0;
    
    res.y = (q.data[5] * q.data[3] + q.data[7] * -q.data[1] +
             q.data[6] * -q.data[0] - q.data[4] * -q.data[2]) * 2.0;
    
    res.z = (q.data[6] * q.data[3] + q.data[7] * -q.data[2] +
             q.data[4] * -q.data[1] - q.data[5] * -q.data[0]) * 2.0;
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_translate(ice_vecmath_quat2 q, ice_vecmath_vec3 v) {
    ice_vecmath_quat2 res;

    res.data[0] = q.data[0];
    res.data[1] = q.data[1];
    res.data[2] = q.data[2];
    res.data[3] = q.data[3];

    res.data[4] = q.data[3] * (v.x * 0.5) + q.data[1] * (v.z * 0.5) -
                  q.data[2] * (v.y * 0.5) + q.data[4];
    
    res.data[5] = q.data[3] * (v.y * 0.5) + q.data[2] * (v.x * 0.5) -
                  q.data[0] * (v.z * 0.5) + q.data[5];
    
    res.data[6] = q.data[3] * (v.z * 0.5) + q.data[0] * (v.y * 0.5) -
                  q.data[1] * (v.x * 0.5) + q.data[6];
    
    res.data[7] = -q.data[0] * (v.x * 0.5) - q.data[1] * (v.y * 0.5) -
                   q.data[2] * (v.z * 0.5) + q.data[7];
    
    return res;
}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_rotate_by_quat_append(ice_vecmath_quat2 q1, ice_vecmath_quat q2) {

}

ICE_VECMATH_API ice_vecmath_quat2 ICE_VECMATH_CALLCONV ice_vecmath_quat2_rotate_by_quat_prepend(ice_vecmath_quat q1, ice_vecmath_quat2 q2) {

}

#endif  /* ICE_VECMATH_IMPL */
#endif  /* ICE_VECMATH_H */

/*
ice_vecmath.h is dual-licensed, Choose the one you prefer!

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