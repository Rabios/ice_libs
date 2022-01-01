/*
ice_str.h, Single-Header Cross-Platform C library for working with Strings!


================================== Full Overview ==================================

ice_str.h is Single-Header Cross-Platform C library for working with Strings, It provides functions for working with strings without depending on string.h and other dependencies...

All strings returned are NULL-terminated and the library allows to use custom memory allocators if you wanna! ;)

To use it #define ICE_STR_IMPL then #include "ice_str.h" in your C/C++ code!


================================== Usage Example ==================================

#define ICE_STR_IMPL
#include "ice_str.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // define variables
    char* str;
    char** strs;
    char* strs_joined;
    unsigned len = 0;
    unsigned i;

    // Create string to split it into array
    str = "First\nSecond\nThird\nFourth";

    // Split it and get length by using len as pointer to store length of created array
    strs = ice_str_splitlines(str, &len);

    // Iterate and print each string split-lined (via \n char)
    for (i = 0; i < len; i++) {
        printf("strs[%u] = %s\n", i, strs[i]);
    }

    // Join strings from array but with + mark (If you don't want to join with mark pass NULL instead of char)
    strs_joined = ice_str_join(strs, len, '+');
    
    // Print the result
    printf("strs_joined = %s\n", strs_joined);
    
    // Free allocated strings
    ice_str_free(strs_joined);
    ice_str_arr_free(strs, len);

    return 0;
}


=================================== Library API ===================================

// Custom Memory Allocators (Can be customized, Defaults to [malloc, calloc, realloc, free])
#define ICE_STR_MALLOC(sz)
#define ICE_STR_CALLOC(n, sz)
#define ICE_STR_REALLOC(ptr, sz)
#define ICE_STR_FREE(ptr)

// Boolean Enum, To avoid including stdbool.h
typedef enum ice_str_bool {
    ICE_STR_FALSE = -1,
    ICE_STR_TRUE = 0
} ice_str_bool;

// Returns string length
unsigned ice_str_len(const char* str);

// Returns substring of string from index from_idx to index to_idx on allocation success or NULL on allocation failure
char* ice_str_sub(const char* str, unsigned from_idx, unsigned to_idx);

// Concats 2 strings and returns resulted string on allocation success or NULL on allocation failure
char* ice_str_concat(const char* str1, const char* str2);

// Concats 2 strings and returns resulted string on allocation success or NULL on allocation failure
char* ice_str_insert(const char* str1, const char* str2, unsigned idx);

// Returns number of string str2 matches in string str1, idxs can be pointer to array of unsigned integers (To be Dynamically-Allocated) to store the matching indexes
unsigned ice_str_matches(const char* str1, const char* str2, unsigned **idxs);

// Replaces string str1 in string str with string str2 and returns result string on allocation success or NULL on allocation failure
char* ice_str_rep(const char* str, const char* str1, const char* str2);

// Returns string repeated multiple times on allocation success or NULL on allocation failure
char* ice_str_dup(const char* str, unsigned times);

// Returns copy of string but malloc-ed on allocation success or NULL on allocation failure
char* ice_str_copy(const char* str);

// Returns reverse of string on allocation success or NULL on allocation failure
char* ice_str_rev(const char* str);

// Converts char to string and returns result on allocation success or NULL on allocation failure
char* ice_str_char_to_str(char ch);

// Returns ICE_STR_TRUE if str1 is same as str2, Else returns ICE_STR_FALSE
ice_str_bool ice_str_same(const char* str1, const char* str2);

// Returns uppercased version of string on allocation success or NULL on allocation failure
char* ice_str_upper(const char* str);

// Returns lowercased version of string on allocation success or NULL on allocation failure
char* ice_str_lower(const char* str);

// Returns capital case version of string on allocation success or NULL on allocation failure
char* ice_str_cap(const char* str);

// Splits string into array of strings for each delimiter and returns it on allocation success or NULL on allocation failure, arrlen is pointer to unsigned integer to store length of resulted array
char** ice_str_split(const char* str, char delim, unsigned *arrlen);

// Same like ice_str_split but uses new line character '\n' as delimiter
char** ice_str_splitlines(const char* str, unsigned *arrlen);

// Returns string which is concat of all strings from array strs on allocation success or NULL on allocation failure, arrlen should be defined for the iteration over the array and delimiter can be used to join each string with (Though it can be NULL as optional parameter)
char* ice_str_join(const char** strs, unsigned arrlen, char delim);

// Returns ICE_STR_TRUE if string str1 starts with string str2, Else returns ICE_STR_FALSE
ice_str_bool ice_str_begins(const char* str1, const char* str2);

// Returns ICE_STR_TRUE if string str1 ends with string str2, Else returns ICE_STR_FALSE
ice_str_bool ice_str_ends(const char* str1, const char* str2);

// Returns ICE_STR_TRUE if string str ends with char ch, Else returns ICE_STR_FALSE
ice_str_bool ice_str_last_char(const char* str, char ch);

// Returns char codes of the string as allocated array on allocation success or NULL on allocation failure, arrlen is pointer to unsigned integer to store length of integer array (Though you can NULL it if you know the length)
int* ice_str_to_bytes(const char* str, unsigned *arrlen);

// Returns string from char codes on allocation success or NULL on allocation failure, arrlen should be set to array length
char* ice_str_from_bytes(const int* chars, unsigned arrlen);

// Frees a String
void ice_str_free(char* str);

// Frees array of char codes
void ice_str_free_bytes(int* bytes);

// Frees array of strings, arrlen should be set to array length
void ice_str_arr_free(char** arr, unsigned arrlen);


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_str.h in the code...
#define ICE_STR_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_STR_VECTORCALL      // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_STR_FASTCALL        // fastcall
#define ICE_STR_STDCALL         // stdcall
#define ICE_STR_CDECL           // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_STR_MICROSOFT       // Microsoft platforms
#define ICE_STR_NON_MICROSOFT   // Non-Microsoft platforms

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_STR_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_STR_DLLEXPORT       // Export the symbols to build as shared library
#define ICE_STR_DLLIMPORT       // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_STR_INLINE          // inlines library functions (Only works on C99 Standard and above)
#define ICE_STR_EXTERN          // externs library functions
#define ICE_STR_STATIC          // statics library functions

// NOTE: ICE_STR_EXTERN and ICE_STR_STATIC cannot be #defined together in the code...


================================= Support ice_libs ================================

ice_str.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_STR_H
#define ICE_STR_H 1

/* Allow to use calling conventions if desired... */
#if defined(ICE_STR_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_STR_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_STR_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_STR_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_STR_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_STR_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_STR_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_STR_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_STR_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_STR_CDECL)
#  if defined(_MSC_VER)
#    define ICE_STR_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_STR_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_STR_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_STR_MICROSOFT) || defined(ICE_STR_NON_MICROSOFT))
#  define ICE_STR_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
#if defined(ICE_STR_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_STR_MICROSOFT 1
#  else
#    define ICE_STR_NON_MICROSOFT 1
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_STR_EXTERN) && defined(ICE_STR_STATIC))
#  define ICE_STR_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_STR_EXTERN)
#  define ICE_STR_APIDEF extern
#elif defined(ICE_STR_STATIC)
#  define ICE_STR_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_STR_INLINE to enable inline functionality.
*/
#if defined(ICE_STR_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_STR_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_STR_INLINEDEF inline
#  endif
#else
#  define ICE_STR_INLINEDEF
#endif

