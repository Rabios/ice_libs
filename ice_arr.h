// Written by Rabia Alhaffar in 1/April/2021
// ice_arr.h
// Single-Header Cross-Platform C library to work with arrays!
// Updated: 24/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_arr.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_arr is cross-platform single-header C library for working with numeric arrays!

The API is heavily inspired by JavaScript array functions and libraries like underscore.js and Lodash!

[2] USAGE:
Define ICE_ARR_IMPL then include ice_arr.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_arr
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_arr by possibly one of following things:
//
// 1. Test ice_arr on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_arr LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_arr is dual-licensed, Choose the one you prefer!

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
Copyright (c) 2021 - 2022 Rabia Alhaffar

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

#ifndef ICE_ARR_H
#define ICE_ARR_H

// Disable security warnings for MSVC compiler, We don't want to force using C11!
#ifdef _MSC_VER
#  define _CRT_SECURE_NO_DEPRECATE
#  define _CRT_SECURE_NO_WARNINGS
#  pragma warning(disable:4996)
#endif

// Define C interface for Windows libraries! ;)
#ifndef CINTERFACE
#  define CINTERFACE
#endif

// Allow to use calling conventions if desired...
#if defined(__GNUC__) || defined(__GNUG__)
#  if defined(ICE_ARR_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_ARR_CALLCONV_FASTCALL)
#    define ICE_ARR_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_ARR_CALLCONV_STDCALL)
#    define ICE_ARR_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_ARR_CALLCONV_CDECL)
#    define ICE_ARR_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_ARR_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_ARR_CALLCONV_VECTORCALL)
#    define ICE_ARR_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_ARR_CALLCONV_FASTCALL)
#    define ICE_ARR_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_ARR_CALLCONV_STDCALL)
#    define ICE_ARR_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_ARR_CALLCONV_CDECL)
#    define ICE_ARR_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_ARR_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_ARR_CALLCONV_VECTORCALL)
#    define ICE_ARR_CALLCONV __vectorcall
#  elif defined(ICE_ARR_CALLCONV_FASTCALL)
#    define ICE_ARR_CALLCONV __fastcall
#  elif defined(ICE_ARR_CALLCONV_STDCALL)
#    define ICE_ARR_CALLCONV __stdcall
#  elif defined(ICE_ARR_CALLCONV_CDECL)
#    define ICE_ARR_CALLCONV __cdecl
#  else
#    define ICE_ARR_CALLCONV
#  endif
#else
#  define ICE_ARR_CALLCONV
#endif

#if !(defined(ICE_ARR_PLATFORM_MICROSOFT) || defined(ICE_ARR_PLATFORM_UNIX) || defined(ICE_ARR_PLATFORM_BEOS))
#  define ICE_ARR_PLATFORM_AUTODETECTED
#endif

// Platform detection
#if defined(ICE_ARR_PLATFORM_AUTODETECTED)
#  if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#    define ICE_ARR_MICROSOFT
#  endif
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_ARR_EXTERN) && defined(ICE_ARR_STATIC))
#  define ICE_ARR_EXTERN
#endif

#if defined(ICE_ARR_EXTERN)
#  define ICE_ARR_APIDEF extern
#elif defined(ICE_ARR_STATIC)
#  define ICE_ARR_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_ARR_INLINE to enable inline functionality.
#if defined(ICE_ARR_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_ARR_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_ARR_INLINEDEF inline
#  endif
#else
#  define ICE_ARR_INLINEDEF
#endif

// Allow to build DLL via ICE_ARR_DLLEXPORT or ICE_ARR_DLLIMPORT if desired!
// Else, Just define API as extern C code!
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

// Custom memory allocators
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

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_arr DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum ice_arr_bool {
    ICE_ARR_TRUE    = 0,
    ICE_ARR_FALSE   = -1,
} ice_arr_bool;

typedef void (*ice_arr_iter_func)(double n);
typedef int (*ice_arr_res_func)(double a, double b);

