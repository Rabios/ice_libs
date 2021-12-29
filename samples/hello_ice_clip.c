#define ICE_CLIP_IMPL
#include "ice_clip.h"
#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str)

int main(int argc, char** argv) {
    /* Result of calling functions */
    ice_clip_bool res;

    /* Retrieve the clipboard text */
    const char* text = ice_clip_get();

    /* If function failed to retrieve Clipboard text, Trace error then terminate the program */
    if (text == NULL) {
        trace("ice_clip_get", "ERROR: failed to retrieve Clipboard text!");
        return -1;
    }

    /* Clear the Clipboard */
    res = ice_clip_clear();

    /* If function failed to clear the Clipboard, Trace error then terminate the program */
    if (res == ICE_CLIP_FALSE) {
        trace("ice_clip_clear", "ERROR: failed to clear the Clipboard!");
        return -1;
    }

    /* Copy text to Clipboard */
    res = ice_clip_set("SPEED!");

    /* If function failed to copy text to the Clipboard, Trace error then terminate the program */
    if (res == ICE_CLIP_FALSE) {
        printf("ERROR: Failed to copy text to Clipboard!\n");
        return -1;
    }
    
    return 0;
}