/*
Allow to build DLL via ICE_STR_DLLEXPORT or ICE_STR_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_STR_MICROSOFT)
#  if defined(ICE_STR_DLLEXPORT)
#    define ICE_STR_API __declspec(dllexport) ICE_STR_INLINEDEF
#  elif defined(ICE_STR_DLLIMPORT)
#    define ICE_STR_API __declspec(dllimport) ICE_STR_INLINEDEF
#  else
#    define ICE_STR_API ICE_STR_APIDEF ICE_STR_INLINEDEF
#  endif
#else
#  define ICE_STR_API ICE_STR_APIDEF ICE_STR_INLINEDEF
#endif

/* Custom Memory Allocators */
#ifndef ICE_STR_MALLOC
#  define ICE_STR_MALLOC(sz) malloc(sz)
#endif
#ifndef ICE_STR_CALLOC
#  define ICE_STR_CALLOC(n, sz) calloc(n, sz)
#endif
#ifndef ICE_STR_REALLOC
#  define ICE_STR_REALLOC(ptr, sz) realloc(ptr, sz)
#endif
#ifndef ICE_STR_FREE
#  define ICE_STR_FREE(ptr) free(ptr)
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_str_bool {
    ICE_STR_FALSE = -1,
    ICE_STR_TRUE = 0
} ice_str_bool;

