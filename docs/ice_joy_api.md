# ice_joy.h Documentation

### Enums

```c
typedef enum {
    ICE_JOY_TRUE  = 0,
    ICE_JOY_FALSE = -1,
} ice_joy_bool;

// Analog to get X and Y axis from
typedef enum {
    ICE_JOY_MOVE_ANALOG,
    ICE_JOY_CAMERA_ANALOG,
} ice_joy_analog;

// Joysticks
typedef enum {
    ICE_JOY_PLAYER1,
    ICE_JOY_PLAYER2,
    ICE_JOY_PLAYER3,
    ICE_JOY_PLAYER4,
} ice_joy_player;

// Joystick buttons
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

// Joystick hats
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
```

### Structs

```c
// Used by X and Y axis of Analog (Thumbstick)
typedef struct ice_joy_vec2 {
    float x;
    float y;
} ice_joy_vec2;
```

### Definitions

```c
// Typedefs
typedef char* ice_joy_str;

// Allow to use ice_joy functions as extern ones...
#define ICE_JOY_EXTERN 

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_JOY_CALLCONV_VECTORCALL
#define ICE_JOY_CALLCONV_FASTCALL
#define ICE_JOY_CALLCONV_STDCALL
#define ICE_JOY_CALLCONV_CDECL

// Default definitions
// Max count of Joysticks allowed by ice_joy library!
#define ICE_JOY_JOYSTICKS 4

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
// NOTE FOR MICROSOFT WINDOWS: Platform backend defined depending on project type!
#define ICE_JOY_PLATFORM_AUTODETECTED

// Platform definitions
#define ICE_JOY_MICROSOFT       // Microsoft Platforms (Except Xbox Original 2004)
#define ICE_JOY_APPLE           // Apple Platforms
#define ICE_JOY_ANDROID         // Android
#define ICE_JOY_LINUX           // Linux and Unix-Like (Except BSD)
#define ICE_JOY_WEB             // Emscripten
#define ICE_JOY_SWITCH          // Nintendo Switch
#define ICE_JOY_WII             // Nintendo Wii, Nintendo WiiU
#define ICE_JOY_GAMECUBE        // Nintendo GameCube
#define ICE_JOY_3DS             // Nintendo 3DS
#define ICE_JOY_NDS             // Nintendo DS
#define ICE_JOY_PSP             // Sony PlayStation Portable
#define ICE_JOY_PSVITA          // Sony PlayStation Vita
#define ICE_JOY_PS1             // Sony PlayStation 1
#define ICE_JOY_PS2             // Sony PlayStation 2
#define ICE_JOY_PS3             // Sony PlayStation 3
#define ICE_JOY_PS4             // Sony PlayStation 4
#define ICE_JOY_BEOS            // BeOS and Haiku

// In case you want to build DLL on Microsoft Windows!
// Keep in mind you should set backend (But it's defined by default if not...)
#define ICE_JOY_DLLEXPORT
#define ICE_JOY_DLLIMPORT

// Android helpers
#define ICE_JOY_ANDROID_CUSTOM_INPUT_EVENT_HANDLERS                     // Allows ice_joy to call custom events via 2 definitions above
#define ANDROID_CMD_HANDLE_FUNC     android_cmd_handling_func_name      // Once loop, ice_joy will call android_cmd_handling_func_name inside command event function
#define ANDROID_INPUT_HANDLE_FUNC   android_input_handling_func_name    // Once loop, ice_joy will call android_input_handling_func_name inside input events function
```

### Functions

```c
// Connection, Misc, etc...
ice_joy_bool ice_joy_init(void);                                                   // Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ice_joy_bool ice_joy_connected(int ice_joy_index);                                 // Returns ICE_JOY_TRUE if Joystick at index ice_joy_index is connected, Else returns ICE_JOY_FALSE.
int          ice_joy_joysticks_count(void);                                        // Returns count of current connected Joysticks as integer.
ice_joy_str  ice_joy_name(int ice_joy_index);                                      // Returns Joystick's name at index ice_joy_index as string.
ice_joy_bool ice_joy_update(int ice_joy_index);                                    // Updates Joystick's state(s) at index ice_joy_index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
int          ice_joy_axis_count(int ice_joy_index);                                // Returns count of axes in Joystick at index ice_joy_index as integer.
int          ice_joy_buttons_count(int ice_joy_index);                             // Returns count of buttons in Joystick at index ice_joy_index as integer.
ice_joy_bool ice_joy_close(void);                                                  // Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.

// Buttons
ice_joy_bool ice_joy_button_down(int ice_joy_index, int button);                   // Returns ICE_JOY_TRUE if button from Joystick at index ice_joy_index is pressed, Else returns ICE_JOY_FALSE.
ice_joy_bool ice_joy_button_up(int ice_joy_index, int button);                     // Returns ICE_JOY_TRUE if button from Joystick at index ice_joy_index is pressed, Else returns ICE_JOY_FALSE.
ice_joy_bool ice_joy_button_pressed(int ice_joy_index, int button);                // Returns ICE_JOY_TRUE if button from Joystick at index ice_joy_index is pressed, Else returns ICE_JOY_FALSE.
ice_joy_bool ice_joy_button_released(int ice_joy_index, int button);               // Returns ICE_JOY_TRUE if button from Joystick at index ice_joy_index is pressed, Else returns ICE_JOY_FALSE.

// Analogs and Hats (Hats might be removed if not compatible...)
ice_joy_vec2 ice_joy_analog_movement(int ice_joy_index, ice_joy_analog analog);    // Returns 2D vector position containing movement of analog from Joystick at index ice_joy_index.
ice_joy_bool ice_joy_hat_pressed(int ice_joy_index, int hat);                      // Returns ICE_JOY_TRUE if Hat is pressed or ICE_JOY_FALSE if not.
```

