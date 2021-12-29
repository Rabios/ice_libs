/*
ice_arr.h, Single-Header Cross-Platform C library for working with Arrays!

TODO: Complete and apply fixes!


================================== Full Overview ==================================

ice_arr.h, Single-Header Cross-Platform C library for working with Arrays, It provides utilites for working with arrays...

To use it #define ICE_ARR_IMPL then #include "ice_arr.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================



=================================== Library API ===================================



================================== Linking Flags ==================================



================================= Usable #define(s) ===============================



================================= Support ice_libs ================================

ice_arr.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_ARR_H
#define ICE_ARR_H 1

/* Disable security warnings for MSVC compiler, We don't want to force using C11! */
#ifdef _MSC_VER
#  ifndef _CRT_SECURE_NO_DEPRECATE
#    define _CRT_SECURE_NO_DEPRECATE 1
#  endif
#  ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS 1
#  endif
#  pragma warning(disable:4996)
#endif

/* Define C interface for Windows libraries! ;) */
#ifndef CINTERFACE
#  define CINTERFACE 1
#endif

/* Allow to use calling conventions if desired... */
#if defined(ICE_ARR_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_ARR_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_ARR_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_ARR_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_ARR_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_ARR_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_ARR_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_ARR_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_ARR_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_ARR_CDECL)
#  if defined(_MSC_VER)
#    define ICE_ARR_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_ARR_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_ARR_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_ARR_MICROSOFT) || defined(ICE_ARR_NON_MICROSOFT))
#  define ICE_ARR_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
#if defined(ICE_ARR_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_ARR_MICROSOFT 1
#  else
#    define ICE_ARR_NON_MICROSOFT 1
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_ARR_EXTERN) && defined(ICE_ARR_STATIC))
#  define ICE_ARR_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_ARR_EXTERN)
#  define ICE_ARR_APIDEF extern
#elif defined(ICE_ARR_STATIC)
#  define ICE_ARR_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_ARR_INLINE to enable inline functionality.
*/
#if defined(ICE_ARR_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_ARR_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_ARR_INLINEDEF inline
#  endif
#else
#  define ICE_ARR_INLINEDEF
#endif

/*
Allow to build DLL via ICE_ARR_DLLEXPORT or ICE_ARR_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_ARR_MICROSOFT)
#  if defined(ICE_ARR_DLLEXPORT)
#    define ICE_ARR_API __declspec(dllexport) ICE_ARR_INLINEDEF
#  elif defined(ICE_ARR_DLLIMPORT)
#    define ICE_ARR_API __declspec(dllimport) ICE_ARR_INLINEDEF
#  else
#    define ICE_ARR_API ICE_ARR_APIDEF ICE_ARR_INLINEDEF
#  endif
#else
#  define ICE_ARR_API ICE_ARR_APIDEF ICE_ARR_INLINEDEF
#endif

/* Custom Memory Allocators */
#ifndef ICE_ARR_MALLOC
#  define ICE_ARR_MALLOC(sz) malloc(sz)
#endif
#ifndef ICE_ARR_CALLOC
#  define ICE_ARR_CALLOC(n, sz) calloc(n, sz)
#endif
#ifndef ICE_ARR_REALLOC
#  define ICE_ARR_REALLOC(ptr, sz) realloc(ptr, sz)
#endif
#ifndef ICE_ARR_FREE
#  define ICE_ARR_FREE(ptr) free(ptr)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_arr_bool {
    ICE_ARR_FALSE = -1,
    ICE_ARR_TRUE = 0
} ice_arr_bool;

/* Array */
typedef struct ice_arr_array {
    void** data;                /* Elements of the Array */
    long size;                  /* Size of allocation that Array uses */
    long len;                   /* Length of the Array */
} ice_arr_array;


/* ============================== Macros ============================== */

#define ice_arr_get(arr, idx, type) (*((type*) arr.data[idx]))

#define ICE_ARR_PTR_SIZE sizeof(void*)

/* ============================== Functions ============================== */

/* Creates/Allocates a new dynamic Array with no data */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_new(void);

/* Deletes/Deallocates the dynamic Array including his elements */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_delete(ice_arr_array* arr);

/* Pushes element to the Array, Array element should be pointer to variable */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_push(ice_arr_array* arr, void* v);

/* Deletes last element from the Array and returns it */
ICE_ARR_API void* ICE_ARR_CALLCONV ice_arr_pop(ice_arr_array* arr);

/* Copies elements of first Array to second one, If the second Array has elements then the function pushes elements of first Array to second Array (No Overwrite) */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_copy(ice_arr_array* arr1, ice_arr_array* arr2);

/* Creates an Array consists of Array's elements duplicated by times */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_dup(ice_arr_array arr, unsigned long count);

