/*
ice_al.h, Single-Header Cross-Platform C library for working with OpenAL!


================================== Full Overview ==================================

ice_al.h, Single-Header Cross-Platform C library for working with OpenAL, It works as OpenAL loader that allows to use OpenAL API from shared libraries...

To use it #define ICE_AL_IMPL then #include "ice_al.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

// Define the implementation of the library and include it
#define ICE_AL_IMPL 1
#include "ice_al.h"

#include <stdio.h>

// Helper
#define trace(fname, str) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(int argc, char** argv) {
    ice_al_bool res;

    // OpenAL device and OpenAL device name
    char* device_name;
    ALCdevice* dev;

    // Define the path of the OpenAL shared library/object depending on the platform (NOTE: You can also use OpenAL-soft)
#if defined(ICE_AL_MICROSOFT)
    const char *path = "OpenAL32.dll";
#else
    const char *path = "./liboal.so";
#endif
    
    // Load OpenAL shared library/object then load OpenAL API
    res = ice_al_load(path);
    
    // If the function failed to load OpenAL shared library and failed to load OpenAL API, Trace error then terminate the program
    if (res == ICE_AL_FALSE) {
        trace("ice_al_load", "ERROR: failed to load OpenAL shared library/object!");
        return -1;
    }
    
    // Get the default OpenAL audio device and initialize
    device_name = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    dev = alcOpenDevice(device_name);
    
    // If the function failed to initialize the default OpenAL device, Trace error then terminate the program
    if (dev == 0) {
        trace("alcOpenDevice", "ERROR: failed to open audio device!");
        return -1;
    }
    
    trace("main", "OpenAL audio device works!");
    
    // Once done close the OpenAL device, If the function failed to close the default OpenAL device, Trace error then terminate the program
    if (alcCloseDevice(dev) == ALC_FALSE) {
        trace("alcCloseDevice", "ERROR: failed to close audio device!");
        return -1;
    }
    
    return 0;
}


=================================== Library API ===================================

// Handle, Type definition for void* for symbols loaded from shared libs
typedef void* ice_al_handle;

// Boolean Enum, To avoid including stdbool.h
typedef enum ice_al_bool {
    ICE_AL_FALSE = -1,
    ICE_AL_TRUE = 0
} ice_al_bool;

// [INTERNAL] Loads symbol from loaded OpenAL shared library, Which can be casted to a function to call
ice_al_handle ice_al_proc(const char *symbol);

// Loads OpenAL API from shared library path (ex. openal32.dll on Windows), Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure
ice_al_bool ice_al_load(const char *path);

// Unloads OpenAL API, Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure
ice_al_bool ice_al_unload(void);

// API above is the OpenAL loader API, For OpenAL API:
// 1. https://www.openal.org/documentation/openal-1.1-specification.pdf
// 2. https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf


================================== Linking Flags ==================================

1. Microsoft Windows    => -lkernel32
2. Linux                => -ldl

// NOTE: When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragma preprocessor


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_al.h in the code...
#define ICE_AL_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_AL_VECTORCALL      // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_AL_FASTCALL        // fastcall
#define ICE_AL_STDCALL         // stdcall
#define ICE_AL_CDECL           // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_AL_MICROSOFT       // Microsoft Platforms
#define ICE_AL_BEOS            // BeOS and Haiku
#define ICE_AL_UNIX            // Unix and Unix-like (Unix/Linux and anything else based on these)


// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_AL_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_AL_DLLEXPORT       // Export the symbols to build as shared library
#define ICE_AL_DLLIMPORT       // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_AL_INLINE          // inlines library functions (Only works on C99 Standard and above)
#define ICE_AL_EXTERN          // externs library functions
#define ICE_AL_STATIC          // statics library functions

// NOTES:
// 1. You cannot #define both ICE_AL_EXTERN and ICE_AL_STATIC together in the code...
// 2. The definitions ONLY affects the OpenAL loader API


================================= Support ice_libs ================================

ice_al.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_AL_H
#define ICE_AL_H 1

/* Allow to use calling conventions if desired... */
#if defined(ICE_AL_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_AL_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_AL_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_AL_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_AL_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_AL_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_AL_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_AL_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_AL_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_AL_CDECL)
#  if defined(_MSC_VER)
#    define ICE_AL_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_AL_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_AL_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_AL_MICROSOFT) || defined(ICE_AL_UNIX) || defined(ICE_AL_BEOS))
#  define ICE_AL_PLATFORM_AUTODETECTED 1
#endif

