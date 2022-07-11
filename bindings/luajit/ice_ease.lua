local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef
local _setmetatable = setmetatable

ffi_cdef([[
/* ============================== Data Types ============================== */

/* Easing Types */
typedef enum ice_ease_type {
    ICE_EASE_TYPE_PROGRESS = 0,
    ICE_EASE_TYPE_PENNER
} ice_ease_type;

/* ============================== Functions ============================== */

/* ------------------------------- Linear ------------------------------- */

double ice_ease_linear(ice_ease_type ease_type, ...);

/* ------------------------------ Sinusoidal ------------------------------ */

double ice_ease_sine_in(ice_ease_type ease_type, ...);
double ice_ease_sine_out(ice_ease_type ease_type, ...);
double ice_ease_sine_in_out(ice_ease_type ease_type, ...);

/* ------------------------------ Quadratic ------------------------------ */

double ice_ease_quad_in(ice_ease_type ease_type, ...);
double ice_ease_quad_out(ice_ease_type ease_type, ...);
double ice_ease_quad_in_out(ice_ease_type ease_type, ...);

/* -------------------------------- Cubic -------------------------------- */

double ice_ease_cubic_in(ice_ease_type ease_type, ...);
double ice_ease_cubic_out(ice_ease_type ease_type, ...);
double ice_ease_cubic_in_out(ice_ease_type ease_type, ...);

/* ------------------------------- Quartic ------------------------------- */

double ice_ease_quart_in(ice_ease_type ease_type, ...);
double ice_ease_quart_out(ice_ease_type ease_type, ...);
double ice_ease_quart_in_out(ice_ease_type ease_type, ...);

/* ------------------------------- Quintic ------------------------------- */

double ice_ease_quint_in(ice_ease_type ease_type, ...);
double ice_ease_quint_out(ice_ease_type ease_type, ...);
double ice_ease_quint_in_out(ice_ease_type ease_type, ...);

/* ----------------------------- Exponential ----------------------------- */

double ice_ease_expo_in(ice_ease_type ease_type, ...);
double ice_ease_expo_out(ice_ease_type ease_type, ...);
double ice_ease_expo_in_out(ice_ease_type ease_type, ...);

/* ------------------------------ Circular ------------------------------ */

double ice_ease_circ_in(ice_ease_type ease_type, ...);
double ice_ease_circ_out(ice_ease_type ease_type, ...);
double ice_ease_circ_in_out(ice_ease_type ease_type, ...);

/* ------------------------------ Elastic ------------------------------ */

double ice_ease_elastic_in(ice_ease_type ease_type, ...);
double ice_ease_elastic_out(ice_ease_type ease_type, ...);
double ice_ease_elastic_in_out(ice_ease_type ease_type, ...);

/* ------------------------------- Back -------------------------------- */

double ice_ease_back_in(ice_ease_type ease_type, ...);
double ice_ease_back_out(ice_ease_type ease_type, ...);
double ice_ease_back_in_out(ice_ease_type ease_type, ...);

/* ------------------------------ Bounce ------------------------------- */

double ice_ease_bounce_in(ice_ease_type ease_type, ...);
double ice_ease_bounce_out(ice_ease_type ease_type, ...);
double ice_ease_bounce_in_out(ice_ease_type ease_type, ...);
]])

local l = ffi_load("ice_ease")
local mt = { __index = l }
local lib = _setmetatable({}, mt)

lib.ICE_EASE_PI       = 3.1415926535897932384626433832795 -- Pi
lib.ICE_EASE_TAU      = 6.283185307179586476925286766559  -- Tau (Double Pi)
lib.ICE_EASE_HALF_PI  = 1.5707963267948966192313216916398 -- Half of Pi

return lib