/* Deletes first element from the Array and returns it */
ICE_ARR_API void* ICE_ARR_CALLCONV ice_arr_shift(ice_arr_array* arr);

/* Adds element to the beginning of the Array */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_unshift(ice_arr_array* arr, void* v);

/* Reverses the Array and stores result in second Array */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_rev(ice_arr_array* arr1, ice_arr_array* arr2);

/* Fills the Array elements with one value */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_fill(ice_arr_array* arr, void* v);

/* Clears the Array */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_clear(ice_arr_array* arr);

/* Returns an Array that contains first n elements of Array */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_first(ice_arr_array arr, unsigned long count);

/* Returns an Array that contains last n elements of Array */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_last(ice_arr_array arr, unsigned long count);

/* Returns an Array that consists of concation of 2 Arrays */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_concat(ice_arr_array arr1, ice_arr_array arr2);

/* Returns ICE_ARR_TRUE if 2 Arrays matches, Else returns ICE_ARR_FALSE */
ICE_ARR_API ice_arr_bool ICE_ARR_CALLCONV ice_arr_match(ice_arr_array arr1, ice_arr_array arr2);

/* Returns how many of the element exists in the Array */
ICE_ARR_API unsigned long ICE_ARR_CALLCONV ice_arr_matches(ice_arr_array arr, void* v);

/* Returns ICE_ARR_TRUE if Array includes element, Else returns ICE_ARR_FALSE */
ICE_ARR_API ice_arr_bool ICE_ARR_CALLCONV ice_arr_includes(ice_arr_array arr, void* v);

/*
#define ice_arr_sub
#define ice_arr_rem
#define ice_arr_without
#define ice_arr_rest
#define ice_arr_uniq
#define ice_arr_index
#define ice_arr_rindex
#define ice_arr_diff
#define ice_arr_range
#define ice_arr_min
#define ice_arr_max
#define ice_arr_compact
#define ice_arr_tail
#define ice_arr_intersect
#define ice_arr_foreach
#define ice_arr_union
#define ice_arr_lrot
#define ice_arr_rrot
#define ice_arr_move
#define ice_arr_sort
#define ice_arr_xsort
*/

#ifdef __cplusplus
}
#endif

#if defined(ICE_ARR_IMPL)

/* Creates/Allocates a new dynamic Array with no data */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_new(void) {
    ice_arr_array arr;
    
    arr.data = ICE_ARR_MALLOC(0);
    arr.len = 0;
    arr.size = 0;

    return arr;
}

/* Deletes/Deallocates the dynamic Array including his elements */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_delete(ice_arr_array* arr) {
    unsigned i;
    
    for (i = 0; i < arr->len; i++) {
        arr->data[i] = 0;
    }
    
    ICE_ARR_FREE(arr->data);
    arr->data = 0;

    arr->len = 0;
    arr->size = 0;
}

/* Pushes element to the Array, Array element should be pointer to variable */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_push(ice_arr_array* arr, void* v) {
    arr->size += ICE_ARR_PTR_SIZE;
    arr->len++;
    
    arr->data = ICE_ARR_REALLOC(arr->data, arr->size);
    
    if (arr->data == 0) {
        arr->data = 0;
        arr->len = 0;
        arr->size = 0;
    }
    
    arr->data[arr->len - 1] = v;
}

/* Deletes last element from the Array and returns it */
ICE_ARR_API void* ICE_ARR_CALLCONV ice_arr_pop(ice_arr_array* arr) {
    void* res = arr->data[arr->len - 1];

    arr->size -= ICE_ARR_PTR_SIZE;
    arr->len--;
    
    arr->data = ICE_ARR_REALLOC(arr->data, arr->size);
    
    if (arr->data == 0) {
        arr->data = 0;
        arr->len = 0;
        arr->size = 0;
    }

    return res;
}

/* Copies elements of first Array to second one, If the second Array has elements then the function pushes elements of first Array to second Array (No Overwrite) */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_copy(ice_arr_array* arr1, ice_arr_array* arr2) {
    int i;

    for (i = 0; i < arr1->len; i++) {
        ice_arr_push(arr2, arr1->data[i]);
    }
}

/* Creates an Array consists of Array's elements duplicated by times */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_dup(ice_arr_array arr, unsigned long count) {
    int i, j;
    ice_arr_array res;

    if ((times == 0) || (times == 1)) return arr;

    res = ice_arr_new();

    for (i = 0; i <= times; i++) {
        for (j = 0; j < arr.len; j++) {
            ice_arr_push(&res, arr.data[j]);
        }
    }

    return res;
}

