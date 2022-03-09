local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef

ffi_cdef([[
/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_cpu_bool {
    ICE_CPU_FALSE   = -1,
    ICE_CPU_TRUE    = 0
} ice_cpu_bool;

/* Struct that contains informations about the CPU (Name, Cores, etc...) */
typedef struct ice_cpu_info {
    const char *name;
    unsigned cores;
} ice_cpu_info;

/* ============================== Functions ============================== */

/* Retrieves info about CPU and stores info into ice_cpu_info struct by pointing to, Returns ICE_CPU_TRUE on success or ICE_CPU_FALSE on failure */
ice_cpu_bool ice_cpu_get_info(ice_cpu_info *cpu_info);
]])

return ffi_load("ice_cpu")
