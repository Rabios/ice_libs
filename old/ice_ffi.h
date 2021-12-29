// Written by Rabia Alhaffar in 26/March/2021
// ice_ffi.h
// Single-Header Cross-Platform C library for working with shared libs!
// Updated: 25/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_ffi.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_ffi is cross-platform single-header C library for working with shared libraries and get
addresses from them without hassle.

Works on Windows, OSX, Linux, Android, iOS, Haiku, BeOS! (Linux-based platforms could work...)

[2] IMPLEMENTATION:
Windows             -> LoadLibrary, FreeLibrary, GetProcAddress
Haiku/BeOS          -> load_add_on, unload_add_on, get_image_symbol
Elsewhere           -> dlopen, dlsym, dlclose

[3] USAGE:
Define ICE_FFI_IMPL then include ice_ffi.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_ffi
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_ffi by possibly one of following things:
//
// 1. Test ice_ffi on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_ffi LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_ffi is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_FFI_H
#define ICE_FFI_H

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
#  if defined(ICE_FFI_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_FFI_CALLCONV_FASTCALL)
#    define ICE_FFI_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_FFI_CALLCONV_STDCALL)
#    define ICE_FFI_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_FFI_CALLCONV_CDECL)
#    define ICE_FFI_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_FFI_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_FFI_CALLCONV_VECTORCALL)
#    define ICE_FFI_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_FFI_CALLCONV_FASTCALL)
#    define ICE_FFI_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_FFI_CALLCONV_STDCALL)
#    define ICE_FFI_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_FFI_CALLCONV_CDECL)
#    define ICE_FFI_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_FFI_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_FFI_CALLCONV_VECTORCALL)
#    define ICE_FFI_CALLCONV __vectorcall
#  elif defined(ICE_FFI_CALLCONV_FASTCALL)
#    define ICE_FFI_CALLCONV __fastcall
#  elif defined(ICE_FFI_CALLCONV_STDCALL)
#    define ICE_FFI_CALLCONV __stdcall
#  elif defined(ICE_FFI_CALLCONV_CDECL)
#    define ICE_FFI_CALLCONV __cdecl
#  else
#    define ICE_FFI_CALLCONV
#  endif
#else
#  define ICE_FFI_CALLCONV
#endif

// If no platform defined, This definition will define itself!
#if !(defined(ICE_FFI_MICROSOFT) || defined(ICE_FFI_UNIX) || defined(ICE_FFI_BEOS))
#  define ICE_FFI_PLATFORM_AUTODETECTED
#endif

// Platform detection
#if defined(ICE_FFI_PLATFORM_AUTODETECTED)
#  if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#    define ICE_FFI_MICROSOFT
#  elif defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU) || defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
#    define ICE_FFI_BEOS
#  else
#    define ICE_FFI_UNIX
#  endif
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_FFI_EXTERN) && defined(ICE_FFI_STATIC))
#  define ICE_FFI_EXTERN
#endif

#if defined(ICE_FFI_EXTERN)
#  define ICE_FFI_APIDEF extern
#elif defined(ICE_FFI_STATIC)
#  define ICE_FFI_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_FFI_INLINE to enable inline functionality.
#if defined(ICE_FFI_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_FFI_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_FFI_INLINEDEF inline
#  endif
#else
#  define ICE_FFI_INLINEDEF
#endif

// Allow to build DLL via ICE_FFI_DLLEXPORT or ICE_FFI_DLLIMPORT if desired!
// Else, Just define API as extern C code!
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

///////////////////////////////////////////////////////////////////////////////////////////
// ice_ffi DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_FFI_TRUE    = 0,
    ICE_FFI_FALSE   = -1,
} ice_ffi_bool;

typedef void* ice_ffi_handle;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_ffi FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
ICE_FFI_API  ice_ffi_handle  ICE_FFI_CALLCONV  ice_ffi_load_library(char* path);                                    // Loads a shared library (dll, so, dylib, etc...) from path, Returns ice_ffi_handle as handle to the library on success or NULL on failure.
ICE_FFI_API  ice_ffi_bool    ICE_FFI_CALLCONV  ice_ffi_unload_library(ice_ffi_handle lib);                          // Unloads a shared library (dll, so, dylib, etc...) with handle from path, Returns ICE_FFI_TRUE on unload success or ICE_FFI_FALSE on failure.
ICE_FFI_API  ice_ffi_handle  ICE_FFI_CALLCONV  ice_ffi_get_address(ice_ffi_handle lib, char* proc_name);            // Gets address value of name proc_name from shared library handle, Returns ice_ffi_handle as handle to the address could be casted to function, variable, Or anything else on success or NULL on failure.

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_ffi IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_FFI_IMPL)

