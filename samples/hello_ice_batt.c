/* Define the implementation of the library then include it */
#define ICE_BATT_IMPL 1
#include "ice_batt.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(int argc, char **argv) {
    /* Struct that contains information about the battery */
    ice_batt_info info;

    /* Fetch battery information and store the information in the struct */
    ice_batt_error err = ice_batt_get_status(&info);

    /* If the function failed to fetch battery information, Trace error then terminate the program */
    if (err != ICE_BATT_ERROR_OK) {
        trace("ice_batt_get_status", "ERROR: failed to fetch battery information!");
        return -1;
    }

    /* Print information we got */
    printf("Device has battery: %s\nIs battery charging: %s\nBattery Level: %u\n",
      (info.exists == ICE_BATT_TRUE) ? "YES" : "NO",
      (info.charging == ICE_BATT_TRUE) ? "YES" : "NO",
      info.level);

    return 0;
}
