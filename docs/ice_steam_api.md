# ice_steam.h Documentation

### Enums

```c
typedef enum ice_steam_bool {
    ICE_STEAM_TRUE = 0,
    ICE_STEAM_FALSE = -1,
} ice_steam_bool;
```

### Definitions

```c
// Definitions
// Implements ice_steam source code, Works same as #pragma once
#define ICE_STEAM_IMPL

#define ICE_STEAM_EXTERN  // Extern functions of the library with extern keyword (Enabled by default) (Enabled by default)
#define ICE_STEAM_STATIC  // Makes functions of the library static with static keyword
#define ICE_STEAM_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_STEAM_CALLCONV_VECTORCALL
#define ICE_STEAM_CALLCONV_FASTCALL
#define ICE_STEAM_CALLCONV_STDCALL
#define ICE_STEAM_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_STEAM_MICROSOFT     // Microsoft platforms
#define ICE_STEAM_UNIX          // Unix and Unix-like platforms
#define ICE_STEAM_BEOS          // BeOS and Haiku

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_STEAM_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
#define ICE_STEAM_DLLEXPORT
#define ICE_STEAM_DLLIMPORT
```

### Functions

```c
ice_steam_bool  ice_steam_init(void);       // Initializes SteamWorks C API, Returns ICE_STEAM_TRUE on success or ICE_STEAM_FALSE on failure.
ice_steam_bool  ice_steam_close(void);      // Deinitializes SteamWorks C API, Returns ICE_STEAM_TRUE on success or ICE_STEAM_FALSE on failure.

// NOTE: ice_al loads SteamWorks C API based on steam.candle by EvilPudding on GitHub so functions and definitions of them exist in ice_steam library!
```
