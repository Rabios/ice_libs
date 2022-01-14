/*
ice_clip.h, Single-Header Cross-Platform library to work with Clipboard!

================================== Full Overview ==================================



================================== Usage Example ==================================



=================================== Library API ===================================



=============================== Linking Requirements ==============================

1. Microsoft Windows => Link kernel32 and user32 with -lkernel32 -luser32


================================= Usable #define(s) ===============================

// Define the implementation, This should be #define(d) before including ice_clip.h in the code...
#define ICE_CLIP_IMPL

// #### Calling Convention (Only define one of them) #### //

// Set functions call convention to vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_CLIP_VECTORCALL

// Set function call convention to fastcall
#define ICE_CLIP_FASTCALL

// Set function call convention to stdcall
#define ICE_CLIP_STDCALL

// Set function call convention to cdecl
#define ICE_CLIP_CDECL

// #### Platform Definitions (Only define one of first <n> definitions) #### //

//
ICE_CLIP_ANDROID

//
ICE_CLIP_IOS

//
ICE_CLIP_OSX

//
ICE_CLIP_UWP

//
ICE_CLIP_MICROSOFT

//
ICE_CLIP_BEOS

//
ICE_CLIP_TIZEN

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_CLIP_PLATFORM_AUTODETECTED

// #### Import/Export from shared libs... (Only define one of them) #### //

// Export the symbols to build as shared library (Windows Only)
#define ICE_CLIP_DLLEXPORT

// Use this definition to use the symbols from built shared library (Windows Only)
#define ICE_CLIP_DLLIMPORT

// #### Use these to make functions inline/extern/static #### //

// inlines library functions (Only works on C99 Standard and above)
#define ICE_CLIP_INLINE

// externs library functions
#define ICE_CLIP_EXTERN

// statics library functions                
#define ICE_CLIP_STATIC

// NOTE: ICE_CLIP_EXTERN and ICE_CLIP_STATIC cannot be #define(d) together in the code...


================================= Support ice_libs ================================

ice_clip.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
*/

#ifndef ICE_CLIP_H
#define ICE_CLIP_H

/* Disable security warnings for MSVC compiler, We don't want to force using C11! */
#ifdef _MSC_VER
#  define _CRT_SECURE_NO_DEPRECATE
#  define _CRT_SECURE_NO_WARNINGS
#  pragma warning(disable:4996)
#endif

/* Define C interface for Windows libraries! ;) */
#ifndef CINTERFACE
#  define CINTERFACE
#endif

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
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_CLIP_MICROSOFT) || defined(ICE_CLIP_BEOS) || defined(ICE_CLIP_IOS) || defined(ICE_CLIP_OSX) || defined(ICE_CLIP_ANDROID) || defined(ICE_CLIP_UWP))
#  define ICE_CLIP_PLATFORM_AUTODETECTED
#endif

/* Platform detection */
#if defined(ICE_CLIP_PLATFORM_AUTODETECTED)
#  if defined(__ANDROID__) || defined(__android__) || defined(__ANDROID) || defined(__android) || defined(_ANDROID) || defined(_android)
#    define ICE_CLIP_ANDROID
#  elif defined(__TIZEN__)
#    define ICE_CLIP_TIZEN
#  elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__DARWIN) || defined(_DARWIN)
#    include <TargetConditionals.h>
#    if defined(TARGET_OS_IOS) || defined(TARGET_OS_IPHONE)
#      define ICE_CLIP_IOS
#    elif defined(TARGET_OS_MAC)
#      define ICE_CLIP_OSX
#    endif
#  elif defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(__WIN32__) || defined(__WIN64__) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#    if (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP))
#      define ICE_CLIP_UWP
#    else
#      define ICE_CLIP_MICROSOFT
#    endif
#  elif defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU) || defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
#    define ICE_CLIP_BEOS
#  else
#    error "ice_clip.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_CLIP_EXTERN) && defined(ICE_CLIP_STATIC))
#  define ICE_CLIP_EXTERN
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

/* The implementation of UWP and BeOS/Haiku written in C++ instead of C :( */
#if (defined(ICE_CLIP_UWP) || defined(ICE_CLIP_BEOS))
#  if !defined(__cplusplus)
#    error "Implementation of UWP and BeOS/Haiku cannot be used with C code, Only C++ :("
#  endif
#endif

