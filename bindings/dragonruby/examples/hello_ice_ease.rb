require "app/ice_ease.rb"

$gtk.show_console

def boot args
  # Use linear easing, With 1 argument (easings.net)
  linear1 = ice_ease_linear(ICE_EASE_TYPE_PROGRESS, 5.0)
  
  # Use linear easing, But with 4 arguments (Robert Penner's version)
  linear4 = ice_ease_linear(ICE_EASE_TYPE_PENNER, 1.0, 2.0, 3.0, 4.0)
  
  # Print the results...
  puts("Linear easing with one variable: #{linear1}\nLinear easing with four variables: #{linear4}\n")
  
  return 0
end
