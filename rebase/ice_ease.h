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

int main(int argc, char **argv) {
    double linear1, linear4;

    // Use linear easing, With 1 argument (easings.net)
    linear1 = ice_ease_linear(ICE_EASE_TYPE_PROGRESS, 5.0);
    
    // Use linear easing, But with 4 arguments (Robert Penner's version)
    linear4 = ice_ease_linear(ICE_EASE_TYPE_PENNER, 1.0, 2.0, 3.0, 4.0);

    // Print the results...
    printf("Linear easing with one variable: %f\nLinear easing with four variables: %f\n",
           linear1, linear4);

    return 0;
}


=================================== Library API ===================================

// PI definition
#define ICE_EASE_PI 3.14159265358979323846

// Easing Types
typedef enum ice_ease_type {
    ICE_EASE_TYPE_PROGRESS = 1,
    ICE_EASE_TYPE_PENNER = 4
} ice_ease_type;

// NOTE: You can use Robert Penner's Easings or Easings that take one value, To use Robert one argc should be 4 and to use Single-Value ones it should be 1 (Arguments Number)

// Examples:
// ice_ease_linear(ICE_EASE_TYPE_PROGRESS, 5);         // Progress-Based easings take 1 argument
// ice_ease_linear(ICE_EASE_TYPE_PENNER, 1, 2, 3, 4);  // Penner easings take 4 arguments

// Functions for Linear Easing
double ice_ease_linear(ice_ease_type ease_type, ...);

// Functions for Quadratic Easing
double ice_ease_quad_in(ice_ease_type ease_type, ...);
double ice_ease_quad_out(ice_ease_type ease_type, ...);
double ice_ease_quad_in_out(ice_ease_type ease_type, ...);

// Functions for Cubic Easing
double ice_ease_cubic_in(ice_ease_type ease_type, ...);
double ice_ease_cubic_out(ice_ease_type ease_type, ...);
double ice_ease_cubic_in_out(ice_ease_type ease_type, ...);

// Functions for Quartic Easing
double ice_ease_quart_in(ice_ease_type ease_type, ...);
double ice_ease_quart_out(ice_ease_type ease_type, ...);
double ice_ease_quart_in_out(ice_ease_type ease_type, ...);

// Functions for Quintic Easing
double ice_ease_quint_in(ice_ease_type ease_type, ...);
double ice_ease_quint_out(ice_ease_type ease_type, ...);
double ice_ease_quint_in_out(ice_ease_type ease_type, ...);

// Functions for Sinusoidal Easing
double ice_ease_sine_in(ice_ease_type ease_type, ...);
double ice_ease_sine_out(ice_ease_type ease_type, ...);
double ice_ease_sine_in_out(ice_ease_type ease_type, ...);

// Functions for Exponential Easing
double ice_ease_expo_in(ice_ease_type ease_type, ...);
double ice_ease_expo_out(ice_ease_type ease_type, ...);
double ice_ease_expo_in_out(ice_ease_type ease_type, ...);

// Functions for Circular Easing
double ice_ease_circ_in(ice_ease_type ease_type, ...);
double ice_ease_circ_out(ice_ease_type ease_type, ...);
double ice_ease_circ_in_out(ice_ease_type ease_type, ...);

// Functions for Elastic Easing
double ice_ease_elastic_in(ice_ease_type ease_type, ...);
double ice_ease_elastic_out(ice_ease_type ease_type, ...);
double ice_ease_elastic_in_out(ice_ease_type ease_type, ...);

// Functions for Back Easing
double ice_ease_back_in(ice_ease_type ease_type, ...);
double ice_ease_back_out(ice_ease_type ease_type, ...);
double ice_ease_back_in_out(ice_ease_type ease_type, ...);

// Functions for Bounce Easing
double ice_ease_bounce_in(ice_ease_type ease_type, ...);
double ice_ease_bounce_out(ice_ease_type ease_type, ...);
double ice_ease_bounce_in_out(ice_ease_type ease_type, ...);


================================== Linking Flags ==================================

1. Everywhere    => -lc -lm (-lc Most times automatically linked...)

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

/* =============================== Macros =============================== */

/* PI definition */
#if !defined(ICE_EASE_PI)
#  define ICE_EASE_PI 3.14159265358979323846
#endif

/* ============================== Data Types ============================== */

/* Easing Types */
typedef enum ice_ease_type {
    ICE_EASE_TYPE_PROGRESS = 1,
    ICE_EASE_TYPE_PENNER = 4
} ice_ease_type;

/* ============================== Functions ============================== */

