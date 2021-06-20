// Written by Rabia Alhaffar in 18/June/2021
// ice_mouse.h
// Single-Header Cross-Platform C library for Mouse input.
// Updated: 20/June/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_mouse.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_mouse is Single-Header Cross-Platform C library for Mouse input.

Works on:

1. Microsoft Platforms
2. OSX
3. Linux and Unix-Like
4. Android
5. Web

[2] USAGE:
Define ICE_MOUSE_IMPL then include ice_mouse.h in your C/C++ code!

[3] IMPLEMENTATION NOTES:

[Windows]
You can use ice_mouse_set_window_handle function to let ice_mouse use a specified window if there is (Pass Window's HWND as param to the function)

[Android]
Before including ice_mouse.h, If you have 2 functions for Android command events and Android input events...
Add #define ICE_MOUSE_ANDROID_CUSTOM_INPUT_EVENT_HANDLERS then set the 2 functions like this way:

#define ANDROID_CMD_HANDLE_FUNC     android_cmd_handling_func_name    // Once loop, ice_mouse will call it inside command event function
#define ANDROID_INPUT_HANDLE_FUNC   android_input_handling_func_name  // Once loop, ice_mouse will call it inside input events function

[LINUX]
ice_mouse expects to recieve mouse input via /dev/input/mice file descriptor...
But, you can set it to default file before #include "ice_mouse.h" by following way:

#define ICE_MOUSE_FD_PATH "/dev/input/mouse0"

[MacOS/OSX]
You need to include ice_mouse in your NSView code as ice_mouse provides Objective-C events like mouseDown, mouseUp, scrollWheel, mouseDragged, and mouseLocation.
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_mouse
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_mouse by possibly one of following things:
//
// 1. Test ice_mouse on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_mouse LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_mouse is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_MOUSE_H
#define ICE_MOUSE_H

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
#  if defined(ICE_MOUSE_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_MOUSE_CALLCONV_FASTCALL)
#    define ICE_MOUSE_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_MOUSE_CALLCONV_STDCALL)
#    define ICE_MOUSE_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_MOUSE_CALLCONV_CDECL)
#    define ICE_MOUSE_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_MOUSE_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_MOUSE_CALLCONV_VECTORCALL)
#    define ICE_MOUSE_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_MOUSE_CALLCONV_FASTCALL)
#    define ICE_MOUSE_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_MOUSE_CALLCONV_STDCALL)
#    define ICE_MOUSE_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_MOUSE_CALLCONV_CDECL)
#    define ICE_MOUSE_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_MOUSE_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_MOUSE_CALLCONV_VECTORCALL)
#    define ICE_MOUSE_CALLCONV __vectorcall
#  elif defined(ICE_MOUSE_CALLCONV_FASTCALL)
#    define ICE_MOUSE_CALLCONV __fastcall
#  elif defined(ICE_MOUSE_CALLCONV_STDCALL)
#    define ICE_MOUSE_CALLCONV __stdcall
#  elif defined(ICE_MOUSE_CALLCONV_CDECL)
#    define ICE_MOUSE_CALLCONV __cdecl
#  else
#    define ICE_MOUSE_CALLCONV
#  endif
#else
#  define ICE_MOUSE_CALLCONV
#endif

// Autodetect platform if not defined!
// If no platform defined, This definition will define itself.
#if !defined(ICE_MOUSE_MICROSOFT) && !defined(ICE_MOUSE_LINUX) && !defined(ICE_MOUSE_OSX) && !defined(ICE_MOUSE_ANDROID) && !defined(ICE_MOUSE_WEB)
#  define ICE_MOUSE_PLATFORM_AUTODETECTED
#endif

// ice_mouse autodetection system (Huge but still worthy...)
#if defined(ICE_MOUSE_PLATFORM_AUTODETECTED)
#  if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox)
#    define ICE_MOUSE_MICROSOFT
#  elif defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android)
#    define ICE_MOUSE_ANDROID
#  elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__DARWIN) || defined(_DARWIN)
#    if defined(APPLE_IOS) || defined(IOS) || defined(__IPHONEOS__) || defined(TARGET_OS_SIMULATOR) || defined(__IOS__) || defined(__APPLE_IOS__) || defined(IOS_OBJ_C) || defined(TARGET_OS_IOS)
#      error "iOS does not support mouse input!"
#    else 
#      define ICE_MOUSE_OSX
#    endif
#  elif defined(__EMSCRIPTEN__) || defined(__EMSCRIPTEN) || defined(EMSCRIPTEN)
#    define ICE_MOUSE_WEB
#  elif defined(__linux__) || defined(__LINUX__) || defined(LINUX) || defined(__LINUX) || defined(__linux) || defined(linux) && !(defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android))
#    define ICE_MOUSE_LINUX
#  endif
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_MOUSE_EXTERN) && defined(ICE_MOUSE_STATIC))
#  define ICE_MOUSE_EXTERN
#endif

