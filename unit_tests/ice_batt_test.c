/* Unit Tests - ice_batt.h */
#define ICE_BATT_IMPL 1
#define ICE_TEST_IMPL 1

#include <stdio.h>
#include "ice_batt.h"
#include "ice_test.h"

ICE_TEST_CREATE(test_ice_batt) {
    ice_batt_info batt;
    ice_batt_error err = ice_batt_get_info(&batt);

    ICE_TEST_ASSERT_INT(err);
    ICE_TEST_ASSERT_EQU(err, ICE_BATT_ERROR_OK);

    ICE_TEST_ASSERT_INT(batt.exists);
    ICE_TEST_ASSERT_EQU(batt.exists, ICE_BATT_TRUE);

    ICE_TEST_ASSERT_INT(batt.charging);
    ICE_TEST_ASSERT_EQU(batt.charging, ICE_BATT_TRUE);

    ICE_TEST_ASSERT_INT(batt.level);
    ICE_TEST_ASSERT_NOT_NULL(batt.level);
    
    printf("ice_batt.h OK!\n");
}

int main(void) {
    test_ice_batt();
    return 0;
}
