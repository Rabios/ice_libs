local ffi = require("ffi")
local lib = require("ice_ffi")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  -- To store result of unloading the shared library/object
  local unload_res
  
  -- Handle for shared library/object
  local lib
  
  -- function from shared library/object
  local F42
  
  -- Define path of the shared library/object depending on platform
  local path

  if ffi.os == "Windows" then
    path = "lib42.dll"
  else
    path = "./lib42.so"
  end
  
  -- Load the shared library/object
  lib = ice_ffi_load(path)
  
  -- If the function failed to load the shared library/object, Trace error then terminate the program
  if (lib == nil) then
    print("ERROR: failed to load shared library/object!")
    return -1
  end
  
  -- If the shared library/object loaded successfully, Get the function F42 symbol to call it!
  F42 = ffi.cast("unsigned (*)(void)", ice_ffi_get(lib, "F42"))
  
  -- If the function failed to get symbol from shared library/object, Trace error then terminate the program
  if (F42 == nil) then
    print("ERROR: failed to get symbol from shared library/object!")
    return -1
  end
  
  -- Call the function and print the result!
  print("F42 call result: " .. tonumber(F42()))
  
  -- When done, Unload symbols and the shared library/object
  F42 = nil
  unload_res = ice_ffi_unload(lib)
  
  -- If the function failed to unload shared library/object, Trace error then terminate the program
  if (unload_res == ICE_FFI_FALSE) then
    print("ERROR: failed to unload shared library/object!")
    return -1
  end
  
  return 0
end

return main()
