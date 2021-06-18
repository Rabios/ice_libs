local ffi = require("ffi")

ffi.cdef([[
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

ice_joy_bool ice_joy_init(void);                                                             // Initializes ice_joy library, Returns ICE_JOY_TRUE on success or ICE_JOY_FALSE on failure.
ice_joy_bool ice_joy_connected(ice_joy_player index);                                        // Returns ICE_JOY_TRUE if Joystick at index index is connected, Else returns ICE_JOY_FALSE.
int          ice_joy_joysticks_count(void);                                                  // Returns count of current connected Joysticks as integer.
ice_joy_str  ice_joy_name(ice_joy_player index);                                             // Returns Joystick's name at index index as string.
ice_joy_bool ice_joy_update(ice_joy_player index);                                           // Updates Joystick's state(s) at index index, Returns ICE_JOY_TRUE on update success and ICE_JOY_FALSE on update failure.
int          ice_joy_axis_count(ice_joy_player index);                                       // Returns count of axes in Joystick at index index as integer.
int          ice_joy_buttons_count(ice_joy_player index);                                    // Returns count of buttons in Joystick at index index as integer.
ice_joy_bool ice_joy_close(void);                                                            // Closes ice_joy library, Returns ICE_JOY_TRUE on success and ICE_JOY_FALSE on failure.

// NOTE: ice_joy_button_code used by functions below, So no need to use it...
ice_joy_bool ice_joy_button_down(ice_joy_player index, ice_joy_button button);               // Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ice_joy_bool ice_joy_button_up(ice_joy_player index, ice_joy_button button);                 // Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ice_joy_bool ice_joy_button_pressed(ice_joy_player index, ice_joy_button button);            // Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.
ice_joy_bool ice_joy_button_released(ice_joy_player index, ice_joy_button button);           // Returns ICE_JOY_TRUE if button from Joystick at index index is pressed, Else returns ICE_JOY_FALSE.

ice_joy_vec2 ice_joy_analog_movement(ice_joy_player index, ice_joy_analog analog);           // Returns 2D vector position containing movement of analog from Joystick at index index.
ice_joy_bool ice_joy_hat_pressed(ice_joy_player index, ice_joy_hat hat);                     // Returns ICE_JOY_TRUE if Hat is pressed or ICE_JOY_FALSE if not.
]])

local lib = ffi.load("ice_joy")

for k, v in pairs(lib) do
  _G[k] = lib[k]
end
