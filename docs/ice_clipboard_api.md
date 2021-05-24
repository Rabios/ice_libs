# ice_clipboard.h API

### Enums

```c
typedef enum {
    ICE_CLIPBOARD_TRUE = 0,
    ICE_CLIPBOARD_FALSE = -1,
} ice_clipboard_bool;
```

### Definitions

```c
// Implements ice_clipboard source code, Works same as #pragma once
#define ICE_CLIPBOARD_IMPL

#define ICE_CLIPBOARD_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_CLIPBOARD_STATIC  // Makes functions of the library static with static keyword
#define ICE_CLIPBOARD_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_CLIPBOARD_CALLCONV_VECTORCALL
#define ICE_CLIPBOARD_CALLCONV_FASTCALL
#define ICE_CLIPBOARD_CALLCONV_STDCALL
#define ICE_CLIPBOARD_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_CLIPBOARD_ANDROID       // Android (JNI)
#define ICE_CLIPBOARD_IOS           // iOS (UIPasteboard)
#define ICE_CLIPBOARD_OSX           // OSX (NSPasteboard)
#define ICE_CLIPBOARD_MICROSOFT     // Microsoft Windows (Win32 clipboard API)
#define ICE_CLIPBOARD_UWP           // UWP
#define ICE_CLIPBOARD_LINUX         // Linux (X11 atoms)
#define ICE_CLIPBOARD_BEOS          // BeOS and Haiku (be_clipboard)
#define ICE_CLIPBOARD_NULL          // Elsewhere (Create file and save/read content from)

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_CLIPBOARD_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
#define ICE_CLIPBOARD_DLLEXPORT
#define ICE_CLIPBOARD_DLLIMPORT

// Custom memory allocators
#define ICE_CLIPBOARD_MALLOC(sz)            // malloc(sz)
#define ICE_CLIPBOARD_CALLOC(n, sz)         // calloc(n, sz)
#define ICE_CLIPBOARD_REALLOC(ptr, sz)      // realloc(ptr, sz)
#define ICE_CLIPBOARD_FREE(ptr)             // free(ptr)
```

### Functions

```c
ice_clipboard_bool  ice_clipboard_init(void);                // Initializes clipboard, Returns ICE_CLIPBOARD_TRUE on success or ICE_CLIPBOARD_FALSE on failure.
ice_clipboard_bool  ice_clipboard_set(char* text);           // Copies string to clipboard, Returns ICE_CLIPBOARD_TRUE on success or ICE_CLIPBOARD_FALSE on failure.
char*               ice_clipboard_get(void);                 // Gets string content of clipboard, Returns latest string copied to clipboard.
ice_clipboard_bool  ice_clipboard_text(char* text);          // Is latest string copied to clipboard same as string text? Returns ICE_CLIPBOARD_TRUE if true or ICE_CLIPBOARD_FALSE if false.
ice_clipboard_bool  ice_clipboard_clear(void);               // Clears clipboard content, Returns ICE_CLIPBOARD_TRUE on success or ICE_CLIPBOARD_FALSE on failure.
ice_clipboard_bool  ice_clipboard_close(void);               // Closes (Deinitializes) clipboard, Returns ICE_CLIPBOARD_TRUE on success or ICE_CLIPBOARD_FALSE on failure.
```
