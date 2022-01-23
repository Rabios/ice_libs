/* Define the implementation of the library and include it */
#define ICE_TIME_IMPL 1
#include "ice_time.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(void) {
    /* Struct that contains Time information */
    ice_time_info current_time;
    
    /* Fetch time information and store it in the struct */
    ice_time_error res = ice_time_get_info(&current_time);

    /* If the function failed to fetch time information, Trace error then terminate the program! */
    if (res != ICE_TIME_ERROR_OK) {
        trace("ice_time_get_info", "ERROR: failed to get time info!");
        return -1;
    }

    /* Print current time! */
    printf("Current Time: %s\n", current_time.str);

    return 0;
}
