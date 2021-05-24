# ice_battery.h Documentation

### Enums

```c
typedef enum {
    ICE_BATTERY_TRUE    = 0,
    ICE_BATTERY_FALSE   = -1,
} ice_battery_bool;
```

### Definitions

```c
// Definitions
// Implements ice_battery source code, Works same as #pragma once
#define ICE_BATTERY_IMPL

#define ICE_BATTERY_EXTERN  // Extern functions of the library with extern keyword (Enabled by default) (Enabled by default)
#define ICE_BATTERY_STATIC  // Makes functions of the library static with static keyword
#define ICE_BATTERY_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_BATTERY_CALLCONV_VECTORCALL
#define ICE_BATTERY_CALLCONV_FASTCALL
#define ICE_BATTERY_CALLCONV_STDCALL
#define ICE_BATTERY_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_BATTERY_MICROSOFT       // Microsoft platforms
#define ICE_BATTERY_ANDROID         // Android (JNI)
#define ICE_BATTERY_IOS             // iOS
#define ICE_BATTERY_OSX             // OSX
#define ICE_BATTERY_UWP             // UWP
#define ICE_BATTERY_LINUX           // Linux
#define ICE_BATTERY_BEOS            // BeOS and Haiku
#define ICE_BATTERY_WEB             // Web (Emscripten)
#define ICE_BATTERY_SWITCH          // Nintendo Switch
#define ICE_BATTERY_PSP             // Sony PlayStation Portable
#define ICE_BATTERY_PSVITA          // Sony PlayStation Vita

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_BATTERY_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
// Keep in mind you should set backend (But it's defined by default if not...)
#define ICE_BATTERY_DLLEXPORT
#define ICE_BATTERY_DLLIMPORT
```

### Functions

```c
ice_battery_bool  ice_battery_init(void);                  // Initializes ice_battery, Returns ICE_BATTERY_TRUE on success or ICE_BATTERY_FALSE on failure.
int               ice_battery_level(void);                 // Returns battery level [0 - 100] as integer.
ice_battery_bool  ice_battery_charging(void);              // Returns ICE_BATTERY_TRUE if battery is charging or ICE_BATTERY_FALSE if not.
ice_battery_bool  ice_battery_level_full(void);            // Returns ICE_BATTERY_TRUE if battery is full or ICE_BATTERY_FALSE if not.
ice_battery_bool  ice_battery_level_high(void);            // Returns ICE_BATTERY_TRUE if battery level is high or ICE_BATTERY_FALSE if not.
ice_battery_bool  ice_battery_level_mid(void);             // Returns ICE_BATTERY_TRUE if battery level is low or ICE_BATTERY_FALSE if not.
ice_battery_bool  ice_battery_level_low(void);             // Returns ICE_BATTERY_TRUE if battery level is critical or ICE_BATTERY_FALSE if not.
ice_battery_bool  ice_battery_close(void);                 // Deinitializes ice_battery, Returns ICE_BATTERY_TRUE on success or ICE_BATTERY_FALSE on failure.
```
