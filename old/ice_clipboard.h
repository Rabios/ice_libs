// Written by Rabia Alhaffar in 11/April/2021
// ice_clipboard.h
// Single-Header Cross-Platform Clipboard library written in C!
// Updated: 25/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_clipboard.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_clipboard is cross-platform single-header C library for working with Clipboard!

[2] IMPLEMENTATION:
Windows             -> Clipboard API
Haiku/BeOS          -> BClipboard
Linux               -> X11
Android             -> JNI (android.clipboard.*)
iOS                 -> UIClipboard
OSX                 -> NSPasteboard
Elsewhere           -> Text file contains string

[3] USAGE:
Define ICE_CLIPBOARD_IMPL then include ice_clipboard.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_clipboard
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_clipboard by possibly one of following things:
//
// 1. Test ice_clipboard on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_clipboard LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_clipboard is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_CLIPBOARD_H
#define ICE_CLIPBOARD_H

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

// Allow to use calling convention if desired...
#if defined(__GNUC__) || defined(__GNUG__)
#  if defined(ICE_CLIPBOARD_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_CLIPBOARD_CALLCONV_FASTCALL)
#    define ICE_CLIPBOARD_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_CLIPBOARD_CALLCONV_STDCALL)
#    define ICE_CLIPBOARD_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_CLIPBOARD_CALLCONV_CDECL)
#    define ICE_CLIPBOARD_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_CLIPBOARD_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_CLIPBOARD_CALLCONV_VECTORCALL)
#    define ICE_CLIPBOARD_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_CLIPBOARD_CALLCONV_FASTCALL)
#    define ICE_CLIPBOARD_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_CLIPBOARD_CALLCONV_STDCALL)
#    define ICE_CLIPBOARD_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_CLIPBOARD_CALLCONV_CDECL)
#    define ICE_CLIPBOARD_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_CLIPBOARD_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_CLIPBOARD_CALLCONV_VECTORCALL)
#    define ICE_CLIPBOARD_CALLCONV __vectorcall
#  elif defined(ICE_CLIPBOARD_CALLCONV_FASTCALL)
#    define ICE_CLIPBOARD_CALLCONV __fastcall
#  elif defined(ICE_CLIPBOARD_CALLCONV_STDCALL)
#    define ICE_CLIPBOARD_CALLCONV __stdcall
#  elif defined(ICE_CLIPBOARD_CALLCONV_CDECL)
#    define ICE_CLIPBOARD_CALLCONV __cdecl
#  else
#    define ICE_CLIPBOARD_CALLCONV
#  endif
#else
#  define ICE_CLIPBOARD_CALLCONV
#endif

// Autodetect platform if not defined!
// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#if !defined(ICE_CLIPBOARD_MICROSOFT) && !defined(ICE_CLIPBOARD_UWP) && !defined(ICE_CLIPBOARD_LINUX) && !defined(ICE_CLIPBOARD_BSD) && !defined(ICE_CLIPBOARD_IOS) && !defined(ICE_CLIPBOARD_OSX) && !defined(ICE_CLIPBOARD_ANDROID) && !defined(ICE_CLIPBOARD_BEOS) && !defined(ICE_CLIPBOARD_NULL)
#  define ICE_CLIPBOARD_PLATFORM_AUTODETECTED
#endif

// ice_clipboard autodetection system (Huge but still worthy...)
#if defined(ICE_CLIPBOARD_PLATFORM_AUTODETECTED)
#  if defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android)
#    define ICE_CLIPBOARD_ANDROID
#  elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__DARWIN) || defined(_DARWIN)
#    if defined(APPLE_IOS) || defined(IOS) || defined(__IPHONEOS__) || defined(TARGET_OS_SIMULATOR) || defined(__IOS__) || defined(__APPLE_IOS__) || defined(IOS_OBJ_C) || defined(TARGET_OS_IOS)
#      define ICE_CLIPBOARD_IOS
#    else 
#      define ICE_CLIPBOARD_OSX
#    endif
#  elif (defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU)) || (defined(__BeOS) || defined(__BEOS__) || defined(_BEOS))
#    define ICE_CLIPBOARD_BEOS
#  elif defined(__linux__) || defined(__LINUX__) || defined(LINUX) || defined(__LINUX) || defined(__linux) || defined(linux) || defined(BSD) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__) && !(defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android))
#    define ICE_CLIPBOARD_LINUX
#  elif defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#    if defined(WINAPI_FAMILY_SYSTEM) || defined(WINAPI_PARTITION_APP)
#      define ICE_CLIPBOARD_UWP
#    else
#      define ICE_CLIPBOARD_MICROSOFT
#    end
#  else
#    define ICE_CLIPBOARD_NULL
#  endif
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_CLIPBOARD_EXTERN) && defined(ICE_CLIPBOARD_STATIC))
#  define ICE_CLIPBOARD_EXTERN
#endif

