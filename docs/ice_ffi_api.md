# ice_ffi.h Documentation

### Enums

```c
// Enums
typedef enum {
    ICE_FFI_TRUE = 0,
    ICE_FFI_FALSE = -1,
} ice_ffi_bool;
```

### Definitions

```c
// Typedefs
typedef void* ice_ffi_handle;

// Definitions
// Implements ice_ffi source code, Works same as #pragma once
#define ICE_FFI_IMPL

#define ICE_FFI_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_FFI_STATIC  // Makes functions of the library static with static keyword
#define ICE_FFI_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_FFI_CALLCONV_VECTORCALL
#define ICE_FFI_CALLCONV_FASTCALL
#define ICE_FFI_CALLCONV_STDCALL
#define ICE_FFI_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_FFI_MICROSOFT      // Microsoft platforms
#define ICE_FFI_BEOS           // BeOS and Haiku
#define ICE_FFI_UNIX           // Elsewhere

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_FFI_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
#define ICE_FFI_DLLEXPORT
#define ICE_FFI_DLLIMPORT
```

### Functions

```c
ice_ffi_handle ice_ffi_load_library(char* path);                                    // Loads a shared library (dll, so, dylib, etc...) from path, Returns ice_ffi_handle as handle to the library on success or NULL on failure.
ice_ffi_bool   ice_ffi_unload_library(ice_ffi_handle lib);                          // Unloads a shared library (dll, so, dylib, etc...) with handle from path, Returns ICE_FFI_TRUE on unload success or ICE_FFI_FALSE on failure.
ice_ffi_handle ice_ffi_get_address(ice_ffi_handle lib, char* proc_name);            // Gets address value of name proc_name from shared library handle, Returns ice_ffi_handle as handle to the address could be casted to function, variable, Or anything else on success or NULL on failure.
```
