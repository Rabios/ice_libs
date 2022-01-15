/*
ice_clip.h, Single-Header Cross-Platform library to work with Clipboard!


================================== Full Overview ==================================

ice_clip.h is Single-Header Cross-Platform C library for working with Clipboard, It gives native access to the System Clipboard!

To use it #define ICE_CLIP_IMPL then #include "ice_clip.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

// Define the implementation of the library and include it
#define ICE_CLIP_IMPL 1
#include "ice_clip.h"

#include <stdio.h>

// Helper
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(int argc, char **argv) {
    // To store result of called functions
    ice_clip_bool res;
    
    // String to copy to clipboard later...
    const char *str = "SPEED!";

    // Retrieve the clipboard text
    const char *text = ice_clip_get();

    // If the function failed to retrieve Clipboard text, Trace error then terminate the program
    if (text == NULL) {
        trace("ice_clip_get", "ERROR: failed to retrieve Clipboard text!");
        return -1;
    }
    
    printf("Text from the Clipboard: %s\n", text);

    // Clear the Clipboard
    res = ice_clip_clear();

    // If the function failed to clear the Clipboard, Trace error then terminate the program
    if (res == ICE_CLIP_FALSE) {
        trace("ice_clip_clear", "ERROR: failed to clear the Clipboard!");
        return -1;
    }

    // Copy text to Clipboard
    res = ice_clip_set(str);

    // If the function failed to copy text to the Clipboard, Trace error then terminate the program
    if (res == ICE_CLIP_FALSE) {
        printf("ERROR: Failed to copy text to Clipboard!\n");
        return -1;
    }
    
    printf("Text copied to the Clipboard: %s\n", str);
    
    return 0;
}


=================================== Library API ===================================

// Boolean Enum, To avoid including stdbool.h
typedef enum ice_clip_bool {
    ICE_CLIP_FALSE = -1,
    ICE_CLIP_TRUE  = 0
} ice_clip_bool;

// [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_clip on Android, This Should be called first before other ice_clip.h functions
void ice_clip_use_native_activity(void *activity);

// [WINDOWS-ONLY, OPTIONAL] Sets the Window to be used with ice_clip, This is optional feature as the Windows implementation do not need Window by default
void ice_clip_use_window(void *window);

// Retrieves the text from Clipboard
const char* ice_clip_get(void);

// Sets the Clipboard text, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure
ice_clip_bool ice_clip_set(const char *text);

// Clears the Clipboard, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure
ice_clip_bool ice_clip_clear(void);


================================== Linking Flags ==================================

1. Microsoft Windows (Non-UWP)  =>  -lkernel32 -luser32
2. iOS                          =>  -framework Foundation -framework UIKit
3. MacOS/OSX                    =>  -framework Foundation -framework AppKit
4. BlackBerry 10                =>  -lbbsystem

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragma preprocessor


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_clip.h in the code...
#define ICE_CLIP_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_CLIP_VECTORCALL     // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_CLIP_FASTCALL       // fastcall
#define ICE_CLIP_STDCALL        // stdcall
#define ICE_CLIP_CDECL          // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_CLIP_ANDROID        // Android
#define ICE_CLIP_IOS            // iOS
#define ICE_CLIP_OSX            // MacOS/OSX
#define ICE_CLIP_BB10           // BlackBerry 10
#define ICE_CLIP_UWP            // UWP (Univeral Windows Platform)
#define ICE_CLIP_MICROSOFT      // Microsoft Platforms
#define ICE_CLIP_BEOS           // BeOS and Haiku

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_CLIP_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_CLIP_DLLEXPORT      // Export the symbols to build as shared library
#define ICE_CLIP_DLLIMPORT      // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_CLIP_INLINE         // inlines library functions (Only works on C99 Standard and above)
#define ICE_CLIP_EXTERN         // externs library functions
#define ICE_CLIP_STATIC         // statics library functions

// NOTE: You cannot #define both ICE_CLIP_EXTERN and ICE_CLIP_STATIC together in the code...


============================== Implementation Resources ===========================

1. https://developer.android.com/reference/android/text/ClipboardManager
2. https://developer.apple.com/documentation/uikit/uipasteboard?language=objc
3. https://developer.apple.com/documentation/appkit/nspasteboard?language=objc
4. https://developer.blackberry.com/native/reference/cascades/bb__system__clipboard.html
5. https://docs.microsoft.com/en-us/windows/win32/dataxchg/clipboard
6. https://docs.microsoft.com/en-us/uwp/api/Windows.ApplicationModel.DataTransfer.Clipboard
7. https://www.haiku-os.org/docs/api/classBClipboard.html


================================= Support ice_libs ================================

ice_clip.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
7. Share ice_libs everywhere!


*/

