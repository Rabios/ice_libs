# ice_str.h Documentation

### Enums

```c
typedef enum {
    ICE_STR_TRUE    = 0,
    ICE_STR_FALSE   = -1,
} ice_str_bool;
```

### Definitions

```c
// Implements ice_str source code, Works same as #pragma once
#define ICE_STR_IMPL

#define ICE_STR_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_STR_STATIC  // Makes functions of the library static with static keyword
#define ICE_STR_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_STR_CALLCONV_VECTORCALL
#define ICE_STR_CALLCONV_FASTCALL
#define ICE_STR_CALLCONV_STDCALL
#define ICE_STR_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_STR_MICROSOFT      // Microsoft platforms (Not autodefined -> using Unix)

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_STR_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
#define ICE_STR_DLLEXPORT
#define ICE_STR_DLLIMPORT

// Custom memory allocators
#define ICE_STR_MALLOC(sz)              // malloc(sz)
#define ICE_STR_CALLOC(n, sz)           // calloc(n, sz)
#define ICE_STR_REALLOC(ptr, sz)        // realloc(ptr, sz)
#define ICE_STR_FREE(ptr)               // free(ptr)
```

### Functions

```c
// NOTE 1: All strings returned are NULL-terminated!
// NOTE 2: Returned string allocated on heap, Consider free it with ice_str_free and then change value to NULL once you don't want to use the string.

int          ice_str_len(char* str);                                // Returns length of string.
int          ice_str_arr_len(char** arr);                           // Returns length of array of strings.
char*        ice_str_sub(char* str, int from, int to);              // Returns substring from (from -> to) index.
char*        ice_str_strdup(char* str);                             // Returns NULL-terminates string?
char*        ice_str_concat(char* s1, char* s2);                    // Joins 2 strings in one and returns result.
char*        ice_str_rep(char* str, int count);                     // Returns string repeated multiple times.
char*        ice_str_char(char* str, int index);                    // Returns char at index as string.
ice_str_bool ice_str_match(char* s1, char* s2);                     // Returns ICE_STR_TRUE if 2 strings are same or ICE_STR_FALSE if not.
char*        ice_str_upper(char* str);                              // Returns uppercased string of str.
char*        ice_str_lower(char* str);                              // Returns lowercased string of str.
char*        ice_str_capitalize(char* str);                         // Returns capitalized string of str.
char**       ice_str_split(char* str, char delim);                  // Split string into array by delimiter/separator (char) and return result.
char**       ice_str_splitlines(char* str);                         // Split string into array by newline char and return the array.
char*        ice_str_join(char** strs);                             // Joins strings from array into one string and returns it.
char*        ice_str_join_with_delim(char** strs, char delim);      // Joins strings from array into one string and returns it.
ice_str_bool ice_str_begin(char* s1, char* s2);                     // Returns ICE_STR_TRUE if string s1 starts with string s2 or ICE_STR_FALSE if not.
ice_str_bool ice_str_end(char* s1, char* s2);                       // Returns ICE_STR_TRUE if string s1 ends with string s2 or ICE_STR_FALSE if not.
ice_str_bool ice_str_end_char(char* str, char ch);                  // Returns ICE_STR_TRUE if string ends with character or ICE_STR_FALSE if not.
char*        ice_str_rev(char* str);                                // Returns reversed string of str.
void         ice_str_free(char* str);                               // Frees the string.
void         ice_str_arr_free(char** arr);                          // Frees array of strings.
```