/* ============================== Functions ============================== */

/* Returns string length */
ICE_STR_API unsigned ICE_STR_CALLCONV ice_str_len(const char* str);

/* Returns substring of string from index from_idx to index to_idx on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_sub(const char* str, unsigned from_idx, unsigned to_idx);

/* Concats 2 strings and returns resulted string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_concat(const char* str1, const char* str2);

/* Concats 2 strings and returns resulted string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_insert(const char* str1, const char* str2, unsigned idx);

/* Returns number of string str2 matches in string str1, idxs can be pointer to array of unsigned integers (To be Dynamically-Allocated) to store the matching indexes */
ICE_STR_API unsigned ICE_STR_CALLCONV ice_str_matches(const char* str1, const char* str2, unsigned **idxs);

/* Replaces string str1 in string str with string str2 and returns result string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_rep(const char* str, const char* str1, const char* str2);

/* Returns string repeated multiple times on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_dup(const char* str, unsigned times);

/* Returns copy of string but malloc-ed on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_copy(const char* str);

/* Returns reverse of string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_rev(const char* str);

/* Converts char to string and returns result on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_char_to_str(char ch);

/* Returns ICE_STR_TRUE if str1 is same as str2, Else returns ICE_STR_FALSE */
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_same(const char* str1, const char* str2);

/* Returns uppercased version of string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_upper(const char* str);

/* Returns lowercased version of string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_lower(const char* str);

/* Returns capital case version of string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_cap(const char* str);

/* Splits string into array of strings for each delimiter and returns it on allocation success or NULL on allocation failure, arrlen is pointer to unsigned integer to store length of resulted array */
ICE_STR_API char** ICE_STR_CALLCONV ice_str_split(const char* str, char delim, unsigned *arrlen);

/* Same like ice_str_split but uses new line character '\n' as delimiter */
ICE_STR_API char** ICE_STR_CALLCONV ice_str_splitlines(const char* str, unsigned *arrlen);

/* Returns string which is concat of all strings from array strs on allocation success or NULL on allocation failure, arrlen should be defined for the iteration over the array and delimiter can be used to join each string with (Though it can be NULL as optional parameter) */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_join(const char** strs, unsigned arrlen, char delim);

/* Returns ICE_STR_TRUE if string str1 starts with string str2, Else returns ICE_STR_FALSE */
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_begins(const char* str1, const char* str2);

/* Returns ICE_STR_TRUE if string str1 ends with string str2, Else returns ICE_STR_FALSE */
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_ends(const char* str1, const char* str2);

/* Returns ICE_STR_TRUE if string str ends with char ch, Else returns ICE_STR_FALSE */
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_last_char(const char* str, char ch);

/* Returns char codes of the string as allocated array on allocation success or NULL on allocation failure, arrlen is pointer to unsigned integer to store length of integer array (Though you can NULL it if you know the length) */
ICE_STR_API int* ICE_STR_CALLCONV ice_str_to_bytes(const char* str, unsigned *arrlen);

/* Returns string from char codes on allocation success or NULL on allocation failure, arrlen should be set to array length */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_from_bytes(const int* chars, unsigned arrlen);

/* Frees a String */
ICE_STR_API void ICE_STR_CALLCONV ice_str_free(char* str);

/* Frees array of char codes */
ICE_STR_API void ICE_STR_CALLCONV ice_str_free_bytes(int* bytes);

/* Frees array of strings, arrlen should be set to array length */
ICE_STR_API void ICE_STR_CALLCONV ice_str_arr_free(char** arr, unsigned arrlen);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_STR_IMPL)

