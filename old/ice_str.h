// Written by Rabia Alhaffar in 19/April/2021
// ice_str.h
// Single-Header Cross-Platform C library for working with strings!
// Updated: 25/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_str.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_str is cross-platform single-header C library for working with strings!

[2] USAGE:
Define ICE_STR_IMPL then include ice_str.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_str
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_str by possibly one of following things:
//
// 1. Test ice_str on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_str LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_str is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_STR_H
#define ICE_STR_H

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
#  if defined(ICE_STR_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_STR_CALLCONV_FASTCALL)
#    define ICE_STR_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_STR_CALLCONV_STDCALL)
#    define ICE_STR_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_STR_CALLCONV_CDECL)
#    define ICE_STR_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_STR_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_STR_CALLCONV_VECTORCALL)
#    define ICE_STR_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_STR_CALLCONV_FASTCALL)
#    define ICE_STR_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_STR_CALLCONV_STDCALL)
#    define ICE_STR_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_STR_CALLCONV_CDECL)
#    define ICE_STR_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_STR_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_STR_CALLCONV_VECTORCALL)
#    define ICE_STR_CALLCONV __vectorcall
#  elif defined(ICE_STR_CALLCONV_FASTCALL)
#    define ICE_STR_CALLCONV __fastcall
#  elif defined(ICE_STR_CALLCONV_STDCALL)
#    define ICE_STR_CALLCONV __stdcall
#  elif defined(ICE_STR_CALLCONV_CDECL)
#    define ICE_STR_CALLCONV __cdecl
#  else
#    define ICE_STR_CALLCONV
#  endif
#else
#  define ICE_STR_CALLCONV
#endif

// Platform detection
#if !defined(ICE_STR_MICROSOFT)
#  if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#     define ICE_STR_MICROSOFT
#  endif
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_STR_EXTERN) && defined(ICE_STR_STATIC))
#  define ICE_STR_EXTERN
#endif

#if defined(ICE_STR_EXTERN)
#  define ICE_STR_APIDEF extern
#elif defined(ICE_STR_STATIC)
#  define ICE_STR_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_STR_INLINE to enable inline functionality.
#if defined(ICE_STR_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_STR_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_STR_INLINEDEF inline
#  endif
#else
#  define ICE_STR_INLINEDEF
#endif

// Allow to build DLL via ICE_STR_DLLEXPORT or ICE_STR_DLLIMPORT if desired!
// Else, Just define API as extern C code!
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

// Custom memory allocators
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

///////////////////////////////////////////////////////////////////////////////////////////
// ice_str DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_STR_TRUE    = 0,
    ICE_STR_FALSE   = -1,
} ice_str_bool;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_str FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////

// NOTE 1: All strings returned are NULL-terminated!
// NOTE 2: Returned string allocated on heap, Consider free it with ice_str_free and then change value to NULL once you don't want to use the string.

