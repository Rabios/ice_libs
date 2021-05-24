// Written by Rabia Alhaffar in 7/March/2021
// ice_joy.h
// Single-Header Cross-Platform Gamepad/Joystick input library written in C!
// Updated: 25/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_joy.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
Most platforms had different gamepad implementation for each platform, Which makes it hard to have unified API for each of them.

Gainput still available as C++ gamepad input lib, But developer left work on it, Plus
it's issues and the lack of platforms supported (Does not support few platforms).
 
ice_joy was created to cover this issues, ice_joy is written in C (Non Apple), C++ (Haiku, BeOS), and
Objective-C (Apple platforms), Despite being easy to deploy games which use it to any platform supports gamepad input as possible.

ice_joy provides unified API for Gamepads/Joysticks for supported platforms!

[2] IMPLEMENTATION:

////////////////////////////////////////////////////////////////////////////////////////////////////////
//           Platform               |     Backends     |            Platform Definition Used
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Microsoft Windows                       XInput                       ICE_JOY_MICROSOFT
// Microsoft Xbox 360                      XInput                       ICE_JOY_MICROSOFT
// Microsoft Xbox ONE                      XInput                       ICE_JOY_MICROSOFT
// Linux                             <linux/joystick.h>                 ICE_JOY_LINUX
// Apple OSX                            GCController                    ICE_JOY_APPLE
// Apple TV                             GCController                    ICE_JOY_APPLE
// Apple iOS                            GCController                    ICE_JOY_APPLE
// Google Android                     <android/input.h>                 ICE_JOY_ANDROID
// HTML5                                 Emscripten                     ICE_JOY_WEB
// Nintendo Switch                         libnx                        ICE_JOY_SWITCH
// Nintendo Wii                            libogc                       ICE_JOY_WII
// Nintendo Wii-U                          libogc                       ICE_JOY_WII
// Nintendo GameCube                       libogc                       ICE_JOY_GAMECUBE
// Nintendo 3DS                            libctru                      ICE_JOY_3DS
// Nintendo DS                             libnds                       ICE_JOY_NDS
// Sony PlayStation Portable               pspsdk                       ICE_JOY_PSP
// Sony PlayStation Vita                   vitasdk                      ICE_JOY_PSVITA
// Sony PlayStation                      PSY-Q's SDK                    ICE_JOY_PS1
// Sony PlayStation 2                      ps2sdk                       ICE_JOY_PS2
// Sony PlayStation 3                      PSL1GHT                      ICE_JOY_PS3
// Sony PlayStation 4                     OpenOrbis                     ICE_JOY_PS4
// Haiku                                  BJoystick                     ICE_JOY_BEOS
// BeOS                                   BJoystick                     ICE_JOY_BEOS

[3] USAGE:
Define ICE_JOY_IMPL then include ice_joy.h in your C/C++ code!

Take look at samples to see how to use it...

[4] ANDROID IMPLEMENTATION NOTES:
If you have 2 functions for Android command events and Android input events...
Add #define ICE_JOY_ANDROID_CUSTOM_INPUT_EVENT_HANDLERS then define 2 functions like this way:

#define ANDROID_CMD_HANDLE_FUNC     android_cmd_handling_func_name    // Once loop, ice_joy will call it inside command event function
#define ANDROID_INPUT_HANDLE_FUNC   android_input_handling_func_name  // Once loop, ice_joy will call it inside input events function

