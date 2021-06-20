// NOTE: You need to have raylib installed on Windows, Also this can work with "Notepad++ for raylib"
// Also it worth mention that this uses small subset of ice_mouse...

// To compile:
// Add -ldinput -ldinput8 -ldxguid -lwinmm when compiling to link required libs...

// On "Notepad++ for raylib", Replace SET_CFLAGS to be like this:
// SET CFLAGS=$(RAYLIB_PATH)\src\raylib.rc.data -s -static -Os -std=c99 -Wall -I$(RAYLIB_PATH)\src -Iexternal -ldinput -ldinput8 -ldxguid -luser32 -lwinmm -DPLATFORM_DESKTOP

// If you get error about PlaySound conflict, Comment RLAPI void PlaySound function in raylib.h then it should works!

#if defined(_WIN32)
/* 
  @raysan5: To avoid conflicting windows.h symbols with raylib, some flags are defined
  WARNING: Those flags avoid inclusion of some Win32 headers that could be required 
  by user at some point and won't be included...
*/

/* If defined, the following flags inhibit definition of the indicated items.*/
#define NOGDICAPMASKS     // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES // VK_*
#define NOWINMESSAGES     // WM_*, EM_*, LB_*, CB_*
#define NOWINSTYLES       // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
#define NOSYSMETRICS      // SM_*
#define NOMENUS           // MF_*
#define NOICONS           // IDI_*
#define NOKEYSTATES       // MK_*
#define NOSYSCOMMANDS     // SC_*
#define NORASTEROPS       // Binary and Tertiary raster ops
#define NOSHOWWINDOW      // SW_*
#define OEMRESOURCE       // OEM Resource values
#define NOATOM            // Atom Manager routines
#define NOCLIPBOARD       // Clipboard routines
#define NOCOLOR           // Screen colors
#define NOCTLMGR          // Control and Dialog routines
#define NODRAWTEXT        // DrawText() and DT_*
#define NOGDI             // All GDI defines and routines
#define NOKERNEL          // All KERNEL defines and routines
#define NOUSER            // All USER defines and routines
#define NOATOM
#define NOGDI
#define NOGDICAPMASKS
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
#define NOOPENFILE
#define NORASTEROPS
#define NOSCROLL
#define NOSOUND
#define NOSYSMETRICS
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOCRYPT
#define NOMCX
/*#define NONLS             // All NLS defines and routines*/
#define NOMB              // MB_* and MessageBox()
#define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE        // typedef METAFILEPICT
#define NOMINMAX          // Macros min(a,b) and max(a,b)
#define NOMSG             // typedef MSG and associated routines
#define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL          // SB_* and scrolling routines
#define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND           // Sound driver routines
#define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines
#define NOWH              // SetWindowsHook and WH_*
#define NOWINOFFSETS      // GWL_*, GCL_*, associated routines
#define NOCOMM            // COMM driver routines
#define NOKANJI           // Kanji support stuff.
#define NOHELP            // Help engine interface.
#define NOPROFILER        // Profiler interface.
#define NODEFERWINDOWPOS  // DeferWindowPos routines
#define NOMCX             // Modem Configuration Extensions

/* Type required before windows.h inclusion  */
typedef struct tagMSG *LPMSG;

#include <windows.h>

/* Type required by some unused function...  */
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

#include <objbase.h>
#include <mmreg.h>

/* @raysan5: Some required types defined for MSVC/TinyC compiler */
#if defined(_MSC_VER) || defined(__TINYC__)
    #include "propidl.h"
#endif
#endif

#define CINTERFACE
#define DIRECTINPUT_VERSION 0x0800

#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120
#endif

#include <windows.h>
#include <winuser.h>
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <raylib.h>
#include <stdio.h>

typedef struct ice_mouse_vec2 { float x; float y; } ice_mouse_vec2;
typedef enum { ICE_MOUSE_TRUE = 0, ICE_MOUSE_FALSE = -1, } ice_mouse_bool;

typedef enum {
    ICE_MOUSE_BUTTON_LEFT = 0,
    ICE_MOUSE_BUTTON_RIGHT = 1,
    ICE_MOUSE_BUTTON_MIDDLE = 2
} ice_mouse_button;

