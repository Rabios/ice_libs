/*
ice_cpu.h, Single-Header Cross-Platform C library to get CPU info!


================================== Full Overview ==================================

ice_cpu.h is Single-Header Cross-Platform C library for working with CPU, It gives information about device's CPU!

To use it #define ICE_CPU_IMPL then #include "ice_cpu.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

// Define the implementation of the library and include it
#define ICE_CPU_IMPL 1
#include "ice_cpu.h"

#include <stdio.h>

// Helper
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(int argc, char **argv) {
    // Struct that contains CPU information
    ice_cpu_info cpu;
    
    // Get CPU information
    ice_cpu_bool res = ice_cpu_get_info(&cpu);
    
    // If the function failed to retrieve CPU information, Trace error then terminate the program
    if (res == ICE_CPU_FALSE) {
        trace("ice_cpu_get_info", "ERROR: failed to retrieve CPU information!");
        return -1;
    }
    
    // Print CPU informations
    printf("CPU Name: %s\nCPU Cores: %u\n", cpu.name, cpu.cores);
    
    return 0;
}


=================================== Library API ===================================

// Boolean Enum, To avoid including stdbool.h
typedef enum ice_cpu_bool {
    ICE_CPU_FALSE = -1,
    ICE_CPU_TRUE = 0
} ice_cpu_bool;

// Struct that contains informations about the CPU (Name, Cores, etc...)
typedef struct ice_cpu_info {
    const char *name;
    unsigned cores;
} ice_cpu_info;

// Retrives info about CPU and stores info into ice_cpu_info struct by pointing to, Returns ICE_CPU_TRUE on success or ICE_CPU_FALSE on failure
ice_cpu_bool ice_cpu_get_info(ice_cpu_info *cpu_info);


================================== Linking Flags ==================================

1. Microsoft Windows    =>  -lkernel32
2. Other                =>  -lc (-lc Most times automatically linked...)

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragma preprocessor


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_cpu.h in the code...
#define ICE_CPU_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_CPU_VECTORCALL      // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_CPU_FASTCALL        // fastcall
#define ICE_CPU_STDCALL         // stdcall
#define ICE_CPU_CDECL           // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_CPU_APPLE           // Apple Platforms
#define ICE_CPU_MICROSOFT       // Microsoft Platforms
#define ICE_CPU_BSD             // BSD (FreeBSD, DragonFly BSD, NetBSD, OpenBSD)
#define ICE_CPU_HPUX            // HP-UX
#define ICE_CPU_IRIX            // IRIX
#define ICE_CPU_UNIX            // Unix and Unix-Like
#define ICE_CPU_BLACKBERRY      // BlackBerry (QNX, QNX Neutrino, BlackBerry PlayBook, BlackBerry 10)

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_CPU_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_CPU_DLLEXPORT       // Export the symbols to build as shared library
#define ICE_CPU_DLLIMPORT       // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_CPU_INLINE          // inlines library functions (Only works on C99 Standard and above)
#define ICE_CPU_EXTERN          // externs library functions
#define ICE_CPU_STATIC          // statics library functions

// NOTE: You cannot #define both ICE_CPU_EXTERN and ICE_CPU_STATIC together in the code...


============================== Implementation Resources ===========================

1. https://en.wikipedia.org/wiki/CPUID
2. https://www.linux.it/~rubini/docs/sysctl
3. https://docstore.mik.ua/manuals/hp-ux/en/B2355-60130/mpctl.2.html
4. https://man7.org/linux/man-pages/man3/sysconf.3.html
5. https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsysteminfo


================================= Support ice_libs ================================

ice_cpu.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
7. Share ice_libs everywhere!


*/

#if !defined(ICE_CPU_H)
#define ICE_CPU_H 1

/* Allow to use calling conventions if desired... */
#if defined(ICE_CPU_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_CPU_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_CPU_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_CPU_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_CPU_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_CPU_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_CPU_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_CPU_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_CPU_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_CPU_CDECL)
#  if defined(_MSC_VER)
#    define ICE_CPU_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_CPU_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_CPU_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_CPU_HPUX) || defined(ICE_CPU_IRIX) || defined(ICE_CPU_APPLE) || defined(ICE_CPU_MICROSOFT) || defined(ICE_CPU_BSD) || defined(ICE_CPU_UNIX) || defined(ICE_CPU_BLACKBERRY))
#  define ICE_CPU_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
#if defined(ICE_CPU_PLATFORM_AUTODETECTED)
#  if defined(__HPUX__)
#    define ICE_CPU_HPUX 1
#  elif defined(__SGI__)
#    define ICE_CPU_IRIX 1
#  elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__)
#    define ICE_CPU_APPLE 1
#  elif (defined(__BLACKBERRY10__) || defined(__BB10__)) || (defined(__QNX__) || defined(__QNXNTO__) || defined(__PLAYBOOK__))
#    define ICE_CPU_BLACKBERRY 1
#  elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_CPU_MICROSOFT 1
#  elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__OpenBSD__)
#    define ICE_CPU_BSD 1
#  elif defined(__unix__) || defined(__unix)
#    define ICE_CPU_UNIX 1
#  else
#    error "ice_cpu.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_CPU_EXTERN) && defined(ICE_CPU_STATIC))
#  define ICE_CPU_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_CPU_EXTERN)
#  define ICE_CPU_APIDEF extern
#elif defined(ICE_CPU_STATIC)
#  define ICE_CPU_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_CPU_INLINE to enable inline functionality.
*/
#if defined(ICE_CPU_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_CPU_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_CPU_INLINEDEF inline
#  endif
#else
#  define ICE_CPU_INLINEDEF
#endif