#if defined(ICE_MOUSE_EXTERN)
#  define ICE_MOUSE_APIDEF extern
#elif defined(ICE_MOUSE_STATIC)
#  define ICE_MOUSE_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_MOUSE_INLINE to enable inline functionality.
#if defined(ICE_MOUSE_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_MOUSE_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_MOUSE_INLINEDEF inline
#  endif
#else
#  define ICE_MOUSE_INLINEDEF
#endif

// Allow to build DLL via ICE_MOUSE_DLLEXPORT or ICE_MOUSE_DLLIMPORT if desired!
// Else, Just define API as extern C code!
#if defined(ICE_MOUSE_MICROSOFT)
#  if defined(ICE_MOUSE_DLLEXPORT)
#    define ICE_MOUSE_API __declspec(dllexport) ICE_MOUSE_INLINEDEF
#  elif defined(ICE_MOUSE_DLLIMPORT)
#    define ICE_MOUSE_API __declspec(dllimport) ICE_MOUSE_INLINEDEF
#  else
#    define ICE_MOUSE_API ICE_MOUSE_APIDEF ICE_MOUSE_INLINEDEF
#  endif
#else
#  define ICE_MOUSE_API ICE_MOUSE_APIDEF ICE_MOUSE_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_mouse DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_MOUSE_TRUE = 0,
    ICE_MOUSE_FALSE = -1
} ice_mouse_bool;

typedef enum {
    ICE_MOUSE_BUTTON_LEFT,
    ICE_MOUSE_BUTTON_RIGHT,
    ICE_MOUSE_BUTTON_CENTER
} ice_mouse_button;

typedef struct ice_mouse_vec2 {
    float x;
    float y;
} ice_mouse_vec2;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_mouse FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
ICE_MOUSE_API  ice_mouse_bool  ICE_MOUSE_CALLCONV  ice_mouse_set_window_handle(void* window);                   // Sets which window will handle input by ice_mouse (Designed for Windows but returns ICE_MOUSE_TRUE on other-platforms).
ICE_MOUSE_API  ice_mouse_bool  ICE_MOUSE_CALLCONV  ice_mouse_init(void);                                        // Initializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API  ice_mouse_bool  ICE_MOUSE_CALLCONV  ice_mouse_update(void);                                      // Updates mouse input, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API  ice_mouse_bool  ICE_MOUSE_CALLCONV  ice_mouse_close(void);                                       // Deinitializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API  ice_mouse_vec2  ICE_MOUSE_CALLCONV  ice_mouse_pos(void);                                         // Returns current mouse position as 2D vector.
ICE_MOUSE_API  ice_mouse_bool  ICE_MOUSE_CALLCONV  ice_mouse_button_down(ice_mouse_button button);              // Returns ICE_MOUSE_TRUE if mouse button is being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API  ice_mouse_bool  ICE_MOUSE_CALLCONV  ice_mouse_button_up(ice_mouse_button button);                // Returns ICE_MOUSE_TRUE if mouse button is not being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API  ice_mouse_bool  ICE_MOUSE_CALLCONV  ice_mouse_button_pressed(ice_mouse_button button);           // Returns ICE_MOUSE_TRUE if mouse button pressed (Not "being" which means hold/down) or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API  ice_mouse_bool  ICE_MOUSE_CALLCONV  ice_mouse_button_released(ice_mouse_button button);          // Returns ICE_MOUSE_TRUE if mouse button released or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API  float           ICE_MOUSE_CALLCONV  ice_mouse_wheel(void);                                       // Returns mouse wheel delta as float.

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_mouse IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_MOUSE_IMPL)