#if defined(ICE_CLIPBOARD_EXTERN)
#  define ICE_CLIPBOARD_APIDEF extern
#elif defined(ICE_CLIPBOARD_STATIC)
#  define ICE_CLIPBOARD_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_CLIPBOARD_INLINE to enable inline functionality.
#if defined(ICE_CLIPBOARD_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_CLIPBOARD_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_CLIPBOARD_INLINEDEF inline
#  endif
#else
#  define ICE_CLIPBOARD_INLINEDEF
#endif

// Allow to build DLL via ICE_CLIPBOARD_DLLEXPORT or ICE_CLIPBOARD_DLLIMPORT if desired!
// Else, Just define API as extern C code!
#if defined(ICE_CLIPBOARD_MICROSOFT)
#  if defined(ICE_CLIPBOARD_DLLEXPORT)
#    define ICE_CLIPBOARD_API __declspec(dllexport) ICE_CLIPBOARD_INLINEDEF
#  elif defined(ICE_CLIPBOARD_DLLIMPORT)
#    define ICE_CLIPBOARD_API __declspec(dllimport) ICE_CLIPBOARD_INLINEDEF
#  else
#    define ICE_CLIPBOARD_API ICE_CLIPBOARD_APIDEF ICE_CLIPBOARD_INLINEDEF
#  endif
#else
#  define ICE_CLIPBOARD_API ICE_CLIPBOARD_APIDEF ICE_CLIPBOARD_INLINEDEF
#endif

// UWP, Haiku, And BeOS can't work with C as their APIs mostly written in C++, They should be used with C++! :(
#if (defined(ICE_JOY_UWP) || defined(ICE_JOY_BEOS))
#  if !defined(__cplusplus)
#    error "C++ required for UWP, Haiku, and BeOS platforms!"
#  endif
#endif

// Custom memory allocators
#ifndef ICE_CLIPBOARD_MALLOC
#  define ICE_CLIPBOARD_MALLOC(sz) malloc(sz)
#endif
#ifndef ICE_CLIPBOARD_CALLOC
#  define ICE_CLIPBOARD_CALLOC(n, sz) calloc(n, sz)
#endif
#ifndef ICE_CLIPBOARD_REALLOC
#  define ICE_CLIPBOARD_REALLOC(ptr, sz) realloc(ptr, sz)
#endif
#ifndef ICE_CLIPBOARD_FREE
#  define ICE_CLIPBOARD_FREE(ptr) free(ptr)
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_clipboard DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_CLIPBOARD_TRUE  = 0,
    ICE_CLIPBOARD_FALSE = -1,
} ice_clipboard_bool;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_clipboard FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
ICE_CLIPBOARD_API  ice_clipboard_bool  ICE_CLIPBOARD_CALLCONV  ice_clipboard_init(void);
ICE_CLIPBOARD_API  ice_clipboard_bool  ICE_CLIPBOARD_CALLCONV  ice_clipboard_set(char* text);
ICE_CLIPBOARD_API  char*               ICE_CLIPBOARD_CALLCONV  ice_clipboard_get(void);
ICE_CLIPBOARD_API  ice_clipboard_bool  ICE_CLIPBOARD_CALLCONV  ice_clipboard_text(char* text);
ICE_CLIPBOARD_API  ice_clipboard_bool  ICE_CLIPBOARD_CALLCONV  ice_clipboard_clear(void);
ICE_CLIPBOARD_API  ice_clipboard_bool  ICE_CLIPBOARD_CALLCONV  ice_clipboard_close(void);

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_clipboard IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_CLIPBOARD_IMPL)
#include <stdio.h>
#include <string.h>

#if defined(ICE_CLIPBOARD_ANDROID)
#include <jni.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

