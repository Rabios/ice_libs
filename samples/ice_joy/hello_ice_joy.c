#define ICE_JOY_IMPL
#include <stdio.h>
#include "ice_joy.h"

int main(int argc, char** argv) {
    if (ice_joy_init() != ICE_JOY_TRUE) {
        return -1;
    }

    while (ice_joy_connected(0) == ICE_JOY_TRUE) {
        if (ice_joy_update(0) == ICE_JOY_TRUE) {
            if (!(ice_joy_button_pressed(0, ICE_JOY_START) == ICE_JOY_TRUE)) {
                printf("RUNNING PROGRAM, PRESS START BUTTON TO BREAK!\n");
            } else {
                break;
            }
        }
    }

    if (ice_joy_close() != ICE_JOY_TRUE) {
        return -1;
    }
    
    return 0;
}