static ice_mouse_bool ice_mouse_open = ICE_MOUSE_FALSE;

#if defined(ICE_MOUSE_MICROSOFT)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_MOUSE_MICROSOFT IMPLEMENTATION       (Microsoft Platforms - DirectInput)
///////////////////////////////////////////////////////////////////////////////////////////
#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include <winuser.h>
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

static LPDIRECTINPUT8 di;
static LPDIRECTINPUTDEVICE8 mice;

static DIMOUSESTATE2 next_ev;
static DIMOUSESTATE2 prev_ev;

static int window_flags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
static void* win = NULL;
static ice_mouse_vec2 mouse_pos;

// Sets which window will handle input by ice_mouse (Designed for Windows but returns ICE_MOUSE_TRUE on other-platforms).
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_set_window_handle(void* window) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        if (window) {
            window_flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
            win = window;
        }
        
        return ICE_MOUSE_TRUE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Initializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_init(void) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        mouse_pos = (ice_mouse_vec2) { 0, 0 };
    
        if (!win) {
            win = GetConsoleWindow();
            SetCursorPos(0, 0);
        }

        if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, &IID_IDirectInput8, (VOID**)&di, NULL))) {
            return ice_mouse_open;
        }

        if (FAILED(IDirectInput_CreateDevice(di, &GUID_SysMouse, &mice, NULL))) {
            return ice_mouse_open;
        }

        if (mice) {
            if (FAILED(IDirectInputDevice_SetDataFormat(mice, &c_dfDIMouse2))) {
                return ice_mouse_open;
            }

            if (FAILED(IDirectInputDevice_SetCooperativeLevel(mice, win, window_flags))) {
                return ice_mouse_open;
            }

            if (FAILED(IDirectInputDevice_Acquire(mice))) {
                return ice_mouse_open;
            }
            
            ice_mouse_open = ICE_MOUSE_TRUE;
            return ice_mouse_open;
        }
        
        return ice_mouse_open;
    }

    return ice_mouse_open;
}

// Deinitializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_close(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        if (FAILED(IDirectInputDevice_Unacquire(mice))) {
            return ICE_MOUSE_FALSE;
        }

        if (FAILED(IDirectInputDevice_Release(mice))) {
            return ICE_MOUSE_FALSE;
        }

        if (FAILED(IDirectInput_Release(di))) {
            return ICE_MOUSE_FALSE;
        }
        
        ice_mouse_open = ICE_MOUSE_FALSE;
        return ICE_MOUSE_TRUE;
    }

    return ICE_MOUSE_TRUE;
}

// Updates mouse input, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_update(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        prev_ev = next_ev;
    
        if (FAILED(IDirectInputDevice_GetDeviceState(mice, sizeof(DIMOUSESTATE2), (LPVOID)&next_ev))) {
            IDirectInputDevice_Acquire(mice);
            return;
        }
    
        //mouse_pos.x += (float)next_ev.lX;
        //mouse_pos.y += (float)next_ev.lY;
        POINT pos;
        GetCursorPos(&pos);
        mouse_pos.x = (float) pos.x;
        mouse_pos.y = (float) pos.y;
    
        return ICE_MOUSE_TRUE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns current mouse position as 2D vector.
ICE_MOUSE_API ice_mouse_vec2 ICE_MOUSE_CALLCONV ice_mouse_pos(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return mouse_pos;
    }
    
    return (ice_mouse_vec2) { -1, -1 };
}