#if !defined(ICE_CLIP_H)
#define ICE_CLIP_H 1

/* Allow to use calling conventions if desired... */
#if defined(ICE_CLIP_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_CLIP_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_CLIP_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_CLIP_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_CLIP_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_CLIP_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_CLIP_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_CLIP_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_CLIP_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_CLIP_CDECL)
#  if defined(_MSC_VER)
#    define ICE_CLIP_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_CLIP_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_CLIP_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_CLIP_MICROSOFT) || defined(ICE_CLIP_UWP) || defined(ICE_CLIP_BEOS) || defined(ICE_CLIP_IOS) || defined(ICE_CLIP_OSX) || defined(ICE_CLIP_BB10) || defined(ICE_CLIP_ANDROID))
#  define ICE_CLIP_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
/* The implementations of UWP and BeOS/Haiku and BlackBerry 10 were written in C++ instead of C because their native APIs uses C++ :( */
#if defined(ICE_CLIP_PLATFORM_AUTODETECTED)
#  if defined(__ANDROID__) || defined(ANDROID)
#    define ICE_CLIP_ANDROID 1
#  elif defined(__APPLE__) || defined(__DARWIN__) || defined(__MACH__)
#    include <TargetConditionals.h>
#    if defined(TARGET_OS_IOS) || defined(TARGET_OS_IPHONE) || defined(TARGET_OS_MACCATALYST) || defined(TARGET_IPHONE_SIMULATOR)
#      define ICE_CLIP_IOS 1
#    elif defined(TARGET_OS_MAC)
#      define ICE_CLIP_OSX 1
#    endif
#  elif defined(__BLACKBERRY10__) || defined(__BB10__)
#    define ICE_CLIP_BB10 1
#    if !defined(__cplusplus)
#      error "BlackBerry 10 implementation for ice_clip.h cannot be used with C code, Only C++ :("
#    endif
#  elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    if (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP))
#      define ICE_CLIP_UWP 1
#      if !defined(__cplusplus)
#        error "UWP implementation for ice_clip.h cannot be used with C code, Only C++ :("
#      endif
#    else
#      define ICE_CLIP_MICROSOFT 1
#    endif
#  elif defined(__HAIKU__) || defined(__BEOS__)
#    define ICE_CLIP_BEOS 1
#    if !defined(__cplusplus)
#      error "BeOS/Haiku implementation for ice_clip.h cannot be used with C code, Only C++ :("
#    endif
#  else
#    error "ice_clip.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_CLIP_EXTERN) && defined(ICE_CLIP_STATIC))
#  define ICE_CLIP_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_CLIP_EXTERN)
#  define ICE_CLIP_APIDEF extern
#elif defined(ICE_CLIP_STATIC)
#  define ICE_CLIP_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_CLIP_INLINE to enable inline functionality.
*/
#if defined(ICE_CLIP_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_CLIP_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_CLIP_INLINEDEF inline
#  endif
#else
#  define ICE_CLIP_INLINEDEF
#endif

