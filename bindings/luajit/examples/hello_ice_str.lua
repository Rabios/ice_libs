local ffi = require("ffi")
local lib = require("ice_str")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  -- Create a string repeated for multiple times
  local haha = ice_str_dup("HA", 8) -- HAHAHAHAHAHAHAHA
  
  -- If the function failed to allocate string, Trace error then terminate the program
  if (haha == 0) then
    print("ERROR: failed to allocate string!")
    return -1
  end
  
  -- Print the string, Once we done we deallocate/free the string
  print(ffi.string(haha))
  ice_str_free(haha)
  
  return 0
end

return main()
