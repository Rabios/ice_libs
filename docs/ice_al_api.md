# ice_al.h Documentation

### Enums

```c
typedef enum ice_al_bool {
    ICE_AL_TRUE = 0,
    ICE_AL_FALSE = -1,
} ice_al_bool;
```

### Definitions

```c
// Definitions
// Implements ice_al source code, Works same as #pragma once
#define ICE_AL_IMPL

#define ICE_AL_EXTERN  // Extern functions of the library with extern keyword (Enabled by default) (Enabled by default)
#define ICE_AL_STATIC  // Makes functions of the library static with static keyword
#define ICE_AL_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_AL_CALLCONV_VECTORCALL
#define ICE_AL_CALLCONV_FASTCALL
#define ICE_AL_CALLCONV_STDCALL
#define ICE_AL_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_AL_MICROSOFT     // Microsoft platforms
#define ICE_AL_UNIX          // Unix and Unix-like platforms
#define ICE_AL_BEOS          // BeOS and Haiku

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_AL_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
#define ICE_AL_DLLEXPORT
#define ICE_AL_DLLIMPORT
```

### Functions

```c
ice_al_bool  ice_al_init(void);       // Initializes OpenAL, Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure.
ice_al_bool  ice_al_close(void);      // Deinitializes OpenAL, Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure.

// NOTE: ice_al loads OpenAL API from al.h and alc.h so functions and definitions of them exist in ice_al library!
```
