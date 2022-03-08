require "app/ice_clip.rb"

$gtk.show_console

def boot args
  # To store result of called functions
  res ||= nil
  
  # String to copy to clipboard later...
  str ||= "SPEED!"
  
  # Retrieve the clipboard text
  text ||= ice_clip_get()
  
  # If the function failed to retrieve Clipboard text or Clipboard has no text then trace log a note, Else print the retrieved text... */
  if (text.str == nil)
    puts("LOG: failed to retrieve Clipboard text, Maybe the Clipboard does not contain text?")
  else
    puts("Text from the Clipboard: #{text.str}")
  end
  
  # Clear the Clipboard
  res = ice_clip_clear()
  
  # If the function failed to clear the Clipboard, Trace error then terminate the program
  if (res == ICE_CLIP_FALSE)
    puts("ERROR: failed to clear the Clipboard!")
    return -1
  end
  
  # Copy text to Clipboard
  res = ice_clip_set(str)
  
  # If the function failed to copy text to the Clipboard, Trace error then terminate the program
  if (res == ICE_CLIP_FALSE)
    puts("ERROR: Failed to copy text to Clipboard!")
    return -1
  end
    
  puts("Text copied to the Clipboard: #{str}")
  
  return 0
end
