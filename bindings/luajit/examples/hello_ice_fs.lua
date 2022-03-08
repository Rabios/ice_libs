local ffi = require("ffi")
local lib = require("ice_fs")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  -- Struct that contains modification date information
  local mod_date = ffi.new("ice_fs_date")

  -- To store result of called functions
  local res
  
  -- Create a directory of name "surprise" if does not exists
  res = ice_fs_create("surprise", ICE_FS_OBJECT_TYPE_DIR)

  -- If function failed to fetch RAM info, Trace error then terminate the program
  if (res == ICE_FS_FALSE) then
    print("ERROR: failed to create a directory!")
    return -1
  end
  
  -- Create a file with content written with no append (overwrite)
  res = ice_fs_file_write("surprise/iCe_SeCrEt_MeSsAgE.txt", "ice_libs makes C more enjoyable! :)", ICE_FS_FALSE)
  
  -- If the function failed to create the file, Trace error then terminate the program
  if (res == ICE_FS_FALSE) then
    print("ERROR: failed to create a file!")
    return -1
  end

  -- Rename the created file to another name in same path
  res = ice_fs_rename("surprise/iCe_SeCrEt_MeSsAgE.txt", "surprise/ice_secret_message.txt")
  
  -- If the function failed to rename the file, Trace error then terminate the program
  if (res == ICE_FS_FALSE) then
    print("ERROR: failed to rename the created file!")
    return -1
  end
  
  -- Get modification date of the created file
  res = ice_fs_get_date("surprise/ice_secret_message.txt", ICE_FS_LAST_MODIFICATION_DATE, mod_date)
  
  -- If the function failed to retrieve modification date of the created file, Trace error then terminate the program
  if (res == ICE_FS_FALSE) then
    print("ERROR: failed to retrieve modification date of the created file!")
    return -1
  end
  
  -- Print the modification date of the created file
  print("modification date of surprise/ice_secret_message.txt: " .. ffi.string(mod_date.str))

  return 0
end

return main()
