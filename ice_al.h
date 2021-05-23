// Written by Rabia Alhaffar in 14/April/2021
// ice_al.h
// Single-Header Cross-Platform C OpenAL loader!
// Updated: 23/May/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_al.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_al is cross-platform single-header C OpenAL loader!

Works anywhere OpenAL works!

[2] IMPLEMENTATION:
Windows             -> LoadLibrary, FreeLibrary, GetProcAddress
Haiku/BeOS          -> load_add_on, unload_add_on, get_image_symbol
Elsewhere           -> dlopen, dlsym, dlclose

DEV NOTE: Android also has 3rd support, Check out this: https://github.com/AerialX/openal-soft-android

[3] USAGE:
Define ICE_AL_IMPL then include ice_al.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_al
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_al by possibly one of following things:
//
// 1. Test ice_al on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

#ifndef ICE_AL_H
#define ICE_AL_H

// Disable security warnings for MSVC compiler, We don't want to force using C11!
#ifdef _MSC_VER
#  define _CRT_SECURE_NO_DEPRECATE
#  define _CRT_SECURE_NO_WARNINGS
#  pragma warning(disable:4996)
#endif

// Define C interface for Windows libraries! ;)
#ifndef CINTERFACE
#  define CINTERFACE
#endif

// Allow to use calling convention if desired...
#if defined(__GNUC__) || defined(__GNUG__)
#  if defined(ICE_AL_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_AL_CALLCONV_FASTCALL)
#    define ICE_AL_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_AL_CALLCONV_STDCALL)
#    define ICE_AL_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_AL_CALLCONV_CDECL)
#    define ICE_AL_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_AL_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_AL_CALLCONV_VECTORCALL)
#    define ICE_AL_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_AL_CALLCONV_FASTCALL)
#    define ICE_AL_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_AL_CALLCONV_STDCALL)
#    define ICE_AL_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_AL_CALLCONV_CDECL)
#    define ICE_AL_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_AL_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_AL_CALLCONV_VECTORCALL)
#    define ICE_AL_CALLCONV __vectorcall
#  elif defined(ICE_AL_CALLCONV_FASTCALL)
#    define ICE_AL_CALLCONV __fastcall
#  elif defined(ICE_AL_CALLCONV_STDCALL)
#    define ICE_AL_CALLCONV __stdcall
#  elif defined(ICE_AL_CALLCONV_CDECL)
#    define ICE_AL_CALLCONV __cdecl
#  else
#    define ICE_AL_CALLCONV
#  endif
#else
#  define ICE_AL_CALLCONV
#endif

// Detect Windows to allow building DLLs
#if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox)
#  define ICE_AL_MICROSOFT
#endif

// Allow to use them as extern functions if desired!
#if defined(ICE_AL_EXTERN)
#  define ICE_AL_EXTERNDEF extern
#else
#  define ICE_AL_EXTERNDEF
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
#if !defined(__STDC_VERSION__)
#  define ICE_AL_INLINEDEF
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define ICE_AL_INLINEDEF inline
#endif

// Allow to build DLL via ICE_AL_DLLEXPORT or ICE_AL_DLLIMPORT if desired!
// Else, Just define API as static inlined C code!
#if defined(ICE_AL_MICROSOFT)
#  if defined(ICE_AL_DLLEXPORT)
#    define ICE_AL_API ICE_AL_EXTERNDEF __declspec(dllexport) ICE_AL_INLINEDEF
#  elif defined(ICE_AL_DLLIMPORT)
#    define ICE_AL_API ICE_AL_EXTERNDEF __declspec(dllimport) ICE_AL_INLINEDEF
#  else
#    define ICE_AL_API ICE_AL_EXTERNDEF static ICE_AL_INLINEDEF
#  endif
#else
#  define ICE_AL_API ICE_AL_EXTERNDEF static ICE_AL_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_al DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_AL_TRUE     = 0,
    ICE_AL_FALSE    = -1,
} ice_al_bool;

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

