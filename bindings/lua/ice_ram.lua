local ffi = require("ffi")

ffi.cdef([[
typedef unsigned long long int ice_ram_bytes;

ice_ram_bytes ice_ram_total(void);           // Returns total memory (RAM) device has, In bytes.
ice_ram_bytes ice_ram_free(void);            // Returns available/free memory (RAM) device has, In bytes.
]])

local lib = ffi.load("ice_ram")

for k, v in pairs(lib) do
  _G[k] = lib[k]
end
