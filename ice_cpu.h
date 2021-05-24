// Written by Rabia Alhaffar in 13/May/2021
// ice_cpu.h
// Single-Header Cross-Platform C library to get CPU info!
// Updated: 25/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_cpu.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_cpu is Single-Header Cross-Platform C library to get CPU info!

Works on:

1. Windows and Xbox platforms
2. Apple platforms
3. Linux (Including BeOS, Haiku, Android, And any Linux-based System)
4. Emscripten
5. PSP
6. PSVita
7. PS1
8. PS2
9. PS3
10. PS4
11. 3DS
12. Switch
13. GameCube
14. Wii/WiiU
15. PS5 (_PS5)
16. IRIX
17. HP-UX
18. GBA
19. NDS

[2] IMPLEMENTATION:
Windows             -> GlobalMemoryStatusEx
Apple               -> host_statistics (mach.h and mach_host.h)
Unix, IRIX          -> sysconf
Emscripten          -> window.navigator.hardwareConcurrency
HP-UX               -> mpctl
Other platforms     -> Constants as nothing changes

[3] USAGE:
Define ICE_CPU_IMPL then include ice_cpu.h in your C/C++ code!

Thanks to caf on stackoverflow: https://stackoverflow.com/a/1290768/10896648

*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_cpu
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_cpu by possibly one of following things:
//
// 1. Test ice_cpu on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_cpu LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_cpu is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_CPU_H
#define ICE_CPU_H

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
#  if defined(ICE_CPU_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_CPU_CALLCONV_FASTCALL)
#    define ICE_CPU_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_CPU_CALLCONV_STDCALL)
#    define ICE_CPU_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_CPU_CALLCONV_CDECL)
#    define ICE_CPU_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_CPU_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_CPU_CALLCONV_VECTORCALL)
#    define ICE_CPU_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_CPU_CALLCONV_FASTCALL)
#    define ICE_CPU_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_CPU_CALLCONV_STDCALL)
#    define ICE_CPU_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_CPU_CALLCONV_CDECL)
#    define ICE_CPU_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_CPU_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_CPU_CALLCONV_VECTORCALL)
#    define ICE_CPU_CALLCONV __vectorcall
#  elif defined(ICE_CPU_CALLCONV_FASTCALL)
#    define ICE_CPU_CALLCONV __fastcall
#  elif defined(ICE_CPU_CALLCONV_STDCALL)
#    define ICE_CPU_CALLCONV __stdcall
#  elif defined(ICE_CPU_CALLCONV_CDECL)
#    define ICE_CPU_CALLCONV __cdecl
#  else
#    define ICE_CPU_CALLCONV
#  endif
#else
#  define ICE_CPU_CALLCONV
#endif

#if !(defined(ICE_CPU_MICROSOFT) || defined(ICE_CPU_UNIX) || defined(ICE_CPU_APPLE) || defined(ICE_CPU_WEB) || defined(ICE_CPU_PSP))
#  define ICE_CPU_PLATFORM_AUTODETECTED
#endif