/* Functions for Linear Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_linear(ice_ease_type ease_type, ...);

/* Functions for Quadratic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_in_out(ice_ease_type ease_type, ...);

/* Functions for Cubic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_in_out(ice_ease_type ease_type, ...);

/* Functions for Quartic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_in_out(ice_ease_type ease_type, ...);

/* Functions for Quintic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_in_out(ice_ease_type ease_type, ...);

/* Functions for Sinusoidal Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_in_out(ice_ease_type ease_type, ...);

/* Functions for Exponential Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_in_out(ice_ease_type ease_type, ...);

/* Functions for Circular Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_in_out(ice_ease_type ease_type, ...);

/* Functions for Elastic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_in_out(ice_ease_type ease_type, ...);

/* Functions for Back Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_in_out(ice_ease_type ease_type, ...);

/* Functions for Bounce Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_in(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_out(ice_ease_type ease_type, ...);
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_in_out(ice_ease_type ease_type, ...);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_EASE_IMPL)

#include <stdarg.h>
#include <math.h>

/* [INTERNAL] Assigns variable arguments to array */
#define ICE_EASE_ASSIGN_ARGS            \
    double args[4];                     \
    va_list argv;                       \
    unsigned i;                         \
                                        \
    va_start(argv, ease_type);          \
                                        \
    for (i = 0; i < ease_type; i++) {   \
        args[i] = va_arg(argv, double); \
    }                                   \
                                        \
    va_end(argv);                       \

/* [INTERNAL] Generates the variable x from array */
#define ICE_EASE_LOAD_ARG               \
    double x = args[0];                 \

/* [INTERNAL] Generates the 4 variables (t, b, c, d) from array */
#define ICE_EASE_LOAD_FOUR_ARGS         \
    double t = args[0];                 \
    double b = args[1];                 \
    double c = args[2];                 \
    double d = args[3];                 \

