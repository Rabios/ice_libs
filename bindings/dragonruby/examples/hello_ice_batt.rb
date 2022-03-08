require "app/ice_batt.rb"

def tick args
  # Struct that contains information about the battery
  batt ||= ICE_BATT_INFO_PTR.new

  # Fetch battery information and store the information in the struct
  err = ice_batt_get_info(batt)
  
  # If the function failed to fetch battery information, Trace error then terminate the program
  if (err != ICE_BATT_ERROR_OK)
    puts("ERROR: failed to fetch battery information!")
    return -1
  end
  
  # Print the informations
  args.outputs.primitives << {
    x: 5,
    y: 5.from_top,
    text: "Device has battery: #{((batt.value.exists == ICE_BATT_TRUE) ? "YES" : "NO")}"
  }.to_label
  
  args.outputs.primitives << {
    x: 5,
    y: 30.from_top,
    text: "Is battery charging: #{((batt.value.charging == ICE_BATT_TRUE) ? "YES" : "NO")}"
  }.to_label
  
  args.outputs.primitives << {
    x: 5,
    y: 55.from_top,
    text: "Battery Level: #{batt.value.level}"
  }.to_label
end