// ice_cpu autodetection system (Huge but still worthy...)
#if defined(ICE_CPU_PLATFORM_AUTODETECTED)
#  if defined(__HPUX__)
#    define ICE_CPU_HPUX
#  elif defined(__SGI__)
#    define ICE_CPU_IRIX
#  elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__DARWIN) || defined(_DARWIN)
#    define ICE_CPU_APPLE
#  elif defined(__EMSCRIPTEN__) || defined(__EMSCRIPTEN) || defined(EMSCRIPTEN)
#    define ICE_CPU_WEB
#  elif defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#    define ICE_CPU_MICROSOFT
#  elif defined(__GAMEBOY__) || defined(__gba__) || defined(__GBA__)
#    define ICE_CPU_GAMEBOY
#  elif defined(_NDS) || defined(NDS) || defined(__NDS__) || defined (__NDS)
#    define ICE_CPU_NDS
#  elif defined(_3DS) || defined(__3DS__) || defined(__N3DS__)
#    define ICE_CPU_3DS
#  elif defined(__SWITCH__) || defined(NINTENDO_SWITCH) || defined(__NX__) || defined(_SWITCH)
#    define ICE_CPU_SWITCH
#  elif defined(GAMECUBE) || defined(__GAMECUBE__) || defined(__gamecube__)
#    define ICE_CPU_GAMECUBE
#  elif defined(__WII__) || defined(WIIU) || defined(WII) || defined(wiiu) || defined(wii) || defined(_WII) || defined(_WIIU) || defined(__WIIU__) || defined(__wii__) || defined(__wiiu__)
#    define ICE_CPU_WII
#  elif defined(__PSX__) || defined(PS1) || defined(__psx__) || defined(__PSONE__) || defined(PLAYSTATION_1) || defined(__PSX) || defined(_PSX)
#    define ICE_CPU_PS1
#  elif defined(__PS2__) || defined(_PS2) || defined(PS2) || defined(PLAYSTATION_2)
#    define ICE_CPU_PS2
#  elif defined(__PS3__) || defined(_PS3) || defined(__PS3) || defined(PS3) || defined(PLAYSTATION3) || defined(__PSL1GHT__)
#    define ICE_CPU_PS3
#  elif defined(PS4) || defined(ORBIS) || defined(__PS4__) || defined(__ORBIS__) || defined(_PS4) || defined(__PS4) || defined(PLAYSTATION4)
#    define ICE_CPU_PS4
#  elif defined(_PS5)
#    define ICE_CPU_PS5
#  elif defined(PSP) || defined(__PSP__) || defined(__psp__) || defined(__PSP) || defined(_PSP)
#    define ICE_CPU_PSP
#  elif defined(_PSVITA) || defined(VITA) || defined(__vita__) || defined(__PSVITA) || defined(__VITA__) || defined(_PSVITA) || defined(SN_TARGET_PSP2) || defined(__PSV__) || defined(__psv__) || defined(_PSV) || defined(__PSVita__) || defined(__PSVita)
#    define ICE_CPU_PSVITA
#  else
#    define ICE_CPU_UNIX
#  endif
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_CPU_EXTERN) && defined(ICE_CPU_STATIC))
#  define ICE_CPU_EXTERN
#endif

#if defined(ICE_CPU_EXTERN)
#  define ICE_CPU_APIDEF extern
#elif defined(ICE_CPU_STATIC)
#  define ICE_CPU_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_CPU_INLINE to enable inline functionality.
#if defined(ICE_AL_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_CPU_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_CPU_INLINEDEF inline
#  endif
#else
#  define ICE_CPU_INLINEDEF
#endif

// Allow to build DLL via ICE_CPU_DLLEXPORT or ICE_CPU_DLLIMPORT if desired!
// Else, Just define API as extern C code!
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

///////////////////////////////////////////////////////////////////////////////////////////
// ice_cpu DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_CPU_ARCH_NONE = -1,  // Trigger 16 and 8 bit CPUs
    ICE_CPU_ARCH_X86,        // 32 bit
    ICE_CPU_ARCH_X86_64,     // x64, x86_64, AMD64 and Intel 64
} ice_cpu_arch;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_cpu FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
ICE_CPU_API  unsigned int    ICE_CPU_CALLCONV  ice_cpu_cores_count(void);                // Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API  ice_cpu_arch    ICE_CPU_CALLCONV  ice_cpu_get_arch(void);                   // Returns CPU architecture.
ICE_CPU_API  char*           ICE_CPU_CALLCONV  ice_cpu_name(void);                       // Returns CPU name used by device as string.

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_cpu IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_CPU_IMPL)