// Returns ICE_MOUSE_TRUE if mouse button is being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_down(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return next_ev.rgbButtons[button] ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button is not being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_up(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return !next_ev.rgbButtons[button] ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button pressed (Not "being" which means hold/down) or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_pressed(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (next_ev.rgbButtons[button] && !prev_ev.rgbButtons[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button released or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_released(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (!next_ev.rgbButtons[button] && !prev_ev.rgbButtons[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns mouse wheel delta as float.
ICE_MOUSE_API float ICE_MOUSE_CALLCONV ice_mouse_wheel(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (float)(next_ev.lZ / WHEEL_DELTA);
    }
    
    return 0;
}

#elif defined(ICE_MOUSE_ANDROID)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_MOUSE_ANDROID IMPLEMENTATION       (Android - Android NDK)
///////////////////////////////////////////////////////////////////////////////////////////
#include <android_native_app_glue.h>
#include <android/input.h>

int prev_state[3];
int next_state[3];
struct android_app* app;
struct android_poll_source *source;
int32_t android_cmd;
int poll_res = 0;
int poll_events = 0;
int mouse_event_type = 0;
ice_mouse_vec2 mouse_pos;
float wy = 0;

// Trick to run from android_main
extern int main(int argc, char *argv[]);

#if defined(ICE_MOUSE_ANDROID_CUSTOM_INPUT_EVENT_HANDLERS)
#  if defined(ANDROID_INPUT_HANDLE_FUNC)
#    define ANDROID_INPUT_HANDLE_FUNC_DEFINED
#  endif
#  if defined(ANDROID_CMD_HANDLE_FUNC)
#    define ANDROID_CMD_HANDLE_FUNC_DEFINED
#  endif
#endif

static int32_t ice_mouse_input_callback(struct android_app *app, AInputEvent *event) {
    if (android_app_get_input == ICE_MOUSE_TRUE) {
#if defined(ANDROID_INPUT_HANDLE_FUNC_DEFINED)
        ANDROID_INPUT_HANDLE_FUNC(app, event);
#endif
        int type = AInputEvent_getType(event);
        int source = AInputEvent_getSource(event);
        
        if (type == AINPUT_EVENT_TYPE_MOTION || type == AINPUT_EVENT_TYPE_DRAG || type == AINPUT_EVENT_TYPE_KEY) {
            if ((source & AINPUT_SOURCE_MOUSE) == AINPUT_SOURCE_MOUSE) {
                prev_state = next_state;
                int32_t action = AMotionEvent_getAction(event);
                unsigned int flags = action & AMOTION_EVENT_ACTION_MASK;
                
                if (flags == AMOTION_EVENT_ACTION_MOVE) {
                    mouse_pos = (ice_mouse_vec2) {
                        (float) AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_X, 0),
                        (float) AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_Y, 0),
                    };
                } else if (flags == AMOTION_EVENT_ACTION_SCROLL) {
                    wy = (float) AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_VSCROLL, 0);
                } else if (flags == AMOTION_EVENT_ACTION_POINTER_DOWN || AMOTION_EVENT_ACTION_BUTTON_DOWN || flags == AMOTION_EVENT_ACTION_DOWN) {
                    int32_t buttons = AMotionEvent_getButtonState(event);
                    next_state[0] = buttons & AMOTION_EVENT_BUTTON_PRIMARY;
                    next_state[1] = buttons & AMOTION_EVENT_BUTTON_SECONDARY;
                    next_state[2] = buttons & AMOTION_EVENT_BUTTON_TERTIARY;
                    
                } else if (flags == AMOTION_EVENT_ACTION_POINTER_UP || AMOTION_EVENT_ACTION_BUTTON_UP || flags == AMOTION_EVENT_ACTION_UP) {
                    int32_t buttons = AMotionEvent_getButtonState(event);
                    next_state[0] = buttons & AMOTION_EVENT_BUTTON_PRIMARY;
                    next_state[1] = buttons & AMOTION_EVENT_BUTTON_SECONDARY;
                    next_state[2] = buttons & AMOTION_EVENT_BUTTON_TERTIARY;
                }
            }
        }
        
        return 0;
    }
    
    return -1;
}