#if defined(ICE_FFI_MICROSOFT)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_FFI_MICROSOFT IMPLEMENTATION    (Microsoft platforms)
///////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>

// Loads a shared library (dll, so, dylib, etc...) from path, Returns ice_ffi_handle as handle to the library on success or NULL on failure.
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_load_library(char* path) {
    return (HMODULE)LoadLibraryA(path);
}

// Unloads a shared library (dll, so, dylib, etc...) with handle from path, Returns ICE_FFI_TRUE on unload success or ICE_FFI_FALSE on failure.
ICE_FFI_API ice_ffi_bool ICE_FFI_CALLCONV ice_ffi_unload_library(ice_ffi_handle lib) {
    return (FreeLibrary((HMODULE)lib) == TRUE) ? ICE_FFI_TRUE : ICE_FFI_FALSE;
}

// Gets address value of name proc_name from shared library handle, Returns ice_ffi_handle as handle to the address could be casted to function, variable, Or anything else on success or NULL on failure.
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_get_address(ice_ffi_handle lib, char* proc_name) {
    return GetProcAddress(lib, proc_name);
}

#elif defined(ICE_FFI_UNIX)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_FFI_UNIX IMPLEMENTATION     (OSX, iOS, Android, Linux, BSD, etc...)
///////////////////////////////////////////////////////////////////////////////////////////
#include <dlfcn.h>

// Loads a shared library (dll, so, dylib, etc...) from path, Returns ice_ffi_handle as handle to the library on success or NULL on failure.
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_load_library(char* path) {
    return dlopen(path, RTDL_LAZY | RTDL_GLOBAL);
}

// Unloads a shared library (dll, so, dylib, etc...) with handle from path, Returns ICE_FFI_TRUE on unload success or ICE_FFI_FALSE on failure.
ICE_FFI_API ice_ffi_bool ICE_FFI_CALLCONV ice_ffi_unload_library(ice_ffi_handle lib) {
    return (dlclose(lib) == 0) ? ICE_FFI_TRUE : ICE_FFI_FALSE;
}

// Gets address value of name proc_name from shared library handle, Returns ice_ffi_handle as handle to the address could be casted to function, variable, Or anything else on success or NULL on failure.
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_get_address(ice_ffi_handle lib, char* proc_name) {
    return dlsym(lib, proc_name);
}

#elif defined(ICE_FFI_BEOS)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_FFI_BEOS IMPLEMENTATION     (Haiku and BeOS)
///////////////////////////////////////////////////////////////////////////////////////////
#include <image.h>

// Loads a shared library (dll, so, dylib, etc...) from path, Returns ice_ffi_handle as handle to the library on success or NULL on failure.
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_load_library(char* path) {
    return (image_id)load_add_on(path);
}

// Unloads a shared library (dll, so, dylib, etc...) with handle from path, Returns ICE_FFI_TRUE on unload success or ICE_FFI_FALSE on failure.
ICE_FFI_API ice_ffi_bool ICE_FFI_CALLCONV ice_ffi_unload_library(ice_ffi_handle lib) {
    return (unload_add_on(lib) == B_OK) ? ICE_FFI_TRUE : ICE_FFI_FALSE;
}

// Gets address value of name proc_name from shared library handle, Returns ice_ffi_handle as handle to the address could be casted to function, variable, Or anything else on success or NULL on failure.
ICE_FFI_API ice_ffi_handle ICE_FFI_CALLCONV ice_ffi_get_address(ice_ffi_handle lib, char* proc_name) {
    ice_ffi_handle addr;

    if (get_image_symbol(lib, proc_name, B_SYMBOL_TYPE_ANY, &addr) == B_OK) {
        return addr;
    }

    return NULL;
}

#endif

#endif  // ICE_FFI_IMPL
#endif  // ICE_FFI_H
