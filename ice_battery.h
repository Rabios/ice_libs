// Written by Rabia Alhaffar in 14/April/2021
// ice_battery.h
// Single-Header Cross-Platform C library to get battery level and status...
// Updated: 20/June/2021

// Special thanks goes to Christopher Mitchell at https://cemetech.net for this code, Which Linux implementation built on top of.
// https://www.cemetech.net/forum/viewtopic.php?t=3638

///////////////////////////////////////////////////////////////////////////////////////////
// ice_battery.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_battery is cross-platform single-header C library to get battery level and status.

Works on:

1. Windows and Xbox platforms
2. OSX
3. Linux
4. BeOS/Haiku
5. Android
6. iOS
7. Emscripten
8. UWP
9. PSP
10. PSVita
11. Nintendo Switch
12. Tizen

[2] USAGE:
Define ICE_BATTERY_IMPL Then include ice_battery.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// ice_battery LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_battery is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_BATTERY_H
#define ICE_BATTERY_H

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
#  if defined(ICE_BATTERY_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_BATTERY_CALLCONV_FASTCALL)
#    define ICE_BATTERY_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_BATTERY_CALLCONV_STDCALL)
#    define ICE_BATTERY_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_BATTERY_CALLCONV_CDECL)
#    define ICE_BATTERY_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_BATTERY_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_BATTERY_CALLCONV_VECTORCALL)
#    define ICE_BATTERY_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_BATTERY_CALLCONV_FASTCALL)
#    define ICE_BATTERY_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_BATTERY_CALLCONV_STDCALL)
#    define ICE_BATTERY_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_BATTERY_CALLCONV_CDECL)
#    define ICE_BATTERY_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_BATTERY_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_BATTERY_CALLCONV_VECTORCALL)
#    define ICE_BATTERY_CALLCONV __vectorcall
#  elif defined(ICE_BATTERY_CALLCONV_FASTCALL)
#    define ICE_BATTERY_CALLCONV __fastcall
#  elif defined(ICE_BATTERY_CALLCONV_STDCALL)
#    define ICE_BATTERY_CALLCONV __stdcall
#  elif defined(ICE_BATTERY_CALLCONV_CDECL)
#    define ICE_BATTERY_CALLCONV __cdecl
#  else
#    define ICE_BATTERY_CALLCONV
#  endif
#else
#  define ICE_BATTERY_CALLCONV
#endif

#if !(defined(ICE_BATTERY_UWP) || defined(ICE_BATTERY_MICROSOFT) || defined(ICE_BATTERY_LINUX) || defined(ICE_BATTERY_BEOS) || defined(ICE_BATTERY_ANDROID) || defined(ICE_BATTERY_IOS) || defined(ICE_BATTERY_OSX) || defined(ICE_BATTERY_WEB) || defined(ICE_BATTERY_PSP) || defined(ICE_BATTERY_PSVITA) || defined(ICE_BATTERY_SWITCH))
#  define ICE_BATTERY_PLATFORM_AUTODETECTED
#endif

