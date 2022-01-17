local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef
local _setmetatable = setmetatable

ffi_cdef([[
/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_clip_bool {
    ICE_CLIP_FALSE  = -1,
    ICE_CLIP_TRUE   = 0
} ice_clip_bool;
    
/* ============================== Functions ============================== */

/* [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_clip on Android, This Should be called first before other ice_clip.h functions */
void ice_clip_use_native_activity(void *activity);

/* [WINDOWS-ONLY, OPTIONAL] Sets the Window to be used with ice_clip, This is optional feature as the Windows implementation do not need Window by default */
void ice_clip_use_window(void *window);
    
/* Retrieves the text from Clipboard, Returns the text on success or NULL on failure */
const char* ice_clip_get(void);
    
/* Sets the Clipboard text, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ice_clip_bool ice_clip_set(const char *text);
    
/* Clears the Clipboard, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ice_clip_bool ice_clip_clear(void);
]])

local lib = ffi_load("ice_clip")
_setmetatable(_G, { __index = lib })
