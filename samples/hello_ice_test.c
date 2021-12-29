#define ICE_TEST_IMPL
#include "ice_test.h"
#include <stdio.h>

/* Create a Test */
ICE_TEST_CREATE_EX(test1) {
    ICE_TEST_ASSERT_TRUE(sizeof(void*) == 8);
}

int main(int argc, char** argv) {
    printf("Testing if program is 64-bit...\n");
    test1(argc, argv); /* test! */
    printf("TEST SUCCESS!\n");

    return 0;
}