static int32_t ice_mouse_cmd_callback(struct android_app *app, int32_t cmd) {
#if defined(ANDROID_CMD_HANDLE_FUNC_DEFINED)
    ANDROID_CMD_HANDLE_FUNC(app, cmd);
#endif
    if ((cmd == APP_CMD_PAUSE) || (cmd == APP_CMD_LOST_FOCUS) || (cmd == APP_CMD_STOP) || (cmd == APP_CMD_DESTROY) || (cmd == APP_CMD_TERM_WINDOW)) {
        android_app_get_input = ICE_MOUSE_FALSE;
    } else {
        if (cmd == APP_CMD_START) {
            android_app_get_input = ICE_MOUSE_FALSE;
        }
        
        if ((cmd == APP_CMD_GAINED_FOCUS) || (cmd == APP_CMD_RESUME)) {
            android_app_get_input = ICE_MOUSE_TRUE;
        }
        
        if (cmd == APP_CMD_INIT_WINDOW) {
            if (app->window != NULL) {
                android_app_get_input = ICE_MOUSE_TRUE;
            }
        } 
    }
    
    return 0;
}

void android_main(struct android_app *app) {
    struct engine engine{};
    memset(&engine, 0, sizeof(engine));
    app->userData = &engine;
    app->onInputEvent = ice_mouse_input_callback;
    app->onAppCmd = ice_mouse_cmd_callback;
    
    do {
        if (ALooper_pollAll(0, nullptr, &poll_events, (void **) &source) >= 0) {
            if (source) {
                source->process(app, source);
            }
        }
    } while (!app->destroyRequested);
    
    (void)main(1, (char *[]) { "ice_mouse", NULL });
}

// Sets which window will handle input by ice_mouse (Designed for Windows but returns ICE_MOUSE_TRUE on other-platforms).
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_set_window_handle(void* window) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        return ICE_MOUSE_TRUE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Initializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_init(void) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        ice_mouse_open = ICE_MOUSE_TRUE;
        return ice_mouse_open;
    }
    
    return ice_mouse_open;
}

// Updates mouse input, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_update(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        if ((poll_res = ALooper_pollAll(android_app_get_input, NULL, &poll_events, (void**)&source)) >= 0) {
            if (source != NULL) {
                source->process(app, source);
                return ICE_MOUSE_TRUE;
            }
            if (app->destroyRequested) {
                android_app_get_input = ICE_MOUSE_FALSE; // Don't close window but don't trigger input anymore!
                return ICE_MOUSE_FALSE;
            }
        }
    }
    
    return ICE_MOUSE_FALSE;
}

// Deinitializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_close(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        android_app_get_input = ICE_MOUSE_FALSE;
        ice_mouse_open = ICE_MOUSE_FALSE;
        return ICE_MOUSE_TRUE;
    }
    
    return ICE_MOUSE_TRUE;
}

// Returns current mouse position as 2D vector.
ICE_MOUSE_API ice_mouse_vec2 ICE_MOUSE_CALLCONV ice_mouse_pos(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return mouse_pos;
    }
    
    return (ice_mouse_vec2) { -1, -1 };
}

// Returns ICE_MOUSE_TRUE if mouse button is being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_down(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (next_state[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button is not being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_up(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (!next_state[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button pressed (Not "being" which means hold/down) or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_pressed(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (next_state[button] && next_state[button] != prev_state[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button released or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_released(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (!next_state[button] && next_state[button] != prev_state[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns mouse wheel delta as float.
ICE_MOUSE_API float ICE_MOUSE_CALLCONV ice_mouse_wheel(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return wy;
    }
    
    return 0;
}

#elif defined(ICE_MOUSE_LINUX)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_MOUSE_LINUX IMPLEMENTATION       (Linux and Unix-Like Platforms)
///////////////////////////////////////////////////////////////////////////////////////////
#include <fcntl.h>
#include <linux/input.h>

#ifndef ICE_MOUSE_FD_PATH
#define ICE_MOUSE_FD_PATH "/dev/input/mice" // Shall we use /dev/input/mouse0 instead?
#endif

int mouse_fd;
unsigned char data[4];
int prev_ev[3];
int next_ev[3];
ice_mouse_vec2 mouse_pos;
float wy;

