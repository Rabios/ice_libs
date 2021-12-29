/*
ice_cpu.h, Single-Header Cross-Platform C library to get CPU info!


================================== Full Overview ==================================

ice_cpu.h is Single-Header Cross-Platform C library for working with CPU, It gives information about device's CPU!

To use it #define ICE_CPU_IMPL then #include "ice_cpu.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

#define ICE_CPU_IMPL
#include "ice_cpu.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Fetch CPU information (Name, Cores, etc...)
    ice_cpu_info status = ice_cpu_status();
    
    // Print the information
    printf("CPU Model: %s\n", status.name);
    printf("CPU Cores: %u\n", status.cores);
    
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
    const char* name;
    unsigned cores;
} ice_cpu_info;

// Fetches CPU information and stores result in cpu_info, Returns ICE_CPU_TRUE pn success or ICE_CPU_FALSE on failure
ICE_CPU_API ice_cpu_bool ICE_CPU_CALLCONV ice_cpu_get_status(ice_cpu_info* cpu_info);


================================== Linking Flags ==================================

1. Microsoft Windows    =>  -lkernel32
2. BlackBerry 10        =>  -lbbdevice

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragmas


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
#define ICE_CPU_BSD             // BSD (FreeBSD, OpenBSD, NetBSD, DragonFly BSD)
#define ICE_CPU_HPUX            // HP-UX
#define ICE_CPU_IRIX            // IRIX
#define ICE_CPU_UNIX            // Unix and Unix-Like
#define ICE_CPU_BB10            // BlackBerry 10

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_CPU_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_CPU_DLLEXPORT       // Export the symbols to build as shared library
#define ICE_CPU_DLLIMPORT       // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_CPU_INLINE          // inlines library functions (Only works on C99 Standard and above)
#define ICE_CPU_EXTERN          // externs library functions
#define ICE_CPU_STATIC          // statics library functions

// NOTE: ICE_CPU_EXTERN and ICE_CPU_STATIC cannot be #defined together in the code...


============================== Implementation Resources ===========================

1. https://en.wikipedia.org/wiki/CPUID
2. https://developer.apple.com/documentation/kernel/1387446-sysctlbyname
3. https://developer.apple.com/documentation/kernel/1502514-host_info
4. https://www.freebsd.org/cgi/man.cgi?query=sysctlbyname
5. https://docstore.mik.ua/manuals/hp-ux/en/B2355-60130/mpctl.2.html
6. https://man7.org/linux/man-pages/man3/sysconf.3.html
7. https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsysteminfo
8. http://developer.blackberry.com/native/reference/cascades/bb__device__hardwareinfo.html


================================= Support ice_libs ================================

ice_cpu.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_CPU_H
#define ICE_CPU_H 1

/* Disable security warnings for MSVC compiler, We don't want to force using C11! */
#ifdef _MSC_VER
#  ifndef _CRT_SECURE_NO_DEPRECATE
#    define _CRT_SECURE_NO_DEPRECATE 1
#  endif
#  ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS 1
#  endif
#  pragma warning(disable:4996)
#endif

/* Define C interface for Windows libraries! ;) */
#ifndef CINTERFACE
#  define CINTERFACE 1
#endif

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
#if !(defined(ICE_CPU_HPUX) || defined(ICE_CPU_IRIX) || defined(ICE_CPU_APPLE) || defined(ICE_CPU_MICROSOFT) || defined(ICE_CPU_BSD) || defined(ICE_CPU_UNIX) || defined(ICE_CPU_BB10))
#  define ICE_CPU_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
/* The implementation of BlackBerry 10 written in C++ instead of C because his native APIs uses C++ :( */
#if defined(ICE_CPU_PLATFORM_AUTODETECTED)
#  if defined(__HPUX__)
#    define ICE_CPU_HPUX 1
#  elif defined(__SGI__)
#    define ICE_CPU_IRIX 1
#  elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__)
#    define ICE_CPU_APPLE 1
#  elif defined(__BLACKBERRY10__) || defined(__BB10__)
#    define ICE_CPU_BB10 1
#    if !defined(__cplusplus)
#      error "BlackBerry 10 implementation for ice_cpu.h cannot be used with C code, Only C++ :("
#    endif
#  elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_CPU_MICROSOFT 1
#  elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
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
    const char* name;
    unsigned cores;
} ice_cpu_info;

/* ============================== Functions ============================== */

/* Fetches CPU information and stores result in cpu_info, Returns ICE_CPU_TRUE pn success or ICE_CPU_FALSE on failure */
ICE_CPU_API ice_cpu_bool ICE_CPU_CALLCONV ice_cpu_get_status(ice_cpu_info* cpu_info);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_CPU_IMPL)