/* Custom memory allocators */
#ifndef ICE_CLIP_MALLOC
#  define ICE_CLIP_MALLOC(sz) malloc(sz)
#endif
#ifndef ICE_CLIP_CALLOC
#  define ICE_CLIP_CALLOC(n, sz) calloc(n, sz)
#endif
#ifndef ICE_CLIP_REALLOC
#  define ICE_CLIP_REALLOC(ptr, sz) realloc(ptr, sz)
#endif
#ifndef ICE_CLIP_FREE
#  define ICE_CLIP_FREE(ptr) free(ptr)
#endif

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum {
    ICE_CLIP_FALSE = -1,
    ICE_CLIP_TRUE  = 0
} ice_clip_bool;

#if defined(ICE_CLIP_ANDROID)
/* Sets native activity to be used by ice_clip on Android, This Should be called first before other ice_clip.h functions */
ICE_CLIP_API void ICE_CLIP_CALLCONV ice_clip_use_native_activity(ANativeActivity* activity);
#endif

/* Retrieves the text from Clipboard */
ICE_CLIP_API const char* ICE_CLIP_CALLCONV ice_clip_get(void);

/* Sets the Clipboard text, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ICE_CLIP_API ice_clip_bool ICE_CLIP_CALLCONV ice_clip_set(const char* text);

/* Clears the Clipboard, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ICE_CLIP_API ice_clip_bool ICE_CLIP_CALLCONV ice_clip_clear(void);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_CLIP_IMPL)

#if defined(ICE_CLIP_ANDROID)
#  include <string.h>
#  include <jni.h>
#  include <sys/types.h>
#  include <unistd.h>
#  include <android/native_activity.h>

static ANativeActivity* ice_clip_native_activity;

#elif defined(ICE_CLIP_IOS)
#  include <string.h>
#  import <Foundation/Foundation.h>
#  import <UIKit/UIPasteboard.h>
#elif defined(ICE_CLIP_OSX)
#  include <string.h>
#  import <Foundation/Foundation.h>
#  import <AppKit/NSPasteboard.h>
#elif defined(ICE_CLIP_TIZEN)
#  include <cbhm.h>
#  include <string.h>
#  include <stdlib.h>
#elif defined(ICE_CLIP_BEOS)
#  include <string.h>
#  include <be/app/Clipboard.h>
#elif defined(ICE_CLIP_MICROSOFT)
#  include <string.h>
#  include <winbase.h>
#  include <winuser.h>
#  if defined(_MSC_VER)
#    pragma comment(lib, "kernel32.lib")
#    pragma comment(lib, "user32.lib")
#  endif
#elif defined(ICE_CLIP_UWP)
#  include <stdlib.h>
#  include <string.h>
#  include <wchar.h>
using namespace Windows::ApplicationModel::DataTransfer;
#endif

#if defined(ICE_CLIP_TIZEN)
// FIXME: There is something really wrong that makes app crash...
const char *res;

static int ice_clipboard_data_cb(cbhm_h cbhm_handle, const char *buf, size_t len, void *user_data) {
	res = strdup(buf);
}
#endif

#if defined(ICE_CLIP_ANDROID)
/* Sets native activity to be used by ice_clip on Android, This Should be called first before other ice_clip.h functions */
ICE_CLIP_API void ICE_CLIP_CALLCONV ice_clip_use_native_activity(ANativeActivity* activity) {
    ice_clip_native_activity = activity;
}
#endif