// ice_battery autodetection system (Huge but still worthy...)
#if defined(ICE_BATTERY_PLATFORM_AUTODETECTED)
#  if defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android)
#    define ICE_BATTERY_ANDROID
#  elif defined(__TIZEN_H__) || defined(TIZEN_DEPRECATION) || defined(__TIZEN__)
#    define ICE_BATTERY_TIZEN
#  elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__DARWIN) || defined(_DARWIN)
#    if defined(APPLE_IOS) || defined(IOS) || defined(__IPHONEOS__) || defined(TARGET_OS_SIMULATOR) || defined(__IOS__) || defined(__APPLE_IOS__) || defined(IOS_OBJ_C) || defined(TARGET_OS_IOS)
#      define ICE_BATTERY_IOS
#    else 
#      define ICE_BATTERY_OSX
#    endif
#  elif defined(__EMSCRIPTEN__) || defined(__EMSCRIPTEN) || defined(EMSCRIPTEN)
#    define ICE_BATTERY_WEB
#  elif (defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)) || (defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU))
#    define ICE_BATTERY_BEOS
#  elif defined(__linux__) || defined(__LINUX__) || defined(LINUX) || defined(__LINUX) || defined(__linux) || defined(linux) && !(defined(__ANDROID__) || defined(ANDROID) || defined(__ANDROID) || defined(__android))
#    define ICE_BATTERY_LINUX
#  elif defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#    if defined(WINAPI_FAMILY_SYSTEM) || defined(WINAPI_PARTITION_APP)
#      define ICE_BATTERY_UWP
#    else
#      define ICE_BATTERY_MICROSOFT
#    end
#  elif defined(__SWITCH__) || defined(NINTENDO_SWITCH) || defined(__NX__) || defined(_SWITCH)
#    define ICE_BATTERY_SWITCH
#  elif defined(PSP) || defined(__PSP__) || defined(__psp__) || defined(__PSP) || defined(_PSP)
#    define ICE_BATTERY_PSP
#  elif defined(_PSVITA) || defined(VITA) || defined(__vita__) || defined(__PSVITA) || defined(__VITA__) || defined(_PSVITA) || defined(SN_TARGET_PSP2) || defined(__PSV__) || defined(__psv__) || defined(_PSV) || defined(__PSVita__) || defined(__PSVita)
#    define ICE_BATTERY_PSVITA
#  endif
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_BATTERY_EXTERN) && defined(ICE_BATTERY_STATIC))
#  define ICE_BATTERY_EXTERN
#endif

#if defined(ICE_BATTERY_EXTERN)
#  define ICE_BATTERY_APIDEF extern
#elif defined(ICE_BATTERY_STATIC)
#  define ICE_BATTERY_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_BATTERY_INLINE to enable inline functionality.
#if defined(ICE_BATTERY_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_BATTERY_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_BATTERY_INLINEDEF inline
#  endif
#else
#  define ICE_BATTERY_INLINEDEF
#endif

// Allow to build DLL via ICE_BATTERY_DLLEXPORT or ICE_BATTERY_DLLIMPORT if desired!
// Else, Just define API as extern C code!
#if defined(ICE_BATTERY_MICROSOFT)
#  if defined(ICE_BATTERY_DLLEXPORT)
#    define ICE_BATTERY_API __declspec(dllexport) ICE_BATTERY_INLINEDEF
#  elif defined(ICE_BATTERY_DLLIMPORT)
#    define ICE_BATTERY_API __declspec(dllimport) ICE_BATTERY_INLINEDEF
#  else
#    define ICE_BATTERY_API ICE_BATTERY_APIDEF ICE_BATTERY_INLINEDEF
#  endif
#else
#  define ICE_BATTERY_API ICE_BATTERY_APIDEF ICE_BATTERY_INLINEDEF
#endif

// UWP can't work with C as his API mostly written in C++, They should be used with C++! :(
#ifdef ICE_BATTERY_UWP
#  if !defined(__cplusplus)
#    error "ice_battery's UWP implementation requires C++!"
#  endif
#endif

// Provide support for bool type!
#if defined(__STDC__) && __STDC_VERSION__ >= 199901L
#  include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
    typedef enum bool { false, true } bool;
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_battery DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_BATTERY_TRUE    = 0,
    ICE_BATTERY_FALSE   = -1,
} ice_battery_bool;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_battery FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
ICE_BATTERY_API  ice_battery_bool    ICE_BATTERY_CALLCONV  ice_battery_init(void);
ICE_BATTERY_API  int                 ICE_BATTERY_CALLCONV  ice_battery_level(void);
ICE_BATTERY_API  ice_battery_bool    ICE_BATTERY_CALLCONV  ice_battery_charging(void);
ICE_BATTERY_API  ice_battery_bool    ICE_BATTERY_CALLCONV  ice_battery_level_full(void);
ICE_BATTERY_API  ice_battery_bool    ICE_BATTERY_CALLCONV  ice_battery_level_high(void);
ICE_BATTERY_API  ice_battery_bool    ICE_BATTERY_CALLCONV  ice_battery_level_mid(void);
ICE_BATTERY_API  ice_battery_bool    ICE_BATTERY_CALLCONV  ice_battery_level_low(void);
ICE_BATTERY_API  ice_battery_bool    ICE_BATTERY_CALLCONV  ice_battery_close(void);

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_battery IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_BATTERY_IMPL)