NOTE: Include ice_joy.h after doing this step if you're on Android!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// ice_joy IMPLEMENTATION NOTES
///////////////////////////////////////////////////////////////////////////////////////////
/*
1. If platform only supports one controller (Ex. ICE_JOY_PSP), The only available index to use is 0.

2. If platform's controller only supports only one analog, index 0 will map to it, Else If platform's controller does not support analogs, It will return vector2 as 0, 0

3. If platform's controller does not support some buttons, ice_joy_button_<state> functions will return ICE_JOY_FALSE when checking buttons states.
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_joy
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_joy by possibly one of following things:
//
// 1. Test ice_joy on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_joy LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_joy is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_JOY_H
#define ICE_JOY_H

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
#  if defined(ICE_JOY_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_JOY_CALLCONV_FASTCALL)
#    define ICE_JOY_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_JOY_CALLCONV_STDCALL)
#    define ICE_JOY_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_JOY_CALLCONV_CDECL)
#    define ICE_JOY_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_JOY_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_JOY_CALLCONV_VECTORCALL)
#    define ICE_JOY_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_JOY_CALLCONV_FASTCALL)
#    define ICE_JOY_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_JOY_CALLCONV_STDCALL)
#    define ICE_JOY_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_JOY_CALLCONV_CDECL)
#    define ICE_JOY_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_JOY_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_JOY_CALLCONV_VECTORCALL)
#    define ICE_JOY_CALLCONV __vectorcall
#  elif defined(ICE_JOY_CALLCONV_FASTCALL)
#    define ICE_JOY_CALLCONV __fastcall
#  elif defined(ICE_JOY_CALLCONV_STDCALL)
#    define ICE_JOY_CALLCONV __stdcall
#  elif defined(ICE_JOY_CALLCONV_CDECL)
#    define ICE_JOY_CALLCONV __cdecl
#  else
#    define ICE_JOY_CALLCONV
#  endif
#else
#  define ICE_JOY_CALLCONV
#endif

// Autodetect platform if not defined!
// If no platform defined, This definition will define itself.
#if !defined(ICE_JOY_MICROSOFT) && !defined(ICE_JOY_LINUX) && !defined(ICE_JOY_BSD) && !defined(ICE_JOY_APPLE) && !defined(ICE_JOY_ANDROID) && !defined(ICE_JOY_WEB) && !defined(ICE_JOY_SWITCH) && !defined(ICE_JOY_3DS) && !defined(ICE_JOY_PSP) && !defined(ICE_JOY_PSVITA) && !defined(ICE_JOY_PS1) && !defined(ICE_JOY_PS2) && !defined(ICE_JOY_PS3) && !defined(ICE_JOY_PS4) && !defined(ICE_JOY_BEOS) && !defined(ICE_JOY_WII) && !defined(ICE_JOY_PSVITA) && !defined(ICE_JOY_GAMECUBE) && !defined(ICE_JOY_NDS)
#  define ICE_JOY_PLATFORM_AUTODETECTED
#endif

// ice_joy autodetection system (Huge but still worthy...)
#if defined(ICE_JOY_PLATFORM_AUTODETECTED)
#  if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#    define ICE_JOY_MICROSOFT
#  elif defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android)
#    define ICE_JOY_ANDROID
#  elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__DARWIN) || defined(_DARWIN)
#    define ICE_JOY_APPLE
#  elif defined(__EMSCRIPTEN__) || defined(__EMSCRIPTEN) || defined(EMSCRIPTEN)
#    define ICE_JOY_WEB
#  elif (defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)) || (defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU))
#    define ICE_JOY_BEOS
#  elif defined(_NDS) || defined(NDS) || defined(__NDS__) || defined (__NDS)
#    define ICE_JOY_NDS
#  elif defined(_3DS) || defined(__3DS__) || defined(__N3DS__)
#    define ICE_JOY_3DS
#  elif defined(__WII__) || defined(WIIU) || defined(WII) || defined(wiiu) || defined(wii) || defined(_WII) || defined(_WIIU) || defined(__WIIU__) || defined(__wii__) || defined(__wiiu__)
#    define ICE_JOY_WII
#  elif defined(__SWITCH__) || defined(NINTENDO_SWITCH) || defined(__NX__) || defined(_SWITCH)
#    define ICE_JOY_SWITCH
#  elif defined(GAMECUBE) || defined(__GAMECUBE__) || defined(__gamecube__)
#    define ICE_JOY_GAMECUBE
#  elif defined(__linux__) || defined(__LINUX__) || defined(LINUX) || defined(__LINUX) || defined(__linux) || defined(linux) && !(defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android))
#    define ICE_JOY_LINUX
#  elif defined(__PSX__) || defined(PS1) || defined(__psx__) || defined(__PSONE__) || defined(PLAYSTATION_1) || defined(__PSX) || defined(_PSX)
#    define ICE_JOY_PS1
#  elif defined(__PS2__) || defined(_PS2) || defined(PS2) || defined(PLAYSTATION_2)
#    define ICE_JOY_PS2
#  elif defined(__PS3__) || defined(_PS3) || defined(__PS3) || defined(PS3) || defined(PLAYSTATION3) || defined(__PSL1GHT__)
#    define ICE_JOY_PS3
#  elif defined(PS4) || defined(ORBIS) || defined(__PS4__) || defined(__ORBIS__) || defined(_PS4) || defined(__PS4) || defined(PLAYSTATION4)
#    define ICE_JOY_PS4
#  elif defined(PSP) || defined(__PSP__) || defined(__psp__) || defined(__PSP) || defined(_PSP)
#    define ICE_JOY_PSP
#  elif defined(_PSVITA) || defined(VITA) || defined(__vita__) || defined(__PSVITA) || defined(__VITA__) || defined(_PSVITA) || defined(SN_TARGET_PSP2) || defined(__PSV__) || defined(__psv__) || defined(_PSV) || defined(__PSVita__) || defined(__PSVita)
#    define ICE_JOY_PSVITA
#  endif
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_JOY_EXTERN) && defined(ICE_JOY_STATIC))
#  define ICE_JOY_EXTERN
#endif

#if defined(ICE_JOY_EXTERN)
#  define ICE_JOY_APIDEF extern
#elif defined(ICE_JOY_STATIC)
#  define ICE_JOY_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_JOY_INLINE to enable inline functionality.
#if defined(ICE_JOY_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_JOY_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_JOY_INLINEDEF inline
#  endif
#else
#  define ICE_JOY_INLINEDEF
#endif

// Allow to build DLL via ICE_JOY_DLLEXPORT or ICE_JOY_DLLIMPORT if desired!
// Else, Just define API as extern C code!
#if defined(ICE_JOY_MICROSOFT)
#  if defined(ICE_JOY_DLLEXPORT)
#    define ICE_JOY_API __declspec(dllexport) ICE_JOY_INLINEDEF
#  elif defined(ICE_JOY_DLLIMPORT)
#    define ICE_JOY_API __declspec(dllimport) ICE_JOY_INLINEDEF
#  else
#    define ICE_JOY_API ICE_JOY_APIDEF ICE_JOY_INLINEDEF
#  endif
#else
#  define ICE_JOY_API ICE_JOY_APIDEF ICE_JOY_INLINEDEF
#endif

// Haiku/BeOS can't work with C as the API written in C++, So we should use C++! :(
#if defined(ICE_JOY_BEOS)
#  if !defined(__cplusplus)
#    error "C++ compilation required for BeOS and Haiku!"
#  endif
#endif

// Custom memory allocators
#ifndef ICE_JOY_MALLOC
#  define ICE_JOY_MALLOC(sz) malloc(sz)
#endif
#ifndef ICE_JOY_CALLOC
#  define ICE_JOY_CALLOC(n, sz) calloc(n, sz)
#endif
#ifndef ICE_JOY_REALLOC
#  define ICE_JOY_REALLOC(ptr, sz) realloc(ptr, sz)
#endif
#ifndef ICE_JOY_FREE
#  define ICE_JOY_FREE(ptr) free(ptr)
#endif

#if defined(__cplusplus)
extern "C" {
#endif
///////////////////////////////////////////////////////////////////////////////////////////
// ice_joy DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
// Default limit of gamepads/joysticks!
// NOTE: Changing this variable could affects functionality in some backends!
#ifndef ICE_JOY_JOYSTICKS
#  define ICE_JOY_JOYSTICKS 4
#endif

typedef enum {
    ICE_JOY_TRUE    = 0,
    ICE_JOY_FALSE   = -1,
} ice_joy_bool;

typedef enum {
    ICE_JOY_MOVE_ANALOG,
    ICE_JOY_CAMERA_ANALOG,
} ice_joy_analog;

typedef enum {
    ICE_JOY_PLAYER1,
    ICE_JOY_PLAYER2,
    ICE_JOY_PLAYER3,
    ICE_JOY_PLAYER4,
} ice_joy_player;

typedef enum {
    ICE_JOY_NONE        = -1,
    ICE_JOY_A           = 0,
    ICE_JOY_B           = 1,
    ICE_JOY_X           = 2,
    ICE_JOY_Y           = 3,
    ICE_JOY_CROSS       = 0,
    ICE_JOY_CIRCLE      = 1,
    ICE_JOY_SQUARE      = 2,
    ICE_JOY_TRIANGLE    = 3,
    ICE_JOY_LB          = 4,
    ICE_JOY_RB          = 5,
    ICE_JOY_LT          = 6,
    ICE_JOY_RT          = 7,
    ICE_JOY_L1          = 4,
    ICE_JOY_R1          = 5,
    ICE_JOY_L2          = 6,
    ICE_JOY_R2          = 7,
    ICE_JOY_OPTIONS     = 9,
    ICE_JOY_START       = 9,
    ICE_JOY_L3          = 10,
    ICE_JOY_R3          = 11,
    ICE_JOY_BACK        = 8,
    ICE_JOY_VIEW        = 8,
    ICE_JOY_MENU        = 9,
    ICE_JOY_SELECT      = 8,
    ICE_JOY_UP          = 12,
    ICE_JOY_DOWN        = 13,
    ICE_JOY_LEFT        = 14,
    ICE_JOY_RIGHT       = 15,
} ice_joy_button;

typedef enum {
    ICE_JOY_HAT_CENTERED,
    ICE_JOY_HAT_UP,
    ICE_JOY_HAT_UP_RIGHT,
    ICE_JOY_HAT_RIGHT,
    ICE_JOY_HAT_DOWN_RIGHT,
    ICE_JOY_HAT_DOWN,
    ICE_JOY_HAT_DOWN_LEFT,
    ICE_JOY_HAT_LEFT,
    ICE_JOY_HAT_UP_LEFT,
} ice_joy_hat;

typedef struct ice_joy_vec2 {
    float x;
    float y;
} ice_joy_vec2;

typedef char* ice_joy_str;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_joy FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
// Connection, Misc, etc...
ICE_JOY_API  ice_joy_bool  ICE_JOY_CALLCONV  ice_joy_init(void);                                                             // Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API  ice_joy_bool  ICE_JOY_CALLCONV  ice_joy_connected(ice_joy_player index);                                        // Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API  int           ICE_JOY_CALLCONV  ice_joy_joysticks_count(void);                                                  // Returns count of current connected Joysticks as integer.
ICE_JOY_API  ice_joy_str   ICE_JOY_CALLCONV  ice_joy_name(ice_joy_player index);                                             // Returns Joystick's name at index index as string.
ICE_JOY_API  ice_joy_bool  ICE_JOY_CALLCONV  ice_joy_update(ice_joy_player index);                                           // Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API  int           ICE_JOY_CALLCONV  ice_joy_axis_count(ice_joy_player index);                                       // Returns count of axes in Joystick at index index as integer.
ICE_JOY_API  int           ICE_JOY_CALLCONV  ice_joy_buttons_count(ice_joy_player index);                                    // Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API  ice_joy_bool  ICE_JOY_CALLCONV  ice_joy_close(void);                                                            // Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.

// Buttons
ICE_JOY_API  int           ICE_JOY_CALLCONV  ice_joy_button_code(ice_joy_button button);                                    // Returns button value by button enum definition as integer.
ICE_JOY_API  ice_joy_bool  ICE_JOY_CALLCONV  ice_joy_button_down(ice_joy_player index, ice_joy_button button);               // Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API  ice_joy_bool  ICE_JOY_CALLCONV  ice_joy_button_up(ice_joy_player index, ice_joy_button button);                 // Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API  ice_joy_bool  ICE_JOY_CALLCONV  ice_joy_button_pressed(ice_joy_player index, ice_joy_button button);            // Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API  ice_joy_bool  ICE_JOY_CALLCONV  ice_joy_button_released(ice_joy_player index, ice_joy_button button);           // Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.

// Analogs and Hats
ICE_JOY_API  ice_joy_vec2  ICE_JOY_CALLCONV  ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog);           // Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API  ice_joy_bool  ICE_JOY_CALLCONV  ice_joy_hat_pressed(ice_joy_player index, ice_joy_hat hat);                     // Returns ICE_JOY_TRUE if Hat is pressed or ICE_JOY_FALSE if not.

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_joy IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_JOY_IMPL)

ice_joy_bool ice_joy_open = ICE_JOY_FALSE;

#if defined(ICE_JOY_PS4)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_PS4 IMPLEMENTATION  (Sony PlayStation 4 - OpenOrbis SDK)
///////////////////////////////////////////////////////////////////////////////////////////
#include <orbis/UserService.h>
#include <orbis/Pad.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE                 -1
#define ICE_JOY_BUTTON_A                    ORBIS_PAD_BUTTON_CROSS
#define ICE_JOY_BUTTON_B                    ORBIS_PAD_BUTTON_CIRCLE
#define ICE_JOY_BUTTON_X                    ORBIS_PAD_BUTTON_SQUARE
#define ICE_JOY_BUTTON_Y                    ORBIS_PAD_BUTTON_TRIANGLE
#define ICE_JOY_BUTTON_CROSS                ORBIS_PAD_BUTTON_CROSS
#define ICE_JOY_BUTTON_CIRCLE               ORBIS_PAD_BUTTON_CIRCLE
#define ICE_JOY_BUTTON_SQUARE               ORBIS_PAD_BUTTON_SQUARE
#define ICE_JOY_BUTTON_TRIANGLE             ORBIS_PAD_BUTTON_TRIANGLE
#define ICE_JOY_BUTTON_LB                   ORBIS_PAD_BUTTON_L1
#define ICE_JOY_BUTTON_RB                   ORBIS_PAD_BUTTON_R1
#define ICE_JOY_BUTTON_LT                   ORBIS_PAD_BUTTON_L2
#define ICE_JOY_BUTTON_RT                   ORBIS_PAD_BUTTON_R2
#define ICE_JOY_BUTTON_L1                   ORBIS_PAD_BUTTON_L1         
#define ICE_JOY_BUTTON_R1                   ORBIS_PAD_BUTTON_R1
#define ICE_JOY_BUTTON_L2                   ORBIS_PAD_BUTTON_L2
#define ICE_JOY_BUTTON_R2                   ORBIS_PAD_BUTTON_R2
#define ICE_JOY_BUTTON_L3                   ORBIS_PAD_BUTTON_L3
#define ICE_JOY_BUTTON_R3                   ORBIS_PAD_BUTTON_R3
#define ICE_JOY_BUTTON_OPTIONS              ORBIS_PAD_BUTTON_OPTIONS
#define ICE_JOY_BUTTON_START                ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_BACK                 ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_VIEW                 ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_MENU                 ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_SELECT               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_DPAD_UP              ORBIS_PAD_BUTTON_UP
#define ICE_JOY_BUTTON_DPAD_DOWN            ORBIS_PAD_BUTTON_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT            ORBIS_PAD_BUTTON_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT           ORBIS_PAD_BUTTON_RIGHT

typedef struct ice_joy_state {
    int id;
    int pad;
    int previous;
    int current;
    OrbisPadData data;
} ice_joy_state;

OrbisUserServiceLoginUserIdList ice_joy_ids;
ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        OrbisUserServiceInitializeParams params;
        params.priority = ORBIS_KERNEL_PRIO_FIFO_LOWEST;

        if (sceUserServiceInitialize(&params) != 0) {
            ice_joy_open = ICE_JOY_FALSE;
            return ice_joy_open;
        }

        if (sceUserServiceGetLoginUserIdList(&ice_joy_ids) != 0) {
            ice_joy_open = ICE_JOY_FALSE;
            return ice_joy_open;
        }

        if (scePadInit() != 0) {
            ice_joy_open = ICE_JOY_FALSE;
            return ice_joy_open;
        }
    
        ice_joy_open = ICE_JOY_TRUE;
        return ice_joy_open;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].pad = scePadOpen(ice_joy_ids[index], 0, 0, NULL);
        return (pad < 0) ? ICE_JOY_FALSE : ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int count = 0;
    
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            if (scePadOpen(index, 0, 0, NULL) == 0) {
                count++;
            } else {
                break;
            }
        }
    
        return count;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "SONY PLAYSTATION DUALSHOCK 4 CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].previous = ice_joy_states[index].current;
    
        if (scePadReadState(ice_joy_states[index].pad, &ice_joy_states[index].padData) != 0) {
            return ICE_JOY_FALSE;
        }
    
        ice_joy_states[index].current = ice_joy_states[index].padData.buttons;
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6;     // Default by Dualshock 4!
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 15;    // Default by OpenOrbis!
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        for (int i = 0; i < ice_joy_joysticks_count(); i++) {
            if (scePadClose(ice_joy_states[i].pad) != 0) {
                ice_joy_open = ICE_JOY_TRUE;
                break;
            } else {
                ice_joy_open = ICE_JOY_FALSE;
            }
        }
        
        return (ice_joy_open == ICE_JOY_FALSE) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].current & button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_states[index].current & button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].current & button) && (ice_joy_states[index].current != ice_joy_states[index].previous)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(ice_joy_states[index].current & button)) && (ice_joy_states[index].current != ice_joy_states[index].previous)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                ice_joy_states[index].padData.rightStick.x,
                ice_joy_states[index].padData.rightStick.y,
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                ice_joy_states[index].padData.leftStick.x,
                ice_joy_states[index].padData.leftStick.y,
            };
        } else {
            return (ice_joy_vec2) { 0, 0 };
        }
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_PS3)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_PS3 IMPLEMENTATION  (Sony PlayStation 3 - PSL1GHT SDK)
///////////////////////////////////////////////////////////////////////////////////////////
#include <io/pad.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE                 -1
#define ICE_JOY_BUTTON_A                    0
#define ICE_JOY_BUTTON_B                    1
#define ICE_JOY_BUTTON_X                    2
#define ICE_JOY_BUTTON_Y                    3
#define ICE_JOY_BUTTON_CROSS                ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE               ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE               ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE             ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB                   4
#define ICE_JOY_BUTTON_RB                   5
#define ICE_JOY_BUTTON_LT                   6
#define ICE_JOY_BUTTON_RT                   7
#define ICE_JOY_BUTTON_L1                   ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1                   ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2                   ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2                   ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3                   10
#define ICE_JOY_BUTTON_R3                   11
#define ICE_JOY_BUTTON_START                9
#define ICE_JOY_BUTTON_MENU                 ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS              ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT               8
#define ICE_JOY_BUTTON_BACK                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP              12
#define ICE_JOY_BUTTON_DPAD_DOWN            13
#define ICE_JOY_BUTTON_DPAD_LEFT            14
#define ICE_JOY_BUTTON_DPAD_RIGHT           15

PadInfo padinfo;

typedef struct ice_joy_state {
    PadData previous;
    PadData current;
} ice_joy_state;

ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        ice_joy_open = (ioPadInit(ICE_JOY_JOYSTICKS - 1) == 0) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        return ice_joy_open;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (ioPadGetInfo(&padinfo) == 0) {
            return ((!(index < 0)) && index <= padinfo.connected - 1);
        } else {
            return ICE_JOY_FALSE;
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (ioPadGetInfo(&padinfo) == 0) {
            return padinfo.connected;
        } else {
            return 0;
        }
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "SONY PLAYSTATION DUALSHOCK 3 CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].previous = ice_joy_states[index].current;
    
        if (ioPadGetData(index, &ice_joy_states[index].current) == 0) {
            return ICE_JOY_TRUE;
        }
    
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6;   // NOTE: PS3 controller has six-axis rule!
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 18;  // NOTE: Reserved buttons also counted...
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = (ioPadEnd() == 0) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        return ice_joy_open;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        
        static int buttons_down[16] = {
            ice_joy_states[index].current.BTN_CROSS,
            ice_joy_states[index].current.BTN_CIRCLE,
            ice_joy_states[index].current.BTN_SQUARE,
            ice_joy_states[index].current.BTN_TRIANGLE,
            ice_joy_states[index].current.BTN_LB,
            ice_joy_states[index].current.BTN_RB,
            ice_joy_states[index].current.BTN_LT,
            ice_joy_states[index].current.BTN_RT,
            ice_joy_states[index].current.BTN_L3,
            ice_joy_states[index].current.BTN_R3,
            ice_joy_states[index].current.BTN_START,
            ice_joy_states[index].current.BTN_SELECT,
            ice_joy_states[index].current.BTN_UP,
            ice_joy_states[index].current.BTN_DOWN,
            ice_joy_states[index].current.BTN_LEFT,
            ice_joy_states[index].current.BTN_RIGHT,
        };
    
        return (buttons_down[button]) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        
        static int buttons_down[16] = {
            ice_joy_states[index].current.BTN_CROSS,
            ice_joy_states[index].current.BTN_CIRCLE,
            ice_joy_states[index].current.BTN_SQUARE,
            ice_joy_states[index].current.BTN_TRIANGLE,
            ice_joy_states[index].current.BTN_LB,
            ice_joy_states[index].current.BTN_RB,
            ice_joy_states[index].current.BTN_LT,
            ice_joy_states[index].current.BTN_RT,
            ice_joy_states[index].current.BTN_L3,
            ice_joy_states[index].current.BTN_R3,
            ice_joy_states[index].current.BTN_START,
            ice_joy_states[index].current.BTN_SELECT,
            ice_joy_states[index].current.BTN_UP,
            ice_joy_states[index].current.BTN_DOWN,
            ice_joy_states[index].current.BTN_LEFT,
            ice_joy_states[index].current.BTN_RIGHT,
        };
    
        return (!buttons_down[button]) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        
        static int buttons_down[16] = {
            ice_joy_states[index].current.BTN_CROSS,
            ice_joy_states[index].current.BTN_CIRCLE,
            ice_joy_states[index].current.BTN_SQUARE,
            ice_joy_states[index].current.BTN_TRIANGLE,
            ice_joy_states[index].current.BTN_LB,
            ice_joy_states[index].current.BTN_RB,
            ice_joy_states[index].current.BTN_LT,
            ice_joy_states[index].current.BTN_RT,
            ice_joy_states[index].current.BTN_L3,
            ice_joy_states[index].current.BTN_R3,
            ice_joy_states[index].current.BTN_START,
            ice_joy_states[index].current.BTN_SELECT,
            ice_joy_states[index].current.BTN_UP,
            ice_joy_states[index].current.BTN_DOWN,
            ice_joy_states[index].current.BTN_LEFT,
            ice_joy_states[index].current.BTN_RIGHT,
        };
    
        static int buttons_up[16] = {
            ice_joy_states[index].previous.BTN_CROSS,
            ice_joy_states[index].previous.BTN_CIRCLE,
            ice_joy_states[index].previous.BTN_SQUARE,
            ice_joy_states[index].previous.BTN_TRIANGLE,
            ice_joy_states[index].previous.BTN_LB,
            ice_joy_states[index].previous.BTN_RB,
            ice_joy_states[index].previous.BTN_LT,
            ice_joy_states[index].previous.BTN_RT,
            ice_joy_states[index].previous.BTN_L3,
            ice_joy_states[index].previous.BTN_R3,
            ice_joy_states[index].previous.BTN_START,
            ice_joy_states[index].previous.BTN_SELECT,
            ice_joy_states[index].previous.BTN_UP,
            ice_joy_states[index].previous.BTN_DOWN,
            ice_joy_states[index].previous.BTN_LEFT,
            ice_joy_states[index].previous.BTN_RIGHT,
        };
    
        return (buttons_down[button] && (buttons_down[button] != buttons_up[button])) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        
        static int buttons_down[16] = {
            ice_joy_states[index].current.BTN_CROSS,
            ice_joy_states[index].current.BTN_CIRCLE,
            ice_joy_states[index].current.BTN_SQUARE,
            ice_joy_states[index].current.BTN_TRIANGLE,
            ice_joy_states[index].current.BTN_LB,
            ice_joy_states[index].current.BTN_RB,
            ice_joy_states[index].current.BTN_LT,
            ice_joy_states[index].current.BTN_RT,
            ice_joy_states[index].current.BTN_L3,
            ice_joy_states[index].current.BTN_R3,
            ice_joy_states[index].current.BTN_START,
            ice_joy_states[index].current.BTN_SELECT,
            ice_joy_states[index].current.BTN_UP,
            ice_joy_states[index].current.BTN_DOWN,
            ice_joy_states[index].current.BTN_LEFT,
            ice_joy_states[index].current.BTN_RIGHT,
        };
    
        static int buttons_up[16] = {
            ice_joy_states[index].previous.BTN_CROSS,
            ice_joy_states[index].previous.BTN_CIRCLE,
            ice_joy_states[index].previous.BTN_SQUARE,
            ice_joy_states[index].previous.BTN_TRIANGLE,
            ice_joy_states[index].previous.BTN_LB,
            ice_joy_states[index].previous.BTN_RB,
            ice_joy_states[index].previous.BTN_LT,
            ice_joy_states[index].previous.BTN_RT,
            ice_joy_states[index].previous.BTN_L3,
            ice_joy_states[index].previous.BTN_R3,
            ice_joy_states[index].previous.BTN_START,
            ice_joy_states[index].previous.BTN_SELECT,
            ice_joy_states[index].previous.BTN_UP,
            ice_joy_states[index].previous.BTN_DOWN,
            ice_joy_states[index].previous.BTN_LEFT,
            ice_joy_states[index].previous.BTN_RIGHT,
        };
    
        return (!buttons_down[button] && (buttons_down[button] != buttons_up[button])) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                ice_joy_states[index].current.ANA_R_H,
                ice_joy_states[index].current.ANA_R_V,
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                ice_joy_states[index].current.ANA_L_H,
                ice_joy_states[index].current.ANA_L_V,
            };
        } else {
            return (ice_joy_vec2) { 0, 0 };
        }
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_PS2)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_PS2 IMPLEMENTATION  (Sony PlayStation 2 - PS2SDK)
///////////////////////////////////////////////////////////////////////////////////////////
#include <tamtypes.h>
#include <kernel.h>
#include <loadfile.h>
#include <libpad.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE             -1
#define ICE_JOY_BUTTON_A                PAD_CROSS
#define ICE_JOY_BUTTON_B                PAD_CIRCLE
#define ICE_JOY_BUTTON_X                PAD_SQUARE
#define ICE_JOY_BUTTON_Y                PAD_TRIANGLE
#define ICE_JOY_BUTTON_CROSS            ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE           ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE           ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE         ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB               PAD_L1
#define ICE_JOY_BUTTON_RB               PAD_R1
#define ICE_JOY_BUTTON_LT               PAD_L2
#define ICE_JOY_BUTTON_RT               PAD_R2
#define ICE_JOY_BUTTON_L1               ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1               ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2               ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2               ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3               PAD_L3
#define ICE_JOY_BUTTON_R3               PAD_R3
#define ICE_JOY_BUTTON_START            PAD_START
#define ICE_JOY_BUTTON_MENU             ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS          ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT           PAD_SELECT
#define ICE_JOY_BUTTON_BACK             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP          PAD_UP
#define ICE_JOY_BUTTON_DPAD_DOWN        PAD_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT        PAD_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT       PAD_RIGHT

typedef struct ice_joy_info {
    char buf[256] __attribute__((aligned(64)));
    struct padButtonStatus buttons;
    u32 data;
    u32 padbuttons;
} ice_joy_info;

typedef struct ice_joy_state {
    ice_joy_info prev;
    ice_joy_info next;
} ice_joy_state;

ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        if (SifLoadModule("rom0:SIO2MAN", 0, NULL) < 0) {
            ice_joy_open = ICE_JOY_FALSE;
            return ice_joy_open;
        }
    
        if (SifLoadModule("rom0:PADMAN", 0, NULL) < 0) {
            ice_joy_open = ICE_JOY_FALSE;
            return ice_joy_open;
        }
        
        ice_joy_open = (padInit(0)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        return ice_joy_open;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (!padPortOpen(index, 0, ice_joy_states[index].next.buf)) {
            return ICE_JOY_FALSE;
        }
    
        int ret = padGetState(index, 0);
        
        if (ret == PAD_STATE_STABLE && ret == PAD_STATE_FINDCTP1) {
            return (ret == PAD_STATE_DISCONN) ? ICE_JOY_FALSE : ICE_JOY_TRUE;
        } else {
            return ICE_JOY_TRUE;
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int count = 0;
    
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            if (ice_joy_connected(i) == ICE_JOY_TRUE) {
                count++;
            }
        }
    
        return count;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "SONY PLAYSTATION DUALSHOCK 2 CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (padRead(index, 0, &ice_joy_states[index].next.buttons) != 0) {
            ice_joy_states[index].next.data = 0xffff ^ ice_joy_states[index].next.buttons.btns;
            ice_joy_states[index].next.padbuttons = ice_joy_states[index].next.data & ~ice_joy_states[index].prev.padbuttons;
            ice_joy_states[index].prev.padbuttons = ice_joy_states[index].next.data;
        
            return ICE_JOY_TRUE;
        }
    
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 16;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = (padEnd()) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        return ice_joy_open;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].next.padbuttons & button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_states[index].next.padbuttons & button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].next.padbuttons & button) && (ice_joy_states[index].next.padbuttons != ice_joy_states[index].prev.padbuttons)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(ice_joy_states[index].next.padbuttons & button)) && (ice_joy_states[index].next.padbuttons != ice_joy_states[index].prev.padbuttons)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                ice_joy_states[index].next.buttons.rjoy_h,
                ice_joy_states[index].next.buttons.rjoy_v,
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                ice_joy_states[index].next.buttons.ljoy_h,
                ice_joy_states[index].next.buttons.ljoy_v,
            };
        } else {
            return (ice_joy_vec2) { 0, 0 };
        }
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_PS1)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_PS1 IMPLEMENTATION  (Sony PlayStation 1 - PSY-Q's SDK)
///////////////////////////////////////////////////////////////////////////////////////////
#include <libetc.h>
#include <libpad.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE             -1
#define ICE_JOY_BUTTON_A                PADLdown
#define ICE_JOY_BUTTON_B                PADLleft
#define ICE_JOY_BUTTON_X                PADLright
#define ICE_JOY_BUTTON_Y                PADLup
#define ICE_JOY_BUTTON_CROSS            ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE           ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE           ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE         ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB               PADL1
#define ICE_JOY_BUTTON_RB               PADR1
#define ICE_JOY_BUTTON_LT               PADL2
#define ICE_JOY_BUTTON_RT               PADR2
#define ICE_JOY_BUTTON_L1               ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1               ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2               ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2               ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_R3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_START            PADstart
#define ICE_JOY_BUTTON_MENU             ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS          ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT           PADselect
#define ICE_JOY_BUTTON_BACK             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP          PADRup
#define ICE_JOY_BUTTON_DPAD_DOWN        PADRdown
#define ICE_JOY_BUTTON_DPAD_LEFT        PADRleft
#define ICE_JOY_BUTTON_DPAD_RIGHT       PADRright

typedef struct ice_joy_state {
    int prev;
    int next;
} ice_joy_state;

ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        return (PadInit(ICE_JOY_JOYSTICKS - 1) == 0) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return (PadRead(index) != NULL) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int count = 0;
    
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            if (PadRead(index) != NULL) {
                count++;
            } else {
                break;
            }
        }
    
        return count;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "SONY PLAYSTATION DUALSHOCK CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].prev = ice_joy_states[index].next;
        int state = PadRead(index);
    
        if (state != NULL) {
            ice_joy_states[index].next = state;
            return ICE_JOY_TRUE;
        }
    
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 14;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        PadStop();
        ice_joy_open = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].next & button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_states[index].next & button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].next & button) && (ice_joy_states[index].next != ice_joy_states[index].prev)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(ice_joy_states[index].next & button)) && (ice_joy_states[index].next != ice_joy_states[index].prev)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    return (ice_joy_vec2) { 0, 0 }; // I did this cause there is no function for Analog Movement even on original SDK
}

#elif defined(ICE_JOY_APPLE)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_APPLE IMPLEMENTATION  (Apple Devices - GameController)
///////////////////////////////////////////////////////////////////////////////////////////
#import <Foundation/Foundation.h>
#import <GameController/GameController.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE                 -1
#define ICE_JOY_BUTTON_A                    0
#define ICE_JOY_BUTTON_B                    1
#define ICE_JOY_BUTTON_X                    2
#define ICE_JOY_BUTTON_Y                    3
#define ICE_JOY_BUTTON_CROSS                ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE               ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE               ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE             ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB                   4
#define ICE_JOY_BUTTON_RB                   5
#define ICE_JOY_BUTTON_LT                   6
#define ICE_JOY_BUTTON_RT                   7
#define ICE_JOY_BUTTON_L1                   ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1                   ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2                   ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2                   ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3                   10
#define ICE_JOY_BUTTON_R3                   11
#define ICE_JOY_BUTTON_START                9
#define ICE_JOY_BUTTON_MENU                 ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS              ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT               8
#define ICE_JOY_BUTTON_BACK                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP              12
#define ICE_JOY_BUTTON_DPAD_DOWN            13
#define ICE_JOY_BUTTON_DPAD_LEFT            14
#define ICE_JOY_BUTTON_DPAD_RIGHT           15

typedef struct ice_joy_state {
    BOOL prev[16];
    BOOL next[16];
} ice_joy_state;

ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if ([[GCController controllers] count] > 0) {
            ice_joy_open = ([GCController controllers][0].extendedGamepad) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        }
        
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if ([GCController controllers][index]) {
            if (NSAssert([GCController controllers][index].extendedGamepad, @"ERROR: EXTENDED GAMEPAD PROFILE NOT SUPPORTED!") == YES) {
                return ICE_JOY_TRUE;
            } else {
                return ICE_JOY_FALSE;
            }
        }
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int len = (int)[[GCController controllers] count];
        return (len > ICE_JOY_JOYSTICKS) ? ICE_JOY_JOYSTICKS : len;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return strdup([[[GCController controllers][index] vendorName] UTF8String]);
    }
    
    return 0;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        for (int i = 0; i < 16; i++) {
            ice_joy_states[index].prev[i] = ice_joy_states[index].next[i];
        }
        
        GCExtendedGamepad* gamepad = [GCController controllers][index].extendedGamepad;
        ice_joy_states[index].next[ICE_JOY_BUTTON_A]            = gamepad.buttonA.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_B]            = gamepad.buttonB.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_X]            = gamepad.buttonX.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_Y]            = gamepad.buttonY.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_LB]           = gamepad.leftShoulder.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_RB]           = gamepad.rightShoulder.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_LT]           = gamepad.leftTrigger.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_RT]           = gamepad.rightTrigger.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_SELECT]       = gamepad.buttonOptions.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_START]        = gamepad.buttonMenu.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_L3]           = gamepad.leftThumbstickButton.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_R3]           = gamepad.rightThumbstickButton.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_DPAD_UP]      = gamepad.dpad.up.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_DPAD_DOWN]    = gamepad.dpad.down.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_DPAD_LEFT]    = gamepad.dpad.left.pressed;
        ice_joy_states[index].next[ICE_JOY_BUTTON_DPAD_RIGHT]   = gamepad.dpad.right.pressed;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return (int)[[GCController controllers][index].extendedGamepad.allAxes count];
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return (int)[[GCController controllers][index].extendedGamepad.allButtons count];
    }
    
    return ICE_JOY_FALSE;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].next[button] == YES) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].next[button] != YES) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].next[button] == YES) && (ice_joy_states[index].next[button] != ice_joy_states[index].prev[button])) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].next[button] != YES) && (ice_joy_states[index].next[button] != ice_joy_states[index].prev[button])) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        GCExtendedGamepad* gamepad = [GCController controllers][index].extendedGamepad;
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                gamepad.rightThumbstick.xAxis.value,
                gamepad.rightThumbstick.yAxis.value,
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                gamepad.leftThumbstick.xAxis.value,
                gamepad.leftThumbstick.yAxis.value,
            };
        }
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_ANDROID)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_ANDROID IMPLEMENTATION  (Android - Android NDK)
///////////////////////////////////////////////////////////////////////////////////////////
#include <android_native_app_glue.h>
#include <android/input.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE                 -1
#define ICE_JOY_BUTTON_A                    AKEYCODE_BUTTON_A
#define ICE_JOY_BUTTON_B                    AKEYCODE_BUTTON_B
#define ICE_JOY_BUTTON_X                    AKEYCODE_BUTTON_X
#define ICE_JOY_BUTTON_Y                    AKEYCODE_BUTTON_Y
#define ICE_JOY_BUTTON_CROSS                ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE               ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE               ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE             ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB                   AKEYCODE_BUTTON_L1
#define ICE_JOY_BUTTON_RB                   AKEYCODE_BUTTON_R1
#define ICE_JOY_BUTTON_LT                   AKEYCODE_BUTTON_L2
#define ICE_JOY_BUTTON_RT                   AKEYCODE_BUTTON_R2
#define ICE_JOY_BUTTON_L1                   AKEYCODE_BUTTON_L1
#define ICE_JOY_BUTTON_R1                   AKEYCODE_BUTTON_R1
#define ICE_JOY_BUTTON_L2                   AKEYCODE_BUTTON_L2
#define ICE_JOY_BUTTON_R2                   AKEYCODE_BUTTON_R2
#define ICE_JOY_BUTTON_L3                   AKEYCODE_BUTTON_THUMBL
#define ICE_JOY_BUTTON_R3                   AKEYCODE_BUTTON_THUMBR
#define ICE_JOY_BUTTON_START                AKEYCODE_BUTTON_START
#define ICE_JOY_BUTTON_MENU                 ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS              ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT               AKEYCODE_BUTTON_SELECT
#define ICE_JOY_BUTTON_BACK                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP              AKEYCODE_DPAD_UP
#define ICE_JOY_BUTTON_DPAD_DOWN            AKEYCODE_DPAD_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT            AKEYCODE_DPAD_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT           AKEYCODE_DPAD_RIGHT

int32_t prev_button;
int32_t next_button;
struct android_app* app;
struct android_poll_source *source;
int32_t android_cmd;
int poll_res = 0;
int poll_events = 0;
int joystick_event_type = 0;
ice_joy_bool android_app_joystick_connected = ICE_JOY_FALSE;
ice_joy_bool android_app_get_input = ICE_JOY_FALSE;
ice_joy_vec2 axes[2];

// Trick to run from android_main
extern int main(int argc, char *argv[]);

#if defined(ICE_JOY_ANDROID_CUSTOM_INPUT_EVENT_HANDLERS)
#  if defined(ANDROID_INPUT_HANDLE_FUNC)
#    define ANDROID_INPUT_HANDLE_FUNC_DEFINED
#  endif
#  if defined(ANDROID_CMD_HANDLE_FUNC)
#    define ANDROID_CMD_HANDLE_FUNC_DEFINED
#  endif
#endif

static int32_t ice_joy_input_callback(struct android_app *app, AInputEvent *event) {
    if (android_app_get_input == ICE_JOY_TRUE) {
#if defined(ANDROID_INPUT_HANDLE_FUNC_DEFINED)
        ANDROID_INPUT_HANDLE_FUNC(app, event);
#endif
        int type = AInputEvent_getType(event);
        int source = AInputEvent_getSource(event);
        
        if (type == AINPUT_EVENT_TYPE_KEY) {
            if (((source & AINPUT_SOURCE_JOYSTICK) == AINPUT_SOURCE_JOYSTICK) || ((source & AINPUT_SOURCE_GAMEPAD) == AINPUT_SOURCE_GAMEPAD)) {
                // Get input!
                int32_t btn = AKeyEvent_getKeyCode(event);
                prev_button = next_button;
                
                joystick_event_type = AKeyEvent_getAction(event);
                
                // Compare with AKEY_EVENT_ACTION_DOWN or AKEY_EVENT_ACTION_UP
                if (joystick_event_type == AKEY_EVENT_ACTION_DOWN) {
                    next_button = btn;
                }
                
                if ((keycode == AKEYCODE_POWER) || (keycode == AKEYCODE_VOLUME_UP) || (keycode == AKEYCODE_VOLUME_DOWN)) {
                    return 0;
                } else if ((keycode == AKEYCODE_BACK) || (keycode == AKEYCODE_MENU)) {
                    return -1;
                }
            }
        } else if (type == AINPUT_EVENT_TYPE_MOTION) {
            if (((source & AINPUT_SOURCE_JOYSTICK) == AINPUT_SOURCE_JOYSTICK) || ((source & AINPUT_SOURCE_GAMEPAD) == AINPUT_SOURCE_GAMEPAD)) {
                // Analogs movement...
                int32_t action = AMotionEvent_getAction(event);
                unsigned int flags = action & AMOTION_EVENT_ACTION_MASK;
                
                if (flags == AMOTION_EVENT_ACTION_DOWN || flags == AMOTION_EVENT_ACTION_MOVE || flags == AMOTION_EVENT_ACTION_UP) {
                    axes[0] = (ice_joy_vec2) {
                        AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_X, 0),
                        AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_Y, 0),
                    };
                
                    axes[1] = (ice_joy_vec2) {
                        AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_Z, 0),
                        AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_RZ, 0),
                    };
                }
            }
        }
        
        return 0;
    }
    
    return -1;
}

static int32_t ice_joy_cmd_callback(struct android_app *app, int32_t cmd) {
#if defined(ANDROID_CMD_HANDLE_FUNC_DEFINED)
    ANDROID_CMD_HANDLE_FUNC(app, cmd);
#endif
    if ((cmd == APP_CMD_PAUSE) || (cmd == APP_CMD_LOST_FOCUS) || (cmd == APP_CMD_STOP) || (cmd == APP_CMD_DESTROY) || (cmd == APP_CMD_TERM_WINDOW)) {
        android_app_get_input = ICE_JOY_FALSE;
    } else {
        if (cmd == APP_CMD_START) {
            android_app_get_input = ICE_JOY_FALSE;
        }
        
        if ((cmd == APP_CMD_GAINED_FOCUS) || (cmd == APP_CMD_RESUME)) {
            android_app_get_input = ICE_JOY_TRUE;
        }
        
        if (cmd == APP_CMD_INIT_WINDOW) {
            if (app->window != NULL) {
                android_app_get_input = ICE_JOY_TRUE;
            }
        } 
    }
    
    return 0;
}

void android_main(struct android_app *app) {
    struct engine engine{};
    memset(&engine, 0, sizeof(engine));
    app->userData = &engine;
    app->onInputEvent = ice_joy_input_callback;
    app->onAppCmd = ice_joy_cmd_callback;
    
    do {
        if (ALooper_pollAll(0, nullptr, &poll_events, (void **) &source) >= 0) {
            if (source) {
                source->process(app, source);
            }
        }
    } while (!app->destroyRequested);
    
    (void)main(1, (char *[]) { "ice_joy", NULL });
}

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        ice_joy_open = ICE_JOY_TRUE;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return android_app_get_input;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 1; // HACK: Is this possible to retrieve via JNI? \_o_/
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "GENERIC GAMEPAD CONTROLLER!"; // HACK: Is this possible to retrieve via JNI? \_o_/
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if ((poll_res = ALooper_pollAll(android_app_get_input, NULL, &poll_events, (void**)&source)) >= 0) {
            if (source != NULL) source->process(app, source);

            if (app->destroyRequested) {
                android_app_get_input = ICE_JOY_FALSE; // Don't close window but don't trigger input anymore!
            }
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6; // HACK: Is this possible to retrieve via JNI? \_o_/
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 16; // HACK: Is this possible to retrieve via JNI? \_o_/
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = ICE_JOY_FALSE;
        android_app_get_input = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (next_button == button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(next_button == button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((next_button == button) && (next_button != prev_button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(next_button == button)) && (next_button != prev_button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                axes[0].x,
                axes[0].y,
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                axes[1].x,
                axes[1].y,
            };
        } else {
            return (ice_joy_vec2) { 0, 0 };
        }
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_WEB)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_WEB IMPLEMENTATION  (Web - Emscripten)
///////////////////////////////////////////////////////////////////////////////////////////
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE                 -1
#define ICE_JOY_BUTTON_A                    0
#define ICE_JOY_BUTTON_B                    1
#define ICE_JOY_BUTTON_X                    2
#define ICE_JOY_BUTTON_Y                    3
#define ICE_JOY_BUTTON_CROSS                ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE               ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE               ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE             ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB                   4
#define ICE_JOY_BUTTON_RB                   5
#define ICE_JOY_BUTTON_LT                   6
#define ICE_JOY_BUTTON_RT                   7
#define ICE_JOY_BUTTON_L1                   ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1                   ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2                   ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2                   ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3                   10
#define ICE_JOY_BUTTON_R3                   11
#define ICE_JOY_BUTTON_START                9
#define ICE_JOY_BUTTON_MENU                 ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS              ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT               8
#define ICE_JOY_BUTTON_BACK                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP              12
#define ICE_JOY_BUTTON_DPAD_DOWN            13
#define ICE_JOY_BUTTON_DPAD_LEFT            14
#define ICE_JOY_BUTTON_DPAD_RIGHT           15

typedef struct ice_joy_state {
    EmscriptenGamepadEvent previous;
    EmscriptenGamepadEvent current;
} ice_joy_state;

ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        if (emscripten_sample_gamepad_data() == EMSCRIPTEN_RESULT_NOT_SUPPORTED) {
            ice_joy_open = ICE_JOY_FALSE;
        }
        
        ice_joy_open = ICE_JOY_TRUE;
        return ice_joy_open;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        EmscriptenGamepadEvent state;
    
        if (emscripten_sample_gamepad_data() == EMSCRIPTEN_RESULT_NOT_SUPPORTED) {
            return ICE_JOY_FALSE;
        }
    
        if (emscripten_get_gamepad_status(index, &state) == EMSCRIPTEN_RESULT_SUCCESS) {
            return (state.connected == EM_TRUE) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        }

        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (emscripten_sample_gamepad_data() == EMSCRIPTEN_RESULT_NOT_SUPPORTED) {
            return 0;
        }

        int result = emscripten_get_num_gamepads();
    
        if (result != EMSCRIPTEN_RESULT_NOT_SUPPORTED) {
            return result;
        } else {
            return 0;
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        EmscriptenGamepadEvent state;
        static char name[64];

        if (emscripten_sample_gamepad_data() == EMSCRIPTEN_RESULT_NOT_SUPPORTED) {
            return NULL;
        }

        if (emscripten_get_gamepad_status(index, &state) == EMSCRIPTEN_RESULT_SUCCESS) {
            for (int i = 0; i < 64; i++) name[i] = state.id[i];
            return name;
        }
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].previous = ice_joy_states[index].current;

        if (emscripten_sample_gamepad_data() == EMSCRIPTEN_RESULT_NOT_SUPPORTED) {
            return ICE_JOY_FALSE;
        }

        if (emscripten_get_gamepad_status(index, &ice_joy_states[index].current) == EMSCRIPTEN_RESULT_SUCCESS) {
            return ICE_JOY_TRUE;
        }
        
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        EmscriptenGamepadEvent state;

        if (emscripten_sample_gamepad_data() == EMSCRIPTEN_RESULT_NOT_SUPPORTED) {
            return 0;
        }

        if (emscripten_get_gamepad_status(index, &state) == EMSCRIPTEN_RESULT_SUCCESS) {
            return state.numAxes;
        }

        return 0;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        EmscriptenGamepadEvent state;

        if (emscripten_sample_gamepad_data() == EMSCRIPTEN_RESULT_NOT_SUPPORTED) {
            return 0;
        }

        if (emscripten_get_gamepad_status(index, &state) == EMSCRIPTEN_RESULT_SUCCESS) {
            return state.numButtons;
        }

        return 0;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = ICE_JOY_TRUE;
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].current.digitalButton[button] == EM_TRUE) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_states[index].current.digitalButton[button] == EM_TRUE)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].current.digitalButton[button] == EM_TRUE && ice_joy_states[index].previous.digitalButton[button] != ice_joy_states[index].current.digitalButton[button]) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].current.digitalButton[button] == EM_FALSE && ice_joy_states[index].previous.digitalButton[button] != ice_joy_states[index].current.digitalButton[button]) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        EmscriptenGamepadEvent state;

        if (emscripten_sample_gamepad_data() == EMSCRIPTEN_RESULT_NOT_SUPPORTED) {
            return (ice_joy_vec2) { 0, 0 };
        }

        if (emscripten_get_gamepad_status(index, &state) == EMSCRIPTEN_RESULT_SUCCESS) {
            if (analog == ICE_JOY_MOVE_ANALOG) {
                return (ice_joy_vec2) {
                    state.axis[2],
                    state.axis[3],
                };
            } else if (analog == ICE_JOY_CAMERA_ANALOG) {
                return (ice_joy_vec2) {
                    state.axis[0],
                    state.axis[1],
                };
            } else {
                return (ice_joy_vec2) { 0, 0 };
            }
        }
        
        return (ice_joy_vec2) { 0, 0 };
    }

    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_3DS)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_3DS IMPLEMENTATION  (Nintendo 3DS - libctru)
///////////////////////////////////////////////////////////////////////////////////////////
#include <3ds.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE             -1
#define ICE_JOY_BUTTON_A                KEY_A
#define ICE_JOY_BUTTON_B                KEY_B
#define ICE_JOY_BUTTON_X                KEY_X
#define ICE_JOY_BUTTON_Y                KEY_Y
#define ICE_JOY_BUTTON_CROSS            ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE           ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE           ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE         ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB               KEY_L
#define ICE_JOY_BUTTON_RB               KEY_R
#define ICE_JOY_BUTTON_LT               KEY_ZL
#define ICE_JOY_BUTTON_RT               KEY_ZR
#define ICE_JOY_BUTTON_L1               ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1               ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2               ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2               ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_R3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_START            KEY_START
#define ICE_JOY_BUTTON_MENU             ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS          ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT           KEY_SELECT
#define ICE_JOY_BUTTON_BACK             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP          KEY_UP
#define ICE_JOY_BUTTON_DPAD_DOWN        KEY_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT        KEY_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT       KEY_RIGHT

typedef struct ice_joy_state_info {
    u32 down;
    u32 up;
    u32 held;
} ice_joy_state_info;

typedef struct ice_joy_states {
    ice_joy_state_info prev;
    ice_joy_state_info next;
} ice_joy_states;

ice_joy_states ice_joy_state;
circlePosition pos;

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        ice_joy_open = ICE_JOY_TRUE;
    }
    
    return ice_joy_open;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 1;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "Nintendo 3DS Controller";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_state.prev.down = ice_joy_state.next.down;
        ice_joy_state.prev.up = ice_joy_state.next.up;
        ice_joy_state.prev.held = ice_joy_state.next.held;
    
        hidScanInput();
    
        ice_joy_state.next.down = hidKeysDown();
        ice_joy_state.next.up = hidKeysUp();
        ice_joy_state.next.held = hidKeysHeld();
    
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 22;              // NOTE: If you don't use Nintendo New 3DS, Your device actually uses 18 buttons.
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_state.next.held & button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_state.next.held & button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_state.next.held & button) && (ice_joy_state.next.held != ice_joy_state.prev.held)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(ice_joy_state.next.held & button)) && (ice_joy_state.next.held != ice_joy_state.prev.held)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        hidCircleRead(&pos);
        return (ice_joy_vec2) { pos.dx, pos.dy };
    }
    
    return ICE_JOY_FALSE;
}

#elif defined(ICE_JOY_WII)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_WII IMPLEMENTATION  (Wii, WiiU - libogc)
///////////////////////////////////////////////////////////////////////////////////////////
#include <wiiuse/wpad.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE             -1
#define ICE_JOY_BUTTON_A                WPAD_CLASSIC_BUTTON_A
#define ICE_JOY_BUTTON_B                WPAD_CLASSIC_BUTTON_B
#define ICE_JOY_BUTTON_X                WPAD_CLASSIC_BUTTON_X
#define ICE_JOY_BUTTON_Y                WPAD_CLASSIC_BUTTON_Y
#define ICE_JOY_BUTTON_CROSS            ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE           ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE           ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE         ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB               WPAD_CLASSIC_BUTTON_FULL_L
#define ICE_JOY_BUTTON_RB               WPAD_CLASSIC_BUTTON_FULL_R
#define ICE_JOY_BUTTON_LT               WPAD_CLASSIC_BUTTON_ZL
#define ICE_JOY_BUTTON_RT               WPAD_CLASSIC_BUTTON_ZR
#define ICE_JOY_BUTTON_L1               ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1               ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2               ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2               ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_R3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_START            WPAD_CLASSIC_BUTTON_PLUS
#define ICE_JOY_BUTTON_MENU             ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS          ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT           WPAD_CLASSIC_BUTTON_MINUS
#define ICE_JOY_BUTTON_BACK             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP          WPAD_CLASSIC_BUTTON_UP
#define ICE_JOY_BUTTON_DPAD_DOWN        WPAD_CLASSIC_BUTTON_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT        WPAD_CLASSIC_BUTTON_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT       WPAD_CLASSIC_BUTTON_RIGHT

typedef struct ice_joy_info {
    u32 down;
    u32 up;
    u32 held;
} ice_joy_info;

typedef struct ice_joy_state {
    ice_joy_info prev;
    ice_joy_info next;
} ice_joy_state;

ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        if (WPAD_Init() == WPAD_ERR_NONE) {
            ice_joy_open = ICE_JOY_TRUE;
        }
    
        ice_joy_open ICE_JOY_FALSE;
        return ice_joy_open;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (WPAD_GetStatus(index) == WPAD_ERR_NONE) {
            return ICE_JOY_TRUE;
        }
        
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int count = 0;
    
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            if (WPAD_GetStatus(index) == WPAD_ERR_NONE) {
                count++;
            }
        }
    
        return count;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "NINTENDO WII CLASSIC CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].prev.down = ice_joy_states[index].next.down;
        ice_joy_states[index].prev.up = ice_joy_states[index].next.up;
        ice_joy_states[index].prev.held = ice_joy_states[index].next.held;
    
        if (WPAD_ScanPads() == WPAD_ERR_NONE) {
            ice_joy_states[index].next.down = WPAD_ButtonsDown(index);
            ice_joy_states[index].next.up = WPAD_ButtonsUp(index);
            ice_joy_states[index].next.held = WPAD_ButtonsHeld(index);
            return ICE_JOY_TRUE;
        }
    
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 4;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 16;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = ICE_JOY_FALSE;
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].next.held & button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_states[index].next.held & button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].next.held & button) && (ice_joy_states[index].next.held != ice_joy_states[index].prev.held)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(ice_joy_states[index].next.held & button)) && (ice_joy_states[index].next.held != ice_joy_states[index].prev.held)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    return (ice_joy_vec2) { 0, 0 }; // Looks like Wii and WiiU doesn't support this...
}

#elif defined(ICE_JOY_GAMECUBE)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_GAMECUBE IMPLEMENTATION  (Nintendo GameCube - libogc)
///////////////////////////////////////////////////////////////////////////////////////////
#include <gccore.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE             -1
#define ICE_JOY_BUTTON_A                PAD_BUTTON_A
#define ICE_JOY_BUTTON_B                PAD_BUTTON_B
#define ICE_JOY_BUTTON_X                PAD_BUTTON_X
#define ICE_JOY_BUTTON_Y                PAD_BUTTON_Y
#define ICE_JOY_BUTTON_CROSS            ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE           ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE           ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE         ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB               PAD_TRIGGER_L
#define ICE_JOY_BUTTON_RB               PAD_TRIGGER_R
#define ICE_JOY_BUTTON_LT               ICE_JOY_BUTTON_NONE // Although Z button exists, I don't want to let both L2/LT and R2/RT both uses it at same time, That sucks!
#define ICE_JOY_BUTTON_RT               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_L1               ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1               ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2               ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2               ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_R3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_START            PAD_BUTTON_START
#define ICE_JOY_BUTTON_MENU             ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS          ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT           ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_BACK             ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_VIEW             ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_DPAD_UP          PAD_BUTTON_UP
#define ICE_JOY_BUTTON_DPAD_DOWN        PAD_BUTTON_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT        PAD_BUTTON_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT       PAD_BUTTON_RIGHT

PADStatus prev_states[ICE_JOY_JOYSTICKS];
PADStatus next_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        ice_joy_open = (PAD_Init() == PAD_ERR_NONE) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        return ice_joy_open;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (PAD_Read(next_states) == PAD_ERR_NONE) {
            return (next_states[index] != NULL) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        }
        
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int count = 0;
    
        if (PAD_Read(next_states) != PAD_ERR_NONE) {
            return 0;
        }
    
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            if (next_states[i]) {
                count++;
            }
        }
    
        return count;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "NINTENDO GAMECUBE CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            prev_states[i] = next_states[i];
        }
    
        if (PAD_Read(next_states) != PAD_ERR_NONE) {
            return ICE_JOY_FALSE;
        }
    
        return (next_states[index] != NULL) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 12;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (next_states[index].button & button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(next_states[index].button & button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((next_states[index].button & button) && (next_states[index].button != prev_states[index].button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(next_states[index].button & button)) && (next_states[index].button != prev_states[index].button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                return next_states[index].substickX,
                return next_states[index].substickY,
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                return next_states[index].stickX,
                return next_states[index].stickY,
            };
        }
    
        return (ice_joy_vec2) { 0, 0 };
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_LINUX)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_LINUX IMPLEMENTATION  (Unix and Unix-Like - linux/joystick.h)
///////////////////////////////////////////////////////////////////////////////////////////
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE             -1
#define ICE_JOY_BUTTON_A                BTN_A
#define ICE_JOY_BUTTON_B                BTN_B
#define ICE_JOY_BUTTON_X                BTN_X
#define ICE_JOY_BUTTON_Y                BTN_Y
#define ICE_JOY_BUTTON_CROSS            ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE           ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE           ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE         ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB               BTN_TL
#define ICE_JOY_BUTTON_RB               BTN_TR
#define ICE_JOY_BUTTON_LT               BTN_TL2
#define ICE_JOY_BUTTON_RT               BTN_TR2
#define ICE_JOY_BUTTON_L1               BTN_TL
#define ICE_JOY_BUTTON_R1               BTN_TR
#define ICE_JOY_BUTTON_L2               BTN_TL2
#define ICE_JOY_BUTTON_R2               BTN_TR2
#define ICE_JOY_BUTTON_L3               BTN_THUMBL
#define ICE_JOY_BUTTON_R3               BTN_THUMBR
#define ICE_JOY_BUTTON_START            BTN_START
#define ICE_JOY_BUTTON_MENU             ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS          ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT           BTN_SELECT
#define ICE_JOY_BUTTON_BACK             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP          BTN_DPAD_UP
#define ICE_JOY_BUTTON_DPAD_DOWN        BTN_DPAD_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT        BTN_DPAD_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT       BTN_DPAD_RIGHT

#if !(JS_VERSION >= 0x010000)
#  error "ice_joy library requires Linux 2.2.x and above!"
#else
typedef struct ice_joy_joyinfo {
    int fd;
    int* axis;
	char* buttons;
    struct js_event event;
} ice_joy_joyinfo;

#endif
typedef struct ice_joy_state {
    ice_joy_joyinfo previous;
    ice_joy_joyinfo current;
} ice_joy_state;

ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

const char ice_joy_dev_names[ICE_JOY_JOYSTICKS][15] = {
    "/dev/input/js0",
    "/dev/input/js1",
    "/dev/input/js2",
    "/dev/input/js3",
};

const char ice_joy_dev_names_old[ICE_JOY_JOYSTICKS][9] = {
    "/dev/js0",
    "/dev/js1",
    "/dev/js2",
    "/dev/js3",
};

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        ice_joy_open = ICE_JOY_TRUE;
    }
    
    return ice_joy_open;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].current.fd = open(ice_joy_dev_names[index], O_RDONLY | O_NONBLOCK);

        if (ice_joy_states[index].current.fd == ICE_JOY_FALSE) {
            ice_joy_states[index].current.fd = open(ice_joy_dev_names_old[index], O_RDONLY | O_NONBLOCK);
        
            if (ice_joy_states[index].current.fd == ICE_JOY_FALSE) {
                return ICE_JOY_FALSE;
            }
        }
    
        int buttons_count = ice_joy_axis_count(index);
        int axis_count = ice_joy_buttons_count(index);
    
        ice_joy_states[index].current.axis = (int*)calloc(axis_count, sizeof(int));
        ice_joy_states[index].current.buttons = (char*)calloc(buttons_count, sizeof(char));
    
        fcntl(ice_joy_states[index].current.fd, F_SETFL, O_RDONLY | O_NONBLOCK);
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int count = 0;
        int js_fds[ICE_JOY_JOYSTICKS];
    
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            if ((js_fds[i] = open(ice_joy_dev_names[i], O_RDONLY | O_NONBLOCK)) == ICE_JOY_FALSE) {
                if ((js_fds[i] = open(ice_joy_dev_names_old[i], O_RDONLY | O_NONBLOCK)) == ICE_JOY_FALSE) {
                    count++;
                    close(js_fds[i]);
                } else {
                    break;
                }
            } else {
                count++;
                close(js_fds[i]);
            }
        }
    
        return count;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int fd;
        char name[80];
        char* result;
    
        if ((fd = open(ice_joy_dev_names[index], O_RDONLY | O_NONBLOCK)) == ICE_JOY_FALSE) {
            if ((fd = open(ice_joy_dev_names_old[index], O_RDONLY | O_NONBLOCK)) == ICE_JOY_FALSE) {
                return NULL;
            }
        
            return NULL;
        }

        ioctl(fd, JSIOCGNAME(80), &name);
        close(fd);
        result = name;
    
        return result;
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].previous = ice_joy_states[index].current;
    
        ssize_t bytes = read(ice_joy_states[index].current.fd, &ice_joy_states[index].current.event, sizeof(struct js_event));

        if (bytes == sizeof(struct js_event)) {
            switch (ice_joy_states[index].current.event.type & ~JS_EVENT_INIT) {
                case JS_EVENT_AXIS:
                    ice_joy_states[index].current.axis[ice_joy_states[index].current.event.number] = ice_joy_states[index].current.event.value;
                    return ICE_JOY_TRUE;
                    break;
                case JS_EVENT_BUTTON:
                    ice_joy_states[index].current.buttons[ice_joy_states[index].current.event.number] = ice_joy_states[index].current.event.value;
                    return ICE_JOY_TRUE;
                    break;
                default:
                    return ICE_JOY_TRUE;
                    break;
            }
        
            return ICE_JOY_TRUE;
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int fd;
        int axis_count = 0;
    
        if ((fd = open(ice_joy_dev_names[index], O_RDONLY)) == ICE_JOY_FALSE) {
            if ((fd = open(ice_joy_dev_names_old[index], O_RDONLY)) == ICE_JOY_FALSE) {
                return 0;
            }
            
            return 0;
        }
    
        ioctl(fd, JSIOCGAXES, &axis_count);
        close(fd);
        
        return axis_count;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int fd;
        int buttons_count = 0;
    
        if ((fd = open(ice_joy_dev_names[index], O_RDONLY | O_NONBLOCK)) == ICE_JOY_FALSE) {
            if ((fd = open(ice_joy_dev_names_old[index], O_RDONLY | O_NONBLOCK)) == ICE_JOY_FALSE) {
                return 0;
            }
            
            return 0;
        }
    
        ioctl(fd, JSIOCGBUTTONS, &buttons_count);
        close(fd);
    
        return buttons_count;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            close(ice_joy_states[i].previous.fd);
            close(ice_joy_states[i].current.fd);
        }

        ice_joy_open = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].current.buttons[button] > 0)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_states[index].current.buttons[button] > 0)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].current.buttons[button] > 0) && (ice_joy_states[index].current.buttons[button] != ice_joy_states[index].previous.buttons[button])) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_states[index].current.buttons[button] > 0) && (ice_joy_states[index].current.buttons[button] != ice_joy_states[index].previous.buttons[button])) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                (float) ice_joy_states[index].current.axis[0],
                (float) ice_joy_states[index].current.axis[1],
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                (float) ice_joy_states[index].current.axis[2],
                (float) ice_joy_states[index].current.axis[3],
            };
        }
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_BEOS)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_BEOS IMPLEMENTATION  (BeOS, Haiku - BJoystick)
///////////////////////////////////////////////////////////////////////////////////////////
#include <beobj.h>
#include <device/Joystick.h>

// Buttons definitions
// HELP: I want someone who uses BeOS/Haiku to fix button codes for me, If BeOS/Haiku only supports 2 buttons then i'm gonna remove BeOS/Haiku support.
#define ICE_JOY_BUTTON_NONE                 -1
#define ICE_JOY_BUTTON_A                    0
#define ICE_JOY_BUTTON_B                    1
#define ICE_JOY_BUTTON_X                    2
#define ICE_JOY_BUTTON_Y                    3
#define ICE_JOY_BUTTON_CROSS                ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE               ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE               ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE             ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB                   4
#define ICE_JOY_BUTTON_RB                   5
#define ICE_JOY_BUTTON_LT                   6
#define ICE_JOY_BUTTON_RT                   7
#define ICE_JOY_BUTTON_L1                   ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1                   ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2                   ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2                   ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3                   10
#define ICE_JOY_BUTTON_R3                   11
#define ICE_JOY_BUTTON_START                9
#define ICE_JOY_BUTTON_MENU                 ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS              ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT               8
#define ICE_JOY_BUTTON_BACK                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW                 ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP              12
#define ICE_JOY_BUTTON_DPAD_DOWN            13
#define ICE_JOY_BUTTON_DPAD_LEFT            14
#define ICE_JOY_BUTTON_DPAD_RIGHT           15

typedef struct ice_joy_state {
    BJoystick* stick;
    int16* axes;
    uint32 next;
    uint32 prev;
} ice_joy_state;

char joysticks_names[ICE_JOY_JOYSTICKS][B_OS_NAME_LENGTH];
ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            ice_joy_states[i].stick = new BJoystick();
            ice_joy_states[i].stick->GetDeviceName(i, joysticks_names[i]);
            ice_joy_states[i].stick->Open(joysticks_names[i]);
            ice_joy_states[i].axes = (int16*) ICE_JOY_MALLOC(sizeof(int16) * ice_joy_states[i].stick->CountAxes());
            ice_joy_states[i].stick->GetAxisValues(ice_joy_states[i].axes);
        }
        
        ice_joy_open = ICE_JOY_TRUE;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_init == ICE_JOY_TRUE) {
        return (ice_joy_states[index].stick->Open(joysticks_names[index]) == B_OK) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_init == ICE_JOY_TRUE) {
        int count = 0;
        ice_joy_states[i].stick->GetDeviceName(i, joysticks_names[i]);
        
        if (ice_joy_states[i].stick->Open(joysticks_names[i]) == B_OK) {
            count++;
        }
        
        return count;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_init == ICE_JOY_TRUE) {
        BString res;
        
        if (ice_joy_states[index].stick->GetControllerName(&res) == B_OK) {
            return strdup(res.String());
        }
        
        return NULL;
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_init == ICE_JOY_TRUE) {
        ice_joy_states[index].prev = ice_joy_states[index].next;
        
        // We try to reconnect to Joystick if failed to update, But if failed to reconnect we return ICE_JOY_FALSE.
        if (ice_joy_states[index].stick->Update() == B_OK) {
            ice_joy_states[index].next = ice_joy_states[index].stick->ButtonsValues();
            ice_joy_states[index].stick->GetAxisValues(ice_joy_states[index].axes);
            return ICE_JOY_TRUE;
        } else {
            ice_joy_states[index].stick->RescanDevices();
            ice_joy_states[index].stick->GetDeviceName(index, joysticks_names[index]);
            
            if (ice_joy_states[index].stick->Open(joysticks_names[index]) == B_OK) {
                ice_joy_states[index].next = ice_joy_states[index].stick->ButtonsValues();
                ice_joy_states[index].stick->GetAxisValues(ice_joy_states[index].axes);
            } else {
                return ICE_JOY_FALSE;
            }
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return (int) ice_joy_states[index].stick->CountAxes();
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return (int) ice_joy_states[index].stick->CountButtons();
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            if (ice_joy_states[i].stick->Close() == B_OK) {
                delete ice_joy_states[i].stick;
                ICE_JOY_FREE(ice_joy_states[i].axes);
                ice_joy_states[i].axes = NULL;
            }
        }
        
        ice_joy_open = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].next & (1 << button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_states[index].next & (1 << button))) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].next & (1 << button)) && (ice_joy_states[index].next != ice_joy_states[index].prev)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(ice_joy_states[index].next & (1 << button))) && (ice_joy_states[index].next != ice_joy_states[index].prev)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                (float)ice_joy_states[index].axes[0],
                (float)ice_joy_states[index].axes[1],
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                (float)ice_joy_states[index].axes[2],
                (float)ice_joy_states[index].axes[3],
            };
        } else {
            return (ice_joy_vec2) { 0, 0 };
        }
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_PSVITA)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_PSVITA IMPLEMENTATION    (Sony PlayStation Vita - vitasdk)
///////////////////////////////////////////////////////////////////////////////////////////
#include <psp2/ctrl.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE             -1
#define ICE_JOY_BUTTON_A                SCE_CTRL_CROSS
#define ICE_JOY_BUTTON_B                SCE_CTRL_CIRCLE
#define ICE_JOY_BUTTON_X                SCE_CTRL_SQUARE
#define ICE_JOY_BUTTON_Y                SCE_CTRL_TRIANGLE
#define ICE_JOY_BUTTON_CROSS            ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE           ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE           ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE         ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB               SCE_CTRL_L1
#define ICE_JOY_BUTTON_RB               SCE_CTRL_R1
#define ICE_JOY_BUTTON_LT               SCE_CTRL_L2
#define ICE_JOY_BUTTON_RT               SCE_CTRL_R2
#define ICE_JOY_BUTTON_L1               ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1               ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2               ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2               ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3               SCE_CTRL_L3
#define ICE_JOY_BUTTON_R3               SCE_CTRL_R3
#define ICE_JOY_BUTTON_START            SCE_CTRL_START
#define ICE_JOY_BUTTON_MENU             ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS          ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT           SCE_CTRL_SELECT
#define ICE_JOY_BUTTON_BACK             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP          SCE_CTRL_UP
#define ICE_JOY_BUTTON_DPAD_DOWN        SCE_CTRL_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT        SCE_CTRL_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT       SCE_CTRL_RIGHT

typedef struct ice_joy_states {
    SceCtrlData prev;
    SceCtrlData next;
} ice_joy_states;

ice_joy_states ice_joy_state;

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        ice_joy_open = (sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG) < 0) ? ICE_JOY_FALSE : ICE_JOY_TRUE;
    }
	
    return ice_joy_open;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 1;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "SONY PLAYSTATION VITA CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_state.prev = ice_joy_state.next;
        sceCtrlPeekBufferPositive(0, &ice_joy_state.next, 1);
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 16;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_state.next & button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_state.next & button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_state.next & button) && (ice_joy_state.next != ice_joy_state.prev)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(ice_joy_state.next & button)) && (ice_joy_state.next != ice_joy_state.prev)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                ice_joy_state.next.rx,
                ice_joy_state.next.ry,
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                ice_joy_state.next.lx,
                ice_joy_state.next.ly,
            };
        }
    
        return (ice_joy_vec2) { 0, 0 };
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_PSP)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_PSP IMPLEMENTATION  (Sony PlayStation Portable - PSPSDK)
///////////////////////////////////////////////////////////////////////////////////////////
#include <pspkernel.h>
#include <pspctrl.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE             -1
#define ICE_JOY_BUTTON_CROSS            PSP_CTRL_CROSS
#define ICE_JOY_BUTTON_CIRCLE           PSP_CTRL_CIRCLE
#define ICE_JOY_BUTTON_SQUARE           PSP_CTRL_SQUARE
#define ICE_JOY_BUTTON_TRIANGLE         PSP_CTRL_TRIANGLE
#define ICE_JOY_BUTTON_A                ICE_JOY_BUTTON_CROSS
#define ICE_JOY_BUTTON_B                ICE_JOY_BUTTON_CIRCLE
#define ICE_JOY_BUTTON_X                ICE_JOY_BUTTON_SQUARE
#define ICE_JOY_BUTTON_Y                ICE_JOY_BUTTON_TRIANGLE
#define ICE_JOY_BUTTON_LB               PSP_CTRL_LTRIGGER
#define ICE_JOY_BUTTON_RB               PSP_CTRL_RTRIGGER
#define ICE_JOY_BUTTON_LT               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_RT               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_L1               PSP_CTRL_LTRIGGER
#define ICE_JOY_BUTTON_R1               PSP_CTRL_RTRIGGER
#define ICE_JOY_BUTTON_L2               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_R2               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_L3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_R3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_START            PSP_CTRL_START
#define ICE_JOY_BUTTON_MENU             ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS          ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT           PSP_CTRL_SELECT
#define ICE_JOY_BUTTON_BACK             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP          PSP_CTRL_UP
#define ICE_JOY_BUTTON_DPAD_DOWN        PSP_CTRL_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT        PSP_CTRL_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT       PSP_CTRL_RIGHT

typedef struct ice_joy_state {
    SceCtrlData previous;
    SceCtrlData current;
} ice_joy_state;

ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        if (sceCtrlSetSamplingCycle(0) < 0) {
            ice_joy_open = ICE_JOY_FALSE;
            return ice_joy_open;
        }

        if (sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG) < 0) {
            ice_joy_open = ICE_JOY_FALSE;
            return ice_joy_open;
        }

        ice_joy_open = ICE_JOY_TRUE;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 1;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "PLAYSTATION PORTABLE CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].previous = ice_joy_states[index].current;

        if (sceCtrlReadBufferPositive(&ice_joy_states[index].current, 1) < 0) {
            return ICE_JOY_FALSE;
        }

        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 22;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].current.Buttons & button) > 0) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!((ice_joy_states[index].current.Buttons & button) > 0)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (((ice_joy_states[index].current.Buttons & button) > 0) && (ice_joy_states[index].current.Buttons != ice_joy_states[index].previous.Buttons)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!((ice_joy_states[index].current.Buttons & button) > 0) && (ice_joy_states[index].current.Buttons != ice_joy_states[index].previous.Buttons)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (ice_joy_analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                ice_joy_states[index].current.Lx,
                ice_joy_states[index].current.Ly,
            };
        } else {
            return (ice_joy_vec2) { 0, 0 };
        }
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_SWITCH)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_SWITCH IMPLEMENTATION  (Nintendo Switch - libnx)
///////////////////////////////////////////////////////////////////////////////////////////
#include <switch.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE             -1
#define ICE_JOY_BUTTON_A                HidDebugPadButton_A
#define ICE_JOY_BUTTON_B                HidDebugPadButton_B
#define ICE_JOY_BUTTON_X                HidDebugPadButton_X
#define ICE_JOY_BUTTON_Y                HidDebugPadButton_Y
#define ICE_JOY_BUTTON_CROSS            ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE           ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE           ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE         ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB               HidDebugPadButton_L
#define ICE_JOY_BUTTON_RB               HidDebugPadButton_R
#define ICE_JOY_BUTTON_LT               HidDebugPadButton_ZL
#define ICE_JOY_BUTTON_RT               HidDebugPadButton_ZR
#define ICE_JOY_BUTTON_L1               ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1               ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2               ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2               ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_R3               ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_START            HidDebugPadButton_Start
#define ICE_JOY_BUTTON_MENU             ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS          ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT           HidDebugPadButton_Select
#define ICE_JOY_BUTTON_BACK             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW             ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP          HidDebugPadButton_Up
#define ICE_JOY_BUTTON_DPAD_DOWN        HidDebugPadButton_Down
#define ICE_JOY_BUTTON_DPAD_LEFT        HidDebugPadButton_Left
#define ICE_JOY_BUTTON_DPAD_RIGHT       HidDebugPadButton_Right

typedef struct ice_joy_state {
    u64 previous;
    u64 current;
} ice_joy_state;

PadState pad;
ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];
HiddbgAbstractedPadHandle joys[ICE_JOY_JOYSTICKS];
HiddbgAbstractedPadState states[ICE_JOY_JOYSTICKS];
s32 res = 0;

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        padConfigureInput(ICE_JOY_JOYSTICKS, HidNpadStyleSet_NpadStandard);
        padInitializeAny(&pad);
        ice_joy_open = R_FAILED(hiddbgInitialize()) ? ICE_JOY_FALSE : ICE_JOY_TRUE;
        return ice_joy_open;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (ice_joy_update(index) == ICE_JOY_TRUE) {
            return (index >= 0 && index <= res - 1) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        }
        
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (ice_joy_update(0) == ICE_JOY_TRUE) {
            return res;
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "NINTENDO SWITCH CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_states[index].previous = ice_joy_states[index].current;
    
        if (R_FAILED(hiddbgGetAbstractedPadHandles(joys, sizeof(joys) / sizeof(u64), &res))) {
            return ICE_JOY_FALSE;
        }
    
        if (R_FAILED(hiddbgGetAbstractedPadState(joys[index], states))) {
            return ICE_JOY_FALSE;
        }
    
        states[index].type = BIT(1);
        states[index].npadInterfaceType = HidNpadInterfaceType_Rail;
        states[index].state.buttons |= HidNpadButton_ZL;
    
        if (R_FAILED(hiddbgSetAutoPilotVirtualPadState(index, &states[index]))) {
            return ICE_JOY_FALSE;
        }
    
        ice_joy_states[index].current = states[index].state.buttons;
    
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 6;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 18;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_initialized == ICE_JOY_TRUE) {
        if (R_FAILED(hiddbgUnsetAllAutoPilotVirtualPadState())) {
            return ICE_JOY_FALSE;
        }
        
        hiddbgExit();
        return ICE_JOY_TRUE;
    }
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_states[index].next & button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_states[index].next & button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_states[index].next & button) && (ice_joy_states[index].next != ice_joy_states[index].previous)) ? ICE_JOY_TRUE : ICE_JOY_FALSE; 
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(ice_joy_states[index].next & button)) && (ice_joy_states[index].next != ice_joy_states[index].previous)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                states[index].state.analog_stick_r.x,
                states[index].state.analog_stick_r.y,
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                states[index].state.analog_stick_l.x,
                states[index].state.analog_stick_l.y,
            };
        }

        return (ice_joy_vec2) { 0, 0 };
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_MICROSOFT)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_MICROSOFT IMPLEMENTATION  (Microsoft Devices - XInput)
///////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <Xinput.h>
#include <joystickapi.h>
#include <mmsystem.h>
#include <stdlib.h>
#pragma comment(lib, "XInput.lib")
#pragma comment(lib, "XInput9_1_0.lib")
#pragma comment(lib, "Winmm.lib")

// Buttons definitions
#define ICE_JOY_BUTTON_NONE                  -1
#define ICE_JOY_BUTTON_A                     XINPUT_GAMEPAD_A
#define ICE_JOY_BUTTON_B                     XINPUT_GAMEPAD_B
#define ICE_JOY_BUTTON_X                     XINPUT_GAMEPAD_X
#define ICE_JOY_BUTTON_Y                     XINPUT_GAMEPAD_Y
#define ICE_JOY_BUTTON_CROSS                 ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE                ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE                ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE              ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB                    XINPUT_GAMEPAD_LEFT_SHOULDER
#define ICE_JOY_BUTTON_RB                    XINPUT_GAMEPAD_RIGHT_SHOULDER
#define ICE_JOY_BUTTON_LT                    XINPUT_GAMEPAD_LEFT_THUMB
#define ICE_JOY_BUTTON_RT                    XINPUT_GAMEPAD_RIGHT_THUMB
#define ICE_JOY_BUTTON_L1                    ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1                    ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2                    ICE_JOY_BUTTON_LT
#define ICE_JOY_BUTTON_R2                    ICE_JOY_BUTTON_RT
#define ICE_JOY_BUTTON_L3                    ICE_JOY_CAMERA_ANALOG
#define ICE_JOY_BUTTON_R3                    ICE_JOY_MOVE_ANALOG
#define ICE_JOY_BUTTON_START                 XINPUT_GAMEPAD_START
#define ICE_JOY_BUTTON_MENU                  ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS               ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT                XINPUT_GAMEPAD_BACK
#define ICE_JOY_BUTTON_BACK                  ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW                  ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP               XINPUT_GAMEPAD_DPAD_UP
#define ICE_JOY_BUTTON_DPAD_DOWN             XINPUT_GAMEPAD_DPAD_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT             XINPUT_GAMEPAD_DPAD_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT            XINPUT_GAMEPAD_DPAD_RIGHT

typedef struct ice_joy_state {
    XINPUT_STATE previous;
    XINPUT_STATE current;
} ice_joy_state;

ice_joy_state ice_joy_states[ICE_JOY_JOYSTICKS];

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        ice_joy_open = ICE_JOY_TRUE;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD connected = XInputGetState(joy_index, &state);
        return (connected == ERROR_SUCCESS) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        int count = 0;
    
        for (int i = 0; i < XUSER_MAX_COUNT; i++) {
            XINPUT_STATE state;
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            DWORD connected = XInputGetState(i, &state);
        
            if (connected == ERROR_SUCCESS) {
                count++;
            }
        }
    
        return count;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        JOYCAPS joycap;
        char str[256];
    
        if (XInputGetState(index, &state) == ERROR_SUCCESS) {
            if (joyGetDevCaps(index, &joycap, sizeof(JOYCAPS)) == JOYERR_NOERROR) {
                wcstombs(str, joycap.szPname, wcslen(joycap.szPname) + 1);
                return str;
            }
        } else {
            return NULL;
        }
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ZeroMemory(&ice_joy_states[index].previous, sizeof(XINPUT_STATE));
        ice_joy_states[index].previous = ice_joy_states[index].current;
    
        ZeroMemory(&ice_joy_states[index].current, sizeof(XINPUT_STATE));
        DWORD connected = XInputGetState(index, &ice_joy_states[index].current);
    
        return (connected == ERROR_SUCCESS) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 4;
    }
    
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 16;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        for (int i = 0; i < ICE_JOY_JOYSTICKS; i++) {
            ZeroMemory(&ice_joy_states[i].previous, sizeof(XINPUT_STATE));
            ZeroMemory(&ice_joy_states[i].current, sizeof(XINPUT_STATE));
        }
        
        ice_joy_open = ICE_JOY_FALSE;
    }

    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        if (button != ICE_JOY_BUTTON_L3 && button != ICE_JOY_BUTTON_R3) {
            return (ice_joy_states[index].current.Gamepad.wButtons & button > 0) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (button == ICE_JOY_BUTTON_L3) {
            return (ice_joy_states[index].current.Gamepad.bLeftTrigger > 0) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (button == ICE_JOY_BUTTON_R3) {
            return (ice_joy_states[index].current.Gamepad.bRightTrigger > 0) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else {
            return ICE_JOY_FALSE;
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        if (button != ICE_JOY_BUTTON_L3 && button != ICE_JOY_BUTTON_R3) {
            return (!(ice_joy_states[index].current.Gamepad.wButtons & button > 0)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (button == ICE_JOY_BUTTON_L3) {
            return (!(ice_joy_states[index].current.Gamepad.bLeftTrigger > 0)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (button == ICE_JOY_BUTTON_R3) {
            return (!(ice_joy_states[index].current.Gamepad.bRightTrigger > 0)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else {
            return ICE_JOY_FALSE;
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        if (button != ICE_JOY_BUTTON_L3 && button != ICE_JOY_BUTTON_R3) {
            return (ice_joy_states[index].current.Gamepad.wButtons & button > 0 && ice_joy_states[index].current.Gamepad.wButtons != ice_joy_states[index].previous.Gamepad.wButtons) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (button == ICE_JOY_BUTTON_L3) {
            return (ice_joy_states[index].current.Gamepad.bLeftTrigger > 0 && ice_joy_states[index].current.Gamepad.bLeftTrigger != ice_joy_states[index].previous.Gamepad.bLeftTrigger) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (button == ICE_JOY_BUTTON_R3) {
            return (ice_joy_states[index].current.Gamepad.bRightTrigger > 0 && ice_joy_states[index].current.Gamepad.bRightTrigger != ice_joy_states[index].previous.Gamepad.bRightTrigger) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else {
            return ICE_JOY_FALSE;
        }
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        if (button != ICE_JOY_BUTTON_L3 && button != ICE_JOY_BUTTON_R3) {
            return (!(ice_joy_states[index].current.Gamepad.wButtons & button > 0) && ice_joy_states[index].current.Gamepad.wButtons != ice_joy_states[index].previous.Gamepad.wButtons) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (button == ICE_JOY_BUTTON_L3) {
            return (!(ice_joy_states[index].current.Gamepad.bLeftTrigger > 0) && ice_joy_states[index].current.Gamepad.bLeftTrigger != ice_joy_states[index].previous.Gamepad.bLeftTrigger) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (button == ICE_JOY_BUTTON_R3) {
            return (!(ice_joy_states[index].current.Gamepad.bRightTrigger > 0) && ice_joy_states[index].current.Gamepad.bRightTrigger != ice_joy_states[index].previous.Gamepad.bRightTrigger) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else {
            return ICE_JOY_FALSE;
        }
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
// HINT: Could both XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE and XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE helps?
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (analog == ICE_JOY_MOVE_ANALOG) {
            return (ice_joy_vec2) {
                (float)(ice_joy_states[index].current.sThumbRX) <= 0 ? ice_joy_states[index].current.sThumbRX / 32768 : ice_joy_states[index].current.sThumbRX / 32767,
                (float)(ice_joy_states[index].current.sThumbRY) <= 0 ? ice_joy_states[index].current.sThumbRY / 32768 : ice_joy_states[index].current.sThumbRY / 32767,
            };
        } else if (analog == ICE_JOY_CAMERA_ANALOG) {
            return (ice_joy_vec2) {
                (float)(ice_joy_states[index].current.sThumbLX) <= 0 ? ice_joy_states[index].current.sThumbLX / 32768 : ice_joy_states[index].current.sThumbLX / 32767,
                (float)(ice_joy_states[index].current.sThumbLY) <= 0 ? ice_joy_states[index].current.sThumbLY / 32768 : ice_joy_states[index].current.sThumbLY / 32767,
            };
        }

        return (ice_joy_vec2) { 0, 0 };
    }
    
    return (ice_joy_vec2) { 0, 0 };
}

#elif defined(ICE_JOY_NDS)
///////////////////////////////////////////////////////////////////////////////////////////
// ICE_JOY_NDS IMPLEMENTATION  (Nintendo DS - libnds)
///////////////////////////////////////////////////////////////////////////////////////////
#include <nds.h>

// Buttons definitions
#define ICE_JOY_BUTTON_NONE                  -1
#define ICE_JOY_BUTTON_A                     KEY_A
#define ICE_JOY_BUTTON_B                     KEY_B
#define ICE_JOY_BUTTON_X                     KEY_X
#define ICE_JOY_BUTTON_Y                     KEY_Y
#define ICE_JOY_BUTTON_CROSS                 ICE_JOY_BUTTON_A
#define ICE_JOY_BUTTON_CIRCLE                ICE_JOY_BUTTON_B
#define ICE_JOY_BUTTON_SQUARE                ICE_JOY_BUTTON_X
#define ICE_JOY_BUTTON_TRIANGLE              ICE_JOY_BUTTON_Y
#define ICE_JOY_BUTTON_LB                    KEY_L
#define ICE_JOY_BUTTON_RB                    KEY_R
#define ICE_JOY_BUTTON_LT                    ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_RT                    ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_L1                    ICE_JOY_BUTTON_LB
#define ICE_JOY_BUTTON_R1                    ICE_JOY_BUTTON_RB
#define ICE_JOY_BUTTON_L2                    ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_R2                    ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_L3                    ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_R3                    ICE_JOY_BUTTON_NONE
#define ICE_JOY_BUTTON_START                 KEY_START
#define ICE_JOY_BUTTON_MENU                  ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_OPTIONS               ICE_JOY_BUTTON_START
#define ICE_JOY_BUTTON_SELECT                KEY_SELECT
#define ICE_JOY_BUTTON_BACK                  ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_VIEW                  ICE_JOY_BUTTON_SELECT
#define ICE_JOY_BUTTON_DPAD_UP               KEY_UP
#define ICE_JOY_BUTTON_DPAD_DOWN             KEY_DOWN
#define ICE_JOY_BUTTON_DPAD_LEFT             KEY_LEFT
#define ICE_JOY_BUTTON_DPAD_RIGHT            KEY_RIGHT

uint32 ice_joy_prev_state;
uint32 ice_joy_next_state;

// Functions
// Connection, Misc, etc...
// Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_init(void) {
    if (ice_joy_open == ICE_JOY_FALSE) {
        ice_joy_open = ICE_JOY_TRUE;
    }
    
    return ICE_JOY_TRUE;
}

// Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_connected(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return ICE_JOY_TRUE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of current connected Joysticks as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_joysticks_count(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 1;
    }
    
    return 0;
}

// Returns Joystick's name at index index as string.
ICE_JOY_API ice_joy_str ICE_JOY_CALLCONV ice_joy_name(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return "NINTENDO DS CONTROLLER";
    }
    
    return NULL;
}

// Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_update(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        scanKeys();
        ice_joy_prev_state = ice_joy_next_state;
        ice_joy_next_state = keysHeld();
    }
    
    return ICE_JOY_FALSE;
}

// Returns count of axes in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_axis_count(ice_joy_player index) {
    return 0;
}

// Returns count of buttons in Joystick at index index as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_buttons_count(ice_joy_player index) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        return 12;
    }
    
    return 0;
}

// Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_close(void) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        ice_joy_open = ICE_JOY_FALSE;
    }
    
    return ICE_JOY_TRUE;
}

// Buttons
// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_down(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (ice_joy_next_state & button) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_up(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return (!(ice_joy_next_state & button)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_pressed(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((ice_joy_next_state & button) && (ice_joy_next_state != ice_joy_prev_state)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_button_released(ice_joy_player index, ice_joy_button button) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        button = ice_joy_button_code(button);
        return ((!(ice_joy_next_state & button)) && (ice_joy_next_state != ice_joy_prev_state)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Analogs and Hats
// Returns 2D vector position containing movement of analog from Joystick at index index.
ICE_JOY_API ice_joy_vec2 ICE_JOY_CALLCONV ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog) {
    return (ice_joy_vec2) { 0, 0 }; // NDS supports touch only, No analogs...
}

#endif

// Returns ICE_JOY_TRUE if Hat is pressed or ICE_JOY_FALSE if not.
ICE_JOY_API ice_joy_bool ICE_JOY_CALLCONV ice_joy_hat_pressed(ice_joy_player index, ice_joy_hat hat) {
    if (ice_joy_open == ICE_JOY_TRUE) {
        if (hat == ICE_JOY_HAT_CENTERED) {
            return (!(ice_joy_button_down(index, ICE_JOY_UP) == ICE_JOY_TRUE && ice_joy_button_down(index, ICE_JOY_DOWN) == ICE_JOY_TRUE && ice_joy_button_down(index, ICE_JOY_LEFT) == ICE_JOY_TRUE && ice_joy_button_down(index, ICE_JOY_RIGHT) == ICE_JOY_TRUE)) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (hat == ICE_JOY_HAT_UP) {
            return ice_joy_button_down(index, ICE_JOY_UP);
        } else if (hat == ICE_JOY_HAT_DOWN) {
            return ice_joy_button_down(index, ICE_JOY_DOWN);
        } else if (hat == ICE_JOY_HAT_LEFT) {
            return ice_joy_button_down(index, ICE_JOY_LEFT);
        } else if (hat == ICE_JOY_HAT_RIGHT) {
            return ice_joy_button_down(index, ICE_JOY_RIGHT);
        } else if (hat == ICE_JOY_HAT_UP_LEFT) {
            return (ice_joy_button_down(index, ICE_JOY_UP) == ICE_JOY_TRUE && ice_joy_button_down(index, ICE_JOY_LEFT) == ICE_JOY_TRUE) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (hat == ICE_JOY_HAT_UP_RIGHT) {
            return (ice_joy_button_down(index, ICE_JOY_UP) == ICE_JOY_TRUE && ice_joy_button_down(index, ICE_JOY_RIGHT) == ICE_JOY_TRUE) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (hat == ICE_JOY_HAT_DOWN_LEFT) {
            return (ice_joy_button_down(index, ICE_JOY_DOWN) == ICE_JOY_TRUE && ice_joy_button_down(index, ICE_JOY_LEFT) == ICE_JOY_TRUE) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        } else if (hat == ICE_JOY_HAT_DOWN_RIGHT) {
            return (ice_joy_button_down(index, ICE_JOY_DOWN) == ICE_JOY_TRUE && ice_joy_button_down(index, ICE_JOY_RIGHT) == ICE_JOY_TRUE) ? ICE_JOY_TRUE : ICE_JOY_FALSE;
        }
    
        return ICE_JOY_FALSE;
    }
    
    return ICE_JOY_FALSE;
}

// Returns button value by button enum definition as integer.
ICE_JOY_API int ICE_JOY_CALLCONV ice_joy_button_code(ice_joy_button button) {
    if (button == ICE_JOY_NONE) return ICE_JOY_BUTTON_NONE;
    
    int btns[16] = {
        ICE_JOY_BUTTON_A,
        ICE_JOY_BUTTON_B,
        ICE_JOY_BUTTON_X,
        ICE_JOY_BUTTON_Y,
        ICE_JOY_BUTTON_LB,
        ICE_JOY_BUTTON_RB,
        ICE_JOY_BUTTON_LT,
        ICE_JOY_BUTTON_RT,
        ICE_JOY_BUTTON_SELECT,
        ICE_JOY_BUTTON_START,
        ICE_JOY_BUTTON_L3,
        ICE_JOY_BUTTON_R3,
        ICE_JOY_BUTTON_DPAD_UP,
        ICE_JOY_BUTTON_DPAD_DOWN,
        ICE_JOY_BUTTON_DPAD_LEFT,
        ICE_JOY_BUTTON_DPAD_RIGHT,
    };
    
    return btns[button];
}

#endif // ICE_JOY_IMPL
#endif // ICE_JOY_H