typedef struct ice_arr_array {
    double* arr;
    int len;
    int real_len;   // Value used for max allocated length (x1.5 array length, Increases by pushing elements)
} ice_arr_array;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_arr FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_new(int len);
ICE_ARR_API  double         ICE_ARR_CALLCONV  ice_arr_get(ice_arr_array arr, int index);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_set(ice_arr_array* arr, int index, double val);
ICE_ARR_API  int            ICE_ARR_CALLCONV  ice_arr_len(ice_arr_array arr);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_pop(ice_arr_array* arr);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_shift(ice_arr_array* arr);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_push(ice_arr_array* arr, double val);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_rev(ice_arr_array* arr);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_free(ice_arr_array arr);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_fill(ice_arr_array* arr, double val);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_clear(ice_arr_array* arr);
ICE_ARR_API  double         ICE_ARR_CALLCONV  ice_arr_sum(ice_arr_array arr);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_first(ice_arr_array arr, int elems);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_last(ice_arr_array arr, int elems);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_concat(ice_arr_array a1, ice_arr_array a2);
ICE_ARR_API  ice_arr_bool   ICE_ARR_CALLCONV  ice_arr_match(ice_arr_array a1, ice_arr_array a2);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_sub(ice_arr_array arr, int from, int to);
ICE_ARR_API  ice_arr_bool   ICE_ARR_CALLCONV  ice_arr_includes(ice_arr_array arr, double val);
ICE_ARR_API  int            ICE_ARR_CALLCONV  ice_arr_matches(ice_arr_array arr, double val);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_rem(ice_arr_array* arr, int index);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_without(ice_arr_array arr, double val);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_clone(ice_arr_array arr, int n);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_rest(ice_arr_array arr, int index);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_unique(ice_arr_array arr);
ICE_ARR_API  int            ICE_ARR_CALLCONV  ice_arr_first_index(ice_arr_array arr, double val);
ICE_ARR_API  int            ICE_ARR_CALLCONV  ice_arr_last_index(ice_arr_array arr, double val);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_unshift(ice_arr_array arr, double val);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_diff(ice_arr_array a1, ice_arr_array a2);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_range(int i);
ICE_ARR_API  double         ICE_ARR_CALLCONV  ice_arr_min(ice_arr_array arr);
ICE_ARR_API  double         ICE_ARR_CALLCONV  ice_arr_max(ice_arr_array arr);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_compact(ice_arr_array arr);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_tail(ice_arr_array arr);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_intersect(ice_arr_array a1, ice_arr_array a2);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_foreach(ice_arr_array arr, ice_arr_iter_func f);
ICE_ARR_API  ice_arr_array  ICE_ARR_CALLCONV  ice_arr_union(ice_arr_array a1, ice_arr_array a2);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_rotate(ice_arr_array* arr, int times);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_move(ice_arr_array* a1, int from_index, int elems_count, int to_index, ice_arr_array* a2);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_sort(ice_arr_array* arr);
ICE_ARR_API  void           ICE_ARR_CALLCONV  ice_arr_sort_ex(ice_arr_array* arr, ice_arr_res_func f);

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_arr IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_ARR_IMPL)

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_new(int len) {
    ice_arr_array res = (ice_arr_array) {
        (double*) ICE_ARR_MALLOC((len + (len / 2)) * sizeof(double)),
        len,
        len + (len / 2),
    };
    
    for (int i = 0; i < res.len; i++) {
        res.arr[i] = 0;
    }
    
    return res;
}

