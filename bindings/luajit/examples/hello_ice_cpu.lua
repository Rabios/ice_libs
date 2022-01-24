local ffi = require("ffi")
local lib = require("ice_cpu")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  -- Struct that contains CPU information
  local cpu = ffi.new("ice_cpu_info")
  
  -- Get CPU information
  local res = ice_cpu_get_info(cpu)
  
  -- If the function failed to retrieve CPU information, Trace error then terminate the program
  if (res == ICE_CPU_FALSE) then
    print("ERROR: failed to retrieve CPU information!")
    return -1
  end
  
  -- Print the informations
  print("CPU Name: " .. ffi.string(cpu.name) .. "\nCPU Cores: " .. cpu.cores)
  
  return 0
end

return main()
