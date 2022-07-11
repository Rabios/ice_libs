/* Define the implementation of the library and include it */
#define ICE_CPU_IMPL 1
#include "ice_cpu.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) (void) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(void) {
    /* Struct that contains CPU information */
    ice_cpu_info cpu;
    
    /* Get CPU information */
    ice_cpu_bool res = ice_cpu_get_info(&cpu);
    
    /* If the function failed to retrieve CPU information, Trace error then terminate the program */
    if (res == ICE_CPU_FALSE) {
        trace("ice_cpu_get_info", "ERROR: failed to retrieve CPU informations!");
        return -1;
    }
    
    /* Print the informations */
    (void) printf("CPU Name: %s\nCPU Cores: %u\n", cpu.name, cpu.cores);
    
    return 0;
}
