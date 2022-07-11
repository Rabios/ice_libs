/*

ice_ease.h, Single-Header Cross-Platform C library for working with Easings!


================================== Full Overview ==================================

ice_ease.h is Single-Header Cross-Platform C library for Easings, It's based on Robert Penner's easings and Easing functions from easings.net

To use it #define ICE_EASE_IMPL then #include "ice_ease.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

// Define the implementation of the library and include it
#define ICE_EASE_IMPL 1
#include "ice_ease.h"

#include <stdio.h>

int main(void) {
    double linear1, linear4;

    // Use linear easing, With 1 argument (easings.net)
    linear1 = ice_ease_linear(ICE_EASE_TYPE_PROGRESS, 5.0);
    
    // Use linear easing, But with 4 arguments (Robert Penner's version)
    linear4 = ice_ease_linear(ICE_EASE_TYPE_PENNER, 1.0, 2.0, 3.0, 4.0);

    // Print the results...
    (void) printf("Linear easing with one variable: %f\nLinear easing with four variables: %f\n",
           linear1, linear4);

    return 0;
}


=================================== Library API ===================================

#define ICE_EASE_PI         3.1415926535897932384626433832795   // Pi
#define ICE_EASE_TAU        6.283185307179586476925286766559    // Tau (Double Pi)
#define ICE_EASE_HALF_PI    1.5707963267948966192313216916398   // Half of Pi

// Easing Types
typedef enum ice_ease_type {
    ICE_EASE_TYPE_PROGRESS = 0,
    ICE_EASE_TYPE_PENNER
} ice_ease_type;

// NOTE: You can use Robert Penner's Easings or Easings that take one value, To use Robert one argc should be 4 and to use Single-Value ones it should be 1 (Arguments Number)

// Examples:
// ice_ease_linear(ICE_EASE_TYPE_PROGRESS, 5.0);                // Progress-Based easings take 1 argument
// ice_ease_linear(ICE_EASE_TYPE_PENNER, 1.0, 2.0, 3.0, 4.0);   // Penner easings take 4 arguments


// ------------------------------- Linear ------------------------------- //

double ice_ease_linear(ice_ease_type ease_type, ...);

// ------------------------------ Sinusoidal ------------------------------ //

double ice_ease_sine_in(ice_ease_type ease_type, ...);
double ice_ease_sine_out(ice_ease_type ease_type, ...);
double ice_ease_sine_in_out(ice_ease_type ease_type, ...);

// ------------------------------ Quadratic ------------------------------ //

double ice_ease_quad_in(ice_ease_type ease_type, ...);
double ice_ease_quad_out(ice_ease_type ease_type, ...);
double ice_ease_quad_in_out(ice_ease_type ease_type, ...);

// -------------------------------- Cubic -------------------------------- //

double ice_ease_cubic_in(ice_ease_type ease_type, ...);
double ice_ease_cubic_out(ice_ease_type ease_type, ...);
double ice_ease_cubic_in_out(ice_ease_type ease_type, ...);

// ------------------------------- Quartic ------------------------------- //

double ice_ease_quart_in(ice_ease_type ease_type, ...);
double ice_ease_quart_out(ice_ease_type ease_type, ...);
double ice_ease_quart_in_out(ice_ease_type ease_type, ...);

// ------------------------------- Quintic ------------------------------- //

double ice_ease_quint_in(ice_ease_type ease_type, ...);
double ice_ease_quint_out(ice_ease_type ease_type, ...);
double ice_ease_quint_in_out(ice_ease_type ease_type, ...);

// ----------------------------- Exponential ----------------------------- //

double ice_ease_expo_in(ice_ease_type ease_type, ...);
double ice_ease_expo_out(ice_ease_type ease_type, ...);
double ice_ease_expo_in_out(ice_ease_type ease_type, ...);

// ------------------------------ Circular ------------------------------ //

double ice_ease_circ_in(ice_ease_type ease_type, ...);
double ice_ease_circ_out(ice_ease_type ease_type, ...);
double ice_ease_circ_in_out(ice_ease_type ease_type, ...);

// ------------------------------ Elastic ------------------------------ //

double ice_ease_elastic_in(ice_ease_type ease_type, ...);
double ice_ease_elastic_out(ice_ease_type ease_type, ...);
double ice_ease_elastic_in_out(ice_ease_type ease_type, ...);

// ------------------------------- Back -------------------------------- //

double ice_ease_back_in(ice_ease_type ease_type, ...);
double ice_ease_back_out(ice_ease_type ease_type, ...);
double ice_ease_back_in_out(ice_ease_type ease_type, ...);

// ------------------------------ Bounce ------------------------------- //

double ice_ease_bounce_in(ice_ease_type ease_type, ...);
double ice_ease_bounce_out(ice_ease_type ease_type, ...);
double ice_ease_bounce_in_out(ice_ease_type ease_type, ...);


================================== Linking Flags ==================================

1. Linux, BSD   =>  -lc -lm (-lc Most times automatically linked...)
2. Elsewhere    =>  -lm

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragma preprocessor


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_ease.h in the code...
#define ICE_EASE_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_EASE_VECTORCALL     // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_EASE_FASTCALL       // fastcall
#define ICE_EASE_STDCALL        // stdcall
#define ICE_EASE_CDECL          // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_EASE_MICROSOFT       // Microsoft platforms
#define ICE_EASE_NON_MICROSOFT   // Non-Microsoft platforms

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_EASE_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_EASE_DLLEXPORT      // Export the symbols to build as shared library
#define ICE_EASE_DLLIMPORT      // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_EASE_INLINE         // inlines library functions (Only works on C99 Standard and above)
#define ICE_EASE_EXTERN         // externs library functions
#define ICE_EASE_STATIC         // statics library functions

// NOTE: You cannot #define both ICE_EASE_EXTERN and ICE_EASE_STATIC together in the code...


============================== Implementation Resources ===========================

1. http://robertpenner.com/easing
2. https://easings.net


================================= Support ice_libs ================================

ice_ease.h is one of libraries that ice_libs project provide...

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

#if !defined(ICE_EASE_H)
#define ICE_EASE_H 1

/* Allow to use calling conventions if desired... */
#if defined(ICE_EASE_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_EASE_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_EASE_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_EASE_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_EASE_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_EASE_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_EASE_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_EASE_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_EASE_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_EASE_CDECL)
#  if defined(_MSC_VER)
#    define ICE_EASE_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_EASE_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_EASE_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_EASE_MICROSOFT) || defined(ICE_EASE_NON_MICROSOFT))
#  define ICE_EASE_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
#if defined(ICE_EASE_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_EASE_MICROSOFT 1
#  else
#    define ICE_EASE_NON_MICROSOFT 1
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_EASE_EXTERN) && defined(ICE_EASE_STATIC))
#  define ICE_EASE_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_EASE_EXTERN)
#  define ICE_EASE_APIDEF extern
#elif defined(ICE_EASE_STATIC)
#  define ICE_EASE_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_EASE_INLINE to enable inline functionality.
*/
#if defined(ICE_EASE_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_EASE_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_EASE_INLINEDEF inline
#  endif
#else
#  define ICE_EASE_INLINEDEF
#endif

