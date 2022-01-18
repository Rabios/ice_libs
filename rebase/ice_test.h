/*
ice_test.h, Single-Header Cross-Platform tiny C library for unit testing!


================================== Full Overview ==================================

ice_test.h is Single-Header tiny C library for unit testing!

To use it #define ICE_TEST_IMPL then #include "ice_test.h" in your C/C++ code!


================================== Usage Example ==================================

// Define the implementation of the library and include it
#define ICE_TEST_IMPL 1
#include "ice_test.h"

#include <stdio.h>

// Helper
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

// Create a Test
ICE_TEST_CREATE_EX(test1) {
    ICE_TEST_ASSERT_TRUE(sizeof(void*) == 8);
}

int main(int argc, char **argv) {
    trace("main", "Testing if program is 64-bit...");
    test1(argc, argv); // test!
    trace("main", "TEST SUCCESS!");

    return 0;
}


================================== Linking Flags ==================================

1. Linux, BSD   =>  -lc (-lc Most times automatically linked...)

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragma preprocessor


=================================== Library API ===================================

// Creates test with a name, This test can be called as name();
#define ICE_TEST_CREATE(name)

// Creates test with a name but this one extended to allow argument passing, This test can be called as name(int argc, char** argv);
#define ICE_TEST_CREATE_EX(name)

// Tests equality between 2 variables, For strings use ICE_TEST_ASSERT_STR_EQU instead!
#define ICE_TEST_ASSERT_EQU(a, b)

// Tests equality between 2 strings
#define ICE_TEST_ASSERT_STR_EQU(a, b)

// Tests if variable value is true/1
#define ICE_TEST_ASSERT_TRUE(a)

// Tests if variable value is false/0
#define ICE_TEST_ASSERT_FALSE(a)

// Tests if variable is NULL
#define ICE_TEST_ASSERT_NULL(a)

// Tests if variable isn't NULL
#define ICE_TEST_ASSERT_NOT_NULL(a)

// Tests if variable is integer number
#define ICE_TEST_ASSERT_INT(a)

// Tests if variable is not integer number
#define ICE_TEST_ASSERT_NOT_INT(a)


================================= Support ice_libs ================================

ice_test.h is one of libraries that ice_libs project provide...

You can support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star (and/or fork) the repo on GitHub: https://github.com/Rabios/ice_libs
7. Share ice_libs Everywhere!
8. Join the Discord Server: https://discord.gg/KfkwXjCW


*/

#if !defined(ICE_TEST_H)
#define ICE_TEST_H 1

#if defined(ICE_TEST_IMPL)

#include <assert.h>

#if defined(_MSC_VER)
#  pragma comment(lib, "msvcrt.lib")
#endif

/* Creates test with a name, This test can be called as name(); */
#if defined(__cplusplus)
#  define ICE_TEST_CREATE(name) extern "C" void name(void)
#else
#  define ICE_TEST_CREATE(name) void name(void)
#endif

/*
Creates test with a name but this one extended to allow argument passing...

This test can be called as name(argc, argv);
*/
#if defined(__cplusplus)
#  define ICE_TEST_CREATE_EX(name) extern "C" void name(int argc, char** argv)
#else
#  define ICE_TEST_CREATE_EX(name) void name(int argc, char** argv)
#endif

/*
Tests equality between 2 variables, For strings use ICE_TEST_ASSERT_STR_EQU instead!
*/
#define ICE_TEST_ASSERT_EQU(a, b) assert(a == b);

/* Tests equality between 2 strings */
#define ICE_TEST_ASSERT_STR_EQU(a, b) {         \
    unsigned long lenstr1, lenstr2, matches, i; \
    lenstr1 = lenstr2 = matches = 0;            \
                                                \
    while (a[lenstr1] != 0) lenstr1++;          \
    while (b[lenstr2] != 0) lenstr2++;          \
                                                \
    if (lenstr1 == lenstr2) {                   \
        for (i = 0; i < lenstr1; i++) {         \
            if (a[i] == b[i]) matches++;        \
        }                                       \
    }                                           \
                                                \
    assert(matches == lenstr1);                 \
}

/* Tests if variable value is true/1 */
#define ICE_TEST_ASSERT_TRUE(a) assert((int)(a) == 1);

/* Tests if variable value is false/0 */
#define ICE_TEST_ASSERT_FALSE(a) assert((int)(a) == 0);

/* Tests if variable is NULL */
#if defined(__OBJC__)
#  define ICE_TEST_ASSERT_NULL(a) assert(((a == 0) && !(a)) || ([a isEqual:[NSNull null]] == YES));
#else
#  define ICE_TEST_ASSERT_NULL(a) assert((a == 0) && !(a));
#endif

/* Tests if variable isn't NULL */
#if defined(__OBJC__)
#  define ICE_TEST_ASSERT_NOT_NULL(a) assert(((a != 0) && (a)) || ([a isEqual:[NSNull null]] == NO));
#else
#  define ICE_TEST_ASSERT_NOT_NULL(a) assert((a != 0) && (a));
#endif

/* Tests if variable is integer number */
#define ICE_TEST_ASSERT_INT(a) assert((int)(a) == a);

/* Tests if variable is not integer number */
#define ICE_TEST_ASSERT_NOT_INT(a) assert((int)(a) != a);

#endif  /* ICE_TEST_IMPL */
#endif  /* ICE_TEST_H */

/*
ice_test.h is dual-licensed, Choose the one you prefer!

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