#if defined(ICE_BATTERY_WEB)
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

EmscriptenBatteryEvent bat_ev;

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    return (emscripten_get_battery_status(&bat_ev) == EMSCRIPTEN_RESULT_SUCCESS) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    EMSCRIPTEN_RESULT res = emscripten_get_battery_status(&bat_ev);
    
    if (res == EMSCRIPTEN_RESULT_SUCCESS) {
        return (int)(bat_ev.level * 100);
    }
    
    return 0;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    EMSCRIPTEN_RESULT res = emscripten_get_battery_status(&bat_ev);
    
    if (res == EMSCRIPTEN_RESULT_SUCCESS) {
        return (bat_ev.charging) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
    }
    
    return ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    return ICE_BATTERY_TRUE;
}

#elif defined(ICE_BATTERY_ANDROID)
#include <jni.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

static JavaVM* mJavaVM;
static pthread_key_t thkey;
jobject clipboard;
JNIEnv* env;

jstring iname;
jmethodID imid;

jstring bname;
jmethodID bmid;

jobject intent;

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    int status = (*mJavaVM)->AttachCurrentThread(mJavaVM, &env, NULL);
    
    if (status < 0) {
        return ICE_BATTERY_FALSE;
    }
    pthread_setspecific(thkey, (void*) env);    
    
    jmethodID mid;

    mid = (*env)->GetStaticMethodID(env, mActivityClass, "getContext", "()Landroid/content/Context;");
    jobject context = (*env)->CallStaticObjectMethod(env, mActivityClass, mid);

    jstring action = (*env)->NewStringUTF(env, "android.intent.action.BATTERY_CHANGED");

    jclass cls = (*env)->FindClass(env, "android/content/IntentFilter");

    mid = (*env)->GetMethodID(env, cls, "<init>", "(Ljava/lang/String;)V");
    jobject filter = (*env)->NewObject(env, cls, mid, action);

    (*env)->DeleteLocalRef(env, action);

    mid = (*env)->GetMethodID(env, mActivityClass, "registerReceiver", "(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)Landroid/content/Intent;");
    intent = (*env)->CallObjectMethod(env, context, mid, NULL, filter);

    (*env)->DeleteLocalRef(env, filter);

    cls = (*env)->GetObjectClass(env, intent);

    imid = (*env)->GetMethodID(env, cls, "getIntExtra", "(Ljava/lang/String;I)I");
    bmid = (*env)->GetMethodID(env, cls, "getBooleanExtra", "(Ljava/lang/String;Z)Z");
    
    return ICE_BATTERY_TRUE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    iname = (*env)->NewStringUTF(env, "level");
    int level = (*env)->CallIntMethod(env, intent, imid, iname, -1);
    (*env)->DeleteLocalRef(env, iname);
    
    iname = (*env)->NewStringUTF(env, "scale");
    int scale = (*env)->CallIntMethod(env, intent, imid, iname, -1);
    (*env)->DeleteLocalRef(env, iname);
    
    if ((level == -1) || (scale == -1)) {
        return 0;
    } else {
        return (int) (level * 100 / scale);
    }
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    iname = (*env)->NewStringUTF(env, "plugged");
    int res = (*env)->CallIntMethod(env, intent, imid, iname, -1);
    (*env)->DeleteLocalRef(env, iname);
    
    return (res > 0) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    (*env)->DeleteLocalRef(env, intent);
    return ICE_BATTERY_TRUE;
}

#elif defined(ICE_BATTERY_TIZEN)
#include <device/battery.h>
#include <device/callback.h> 

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    return ICE_BATTERY_TRUE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    int res = 0;
    
    if (device_battery_get_percent(&res) == 0) {
        return res;
    }
    
    return -1;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    bool res;
    
    if (device_battery_is_charging(&res) == 0) {
        return res ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
    }
    
    return ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    return ICE_BATTERY_TRUE;
}

#elif defined(ICE_BATTERY_IOS)
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include <math.h>

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    [[UIDevice currentDevice] setBatteryMonitoringEnabled:YES];
    return ICE_BATTERY_TRUE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    return (int) ([[UIDevice currentDevice] batteryLevel] * 100);
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    return ([[UIDevice currentDevice] batteryState] == 2) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    return ICE_BATTERY_TRUE;
}