/*
Allow to build DLL via ICE_EASE_DLLEXPORT or ICE_EASE_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_EASE_MICROSOFT)
#  if defined(ICE_EASE_DLLEXPORT)
#    define ICE_EASE_API __declspec(dllexport) ICE_EASE_INLINEDEF
#  elif defined(ICE_EASE_DLLIMPORT)
#    define ICE_EASE_API __declspec(dllimport) ICE_EASE_INLINEDEF
#  else
#    define ICE_EASE_API ICE_EASE_APIDEF ICE_EASE_INLINEDEF
#  endif
#else
#  define ICE_EASE_API ICE_EASE_APIDEF ICE_EASE_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* =============================== Defines =============================== */

#if !defined(ICE_EASE_PI)
#  define ICE_EASE_PI           3.1415926535897932384626433832795   /* Pi */
#endif
#if !defined(ICE_EASE_TAU)
#  define ICE_EASE_TAU          6.283185307179586476925286766559    /* Tau (Double Pi) */
#endif
#if !defined(ICE_EASE_HALF_PI)
#  define ICE_EASE_HALF_PI      1.5707963267948966192313216916398   /* Half of Pi */
#endif

/* ============================== Data Types ============================== */

/* Easing Types */
typedef enum ice_ease_type {
    ICE_EASE_TYPE_PROGRESS = 0,
    ICE_EASE_TYPE_PENNER
} ice_ease_type;

/* ============================== Functions ============================== */