/* Returns string length */
ICE_STR_API unsigned ICE_STR_CALLCONV ice_str_len(const char* str) {
    unsigned res = 0;
    while (str[res] != 0) res++;   
    return res;
}

/* Returns substring of string from index from_idx to index to_idx on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_sub(const char* str, unsigned from_idx, unsigned to_idx) {
    int i = 0;
    unsigned count = 0;
    ice_str_bool backwards = (to_idx < from_idx) ? ICE_STR_TRUE : ICE_STR_FALSE;
    unsigned len = (backwards == ICE_STR_TRUE) ? ((from_idx - to_idx) + 2) : ((to_idx - from_idx) + 2);
    unsigned alloc_size = (len * sizeof(char));
    char* res = ICE_STR_MALLOC(alloc_size);
    
    if (res == 0) return 0;
    
    if (backwards == ICE_STR_TRUE) {
        for (i = ((int) from_idx); i >= ((int) to_idx); i--) {
            res[count] = str[i];
            count++;
        }
    } else {
        for (i = ((int) from_idx); i <= ((int) to_idx); i++) {
            res[count] = str[i];
            count++;
        }
    }
    
    res[count] = 0;
    
    return res;
}

/* Concats 2 strings and returns resulted string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_concat(const char* str1, const char* str2) {
    unsigned len1 = ice_str_len(str1);
    unsigned len2 = ice_str_len(str2);
    unsigned count = 0;
    unsigned alloc_size = ((len1 + len2 + 1) * sizeof(char));
    unsigned i;
    char* res = ICE_STR_MALLOC(alloc_size);
    
    if (res == 0) return 0;
    
    for (i = 0; i < len1; i++) {
        res[count] = str1[i];
        count++;
    }
    
    for (i = 0; i < len2; i++) {
        res[count] = str2[i];
        count++;
    }
    
    res[count] = 0;
    
    return res;
}

/* Inserts string str2 into string str1 at specified index and returns result string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_insert(const char* str1, const char* str2, unsigned idx) {
    unsigned len1 = ice_str_len(str1);
    unsigned len2 = ice_str_len(str2);
    unsigned count = 0;
    unsigned alloc_size = ((len1 + len2 + 1) * sizeof(char));
    unsigned i;
    
    char* res = ICE_STR_MALLOC(alloc_size);
    
    if (res == 0) return 0;
    
    for (i = 0; i < idx; i++) {
        res[count] = str1[i];
        count++;
    }
    
    for (i = 0; i < len2; i++) {
        res[count] = str2[i];
        count++;
    }
    
    for (i = idx; i < len1; i++) {
        res[count] = str1[i];
        count++;
    }
    
    res[len1 + len2] = 0;

    return res;
}

/* Returns number of string str2 matches in string str1, idxs can be pointer to array of unsigned integers (To be Dynamically-Allocated) to store the matching indexes */
ICE_STR_API unsigned ICE_STR_CALLCONV ice_str_matches(const char* str1, const char* str2, unsigned **idxs) {
    unsigned len1 = ice_str_len(str1);
    unsigned len2 = ice_str_len(str2);
    unsigned char_matches = 0;
    unsigned matches = 0;
    unsigned alloc_size;
    unsigned i;

    for (i = 0; i < len1; i++) {
        if ((str1[i] == str2[0]) && ((i + (len2 - 1)) < len1)) {
            unsigned j;

            for (j = 0; j < len2; j++) {
                if (str1[i + j] == str2[j]) {
                    char_matches++;
                }
            }

            if (char_matches == len2) {
                matches++;
                char_matches = 0;
            }
        }
    }
    
    if (idxs != 0) {
        unsigned* matches_idxs;
        unsigned count = 0;

        alloc_size = (matches * sizeof(unsigned));
        matches_idxs = ICE_STR_MALLOC(alloc_size);

        if (matches_idxs == 0) return 0;

        for (i = 0; i < len1; i++) {
            if ((str1[i] == str2[0]) && ((i + (len2 - 1)) < len1)) {
                matches_idxs[count] = i;
                count++;
            }
        }

        *idxs = matches_idxs;
    }

    return matches;
}

