local ffi = require("ffi")

ffi.cdef([[
typedef enum {
    ICE_MOUSE_BUTTON_LEFT,
    ICE_MOUSE_BUTTON_RIGHT,
    ICE_MOUSE_BUTTON_CENTER
} ice_mouse_button;

typedef enum {
    ICE_MOUSE_TRUE = 0,
    ICE_MOUSE_FALSE = -1
} ice_mouse_bool;

typedef struct ice_mouse_vec2 {
    float x;
    float y;
} ice_mouse_vec2;

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
]])

local lib = ffi.load("ice_mouse")

for k, v in pairs(lib) do
  _G[k] = lib[k]
end
