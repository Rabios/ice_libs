/*
ice_batt.h, Single-Header Cross-Platform C library to get battery info!


================================== Full Overview ==================================

ice_batt.h is Single-Header Cross-Platform C library for working with the Battery, It gives info about the Battery...

To use it #define ICE_BATT_IMPL then #include "ice_batt.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

#define ICE_BATT_IMPL
#include "ice_batt.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Fetch battery info
    ice_batt_info status = ice_batt_status();
    
    // Prints if battery exists and if charging and battery level
    printf("Battery Exists: %s\n", (status.exists == ICE_BATT_TRUE) ? "YES" : "NO");
    printf("Battery Charging: %s\n", (status.charging == ICE_BATT_TRUE) ? "YES" : "NO");
    printf("Battery Level: %u\n", status.level);
    
    return 0;
}


=================================== Library API ===================================

// Boolean Enum, To avoid including stdbool.h
typedef enum ice_batt_bool {
    ICE_BATT_FALSE = -1,
    ICE_BATT_TRUE = 0
} ice_batt_bool;

// Struct that contains battery status (Exists?, Charging?, Battery Level)
typedef struct ice_batt_info {
    ice_batt_bool exists;
    ice_batt_bool charging;
    unsigned level;
} ice_batt_info;

// [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_batt on Android, This Should be called first before other ice_batt.h functions
void ice_batt_use_native_activity(const void* activity);

// Returns curreny battery status
ice_batt_info ice_batt_status(void);


================================== Linking Flags ==================================

1. Microsoft Windows (Non-UWP)  =>  -lkernel32
2. BlackBerry 10                =>  -lbbdevice
3. iOS                          =>  -framework Foundation -framework UIKit
4. MacOS/OSX                    =>  -framework Foundation -framework CoreFoundation -framework IOKit
5. Nintendo Switch (libnx)      =>  -lnx
6. PlayStation Vita (vitasdk)   =>  -lScePower_stub

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragmas


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_clip.h in the code...
#define ICE_BATT_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_BATT_VECTORCALL     // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_BATT_FASTCALL       // fastcall
#define ICE_BATT_STDCALL        // stdcall
#define ICE_BATT_CDECL          // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_BATT_ANDROID        // Android
#define ICE_BATT_IOS            // iOS
#define ICE_BATT_OSX            // MacOS/OSX
#define ICE_BATT_TIZEN          // Tizen
#define ICE_BATT_WEB            // Web (Emscripten)
#define ICE_BATT_SWITCH         // Nintendo Switch (libnx)
#define ICE_BATT_PSP            // PlayStation Portable (pspsdk)
#define ICE_BATT_PSVITA         // PlayStation Vita (vitasdk)
#define ICE_BATT_BB10           // BlackBerry 10
#define ICE_BATT_UWP            // UWP (Univeral Windows Platform)
#define ICE_BATT_MICROSOFT      // Microsoft platforms (Non-UWP)
#define ICE_BATT_BSD            // BSD (FreeBSD, OpenBSD, NetBSD, DragonFly BSD)
#define ICE_BATT_UNIX           // Unix and Unix-Like

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_BATT_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_BATT_DLLEXPORT      // Export the symbols to build as shared library
#define ICE_BATT_DLLIMPORT      // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_BATT_INLINE         // inlines library functions (Only works on C99 Standard and above)
#define ICE_BATT_EXTERN         // externs library functions
#define ICE_BATT_STATIC         // statics library functions

// NOTE: ICE_BATT_EXTERN and ICE_BATT_STATIC cannot be #defined together in the code...


============================== Implementation Resources ===========================

1. https://docs.tizen.org/application/native/api/mobile/6.0/group__CAPI__SYSTEM__DEVICE__BATTERY__MODULE.html
2. https://developer.apple.com/documentation/uikit/uidevice?language=objc
3. https://developer.apple.com/documentation/iokit/iopowersources_h
4. https://developer.blackberry.com/native/reference/cascades/bb__device__batteryinfo.html
5. https://doc.qt.io/qt-5.15/qstring.html
6. https://doc.qt.io/qt-5.15/qbytearray.html
7. https://emscripten.org/docs/api_reference/html5.h.html#battery
8. https://docs.microsoft.com/en-us/uwp/api/windows.devices.power
9. https://docs.microsoft.com/en-us/uwp/api/windows.system.power
10. https://docs.microsoft.com/en-us/windows/win32/power/power-management-functions
11. https://switchbrew.github.io/libnx/psm_8h.html
12. https://github.com/pspdev/pspsdk/blob/master/src/power/psppower.h
13. https://docs.vitasdk.org/group__ScePowerKernel.html


================================= Support ice_libs ================================

ice_batt.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_BATT_H
#define ICE_BATT_H 1

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
#if defined(ICE_BATT_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_BATT_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_BATT_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_BATT_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_BATT_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_BATT_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_BATT_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_BATT_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_BATT_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_BATT_CDECL)
#  if defined(_MSC_VER)
#    define ICE_BATT_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_BATT_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_BATT_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_BATT_MICROSOFT) || defined(ICE_BATT_APPLE) || defined(ICE_BATT_WEB) || defined(ICE_BATT_TIZEN) || defined(ICE_BATT_BB10) || defined(ICE_BATT_UNIX))
#  define ICE_BATT_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
/* The implementations of UWP and BlackBerry 10 were written in C++ instead of C because their native APIs uses C++ :( */
#if defined(ICE_BATT_PLATFORM_AUTODETECTED)
#  if defined(__ANDROID__) || defined(ANDROID)
#    define ICE_BATT_ANDROID 1
#  elif defined(__TIZEN__)
#    define ICE_BATT_TIZEN 1
#  elif defined(__APPLE__) || defined(__DARWIN__) || defined(__MACH__)
#    include <TargetConditionals.h>
#    if defined(TARGET_OS_IOS) || defined(TARGET_OS_IPHONE) || defined(TARGET_OS_MACCATALYST) || defined(TARGET_IPHONE_SIMULATOR)
#      define ICE_BATT_IOS 1
#    elif defined(TARGET_OS_MAC)
#      define ICE_BATT_OSX 1
#    endif
#  elif defined(__BLACKBERRY10__) || defined(__BB10__)
#    define ICE_BATT_BB10 1
#    if !defined(__cplusplus)
#      error "BlackBerry 10 implementation for ice_batt.h cannot be used with C code, Only C++ :("
#    endif
#  elif defined(__EMSCRIPTEN__)
#    define ICE_BATT_WEB 1
#  elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    if (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP))
#      define ICE_BATT_UWP 1
#      if !defined(__cplusplus)
#        error "UWP implementation for ice_batt.h cannot be used with C code, Only C++ :("
#      endif
#    else
#      define ICE_BATT_MICROSOFT 1
#    endif
#  elif defined(__NX__)
#    define ICE_BATT_SWITCH 1
#  elif defined(__PSP__) || defined(_PSP)
#    define ICE_BATT_PSP 1
#  elif defined(_PSVITA) || defined(__VITA__) || defined(SN_TARGET_PSP2)
#    define ICE_BATT_PSVITA 1
#  elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
#    define ICE_BATT_BSD 1
#  elif defined(__unix__) || defined(__unix)
#    define ICE_BATT_UNIX 1
#  else
#    error "ice_batt.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_BATT_EXTERN) && defined(ICE_BATT_STATIC))
#  define ICE_BATT_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_BATT_EXTERN)
#  define ICE_BATT_APIDEF extern
#elif defined(ICE_BATT_STATIC)
#  define ICE_BATT_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_BATT_INLINE to enable inline functionality.
*/
#if defined(ICE_BATT_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_BATT_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_BATT_INLINEDEF inline
#  endif
#else
#  define ICE_BATT_INLINEDEF
#endif

