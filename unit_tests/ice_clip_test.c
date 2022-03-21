/* Unit Tests - ice_clip.h */
#define ICE_CLIP_IMPL 1
#define ICE_TEST_IMPL 1

#include <stdio.h>
#include "ice_clip.h"
#include "ice_test.h"

ICE_TEST_CREATE(test_ice_clip) {
    ice_clip_bool res;
    char *txt = 0;
    
    txt = ice_clip_get();
    
    ICE_TEST_ASSERT_NOT_NULL(txt);

    res = ice_clip_set("TEST!");
    
    ICE_TEST_ASSERT_INT(res);
    ICE_TEST_ASSERT_EQU(res, ICE_CLIP_TRUE);

    res = ice_clip_clear();
    
    ICE_TEST_ASSERT_INT(res);
    ICE_TEST_ASSERT_EQU(res, ICE_CLIP_TRUE);
    
    printf("ice_clip.h OK!\n");
}

int main(void) {
    test_ice_clip();
    return 0;
}
