/*
ice_ffi.h, Single-Header Cross-Platform C library for working with shared libs!


================================== Full Overview ==================================

ice_ffi.h, Single-Header Cross-Platform C library for working with shared libs, It allows to load symbols from shared libs depending on platform!

To use it #define ICE_FFI_IMPL then #include "ice_ffi.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

// Define the implementation of the library and include it
#define ICE_FFI_IMPL 1
#include "ice_ffi.h"

#include <stdio.h>

// Helper
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(int argc, char **argv) {
    ice_ffi_bool unload_res;
    ice_ffi_handle lib;
    unsigned (*F42)(void); // function from shared library/object
    
    // Define path of the shared library/object depending on platform
#if defined(ICE_FFI_MICROSOFT)
    const char *path = "lib42.dll";
#else
    const char *path = "./lib42.so";
#endif

    // Load the shared library/object
    lib = ice_ffi_load(path);
    
    // If the function failed to load the shared library/object, Trace error then terminate the program
    if (lib == NULL) {
        trace("ice_ffi_load", "ERROR: failed to load shared library/object!");
        return -1;
    }
    
    // If the shared library/object loaded successfully, Get the function F42 symbol to call it!
    *(unsigned**)(&F42) = ice_ffi_get(lib, "F42");
    
    // If the function failed to get symbol from shared library/object, Trace error then terminate the program
    if (F42 == NULL) {
        trace("ice_ffi_get", "ERROR: failed to get symbol from shared library/object!");
        return -1;
    }
    
    // Call the function and print the result!
    printf("F42 call result: %u\n", F42());
    
    // When done, Unload symbols and the shared library/object
    F42 = NULL;
    unload_res = ice_ffi_unload(lib);
    
    // If the function failed to unload shared library/object, Trace error then terminate the program
    if (unload_res == ICE_FFI_FALSE) {
        trace("ice_ffi_unload", "ERROR: failed to unload shared library/object!");
        return -1;
    }
    
    return 0;
}


=================================== Library API ===================================

// Boolean Enum, To avoid including stdbool.h
typedef enum ice_ffi_bool {
    ICE_FFI_FALSE = -1,
    ICE_FFI_TRUE = 0
} ice_ffi_bool;

// Handle, Represents pointer to loaded shared library or symbol loaded from shared library
typedef void* ice_ffi_handle;

// Loads shared library from path, Returns handle of loaded shared library on success or NULL on failure
ice_ffi_handle ice_ffi_load(const char *path);

// Unloads shared library loaded via ice_ffi_load, Returns ICE_FFI_TRUE on success or ICE_FFI_FALSE on failure
ice_ffi_bool ice_ffi_unload(ice_ffi_handle lib);

// Loads symbol from shared library loaded via ice_ffi_load, Returns pointer to loaded symbol on success or NULL on failure
ice_ffi_handle ice_ffi_get(ice_ffi_handle lib, const char *symbol);


================================== Linking Flags ==================================

1. Microsoft Windows    => -lkernel32
2. Linux                => -ldl

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragma preprocessor


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_ffi.h in the code...
#define ICE_FFI_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_FFI_VECTORCALL      // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_FFI_FASTCALL        // fastcall
#define ICE_FFI_STDCALL         // stdcall
#define ICE_FFI_CDECL           // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_FFI_MICROSOFT       // Microsoft Platforms
#define ICE_FFI_BEOS            // BeOS and Haiku
#define ICE_FFI_UNIX            // Unix and Unix-like (Unix/Linux and anything else based on these)

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_FFI_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_FFI_DLLEXPORT       // Export the symbols to build as shared library
#define ICE_FFI_DLLIMPORT       // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_FFI_INLINE          // inlines library functions (Only works on C99 Standard and above)
#define ICE_FFI_EXTERN          // externs library functions
#define ICE_FFI_STATIC          // statics library functions

// NOTE: You cannot #define both ICE_FFI_EXTERN and ICE_FFI_STATIC together in the code...


============================== Implementation Resources ===========================

1. https://docs.microsoft.com/en-us/cpp/build/linking-an-executable-to-a-dll?view=msvc-170#linking-explicitly
2. https://tldp.org/HOWTO/Program-Library-HOWTO/dl-libraries.html
3. https://www.haiku-os.org/legacy-docs/bebook/TheKernelKit_Images.html


================================= Support ice_libs ================================

ice_ffi.h is one of libraries that ice_libs project provide...

You could can or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star (and/or fork) the repo on GitHub: https://github.com/Rabios/ice_libs
7. Share ice_libs Everywhere!
8. Join the Discord Server: https://discord.gg/KfkwXjCW


*/

#if !defined(ICE_FFI_H)
#define ICE_FFI_H 1

/* Allow to use calling conventions if desired... */
#if defined(ICE_FFI_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_FFI_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_FFI_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_FFI_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_FFI_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_FFI_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_FFI_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_FFI_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_FFI_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_FFI_CDECL)
#  if defined(_MSC_VER)
#    define ICE_FFI_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_FFI_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_FFI_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_FFI_MICROSOFT) || defined(ICE_FFI_UNIX) || defined(ICE_FFI_BEOS))
#  define ICE_FFI_PLATFORM_AUTODETECTED 1
#endif