/*
Allow to build DLL via ICE_BATT_DLLEXPORT or ICE_BATT_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_BATT_MICROSOFT)
#  if defined(ICE_BATT_DLLEXPORT)
#    define ICE_BATT_API __declspec(dllexport) ICE_BATT_INLINEDEF
#  elif defined(ICE_BATT_DLLIMPORT)
#    define ICE_BATT_API __declspec(dllimport) ICE_BATT_INLINEDEF
#  else
#    define ICE_BATT_API ICE_BATT_APIDEF ICE_BATT_INLINEDEF
#  endif
#else
#  define ICE_BATT_API ICE_BATT_APIDEF ICE_BATT_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_batt_bool {
    ICE_BATT_FALSE = -1,
    ICE_BATT_TRUE = 0
} ice_batt_bool;

/* Struct that contains battery status (Exists?, Charging?, Battery Level) */
typedef struct ice_batt_info {
    ice_batt_bool exists;
    ice_batt_bool charging;
    unsigned level;
} ice_batt_info;

/* Enumeration for errors that may occur */
typedef enum ice_batt_error {
    ICE_BATT_ERROR_OK = 0,          /* OK - no errors */
    ICE_BATT_ERROR_NO_BATTERY,      /* Occurs when device has no battery */
    ICE_BATT_ERROR_UNKNOWN_STATUS,  /* Occurs when failed to get battery status, Or if battery status is undefined */
    ICE_BATT_ERROR_SYSCALL_FAILURE  /* Occurs when failed to call platform-specific function */
} ice_batt_error;

