$gtk.ffi_misc.gtk_dlopen("ice_ram")
include FFI::CExt

def tick args
  # Struct that contains RAM information
  ram ||= ICE_RAM_INFO_PTR.new
  
  # Fetch RAM info
  res = ice_ram_get_info(ram)
  
  # If function failed to fetch RAM info, Trace error then terminate the program
  if (res == -1)
    puts("ERROR: failed to get RAM info!")
    return -1
  end
  
  # Print RAM info (free, used, total) in bytes
  args.outputs.primitives << {
    x: 5,
    y: 5.from_top,
    text: "Free RAM: #{ram.value.free} bytes"
  }.to_label
  
  args.outputs.primitives << {
    x: 5,
    y: 30.from_top,
    text: "Used RAM: #{ram.value.used} bytes"
  }.to_label
  
  args.outputs.primitives << {
    x: 5,
    y: 55.from_top,
    text: "Total RAM: #{ram.value.total} bytes"
  }.to_label
end