/* Deletes first element from the Array and returns it */
ICE_ARR_API void* ICE_ARR_CALLCONV ice_arr_shift(ice_arr_array* arr) {
    int i;
    void* res = arr->data[0];

    arr->data[0] = 0;

    for (i = 1; i < arr->len; i++) {
        arr->data[i - 1] = arr->data[i];
    }

    ice_arr_pop(arr);

    return res;
}

/* Adds element to the beginning of the Array */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_unshift(ice_arr_array* arr, void* v) {
    int i;

    arr->size += ICE_ARR_PTR_SIZE;
    arr->len++;
    
    arr->data = ICE_ARR_REALLOC(arr->data, arr->size);
    
    if (arr->data == 0) {
        arr->data = 0;
        arr->len = 0;
        arr->size = 0;
    }

    arr->data[arr->len - 1] = 0; /* NULL-element removed via unshift */

    for (i = 0; i < arr->len - 1; i++) {
        arr->data[i + 1] = arr->data[i];
    }
    
    arr->data[0] = v;
}

/* Reverses the Array and stores result in second Array */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_rev(ice_arr_array* arr1, ice_arr_array* arr2) {
    int i;

    for (i = arr->len - 1; i >= 0; i--) {
        ice_arr_push(arr2, arr1->data[i]);
    }
}

/* Fills the Array elements with one value */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_fill(ice_arr_array* arr, void* v) {
    int i;

    for (i = 0; i < arr->len; i++) {
        arr->data[i] = v;
    }
}

/* Clears the Array */
ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_clear(ice_arr_array* arr) {
    int i;

    for (i = 0; i < arr->len; i++) {
        ice_arr_pop(arr);
    }
}

/* Returns an Array that contains first n elements of Array */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_first(ice_arr_array arr, unsigned long count) {
    int i;
    ice_arr_array res;

    if ((count == 0) || (arr.len < count)) {
        res.data = 0;
        res.len = 0;
        res.size = 0;
    }

    res = ice_arr_new();

    for (i = 0; i < count; i++) {
        ice_arr_push(&res, arr.data[i]);
    }

    return res;
}

/* Returns an Array that contains last n elements of Array */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_last(ice_arr_array arr, unsigned long count) {
    int i;
    ice_arr_array res;

    if ((count == 0) || (arr.len < count)) {
        res.data = 0;
        res.len = 0;
        res.size = 0;
    }

    res = ice_arr_new();

    for (i = arr.len - 1; i >= (arr.len - count); i--) {
        ice_arr_push(&res, arr.data[i]);
    }

    return res;
}

/* Returns an Array that consists of concation of 2 Arrays */
ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_concat(ice_arr_array arr1, ice_arr_array arr2) {
    int i;
    ice_arr_array res = ice_arr_new();

    for (i = 0; i < arr1.len; i++) {
        ice_arr_push(&res, arr1.data[i]);
    }

    for (i = 0; i < arr2.len; i++) {
        ice_arr_push(&res, arr2.data[i]);
    }

    return res;
}

#define ice_arr_get(arr, idx) (*((void*) arr.data[idx]))

/* Returns ICE_ARR_TRUE if 2 Arrays matches, Else returns ICE_ARR_FALSE */
ICE_ARR_API ice_arr_bool ICE_ARR_CALLCONV ice_arr_match(ice_arr_array arr1, ice_arr_array arr2) {
    int i, count;

    if (arr1.len != arr2.len) return ICE_ARR_FALSE;

    for (i = 0; i < arr1.len; i++) {
        if (ice_arr_get(arr1, i) == ice_arr_get(arr2, i)) {
            count++;
        }
    }

    return (count == arr1.len) ? ICE_ARR_TRUE : ICE_ARR_FALSE;
}

/* Returns how many of the element exists in the Array */
ICE_ARR_API unsigned long ICE_ARR_CALLCONV ice_arr_matches(ice_arr_array arr, void* v) {
    int i;
    unsigned long matches;

    for (i = 0; i < arr.len; i++) {
        if (ice_arr_get(arr, i) == v) matches++;
    }

    return matches;
}

/* Returns ICE_ARR_TRUE if Array includes element, Else returns ICE_ARR_FALSE */
ICE_ARR_API ice_arr_bool ICE_ARR_CALLCONV ice_arr_includes(ice_arr_array arr, void* v) {
    int i;
    ice_arr_bool res = ICE_ARR_FALSE;

    for (i = 0; i < arr.len; i++) {
        if (v == (*((void*) arr.data[i]))) {
            res = ICE_ARR_TRUE;
            break;
        }
    }

    return res;
}

#endif  /* ICE_ARR_IMPL */
#endif  /* ICE_ARR_H */

/*
ice_arr.h is dual-licensed, Choose the one you prefer!

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
