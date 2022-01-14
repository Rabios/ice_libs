/*
ice_arr.h, Single-Header Cross-Platform C library for working with Arrays!


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
#define ICE_ARR_H

/* Disable security warnings for MSVC compiler, We don't want to force using C11! */
#ifdef _MSC_VER
#  ifndef _CRT_SECURE_NO_DEPRECATE
#    define _CRT_SECURE_NO_DEPRECATE
#  endif
#  ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS
#  endif
#  pragma warning(disable:4996)
#endif

/* Define C interface for Windows libraries! ;) */
#ifndef CINTERFACE
#  define CINTERFACE
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

/* NULL Implementation ;) */
#ifndef ICE_ARR_NULL
#  if defined(__cplusplus)
#    define ICE_ARR_NULL 0
#  else
#    define ICE_ARR_NULL (void*)(0)
#  endif
#endif

#if defined(ICE_ARR_IMPL)

/* Creates a new array and creates length variable that can be used */
#define ice_arr_new(type, len, res)                     \
    res = (type*) ICE_ARR_MALLOC(len * sizeof(type));   \
/*    unsigned long res##_length = len;                   \ */

/* Frees/Deallocates the array */
#define ice_arr_delete(arr)                             \
    ICE_ARR_FREE(arr);                                  \
    arr = ICE_ARR_NULL;                                 \

/* #define ice_arr_len(arr) arr##_len */

#define ice_arr_pop(arr, type, len, res) {      \
    int i;                                      \
    int count = 0;                              \
    ice_arr_new(type, len - 1, res)             \
                                                \
    for (i = 0; i < len - 1; i++) {             \
        res[count] = arr[i];                    \
        count++;                                \
    }                                           \
}                                               \

#define ice_arr_clone(arr, type, len, res) {    \
    int i;                                      \
    int count = 0;                              \
    ice_arr_new(type, len, res)                 \
                                                \
    for (i = 0; i < len; i++) {                 \
        res[count] = arr[i];                    \
        count++;                                \
    }                                           \
}                                               \

#define ice_arr_shift(arr, type, len, value, res)
#define ice_arr_unshift(arr, type, len, value, res)
#define ice_arr_push(arr, type, len, value, res)

#define ice_arr_rev(arr, type, len, res) {  \
    int i;                                  \
    int count = 0;                          \
    ice_arr_new(type, len, res)             \
                                            \
    for (i = len - 1; i >= 0; i--) {        \
        res[count] = arr[i];                \
        count++;                            \
    }                                       \
}                                           \

#define ice_arr_fill(arr, len, value) { \
    int i;                              \
                                        \
    for (i = 0; i < len; i++) {         \
        arr[i] = value;                 \
    }                                   \
}                                       \

#define ice_arr_clear(arr, len) {       \
    int i;                              \
                                        \
    for (i = 0; i < len; i++) {         \
        arr[i] = ICE_ARR_NULL;          \
    }                                   \
}                                       \

#define ice_arr_sum(arr, len, res) {    \
    int i;                              \
    double sum = 0;                     \
                                        \
    for (i = 0; i < len; i++) {         \
        sum += arr[i];                  \
    }                                   \
                                        \
    res = sum;                          \
}                                       \

#define ice_arr_first(arr, type, len, count, res) { \
    int i;                                          \
    ice_arr_new(type, count, res)                   \
                                                    \
    for (i = 0; i < count; i++) {                   \
        res[i] = arr[i];                            \
    }                                               \
}                                                   \

#define ice_arr_last(arr, type, len, count, res) {  \
    int i;                                          \
    ice_arr_new(type, count, res)                   \
                                                    \
    for (i = 0; i < count; i++) {                   \
        res[i] = arr[(len - 1) - i];                \
    }                                               \
}                                                   \

#define ice_arr_concat(type, arr1, len1, arr2, len2, res) { \
    int i;                                                  \
    int count = 0;                                          \
    ice_arr_new(type, len1 + len2, res)                     \
                                                            \
    for (i = 0; i < len1; i++) {                            \
        res[count] = arr1[i];                               \
        count++;                                            \
    }                                                       \
                                                            \
    for (i = 0; i < len2; i++) {                            \
        res[count] = arr2[i];                               \
        count++;                                            \
    }                                                       \
}                                                           \

