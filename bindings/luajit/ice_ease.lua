local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef
local _setmetatable = setmetatable

ffi_cdef([[
/* ============================== Data Types ============================== */

/* Easing Types */
typedef enum ice_ease_type {
    ICE_EASE_TYPE_PROGRESS  = 1,
    ICE_EASE_TYPE_PENNER    = 4
} ice_ease_type;

/* ============================== Functions ============================== */

/* Functions for Linear Easing */
double ice_ease_linear(ice_ease_type ease_type, ...);

/* Functions for Quadratic Easing */
double ice_ease_quad_in(ice_ease_type ease_type, ...);
double ice_ease_quad_out(ice_ease_type ease_type, ...);
double ice_ease_quad_in_out(ice_ease_type ease_type, ...);

/* Functions for Cubic Easing */
double ice_ease_cubic_in(ice_ease_type ease_type, ...);
double ice_ease_cubic_out(ice_ease_type ease_type, ...);
double ice_ease_cubic_in_out(ice_ease_type ease_type, ...);

/* Functions for Quartic Easing */
double ice_ease_quart_in(ice_ease_type ease_type, ...);
double ice_ease_quart_out(ice_ease_type ease_type, ...);
double ice_ease_quart_in_out(ice_ease_type ease_type, ...);

/* Functions for Quintic Easing */
double ice_ease_quint_in(ice_ease_type ease_type, ...);
double ice_ease_quint_out(ice_ease_type ease_type, ...);
double ice_ease_quint_in_out(ice_ease_type ease_type, ...);

/* Functions for Sinusoidal Easing */
double ice_ease_sine_in(ice_ease_type ease_type, ...);
double ice_ease_sine_out(ice_ease_type ease_type, ...);
double ice_ease_sine_in_out(ice_ease_type ease_type, ...);

/* Functions for Exponential Easing */
double ice_ease_expo_in(ice_ease_type ease_type, ...);
double ice_ease_expo_out(ice_ease_type ease_type, ...);
double ice_ease_expo_in_out(ice_ease_type ease_type, ...);

/* Functions for Circular Easing */
double ice_ease_circ_in(ice_ease_type ease_type, ...);
double ice_ease_circ_out(ice_ease_type ease_type, ...);
double ice_ease_circ_in_out(ice_ease_type ease_type, ...);

/* Functions for Elastic Easing */
double ice_ease_elastic_in(ice_ease_type ease_type, ...);
double ice_ease_elastic_out(ice_ease_type ease_type, ...);
double ice_ease_elastic_in_out(ice_ease_type ease_type, ...);

/* Functions for Back Easing */
double ice_ease_back_in(ice_ease_type ease_type, ...);
double ice_ease_back_out(ice_ease_type ease_type, ...);
double ice_ease_back_in_out(ice_ease_type ease_type, ...);

/* Functions for Bounce Easing */
double ice_ease_bounce_in(ice_ease_type ease_type, ...);
double ice_ease_bounce_out(ice_ease_type ease_type, ...);
double ice_ease_bounce_in_out(ice_ease_type ease_type, ...);
]])

local l = ffi_load("ice_ease")
local mt = { __index = l }
local lib = _setmetatable({}, mt)

lib.ICE_EASE_PI = 3.14159265358979323846

return lib