#elif defined(ICE_BATTERY_OSX)
#import <Foundation/Foundation.h>
#include <CoreFoundation/CoreFoundation.h>
#import <IOKit/ps/IOPowerSources.h>
#import <IOKit/ps/IOPSKeys.h>

CFTypeRef blob;
CFArrayRef sources;
CFDictionaryRef psrc;
void *psval;
int sourcesCount;

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    blob = IOPSCopyPowerSourcesInfo();
    sources = IOPSCopyPowerSourcesList(blob);
    sourcesCount = CFArrayGetCount(sources);
    
    if (sourcesCount > 0) {
        psrc = IOPSGetPowerSourceDescription(blob, CFArrayGetValueAtIndex(sources, 0));
        return (psrc == NULL) ? ICE_BATTERY_FALSE : ICE_BATTERY_TRUE;
    }
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    int cur_cap = 0;
    int max_cap = 0;
    int percent;
    
    psval = CFDictionaryGetValue(psrc, CFSTR(kIOPSCurrentCapacityKey));
    CFNumberGetValue((CFNumberRef) psval, kCFNumberSInt32Type, &cur_cap);
    
    psval = CFDictionaryGetValue(psrc, CFSTR(kIOPSMaxCapacityKey));
    CFNumberGetValue((CFNumberRef) psval, kCFNumberSInt32Type, &max_cap);
    
    percent = (int)((float)(cur_cap / max_cap) * 100.0f);
    
    return percent;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    return (CFDictionaryGetValue(psrc, CFSTR(kIOPSIsChargingKey)) == kCFBooleanTrue) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    return ICE_BATTERY_TRUE;
}

#elif defined(ICE_BATTERY_BEOS)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <drivers/Drivers.h>

// From apm.h
#define ICE_BATTERY_APM_DEVICE_PATH "/dev/misc/apm"
#define ICE_BATTERY_APM_FUNC_OFFSET 0x5300
#define ICE_BATTERY_APM_FUNC_GET_POWER_STATUS 10
#define ICE_BATTERY_APM_DEVICE_ALL 1
#define ICE_BATTERY_APM_BIOS_CALL (B_DEVICE_OP_CODES_END + 3)

static int ice_battery_fd;

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    ice_battery_fd fd = open("/dev/misc/apm", O_RDONLY);
    
    if (fd == -1) {
        return ICE_BATTERY_FALSE;
    }
    
    return ICE_BATTERY_TRUE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    uint16 regs[6];
    uint8 ac_status;
    uint8 battery_status;
    uint8 battery_flags;
    uint8 battery_life;
    int rc;

    memset(regs, '\0', sizeof(regs));
    regs[0] = ICE_BATTERY_APM_FUNC_OFFSET + ICE_BATTERY_APM_FUNC_GET_POWER_STATUS;
    regs[1] = ICE_BATTERY_APM_DEVICE_ALL;
    rc = ioctl(ice_battery_fd, ICE_BATTERY_APM_BIOS_CALL, regs);
    
    if (rc < 0) {
        return 0;
    }

    ac_status = regs[1] >> 8;
    battery_status = regs[1] & 0xFF;
    battery_flags = regs[2] >> 8;
    battery_life = regs[2] & 0xFF;

    /* in theory, _something_ should be set in battery_flags, right? */
    if (battery_flags == 0x00) {        /* older APM BIOS? Less fields. */
        battery_time = 0xFFFF;
        if (battery_status == 0xFF) {
            battery_flags = 0xFF;
        } else {
            battery_flags = (1 << battery_status);
        }
    }
    
    const int pct = (int) battery_life;
    if (pct != 255) {       /* 255 == unknown */
        return (pct > 100) ? 100 : pct; /* clamp between 0%, 100% */
    }
    
    return 0;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    uint16 regs[6];
    uint8 ac_status;
    uint8 battery_status;
    uint8 battery_flags;
    uint8 battery_life;
    int rc;

    memset(regs, '\0', sizeof(regs));
    regs[0] = ICE_BATTERY_APM_FUNC_OFFSET + ICE_BATTERY_APM_FUNC_GET_POWER_STATUS;
    regs[1] = ICE_BATTERY_APM_DEVICE_ALL;
    rc = ioctl(ice_battery_fd, ICE_BATTERY_APM_BIOS_CALL, regs);
    
    if (rc < 0) {
        return ICE_BATTERY_FALSE;
    }

    ac_status = regs[1] >> 8;
    battery_status = regs[1] & 0xFF;
    battery_flags = regs[2] >> 8;
    battery_life = regs[2] & 0xFF;

    /* in theory, _something_ should be set in battery_flags, right? */
    if (battery_flags == 0x00) {        /* older APM BIOS? Less fields. */
        battery_time = 0xFFFF;
        if (battery_status == 0xFF) {
            battery_flags = 0xFF;
        } else {
            battery_flags = (1 << battery_status);
        }
    }
    
    if (battery_flags == 0xFF) {        /* unknown state */
        return ICE_BATTERY_FALSE;
    } else if (battery_flags & (1 << 7)) {      /* no battery */
        return ICE_BATTERY_FALSE;
    } else if (battery_flags & (1 << 3)) {      /* charging */
        return ICE_BATTERY_TRUE;
    } else if (ac_status == 1) {
        return ICE_BATTERY_TRUE;        /* on AC, not charging. */
    } else {
        return ICE_BATTERY_TRUE;     /* not on AC. */
    }
    
    return ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    close(ice_battery_fd);
}