/* ------------------------------- Linear ------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_linear(ice_ease_type ease_type, ...);

/* ------------------------------ Sinusoidal ------------------------------ */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_in_out(ice_ease_type ease_type, ...);

/* ------------------------------ Quadratic ------------------------------ */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_in_out(ice_ease_type ease_type, ...);

/* -------------------------------- Cubic -------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_in_out(ice_ease_type ease_type, ...);

/* ------------------------------- Quartic ------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_in_out(ice_ease_type ease_type, ...);

/* ------------------------------- Quintic ------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_in_out(ice_ease_type ease_type, ...);

/* ----------------------------- Exponential ----------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_in_out(ice_ease_type ease_type, ...);

/* ------------------------------ Circular ------------------------------ */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_in_out(ice_ease_type ease_type, ...);

/* ------------------------------ Elastic ------------------------------ */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_in_out(ice_ease_type ease_type, ...);

/* ------------------------------- Back -------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_in_out(ice_ease_type ease_type, ...);

/* ------------------------------ Bounce ------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_in_out(ice_ease_type ease_type, ...);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_EASE_IMPL)

#include <stdarg.h>
#include <math.h>

/* [INTERNAL] Fetches x from the variable arguments */
#define ICE_EASE_LOAD_ARG       \
    double x;                   \
    va_list argv;               \
    va_start(argv, ease_type);  \
    x = va_arg(argv, double);   \
    va_end(argv);

/* [INTERNAL] Fetches (t, b, c, d) from the variable arguments */
#define ICE_EASE_LOAD_FOUR_ARGS \
    double t, b, c, d;          \
    va_list argv;               \
    va_start(argv, ease_type);  \
    t = va_arg(argv, double);   \
    b = va_arg(argv, double);   \
    c = va_arg(argv, double);   \
    d = va_arg(argv, double);   \
    va_end(argv);

/* ------------------------------- Linear ------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_linear(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = x;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        res = c * (t / d) + b;
    }
    
    return res;
}

/* ------------------------------ Sinusoidal ------------------------------ */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = 1 - cos(x * ICE_EASE_HALF_PI);
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        res = -c * cos((t / d) * ICE_EASE_HALF_PI) + c + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = sin(x * ICE_EASE_HALF_PI);
    
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        res = c * sin((t / d) * ICE_EASE_HALF_PI) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = -(cos(ICE_EASE_PI * x) - 1) * 0.5;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        res = -c * 0.5 * (cos(ICE_EASE_PI * (t / d)) - 1) + b;
    }
    
    return res;
}

/* ------------------------------ Quadratic ------------------------------ */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = x * x;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t /= d;
        res = c * t * t + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y;
        ICE_EASE_LOAD_ARG
        
        y = 1 - x;
        res = 1 - y * y;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t /= d;
        res = -c * t * (t - 2) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        if (x < 0.5) {
            res = 2 * x * x;
        } else {
            double y = -2 * x + 2;
            res = 1 - y * y * 0.5;
        }
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        double x, y = 0, z = 0;
        ICE_EASE_LOAD_FOUR_ARGS
        
        x = c * 0.5, t /= d * 0.5;
        if (!(t < 1)) t -= 1, x = -x, y = -2, z = -1;
        
        res = x * (t * (t + y) + z) + b;
    }
    
    return res;
}

