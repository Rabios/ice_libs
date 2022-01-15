local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef
local _setmetatable = setmetatable

ffi_cdef([[
/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_ffi_bool {
    ICE_FFI_FALSE = -1,
    ICE_FFI_TRUE = 0
} ice_ffi_bool;

/* Handle, Represents pointer to loaded shared library or symbol loaded from shared library */
typedef void* ice_ffi_handle;

/* ============================== Functions ============================== */

/* Loads shared library from path, Returns handle of loaded shared library on success or NULL on failure */
ice_ffi_handle ice_ffi_load(const char *path);

/* Unloads shared library loaded via ice_ffi_load, Returns ICE_FFI_TRUE on success or ICE_FFI_FALSE on failure */
ice_ffi_bool ice_ffi_unload(ice_ffi_handle lib);

/* Loads symbol from shared library loaded via ice_ffi_load, Returns pointer to loaded symbol on success or NULL on failure */
ice_ffi_handle ice_ffi_get(ice_ffi_handle lib, const char *symbol);
]])

local lib = ffi_load("ice_ffi")
_setmetatable(_G, { __index = lib })