/* Platform detection */
#if defined(ICE_FFI_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_FFI_MICROSOFT 1
#  elif defined(__HAIKU__) || defined(__BEOS__)
#    define ICE_FFI_BEOS 1
#  elif defined(__unix__) || defined(__unix)
#    define ICE_FFI_UNIX 1
#  else
#    error "ice_ffi.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_FFI_EXTERN) && defined(ICE_FFI_STATIC))
#  define ICE_FFI_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_FFI_EXTERN)
#  define ICE_FFI_APIDEF extern
#elif defined(ICE_FFI_STATIC)
#  define ICE_FFI_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_FFI_INLINE to enable inline functionality.
*/
#if defined(ICE_FFI_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_FFI_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_FFI_INLINEDEF inline
#  endif
#else
#  define ICE_FFI_INLINEDEF
#endif

/*
Allow to build DLL via ICE_FFI_DLLEXPORT or ICE_FFI_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_FFI_MICROSOFT)
#  if defined(ICE_FFI_DLLEXPORT)
#    define ICE_FFI_API __declspec(dllexport) ICE_FFI_INLINEDEF
#  elif defined(ICE_FFI_DLLIMPORT)
#    define ICE_FFI_API __declspec(dllimport) ICE_FFI_INLINEDEF
#  else
#    define ICE_FFI_API ICE_FFI_APIDEF ICE_FFI_INLINEDEF
#  endif
#else
#  define ICE_FFI_API ICE_FFI_APIDEF ICE_FFI_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_ffi_bool {
    ICE_FFI_FALSE = -1,
    ICE_FFI_TRUE = 0
} ice_ffi_bool;

/* Handle, Represents pointer to loaded shared library or symbol loaded from shared library */
typedef void* ice_ffi_handle;

/* ============================== Functions ============================== */

/* Loads shared library from path, Returns handle of loaded shared library on success or NULL on failure */
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_load(const char *path);

/* Unloads shared library loaded via ice_ffi_load, Returns ICE_FFI_TRUE on success or ICE_FFI_FALSE on failure */
ICE_FFI_API ice_ffi_bool ICE_FFI_CALLCONV ice_ffi_unload(ice_ffi_handle lib);

/* Loads symbol from shared library loaded via ice_ffi_load, Returns pointer to loaded symbol on success or NULL on failure */
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_get(ice_ffi_handle lib, const char *symbol);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_FFI_IMPL)

#if defined(ICE_FFI_MICROSOFT)
#  if defined(_MSC_VER)
#    include <windows.h>
#    pragma comment(lib, "kernel32.lib")
#  else
#    include <libloaderapi.h>
#  endif
#elif defined(ICE_FFI_BEOS)
#  include <be/kernel/image.h>
#elif defined(ICE_FFI_UNIX)
#  include <dlfcn.h>
#endif

/* Loads shared library from path, Returns handle of loaded shared library on success or NULL on failure */
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_load(const char *path) {
#if defined(ICE_FFI_MICROSOFT)
    return LoadLibraryA(path);
#elif defined(ICE_FFI_BEOS)
    isize lib = load_add_on(path);

    if (lib < 0) return 0;
    
    return (ice_ffi_handle) lib;
#elif defined(ICE_FFI_UNIX)
    return dlopen(path, RTLD_NOW | RTLD_GLOBAL);
#endif
}

/* Unloads shared library loaded via ice_ffi_load, Returns ICE_FFI_TRUE on success or ICE_FFI_FALSE on failure */
ICE_FFI_API ice_ffi_bool ICE_FFI_CALLCONV ice_ffi_unload(ice_ffi_handle lib) {
    int res;

#if defined(ICE_FFI_MICROSOFT)
    res = (FreeLibrary(lib) != 0) ? 0 : -1;
#elif defined(ICE_FFI_BEOS)
    res = unload_add_on((isize) lib);
#elif defined(ICE_FFI_UNIX)
    res = dlclose(lib);
#endif

    lib = 0;

    return (res == 0) ? ICE_FFI_TRUE : ICE_FFI_FALSE;
}

/* Loads symbol from shared library loaded via ice_ffi_load, Returns pointer to loaded symbol on success or NULL on failure */
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_get(ice_ffi_handle lib, const char *symbol) {
#if defined(ICE_FFI_MICROSOFT)
    return GetProcAddress(lib, symbol);
#elif defined(ICE_FFI_BEOS)
    ice_ffi_handle sym;
    int res = get_image_symbol((isize) lib, symbol, B_SYMBOL_TYPE_ANY, &sym);

    return (res == 0) ? sym : 0;
#elif defined(ICE_FFI_UNIX)
    return dlsym(lib, symbol);
#endif
}

#endif  /* ICE_FFI_IMPL */
#endif  /* ICE_FFI_H */

/*
ice_ffi.h is dual-licensed, Choose the one you prefer!

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