/* -------------------------------- Cubic -------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = x * x * x;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t /= d;
        res = c * t * t * t + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y;
        ICE_EASE_LOAD_ARG
        
        y = 1 - x;
        res = 1 - y * y * y;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t = t / d - 1;
        res = c * (t * t * t + 1) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        if (x < 0.5) {
            res = 4 * x * x * x;
        } else {
            double y = -2 * x + 2;
            res = 1 - y * y * y * 0.5;
        }
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        double x, y = 0;
        ICE_EASE_LOAD_FOUR_ARGS
        
        x = c * 0.5, t /= d * 0.5;
        if (!(t < 1)) t -= 2, y = 2;
        
        res = x * (t * t * t + y) + b;
    }
    
    return res;
}

/* ------------------------------- Quartic ------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = x * x * x * x;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t /= d;
        res = c * t * t * t * t + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y;
        ICE_EASE_LOAD_ARG
        
        y = 1 - x;
        res = 1 - y * y * y * y;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t = t / d - 1;
        res = -c * (t * t * t * t - 1) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        if (x < 0.5) {
            res = 8 * x * x * x * x;
        } else {
            double y = -2 * x + 2;
            
            res = 1 - y * y * y * y * 0.5;
        }
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        double x, y = 0;
        ICE_EASE_LOAD_FOUR_ARGS
        
        x = c * 0.5, t /= d * 0.5;
        if (!(t < 1)) t -= 2, x = -x, y = -2;
        
        res = x * (t * t * t * t + y) + b;
    }
    
    return res;
}

/* ------------------------------- Quintic ------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = x * x * x * x * x;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t /= d;
        res = c * t * t * t * t * t + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y;
        ICE_EASE_LOAD_ARG
        
        y = 1 - x;
        res = 1 - y * y * y * y * y;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t = t / d - 1;
        res = c * (t * t * t * t * t + 1) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        if (x < 0.5) {
            res = 16 * x * x * x * x * x;
        } else {
            double y = -2 * x + 2;
            res = 1 - y * y * y * y * y * 0.5;
        }
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        double x, y = 0;
        ICE_EASE_LOAD_FOUR_ARGS
        
        x = c * 0.5, t /= d * 0.5;
        if (!(t < 1)) t -= 2, y = 2;
        
        res = x * (t * t * t * t * t + y) + b;
    }
    
    return res;
}

/* ----------------------------- Exponential ----------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = ((x == 0) ? 0 : pow(2, 10 * x - 10));
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        res = ((t == 0) ? b : (c * pow(2, 10 * (t / d - 1)) + b));
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = ((x == 1) ? 1 : 1 - pow(2, -10 * x));
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        res = ((t == d) ? (b + c) : (c * (-pow(2, -10 * t / d) + 1) + b));
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        if ((x == 0) || (x == 1)) {
            res = x;
        } else {
            double y = 20 * x - 10, z = pow(2, y);
            res = ((x < 0.5) ? (z * 0.5) : ((2 - (1 / z)) * 0.5));
        }
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        if (t == 0) {
            res = b;
        } else if (t == d) {
            res = b + c;
        } else if ((t /= d * 0.5) < 1) {
            res = c * 0.5 * pow(2, 10 * (t - 1)) + b;
        } else {
            t -= 1;
            res = c * 0.5 * (-pow(2, -10 * t) + 2) + b;
        }
    }
    
    return res;
}

/* ------------------------------ Circular ------------------------------ */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = 1 - sqrt(1 - x * x);
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t /= d;
        res = -c * (sqrt(1 - t * t) - 1) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y;
        ICE_EASE_LOAD_ARG
        
        y = x - 1;
        res = sqrt(1 - y * y);
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t = t / d - 1;
        res = c * sqrt(1 - t * t) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        if (x < 0.5) {
            res = (1 - sqrt(1 - (4 * x * x))) * 0.5;
        } else {
            double y = -2 * x + 2;
            res = (sqrt(1 - y * y) + 1) * 0.5;
        }
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        double x, y, z = -1;
        ICE_EASE_LOAD_FOUR_ARGS
        
        x = -c * 0.5, t /= d * 0.5;
        if (!(t < 1)) t -= 2, x = -x, z = 1;
        
        y = sqrt(1 - t * t);
        res = x * (y + z) + b;
    }
    
    return res;
}

/* ------------------------------ Elastic ------------------------------ */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        if ((x == 0) || (x == 1)) {
            res = x;
        } else {
            res = -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * 2.0943951023931954923084289221863);
        }
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        if (t == 0) {
            res = b;
        } else if ((t /= d) == 1) {
            res = b + c;
        } else {
            double p = d * 0.3f, s = p * 0.25f;
            
            t -= 1;
            res = -(c * pow(2, 10 * t) * sin((t * d - s) * ICE_EASE_TAU / p)) + b;
        }
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        if ((x == 0) || (x == 1)) {
            res = x;
        } else {
            res = pow(2, -10 * x) * sin((x * 10 - 0.75) * 2.0943951023931954923084289221863) + 1;
        }
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        if (t == 0) {
            res = b;
        } else if ((t /= d) == 1) {
            res = b + c;
        } else {
            double p = d * 0.3, s = p * 0.25;
            res = (c * pow(2, -10 * t) * sin((t * d - s) * ICE_EASE_TAU / p) + c + b);
        }
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        if ((x == 0) || (x == 1)) {
            res = x;
        } else {
            double y = 20 * x - 10,
                   z = sin((20 * x - 11.125) * 1.3962634015954636615389526147909) * 0.5,
                   w = -pow(2, y), n = 0;
            
            if (!(x < 0.5)) w = 1 / -w, z = 1;
            
            res = (w * z + n);
        }
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        if (t == 0) {
            res = b;
        } else if ((t /= d * 0.5) == 2) {
            res = b + c;
        } else {
            double p = d * 0.45, s = p * 0.25, x, y, z, w, n;
            
            t -= 1, x = 10 * t, y = sin((t * d - s) * ICE_EASE_TAU / p),
            z = -0.5 * c, w = pow(2, x), n = b;
            
            if (!((t + 1) < 1)) w = 1 / w, z = -z, n += c;
            
            res = z * w * y + n;
        }	
    }
    
    return res;
}

