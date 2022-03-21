/* Unit Tests - ice_ram.h */
#define ICE_RAM_IMPL 1
#define ICE_TEST_IMPL 1

#include <stdio.h>
#include "ice_ram.h"
#include "ice_test.h"

ICE_TEST_CREATE(test_ice_ram) {
    ice_ram_info ram;
    ice_ram_bool res = ice_ram_get_info(&ram);

    ICE_TEST_ASSERT_INT(res);
    ICE_TEST_ASSERT_EQU(res, ICE_RAM_TRUE);
    
    ICE_TEST_ASSERT_TRUE(((ice_ram_bytes)(ram.free) == ram.free));
    ICE_TEST_ASSERT_NOT_NULL(ram.free);

    ICE_TEST_ASSERT_TRUE(((ice_ram_bytes)(ram.used) == ram.used));
    ICE_TEST_ASSERT_NOT_NULL(ram.used);

    ICE_TEST_ASSERT_TRUE(((ice_ram_bytes)(ram.total) == ram.total));
    ICE_TEST_ASSERT_NOT_NULL(ram.total);
    
    printf("ice_ram.h OK!\n");
}

int main(void) {
    test_ice_ram();
    return 0;
}