/* Platform detection */
#if defined(ICE_AL_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_AL_MICROSOFT 1
#  elif defined(__HAIKU__) || defined(__BEOS__)
#    define ICE_AL_BEOS 1
#  elif defined(__unix__) || defined(__unix)
#    define ICE_AL_UNIX 1
#  else
#    error "ice_al.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_AL_EXTERN) && defined(ICE_AL_STATIC))
#  define ICE_AL_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_AL_EXTERN)
#  define ICE_AL_APIDEF extern
#elif defined(ICE_AL_STATIC)
#  define ICE_AL_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_AL_INLINE to enable inline functionality.
*/
#if defined(ICE_AL_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_AL_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_AL_INLINEDEF inline
#  endif
#else
#  define ICE_AL_INLINEDEF
#endif

/*
Allow to build DLL via ICE_AL_DLLEXPORT or ICE_AL_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
#if defined(ICE_AL_MICROSOFT)
#  if defined(ICE_AL_DLLEXPORT)
#    define ICE_AL_API __declspec(dllexport) ICE_AL_INLINEDEF
#  elif defined(ICE_AL_DLLIMPORT)
#    define ICE_AL_API __declspec(dllimport) ICE_AL_INLINEDEF
#  else
#    define ICE_AL_API ICE_AL_APIDEF ICE_AL_INLINEDEF
#  endif
#else
#  define ICE_AL_API ICE_AL_APIDEF ICE_AL_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Macros ============================== */