ICE_STR_API  int           ICE_STR_CALLCONV  ice_str_len(char* str);                                // Returns length of string.
ICE_STR_API  int           ICE_STR_CALLCONV  ice_str_arr_len(char** arr);                           // Returns length of array of strings.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_sub(char* str, int from, int to);              // Returns substring from (from -> to) index.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_strdup(char* str);                             // Returns NULL-terminates string?
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_concat(char* s1, char* s2);                    // Joins 2 strings in one and returns result.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_rep(char* str, int count);                     // Returns string repeated multiple times.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_char(char* str, int index);                    // Returns char at index as string.
ICE_STR_API  ice_str_bool  ICE_STR_CALLCONV  ice_str_match(char* s1, char* s2);                     // Returns ICE_STR_TRUE if 2 strings are same or ICE_STR_FALSE if not.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_upper(char* str);                              // Returns uppercased string of str.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_lower(char* str);                              // Returns lowercased string of str.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_capitalize(char* str);                         // Returns capitalized string of str.
ICE_STR_API  char**        ICE_STR_CALLCONV  ice_str_split(char* str, char delim);                  // Split string into array by delimiter/separator (char) and return result.
ICE_STR_API  char**        ICE_STR_CALLCONV  ice_str_splitlines(char* str);                         // Split string into array by newline char and return the array.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_join(char** strs);                             // Joins strings from array into one string and returns it.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_join_with_delim(char** strs, char delim);      // Joins strings from array into one string and returns it.
ICE_STR_API  ice_str_bool  ICE_STR_CALLCONV  ice_str_begin(char* s1, char* s2);                     // Returns ICE_STR_TRUE if string s1 starts with string s2 or ICE_STR_FALSE if not.
ICE_STR_API  ice_str_bool  ICE_STR_CALLCONV  ice_str_end(char* s1, char* s2);                       // Returns ICE_STR_TRUE if string s1 ends with string s2 or ICE_STR_FALSE if not.
ICE_STR_API  ice_str_bool  ICE_STR_CALLCONV  ice_str_end_char(char* str, char ch);                  // Returns ICE_STR_TRUE if string ends with character or ICE_STR_FALSE if not.
ICE_STR_API  char*         ICE_STR_CALLCONV  ice_str_rev(char* str);                                // Returns reversed string of str.
ICE_STR_API  void          ICE_STR_CALLCONV  ice_str_free(char* str);                               // Frees the string.
ICE_STR_API  void          ICE_STR_CALLCONV  ice_str_arr_free(char** arr);                          // Frees array of strings.

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_str IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_STR_IMPL)

// Returns length of string.
ICE_STR_API int ICE_STR_CALLCONV ice_str_len(char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

// Returns length of array of strings.
ICE_STR_API int ICE_STR_CALLCONV ice_str_arr_len(char** arr) {
    int arrlen = 0;
    while (arr[arrlen] != NULL) arrlen++;
    return arrlen;
}

// Returns substring from (from -> to) index.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_sub(char* str, int from, int to) {
    char* res = (char*) ICE_STR_MALLOC((to - from) + 1 * sizeof(char));
    int count = 0;

    for (int i = from; i <= to; i++) {
        res[count] = str[i];
        count++;
    }

    res[count] = '\0';
    return res;
}

// Returns NULL-terminates string?
ICE_STR_API char* ICE_STR_CALLCONV ice_str_strdup(char* str) {
    int len = ice_str_len(str);
    char* res = (char*) ICE_STR_MALLOC(len + 1 * sizeof(char));

    for (int i = 0; i < len; i++) {
        res[i] = str[i];
    }

    res[len] = '\0';
    return res;
}

// Joins 2 strings in one and returns result.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_concat(char* s1, char* s2) {
    int len_str1 = ice_str_len(s1);
    int len_str2 = ice_str_len(s2);

    char* res = (char*) ICE_STR_MALLOC((len_str1 + len_str2) * sizeof(char));
    for (int i = 0; i < len_str1; i++) {
        res[i] = s1[i];
    }

    for (int i = 0; i < len_str2; i++) {
        res[len_str1 + i] = s2[i];
    }

    res[len_str1 + len_str2] = '\0';
    return res;
}

// Returns string repeated multiple times.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_rep(char* str, int count) {
    int lenstr = ice_str_len(str);
    char* res = (char*) ICE_STR_MALLOC((lenstr * count) + 1 * sizeof(char));
    int times = 0;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < lenstr; j++) {
            res[(lenstr * i) + j] = str[j];
        }

        times++;
    }

    res[lenstr * count] = '\0';
    return res;
}

// Returns char at index as string.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_char(char* str, int index) {
    char* c = (char*) ICE_STR_MALLOC(2 * sizeof(char));
    c[0] = str[index];
    c[1] = '\0';
    return c;
}