/*
Allow to build DLL via ICE_CPU_DLLEXPORT or ICE_CPU_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_CPU_MICROSOFT)
#  if defined(ICE_CPU_DLLEXPORT)
#    define ICE_CPU_API __declspec(dllexport) ICE_CPU_INLINEDEF
#  elif defined(ICE_CPU_DLLIMPORT)
#    define ICE_CPU_API __declspec(dllimport) ICE_CPU_INLINEDEF
#  else
#    define ICE_CPU_API ICE_CPU_APIDEF ICE_CPU_INLINEDEF
#  endif
#else
#  define ICE_CPU_API ICE_CPU_APIDEF ICE_CPU_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_cpu_bool {
    ICE_CPU_FALSE = -1,
    ICE_CPU_TRUE = 0
} ice_cpu_bool;

/* Struct that contains informations about the CPU (Name, Cores, etc...) */
typedef struct ice_cpu_info {
    const char *name;
    unsigned cores;
} ice_cpu_info;

/* ============================== Functions ============================== */

/* Retrives info about CPU and stores info into ice_cpu_info struct by pointing to, Returns ICE_CPU_TRUE on success or ICE_CPU_FALSE on failure */
ICE_CPU_API ice_cpu_bool ICE_CPU_CALLCONV ice_cpu_get_info(ice_cpu_info *cpu_info);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_CPU_IMPL)

#if defined(ICE_CPU_HPUX) || defined(ICE_CPU_IRIX) || defined(ICE_CPU_UNIX)
#  include <cpuid.h>
#  if defined(ICE_CPU_HPUX)
#    include <sys/mpctl.h>
#  elif defined(ICE_CPU_IRIX) || defined(ICE_CPU_UNIX)
#    include <unistd.h>
#  endif
unsigned ice_cpu_brand[12];
#elif defined(ICE_CPU_MICROSOFT)
#  if defined(_MSC_VER)
#    include <windows.h>
#    include <intrin.h>
#    pragma comment(lib, "kernel32.lib")
#  else
#    include <sysinfoapi.h>
#    include <cpuid.h>
#  endif
unsigned ice_cpu_brand[12];
#elif defined(ICE_CPU_BSD) || defined(ICE_CPU_APPLE) || defined(ICE_CPU_BLACKBERRY)
#  include <stddef.h>
#  if defined(__FreeBSD__) || defined(__DragonFly__) || defined(ICE_CPU_APPLE)
#    include <sys/types.h>
#  elif defined(__NetBSD__) || defined(__OpenBSD__) || defined(ICE_CPU_BLACKBERRY)
#    include <sys/param.h>
#  endif
#  include <sys/sysctl.h>
#endif

/* Retrives info about CPU and stores info into ice_cpu_info struct by pointing to, Returns ICE_CPU_TRUE on success or ICE_CPU_FALSE on failure */
ICE_CPU_API ice_cpu_bool ICE_CPU_CALLCONV ice_cpu_get_info(ice_cpu_info* cpu_info) {
#if defined(ICE_CPU_BSD) || defined(ICE_CPU_APPLE) || defined(ICE_CPU_BLACKBERRY)
    char brand[128];
    unsigned cores;
    int res, mibs[2][2] = {
        { CTL_HW, HW_MODEL },
        { CTL_HW, HW_NCPU }
    };
    size_t len;
    
    len = sizeof(brand);
    res = sysctl(mibs[0], 2, &brand, &len, 0, 0);
    if (res != 0) goto failure;
    
    len = sizeof(cores);
    res = sysctl(mibs[1], 2, &cores, &len, 0, 0);
    if (res != 0) goto failure;

    cpu_info->name = (const char*) brand;
    cpu_info->cores = cores;

#elif defined(ICE_CPU_MICROSOFT) || defined(ICE_CPU_UNIX) || defined(ICE_CPU_HPUX) || defined(ICE_CPU_IRIX)
    unsigned cores = 0;
    int res;

#if defined(ICE_CPU_MICROSOFT)
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    cores = (unsigned) sysinfo.dwNumberOfProcessors;
#elif defined(ICE_CPU_UNIX)
    cores = sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(ICE_CPU_HPUX)
    cores = mpctl(MPC_GETNUMSPUS, 0, 0);
#elif defined(ICE_CPU_IRIX)
    cores = sysconf(_SC_NPROC_ONLN);
#endif

    res = __get_cpuid_max(0x80000004, 0);
    if (res == 0) goto failure;

    __get_cpuid(0x80000002, ice_cpu_brand + 0x0, ice_cpu_brand + 0x1, ice_cpu_brand + 0x2, ice_cpu_brand + 0x3);
    __get_cpuid(0x80000003, ice_cpu_brand + 0x4, ice_cpu_brand + 0x5, ice_cpu_brand + 0x6, ice_cpu_brand + 0x7);
    __get_cpuid(0x80000004, ice_cpu_brand + 0x8, ice_cpu_brand + 0x9, ice_cpu_brand + 0xa, ice_cpu_brand + 0xb);
    
    cpu_info->name = (const char*)(&ice_cpu_brand);
    cpu_info->cores = cores;
#endif

    return ICE_CPU_TRUE;

failure:
    cpu_info->name = 0;
    cpu_info->cores = 0;

    return ICE_CPU_FALSE;
}

#endif  /* ICE_CPU_IMPL */
#endif  /* ICE_CPU_H */

/*
ice_cpu.h is dual-licensed, Choose the one you prefer!

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