///////////////////////////////////////////////////////////////////////////////////////////
// ice_al FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef void (*PFNALDOPPLERFACTORPROC) (ALfloat value);
typedef void (*PFNALSPEEDOFSOUNDPROC) (ALfloat value);
typedef void (*PFNALDISTANCEMODELPROC) (ALenum distanceModel);
typedef void (*PFNALENABLEPROC) (ALenum capability);
typedef void (*PFNALDISABLEPROC) (ALenum capability);
typedef ALboolean (*PFNALISENABLEDPROC) (ALenum capability);
typedef const ALchar * (*PFNALGETSTRINGPROC) (ALenum param);
typedef void (*PFNALGETBOOLEANVPROC) (ALenum param, ALboolean *values);
typedef void (*PFNALGETINTEGERVPROC) (ALenum param, ALint *values);
typedef void (*PFNALGETFLOATVPROC) (ALenum param, ALfloat *values);
typedef void (*PFNALGETDOUBLEVPROC) (ALenum param, ALdouble *values);
typedef ALboolean (*PFNALGETBOOLEANPROC) (ALenum param);
typedef ALint (*PFNALGETINTEGERPROC) (ALenum param);
typedef ALfloat (*PFNALGETFLOATPROC) (ALenum param);
typedef ALdouble (*PFNALGETDOUBLEPROC) (ALenum param);
typedef ALenum (*PFNALGETERRORPROC) (void);
typedef ALboolean (*PFNALISEXTENSIONPRESENTPROC) (const ALchar *extname);
typedef void* (*PFNALGETPROCADDRESSPROC) (const ALchar *fname);
typedef ALenum (*PFNALGETENUMVALUEPROC) (const ALchar *ename);
typedef void (*PFNALLISTENERFPROC) (ALenum param, ALfloat value);
typedef void (*PFNALLISTENER3FPROC) (ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
typedef void (*PFNALLISTENERFVPROC) (ALenum param, const ALfloat *values);
typedef void (*PFNALLISTENERIPROC) (ALenum param, ALint value);
typedef void (*PFNALLISTENER3IPROC) (ALenum param, ALint value1, ALint value2, ALint value3);
typedef void (*PFNALLISTENERIVPROC) (ALenum param, const ALint *values);
typedef void (*PFNALGETLISTENERFPROC) (ALenum param, ALfloat *value);
typedef void (*PFNALGETLISTENER3FPROC) (ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
typedef void (*PFNALGETLISTENERFVPROC) (ALenum param, ALfloat *values);
typedef void (*PFNALGETLISTENERIPROC) (ALenum param, ALint *value);
typedef void (*PFNALGETLISTENER3IPROC) (ALenum param, ALint *value1, ALint *value2, ALint *value3);
typedef void (*PFNALGETLISTENERIVPROC) (ALenum param, ALint *values);
typedef void (*PFNALGENSOURCESPROC) (ALsizei n, ALuint *sources);
typedef void (*PFNALDELETESOURCESPROC) (ALsizei n, const ALuint *sources);
typedef ALboolean (*PFNALISSOURCEPROC) (ALuint source);
typedef void (*PFNALSOURCEFPROC) (ALuint source, ALenum param, ALfloat value);
typedef void (*PFNALSOURCE3FPROC) (ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
typedef void (*PFNALSOURCEFVPROC) (ALuint source, ALenum param, const ALfloat *values);
typedef void (*PFNALSOURCEIPROC) (ALuint source, ALenum param, ALint value);
typedef void (*PFNALSOURCE3IPROC) (ALuint source, ALenum param, ALint value1, ALint value2, ALint value3);
typedef void (*PFNALSOURCEIVPROC) (ALuint source, ALenum param, const ALint *values);
typedef void (*PFNALGETSOURCEFPROC) (ALuint source, ALenum param, ALfloat *value);
typedef void (*PFNALGETSOURCE3FPROC) (ALuint source, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
typedef void (*PFNALGETSOURCEFVPROC) (ALuint source, ALenum param, ALfloat *values);
typedef void (*PFNALGETSOURCEIPROC) (ALuint source,  ALenum param, ALint *value);
typedef void (*PFNALGETSOURCE3IPROC) (ALuint source, ALenum param, ALint *value1, ALint *value2, ALint *value3);
typedef void (*PFNALGETSOURCEIVPROC) (ALuint source,  ALenum param, ALint *values);
typedef void (*PFNALSOURCEPLAYVPROC) (ALsizei n, const ALuint *sources);
typedef void (*PFNALSOURCESTOPVPROC) (ALsizei n, const ALuint *sources);
typedef void (*PFNALSOURCEREWINDVPROC) (ALsizei n, const ALuint *sources);
typedef void (*PFNALSOURCEPAUSEVPROC) (ALsizei n, const ALuint *sources);
typedef void (*PFNALSOURCEPLAYPROC) (ALuint source);
typedef void (*PFNALSOURCESTOPPROC) (ALuint source);
typedef void (*PFNALSOURCEREWINDPROC) (ALuint source);
typedef void (*PFNALSOURCEPAUSEPROC) (ALuint source);
typedef void (*PFNALSOURCEQUEUEBUFFERSPROC) (ALuint source, ALsizei nb, const ALuint *buffers);
typedef void (*PFNALSOURCEUNQUEUEBUFFERSPROC) (ALuint source, ALsizei nb, ALuint *buffers);
typedef void (*PFNALGENBUFFERSPROC) (ALsizei n, ALuint *buffers);
typedef void (*PFNALDELETEBUFFERSPROC) (ALsizei n, const ALuint *buffers);
typedef ALboolean (*PFNALISBUFFERPROC) (ALuint buffer);
typedef void (*PFNALBUFFERDATAPROC) (ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);
typedef void (*PFNALBUFFERFPROC) (ALuint buffer, ALenum param, ALfloat value);
typedef void (*PFNALBUFFER3FPROC) (ALuint buffer, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
typedef void (*PFNALBUFFERFVPROC) (ALuint buffer, ALenum param, const ALfloat *values);
typedef void (*PFNALBUFFERIPROC) (ALuint buffer, ALenum param, ALint value);
typedef void (*PFNALBUFFER3IPROC) (ALuint buffer, ALenum param, ALint value1, ALint value2, ALint value3);
typedef void (*PFNALBUFFERIVPROC) (ALuint buffer, ALenum param, const ALint *values);
typedef void (*PFNALGETBUFFERFPROC) (ALuint buffer, ALenum param, ALfloat *value);
typedef void (*PFNALGETBUFFER3FPROC) (ALuint buffer, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
typedef void (*PFNALGETBUFFERFVPROC) (ALuint buffer, ALenum param, ALfloat *values);
typedef void (*PFNALGETBUFFERIPROC) (ALuint buffer, ALenum param, ALint *value);
typedef void (*PFNALGETBUFFER3IPROC) (ALuint buffer, ALenum param, ALint *value1, ALint *value2, ALint *value3);
typedef void (*PFNALGETBUFFERIVPROC) (ALuint buffer, ALenum param, ALint *values);

typedef ALCcontext* (*PFNALCCREATECONTEXT)(ALCdevice *device, const ALCint *attrlist);
typedef ALCboolean (*PFNALCMAKECONTEXTCURRENT)(ALCcontext *context);
typedef void (*PFNALCPROCESSCONTEXT)(ALCcontext *context);
typedef void (*PFNALCSUSPENDCONTEXT)(ALCcontext *context);
typedef void (*PFNALCDESTROYCONTEXT)(ALCcontext *context);
typedef ALCcontext* (*PFNALCGETCURRENTCONTEXT)(void);
typedef ALCdevice* (*PFNALCGETCONTEXTSDEVICE)(ALCcontext *context);
typedef ALCdevice* (*PFNALCOPENDEVICE)(const ALCchar *devicename);
typedef ALCboolean *(PFNALCCLOSEDEVICE)(ALCdevice *device);
typedef ALCenum (*PFNALCGETERROR)(ALCdevice *device);
typedef ALCboolean (*PFNALCISEXTENSIONPRESENT)(ALCdevice *device, const ALCchar *extname);
typedef ALCvoid* (*PFNALCGETPROCADDRESS)(ALCdevice *device, const ALCchar *funcname);
typedef ALCenum (*PFNALCGETENUMVALUE)(ALCdevice *device, const ALCchar *enumname);
typedef const ALCchar* (*PFNALCGETSTRING)(ALCdevice *device, ALCenum param);
typedef void (*PFNALCGETINTEGERV)(ALCdevice *device, ALCenum param, ALCsizei size, ALCint *values);
typedef ALCdevice* (*PFNALCCAPTUREOPENDEVICE)(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize);
typedef ALCboolean (*PFNALCCAPTURECLOSEDEVICE)(ALCdevice *device);
typedef void (*PFNALCCAPTURESTART)(ALCdevice *device);
typedef void (*PFNALCCAPTURESTOP)(ALCdevice *device);
typedef void (*PFNALCCAPTURESAMPLES)(ALCdevice *device, ALCvoid *buffer, ALCsizei samples);

PFNALDOPPLERFACTORPROC alDopplerFactor;
PFNALSPEEDOFSOUNDPROC alSpeedOfSound;
PFNALDISTANCEMODELPROC alDistanceModel;
PFNALENABLEPROC alEnable;
PFNALDISABLEPROC alDisable;
PFNALISENABLEDPROC alIsEnabled;
PFNALGETSTRINGPROC alGetString;
PFNALGETBOOLEANVPROC alGetBooleanv;
PFNALGETINTEGERVPROC alGetIntegerv;
PFNALGETFLOATVPROC alGetFloatv;
PFNALGETDOUBLEVPROC alGetDoublev;
PFNALGETBOOLEANPROC alGetBoolean;
PFNALGETINTEGERPROC alGetInteger;
PFNALGETFLOATPROC alGetFloat;
PFNALGETDOUBLEPROC alGetDouble;
PFNALGETERRORPROC alGetError;
PFNALISEXTENSIONPRESENTPROC alIsExtensionPresent;
PFNALGETPROCADDRESSPROC alGetProcAddress;
PFNALGETENUMVALUEPROC alGetEnumValue;
PFNALLISTENERFPROC alListenerf;
PFNALLISTENER3FPROC alListener3f;
PFNALLISTENERFVPROC alListenerfv;
PFNALLISTENERIPROC alListeneri;
PFNALLISTENER3IPROC alListener3i;
PFNALLISTENERIVPROC alListeneriv;
PFNALGETLISTENERFPROC alGetListenerf;
PFNALGETLISTENER3FPROC alGetListener3f;
PFNALGETLISTENERFVPROC alGetListenerfv;
PFNALGETLISTENERIPROC alGetListeneri;
PFNALGETLISTENER3IPROC alGetListener3i;
PFNALGETLISTENERIVPROC alGetListeneriv;
PFNALGENSOURCESPROC alGenSources;
PFNALDELETESOURCESPROC alDeleteSources;
PFNALISSOURCEPROC alIsSource;
PFNALSOURCEFPROC alSourcef;
PFNALSOURCE3FPROC alSource3f;
PFNALSOURCEFVPROC alSourcefv;
PFNALSOURCEIPROC alSourcei;
PFNALSOURCE3IPROC alSource3i;
PFNALSOURCEIVPROC alSourceiv;
PFNALGETSOURCEFPROC alGetSourcef;
PFNALGETSOURCE3FPROC alGetSource3f;
PFNALGETSOURCEFVPROC alGetSourcefv;
PFNALGETSOURCEIPROC alGetSourcei;
PFNALGETSOURCE3IPROC alGetSource3i;
PFNALGETSOURCEIVPROC alGetSourceiv;
PFNALSOURCEPLAYVPROC alSourcePlayv;
PFNALSOURCESTOPVPROC alSourceStopv;
PFNALSOURCEREWINDVPROC alSourceRewindv;
PFNALSOURCEPAUSEVPROC alSourcePausev;
PFNALSOURCEPLAYPROC alSourcePlay;
PFNALSOURCESTOPPROC alSourceStop;
PFNALSOURCEREWINDPROC alSourceRewind;
PFNALSOURCEPAUSEPROC alSourcePause;
PFNALSOURCEQUEUEBUFFERSPROC alSourceQueueBuffers;
PFNALSOURCEUNQUEUEBUFFERSPROC alSourceUnqueueBuffers;
PFNALGENBUFFERSPROC alGenBuffers;
PFNALDELETEBUFFERSPROC alDeleteBuffers;
PFNALISBUFFERPROC alIsBuffer;
PFNALBUFFERDATAPROC alBufferData;
PFNALBUFFERFPROC alBufferf;
PFNALBUFFER3FPROC alBuffer3f;
PFNALBUFFERFVPROC alBufferfv;
PFNALBUFFERIPROC alBufferi;
PFNALBUFFER3IPROC alBuffer3i;
PFNALBUFFERIVPROC alBufferiv;
PFNALGETBUFFERFPROC alGetBufferf;
PFNALGETBUFFER3FPROC alGetBuffer3f;
PFNALGETBUFFERFVPROC alGetBufferfv;
PFNALGETBUFFERIPROC alGetBufferi;
PFNALGETBUFFER3IPROC alGetBuffer3i;
PFNALGETBUFFERIVPROC alGetBufferiv;

PFNALCCREATECONTEXT alcCreateContext;
PFNALCMAKECONTEXTCURRENT alcMakeContextCurrent;
PFNALCPROCESSCONTEXT alcProcessContext;
PFNALCSUSPENDCONTEXT alcSuspendContext;
PFNALCDESTROYCONTEXT alcDestroyContext;
PFNALCGETCURRENTCONTEXT alcGetCurrentContext;
PFNALCGETCONTEXTSDEVICE alcGetContextsDevice;
PFNALCOPENDEVICE alcOpenDevice;
PFNALCCLOSEDEVICE alcCloseDevice;
PFNALCGETERROR alcGetError;
PFNALCISEXTENSIONPRESENT alcIsExtensionPresent;
PFNALCGETPROCADDRESS alcGetProcAddress;
PFNALCGETENUMVALUE alcGetEnumValue;
PFNALCGETSTRING alcGetString;
PFNALCGETINTEGERV alcGetIntegerv;
PFNALCCAPTUREOPENDEVICE alcCaptureOpenDevice;
PFNALCCAPTURECLOSEDEVICE alcCaptureCloseDevice;
PFNALCCAPTURESTART alcCaptureStart;
PFNALCCAPTURESTOP alcCaptureStop;
PFNALCCAPTURESAMPLES alcCaptureSamples;

void* oal_lib;
void* ice_al_load(void);
void* ice_al_proc(char* name);
ice_al_bool ice_al_close(void);
ice_al_bool ice_al_init(void);

#if defined(_WIN32) || defined(WIN32)
const char* oal_libname = "OpenAL32.dll";

#elif defined(_WIN64) || defined(WIN64)
const char* oal_libname = "OpenAL32.dll";

#elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__DARWIN) || defined(_DARWIN)
const char* oal_libname = "libopenal.dylib";

#else
const char* oal_libname = "libopenal.so";

#endif

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_al IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_AL_IMPL)
#include <stdio.h>

#if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox)
#  include <windows.h>
#  define ICE_AL_PLATFORM_WINDOWS
#elif defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU) || defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
#  include <image.h>
#  define ICE_AL_PLATFORM_BEOS
#else
#  include <dlfcn.h>
#  define ICE_AL_PLATFORM_UNIX
#endif

void* ice_al_load(void) {
#if defined(ICE_AL_PLATFORM_WINDOWS)
return (HMODULE)LoadLibraryA(steamworks_libname);

#elif defined(ICE_AL_PLATFORM_BEOS)
return (image_id)load_add_on(steamworks_libname);

#elif defined(ICE_AL_PLATFORM_UNIX)
return dlopen(steamworks_libname, RTLD_LAZY | RTLD_GLOBAL);

#endif
}

void* ice_al_proc(char* name) {
#if defined(ICE_AL_PLATFORM_WINDOWS)
return GetProcAddress((HMODULE)steam_lib, name);

#elif defined(ICE_AL_PLATFORM_BEOS)
void* addr;

if (get_image_symbol((image_id)steam_lib, name, B_SYMBOL_TYPE_ANY, &addr) == B_OK) {
    return addr;
}

#elif defined(ICE_AL_PLATFORM_UNIX)
return dlsym(steam_lib, name);

#endif
}

ice_al_bool ice_al_close(void) {
#if defined(ICE_AL_PLATFORM_WINDOWS)
return (FreeLibrary((HMODULE)steam_lib) == TRUE) ? ICE_AL_TRUE : ICE_AL_FALSE;

#elif defined(ICE_AL_PLATFORM_BEOS)
return (unload_add_on((image_id)steam_lib) == B_OK) ? ICE_AL_TRUE : ICE_AL_FALSE;

#elif defined(ICE_AL_PLATFORM_UNIX)
return (dlclose(steam_lib) == 0) ? ICE_AL_TRUE : ICE_AL_FALSE;

#endif
}

ice_al_bool ice_oal_init(void) {
    oal_lib = ice_al_load();
    if (oal_lib == NULL) return ICE_AL_FALSE;
    
    alDopplerFactor = (PFNALDOPPLERFACTORPROC) ice_al_proc("alDopplerFactor");
    alSpeedOfSound = (PFNALSPEEDOFSOUNDPROC) ice_al_proc("alSpeedOfSound");
    alDistanceModel = (PFNALDISTANCEMODELPROC) ice_al_proc("alDistanceModel");
    alEnable = (PFNALENABLEPROC) ice_al_proc("alEnable");
    alDisable = (PFNALDISABLEPROC) ice_al_proc("alDisable");
    alIsEnabled = (PFNALISENABLEDPROC) ice_al_proc("alIsEnabled");
    alGetString = (PFNALGETSTRINGPROC) ice_al_proc("alGetString");
    alGetBooleanv = (PFNALGETBOOLEANVPROC) ice_al_proc("alGetBooleanv");
    alGetIntegerv = (PFNALGETINTEGERVPROC) ice_al_proc("alGetIntegerv");
    alGetFloatv = (PFNALGETFLOATVPROC) ice_al_proc("alGetFloatv");
    alGetDoublev = (PFNALGETDOUBLEVPROC) ice_al_proc("alGetDoublev");
    alGetBoolean = (PFNALGETBOOLEANPROC) ice_al_proc("alGetBoolean");
    alGetInteger = (PFNALGETINTEGERPROC) ice_al_proc("alGetInteger");
    alGetFloat = (PFNALGETFLOATPROC) ice_al_proc("alGetFloat");
    alGetDouble = (PFNALGETDOUBLEPROC) ice_al_proc("alGetDouble");
    alGetError = (PFNALGETERRORPROC) ice_al_proc("alGetError");
    alIsExtensionPresent = (PFNALISEXTENSIONPRESENTPROC) ice_al_proc("alIsExtensionPresent");
    alGetProcAddress = (PFNALGETPROCADDRESSPROC) ice_al_proc("alGetProcAddress");
    alGetEnumValue = (PFNALGETENUMVALUEPROC) ice_al_proc("alGetEnumValue");
    alListenerf = (PFNALLISTENERFPROC) ice_al_proc("alListenerf");
    alListener3f = (PFNALLISTENER3FPROC) ice_al_proc("alListener3f");
    alListenerfv = (PFNALLISTENERFVPROC) ice_al_proc("alListenerfv");
    alListeneri = (PFNALLISTENERIPROC) ice_al_proc("alListeneri");
    alListener3i = (PFNALLISTENER3IPROC) ice_al_proc("alListener3i");
    alListeneriv = (PFNALLISTENERIVPROC) ice_al_proc("alListeneriv");
    alGetListenerf = (PFNALGETLISTENERFPROC) ice_al_proc("alGetListenerf");
    alGetListener3f = (PFNALGETLISTENER3FPROC) ice_al_proc("alGetListener3f");
    alGetListenerfv = (PFNALGETLISTENERFVPROC) ice_al_proc("alGetListenerfv");
    alGetListeneri = (PFNALGETLISTENERIPROC) ice_al_proc("alGetListeneri");
    alGetListener3i = (PFNALGETLISTENER3IPROC) ice_al_proc("alGetListener3i");
    alGetListeneriv = (PFNALGETLISTENERIVPROC) ice_al_proc("alGetListeneriv");
    alGenSources = (PFNALGENSOURCESPROC) ice_al_proc("alGenSources");
    alDeleteSources = (PFNALDELETESOURCESPROC) ice_al_proc("alDeleteSources");
    alIsSource = (PFNALISSOURCEPROC) ice_al_proc("alIsSource");
    alSourcef = (PFNALSOURCEFPROC) ice_al_proc("alSourcef");
    alSource3f = (PFNALSOURCE3FPROC) ice_al_proc("alSource3f");
    alSourcefv = (PFNALSOURCEFVPROC) ice_al_proc("alSourcefv");
    alSourcei = (PFNALSOURCEIPROC) ice_al_proc("alSourcei");
    alSource3i = (PFNALSOURCE3IPROC) ice_al_proc("alSource3i");
    alSourceiv = (PFNALSOURCEIVPROC) ice_al_proc("alSourceiv");
    alGetSourcef = (PFNALGETSOURCEFPROC) ice_al_proc("alGetSourcef");
    alGetSource3f = (PFNALGETSOURCE3FPROC) ice_al_proc("alGetSource3f");
    alGetSourcefv = (PFNALGETSOURCEFVPROC) ice_al_proc("alGetSourcefv");
    alGetSourcei = (PFNALGETSOURCEIPROC) ice_al_proc("alGetSourcei");
    alGetSource3i = (PFNALGETSOURCE3IPROC) ice_al_proc("alGetSource3i");
    alGetSourceiv = (PFNALGETSOURCEIVPROC) ice_al_proc("alGetSourceiv");
    alSourcePlayv = (PFNALSOURCEPLAYVPROC) ice_al_proc("alSourcePlayv");
    alSourceStopv = (PFNALSOURCESTOPVPROC) ice_al_proc("alSourceStopv");
    alSourceRewindv = (PFNALSOURCEREWINDVPROC) ice_al_proc("alSourceRewindv");
    alSourcePausev = (PFNALSOURCEPAUSEVPROC) ice_al_proc("alSourcePausev");
    alSourcePlay = (PFNALSOURCEPLAYPROC) ice_al_proc("alSourcePlay");
    alSourceStop = (PFNALSOURCESTOPPROC) ice_al_proc("alSourceStop");
    alSourceRewind = (PFNALSOURCEREWINDPROC) ice_al_proc("alSourceRewind");
    alSourcePause = (PFNALSOURCEPAUSEPROC) ice_al_proc("alSourcePause");
    alSourceQueueBuffers = (PFNALSOURCEQUEUEBUFFERSPROC) ice_al_proc("alSourceQueueBuffers");
    alSourceUnqueueBuffers = (PFNALSOURCEUNQUEUEBUFFERSPROC) ice_al_proc("alSourceUnqueueBuffers");
    alGenBuffers = (PFNALGENBUFFERSPROC) ice_al_proc("alGenBuffers");
    alDeleteBuffers = (PFNALDELETEBUFFERSPROC) ice_al_proc("alDeleteBuffers");
    alIsBuffer = (PFNALISBUFFERPROC) ice_al_proc("alIsBuffer");
    alBufferData = (PFNALBUFFERDATAPROC) ice_al_proc("alBufferData");
    alBufferf = (PFNALBUFFERFPROC) ice_al_proc("alBufferf");
    alBuffer3f = (PFNALBUFFER3FPROC) ice_al_proc("alBuffer3f");
    alBufferfv = (PFNALBUFFERFVPROC) ice_al_proc("alBufferfv");
    alBufferi = (PFNALBUFFERIPROC) ice_al_proc("alBufferi");
    alBuffer3i = (PFNALBUFFER3IPROC) ice_al_proc("alBuffer3i");
    alBufferiv = (PFNALBUFFERIVPROC) ice_al_proc("alBufferiv");
    alGetBufferf = (PFNALGETBUFFERFPROC) ice_al_proc("alGetBufferf");
    alGetBuffer3f = (PFNALGETBUFFER3FPROC) ice_al_proc("alGetBuffer3f");
    alGetBufferfv = (PFNALGETBUFFERFVPROC) ice_al_proc("alGetBufferfv");
    alGetBufferi = (PFNALGETBUFFERIPROC) ice_al_proc("alGetBufferi");
    alGetBuffer3i = (PFNALGETBUFFER3IPROC) ice_al_proc("alGetBuffer3i");
    alGetBufferiv = (PFNALGETBUFFERIVPROC) ice_al_proc("alGetBufferiv");
    
    alcCreateContext = (PFNALCCREATECONTEXT) ice_al_proc("alcCreateContext");
    alcMakeContextCurrent = (PFNALCMAKECONTEXTCURRENT) ice_al_proc("alcMakeContextCurrent");
    alcProcessContext = (PFNALCPROCESSCONTEXT) ice_al_proc("alcProcessContext");
    alcSuspendContext = (PFNALCSUSPENDCONTEXT) ice_al_proc("alcSuspendContext");
    alcDestroyContext = (PFNALCDESTROYCONTEXT) ice_al_proc("alcDestroyContext");
    alcGetCurrentContext = (PFNALCGETCURRENTCONTEXT) ice_al_proc("alcGetCurrentContext");
    alcGetContextsDevice = (PFNALCGETCONTEXTSDEVICE) ice_al_proc("alcGetContextsDevice");
    alcOpenDevice = (PFNALCOPENDEVICE) ice_al_proc("alcOpenDevice");
    alcCloseDevice = (PFNALCCLOSEDEVICE) ice_al_proc("alcCloseDevice");
    alcGetError = (PFNALCGETERROR) ice_al_proc("alcGetError");
    alcIsExtensionPresent = (PFNALCISEXTENSIONPRESENT) ice_al_proc("alcIsExtensionPresent");
    alcGetProcAddress = (PFNALCGETPROCADDRESS) ice_al_proc("alcGetProcAddress");
    alcGetEnumValue = (PFNALCGETENUMVALUE) ice_al_proc("alcGetEnumValue");
    alcGetString = (PFNALCGETSTRING) ice_al_proc("alcGetString");
    alcGetIntegerv = (PFNALCGETINTEGERV) ice_al_proc("alcGetIntegerv");
    alcCaptureOpenDevice = (PFNALCCAPTUREOPENDEVICE) ice_al_proc("alcCaptureOpenDevice");
    alcCaptureCloseDevice = (PFNALCCAPTURECLOSEDEVICE) ice_al_proc("alcCaptureCloseDevice");
    alcCaptureStart = (PFNALCCAPTURESTART) ice_al_proc("alcCaptureStart");
    alcCaptureStop = (PFNALCCAPTURESTOP) ice_al_proc("alcCaptureStop");
    alcCaptureSamples = (PFNALCCAPTURESAMPLES) ice_al_proc("alcCaptureSamples");
    
    return ICE_AL_TRUE;
}

#endif  // ICE_AL_IMPL
#endif  // ICE_AL_H
