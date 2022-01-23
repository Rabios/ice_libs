local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef

ffi_cdef([[
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

enum {
    AL_NONE                                  = 0,
    AL_FALSE                                 = 0,
    AL_TRUE                                  = 1,
    AL_SOURCE_RELATIVE                       = 0x202,
    AL_CONE_INNER_ANGLE                      = 0x1001,
    AL_CONE_OUTER_ANGLE                      = 0x1002,
    AL_PITCH                                 = 0x1003,
    AL_POSITION                              = 0x1004,
    AL_DIRECTION                             = 0x1005,
    AL_VELOCITY                              = 0x1006,
    AL_LOOPING                               = 0x1007,
    AL_BUFFER                                = 0x1009,
    AL_GAIN                                  = 0x100A,
    AL_MIN_GAIN                              = 0x100D,
    AL_MAX_GAIN                              = 0x100E,
    AL_ORIENTATION                           = 0x100F,
    AL_SOURCE_STATE                          = 0x1010,
    AL_INITIAL                               = 0x1011,
    AL_PLAYING                               = 0x1012,
    AL_PAUSED                                = 0x1013,
    AL_STOPPED                               = 0x1014,
    AL_BUFFERS_QUEUED                        = 0x1015,
    AL_BUFFERS_PROCESSED                     = 0x1016,
    AL_REFERENCE_DISTANCE                    = 0x1020,
    AL_ROLLOFF_FACTOR                        = 0x1021,
    AL_CONE_OUTER_GAIN                       = 0x1022,
    AL_MAX_DISTANCE                          = 0x1023,
    AL_SEC_OFFSET                            = 0x1024,
    AL_SAMPLE_OFFSET                         = 0x1025,
    AL_BYTE_OFFSET                           = 0x1026,
    AL_SOURCE_TYPE                           = 0x1027,
    AL_STATIC                                = 0x1028,
    AL_STREAMING                             = 0x1029,
    AL_UNDETERMINED                          = 0x1030,
    AL_FORMAT_MONO8                          = 0x1100,
    AL_FORMAT_MONO16                         = 0x1101,
    AL_FORMAT_STEREO8                        = 0x1102,
    AL_FORMAT_STEREO16                       = 0x1103,
    AL_FREQUENCY                             = 0x2001,
    AL_BITS                                  = 0x2002,
    AL_CHANNELS                              = 0x2003,
    AL_SIZE                                  = 0x2004,
    AL_UNUSED                                = 0x2010,
    AL_PENDING                               = 0x2011,
    AL_PROCESSED                             = 0x2012,
    AL_NO_ERROR                              = 0,
    AL_INVALID_NAME                          = 0xA001,
    AL_INVALID_ENUM                          = 0xA002,
    AL_INVALID_VALUE                         = 0xA003,
    AL_INVALID_OPERATION                     = 0xA004,
    AL_OUT_OF_MEMORY                         = 0xA005,
    AL_VENDOR                                = 0xB001,
    AL_VERSION                               = 0xB002,
    AL_RENDERER                              = 0xB003,
    AL_EXTENSIONS                            = 0xB004,
    AL_DOPPLER_FACTOR                        = 0xC000,
    AL_DOPPLER_VELOCITY                      = 0xC001,
    AL_SPEED_OF_SOUND                        = 0xC003,
    AL_DISTANCE_MODEL                        = 0xD000,
    AL_INVERSE_DISTANCE                      = 0xD001,
    AL_INVERSE_DISTANCE_CLAMPED              = 0xD002,
    AL_LINEAR_DISTANCE                       = 0xD003,
    AL_LINEAR_DISTANCE_CLAMPED               = 0xD004,
    AL_EXPONENT_DISTANCE                     = 0xD005,
    AL_EXPONENT_DISTANCE_CLAMPED             = 0xD006,

    ALC_VERSION_0_1                          = 1,
    ALC_INVALID                              = 0,
    ALC_FALSE                                = 0,
    ALC_TRUE                                 = 1,
    ALC_FREQUENCY                            = 0x1007,
    ALC_REFRESH                              = 0x1008,
    ALC_SYNC                                 = 0x1009,
    ALC_MONO_SOURCES                         = 0x1010,
    ALC_STEREO_SOURCES                       = 0x1011,
    ALC_NO_ERROR                             = 0,
    ALC_INVALID_DEVICE                       = 0xA001,
    ALC_INVALID_CONTEXT                      = 0xA002,
    ALC_INVALID_ENUM                         = 0xA003,
    ALC_INVALID_VALUE                        = 0xA004,
    ALC_OUT_OF_MEMORY                        = 0xA005,
    ALC_MAJOR_VERSION                        = 0x1000,
    ALC_MINOR_VERSION                        = 0x1001,
    ALC_ATTRIBUTES_SIZE                      = 0x1002,
    ALC_ALL_ATTRIBUTES                       = 0x1003,
    ALC_DEFAULT_DEVICE_SPECIFIER             = 0x1004,
    ALC_DEVICE_SPECIFIER                     = 0x1005,
    ALC_EXTENSIONS                           = 0x1006,
    ALC_EXT_CAPTURE                          = 1,
    ALC_CAPTURE_DEVICE_SPECIFIER             = 0x310,
    ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER     = 0x311,
    ALC_CAPTURE_SAMPLES                      = 0x312,
    ALC_ENUMERATE_ALL_EXT                    = 1,
    ALC_DEFAULT_ALL_DEVICES_SPECIFIER        = 0x1012,
    ALC_ALL_DEVICES_SPECIFIER                = 0x1013
};

/* ============================= Functions (OpenAL API) ============================= */

void (*alDopplerFactor)(ALfloat value);
void (*alSpeedOfSound)(ALfloat value);
void (*alDistanceModel)(ALenum distanceModel);
void (*alEnable)(ALenum capability);
void (*alDisable)(ALenum capability);
ALboolean (*alIsEnabled)(ALenum capability);
const ALchar * (*alGetString)(ALenum param);
void (*alGetBooleanv)(ALenum param, ALboolean *values);
void (*alGetIntegerv)(ALenum param, ALint *values);
void (*alGetFloatv)(ALenum param, ALfloat *values);
void (*alGetDoublev)(ALenum param, ALdouble *values);
ALboolean (*alGetBoolean)(ALenum param);
ALint (*alGetInteger)(ALenum param);
ALfloat (*alGetFloat)(ALenum param);
ALdouble (*alGetDouble)(ALenum param);
ALenum (*alGetError)(void);
ALboolean (*alIsExtensionPresent)(const ALchar *extname);
void* (*alGetProcAddress)(const ALchar *fname);
ALenum (*alGetEnumValue)(const ALchar *ename);
void (*alListenerf)(ALenum param, ALfloat value);
void (*alListener3f)(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
void (*alListenerfv)(ALenum param, const ALfloat *values);
void (*alListeneri)(ALenum param, ALint value);
void (*alListener3i)(ALenum param, ALint value1, ALint value2, ALint value3);
void (*alListeneriv)(ALenum param, const ALint *values);
void (*alGetListenerf)(ALenum param, ALfloat *value);
void (*alGetListener3f)(ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
void (*alGetListenerfv)(ALenum param, ALfloat *values);
void (*alGetListeneri)(ALenum param, ALint *value);
void (*alGetListener3i)(ALenum param, ALint *value1, ALint *value2, ALint *value3);
void (*alGetListeneriv)(ALenum param, ALint *values);
void (*alGenSources)(ALsizei n, ALuint *sources);
void (*alDeleteSources)(ALsizei n, const ALuint *sources);
ALboolean (*alIsSource)(ALuint source);
void (*alSourcef)(ALuint source, ALenum param, ALfloat value);
void (*alSource3f)(ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
void (*alSourcefv)(ALuint source, ALenum param, const ALfloat *values);
void (*alSourcei)(ALuint source, ALenum param, ALint value);
void (*alSource3i)(ALuint source, ALenum param, ALint value1, ALint value2, ALint value3);
void (*alSourceiv)(ALuint source, ALenum param, const ALint *values);
void (*alGetSourcef)(ALuint source, ALenum param, ALfloat *value);
void (*alGetSource3f)(ALuint source, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
void (*alGetSourcefv)(ALuint source, ALenum param, ALfloat *values);
void (*alGetSourcei)(ALuint source,  ALenum param, ALint *value);
void (*alGetSource3i)(ALuint source, ALenum param, ALint *value1, ALint *value2, ALint *value3);
void (*alGetSourceiv)(ALuint source,  ALenum param, ALint *values);
void (*alSourcePlayv)(ALsizei n, const ALuint *sources);
void (*alSourceStopv)(ALsizei n, const ALuint *sources);
void (*alSourceRewindv)(ALsizei n, const ALuint *sources);
void (*alSourcePausev)(ALsizei n, const ALuint *sources);
void (*alSourcePlay)(ALuint source);
void (*alSourceStop)(ALuint source);
void (*alSourceRewind)(ALuint source);
void (*alSourcePause)(ALuint source);
void (*alSourceQueueBuffers)(ALuint source, ALsizei nb, const ALuint *buffers);
void (*alSourceUnqueueBuffers)(ALuint source, ALsizei nb, ALuint *buffers);
void (*alGenBuffers)(ALsizei n, ALuint *buffers);
void (*alDeleteBuffers)(ALsizei n, const ALuint *buffers);
ALboolean (*alIsBuffer)(ALuint buffer);
void (*alBufferData)(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);
void (*alBufferf)(ALuint buffer, ALenum param, ALfloat value);
void (*alBuffer3f)(ALuint buffer, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
void (*alBufferfv)(ALuint buffer, ALenum param, const ALfloat *values);
void (*alBufferi)(ALuint buffer, ALenum param, ALint value);
void (*alBuffer3i)(ALuint buffer, ALenum param, ALint value1, ALint value2, ALint value3);
void (*alBufferiv)(ALuint buffer, ALenum param, const ALint *values);
void (*alGetBufferf)(ALuint buffer, ALenum param, ALfloat *value);
void (*alGetBuffer3f)(ALuint buffer, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
void (*alGetBufferfv)(ALuint buffer, ALenum param, ALfloat *values);
void (*alGetBufferi)(ALuint buffer, ALenum param, ALint *value);
void (*alGetBuffer3i)(ALuint buffer, ALenum param, ALint *value1, ALint *value2, ALint *value3);
void (*alGetBufferiv)(ALuint buffer, ALenum param, ALint *values);

ALCcontext* (*alcCreateContext)(ALCdevice *device, const ALCint *attrlist);
ALCboolean (*alcMakeContextCurrent)(ALCcontext *context);
void (*alcProcessContext)(ALCcontext *context);
void (*alcSuspendContext)(ALCcontext *context);
void (*alcDestroyContext)(ALCcontext *context);
ALCcontext* (*alcGetCurrentContext)(void);
ALCcontext* (*alcGetContextsDevice)(ALCcontext *context);
ALCdevice* (*alcOpenDevice)(const ALCchar *devicename);
ALCboolean (*alcCloseDevice)(ALCdevice *device);
ALCenum (*alcGetError)(ALCdevice *device);
ALCboolean (*alcIsExtensionPresent)(ALCdevice *device, const ALCchar *extname);
ALCvoid* (*alcGetProcAddress)(ALCdevice *device, const ALCchar *funcname);
ALCenum (*alcGetEnumValue)(ALCdevice *device, const ALCchar *enumname);
const ALCchar* (*alcGetString)(ALCdevice *device, ALCenum param);
void (*alcGetIntegerv)(ALCdevice *device, ALCenum param, ALCsizei size, ALCint *values);
ALCdevice* (*alcCaptureOpenDevice)(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize);
ALCboolean (*alcCaptureCloseDevice)(ALCdevice *device);
void (*alcCaptureStart)(ALCdevice *device);
void (*alcCaptureStop)(ALCdevice *device);
void (*alcCaptureSamples)(ALCdevice *device, ALCvoid* buffer, ALCsizei samples);

/* ============================= Data Types ============================= */

/* Handle, Type definition for void* for symbols loaded from shared libs */
typedef void* ice_al_handle;

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_al_bool {
    ICE_AL_FALSE    = -1,
    ICE_AL_TRUE     = 0
} ice_al_bool;

/* ============================= Functions ============================= */

/* [INTERNAL] Loads symbol from loaded OpenAL shared library, Which can be casted to a function to call */
ice_al_handle ice_al_proc(const char *symbol);

/* Loads OpenAL API from shared library path (ex. openal32.dll on Windows), Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ice_al_bool ice_al_load(const char *path);

/* Unloads OpenAL API, Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ice_al_bool ice_al_unload(void);
]])

return ffi_load("ice_al")