ICE_ARR_API double ICE_ARR_CALLCONV ice_arr_get(ice_arr_array arr, int index) {
    if (index < arr.len) {
        return arr.arr[index];
    }
    
    return 0;
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_set(ice_arr_array* arr, int index, double val) {
    if (index < arr->len) {
        arr->arr[index] = val;
    }
}

ICE_ARR_API int ICE_ARR_CALLCONV ice_arr_len(ice_arr_array arr) {
    return arr.len;
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_pop(ice_arr_array* arr) {
    arr->len--;
    //arr->arr[arr->len - 1] = 0;
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_shift(ice_arr_array* arr) {
    arr->len--;
    
    for (int i = 1; i < arr->len + 1; i++) {
        arr->arr[i - 1] = arr->arr[i];
    }
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_push(ice_arr_array* arr, double val) {
    if (arr->len++ < arr->real_len) {
        arr->arr[arr->len - 1] = val;
    } else {
        ICE_ARR_REALLOC(arr->arr, (arr->real_len + (arr->real_len / 2)) * sizeof(double));
        arr->arr[arr->len - 1] = val;
        arr->real_len += (arr->real_len / 2);
    }
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_swap(double *a, double *b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_rev(ice_arr_array* arr) {
    for (int i = 0; i < arr->len / 2; i++) {
        ice_arr_swap(arr->arr + i, arr->arr + arr->len - 1 - i);
    }
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_free(ice_arr_array arr) {
    ICE_ARR_FREE(arr.arr);
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_fill(ice_arr_array* arr, double val) {
    for (int i = 0; i < arr->len; i++) {
        arr->arr[i] = val;
    }
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_clear(ice_arr_array* arr) {
    for (int i = 0; i < arr->len; i++) {
        arr->arr[i] = 0;
    }
}

ICE_ARR_API double ICE_ARR_CALLCONV ice_arr_sum(ice_arr_array arr) {
    double res = 0;
    
    for (int i = 0; i < arr.len; i++) {
        res += arr.arr[i];
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_first(ice_arr_array arr, int elems) {
    ice_arr_array res = ice_arr_new((elems <= 1) ? 1 : elems);
    
    for (int i = 0; i < res.len; i++) {
        res.arr[i] = arr.arr[i];
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_last(ice_arr_array arr, int elems) {
    ice_arr_array res = ice_arr_new((elems <= 1) ? 1 : elems);
    
    for (int i = 0; i < res.len; i++) {
        res.arr[i] = arr.arr[(arr.len - 1) - i];
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_concat(ice_arr_array a1, ice_arr_array a2) {
    int idx = 0;
    
    ice_arr_array res = ice_arr_new(a1.len + a2.len);
    
    for (int i = 0; i < a1.len; i++) {
        res.arr[idx + i] = a1.arr[i];
    }
    
    idx += a1.len;
    
    for (int i = 0; i < a2.len; i++) {
        res.arr[idx + i] = a2.arr[i];
    }
    
    return res;
}

ICE_ARR_API ice_arr_bool ICE_ARR_CALLCONV ice_arr_match(ice_arr_array a1, ice_arr_array a2) {
    int matches = 0;
    
    if (a1.len != a2.len) {
        return ICE_ARR_FALSE;
    }
        
    for (int i = 0; i < a1.len; i++) {
        if (a1.arr[i] == a2.arr[i]) matches++;
    }
    
    return (matches == a1.len) ? ICE_ARR_TRUE : ICE_ARR_FALSE;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_sub(ice_arr_array arr, int from, int to) {
    ice_arr_array res = ice_arr_new((from - to) + 1);
    
    int count = 0;
    for (int i = from; i <= to; i++) {
        res.arr[count] = arr.arr[i];
        count++;
    }
    
    return res;
}

ICE_ARR_API ice_arr_bool ICE_ARR_CALLCONV ice_arr_includes(ice_arr_array arr, double val) {
    ice_arr_bool res = ICE_ARR_FALSE;
    
    for (int i = 0; i < arr.len; i++) {
        if (arr.arr[i] == val) {
            res = ICE_ARR_TRUE;
            break;
        }
    }
    
    return res;
}

ICE_ARR_API int ICE_ARR_CALLCONV ice_arr_matches(ice_arr_array arr, double val) {
    int matches = 0;
    
    for (int i = 0; i < arr.len; i++) {
        if (arr.arr[i] == val) matches++;
    }
    
    return matches;
}

ICE_ARR_API int ICE_ARR_CALLCONV ice_arr_first_index(ice_arr_array arr, double val) {
    int occurence = 0;
    
    for (int i = 0; i < arr.len; i++) {
        if (arr.arr[i] == val) {
            occurence = i;
            break;
        }
    }
    
    return occurence;
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_rem(ice_arr_array* arr, int index) {
    if (index < arr->len) {
        arr->len--;
    
        for (int i = index; i < arr->len + 1; i++) {
            arr->arr[i] = arr->arr[i + 1];
        }
    }
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_without(ice_arr_array arr, double val) {
    int matches = 0;
    int count   = 0;
    
    for (int i = 0; i < arr.len; i++) {
        if (arr.arr[i] == val) matches++;
    }
    
    ice_arr_array res = ice_arr_new(arr.len - matches);
    
    for (int i = 0; i < arr.len; i++) {
        if (arr.arr[i] != val) {
            res.arr[count] = arr.arr[i];
            count++;
        }
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_clone(ice_arr_array arr, int n) {
    int count = 0;
    ice_arr_array res = ice_arr_new(arr.len * n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < arr.len; j++) {
            res.arr[j + count] = arr.arr[j];
        }
        
        count += arr.len;
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_rest(ice_arr_array arr, int index) {
    ice_arr_array res = ice_arr_new(arr.len - 1);
    
    for (int i = 0; i < arr.len; i++) {
        if (!(i == index)) {
            res.arr[i] = arr.arr[i];
        }
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_unique(ice_arr_array arr) {
    int len = 0;
    int count = 0;
    
    for (int i = 0; i < arr.len; i++) {
        if (ice_arr_matches(arr, arr.arr[i]) == 1) {
            len++;
        }
    }
    
    ice_arr_array res = ice_arr_new(len);
    
    for (int i = 0; i < arr.len; i++) {
        if (ice_arr_matches(arr, arr.arr[i]) == 1) {
            res.arr[count] = arr.arr[i];
            count++;
        }
    }
    
    return res;
}

ICE_ARR_API int ICE_ARR_CALLCONV ice_arr_last_index(ice_arr_array arr, double val) {
    int occurence = 0;
    
    for (int i = 0; i < arr.len; i++) {
        if (arr.arr[i] == val) {
            if (i >= occurence) {
                occurence = i;
            }
        }
    }
    
    return occurence;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_unshift(ice_arr_array arr, double val) {
    ice_arr_array res = ice_arr_new(arr.len + 1);
    arr.arr[0] = val;
    
    for (int i = 0; i < arr.len; i++) {
        res.arr[i + 1] = arr.arr[i];
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_diff(ice_arr_array a1, ice_arr_array a2) {
    int len = 0;
    int count = 0;
    
    for (int i = 0; i < a1.len; i++) {
        if (ice_arr_matches(a2, a1.arr[i]) == 1) {
            len++;
        }
    }
    
    ice_arr_array res = ice_arr_new(len);
    
    for (int i = 0; i < a1.len; i++) {
        if (ice_arr_matches(a2, a1.arr[i]) == 1) {
            res.arr[count] = a1.arr[i];
            count++;
        }
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_range(int i) {
    ice_arr_array res = ice_arr_new(i);
    
    for (int j = 0; j < i; j++) {
        res.arr[j] = i;
    }
    
    return res;
}

ICE_ARR_API double ICE_ARR_CALLCONV ice_arr_min(ice_arr_array arr) {
    double n  = (1 / 0);
    
    for (int i = 0; i < arr.len; i++) {
        if (arr.arr[i] < n) {
            n = arr.arr[i];
        }
    }
    
    return n;
}

ICE_ARR_API double ICE_ARR_CALLCONV ice_arr_max(ice_arr_array arr) {
    double n  = -(1 / 0);
    
    for (int i = 0; i < arr.len; i++) {
        if (arr.arr[i] > n) {
            n = arr.arr[i];
        }
    }
    
    return n;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_compact(ice_arr_array arr) {
    int zeros = ice_arr_matches(arr, 0);
    int count = 0;
    ice_arr_array res = ice_arr_new(arr.len - zeros);
    
    for (int i = 0; i < arr.len; i++) {
        if (arr.arr[i] != 0) {
            res.arr[count] = arr.arr[i];
            count++;
        }
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_tail(ice_arr_array arr) {
    ice_arr_array res = ice_arr_new(arr.len - 1);
    
    for (int i = 1; i < arr.len; i++) {
        res.arr[i - 1] = arr.arr[i];
    }
    
    return res;
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_intersect(ice_arr_array a1, ice_arr_array a2) {
    int len = 0;
    int count = 0;
    
    for (int i = 0; i < a1.len; i++) {
        if (ice_arr_matches(a2, a1.arr[i]) >= 1 && ice_arr_matches(a1, a1.arr[i]) >= 1) {
            len++;
        }
    }
    
    ice_arr_array res = ice_arr_new(len);
    
    for (int i = 0; i < a1.len; i++) {
        if (ice_arr_matches(a2, a1.arr[i]) >= 1) {
            if (ice_arr_matches(a1, a1.arr[i])) {
                res.arr[count] = a2.arr[i];
                count++;
            }
        } else if (ice_arr_matches(a1, a1.arr[i]) >= 1) {
            if (ice_arr_matches(a2, a1.arr[i])) {
                res.arr[count] = a1.arr[i];
                count++;
            }
        }
    }
    
    return res;
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_foreach(ice_arr_array arr, ice_arr_iter_func f) {
    for (int i = 0; i < arr.len; i++) {
        f(arr.arr[i]);
    }
}

ICE_ARR_API ice_arr_array ICE_ARR_CALLCONV ice_arr_union(ice_arr_array a1, ice_arr_array a2) {
    int len = 0;
    int count = 0;
    
    for (int i = 0; i < a1.len; i++) {
        if (ice_arr_matches(a2, a1.arr[i]) >= 1 && ice_arr_matches(a1, a1.arr[i]) >= 1) {
            len++;
        }
    }
    
    ice_arr_array res = ice_arr_new(len);
    
    for (int i = 0; i < a1.len; i++) {
        if (!(ice_arr_includes(res, a1.arr[i]) == ICE_ARR_TRUE)) {
            res.arr[count] = a1.arr[i];
            count++;
        }
    }
    
    for (int i = 0; i < a2.len; i++) {
        if (!(ice_arr_includes(res, a2.arr[i]) == ICE_ARR_TRUE)) {
            res.arr[count] = a2.arr[i];
            count++;
        }
    }
    
    return res;
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_rotate(ice_arr_array* arr, int times) {
    for (int i = 0; i < times; i++) {
        int i, temp;
        temp = arr->arr[0];
        
        for (i = 0; i < arr->len - 1; i++)  {
            arr->arr[i] = arr->arr[i + 1];
        }
        arr->arr[i] = temp;
    }
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_move(ice_arr_array* a1, int from_index, int elems_count, int to_index, ice_arr_array* a2) {
    if (a1->len + elems_count - 1 >= a1->real_len) {
        ICE_ARR_REALLOC(a1->arr, (a1->real_len + ((a1->len + elems_count - 1) - a1->real_len / 2)));
    }
    
    if (a2->len + elems_count - 1 >= a2->real_len) {
        ICE_ARR_REALLOC(a2->arr, (a2->real_len + ((a2->len + elems_count - 1) - a2->real_len / 2)));
    }
    
    for (int i = 0; i < (elems_count - 1); i++) {
        a2->arr[to_index + i] = a1->arr[from_index + i];
    }
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_sort(ice_arr_array* arr) {
    int i, j, swapped;
    double temp;
    
    for (i = 0; i < arr->len; ++i) {
        for (j = i + 1; j < arr->len; ++j) {
            if (arr->arr[i] < arr->arr[j]) {
                temp = arr->arr[i];
                arr->arr[i] = arr->arr[j];
                arr->arr[j] = temp;
            }
        }
    }
}

ICE_ARR_API void ICE_ARR_CALLCONV ice_arr_sort_ex(ice_arr_array* arr, ice_arr_res_func f) {
    int i, j, swapped;
    double temp;
    
    for (i = 0; i < arr->len; ++i) {
        for (j = i + 1; j < arr->len; ++j) {
            if ((int) f(arr->arr[i], arr->arr[j]) == 1) {
                temp = arr->arr[i];
                arr->arr[i] = arr->arr[j];
                arr->arr[j] = temp;
            }
        }
    }
}

#endif  // ICE_ARR_IMPL
#endif  // ICE_ARR_H
