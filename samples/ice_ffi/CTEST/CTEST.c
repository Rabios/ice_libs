// NOTE: Compile this as shared library by the way you do (with the shared lib extension)
// Microsoft Platforms:  CTEST.dll
// Apple Platforms:      CTEST.dylib
// Elsewhere:            CTEST.so
#if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#  define PLATFORM_MICROSOFT
#endif

#if defined(PLATFORM_MICROSOFT)
#  define CAPI extern __declspec(dllexport)
#else
#  define CAPI extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

CAPI int test(void);

CAPI int test(void) {
    return 42;
}

#ifdef __cplusplus
}
#endif