#elif defined(ICE_BATTERY_LINUX)
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ICE_BATTERY_STATE_PATH  "/proc/acpi/battery/BAT0/state"
#define ICE_BATTERY_INFO_PATH   "/proc/acpi/battery/BAT0/info"

static int ice_battery_state_handle;
static int ice_battery_info_handle;

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    ice_battery_info_handle = open(ICE_BATTERY_INFO_PATH, O_RDONLY);
    
    if (ice_battery_info_handle == -1) {
        return ICE_BATTERY_FALSE;
    }
    
    ice_battery_state_handle = open(ICE_BATTERY_STATE_PATH, O_RDONLY);
    
    if (ice_battery_state_handle == -1) {
        return ICE_BATTERY_FALSE;
    }
    
    return ICE_BATTERY_TRUE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    long int battRate_mA = 0;
    long int battMax_mAh = 0;
    long int battRemain_mAh = 0;
    char buffer[BATT_READ_BUFLEN];
    char tok_unit[8];
    int readoffset;
    short int readstate = 0,readlen = 0;
   
   while (readstate < 2) {
      readoffset = 0;
      readstate = 0;
      while (!readstate) {
         if (0 > (readlen = read(ice_battery_state_handle, buffer + readoffset, 1))) {
            return 0;
         }
         if (!readlen) {
            readstate=2;
            break;
         }
         if ('\n' == *(buffer + readoffset)) {
            readstate++;
            *(buffer + readoffset + 1) = '\0';
         }
         readoffset++;
      }
      if (readstate == 2) break;
      if (NULL != strstr(buffer,"last full capacity")) {
         if (0 >= sscanf(buffer + 25,"%ld %s", &battMax_mAh, tok_unit)) {
            return 0;
         }
         break;
      }
   }
   
   readstate = 0;
   while (readstate < 2) {
      readoffset = 0;
      readstate = 0;
      while (!readstate) {
         if (0 > (readlen = read(ice_battery_state_handle, buffer + readoffset, 1))) {
            return 0;
         }
         if (0 == readlen) {
            readstate=2;
            break;
         }
         if ('\n' == *(buffer + readoffset)) {
            readstate++;
            *(buffer + readoffset + 1) = '\0';
         }
         readoffset++;
      }
      if (readstate == 2) break;
      if (NULL != strstr(buffer, "present rate")) {
         if (0 >= sscanf(buffer + 25, "%ld %s", &battRate_mA, tok_unit)) {
            return 0;
         }
      } else if (NULL != strstr(buffer,"remaining capacity")) {
         if (0 >= sscanf(buffer + 25, "%ld %s", &battRemain_mAh, tok_unit)) {
            return 0;
         }
      }
   }
   
   return (int) (100.0f * ((float)battRemain_mAh / (float)battMax_mAh));
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    char buffer[512];
    int readoffset;
    short int readstate = 0, readlen = 0;
   
    while (readstate < 2) {
        readoffset = 0;
        readstate = 0;
       
        while (!readstate) {
            if (0 > (readlen = read(ice_battery_state_handle, buffer + readoffset, 1))) {
                return ICE_BATTERY_FALSE;
            }
            if (0 == readlen) {
                readstate = 2;
                break;
            }
            if ('\n' == *(buffer + readoffset)) {
                readstate++;
                *(buffer + readoffset + 1) = '\0';
            }
            readoffset++;
        }
        
        if (readstate == 2) break;
        
        if (NULL != strstr(buffer, "charging state")) {
            if (NULL != strstr(buffer, "discharging")) return ICE_BATTERY_FALSE;
            else if (NULL != strstr(buffer, "charged")) return ICE_BATTERY_TRUE;
            else return ICE_BATTERY_TRUE;
        }
    }
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    close(ice_battery_info_handle);
    close(ice_battery_state_handle);
    return ICE_BATTERY_TRUE;
}

