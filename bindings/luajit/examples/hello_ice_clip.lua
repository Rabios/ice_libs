local ffi = require("ffi")
local lib = require("ice_clip")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  -- To store result of called functions
  local res
  
  -- String to copy to clipboard later...
  local str = "SPEED!"
  
  -- Retrieve the clipboard text
  local text = ice_clip_get()
  
  -- If the function failed to retrieve Clipboard text or Clipboard has no text then trace log a note, Else print the retrieved text...
  if (text == nil) then
    print("LOG: failed to retrieve Clipboard text, Maybe the Clipboard does not contain text?")
  else
    print("Text from the Clipboard: " .. ffi.string(text))
  end
  
  -- Clear the Clipboard
  res = ice_clip_clear()
  
  -- If the function failed to clear the Clipboard, Trace error then terminate the program
  if (res == ICE_CLIP_FALSE) then
    print("ERROR: failed to clear the Clipboard!")
    return -1
  end
  
  -- Copy text to Clipboard
  res = ice_clip_set(str)
  
  -- If the function failed to copy text to the Clipboard, Trace error then terminate the program
  if (res == ICE_CLIP_FALSE) then
    print("ERROR: Failed to copy text to Clipboard!")
    return -1
  end
    
  print("Text copied to the Clipboard: " .. str)

  return 0
end

return main()