/* Replaces string str1 in string str with string str2 and returns result string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_rep(const char* str, const char* str1, const char* str2) {
    char* res;

    unsigned len1 = ice_str_len(str);
    unsigned len2 = ice_str_len(str1);
    unsigned len3 = ice_str_len(str2);
    
    unsigned* matches_idxs;
    unsigned char_matches = 0;
    unsigned matches = 0;
    unsigned count = 0;
    unsigned count2 = 0;
    unsigned matches_alloc_size;
    unsigned alloc_size;
    unsigned i;

    for (i = 0; i < len1; i++) {
        if ((str[i] == str1[0]) && ((i + (len2 - 1)) < len1)) {
            unsigned j;

            for (j = 0; j < len2; j++) {
                if (str[i + j] == str1[j]) {
                    char_matches++;
                }
            }

            if (char_matches == len2) {
                matches++;
                char_matches = 0;
            }
        }
    }

    matches_alloc_size = (matches * sizeof(unsigned));
    alloc_size = ((len1 + ((len3 - len2) * matches) + 1) * sizeof(char));

    matches_idxs = ICE_STR_MALLOC(matches_alloc_size);
    if (matches_idxs == 0) return 0;
    
    for (i = 0; i < len1; i++) {
        if ((str[i] == str1[0]) && ((i + (len2 - 1)) < len1)) {
            matches_idxs[count] = i;
            count++;
        }
    }

    res = ICE_STR_MALLOC(alloc_size);

    if (res == 0) return 0;

    for (i = 0; i < len1; i++) {
        unsigned j;

        for (j = 0; j < count; j++) {
            if (i == matches_idxs[j]) {
                unsigned k;

                for (k = 0; k < len3; k++) {
                    res[count2] = str2[k];
                    count2++;
                }
                
                if (len2 == len3) {
                    i += len3;
                } else if (len2 < len3) {
                    i += +(len2 - len3);
                } else if (len2 > len3) {
                    i += len2 - len3;
                }
            }
        }

        res[count2] = str[i];
        count2++;
    }
    
    res[(len1 + (len3 - len2) * matches)] = 0;
    ICE_STR_FREE(matches_idxs);
    matches_idxs = 0;
    
    return res;
}

/* Returns string repeated multiple times on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_dup(const char* str, unsigned times) {
    unsigned len = ice_str_len(str);
    unsigned count = 0;
    unsigned alloc_size = (((len * times) + 1) * sizeof(char));
    char* res = ICE_STR_MALLOC(alloc_size);
    unsigned i;
    
    if (res == 0) return 0;

    for (i = 0; i < times; i++) {
        unsigned j;

        for (j = 0; j < len; j++) {
            res[count] = str[j];
            count++;
        }
    }

    res[len * times] = 0;
    
    return res;
}

/* Returns copy of string but malloc-ed on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_copy(const char* str) {
    unsigned len = ice_str_len(str);
    unsigned alloc_size = ((len + 1) * sizeof(char));
    char* res = ICE_STR_MALLOC(alloc_size);
    unsigned i;

    if (res == 0) return 0;

    for (i = 0; i < len; i++) res[i] = str[i];

    res[len] = 0;

    return res;
}

/* Returns reverse of string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_rev(const char* str) {
    unsigned len = ice_str_len(str);
    unsigned count = 0;
    unsigned alloc_size = ((len + 1) * sizeof(char));
    char* res = ICE_STR_MALLOC(alloc_size);
    unsigned i;

    if (res == 0) return 0;

    for (i = 0; i < len; i++) {
        res[count] = str[(len - i) - 1];
        count++;
    }
    
    res[count] = 0;
    
    return res;
}

/* Converts char to string and returns result on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_char_to_str(char ch) {
    unsigned alloc_size = (2 * sizeof(char));
    char* res = ICE_STR_MALLOC(alloc_size);

    if (res == 0) return 0;
    
    res[0] = ch;
    res[1] = 0;
    
    return res;
}

/* Returns ICE_STR_TRUE if str1 is same as str2, Else returns ICE_STR_FALSE */
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_same(const char* str1, const char* str2) {
    unsigned len1 = ice_str_len(str1);
    unsigned len2 = ice_str_len(str2);
    unsigned count = 0;
    unsigned i;
    
    if (len1 != len2) return ICE_STR_FALSE;

    for (i = 0; i < len1; i++) {
        if (str1[i] == str2[i]) count++;
    }
    
    return (count == len1) ? ICE_STR_TRUE : ICE_STR_FALSE;
}