// Returns ICE_STR_TRUE if 2 strings are same or ICE_STR_FALSE if not.
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_match(char* s1, char* s2) {
    int len_str1 = ice_str_len(s1);
    int len_str2 = ice_str_len(s2);
    int matches = 0;

    if (len_str1 != len_str2) {
        return ICE_STR_FALSE;
    }

    for (int i = 0; i < len_str1; i++) {
        if (s1[i] == s2[i]) {
            matches++;
        }
    }

    return (matches == len_str1) ? ICE_STR_TRUE : ICE_STR_FALSE;
}

// Returns uppercased string of str.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_upper(char* str) {
    int lenstr = ice_str_len(str);
    char* res = (char*) ICE_STR_MALLOC(lenstr + 1 * sizeof(char));

    for (int i = 0; i < lenstr; i++) {
        if (str[i] == 'a') res[i] = 'A';
        else if (str[i] == 'b') res[i] = 'B';
        else if (str[i] == 'c') res[i] = 'C';
        else if (str[i] == 'd') res[i] = 'D';
        else if (str[i] == 'e') res[i] = 'E';
        else if (str[i] == 'f') res[i] = 'F';
        else if (str[i] == 'g') res[i] = 'G';
        else if (str[i] == 'h') res[i] = 'H';
        else if (str[i] == 'i') res[i] = 'I';
        else if (str[i] == 'j') res[i] = 'J';
        else if (str[i] == 'k') res[i] = 'K';
        else if (str[i] == 'l') res[i] = 'L';
        else if (str[i] == 'm') res[i] = 'M';
        else if (str[i] == 'n') res[i] = 'N';
        else if (str[i] == 'o') res[i] = 'O';
        else if (str[i] == 'p') res[i] = 'P';
        else if (str[i] == 'q') res[i] = 'Q';
        else if (str[i] == 'r') res[i] = 'R';
        else if (str[i] == 's') res[i] = 'S';
        else if (str[i] == 't') res[i] = 'T';
        else if (str[i] == 'u') res[i] = 'U';
        else if (str[i] == 'v') res[i] = 'V';
        else if (str[i] == 'w') res[i] = 'W';
        else if (str[i] == 'x') res[i] = 'X';
        else if (str[i] == 'y') res[i] = 'Y';
        else if (str[i] == 'z') res[i] = 'Z';
        else res[i] = str[i];
    }

    res[lenstr] = '\0';
    return res;
}

// Returns lowercased string of str.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_lower(char* str) {
    int lenstr = ice_str_len(str);
    char* res = (char*) ICE_STR_MALLOC(lenstr + 1 * sizeof(char));

    for (int i = 0; i < lenstr; i++) {
        if (str[i] == 'A') res[i] = 'a';
        else if (str[i] == 'B') res[i] = 'b';
        else if (str[i] == 'C') res[i] = 'c';
        else if (str[i] == 'D') res[i] = 'd';
        else if (str[i] == 'E') res[i] = 'e';
        else if (str[i] == 'F') res[i] = 'f';
        else if (str[i] == 'G') res[i] = 'g';
        else if (str[i] == 'H') res[i] = 'h';
        else if (str[i] == 'I') res[i] = 'i';
        else if (str[i] == 'J') res[i] = 'j';
        else if (str[i] == 'K') res[i] = 'k';
        else if (str[i] == 'L') res[i] = 'l';
        else if (str[i] == 'M') res[i] = 'm';
        else if (str[i] == 'N') res[i] = 'n';
        else if (str[i] == 'O') res[i] = 'o';
        else if (str[i] == 'P') res[i] = 'p';
        else if (str[i] == 'Q') res[i] = 'q';
        else if (str[i] == 'R') res[i] = 'r';
        else if (str[i] == 'S') res[i] = 's';
        else if (str[i] == 'T') res[i] = 't';
        else if (str[i] == 'U') res[i] = 'u';
        else if (str[i] == 'V') res[i] = 'v';
        else if (str[i] == 'W') res[i] = 'w';
        else if (str[i] == 'X') res[i] = 'x';
        else if (str[i] == 'Y') res[i] = 'y';
        else if (str[i] == 'Z') res[i] = 'z';
        else res[i] = str[i];
    }

    res[lenstr] = '\0';
    return res;
}