#if defined(ICE_CPU_HPUX) || defined(ICE_CPU_IRIX) || defined(ICE_CPU_UNIX)
#  include <string.h>
#  include <cpuid.h>
#  if defined(ICE_CPU_HPUX)
#    include <sys/mpctl.h>
#  elif defined(ICE_CPU_IRIX) || defined(ICE_CPU_UNIX)
#    include <unistd.h>
#  endif
uint32_t ice_cpu_brand[12];
#elif defined(ICE_CPU_APPLE)
#  include <mach/mach.h>
#  include <mach/mach_host.h>
#  include <sys/types.h>
#  include <sys/sysctl.h>
#elif defined(ICE_CPU_MICROSOFT)
#  include <string.h>
#  if defined(_MSC_VER)
#    include <windows.h>
#    include <intrin.h>
#    pragma comment(lib, "kernel32.lib")
#  else
#    include <sysinfoapi.h>
#    include <cpuid.h>
#  endif
const char ice_cpu_brand[0x40];
#elif defined(ICE_CPU_BSD)
#  include <sys/types.h>
#  include <sys/sysctl.h>
#elif defined(ICE_CPU_BB10)
#  include <QtCore/QString>
#  include <QtCore/QByteArray>
#  include <bb/device/HardwareInfo>
using namespace bb;
#endif

/* Fetches CPU information and stores result in cpu_info, Returns ICE_CPU_TRUE pn success or ICE_CPU_FALSE on failure */
ICE_CPU_API ice_cpu_bool ICE_CPU_CALLCONV ice_cpu_get_status(ice_cpu_info* cpu_info) {
#if defined(ICE_CPU_APPLE)
    size_t buflen = 128;
    char brand[128];
    mach_port_t host_port = mach_host_self();
    host_basic_info_data_t info;
    mach_msg_type_number_t info_count = HOST_BASIC_INFO_COUNT;
    int res = host_info(host_port, HOST_BASIC_INFO, (host_info_t) &info, &info_count);

    if (res != 0) goto failure;

    res = sysctlbyname("machdep.cpu.brand_string", &brand, &buflen, 0, 0);

    if (res != 0) goto failure;

    cpu_info->name = brand;
    cpu_info->cores = (unsigned) avail_cpus;
    
#elif defined(ICE_CPU_MICROSOFT)
    SYSTEM_INFO sysinfo;
    unsigned exts;
    unsigned long cpuinf_size;
    int i;
    
#if defined(_MSC_VER)
    int cpuinf[4] = { -1 };
#else
    int cpuinf[4] = { 0, 0, 0, 0 };
#endif

    GetSystemInfo(&sysinfo);
    __cpuid(cpuinf, 0x80000000);
    
    exts = cpuinf[0];
    memset(ice_cpu_brand, 0, sizeof(ice_cpu_brand));
    cpuinf_size = sizeof(cpuinf);
    
    for (i = 0x80000000; i <= exts; ++i) {
        __cpuid(cpuinf, i);
        
        if  (i == 0x80000002) {
            memcpy(ice_cpu_brand, cpuinf, cpuinf_size);
        } else if  (i == 0x80000003) {
            memcpy(ice_cpu_brand + 16, cpuinf, cpuinf_size);
        } else if  (i == 0x80000004) {
            memcpy(ice_cpu_brand + 32, cpuinf, cpuinf_size);
        }
    }

    cpu_info->name = ice_cpu_brand;
    cpu_info->cores = (unsigned) sysinfo.dwNumberOfProcessors;

#elif defined(ICE_CPU_BSD)
    char brand[128];
    unsigned cores;
    int res;

    res = sysctlbyname("hw.model", &brand, &buflen, 0, 0);
    if (res != 0) goto failure;

    res = sysctlbyname("hw.ncpu", &cores, 0, 0, 0);
    if (res != 0) goto failure;

    cpu_info->name = brand;
    cpu_info->cores = (unsigned) cores;
    
#elif defined(ICE_CPU_UNIX) || defined(ICE_CPU_HPUX) || defined(ICE_CPU_IRIX)
    unsigned cores = 0;
    unsigned res;

#if defined(ICE_CPU_UNIX)
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
    
    cpu_info->name = &ice_cpu_brand;
    cpu_info->cores = cores;
    
#elif defined(ICE_CPU_BB10)
    bb::HardwareInfo info;
    
    unsigned cores = info.processorCount();
    QString model = info.processorModel(0);
    QByteArray model_utf8 = model.toUtf8();
    const char* cpuname = model_utf8.constData();
    
    delete info;
    delete model;
    delete model_utf8;

    cpu_info->name = cpuname;
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
