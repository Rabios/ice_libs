/* Define the implementation of the library and include it */
#define ICE_FFI_IMPL
#include "ice_ffi.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(int argc, char** argv) {
    ice_ffi_bool unload_res;
    ice_ffi_handle lib;
    unsigned (*F42)(void); /* function from shared library/object */
    
    /* Define path of shared library/object depending on platform */
#if defined(ICE_FFI_MICROSOFT)
    const char *path = "lib42.dll";
#else
    const char *path = "./lib42.so";
#endif

    /* Load the shared library/object */
    lib = ice_ffi_load(path);
    
    /* If function failed to load the shared library/object, Trace error then terminate the program */
    if (lib == NULL) {
        trace("ice_ffi_load", "ERROR: failed to load shared library/object!");
        return -1;
    }
    
    /* If shared library/object loaded successfully, Get the function F42 symbol to call it! */
    *(unsigned**)(&F42) = ice_ffi_get(lib, "F42");
    
    /* If function failed to get symbol from shared library/object, Trace error then terminate the program */
    if (F42 == NULL) {
        trace("ice_ffi_get", "ERROR: failed to get symbol from shared library/object!");
        return -1;
    }
    
    /* Call the function and print the result! */
    printf("F42 call result: %u\n", F42());
    
    /* Once we finished, We have to unload symbols and the shared library/object */
    F42 = NULL;
    unload_res = ice_ffi_unload(lib);
    
    /* If function failed to unload shared library/object, Trace error then terminate the program */
    if (unload_res == ICE_FFI_FALSE) {
        trace("ice_ffi_unload", "ERROR: failed to unload shared library/object!");
        return -1;
    }
    
    return 0;
}