#define ice_arr_match(arr1, len1, arr2, len2, res) {    \
    int i;                                              \
    int matches = 0;                                    \
                                                        \
    if (len1 != len2) res = -1;                         \
                                                        \
    for (i = 0; i < len1; i++) {                        \
        if (arr1[i] == arr2[i]) {                       \
            matches++;                                  \
        }                                               \
    }                                                   \
                                                        \
    res = (matches == len1) ? 0 : -1;                   \
}                                                       \

#define ice_arr_matches(arr, len, value, res) {         \
    int i;                                              \
                                                        \
    for (i = 0; i < len; i++) {                         \
        if (arr[i] == value) {                          \
            res++;                                      \
        }                                               \
    }                                                   \
}                                                       \

#define ice_arr_includes(arr, len, value, res) {        \
    int i;                                              \
                                                        \
    for (i = 0; i < len; i++) {                         \
        if (arr[i] == value) {                          \
            res = 0;                                    \
            break;                                      \
        }                                               \
    }                                                   \
                                                        \
    if (i == len && res != 0) res = -1;                 \
}                                                       \

#define ice_arr_sub(arr, type, idx1, idx2, res) {               \
    int i;                                                      \
    int count = 0;                                              \
    int backward = (idx1 > idx2) ? 0 : -1;                      \
    int len = (backward == 0) ? (idx1 - idx2) ? (idx2 - idx1);  \
    ice_arr_new(type, len, res)                                 \
                                                                \
    if (backward == 0) {                                        \
        for (i = idx1; i >= idx2; i--) {                        \
            res[count] = arr[i];                                \
            count++;                                            \
        }                                                       \
    } else if (backward == -1) {                                \
        for (i = idx1; i <= idx2; i++) {                        \
            res[count] = arr[i];                                \
            count++;                                            \
        }                                                       \
    }                                                           \
}                                                               \

#define ice_arr_rem
#define ice_arr_without
#define ice_arr_rest
#define ice_arr_uniq

#define ice_arr_index(arr, len, value, res) {   \
    int i;                                      \
                                                \
    for (i = 0; i < len; i++) {                 \
        if (arr[i] == value) {                  \
            res = i;                            \
            break;                              \
        }                                       \
    }                                           \
                                                \
    if (res <= 0) res = -1;                     \
}                                               \

#define ice_arr_rindex(arr, len, value, res) {  \
    int i;                                      \
                                                \
    for (i = 0; i < len; i++) {                 \
        if (arr[i] == value) {                  \
            res = i;                            \
        }                                       \
    }                                           \
                                                \
    if (res <= 0) res = -1;                     \
}                                               \

#define ice_arr_diff

#define ice_arr_range(i1, i2, code) {                               \
    int i;                                                          \
    int backside = (i1 > i2) ? -1 : 0;                              \
    int from = ((backside == -1) ? i1 : i2);                        \
    int to = ((backside == 0) ? i2 : i1);                           \
                                                                    \
    for (i = from; i <= to; ((backside == -1) ? i++ : i--)) code    \
}                                                                   \

#define ice_arr_min(arr, len, res) {            \
    int i;                                      \
                                                \
    for (i = 0; i < len; i++) {                 \
        if (arr[i] < res) res = arr[i];         \
    }                                           \
}                                               \

#define ice_arr_max(arr, len, res) {            \
    int i;                                      \
                                                \
    for (i = 0; i < len; i++) {                 \
        if (arr[i] > res) res = arr[i];         \
    }                                           \
}                                               \

#define ice_arr_compact
#define ice_arr_tail
#define ice_arr_intersect

#define ice_arr_foreach(arr, len, code) {   \
    int i;                                  \
    for (i = 0; i < len; i++) f             \
}

#define ice_arr_union
#define ice_arr_lrot
#define ice_arr_rrot
#define ice_arr_move
#define ice_arr_sort
#define ice_arr_xsort

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
