# ice_mouse.h Documentation

### Enums

```c
typedef enum {
    ICE_MOUSE_TRUE = 0,
    ICE_MOUSE_FALSE = -1
} ice_mouse_bool;

typedef enum {
    ICE_MOUSE_BUTTON_LEFT,
    ICE_MOUSE_BUTTON_RIGHT,
    ICE_MOUSE_BUTTON_CENTER
} ice_mouse_button;
```

### Structs

```c
// Used for mouse position!
typedef struct ice_mouse_vec2 {
    float x;
    float y;
} ice_mouse_vec2;
```

### Definitions

```c
#define ICE_MOUSE_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_MOUSE_STATIC  // Makes functions of the library static with static keyword
#define ICE_MOUSE_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_MOUSE_CALLCONV_VECTORCALL
#define ICE_MOUSE_CALLCONV_FASTCALL
#define ICE_MOUSE_CALLCONV_STDCALL
#define ICE_MOUSE_CALLCONV_CDECL

// Default definitions
// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_MOUSE_PLATFORM_AUTODETECTED

// Platform definitions
#define ICE_MOUSE_MICROSOFT       // Microsoft Platforms (Except Xbox Original 2004)
#define ICE_MOUSE_OSX             // Apple Platforms
#define ICE_MOUSE_ANDROID         // Android
#define ICE_MOUSE_LINUX           // Linux and Unix-Like (Except BSD)
#define ICE_MOUSE_WEB             // Emscripten

// In case you want to build DLL on Microsoft Windows!
// Keep in mind you should set backend (But it's defined by default if not...)
#define ICE_MOUSE_DLLEXPORT
#define ICE_MOUSE_DLLIMPORT

// Linux helpers
#define ICE_MOUSE_FD_PATH                                               // Default file descriptor path for Linux mouse device (default is /dev/input/mice) but can be changed before including ice_mouse.h

// Android helpers
#define ICE_MOUSE_ANDROID_CUSTOM_INPUT_EVENT_HANDLERS                   // Allows ice_mouse to call custom events via 2 definitions above
#define ANDROID_CMD_HANDLE_FUNC     android_cmd_handling_func_name      // Once loop, ice_mouse will call android_cmd_handling_func_name inside command event function
#define ANDROID_INPUT_HANDLE_FUNC   android_input_handling_func_name    // Once loop, ice_mouse will call android_input_handling_func_name inside input events function
```

### Functions

```c
ice_mouse_bool ice_mouse_set_window_handle(void* window);                   // Sets which window will handle input by ice_mouse (Designed for Windows but returns ICE_MOUSE_TRUE on other-platforms).
ice_mouse_bool ice_mouse_init(void);                                        // Initializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ice_mouse_bool ice_mouse_update(void);                                      // Updates mouse input, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ice_mouse_bool ice_mouse_close(void);                                       // Deinitializes ice_mouse library, Returns ICE_MOUSE_TRUE if success or ICE_MOUSE_FALSE if failed.
ice_mouse_vec2 ice_mouse_pos(void);                                         // Returns current mouse position as 2D vector.
ice_mouse_bool ice_mouse_button_down(ice_mouse_button button);              // Returns ICE_MOUSE_TRUE if mouse button is being pressed or ICE_MOUSE_FALSE if not.
ice_mouse_bool ice_mouse_button_up(ice_mouse_button button);                // Returns ICE_MOUSE_TRUE if mouse button is not being pressed or ICE_MOUSE_FALSE if not.
ice_mouse_bool ice_mouse_button_pressed(ice_mouse_button button);           // Returns ICE_MOUSE_TRUE if mouse button pressed (Not "being" which means hold/down) or ICE_MOUSE_FALSE if not.
ice_mouse_bool ice_mouse_button_released(ice_mouse_button button);          // Returns ICE_MOUSE_TRUE if mouse button released or ICE_MOUSE_FALSE if not.
float          ice_mouse_wheel(void);                                       // Returns mouse wheel delta as float.
```
