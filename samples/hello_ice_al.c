/* Define the implementation of the library and include it */
#define ICE_AL_IMPL 1
#include "ice_al.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(int argc, char** argv) {
    ice_al_bool res;

    /* OpenAL device and OpenAL device name */
    char* device_name;
    ALCdevice* dev;

    /* Define the path of the OpenAL shared library/object depending on the platform (NOTE: You can also use OpenAL-soft) */
#if defined(ICE_AL_MICROSOFT)
    const char *path = "OpenAL32.dll";
#else
    const char *path = "./liboal.so";
#endif
    
    /* Load OpenAL shared library/object then load OpenAL API */
    res = ice_al_load(path);
    
    /* If the function failed to load OpenAL shared library and failed to load OpenAL API, Trace error then terminate the program */
    if (res == ICE_AL_FALSE) {
        trace("ice_al_load", "ERROR: failed to load OpenAL shared library/object!");
        return -1;
    }
    
    /* Get the default OpenAL audio device and initialize */
    device_name = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    dev = alcOpenDevice(device_name);
    
    /* If the function failed to initialize the default OpenAL device, Trace error then terminate the program */
    if (dev == 0) {
        trace("alcOpenDevice", "ERROR: failed to open audio device!");
        return -1;
    }
    
    trace("main", "OpenAL audio device works!");
    
    /* Once done close the OpenAL device, If the function failed to close the default OpenAL device, Trace error then terminate the program */
    if (alcCloseDevice(dev) == ALC_FALSE) {
        trace("alcCloseDevice", "ERROR: failed to close audio device!");
        return -1;
    }
    
    return 0;
}