/* ============================== Functions ============================== */

#if defined(ICE_BATT_ANDROID)
/* [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_batt on Android, This Should be called first before other ice_batt.h functions */
ICE_BATT_API void ICE_BATT_CALLCONV ice_batt_use_native_activity(const void* activity);
#endif

/* fetches battery information and stores result information in info, Returns ICE_BATT_TRUE on success or ICE_BATT_FALSE on failure */
ICE_BATT_API ice_batt_error ICE_BATT_CALLCONV ice_batt_get_status(ice_batt_info* info);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_BATT_IMPL)

/* Implementation of bool */
#if !defined(__STDC_VERSION__)
typedef enum bool { false, true } bool;
#else
#  if (!(defined(_STDBOOL_H) && defined(__cplusplus) && defined(bool)) && __STDC_VERSION__ >= 199901L)
#    include <stdbool.h>
#  endif
#endif

#if defined(ICE_BATT_ANDROID)
#  include <jni.h>
#  include <android/native_activity.h>
#elif defined(ICE_BATT_TIZEN)
#  include <device/battery.h>
#  include <device/callback.h>
#elif defined(ICE_BATT_IOS)
#  import <Foundation/Foundation.h>
#  import <UIKit/UIDevice.h>
#elif defined(ICE_BATT_OSX)
#  import <Foundation/Foundation.h>
#  include <CoreFoundation/CoreFoundation.h>
#  import <IOKit/ps/IOPowerSources.h>
#  import <IOKit/ps/IOPSKeys.h>
#elif defined(ICE_BATT_BB10)
#  include <bb/device/BatteryInfo>
#  include <bb/device/BatteryChargingState>
using namespace bb::device;
#elif defined(ICE_BATT_WEB)
#  include <emscripten/html5.h>
#elif defined(ICE_BATT_UWP)
using namespace Windows::Devices::Power;
using namespace Windows::System::Power;
#elif defined(ICE_BATT_MICROSOFT)
#  if defined(_MSC_VER)
#    include <windows.h>
#    pragma comment(lib, "kernel32.lib")
#  else
#    include <winbase.h>
#  endif
#elif defined(ICE_BATT_SWITCH)
#  include <switch/services/psm.h>
#elif defined(ICE_BATT_PSP)
#  include <psppower.h>
#elif defined(ICE_BATT_PSVITA)
#  include <psp2kern/power.h>
#elif defined(ICE_BATT_BSD)
#  include <unistd.h>
#  include <sys/types.h>
#  include <sys/sysctl.h>
#elif defined(ICE_BATT_UNIX)
#  include <unistd.h>
#  include <string.h>
#endif

/* Check if ARC enabled or not... */
#if defined(ICE_BATT_IOS) || defined(ICE_BATT_OSX)
#  if __has_feature(objc_arc)
#    define ICE_BATT_OBJC_ARC_ENABLED 1
#  else
#    define ICE_BATT_OBJC_ARC_DISABLED 1
#  endif
#endif

#if defined(ICE_BATT_ANDROID)

/* [ANDROID-ONLY, INTERNAL] Check if JNI object is NULL to stop if problem occurs */
#define ice_batt_android_null_check(o)          \
    if (o == 0) {                               \
        failed = ICE_BATT_TRUE;                 \
        error = ICE_BATT_ERROR_SYSCALL_FAILURE; \
        goto finish;                            \
    }

/* native activity that ice_batt will use on Android for Clipboard */
static ANativeActivity* ice_batt_native_activity;

/* [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_batt on Android, This Should be called first before other ice_batt.h functions */
ICE_BATT_API void ICE_BATT_CALLCONV ice_batt_use_native_activity(const void* activity) {
    ice_batt_native_activity = (ANativeActivity*) activity;
}
#endif