// Sets which window will handle input by ice_mouse (Designed for Windows but returns ICE_MOUSE_TRUE on other-platforms).
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_set_window_handle(void* window) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        return ICE_MOUSE_TRUE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Initializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_init(void) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        mouse_pos = (ice_mouse_vec2) { 0, 0 };
    
        if ((mouse_fd = open(ICE_MOUSE_FD_PATH, O_RDONLY | O_NONBLOCK)) == -1) {
            return ICE_MOUSE_FALSE;
        }
    
        return ICE_MOUSE_TRUE;
    }
    
    return ice_mouse_open;
}

// Updates mouse input, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_update(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        prev_ev = next_ev;
        int res = read(fd, data, sizeof(data));
    
        if (res > 0) {
            next_ev[0] = data[0] & 0x1;
            next_ev[1] = data[0] & 0x2;
            next_ev[2] = data[0] & 0x4;
            mouse_pos.x += (float) data[1];
            mouse_pos.y += (float) data[2];
            wy = (float) data[3];
        }
    
        return ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Deinitializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_close(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        if (close(mouse_fd) == -1) {
            return ICE_MOUSE_FALSE;
        }
    
        return ICE_MOUSE_TRUE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns current mouse position as 2D vector.
ICE_MOUSE_API ice_mouse_vec2 ICE_MOUSE_CALLCONV ice_mouse_pos(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return mouse_pos;
    }
    
    return (ice_mouse_vec2) { -1, -1 };
}

// Returns ICE_MOUSE_TRUE if mouse button is being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_down(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return next_ev[button] ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button is not being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_up(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return !next_ev[button] ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button pressed (Not "being" which means hold/down) or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_pressed(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (next_ev[button] && next_ev[button] != prev_ev[button) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button released or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_released(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (!next_ev[button] && next_ev[button] != prev_ev[button) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns mouse wheel delta as float.
ICE_MOUSE_API float ICE_MOUSE_CALLCONV ice_mouse_wheel(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return wy;
    }
    
    return 0;
}

#elif defined(ICE_MOUSE_OSX)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_MOUSE_OSX IMPLEMENTATION       (macOS/OSX - NSView events)
///////////////////////////////////////////////////////////////////////////////////////////
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

int prev_state[3];
int next_state[3];
float wy = 0;
ice_mouse_vec2 mouse_pos;

- (void) mouseDown: (NSEvent*) event {
    prev_state = next_state;
    NSUInteger buttons = [event pressedMouseButtons];
    next_state[0] = (buttons & (1 << 0));
    next_state[1] = (buttons & (1 << 1));
    next_state[2] = (buttons & (1 << 2));
}

- (void) mouseUp: (NSEvent*) event {
    prev_state = next_state;
    NSUInteger buttons = [event pressedMouseButtons];
    next_state[0] = (buttons & (1 << 0));
    next_state[1] = (buttons & (1 << 1));
    next_state[2] = (buttons & (1 << 2));
}

- (void) mouseDragged: (NSEvent*) event {
    prev_state = next_state;
    NSUInteger buttons = [event pressedMouseButtons];
    next_state[0] = (buttons & (1 << 0));
    next_state[1] = (buttons & (1 << 1));
    next_state[2] = (buttons & (1 << 2));
}

- (void) scrollWheel: (NSEvent*) event {
    wy = (float) [event scrollingDeltaY];
}

// Sets which window will handle input by ice_mouse (Designed for Windows but returns ICE_MOUSE_TRUE on other-platforms).
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_set_window_handle(void* window) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        return ICE_MOUSE_TRUE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Initializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_init(void) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        ice_mouse_open = ICE_MOUSE_TRUE;
    }
    
    return ice_mouse_open;
}

// Updates mouse input, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_update(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        NSPoint pos = [NSEvent mouseLocation];
        mouse_pos.x = (float) pos.x;
        mouse_pos.y = (float) pos.y;
        
        return ICE_MOUSE_TRUE;
    }
    
    return ICE_MOUSE_FALSE;;
}

// Deinitializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_close(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        ice_mouse_open = ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_TRUE;
}

