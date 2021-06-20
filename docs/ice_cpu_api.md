# ice_cpu.h Documentation

### Enums

```c
typedef enum {
    ICE_CPU_ARCH_NONE = -1,  // Trigger 16 and 8 bit CPUs
    ICE_CPU_ARCH_X86,        // 32 bit
    ICE_CPU_ARCH_X86_64,     // x64, x86_64, AMD64 and Intel 64
} ice_cpu_arch;
```

### Definitions

```c
// Definitions
// Implements ice_cpu source code, Works same as #pragma once
#define ICE_CPU_IMPL

#define ICE_CPU_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_CPU_STATIC  // Makes functions of the library static with static keyword
#define ICE_CPU_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_CPU_CALLCONV_VECTORCALL
#define ICE_CPU_CALLCONV_FASTCALL
#define ICE_CPU_CALLCONV_STDCALL
#define ICE_CPU_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_CPU_MICROSOFT      // Microsoft platforms
#define ICE_CPU_HPUX           // HP-UX
#define ICE_CPU_IRIX           // IRIX
#define ICE_CPU_APPLE          // Apple platforms
#define ICE_CPU_WEB            // Web (Emscripten)
#define ICE_CPU_GAMEBOY        // Nintendo Gameboy
#define ICE_CPU_NDS            // Nintendo NDS
#define ICE_CPU_3DS            // Nintendo 3DS
#define ICE_CPU_SWITCH         // Nintendo Switch
#define ICE_CPU_GAMECUBE       // Nintendo GameCube
#define ICE_CPU_WII            // Nintendo Wii
#define ICE_CPU_PS1            // Sony PlayStation 1
#define ICE_CPU_PS2            // Sony PlayStation 2
#define ICE_CPU_PS3            // Sony PlayStation 3
#define ICE_CPU_PS4            // Sony PlayStation 4
#define ICE_CPU_PS5            // Sony PlayStation 5
#define ICE_CPU_PSP            // Sony PlayStation Portable
#define ICE_CPU_PSVITA         // Sony PlayStation Vita
#define ICE_CPU_TIZEN          // Tizen
#define ICE_CPU_UNIX           // Elsewhere

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_CPU_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
#define ICE_CPU_DLLEXPORT
#define ICE_CPU_DLLIMPORT
```

### Functions

```c
unsigned int  ice_cpu_cores_count(void);                // Returns count of CPU cores device has as unsigned integer.
ice_cpu_arch  ice_cpu_get_arch(void);                   // Returns CPU architecture.
char*         ice_cpu_name(void);                       // Returns CPU name used by device as string.
```