#if defined(ICE_CPU_APPLE)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_APPLE IMPLEMENTATION    (Apple platforms)
///////////////////////////////////////////////////////////////////////////////////////////
#include <mach/mach.h>
#include <mach/mach_host.h>
#include <sys/types.h>
#include <sys/sysctl.h>

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    host_basic_info_data_t info;
    mach_msg_type_number_t info_count;

    info_count = HOST_BASIC_INFO_COUNT;
    host_info(mach_host_self(), HOST_BASIC_INFO, (host_info_t)&info, &info_count);

    return (unsigned int)(info.max_cpus);
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    char buf[128];
    size_t buflen = 128;
    sysctlbyname("machdep.cpu.brand_string", &buf, &buflen, NULL, 0);
    return buf;
}

#elif defined(ICE_CPU_WEB)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_WEB IMPLEMENTATION    (Web platforms)
///////////////////////////////////////////////////////////////////////////////////////////
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return (unsigned int) EM_ASM_INT({
        return (window.navigator.hardwareConcurrency || 0);
    });
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "[undefined]";
}

#elif defined(ICE_CPU_MICROSOFT)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_MICROSOFT IMPLEMENTATION    (Microsoft platforms)
///////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>

#if (_MSC_VER)
#  include <intrin.h>
#else
#  include <cpuid.h>
#endif

#include <string.h>

SYSTEM_INFO sysinfo;
char CPUBrandString[0x40];

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}

#if (_MSC_VER)
// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    int CPUInfo[4] = {-1};
    __cpuid(CPUInfo, 0x80000000);
    unsigned int nExIds = CPUInfo[0];

    memset(CPUBrandString, 0, sizeof(CPUBrandString));
    
    for (int i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(CPUInfo, i);
        
        if  (i == 0x80000002) {
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        } else if  (i == 0x80000003) {
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        } else if  (i == 0x80000004) {
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        }
    }
    
    return CPUBrandString;
}

#else
// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    unsigned int CPUInfo[4] = {0,0,0,0};
    __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    unsigned int nExIds = CPUInfo[0];
    memset(CPUBrandString, 0, sizeof(CPUBrandString));
    
    for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

        if (i == 0x80000002) {
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000003) {
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000004) {
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        }
    }
    
    return CPUBrandString;
}

#endif

#elif defined(ICE_CPU_3DS)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_3DS IMPLEMENTATION    (Nintendo 3DS)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 2;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "Dual-core ARM11 MPCore @ 268 MHz";
}

#elif defined(ICE_CPU_SWITCH)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_SWITCH IMPLEMENTATION    (Nintendo Switch)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 4;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "Quad-core ARM Cortex-A57 @ 1.02 GHz"; // To comply with latest Nintendo updates.
}

#elif defined(ICE_CPU_GAMECUBE)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_GAMECUBE IMPLEMENTATION    (Nintendo GameCube)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 1;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "IBM PowerPC 750CXe Gekko @ 485 MHz";
}

#elif defined(ICE_CPU_WII)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_WII IMPLEMENTATION    (Nintendo Wii, Nintendo WiiU)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 3;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "IBM PowerPC Broadway @ 729 MHz";
}

#elif defined(ICE_CPU_PS1)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_PS1 IMPLEMENTATION    (Sony PlayStation 1)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 1;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "MIPS R3000A @ 33.8688 MHz";
}

#elif defined(ICE_CPU_PS2)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_PS2 IMPLEMENTATION    (Sony PlayStation 2)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 1;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "MIPS R5900 @ 294 MHz";
}

#elif defined(ICE_CPU_PS3)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_PS3 IMPLEMENTATION    (Sony PlayStation 3)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 2;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "PLAYSTATION 3 (R) CELL-BROADBAND CPU @ 3.2 GHz";
}

#elif defined(ICE_CPU_PS4)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_PS4 IMPLEMENTATION    (Sony PlayStation 4)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 4;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "AMD x86-64 Jaguar @ 1.6 GHz";
}