ICE_BATT_API ice_batt_error ICE_BATT_CALLCONV ice_batt_get_status(ice_batt_info* info) {
    ice_batt_error error = ICE_BATT_ERROR_OK;
#if defined(ICE_BATT_ANDROID)
    JNIEnv* env = ice_batt_native_activity->env;
    jclass activity_class = (jclass) ice_batt_native_activity->clazz;

    jmethodID mid, imid, bmid;
    jobject context, filter, intent;
    jstring name, action;
    jboolean res;
    int level, scale;
    unsigned batt_level = 0;
    ice_batt_bool batt_charging = ICE_BATT_FALSE;
    ice_batt_bool failed = ICE_BATT_FALSE;

    mid = env->GetStaticMethodID(env, activity_class, "getContext", "()Landroid/content/Context;");
    ice_batt_android_null_check(mid);

    context = env->CallStaticObjectMethod(env, activity_class, mid);
    ice_batt_android_null_check(context);
    
    action = env->NewStringUTF(env, "android.intent.action.BATTERY_CHANGED");
    ice_batt_android_null_check(action);
    
    cls = env->FindClass(env, "android/content/IntentFilter");
    ice_batt_android_null_check(cls);

    mid = env->GetMethodID(env, cls, "<init>", "(Ljava/lang/String;)V");
    ice_batt_android_null_check(mid);

    filter = env->NewObject(env, cls, mid, action);
    ice_batt_android_null_check(filter);
    
    mid = env->GetMethodID(env, activity_class, "registerReceiver", "(Landroid/content/BroadcastReceiver;Landroid/content/IntentFilter;)Landroid/content/Intent;");
    ice_batt_android_null_check(mid);

    intent = env->CallObjectMethod(env, context, mid, 0, filter);
    ice_batt_android_null_check(intent);

    cls = env->GetObjectClass(env, intent);
    ice_batt_android_null_check(cls);
    
    imid = env->GetMethodID(env, cls, "getIntExtra", "(Ljava/lang/String;I)I");
    ice_batt_android_null_check(imid);

    name = env->NewStringUTF(env, "level");
    ice_batt_android_null_check(name);
    
    level = envCallIntMethod(env, intent, imid, name, -1);

    name = env->NewStringUTF(env, "scale");
    ice_batt_android_null_check(name);

    scale = env->CallIntMethod(env, intent, imid, name, -1);

    if ((level == -1) || (scale == -1)) {
        failed = ICE_BATT_TRUE;
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        goto finish;
    }
    
    batt_level = (unsigned) (level * 100 / scale);
    
    bmid = env->GetMethodID(env, cls, "getBooleanExtra", "(Ljava/lang/String;Z)Z");
    ice_batt_android_null_check(bmid);

    name = env->NewStringUTF(env, "plugged");
    ice_batt_android_null_check(name);

    res = env->CallBooleanMethod(env, intent, bmid, name, -1);
    ice_batt_android_null_check(res);

    batt_charging = (res > 0) ? ICE_BATT_TRUE : ICE_BATT_FALSE;

    goto finish;

goto finish:
    if (context != 0) env->DeleteLocalRef(env, context);
    if (filter != 0) env->DeleteLocalRef(env, filter);
    if (intent != 0) env->DeleteLocalRef(env, intent);

    if (name != 0) env->DeleteLocalRef(env, name);
    if (action != 0) env->DeleteLocalRef(env, action);
    if (res != 0) env->DeleteLocalRef(env, res);

    if (failed == ICE_BATT_TRUE) goto failure;

    info->exists = ICE_BATT_TRUE;
    info->charging = batt_charging;
    info->level = batt_level;

#elif defined(ICE_BATT_TIZEN)
    int res;
    int batt_level = 0;
    bool batt_charging = false;
    
    res = device_battery_get_percent(&batt_level);
    if (res != 0) {
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        goto failure;
    }

    res = device_battery_is_charging(&batt_charging);
    if (res != 0) {
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        goto failure;
    }

    info->exists = ICE_BATT_TRUE;
    info->charging = (batt_charging == true) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    info->level = (unsigned) batt_level;
    
#elif defined(ICE_BATT_IOS)

#if defined(ICE_BATT_OBJC_ARC_ENABLED)
    @autoreleasepool {
#else
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
#endif
    int batt_level, batt_state;
    ice_batt_bool batt_charging, batt_exist;
    
    UIDevice *device = [UIDevice currentDevice];
    [device setBatteryMonitoringEnabled:YES];
    
    batt_level = (int) ([device batteryLevel] * 100.0f);
    batt_state = (int) [device batteryState];

    [device setBatteryMonitoringEnabled:NO];
        
    batt_charging = (batt_state == 2) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    batt_exist = (batt_state == 0) ? ICE_BATT_TRUE : ICE_BATT_FALSE;

#if defined(ICE_BATT_OBJC_ARC_DISABLED)
    [pool release];
#endif
    
    info->exists = batt_exist;
    info->charging = batt_charging;
    info->level = (unsigned) batt_level;
    
#if defined(ICE_BATT_OBJC_ARC_ENABLED)
    }
#endif

/* [@Rabios] TODO: Do some checks here... */
#elif defined(ICE_BATT_OSX)

#if defined(ICE_BATT_OBJC_ARC_ENABLED)
    @autoreleasepool {
#else
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
#endif
    CFTypeRef blob = IOPSCopyPowerSourcesInfo();
    CFArrayRef sources = IOPSCopyPowerSourcesList(blob);
    CFDictionaryRef psrc;
    void *psval;
    int cur_cap = 0, max_cap = 0, srcs = CFArrayGetCount(sources);
    unsigned batt_level;
    ice_batt_bool batt_charging;
    
    if (srcs > 0) {
        psrc = IOPSGetPowerSourceDescription(blob, CFArrayGetValueAtIndex(sources, 0));
        
        if (psrc == 0) {
            error = ICE_BATT_ERROR_UNKNOWN_STATUS;
            goto failure;
        }
    } else {
        error = ICE_BATT_ERROR_NO_BATTERY;
        goto failure;
    }
    
    psval = CFDictionaryGetValue(psrc, CFSTR(kIOPSCurrentCapacityKey));
    CFNumberGetValue((CFNumberRef) psval, kCFNumberSInt32Type, &cur_cap);
    
    psval = CFDictionaryGetValue(psrc, CFSTR(kIOPSMaxCapacityKey));
    CFNumberGetValue((CFNumberRef) psval, kCFNumberSInt32Type, &max_cap);
    
    batt_level = (unsigned)((float)(cur_cap / max_cap) * 100);
    
    psval = CFDictionaryGetValue(psrc, CFSTR(kIOPSIsChargingKey));
    batt_charging = (CFBooleanGetValue((CFBooleanRef) psval) == TRUE) ? ICE_BATT_TRUE : ICE_BATT_FALSE;

#if defined(ICE_BATT_OBJC_ARC_DISABLED)
    [pool release];
#endif

    info->exists = ICE_BATT_TRUE;
    info->charging = batt_charging;
    info->level = batt_level;

#if defined(ICE_BATT_OBJC_ARC_ENABLED)
    }
#endif

#elif defined(ICE_BATT_BB10)
    bb::device::BatteryInfo info;
    bb::device::BatteryChargingState::Type charge_state;
    ice_batt_bool batt_exist, charging;
    int batt_level;
    
    batt_exist = info.isPresent() ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    batt_level = info.level();
    
    if (batt_level == -1) {
        batt_level = 0;
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        
        delete info;
        goto failure;
    }
    
    charge_state = info.chargingState();
    charging = (charge_state == bb::device::BatteryChargingState::Charging || charge_state == bb::device::BatteryChargingState::Full) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    
    delete info;

    info->exists = batt_exist;
    info->charging = charging;
    info->level = (unsigned) batt_level;

#elif defined(ICE_BATT_WEB)
    EmscriptenBatteryEvent batt_state;
    
    if (emscripten_get_battery_status(&batt_state) != 0) {
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        goto failure;
    }

    info->exists = (batt_state.dischargingTime != 0) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    info->charging = (batt_state.charging == 1) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    info->level = (unsigned)(batt_state.level * 100);

#elif defined(ICE_BATT_UWP)
    Windows::Devices::Power::BatteryReport^ batt_state = Windows::Devices::Power::Battery::AggregateBattery->GetReport();
    
    ice_batt_bool batt_exists = (batt_state->Status != Windows::System::Power::BatteryStatus::NotPresent) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    ice_batt_bool batt_charging = (batt_state->Status != Windows::System::Power::BatteryStatus::Charging) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    unsigned batt_level = (unsigned)((float)(batt_state->RemainingCapacityInMilliwattHours->Value / batt_state->FullChargeCapacityInMilliwattHours->Value) * 100);
    
    delete batt_state;

    info.exists = batt_exists;
    info.charging = batt_charging;
    info.level = (batt_exists == ICE_BATT_TRUE) ? batt_level : 0;

#elif defined(ICE_BATT_MICROSOFT)
    SYSTEM_POWER_STATUS status;
    unsigned batt_level;
    
    if (GetSystemPowerStatus(&status) == 0) {
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        goto failure;
    }
    
    batt_level = (unsigned) status.BatteryLifePercent;
    
    if (batt_level == 255) batt_level = 0;

    info.exists = (!(status.BatteryFlag & (1 << 7)) && status.BatteryFlag != 255) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    info.charging = (status.BatteryFlag & (1 << 3)) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    info.level = batt_level;
    
#elif defined(ICE_BATT_SWITCH)
    Result res;
    u32 charge;
    ChargerType chtype;
    ice_batt_bool batt_exist;
    
    res = psmInitialize();
    if (R_FAILED(res)) {
        error = ICE_BATT_ERROR_SYSCALL_FAILURE;
        goto failure;
    }

    info->exists = ICE_BATT_TRUE;
    
    res = psmGetChargerType(&chtype);
    if (R_FAILED(res)) {
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        goto failure;
    }

    info->charging = (chtype > 0) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    
    res = psmGetBatteryChargePercentage(&charge);
    if (R_FAILED(res)) {
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        goto failure;
    }

    info->level = (unsigned) charge;
    
    psmExit();

#elif defined(ICE_BATT_PSP)
    info->exists = (scePowerIsBatteryExist() == SCE_TRUE) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    info->charging = (scePowerIsBatteryCharging() SCE_TRUE) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    info->level = (unsigned) scePowerGetBatteryLifePercent();

#elif defined(ICE_BATT_PSVITA)
    int batt_level = kscePowerGetBatteryLifePercent();
    SceBool batt_charging = kscePowerIsBatteryCharging();
    ice_batt_bool batt_exist = (batt_level >= 0 && batt_level <= 100) ? ICE_BATT_TRUE : ICE_BATT_FALSE;

    info->exists = batt_exist;
    info->charging = (batt_charging == SCE_TRUE) ?  ICE_BATT_TRUE : ICE_BATT_FALSE;
    info->level = (unsigned) batt_level;

#elif defined(ICE_BATT_BSD)
    int nofail = 0;
    int acpi_info[2];
    int fd;
    unsigned i;
    
    const char* acpi_dev[2] = {
        "hw.acpi.battery.life",
        "hw.acpi.battery.state"
    };
    
    fd = open("/dev/acpi", O_RDONLY);

    if (fd == -1) goto failure;

    for (i = 0; i < 2; i++) {
        int res = sysctlbyname(acpi_dev[i], &acpi_info[i], 0, 0);
        
        if (res == -1) {
            nofail = -1;
            break;
        }
    }
    
    if (nofail == -1) goto failure;

    info->exists = (!(acpi_info[1] & 0x0007)) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    info->charging = (acpi_info[1] & 0x0002) ? ICE_BATT_TRUE : ICE_BATT_FALSE;
    info->level = (unsigned) acpi_info[0];
    
#elif defined(ICE_BATT_UNIX)
    int handle, res, readlen;
    char buf[513];
    unsigned level;
    ice_batt_bool charging;
    
    handle = open("/sys/class/power_supply/BAT0/capacity", O_RDONLY);
    if (handle == -1) {
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        goto failure;
    }
    
    lseek(handle, 0, SEEK_SET);
    readlen = read(handle, buf, 512);
    buf[readlen < 0 ? 0 : readlen] = '\0';
    
    level = (unsigned) atoi(buf);

    res = close(handle);
    if (res == -1) goto failure;

    handle = open("/sys/class/power_supply/BAT0/status", O_RDONLY);
    if (handle == -1) {
        error = ICE_BATT_ERROR_UNKNOWN_STATUS;
        goto failure;
    }
    
    lseek(handle, 0, SEEK_SET);
    readlen = read(handle, buf, 512);
    buf[readlen < 0 ? 0 : readlen] = '\0';
    
    charging = strstr(buf, "Discharging") ? ICE_BATT_FALSE : ICE_BATT_TRUE;

    res = close(handle);
    if (res == -1) goto failure;

    info->exists = ICE_BATT_TRUE;
    info->charging = charging;
    info->level = level;
#endif

    return error;

failure:
    info->exists = ICE_BATT_FALSE;
    info->charging = ICE_BATT_FALSE;
    info->level = 0;
    
    return error;
}

#endif  /* ICE_BATT_IMPL */
#endif  /* ICE_BATT_H */

/*
ice_batt.h is dual-licensed, Choose the one you prefer!

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