/* Functions for Linear Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_linear(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return x;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c * t / d + b;
    }

    return 0;
}

/* Functions for Quadratic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return x * x;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c * (t /= d) * t + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS
    
    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return 1 - (1 - x) * (1 - x);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return -c * (t /= d) * (t - 2) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quad_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return (x < 0.5) ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS

        if ((t /= d / 2) < 1) return c / 2 * t * t + b;
        return -c / 2 * ((--t) * (t - 2) - 1) + b;
    }

    return 0;
}

/* Functions for Cubic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return x * x * x;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c * (t /= d) * t * t + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return 1 - pow(1 - x, 3);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c * ((t = t / d - 1) * t * t + 1) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_cubic_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        if (x < 0.5) return 4 * x * x * x;
        return 1 - pow(-2 * x + 2, 3) / 2;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        if ((t /= d / 2) < 1) return c / 2 * t * t * t + b;
        return c / 2 * ((t -= 2) * t * t + 2) + b;
    }

    return 0;
}

/* Functions for Quartic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return x * x * x * x;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c * (t /= d) * t * t * t + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return 1 - pow(1 - x, 4);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return -c * ((t = t / d - 1) * t * t * t - 1) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quart_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        if (x < 0.5) return 8 * x * x * x * x;
        return 1 - pow(-2 * x + 2, 4) / 2;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS

        if ((t /= d / 2) < 1) return c / 2 * t * t * t * t + b;
        return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
    }

    return 0;
}

/* Functions for Quintic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return x * x * x * x * x;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c * (t /= d) * t * t * t * t + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return 1 - pow(1 - x, 5);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c * ((t = t / d - 1) * t * t * t * t + 1) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_quint_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        if (x < 0.5) return 16 * x * x * x * x * x;
        return 1 - pow(-2 * x + 2, 5) / 2;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        if ((t /= d / 2) < 1) return c / 2 * t * t * t * t * t + b;
        return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
    }

    return 0;
}

/* Functions for Sinusoidal Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return 1 - cos((x * ICE_EASE_PI) / 2);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return -c * cos(t / d * (ICE_EASE_PI / 2)) + c + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return sin((x * ICE_EASE_PI) / 2);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c * sin(t / d * (ICE_EASE_PI / 2)) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_sine_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return -(cos(ICE_EASE_PI * x) - 1) / 2;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return -c / 2 * (cos(ICE_EASE_PI * t / d) - 1) + b;
    }

    return 0;
}

/* Functions for Exponential Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return (x == 0) ? 0 : pow(2, 10 * x - 10);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        if (t == 0) return b;
        return c * pow(2, 10 * (t / d - 1)) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return (x == 1) ? 1 : 1 - pow(2, -10 * x);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        if (t == d) return b + c;
        return c * (-pow(2, -10 * t / d) + 1) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_expo_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG

        if (x == 0) return 0;
        else if (x == 1) return 1;

        if (x < 0.5) return pow(2, 20 * x - 10) / 2;
        return (2 - pow(2, -20 * x + 10)) / 2;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS

        if (t == 0) return b;
        else if (t == d) return b + c;
        else if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
        return c / 2 * (-pow(2, -10 * --t) + 2) + b;
    }

    return 0;
}

/* Functions for Circular Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return 1 - sqrt(1 - pow(x, 2));

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return -c * (sqrt(1 - (t /= d) * t) - 1) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return sqrt(1 - pow(x - 1, 2));

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c * sqrt(1 - (t = t / d - 1) * t) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_circ_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        if (x < 0.5) return (1 - sqrt(1 - pow(2 * x, 2))) / 2;
        return (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t * t) - 1) + b;
        return c / 2 * (sqrt(1 - (t -= 2) * t) + 1) + b;
    }

    return 0;
}

/* Functions for Elastic Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        double c4 = (2 * ICE_EASE_PI) / 3;

        if (x == 0) return 0;
        else if (x == 1) return 1;

        return -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        double p = d * 0.3;
        double a = c;
        double s = p / 4;
        double postFix = a * pow(2, 10 * (t -= 1));

        if (t == 0) return b;
        else if ((t /= d) == 1) return b + c;
        return -(postFix * sin((t * d - s) * (2 * ICE_EASE_PI) / p)) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        double c4 = (2 * ICE_EASE_PI) / 3;

        if (x == 0) return 0;
        else if (x == 1) return 1;
        return pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        double p = d * 0.3;
        double a = c;
        double s = p / 4;
        double postFix;

        if (t == 0) return 0;
        else if (t == 1) return 1;

        if (t < 1) {
            postFix = a * pow(2, 10 * (t -= 1));
            return -0.5 * (postFix * sin((t * d - s) * (2 * ICE_EASE_PI) / p)) + b;
        }

        postFix = a * pow(2, -10 * (t -= 1));
        return postFix * sin((t * d - s) * (2 * ICE_EASE_PI) / p) * 0.5 + c + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_elastic_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        double c5 = (2 * ICE_EASE_PI) / 4.5;

        if (x == 0) return 0;
        else if (x == 1) return 1;

        if (x < 0.5) return -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2;
        return (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        double p = d * (0.3 * 1.5);
        double a = c;
        double s = p / 4;
        double postFix;

        if (t == 0) return 0;
        else if (t == 1) return 1;

        if (t < 1) {
            postFix = a * pow(2, 10 * (t -= 1));
            return -0.5 * (postFix * sin((t * d - s) * (2 * ICE_EASE_PI) / p)) + b;
        }

        postFix = a * pow(2, -10 * (t -= 1));
        return postFix * sin((t * d - s) * (2 * ICE_EASE_PI) / p) * 0.5 + c + b;
    }

    return 0;
}

/* Functions for Back Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        double c1 = 1.70158;
        double c3 = c1 + 1;

        return c3 * x * x * x - c1 * x * x;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        double s = 1.70158;

        return c * (t /= d) * t * ((s + 1) * t - s) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        double c1 = 1.70158;
        double c3 = c1 + 1;
        return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        double s = 1.70158;
        return c * ((t = t / d - 1) * t * ((s + 1) * t + s) + 1) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_back_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        double c1 = 1.70158;
        double c2 = c1 * 1.525;

        if (x < 0.5) return (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2;
        return (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        double s = 1.70158;
        double v = 1.525;

        if ((t /= d / 2) < 1) return c / 2 * (t * t * (((s *= v) + 1) * t - s)) + b;
        return c / 2 * ((t -= 2) * t * (((s *= v) + 1) * t + s) + 2) + b;
    }

    return 0;
}

/* Functions for Bounce Easing */
ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_in(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        return 1 - ice_ease_bounce_out(ease_type, 1 - x);

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        return c - ice_ease_bounce_out(ease_type, d - t, 0, c, d) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG
        double n1 = 7.5625;
        double d1 = 2.75;

        if (x < 1 / d1) return n1 * x * x;
        else if (x < 2 / d1) return n1 * (x -= 1.5 / d1) * x + 0.75;
        else if (x < 2.5 / d1) return n1 * (x -= 2.25 / d1) * x + 0.9375;
        return n1 * (x -= 2.625 / d1) * x + 0.984375;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        double n1 = 7.5625;
        double d1 = 2.75;

        if ((t /= d) < (1 / d1)) return c * (n1 * t * t) + b;
        else if (t < (2 / d1)) return c * (n1 * (t -= (1.5 / d1)) * t + 0.75) + b;
        else if (t < (2.5 / d1)) return c * (n1 * (t -= (2.25 / d1)) * t + 0.9375) + b;
        return c * (n1 * (t -= (2.625 / d1)) * t + 0.984375) + b;
    }

    return 0;
}

ICE_EASE_API double ICE_EASE_CALLCONV ice_ease_bounce_in_out(ice_ease_type ease_type, ...) {
    ICE_EASE_ASSIGN_ARGS

    if (ease_type == ICE_EASE_TYPE_PROGRESS) {
        ICE_EASE_LOAD_ARG

        if (x < 0.5) return (1 - ice_ease_bounce_out(ease_type, 1 - 2 * x)) / 2;
        return (1 + ice_ease_bounce_out(ease_type, 2 * x - 1)) / 2;

    } else if (ease_type == ICE_EASE_TYPE_PENNER) {
        ICE_EASE_LOAD_FOUR_ARGS
        
        if (t < d / 2) return ice_ease_bounce_in(ease_type, t * 2, 0, c, d) * 0.5 + b;
        return ice_ease_bounce_out(ease_type, t * 2 - d, 0, c, d) * 0.5 + c * 0.5 + b;
    }

    return 0;
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