/*
Allow to build DLL via ICE_TIME_DLLEXPORT or ICE_TIME_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_CLIP_MICROSOFT)
#  if defined(ICE_CLIP_DLLEXPORT)
#    define ICE_CLIP_API __declspec(dllexport) ICE_CLIP_INLINEDEF
#  elif defined(ICE_CLIP_DLLIMPORT)
#    define ICE_CLIP_API __declspec(dllimport) ICE_CLIP_INLINEDEF
#  else
#    define ICE_CLIP_API ICE_CLIP_APIDEF ICE_CLIP_INLINEDEF
#  endif
#else
#  define ICE_CLIP_API ICE_CLIP_APIDEF ICE_CLIP_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_clip_bool {
    ICE_CLIP_FALSE = -1,
    ICE_CLIP_TRUE  = 0
} ice_clip_bool;

/* ============================== Functions ============================== */

#if defined(ICE_CLIP_ANDROID)
/* [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_clip on Android, This Should be called first before other ice_clip.h functions */
ICE_CLIP_API void ICE_CLIP_CALLCONV ice_clip_use_native_activity(void *activity);
#endif

#if defined(ICE_CLIP_MICROSOFT)
/* [WINDOWS-ONLY, OPTIONAL] Sets the Window to be used with ice_clip, This is optional feature as the Windows implementation do not need Window by default */
ICE_CLIP_API void ICE_CLIP_CALLCONV ice_clip_use_window(void *window);
#endif

/* Retrieves the text from Clipboard, Returns the text on success or NULL on failure */
ICE_CLIP_API const char* ICE_CLIP_CALLCONV ice_clip_get(void);

/* Sets the Clipboard text, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ICE_CLIP_API ice_clip_bool ICE_CLIP_CALLCONV ice_clip_set(const char *text);

/* Clears the Clipboard, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ICE_CLIP_API ice_clip_bool ICE_CLIP_CALLCONV ice_clip_clear(void);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_CLIP_IMPL)

#if !defined(__STDC_VERSION__)
typedef enum bool { false, true } bool;
#else
#  if (!defined(_STDBOOL_H) && !defined(__cplusplus) && !defined(bool)) && (defined(__STDC__) && __STDC_VERSION__ >= 199901L)
#    include <stdbool.h>
#  endif
#endif

#if defined(ICE_CLIP_ANDROID)
#  include <jni.h>
#  include <android/native_activity.h>
#  include <string.h>
#elif defined(ICE_CLIP_IOS)
#  import <Foundation/Foundation.h>
#  import <UIKit/UIPasteboard.h>
#elif defined(ICE_CLIP_OSX)
#  import <Foundation/Foundation.h>
#  import <AppKit/NSPasteboard.h>
#elif defined(ICE_CLIP_BB10)
#  include <QtCore/QString>
#  include <QtCore/QByteArray>
#  include <bb/system/Clipboard>
using namespace bb::system;
#elif defined(ICE_CLIP_BEOS)
#  include <be/app/Clipboard.h>
#  include <string.h>
#elif defined(ICE_CLIP_MICROSOFT)
#  include <string.h>
#  if defined(_MSC_VER)
#    include <windows.h>
#    pragma comment(lib, "kernel32.lib")
#    pragma comment(lib, "user32.lib")
#  else
#    include <windef.h>
#    include <winbase.h>
#    include <winuser.h>
#  endif
#elif defined(ICE_CLIP_UWP)
#  include <cstring>
#  include <wchar.h>
#  include <iostream>
#  include <string>
using namespace Platform;
using namespace Windows::ApplicationModel::DataTransfer;
#endif

/* Check if ARC enabled or not... */
#if defined(ICE_CLIP_IOS) || defined(ICE_CLIP_OSX)
#  if __has_feature(objc_arc)
#    define ICE_CLIP_OBJC_ARC_ENABLED 1
#  endif
#endif

#if defined(ICE_CLIP_ANDROID)
/* native activity that ice_clip will use on Android for Clipboard */
static ANativeActivity *ice_clip_native_activity;

