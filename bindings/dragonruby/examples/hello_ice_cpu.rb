require "app/ice_cpu.rb"

$gtk.show_console

def boot args
  # Struct that contains CPU information
  cpu ||= ICE_CPU_INFO_PTR.new

  # Get CPU information
  res ||= ice_cpu_get_info(cpu)
  
  # If the function failed to retrieve CPU information, Trace error then terminate the program
  if (res == ICE_CPU_FALSE)
    puts("ERROR: failed to retrieve CPU information!")
    return -1
  end
  
  # Print the informations
  puts("CPU Name: #{cpu.value.name.str}\nCPU Cores: #{cpu.value.cores}")

  return 0
end
