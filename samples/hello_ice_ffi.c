/* Define the implementation of the library and include it */
#define ICE_FFI_IMPL
#include "ice_ffi.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(void) {
    /* To store result of unloading the shared library/object */
    ice_ffi_bool unload_res;

    /* Handle for shared library/object */
    ice_ffi_handle lib;

    /* function from shared library/object */
    unsigned (*F42)(void);
    
    /* Define path of the shared library/object depending on platform */
#if defined(ICE_FFI_MICROSOFT)
    const char *path = "lib42.dll";
#else
    const char *path = "./lib42.so";
#endif

    /* Load the shared library/object */
    lib = ice_ffi_load(path);
    
    /* If the function failed to load the shared library/object, Trace error then terminate the program */
    if (lib == 0) {
        trace("ice_ffi_load", "ERROR: failed to load shared library/object!");
        return -1;
    }
    
    /* If the shared library/object loaded successfully, Get the function F42 symbol to call it! */
    *(unsigned**)(&F42) = ice_ffi_get(lib, "F42");
    
    /* If the function failed to get symbol from shared library/object, Trace error then terminate the program */
    if (F42 == 0) {
        trace("ice_ffi_get", "ERROR: failed to get symbol from shared library/object!");
        return -1;
    }
    
    /* Call the function and print the result! */
    printf("F42 call result: %u\n", F42());
    
    /* When done, Unload symbols and the shared library/object */
    F42 = 0;
    unload_res = ice_ffi_unload(lib);
    
    /* If the function failed to unload shared library/object, Trace error then terminate the program */
    if (unload_res == ICE_FFI_FALSE) {
        trace("ice_ffi_unload", "ERROR: failed to unload shared library/object!");
        return -1;
    }
    
    return 0;
}
