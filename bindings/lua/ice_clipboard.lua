local ffi = require("ffi")

ffi.cdef([[
typedef enum {
    ICE_CLIPBOARD_TRUE  = 0,
    ICE_CLIPBOARD_FALSE = -1,
} ice_clipboard_bool;

ice_clipboard_bool ice_clipboard_init(void);
ice_clipboard_bool ice_clipboard_set(char* text);
char*              ice_clipboard_get(void);
ice_clipboard_bool ice_clipboard_text(char* text);
ice_clipboard_bool ice_clipboard_clear(void);
ice_clipboard_bool ice_clipboard_close(void);
]])

local lib = ffi.load("ice_clipboard")

for k, v in pairs(lib) do
  _G[k] = lib[k]
end
