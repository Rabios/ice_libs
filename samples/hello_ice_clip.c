/* Define the implementation of the library and include it */
#define ICE_CLIP_IMPL 1
#include "ice_clip.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) (void) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(void) {
    /* To store result of called functions */
    ice_clip_bool res;
    
    /* String to copy to clipboard later... */
    const char *str = "SPEED!";

    /* Retrieve the clipboard text */
    const char *text = ice_clip_get();

    /* If the function failed to retrieve Clipboard text or Clipboard has no text then trace log a note, Else print the retrieved text... */
    if (text == 0) {
        trace("ice_clip_get", "LOG: failed to retrieve Clipboard text, Maybe the Clipboard does not contain text?");
    } else {
        (void) printf("Text from the Clipboard: %s\n", text);
    }

    /* Clear the Clipboard */
    res = ice_clip_clear();

    /* If the function failed to clear the Clipboard, Trace error then terminate the program */
    if (res == ICE_CLIP_FALSE) {
        trace("ice_clip_clear", "ERROR: failed to clear the Clipboard!");
        return -1;
    }

    /* Copy text to Clipboard */
    res = ice_clip_set(str);

    /* If the function failed to copy text to the Clipboard, Trace error then terminate the program */
    if (res == ICE_CLIP_FALSE) {
        trace("ice_clip_set", "ERROR: failed to copy text to Clipboard!");
        return -1;
    }
    
    (void) printf("Text copied to the Clipboard: %s\n", str);
    
    return 0;
}
