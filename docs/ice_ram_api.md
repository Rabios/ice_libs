# ice_ram.h Documentation

### Definitions

```c
// Typedefs
typedef unsigned long long int ice_ram_bytes;

// Definitions
// Implements ice_ram source code, Works same as #pragma once
#define ICE_RAM_IMPL

#define ICE_RAM_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_RAM_STATIC  // Makes functions of the library static with static keyword
#define ICE_RAM_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_RAM_CALLCONV_VECTORCALL
#define ICE_RAM_CALLCONV_FASTCALL
#define ICE_RAM_CALLCONV_STDCALL
#define ICE_RAM_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_RAM_MICROSOFT       // Microsoft platforms
#define ICE_RAM_APPLE           // Apple platforms
#define ICE_RAM_WEB             // Node.js and Web (Emscripten)
#define ICE_RAM_PSP             // Sony PlayStation Portable
#define ICE_RAM_UNIX            // Elsewhere

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_RAM_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
#define ICE_RAM_DLLEXPORT
#define ICE_RAM_DLLIMPORT
```

### Functions

```c
ice_ram_bytes ice_ram_total(void);  // Returns total memory (RAM) device has, In bytes.
ice_ram_bytes ice_ram_free(void);   // Returns available/free memory (RAM) device has, In bytes.
```