/* ------------------------------- Back -------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y;
        ICE_EASE_LOAD_ARG
        
        y = x * x;
        res = 2.70158 * x * y - 1.70158 * y;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t /= d;
        res = c * t * t * (2.70158 * t - 1.70158) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y, z;
        ICE_EASE_LOAD_ARG
        
        y = x - 1, z = y * y;
        res = 1 + 2.70158 * z * y + 1.70158 * z;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        t = t / d - 1;
        res = c * (t * t * (2.70158 * t + 1.70158) + 1) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y, z = 0;
        ICE_EASE_LOAD_ARG
        
        y = 2 * x;
        if (!(x < 0.5)) y -= 2, z = 2;
        
        res = (y * y * (3.5949095 * y + 2.5949095) + z) * 0.5;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        double x, y, z = -2.5949095;
        ICE_EASE_LOAD_FOUR_ARGS
        
        x = c * 0.5, t /= d * 0.5;
        if (!(t < 1)) t -= 2, y = 2, z = -z;
        
        res = x * (t * t * (3.5949095 * t + z) + y) + b;
    }
    
    return res;
}

/* ------------------------------ Bounce ------------------------------- */

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_in(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        
        res = 1 - ice_ease_bounce_out(ICE_EASE_TYPE_PROGRESS, 1 - x);
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        res = c - ice_ease_bounce_out(ICE_EASE_TYPE_PENNER, d - t, 0, c, d) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y;
        ICE_EASE_LOAD_ARG
        
        if (x < 0.36363636363636363636363636363636) {
            y = 0;
        } else if (x < 0.72727272727272727272727272727273) {
            x -= 0.54545454545454545454545454545455, y = 0.75;
        } else if (x < 0.90909090909090909090909090909091) {
            x -= 0.81818181818181818181818181818182, y = 0.9375;
        } else {
            x -= 0.95454545454545454545454545454545, y = 0.984375;
        }
        
        res = 7.5625 * x * x + y;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        double x;
        ICE_EASE_LOAD_FOUR_ARGS
        
        t /= d;
        
        if (t < 0.36363636363636363636363636363636) {
            x = 0;
        } else if (t < 0.72727272727272727272727272727273) {
            t -= 0.54545454545454545454545454545455, x = 0.75;
        } else if (t < 0.90909090909090909090909090909091) {
            t -= 0.81818181818181818181818181818182, x = 0.9375;
        } else {
            t -= 0.95454545454545454545454545454545, x = 0.984375;
        }
        
        res = c * (7.5625 * t * t + x) + b;
    }
    
    return res;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_in_out(ice_ease_type ease_type, ...) {
    double res = 0;
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        double y, z = -1;
        ICE_EASE_LOAD_ARG
        
        y = 1 - 2 * x;
        if (!(x < 0.5)) y = -y, z = -z;
        
        res = (1 + z * ice_ease_bounce_out(ICE_EASE_TYPE_PROGRESS, y)) * 0.5;
        
    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        if (t < (d * 0.5)) {
            res = ice_ease_bounce_in(ICE_EASE_TYPE_PENNER, t * 2, 0, c, d) * 0.5 + b;
        } else {
            res = ice_ease_bounce_out(ICE_EASE_TYPE_PENNER, t * 2 - d, 0, c, d) * 0.5 + c * 0.5f + b;
        }
    }
    
    return res;
}

#endif  /* ICE_EASE_IMPL */
#endif  /* ICE_EASE_H */

/*
ice_ease.h is dual-licensed, Choose the one you prefer!

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