static LPDIRECTINPUT8 di;
static LPDIRECTINPUTDEVICE8 mice;

static DIMOUSESTATE2 next_ev;
static DIMOUSESTATE2 prev_ev;

static int window_flags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
static void* win = NULL;
ice_mouse_vec2 mouse_pos;

void ice_mouse_set_window_handle(void* window) {
    if (window) {
        window_flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
        win = window;
    }
}

ice_mouse_bool ice_mouse_init(void) {
    mouse_pos = (ice_mouse_vec2) { 0, 0 };
    
    if (!win) {
        win = GetConsoleWindow();
    }
    
    if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, &IID_IDirectInput8, (VOID**)&di, NULL))) {
        return ICE_MOUSE_FALSE;
    }

    if (FAILED(IDirectInput_CreateDevice(di, &GUID_SysMouse, &mice, NULL))) {
        return ICE_MOUSE_FALSE;
    }

    if (mice) {
        if (FAILED(IDirectInputDevice_SetDataFormat(mice, &c_dfDIMouse2))) {
            return ICE_MOUSE_FALSE;
        }

        if (FAILED(IDirectInputDevice_SetCooperativeLevel(mice, win, window_flags))) {
            return ICE_MOUSE_FALSE;
        }

        if (FAILED(IDirectInputDevice_Acquire(mice))) {
            return ICE_MOUSE_FALSE;
        }
    }

    return ICE_MOUSE_TRUE;
}

ice_mouse_bool ice_mouse_close(void) {
     if (FAILED(IDirectInputDevice_Unacquire(mice))) {
        return ICE_MOUSE_FALSE;
    }

    if (FAILED(IDirectInputDevice_Release(mice))) {
        return ICE_MOUSE_FALSE;
    }

    if (FAILED(IDirectInput_Release(di))) {
        return ICE_MOUSE_TRUE;
    }

    return ICE_MOUSE_TRUE;
}

ice_mouse_bool ice_mouse_update(void) {
    prev_ev = next_ev;
    
    if (FAILED(IDirectInputDevice_GetDeviceState(mice, sizeof(DIMOUSESTATE2), (LPVOID)&next_ev))) {
        IDirectInputDevice_Acquire(mice);
        return;
    }
    
    mouse_pos.x += (float) next_ev.lX;
    mouse_pos.y += (float) next_ev.lY;
    
    return ICE_MOUSE_TRUE;
}

ice_mouse_bool ice_mouse_button_pressed(int b) {
    return (next_ev.rgbButtons[b] && next_ev.rgbButtons[b] != prev_ev.rgbButtons[b]) ? ICE_MOUSE_TRUE : ICE_MOUSE_FALSE;
}

float ice_mouse_wheel(void) {
    return (float)(next_ev.lZ / WHEEL_DELTA);
}

int main(int argc, char** argv) {
    InitWindow(800, 450, "DirectInput test!");
    SetTargetFPS(60);
    void* hwnd = GetWindowHandle();
    ice_mouse_set_window_handle(hwnd);
    Color circle_color = RED;
    int color_state = 0;
    
    if (ice_mouse_init() != ICE_MOUSE_TRUE) {
        printf("ERROR: Failed to initialize DirectInput within raylib!\n");
        CloseWindow();
        return -1;
    }
    
    while (!WindowShouldClose()) {
        if (ice_mouse_update() != ICE_MOUSE_TRUE) {
            printf("ERROR: Failed to update mouse!\n");
            break;
        }
        
        if (ice_mouse_button_pressed(ICE_MOUSE_BUTTON_LEFT) == ICE_MOUSE_TRUE) {
            if (color_state == 0) {
                circle_color = BLUE;
                color_state = 1;
            } else if (color_state == 1) {
                circle_color = RED;
                color_state = 0;
            }
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("X: %f, Y: %f", mouse_pos.x, mouse_pos.y), 16, 16, 18, circle_color);
        DrawCircleV((Vector2) { mouse_pos.x, mouse_pos.y }, 25.0f, circle_color);
        mouse_pos.y += ice_mouse_wheel();
        EndDrawing();
    }
    
    ice_mouse_close();
    CloseWindow();
    return 0;
}