#elif defined(ICE_BATTERY_MICROSOFT)
#include <windows.h>

SYSTEM_POWER_STATUS ibstatus;

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    return (GetSystemPowerStatus(&ibstatus) != FALSE) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    if (GetSystemPowerStatus(&ibstatus)) {
        return (ibstatus.BatteryLifePercent != 255) ibstatus.BatteryLifePercent : 0;
    }
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    if (GetSystemPowerStatus(&ibstatus)) {
        return (ibstatus.BatteryFlag & 8 > 0) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
    }
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    return ICE_BATTERY_TRUE;
}

#elif defined(ICE_BATTERY_UWP)

using namespace Windows::Devices::Power;

BatteryReport bstate;

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    return ICE_BATTERY_TRUE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    bstate = Battery.AggregateBattery.GetReport();

    double percentage = (bstate.RemainingCapacityInMilliwattHours.Value / (double)bstate.FullChargeCapacityInMilliwattHours.Value);

    return (int)(percentage * 100);
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    return (!(Battery.AggregateBattery.GetReport().Status == Windows.System.Power.BatteryStatus.Discharging)) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    return ICE_BATTERY_TRUE;
}

#elif defined(ICE_BATTERY_SWITCH)
#include <switch.h>

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    Result res = psmGetBatteryChargePercentage(&charge);
    return (!R_FAILED(res)) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    u32 charge;
    Result res = psmGetBatteryChargePercentage(&charge);
    
    if (R_FAILED(res)) {
        return 0;
    }
    
    return (int) charge;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    ChargerType chtype;
    Result res = psmGetChargerType(&chtype);
    
    if (R_FAILED(res)) {
        return ICE_BATTERY_FALSE;
    }
    
    return (chtype > 0) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE; 
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    psmExit();
}

#elif defined(ICE_BATTERY_PSP)
#include <psppower.h>

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    return scePowerIsBatteryExist() ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    return scePowerGetBatteryLifePercent();
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    return scePowerIsBatteryCharging() ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    return ICE_BATTERY_TRUE;
}

#elif defined(ICE_BATTERY_PSVITA)
#include <psp2/power.h>

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_init(void) {
    return ICE_BATTERY_TRUE;
}

ICE_BATTERY_API int ICE_BATTERY_CALLCONV ice_battery_level(void) {
    return scePowerGetBatteryLifePercent();
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_charging(void) {
    return (scePowerIsBatteryCharging()) ? ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_close(void) {
    return ICE_BATTERY_TRUE;
}

#endif

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_level_full(void) {
    return (ice_battery_level() == 100) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_level_high(void) {
    return (ice_battery_level() < 100 && ice_battery_level() >= 50) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_level_mid(void) {
    return (ice_battery_level() < 50 && ice_battery_level() >= 25) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

ICE_BATTERY_API ice_battery_bool ICE_BATTERY_CALLCONV ice_battery_level_low(void) {
    return (ice_battery_level() < 25) ? ICE_BATTERY_TRUE : ICE_BATTERY_FALSE;
}

#endif  // ICE_BATTERY_IMPL
#endif  // ICE_BATTERY_H
