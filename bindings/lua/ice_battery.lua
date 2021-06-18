local ffi = require("ffi")

ffi.cdef([[
typedef enum {
    ICE_BATTERY_TRUE    = 0,
    ICE_BATTERY_FALSE   = -1,
} ice_battery_bool;

ice_battery_bool ice_battery_init(void);
int ice_battery_level(void);
ice_battery_bool ice_battery_charging(void);
ice_battery_bool ice_battery_level_full(void);
ice_battery_bool ice_battery_level_high(void);
ice_battery_bool ice_battery_level_mid(void);
ice_battery_bool ice_battery_level_low(void);
ice_battery_bool ice_battery_close(void);
]])

local lib = ffi.load("ice_battery")

for k, v in pairs(lib) do
  _G[k] = lib[k]
end
