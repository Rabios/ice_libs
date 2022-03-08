require "app/ice_fs.rb"

$gtk.show_console

def boot args
  # Struct that contains modification date information
  mod_date ||= ICE_FS_DATE_PTR.new
  
  # To store result of called functions
  res |= nil
  
  # Create a directory of name "surprise" if does not exists
  res = ice_fs_create("surprise", ICE_FS_OBJECT_TYPE_DIR)
  
  # If the function failed to create the directory, Trace error then terminate the program
  if (res == ICE_FS_FALSE)
    puts("ERROR: failed to create a directory!")
    return -1
  end
  
  # Create a file with content written with no append (overwrite)
  res = ice_fs_file_write("surprise/iCe_SeCrEt_MeSsAgE.txt", "ice_libs makes C more enjoyable! :)", ICE_FS_FALSE)
  
  # If the function failed to create the file, Trace error then terminate the program
  if (res == ICE_FS_FALSE)
    puts("ERROR: failed to create a file!")
    return -1
  end
  
  # Rename the created file to another name in same path
  res = ice_fs_rename("surprise/iCe_SeCrEt_MeSsAgE.txt", "surprise/ice_secret_message.txt")
  
  # If the function failed to rename the file, Trace error then terminate the program
  if (res == ICE_FS_FALSE)
    puts("ERROR: failed to rename the created file!")
    return -1
  end
  
  # Get modification date of the created file
  res = ice_fs_get_date("surprise/ice_secret_message.txt", 0, mod_date)
  
  # If the function failed to retrieve modification date of the created file, Trace error then terminate the program
  if (res == ICE_FS_FALSE)
    puts("ERROR: failed to retrieve modification date of the created file!")
    return -1
  end
  
  # Print the modification date of the created file
  puts("modification date of surprise/ice_secret_message.txt: #{mod_date.value.str.str}")

  return 0
end
