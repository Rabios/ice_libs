/* Define the implementation of the library and include it */
#define ICE_RAM_IMPL 1
#include "ice_ram.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(void) {
    /* Struct that contains RAM information */
    ice_ram_info ram;

    /* Fetch RAM info */
    ice_ram_bool res = ice_ram_get_info(&ram);

    /* If function failed to fetch RAM info, Trace error then terminate the program */
    if (res == ICE_RAM_FALSE) {
        trace("ice_ram_get_info", "ERROR: failed to retrieve RAM informations!");
        return -1;
    }
    
    /* Print RAM info (free, used, total) in bytes */
    printf("%s %llu bytes\n%s %llu bytes\n%s %llu bytes\n",
            "Free RAM:", ram.free,
            "Used RAM:", ram.used,
            "Total RAM:", ram.total);

    return 0;
}