/* [INTERNAL] Macro to ease definition of functions */
#define ice_al_def_func(return_type, name, args)    \
    typedef return_type (*PFN_##name) args;         \
    PFN_##name name;                                \

/* [INTERNAL] Macro to ease loading symbols */
#define ICE_AL_LOAD_PROC(sym)                       \
    sym = (PFN_##sym) ice_al_proc(#sym);            \

/* [INTERNAL] Macro to ease unloading symbols */
#define ICE_AL_UNLOAD_PROC(sym) sym = 0;

/* ============================= Data Types (OpenAL API) ============================= */

typedef char ALboolean;
typedef char ALchar;
typedef signed char ALbyte;
typedef unsigned char ALubyte;
typedef short ALshort;
typedef unsigned short ALushort;
typedef int ALint;
typedef unsigned int ALuint;
typedef int ALsizei;
typedef int ALenum;
typedef float ALfloat;
typedef double ALdouble;
typedef void ALvoid;

typedef struct ALCdevice ALCdevice;
typedef struct ALCcontext ALCcontext;
typedef char ALCboolean;
typedef char ALCchar;
typedef signed char ALCbyte;
typedef unsigned char ALCubyte;
typedef short ALCshort;
typedef unsigned short ALCushort;
typedef int ALCint;
typedef unsigned int ALCuint;
typedef int ALCsizei;
typedef int ALCenum;
typedef float ALCfloat;
typedef double ALCdouble;
typedef void ALCvoid;

/* ============================= Definitions (OpenAL API) ============================= */

#define AL_NONE 0
#define AL_FALSE 0
#define AL_TRUE 1
#define AL_SOURCE_RELATIVE                       0x202
#define AL_CONE_INNER_ANGLE                      0x1001
#define AL_CONE_OUTER_ANGLE                      0x1002
#define AL_PITCH                                 0x1003
#define AL_POSITION                              0x1004
#define AL_DIRECTION                             0x1005
#define AL_VELOCITY                              0x1006
#define AL_LOOPING                               0x1007
#define AL_BUFFER                                0x1009
#define AL_GAIN                                  0x100A
#define AL_MIN_GAIN                              0x100D
#define AL_MAX_GAIN                              0x100E
#define AL_ORIENTATION                           0x100F
#define AL_SOURCE_STATE                          0x1010
#define AL_INITIAL                               0x1011
#define AL_PLAYING                               0x1012
#define AL_PAUSED                                0x1013
#define AL_STOPPED                               0x1014
#define AL_BUFFERS_QUEUED                        0x1015
#define AL_BUFFERS_PROCESSED                     0x1016
#define AL_REFERENCE_DISTANCE                    0x1020
#define AL_ROLLOFF_FACTOR                        0x1021
#define AL_CONE_OUTER_GAIN                       0x1022
#define AL_MAX_DISTANCE                          0x1023
#define AL_SEC_OFFSET                            0x1024
#define AL_SAMPLE_OFFSET                         0x1025
#define AL_BYTE_OFFSET                           0x1026
#define AL_SOURCE_TYPE                           0x1027
#define AL_STATIC                                0x1028
#define AL_STREAMING                             0x1029
#define AL_UNDETERMINED                          0x1030
#define AL_FORMAT_MONO8                          0x1100
#define AL_FORMAT_MONO16                         0x1101
#define AL_FORMAT_STEREO8                        0x1102
#define AL_FORMAT_STEREO16                       0x1103
#define AL_FREQUENCY                             0x2001
#define AL_BITS                                  0x2002
#define AL_CHANNELS                              0x2003
#define AL_SIZE                                  0x2004
#define AL_UNUSED                                0x2010
#define AL_PENDING                               0x2011
#define AL_PROCESSED                             0x2012
#define AL_NO_ERROR                              0
#define AL_INVALID_NAME                          0xA001
#define AL_INVALID_ENUM                          0xA002
#define AL_INVALID_VALUE                         0xA003
#define AL_INVALID_OPERATION                     0xA004
#define AL_OUT_OF_MEMORY                         0xA005
#define AL_VENDOR                                0xB001
#define AL_VERSION                               0xB002
#define AL_RENDERER                              0xB003
#define AL_EXTENSIONS                            0xB004
#define AL_DOPPLER_FACTOR                        0xC000
#define AL_DOPPLER_VELOCITY                      0xC001
#define AL_SPEED_OF_SOUND                        0xC003
#define AL_DISTANCE_MODEL                        0xD000
#define AL_INVERSE_DISTANCE                      0xD001
#define AL_INVERSE_DISTANCE_CLAMPED              0xD002
#define AL_LINEAR_DISTANCE                       0xD003
#define AL_LINEAR_DISTANCE_CLAMPED               0xD004
#define AL_EXPONENT_DISTANCE                     0xD005
#define AL_EXPONENT_DISTANCE_CLAMPED             0xD006

#define ALC_VERSION_0_1                          1
#define ALC_INVALID                              0
#define ALC_FALSE                                0
#define ALC_TRUE                                 1
#define ALC_FREQUENCY                            0x1007
#define ALC_REFRESH                              0x1008
#define ALC_SYNC                                 0x1009
#define ALC_MONO_SOURCES                         0x1010
#define ALC_STEREO_SOURCES                       0x1011
#define ALC_NO_ERROR                             0
#define ALC_INVALID_DEVICE                       0xA001
#define ALC_INVALID_CONTEXT                      0xA002
#define ALC_INVALID_ENUM                         0xA003
#define ALC_INVALID_VALUE                        0xA004
#define ALC_OUT_OF_MEMORY                        0xA005
#define ALC_MAJOR_VERSION                        0x1000
#define ALC_MINOR_VERSION                        0x1001
#define ALC_ATTRIBUTES_SIZE                      0x1002
#define ALC_ALL_ATTRIBUTES                       0x1003
#define ALC_DEFAULT_DEVICE_SPECIFIER             0x1004
#define ALC_DEVICE_SPECIFIER                     0x1005
#define ALC_EXTENSIONS                           0x1006
#define ALC_EXT_CAPTURE                          1
#define ALC_CAPTURE_DEVICE_SPECIFIER             0x310
#define ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER     0x311
#define ALC_CAPTURE_SAMPLES                      0x312
#define ALC_ENUMERATE_ALL_EXT                    1
#define ALC_DEFAULT_ALL_DEVICES_SPECIFIER        0x1012
#define ALC_ALL_DEVICES_SPECIFIER                0x1013

/* ============================= Functions (OpenAL API) ============================= */

ice_al_def_func(void, alDopplerFactor, (ALfloat value));
ice_al_def_func(void, alSpeedOfSound, (ALfloat value));
ice_al_def_func(void, alDistanceModel, (ALenum distanceModel));
ice_al_def_func(void, alEnable, (ALenum capability));
ice_al_def_func(void, alDisable, (ALenum capability));
ice_al_def_func(ALboolean, alIsEnabled, (ALenum capability));
ice_al_def_func(const ALchar *, alGetString, (ALenum param));
ice_al_def_func(void, alGetBooleanv, (ALenum param, ALboolean *values));
ice_al_def_func(void, alGetIntegerv, (ALenum param, ALint *values));
ice_al_def_func(void, alGetFloatv, (ALenum param, ALfloat *values));
ice_al_def_func(void, alGetDoublev, (ALenum param, ALdouble *values));
ice_al_def_func(ALboolean, alGetBoolean, (ALenum param));
ice_al_def_func(ALint, alGetInteger, (ALenum param));
ice_al_def_func(ALfloat, alGetFloat, (ALenum param));
ice_al_def_func(ALdouble, alGetDouble, (ALenum param));
ice_al_def_func(ALenum, alGetError, (void));
ice_al_def_func(ALboolean, alIsExtensionPresent, (const ALchar *extname));
ice_al_def_func(void*, alGetProcAddress, (const ALchar *fname));
ice_al_def_func(ALenum, alGetEnumValue, (const ALchar *ename));
ice_al_def_func(void, alListenerf, (ALenum param, ALfloat value));
ice_al_def_func(void, alListener3f, (ALenum param, ALfloat value1, ALfloat value2, ALfloat value3));
ice_al_def_func(void, alListenerfv, (ALenum param, const ALfloat *values));
ice_al_def_func(void, alListeneri, (ALenum param, ALint value));
ice_al_def_func(void, alListener3i, (ALenum param, ALint value1, ALint value2, ALint value3));
ice_al_def_func(void, alListeneriv, (ALenum param, const ALint *values));
ice_al_def_func(void, alGetListenerf, (ALenum param, ALfloat *value));
ice_al_def_func(void, alGetListener3f, (ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3));
ice_al_def_func(void, alGetListenerfv, (ALenum param, ALfloat *values));
ice_al_def_func(void, alGetListeneri, (ALenum param, ALint *value));
ice_al_def_func(void, alGetListener3i, (ALenum param, ALint *value1, ALint *value2, ALint *value3));
ice_al_def_func(void, alGetListeneriv, (ALenum param, ALint *values));
ice_al_def_func(void, alGenSources, (ALsizei n, ALuint *sources));
ice_al_def_func(void, alDeleteSources, (ALsizei n, const ALuint *sources));
ice_al_def_func(ALboolean, alIsSource, (ALuint source));
ice_al_def_func(void, alSourcef, (ALuint source, ALenum param, ALfloat value));
ice_al_def_func(void, alSource3f, (ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3));
ice_al_def_func(void, alSourcefv, (ALuint source, ALenum param, const ALfloat *values));
ice_al_def_func(void, alSourcei, (ALuint source, ALenum param, ALint value));
ice_al_def_func(void, alSource3i, (ALuint source, ALenum param, ALint value1, ALint value2, ALint value3));
ice_al_def_func(void, alSourceiv, (ALuint source, ALenum param, const ALint *values));
ice_al_def_func(void, alGetSourcef, (ALuint source, ALenum param, ALfloat *value));
ice_al_def_func(void, alGetSource3f, (ALuint source, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3));
ice_al_def_func(void, alGetSourcefv, (ALuint source, ALenum param, ALfloat *values));
ice_al_def_func(void, alGetSourcei, (ALuint source,  ALenum param, ALint *value));
ice_al_def_func(void, alGetSource3i, (ALuint source, ALenum param, ALint *value1, ALint *value2, ALint *value3));
ice_al_def_func(void, alGetSourceiv, (ALuint source,  ALenum param, ALint *values));
ice_al_def_func(void, alSourcePlayv, (ALsizei n, const ALuint *sources));
ice_al_def_func(void, alSourceStopv, (ALsizei n, const ALuint *sources));
ice_al_def_func(void, alSourceRewindv, (ALsizei n, const ALuint *sources));
ice_al_def_func(void, alSourcePausev, (ALsizei n, const ALuint *sources));
ice_al_def_func(void, alSourcePlay, (ALuint source));
ice_al_def_func(void, alSourceStop, (ALuint source));
ice_al_def_func(void, alSourceRewind, (ALuint source));
ice_al_def_func(void, alSourcePause, (ALuint source));
ice_al_def_func(void, alSourceQueueBuffers, (ALuint source, ALsizei nb, const ALuint *buffers));
ice_al_def_func(void, alSourceUnqueueBuffers, (ALuint source, ALsizei nb, ALuint *buffers));
ice_al_def_func(void, alGenBuffers, (ALsizei n, ALuint *buffers));
ice_al_def_func(void, alDeleteBuffers, (ALsizei n, const ALuint *buffers));
ice_al_def_func(ALboolean, alIsBuffer, (ALuint buffer));
ice_al_def_func(void, alBufferData, (ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq));
ice_al_def_func(void, alBufferf, (ALuint buffer, ALenum param, ALfloat value));
ice_al_def_func(void, alBuffer3f, (ALuint buffer, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3));
ice_al_def_func(void, alBufferfv, (ALuint buffer, ALenum param, const ALfloat *values));
ice_al_def_func(void, alBufferi, (ALuint buffer, ALenum param, ALint value));
ice_al_def_func(void, alBuffer3i, (ALuint buffer, ALenum param, ALint value1, ALint value2, ALint value3));
ice_al_def_func(void, alBufferiv, (ALuint buffer, ALenum param, const ALint *values));
ice_al_def_func(void, alGetBufferf, (ALuint buffer, ALenum param, ALfloat *value));
ice_al_def_func(void, alGetBuffer3f, (ALuint buffer, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3));
ice_al_def_func(void, alGetBufferfv, (ALuint buffer, ALenum param, ALfloat *values));
ice_al_def_func(void, alGetBufferi, (ALuint buffer, ALenum param, ALint *value));
ice_al_def_func(void, alGetBuffer3i, (ALuint buffer, ALenum param, ALint *value1, ALint *value2, ALint *value3));
ice_al_def_func(void, alGetBufferiv, (ALuint buffer, ALenum param, ALint *values));

ice_al_def_func(ALCcontext*, alcCreateContext, (ALCdevice *device, const ALCint *attrlist));
ice_al_def_func(ALCboolean, alcMakeContextCurrent, (ALCcontext *context));
ice_al_def_func(void, alcProcessContext, (ALCcontext *context));
ice_al_def_func(void, alcSuspendContext, (ALCcontext *context));
ice_al_def_func(void, alcDestroyContext, (ALCcontext *context));
ice_al_def_func(ALCcontext*, alcGetCurrentContext, (void));
ice_al_def_func(ALCcontext*, alcGetContextsDevice, (ALCcontext *context));
ice_al_def_func(ALCdevice*, alcOpenDevice, (const ALCchar *devicename));
ice_al_def_func(ALCboolean, alcCloseDevice, (ALCdevice *device));
ice_al_def_func(ALCenum, alcGetError, (ALCdevice *device));
ice_al_def_func(ALCboolean, alcIsExtensionPresent, (ALCdevice *device, const ALCchar *extname));
ice_al_def_func(ALCvoid*, alcGetProcAddress, (ALCdevice *device, const ALCchar *funcname));
ice_al_def_func(ALCenum, alcGetEnumValue, (ALCdevice *device, const ALCchar *enumname));
ice_al_def_func(ALCchar*, alcGetString, (ALCdevice *device, ALCenum param));
ice_al_def_func(void, alcGetIntegerv, (ALCdevice *device, ALCenum param, ALCsizei size, ALCint *values));
ice_al_def_func(ALCdevice*, alcCaptureOpenDevice, (const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize));
ice_al_def_func(ALCboolean, alcCaptureCloseDevice, (ALCdevice *device));
ice_al_def_func(void, alcCaptureStart, (ALCdevice *device));
ice_al_def_func(void, alcCaptureStop, (ALCdevice *device));
ice_al_def_func(void, alcCaptureSamples, (ALCdevice *device, ALCvoid* buffer, ALCsizei samples));

/* ============================= Data Types ============================= */

/* Handle, Type definition for void* for symbols loaded from shared libs */
typedef void* ice_al_handle;

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_al_bool {
    ICE_AL_FALSE = -1,
    ICE_AL_TRUE = 0
} ice_al_bool;

/* ============================= Functions ============================= */

/* [INTERNAL] Loads symbol from loaded OpenAL shared library, Which can be casted to a function to call */
ICE_AL_API ice_al_handle ICE_AL_CALLCONV ice_al_proc(const char *symbol);

/* Loads OpenAL API from shared library path (ex. openal32.dll on Windows), Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ICE_AL_API ice_al_bool ICE_AL_CALLCONV ice_al_load(const char *path);

/* Unloads OpenAL API, Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ICE_AL_API ice_al_bool ICE_AL_CALLCONV ice_al_unload(void);

/*
API above is the OpenAL loader API, For OpenAL API:

1. https://www.openal.org/documentation/openal-1.1-specification.pdf
2. https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
*/

#if defined(__cplusplus)
}
#endif

#if defined(ICE_AL_IMPL)

#if defined(ICE_AL_MICROSOFT)
#  if defined(_MSC_VER)
#    include <windows.h>
#    pragma comment(lib, "kernel32.lib")
#  else
#    include <libloaderapi.h>
#  endif
#elif defined(ICE_AL_BEOS)
#  include <be/kernel/image.h>
#elif defined(ICE_AL_UNIX)
#  include <dlfcn.h>
#endif

static ice_al_handle ice_al_lib;

/* [INTERNAL] Loads symbol from loaded OpenAL shared library, Which can be casted to a function to call */
ICE_AL_API ice_al_handle ICE_AL_CALLCONV ice_al_proc(const char *symbol) {
#if defined(ICE_AL_MICROSOFT)
    return GetProcAddress(ice_al_lib, symbol);
#elif defined(ICE_AL_BEOS)
    ice_al_handle sym;
    int res = get_image_symbol((isize) ice_al_lib, symbol, B_SYMBOL_TYPE_ANY, &sym);
    
    if (res != 0) return 0;

#elif defined(ICE_AL_UNIX)
    return dlsym(ice_al_lib, symbol);
#endif
}

/* Loads OpenAL API from shared library path (ex. openal32.dll on Windows), Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ICE_AL_API ice_al_bool ICE_AL_CALLCONV ice_al_load(const char* path) {
#if defined(ICE_AL_MICROSOFT)
    ice_al_lib = LoadLibraryA(path);
    if (ice_al_lib == 0) return ICE_AL_FALSE;
#elif defined(ICE_AL_BEOS)
    isize lib = load_add_on(path);
    if (lib < 0) return ICE_AL_FALSE;
    
    ice_al_lib = (ice_al_handle) lib;

#elif defined(ICE_AL_UNIX)
    ice_al_lib = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
    if (ice_al_lib == 0) return ICE_AL_FALSE;
#endif

    ICE_AL_LOAD_PROC(alDopplerFactor);
    ICE_AL_LOAD_PROC(alSpeedOfSound);
    ICE_AL_LOAD_PROC(alDistanceModel);
    ICE_AL_LOAD_PROC(alEnable);
    ICE_AL_LOAD_PROC(alDisable);
    ICE_AL_LOAD_PROC(alIsEnabled);
    ICE_AL_LOAD_PROC(alGetString);
    ICE_AL_LOAD_PROC(alGetBooleanv);
    ICE_AL_LOAD_PROC(alGetIntegerv);
    ICE_AL_LOAD_PROC(alGetFloatv);
    ICE_AL_LOAD_PROC(alGetDoublev);
    ICE_AL_LOAD_PROC(alGetBoolean);
    ICE_AL_LOAD_PROC(alGetInteger);
    ICE_AL_LOAD_PROC(alGetFloat);
    ICE_AL_LOAD_PROC(alGetDouble);
    ICE_AL_LOAD_PROC(alGetError);
    ICE_AL_LOAD_PROC(alIsExtensionPresent);
    ICE_AL_LOAD_PROC(alGetProcAddress);
    ICE_AL_LOAD_PROC(alGetEnumValue);
    ICE_AL_LOAD_PROC(alListenerf);
    ICE_AL_LOAD_PROC(alListener3f);
    ICE_AL_LOAD_PROC(alListenerfv);
    ICE_AL_LOAD_PROC(alListeneri);
    ICE_AL_LOAD_PROC(alListener3i);
    ICE_AL_LOAD_PROC(alListeneriv);
    ICE_AL_LOAD_PROC(alGetListenerf);
    ICE_AL_LOAD_PROC(alGetListener3f);
    ICE_AL_LOAD_PROC(alGetListenerfv);
    ICE_AL_LOAD_PROC(alGetListeneri);
    ICE_AL_LOAD_PROC(alGetListener3i);
    ICE_AL_LOAD_PROC(alGetListeneriv);
    ICE_AL_LOAD_PROC(alGenSources);
    ICE_AL_LOAD_PROC(alDeleteSources);
    ICE_AL_LOAD_PROC(alIsSource);
    ICE_AL_LOAD_PROC(alSourcef);
    ICE_AL_LOAD_PROC(alSource3f);
    ICE_AL_LOAD_PROC(alSourcefv);
    ICE_AL_LOAD_PROC(alSourcei);
    ICE_AL_LOAD_PROC(alSource3i);
    ICE_AL_LOAD_PROC(alSourceiv);
    ICE_AL_LOAD_PROC(alGetSourcef);
    ICE_AL_LOAD_PROC(alGetSource3f);
    ICE_AL_LOAD_PROC(alGetSourcefv);
    ICE_AL_LOAD_PROC(alGetSourcei);
    ICE_AL_LOAD_PROC(alGetSource3i);
    ICE_AL_LOAD_PROC(alGetSourceiv);
    ICE_AL_LOAD_PROC(alSourcePlayv);
    ICE_AL_LOAD_PROC(alSourceStopv);
    ICE_AL_LOAD_PROC(alSourceRewindv);
    ICE_AL_LOAD_PROC(alSourcePausev);
    ICE_AL_LOAD_PROC(alSourcePlay);
    ICE_AL_LOAD_PROC(alSourceStop);
    ICE_AL_LOAD_PROC(alSourceRewind);
    ICE_AL_LOAD_PROC(alSourcePause);
    ICE_AL_LOAD_PROC(alSourceQueueBuffers);
    ICE_AL_LOAD_PROC(alSourceUnqueueBuffers);
    ICE_AL_LOAD_PROC(alGenBuffers);
    ICE_AL_LOAD_PROC(alDeleteBuffers);
    ICE_AL_LOAD_PROC(alIsBuffer);
    ICE_AL_LOAD_PROC(alBufferData);
    ICE_AL_LOAD_PROC(alBufferf);
    ICE_AL_LOAD_PROC(alBuffer3f);
    ICE_AL_LOAD_PROC(alBufferfv);
    ICE_AL_LOAD_PROC(alBufferi);
    ICE_AL_LOAD_PROC(alBuffer3i);
    ICE_AL_LOAD_PROC(alBufferiv);
    ICE_AL_LOAD_PROC(alGetBufferf);
    ICE_AL_LOAD_PROC(alGetBuffer3f);
    ICE_AL_LOAD_PROC(alGetBufferfv);
    ICE_AL_LOAD_PROC(alGetBufferi);
    ICE_AL_LOAD_PROC(alGetBuffer3i);
    ICE_AL_LOAD_PROC(alGetBufferiv);

    ICE_AL_LOAD_PROC(alcCreateContext);
    ICE_AL_LOAD_PROC(alcMakeContextCurrent);
    ICE_AL_LOAD_PROC(alcProcessContext);
    ICE_AL_LOAD_PROC(alcSuspendContext);
    ICE_AL_LOAD_PROC(alcDestroyContext);
    ICE_AL_LOAD_PROC(alcGetCurrentContext);
    ICE_AL_LOAD_PROC(alcGetContextsDevice);
    ICE_AL_LOAD_PROC(alcOpenDevice);
    ICE_AL_LOAD_PROC(alcCloseDevice);
    ICE_AL_LOAD_PROC(alcGetError);
    ICE_AL_LOAD_PROC(alcIsExtensionPresent);
    ICE_AL_LOAD_PROC(alcGetProcAddress);
    ICE_AL_LOAD_PROC(alcGetEnumValue);
    ICE_AL_LOAD_PROC(alcGetString);
    ICE_AL_LOAD_PROC(alcGetIntegerv);
    ICE_AL_LOAD_PROC(alcCaptureOpenDevice);
    ICE_AL_LOAD_PROC(alcCaptureCloseDevice);
    ICE_AL_LOAD_PROC(alcCaptureStart);
    ICE_AL_LOAD_PROC(alcCaptureStop);
    ICE_AL_LOAD_PROC(alcCaptureSamples);
    
    return ICE_AL_TRUE;
}

/* Unloads OpenAL API, Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ICE_AL_API ice_al_bool ICE_AL_CALLCONV ice_al_unload(void) {
    int res = 0;
    
    ICE_AL_UNLOAD_PROC(alDopplerFactor);
    ICE_AL_UNLOAD_PROC(alSpeedOfSound);
    ICE_AL_UNLOAD_PROC(alDistanceModel);
    ICE_AL_UNLOAD_PROC(alEnable);
    ICE_AL_UNLOAD_PROC(alDisable);
    ICE_AL_UNLOAD_PROC(alIsEnabled);
    ICE_AL_UNLOAD_PROC(alGetString);
    ICE_AL_UNLOAD_PROC(alGetBooleanv);
    ICE_AL_UNLOAD_PROC(alGetIntegerv);
    ICE_AL_UNLOAD_PROC(alGetFloatv);
    ICE_AL_UNLOAD_PROC(alGetDoublev);
    ICE_AL_UNLOAD_PROC(alGetBoolean);
    ICE_AL_UNLOAD_PROC(alGetInteger);
    ICE_AL_UNLOAD_PROC(alGetFloat);
    ICE_AL_UNLOAD_PROC(alGetDouble);
    ICE_AL_UNLOAD_PROC(alGetError);
    ICE_AL_UNLOAD_PROC(alIsExtensionPresent);
    ICE_AL_UNLOAD_PROC(alGetProcAddress);
    ICE_AL_UNLOAD_PROC(alGetEnumValue);
    ICE_AL_UNLOAD_PROC(alListenerf);
    ICE_AL_UNLOAD_PROC(alListener3f);
    ICE_AL_UNLOAD_PROC(alListenerfv);
    ICE_AL_UNLOAD_PROC(alListeneri);
    ICE_AL_UNLOAD_PROC(alListener3i);
    ICE_AL_UNLOAD_PROC(alListeneriv);
    ICE_AL_UNLOAD_PROC(alGetListenerf);
    ICE_AL_UNLOAD_PROC(alGetListener3f);
    ICE_AL_UNLOAD_PROC(alGetListenerfv);
    ICE_AL_UNLOAD_PROC(alGetListeneri);
    ICE_AL_UNLOAD_PROC(alGetListener3i);
    ICE_AL_UNLOAD_PROC(alGetListeneriv);
    ICE_AL_UNLOAD_PROC(alGenSources);
    ICE_AL_UNLOAD_PROC(alDeleteSources);
    ICE_AL_UNLOAD_PROC(alIsSource);
    ICE_AL_UNLOAD_PROC(alSourcef);
    ICE_AL_UNLOAD_PROC(alSource3f);
    ICE_AL_UNLOAD_PROC(alSourcefv);
    ICE_AL_UNLOAD_PROC(alSourcei);
    ICE_AL_UNLOAD_PROC(alSource3i);
    ICE_AL_UNLOAD_PROC(alSourceiv);
    ICE_AL_UNLOAD_PROC(alGetSourcef);
    ICE_AL_UNLOAD_PROC(alGetSource3f);
    ICE_AL_UNLOAD_PROC(alGetSourcefv);
    ICE_AL_UNLOAD_PROC(alGetSourcei);
    ICE_AL_UNLOAD_PROC(alGetSource3i);
    ICE_AL_UNLOAD_PROC(alGetSourceiv);
    ICE_AL_UNLOAD_PROC(alSourcePlayv);
    ICE_AL_UNLOAD_PROC(alSourceStopv);
    ICE_AL_UNLOAD_PROC(alSourceRewindv);
    ICE_AL_UNLOAD_PROC(alSourcePausev);
    ICE_AL_UNLOAD_PROC(alSourcePlay);
    ICE_AL_UNLOAD_PROC(alSourceStop);
    ICE_AL_UNLOAD_PROC(alSourceRewind);
    ICE_AL_UNLOAD_PROC(alSourcePause);
    ICE_AL_UNLOAD_PROC(alSourceQueueBuffers);
    ICE_AL_UNLOAD_PROC(alSourceUnqueueBuffers);
    ICE_AL_UNLOAD_PROC(alGenBuffers);
    ICE_AL_UNLOAD_PROC(alDeleteBuffers);
    ICE_AL_UNLOAD_PROC(alIsBuffer);
    ICE_AL_UNLOAD_PROC(alBufferData);
    ICE_AL_UNLOAD_PROC(alBufferf);
    ICE_AL_UNLOAD_PROC(alBuffer3f);
    ICE_AL_UNLOAD_PROC(alBufferfv);
    ICE_AL_UNLOAD_PROC(alBufferi);
    ICE_AL_UNLOAD_PROC(alBuffer3i);
    ICE_AL_UNLOAD_PROC(alBufferiv);
    ICE_AL_UNLOAD_PROC(alGetBufferf);
    ICE_AL_UNLOAD_PROC(alGetBuffer3f);
    ICE_AL_UNLOAD_PROC(alGetBufferfv);
    ICE_AL_UNLOAD_PROC(alGetBufferi);
    ICE_AL_UNLOAD_PROC(alGetBuffer3i);
    ICE_AL_UNLOAD_PROC(alGetBufferiv);

    ICE_AL_UNLOAD_PROC(alcCreateContext);
    ICE_AL_UNLOAD_PROC(alcMakeContextCurrent);
    ICE_AL_UNLOAD_PROC(alcProcessContext);
    ICE_AL_UNLOAD_PROC(alcSuspendContext);
    ICE_AL_UNLOAD_PROC(alcDestroyContext);
    ICE_AL_UNLOAD_PROC(alcGetCurrentContext);
    ICE_AL_UNLOAD_PROC(alcGetContextsDevice);
    ICE_AL_UNLOAD_PROC(alcOpenDevice);
    ICE_AL_UNLOAD_PROC(alcCloseDevice);
    ICE_AL_UNLOAD_PROC(alcGetError);
    ICE_AL_UNLOAD_PROC(alcIsExtensionPresent);
    ICE_AL_UNLOAD_PROC(alcGetProcAddress);
    ICE_AL_UNLOAD_PROC(alcGetEnumValue);
    ICE_AL_UNLOAD_PROC(alcGetString);
    ICE_AL_UNLOAD_PROC(alcGetIntegerv);
    ICE_AL_UNLOAD_PROC(alcCaptureOpenDevice);
    ICE_AL_UNLOAD_PROC(alcCaptureCloseDevice);
    ICE_AL_UNLOAD_PROC(alcCaptureStart);
    ICE_AL_UNLOAD_PROC(alcCaptureStop);
    ICE_AL_UNLOAD_PROC(alcCaptureSamples);

#if defined(ICE_AL_MICROSOFT)
    res = (FreeLibrary(lib) != 0) ? 0 : -1;

#elif defined(ICE_AL_BEOS)
    res = unload_add_on((isize) ice_al_lib);

#elif defined(ICE_AL_UNIX)
    res = dlclose(ice_al_lib);

#endif

    ice_al_lib = 0;
    return (res == 0) ? ICE_AL_TRUE : ICE_AL_FALSE;
}

#endif  /* ICE_AL_IMPL */
#endif  /* ICE_AL_H */

/*
ice_al.h is dual-licensed, Choose the one you prefer!

------------------------------------------------------------------------
LICENSE A - PUBLIC DOMAIN LICENSE
------------------------------------------------------------------------
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

------------------------------------------------------------------------
LICENSE B - MIT LICENSE
------------------------------------------------------------------------
Copyright (c) 2021 - <Present> Rabia Alhaffar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
