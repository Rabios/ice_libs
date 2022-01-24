$gtk.ffi_misc.gtk_dlopen("ice_batt")
include FFI::CExt

def tick args
  # Struct that contains information about the battery
  batt ||= ICE_BATT_INFO_PTR.new

  # Fetch battery information and store the information in the struct
  err = ice_batt_get_info(batt)
  
  # If the function failed to fetch battery information, Trace error then terminate the program
  if (err != 0)
    puts("ERROR: failed to fetch battery information!")
    return -1
  end
  
  # Print the informations
  args.outputs.primitives << {
    x: 5,
    y: 5.from_top,
    text: "Device has battery: #{((batt.value.exists == 0) ? "YES" : "NO")}"
  }.to_label
  
  args.outputs.primitives << {
    x: 5,
    y: 30.from_top,
    text: "Is battery charging: #{((batt.value.charging == 0) ? "YES" : "NO")}"
  }.to_label
  
  args.outputs.primitives << {
    x: 5,
    y: 55.from_top,
    text: "Battery Level: #{batt.value.level}"
  }.to_label
end
