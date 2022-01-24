local lib = require("ice_ease")

-- This allows the functions of the bindings to be globally called...
setmetatable(_G, { __index = lib })

local function main()
  -- Use linear easing, With 1 argument (easings.net)
  local linear1 = ice_ease_linear(ICE_EASE_TYPE_PROGRESS, 5.0)
  
  -- Use linear easing, But with 4 arguments (Robert Penner's version)
  local linear4 = ice_ease_linear(ICE_EASE_TYPE_PENNER, 1.0, 2.0, 3.0, 4.0)
  
  -- Print the results...
  print("Linear easing with one variable: " .. linear1 .. "\nLinear easing with four variables: " .. linear4)
  
  return 0
end

return main()