/* Returns uppercased version of string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_upper(const char* str) {
    unsigned len = ice_str_len(str);
    unsigned alloc_size = ((len + 1) * sizeof(char));
    char* res = ICE_STR_MALLOC(alloc_size);
    unsigned i;

    if (res == 0) return 0;

    for (i = 0; i < len; i++) {
        int c = (int) str[i];
        
        if (c >= 97 && c <= 122) {
            res[i] = (char)(c - 32);
        } else {
            res[i] = str[i];
        }
    }
    
    res[len] = 0;
    
    return res;
}

/* Returns lowercased version of string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_lower(const char* str) {
    unsigned len = ice_str_len(str);
    unsigned alloc_size = ((len + 1) * sizeof(char));
    char* res = ICE_STR_MALLOC(alloc_size);
    unsigned i;

    if (res == 0) return 0;

    for (i = 0; i < len; i++) {
        int c = (int) str[i];
        
        if (c >= 65 && c <= 90) {
            res[i] = (char)(c + 32);
        } else {
            res[i] = str[i];
        }
    }
    
    res[len] = 0;
    
    return res;
}

/* Returns capital case version of string on allocation success or NULL on allocation failure */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_cap(const char* str) {
    unsigned len = ice_str_len(str);
    unsigned alloc_size = ((len + 1) * sizeof(char));
    char* res = ICE_STR_MALLOC(alloc_size);
    int c = (int) str[0];
    unsigned i;
    
    if (res == 0) return 0;

    if (c >= 97 && c <= 122) {
        res[0] = (char)(c - 32);
    } else {
        res[0] = str[0];
    }
    
    for (i = 1; i < len; i++) {
        res[i] = str[i];
    }
    
    res[len] = 0;
    
    return res;
}

/* Splits string into array of strings for each delimiter and returns it on allocation success or NULL on allocation failure, arrlen is pointer to unsigned integer to store length of resulted array */
ICE_STR_API char** ICE_STR_CALLCONV ice_str_split(const char* str, char delim, unsigned *arrlen) {
    unsigned len = ice_str_len(str);
    unsigned arr_len = 0;
    unsigned arr_idx = 0;
    unsigned sz = 0;
    char** res;
    unsigned alloc_size;
    unsigned i;

    if (str[len - 1] != delim) arr_len++;

    alloc_size = (arr_len * sizeof(char*));

    res = ICE_STR_MALLOC(alloc_size);

    if (res == 0) return 0;

    for (i = 0; i < len; i++) {
        if (str[i] == delim) {
            if (sz == 0) {
                res[arr_idx] = ice_str_sub(str, 0, i - 1);
            } else {
                res[arr_idx] = ice_str_sub(str, sz + 1, i - 1);
            }

            arr_len++;
            arr_idx++;
            sz = i;
        }
        
        if (i == len - 1 && str[len - 1] != delim) {
            res[arr_idx] = ice_str_sub(str, sz + 1, i);
        }
    }

    *arrlen = arr_len;
    
    return res;
}

/* Same like ice_str_split but uses new line character '\n' as delimiter */
ICE_STR_API char** ICE_STR_CALLCONV ice_str_splitlines(const char* str, unsigned *arrlen) {
    return ice_str_split(str, '\n', arrlen);
}

