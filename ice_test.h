// Written by Rabia Alhaffar in 20/April/2021
// ice_test.h
// Single-Header Cross-Platform tiny C library for unit testing!
// Updated: 21/June/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_test.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_test is cross-platform single-header tiny C library for unit testing!

[2] USAGE:
Define ICE_TEST_IMPL then include ice_test.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_test
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_test by possibly one of following things:
//
// 1. Test ice_test on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_test LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_test is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_TEST_H
#define ICE_TEST_H

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

///////////////////////////////////////////////////////////////////////////////////////////
// ice_test IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_TEST_IMPL)
#include <assert.h>

#if defined(__cplusplus)
#define ICE_TEST_CREATE(name)\
    extern "C" void name(void)
#else
#define ICE_TEST_CREATE(name)\
    void name(void)
#endif

#define ICE_TEST_ASSERT_EQU(a, b) {\
    assert(a == b);\
}

#define ICE_TEST_ASSERT_STR_EQU(a, b) ({\
    int lenstr1 = 0;\
    int lenstr2 = 0;\
    int matches = 0;\
    \
    while (a[lenstr1] != '\0') lenstr1++;\
    while (b[lenstr2] != '\0') lenstr2++;\
    \
    if (lenstr1 == lenstr2) {\
        for (int i = 0; i < lenstr1; i++) {\
            if (a[i] == b[i]) matches++;\
        }\
    }\
    assert(matches == lenstr1);\
})

#define ICE_TEST_ASSERT_TRUE(a) {\
    assert(a);\
}

#define ICE_TEST_ASSERT_FALSE(a) {\
    assert(!a);\
}

#define ICE_TEST_ASSERT_NULL(a) {\
    assert(a == NULL);\
}

#define ICE_TEST_ASSERT_NOT_NULL(a) {\
    assert(a != NULL);\
}

#define ICE_TEST_ASSERT_INT(a) {\
    int x = (int) a;\
    assert(x == a);\
}

#define ICE_TEST_ASSERT_NOT_INT(a) {\
    int x = (int) a;\
    assert(x != a);\
}

#endif  // ICE_TEST_IMPL
#endif  // ICE_TEST_H