// Returns capitalized string of str.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_capitalize(char* str) {
    int lenstr = ice_str_len(str);
    char* res = (char*) ICE_STR_MALLOC(lenstr + 1 * sizeof(char));

    if (str[0] == 'a') res[0] = 'A';
    else if (str[0] == 'b') res[0] = 'B';
    else if (str[0] == 'c') res[0] = 'C';
    else if (str[0] == 'd') res[0] = 'D';
    else if (str[0] == 'e') res[0] = 'E';
    else if (str[0] == 'f') res[0] = 'F';
    else if (str[0] == 'g') res[0] = 'G';
    else if (str[0] == 'h') res[0] = 'H';
    else if (str[0] == 'i') res[0] = 'I';
    else if (str[0] == 'j') res[0] = 'J';
    else if (str[0] == 'k') res[0] = 'K';
    else if (str[0] == 'l') res[0] = 'L';
    else if (str[0] == 'm') res[0] = 'M';
    else if (str[0] == 'n') res[0] = 'N';
    else if (str[0] == 'o') res[0] = 'O';
    else if (str[0] == 'p') res[0] = 'R';
    else if (str[0] == 'q') res[0] = 'Q';
    else if (str[0] == 'r') res[0] = 'R';
    else if (str[0] == 's') res[0] = 'S';
    else if (str[0] == 't') res[0] = 'T';
    else if (str[0] == 'u') res[0] = 'U';
    else if (str[0] == 'v') res[0] = 'V';
    else if (str[0] == 'w') res[0] = 'W';
    else if (str[0] == 'x') res[0] = 'X';
    else if (str[0] == 'y') res[0] = 'Y';
    else if (str[0] == 'z') res[0] = 'Z';
    else res[0] = str[0];

    for (int i = 1; i < lenstr; i++) {
        res[i] = str[i];
    }

    res[lenstr] = '\0';
    return res;
}

// Split string into array by delimiter/separator (char) and return result.
ICE_STR_API char** ICE_STR_CALLCONV ice_str_split(char* str, char delim) {
    int arrlen = 0;
    int count = 0;
    int elems = 0;
    int lenstr = ice_str_len(str);

    for (int i = 0; i < lenstr; i++) {
        if (str[i] == delim) {
            arrlen++;
        }
    }

    ice_str_bool last_char_not_delim = (ice_str_end_char(str, delim) == ICE_STR_FALSE) ? ICE_STR_TRUE : ICE_STR_FALSE;

    if (last_char_not_delim == ICE_STR_TRUE) {
        arrlen++;
    }

    int* arr_elem_lengths = (int*) ICE_STR_MALLOC(arrlen * sizeof(int));

    for (int i = 0; i < lenstr; i++) {
        count++;

        if (str[i] == delim) {
            arr_elem_lengths[elems] = count;
            elems++;
        }
    }

    if (last_char_not_delim == ICE_STR_TRUE) {
        arr_elem_lengths[arrlen - 1] = lenstr + 1;
        elems++;
    }

    int sum = 0;

    for (int i = 0; i < elems; i++) {
        sum += arr_elem_lengths[i];
    }

    char** res = (char**) ICE_STR_MALLOC(sum * sizeof(char));

    for (int i = 0; i < elems; i++) {
        if (i == 0) {
            res[i] = ice_str_sub(str, 0, arr_elem_lengths[i] - 2);
        } else {
            res[i] = ice_str_sub(str, arr_elem_lengths[i - 1], arr_elem_lengths[i] - 2);
        }
    }

    return res;
}

