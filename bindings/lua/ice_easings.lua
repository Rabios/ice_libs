local ffi = require("ffi")

ffi.cdef([[
double ice_easings_linear_none(double t, double b, double c, double d);
double ice_easings_linear_in(double t, double b, double c, double d);
double ice_easings_linear_out(double t, double b, double c, double d);
double ice_easings_linear_in_out(double t, double b, double c, double d);

double ice_easings_sine_in(double t, double b, double c, double d);
double ice_easings_sine_out(double t, double b, double c, double d);
double ice_easings_sine_in_out(double t, double b, double c, double d);

double ice_easings_cubic_in(double t, double b, double c, double d);
double ice_easings_cubic_out(double t, double b, double c, double d);
double ice_easings_cubic_in_out(double t, double b, double c, double d);

double ice_easings_quint_in(double t, double b, double c, double d);
double ice_easings_quint_out(double t, double b, double c, double d);
double ice_easings_quint_in_out(double t, double b, double c, double d);

double ice_easings_circ_in(double t, double b, double c, double d);
double ice_easings_circ_out(double t, double b, double c, double d);
double ice_easings_circ_in_out(double t, double b, double c, double d);

double ice_easings_elastic_in(double t, double b, double c, double d);
double ice_easings_elastic_out(double t, double b, double c, double d);
double ice_easings_elastic_in_out(double t, double b, double c, double d);

double ice_easings_quad_in(double t, double b, double c, double d);
double ice_easings_quad_out(double t, double b, double c, double d);
double ice_easings_quad_in_out(double t, double b, double c, double d);

double ice_easings_quart_in(double t, double b, double c, double d);
double ice_easings_quart_out(double t, double b, double c, double d);
double ice_easings_quart_in_out(double t, double b, double c, double d);

double ice_easings_expo_in(double t, double b, double c, double d);
double ice_easings_expo_out(double t, double b, double c, double d);
double ice_easings_expo_in_out(double t, double b, double c, double d);

double ice_easings_back_in(double t, double b, double c, double d);
double ice_easings_back_out(double t, double b, double c, double d);
double ice_easings_back_in_out(double t, double b, double c, double d);

double ice_easings_bounce_in(double t, double b, double c, double d);
double ice_easings_bounce_out(double t, double b, double c, double d);
double ice_easings_bounce_in_out(double t, double b, double c, double d);
]])

local lib = ffi.load("ice_easings")

_G.ICE_EASINGS_PI = 3.14159265358979323846

for k, v in pairs(lib) do
  _G[k] = lib[k]
end