#elif defined(ICE_CPU_PS5)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_PS5 IMPLEMENTATION    (Sony PlayStation 5)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 8;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "AMD Zen 2 @ 3.5 GHz";
}

#elif defined(ICE_CPU_PSP)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_PSP IMPLEMENTATION    (Sony PlayStation Portable)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 2;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "MIPS R4000 @ 222 MHz";
}

#elif defined(ICE_CPU_PSVITA)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_PSVITA IMPLEMENTATION    (Sony PlayStation Vita)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 4;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "ARM® Cortex™-A9 @ 333 MHz";
}

#elif defined(ICE_CPU_UNIX)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_UNIX IMPLEMENTATION     (Android, Linux, BSD, etc...)
///////////////////////////////////////////////////////////////////////////////////////////#include <unistd.h>
#include <cpuid.h>
#include <string.h>

char CPUBrandString[0x40];

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    unsigned int CPUInfo[4] = {0,0,0,0};
    __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    unsigned int nExIds = CPUInfo[0];
    memset(CPUBrandString, 0, sizeof(CPUBrandString));
    
    for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

        if (i == 0x80000002) {
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000003) {
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000004) {
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        }
    }
    
    return CPUBrandString;
}

#elif defined(ICE_CPU_HPUX)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_HPUX IMPLEMENTATION    (HP-UX)
///////////////////////////////////////////////////////////////////////////////////////////
#include <sys/mpctl.h>
#include <string.h>

char CPUBrandString[0x40];

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return mpctl(MPC_GETNUMSPUS, NULL, NULL);
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {    
    unsigned int CPUInfo[4] = {0,0,0,0};
    __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    unsigned int nExIds = CPUInfo[0];
    memset(CPUBrandString, 0, sizeof(CPUBrandString));
    
    for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

        if (i == 0x80000002) {
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000003) {
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000004) {
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        }
    }
    
    return CPUBrandString;
}

#elif defined(ICE_CPU_IRIX)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_IRIX IMPLEMENTATION    (IRIX)
///////////////////////////////////////////////////////////////////////////////////////////
#include <unistd.h>
#include <string.h>

char CPUBrandString[0x40];

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return sysconf(_SC_NPROC_ONLN);
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {    
    unsigned int CPUInfo[4] = {0,0,0,0};
    __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    unsigned int nExIds = CPUInfo[0];
    memset(CPUBrandString, 0, sizeof(CPUBrandString));
    
    for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

        if (i == 0x80000002) {
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000003) {
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        } else if (i == 0x80000004) {
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        }
    }
    
    return CPUBrandString;
}

#elif defined(ICE_CPU_GBA)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_GBA IMPLEMENTATION    (Nintendo Game Boy Advance)
///////////////////////////////////////////////////////////////////////////////////////////

// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 1;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "ARM7TDMI @ 16.78 MHz";
}

#elif defined(ICE_CPU_NDS)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_CPU_NDS IMPLEMENTATION    (Nintendo DS)
///////////////////////////////////////////////////////////////////////////////////////////
// Returns count of CPU cores device has as unsigned integer.
ICE_CPU_API unsigned int ICE_CPU_CALLCONV ice_cpu_cores_count(void) {
    return 2;
}

// Returns CPU name used by device as string.
ICE_CPU_API char* ICE_CPU_CALLCONV ice_cpu_name(void) {
    return "ARM946E-S @ 67 MHz, ARM7TDMI @ 33 MHz"
}

#endif

// Returns CPU architecture.
ICE_CPU_API ice_cpu_arch ICE_CPU_CALLCONV ice_cpu_get_arch(void) {
    if ((size_t)-1 > 0xffffffffUL) {
        return ICE_CPU_ARCH_X86_64;
    } else {
        if ((size_t)-1 < 4294967295) {
            return ICE_CPU_ARCH_NONE;
        } else {
            return ICE_CPU_ARCH_X86;
        }
    }
}

#endif  // ICE_CPU_IMPL
#endif  // ICE_CPU_H
