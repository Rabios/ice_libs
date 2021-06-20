#define ICE_MOUSE_IMPL
#include <stdio.h>
#include "ice_mouse.h"

int main(int argc, char** argv) {
    // Initialize mouse
    if (ice_mouse_init() == ICE_MOUSE_FALSE) {
        printf("ERROR: Failed to initialize mouse!\n");
        return -1;
    }

    while (1) {
        // Update mouse and print position!
        if (ice_mouse_update() == ICE_MOUSE_TRUE) {
            ice_mouse_vec2 pos = ice_mouse_pos();
            printf("Mouse X: %f, Mouse Y: %f\n", pos.x, pos.y);
            
            // If right mouse button pressed, Break the loop and exit the program!
            if (ice_mouse_button_pressed(ICE_MOUSE_BUTTON_RIGHT) == ICE_MOUSE_TRUE) {
                break;
            }
        } else {
            break;
        }
    }

    if (ice_mouse_close() == ICE_MOUSE_FALSE) {
        printf("ERROR: Failed to deinitialize mouse!\n");
        return -1;
    }

    return 0;
}
