local ffi = require("ffi")

ffi.cdef([[
typedef enum {
    ICE_CPU_ARCH_NONE = -1,  // Trigger 16 and 8 bit CPUs
    ICE_CPU_ARCH_X86,        // 32 bit
    ICE_CPU_ARCH_X86_64,     // x64, x86_64, AMD64 and Intel 64
} ice_cpu_arch;

unsigned int ice_cpu_cores_count(void);         // Returns count of CPU cores device has as unsigned integer.
ice_cpu_arch ice_cpu_get_arch(void);            // Returns CPU architecture.
char* ice_cpu_name(void);                       // Returns CPU name used by device as string.
]])

local lib = ffi.load("ice_cpu")

for k, v in pairs(lib) do
  _G[k] = lib[k]
end
