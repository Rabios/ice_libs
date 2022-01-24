local ffi = require("ffi")
local lib = require("ice_ram")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  -- Struct that contains RAM information
  local ram = ffi.new("ice_ram_info")

  -- Fetch RAM info
  local res = ice_ram_get_info(ram)
  
  -- If function failed to fetch RAM info, Trace error then terminate the program
  if (res == ICE_RAM_FALSE) then
    print("ERROR: failed to get RAM info!")
    return -1
  end
  
  -- Print RAM info (free, used, total) in bytes
  print("Free RAM: " .. tonumber(ram.free) .. " bytes\n" ..
        "Used RAM: " .. tonumber(ram.used) .. " bytes\n" ..
        "Total RAM: " .. tonumber(ram.total) .. " bytes")

  return 0
end

return main()
