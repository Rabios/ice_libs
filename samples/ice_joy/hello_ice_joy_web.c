#define ICE_JOY_IMPL
#include <stdio.h>
#include <emscripten/emscripten.h>
#include "ice_joy.h"

void update(void);

int main(int argc, char** argv) {
    if (ice_joy_init() != ICE_JOY_TRUE) {
        return -1;
    }
    
    emscripten_set_main_loop(update, 0, 1);

    if (ice_joy_close() != ICE_JOY_TRUE) {
        return -1;
    }
    
    return 0;
}

void update(void) {
    if (ice_joy_connected(0) == ICE_JOY_TRUE) {
        if (ice_joy_update(0) == ICE_JOY_TRUE) {
            if (ice_joy_button_pressed(0, ICE_JOY_START) == ICE_JOY_TRUE) {
                printf("START PRESSED! YAY!\n");
            }
        } else {
            printf("ERROR: FAILED TO UPDATE JOYSTICK!\n");
        }
    } else {
        printf("ERROR: JOYSTICK NOT CONNECTED! PRESS START TO TRY CONNECT!\n");
    }
}
