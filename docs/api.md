# API

The following page includes "Full"

- [API](#api)
  - [`ice_test.h`](#ice_testh)
    - [API](#api-1)
    - [Example](#example)
  - [`ice_ffi.h`](#ice_ffih)
    - [Definitions](#definitions)
    - [API](#api-2)
    - [Linking Flags](#linking-flags)
    - [Example](#example-1)
  - [`ice_str.h`](#ice_strh)
    - [Definitions](#definitions-1)
    - [API](#api-3)
    - [Example](#example-2)
  - [`ice_clip.h`](#ice_cliph)
    - [Definitions](#definitions-2)
    - [API](#api-4)
    - [Linking Flags](#linking-flags-1)
    - [Example](#example-3)
  - [`ice_batt.h`](#ice_batth)
    - [Definitions](#definitions-3)
    - [API](#api-5)
    - [Linking Flags](#linking-flags-2)
    - [Example](#example-4)
  - [`ice_time.h`](#ice_timeh)
    - [Definitions](#definitions-4)
    - [API](#api-6)
    - [Linking Flags](#linking-flags-3)
    - [Example](#example-5)
  - [`ice_ease.h`](#ice_easeh)
    - [Definitions](#definitions-5)
    - [API](#api-7)
    - [Linking Flags](#linking-flags-4)
    - [Example](#example-6)
  - [`ice_ram.h`](#ice_ramh)
    - [Definitions](#definitions-6)
    - [API](#api-8)
    - [Linking Flags](#linking-flags-5)
    - [Example](#example-7)
  - [`ice_cpu.h`](#ice_cpuh)
    - [Definitions](#definitions-7)
    - [API](#api-9)
    - [Linking Flags](#linking-flags-6)
    - [Example](#example-8)
  - [`ice_al.h`](#ice_alh)
    - [Definitions](#definitions-8)
    - [API](#api-10)
    - [Linking Flags](#linking-flags-7)
    - [Example](#example-9)

<br><br>

----

## `ice_test.h`

----

Single-Header tiny C library for unit testing!

To use it `#define ICE_TEST_IMPL` then `#include "ice_test.h"` in your C/C++ code!

----

<br>

### API

<br>

```c
/* Creates test with a name, This test can be called as name(); */
#define ICE_TEST_CREATE(name)

/* Creates test with a name but this one extended to allow argument passing, This test can be called as name(int argc, char** argv); */
#define ICE_TEST_CREATE_ARGS(name)

/* Tests equality between 2 variables, For strings use ICE_TEST_IS_STR_EQU instead! */
#define ICE_TEST_ASSERT_EQU(a, b)

/* Tests equality between 2 strings. */
#define ICE_TEST_ASSERT_STR_EQU(a, b)

/* Tests if variable value is true or 1 */
#define ICE_TEST_ASSERT_TRUE(a)

/* Tests if variable value is false or 0 */
#define ICE_TEST_ASSERT_FALSE(a)

/* Tests if variable is NULL */
#define ICE_TEST_ASSERT_NULL(a)

/* Tests if variable isn't NULL */
#define ICE_TEST_ASSERT_NOT_NULL(a)

/* Tests if variable is integer number */
#define ICE_TEST_ASSERT_INT(a)

/* Tests if variable is not integer number */
#define ICE_TEST_ASSERT_NOT_INT(a)
```

----

<br>

### Example

<br>

```c
#define ICE_TEST_IMPL
#include "ice_test.h"

/* Create a test example that can be called as function */
ICE_TEST_CREATE(sqrtest) {
    /* Do some test assertions */
    ICE_TEST_ASSERT_STR_EQU("ZIO", "ZIO");
    ICE_TEST_ASSERT_EQU(6 * 6, 36);
}

int main(int argc, char** argv) {
    /* Call the test */
    sqrtest();
    return 0;
}
```


----

<br><br>

----

## `ice_ffi.h`

----

Single-Header Cross-Platform C library for working with shared libs, It allows to load symbols from shared libs depending on platform!

To use it `#define ICE_FFI_IMPL` then `#include "ice_ffi.h"` in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...

----

<br>

### Definitions

<br>

```c
/* Define the implementation, This should be #defined before including ice_ffi.h in the code... */
#define ICE_FFI_IMPL


/* #### Define one of these to set functions call convention of the library (Optional) #### */

#define ICE_FFI_VECTORCALL      /* vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet) */
#define ICE_FFI_FASTCALL        /* fastcall */
#define ICE_FFI_STDCALL         /* stdcall */
#define ICE_FFI_CDECL           /* cdecl */


/* #### Define one of these to set implementation platform (Optional) #### */

#define ICE_FFI_MICROSOFT       /* Microsoft platforms */
#define ICE_FFI_BEOS            /* BeOS and Haiku */
#define ICE_FFI_UNIX            /* Unix and Unix-like (Unix/Linux and anything else based on these) */

/* Automatically defined when no platform is set manually, When this defined it detects platform automatically... */
#define ICE_FFI_PLATFORM_AUTODETECTED


/* #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### */

#define ICE_FFI_DLLEXPORT       /* Export the symbols to build as shared library */
#define ICE_FFI_DLLIMPORT       /* Use the symbols from built shared library */


/* #### Define one of these to inline/extern/static library's functions (Optional) #### */

#define ICE_FFI_INLINE          /* inlines library functions (Only works on C99 Standard and above) */
#define ICE_FFI_EXTERN          /* externs library functions */
#define ICE_FFI_STATIC          /* statics library functions */
```

> NOTE: `ICE_FFI_EXTERN` and `ICE_FFI_STATIC` cannot be `#define`d together in the code...

----

<br>

### API

<br>

```c
/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_ffi_bool {
    ICE_FFI_FALSE = -1,
    ICE_FFI_TRUE = 0
} ice_ffi_bool;

/* Handle, Represents pointer to loaded shared library or symbol loaded from shared library */
typedef void* ice_ffi_handle;

/* Loads shared library from path, Returns handle of loaded shared library on success or NULL on failure */
ice_ffi_handle ice_ffi_load(const char* path);

/* Unloads shared library loaded via ice_ffi_load, Returns ICE_FFI_TRUE on success or ICE_FFI_FALSE on failure */
ice_ffi_bool ice_ffi_unload(ice_ffi_handle lib);

/* Loads symbol from shared library loaded via ice_ffi_load, Returns pointer to loaded symbol on success or NULL on failure */
ice_ffi_handle ice_ffi_get(ice_ffi_handle lib, const char* symbol);
```

----

<br>

### Linking Flags

<br>

1. Microsoft Windows: `-lkernel32`
2. Linux: `-ldl`

<br>


> NOTE: When using MSVC on Microsoft Windows, static libraries automatically linked via `#pragma` preprocessor

----

<br>

### Example

<br>

```c
#define ICE_FFI_IMPL
#include "ice_ffi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    /* Load shared library depending on detected platform */
#if ICE_FFI_MICROSOFT
    ice_ffi_handle lib = ice_ffi_load("lib42.dll");
#else
    ice_ffi_handle lib = ice_ffi_load("./lib42.so");
#endif

    /* Get the symbol "F42" from the shared library and cast it to function (Because F42 is C function) */
    unsigned int (*f42)(void) = (unsigned int(*)(void)) ice_ffi_get(lib, "F42");
    
    /* Call the function, Then unload the library */
    printf("F42 Call: %u\n", f42());
    
    ice_ffi_unload(lib);
    
    return 0;
}
```

----

<br><br>

----

## `ice_str.h`

----

Single-Header Cross-Platform C library for working with Strings, It provides functions for working with strings without depending on string.h and other dependencies...

All strings returned are NULL-terminated and the library allows to use custom memory allocators if you wanna! ;)

To use it `#define ICE_STR_IMPL` then `#include "ice_str.h"` in your C/C++ code!

----

<br>

### Definitions

<br>

```c
/* Define the implementation, This should be #defined before including ice_str.h in the code... */
#define ICE_STR_IMPL


/* #### Define one of these to set functions call convention of the library (Optional) #### */

#define ICE_STR_VECTORCALL      /* vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet) */
#define ICE_STR_FASTCALL        /* fastcall */
#define ICE_STR_STDCALL         /* stdcall */
#define ICE_STR_CDECL           /* cdecl */


/* #### Define one of these to set implementation platform (Optional) #### */

#define ICE_STR_MICROSOFT       /* Microsoft platforms */
#define ICE_STR_NON_MICROSOFT   /* Non-Microsoft platforms */

/* Automatically defined when no platform is set manually, When this defined it detects platform automatically... */
#define ICE_STR_PLATFORM_AUTODETECTED


/* #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### */

#define ICE_STR_DLLEXPORT       /* Export the symbols to build as shared library */
#define ICE_STR_DLLIMPORT       /* Use the symbols from built shared library */


/* #### Define one of these to inline/extern/static library's functions (Optional) #### */

#define ICE_STR_INLINE          /* inlines library functions (Only works on C99 Standard and above) */
#define ICE_STR_EXTERN          /* externs library functions */
#define ICE_STR_STATIC          /* statics library functions */
```

> NOTE: `ICE_STR_EXTERN` and `ICE_STR_STATIC` cannot be `#define`d together in the code...

----

<br>

### API

<br>

```c
/* Custom Memory Allocators (Can be customized, Defaults to [malloc, calloc, realloc, free]) */
#define ICE_STR_MALLOC(sz)
#define ICE_STR_CALLOC(n, sz)
#define ICE_STR_REALLOC(ptr, sz)
#define ICE_STR_FREE(ptr)

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_str_bool {
    ICE_STR_FALSE = -1,
    ICE_STR_TRUE = 0
} ice_str_bool;

/* Returns string length */
unsigned ice_str_len(const char* str);

/* Returns substring of string from index from_idx to index to_idx */
char* ice_str_sub(const char* str, int from_idx, int to_idx);

/* Concats 2 strings and returns resulted string */
char* ice_str_concat(const char* str1, const char* str2);

/* Inserts string str2 into string str1 at specified index */
char* ice_str_insert(const char* str1, const char* str2, unsigned idx);

/* Returns number of string str2 matches in string str1, idxs can be pointer to array of unsigned integers (To be Dynamically-Allocated) to store the matching indexes */
int ice_str_match(const char* str1, const char* str2, unsigned **idxs);

/* Replaces string str1 in string str with string str2 */
char* ice_str_rep(const char* str, const char* str1, const char* str2);

/* Returns string repeated multiple times */
char* ice_str_dup(const char* str, unsigned times);

/* Returns copy of string but malloc-ed */
char* ice_str_copy(const char* str);

/* Returns reverse of string */
char* ice_str_rev(const char* str);

/* Converts char to string and returns result */
char* ice_str_char_to_str(char ch);

/* Returns ICE_STR_TRUE if str1 is same as str2, Else returns ICE_STR_FALSE */
ice_str_bool ice_str_same(const char* str1, const char* str2);

/* Returns uppercased version of string */
char* ice_str_upper(const char* str);

/* Returns lowercased version of string */
char* ice_str_lower(const char* str);

/* Returns capital case version of string */
char* ice_str_cap(const char* str);

/* Splits string into array of strings for each delimiter, arrlen is pointer to unsigned integer to store length of resulted array */
char** ice_str_split(const char* str, char delim, unsigned *arrlen);

/* Same like ice_str_split but uses new line character '\n' as delimiter */
char** ice_str_splitlines(const char* str, unsigned *arrlen);

/*
Returns string which is concat of all strings from array strs, arrlen should be defined for the iteration over the array and delimiter can be used to join each string with (Though it can be NULL as optional parameter)
*/
char* ice_str_join(const char** strs, unsigned arrlen, char delim);

/* Returns ICE_STR_TRUE if string str1 starts with string str2, Else returns ICE_STR_FALSE */
ice_str_bool ice_str_begins(const char* str1, const char* str2);

/* Returns ICE_STR_TRUE if string str1 ends with string str2, Else returns ICE_STR_FALSE */
ice_str_bool ice_str_ends(const char* str1, const char* str2);

/* Returns ICE_STR_TRUE if string str ends with char ch, Else returns ICE_STR_FALSE */
ice_str_bool ice_str_last_char(const char* str, char ch);

/* Returns char codes of the string, arrlen is pointer to unsigned integer to store length of integer array (Though you can NULL it if you know the length) */
int* ice_str_bytes(const char* str, unsigned *arrlen);

/* Returns string from char codes, arrlen should be set to array length */
char* ice_str_bstr(const int* chars, unsigned arrlen);

/* Frees a String */
void ice_str_free(char* str);

/* Frees array of char codes */
void ice_str_free_bytes(int* bytes);

/* Frees array of strings, arrlen should be set to array length */
void ice_str_arr_free(char** arr, unsigned arrlen);
```

----

<br>

### Example

<br>

```c
#define ICE_STR_IMPL
#include "ice_str.h"
#include <stdio.h>

int main(int argc, char** argv) {
    /* define variables */
    char* str;
    char** strs;
    char* strs_joined;
    unsigned len = 0;
    unsigned i;

    /* Create string to split it into array */
    str = "First\nSecond\nThird\nFourth";

    /* Split it and get length by using len as pointer to store length of created array */
    strs = ice_str_splitlines(str, &len);

    /* Iterate and print each string split-lined (via \n char) */
    for (i = 0; i < len; i++) {
        printf("strs[%u] = %s\n", i, strs[i]);
    }

    /* Join strings from array but with + mark (If you don't want to join with mark pass NULL instead of char) */
    strs_joined = ice_str_join(strs, len, '+');
    
    /* Print the result */
    printf("strs_joined = %s\n", strs_joined);
    
    /* Free allocated strings */
    ice_str_free(strs_joined);
    ice_str_arr_free(strs, len);

    return 0;
}
```

----

<br><br>

----

## `ice_clip.h`

----

Single-Header Cross-Platform C library for working with Clipboard, It gives native access to the System Clipboard!

To use it `#define ICE_CLIP_IMPL` then `#include "ice_clip.h"` in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...

----

<br>

### Definitions

<br>

```c
/* Define the implementation, This should be #defined before including ice_clip.h in the code... */
#define ICE_CLIP_IMPL


/* #### Define one of these to set functions call convention of the library (Optional) #### */

#define ICE_CLIP_VECTORCALL     /* vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet) */
#define ICE_CLIP_FASTCALL       /* fastcall */
#define ICE_CLIP_STDCALL        /* stdcall */
#define ICE_CLIP_CDECL          /* cdecl */


/* #### Define one of these to set implementation platform (Optional) #### */

#define ICE_CLIP_ANDROID        /* Android */
#define ICE_CLIP_IOS            /* iOS */
#define ICE_CLIP_OSX            /* MacOS/OSX */
#define ICE_CLIP_BB10           /* BlackBerry 10 */
#define ICE_CLIP_UWP            /* UWP (Univeral Windows Platform) */
#define ICE_CLIP_MICROSOFT      /* Microsoft platforms */
#define ICE_CLIP_BEOS           /* BeOS and Haiku */

/* Automatically defined when no platform is set manually, When this defined it detects platform automatically... */
#define ICE_CLIP_PLATFORM_AUTODETECTED


/* #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### */

#define ICE_CLIP_DLLEXPORT      /* Export the symbols to build as shared library */
#define ICE_CLIP_DLLIMPORT      /* Use the symbols from built shared library */


/* #### Define one of these to inline/extern/static library's functions (Optional) #### */

#define ICE_CLIP_INLINE         /* inlines library functions (Only works on C99 Standard and above) */
#define ICE_CLIP_EXTERN         /* externs library functions */
#define ICE_CLIP_STATIC         /* statics library functions */
```

> NOTE: `ICE_CLIP_EXTERN` and `ICE_CLIP_STATIC` cannot be `#define`d together in the code...

----

<br>

### API

<br>

```c
/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_clip_bool {
    ICE_CLIP_FALSE = -1,
    ICE_CLIP_TRUE  = 0
} ice_clip_bool;

/* [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_clip on Android, This Should be called first before other ice_clip.h functions */
void ice_clip_use_native_activity(void* activity);

/* [WINDOWS-ONLY, OPTIONAL] Sets the Window to be used with ice_clip, This is optional feature as the Windows implementation do not need Window by default */
void ice_clip_use_window(void* window);

/* Retrieves the text from Clipboard */
const char* ice_clip_get(void);

/* Sets the Clipboard text, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ice_clip_bool ice_clip_set(const char* text);

/* Clears the Clipboard, Returns ICE_CLIP_TRUE on success or ICE_CLIP_FALSE on failure */
ice_clip_bool ice_clip_clear(void);
```

----

<br>

### Linking Flags

<br>

1. Microsoft Windows: `-lkernel32 -luser32`
2. iOS: `-framework Foundation -framework UIKit`
3. MacOS/OSX: `-framework Foundation -framework AppKit`
4. BlackBerry 10: `-lbbsystem`

<br>


> NOTE: When using MSVC on Microsoft Windows, static libraries automatically linked via `#pragma` preprocessor

----

<br>

### Example

<br>

```c
#define ICE_CLIP_IMPL
#include "ice_clip.h"
#include <stdio.h>

int main(int argc, char** argv) {
    /* Clear the Clipboard */
    if (ice_clip_clear() == ICE_CLIP_FALSE) {
        return -1;
    }
    
    /* Copy text to Clipboard */
    if (ice_clip_set("SPEED") == ICE_CLIP_FALSE) {
        return -1;
    }
    
    /* Get text from Clipboard */
    printf("Clipboard Text: %s\n", ice_clip_get());
    
    return 0;
}
```

----

<br><br>

----

## `ice_batt.h`

----

Single-Header Cross-Platform C library for working with the Battery, It gives info about the Battery...

To use it `#define ICE_BATT_IMPL` then `#include "ice_batt.h"` in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...

----

<br>

### Definitions

<br>

```c
/* Define the implementation, This should be #defined before including ice_clip.h in the code... */
#define ICE_BATT_IMPL


/* #### Define one of these to set functions call convention of the library (Optional) #### */

#define ICE_BATT_VECTORCALL     /* vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet) */
#define ICE_BATT_FASTCALL       /* fastcall */
#define ICE_BATT_STDCALL        /* stdcall */
#define ICE_BATT_CDECL          /* cdecl */


/* #### Define one of these to set implementation platform (Optional) #### */

#define ICE_BATT_ANDROID        /* Android */
#define ICE_BATT_IOS            /* iOS */
#define ICE_BATT_OSX            /* MacOS/OSX */
#define ICE_BATT_TIZEN          /* Tizen */
#define ICE_BATT_WEB            /* Web (Emscripten) */
#define ICE_BATT_SWITCH         /* Nintendo Switch (libnx) */
#define ICE_BATT_PSP            /* PlayStation Portable (pspsdk) */
#define ICE_BATT_PSVITA         /* PlayStation Vita (vitasdk) */
#define ICE_BATT_BB10           /* BlackBerry 10 */
#define ICE_BATT_UWP            /* UWP (Univeral Windows Platform) */
#define ICE_BATT_MICROSOFT      /* Microsoft platforms (Non-UWP) */
#define ICE_BATT_BSD            /* BSD (FreeBSD, OpenBSD, NetBSD, DragonFly BSD) */
#define ICE_BATT_UNIX           /* Unix and Unix-Like */

/* Automatically defined when no platform is set manually, When this defined it detects platform automatically... */
#define ICE_BATT_PLATFORM_AUTODETECTED


/* #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### */

#define ICE_BATT_DLLEXPORT      /* Export the symbols to build as shared library */
#define ICE_BATT_DLLIMPORT      /* Use the symbols from built shared library */


/* #### Define one of these to inline/extern/static library's functions (Optional) #### */

#define ICE_BATT_INLINE         /* inlines library functions (Only works on C99 Standard and above) */
#define ICE_BATT_EXTERN         /* externs library functions */
#define ICE_BATT_STATIC         /* statics library functions */
```

> NOTE: `ICE_BATT_EXTERN` and `ICE_BATT_STATIC` cannot be `#define`d together in the code...

----

<br>

### API

<br>

```c
/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_batt_bool {
    ICE_BATT_FALSE = -1,
    ICE_BATT_TRUE = 0
} ice_batt_bool;

/* Struct that contains battery status (Exists?, Charging?, Battery Level) */
typedef struct ice_batt_info {
    ice_batt_bool exists;
    ice_batt_bool charging;
    unsigned int level;
} ice_batt_info;

/* [ANDROID-ONLY, REQUIRED] Sets native activity to be used by ice_batt on Android, This Should be called first before other ice_batt.h functions */
void ice_batt_use_native_activity(void* activity);

/* Returns curreny battery status */
ice_batt_info ice_batt_status(void);
```

----

<br>

### Linking Flags

<br>

1. Microsoft Windows (Non-UWP): `-lkernel32`
2. BlackBerry 10: `-lbbdevice`
3. iOS: `-framework Foundation -framework UIKit`
4. MacOS/OSX: `-framework Foundation -framework CoreFoundation -framework IOKit`
5. Nintendo Switch: `-lnx`
6. PlayStation Vita: `-lScePower_stub`

<br>


> NOTE: When using MSVC on Microsoft Windows, static libraries automatically linked via `#pragma` preprocessor

----

<br>

### Example

<br>

```c
#define ICE_BATT_IMPL
#include "ice_batt.h"
#include <stdio.h>

int main(int argc, char** argv) {
    /* Fetch battery info */
    ice_batt_info status = ice_batt_status();
    
    /* Prints if battery exists and if charging and battery level */
    printf("Battery Exists: %s\n", (status.exists == ICE_BATT_TRUE) ? "YES" : "NO");
    printf("Battery Charging: %s\n", (status.charging == ICE_BATT_TRUE) ? "YES" : "NO");
    printf("Battery Level: %u\n", status.level);
    
    return 0;
}
```

----

<br><br>

----

## `ice_time.h`

----

Single-Header Cross-Platform C library for time functionality!

To use it `#define ICE_TIME_IMPL` then `#include "ice_time.h"` in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...

----

<br>

### Definitions

<br>

```c
/* Define the implementation, This should be #define(d) before including ice_time.h in the code... */
#define ICE_TIME_IMPL


/* #### Define one of these to set functions call convention of the library (Optional) #### */

#define ICE_TIME_VECTORCALL     /* vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet) */
#define ICE_TIME_FASTCALL       /* fastcall */
#define ICE_TIME_STDCALL        /* stdcall */
#define ICE_TIME_CDECL          /* cdecl */


/* #### Define one of these to set implementation platform (Optional) #### */

#define ICE_TIME_MICROSOFT      /* Microsoft platforms */
#define ICE_TIME_APPLE          /* Apple platforms */
#define ICE_TIME_UNIX           /* Unix and Unix-like */
#define ICE_TIME_3DS            /* Nintendo 3DS (libctru) */
#define ICE_TIME_WEB            /* Web (Emscripten) */

/* Automatically defined when no platform is set manually, When this defined it detects platform automatically... */
#define ICE_TIME_PLATFORM_AUTODETECTED


/* #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### */

#define ICE_TIME_DLLEXPORT      /* Export the symbols to build as shared library */
#define ICE_TIME_DLLIMPORT      /* Use the symbols from built shared library */


/* #### Define one of these to inline/extern/static library's functions (Optional) #### */

#define ICE_TIME_INLINE         /* inlines library functions (Only works on C99 Standard and above) */
#define ICE_TIME_EXTERN         /* externs library functions */
#define ICE_TIME_STATIC         /* statics library functions */
```

> NOTE: `ICE_TIME_EXTERN` and `ICE_TIME_STATIC` cannot be `#define`d together in the code...

----

<br>

### API

<br>

```c
/* Typedef for very long integers */
typedef unsigned long long int ice_time_ulong;

/* Enumeration for week days */
typedef enum ice_time_day {
    ICE_TIME_DAY_SUNDAY = 1,
    ICE_TIME_DAY_MONDAY,
    ICE_TIME_DAY_TUESDAY,
    ICE_TIME_DAY_WEDNESDAY,
    ICE_TIME_DAY_THURSDAY,
    ICE_TIME_DAY_FRIDAY,
    ICE_TIME_DAY_SATURDAY
} ice_time_day;

/* Enumeration for year months */
typedef enum ice_time_month {
    ICE_TIME_MONTH_JANUARY = 1,
    ICE_TIME_MONTH_FEBRUARY,
    ICE_TIME_MONTH_MARCH,
    ICE_TIME_MONTH_APRIL,
    ICE_TIME_MONTH_MAY,
    ICE_TIME_MONTH_JUNE,
    ICE_TIME_MONTH_JULY,
    ICE_TIME_MONTH_AUGUST,
    ICE_TIME_MONTH_SEPTEMBER,
    ICE_TIME_MONTH_OCTOBER,
    ICE_TIME_MONTH_NOVEMBER,
    ICE_TIME_MONTH_DECEMBER
} ice_time_month;

/* Enumeration for seasons (helpful?) */
typedef enum ice_time_season {
    ICE_TIME_SEASON_WINTER = 1,
    ICE_TIME_SEASON_SPRING,
    ICE_TIME_SEASON_SUMMER,
    ICE_TIME_SEASON_AUTUMN
} ice_time_season;

/* Struct that contains patched current time info, Including ticks */
typedef struct ice_time_info {
    char* string;                   /* Time as string */
    ice_time_ulong clock_ticks;     /* Clock Ticks (Nanoseconds) */
    ice_time_ulong system_ticks;    /* Ticks since system started (Milliseconds) */
    ice_time_ulong epoch;           /* Unix timestamp */
    ice_time_ulong nanoseconds;
    ice_time_ulong microseconds;
    ice_time_ulong milliseconds;
    unsigned int second;
    unsigned int minute;
    unsigned int hour;
    ice_time_day week_day;          /* (ICE_TIME_DAY_SUNDAY - ICE_TIME_DAY_SATURDAY) */
    unsigned int month_day;         /* (1 - Month last day number) */
    unsigned int year_day;          /* (1 - 365) */
    ice_time_month month;
    ice_time_season season;         /* (ICE_TIME_SEASON_WINTER - ICE_TIME_SEASON_AUTUMN) */
    unsigned int year;
} ice_time_info;

/* Returns difference between 2 ticks, The 2 ticks are acquired by via clock_ticks from 2 times */
ice_time_ulong ice_time_diff(ice_time_info t1, ice_time_info t2);

/* Returns Delta Time between 2 ticks, The 2 ticks are acquired by via clock_ticks from 2 times */
double ice_time_dt(ice_time_info t1, ice_time_info t2);

/* Returns current time info (eg. Ticks, Seconds, Days, Months, Year, Month, etc...) */
ice_time_info ice_time_status(void);

/* Sleeps thread/program for milliseconds */
void ice_time_sleep(ice_time_ulong ms);
```

----

<br>

### Linking Flags

<br>

1. Microsoft Windows: `-lkernel32`
2. Nintendo 3DS (libctru): `-lctru`

<br>


> NOTE: When using MSVC on Microsoft Windows, static libraries automatically linked via `#pragma` preprocessor

----

<br>

### Example

<br>

```c
#define ICE_TIME_IMPL
#include "ice_time.h"
#include <stdio.h>

int main(int argc, char** argv) {
    /* Fetch time info */
    ice_time_info curr_time = ice_time_status();

    /* Print time fetched as string */
    printf("Current Time: %s\n", curr_time.string);

    return 0;
}
```

----

<br><br>

----

## `ice_ease.h`

----

Single-Header Cross-Platform C library for Easings, It's based on Robert Penner easings and Easing functions from easings.net

To use it `#define ICE_EASE_IMPL` then `#include "ice_ease.h"` in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...

----

<br>

### Definitions

<br>

```c
/* Define the implementation, This should be #defined before including ice_ease.h in the code... */
#define ICE_EASE_IMPL


/* #### Define one of these to set functions call convention of the library (Optional) #### */

#define ICE_EASE_VECTORCALL     /* vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet) */
#define ICE_EASE_FASTCALL       /* fastcall */
#define ICE_EASE_STDCALL        /* stdcall */
#define ICE_EASE_CDECL          /* cdecl */


/* #### Define one of these to set implementation platform (Optional) #### */

#define ICE_EASE_MICROSOFT       /* Microsoft platforms */
#define ICE_EASE_NON_MICROSOFT   /* Non-Microsoft platforms */

/* Automatically defined when no platform is set manually, When this defined it detects platform automatically... */
#define ICE_EASE_PLATFORM_AUTODETECTED


/* #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### */

#define ICE_EASE_DLLEXPORT      /* Export the symbols to build as shared library */
#define ICE_EASE_DLLIMPORT      /* Use the symbols from built shared library */


/* #### Define one of these to inline/extern/static library's functions (Optional) #### */

#define ICE_EASE_INLINE         /* inlines library functions (Only works on C99 Standard and above)
#define ICE_EASE_EXTERN         /* externs library functions */
#define ICE_EASE_STATIC         /* statics library functions */
```

> NOTE: `ICE_EASE_EXTERN` and `ICE_EASE_STATIC` cannot be `#define`d together in the code...

----

<br>

### API

<br>

```c
/* PI definition */
#define ICE_EASE_PI 3.14159265358979323846

/* Easing Types */
typedef enum ice_ease_type {
    ICE_EASE_TYPE_PROGRESS = 1,
    ICE_EASE_TYPE_PENNER = 4
} ice_ease_type;

/* NOTE: You can use Robert Penner's Easings or Easings that take one value, To use Robert one argc should be 4 and to use Single-Value ones it should be 1 (Arguments Number) */

/*

Examples:

ice_ease_linear(ICE_EASE_TYPE_PROGRESS, 5);         // Progress-Based easings take 1 argument
ice_ease_linear(ICE_EASE_TYPE_PENNER, 1, 2, 3, 4);  // Penner easings take 4 arguments

*/

/* Functions for Linear Easing */
double ice_ease_linear(ice_ease_type ease_type, ...);

/* Functions for Quadratic Easing */
double ice_ease_quad_in(ice_ease_type ease_type, ...);
double ice_ease_quad_out(ice_ease_type ease_type, ...);
double ice_ease_quad_in_out(ice_ease_type ease_type, ...);

/* Functions for Cubic Easing */
double ice_ease_cubic_in(ice_ease_type ease_type, ...);
double ice_ease_cubic_out(ice_ease_type ease_type, ...);
double ice_ease_cubic_in_out(ice_ease_type ease_type, ...);

/* Functions for Quartic Easing */
double ice_ease_quart_in(ice_ease_type ease_type, ...);
double ice_ease_quart_out(ice_ease_type ease_type, ...);
double ice_ease_quart_in_out(ice_ease_type ease_type, ...);

/* Functions for Quintic Easing */
double ice_ease_quint_in(ice_ease_type ease_type, ...);
double ice_ease_quint_out(ice_ease_type ease_type, ...);
double ice_ease_quint_in_out(ice_ease_type ease_type, ...);

/* Functions for Sinusoidal Easing */
double ice_ease_sine_in(ice_ease_type ease_type, ...);
double ice_ease_sine_out(ice_ease_type ease_type, ...);
double ice_ease_sine_in_out(ice_ease_type ease_type, ...);

/* Functions for Exponential Easing */
double ice_ease_expo_in(ice_ease_type ease_type, ...);
double ice_ease_expo_out(ice_ease_type ease_type, ...);
double ice_ease_expo_in_out(ice_ease_type ease_type, ...);

/* Functions for Circular Easing */
double ice_ease_circ_in(ice_ease_type ease_type, ...);
double ice_ease_circ_out(ice_ease_type ease_type, ...);
double ice_ease_circ_in_out(ice_ease_type ease_type, ...);

/* Functions for Elastic Easing */
double ice_ease_elastic_in(ice_ease_type ease_type, ...);
double ice_ease_elastic_out(ice_ease_type ease_type, ...);
double ice_ease_elastic_in_out(ice_ease_type ease_type, ...);

/* Functions for Back Easing */
double ice_ease_back_in(ice_ease_type ease_type, ...);
double ice_ease_back_out(ice_ease_type ease_type, ...);
double ice_ease_back_in_out(ice_ease_type ease_type, ...);

/* Functions for Bounce Easing */
double ice_ease_bounce_in(ice_ease_type ease_type, ...);
double ice_ease_bounce_out(ice_ease_type ease_type, ...);
double ice_ease_bounce_in_out(ice_ease_type ease_type, ...);
```

----

<br>

### Linking Flags

<br>

1. Linux: `-lm` if required

<br>


> NOTE: When using MSVC on Microsoft Windows, static libraries automatically linked via `#pragma` preprocessor

----

<br>

### Example

<br>

```c
#define ICE_EASE_IMPL
#include "ice_ease.h"
#include <stdio.h>

int main(ice_ease_type ease_type, char** argv) {
    /* easings.net implementation (1 argument, 5.0) */
    printf("Ease Linear 1: %f\n", ice_ease_linear(ICE_EASE_TYPE_PROGRESS, 5.0));
    
    /* Robert Penner implementation (4 arguments, 1.0 2.0 3.0 4.0) */
    printf("Ease Linear 4: %f\n", ice_ease_linear(ICE_EASE_TYPE_PENNER, 1.0, 2.0, 3.0, 4.0));

    return 0;
}
```

----

<br><br>

----

## `ice_ram.h`

----

Single-Header Cross-Platform C library for working with RAM, It gives information about RAM usage!

To use it `#define ICE_RAM_IMPL` then `#include "ice_ram.h"` in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...

----

<br>

### Definitions

<br>

```c
/* Define the implementation, This should be #defined before including ice_ram.h in the code... */
#define ICE_RAM_IMPL


/* #### Define one of these to set functions call convention of the library (Optional) #### */

#define ICE_RAM_VECTORCALL      /* vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet) */
#define ICE_RAM_FASTCALL        /* fastcall */
#define ICE_RAM_STDCALL         /* stdcall */
#define ICE_RAM_CDECL           /* cdecl */


/* #### Define one of these to set implementation platform (Optional) #### */

#define ICE_RAM_MICROSOFT       /* Microsoft platforms */
#define ICE_RAM_APPLE           /* Apple (MacOS, iOS, etc...) */
#define ICE_RAM_BSD             /* BSD (FreeBSD, OpenBSD, NetBSD, DragonFly BSD) */
#define ICE_RAM_WEB             /* Web (Emscripten) */
#define ICE_RAM_TIZEN           /* Tizen */
#define ICE_RAM_BB10            /* BlackBerry 10 */
#define ICE_RAM_LINUX           /* Linux (This includes Android, Consoles, etc...) */

/* Automatically defined when no platform is set manually, When this defined it detects platform automatically... */
#define ICE_RAM_PLATFORM_AUTODETECTED


/* #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### */

#define ICE_RAM_DLLEXPORT       /* Export the symbols to build as shared library */
#define ICE_RAM_DLLIMPORT       /* Use the symbols from built shared library */


/* #### Define one of these to inline/extern/static library's functions (Optional) #### */

#define ICE_RAM_INLINE          /* inlines library functions (Only works on C99 Standard and above) */
#define ICE_RAM_EXTERN          /* externs library functions */
#define ICE_RAM_STATIC          /* statics library functions */
```

> NOTE: `ICE_RAM_EXTERN` and `ICE_RAM_STATIC` cannot be `#define`d together in the code...

----

<br>

### API

<br>

```c
/* Typedef for free and used and total Bytes of RAM */
typedef unsigned long long int ice_ram_bytes;

/* RAM Information, Contains free and used and total RAM in Bytes */
typedef struct ice_ram_info {
    ice_ram_bytes free;
    ice_ram_bytes used;
    ice_ram_bytes total;
} ice_ram_info;

/* Retrives RAM info (Free RAM, Used RAM, Total RAM) in Bytes */
ice_ram_info ice_ram_status(void);
```

----

<br>

### Linking Flags

<br>

1. Microsoft Windows: `-lkernel32`
2. BlackBerry 10: `-lbb`

<br>


> NOTE: When using MSVC on Microsoft Windows, static libraries automatically linked via `#pragma` preprocessor

----

<br>

### Example

<br>

```c
#define ICE_RAM_IMPL
#include "ice_ram.h"
#include <stdio.h>

int main(int argc, char** argv) {
    /* Fetch RAM memory info */
    ice_ram_info info = ice_ram_status();
    
    /* Print free, used, and total used RAM memory in bytes */
    printf("Free RAM in Bytes: %llu\n", info.free);
    printf("Used RAM in Bytes: %llu\n", info.used);
    printf("Total RAM in Bytes: %llu\n", info.total);
    
    return 0;
}
```

----

<br><br>

----

## `ice_cpu.h`

----

Single-Header Cross-Platform C library for working with CPU, It gives information about device's CPU!

To use it `#define ICE_CPU_IMPL` then `#include "ice_cpu.h"` in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...

----

<br>

### Definitions

<br>

```c
/* Define the implementation, This should be #defined before including ice_cpu.h in the code... */
#define ICE_CPU_IMPL


/* #### Define one of these to set functions call convention of the library (Optional) #### */

#define ICE_CPU_VECTORCALL      /* vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_CPU_FASTCALL        /* fastcall */
#define ICE_CPU_STDCALL         /* stdcall */
#define ICE_CPU_CDECL           /* cdecl */


/* #### Define one of these to set implementation platform (Optional) #### */

#define ICE_CPU_APPLE           /* Apple Platforms */
#define ICE_CPU_MICROSOFT       /* Microsoft Platforms */
#define ICE_CPU_BSD             /* BSD (FreeBSD, OpenBSD, NetBSD, DragonFly BSD) */
#define ICE_CPU_HPUX            /* HP-UX */
#define ICE_CPU_IRIX            /* IRIX */
#define ICE_CPU_UNIX            /* Unix and Unix-Like */
#define ICE_CPU_BB10            /* BlackBerry 10 */

/* Automatically defined when no platform is set manually, When this defined it detects platform automatically... */
#define ICE_CPU_PLATFORM_AUTODETECTED


/* #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### */

#define ICE_CPU_DLLEXPORT       /* Export the symbols to build as shared library */
#define ICE_CPU_DLLIMPORT       /* Use the symbols from built shared library */


/* #### Define one of these to inline/extern/static library's functions (Optional) #### */

#define ICE_CPU_INLINE          /* inlines library functions (Only works on C99 Standard and above) */
#define ICE_CPU_EXTERN          /* externs library functions */
#define ICE_CPU_STATIC          /* statics library functions */
```

> NOTE: `ICE_CPU_EXTERN` and `ICE_CPU_STATIC` cannot be `#define`d together in the code...

----

<br>

### API

<br>

```c
/* Struct that contains informations about the CPU (Name, Cores, etc...) */
typedef struct ice_cpu_info {
    const char* name;
    unsigned int cores;
} ice_cpu_info;

/* Fetches informations about the CPU */
ice_cpu_info ice_cpu_status(void);
```

----

<br>

### Linking Flags

<br>

1. Microsoft Windows: `-lkernel32`
2. BlackBerry 10: `-lbbdevice`

<br>

> NOTE: When using MSVC on Microsoft Windows, static libraries automatically linked via `#pragma` preprocessor

----

<br>

### Example

<br>

```c
#define ICE_CPU_IMPL
#include "ice_cpu.h"
#include <stdio.h>

int main(int argc, char** argv) {
    /* Fetch CPU information (Name, Cores, etc...) */
    ice_cpu_info status = ice_cpu_status();
    
    /* Print the information */
    printf("CPU Model: %s\n", status.name);
    printf("CPU Cores: %u\n", status.cores);
    
    return 0;     
}
```

----

<br><br>

----

## `ice_al.h`

----

Single-Header Cross-Platform C library for working with OpenAL, It works as OpenAL loader that allows to use OpenAL API from shared libraries...

To use it `#define ICE_AL_IMPL` then `#include "ice_al.h"` in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...

----

<br>

### Definitions

<br>

```c
/* Define the implementation, This should be #defined before including ice_al.h in the code... */
#define ICE_AL_IMPL


/* #### Define one of these to set functions call convention of the library (Optional) #### */

#define ICE_AL_VECTORCALL      /* vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet) */
#define ICE_AL_FASTCALL        /* fastcall */
#define ICE_AL_STDCALL         /* stdcall */
#define ICE_AL_CDECL           /* cdecl */


/* #### Define one of these to set implementation platform (Optional) #### */

#define ICE_AL_MICROSOFT       /* Microsoft platforms */
#define ICE_AL_BEOS            /* BeOS and Haiku */
#define ICE_AL_UNIX            /* Unix and Unix-like (Unix/Linux and anything else based on these) */


/* Automatically defined when no platform is set manually, When this defined it detects platform automatically... */
#define ICE_AL_PLATFORM_AUTODETECTED


/* #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### */

#define ICE_AL_DLLEXPORT       /* Export the symbols to build as shared library */
#define ICE_AL_DLLIMPORT       /* Use the symbols from built shared library */


/* #### Define one of these to inline/extern/static library's functions (Optional) #### */

#define ICE_AL_INLINE          /* inlines library functions (Only works on C99 Standard and above) */
#define ICE_AL_EXTERN          /* externs library functions */
#define ICE_AL_STATIC          /* statics library functions */
```

> NOTE: `ICE_AL_EXTERN` and `ICE_AL_STATIC` cannot be `#define`d together in the code... (Only one of both can be defined), And the definitions ONLY affects the OpenAL loader API

----

<br>

### API

<br>

```c
/* Handle, Type definition for void* for symbols loaded from shared libs */
typedef void* ice_al_handle;

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_al_bool {
    ICE_AL_FALSE = -1,
    ICE_AL_TRUE = 0
} ice_al_bool;

/* [INTERNAL] Loads symbol from loaded OpenAL shared library, Which can be casted to a function to call */
ice_al_handle ice_al_proc(const char* symbol);

/* Loads OpenAL API from shared library path (eg. openal32.dll on Windows), Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ice_al_bool ice_al_load(const char* path);

/* Unloads OpenAL API, Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ice_al_bool ice_al_unload(void);

/*
API above is the OpenAL loader API, For OpenAL API:

1. https://www.openal.org/documentation/openal-1.1-specification.pdf
2. https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
*/
```

----

<br>

### Linking Flags

<br>

1. Microsoft Windows: `-lkernel32`
2. Linux: `-ldl`
 
<br>

> NOTE: When using MSVC on Microsoft Windows, static libraries automatically linked via `#pragma` preprocessor

----

<br>

### Example

<br>

```c
#define ICE_AL_IMPL
#include "ice_al.h"
#include <stdio.h>

int main(int argc, char** argv) {
    /* Load OpenAL API from shared library, Here we loaded the API from OpenAL-soft shared library (Also can be loaded from openal32.dll, Or anything contains the API depending on platform) */
    ice_al_bool res = ice_al_load("soft_oal.dll");
    if (res == ICE_AL_FALSE) return -1;
    
    /* Initializes default audio device, To check if OpenAL would work or no... */
    const char* devicename = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    ALCdevice* device = alcOpenDevice(devicename);
    
    if (device == NULL) return -1;
    printf("WE DID IT!\n");
    
    /* Unload the OpenAL API and terminate the program */
    res = ice_al_unload();
    if (res == ICE_AL_FALSE) return -1;

    return 0;
}
```

----