static JavaVM* mJavaVM;
static pthread_key_t thkey;
jobject clipboard;
JNIEnv* env;

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_init(void) {
    int status = (*mJavaVM)->AttachCurrentThread(mJavaVM, &env, NULL);
    
    if (status < 0) {
        return ICE_CLIPBOARD_FALSE;
    }
    
    pthread_setspecific(thkey, (void*) env);
    jstring service = (*env)->NewStringUTF(env, "clipboard");

    jmethodID mid;

    mid = (*env)->GetStaticMethodID(env, mActivityClass, "getContext", "()Landroid/content/Context;");
    jobject context = (*env)->CallStaticObjectMethod(env, mActivityClass, mid);

    mid = (*env)->GetMethodID(env, mActivityClass, "getSystemServiceFromUiThread", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject manager = (*env)->CallObjectMethod(env, context, mid, service);

    (*env)->DeleteLocalRef(env, service);

    clipboard = manager ? (*env)->NewGlobalRef(env, manager) : NULL;
    
    return (clipboard != NULL) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_set(char* text) {
    jmethodID mid = (*env)->GetMethodID(env, (*env)->GetObjectClass(env, clipboard), "setText", "(Ljava/lang/CharSequence;)V");
    jstring string = (*env)->NewStringUTF(env, text);
    (*env)->CallVoidMethod(env, clipboard, mid, string);
    (*env)->DeleteGlobalRef(env, clipboard);
    (*env)->DeleteLocalRef(env, string);
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API char* ICE_CLIPBOARD_CALLCONV ice_clipboard_get(void) {
    jmethodID mid = (*env)->GetMethodID(env, (*env)->GetObjectClass(env, clipboard), "getText", "()Ljava/lang/CharSequence;");
    jobject sequence = (*env)->CallObjectMethod(env, clipboard, mid);
    (*env)->DeleteGlobalRef(env, clipboard);
    
    if (sequence) {
        mid = (*env)->GetMethodID(env, (*env)->GetObjectClass(env, sequence), "toString", "()Ljava/lang/String;");
        jstring string = (jstring)((*env)->CallObjectMethod(env, sequence, mid));
        const char* utf = (*env)->GetStringUTFChars(env, string, 0);
        
        if (utf) {
            char* text = strdup(utf);
            (*env)->ReleaseStringUTFChars(env, string, utf);
            return text;
        }
    }
    
    return NULL;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_text(char* text) {
    return (strcmp(ice_clipboard_get(), text) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_clear(void) {
    ice_clipboard_set("");
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_close(void) {
    return ICE_CLIPBOARD_TRUE;
}

#elif defined(ICE_CLIPBOARD_IOS)
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_init(void) {
    return ([UIPasteboard generalPasteboard] != NULL) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_set(char* text) {
    NSString *txt = [NSString stringWithFormat:@"%s", text];
    [UIPasteboard generalPasteboard].string = txt;
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API char* ICE_CLIPBOARD_CALLCONV ice_clipboard_get(void) {
    return strdup([[UIPasteboard generalPasteboard].string UTF8String]);
    //return [[UIPasteboard generalPasteboard].string cStringUsingEncoding:[NSString defaultCStringEncoding]];
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_text(char* text) {
    return (strcmp(ice_clipboard_get(), text) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_clear(void) {
    [UIPasteboard generalPasteboard].string = @"";
    //ice_clipboard_set("");
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_close(void) {
    return ICE_CLIPBOARD_TRUE;
}

#elif defined(ICE_CLIPBOARD_OSX)
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_init(void) {
    return ([NSPasteboard generalPasteboard] != NULL) ? ICE_CLIPBOARD_TRUE: ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_set(char* text) {
    NSString *txt = [NSString stringWithFormat:@"%s", text];
    [[NSPasteboard generalPasteboard] clearContents];
    return ([[NSPasteboard generalPasteboard] setString:txt forType:NSStringPboardType] == YES) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API char* ICE_CLIPBOARD_CALLCONV ice_clipboard_get(void) {
    return strdup([[[NSPasteboard generalPasteboard] stringForType:NSPasteboardTypeString] UTF8String]);
    //return [[[NSPasteboard generalPasteboard] stringForType:NSPasteboardTypeString] cStringUsingEncoding:[NSString defaultCStringEncoding]];
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_clear(void) {
    [[NSPasteboard generalPasteboard] clearContents];
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_text(char* text) {
    return (strcmp(ice_clipboard_get(), text) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_close(void) {
    return ICE_CLIPBOARD_TRUE;
}

#elif defined(ICE_CLIPBOARD_BEOS)
#include <app/Clipboard.h>

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_init(void) {
    return (be_clipboard != NULL) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_set(char* text) {
    if (be_clipboard->Lock()) {
        be_clipboard->Clear();
        BMessage *clip = be_clipboard->Data();
        clip->AddData("text/plain", B_MIME_TYPE, text, strlen(text));
        
        if (be_clipboard->Commit() != B_OK) {
            return ICE_CLIPBOARD_FALSE;
        }
        
        be_clipboard->Unlock();
        return ICE_CLIPBOARD_TRUE;
    } else {
        return ICE_CLIPBOARD_FALSE;
    }
}

ICE_CLIPBOARD_API char* ICE_CLIPBOARD_CALLCONV ice_clipboard_get(void) {
    if (be_clipboard->Lock()) {
        int32 lenstr;
        char* str;
        BMessage* clip = be_clipboard->Data();
        clip->FindData("text/plain", B_MIME_TYPE, (const void **)&str, &lenstr);
        be_clipboard->Unlock();
        return strdup(str);
    } else {
        return NULL;
    }
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_clear(void) {
    if (be_clipboard->Lock()) {
        be_clipboard->Clear();
        be_clipboard->Unlock();
        return ICE_CLIPBOARD_TRUE;
    } else {
        return ICE_CLIPBOARD_FALSE;
    }
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_text(char* text) {
    return (strcmp(ice_clipboard_get(), text) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_close(void) {
    return ICE_CLIPBOARD_TRUE;
}

#elif defined(ICE_CLIPBOARD_LINUX)
#include <X11/Xlib.h>

static Display* display;
static Atom UTF8;
static Atom CLIPBOARD;
static Atom XSEL_DATA;
static Atom TARGETS;
static Atom TEXT;
static int XA_STRING    = 31;
static int XA_ATOM      = 4;
static Atom copy_type;

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_init(void) {
    display = XOpenDisplay(0);
    
    if (display == NULL) {
        return ICE_CLIPBOARD_FALSE;
    }
    
    TARGETS     = XInternAtom(display, "TARGETS", 0);
    TEXT        = XInternAtom(display, "TEXT", 0);
    UTF8        = XInternAtom(display, "UTF8_STRING", True);
    CLIPBOARD   = XInternAtom(display, "CLIPBOARD", 0);
    XSEL_DATA   = XInternAtom(display, "XSEL_DATA", 0);
    
    if (UTF8 != None) {
        copy_type = UTF8;
    } else {
        copy_type = XA_STRING;
    }
    
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_set(char* text) {
    XEvent event;
    XSetSelectionOwner(display, CLIPBOARD, NULL, 0);
    
    while (1) {
        XNextEvent(display, &event);
        if (event.type == SelectionRequest) {
            if (event.xselectionrequest.selection != CLIPBOARD) break;
            XSelectionRequestEvent * xsr = &event.xselectionrequest;
            XSelectionEvent ev = {0};
            int R = 0;
            ev.type = SelectionNotify, ev.display = xsr->display, ev.requestor = xsr->requestor,
            ev.selection = xsr->selection, ev.time = xsr->time, ev.target = xsr->target, ev.property = xsr->property;
            
            if (ev.target == targets_atom) {
                R = XChangeProperty(ev.display, ev.requestor, ev.property, XA_ATOM, 32, PropModeReplace, (unsigned char*)&UTF8, 1);
            } else if (ev.target == XA_STRING || ev.target == text_atom) {
                R = XChangeProperty(ev.display, ev.requestor, ev.property, XA_STRING, 8, PropModeReplace, text, strlen(text));
            } else if (ev.target == UTF8) {
                R = XChangeProperty(ev.display, ev.requestor, ev.property, UTF8, 8, PropModeReplace, text, strlen(text));
            } else {
                ev.property = None;
            }
            
            if ((R & 2) == 0) XSendEvent(display, ev.requestor, 0, 0, (XEvent *)&ev);
            break;
        } else if (event.type == SelectionClear) {
            return ICE_CLIPBOARD_TRUE;
        }
    }
}

ICE_CLIPBOARD_API char* ICE_CLIPBOARD_CALLCONV ice_clipboard_get(void) {
    XEvent event;
    int format;
    unsigned long N, size;
    char* data, *s = 0;
    Atom target;
	
    XConvertSelection(display, CLIPBOARD, copy_type, XSEL_DATA, NULL, CurrentTime);
    XSync(display, 0);
    XNextEvent(display, &event);
	
    if (event.type == SelectionNotify) {
        if (event.xselection.selection != CLIPBOARD) break;
        if (event.xselection.property) {
            XGetWindowProperty(event.xselection.display, event.xselection.requestor, event.xselection.property, 0L,(~0L), 0, AnyPropertyType, &target, &format, &size, &N,(unsigned char**)&data);
            
            if (target == UTF8 || target == XA_STRING) {
                s = strndup(data, size);
                XFree(data);
            }
            
            XDeleteProperty(event.xselection.display, event.xselection.requestor, event.xselection.property);
        }
        
        return s;
    } else {
        return NULL;
    }
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_clear(void) {
    ice_clipboard_set("");
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_text(char* text) {
    return (strcmp(ice_clipboard_get(), text) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_close(void) {
    return ICE_CLIPBOARD_TRUE;
}

#elif defined(ICE_CLIPBOARD_MICROSOFT)
#include <windows.h>

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_init(void) {
    return OpenClipboard(NULL) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_set(char* text) {
    EmptyClipboard();
    HGLOBAL clipbuffer = GlobalAlloc(GMEM_DDESHARE, strlen(text) + 1);
    char* buffer = (char*) GlobalLock(clipbuffer);
    strcpy(buffer, LPCSTR(text));
    GlobalUnlock(clipbuffer);
    SetClipboardData(CF_TEXT, clipbuffer);
}

ICE_CLIPBOARD_API char* ICE_CLIPBOARD_CALLCONV ice_clipboard_get(void) {
    return (char*)GetClipboardData(CF_TEXT);
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_clear(void) {
    EmptyClipboard();
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_text(char* text) {
    return (strcmp(ice_clipboard_get(), text) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_close(void) {
    CloseClipboard();
    return ICE_CLIPBOARD_TRUE;
}

#elif defined(ICE_CLIPBOARD_UWP)

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::DataTransfer;

auto dataPackage;

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_init(void) {
    dataPackage = ref new DataPackage();
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_set(char* text) {
    dataPackage->SetText(text);
    DataTransfer::Clipboard::SetContent(dataPackage);
}

ICE_CLIPBOARD_API char* ICE_CLIPBOARD_CALLCONV ice_clipboard_get(void) {
    DataPackageView^ dataPackageView = DataTransfer::Clipboard::GetContent();
    
    if (dataPackageView->Contains(StandardDataFormats::Text)) {
        create_task(dataPackageView->GetTextAsync()).then([this](task<String^> textTask) {
            try {
                return strdup(textTask.get().c_str());
            }
        });
    }
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_clear(void) {
    DataTransfer::Clipboard::Clear();
    return ICE_CLIPBOARD_TRUE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_text(char* text) {
    return (strcmp(ice_clipboard_get(), text) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_close(void) {
    return ICE_CLIPBOARD_TRUE;
}

#elif defined(ICE_CLIPBOARD_NULL)
#include <stdio.h>
#include <string.h>

FILE* ice_clipboard_data;

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_init(void) {
    ice_clipboard_data = fopen("ice_clipboard_data.txt", "a");
    return (ice_clipboard_data != NULL) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_set(char* text) {
    fclose(fopen("ice_clipboard_data.txt", "w"));
    return (fprintf(ice_clipboard_data, "%s\0", text) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API char* ICE_CLIPBOARD_CALLCONV ice_clipboard_get(void) {
    int ch;
    int nch = 0;
    int size = 64;
    char *buf = ICE_CLIPBOARD_MALLOC(size);
    
    while ((c = fgetc(ice_clipboard_data)) != EOF) {
        if (nch >= size - 1) {
            size += 64;
            buf = ICE_CLIPBOARD_REALLOC(buf, size);
         
            if (buf == NULL) {
               return NULL;
            }
        }

        buf[nch++] = c;
    }

    buf[nch++] = '\0';
    return buf;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_clear(void) {
    fclose(fopen("ice_clipboard_data.txt", "w"));
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_text(char* text) {
    return (strcmp(ice_clipboard_get(), text) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

ICE_CLIPBOARD_API ice_clipboard_bool ICE_CLIPBOARD_CALLCONV ice_clipboard_close(void) {
    return (fclose(ice_clipboard_data) == 0) ? ICE_CLIPBOARD_TRUE : ICE_CLIPBOARD_FALSE;
}

#endif

#endif  // ICE_CLIPBOARD_IMPL
#endif  // ICE_CLIPBOARD_H
