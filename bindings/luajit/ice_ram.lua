local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef
local _setmetatable = setmetatable

ffi_cdef([[
/* ============================== Data Types ============================== */

/* Typedef for free and used and total bytes of RAM */
typedef unsigned long long ice_ram_bytes;
    
/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_ram_bool {
    ICE_RAM_FALSE   = -1,
    ICE_RAM_TRUE    = 0
} ice_ram_bool;
    
/* RAM Information, Contains free and used and total RAM in bytes */
typedef struct ice_ram_info { ice_ram_bytes free, used, total; } ice_ram_info;
    
/* ============================== Functions ============================== */
    
/* Retrives info about RAM (free, used, total) in bytes and stores info into ice_ram_info struct by pointing to, Returns ICE_RAM_TRUE on success or ICE_RAM_FALSE on failure */
ice_ram_bool ice_ram_get_info(ice_ram_info *ram_info);
]])

local lib = ffi_load("ice_ram")
_setmetatable(_G, { __index = lib })
