/* Define the implementation of the library and include it */
#define ICE_STR_IMPL 1
#include "ice_str.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(void) {
    /* Create a string repeated for multiple times */
    char *haha = ice_str_dup("HA", 8); /* HAHAHAHAHAHAHAHA */

    /* If the function failed to allocate string, Trace error then terminate the program */
    if (haha == 0) {
        trace("ice_str_dup", "ERROR: failed to allocate string!");
        return -1;
    }

    /* Print the string, Once we done we deallocate/free the string */
    printf("%s\n", haha);
    ice_str_free(haha);

    return 0;
}