/* Retrieves the text from Clipboard */
ICE_CLIP_API const char* ICE_CLIP_CALLCONV ice_clip_get(void) {
#if defined(ICE_CLIP_ANDROID)
    JNIEnv* env = ice_clip_native_activity->env;
    jclass activity_class = (jclass) ice_clip_native_activity->clazz;
    jstring service = env->NewStringUTF(env, "clipboard");
    jmethodID mid;
    
    mid = env->GetStaticMethodID(env, activity_class, "getContext", "()Landroid/content/Context;");
    jobject context = env->CallStaticObjectMethod(env, activity_class, mid);

    mid = env->GetMethodID(env, activity_class, "getSystemServiceFromUiThread", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject manager = env->CallObjectMethod(env, context, mid, service);

    env->DeleteLocalRef(env, service);

    jobject clipboard = manager ? env->NewGlobalRef(env, manager) : NULL;
    
    if (!clipboard) {
        return NULL;
    }
    
    jmethodID mid = env->GetMethodID(env, env->GetObjectClass(env, clipboard), "getText", "()Ljava/lang/CharSequence;");
    jobject sequence = env->CallObjectMethod(env, clipboard, mid);
    env->DeleteGlobalRef(env, clipboard);
    
    if (sequence) {
        mid = env->GetMethodID(env, env->GetObjectClass(env, sequence), "toString", "()Ljava/lang/String;");
        jstring string = (jstring)(env->CallObjectMethod(env, sequence, mid));
        const char* utf = env->GetStringUTFChars(env, string, 0);
        
        if (utf) {
            const char* text = strdup(utf);
            env->ReleaseStringUTFChars(env, string, utf);
            return text;
        }
        
        return NULL;
    }
    
    return NULL;
#elif defined(ICE_CLIP_IOS)
    return strdup([[UIPasteboard generalPasteboard].string UTF8String]);
#elif defined(ICE_CLIP_OSX)
    return strdup([[[NSPasteboard generalPasteboard] stringForType:NSPasteboardTypeString] UTF8String]);
#elif defined(ICE_CLIP_TIZEN)
    cbhm_h clipboard;

	if (cbhm_open_service(&clipboard) != CBHM_ERROR_NONE) {
	    return NULL;
	}

	if (cbhm_selection_type_set(clipboard, CBHM_SEL_TYPE_TEXT) != CBHM_ERROR_NONE) {
		return NULL;
	}

    if (cbhm_selection_get(clipboard, CBHM_SEL_TYPE_TEXT, ice_clipboard_data_cb, NULL) != CBHM_ERROR_NONE) {
        return NULL;
    }

    if (cbhm_close_service(clipboard) != CBHM_ERROR_NONE) {
	    return NULL;
	}

    return res;
    
#elif defined(ICE_CLIP_BEOS)
    if (be_clipboard->Lock()) {
        int32 lenstr;
        const char* str;
        BMessage* clip = be_clipboard->Data();
        clip->FindData("text/plain", B_MIME_TYPE, (const void**) &str, &lenstr);
        be_clipboard->Unlock();
        return strdup(str);
    }
    
    return NULL;
#elif defined(ICE_CLIP_MICROSOFT)
    if (OpenClipboard(NULL) == 0) {
        return NULL;
    }
    
    const char* res = strdup((char*) GetClipboardData(CF_TEXT));
    
    if (CloseClipboard(NULL) == 0) {
        return NULL;
    }
    
    return res;
#elif defined(ICE_CLIP_UWP)
    DataPackageView^ dataPackageView = DataTransfer::Clipboard::GetContent();

    if (dataPackageView->Contains(StandardDataFormats::Text)) {
        Platform::String^ text_data = dataPackageView->GetTextAsync()->ToString();
        const wchar_t* text = text_data->Data();
        size_t text_len = wcslen(text);
        char* res = (char*) ICE_CLIP_MALLOC(text_len + 1);
        wcstombs(res, text, text_len);
        res[text_len + 1] = '\0';
        return res;
    }
    
    return NULL;
#endif
}

/* Sets the Clipboard text, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ICE_CLIP_API ice_clip_bool ICE_CLIP_CALLCONV ice_clip_set(const char* text) {
#if defined(ICE_CLIP_ANDROID)
    JNIEnv* env = ice_clip_native_activity->env;
    jclass activity_class = (jclass) ice_clip_native_activity->clazz;
    jstring service = env->NewStringUTF(env, "clipboard");
    jmethodID mid;
    
    mid = env->GetStaticMethodID(env, activity_class, "getContext", "()Landroid/content/Context;");
    jobject context = env->CallStaticObjectMethod(env, activity_class, mid);

    mid = env->GetMethodID(env, activity_class, "getSystemServiceFromUiThread", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject manager = env->CallObjectMethod(env, context, mid, service);

    env->DeleteLocalRef(env, service);

    jobject clipboard = manager ? env->NewGlobalRef(env, manager) : NULL;
    
    if (!clipboard) {
        return ICE_CLIP_FALSE;
    }
    
    jmethodID mid = env->GetMethodID(env, env->GetObjectClass(env, clipboard), "setText", "(Ljava/lang/CharSequence;)V");
    jstring string = env->NewStringUTF(env, text);
    env->CallVoidMethod(env, clipboard, mid, string);
    env->DeleteGlobalRef(env, clipboard);
    env->DeleteLocalRef(env, string);
    
    return ICE_CLIP_TRUE;
#elif defined(ICE_CLIP_IOS)
    NSString *txt = [NSString stringWithFormat:@"%s", text];
    [UIPasteboard generalPasteboard].string = txt;
    return ICE_CLIP_TRUE;
#elif defined(ICE_CLIP_OSX)
    NSString *txt = [NSString stringWithFormat:@"%s", text];
    [[NSPasteboard generalPasteboard] clearContents];
    return ([[NSPasteboard generalPasteboard] setString:txt forType:NSStringPboardType]) == YES ? ICE_CLIP_TRUE : ICE_CLIP_FALSE;
#elif defined(ICE_CLIP_TIZEN)
    cbhm_h clipboard;

    if (cbhm_open_service(&clipboard) != CBHM_ERROR_NONE) {
        return ICE_CLIP_FALSE;
    }

	if (cbhm_selection_type_set(clipboard, CBHM_SEL_TYPE_TEXT) != CBHM_ERROR_NONE) {
		return ICE_CLIP_FALSE;
	}

	if (cbhm_selection_set(clipboard, CBHM_SEL_TYPE_TEXT, text, strlen(text)) != CBHM_ERROR_NONE) {
		return ICE_CLIP_FALSE;
	}

	if (cbhm_close_service(clipboard) != CBHM_ERROR_NONE) {
		return ICE_CLIP_FALSE;
	}

	return ICE_CLIP_TRUE;
#elif defined(ICE_CLIP_BEOS)
    if (be_clipboard->Lock()) {
        be_clipboard->Clear();
        BMessage *clip = be_clipboard->Data();
        clip->AddData("text/plain", B_MIME_TYPE, text, strlen(text));
        
        if (be_clipboard->Commit() != B_OK) {
            return ICE_CLIP_FALSE;
        }
        
        be_clipboard->Unlock();
        return ICE_CLIP_TRUE;
    }
    
    return ICE_CLIP_FALSE;
#elif defined(ICE_CLIP_MICROSOFT)
    if (OpenClipboard(NULL) == 0) {
        return ICE_CLIP_FALSE;
    }
    
    HGLOBAL clipbuffer = GlobalAlloc(GMEM_DDESHARE, strlen(text) + 1);
    char* buffer = (char*) GlobalLock(clipbuffer);
    strcpy(buffer, LPCSTR(text));
    
    if (GlobalUnlock(clipbuffer) == 0) {
        return ICE_CLIP_FALSE;
    }
    
    SetClipboardData(CF_TEXT, clipbuffer);
    
    return (CloseClipboard(NULL) != 0) ? ICE_CLIP_TRUE : ICE_CLIP_FALSE;
#elif defined(ICE_CLIP_UWP)
    DataPackage^ dataPackage = ref new DataPackage();
    const size_t sz = strlen(text) + 1;
    wchar_t* wc = new wchar_t[sz];
    mbstowcs(wc, text, sz);
    
    String^ str = ref new String(wc);
    dataPackage->SetText(str);
    DataTransfer::Clipboard::SetContent(dataPackage);
    DataTransfer::Clipboard::Flush();
    
    delete dataPackage;
    delete wc;
    delete str;
    
    return ICE_CLIP_TRUE;
#endif
}

/* Clears the Clipboard, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ICE_CLIP_API ice_clip_bool ICE_CLIP_CALLCONV ice_clip_clear(void) {
#if defined(ICE_CLIP_ANDROID)
    ice_clip_set("");
#elif defined(ICE_CLIP_IOS)
    [UIPasteboard generalPasteboard].string = @"";
    return ICE_CLIP_TRUE;
#elif defined(ICE_CLIP_OSX)
    [[NSPasteboard generalPasteboard] clearContents];
    return ICE_CLIP_TRUE;
#elif defined(ICE_CLIP_TIZEN)
    return ice_clip_set("");
#elif defined(ICE_CLIP_BEOS)
    if (be_clipboard->Lock()) {
        be_clipboard->Clear();
        be_clipboard->Unlock();
        
        return ICE_CLIP_TRUE;
    }
    
    return ICE_CLIP_FALSE;
#elif defined(ICE_CLIP_MICROSOFT)
    if (OpenClipboard(NULL) == 0) {
        return ICE_CLIP_FALSE;
    }
    
    if (EmptyClipboard() == 0) {
        return ICE_CLIP_FALSE;
    }
    
    return (CloseClipboard() != 0) ? ICE_CLIP_TRUE : ICE_CLIP_FALSE;
#elif defined(ICE_CLIP_UWP)
    DataTransfer::Clipboard::Clear();
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