// Split string into array by newline char and return the array.
ICE_STR_API char** ICE_STR_CALLCONV ice_str_splitlines(char* str) {
    return ice_str_split(str, '\n');
}

// Joins strings from array into one string and returns it.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_join(char** strs) {
    int arrlen = 0;
    int strs_size = 0;

    while (strs[arrlen] != NULL) arrlen++;

    for (int i = 0; i < arrlen; i++) {
        strs_size += ice_str_len(strs[i]);
    }

    char* res = (char*) ICE_STR_MALLOC(strs_size + 1 * sizeof(char));
    int res_s = 0;

    for (int i = 0; i < arrlen; i++) {
        int lenstr = ice_str_len(strs[i]);

        for (int j = 0; j < lenstr; j++) {
            res[j + res_s] = strs[i][j];
        }

        res_s += lenstr;
    }

    res[res_s] = '\0';
    return res;
}

// Joins strings from array into one string and returns it.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_join_with_delim(char** strs, char delim) {
    int count = 0;
    int res_s = 0;
    int arrlen = 0;
    int strs_size = 0;

    while (strs[arrlen] != NULL) arrlen++;

    for (int i = 0; i < arrlen; i++) {
        strs_size += ice_str_len(strs[i]);
    }

    char* res = (char*) ICE_STR_MALLOC(1 + strs_size + arrlen * sizeof(char));

    for (int i = 0; i < arrlen; i++) {
        int lstr = ice_str_len(strs[i]);

        for (int j = 0; j < lstr; j++) {
            res[j + res_s + ((i > 0) ? 1 : 0)] = strs[i][j];
        }

        if (i != 0) {
            res[res_s] = delim;
            res_s += lstr + count++;
        } else {
            res_s += lstr + count++;
        }
    }

    res[res_s - 1] = '\0';
    return res;
}

// Returns ICE_STR_TRUE if string s1 starts with string s2 or ICE_STR_FALSE if not.
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_begin(char* s1, char* s2) {
    int lenstr = ice_str_len(s2);
    char* sub = ice_str_sub(s1, 0, lenstr - 1);
    
    return ice_str_match(sub, s2);
}

// Returns ICE_STR_TRUE if string s1 ends with string s2 or ICE_STR_FALSE if not.
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_end(char* s1, char* s2) {
    int lenstr1 = ice_str_len(s1);
    int lenstr2 = ice_str_len(s2);

    char* sub = ice_str_sub(s1, lenstr1 - lenstr2, lenstr1 - 1);
    return ice_str_match(sub, s2);
}

// Returns ICE_STR_TRUE if string ends with character or ICE_STR_FALSE if not.
ICE_STR_API ice_str_bool ICE_STR_CALLCONV ice_str_end_char(char* str, char ch) {
    int lenstr = ice_str_len(str);
    return (str[lenstr - 1] == ch) ? ICE_STR_TRUE : ICE_STR_FALSE;
}

// Returns reversed string of str.
ICE_STR_API char* ICE_STR_CALLCONV ice_str_rev(char* str) {
    int lenstr = ice_str_len(str);
    char* res = (char*) ICE_STR_MALLOC(lenstr * sizeof(char));

    for (int i = 0; i < lenstr; i++) {
        res[(lenstr - 1) - i] = str[i];
    }

    res[lenstr] = '\0';
    return res;
}

// Frees the string.
ICE_STR_API void ICE_STR_CALLCONV ice_str_free(char* str) {
    ICE_STR_FREE(str);
    str = NULL;
}

// Frees array of strings.
ICE_STR_API void ICE_STR_CALLCONV ice_str_arr_free(char** arr) {
    for (int i = 0; i < ice_str_arr_len(arr); i++) {
        ICE_STR_FREE(arr[i]);
        arr[i] = NULL;
    }
    
    ICE_STR_FREE(arr);
    arr = NULL;
}

#endif  // ICE_STR_IMPL
#endif  // ICE_STR_H
