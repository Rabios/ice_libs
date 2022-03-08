require "app/ice_str.rb"

$gtk.show_console

def boot args
  # Create a string repeated for multiple times
  haha ||= ice_str_dup("HA", 8) # HAHAHAHAHAHAHAHA
  
  # If the function failed to allocate string, Trace error then terminate the program
  if (haha == 0)
    puts("ERROR: failed to allocate string!")
    return -1
  end
  
  # Print the string, Once we done we deallocate/free the string
  puts(haha.str)
  ice_str_free(haha)

  return 0
end
