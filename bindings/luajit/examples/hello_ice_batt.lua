local ffi = require("ffi")
local lib = require("ice_batt")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  -- Struct that contains information about the battery
  local batt = ffi.new("ice_batt_info")
  
  -- Fetch battery information and store the information in the struct
  local err = ice_batt_get_info(batt)
  
  -- If the function failed to fetch battery information, Trace error then terminate the program
  if (err ~= ICE_BATT_ERROR_OK) then
    print("ERROR: failed to fetch battery information!")
    return -1
  end
  
  -- Print the informations
  print("Device has battery: " .. ((batt.exists == ICE_BATT_TRUE) and "YES" or "NO") ..
        "\nIs battery charging: " .. ((batt.charging == ICE_BATT_TRUE) and "YES" or "NO") ..
        "\nBattery Level: " .. batt.level)
  
  return 0
end

return main()
