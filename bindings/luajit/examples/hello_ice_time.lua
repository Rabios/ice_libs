local ffi = require("ffi")
local lib = require("ice_time")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  -- Struct that contains Time information
  local current_time = ffi.new("ice_time_info")
  
  -- Fetch time information and store it in the struct
  local res = ice_time_get_info(current_time)
  
  -- If the function failed to fetch time information, Trace error then terminate the program!
  if (res ~= ICE_TIME_ERROR_OK) then
    print("ERROR: failed to retrieve time info!")
    return -1
  end
  
  -- Print current time!
  print("Current Time: " .. ffi.string(current_time.str))
  
  return 0
end

return main()