/* [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_clip on Android, This Should be called first before other ice_clip.h functions */
ICE_CLIP_API void ICE_CLIP_CALLCONV ice_clip_use_native_activity(void *activity) {
    ice_clip_native_activity = (ANativeActivity*) activity;
}
#endif

#if defined(ICE_CLIP_MICROSOFT)
/* Window that ice_clip can use on Windows (Optional because ice_clip does not require Window on Windows) */
static void *ice_clip_hwnd = 0;

/* [WINDOWS-ONLY, OPTIONAL] Sets the Window to be used with ice_clip, This is optional feature as the Windows implementation do not need Window by default */
ICE_CLIP_API void ICE_CLIP_CALLCONV ice_clip_use_window(void *window) {
    ice_clip_hwnd = window;
}
#endif

/* Retrieves the text from Clipboard, Returns the text on success or NULL on failure */
ICE_CLIP_API const char* ICE_CLIP_CALLCONV ice_clip_get(void) {
#if defined(ICE_CLIP_ANDROID)
    JNIEnv *env = ice_clip_native_activity->env;
    jclass activity_class = (jclass) ice_clip_native_activity->clazz;
    jstring service = env->NewStringUTF(env, "clipboard");
    jmethodID mid;
    jobject context;
    jobject manager;
    jobject clipboard;
    jobject sequence;
    jclass clipboard_class;
    jstring string;
    
    mid = env->GetStaticMethodID(env, activity_class, "getContext", "()Landroid/content/Context;");
    if (mid == 0) goto failure;
    
    context = env->CallStaticObjectMethod(env, activity_class, mid);
    if (context == 0) goto failure;

    mid = env->GetMethodID(env, activity_class, "getSystemServiceFromUiThread", "(Ljava/lang/String;)Ljava/lang/Object;");
    if (mid == 0) goto failure;
    
    manager = env->CallObjectMethod(env, context, mid, service);
    if (manager == 0) goto failure;

    env->DeleteLocalRef(env, service);

    clipboard = manager ? env->NewGlobalRef(env, manager) : 0;
    if (!clipboard) goto failure;

    clipboard_class = env->GetObjectClass(env, clipboard);
    if (clipboard_class == 0) goto failure;
    
    mid = env->GetMethodID(env, clipboard_class, "getText", "()Ljava/lang/CharSequence;");
    if (mid == 0) goto failure;

    sequence = env->CallObjectMethod(env, clipboard, mid);
    if (sequence == 0) goto failure;
    
    env->DeleteGlobalRef(env, clipboard);
    env->DeleteLocalRef(env, manager);
    env->DeleteLocalRef(env, context);
    
    if (sequence) {
        char *utf;

        mid = env->GetMethodID(env, env->GetObjectClass(env, sequence), "toString", "()Ljava/lang/String;");
        if (mid == 0) goto failure;

        string = (jstring)(env->CallObjectMethod(env, sequence, mid));
        if (string == 0) goto failure;
        
        utf = env->GetStringUTFChars(env, string, 0);
        if (utf == 0) goto failure;
        
        if (utf) {
            const char *text = strdup(utf);
            
            env->ReleaseStringUTFChars(env, string, utf);
            env->DeleteLocalRef(env, sequence);
            
            return text;
        }
        
        env->DeleteLocalRef(env, sequence);
        
        return 0;
    }
    
    return 0;

failure:
    if (service != 0) env->DeleteLocalRef(env, service);
    if (context != 0) env->DeleteLocalRef(env, context);
    if (manager != 0) env->DeleteLocalRef(env, manager);
    if (clipboard != 0) env->DeleteGlobalRef(env, clipboard);
    if (clipboard_class != 0) env->DeleteLocalRef(env, clipboard_class);
    if (string != 0) env->DeleteLocalRef(env, string);

    return 0;

#elif defined(ICE_CLIP_IOS)

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    @autoreleasepool {
#else
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
#endif

    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    if (pasteboard == 0) return 0;

    NSString *str = pasteboard.string;

    int has_text = ([pasteboard hasStrings] == NO || str == 0) ? -1 : 0;
    if (has_text == -1) return 0;
        
    const char *res = [str UTF8String];

#if !defined(ICE_CLIP_OBJC_ARC_ENABLED)
    [pool release];
#endif

    return res;
        
#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    }
#endif

#elif defined(ICE_CLIP_OSX)

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    @autoreleasepool {
#else
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
#endif

    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    if (pasteboard == 0) return 0;

    NSString *str = [pasteboard stringForType:NSPasteboardTypeString];
    if (str == 0) return 0;
    
    const char *res = [str UTF8String];
    
#if !defined(ICE_CLIP_OBJC_ARC_ENABLED)
    [pool release];
#endif

    return res;

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    }
#endif

#elif defined(ICE_CLIP_BB10)
    bool data_not_empty;
    bb::system::Clipboard clipboard;
    QByteArray data = clipboard.value("text/plain");
    
    data_not_empty = !data.isEmpty();
    
    if (data_not_empty == true) {
        const char *res = return data.constData();
        
        delete clipboard;
        delete data;
        
        return res;
    }
    
    delete data;
    delete clipboard;
    
    return 0;

#elif defined(ICE_CLIP_BEOS)
    bool r1;
    int r2;
    int lenstr;
    const char *str;
    BMessage *clip;

    r1 = be_clipboard->Lock();
    if (r1 == false) return 0;

    clip = be_clipboard->Data();
    if (clip == 0) goto failure;
    
    r2 = clip->FindData("text/plain", B_MIME_TYPE, (const void**) &str, &lenstr);
    if (r2 != 0) goto failure;

    be_clipboard->Unlock();
    return str;

failure:
    be_clipboard->Unlock();
    return 0;

#elif defined(ICE_CLIP_MICROSOFT)
    char *res;
    int fetch_res, close_res;

    fetch_res = OpenClipboard(ice_clip_hwnd);
    if (fetch_res == 0) return 0;
    
    res = (char*) GetClipboardData(CF_TEXT);

    goto deinit;
    
deinit:
    close_res = CloseClipboard();
    
    if (close_res == 0) return 0;

    return res;

#elif defined(ICE_CLIP_UWP)
    Windows::ApplicationModel::DataTransfer::DataPackageView ^datapackview = Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();
    bool pass = datapackview->Contains(Windows::ApplicationModel::DataTransfer::StandardDataFormats::Text);
    
    if (pass == true) {
        Platform::String ^text_data = datapackview->GetTextAsync()->ToString();
        
        std::wstring txt1(text_data->Begin());
        delete text_data;
        
        std::string txt2(txt1.begin(), txt1.end());
        delete txt1;
        delete datapackview;

        const char *res = txt2.c_str();
        delete txt2;
        
        return res;
    }
    
    delete datapackview;

    return 0;

#endif
}

/* Sets the Clipboard text, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ICE_CLIP_API ice_clip_bool ICE_CLIP_CALLCONV ice_clip_set(const char *text) {
#if defined(ICE_CLIP_ANDROID)
    JNIEnv *env = ice_clip_native_activity->env;
    
    jclass activity_class = (jclass) ice_clip_native_activity->clazz;
    jclass clipboard_class;
    
    jstring service = env->NewStringUTF(env, "clipboard");
    jstring string;
    jmethodID mid;

    jobject context;
    jobject manager;
    jobject clipboard;

    if (service == 0) goto failure;

    mid = env->GetStaticMethodID(env, activity_class, "getContext", "()Landroid/content/Context;");
    if (mid == 0) goto failure;

    context = env->CallStaticObjectMethod(env, activity_class, mid);
    if (context == 0) goto failure;

    mid = env->GetMethodID(env, activity_class, "getSystemServiceFromUiThread", "(Ljava/lang/String;)Ljava/lang/Object;");
    if (mid == 0) goto failure;

    manager = env->CallObjectMethod(env, context, mid, service);
    if (manager == 0) goto failure;

    clipboard = (manager != 0) ? env->NewGlobalRef(env, manager) : 0;
    if (clipboard == 0) goto failure;

    clipboard_class = env->GetObjectClass(env, clipboard);
    if (clipboard_class == 0) goto failure;
    
    mid = env->GetMethodID(env, clipboard_class, "setText", "(Ljava/lang/CharSequence;)V");
    if (mid == 0) goto failure;
    
    string = env->NewStringUTF(env, text);
    if (text == 0) goto failure;

    env->CallVoidMethod(env, clipboard, mid, string);

    env->DeleteLocalRef(env, string);
    env->DeleteLocalRef(env, clipboard_class);
    env->DeleteGlobalRef(env, clipboard);
    env->DeleteLocalRef(env, manager);
    env->DeleteLocalRef(env, context);
    env->DeleteLocalRef(env, service);
    
    return ICE_CLIP_TRUE;

goto failure:
    if (service != 0) env->DeleteLocalRef(env, service);
    if (context != 0) env->DeleteLocalRef(env, context);
    if (manager != 0) env->DeleteLocalRef(env, manager);
    if (clipboard != 0) env->DeleteGlobalRef(env, clipboard);
    if (clipboard_class != 0) env->DeleteLocalRef(env, clipboard_class);
    if (string != 0) env->DeleteLocalRef(env, string);

    return ICE_CLIP_FALSE;

#elif defined(ICE_CLIP_IOS)

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    @autoreleasepool {
#else
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
#endif

    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    if (pasteboard == 0) return 0;

    NSString *txt = [NSString stringWithFormat:@"%s", text];
    pasteboard.string = txt;

#if !defined(ICE_CLIP_OBJC_ARC_ENABLED)
    [pool release];
#endif
        
    return ICE_CLIP_TRUE;

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    }
#endif

#elif defined(ICE_CLIP_OSX)

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    @autoreleasepool {
#else
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
#endif

    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    if (pasteboard == 0) return ICE_CLIP_FALSE;

    NSString *txt = [NSString stringWithFormat:@"%s", text];
    
    [pasteboard clearContents];
    
    BOOL res = [pasteboard setString:txt forType:NSStringPboardType];
    if (res == NO) return ICE_CLIP_FALSE;
        
#if !defined(ICE_CLIP_OBJC_ARC_ENABLED)
    [pool release];
#endif
    
    return ICE_CLIP_TRUE;

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    }
#endif

#elif defined(ICE_CLIP_BB10)
    bool res;
    bb::system::Clipboard clipboard;
    QString txt = QString::fromUtf8(text);
    
    res = clipboard.clear();
    if (res == false) goto failure;

    res = clipboard.insert("text/plain", txt);
    if (res == false) goto failure;
    
    delete txt;
    delete clipboard;

    return ICE_CLIP_TRUE;

failure:
    delete txt;
    delete clipboard;
    return ICE_CLIP_FALSE;

#elif defined(ICE_CLIP_BEOS)
    bool r1;
    int r2;
    BMessage *clip;

    r1 = be_clipboard->Lock();
    if (r1 == false) return ICE_CLIP_FALSE;

    r2 = be_clipboard->Clear();
    if (r2 != 0) goto failure;
    
    clip = be_clipboard->Data();
    r2 = clip->AddData("text/plain", B_MIME_TYPE, text, strlen(text));
    if (r2 != 0) goto failure;

    r2 = be_clipboard->Commit();
    if (r2 != 0) goto failure;
    
    be_clipboard->Unlock();
    return ICE_CLIP_TRUE;

failure:
    be_clipboard->Unlock();
    return ICE_CLIP_FALSE;

#elif defined(ICE_CLIP_MICROSOFT)
    void *clipbuffer, *clipset;
    char *buffer;
    int res;
    unsigned alloc_size = strlen(text) + 1;

    res = OpenClipboard(ice_clip_hwnd);
    if (res == 0) return ICE_CLIP_FALSE;

    clipbuffer = GlobalAlloc(GMEM_DDESHARE, alloc_size);
    if (clipbuffer == 0) goto failure;

    buffer = (char*) GlobalLock(clipbuffer);
    if (buffer == 0) goto failure;

    strcpy(buffer, text);

    res = GlobalUnlock(clipbuffer);
    if (res == 0) goto failure;
    
    clipset = SetClipboardData(CF_TEXT, clipbuffer);
    if (clipset == 0) goto failure;

    res = CloseClipboard();
    if (res == 0) return ICE_CLIP_FALSE;

    return ICE_CLIP_TRUE;

failure:
    if (clipbuffer != 0) GlobalFree(clipbuffer);
    res = CloseClipboard();
    
    return ICE_CLIP_FALSE;
    
#elif defined(ICE_CLIP_UWP)
    Windows::ApplicationModel::DataTransfer::DataPackage ^datapack = ref new Windows::ApplicationModel::DataTransfer::DataPackage();
    Platform::String ^str;
    const size_t sz = strlen(text) + 1;
    wchar_t *wc = new wchar_t[sz];

    mbstowcs(wc, text, sz);
    
    str = ref new Platform::String(wc);
    datapack->SetText(str);
    Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(datapack);
    Windows::ApplicationModel::DataTransfer::Clipboard::Flush();
    
    delete datapack;
    delete wc;
    delete str;
    
    return ICE_CLIP_TRUE;
#endif
}

/* Clears the Clipboard, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ICE_CLIP_API ice_clip_bool ICE_CLIP_CALLCONV ice_clip_clear(void) {
#if defined(ICE_CLIP_ANDROID)
    return ice_clip_set("");
#elif defined(ICE_CLIP_IOS)

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    @autoreleasepool {
#else
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
#endif

    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    if (pasteboard == 0) return ICE_CLIP_FALSE;

    pasteboard.string = @"";
    
#if !defined(ICE_CLIP_OBJC_ARC_ENABLED)
    [pool release];
#endif

    return ICE_CLIP_TRUE;

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    }
#endif

#elif defined(ICE_CLIP_OSX)

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    @autoreleasepool {
#else
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
#endif

    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    if (pasteboard == 0) return ICE_CLIP_FALSE;

    [pasteboard clearContents];

#if !defined(ICE_CLIP_OBJC_ARC_ENABLED)
    [pool release];
#endif

    return ICE_CLIP_TRUE;

#if defined(ICE_CLIP_OBJC_ARC_ENABLED)
    }
#endif

#elif defined(ICE_CLIP_BB10)
    bool res;
    bb::system::Clipboard clipboard;
    
    res = clipboard.clear();

    delete clipboard;

    return (res == true) ? ICE_CLIP_TRUE : ICE_CLIP_FALSE;

#elif defined(ICE_CLIP_BEOS)
    bool r1;
    int r2;

    r1 = be_clipboard->Lock();
    if (r1 == false) return ICE_CLIP_FALSE;
    
    r2 = be_clipboard->Clear();
    
    be_clipboard->Unlock();

    return (r2 != 0) ? ICE_CLIP_FALSE : ICE_CLIP_TRUE;
    
#elif defined(ICE_CLIP_MICROSOFT)
    int res;

    res = OpenClipboard(ice_clip_hwnd);
    if (res == 0) return ICE_CLIP_FALSE;

    res = EmptyClipboard();
    if (res == 0) goto failure;

    res = CloseClipboard();
    if (res == 0) return ICE_CLIP_FALSE;

    return ICE_CLIP_TRUE;

failure:
    res = CloseClipboard();
    return ICE_CLIP_FALSE;

#elif defined(ICE_CLIP_UWP)
    Windows::ApplicationModel::DataTransfer::Clipboard::Clear();

    return ICE_CLIP_TRUE;
#endif
}

#endif  /* ICE_CLIP_IMPL */
#endif  /* ICE_CLIP_H */

/*
ice_clip.h is dual-licensed, Choose the one you prefer!

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
