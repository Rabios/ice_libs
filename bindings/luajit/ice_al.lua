local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef
local _setmetatable = setmetatable

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

void alDopplerFactor(ALfloat value);
void alSpeedOfSound(ALfloat value);
void alDistanceModel(ALenum distanceModel);
void alEnable(ALenum capability);
void alDisable(ALenum capability);
ALboolean alIsEnabled(ALenum capability);
const ALchar * alGetString(ALenum param);
void alGetBooleanv(ALenum param, ALboolean *values);
void alGetIntegerv(ALenum param, ALint *values);
void alGetFloatv(ALenum param, ALfloat *values);
void alGetDoublev(ALenum param, ALdouble *values);
ALboolean alGetBoolean(ALenum param);
ALint alGetInteger(ALenum param);
ALfloat alGetFloat(ALenum param);
ALdouble alGetDouble(ALenum param);
ALenum alGetError(void);
ALboolean alIsExtensionPresent(const ALchar *extname);
void* alGetProcAddress(const ALchar *fname);
ALenum alGetEnumValue(const ALchar *ename);
void alListenerf(ALenum param, ALfloat value);
void alListener3f(ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
void alListenerfv(ALenum param, const ALfloat *values);
void alListeneri(ALenum param, ALint value);
void alListener3i(ALenum param, ALint value1, ALint value2, ALint value3);
void alListeneriv(ALenum param, const ALint *values);
void alGetListenerf(ALenum param, ALfloat *value);
void alGetListener3f(ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
void alGetListenerfv(ALenum param, ALfloat *values);
void alGetListeneri(ALenum param, ALint *value);
void alGetListener3i(ALenum param, ALint *value1, ALint *value2, ALint *value3);
void alGetListeneriv(ALenum param, ALint *values);
void alGenSources(ALsizei n, ALuint *sources);
void alDeleteSources(ALsizei n, const ALuint *sources);
ALboolean alIsSource(ALuint source);
void alSourcef(ALuint source, ALenum param, ALfloat value);
void alSource3f(ALuint source, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
void alSourcefv(ALuint source, ALenum param, const ALfloat *values);
void alSourcei(ALuint source, ALenum param, ALint value);
void alSource3i(ALuint source, ALenum param, ALint value1, ALint value2, ALint value3);
void alSourceiv(ALuint source, ALenum param, const ALint *values);
void alGetSourcef(ALuint source, ALenum param, ALfloat *value);
void alGetSource3f(ALuint source, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
void alGetSourcefv(ALuint source, ALenum param, ALfloat *values);
void alGetSourcei(ALuint source,  ALenum param, ALint *value);
void alGetSource3i(ALuint source, ALenum param, ALint *value1, ALint *value2, ALint *value3);
void alGetSourceiv(ALuint source,  ALenum param, ALint *values);
void alSourcePlayv(ALsizei n, const ALuint *sources);
void alSourceStopv(ALsizei n, const ALuint *sources);
void alSourceRewindv(ALsizei n, const ALuint *sources);
void alSourcePausev(ALsizei n, const ALuint *sources);
void alSourcePlay(ALuint source);
void alSourceStop(ALuint source);
void alSourceRewind(ALuint source);
void alSourcePause(ALuint source);
void alSourceQueueBuffers(ALuint source, ALsizei nb, const ALuint *buffers);
void alSourceUnqueueBuffers(ALuint source, ALsizei nb, ALuint *buffers);
void alGenBuffers(ALsizei n, ALuint *buffers);
void alDeleteBuffers(ALsizei n, const ALuint *buffers);
ALboolean alIsBuffer(ALuint buffer);
void alBufferData(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);
void alBufferf(ALuint buffer, ALenum param, ALfloat value);
void alBuffer3f(ALuint buffer, ALenum param, ALfloat value1, ALfloat value2, ALfloat value3);
void alBufferfv(ALuint buffer, ALenum param, const ALfloat *values);
void alBufferi(ALuint buffer, ALenum param, ALint value);
void alBuffer3i(ALuint buffer, ALenum param, ALint value1, ALint value2, ALint value3);
void alBufferiv(ALuint buffer, ALenum param, const ALint *values);
void alGetBufferf(ALuint buffer, ALenum param, ALfloat *value);
void alGetBuffer3f(ALuint buffer, ALenum param, ALfloat *value1, ALfloat *value2, ALfloat *value3);
void alGetBufferfv(ALuint buffer, ALenum param, ALfloat *values);
void alGetBufferi(ALuint buffer, ALenum param, ALint *value);
void alGetBuffer3i(ALuint buffer, ALenum param, ALint *value1, ALint *value2, ALint *value3);
void alGetBufferiv(ALuint buffer, ALenum param, ALint *values);

ALCcontext* alcCreateContext(ALCdevice *device, const ALCint *attrlist);
ALCboolean alcMakeContextCurrent(ALCcontext *context);
void alcProcessContext(ALCcontext *context);
void alcSuspendContext(ALCcontext *context);
void alcDestroyContext(ALCcontext *context);
ALCcontext* alcGetCurrentContext(void);
ALCcontext* alcGetContextsDevice(ALCcontext *context);
ALCdevice* alcOpenDevice(const ALCchar *devicename);
ALCboolean alcCloseDevice(ALCdevice *device);
ALCenum alcGetError(ALCdevice *device);
ALCboolean alcIsExtensionPresent(ALCdevice *device, const ALCchar *extname);
ALCvoid* alcGetProcAddress(ALCdevice *device, const ALCchar *funcname);
ALCenum alcGetEnumValue(ALCdevice *device, const ALCchar *enumname);
ALCchar* alcGetString(ALCdevice *device, ALCenum param);
void alcGetIntegerv(ALCdevice *device, ALCenum param, ALCsizei size, ALCint *values);
ALCdevice* alcCaptureOpenDevice(const ALCchar *devicename, ALCuint frequency, ALCenum format, ALCsizei buffersize);
ALCboolean alcCaptureCloseDevice(ALCdevice *device);
void alcCaptureStart(ALCdevice *device);
void alcCaptureStop(ALCdevice *device);
void alcCaptureSamples(ALCdevice *device, ALCvoid* buffer, ALCsizei samples);

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
ice_al_handle ice_al_proc(const char *symbol);

/* Loads OpenAL API from shared library path (ex. openal32.dll on Windows), Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ice_al_bool ice_al_load(const char *path);

/* Unloads OpenAL API, Returns ICE_AL_TRUE on success or ICE_AL_FALSE on failure */
ice_al_bool ice_al_unload(void);
]])

local lib = ffi_load("ice_al")
_setmetatable(_G, { __index = lib })
