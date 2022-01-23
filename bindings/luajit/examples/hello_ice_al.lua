local ffi = require("ffi")
local lib = require("ice_al")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  local res
  
  -- OpenAL device and OpenAL device name
  local device_name
  local dev 

  -- Define the path of the OpenAL shared library/object depending on the platform (NOTE: You can also use OpenAL-soft) */
  local path

  if ffi.os == "Windows" then
    path = "OpenAL32.dll"
  else
    path = "./liboal.so"
  end
  
  -- Load OpenAL shared library/object then load OpenAL API
  res = ice_al_load(path)
  
  -- If the function failed to load OpenAL shared library and failed to load OpenAL API, Trace error then terminate the program
  if (res == ICE_AL_FALSE) then
    print("ERROR: failed to load OpenAL shared library/object!")
    return -1
  end
  
  -- Get the default OpenAL audio device and initialize it
  local device_name = alcGetString(nil, ALC_DEFAULT_DEVICE_SPECIFIER)
  local dev = alcOpenDevice(device_name)
  
  -- If the function failed to initialize the default OpenAL device, Trace error then terminate the program
  if (dev == 0) then
    print("ERROR: failed to open audio device!")
    return -1
  end
  
  print("OpenAL audio device works!")
  
  -- Once done close the OpenAL device, If the function failed to close the default OpenAL device, Trace error then terminate the program
  if (alcCloseDevice(dev) == ALC_FALSE) then
    print("ERROR: failed to close audio device!")
    return -1
  end
    
  return 0
end

return main()