// Returns current mouse position as 2D vector.
ICE_MOUSE_API ice_mouse_vec2 ICE_MOUSE_CALLCONV ice_mouse_pos(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return mouse_pos;
    }
    
    return (ice_mouse_vec2) { -1, -1 };
}

// Returns ICE_MOUSE_TRUE if mouse button is being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_down(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (next_state[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button is not being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_up(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (!next_state[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button pressed (Not "being" which means hold/down) or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_pressed(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (next_state[button] && next_state[button] != prev_state[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button released or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_released(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (!next_state[button] && next_state[button] != prev_state[button]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns mouse wheel delta as float.
ICE_MOUSE_API float ICE_MOUSE_CALLCONV ice_mouse_wheel(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return wy;
    }
    
    return 0;
}

#elif defined(ICE_MOUSE_WEB)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_MOUSE_WEB IMPLEMENTATION       (Web - Emscripten)
///////////////////////////////////////////////////////////////////////////////////////////
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

EmscriptenMouseEvent prev_ev;
EmscriptenMouseEvent next_ev;
float wy = 0;

EM_BOOL wheel_event(int eventType, const EmscriptenWheelEvent *ev, void *userData) {
    wy = (float) ev.deltaY;
}

// Sets which window will handle input by ice_mouse (Designed for Windows but returns ICE_MOUSE_TRUE on other-platforms).
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_set_window_handle(void* window) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        ice_mouse_open = ICE_MOUSE_TRUE;
    }
    
    return ice_mouse_open;
}

// Initializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_init(void) {
    if (ice_mouse_open == ICE_MOUSE_FALSE) {
        ice_mouse_open = ICE_MOUSE_TRUE;
    }
    
    return ice_mouse_open;
}

// Updates mouse input, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_update(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        prev_ev = next_ev;
    
        if (emscripten_get_mouse_status(&next_ev) != EMSCRIPTEN_RESULT_SUCCESS) {
            return ICE_MOUSE_FALSE;
        }
    
        if (emscripten_set_wheel_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, EM_FALSE, wheel_event) != EMSCRIPTEN_RESULT_SUCCESS) {
            return ICE_MOUSE_FALSE;
        }
    
        return ICE_MOUSE_TRUE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Deinitializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_close(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        ice_mouse_open = ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_TRUE;
}

// Returns current mouse position as 2D vector.
ICE_MOUSE_API ice_mouse_vec2 ICE_MOUSE_CALLCONV ice_mouse_pos(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return (ice_mouse_vec2) { (float) next_ev.clientX, (float) next_ev.clientY };
    }
    
    return (ice_mouse_vec2) { -1, -1 };
}

// [DEV] Returns button code depending on enum...
unsigned int ice_mouse_button_code(ice_mouse_button button) {
    unsigned int list[3] = { 0, 2, 1 };
    return list[button];
}

// Returns ICE_MOUSE_TRUE if mouse button is being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_down(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        unsigned int btn = ice_mouse_button_code(button);
        return (next_ev.button == btn) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button is not being pressed or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_up(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        unsigned int btn = ice_mouse_button_code(button);
        return (next_ev.button != btn) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button pressed (Not "being" which means hold/down) or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_pressed(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        unsigned int btn = ice_mouse_button_code(button);
        return (next_ev.button == btn && next_ev.button != prev_ev.button) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns ICE_MOUSE_TRUE if mouse button released or ICE_MOUSE_FALSE if not.
ICE_MOUSE_API ice_mouse_bool ICE_MOUSE_CALLCONV ice_mouse_button_released(ice_mouse_button button) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        unsigned int btn = ice_mouse_button_code(button);
        return (next_ev.button != btn && next_ev.button != prev_ev.button) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
    }
    
    return ICE_MOUSE_FALSE;
}

// Returns mouse wheel delta as float.
ICE_MOUSE_API float ICE_MOUSE_CALLCONV ice_mouse_wheel(void) {
    if (ice_mouse_open == ICE_MOUSE_TRUE) {
        return wy;
    }
    
    return 0;
}

#endif

#endif // ICE_MOUSE_IMPL
#endif // ICE_MOUSE_H
