$gtk.ffi_misc.gtk_dlopen("ice_time")
include FFI::CExt

def tick args
  # Struct that contains Time information
  current_time ||= ICE_TIME_INFO_PTR.new
  
  # Fetch time information and store it in the struct
  res ||= ice_time_get_info(current_time)
  
  # If the function failed to fetch time information, Trace error then terminate the program!
  if (res != 0)
    puts("ERROR: failed to get time info!")
    return -1
  end
  
  # Print current time!
  args.outputs.primitives << {
    x: 5,
    y: 5.from_top,
    text: "Current Time: #{current_time.value.str.str}"
  }.to_label
  
  return 0
end