/* Returns string which is concat of all strings from array strs on allocation success or NULL on allocation failure, arrlen should be defined for the iteration over the array and delimiter can be used to join each string with (Though it can be NULL as optional parameter) */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_join(const char** strs, unsigned arrlen, char delim) {
    char* res;
    unsigned len = 0;
    unsigned alloc_size = ((len + 1) * sizeof(char));
    unsigned count = 0;
    unsigned i;

    if (delim != 0) {
        len += arrlen - 1;
    }

    for (i = 0; i < arrlen; i++) {
        len += ice_str_len(strs[i]);
    }

    res = ICE_STR_MALLOC(alloc_size);

    if (res == 0) return 0;

    for (i = 0; i < arrlen; i++) {
        unsigned lenstr = ice_str_len(strs[i]);
        unsigned j;

        for (j = 0; j < lenstr; j++) {
            res[count] = strs[i][j];
            count++;
        }

        if (i != arrlen - 1 && delim != 0) {
            res[count] = delim;
            count++;
        }
    }

    res[len] = 0;
    
    return res;
}

/* Returns ICE_STR_TRUE if string str1 starts with string str2, Else returns ICE_STR_FALSE */
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_begins(const char* str1, const char* str2) {
    unsigned len = ice_str_len(str2);
    char* sub = ice_str_sub(str1, 0, len - 1);
    ice_str_bool res = ice_str_same(sub, str2);
    
    ice_str_free(sub);

    return res;
}

/* Returns ICE_STR_TRUE if string str1 ends with string str2, Else returns ICE_STR_FALSE */
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_ends(const char* str1, const char* str2) {
    unsigned len1 = ice_str_len(str1);
    unsigned len2 = ice_str_len(str2);
    char* sub = ice_str_sub(str1, (len1 - len2), len1 - 1);
    ice_str_bool res = ice_str_same(sub, str2);
    
    ice_str_free(sub);

    return res;
}

/* Returns ICE_STR_TRUE if string str ends with char ch, Else returns ICE_STR_FALSE */
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_last_char(const char* str, char ch) {
    unsigned len = ice_str_len(str);

    return (str[len - 1] == ch) ? ICE_STR_TRUE : ICE_STR_FALSE;
}

/* Returns char codes of the string as allocated array on allocation success or NULL on allocation failure, arrlen is pointer to unsigned integer to store length of integer array (Though you can NULL it if you know the length) */
ICE_STR_API int* ICE_STR_CALLCONV ice_str_to_bytes(const char* str, unsigned *arrlen) {
    unsigned len = ice_str_len(str);
    unsigned alloc_size = (len * sizeof(int));
    int* res = ICE_STR_MALLOC(alloc_size);
    unsigned i;
    
    if (res == 0) return 0;
    
    for (i = 0; i < len; i++) {
        res[i] = (int) str[i];
    }

    *arrlen = len;
    
    return res;
}

/* Returns string from char codes on allocation success or NULL on allocation failure, arrlen should be set to array length */
ICE_STR_API char* ICE_STR_CALLCONV ice_str_from_bytes(const int* chars, unsigned arrlen) {
    unsigned alloc_size = ((arrlen + 1) * sizeof(char));
    char* res = ICE_STR_MALLOC(alloc_size);
    unsigned i;
    
    if (res == 0) return 0;
    
    for (i = 0; i < arrlen; i++) {
        res[i] = (char) chars[i];
    }
    
    res[arrlen] = 0;
    
    return res;
}

/* Frees a String */
ICE_STR_API void ICE_STR_CALLCONV ice_str_free(char* str) {
    ICE_STR_FREE(str);
    str = 0;
}

/* Frees array of char codes */
ICE_STR_API void ICE_STR_CALLCONV ice_str_free_bytes(int* bytes) {
    ICE_STR_FREE(bytes);
    bytes = 0;
}

/* Frees array of strings, arrlen should be set to array length */
ICE_STR_API void ICE_STR_CALLCONV ice_str_arr_free(char** arr, unsigned arrlen) {
    unsigned i;
    
    for (i = 0; i < arrlen; i++) {
        ICE_STR_FREE(arr[i]);
        arr[i] = 0;
    }
    
    arr = 0;
}

#endif  /* ICE_STR_H */
#endif  /* ICE_STR_H */

/*
ice_str.h is dual-licensed, Choose the one you prefer!

------------------------------------------------------------------------
LICENSE A - PUBLIC DOMAIN LICENSE
------------------------------------------------------------------------
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

------------------------------------------------------------------------
LICENSE B - MIT LICENSE
------------------------------------------------------------------------
Copyright (c) 2021 - <Present> Rabia Alhaffar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/