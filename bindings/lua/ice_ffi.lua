local ffi = require("ffi")

ffi.cdef([[
typedef enum {
    ICE_FFI_TRUE    = 0,
    ICE_FFI_FALSE   = -1,
} ice_ffi_bool;

typedef void* ice_ffi_handle;

ice_ffi_handle ice_ffi_load_library(char* path);                            // Loads a shared library (dll, so, dylib, etc...) from path, Returns ice_ffi_handle as handle to the library on success or NULL on failure.
ice_ffi_bool   ice_ffi_unload_library(ice_ffi_handle lib);                  // Unloads a shared library (dll, so, dylib, etc...) with handle from path, Returns ICE_FFI_TRUE on unload success or ICE_FFI_FALSE on failure.
ice_ffi_handle ice_ffi_get_address(ice_ffi_handle lib, char* proc_name);    // Gets address value of name proc_name from shared library handle, Returns ice_ffi_handle as handle to the address could be casted to function, variable, Or anything else on success or NULL on failure.
]])

local lib = ffi.load("ice_ffi")

for k, v in pairs(lib) do
  _G[k] = lib[k]
end
