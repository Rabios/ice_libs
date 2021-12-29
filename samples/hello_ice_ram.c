/* Define the implementation and include the library */
#define ICE_RAM_IMPL
#include "ice_ram.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str)

int main(int argc, char** argv) {
    ice_ram_info info;

    /* Fetch RAM info */
    ice_ram_bool res = ice_ram_get_status(&info);

    /* If function failed to fetch RAM info, Trace error then terminate the program */
    if (res == ICE_RAM_FALSE) {
        trace("ice_ram_get_status", "ERROR: failed to get RAM info!");
        return -1;
    }
    
    /* Print RAM info (free, used, total) in Bytes */
    printf("%s %lu bytes\n%s %lu bytes\n%s %lu bytes\n",
            "Free RAM:", info.free,
            "Used RAM:", info.used,
            "Total RAM:", info.total);

    return 0;
}
