### ice_easings.h Documentation

### Definitions

```c
// Implements ice_easings source code, Works same as #pragma once
#define ICE_EASINGS_IMPL

#define ICE_EASINGS_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_EASINGS_STATIC  // Makes functions of the library static with static keyword
#define ICE_EASINGS_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_EASINGS_CALLCONV_VECTORCALL
#define ICE_EASINGS_CALLCONV_FASTCALL
#define ICE_EASINGS_CALLCONV_STDCALL
#define ICE_EASINGS_CALLCONV_CDECL

// In case you want to build DLL on Microsoft Windows!
#define ICE_EASINGS_DLLEXPORT
#define ICE_EASINGS_DLLIMPORT
```

### Functions

```c
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
```
