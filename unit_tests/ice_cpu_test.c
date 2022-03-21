/* Unit Tests - ice_cpu.h */
#define ICE_CPU_IMPL 1
#define ICE_TEST_IMPL 1

#include <stdio.h>
#include "ice_cpu.h"
#include "ice_test.h"

ICE_TEST_CREATE(test_ice_cpu) {
    ice_cpu_info cpu;
    ice_cpu_bool res = ice_cpu_get_info(&cpu);
    
    ICE_TEST_ASSERT_INT(res);
    ICE_TEST_ASSERT_EQU(res, ICE_CPU_TRUE);

    ICE_TEST_ASSERT_INT(cpu.cores);
    ICE_TEST_ASSERT_NOT_NULL(cpu.cores);
    
    ICE_TEST_ASSERT_NOT_NULL(cpu.name);
    
    printf("ice_cpu.h OK!\n");
}

int main(void) {
    test_ice_cpu();
    return 0;
}
