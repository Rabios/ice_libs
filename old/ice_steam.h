// Written by Rabia Alhaffar in 4/April/2021
// ice_steam.h
// Single-Header Cross-Platform C library for working with Steamworks API!
// Updated: 19/June/2021

///////////////////////////////////////////////////////////////////////////////////////////
// ice_steam.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_steam is cross-platform single-header C library for working with Steamworks API!

Works on Windows, OSX, Linux, Android, iOS, Haiku, BeOS! (Linux-based platforms could work...)

[2] IMPLEMENTATION:
Windows             -> LoadLibrary, FreeLibrary, GetProcAddress
Haiku/BeOS          -> load_add_on, unload_add_on, get_image_symbol
Elsewhere           -> dlopen, dlsym, dlclose

[3] USAGE:
Define ICE_STEAM_IMPL then include ice_steam.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_steam
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_steam by possibly one of following things:
//
// 1. Test ice_steam on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

#ifndef ICE_STEAM_H
#define ICE_STEAM_H

#include <stdint.h>
#include <stdbool.h>

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
#  if defined(ICE_STEAM_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_STEAM_CALLCONV_FASTCALL)
#    define ICE_STEAM_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_STEAM_CALLCONV_STDCALL)
#    define ICE_STEAM_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_STEAM_CALLCONV_CDECL)
#    define ICE_STEAM_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_STEAM_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_STEAM_CALLCONV_VECTORCALL)
#    define ICE_STEAM_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_STEAM_CALLCONV_FASTCALL)
#    define ICE_STEAM_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_STEAM_CALLCONV_STDCALL)
#    define ICE_STEAM_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_STEAM_CALLCONV_CDECL)
#    define ICE_STEAM_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_STEAM_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_STEAM_CALLCONV_VECTORCALL)
#    define ICE_STEAM_CALLCONV __vectorcall
#  elif defined(ICE_STEAM_CALLCONV_FASTCALL)
#    define ICE_STEAM_CALLCONV __fastcall
#  elif defined(ICE_STEAM_CALLCONV_STDCALL)
#    define ICE_STEAM_CALLCONV __stdcall
#  elif defined(ICE_STEAM_CALLCONV_CDECL)
#    define ICE_STEAM_CALLCONV __cdecl
#  else
#    define ICE_STEAM_CALLCONV
#  endif
#else
#  define ICE_STEAM_CALLCONV
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_STEAM_EXTERN) && defined(ICE_STEAM_STATIC))
#  define ICE_STEAM_EXTERN
#endif

#if defined(ICE_STEAM_EXTERN)
#  define ICE_STEAM_APIDEF extern
#elif defined(ICE_STEAM_STATIC)
#  define ICE_STEAM_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_STEAM_INLINE to enable inline functionality.
#if defined(ICE_STEAM_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_STEAM_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_STEAM_INLINEDEF inline
#  endif
#else
#  define ICE_STEAM_INLINEDEF
#endif

// Autodetect platform if not defined!
// If no platform defined, This definition will define itself.
#if !defined(ICE_STEAM_MICROSOFT) && !defined(ICE_STEAM_BEOS) && !defined(ICE_STEAM_UNIX)
#  define ICE_STEAM_PLATFORM_AUTODETECTED
#endif

// ice_steam autodetection system (Huge but still worthy...)
#if defined(ICE_STEAM_PLATFORM_AUTODETECTED)
#  if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#    define ICE_STEAM_MICROSOFT
#  elif defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU) || defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
#    define ICE_STEAM_BEOS
#  else
#    if !(defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android))
#      define ICE_STEAM_UNIX
#    else
#      error "Steamworks SDK does not support Android! :("
#    endif
#  endif
#endif

// Allow to build DLL via ICE_STEAM_DLLEXPORT or ICE_STEAM_DLLIMPORT if desired!
// Else, Just define API as extern C code!
#if defined(ICE_STEAM_MICROSOFT)
#  if defined(ICE_STEAM_DLLEXPORT)
#    define ICE_STEAM_API __declspec(dllexport) ICE_STEAM_INLINEDEF
#  elif defined(ICE_STEAM_DLLIMPORT)
#    define ICE_STEAM_API __declspec(dllimport) ICE_STEAM_INLINEDEF
#  else
#    define ICE_STEAM_API ICE_STEAM_APIDEF ICE_STEAM_INLINEDEF
#  endif
#else
#  define ICE_STEAM_API ICE_STEAM_APIDEF ICE_STEAM_INLINEDEF
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_steam DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_STEAM_TRUE = 0,
    ICE_STEAM_FALSE = -1,
} ice_steam_bool;

typedef unsigned char uint8;
typedef signed char int8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;
typedef int64 lint64;
typedef uint64 ulint64;
typedef long long intp;
typedef unsigned long long uintp;
typedef uint64 CSteamID;
typedef uint8 Salt_t[8];
typedef uint64 GID_t;
typedef uint64 JobID_t;
typedef GID_t TxnID_t;
typedef uint32 PackageId_t;
typedef uint32 BundleId_t;
typedef uint32 AppId_t;
typedef uint64 AssetClassId_t;
typedef uint32 PhysicalItemId_t;
typedef uint32 DepotId_t;
typedef uint32 RTime32;
typedef uint32 CellID_t;
typedef uint64 SteamAPICall_t;
typedef uint32 AccountID_t;
typedef uint32 PartnerId_t;
typedef uint64 ManifestId_t;
typedef uint64 SiteId_t;
typedef uint32 HAuthTicket;
typedef void (*PFNLegacyKeyRegistration)(const char *, const char *);
typedef _Bool (*PFNLegacyKeyInstalled)(void);
typedef void (*PFNPreMinidumpCallback)(void *);
typedef void * BREAKPAD_HANDLE;
typedef int32 HSteamPipe;
typedef int32 HSteamUser;
typedef void (*SteamAPIWarningMessageHook_t)(int, const char *);
typedef uint32 (*SteamAPI_CheckCallbackRegistered_t)(int) ;
typedef int16 FriendsGroupID_t;
typedef void (*SteamAPIWarningMessageHook_t)(int, const char *);
typedef void * HServerListRequest;
typedef int HServerQuery;
typedef uint64 UGCHandle_t;
typedef uint64 PublishedFileUpdateHandle_t;
typedef uint64 PublishedFileId_t;
typedef uint64 UGCFileWriteStreamHandle_t;
typedef uint64 SteamLeaderboard_t;
typedef uint64 SteamLeaderboardEntries_t;
typedef uint32 SNetSocket_t;
typedef uint32 SNetListenSocket_t;
typedef uint32 ScreenshotHandle;
typedef uint32 HTTPRequestHandle;
typedef uint32 HTTPCookieContainerHandle;
typedef uint64 ControllerHandle_t;
typedef uint64 ControllerActionSetHandle_t;
typedef uint64 ControllerDigitalActionHandle_t;
typedef uint64 ControllerAnalogActionHandle_t;
typedef uint64 UGCQueryHandle_t;
typedef uint64 UGCUpdateHandle_t;
typedef uint32 HHTMLBrowser;
typedef uint64 SteamItemInstanceID_t;
typedef int32 SteamItemDef_t;
typedef int32 SteamInventoryResult_t;
typedef uint64 SteamInventoryUpdateHandle_t;

typedef enum EUniverse {
	k_EUniverseInvalid = 0,
	k_EUniversePublic = 1,
	k_EUniverseBeta = 2,
	k_EUniverseInternal = 3,
	k_EUniverseDev = 4,
	k_EUniverseMax = 5
} EUniverse;

typedef enum EResult {
	k_EResultOK = 1,
	k_EResultFail = 2,
	k_EResultNoConnection = 3,
	k_EResultInvalidPassword = 5,
	k_EResultLoggedInElsewhere = 6,
	k_EResultInvalidProtocolVer = 7,
	k_EResultInvalidParam = 8,
	k_EResultFileNotFound = 9,
	k_EResultBusy = 10,
	k_EResultInvalidState = 11,
	k_EResultInvalidName = 12,
	k_EResultInvalidEmail = 13,
	k_EResultDuplicateName = 14,
	k_EResultAccessDenied = 15,
	k_EResultTimeout = 16,
	k_EResultBanned = 17,
	k_EResultAccountNotFound = 18,
	k_EResultInvalidSteamID = 19,
	k_EResultServiceUnavailable = 20,
	k_EResultNotLoggedOn = 21,
	k_EResultPending = 22,
	k_EResultEncryptionFailure = 23,
	k_EResultInsufficientPrivilege = 24,
	k_EResultLimitExceeded = 25,
	k_EResultRevoked = 26,
	k_EResultExpired = 27,
	k_EResultAlreadyRedeemed = 28,
	k_EResultDuplicateRequest = 29,
	k_EResultAlreadyOwned = 30,
	k_EResultIPNotFound = 31,
	k_EResultPersistFailed = 32,
	k_EResultLockingFailed = 33,
	k_EResultLogonSessionReplaced = 34,
	k_EResultConnectFailed = 35,
	k_EResultHandshakeFailed = 36,
	k_EResultIOFailure = 37,
	k_EResultRemoteDisconnect = 38,
	k_EResultShoppingCartNotFound = 39,
	k_EResultBlocked = 40,
	k_EResultIgnored = 41,
	k_EResultNoMatch = 42,
	k_EResultAccountDisabled = 43,
	k_EResultServiceReadOnly = 44,
	k_EResultAccountNotFeatured = 45,
	k_EResultAdministratorOK = 46,
	k_EResultContentVersion = 47,
	k_EResultTryAnotherCM = 48,
	k_EResultPasswordRequiredToKickSession = 49,
	k_EResultAlreadyLoggedInElsewhere = 50,
	k_EResultSuspended = 51,
	k_EResultCancelled = 52,
	k_EResultDataCorruption = 53,
	k_EResultDiskFull = 54,
	k_EResultRemoteCallFailed = 55,
	k_EResultPasswordUnset = 56,
	k_EResultExternalAccountUnlinked = 57,
	k_EResultPSNTicketInvalid = 58,
	k_EResultExternalAccountAlreadyLinked = 59,
	k_EResultRemoteFileConflict = 60,
	k_EResultIllegalPassword = 61,
	k_EResultSameAsPreviousValue = 62,
	k_EResultAccountLogonDenied = 63,
	k_EResultCannotUseOldPassword = 64,
	k_EResultInvalidLoginAuthCode = 65,
	k_EResultAccountLogonDeniedNoMail = 66,
	k_EResultHardwareNotCapableOfIPT = 67,
	k_EResultIPTInitError = 68,
	k_EResultParentalControlRestricted = 69,
	k_EResultFacebookQueryError = 70,
	k_EResultExpiredLoginAuthCode = 71,
	k_EResultIPLoginRestrictionFailed = 72,
	k_EResultAccountLockedDown = 73,
	k_EResultAccountLogonDeniedVerifiedEmailRequired = 74,
	k_EResultNoMatchingURL = 75,
	k_EResultBadResponse = 76,
	k_EResultRequirePasswordReEntry = 77,
	k_EResultValueOutOfRange = 78,
	k_EResultUnexpectedError = 79,
	k_EResultDisabled = 80,
	k_EResultInvalidCEGSubmission = 81,
	k_EResultRestrictedDevice = 82,
	k_EResultRegionLocked = 83,
	k_EResultRateLimitExceeded = 84,
	k_EResultAccountLoginDeniedNeedTwoFactor = 85,
	k_EResultItemDeleted = 86,
	k_EResultAccountLoginDeniedThrottle = 87,
	k_EResultTwoFactorCodeMismatch = 88,
	k_EResultTwoFactorActivationCodeMismatch = 89,
	k_EResultAccountAssociatedToMultiplePartners = 90,
	k_EResultNotModified = 91,
	k_EResultNoMobileDevice = 92,
	k_EResultTimeNotSynced = 93,
	k_EResultSmsCodeFailed = 94,
	k_EResultAccountLimitExceeded = 95,
	k_EResultAccountActivityLimitExceeded = 96,
	k_EResultPhoneActivityLimitExceeded = 97,
	k_EResultRefundToWallet = 98,
	k_EResultEmailSendFailure = 99,
	k_EResultNotSettled = 100,
	k_EResultNeedCaptcha = 101,
	k_EResultGSLTDenied = 102,
	k_EResultGSOwnerDenied = 103,
	k_EResultInvalidItemType = 104,
	k_EResultIPBanned = 105,
	k_EResultGSLTExpired = 106,
	k_EResultInsufficientFunds = 107,
	k_EResultTooManyPending = 108,
	k_EResultNoSiteLicensesFound = 109,
	k_EResultWGNetworkSendExceeded = 110,
	k_EResultAccountNotFriends = 111,
	k_EResultLimitedUserAccount = 112,
} EResult;

typedef enum EVoiceResult {
	k_EVoiceResultOK = 0,
	k_EVoiceResultNotInitialized = 1,
	k_EVoiceResultNotRecording = 2,
	k_EVoiceResultNoData = 3,
	k_EVoiceResultBufferTooSmall = 4,
	k_EVoiceResultDataCorrupted = 5,
	k_EVoiceResultRestricted = 6,
	k_EVoiceResultUnsupportedCodec = 7,
	k_EVoiceResultReceiverOutOfDate = 8,
	k_EVoiceResultReceiverDidNotAnswer = 9,
} EVoiceResult;

typedef enum EDenyReason {
	k_EDenyInvalid = 0,
	k_EDenyInvalidVersion = 1,
	k_EDenyGeneric = 2,
	k_EDenyNotLoggedOn = 3,
	k_EDenyNoLicense = 4,
	k_EDenyCheater = 5,
	k_EDenyLoggedInElseWhere = 6,
	k_EDenyUnknownText = 7,
	k_EDenyIncompatibleAnticheat = 8,
	k_EDenyMemoryCorruption = 9,
	k_EDenyIncompatibleSoftware = 10,
	k_EDenySteamConnectionLost = 11,
	k_EDenySteamConnectionError = 12,
	k_EDenySteamResponseTimedOut = 13,
	k_EDenySteamValidationStalled = 14,
	k_EDenySteamOwnerLeftGuestUser = 15,
} EDenyReason;

typedef enum EBeginAuthSessionResult {
	k_EBeginAuthSessionResultOK = 0,
	k_EBeginAuthSessionResultInvalidTicket = 1,
	k_EBeginAuthSessionResultDuplicateRequest = 2,
	k_EBeginAuthSessionResultInvalidVersion = 3,
	k_EBeginAuthSessionResultGameMismatch = 4,
	k_EBeginAuthSessionResultExpiredTicket = 5,
} EBeginAuthSessionResult;

typedef enum EAuthSessionResponse {
	k_EAuthSessionResponseOK = 0,
	k_EAuthSessionResponseUserNotConnectedToSteam = 1,
	k_EAuthSessionResponseNoLicenseOrExpired = 2,
	k_EAuthSessionResponseVACBanned = 3,
	k_EAuthSessionResponseLoggedInElseWhere = 4,
	k_EAuthSessionResponseVACCheckTimedOut = 5,
	k_EAuthSessionResponseAuthTicketCanceled = 6,
	k_EAuthSessionResponseAuthTicketInvalidAlreadyUsed = 7,
	k_EAuthSessionResponseAuthTicketInvalid = 8,
	k_EAuthSessionResponsePublisherIssuedBan = 9,
} EAuthSessionResponse;

typedef enum EUserHasLicenseForAppResult {
	k_EUserHasLicenseResultHasLicense = 0,
	k_EUserHasLicenseResultDoesNotHaveLicense = 1,
	k_EUserHasLicenseResultNoAuth = 2,
} EUserHasLicenseForAppResult;

typedef enum EAccountType {
	k_EAccountTypeInvalid = 0,
	k_EAccountTypeIndividual = 1,
	k_EAccountTypeMultiseat = 2,
	k_EAccountTypeGameServer = 3,
	k_EAccountTypeAnonGameServer = 4,
	k_EAccountTypePending = 5,
	k_EAccountTypeContentServer = 6,
	k_EAccountTypeClan = 7,
	k_EAccountTypeChat = 8,
	k_EAccountTypeConsoleUser = 9,
	k_EAccountTypeAnonUser = 10,
	k_EAccountTypeMax = 11,
} EAccountType;

typedef enum EAppReleaseState {
	k_EAppReleaseState_Unknown = 0,
	k_EAppReleaseState_Unavailable = 1,
	k_EAppReleaseState_Prerelease = 2,
	k_EAppReleaseState_PreloadOnly = 3,
	k_EAppReleaseState_Released = 4,
} EAppReleaseState;

typedef enum EAppOwnershipFlags {
	k_EAppOwnershipFlags_None = 0,
	k_EAppOwnershipFlags_OwnsLicense = 1,
	k_EAppOwnershipFlags_FreeLicense = 2,
	k_EAppOwnershipFlags_RegionRestricted = 4,
	k_EAppOwnershipFlags_LowViolence = 8,
	k_EAppOwnershipFlags_InvalidPlatform = 16,
	k_EAppOwnershipFlags_SharedLicense = 32,
	k_EAppOwnershipFlags_FreeWeekend = 64,
	k_EAppOwnershipFlags_RetailLicense = 128,
	k_EAppOwnershipFlags_LicenseLocked = 256,
	k_EAppOwnershipFlags_LicensePending = 512,
	k_EAppOwnershipFlags_LicenseExpired = 1024,
	k_EAppOwnershipFlags_LicensePermanent = 2048,
	k_EAppOwnershipFlags_LicenseRecurring = 4096,
	k_EAppOwnershipFlags_LicenseCanceled = 8192,
	k_EAppOwnershipFlags_AutoGrant = 16384,
	k_EAppOwnershipFlags_PendingGift = 32768,
	k_EAppOwnershipFlags_RentalNotActivated = 65536,
	k_EAppOwnershipFlags_Rental = 131072,
	k_EAppOwnershipFlags_SiteLicense = 262144,
} EAppOwnershipFlags;

typedef enum EAppType {
	k_EAppType_Invalid = 0,
	k_EAppType_Game = 1,
	k_EAppType_Application = 2,
	k_EAppType_Tool = 4,
	k_EAppType_Demo = 8,
	k_EAppType_Media_DEPRECATED = 16,
	k_EAppType_DLC = 32,
	k_EAppType_Guide = 64,
	k_EAppType_Driver = 128,
	k_EAppType_Config = 256,
	k_EAppType_Hardware = 512,
	k_EAppType_Franchise = 1024,
	k_EAppType_Video = 2048,
	k_EAppType_Plugin = 4096,
	k_EAppType_Music = 8192,
	k_EAppType_Series = 16384,
	k_EAppType_Comic = 32768,
	k_EAppType_Shortcut = 1073741824,
	k_EAppType_DepotOnly = 0x80000000,//-2147483648,
} EAppType;

typedef enum ESteamUserStatType {
	k_ESteamUserStatTypeINVALID = 0,
	k_ESteamUserStatTypeINT = 1,
	k_ESteamUserStatTypeFLOAT = 2,
	k_ESteamUserStatTypeAVGRATE = 3,
	k_ESteamUserStatTypeACHIEVEMENTS = 4,
	k_ESteamUserStatTypeGROUPACHIEVEMENTS = 5,
	k_ESteamUserStatTypeMAX = 6,
} ESteamUserStatType;

typedef enum EChatEntryType {
	k_EChatEntryTypeInvalid = 0,
	k_EChatEntryTypeChatMsg = 1,
	k_EChatEntryTypeTyping = 2,
	k_EChatEntryTypeInviteGame = 3,
	k_EChatEntryTypeEmote = 4,
	k_EChatEntryTypeLeftConversation = 6,
	k_EChatEntryTypeEntered = 7,
	k_EChatEntryTypeWasKicked = 8,
	k_EChatEntryTypeWasBanned = 9,
	k_EChatEntryTypeDisconnected = 10,
	k_EChatEntryTypeHistoricalChat = 11,
	k_EChatEntryTypeLinkBlocked = 14,
} EChatEntryType;

typedef enum EChatRoomEnterResponse {
	k_EChatRoomEnterResponseSuccess = 1,
	k_EChatRoomEnterResponseDoesntExist = 2,
	k_EChatRoomEnterResponseNotAllowed = 3,
	k_EChatRoomEnterResponseFull = 4,
	k_EChatRoomEnterResponseError = 5,
	k_EChatRoomEnterResponseBanned = 6,
	k_EChatRoomEnterResponseLimited = 7,
	k_EChatRoomEnterResponseClanDisabled = 8,
	k_EChatRoomEnterResponseCommunityBan = 9,
	k_EChatRoomEnterResponseMemberBlockedYou = 10,
	k_EChatRoomEnterResponseYouBlockedMember = 11,
	k_EChatRoomEnterResponseRatelimitExceeded = 15,
} EChatRoomEnterResponse;

typedef enum EChatSteamIDInstanceFlags {
	k_EChatAccountInstanceMask = 4095,
	k_EChatInstanceFlagClan = 524288,
	k_EChatInstanceFlagLobby = 262144,
	k_EChatInstanceFlagMMSLobby = 131072,
} EChatSteamIDInstanceFlags;

typedef enum EMarketingMessageFlags {
	k_EMarketingMessageFlagsNone = 0,
	k_EMarketingMessageFlagsHighPriority = 1,
	k_EMarketingMessageFlagsPlatformWindows = 2,
	k_EMarketingMessageFlagsPlatformMac = 4,
	k_EMarketingMessageFlagsPlatformLinux = 8,
	k_EMarketingMessageFlagsPlatformRestrictions = 14,
} EMarketingMessageFlags;

typedef enum ENotificationPosition {
	k_EPositionTopLeft = 0,
	k_EPositionTopRight = 1,
	k_EPositionBottomLeft = 2,
	k_EPositionBottomRight = 3,
} ENotificationPosition;

typedef enum EBroadcastUploadResult {
	k_EBroadcastUploadResultNone = 0,
	k_EBroadcastUploadResultOK = 1,
	k_EBroadcastUploadResultInitFailed = 2,
	k_EBroadcastUploadResultFrameFailed = 3,
	k_EBroadcastUploadResultTimeout = 4,
	k_EBroadcastUploadResultBandwidthExceeded = 5,
	k_EBroadcastUploadResultLowFPS = 6,
	k_EBroadcastUploadResultMissingKeyFrames = 7,
	k_EBroadcastUploadResultNoConnection = 8,
	k_EBroadcastUploadResultRelayFailed = 9,
	k_EBroadcastUploadResultSettingsChanged = 10,
	k_EBroadcastUploadResultMissingAudio = 11,
	k_EBroadcastUploadResultTooFarBehind = 12,
	k_EBroadcastUploadResultTranscodeBehind = 13,
} EBroadcastUploadResult;

typedef enum ELaunchOptionType {
	k_ELaunchOptionType_None = 0,
	k_ELaunchOptionType_Default = 1,
	k_ELaunchOptionType_SafeMode = 2,
	k_ELaunchOptionType_Multiplayer = 3,
	k_ELaunchOptionType_Config = 4,
	k_ELaunchOptionType_OpenVR = 5,
	k_ELaunchOptionType_Server = 6,
	k_ELaunchOptionType_Editor = 7,
	k_ELaunchOptionType_Manual = 8,
	k_ELaunchOptionType_Benchmark = 9,
	k_ELaunchOptionType_Option1 = 10,
	k_ELaunchOptionType_Option2 = 11,
	k_ELaunchOptionType_Option3 = 12,
	k_ELaunchOptionType_OculusVR = 13,
	k_ELaunchOptionType_OpenVROverlay = 14,
	k_ELaunchOptionType_OSVR = 15,
	k_ELaunchOptionType_Dialog = 1000,
} ELaunchOptionType;

typedef enum EVRHMDType {
	k_eEVRHMDType_None = -1,
	k_eEVRHMDType_Unknown = 0,
	k_eEVRHMDType_HTC_Dev = 1,
	k_eEVRHMDType_HTC_VivePre = 2,
	k_eEVRHMDType_HTC_Vive = 3,
	k_eEVRHMDType_HTC_Unknown = 20,
	k_eEVRHMDType_Oculus_DK1 = 21,
	k_eEVRHMDType_Oculus_DK2 = 22,
	k_eEVRHMDType_Oculus_Rift = 23,
	k_eEVRHMDType_Oculus_Unknown = 40,
	k_eEVRHMDType_Acer_Unknown = 50,
	k_eEVRHMDType_Acer_WindowsMR = 51,
	k_eEVRHMDType_Dell_Unknown = 60,
	k_eEVRHMDType_Dell_Visor = 61,
	k_eEVRHMDType_Lenovo_Unknown = 70,
	k_eEVRHMDType_Lenovo_Explorer = 71,
	k_eEVRHMDType_HP_Unknown = 80,
	k_eEVRHMDType_HP_WindowsMR = 81,
	k_eEVRHMDType_Samsung_Unknown = 90,
	k_eEVRHMDType_Samsung_Odyssey = 91,
	k_eEVRHMDType_Unannounced_Unknown = 100,
	k_eEVRHMDType_Unannounced_WindowsMR = 101,
} EVRHMDType;

typedef enum EGameIDType {
	k_EGameIDTypeApp = 0,
	k_EGameIDTypeGameMod = 1,
	k_EGameIDTypeShortcut = 2,
	k_EGameIDTypeP2P = 3,
} EGameIDType;

typedef enum EFailureType {
	k_EFailureFlushedCallbackQueue = 0,
	k_EFailurePipeFail = 1,
} EFailureType;

typedef enum EFriendRelationship {
	k_EFriendRelationshipNone = 0,
	k_EFriendRelationshipBlocked = 1,
	k_EFriendRelationshipRequestRecipient = 2,
	k_EFriendRelationshipFriend = 3,
	k_EFriendRelationshipRequestInitiator = 4,
	k_EFriendRelationshipIgnored = 5,
	k_EFriendRelationshipIgnoredFriend = 6,
	k_EFriendRelationshipSuggested_DEPRECATED = 7,
	k_EFriendRelationshipMax = 8,
} EFriendRelationship;

typedef enum EPersonaState {
	k_EPersonaStateOffline = 0,
	k_EPersonaStateOnline = 1,
	k_EPersonaStateBusy = 2,
	k_EPersonaStateAway = 3,
	k_EPersonaStateSnooze = 4,
	k_EPersonaStateLookingToTrade = 5,
	k_EPersonaStateLookingToPlay = 6,
	k_EPersonaStateMax = 7,
} EPersonaState;

typedef enum EFriendFlags {
	k_EFriendFlagNone = 0,
	k_EFriendFlagBlocked = 1,
	k_EFriendFlagFriendshipRequested = 2,
	k_EFriendFlagImmediate = 4,
	k_EFriendFlagClanMember = 8,
	k_EFriendFlagOnGameServer = 16,
	k_EFriendFlagRequestingFriendship = 128,
	k_EFriendFlagRequestingInfo = 256,
	k_EFriendFlagIgnored = 512,
	k_EFriendFlagIgnoredFriend = 1024,
	k_EFriendFlagChatMember = 4096,
	k_EFriendFlagAll = 65535,
} EFriendFlags;

typedef enum EUserRestriction {
	k_nUserRestrictionNone = 0,
	k_nUserRestrictionUnknown = 1,
	k_nUserRestrictionAnyChat = 2,
	k_nUserRestrictionVoiceChat = 4,
	k_nUserRestrictionGroupChat = 8,
	k_nUserRestrictionRating = 16,
	k_nUserRestrictionGameInvites = 32,
	k_nUserRestrictionTrading = 64,
} EUserRestriction;

typedef enum EOverlayToStoreFlag {
	k_EOverlayToStoreFlag_None = 0,
	k_EOverlayToStoreFlag_AddToCart = 1,
	k_EOverlayToStoreFlag_AddToCartAndShow = 2,
} EOverlayToStoreFlag;

typedef enum EPersonaChange {
	k_EPersonaChangeName = 1,
	k_EPersonaChangeStatus = 2,
	k_EPersonaChangeComeOnline = 4,
	k_EPersonaChangeGoneOffline = 8,
	k_EPersonaChangeGamePlayed = 16,
	k_EPersonaChangeGameServer = 32,
	k_EPersonaChangeAvatar = 64,
	k_EPersonaChangeJoinedSource = 128,
	k_EPersonaChangeLeftSource = 256,
	k_EPersonaChangeRelationshipChanged = 512,
	k_EPersonaChangeNameFirstSet = 1024,
	k_EPersonaChangeFacebookInfo = 2048,
	k_EPersonaChangeNickname = 4096,
	k_EPersonaChangeSteamLevel = 8192,
} EPersonaChange;

typedef enum ESteamAPICallFailure {
	k_ESteamAPICallFailureNone = -1,
	k_ESteamAPICallFailureSteamGone = 0,
	k_ESteamAPICallFailureNetworkFailure = 1,
	k_ESteamAPICallFailureInvalidHandle = 2,
	k_ESteamAPICallFailureMismatchedCallback = 3,
} ESteamAPICallFailure;

typedef enum EGamepadTextInputMode {
	k_EGamepadTextInputModeNormal = 0,
	k_EGamepadTextInputModePassword = 1,
} EGamepadTextInputMode;

typedef enum EGamepadTextInputLineMode {
	k_EGamepadTextInputLineModeSingleLine = 0,
	k_EGamepadTextInputLineModeMultipleLines = 1,
} EGamepadTextInputLineMode;

typedef enum ECheckFileSignature {
	k_ECheckFileSignatureInvalidSignature = 0,
	k_ECheckFileSignatureValidSignature = 1,
	k_ECheckFileSignatureFileNotFound = 2,
	k_ECheckFileSignatureNoSignaturesFoundForThisApp = 3,
	k_ECheckFileSignatureNoSignaturesFoundForThisFile = 4,
} ECheckFileSignature;

typedef enum EMatchMakingServerResponse {
	eServerResponded = 0,
	eServerFailedToRespond = 1,
	eNoServersListedOnMasterServer = 2,
} EMatchMakingServerResponse;

typedef enum ELobbyType {
	k_ELobbyTypePrivate = 0,
	k_ELobbyTypeFriendsOnly = 1,
	k_ELobbyTypePublic = 2,
	k_ELobbyTypeInvisible = 3,
} ELobbyType;

typedef enum ELobbyComparison {
	k_ELobbyComparisonEqualToOrLessThan = -2,
	k_ELobbyComparisonLessThan = -1,
	k_ELobbyComparisonEqual = 0,
	k_ELobbyComparisonGreaterThan = 1,
	k_ELobbyComparisonEqualToOrGreaterThan = 2,
	k_ELobbyComparisonNotEqual = 3,
} ELobbyComparison;

typedef enum ELobbyDistanceFilter {
	k_ELobbyDistanceFilterClose = 0,
	k_ELobbyDistanceFilterDefault = 1,
	k_ELobbyDistanceFilterFar = 2,
	k_ELobbyDistanceFilterWorldwide = 3,
} ELobbyDistanceFilter;

typedef enum EChatMemberStateChange {
	k_EChatMemberStateChangeEntered = 1,
	k_EChatMemberStateChangeLeft = 2,
	k_EChatMemberStateChangeDisconnected = 4,
	k_EChatMemberStateChangeKicked = 8,
	k_EChatMemberStateChangeBanned = 16,
} EChatMemberStateChange;

typedef enum ERemoteStoragePlatform {
	k_ERemoteStoragePlatformNone = 0,
	k_ERemoteStoragePlatformWindows = 1,
	k_ERemoteStoragePlatformOSX = 2,
	k_ERemoteStoragePlatformPS3 = 4,
	k_ERemoteStoragePlatformLinux = 8,
	k_ERemoteStoragePlatformReserved2 = 16,
	k_ERemoteStoragePlatformAll = -1,
} ERemoteStoragePlatform;

typedef enum ERemoteStoragePublishedFileVisibility {
	k_ERemoteStoragePublishedFileVisibilityPublic = 0,
	k_ERemoteStoragePublishedFileVisibilityFriendsOnly = 1,
	k_ERemoteStoragePublishedFileVisibilityPrivate = 2,
} ERemoteStoragePublishedFileVisibility;

typedef enum EWorkshopFileType {
	k_EWorkshopFileTypeFirst = 0,
	k_EWorkshopFileTypeCommunity = 0,
	k_EWorkshopFileTypeMicrotransaction = 1,
	k_EWorkshopFileTypeCollection = 2,
	k_EWorkshopFileTypeArt = 3,
	k_EWorkshopFileTypeVideo = 4,
	k_EWorkshopFileTypeScreenshot = 5,
	k_EWorkshopFileTypeGame = 6,
	k_EWorkshopFileTypeSoftware = 7,
	k_EWorkshopFileTypeConcept = 8,
	k_EWorkshopFileTypeWebGuide = 9,
	k_EWorkshopFileTypeIntegratedGuide = 10,
	k_EWorkshopFileTypeMerch = 11,
	k_EWorkshopFileTypeControllerBinding = 12,
	k_EWorkshopFileTypeSteamworksAccessInvite = 13,
	k_EWorkshopFileTypeSteamVideo = 14,
	k_EWorkshopFileTypeGameManagedItem = 15,
	k_EWorkshopFileTypeMax = 16,
} EWorkshopFileType;

typedef enum EWorkshopVote {
	k_EWorkshopVoteUnvoted = 0,
	k_EWorkshopVoteFor = 1,
	k_EWorkshopVoteAgainst = 2,
	k_EWorkshopVoteLater = 3,
} EWorkshopVote;

typedef enum EWorkshopFileAction {
	k_EWorkshopFileActionPlayed = 0,
	k_EWorkshopFileActionCompleted = 1,
} EWorkshopFileAction;

typedef enum EWorkshopEnumerationType {
	k_EWorkshopEnumerationTypeRankedByVote = 0,
	k_EWorkshopEnumerationTypeRecent = 1,
	k_EWorkshopEnumerationTypeTrending = 2,
	k_EWorkshopEnumerationTypeFavoritesOfFriends = 3,
	k_EWorkshopEnumerationTypeVotedByFriends = 4,
	k_EWorkshopEnumerationTypeContentByFriends = 5,
	k_EWorkshopEnumerationTypeRecentFromFollowedUsers = 6,
} EWorkshopEnumerationType;

typedef enum EWorkshopVideoProvider {
	k_EWorkshopVideoProviderNone = 0,
	k_EWorkshopVideoProviderYoutube = 1,
} EWorkshopVideoProvider;

typedef enum EUGCReadAction {
	k_EUGCRead_ContinueReadingUntilFinished = 0,
	k_EUGCRead_ContinueReading = 1,
	k_EUGCRead_Close = 2,
} EUGCReadAction;

typedef enum ELeaderboardDataRequest {
	k_ELeaderboardDataRequestGlobal = 0,
	k_ELeaderboardDataRequestGlobalAroundUser = 1,
	k_ELeaderboardDataRequestFriends = 2,
	k_ELeaderboardDataRequestUsers = 3,
} ELeaderboardDataRequest;

typedef enum ELeaderboardSortMethod {
	k_ELeaderboardSortMethodNone = 0,
	k_ELeaderboardSortMethodAscending = 1,
	k_ELeaderboardSortMethodDescending = 2,
} ELeaderboardSortMethod;

typedef enum ELeaderboardDisplayType {
	k_ELeaderboardDisplayTypeNone = 0,
	k_ELeaderboardDisplayTypeNumeric = 1,
	k_ELeaderboardDisplayTypeTimeSeconds = 2,
	k_ELeaderboardDisplayTypeTimeMilliSeconds = 3,
} ELeaderboardDisplayType;

typedef enum ELeaderboardUploadScoreMethod {
	k_ELeaderboardUploadScoreMethodNone = 0,
	k_ELeaderboardUploadScoreMethodKeepBest = 1,
	k_ELeaderboardUploadScoreMethodForceUpdate = 2,
} ELeaderboardUploadScoreMethod;

typedef enum ERegisterActivationCodeResult {
	k_ERegisterActivationCodeResultOK = 0,
	k_ERegisterActivationCodeResultFail = 1,
	k_ERegisterActivationCodeResultAlreadyRegistered = 2,
	k_ERegisterActivationCodeResultTimeout = 3,
	k_ERegisterActivationCodeAlreadyOwned = 4,
} ERegisterActivationCodeResult;

typedef enum EP2PSessionError {
	k_EP2PSessionErrorNone = 0,
	k_EP2PSessionErrorNotRunningApp = 1,
	k_EP2PSessionErrorNoRightsToApp = 2,
	k_EP2PSessionErrorDestinationNotLoggedIn = 3,
	k_EP2PSessionErrorTimeout = 4,
	k_EP2PSessionErrorMax = 5,
} EP2PSessionError;

typedef enum EP2PSend {
	k_EP2PSendUnreliable = 0,
	k_EP2PSendUnreliableNoDelay = 1,
	k_EP2PSendReliable = 2,
	k_EP2PSendReliableWithBuffering = 3,
} EP2PSend;

typedef enum ESNetSocketState {
	k_ESNetSocketStateInvalid = 0,
	k_ESNetSocketStateConnected = 1,
	k_ESNetSocketStateInitiated = 10,
	k_ESNetSocketStateLocalCandidatesFound = 11,
	k_ESNetSocketStateReceivedRemoteCandidates = 12,
	k_ESNetSocketStateChallengeHandshake = 15,
	k_ESNetSocketStateDisconnecting = 21,
	k_ESNetSocketStateLocalDisconnect = 22,
	k_ESNetSocketStateTimeoutDuringConnect = 23,
	k_ESNetSocketStateRemoteEndDisconnected = 24,
	k_ESNetSocketStateConnectionBroken = 25,
} ESNetSocketState;

typedef enum ESNetSocketConnectionType {
	k_ESNetSocketConnectionTypeNotConnected = 0,
	k_ESNetSocketConnectionTypeUDP = 1,
	k_ESNetSocketConnectionTypeUDPRelay = 2,
} ESNetSocketConnectionType;

typedef enum EVRScreenshotType {
	k_EVRScreenshotType_None = 0,
	k_EVRScreenshotType_Mono = 1,
	k_EVRScreenshotType_Stereo = 2,
	k_EVRScreenshotType_MonoCubemap = 3,
	k_EVRScreenshotType_MonoPanorama = 4,
	k_EVRScreenshotType_StereoPanorama = 5,
} EVRScreenshotType;

typedef enum AudioPlayback_Status {
	AudioPlayback_Undefined = 0,
	AudioPlayback_Playing = 1,
	AudioPlayback_Paused = 2,
	AudioPlayback_Idle = 3,
} AudioPlayback_Status;

typedef enum EHTTPMethod {
	k_EHTTPMethodInvalid = 0,
	k_EHTTPMethodGET = 1,
	k_EHTTPMethodHEAD = 2,
	k_EHTTPMethodPOST = 3,
	k_EHTTPMethodPUT = 4,
	k_EHTTPMethodDELETE = 5,
	k_EHTTPMethodOPTIONS = 6,
	k_EHTTPMethodPATCH = 7,
} EHTTPMethod;

typedef enum EHTTPStatusCode {
	k_EHTTPStatusCodeInvalid = 0,
	k_EHTTPStatusCode100Continue = 100,
	k_EHTTPStatusCode101SwitchingProtocols = 101,
	k_EHTTPStatusCode200OK = 200,
	k_EHTTPStatusCode201Created = 201,
	k_EHTTPStatusCode202Accepted = 202,
	k_EHTTPStatusCode203NonAuthoritative = 203,
	k_EHTTPStatusCode204NoContent = 204,
	k_EHTTPStatusCode205ResetContent = 205,
	k_EHTTPStatusCode206PartialContent = 206,
	k_EHTTPStatusCode300MultipleChoices = 300,
	k_EHTTPStatusCode301MovedPermanently = 301,
	k_EHTTPStatusCode302Found = 302,
	k_EHTTPStatusCode303SeeOther = 303,
	k_EHTTPStatusCode304NotModified = 304,
	k_EHTTPStatusCode305UseProxy = 305,
	k_EHTTPStatusCode307TemporaryRedirect = 307,
	k_EHTTPStatusCode400BadRequest = 400,
	k_EHTTPStatusCode401Unauthorized = 401,
	k_EHTTPStatusCode402PaymentRequired = 402,
	k_EHTTPStatusCode403Forbidden = 403,
	k_EHTTPStatusCode404NotFound = 404,
	k_EHTTPStatusCode405MethodNotAllowed = 405,
	k_EHTTPStatusCode406NotAcceptable = 406,
	k_EHTTPStatusCode407ProxyAuthRequired = 407,
	k_EHTTPStatusCode408RequestTimeout = 408,
	k_EHTTPStatusCode409Conflict = 409,
	k_EHTTPStatusCode410Gone = 410,
	k_EHTTPStatusCode411LengthRequired = 411,
	k_EHTTPStatusCode412PreconditionFailed = 412,
	k_EHTTPStatusCode413RequestEntityTooLarge = 413,
	k_EHTTPStatusCode414RequestURITooLong = 414,
	k_EHTTPStatusCode415UnsupportedMediaType = 415,
	k_EHTTPStatusCode416RequestedRangeNotSatisfiable = 416,
	k_EHTTPStatusCode417ExpectationFailed = 417,
	k_EHTTPStatusCode4xxUnknown = 418,
	k_EHTTPStatusCode429TooManyRequests = 429,
	k_EHTTPStatusCode500InternalServerError = 500,
	k_EHTTPStatusCode501NotImplemented = 501,
	k_EHTTPStatusCode502BadGateway = 502,
	k_EHTTPStatusCode503ServiceUnavailable = 503,
	k_EHTTPStatusCode504GatewayTimeout = 504,
	k_EHTTPStatusCode505HTTPVersionNotSupported = 505,
	k_EHTTPStatusCode5xxUnknown = 599,
} EHTTPStatusCode;

typedef enum ESteamControllerPad {
	k_ESteamControllerPad_Left = 0,
	k_ESteamControllerPad_Right = 1,
} ESteamControllerPad;

typedef enum EControllerSource {
	k_EControllerSource_None = 0,
	k_EControllerSource_LeftTrackpad = 1,
	k_EControllerSource_RightTrackpad = 2,
	k_EControllerSource_Joystick = 3,
	k_EControllerSource_ABXY = 4,
	k_EControllerSource_Switch = 5,
	k_EControllerSource_LeftTrigger = 6,
	k_EControllerSource_RightTrigger = 7,
	k_EControllerSource_Gyro = 8,
	k_EControllerSource_CenterTrackpad = 9,
	k_EControllerSource_RightJoystick = 10,
	k_EControllerSource_DPad = 11,
	k_EControllerSource_Key = 12,
	k_EControllerSource_Mouse = 13,
	k_EControllerSource_Count = 14,
} EControllerSource;

typedef enum EControllerSourceMode {
	k_EControllerSourceMode_None = 0,
	k_EControllerSourceMode_Dpad = 1,
	k_EControllerSourceMode_Buttons = 2,
	k_EControllerSourceMode_FourButtons = 3,
	k_EControllerSourceMode_AbsoluteMouse = 4,
	k_EControllerSourceMode_RelativeMouse = 5,
	k_EControllerSourceMode_JoystickMove = 6,
	k_EControllerSourceMode_JoystickMouse = 7,
	k_EControllerSourceMode_JoystickCamera = 8,
	k_EControllerSourceMode_ScrollWheel = 9,
	k_EControllerSourceMode_Trigger = 10,
	k_EControllerSourceMode_TouchMenu = 11,
	k_EControllerSourceMode_MouseJoystick = 12,
	k_EControllerSourceMode_MouseRegion = 13,
	k_EControllerSourceMode_RadialMenu = 14,
	k_EControllerSourceMode_SingleButton = 15,
	k_EControllerSourceMode_Switches = 16,
} EControllerSourceMode;

typedef enum EControllerActionOrigin {
	k_EControllerActionOrigin_None = 0,
	k_EControllerActionOrigin_A = 1,
	k_EControllerActionOrigin_B = 2,
	k_EControllerActionOrigin_X = 3,
	k_EControllerActionOrigin_Y = 4,
	k_EControllerActionOrigin_LeftBumper = 5,
	k_EControllerActionOrigin_RightBumper = 6,
	k_EControllerActionOrigin_LeftGrip = 7,
	k_EControllerActionOrigin_RightGrip = 8,
	k_EControllerActionOrigin_Start = 9,
	k_EControllerActionOrigin_Back = 10,
	k_EControllerActionOrigin_LeftPad_Touch = 11,
	k_EControllerActionOrigin_LeftPad_Swipe = 12,
	k_EControllerActionOrigin_LeftPad_Click = 13,
	k_EControllerActionOrigin_LeftPad_DPadNorth = 14,
	k_EControllerActionOrigin_LeftPad_DPadSouth = 15,
	k_EControllerActionOrigin_LeftPad_DPadWest = 16,
	k_EControllerActionOrigin_LeftPad_DPadEast = 17,
	k_EControllerActionOrigin_RightPad_Touch = 18,
	k_EControllerActionOrigin_RightPad_Swipe = 19,
	k_EControllerActionOrigin_RightPad_Click = 20,
	k_EControllerActionOrigin_RightPad_DPadNorth = 21,
	k_EControllerActionOrigin_RightPad_DPadSouth = 22,
	k_EControllerActionOrigin_RightPad_DPadWest = 23,
	k_EControllerActionOrigin_RightPad_DPadEast = 24,
	k_EControllerActionOrigin_LeftTrigger_Pull = 25,
	k_EControllerActionOrigin_LeftTrigger_Click = 26,
	k_EControllerActionOrigin_RightTrigger_Pull = 27,
	k_EControllerActionOrigin_RightTrigger_Click = 28,
	k_EControllerActionOrigin_LeftStick_Move = 29,
	k_EControllerActionOrigin_LeftStick_Click = 30,
	k_EControllerActionOrigin_LeftStick_DPadNorth = 31,
	k_EControllerActionOrigin_LeftStick_DPadSouth = 32,
	k_EControllerActionOrigin_LeftStick_DPadWest = 33,
	k_EControllerActionOrigin_LeftStick_DPadEast = 34,
	k_EControllerActionOrigin_Gyro_Move = 35,
	k_EControllerActionOrigin_Gyro_Pitch = 36,
	k_EControllerActionOrigin_Gyro_Yaw = 37,
	k_EControllerActionOrigin_Gyro_Roll = 38,
	k_EControllerActionOrigin_PS4_X = 39,
	k_EControllerActionOrigin_PS4_Circle = 40,
	k_EControllerActionOrigin_PS4_Triangle = 41,
	k_EControllerActionOrigin_PS4_Square = 42,
	k_EControllerActionOrigin_PS4_LeftBumper = 43,
	k_EControllerActionOrigin_PS4_RightBumper = 44,
	k_EControllerActionOrigin_PS4_Options = 45,
	k_EControllerActionOrigin_PS4_Share = 46,
	k_EControllerActionOrigin_PS4_LeftPad_Touch = 47,
	k_EControllerActionOrigin_PS4_LeftPad_Swipe = 48,
	k_EControllerActionOrigin_PS4_LeftPad_Click = 49,
	k_EControllerActionOrigin_PS4_LeftPad_DPadNorth = 50,
	k_EControllerActionOrigin_PS4_LeftPad_DPadSouth = 51,
	k_EControllerActionOrigin_PS4_LeftPad_DPadWest = 52,
	k_EControllerActionOrigin_PS4_LeftPad_DPadEast = 53,
	k_EControllerActionOrigin_PS4_RightPad_Touch = 54,
	k_EControllerActionOrigin_PS4_RightPad_Swipe = 55,
	k_EControllerActionOrigin_PS4_RightPad_Click = 56,
	k_EControllerActionOrigin_PS4_RightPad_DPadNorth = 57,
	k_EControllerActionOrigin_PS4_RightPad_DPadSouth = 58,
	k_EControllerActionOrigin_PS4_RightPad_DPadWest = 59,
	k_EControllerActionOrigin_PS4_RightPad_DPadEast = 60,
	k_EControllerActionOrigin_PS4_CenterPad_Touch = 61,
	k_EControllerActionOrigin_PS4_CenterPad_Swipe = 62,
	k_EControllerActionOrigin_PS4_CenterPad_Click = 63,
	k_EControllerActionOrigin_PS4_CenterPad_DPadNorth = 64,
	k_EControllerActionOrigin_PS4_CenterPad_DPadSouth = 65,
	k_EControllerActionOrigin_PS4_CenterPad_DPadWest = 66,
	k_EControllerActionOrigin_PS4_CenterPad_DPadEast = 67,
	k_EControllerActionOrigin_PS4_LeftTrigger_Pull = 68,
	k_EControllerActionOrigin_PS4_LeftTrigger_Click = 69,
	k_EControllerActionOrigin_PS4_RightTrigger_Pull = 70,
	k_EControllerActionOrigin_PS4_RightTrigger_Click = 71,
	k_EControllerActionOrigin_PS4_LeftStick_Move = 72,
	k_EControllerActionOrigin_PS4_LeftStick_Click = 73,
	k_EControllerActionOrigin_PS4_LeftStick_DPadNorth = 74,
	k_EControllerActionOrigin_PS4_LeftStick_DPadSouth = 75,
	k_EControllerActionOrigin_PS4_LeftStick_DPadWest = 76,
	k_EControllerActionOrigin_PS4_LeftStick_DPadEast = 77,
	k_EControllerActionOrigin_PS4_RightStick_Move = 78,
	k_EControllerActionOrigin_PS4_RightStick_Click = 79,
	k_EControllerActionOrigin_PS4_RightStick_DPadNorth = 80,
	k_EControllerActionOrigin_PS4_RightStick_DPadSouth = 81,
	k_EControllerActionOrigin_PS4_RightStick_DPadWest = 82,
	k_EControllerActionOrigin_PS4_RightStick_DPadEast = 83,
	k_EControllerActionOrigin_PS4_DPad_North = 84,
	k_EControllerActionOrigin_PS4_DPad_South = 85,
	k_EControllerActionOrigin_PS4_DPad_West = 86,
	k_EControllerActionOrigin_PS4_DPad_East = 87,
	k_EControllerActionOrigin_PS4_Gyro_Move = 88,
	k_EControllerActionOrigin_PS4_Gyro_Pitch = 89,
	k_EControllerActionOrigin_PS4_Gyro_Yaw = 90,
	k_EControllerActionOrigin_PS4_Gyro_Roll = 91,
	k_EControllerActionOrigin_XBoxOne_A = 92,
	k_EControllerActionOrigin_XBoxOne_B = 93,
	k_EControllerActionOrigin_XBoxOne_X = 94,
	k_EControllerActionOrigin_XBoxOne_Y = 95,
	k_EControllerActionOrigin_XBoxOne_LeftBumper = 96,
	k_EControllerActionOrigin_XBoxOne_RightBumper = 97,
	k_EControllerActionOrigin_XBoxOne_Menu = 98,
	k_EControllerActionOrigin_XBoxOne_View = 99,
	k_EControllerActionOrigin_XBoxOne_LeftTrigger_Pull = 100,
	k_EControllerActionOrigin_XBoxOne_LeftTrigger_Click = 101,
	k_EControllerActionOrigin_XBoxOne_RightTrigger_Pull = 102,
	k_EControllerActionOrigin_XBoxOne_RightTrigger_Click = 103,
	k_EControllerActionOrigin_XBoxOne_LeftStick_Move = 104,
	k_EControllerActionOrigin_XBoxOne_LeftStick_Click = 105,
	k_EControllerActionOrigin_XBoxOne_LeftStick_DPadNorth = 106,
	k_EControllerActionOrigin_XBoxOne_LeftStick_DPadSouth = 107,
	k_EControllerActionOrigin_XBoxOne_LeftStick_DPadWest = 108,
	k_EControllerActionOrigin_XBoxOne_LeftStick_DPadEast = 109,
	k_EControllerActionOrigin_XBoxOne_RightStick_Move = 110,
	k_EControllerActionOrigin_XBoxOne_RightStick_Click = 111,
	k_EControllerActionOrigin_XBoxOne_RightStick_DPadNorth = 112,
	k_EControllerActionOrigin_XBoxOne_RightStick_DPadSouth = 113,
	k_EControllerActionOrigin_XBoxOne_RightStick_DPadWest = 114,
	k_EControllerActionOrigin_XBoxOne_RightStick_DPadEast = 115,
	k_EControllerActionOrigin_XBoxOne_DPad_North = 116,
	k_EControllerActionOrigin_XBoxOne_DPad_South = 117,
	k_EControllerActionOrigin_XBoxOne_DPad_West = 118,
	k_EControllerActionOrigin_XBoxOne_DPad_East = 119,
	k_EControllerActionOrigin_XBox360_A = 120,
	k_EControllerActionOrigin_XBox360_B = 121,
	k_EControllerActionOrigin_XBox360_X = 122,
	k_EControllerActionOrigin_XBox360_Y = 123,
	k_EControllerActionOrigin_XBox360_LeftBumper = 124,
	k_EControllerActionOrigin_XBox360_RightBumper = 125,
	k_EControllerActionOrigin_XBox360_Start = 126,
	k_EControllerActionOrigin_XBox360_Back = 127,
	k_EControllerActionOrigin_XBox360_LeftTrigger_Pull = 128,
	k_EControllerActionOrigin_XBox360_LeftTrigger_Click = 129,
	k_EControllerActionOrigin_XBox360_RightTrigger_Pull = 130,
	k_EControllerActionOrigin_XBox360_RightTrigger_Click = 131,
	k_EControllerActionOrigin_XBox360_LeftStick_Move = 132,
	k_EControllerActionOrigin_XBox360_LeftStick_Click = 133,
	k_EControllerActionOrigin_XBox360_LeftStick_DPadNorth = 134,
	k_EControllerActionOrigin_XBox360_LeftStick_DPadSouth = 135,
	k_EControllerActionOrigin_XBox360_LeftStick_DPadWest = 136,
	k_EControllerActionOrigin_XBox360_LeftStick_DPadEast = 137,
	k_EControllerActionOrigin_XBox360_RightStick_Move = 138,
	k_EControllerActionOrigin_XBox360_RightStick_Click = 139,
	k_EControllerActionOrigin_XBox360_RightStick_DPadNorth = 140,
	k_EControllerActionOrigin_XBox360_RightStick_DPadSouth = 141,
	k_EControllerActionOrigin_XBox360_RightStick_DPadWest = 142,
	k_EControllerActionOrigin_XBox360_RightStick_DPadEast = 143,
	k_EControllerActionOrigin_XBox360_DPad_North = 144,
	k_EControllerActionOrigin_XBox360_DPad_South = 145,
	k_EControllerActionOrigin_XBox360_DPad_West = 146,
	k_EControllerActionOrigin_XBox360_DPad_East = 147,
	k_EControllerActionOrigin_SteamV2_A = 148,
	k_EControllerActionOrigin_SteamV2_B = 149,
	k_EControllerActionOrigin_SteamV2_X = 150,
	k_EControllerActionOrigin_SteamV2_Y = 151,
	k_EControllerActionOrigin_SteamV2_LeftBumper = 152,
	k_EControllerActionOrigin_SteamV2_RightBumper = 153,
	k_EControllerActionOrigin_SteamV2_LeftGrip = 154,
	k_EControllerActionOrigin_SteamV2_RightGrip = 155,
	k_EControllerActionOrigin_SteamV2_LeftGrip_Upper = 156,
	k_EControllerActionOrigin_SteamV2_RightGrip_Upper = 157,
	k_EControllerActionOrigin_SteamV2_LeftBumper_Pressure = 158,
	k_EControllerActionOrigin_SteamV2_RightBumper_Pressure = 159,
	k_EControllerActionOrigin_SteamV2_LeftGrip_Pressure = 160,
	k_EControllerActionOrigin_SteamV2_RightGrip_Pressure = 161,
	k_EControllerActionOrigin_SteamV2_LeftGrip_Upper_Pressure = 162,
	k_EControllerActionOrigin_SteamV2_RightGrip_Upper_Pressure = 163,
	k_EControllerActionOrigin_SteamV2_Start = 164,
	k_EControllerActionOrigin_SteamV2_Back = 165,
	k_EControllerActionOrigin_SteamV2_LeftPad_Touch = 166,
	k_EControllerActionOrigin_SteamV2_LeftPad_Swipe = 167,
	k_EControllerActionOrigin_SteamV2_LeftPad_Click = 168,
	k_EControllerActionOrigin_SteamV2_LeftPad_Pressure = 169,
	k_EControllerActionOrigin_SteamV2_LeftPad_DPadNorth = 170,
	k_EControllerActionOrigin_SteamV2_LeftPad_DPadSouth = 171,
	k_EControllerActionOrigin_SteamV2_LeftPad_DPadWest = 172,
	k_EControllerActionOrigin_SteamV2_LeftPad_DPadEast = 173,
	k_EControllerActionOrigin_SteamV2_RightPad_Touch = 174,
	k_EControllerActionOrigin_SteamV2_RightPad_Swipe = 175,
	k_EControllerActionOrigin_SteamV2_RightPad_Click = 176,
	k_EControllerActionOrigin_SteamV2_RightPad_Pressure = 177,
	k_EControllerActionOrigin_SteamV2_RightPad_DPadNorth = 178,
	k_EControllerActionOrigin_SteamV2_RightPad_DPadSouth = 179,
	k_EControllerActionOrigin_SteamV2_RightPad_DPadWest = 180,
	k_EControllerActionOrigin_SteamV2_RightPad_DPadEast = 181,
	k_EControllerActionOrigin_SteamV2_LeftTrigger_Pull = 182,
	k_EControllerActionOrigin_SteamV2_LeftTrigger_Click = 183,
	k_EControllerActionOrigin_SteamV2_RightTrigger_Pull = 184,
	k_EControllerActionOrigin_SteamV2_RightTrigger_Click = 185,
	k_EControllerActionOrigin_SteamV2_LeftStick_Move = 186,
	k_EControllerActionOrigin_SteamV2_LeftStick_Click = 187,
	k_EControllerActionOrigin_SteamV2_LeftStick_DPadNorth = 188,
	k_EControllerActionOrigin_SteamV2_LeftStick_DPadSouth = 189,
	k_EControllerActionOrigin_SteamV2_LeftStick_DPadWest = 190,
	k_EControllerActionOrigin_SteamV2_LeftStick_DPadEast = 191,
	k_EControllerActionOrigin_SteamV2_Gyro_Move = 192,
	k_EControllerActionOrigin_SteamV2_Gyro_Pitch = 193,
	k_EControllerActionOrigin_SteamV2_Gyro_Yaw = 194,
	k_EControllerActionOrigin_SteamV2_Gyro_Roll = 195,
	k_EControllerActionOrigin_Count = 196,
} EControllerActionOrigin;

typedef enum ESteamControllerLEDFlag {
	k_ESteamControllerLEDFlag_SetColor = 0,
	k_ESteamControllerLEDFlag_RestoreUserDefault = 1,
} ESteamControllerLEDFlag;

typedef enum ESteamInputType {
	k_ESteamInputType_Unknown = 0,
	k_ESteamInputType_SteamController = 1,
	k_ESteamInputType_XBox360Controller = 2,
	k_ESteamInputType_XBoxOneController = 3,
	k_ESteamInputType_GenericXInput = 4,
	k_ESteamInputType_PS4Controller = 5,
} ESteamInputType;

typedef enum EUGCMatchingUGCType {
	k_EUGCMatchingUGCType_Items = 0,
	k_EUGCMatchingUGCType_Items_Mtx = 1,
	k_EUGCMatchingUGCType_Items_ReadyToUse = 2,
	k_EUGCMatchingUGCType_Collections = 3,
	k_EUGCMatchingUGCType_Artwork = 4,
	k_EUGCMatchingUGCType_Videos = 5,
	k_EUGCMatchingUGCType_Screenshots = 6,
	k_EUGCMatchingUGCType_AllGuides = 7,
	k_EUGCMatchingUGCType_WebGuides = 8,
	k_EUGCMatchingUGCType_IntegratedGuides = 9,
	k_EUGCMatchingUGCType_UsableInGame = 10,
	k_EUGCMatchingUGCType_ControllerBindings = 11,
	k_EUGCMatchingUGCType_GameManagedItems = 12,
	k_EUGCMatchingUGCType_All = -1,
} EUGCMatchingUGCType;

typedef enum EUserUGCList {
	k_EUserUGCList_Published = 0,
	k_EUserUGCList_VotedOn = 1,
	k_EUserUGCList_VotedUp = 2,
	k_EUserUGCList_VotedDown = 3,
	k_EUserUGCList_WillVoteLater = 4,
	k_EUserUGCList_Favorited = 5,
	k_EUserUGCList_Subscribed = 6,
	k_EUserUGCList_UsedOrPlayed = 7,
	k_EUserUGCList_Followed = 8,
} EUserUGCList;

typedef enum EUserUGCListSortOrder {
	k_EUserUGCListSortOrder_CreationOrderDesc = 0,
	k_EUserUGCListSortOrder_CreationOrderAsc = 1,
	k_EUserUGCListSortOrder_TitleAsc = 2,
	k_EUserUGCListSortOrder_LastUpdatedDesc = 3,
	k_EUserUGCListSortOrder_SubscriptionDateDesc = 4,
	k_EUserUGCListSortOrder_VoteScoreDesc = 5,
	k_EUserUGCListSortOrder_ForModeration = 6,
} EUserUGCListSortOrder;

typedef enum EUGCQuery {
	k_EUGCQuery_RankedByVote = 0,
	k_EUGCQuery_RankedByPublicationDate = 1,
	k_EUGCQuery_AcceptedForGameRankedByAcceptanceDate = 2,
	k_EUGCQuery_RankedByTrend = 3,
	k_EUGCQuery_FavoritedByFriendsRankedByPublicationDate = 4,
	k_EUGCQuery_CreatedByFriendsRankedByPublicationDate = 5,
	k_EUGCQuery_RankedByNumTimesReported = 6,
	k_EUGCQuery_CreatedByFollowedUsersRankedByPublicationDate = 7,
	k_EUGCQuery_NotYetRated = 8,
	k_EUGCQuery_RankedByTotalVotesAsc = 9,
	k_EUGCQuery_RankedByVotesUp = 10,
	k_EUGCQuery_RankedByTextSearch = 11,
	k_EUGCQuery_RankedByTotalUniqueSubscriptions = 12,
	k_EUGCQuery_RankedByPlaytimeTrend = 13,
	k_EUGCQuery_RankedByTotalPlaytime = 14,
	k_EUGCQuery_RankedByAveragePlaytimeTrend = 15,
	k_EUGCQuery_RankedByLifetimeAveragePlaytime = 16,
	k_EUGCQuery_RankedByPlaytimeSessionsTrend = 17,
	k_EUGCQuery_RankedByLifetimePlaytimeSessions = 18,
} EUGCQuery;

typedef enum EItemUpdateStatus {
	k_EItemUpdateStatusInvalid = 0,
	k_EItemUpdateStatusPreparingConfig = 1,
	k_EItemUpdateStatusPreparingContent = 2,
	k_EItemUpdateStatusUploadingContent = 3,
	k_EItemUpdateStatusUploadingPreviewFile = 4,
	k_EItemUpdateStatusCommittingChanges = 5,
} EItemUpdateStatus;

typedef enum EItemState {
	k_EItemStateNone = 0,
	k_EItemStateSubscribed = 1,
	k_EItemStateLegacyItem = 2,
	k_EItemStateInstalled = 4,
	k_EItemStateNeedsUpdate = 8,
	k_EItemStateDownloading = 16,
	k_EItemStateDownloadPending = 32,
} EItemState;

typedef enum EItemStatistic {
	k_EItemStatistic_NumSubscriptions = 0,
	k_EItemStatistic_NumFavorites = 1,
	k_EItemStatistic_NumFollowers = 2,
	k_EItemStatistic_NumUniqueSubscriptions = 3,
	k_EItemStatistic_NumUniqueFavorites = 4,
	k_EItemStatistic_NumUniqueFollowers = 5,
	k_EItemStatistic_NumUniqueWebsiteViews = 6,
	k_EItemStatistic_ReportScore = 7,
	k_EItemStatistic_NumSecondsPlayed = 8,
	k_EItemStatistic_NumPlaytimeSessions = 9,
	k_EItemStatistic_NumComments = 10,
	k_EItemStatistic_NumSecondsPlayedDuringTimePeriod = 11,
	k_EItemStatistic_NumPlaytimeSessionsDuringTimePeriod = 12,
} EItemStatistic;

typedef enum EItemPreviewType {
	k_EItemPreviewType_Image = 0,
	k_EItemPreviewType_YouTubeVideo = 1,
	k_EItemPreviewType_Sketchfab = 2,
	k_EItemPreviewType_EnvironmentMap_HorizontalCross = 3,
	k_EItemPreviewType_EnvironmentMap_LatLong = 4,
	k_EItemPreviewType_ReservedMax = 255,
} EItemPreviewType;

typedef enum EHTMLMouseButton {
	eHTMLMouseButton_Left = 0,
	eHTMLMouseButton_Right = 1,
	eHTMLMouseButton_Middle = 2,
} EHTMLMouseButton;

typedef enum EMouseCursor {
	dc_user = 0,
	dc_none = 1,
	dc_arrow = 2,
	dc_ibeam = 3,
	dc_hourglass = 4,
	dc_waitarrow = 5,
	dc_crosshair = 6,
	dc_up = 7,
	dc_sizenw = 8,
	dc_sizese = 9,
	dc_sizene = 10,
	dc_sizesw = 11,
	dc_sizew = 12,
	dc_sizee = 13,
	dc_sizen = 14,
	dc_sizes = 15,
	dc_sizewe = 16,
	dc_sizens = 17,
	dc_sizeall = 18,
	dc_no = 19,
	dc_hand = 20,
	dc_blank = 21,
	dc_middle_pan = 22,
	dc_north_pan = 23,
	dc_north_east_pan = 24,
	dc_east_pan = 25,
	dc_south_east_pan = 26,
	dc_south_pan = 27,
	dc_south_west_pan = 28,
	dc_west_pan = 29,
	dc_north_west_pan = 30,
	dc_alias = 31,
	dc_cell = 32,
	dc_colresize = 33,
	dc_copycur = 34,
	dc_verticaltext = 35,
	dc_rowresize = 36,
	dc_zoomin = 37,
	dc_zoomout = 38,
	dc_help = 39,
	dc_custom = 40,
	dc_last = 41,
} EMouseCursor;

typedef enum EHTMLKeyModifiers {
	k_eHTMLKeyModifier_None = 0,
	k_eHTMLKeyModifier_AltDown = 1,
	k_eHTMLKeyModifier_CtrlDown = 2,
	k_eHTMLKeyModifier_ShiftDown = 4,
} EHTMLKeyModifiers;

typedef enum ESteamItemFlags {
	k_ESteamItemNoTrade = 1,
	k_ESteamItemRemoved = 256,
	k_ESteamItemConsumed = 512,
} ESteamItemFlags;

typedef enum EParentalFeature {
	k_EFeatureInvalid = 0,
	k_EFeatureStore = 1,
	k_EFeatureCommunity = 2,
	k_EFeatureProfile = 3,
	k_EFeatureFriends = 4,
	k_EFeatureNews = 5,
	k_EFeatureTrading = 6,
	k_EFeatureSettings = 7,
	k_EFeatureConsole = 8,
	k_EFeatureBrowser = 9,
	k_EFeatureParentalSetup = 10,
	k_EFeatureLibrary = 11,
	k_EFeatureTest = 12,
	k_EFeatureMax = 13,
} EParentalFeature;

typedef struct {
	uint32 m_unAccountID;
	unsigned int m_unAccountInstance;
	unsigned int m_EAccountType;
	enum EUniverse m_EUniverse;
} SteamIDComponent_t;

typedef struct {
	SteamIDComponent_t m_comp;
	uint64 m_unAll64Bits;
} SteamID_t;

typedef struct {
	unsigned int m_nAppID;
	unsigned int m_nType;
	unsigned int m_nModID;
} GameID_t;

typedef struct {
	HSteamUser m_hSteamUser;
	int m_iCallback;
	uint8 * m_pubParam;
	int m_cubParam;
} CallbackMsg_t;

typedef struct { 
	enum EResult m_eResult;
	_Bool m_bStillRetrying;
} SteamServerConnectFailure_t;

typedef struct {
	enum EResult m_eResult;
} SteamServersDisconnected_t;

typedef struct {
	uint32 m_uAppID;
	uint32 m_unGameServerIP;
	uint16 m_usGameServerPort;
	uint16 m_bSecure;
	uint32 m_uReason;
} ClientGameServerDeny_t;

typedef struct {
	CSteamID m_SteamID;
	enum EAuthSessionResponse m_eAuthSessionResponse;
	CSteamID m_OwnerSteamID;
} ValidateAuthTicketResponse_t;

typedef struct {
	uint32 m_unAppID;
	uint64 m_ulOrderID;
	uint8 m_bAuthorized;
} MicroTxnAuthorizationResponse_t;

typedef struct {
	enum EResult m_eResult;
} EncryptedAppTicketResponse_t;

typedef struct {
	HAuthTicket m_hAuthTicket;
	enum EResult m_eResult;
} GetAuthSessionTicketResponse_t;

typedef struct {
	char m_szURL[256];
} GameWebCallback_t;

typedef struct {
	char m_szURL[512];
} StoreAuthURLResponse_t;

typedef struct CGameID {
	unsigned int m_nAppID;
	unsigned int m_nType;
	unsigned int m_nModID;
	uint64 m_ulGameID;
	//struct GameID_t m_gameID;
	GameID_t m_gameID;
} CGameID;

typedef struct {
	CGameID m_gameID;
	uint32 m_unGameIP;
	uint16 m_usGamePort;
	uint16 m_usQueryPort;
	CSteamID m_steamIDLobby;
} FriendGameInfo_t;

typedef struct {
	uint32 m_uiOnlineSessionInstances;
	uint8 m_uiPublishedToFriendsSessionInstance;
} FriendSessionStateInfo_t;

typedef struct {
	uint64 m_ulSteamID;
	int m_nChangeFlags;
} PersonaStateChange_t;

typedef struct {
	uint8 m_bActive;
} GameOverlayActivated_t;

typedef struct {
	char m_rgchServer[64];
	char m_rgchPassword[64];
} GameServerChangeRequested_t;

typedef struct {
	CSteamID m_steamIDLobby;
	CSteamID m_steamIDFriend;
} GameLobbyJoinRequested_t;

typedef struct {
	CSteamID m_steamID;
	int m_iImage;
	int m_iWide;
	int m_iTall;
} AvatarImageLoaded_t;

typedef struct {
	CSteamID m_steamIDClan;
	int m_cOfficers;
	uint8 m_bSuccess;
} ClanOfficerListResponse_t;

typedef struct {
	CSteamID m_steamIDFriend;
	AppId_t m_nAppID;
} FriendRichPresenceUpdate_t;

typedef struct {
	CSteamID m_steamIDFriend;
	char m_rgchConnect[256];
} GameRichPresenceJoinRequested_t;

typedef struct {
	CSteamID m_steamIDClanChat;
	CSteamID m_steamIDUser;
	int m_iMessageID;
} GameConnectedClanChatMsg_t;

typedef struct {
	CSteamID m_steamIDClanChat;
	CSteamID m_steamIDUser;
} GameConnectedChatJoin_t;

typedef struct {
	CSteamID m_steamIDClanChat;
	CSteamID m_steamIDUser;
	_Bool m_bKicked;
	_Bool m_bDropped;
} GameConnectedChatLeave_t;

typedef struct {
	_Bool m_bSuccess;
} DownloadClanActivityCountsResult_t;

typedef struct {
	CSteamID m_steamIDClanChat;
	enum EChatRoomEnterResponse m_eChatRoomEnterResponse;
} JoinClanChatRoomCompletionResult_t;

typedef struct {
	CSteamID m_steamIDUser;
	int m_iMessageID;
} GameConnectedFriendChatMsg_t;

typedef struct {
	enum EResult m_eResult;
	CSteamID m_steamID;
	int m_nCount;
} FriendsGetFollowerCount_t;

typedef struct {
	enum EResult m_eResult;
	CSteamID m_steamID;
	_Bool m_bIsFollowing;
} FriendsIsFollowing_t;

typedef struct {
	enum EResult m_eResult;
	CSteamID m_rgSteamID[50];
	int32 m_nResultsReturned;
	int32 m_nTotalResultCount;
} FriendsEnumerateFollowingList_t;

typedef struct {
	_Bool m_bSuccess;
	_Bool m_bLocalSuccess;
	enum EResult m_result;
} SetPersonaNameResponse_t;

typedef struct {
	uint8 m_nMinutesBatteryLeft;
} LowBatteryPower_t;

typedef struct {
	SteamAPICall_t m_hAsyncCall;
	int m_iCallback;
	uint32 m_cubParam;
} SteamAPICallCompleted_t;

typedef struct {
	enum ECheckFileSignature m_eCheckFileSignature;
} CheckFileSignature_t;

typedef struct {
	_Bool m_bSubmitted;
	uint32 m_unSubmittedText;
} GamepadTextInputDismissed_t;

typedef struct {
	char m_szKey[256];
	char m_szValue[256];
} MatchMakingKeyValuePair_t;

typedef struct {
	uint16 m_usConnectionPort;
	uint16 m_usQueryPort;
	uint32 m_unIP;
} servernetadr_t;

typedef struct {
	servernetadr_t m_NetAdr;
	int m_nPing;
	_Bool m_bHadSuccessfulResponse;
	_Bool m_bDoNotRefresh;
	char m_szGameDir[32];
	char m_szMap[32];
	char m_szGameDescription[64];
	uint32 m_nAppID;
	int m_nPlayers;
	int m_nMaxPlayers;
	int m_nBotPlayers;
	_Bool m_bPassword;
	_Bool m_bSecure;
	uint32 m_ulTimeLastPlayed;
	int m_nServerVersion;
	char m_szServerName[64];
	char m_szGameTags[128];
	CSteamID m_steamID;
} gameserveritem_t;

typedef struct {
	uint32 m_nIP;
	uint32 m_nQueryPort;
	uint32 m_nConnPort;
	uint32 m_nAppID;
	uint32 m_nFlags;
	_Bool m_bAdd;
	AccountID_t m_unAccountId;
} FavoritesListChanged_t;

typedef struct {
	uint64 m_ulSteamIDUser;
	uint64 m_ulSteamIDLobby;
	uint64 m_ulGameID;
} LobbyInvite_t;

typedef struct {
	uint64 m_ulSteamIDLobby;
	uint32 m_rgfChatPermissions;
	_Bool m_bLocked;
	uint32 m_EChatRoomEnterResponse;
} LobbyEnter_t;

typedef struct {
	uint64 m_ulSteamIDLobby;
	uint64 m_ulSteamIDMember;
	uint8 m_bSuccess;
} LobbyDataUpdate_t;

typedef struct {
	uint64 m_ulSteamIDLobby;
	uint64 m_ulSteamIDUserChanged;
	uint64 m_ulSteamIDMakingChange;
	uint32 m_rgfChatMemberStateChange;
} LobbyChatUpdate_t;

typedef struct {
	uint64 m_ulSteamIDLobby;
	uint64 m_ulSteamIDUser;
	uint8 m_eChatEntryType;
	uint32 m_iChatID;
} LobbyChatMsg_t;

typedef struct {
	uint64 m_ulSteamIDLobby;
	uint64 m_ulSteamIDGameServer;
	uint32 m_unIP;
	uint16 m_usPort;
} LobbyGameCreated_t;

typedef struct {
	uint32 m_nLobbiesMatching;
} LobbyMatchList_t;

typedef struct {
	uint64 m_ulSteamIDLobby;
	uint64 m_ulSteamIDAdmin;
	uint8 m_bKickedDueToDisconnect;
} LobbyKicked_t;

typedef struct {
	enum EResult m_eResult;
	uint64 m_ulSteamIDLobby;
} LobbyCreated_t;

typedef struct {
	_Bool m_bGameBootInviteExists;
	CSteamID m_steamIDLobby;
} PSNGameBootInviteResult_t;

typedef struct {
	enum EResult m_eResult;
} FavoritesListAccountsUpdated_t;

typedef struct {
	const char ** m_ppStrings;
	int32 m_nNumStrings;
} SteamParamStringArray_t;

typedef struct {
	AppId_t m_nAppID;
	enum EResult m_eResult;
	int m_unNumDownloads;
} RemoteStorageAppSyncedClient_t;

typedef struct {
	AppId_t m_nAppID;
	enum EResult m_eResult;
	int m_unNumUploads;
} RemoteStorageAppSyncedServer_t;

typedef struct {
	char m_rgchCurrentFile[260];
	AppId_t m_nAppID;
	uint32 m_uBytesTransferredThisChunk;
	double m_dAppPercentComplete;
	_Bool m_bUploading;
} RemoteStorageAppSyncProgress_t;

typedef struct {
	AppId_t m_nAppID;
	enum EResult m_eResult;
} RemoteStorageAppSyncStatusCheck_t;

typedef struct {
	enum EResult m_eResult;
	UGCHandle_t m_hFile;
	char m_rgchFilename[260];
} RemoteStorageFileShareResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	_Bool m_bUserNeedsToAcceptWorkshopLegalAgreement;
} RemoteStoragePublishFileResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
} RemoteStorageDeletePublishedFileResult_t;

typedef struct {
	enum EResult m_eResult;
	int32 m_nResultsReturned;
	int32 m_nTotalResultCount;
	PublishedFileId_t m_rgPublishedFileId[50];
} RemoteStorageEnumerateUserPublishedFilesResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
} RemoteStorageSubscribePublishedFileResult_t;

typedef struct {
	enum EResult m_eResult;
	int32 m_nResultsReturned;
	int32 m_nTotalResultCount;
	PublishedFileId_t m_rgPublishedFileId[50];
	uint32 m_rgRTimeSubscribed[50];
} RemoteStorageEnumerateUserSubscribedFilesResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
} RemoteStorageUnsubscribePublishedFileResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	_Bool m_bUserNeedsToAcceptWorkshopLegalAgreement;
} RemoteStorageUpdatePublishedFileResult_t;

typedef struct {
	enum EResult m_eResult;
	UGCHandle_t m_hFile;
	AppId_t m_nAppID;
	int32 m_nSizeInBytes;
	char m_pchFileName[260];
	uint64 m_ulSteamIDOwner;
} RemoteStorageDownloadUGCResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	AppId_t m_nCreatorAppID;
	AppId_t m_nConsumerAppID;
	char m_rgchTitle[129];
	char m_rgchDescription[8000];
	UGCHandle_t m_hFile;
	UGCHandle_t m_hPreviewFile;
	uint64 m_ulSteamIDOwner;
	uint32 m_rtimeCreated;
	uint32 m_rtimeUpdated;
	enum ERemoteStoragePublishedFileVisibility m_eVisibility;
	_Bool m_bBanned;
	char m_rgchTags[1025];
	_Bool m_bTagsTruncated;
	char m_pchFileName[260];
	int32 m_nFileSize;
	int32 m_nPreviewFileSize;
	char m_rgchURL[256];
	enum EWorkshopFileType m_eFileType;
	_Bool m_bAcceptedForUse;
} RemoteStorageGetPublishedFileDetailsResult_t;

typedef struct {
	enum EResult m_eResult;
	int32 m_nResultsReturned;
	int32 m_nTotalResultCount;
	PublishedFileId_t m_rgPublishedFileId[50] ;
	float m_rgScore[50];
	AppId_t m_nAppId;
	uint32 m_unStartIndex;
} RemoteStorageEnumerateWorkshopFilesResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_unPublishedFileId;
	int32 m_nVotesFor;
	int32 m_nVotesAgainst;
	int32 m_nReports;
	float m_fScore;
} RemoteStorageGetPublishedItemVoteDetailsResult_t;

typedef struct {
	PublishedFileId_t m_nPublishedFileId;
	AppId_t m_nAppID;
} RemoteStoragePublishedFileSubscribed_t;

typedef struct {
	PublishedFileId_t m_nPublishedFileId;
	AppId_t m_nAppID;
} RemoteStoragePublishedFileUnsubscribed_t;

typedef struct {
	PublishedFileId_t m_nPublishedFileId;
	AppId_t m_nAppID;
} RemoteStoragePublishedFileDeleted_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
} RemoteStorageUpdateUserPublishedItemVoteResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	enum EWorkshopVote m_eVote;
} RemoteStorageUserVoteDetails_t;

typedef struct {
	enum EResult m_eResult;
	int32 m_nResultsReturned;
	int32 m_nTotalResultCount;
	PublishedFileId_t m_rgPublishedFileId[50];
} RemoteStorageEnumerateUserSharedWorkshopFilesResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	enum EWorkshopFileAction m_eAction;
} RemoteStorageSetUserPublishedFileActionResult_t;

typedef struct {
	enum EResult m_eResult;
	enum EWorkshopFileAction m_eAction;
	int32 m_nResultsReturned;
	int32 m_nTotalResultCount;
	PublishedFileId_t m_rgPublishedFileId[50];
	uint32 m_rgRTimeUpdated[50];
} RemoteStorageEnumeratePublishedFilesByUserActionResult_t;

typedef struct {
	double m_dPercentFile;
	_Bool m_bPreview;
} RemoteStoragePublishFileProgress_t;

typedef struct {
	PublishedFileId_t m_nPublishedFileId;
	AppId_t m_nAppID;
	uint64 m_ulUnused;
} RemoteStoragePublishedFileUpdated_t;

typedef struct {
	enum EResult m_eResult;
} RemoteStorageFileWriteAsyncComplete_t;

typedef struct {
	SteamAPICall_t m_hFileReadAsync;
	enum EResult m_eResult;
	uint32 m_nOffset;
	uint32 m_cubRead;
} RemoteStorageFileReadAsyncComplete_t;

typedef struct {
	CSteamID m_steamIDUser;
	int32 m_nGlobalRank;
	int32 m_nScore;
	int32 m_cDetails;
	UGCHandle_t m_hUGC;
} LeaderboardEntry_t;

typedef struct {
	uint64 m_nGameID;
	enum EResult m_eResult;
	CSteamID m_steamIDUser;
} UserStatsReceived_t;

typedef struct {
	uint64 m_nGameID;
	enum EResult m_eResult;
} UserStatsStored_t;

typedef struct {
	uint64 m_nGameID;
	_Bool m_bGroupAchievement;
	char m_rgchAchievementName[128];
	uint32 m_nCurProgress;
	uint32 m_nMaxProgress;
} UserAchievementStored_t;

typedef struct {
	SteamLeaderboard_t m_hSteamLeaderboard;
	uint8 m_bLeaderboardFound;
} LeaderboardFindResult_t;

typedef struct {
	SteamLeaderboard_t m_hSteamLeaderboard;
	SteamLeaderboardEntries_t m_hSteamLeaderboardEntries;
	int m_cEntryCount;
} LeaderboardScoresDownloaded_t;

typedef struct {
	uint8 m_bSuccess;
	SteamLeaderboard_t m_hSteamLeaderboard;
	int32 m_nScore;
	uint8 m_bScoreChanged;
	int m_nGlobalRankNew;
	int m_nGlobalRankPrevious;
} LeaderboardScoreUploaded_t;

typedef struct {
	uint8 m_bSuccess;
	int32 m_cPlayers;
} NumberOfCurrentPlayers_t;

typedef struct {
	CSteamID m_steamIDUser;
} UserStatsUnloaded_t;

typedef struct {
	CGameID m_nGameID;
	char m_rgchAchievementName[128];
	_Bool m_bAchieved;
	int m_nIconHandle;
} UserAchievementIconFetched_t;

typedef struct {
	uint64 m_nGameID;
	enum EResult m_eResult;
} GlobalAchievementPercentagesReady_t;

typedef struct {
	enum EResult m_eResult;
	SteamLeaderboard_t m_hSteamLeaderboard;
} LeaderboardUGCSet_t;

typedef struct {
	uint64 m_nGameID;
	enum EResult m_eResult;
	uint64 m_ulRequiredDiskSpace;
} PS3TrophiesInstalled_t;

typedef struct {
	uint64 m_nGameID;
	enum EResult m_eResult;
} GlobalStatsReceived_t;

typedef struct {
	AppId_t m_nAppID;
} DlcInstalled_t;

typedef struct {
	enum ERegisterActivationCodeResult m_eResult;
	uint32 m_unPackageRegistered;
} RegisterActivationCodeResponse_t;

typedef struct {
	enum EResult m_eResult;
	uint32 m_nAppID;
	uint32 m_cchKeyLength;
	char m_rgchKey[240];
} AppProofOfPurchaseKeyResponse_t;

typedef struct {
	enum EResult m_eResult;
	uint64 m_ulFileSize;
	uint8 m_FileSHA[20] ;
	uint32 m_unFlags;
} FileDetailsResult_t;

typedef struct {
	uint8 m_bConnectionActive;
	uint8 m_bConnecting;
	uint8 m_eP2PSessionError;
	uint8 m_bUsingRelay;
	int32 m_nBytesQueuedForSend;
	int32 m_nPacketsQueuedForSend;
	uint32 m_nRemoteIP;
	uint16 m_nRemotePort;
} P2PSessionState_t;

typedef struct {
	CSteamID m_steamIDRemote;
} P2PSessionRequest_t;

typedef struct {
	CSteamID m_steamIDRemote;
	uint8 m_eP2PSessionError;
} P2PSessionConnectFail_t;

typedef struct {
	SNetSocket_t m_hSocket;
	SNetListenSocket_t m_hListenSocket;
	CSteamID m_steamIDRemote;
	int m_eSNetSocketState;
} SocketStatusCallback_t;

typedef struct {
	ScreenshotHandle m_hLocal;
	enum EResult m_eResult;
} ScreenshotReady_t;

typedef struct {
	float m_flNewVolume;
} VolumeHasChanged_t;

typedef struct {
	_Bool m_bShuffled;
} MusicPlayerWantsShuffled_t;

typedef struct {
	_Bool m_bLooped;
} MusicPlayerWantsLooped_t;

typedef struct {
	float m_flNewVolume;
} MusicPlayerWantsVolume_t;

typedef struct {
	int nID;
} MusicPlayerSelectsQueueEntry_t;

typedef struct {
	int nID;
} MusicPlayerSelectsPlaylistEntry_t;

typedef struct {
	int m_nPlayingRepeatStatus;
} MusicPlayerWantsPlayingRepeatStatus_t;

typedef struct {
	HTTPRequestHandle m_hRequest;
	uint64 m_ulContextValue;
	_Bool m_bRequestSuccessful;
	enum EHTTPStatusCode m_eStatusCode;
	uint32 m_unBodySize;
} HTTPRequestCompleted_t;

typedef struct {
	HTTPRequestHandle m_hRequest;
	uint64 m_ulContextValue;
} HTTPRequestHeadersReceived_t;

typedef struct {
	HTTPRequestHandle m_hRequest;
	uint64 m_ulContextValue;
	uint32 m_cOffset;
	uint32 m_cBytesReceived;
} HTTPRequestDataReceived_t;

typedef struct {
	enum EControllerSourceMode eMode;
	float x;
	float y;
	_Bool bActive;
} ControllerAnalogActionData_t;

typedef struct {
	_Bool bState;
	_Bool bActive;
} ControllerDigitalActionData_t;

typedef struct {
	float rotQuatX;
	float rotQuatY;
	float rotQuatZ;
	float rotQuatW;
	float posAccelX;
	float posAccelY;
	float posAccelZ;
	float rotVelX;
	float rotVelY;
	float rotVelZ;
} ControllerMotionData_t;

typedef struct {
	PublishedFileId_t m_nPublishedFileId;
	enum EResult m_eResult;
	enum EWorkshopFileType m_eFileType;
	AppId_t m_nCreatorAppID;
	AppId_t m_nConsumerAppID;
	char m_rgchTitle[129];
	char m_rgchDescription[8000];
	uint64 m_ulSteamIDOwner;
	uint32 m_rtimeCreated;
	uint32 m_rtimeUpdated;
	uint32 m_rtimeAddedToUserList;
	enum ERemoteStoragePublishedFileVisibility m_eVisibility;
	_Bool m_bBanned;
	_Bool m_bAcceptedForUse;
	_Bool m_bTagsTruncated;
	char m_rgchTags[1025];
	UGCHandle_t m_hFile;
	UGCHandle_t m_hPreviewFile;
	char m_pchFileName[260];
	int32 m_nFileSize;
	int32 m_nPreviewFileSize;
	char m_rgchURL[256];
	uint32 m_unVotesUp;
	uint32 m_unVotesDown;
	float m_flScore;
	uint32 m_unNumChildren;
} SteamUGCDetails_t;

typedef struct {
	UGCQueryHandle_t m_handle;
	enum EResult m_eResult;
	uint32 m_unNumResultsReturned;
	uint32 m_unTotalMatchingResults;
	_Bool m_bCachedData;
} SteamUGCQueryCompleted_t;

typedef struct {
	SteamUGCDetails_t m_details;
	_Bool m_bCachedData;
} SteamUGCRequestUGCDetailsResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	_Bool m_bUserNeedsToAcceptWorkshopLegalAgreement;
} CreateItemResult_t;

typedef struct {
	enum EResult m_eResult;
	_Bool m_bUserNeedsToAcceptWorkshopLegalAgreement;
	PublishedFileId_t m_nPublishedFileId;
} SubmitItemUpdateResult_t;

typedef struct {
	AppId_t m_unAppID;
	PublishedFileId_t m_nPublishedFileId;
	enum EResult m_eResult;
} DownloadItemResult_t;

typedef struct {
	PublishedFileId_t m_nPublishedFileId;
	enum EResult m_eResult;
	_Bool m_bWasAddRequest;
} UserFavoriteItemsListChanged_t;

typedef struct {
	PublishedFileId_t m_nPublishedFileId;
	enum EResult m_eResult;
	_Bool m_bVoteUp;
} SetUserItemVoteResult_t;

typedef struct {
	PublishedFileId_t m_nPublishedFileId;
	enum EResult m_eResult;
	_Bool m_bVotedUp;
	_Bool m_bVotedDown;
	_Bool m_bVoteSkipped;
} GetUserItemVoteResult_t;

typedef struct {
	enum EResult m_eResult;
} StartPlaytimeTrackingResult_t;

typedef struct {
	enum EResult m_eResult;
} StopPlaytimeTrackingResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	PublishedFileId_t m_nChildPublishedFileId;
} AddUGCDependencyResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	PublishedFileId_t m_nChildPublishedFileId;
} RemoveUGCDependencyResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	AppId_t m_nAppID;
} AddAppDependencyResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	AppId_t m_nAppID;
} RemoveAppDependencyResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
	AppId_t m_rgAppIDs[32];
	uint32 m_nNumAppDependencies;
	uint32 m_nTotalNumAppDependencies;
} GetAppDependenciesResult_t;

typedef struct {
	enum EResult m_eResult;
	PublishedFileId_t m_nPublishedFileId;
} DeleteItemResult_t;

typedef struct {
	AppId_t m_nAppID;
} SteamAppInstalled_t;

typedef struct {
	AppId_t m_nAppID;
} SteamAppUninstalled_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
} HTML_BrowserReady_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pBGRA;
	uint32 unWide;
	uint32 unTall;
	uint32 unUpdateX;
	uint32 unUpdateY;
	uint32 unUpdateWide;
	uint32 unUpdateTall;
	uint32 unScrollX;
	uint32 unScrollY;
	float flPageScale;
	uint32 unPageSerial;
} HTML_NeedsPaint_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchURL;
	const char * pchTarget;
	const char * pchPostData;
	_Bool bIsRedirect;
} HTML_StartRequest_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
} HTML_CloseBrowser_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchURL;
	const char * pchPostData;
	_Bool bIsRedirect;
	const char * pchPageTitle;
	_Bool bNewNavigation;
} HTML_URLChanged_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchURL;
	const char * pchPageTitle;
} HTML_FinishedRequest_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchURL;
} HTML_OpenLinkInNewTab_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchTitle;
} HTML_ChangedTitle_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	uint32 unResults;
	uint32 unCurrentMatch;
} HTML_SearchResults_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	_Bool bCanGoBack;
	_Bool bCanGoForward;
} HTML_CanGoBackAndForward_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	uint32 unScrollMax;
	uint32 unScrollCurrent;
	float flPageScale;
	_Bool bVisible;
	uint32 unPageSize;
} HTML_HorizontalScroll_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	uint32 unScrollMax;
	uint32 unScrollCurrent;
	float flPageScale;
	_Bool bVisible;
	uint32 unPageSize;
} HTML_VerticalScroll_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	uint32 x;
	uint32 y;
	const char * pchURL;
	_Bool bInput;
	_Bool bLiveLink;
} HTML_LinkAtPosition_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchMessage;
} HTML_JSAlert_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchMessage;
} HTML_JSConfirm_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchTitle;
	const char * pchInitialFile;
} HTML_FileOpenDialog_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchURL;
	uint32 unX;
	uint32 unY;
	uint32 unWide;
	uint32 unTall;
	HHTMLBrowser unNewWindow_BrowserHandle;
} HTML_NewWindow_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	uint32 eMouseCursor;
} HTML_SetCursor_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchMsg;
} HTML_StatusText_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchMsg;
} HTML_ShowToolTip_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	const char * pchMsg;
} HTML_UpdateToolTip_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
} HTML_HideToolTip_t;

typedef struct {
	HHTMLBrowser unBrowserHandle;
	HHTMLBrowser unOldBrowserHandle;
} HTML_BrowserRestarted_t;

typedef struct {
	SteamItemInstanceID_t m_itemId;
	SteamItemDef_t m_iDefinition;
	uint16 m_unQuantity;
	uint16 m_unFlags;
} SteamItemDetails_t;

typedef struct {
	SteamInventoryResult_t m_handle;
	enum EResult m_result;
} SteamInventoryResultReady_t;

typedef struct {
	SteamInventoryResult_t m_handle;
} SteamInventoryFullUpdate_t;

typedef struct {
	enum EResult m_result;
	CSteamID m_steamID;
	int m_numEligiblePromoItemDefs;
	_Bool m_bCachedData;
} SteamInventoryEligiblePromoItemDefIDs_t;

typedef struct {
	enum EResult m_result;
	uint64 m_ulOrderID;
	uint64 m_ulTransID;
} SteamInventoryStartPurchaseResult_t;

typedef struct {
	enum EResult m_result;
	char m_rgchCurrency[4];
} SteamInventoryRequestPricesResult_t;

typedef struct {
	enum EBroadcastUploadResult m_eResult;
} BroadcastUploadStop_t;

typedef struct {
	enum EResult m_eResult;
	AppId_t m_unVideoAppID;
	char m_rgchURL[256];
} GetVideoURLResult_t;

typedef struct {
	enum EResult m_eResult;
	AppId_t m_unVideoAppID;
} GetOPFSettingsResult_t;

#define ISteamUser void
#define ISteamFriends void
#define ISteamUtils void
#define ISteamMatchmaking void
#define ISteamUserStats void
#define ISteamApps void
#define ISteamMatchmakingServers void
#define ISteamNetworking void
#define ISteamRemoteStorage void
#define ISteamScreenshots void
#define ISteamHTTP void
#define ISteamController void
#define ISteamUGC void
#define ISteamAppList void
#define ISteamMusic void
#define ISteamMusicRemote void
#define ISteamHTMLSurface void
#define ISteamInventory void
#define ISteamVideo void
#define ISteamParentalSettings void
#define ISteamGameServer void
#define ISteamGameServerStats  void
#define ISteamMatchmakingServerListResponse void
#define ISteamMatchmakingPingResponse  void
#define ISteamMatchmakingPlayersResponse  void
#define ISteamMatchmakingRulesResponse   void

typedef struct {
	uint8 m_nCallbackFlags;
	int m_iCallback;
} CCallbackBase;

typedef struct {
	SteamAPICall_t m_hAPICall;
	void * m_pObj;
	void(*m_func)(void *, _Bool);
} CCallResult;

typedef struct {
	void * m_pObj;
	void(*m_func)(void *);
} CCallback;

typedef struct {
	CSteamID m_SteamID;
	CSteamID m_OwnerSteamID;
} GSClientApprove_t;

typedef struct {
	CSteamID m_SteamID;
	enum EDenyReason m_eDenyReason;
	char m_rgchOptionalText[128];
} GSClientDeny_t;

typedef struct {
	CSteamID m_SteamID;
	enum EDenyReason m_eDenyReason;
} GSClientKick_t;

typedef struct {
	uint64 m_SteamID;
	char m_pchAchievement[128];
	_Bool m_bUnlocked;
} GSClientAchievementStatus_t;

typedef struct {
	uint8 m_bSecure;
} GSPolicyResponse_t;

typedef struct {
	enum EResult m_eResult;
	int32 m_nRank;
	uint32 m_unTotalConnects;
	uint32 m_unTotalMinutesPlayed;
} GSGameplayStats_t;

typedef struct {
	CSteamID m_SteamIDUser;
	CSteamID m_SteamIDGroup;
	_Bool m_bMember;
	_Bool m_bOfficer;
} GSClientGroupStatus_t;

typedef struct {
	enum EResult m_eResult;
	uint32 m_unReputationScore;
	_Bool m_bBanned;
	uint32 m_unBannedIP;
	uint16 m_usBannedPort;
	uint64 m_ulBannedGameID;
	uint32 m_unBanExpires;
} GSReputation_t;

typedef struct {
	enum EResult m_eResult;
} AssociateWithClanResult_t;

typedef struct {
	enum EResult m_eResult;
	int m_cPlayersThatDontLikeCandidate;
	int m_cPlayersThatCandidateDoesntLike;
	int m_cClanPlayersThatDontLikeCandidate;
	CSteamID m_SteamIDCandidate;
} ComputeNewPlayerCompatibilityResult_t;

typedef struct {
	enum EResult m_eResult;
	CSteamID m_steamIDUser;
} GSStatsReceived_t;

typedef struct {
	enum EResult m_eResult;
	CSteamID m_steamIDUser;
} GSStatsStored_t;

typedef struct {
	CSteamID m_steamIDUser;
} GSStatsUnloaded_t;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_steam FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
typedef bool (*PFN_SteamAPI_Init) ();
typedef void (*PFN_SteamAPI_Shutdown) ();
typedef bool (*PFN_SteamAPI_RestartAppIfNecessary) ( uint32 unOwnAppID );
typedef void (*PFN_SteamAPI_ReleaseCurrentThreadMemory) ();
typedef void (*PFN_SteamAPI_WriteMiniDump) ( uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID );
typedef void (*PFN_SteamAPI_SetMiniDumpComment) ( const char *pchMsg );
typedef intptr_t (*PFN_SteamClient) ();
typedef HSteamPipe (*PFN_SteamAPI_ISteamClient_CreateSteamPipe) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamClient_BReleaseSteamPipe) (intptr_t instancePtr, HSteamPipe hSteamPipe);
typedef HSteamUser (*PFN_SteamAPI_ISteamClient_ConnectToGlobalUser) (intptr_t instancePtr, HSteamPipe hSteamPipe);
typedef HSteamUser (*PFN_SteamAPI_ISteamClient_CreateLocalUser) (intptr_t instancePtr, HSteamPipe * phSteamPipe, EAccountType eAccountType);
typedef void (*PFN_SteamAPI_ISteamClient_ReleaseUser) (intptr_t instancePtr, HSteamPipe hSteamPipe, HSteamUser hUser);
typedef ISteamUser* (*PFN_SteamAPI_ISteamClient_GetISteamUser) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamGameServer* (*PFN_SteamAPI_ISteamClient_GetISteamGameServer) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef void (*PFN_SteamAPI_ISteamClient_SetLocalIPBinding) (intptr_t instancePtr, uint32 unIP, uint16 usPort);
typedef ISteamFriends* (*PFN_SteamAPI_ISteamClient_GetISteamFriends) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamUtils* (*PFN_SteamAPI_ISteamClient_GetISteamUtils) (intptr_t instancePtr, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamMatchmaking* (*PFN_SteamAPI_ISteamClient_GetISteamMatchmaking) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamMatchmakingServers* (*PFN_SteamAPI_ISteamClient_GetISteamMatchmakingServers) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef void* (*PFN_SteamAPI_ISteamClient_GetISteamGenericInterface) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamUserStats* (*PFN_SteamAPI_ISteamClient_GetISteamUserStats) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamGameServerStats* (*PFN_SteamAPI_ISteamClient_GetISteamGameServerStats) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamApps* (*PFN_SteamAPI_ISteamClient_GetISteamApps) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamNetworking* (*PFN_SteamAPI_ISteamClient_GetISteamNetworking) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamRemoteStorage* (*PFN_SteamAPI_ISteamClient_GetISteamRemoteStorage) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamScreenshots* (*PFN_SteamAPI_ISteamClient_GetISteamScreenshots) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef uint32 (*PFN_SteamAPI_ISteamClient_GetIPCCallCount) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamClient_SetWarningMessageHook) (intptr_t instancePtr, SteamAPIWarningMessageHook_t pFunction);
typedef bool (*PFN_SteamAPI_ISteamClient_BShutdownIfAllPipesClosed) (intptr_t instancePtr);
typedef ISteamHTTP* (*PFN_SteamAPI_ISteamClient_GetISteamHTTP) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamController* (*PFN_SteamAPI_ISteamClient_GetISteamController) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamUGC* (*PFN_SteamAPI_ISteamClient_GetISteamUGC) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamAppList* (*PFN_SteamAPI_ISteamClient_GetISteamAppList) (intptr_t instancePtr, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamMusic* (*PFN_SteamAPI_ISteamClient_GetISteamMusic) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamMusicRemote* (*PFN_SteamAPI_ISteamClient_GetISteamMusicRemote) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamHTMLSurface* (*PFN_SteamAPI_ISteamClient_GetISteamHTMLSurface) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamInventory* (*PFN_SteamAPI_ISteamClient_GetISteamInventory) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamVideo* (*PFN_SteamAPI_ISteamClient_GetISteamVideo) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef ISteamParentalSettings* (*PFN_SteamAPI_ISteamClient_GetISteamParentalSettings) (intptr_t instancePtr, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char * pchVersion);
typedef HSteamUser (*PFN_SteamAPI_ISteamUser_GetHSteamUser) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUser_BLoggedOn) (intptr_t instancePtr);
typedef uint64 (*PFN_SteamAPI_ISteamUser_GetSteamID) (intptr_t instancePtr);
typedef int (*PFN_SteamAPI_ISteamUser_InitiateGameConnection) (intptr_t instancePtr, void * pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure);
typedef void (*PFN_SteamAPI_ISteamUser_TerminateGameConnection) (intptr_t instancePtr, uint32 unIPServer, uint16 usPortServer);
typedef void (*PFN_SteamAPI_ISteamUser_TrackAppUsageEvent) (intptr_t instancePtr, CGameID gameID, int eAppUsageEvent, const char * pchExtraInfo);
typedef bool (*PFN_SteamAPI_ISteamUser_GetUserDataFolder) (intptr_t instancePtr, char * pchBuffer, int cubBuffer);
typedef void (*PFN_SteamAPI_ISteamUser_StartVoiceRecording) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamUser_StopVoiceRecording) (intptr_t instancePtr);
typedef EVoiceResult (*PFN_SteamAPI_ISteamUser_GetAvailableVoice) (intptr_t instancePtr, uint32 * pcbCompressed, uint32 * pcbUncompressed_Deprecated, uint32 nUncompressedVoiceDesiredSampleRate_Deprecated);
typedef EVoiceResult (*PFN_SteamAPI_ISteamUser_GetVoice) (intptr_t instancePtr, bool bWantCompressed, void * pDestBuffer, uint32 cbDestBufferSize, uint32 * nBytesWritten, bool bWantUncompressed_Deprecated, void * pUncompressedDestBuffer_Deprecated, uint32 cbUncompressedDestBufferSize_Deprecated, uint32 * nUncompressBytesWritten_Deprecated, uint32 nUncompressedVoiceDesiredSampleRate_Deprecated);
typedef EVoiceResult (*PFN_SteamAPI_ISteamUser_DecompressVoice) (intptr_t instancePtr, const void * pCompressed, uint32 cbCompressed, void * pDestBuffer, uint32 cbDestBufferSize, uint32 * nBytesWritten, uint32 nDesiredSampleRate);
typedef uint32 (*PFN_SteamAPI_ISteamUser_GetVoiceOptimalSampleRate) (intptr_t instancePtr);
typedef HAuthTicket (*PFN_SteamAPI_ISteamUser_GetAuthSessionTicket) (intptr_t instancePtr, void * pTicket, int cbMaxTicket, uint32 * pcbTicket);
typedef EBeginAuthSessionResult (*PFN_SteamAPI_ISteamUser_BeginAuthSession) (intptr_t instancePtr, const void * pAuthTicket, int cbAuthTicket, CSteamID steamID);
typedef void (*PFN_SteamAPI_ISteamUser_EndAuthSession) (intptr_t instancePtr, CSteamID steamID);
typedef void (*PFN_SteamAPI_ISteamUser_CancelAuthTicket) (intptr_t instancePtr, HAuthTicket hAuthTicket);
typedef EUserHasLicenseForAppResult (*PFN_SteamAPI_ISteamUser_UserHasLicenseForApp) (intptr_t instancePtr, CSteamID steamID, AppId_t appID);
typedef bool (*PFN_SteamAPI_ISteamUser_BIsBehindNAT) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamUser_AdvertiseGame) (intptr_t instancePtr, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUser_RequestEncryptedAppTicket) (intptr_t instancePtr, void * pDataToInclude, int cbDataToInclude);
typedef bool (*PFN_SteamAPI_ISteamUser_GetEncryptedAppTicket) (intptr_t instancePtr, void * pTicket, int cbMaxTicket, uint32 * pcbTicket);
typedef int (*PFN_SteamAPI_ISteamUser_GetGameBadgeLevel) (intptr_t instancePtr, int nSeries, bool bFoil);
typedef int (*PFN_SteamAPI_ISteamUser_GetPlayerSteamLevel) (intptr_t instancePtr);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUser_RequestStoreAuthURL) (intptr_t instancePtr, const char * pchRedirectURL);
typedef bool (*PFN_SteamAPI_ISteamUser_BIsPhoneVerified) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUser_BIsTwoFactorEnabled) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUser_BIsPhoneIdentifying) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUser_BIsPhoneRequiringVerification) (intptr_t instancePtr);
typedef const char * (*PFN_SteamAPI_ISteamFriends_GetPersonaName) (intptr_t instancePtr);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamFriends_SetPersonaName) (intptr_t instancePtr, const char * pchPersonaName);
typedef EPersonaState (*PFN_SteamAPI_ISteamFriends_GetPersonaState) (intptr_t instancePtr);
typedef int (*PFN_SteamAPI_ISteamFriends_GetFriendCount) (intptr_t instancePtr, int iFriendFlags);
typedef uint64 (*PFN_SteamAPI_ISteamFriends_GetFriendByIndex) (intptr_t instancePtr, int iFriend, int iFriendFlags);
typedef EFriendRelationship (*PFN_SteamAPI_ISteamFriends_GetFriendRelationship) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef EPersonaState (*PFN_SteamAPI_ISteamFriends_GetFriendPersonaState) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef const char * (*PFN_SteamAPI_ISteamFriends_GetFriendPersonaName) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef bool (*PFN_SteamAPI_ISteamFriends_GetFriendGamePlayed) (intptr_t instancePtr, CSteamID steamIDFriend, FriendGameInfo_t * pFriendGameInfo);
typedef const char * (*PFN_SteamAPI_ISteamFriends_GetFriendPersonaNameHistory) (intptr_t instancePtr, CSteamID steamIDFriend, int iPersonaName);
typedef int (*PFN_SteamAPI_ISteamFriends_GetFriendSteamLevel) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef const char * (*PFN_SteamAPI_ISteamFriends_GetPlayerNickname) (intptr_t instancePtr, CSteamID steamIDPlayer);
typedef int (*PFN_SteamAPI_ISteamFriends_GetFriendsGroupCount) (intptr_t instancePtr);
typedef FriendsGroupID_t (*PFN_SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex) (intptr_t instancePtr, int iFG);
typedef const char * (*PFN_SteamAPI_ISteamFriends_GetFriendsGroupName) (intptr_t instancePtr, FriendsGroupID_t friendsGroupID);
typedef int (*PFN_SteamAPI_ISteamFriends_GetFriendsGroupMembersCount) (intptr_t instancePtr, FriendsGroupID_t friendsGroupID);
typedef void (*PFN_SteamAPI_ISteamFriends_GetFriendsGroupMembersList) (intptr_t instancePtr, FriendsGroupID_t friendsGroupID, CSteamID * pOutSteamIDMembers, int nMembersCount);
typedef bool (*PFN_SteamAPI_ISteamFriends_HasFriend) (intptr_t instancePtr, CSteamID steamIDFriend, int iFriendFlags);
typedef int (*PFN_SteamAPI_ISteamFriends_GetClanCount) (intptr_t instancePtr);
typedef uint64 (*PFN_SteamAPI_ISteamFriends_GetClanByIndex) (intptr_t instancePtr, int iClan);
typedef const char * (*PFN_SteamAPI_ISteamFriends_GetClanName) (intptr_t instancePtr, CSteamID steamIDClan);
typedef const char * (*PFN_SteamAPI_ISteamFriends_GetClanTag) (intptr_t instancePtr, CSteamID steamIDClan);
typedef bool (*PFN_SteamAPI_ISteamFriends_GetClanActivityCounts) (intptr_t instancePtr, CSteamID steamIDClan, int * pnOnline, int * pnInGame, int * pnChatting);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamFriends_DownloadClanActivityCounts) (intptr_t instancePtr, CSteamID * psteamIDClans, int cClansToRequest);
typedef int (*PFN_SteamAPI_ISteamFriends_GetFriendCountFromSource) (intptr_t instancePtr, CSteamID steamIDSource);
typedef uint64 (*PFN_SteamAPI_ISteamFriends_GetFriendFromSourceByIndex) (intptr_t instancePtr, CSteamID steamIDSource, int iFriend);
typedef bool (*PFN_SteamAPI_ISteamFriends_IsUserInSource) (intptr_t instancePtr, CSteamID steamIDUser, CSteamID steamIDSource);
typedef void (*PFN_SteamAPI_ISteamFriends_SetInGameVoiceSpeaking) (intptr_t instancePtr, CSteamID steamIDUser, bool bSpeaking);
typedef void (*PFN_SteamAPI_ISteamFriends_ActivateGameOverlay) (intptr_t instancePtr, const char * pchDialog);
typedef void (*PFN_SteamAPI_ISteamFriends_ActivateGameOverlayToUser) (intptr_t instancePtr, const char * pchDialog, CSteamID steamID);
typedef void (*PFN_SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage) (intptr_t instancePtr, const char * pchURL);
typedef void (*PFN_SteamAPI_ISteamFriends_ActivateGameOverlayToStore) (intptr_t instancePtr, AppId_t nAppID, EOverlayToStoreFlag eFlag);
typedef void (*PFN_SteamAPI_ISteamFriends_SetPlayedWith) (intptr_t instancePtr, CSteamID steamIDUserPlayedWith);
typedef void (*PFN_SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog) (intptr_t instancePtr, CSteamID steamIDLobby);
typedef int (*PFN_SteamAPI_ISteamFriends_GetSmallFriendAvatar) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef int (*PFN_SteamAPI_ISteamFriends_GetMediumFriendAvatar) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef int (*PFN_SteamAPI_ISteamFriends_GetLargeFriendAvatar) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef bool (*PFN_SteamAPI_ISteamFriends_RequestUserInformation) (intptr_t instancePtr, CSteamID steamIDUser, bool bRequireNameOnly);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamFriends_RequestClanOfficerList) (intptr_t instancePtr, CSteamID steamIDClan);
typedef uint64 (*PFN_SteamAPI_ISteamFriends_GetClanOwner) (intptr_t instancePtr, CSteamID steamIDClan);
typedef int (*PFN_SteamAPI_ISteamFriends_GetClanOfficerCount) (intptr_t instancePtr, CSteamID steamIDClan);
typedef uint64 (*PFN_SteamAPI_ISteamFriends_GetClanOfficerByIndex) (intptr_t instancePtr, CSteamID steamIDClan, int iOfficer);
typedef uint32 (*PFN_SteamAPI_ISteamFriends_GetUserRestrictions) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamFriends_SetRichPresence) (intptr_t instancePtr, const char * pchKey, const char * pchValue);
typedef void (*PFN_SteamAPI_ISteamFriends_ClearRichPresence) (intptr_t instancePtr);
typedef const char * (*PFN_SteamAPI_ISteamFriends_GetFriendRichPresence) (intptr_t instancePtr, CSteamID steamIDFriend, const char * pchKey);
typedef int (*PFN_SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef const char * (*PFN_SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex) (intptr_t instancePtr, CSteamID steamIDFriend, int iKey);
typedef void (*PFN_SteamAPI_ISteamFriends_RequestFriendRichPresence) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef bool (*PFN_SteamAPI_ISteamFriends_InviteUserToGame) (intptr_t instancePtr, CSteamID steamIDFriend, const char * pchConnectString);
typedef int (*PFN_SteamAPI_ISteamFriends_GetCoplayFriendCount) (intptr_t instancePtr);
typedef uint64 (*PFN_SteamAPI_ISteamFriends_GetCoplayFriend) (intptr_t instancePtr, int iCoplayFriend);
typedef int (*PFN_SteamAPI_ISteamFriends_GetFriendCoplayTime) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef AppId_t (*PFN_SteamAPI_ISteamFriends_GetFriendCoplayGame) (intptr_t instancePtr, CSteamID steamIDFriend);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamFriends_JoinClanChatRoom) (intptr_t instancePtr, CSteamID steamIDClan);
typedef bool (*PFN_SteamAPI_ISteamFriends_LeaveClanChatRoom) (intptr_t instancePtr, CSteamID steamIDClan);
typedef int (*PFN_SteamAPI_ISteamFriends_GetClanChatMemberCount) (intptr_t instancePtr, CSteamID steamIDClan);
typedef uint64 (*PFN_SteamAPI_ISteamFriends_GetChatMemberByIndex) (intptr_t instancePtr, CSteamID steamIDClan, int iUser);
typedef bool (*PFN_SteamAPI_ISteamFriends_SendClanChatMessage) (intptr_t instancePtr, CSteamID steamIDClanChat, const char * pchText);
typedef int (*PFN_SteamAPI_ISteamFriends_GetClanChatMessage) (intptr_t instancePtr, CSteamID steamIDClanChat, int iMessage, void * prgchText, int cchTextMax, EChatEntryType * peChatEntryType, CSteamID * psteamidChatter);
typedef bool (*PFN_SteamAPI_ISteamFriends_IsClanChatAdmin) (intptr_t instancePtr, CSteamID steamIDClanChat, CSteamID steamIDUser);
typedef bool (*PFN_SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam) (intptr_t instancePtr, CSteamID steamIDClanChat);
typedef bool (*PFN_SteamAPI_ISteamFriends_OpenClanChatWindowInSteam) (intptr_t instancePtr, CSteamID steamIDClanChat);
typedef bool (*PFN_SteamAPI_ISteamFriends_CloseClanChatWindowInSteam) (intptr_t instancePtr, CSteamID steamIDClanChat);
typedef bool (*PFN_SteamAPI_ISteamFriends_SetListenForFriendsMessages) (intptr_t instancePtr, bool bInterceptEnabled);
typedef bool (*PFN_SteamAPI_ISteamFriends_ReplyToFriendMessage) (intptr_t instancePtr, CSteamID steamIDFriend, const char * pchMsgToSend);
typedef int (*PFN_SteamAPI_ISteamFriends_GetFriendMessage) (intptr_t instancePtr, CSteamID steamIDFriend, int iMessageID, void * pvData, int cubData, EChatEntryType * peChatEntryType);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamFriends_GetFollowerCount) (intptr_t instancePtr, CSteamID steamID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamFriends_IsFollowing) (intptr_t instancePtr, CSteamID steamID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamFriends_EnumerateFollowingList) (intptr_t instancePtr, uint32 unStartIndex);
typedef bool (*PFN_SteamAPI_ISteamFriends_IsClanPublic) (intptr_t instancePtr, CSteamID steamIDClan);
typedef bool (*PFN_SteamAPI_ISteamFriends_IsClanOfficialGameGroup) (intptr_t instancePtr, CSteamID steamIDClan);
typedef uint32 (*PFN_SteamAPI_ISteamUtils_GetSecondsSinceAppActive) (intptr_t instancePtr);
typedef uint32 (*PFN_SteamAPI_ISteamUtils_GetSecondsSinceComputerActive) (intptr_t instancePtr);
typedef EUniverse (*PFN_SteamAPI_ISteamUtils_GetConnectedUniverse) (intptr_t instancePtr);
typedef uint32 (*PFN_SteamAPI_ISteamUtils_GetServerRealTime) (intptr_t instancePtr);
typedef const char * (*PFN_SteamAPI_ISteamUtils_GetIPCountry) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUtils_GetImageSize) (intptr_t instancePtr, int iImage, uint32 * pnWidth, uint32 * pnHeight);
typedef bool (*PFN_SteamAPI_ISteamUtils_GetImageRGBA) (intptr_t instancePtr, int iImage, uint8 * pubDest, int nDestBufferSize);
typedef bool (*PFN_SteamAPI_ISteamUtils_GetCSERIPPort) (intptr_t instancePtr, uint32 * unIP, uint16 * usPort);
typedef uint8 (*PFN_SteamAPI_ISteamUtils_GetCurrentBatteryPower) (intptr_t instancePtr);
typedef uint32 (*PFN_SteamAPI_ISteamUtils_GetAppID) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamUtils_SetOverlayNotificationPosition) (intptr_t instancePtr, ENotificationPosition eNotificationPosition);
typedef bool (*PFN_SteamAPI_ISteamUtils_IsAPICallCompleted) (intptr_t instancePtr, SteamAPICall_t hSteamAPICall, bool * pbFailed);
typedef ESteamAPICallFailure (*PFN_SteamAPI_ISteamUtils_GetAPICallFailureReason) (intptr_t instancePtr, SteamAPICall_t hSteamAPICall);
typedef bool (*PFN_SteamAPI_ISteamUtils_GetAPICallResult) (intptr_t instancePtr, SteamAPICall_t hSteamAPICall, void * pCallback, int cubCallback, int iCallbackExpected, bool * pbFailed);
typedef uint32 (*PFN_SteamAPI_ISteamUtils_GetIPCCallCount) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamUtils_SetWarningMessageHook) (intptr_t instancePtr, SteamAPIWarningMessageHook_t pFunction);
typedef bool (*PFN_SteamAPI_ISteamUtils_IsOverlayEnabled) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUtils_BOverlayNeedsPresent) (intptr_t instancePtr);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUtils_CheckFileSignature) (intptr_t instancePtr, const char * szFileName);
typedef bool (*PFN_SteamAPI_ISteamUtils_ShowGamepadTextInput) (intptr_t instancePtr, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char * pchDescription, uint32 unCharMax, const char * pchExistingText);
typedef uint32 (*PFN_SteamAPI_ISteamUtils_GetEnteredGamepadTextLength) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUtils_GetEnteredGamepadTextInput) (intptr_t instancePtr, char * pchText, uint32 cchText);
typedef const char * (*PFN_SteamAPI_ISteamUtils_GetSteamUILanguage) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUtils_IsSteamRunningInVR) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamUtils_SetOverlayNotificationInset) (intptr_t instancePtr, int nHorizontalInset, int nVerticalInset);
typedef bool (*PFN_SteamAPI_ISteamUtils_IsSteamInBigPictureMode) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamUtils_StartVRDashboard) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled) (intptr_t instancePtr, bool bEnabled);
typedef int (*PFN_SteamAPI_ISteamMatchmaking_GetFavoriteGameCount) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_GetFavoriteGame) (intptr_t instancePtr, int iGame, AppId_t * pnAppID, uint32 * pnIP, uint16 * pnConnPort, uint16 * pnQueryPort, uint32 * punFlags, uint32 * pRTime32LastPlayedOnServer);
typedef int (*PFN_SteamAPI_ISteamMatchmaking_AddFavoriteGame) (intptr_t instancePtr, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_RemoveFavoriteGame) (intptr_t instancePtr, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamMatchmaking_RequestLobbyList) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter) (intptr_t instancePtr, const char * pchKeyToMatch, const char * pchValueToMatch, ELobbyComparison eComparisonType);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter) (intptr_t instancePtr, const char * pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter) (intptr_t instancePtr, const char * pchKeyToMatch, int nValueToBeCloseTo);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable) (intptr_t instancePtr, int nSlotsAvailable);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter) (intptr_t instancePtr, ELobbyDistanceFilter eLobbyDistanceFilter);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter) (intptr_t instancePtr, int cMaxResults);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter) (intptr_t instancePtr, CSteamID steamIDLobby);
typedef uint64 (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyByIndex) (intptr_t instancePtr, int iLobby);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamMatchmaking_CreateLobby) (intptr_t instancePtr, ELobbyType eLobbyType, int cMaxMembers);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamMatchmaking_JoinLobby) (intptr_t instancePtr, CSteamID steamIDLobby);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_LeaveLobby) (intptr_t instancePtr, CSteamID steamIDLobby);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_InviteUserToLobby) (intptr_t instancePtr, CSteamID steamIDLobby, CSteamID steamIDInvitee);
typedef int (*PFN_SteamAPI_ISteamMatchmaking_GetNumLobbyMembers) (intptr_t instancePtr, CSteamID steamIDLobby);
typedef uint64 (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex) (intptr_t instancePtr, CSteamID steamIDLobby, int iMember);
typedef const char * (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyData) (intptr_t instancePtr, CSteamID steamIDLobby, const char * pchKey);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_SetLobbyData) (intptr_t instancePtr, CSteamID steamIDLobby, const char * pchKey, const char * pchValue);
typedef int (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyDataCount) (intptr_t instancePtr, CSteamID steamIDLobby);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex) (intptr_t instancePtr, CSteamID steamIDLobby, int iLobbyData, char * pchKey, int cchKeyBufferSize, char * pchValue, int cchValueBufferSize);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_DeleteLobbyData) (intptr_t instancePtr, CSteamID steamIDLobby, const char * pchKey);
typedef const char * (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyMemberData) (intptr_t instancePtr, CSteamID steamIDLobby, CSteamID steamIDUser, const char * pchKey);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_SetLobbyMemberData) (intptr_t instancePtr, CSteamID steamIDLobby, const char * pchKey, const char * pchValue);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_SendLobbyChatMsg) (intptr_t instancePtr, CSteamID steamIDLobby, const void * pvMsgBody, int cubMsgBody);
typedef int (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyChatEntry) (intptr_t instancePtr, CSteamID steamIDLobby, int iChatID, CSteamID * pSteamIDUser, void * pvData, int cubData, EChatEntryType * peChatEntryType);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_RequestLobbyData) (intptr_t instancePtr, CSteamID steamIDLobby);
typedef void (*PFN_SteamAPI_ISteamMatchmaking_SetLobbyGameServer) (intptr_t instancePtr, CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyGameServer) (intptr_t instancePtr, CSteamID steamIDLobby, uint32 * punGameServerIP, uint16 * punGameServerPort, CSteamID * psteamIDGameServer);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit) (intptr_t instancePtr, CSteamID steamIDLobby, int cMaxMembers);
typedef int (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit) (intptr_t instancePtr, CSteamID steamIDLobby);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_SetLobbyType) (intptr_t instancePtr, CSteamID steamIDLobby, ELobbyType eLobbyType);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_SetLobbyJoinable) (intptr_t instancePtr, CSteamID steamIDLobby, bool bLobbyJoinable);
typedef uint64 (*PFN_SteamAPI_ISteamMatchmaking_GetLobbyOwner) (intptr_t instancePtr, CSteamID steamIDLobby);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_SetLobbyOwner) (intptr_t instancePtr, CSteamID steamIDLobby, CSteamID steamIDNewOwner);
typedef bool (*PFN_SteamAPI_ISteamMatchmaking_SetLinkedLobby) (intptr_t instancePtr, CSteamID steamIDLobby, CSteamID steamIDLobbyDependent);
typedef void (*PFN_SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded) (intptr_t instancePtr, HServerListRequest hRequest, int iServer);
typedef void (*PFN_SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond) (intptr_t instancePtr, HServerListRequest hRequest, int iServer);
typedef void (*PFN_SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete) (intptr_t instancePtr, HServerListRequest hRequest, EMatchMakingServerResponse response);
typedef void (*PFN_SteamAPI_ISteamMatchmakingPingResponse_ServerResponded) (intptr_t instancePtr, gameserveritem_t *server);
typedef void (*PFN_SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList) (intptr_t instancePtr, const char * pchName, int nScore, float flTimePlayed);
typedef void (*PFN_SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded) (intptr_t instancePtr, const char * pchRule, const char * pchValue);
typedef void (*PFN_SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete) (intptr_t instancePtr);
typedef HServerListRequest (*PFN_SteamAPI_ISteamMatchmakingServers_RequestInternetServerList) (intptr_t instancePtr, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse);
typedef HServerListRequest (*PFN_SteamAPI_ISteamMatchmakingServers_RequestLANServerList) (intptr_t instancePtr, AppId_t iApp, ISteamMatchmakingServerListResponse * pRequestServersResponse);
typedef HServerListRequest (*PFN_SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList) (intptr_t instancePtr, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse);
typedef HServerListRequest (*PFN_SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList) (intptr_t instancePtr, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse);
typedef HServerListRequest (*PFN_SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList) (intptr_t instancePtr, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse);
typedef HServerListRequest (*PFN_SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList) (intptr_t instancePtr, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse);
typedef void (*PFN_SteamAPI_ISteamMatchmakingServers_ReleaseRequest) (intptr_t instancePtr, HServerListRequest hServerListRequest);
typedef gameserveritem_t* (*PFN_SteamAPI_ISteamMatchmakingServers_GetServerDetails) (intptr_t instancePtr, HServerListRequest hRequest, int iServer);
typedef void (*PFN_SteamAPI_ISteamMatchmakingServers_CancelQuery) (intptr_t instancePtr, HServerListRequest hRequest);
typedef void (*PFN_SteamAPI_ISteamMatchmakingServers_RefreshQuery) (intptr_t instancePtr, HServerListRequest hRequest);
typedef bool (*PFN_SteamAPI_ISteamMatchmakingServers_IsRefreshing) (intptr_t instancePtr, HServerListRequest hRequest);
typedef int (*PFN_SteamAPI_ISteamMatchmakingServers_GetServerCount) (intptr_t instancePtr, HServerListRequest hRequest);
typedef void (*PFN_SteamAPI_ISteamMatchmakingServers_RefreshServer) (intptr_t instancePtr, HServerListRequest hRequest, int iServer);
typedef HServerQuery (*PFN_SteamAPI_ISteamMatchmakingServers_PingServer) (intptr_t instancePtr, uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse * pRequestServersResponse);
typedef HServerQuery (*PFN_SteamAPI_ISteamMatchmakingServers_PlayerDetails) (intptr_t instancePtr, uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse * pRequestServersResponse);
typedef HServerQuery (*PFN_SteamAPI_ISteamMatchmakingServers_ServerRules) (intptr_t instancePtr, uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse * pRequestServersResponse);
typedef void (*PFN_SteamAPI_ISteamMatchmakingServers_CancelServerQuery) (intptr_t instancePtr, HServerQuery hServerQuery);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_FileWrite) (intptr_t instancePtr, const char * pchFile, const void * pvData, int32 cubData);
typedef int32 (*PFN_SteamAPI_ISteamRemoteStorage_FileRead) (intptr_t instancePtr, const char * pchFile, void * pvData, int32 cubDataToRead);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_FileWriteAsync) (intptr_t instancePtr, const char * pchFile, const void * pvData, uint32 cubData);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_FileReadAsync) (intptr_t instancePtr, const char * pchFile, uint32 nOffset, uint32 cubToRead);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete) (intptr_t instancePtr, SteamAPICall_t hReadCall, void * pvBuffer, uint32 cubToRead);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_FileForget) (intptr_t instancePtr, const char * pchFile);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_FileDelete) (intptr_t instancePtr, const char * pchFile);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_FileShare) (intptr_t instancePtr, const char * pchFile);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_SetSyncPlatforms) (intptr_t instancePtr, const char * pchFile, ERemoteStoragePlatform eRemoteStoragePlatform);
typedef UGCFileWriteStreamHandle_t (*PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen) (intptr_t instancePtr, const char * pchFile);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk) (intptr_t instancePtr, UGCFileWriteStreamHandle_t writeHandle, const void * pvData, int32 cubData);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamClose) (intptr_t instancePtr, UGCFileWriteStreamHandle_t writeHandle);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel) (intptr_t instancePtr, UGCFileWriteStreamHandle_t writeHandle);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_FileExists) (intptr_t instancePtr, const char * pchFile);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_FilePersisted) (intptr_t instancePtr, const char * pchFile);
typedef int32 (*PFN_SteamAPI_ISteamRemoteStorage_GetFileSize) (intptr_t instancePtr, const char * pchFile);
typedef int64 (*PFN_SteamAPI_ISteamRemoteStorage_GetFileTimestamp) (intptr_t instancePtr, const char * pchFile);
typedef ERemoteStoragePlatform (*PFN_SteamAPI_ISteamRemoteStorage_GetSyncPlatforms) (intptr_t instancePtr, const char * pchFile);
typedef int32 (*PFN_SteamAPI_ISteamRemoteStorage_GetFileCount) (intptr_t instancePtr);
typedef const char * (*PFN_SteamAPI_ISteamRemoteStorage_GetFileNameAndSize) (intptr_t instancePtr, int iFile, int32 * pnFileSizeInBytes);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_GetQuota) (intptr_t instancePtr, uint64 * pnTotalBytes, uint64 * puAvailableBytes);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp) (intptr_t instancePtr, bool bEnabled);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_UGCDownload) (intptr_t instancePtr, UGCHandle_t hContent, uint32 unPriority);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress) (intptr_t instancePtr, UGCHandle_t hContent, int32 * pnBytesDownloaded, int32 * pnBytesExpected);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_GetUGCDetails) (intptr_t instancePtr, UGCHandle_t hContent, AppId_t * pnAppID, char ** ppchName, int32 * pnFileSizeInBytes, CSteamID * pSteamIDOwner);
typedef int32 (*PFN_SteamAPI_ISteamRemoteStorage_UGCRead) (intptr_t instancePtr, UGCHandle_t hContent, void * pvData, int32 cubDataToRead, uint32 cOffset, EUGCReadAction eAction);
typedef int32 (*PFN_SteamAPI_ISteamRemoteStorage_GetCachedUGCCount) (intptr_t instancePtr);
typedef UGCHandle_t (*PFN_SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle) (intptr_t instancePtr, int32 iCachedContent);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_PublishWorkshopFile) (intptr_t instancePtr, const char * pchFile, const char * pchPreviewFile, AppId_t nConsumerAppId, const char * pchTitle, const char * pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t * pTags, EWorkshopFileType eWorkshopFileType);
typedef PublishedFileUpdateHandle_t (*PFN_SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest) (intptr_t instancePtr, PublishedFileId_t unPublishedFileId);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile) (intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle, const char * pchFile);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile) (intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle, const char * pchPreviewFile);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle) (intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle, const char * pchTitle);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription) (intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle, const char * pchDescription);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility) (intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle, ERemoteStoragePublishedFileVisibility eVisibility);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags) (intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle, SteamParamStringArray_t * pTags);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate) (intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails) (intptr_t instancePtr, PublishedFileId_t unPublishedFileId, uint32 unMaxSecondsOld);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_DeletePublishedFile) (intptr_t instancePtr, PublishedFileId_t unPublishedFileId);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles) (intptr_t instancePtr, uint32 unStartIndex);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_SubscribePublishedFile) (intptr_t instancePtr, PublishedFileId_t unPublishedFileId);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles) (intptr_t instancePtr, uint32 unStartIndex);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile) (intptr_t instancePtr, PublishedFileId_t unPublishedFileId);
typedef bool (*PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription) (intptr_t instancePtr, PublishedFileUpdateHandle_t updateHandle, const char * pchChangeDescription);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails) (intptr_t instancePtr, PublishedFileId_t unPublishedFileId);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote) (intptr_t instancePtr, PublishedFileId_t unPublishedFileId, bool bVoteUp);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails) (intptr_t instancePtr, PublishedFileId_t unPublishedFileId);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles) (intptr_t instancePtr, CSteamID steamId, uint32 unStartIndex, SteamParamStringArray_t * pRequiredTags, SteamParamStringArray_t * pExcludedTags);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_PublishVideo) (intptr_t instancePtr, EWorkshopVideoProvider eVideoProvider, const char * pchVideoAccount, const char * pchVideoIdentifier, const char * pchPreviewFile, AppId_t nConsumerAppId, const char * pchTitle, const char * pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t * pTags);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction) (intptr_t instancePtr, PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction) (intptr_t instancePtr, EWorkshopFileAction eAction, uint32 unStartIndex);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles) (intptr_t instancePtr, EWorkshopEnumerationType eEnumerationType, uint32 unStartIndex, uint32 unCount, uint32 unDays, SteamParamStringArray_t * pTags, SteamParamStringArray_t * pUserTags);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation) (intptr_t instancePtr, UGCHandle_t hContent, const char * pchLocation, uint32 unPriority);
typedef bool (*PFN_SteamAPI_ISteamUserStats_RequestCurrentStats) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetStat) (intptr_t instancePtr, const char * pchName, int32 * pData);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetStat0) (intptr_t instancePtr, const char * pchName, float * pData);
typedef bool (*PFN_SteamAPI_ISteamUserStats_SetStat) (intptr_t instancePtr, const char * pchName, int32 nData);
typedef bool (*PFN_SteamAPI_ISteamUserStats_SetStat0) (intptr_t instancePtr, const char * pchName, float fData);
typedef bool (*PFN_SteamAPI_ISteamUserStats_UpdateAvgRateStat) (intptr_t instancePtr, const char * pchName, float flCountThisSession, double dSessionLength);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetAchievement) (intptr_t instancePtr, const char * pchName, bool * pbAchieved);
typedef bool (*PFN_SteamAPI_ISteamUserStats_SetAchievement) (intptr_t instancePtr, const char * pchName);
typedef bool (*PFN_SteamAPI_ISteamUserStats_ClearAchievement) (intptr_t instancePtr, const char * pchName);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime) (intptr_t instancePtr, const char * pchName, bool * pbAchieved, uint32 * punUnlockTime);
typedef bool (*PFN_SteamAPI_ISteamUserStats_StoreStats) (intptr_t instancePtr);
typedef int (*PFN_SteamAPI_ISteamUserStats_GetAchievementIcon) (intptr_t instancePtr, const char * pchName);
typedef const char * (*PFN_SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute) (intptr_t instancePtr, const char * pchName, const char * pchKey);
typedef bool (*PFN_SteamAPI_ISteamUserStats_IndicateAchievementProgress) (intptr_t instancePtr, const char * pchName, uint32 nCurProgress, uint32 nMaxProgress);
typedef uint32 (*PFN_SteamAPI_ISteamUserStats_GetNumAchievements) (intptr_t instancePtr);
typedef const char * (*PFN_SteamAPI_ISteamUserStats_GetAchievementName) (intptr_t instancePtr, uint32 iAchievement);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_RequestUserStats) (intptr_t instancePtr, CSteamID steamIDUser);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetUserStat) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, int32 * pData);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetUserStat0) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, float * pData);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetUserAchievement) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, bool * pbAchieved);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, bool * pbAchieved, uint32 * punUnlockTime);
typedef bool (*PFN_SteamAPI_ISteamUserStats_ResetAllStats) (intptr_t instancePtr, bool bAchievementsToo);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_FindOrCreateLeaderboard) (intptr_t instancePtr, const char * pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_FindLeaderboard) (intptr_t instancePtr, const char * pchLeaderboardName);
typedef const char * (*PFN_SteamAPI_ISteamUserStats_GetLeaderboardName) (intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard);
typedef int (*PFN_SteamAPI_ISteamUserStats_GetLeaderboardEntryCount) (intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard);
typedef ELeaderboardSortMethod (*PFN_SteamAPI_ISteamUserStats_GetLeaderboardSortMethod) (intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard);
typedef ELeaderboardDisplayType (*PFN_SteamAPI_ISteamUserStats_GetLeaderboardDisplayType) (intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_DownloadLeaderboardEntries) (intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers) (intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard, CSteamID * prgUsers, int cUsers);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry) (intptr_t instancePtr, SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t * pLeaderboardEntry, int32 * pDetails, int cDetailsMax);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_UploadLeaderboardScore) (intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32 * pScoreDetails, int cScoreDetailsCount);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_AttachLeaderboardUGC) (intptr_t instancePtr, SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers) (intptr_t instancePtr);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages) (intptr_t instancePtr);
typedef int (*PFN_SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo) (intptr_t instancePtr, char * pchName, uint32 unNameBufLen, float * pflPercent, bool * pbAchieved);
typedef int (*PFN_SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo) (intptr_t instancePtr, int iIteratorPrevious, char * pchName, uint32 unNameBufLen, float * pflPercent, bool * pbAchieved);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetAchievementAchievedPercent) (intptr_t instancePtr, const char * pchName, float * pflPercent);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUserStats_RequestGlobalStats) (intptr_t instancePtr, int nHistoryDays);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetGlobalStat) (intptr_t instancePtr, const char * pchStatName, int64 * pData);
typedef bool (*PFN_SteamAPI_ISteamUserStats_GetGlobalStat0) (intptr_t instancePtr, const char * pchStatName, double * pData);
typedef int32 (*PFN_SteamAPI_ISteamUserStats_GetGlobalStatHistory) (intptr_t instancePtr, const char * pchStatName, int64 * pData, uint32 cubData);
typedef int32 (*PFN_SteamAPI_ISteamUserStats_GetGlobalStatHistory0) (intptr_t instancePtr, const char * pchStatName, double * pData, uint32 cubData);
typedef bool (*PFN_SteamAPI_ISteamApps_BIsSubscribed) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamApps_BIsLowViolence) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamApps_BIsCybercafe) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamApps_BIsVACBanned) (intptr_t instancePtr);
typedef const char * (*PFN_SteamAPI_ISteamApps_GetCurrentGameLanguage) (intptr_t instancePtr);
typedef const char * (*PFN_SteamAPI_ISteamApps_GetAvailableGameLanguages) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamApps_BIsSubscribedApp) (intptr_t instancePtr, AppId_t appID);
typedef bool (*PFN_SteamAPI_ISteamApps_BIsDlcInstalled) (intptr_t instancePtr, AppId_t appID);
typedef uint32 (*PFN_SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime) (intptr_t instancePtr, AppId_t nAppID);
typedef bool (*PFN_SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend) (intptr_t instancePtr);
typedef int (*PFN_SteamAPI_ISteamApps_GetDLCCount) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamApps_BGetDLCDataByIndex) (intptr_t instancePtr, int iDLC, AppId_t * pAppID, bool * pbAvailable, char * pchName, int cchNameBufferSize);
typedef void (*PFN_SteamAPI_ISteamApps_InstallDLC) (intptr_t instancePtr, AppId_t nAppID);
typedef void (*PFN_SteamAPI_ISteamApps_UninstallDLC) (intptr_t instancePtr, AppId_t nAppID);
typedef void (*PFN_SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey) (intptr_t instancePtr, AppId_t nAppID);
typedef bool (*PFN_SteamAPI_ISteamApps_GetCurrentBetaName) (intptr_t instancePtr, char * pchName, int cchNameBufferSize);
typedef bool (*PFN_SteamAPI_ISteamApps_MarkContentCorrupt) (intptr_t instancePtr, bool bMissingFilesOnly);
typedef uint32 (*PFN_SteamAPI_ISteamApps_GetInstalledDepots) (intptr_t instancePtr, AppId_t appID, DepotId_t * pvecDepots, uint32 cMaxDepots);
typedef uint32 (*PFN_SteamAPI_ISteamApps_GetAppInstallDir) (intptr_t instancePtr, AppId_t appID, char * pchFolder, uint32 cchFolderBufferSize);
typedef bool (*PFN_SteamAPI_ISteamApps_BIsAppInstalled) (intptr_t instancePtr, AppId_t appID);
typedef uint64 (*PFN_SteamAPI_ISteamApps_GetAppOwner) (intptr_t instancePtr);
typedef const char * (*PFN_SteamAPI_ISteamApps_GetLaunchQueryParam) (intptr_t instancePtr, const char * pchKey);
typedef bool (*PFN_SteamAPI_ISteamApps_GetDlcDownloadProgress) (intptr_t instancePtr, AppId_t nAppID, uint64 * punBytesDownloaded, uint64 * punBytesTotal);
typedef int (*PFN_SteamAPI_ISteamApps_GetAppBuildId) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys) (intptr_t instancePtr);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamApps_GetFileDetails) (intptr_t instancePtr, const char * pszFileName);
typedef bool (*PFN_SteamAPI_ISteamNetworking_SendP2PPacket) (intptr_t instancePtr, CSteamID steamIDRemote, const void * pubData, uint32 cubData, EP2PSend eP2PSendType, int nChannel);
typedef bool (*PFN_SteamAPI_ISteamNetworking_IsP2PPacketAvailable) (intptr_t instancePtr, uint32 * pcubMsgSize, int nChannel);
typedef bool (*PFN_SteamAPI_ISteamNetworking_ReadP2PPacket) (intptr_t instancePtr, void * pubDest, uint32 cubDest, uint32 * pcubMsgSize, CSteamID * psteamIDRemote, int nChannel);
typedef bool (*PFN_SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser) (intptr_t instancePtr, CSteamID steamIDRemote);
typedef bool (*PFN_SteamAPI_ISteamNetworking_CloseP2PSessionWithUser) (intptr_t instancePtr, CSteamID steamIDRemote);
typedef bool (*PFN_SteamAPI_ISteamNetworking_CloseP2PChannelWithUser) (intptr_t instancePtr, CSteamID steamIDRemote, int nChannel);
typedef bool (*PFN_SteamAPI_ISteamNetworking_GetP2PSessionState) (intptr_t instancePtr, CSteamID steamIDRemote, P2PSessionState_t * pConnectionState);
typedef bool (*PFN_SteamAPI_ISteamNetworking_AllowP2PPacketRelay) (intptr_t instancePtr, bool bAllow);
typedef SNetListenSocket_t (*PFN_SteamAPI_ISteamNetworking_CreateListenSocket) (intptr_t instancePtr, int nVirtualP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay);
typedef SNetSocket_t (*PFN_SteamAPI_ISteamNetworking_CreateP2PConnectionSocket) (intptr_t instancePtr, CSteamID steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay);
typedef SNetSocket_t (*PFN_SteamAPI_ISteamNetworking_CreateConnectionSocket) (intptr_t instancePtr, uint32 nIP, uint16 nPort, int nTimeoutSec);
typedef bool (*PFN_SteamAPI_ISteamNetworking_DestroySocket) (intptr_t instancePtr, SNetSocket_t hSocket, bool bNotifyRemoteEnd);
typedef bool (*PFN_SteamAPI_ISteamNetworking_DestroyListenSocket) (intptr_t instancePtr, SNetListenSocket_t hSocket, bool bNotifyRemoteEnd);
typedef bool (*PFN_SteamAPI_ISteamNetworking_SendDataOnSocket) (intptr_t instancePtr, SNetSocket_t hSocket, void * pubData, uint32 cubData, bool bReliable);
typedef bool (*PFN_SteamAPI_ISteamNetworking_IsDataAvailableOnSocket) (intptr_t instancePtr, SNetSocket_t hSocket, uint32 * pcubMsgSize);
typedef bool (*PFN_SteamAPI_ISteamNetworking_RetrieveDataFromSocket) (intptr_t instancePtr, SNetSocket_t hSocket, void * pubDest, uint32 cubDest, uint32 * pcubMsgSize);
typedef bool (*PFN_SteamAPI_ISteamNetworking_IsDataAvailable) (intptr_t instancePtr, SNetListenSocket_t hListenSocket, uint32 * pcubMsgSize, SNetSocket_t * phSocket);
typedef bool (*PFN_SteamAPI_ISteamNetworking_RetrieveData) (intptr_t instancePtr, SNetListenSocket_t hListenSocket, void * pubDest, uint32 cubDest, uint32 * pcubMsgSize, SNetSocket_t * phSocket);
typedef bool (*PFN_SteamAPI_ISteamNetworking_GetSocketInfo) (intptr_t instancePtr, SNetSocket_t hSocket, CSteamID * pSteamIDRemote, int * peSocketStatus, uint32 * punIPRemote, uint16 * punPortRemote);
typedef bool (*PFN_SteamAPI_ISteamNetworking_GetListenSocketInfo) (intptr_t instancePtr, SNetListenSocket_t hListenSocket, uint32 * pnIP, uint16 * pnPort);
typedef ESNetSocketConnectionType (*PFN_SteamAPI_ISteamNetworking_GetSocketConnectionType) (intptr_t instancePtr, SNetSocket_t hSocket);
typedef int (*PFN_SteamAPI_ISteamNetworking_GetMaxPacketSize) (intptr_t instancePtr, SNetSocket_t hSocket);
typedef ScreenshotHandle (*PFN_SteamAPI_ISteamScreenshots_WriteScreenshot) (intptr_t instancePtr, void * pubRGB, uint32 cubRGB, int nWidth, int nHeight);
typedef ScreenshotHandle (*PFN_SteamAPI_ISteamScreenshots_AddScreenshotToLibrary) (intptr_t instancePtr, const char * pchFilename, const char * pchThumbnailFilename, int nWidth, int nHeight);
typedef void (*PFN_SteamAPI_ISteamScreenshots_TriggerScreenshot) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamScreenshots_HookScreenshots) (intptr_t instancePtr, bool bHook);
typedef bool (*PFN_SteamAPI_ISteamScreenshots_SetLocation) (intptr_t instancePtr, ScreenshotHandle hScreenshot, const char * pchLocation);
typedef bool (*PFN_SteamAPI_ISteamScreenshots_TagUser) (intptr_t instancePtr, ScreenshotHandle hScreenshot, CSteamID steamID);
typedef bool (*PFN_SteamAPI_ISteamScreenshots_TagPublishedFile) (intptr_t instancePtr, ScreenshotHandle hScreenshot, PublishedFileId_t unPublishedFileID);
typedef bool (*PFN_SteamAPI_ISteamScreenshots_IsScreenshotsHooked) (intptr_t instancePtr);
typedef ScreenshotHandle (*PFN_SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary) (intptr_t instancePtr, EVRScreenshotType eType, const char * pchFilename, const char * pchVRFilename);
typedef bool (*PFN_SteamAPI_ISteamMusic_BIsEnabled) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusic_BIsPlaying) (intptr_t instancePtr);
typedef AudioPlayback_Status (*PFN_SteamAPI_ISteamMusic_GetPlaybackStatus) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMusic_Play) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMusic_Pause) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMusic_PlayPrevious) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMusic_PlayNext) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamMusic_SetVolume) (intptr_t instancePtr, float flVolume);
typedef float (*PFN_SteamAPI_ISteamMusic_GetVolume) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote) (intptr_t instancePtr, const char * pchName);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_BActivationSuccess) (intptr_t instancePtr, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_SetDisplayName) (intptr_t instancePtr, const char * pchDisplayName);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64) (intptr_t instancePtr, void * pvBuffer, uint32 cbBufferLength);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_EnablePlayPrevious) (intptr_t instancePtr, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_EnablePlayNext) (intptr_t instancePtr, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_EnableShuffled) (intptr_t instancePtr, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_EnableLooped) (intptr_t instancePtr, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_EnableQueue) (intptr_t instancePtr, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_EnablePlaylists) (intptr_t instancePtr, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus) (intptr_t instancePtr, AudioPlayback_Status nStatus);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_UpdateShuffled) (intptr_t instancePtr, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_UpdateLooped) (intptr_t instancePtr, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_UpdateVolume) (intptr_t instancePtr, float flValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_CurrentEntryWillChange) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable) (intptr_t instancePtr, bool bAvailable);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText) (intptr_t instancePtr, const char * pchText);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds) (intptr_t instancePtr, int nValue);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt) (intptr_t instancePtr, void * pvBuffer, uint32 cbBufferLength);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_CurrentEntryDidChange) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_QueueWillChange) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_ResetQueueEntries) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_SetQueueEntry) (intptr_t instancePtr, int nID, int nPosition, const char * pchEntryText);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry) (intptr_t instancePtr, int nID);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_QueueDidChange) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_PlaylistWillChange) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_ResetPlaylistEntries) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_SetPlaylistEntry) (intptr_t instancePtr, int nID, int nPosition, const char * pchEntryText);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry) (intptr_t instancePtr, int nID);
typedef bool (*PFN_SteamAPI_ISteamMusicRemote_PlaylistDidChange) (intptr_t instancePtr);
typedef HTTPRequestHandle (*PFN_SteamAPI_ISteamHTTP_CreateHTTPRequest) (intptr_t instancePtr, EHTTPMethod eHTTPRequestMethod, const char * pchAbsoluteURL);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetHTTPRequestContextValue) (intptr_t instancePtr, HTTPRequestHandle hRequest, uint64 ulContextValue);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout) (intptr_t instancePtr, HTTPRequestHandle hRequest, uint32 unTimeoutSeconds);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue) (intptr_t instancePtr, HTTPRequestHandle hRequest, const char * pchHeaderName, const char * pchHeaderValue);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter) (intptr_t instancePtr, HTTPRequestHandle hRequest, const char * pchParamName, const char * pchParamValue);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SendHTTPRequest) (intptr_t instancePtr, HTTPRequestHandle hRequest, SteamAPICall_t * pCallHandle);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse) (intptr_t instancePtr, HTTPRequestHandle hRequest, SteamAPICall_t * pCallHandle);
typedef bool (*PFN_SteamAPI_ISteamHTTP_DeferHTTPRequest) (intptr_t instancePtr, HTTPRequestHandle hRequest);
typedef bool (*PFN_SteamAPI_ISteamHTTP_PrioritizeHTTPRequest) (intptr_t instancePtr, HTTPRequestHandle hRequest);
typedef bool (*PFN_SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize) (intptr_t instancePtr, HTTPRequestHandle hRequest, const char * pchHeaderName, uint32 * unResponseHeaderSize);
typedef bool (*PFN_SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue) (intptr_t instancePtr, HTTPRequestHandle hRequest, const char * pchHeaderName, uint8 * pHeaderValueBuffer, uint32 unBufferSize);
typedef bool (*PFN_SteamAPI_ISteamHTTP_GetHTTPResponseBodySize) (intptr_t instancePtr, HTTPRequestHandle hRequest, uint32 * unBodySize);
typedef bool (*PFN_SteamAPI_ISteamHTTP_GetHTTPResponseBodyData) (intptr_t instancePtr, HTTPRequestHandle hRequest, uint8 * pBodyDataBuffer, uint32 unBufferSize);
typedef bool (*PFN_SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData) (intptr_t instancePtr, HTTPRequestHandle hRequest, uint32 cOffset, uint8 * pBodyDataBuffer, uint32 unBufferSize);
typedef bool (*PFN_SteamAPI_ISteamHTTP_ReleaseHTTPRequest) (intptr_t instancePtr, HTTPRequestHandle hRequest);
typedef bool (*PFN_SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct) (intptr_t instancePtr, HTTPRequestHandle hRequest, float * pflPercentOut);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody) (intptr_t instancePtr, HTTPRequestHandle hRequest, const char * pchContentType, uint8 * pubBody, uint32 unBodyLen);
typedef HTTPCookieContainerHandle (*PFN_SteamAPI_ISteamHTTP_CreateCookieContainer) (intptr_t instancePtr, bool bAllowResponsesToModify);
typedef bool (*PFN_SteamAPI_ISteamHTTP_ReleaseCookieContainer) (intptr_t instancePtr, HTTPCookieContainerHandle hCookieContainer);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetCookie) (intptr_t instancePtr, HTTPCookieContainerHandle hCookieContainer, const char * pchHost, const char * pchUrl, const char * pchCookie);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer) (intptr_t instancePtr, HTTPRequestHandle hRequest, HTTPCookieContainerHandle hCookieContainer);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo) (intptr_t instancePtr, HTTPRequestHandle hRequest, const char * pchUserAgentInfo);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate) (intptr_t instancePtr, HTTPRequestHandle hRequest, bool bRequireVerifiedCertificate);
typedef bool (*PFN_SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS) (intptr_t instancePtr, HTTPRequestHandle hRequest, uint32 unMilliseconds);
typedef bool (*PFN_SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut) (intptr_t instancePtr, HTTPRequestHandle hRequest, bool * pbWasTimedOut);
typedef bool (*PFN_SteamAPI_ISteamController_Init) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamController_Shutdown) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamController_RunFrame) (intptr_t instancePtr);
typedef int (*PFN_SteamAPI_ISteamController_GetConnectedControllers) (intptr_t instancePtr, ControllerHandle_t * handlesOut);
typedef bool (*PFN_SteamAPI_ISteamController_ShowBindingPanel) (intptr_t instancePtr, ControllerHandle_t controllerHandle);
typedef ControllerActionSetHandle_t (*PFN_SteamAPI_ISteamController_GetActionSetHandle) (intptr_t instancePtr, const char * pszActionSetName);
typedef void (*PFN_SteamAPI_ISteamController_ActivateActionSet) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle);
typedef ControllerActionSetHandle_t (*PFN_SteamAPI_ISteamController_GetCurrentActionSet) (intptr_t instancePtr, ControllerHandle_t controllerHandle);
typedef void (*PFN_SteamAPI_ISteamController_ActivateActionSetLayer) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle);
typedef void (*PFN_SteamAPI_ISteamController_DeactivateActionSetLayer) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle);
typedef void (*PFN_SteamAPI_ISteamController_DeactivateAllActionSetLayers) (intptr_t instancePtr, ControllerHandle_t controllerHandle);
typedef int (*PFN_SteamAPI_ISteamController_GetActiveActionSetLayers) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t * handlesOut);
typedef ControllerDigitalActionHandle_t (*PFN_SteamAPI_ISteamController_GetDigitalActionHandle) (intptr_t instancePtr, const char * pszActionName);
typedef ControllerDigitalActionData_t (*PFN_SteamAPI_ISteamController_GetDigitalActionData) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle);
typedef int (*PFN_SteamAPI_ISteamController_GetDigitalActionOrigins) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerDigitalActionHandle_t digitalActionHandle, EControllerActionOrigin * originsOut);
typedef ControllerAnalogActionHandle_t (*PFN_SteamAPI_ISteamController_GetAnalogActionHandle) (intptr_t instancePtr, const char * pszActionName);
typedef ControllerAnalogActionData_t (*PFN_SteamAPI_ISteamController_GetAnalogActionData) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle);
typedef int (*PFN_SteamAPI_ISteamController_GetAnalogActionOrigins) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerAnalogActionHandle_t analogActionHandle, EControllerActionOrigin * originsOut);
typedef void (*PFN_SteamAPI_ISteamController_StopAnalogActionMomentum) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t eAction);
typedef void (*PFN_SteamAPI_ISteamController_TriggerHapticPulse) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec);
typedef void (*PFN_SteamAPI_ISteamController_TriggerRepeatedHapticPulse) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags);
typedef void (*PFN_SteamAPI_ISteamController_TriggerVibration) (intptr_t instancePtr, ControllerHandle_t controllerHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed);
typedef void (*PFN_SteamAPI_ISteamController_SetLEDColor) (intptr_t instancePtr, ControllerHandle_t controllerHandle, uint8 nColorR, uint8 nColorG, uint8 nColorB, unsigned int nFlags);
typedef int (*PFN_SteamAPI_ISteamController_GetGamepadIndexForController) (intptr_t instancePtr, ControllerHandle_t ulControllerHandle);
typedef ControllerHandle_t (*PFN_SteamAPI_ISteamController_GetControllerForGamepadIndex) (intptr_t instancePtr, int nIndex);
typedef ControllerMotionData_t (*PFN_SteamAPI_ISteamController_GetMotionData) (intptr_t instancePtr, ControllerHandle_t controllerHandle);
typedef bool (*PFN_SteamAPI_ISteamController_ShowDigitalActionOrigins) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle, float flScale, float flXPosition, float flYPosition);
typedef bool (*PFN_SteamAPI_ISteamController_ShowAnalogActionOrigins) (intptr_t instancePtr, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle, float flScale, float flXPosition, float flYPosition);
typedef const char * (*PFN_SteamAPI_ISteamController_GetStringForActionOrigin) (intptr_t instancePtr, EControllerActionOrigin eOrigin);
typedef const char * (*PFN_SteamAPI_ISteamController_GetGlyphForActionOrigin) (intptr_t instancePtr, EControllerActionOrigin eOrigin);
typedef ESteamInputType (*PFN_SteamAPI_ISteamController_GetInputTypeForHandle) (intptr_t instancePtr, ControllerHandle_t controllerHandle);
typedef UGCQueryHandle_t (*PFN_SteamAPI_ISteamUGC_CreateQueryUserUGCRequest) (intptr_t instancePtr, AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);
typedef UGCQueryHandle_t (*PFN_SteamAPI_ISteamUGC_CreateQueryAllUGCRequest) (intptr_t instancePtr, EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage);
typedef UGCQueryHandle_t (*PFN_SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest) (intptr_t instancePtr, PublishedFileId_t * pvecPublishedFileID, uint32 unNumPublishedFileIDs);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_SendQueryUGCRequest) (intptr_t instancePtr, UGCQueryHandle_t handle);
typedef bool (*PFN_SteamAPI_ISteamUGC_GetQueryUGCResult) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t * pDetails);
typedef bool (*PFN_SteamAPI_ISteamUGC_GetQueryUGCPreviewURL) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index, char * pchURL, uint32 cchURLSize);
typedef bool (*PFN_SteamAPI_ISteamUGC_GetQueryUGCMetadata) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index, char * pchMetadata, uint32 cchMetadatasize);
typedef bool (*PFN_SteamAPI_ISteamUGC_GetQueryUGCChildren) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index, PublishedFileId_t * pvecPublishedFileID, uint32 cMaxEntries);
typedef bool (*PFN_SteamAPI_ISteamUGC_GetQueryUGCStatistic) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index, EItemStatistic eStatType, uint64 * pStatValue);
typedef uint32 (*PFN_SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index);
typedef bool (*PFN_SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index, uint32 previewIndex, char * pchURLOrVideoID, uint32 cchURLSize, char * pchOriginalFileName, uint32 cchOriginalFileNameSize, EItemPreviewType * pPreviewType);
typedef uint32 (*PFN_SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index);
typedef bool (*PFN_SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 index, uint32 keyValueTagIndex, char * pchKey, uint32 cchKeySize, char * pchValue, uint32 cchValueSize);
typedef bool (*PFN_SteamAPI_ISteamUGC_ReleaseQueryUGCRequest) (intptr_t instancePtr, UGCQueryHandle_t handle);
typedef bool (*PFN_SteamAPI_ISteamUGC_AddRequiredTag) (intptr_t instancePtr, UGCQueryHandle_t handle, const char * pTagName);
typedef bool (*PFN_SteamAPI_ISteamUGC_AddExcludedTag) (intptr_t instancePtr, UGCQueryHandle_t handle, const char * pTagName);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetReturnOnlyIDs) (intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnOnlyIDs);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetReturnKeyValueTags) (intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnKeyValueTags);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetReturnLongDescription) (intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnLongDescription);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetReturnMetadata) (intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnMetadata);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetReturnChildren) (intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnChildren);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetReturnAdditionalPreviews) (intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnAdditionalPreviews);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetReturnTotalOnly) (intptr_t instancePtr, UGCQueryHandle_t handle, bool bReturnTotalOnly);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetReturnPlaytimeStats) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 unDays);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetLanguage) (intptr_t instancePtr, UGCQueryHandle_t handle, const char * pchLanguage);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetAllowCachedResponse) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 unMaxAgeSeconds);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetCloudFileNameFilter) (intptr_t instancePtr, UGCQueryHandle_t handle, const char * pMatchCloudFileName);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetMatchAnyTag) (intptr_t instancePtr, UGCQueryHandle_t handle, bool bMatchAnyTag);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetSearchText) (intptr_t instancePtr, UGCQueryHandle_t handle, const char * pSearchText);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetRankedByTrendDays) (intptr_t instancePtr, UGCQueryHandle_t handle, uint32 unDays);
typedef bool (*PFN_SteamAPI_ISteamUGC_AddRequiredKeyValueTag) (intptr_t instancePtr, UGCQueryHandle_t handle, const char * pKey, const char * pValue);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_RequestUGCDetails) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_CreateItem) (intptr_t instancePtr, AppId_t nConsumerAppId, EWorkshopFileType eFileType);
typedef UGCUpdateHandle_t (*PFN_SteamAPI_ISteamUGC_StartItemUpdate) (intptr_t instancePtr, AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetItemTitle) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pchTitle);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetItemDescription) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pchDescription);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetItemUpdateLanguage) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pchLanguage);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetItemMetadata) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pchMetaData);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetItemVisibility) (intptr_t instancePtr, UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetItemTags) (intptr_t instancePtr, UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t * pTags);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetItemContent) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pszContentFolder);
typedef bool (*PFN_SteamAPI_ISteamUGC_SetItemPreview) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pszPreviewFile);
typedef bool (*PFN_SteamAPI_ISteamUGC_RemoveItemKeyValueTags) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pchKey);
typedef bool (*PFN_SteamAPI_ISteamUGC_AddItemKeyValueTag) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pchKey, const char * pchValue);
typedef bool (*PFN_SteamAPI_ISteamUGC_AddItemPreviewFile) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pszPreviewFile, EItemPreviewType type);
typedef bool (*PFN_SteamAPI_ISteamUGC_AddItemPreviewVideo) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pszVideoID);
typedef bool (*PFN_SteamAPI_ISteamUGC_UpdateItemPreviewFile) (intptr_t instancePtr, UGCUpdateHandle_t handle, uint32 index, const char * pszPreviewFile);
typedef bool (*PFN_SteamAPI_ISteamUGC_UpdateItemPreviewVideo) (intptr_t instancePtr, UGCUpdateHandle_t handle, uint32 index, const char * pszVideoID);
typedef bool (*PFN_SteamAPI_ISteamUGC_RemoveItemPreview) (intptr_t instancePtr, UGCUpdateHandle_t handle, uint32 index);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_SubmitItemUpdate) (intptr_t instancePtr, UGCUpdateHandle_t handle, const char * pchChangeNote);
typedef EItemUpdateStatus (*PFN_SteamAPI_ISteamUGC_GetItemUpdateProgress) (intptr_t instancePtr, UGCUpdateHandle_t handle, uint64 * punBytesProcessed, uint64 * punBytesTotal);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_SetUserItemVote) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID, bool bVoteUp);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_GetUserItemVote) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_AddItemToFavorites) (intptr_t instancePtr, AppId_t nAppId, PublishedFileId_t nPublishedFileID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_RemoveItemFromFavorites) (intptr_t instancePtr, AppId_t nAppId, PublishedFileId_t nPublishedFileID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_SubscribeItem) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_UnsubscribeItem) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID);
typedef uint32 (*PFN_SteamAPI_ISteamUGC_GetNumSubscribedItems) (intptr_t instancePtr);
typedef uint32 (*PFN_SteamAPI_ISteamUGC_GetSubscribedItems) (intptr_t instancePtr, PublishedFileId_t * pvecPublishedFileID, uint32 cMaxEntries);
typedef uint32 (*PFN_SteamAPI_ISteamUGC_GetItemState) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID);
typedef bool (*PFN_SteamAPI_ISteamUGC_GetItemInstallInfo) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID, uint64 * punSizeOnDisk, char * pchFolder, uint32 cchFolderSize, uint32 * punTimeStamp);
typedef bool (*PFN_SteamAPI_ISteamUGC_GetItemDownloadInfo) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID, uint64 * punBytesDownloaded, uint64 * punBytesTotal);
typedef bool (*PFN_SteamAPI_ISteamUGC_DownloadItem) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID, bool bHighPriority);
typedef bool (*PFN_SteamAPI_ISteamUGC_BInitWorkshopForGameServer) (intptr_t instancePtr, DepotId_t unWorkshopDepotID, const char * pszFolder);
typedef void (*PFN_SteamAPI_ISteamUGC_SuspendDownloads) (intptr_t instancePtr, bool bSuspend);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_StartPlaytimeTracking) (intptr_t instancePtr, PublishedFileId_t * pvecPublishedFileID, uint32 unNumPublishedFileIDs);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_StopPlaytimeTracking) (intptr_t instancePtr, PublishedFileId_t * pvecPublishedFileID, uint32 unNumPublishedFileIDs);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems) (intptr_t instancePtr);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_AddDependency) (intptr_t instancePtr, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_RemoveDependency) (intptr_t instancePtr, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_AddAppDependency) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID, AppId_t nAppID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_RemoveAppDependency) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID, AppId_t nAppID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_GetAppDependencies) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamUGC_DeleteItem) (intptr_t instancePtr, PublishedFileId_t nPublishedFileID);
typedef uint32 (*PFN_SteamAPI_ISteamAppList_GetNumInstalledApps) (intptr_t instancePtr);
typedef uint32 (*PFN_SteamAPI_ISteamAppList_GetInstalledApps) (intptr_t instancePtr, AppId_t * pvecAppID, uint32 unMaxAppIDs);
typedef int (*PFN_SteamAPI_ISteamAppList_GetAppName) (intptr_t instancePtr, AppId_t nAppID, char * pchName, int cchNameMax);
typedef int (*PFN_SteamAPI_ISteamAppList_GetAppInstallDir) (intptr_t instancePtr, AppId_t nAppID, char * pchDirectory, int cchNameMax);
typedef int (*PFN_SteamAPI_ISteamAppList_GetAppBuildId) (intptr_t instancePtr, AppId_t nAppID);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_DestructISteamHTMLSurface) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamHTMLSurface_Init) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamHTMLSurface_Shutdown) (intptr_t instancePtr);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamHTMLSurface_CreateBrowser) (intptr_t instancePtr, const char * pchUserAgent, const char * pchUserCSS);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_RemoveBrowser) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_LoadURL) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, const char * pchURL, const char * pchPostData);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_SetSize) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, uint32 unWidth, uint32 unHeight);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_StopLoad) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_Reload) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_GoBack) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_GoForward) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_AddHeader) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, const char * pchKey, const char * pchValue);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_ExecuteJavascript) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, const char * pchScript);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_SetHorizontalScroll) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_SetVerticalScroll) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_SetKeyFocus) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, bool bHasKeyFocus);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_ViewSource) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_CopyToClipboard) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_PasteFromClipboard) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_Find) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, const char * pchSearchStr, bool bCurrentlyInFind, bool bReverse);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_StopFind) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_GetLinkAtPosition) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, int x, int y);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_SetCookie) (intptr_t instancePtr, const char * pchHostname, const char * pchKey, const char * pchValue, const char * pchPath, RTime32 nExpires, bool bSecure, bool bHTTPOnly);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_SetPageScaleFactor) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, float flZoom, int nPointX, int nPointY);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_SetBackgroundMode) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, bool bBackgroundMode);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, float flDPIScaling);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_AllowStartRequest) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, bool bAllowed);
typedef void (*PFN_SteamAPI_ISteamHTMLSurface_JSDialogResponse) (intptr_t instancePtr, HHTMLBrowser unBrowserHandle, bool bResult);
typedef EResult (*PFN_SteamAPI_ISteamInventory_GetResultStatus) (intptr_t instancePtr, SteamInventoryResult_t resultHandle);
typedef bool (*PFN_SteamAPI_ISteamInventory_GetResultItems) (intptr_t instancePtr, SteamInventoryResult_t resultHandle, SteamItemDetails_t * pOutItemsArray, uint32 * punOutItemsArraySize);
typedef bool (*PFN_SteamAPI_ISteamInventory_GetResultItemProperty) (intptr_t instancePtr, SteamInventoryResult_t resultHandle, uint32 unItemIndex, const char * pchPropertyName, char * pchValueBuffer, uint32 * punValueBufferSizeOut);
typedef uint32 (*PFN_SteamAPI_ISteamInventory_GetResultTimestamp) (intptr_t instancePtr, SteamInventoryResult_t resultHandle);
typedef bool (*PFN_SteamAPI_ISteamInventory_CheckResultSteamID) (intptr_t instancePtr, SteamInventoryResult_t resultHandle, CSteamID steamIDExpected);
typedef void (*PFN_SteamAPI_ISteamInventory_DestroyResult) (intptr_t instancePtr, SteamInventoryResult_t resultHandle);
typedef bool (*PFN_SteamAPI_ISteamInventory_GetAllItems) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle);
typedef bool (*PFN_SteamAPI_ISteamInventory_GetItemsByID) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle, const SteamItemInstanceID_t * pInstanceIDs, uint32 unCountInstanceIDs);
typedef bool (*PFN_SteamAPI_ISteamInventory_SerializeResult) (intptr_t instancePtr, SteamInventoryResult_t resultHandle, void * pOutBuffer, uint32 * punOutBufferSize);
typedef bool (*PFN_SteamAPI_ISteamInventory_DeserializeResult) (intptr_t instancePtr, SteamInventoryResult_t * pOutResultHandle, const void * pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE);
typedef bool (*PFN_SteamAPI_ISteamInventory_GenerateItems) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle, const SteamItemDef_t * pArrayItemDefs, const uint32 * punArrayQuantity, uint32 unArrayLength);
typedef bool (*PFN_SteamAPI_ISteamInventory_GrantPromoItems) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle);
typedef bool (*PFN_SteamAPI_ISteamInventory_AddPromoItem) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle, SteamItemDef_t itemDef);
typedef bool (*PFN_SteamAPI_ISteamInventory_AddPromoItems) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle, const SteamItemDef_t * pArrayItemDefs, uint32 unArrayLength);
typedef bool (*PFN_SteamAPI_ISteamInventory_ConsumeItem) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle, SteamItemInstanceID_t itemConsume, uint32 unQuantity);
typedef bool (*PFN_SteamAPI_ISteamInventory_ExchangeItems) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle, const SteamItemDef_t * pArrayGenerate, const uint32 * punArrayGenerateQuantity, uint32 unArrayGenerateLength, const SteamItemInstanceID_t * pArrayDestroy, const uint32 * punArrayDestroyQuantity, uint32 unArrayDestroyLength);
typedef bool (*PFN_SteamAPI_ISteamInventory_TransferItemQuantity) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle, SteamItemInstanceID_t itemIdSource, uint32 unQuantity, SteamItemInstanceID_t itemIdDest);
typedef void (*PFN_SteamAPI_ISteamInventory_SendItemDropHeartbeat) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamInventory_TriggerItemDrop) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle, SteamItemDef_t dropListDefinition);
typedef bool (*PFN_SteamAPI_ISteamInventory_TradeItems) (intptr_t instancePtr, SteamInventoryResult_t * pResultHandle, CSteamID steamIDTradePartner, const SteamItemInstanceID_t * pArrayGive, const uint32 * pArrayGiveQuantity, uint32 nArrayGiveLength, const SteamItemInstanceID_t * pArrayGet, const uint32 * pArrayGetQuantity, uint32 nArrayGetLength);
typedef bool (*PFN_SteamAPI_ISteamInventory_LoadItemDefinitions) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamInventory_GetItemDefinitionIDs) (intptr_t instancePtr, SteamItemDef_t * pItemDefIDs, uint32 * punItemDefIDsArraySize);
typedef bool (*PFN_SteamAPI_ISteamInventory_GetItemDefinitionProperty) (intptr_t instancePtr, SteamItemDef_t iDefinition, const char * pchPropertyName, char * pchValueBuffer, uint32 * punValueBufferSizeOut);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs) (intptr_t instancePtr, CSteamID steamID);
typedef bool (*PFN_SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs) (intptr_t instancePtr, CSteamID steamID, SteamItemDef_t * pItemDefIDs, uint32 * punItemDefIDsArraySize);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamInventory_StartPurchase) (intptr_t instancePtr, const SteamItemDef_t * pArrayItemDefs, const uint32 * punArrayQuantity, uint32 unArrayLength);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamInventory_RequestPrices) (intptr_t instancePtr);
typedef uint32 (*PFN_SteamAPI_ISteamInventory_GetNumItemsWithPrices) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamInventory_GetItemsWithPrices) (intptr_t instancePtr, SteamItemDef_t * pArrayItemDefs, uint64 * pPrices, uint32 unArrayLength);
typedef bool (*PFN_SteamAPI_ISteamInventory_GetItemPrice) (intptr_t instancePtr, SteamItemDef_t iDefinition, uint64 * pPrice);
typedef SteamInventoryUpdateHandle_t (*PFN_SteamAPI_ISteamInventory_StartUpdateProperties) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamInventory_RemoveProperty) (intptr_t instancePtr, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName);
typedef bool (*PFN_SteamAPI_ISteamInventory_SetProperty) (intptr_t instancePtr, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName, const char * pchPropertyValue);
typedef bool (*PFN_SteamAPI_ISteamInventory_SetProperty0) (intptr_t instancePtr, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName, bool bValue);
typedef bool (*PFN_SteamAPI_ISteamInventory_SetProperty1) (intptr_t instancePtr, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName, int64 nValue);
typedef bool (*PFN_SteamAPI_ISteamInventory_SetProperty2) (intptr_t instancePtr, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName, float flValue);
typedef bool (*PFN_SteamAPI_ISteamInventory_SubmitUpdateProperties) (intptr_t instancePtr, SteamInventoryUpdateHandle_t handle, SteamInventoryResult_t * pResultHandle);
typedef void (*PFN_SteamAPI_ISteamVideo_GetVideoURL) (intptr_t instancePtr, AppId_t unVideoAppID);
typedef bool (*PFN_SteamAPI_ISteamVideo_IsBroadcasting) (intptr_t instancePtr, int * pnNumViewers);
typedef void (*PFN_SteamAPI_ISteamVideo_GetOPFSettings) (intptr_t instancePtr, AppId_t unVideoAppID);
typedef bool (*PFN_SteamAPI_ISteamVideo_GetOPFStringForApp) (intptr_t instancePtr, AppId_t unVideoAppID, char * pchBuffer, int32 * pnBufferSize);
typedef bool (*PFN_SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamParentalSettings_BIsParentalLockLocked) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamParentalSettings_BIsAppBlocked) (intptr_t instancePtr, AppId_t nAppID);
typedef bool (*PFN_SteamAPI_ISteamParentalSettings_BIsAppInBlockList) (intptr_t instancePtr, AppId_t nAppID);
typedef bool (*PFN_SteamAPI_ISteamParentalSettings_BIsFeatureBlocked) (intptr_t instancePtr, EParentalFeature eFeature);
typedef bool (*PFN_SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList) (intptr_t instancePtr, EParentalFeature eFeature);
typedef bool (*PFN_SteamAPI_ISteamGameServer_InitGameServer) (intptr_t instancePtr, uint32 unIP, uint16 usGamePort, uint16 usQueryPort, uint32 unFlags, AppId_t nGameAppId, const char * pchVersionString);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetProduct) (intptr_t instancePtr, const char * pszProduct);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetGameDescription) (intptr_t instancePtr, const char * pszGameDescription);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetModDir) (intptr_t instancePtr, const char * pszModDir);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetDedicatedServer) (intptr_t instancePtr, bool bDedicated);
typedef void (*PFN_SteamAPI_ISteamGameServer_LogOn) (intptr_t instancePtr, const char * pszToken);
typedef void (*PFN_SteamAPI_ISteamGameServer_LogOnAnonymous) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamGameServer_LogOff) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamGameServer_BLoggedOn) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamGameServer_BSecure) (intptr_t instancePtr);
typedef uint64 (*PFN_SteamAPI_ISteamGameServer_GetSteamID) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamGameServer_WasRestartRequested) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetMaxPlayerCount) (intptr_t instancePtr, int cPlayersMax);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetBotPlayerCount) (intptr_t instancePtr, int cBotplayers);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetServerName) (intptr_t instancePtr, const char * pszServerName);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetMapName) (intptr_t instancePtr, const char * pszMapName);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetPasswordProtected) (intptr_t instancePtr, bool bPasswordProtected);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetSpectatorPort) (intptr_t instancePtr, uint16 unSpectatorPort);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetSpectatorServerName) (intptr_t instancePtr, const char * pszSpectatorServerName);
typedef void (*PFN_SteamAPI_ISteamGameServer_ClearAllKeyValues) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetKeyValue) (intptr_t instancePtr, const char * pKey, const char * pValue);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetGameTags) (intptr_t instancePtr, const char * pchGameTags);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetGameData) (intptr_t instancePtr, const char * pchGameData);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetRegion) (intptr_t instancePtr, const char * pszRegion);
typedef bool (*PFN_SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate) (intptr_t instancePtr, uint32 unIPClient, const void * pvAuthBlob, uint32 cubAuthBlobSize, CSteamID * pSteamIDUser);
typedef uint64 (*PFN_SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection) (intptr_t instancePtr);
typedef void (*PFN_SteamAPI_ISteamGameServer_SendUserDisconnect) (intptr_t instancePtr, CSteamID steamIDUser);
typedef bool (*PFN_SteamAPI_ISteamGameServer_BUpdateUserData) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchPlayerName, uint32 uScore);
typedef HAuthTicket (*PFN_SteamAPI_ISteamGameServer_GetAuthSessionTicket) (intptr_t instancePtr, void * pTicket, int cbMaxTicket, uint32 * pcbTicket);
typedef EBeginAuthSessionResult (*PFN_SteamAPI_ISteamGameServer_BeginAuthSession) (intptr_t instancePtr, const void * pAuthTicket, int cbAuthTicket, CSteamID steamID);
typedef void (*PFN_SteamAPI_ISteamGameServer_EndAuthSession) (intptr_t instancePtr, CSteamID steamID);
typedef void (*PFN_SteamAPI_ISteamGameServer_CancelAuthTicket) (intptr_t instancePtr, HAuthTicket hAuthTicket);
typedef EUserHasLicenseForAppResult (*PFN_SteamAPI_ISteamGameServer_UserHasLicenseForApp) (intptr_t instancePtr, CSteamID steamID, AppId_t appID);
typedef bool (*PFN_SteamAPI_ISteamGameServer_RequestUserGroupStatus) (intptr_t instancePtr, CSteamID steamIDUser, CSteamID steamIDGroup);
typedef void (*PFN_SteamAPI_ISteamGameServer_GetGameplayStats) (intptr_t instancePtr);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamGameServer_GetServerReputation) (intptr_t instancePtr);
typedef uint32 (*PFN_SteamAPI_ISteamGameServer_GetPublicIP) (intptr_t instancePtr);
typedef bool (*PFN_SteamAPI_ISteamGameServer_HandleIncomingPacket) (intptr_t instancePtr, const void * pData, int cbData, uint32 srcIP, uint16 srcPort);
typedef int (*PFN_SteamAPI_ISteamGameServer_GetNextOutgoingPacket) (intptr_t instancePtr, void * pOut, int cbMaxOut, uint32 * pNetAdr, uint16 * pPort);
typedef void (*PFN_SteamAPI_ISteamGameServer_EnableHeartbeats) (intptr_t instancePtr, bool bActive);
typedef void (*PFN_SteamAPI_ISteamGameServer_SetHeartbeatInterval) (intptr_t instancePtr, int iHeartbeatInterval);
typedef void (*PFN_SteamAPI_ISteamGameServer_ForceHeartbeat) (intptr_t instancePtr);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamGameServer_AssociateWithClan) (intptr_t instancePtr, CSteamID steamIDClan);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility) (intptr_t instancePtr, CSteamID steamIDNewPlayer);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamGameServerStats_RequestUserStats) (intptr_t instancePtr, CSteamID steamIDUser);
typedef bool (*PFN_SteamAPI_ISteamGameServerStats_GetUserStat) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, int32 * pData);
typedef bool (*PFN_SteamAPI_ISteamGameServerStats_GetUserStat0) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, float * pData);
typedef bool (*PFN_SteamAPI_ISteamGameServerStats_GetUserAchievement) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, bool * pbAchieved);
typedef bool (*PFN_SteamAPI_ISteamGameServerStats_SetUserStat) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, int32 nData);
typedef bool (*PFN_SteamAPI_ISteamGameServerStats_SetUserStat0) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, float fData);
typedef bool (*PFN_SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName, float flCountThisSession, double dSessionLength);
typedef bool (*PFN_SteamAPI_ISteamGameServerStats_SetUserAchievement) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName);
typedef bool (*PFN_SteamAPI_ISteamGameServerStats_ClearUserAchievement) (intptr_t instancePtr, CSteamID steamIDUser, const char * pchName);
typedef SteamAPICall_t (*PFN_SteamAPI_ISteamGameServerStats_StoreUserStats) (intptr_t instancePtr, CSteamID steamIDUser);

PFN_SteamAPI_Init SteamAPI_Init;
PFN_SteamAPI_Shutdown SteamAPI_Shutdown;
PFN_SteamAPI_RestartAppIfNecessary SteamAPI_RestartAppIfNecessary;
PFN_SteamAPI_ReleaseCurrentThreadMemory SteamAPI_ReleaseCurrentThreadMemory;
PFN_SteamAPI_WriteMiniDump SteamAPI_WriteMiniDump;
PFN_SteamAPI_SetMiniDumpComment SteamAPI_SetMiniDumpComment;
PFN_SteamClient SteamClient;
PFN_SteamAPI_ISteamClient_CreateSteamPipe SteamAPI_ISteamClient_CreateSteamPipe;
PFN_SteamAPI_ISteamClient_BReleaseSteamPipe SteamAPI_ISteamClient_BReleaseSteamPipe;
PFN_SteamAPI_ISteamClient_ConnectToGlobalUser SteamAPI_ISteamClient_ConnectToGlobalUser;
PFN_SteamAPI_ISteamClient_CreateLocalUser SteamAPI_ISteamClient_CreateLocalUser;
PFN_SteamAPI_ISteamClient_ReleaseUser SteamAPI_ISteamClient_ReleaseUser;
PFN_SteamAPI_ISteamClient_GetISteamUser SteamAPI_ISteamClient_GetISteamUser;
PFN_SteamAPI_ISteamClient_GetISteamGameServer SteamAPI_ISteamClient_GetISteamGameServer;
PFN_SteamAPI_ISteamClient_SetLocalIPBinding SteamAPI_ISteamClient_SetLocalIPBinding;
PFN_SteamAPI_ISteamClient_GetISteamFriends SteamAPI_ISteamClient_GetISteamFriends;
PFN_SteamAPI_ISteamClient_GetISteamUtils SteamAPI_ISteamClient_GetISteamUtils;
PFN_SteamAPI_ISteamClient_GetISteamMatchmaking SteamAPI_ISteamClient_GetISteamMatchmaking;
PFN_SteamAPI_ISteamClient_GetISteamMatchmakingServers SteamAPI_ISteamClient_GetISteamMatchmakingServers;
PFN_SteamAPI_ISteamClient_GetISteamGenericInterface SteamAPI_ISteamClient_GetISteamGenericInterface;
PFN_SteamAPI_ISteamClient_GetISteamUserStats SteamAPI_ISteamClient_GetISteamUserStats;
PFN_SteamAPI_ISteamClient_GetISteamGameServerStats SteamAPI_ISteamClient_GetISteamGameServerStats;
PFN_SteamAPI_ISteamClient_GetISteamApps SteamAPI_ISteamClient_GetISteamApps;
PFN_SteamAPI_ISteamClient_GetISteamNetworking SteamAPI_ISteamClient_GetISteamNetworking;
PFN_SteamAPI_ISteamClient_GetISteamRemoteStorage SteamAPI_ISteamClient_GetISteamRemoteStorage;
PFN_SteamAPI_ISteamClient_GetISteamScreenshots SteamAPI_ISteamClient_GetISteamScreenshots;
PFN_SteamAPI_ISteamClient_GetIPCCallCount SteamAPI_ISteamClient_GetIPCCallCount;
PFN_SteamAPI_ISteamClient_SetWarningMessageHook SteamAPI_ISteamClient_SetWarningMessageHook;
PFN_SteamAPI_ISteamClient_BShutdownIfAllPipesClosed SteamAPI_ISteamClient_BShutdownIfAllPipesClosed;
PFN_SteamAPI_ISteamClient_GetISteamHTTP SteamAPI_ISteamClient_GetISteamHTTP;
PFN_SteamAPI_ISteamClient_GetISteamController SteamAPI_ISteamClient_GetISteamController;
PFN_SteamAPI_ISteamClient_GetISteamUGC SteamAPI_ISteamClient_GetISteamUGC;
PFN_SteamAPI_ISteamClient_GetISteamAppList SteamAPI_ISteamClient_GetISteamAppList;
PFN_SteamAPI_ISteamClient_GetISteamMusic SteamAPI_ISteamClient_GetISteamMusic;
PFN_SteamAPI_ISteamClient_GetISteamMusicRemote SteamAPI_ISteamClient_GetISteamMusicRemote;
PFN_SteamAPI_ISteamClient_GetISteamHTMLSurface SteamAPI_ISteamClient_GetISteamHTMLSurface;
PFN_SteamAPI_ISteamClient_GetISteamInventory SteamAPI_ISteamClient_GetISteamInventory;
PFN_SteamAPI_ISteamClient_GetISteamVideo SteamAPI_ISteamClient_GetISteamVideo;
PFN_SteamAPI_ISteamClient_GetISteamParentalSettings SteamAPI_ISteamClient_GetISteamParentalSettings;
PFN_SteamAPI_ISteamUser_GetHSteamUser SteamAPI_ISteamUser_GetHSteamUser;
PFN_SteamAPI_ISteamUser_BLoggedOn SteamAPI_ISteamUser_BLoggedOn;
PFN_SteamAPI_ISteamUser_GetSteamID SteamAPI_ISteamUser_GetSteamID;
PFN_SteamAPI_ISteamUser_InitiateGameConnection SteamAPI_ISteamUser_InitiateGameConnection;
PFN_SteamAPI_ISteamUser_TerminateGameConnection SteamAPI_ISteamUser_TerminateGameConnection;
PFN_SteamAPI_ISteamUser_TrackAppUsageEvent SteamAPI_ISteamUser_TrackAppUsageEvent;
PFN_SteamAPI_ISteamUser_GetUserDataFolder SteamAPI_ISteamUser_GetUserDataFolder;
PFN_SteamAPI_ISteamUser_StartVoiceRecording SteamAPI_ISteamUser_StartVoiceRecording;
PFN_SteamAPI_ISteamUser_StopVoiceRecording SteamAPI_ISteamUser_StopVoiceRecording;
PFN_SteamAPI_ISteamUser_GetAvailableVoice SteamAPI_ISteamUser_GetAvailableVoice;
PFN_SteamAPI_ISteamUser_GetVoice SteamAPI_ISteamUser_GetVoice;
PFN_SteamAPI_ISteamUser_DecompressVoice SteamAPI_ISteamUser_DecompressVoice;
PFN_SteamAPI_ISteamUser_GetVoiceOptimalSampleRate SteamAPI_ISteamUser_GetVoiceOptimalSampleRate;
PFN_SteamAPI_ISteamUser_GetAuthSessionTicket SteamAPI_ISteamUser_GetAuthSessionTicket;
PFN_SteamAPI_ISteamUser_BeginAuthSession SteamAPI_ISteamUser_BeginAuthSession;
PFN_SteamAPI_ISteamUser_EndAuthSession SteamAPI_ISteamUser_EndAuthSession;
PFN_SteamAPI_ISteamUser_CancelAuthTicket SteamAPI_ISteamUser_CancelAuthTicket;
PFN_SteamAPI_ISteamUser_UserHasLicenseForApp SteamAPI_ISteamUser_UserHasLicenseForApp;
PFN_SteamAPI_ISteamUser_BIsBehindNAT SteamAPI_ISteamUser_BIsBehindNAT;
PFN_SteamAPI_ISteamUser_AdvertiseGame SteamAPI_ISteamUser_AdvertiseGame;
PFN_SteamAPI_ISteamUser_RequestEncryptedAppTicket SteamAPI_ISteamUser_RequestEncryptedAppTicket;
PFN_SteamAPI_ISteamUser_GetEncryptedAppTicket SteamAPI_ISteamUser_GetEncryptedAppTicket;
PFN_SteamAPI_ISteamUser_GetGameBadgeLevel SteamAPI_ISteamUser_GetGameBadgeLevel;
PFN_SteamAPI_ISteamUser_GetPlayerSteamLevel SteamAPI_ISteamUser_GetPlayerSteamLevel;
PFN_SteamAPI_ISteamUser_RequestStoreAuthURL SteamAPI_ISteamUser_RequestStoreAuthURL;
PFN_SteamAPI_ISteamUser_BIsPhoneVerified SteamAPI_ISteamUser_BIsPhoneVerified;
PFN_SteamAPI_ISteamUser_BIsTwoFactorEnabled SteamAPI_ISteamUser_BIsTwoFactorEnabled;
PFN_SteamAPI_ISteamUser_BIsPhoneIdentifying SteamAPI_ISteamUser_BIsPhoneIdentifying;
PFN_SteamAPI_ISteamUser_BIsPhoneRequiringVerification SteamAPI_ISteamUser_BIsPhoneRequiringVerification;
PFN_SteamAPI_ISteamFriends_GetPersonaName SteamAPI_ISteamFriends_GetPersonaName;
PFN_SteamAPI_ISteamFriends_SetPersonaName SteamAPI_ISteamFriends_SetPersonaName;
PFN_SteamAPI_ISteamFriends_GetPersonaState SteamAPI_ISteamFriends_GetPersonaState;
PFN_SteamAPI_ISteamFriends_GetFriendCount SteamAPI_ISteamFriends_GetFriendCount;
PFN_SteamAPI_ISteamFriends_GetFriendByIndex SteamAPI_ISteamFriends_GetFriendByIndex;
PFN_SteamAPI_ISteamFriends_GetFriendRelationship SteamAPI_ISteamFriends_GetFriendRelationship;
PFN_SteamAPI_ISteamFriends_GetFriendPersonaState SteamAPI_ISteamFriends_GetFriendPersonaState;
PFN_SteamAPI_ISteamFriends_GetFriendPersonaName SteamAPI_ISteamFriends_GetFriendPersonaName;
PFN_SteamAPI_ISteamFriends_GetFriendGamePlayed SteamAPI_ISteamFriends_GetFriendGamePlayed;
PFN_SteamAPI_ISteamFriends_GetFriendPersonaNameHistory SteamAPI_ISteamFriends_GetFriendPersonaNameHistory;
PFN_SteamAPI_ISteamFriends_GetFriendSteamLevel SteamAPI_ISteamFriends_GetFriendSteamLevel;
PFN_SteamAPI_ISteamFriends_GetPlayerNickname SteamAPI_ISteamFriends_GetPlayerNickname;
PFN_SteamAPI_ISteamFriends_GetFriendsGroupCount SteamAPI_ISteamFriends_GetFriendsGroupCount;
PFN_SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex;
PFN_SteamAPI_ISteamFriends_GetFriendsGroupName SteamAPI_ISteamFriends_GetFriendsGroupName;
PFN_SteamAPI_ISteamFriends_GetFriendsGroupMembersCount SteamAPI_ISteamFriends_GetFriendsGroupMembersCount;
PFN_SteamAPI_ISteamFriends_GetFriendsGroupMembersList SteamAPI_ISteamFriends_GetFriendsGroupMembersList;
PFN_SteamAPI_ISteamFriends_HasFriend SteamAPI_ISteamFriends_HasFriend;
PFN_SteamAPI_ISteamFriends_GetClanCount SteamAPI_ISteamFriends_GetClanCount;
PFN_SteamAPI_ISteamFriends_GetClanByIndex SteamAPI_ISteamFriends_GetClanByIndex;
PFN_SteamAPI_ISteamFriends_GetClanName SteamAPI_ISteamFriends_GetClanName;
PFN_SteamAPI_ISteamFriends_GetClanTag SteamAPI_ISteamFriends_GetClanTag;
PFN_SteamAPI_ISteamFriends_GetClanActivityCounts SteamAPI_ISteamFriends_GetClanActivityCounts;
PFN_SteamAPI_ISteamFriends_DownloadClanActivityCounts SteamAPI_ISteamFriends_DownloadClanActivityCounts;
PFN_SteamAPI_ISteamFriends_GetFriendCountFromSource SteamAPI_ISteamFriends_GetFriendCountFromSource;
PFN_SteamAPI_ISteamFriends_GetFriendFromSourceByIndex SteamAPI_ISteamFriends_GetFriendFromSourceByIndex;
PFN_SteamAPI_ISteamFriends_IsUserInSource SteamAPI_ISteamFriends_IsUserInSource;
PFN_SteamAPI_ISteamFriends_SetInGameVoiceSpeaking SteamAPI_ISteamFriends_SetInGameVoiceSpeaking;
PFN_SteamAPI_ISteamFriends_ActivateGameOverlay SteamAPI_ISteamFriends_ActivateGameOverlay;
PFN_SteamAPI_ISteamFriends_ActivateGameOverlayToUser SteamAPI_ISteamFriends_ActivateGameOverlayToUser;
PFN_SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage;
PFN_SteamAPI_ISteamFriends_ActivateGameOverlayToStore SteamAPI_ISteamFriends_ActivateGameOverlayToStore;
PFN_SteamAPI_ISteamFriends_SetPlayedWith SteamAPI_ISteamFriends_SetPlayedWith;
PFN_SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog;
PFN_SteamAPI_ISteamFriends_GetSmallFriendAvatar SteamAPI_ISteamFriends_GetSmallFriendAvatar;
PFN_SteamAPI_ISteamFriends_GetMediumFriendAvatar SteamAPI_ISteamFriends_GetMediumFriendAvatar;
PFN_SteamAPI_ISteamFriends_GetLargeFriendAvatar SteamAPI_ISteamFriends_GetLargeFriendAvatar;
PFN_SteamAPI_ISteamFriends_RequestUserInformation SteamAPI_ISteamFriends_RequestUserInformation;
PFN_SteamAPI_ISteamFriends_RequestClanOfficerList SteamAPI_ISteamFriends_RequestClanOfficerList;
PFN_SteamAPI_ISteamFriends_GetClanOwner SteamAPI_ISteamFriends_GetClanOwner;
PFN_SteamAPI_ISteamFriends_GetClanOfficerCount SteamAPI_ISteamFriends_GetClanOfficerCount;
PFN_SteamAPI_ISteamFriends_GetClanOfficerByIndex SteamAPI_ISteamFriends_GetClanOfficerByIndex;
PFN_SteamAPI_ISteamFriends_GetUserRestrictions SteamAPI_ISteamFriends_GetUserRestrictions;
PFN_SteamAPI_ISteamFriends_SetRichPresence SteamAPI_ISteamFriends_SetRichPresence;
PFN_SteamAPI_ISteamFriends_ClearRichPresence SteamAPI_ISteamFriends_ClearRichPresence;
PFN_SteamAPI_ISteamFriends_GetFriendRichPresence SteamAPI_ISteamFriends_GetFriendRichPresence;
PFN_SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount;
PFN_SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex;
PFN_SteamAPI_ISteamFriends_RequestFriendRichPresence SteamAPI_ISteamFriends_RequestFriendRichPresence;
PFN_SteamAPI_ISteamFriends_InviteUserToGame SteamAPI_ISteamFriends_InviteUserToGame;
PFN_SteamAPI_ISteamFriends_GetCoplayFriendCount SteamAPI_ISteamFriends_GetCoplayFriendCount;
PFN_SteamAPI_ISteamFriends_GetCoplayFriend SteamAPI_ISteamFriends_GetCoplayFriend;
PFN_SteamAPI_ISteamFriends_GetFriendCoplayTime SteamAPI_ISteamFriends_GetFriendCoplayTime;
PFN_SteamAPI_ISteamFriends_GetFriendCoplayGame SteamAPI_ISteamFriends_GetFriendCoplayGame;
PFN_SteamAPI_ISteamFriends_JoinClanChatRoom SteamAPI_ISteamFriends_JoinClanChatRoom;
PFN_SteamAPI_ISteamFriends_LeaveClanChatRoom SteamAPI_ISteamFriends_LeaveClanChatRoom;
PFN_SteamAPI_ISteamFriends_GetClanChatMemberCount SteamAPI_ISteamFriends_GetClanChatMemberCount;
PFN_SteamAPI_ISteamFriends_GetChatMemberByIndex SteamAPI_ISteamFriends_GetChatMemberByIndex;
PFN_SteamAPI_ISteamFriends_SendClanChatMessage SteamAPI_ISteamFriends_SendClanChatMessage;
PFN_SteamAPI_ISteamFriends_GetClanChatMessage SteamAPI_ISteamFriends_GetClanChatMessage;
PFN_SteamAPI_ISteamFriends_IsClanChatAdmin SteamAPI_ISteamFriends_IsClanChatAdmin;
PFN_SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam;
PFN_SteamAPI_ISteamFriends_OpenClanChatWindowInSteam SteamAPI_ISteamFriends_OpenClanChatWindowInSteam;
PFN_SteamAPI_ISteamFriends_CloseClanChatWindowInSteam SteamAPI_ISteamFriends_CloseClanChatWindowInSteam;
PFN_SteamAPI_ISteamFriends_SetListenForFriendsMessages SteamAPI_ISteamFriends_SetListenForFriendsMessages;
PFN_SteamAPI_ISteamFriends_ReplyToFriendMessage SteamAPI_ISteamFriends_ReplyToFriendMessage;
PFN_SteamAPI_ISteamFriends_GetFriendMessage SteamAPI_ISteamFriends_GetFriendMessage;
PFN_SteamAPI_ISteamFriends_GetFollowerCount SteamAPI_ISteamFriends_GetFollowerCount;
PFN_SteamAPI_ISteamFriends_IsFollowing SteamAPI_ISteamFriends_IsFollowing;
PFN_SteamAPI_ISteamFriends_EnumerateFollowingList SteamAPI_ISteamFriends_EnumerateFollowingList;
PFN_SteamAPI_ISteamFriends_IsClanPublic SteamAPI_ISteamFriends_IsClanPublic;
PFN_SteamAPI_ISteamFriends_IsClanOfficialGameGroup SteamAPI_ISteamFriends_IsClanOfficialGameGroup;
PFN_SteamAPI_ISteamUtils_GetSecondsSinceAppActive SteamAPI_ISteamUtils_GetSecondsSinceAppActive;
PFN_SteamAPI_ISteamUtils_GetSecondsSinceComputerActive SteamAPI_ISteamUtils_GetSecondsSinceComputerActive;
PFN_SteamAPI_ISteamUtils_GetConnectedUniverse SteamAPI_ISteamUtils_GetConnectedUniverse;
PFN_SteamAPI_ISteamUtils_GetServerRealTime SteamAPI_ISteamUtils_GetServerRealTime;
PFN_SteamAPI_ISteamUtils_GetIPCountry SteamAPI_ISteamUtils_GetIPCountry;
PFN_SteamAPI_ISteamUtils_GetImageSize SteamAPI_ISteamUtils_GetImageSize;
PFN_SteamAPI_ISteamUtils_GetImageRGBA SteamAPI_ISteamUtils_GetImageRGBA;
PFN_SteamAPI_ISteamUtils_GetCSERIPPort SteamAPI_ISteamUtils_GetCSERIPPort;
PFN_SteamAPI_ISteamUtils_GetCurrentBatteryPower SteamAPI_ISteamUtils_GetCurrentBatteryPower;
PFN_SteamAPI_ISteamUtils_GetAppID SteamAPI_ISteamUtils_GetAppID;
PFN_SteamAPI_ISteamUtils_SetOverlayNotificationPosition SteamAPI_ISteamUtils_SetOverlayNotificationPosition;
PFN_SteamAPI_ISteamUtils_IsAPICallCompleted SteamAPI_ISteamUtils_IsAPICallCompleted;
PFN_SteamAPI_ISteamUtils_GetAPICallFailureReason SteamAPI_ISteamUtils_GetAPICallFailureReason;
PFN_SteamAPI_ISteamUtils_GetAPICallResult SteamAPI_ISteamUtils_GetAPICallResult;
PFN_SteamAPI_ISteamUtils_GetIPCCallCount SteamAPI_ISteamUtils_GetIPCCallCount;
PFN_SteamAPI_ISteamUtils_SetWarningMessageHook SteamAPI_ISteamUtils_SetWarningMessageHook;
PFN_SteamAPI_ISteamUtils_IsOverlayEnabled SteamAPI_ISteamUtils_IsOverlayEnabled;
PFN_SteamAPI_ISteamUtils_BOverlayNeedsPresent SteamAPI_ISteamUtils_BOverlayNeedsPresent;
PFN_SteamAPI_ISteamUtils_CheckFileSignature SteamAPI_ISteamUtils_CheckFileSignature;
PFN_SteamAPI_ISteamUtils_ShowGamepadTextInput SteamAPI_ISteamUtils_ShowGamepadTextInput;
PFN_SteamAPI_ISteamUtils_GetEnteredGamepadTextLength SteamAPI_ISteamUtils_GetEnteredGamepadTextLength;
PFN_SteamAPI_ISteamUtils_GetEnteredGamepadTextInput SteamAPI_ISteamUtils_GetEnteredGamepadTextInput;
PFN_SteamAPI_ISteamUtils_GetSteamUILanguage SteamAPI_ISteamUtils_GetSteamUILanguage;
PFN_SteamAPI_ISteamUtils_IsSteamRunningInVR SteamAPI_ISteamUtils_IsSteamRunningInVR;
PFN_SteamAPI_ISteamUtils_SetOverlayNotificationInset SteamAPI_ISteamUtils_SetOverlayNotificationInset;
PFN_SteamAPI_ISteamUtils_IsSteamInBigPictureMode SteamAPI_ISteamUtils_IsSteamInBigPictureMode;
PFN_SteamAPI_ISteamUtils_StartVRDashboard SteamAPI_ISteamUtils_StartVRDashboard;
PFN_SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled;
PFN_SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled;
PFN_SteamAPI_ISteamMatchmaking_GetFavoriteGameCount SteamAPI_ISteamMatchmaking_GetFavoriteGameCount;
PFN_SteamAPI_ISteamMatchmaking_GetFavoriteGame SteamAPI_ISteamMatchmaking_GetFavoriteGame;
PFN_SteamAPI_ISteamMatchmaking_AddFavoriteGame SteamAPI_ISteamMatchmaking_AddFavoriteGame;
PFN_SteamAPI_ISteamMatchmaking_RemoveFavoriteGame SteamAPI_ISteamMatchmaking_RemoveFavoriteGame;
PFN_SteamAPI_ISteamMatchmaking_RequestLobbyList SteamAPI_ISteamMatchmaking_RequestLobbyList;
PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter;
PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter;
PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter;
PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable;
PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter;
PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter;
PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyByIndex SteamAPI_ISteamMatchmaking_GetLobbyByIndex;
PFN_SteamAPI_ISteamMatchmaking_CreateLobby SteamAPI_ISteamMatchmaking_CreateLobby;
PFN_SteamAPI_ISteamMatchmaking_JoinLobby SteamAPI_ISteamMatchmaking_JoinLobby;
PFN_SteamAPI_ISteamMatchmaking_LeaveLobby SteamAPI_ISteamMatchmaking_LeaveLobby;
PFN_SteamAPI_ISteamMatchmaking_InviteUserToLobby SteamAPI_ISteamMatchmaking_InviteUserToLobby;
PFN_SteamAPI_ISteamMatchmaking_GetNumLobbyMembers SteamAPI_ISteamMatchmaking_GetNumLobbyMembers;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyData SteamAPI_ISteamMatchmaking_GetLobbyData;
PFN_SteamAPI_ISteamMatchmaking_SetLobbyData SteamAPI_ISteamMatchmaking_SetLobbyData;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyDataCount SteamAPI_ISteamMatchmaking_GetLobbyDataCount;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex;
PFN_SteamAPI_ISteamMatchmaking_DeleteLobbyData SteamAPI_ISteamMatchmaking_DeleteLobbyData;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyMemberData SteamAPI_ISteamMatchmaking_GetLobbyMemberData;
PFN_SteamAPI_ISteamMatchmaking_SetLobbyMemberData SteamAPI_ISteamMatchmaking_SetLobbyMemberData;
PFN_SteamAPI_ISteamMatchmaking_SendLobbyChatMsg SteamAPI_ISteamMatchmaking_SendLobbyChatMsg;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyChatEntry SteamAPI_ISteamMatchmaking_GetLobbyChatEntry;
PFN_SteamAPI_ISteamMatchmaking_RequestLobbyData SteamAPI_ISteamMatchmaking_RequestLobbyData;
PFN_SteamAPI_ISteamMatchmaking_SetLobbyGameServer SteamAPI_ISteamMatchmaking_SetLobbyGameServer;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyGameServer SteamAPI_ISteamMatchmaking_GetLobbyGameServer;
PFN_SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit;
PFN_SteamAPI_ISteamMatchmaking_SetLobbyType SteamAPI_ISteamMatchmaking_SetLobbyType;
PFN_SteamAPI_ISteamMatchmaking_SetLobbyJoinable SteamAPI_ISteamMatchmaking_SetLobbyJoinable;
PFN_SteamAPI_ISteamMatchmaking_GetLobbyOwner SteamAPI_ISteamMatchmaking_GetLobbyOwner;
PFN_SteamAPI_ISteamMatchmaking_SetLobbyOwner SteamAPI_ISteamMatchmaking_SetLobbyOwner;
PFN_SteamAPI_ISteamMatchmaking_SetLinkedLobby SteamAPI_ISteamMatchmaking_SetLinkedLobby;
PFN_SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded;
PFN_SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond;
PFN_SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete;
PFN_SteamAPI_ISteamMatchmakingPingResponse_ServerResponded SteamAPI_ISteamMatchmakingPingResponse_ServerResponded;
PFN_SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond;
PFN_SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList;
PFN_SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond;
PFN_SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete;
PFN_SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded;
PFN_SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond;
PFN_SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete;
PFN_SteamAPI_ISteamMatchmakingServers_RequestInternetServerList SteamAPI_ISteamMatchmakingServers_RequestInternetServerList;
PFN_SteamAPI_ISteamMatchmakingServers_RequestLANServerList SteamAPI_ISteamMatchmakingServers_RequestLANServerList;
PFN_SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList;
PFN_SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList;
PFN_SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList;
PFN_SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList;
PFN_SteamAPI_ISteamMatchmakingServers_ReleaseRequest SteamAPI_ISteamMatchmakingServers_ReleaseRequest;
PFN_SteamAPI_ISteamMatchmakingServers_GetServerDetails SteamAPI_ISteamMatchmakingServers_GetServerDetails;
PFN_SteamAPI_ISteamMatchmakingServers_CancelQuery SteamAPI_ISteamMatchmakingServers_CancelQuery;
PFN_SteamAPI_ISteamMatchmakingServers_RefreshQuery SteamAPI_ISteamMatchmakingServers_RefreshQuery;
PFN_SteamAPI_ISteamMatchmakingServers_IsRefreshing SteamAPI_ISteamMatchmakingServers_IsRefreshing;
PFN_SteamAPI_ISteamMatchmakingServers_GetServerCount SteamAPI_ISteamMatchmakingServers_GetServerCount;
PFN_SteamAPI_ISteamMatchmakingServers_RefreshServer SteamAPI_ISteamMatchmakingServers_RefreshServer;
PFN_SteamAPI_ISteamMatchmakingServers_PingServer SteamAPI_ISteamMatchmakingServers_PingServer;
PFN_SteamAPI_ISteamMatchmakingServers_PlayerDetails SteamAPI_ISteamMatchmakingServers_PlayerDetails;
PFN_SteamAPI_ISteamMatchmakingServers_ServerRules SteamAPI_ISteamMatchmakingServers_ServerRules;
PFN_SteamAPI_ISteamMatchmakingServers_CancelServerQuery SteamAPI_ISteamMatchmakingServers_CancelServerQuery;
PFN_SteamAPI_ISteamRemoteStorage_FileWrite SteamAPI_ISteamRemoteStorage_FileWrite;
PFN_SteamAPI_ISteamRemoteStorage_FileRead SteamAPI_ISteamRemoteStorage_FileRead;
PFN_SteamAPI_ISteamRemoteStorage_FileWriteAsync SteamAPI_ISteamRemoteStorage_FileWriteAsync;
PFN_SteamAPI_ISteamRemoteStorage_FileReadAsync SteamAPI_ISteamRemoteStorage_FileReadAsync;
PFN_SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete;
PFN_SteamAPI_ISteamRemoteStorage_FileForget SteamAPI_ISteamRemoteStorage_FileForget;
PFN_SteamAPI_ISteamRemoteStorage_FileDelete SteamAPI_ISteamRemoteStorage_FileDelete;
PFN_SteamAPI_ISteamRemoteStorage_FileShare SteamAPI_ISteamRemoteStorage_FileShare;
PFN_SteamAPI_ISteamRemoteStorage_SetSyncPlatforms SteamAPI_ISteamRemoteStorage_SetSyncPlatforms;
PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen;
PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk;
PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamClose SteamAPI_ISteamRemoteStorage_FileWriteStreamClose;
PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel;
PFN_SteamAPI_ISteamRemoteStorage_FileExists SteamAPI_ISteamRemoteStorage_FileExists;
PFN_SteamAPI_ISteamRemoteStorage_FilePersisted SteamAPI_ISteamRemoteStorage_FilePersisted;
PFN_SteamAPI_ISteamRemoteStorage_GetFileSize SteamAPI_ISteamRemoteStorage_GetFileSize;
PFN_SteamAPI_ISteamRemoteStorage_GetFileTimestamp SteamAPI_ISteamRemoteStorage_GetFileTimestamp;
PFN_SteamAPI_ISteamRemoteStorage_GetSyncPlatforms SteamAPI_ISteamRemoteStorage_GetSyncPlatforms;
PFN_SteamAPI_ISteamRemoteStorage_GetFileCount SteamAPI_ISteamRemoteStorage_GetFileCount;
PFN_SteamAPI_ISteamRemoteStorage_GetFileNameAndSize SteamAPI_ISteamRemoteStorage_GetFileNameAndSize;
PFN_SteamAPI_ISteamRemoteStorage_GetQuota SteamAPI_ISteamRemoteStorage_GetQuota;
PFN_SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount;
PFN_SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp;
PFN_SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp;
PFN_SteamAPI_ISteamRemoteStorage_UGCDownload SteamAPI_ISteamRemoteStorage_UGCDownload;
PFN_SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress;
PFN_SteamAPI_ISteamRemoteStorage_GetUGCDetails SteamAPI_ISteamRemoteStorage_GetUGCDetails;
PFN_SteamAPI_ISteamRemoteStorage_UGCRead SteamAPI_ISteamRemoteStorage_UGCRead;
PFN_SteamAPI_ISteamRemoteStorage_GetCachedUGCCount SteamAPI_ISteamRemoteStorage_GetCachedUGCCount;
PFN_SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle;
PFN_SteamAPI_ISteamRemoteStorage_PublishWorkshopFile SteamAPI_ISteamRemoteStorage_PublishWorkshopFile;
PFN_SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest;
PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile;
PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile;
PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle;
PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription;
PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility;
PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags;
PFN_SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate;
PFN_SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails;
PFN_SteamAPI_ISteamRemoteStorage_DeletePublishedFile SteamAPI_ISteamRemoteStorage_DeletePublishedFile;
PFN_SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles;
PFN_SteamAPI_ISteamRemoteStorage_SubscribePublishedFile SteamAPI_ISteamRemoteStorage_SubscribePublishedFile;
PFN_SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles;
PFN_SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile;
PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription;
PFN_SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails;
PFN_SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote;
PFN_SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails;
PFN_SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles;
PFN_SteamAPI_ISteamRemoteStorage_PublishVideo SteamAPI_ISteamRemoteStorage_PublishVideo;
PFN_SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction;
PFN_SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction;
PFN_SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles;
PFN_SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation;
PFN_SteamAPI_ISteamUserStats_RequestCurrentStats SteamAPI_ISteamUserStats_RequestCurrentStats;
PFN_SteamAPI_ISteamUserStats_GetStat SteamAPI_ISteamUserStats_GetStat;
PFN_SteamAPI_ISteamUserStats_GetStat0 SteamAPI_ISteamUserStats_GetStat0;
PFN_SteamAPI_ISteamUserStats_SetStat SteamAPI_ISteamUserStats_SetStat;
PFN_SteamAPI_ISteamUserStats_SetStat0 SteamAPI_ISteamUserStats_SetStat0;
PFN_SteamAPI_ISteamUserStats_UpdateAvgRateStat SteamAPI_ISteamUserStats_UpdateAvgRateStat;
PFN_SteamAPI_ISteamUserStats_GetAchievement SteamAPI_ISteamUserStats_GetAchievement;
PFN_SteamAPI_ISteamUserStats_SetAchievement SteamAPI_ISteamUserStats_SetAchievement;
PFN_SteamAPI_ISteamUserStats_ClearAchievement SteamAPI_ISteamUserStats_ClearAchievement;
PFN_SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime;
PFN_SteamAPI_ISteamUserStats_StoreStats SteamAPI_ISteamUserStats_StoreStats;
PFN_SteamAPI_ISteamUserStats_GetAchievementIcon SteamAPI_ISteamUserStats_GetAchievementIcon;
PFN_SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute;
PFN_SteamAPI_ISteamUserStats_IndicateAchievementProgress SteamAPI_ISteamUserStats_IndicateAchievementProgress;
PFN_SteamAPI_ISteamUserStats_GetNumAchievements SteamAPI_ISteamUserStats_GetNumAchievements;
PFN_SteamAPI_ISteamUserStats_GetAchievementName SteamAPI_ISteamUserStats_GetAchievementName;
PFN_SteamAPI_ISteamUserStats_RequestUserStats SteamAPI_ISteamUserStats_RequestUserStats;
PFN_SteamAPI_ISteamUserStats_GetUserStat SteamAPI_ISteamUserStats_GetUserStat;
PFN_SteamAPI_ISteamUserStats_GetUserStat0 SteamAPI_ISteamUserStats_GetUserStat0;
PFN_SteamAPI_ISteamUserStats_GetUserAchievement SteamAPI_ISteamUserStats_GetUserAchievement;
PFN_SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime;
PFN_SteamAPI_ISteamUserStats_ResetAllStats SteamAPI_ISteamUserStats_ResetAllStats;
PFN_SteamAPI_ISteamUserStats_FindOrCreateLeaderboard SteamAPI_ISteamUserStats_FindOrCreateLeaderboard;
PFN_SteamAPI_ISteamUserStats_FindLeaderboard SteamAPI_ISteamUserStats_FindLeaderboard;
PFN_SteamAPI_ISteamUserStats_GetLeaderboardName SteamAPI_ISteamUserStats_GetLeaderboardName;
PFN_SteamAPI_ISteamUserStats_GetLeaderboardEntryCount SteamAPI_ISteamUserStats_GetLeaderboardEntryCount;
PFN_SteamAPI_ISteamUserStats_GetLeaderboardSortMethod SteamAPI_ISteamUserStats_GetLeaderboardSortMethod;
PFN_SteamAPI_ISteamUserStats_GetLeaderboardDisplayType SteamAPI_ISteamUserStats_GetLeaderboardDisplayType;
PFN_SteamAPI_ISteamUserStats_DownloadLeaderboardEntries SteamAPI_ISteamUserStats_DownloadLeaderboardEntries;
PFN_SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers;
PFN_SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry;
PFN_SteamAPI_ISteamUserStats_UploadLeaderboardScore SteamAPI_ISteamUserStats_UploadLeaderboardScore;
PFN_SteamAPI_ISteamUserStats_AttachLeaderboardUGC SteamAPI_ISteamUserStats_AttachLeaderboardUGC;
PFN_SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers;
PFN_SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages;
PFN_SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo;
PFN_SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo;
PFN_SteamAPI_ISteamUserStats_GetAchievementAchievedPercent SteamAPI_ISteamUserStats_GetAchievementAchievedPercent;
PFN_SteamAPI_ISteamUserStats_RequestGlobalStats SteamAPI_ISteamUserStats_RequestGlobalStats;
PFN_SteamAPI_ISteamUserStats_GetGlobalStat SteamAPI_ISteamUserStats_GetGlobalStat;
PFN_SteamAPI_ISteamUserStats_GetGlobalStat0 SteamAPI_ISteamUserStats_GetGlobalStat0;
PFN_SteamAPI_ISteamUserStats_GetGlobalStatHistory SteamAPI_ISteamUserStats_GetGlobalStatHistory;
PFN_SteamAPI_ISteamUserStats_GetGlobalStatHistory0 SteamAPI_ISteamUserStats_GetGlobalStatHistory0;
PFN_SteamAPI_ISteamApps_BIsSubscribed SteamAPI_ISteamApps_BIsSubscribed;
PFN_SteamAPI_ISteamApps_BIsLowViolence SteamAPI_ISteamApps_BIsLowViolence;
PFN_SteamAPI_ISteamApps_BIsCybercafe SteamAPI_ISteamApps_BIsCybercafe;
PFN_SteamAPI_ISteamApps_BIsVACBanned SteamAPI_ISteamApps_BIsVACBanned;
PFN_SteamAPI_ISteamApps_GetCurrentGameLanguage SteamAPI_ISteamApps_GetCurrentGameLanguage;
PFN_SteamAPI_ISteamApps_GetAvailableGameLanguages SteamAPI_ISteamApps_GetAvailableGameLanguages;
PFN_SteamAPI_ISteamApps_BIsSubscribedApp SteamAPI_ISteamApps_BIsSubscribedApp;
PFN_SteamAPI_ISteamApps_BIsDlcInstalled SteamAPI_ISteamApps_BIsDlcInstalled;
PFN_SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime;
PFN_SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend;
PFN_SteamAPI_ISteamApps_GetDLCCount SteamAPI_ISteamApps_GetDLCCount;
PFN_SteamAPI_ISteamApps_BGetDLCDataByIndex SteamAPI_ISteamApps_BGetDLCDataByIndex;
PFN_SteamAPI_ISteamApps_InstallDLC SteamAPI_ISteamApps_InstallDLC;
PFN_SteamAPI_ISteamApps_UninstallDLC SteamAPI_ISteamApps_UninstallDLC;
PFN_SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey;
PFN_SteamAPI_ISteamApps_GetCurrentBetaName SteamAPI_ISteamApps_GetCurrentBetaName;
PFN_SteamAPI_ISteamApps_MarkContentCorrupt SteamAPI_ISteamApps_MarkContentCorrupt;
PFN_SteamAPI_ISteamApps_GetInstalledDepots SteamAPI_ISteamApps_GetInstalledDepots;
PFN_SteamAPI_ISteamApps_GetAppInstallDir SteamAPI_ISteamApps_GetAppInstallDir;
PFN_SteamAPI_ISteamApps_BIsAppInstalled SteamAPI_ISteamApps_BIsAppInstalled;
PFN_SteamAPI_ISteamApps_GetAppOwner SteamAPI_ISteamApps_GetAppOwner;
PFN_SteamAPI_ISteamApps_GetLaunchQueryParam SteamAPI_ISteamApps_GetLaunchQueryParam;
PFN_SteamAPI_ISteamApps_GetDlcDownloadProgress SteamAPI_ISteamApps_GetDlcDownloadProgress;
PFN_SteamAPI_ISteamApps_GetAppBuildId SteamAPI_ISteamApps_GetAppBuildId;
PFN_SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys;
PFN_SteamAPI_ISteamApps_GetFileDetails SteamAPI_ISteamApps_GetFileDetails;
PFN_SteamAPI_ISteamNetworking_SendP2PPacket SteamAPI_ISteamNetworking_SendP2PPacket;
PFN_SteamAPI_ISteamNetworking_IsP2PPacketAvailable SteamAPI_ISteamNetworking_IsP2PPacketAvailable;
PFN_SteamAPI_ISteamNetworking_ReadP2PPacket SteamAPI_ISteamNetworking_ReadP2PPacket;
PFN_SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser;
PFN_SteamAPI_ISteamNetworking_CloseP2PSessionWithUser SteamAPI_ISteamNetworking_CloseP2PSessionWithUser;
PFN_SteamAPI_ISteamNetworking_CloseP2PChannelWithUser SteamAPI_ISteamNetworking_CloseP2PChannelWithUser;
PFN_SteamAPI_ISteamNetworking_GetP2PSessionState SteamAPI_ISteamNetworking_GetP2PSessionState;
PFN_SteamAPI_ISteamNetworking_AllowP2PPacketRelay SteamAPI_ISteamNetworking_AllowP2PPacketRelay;
PFN_SteamAPI_ISteamNetworking_CreateListenSocket SteamAPI_ISteamNetworking_CreateListenSocket;
PFN_SteamAPI_ISteamNetworking_CreateP2PConnectionSocket SteamAPI_ISteamNetworking_CreateP2PConnectionSocket;
PFN_SteamAPI_ISteamNetworking_CreateConnectionSocket SteamAPI_ISteamNetworking_CreateConnectionSocket;
PFN_SteamAPI_ISteamNetworking_DestroySocket SteamAPI_ISteamNetworking_DestroySocket;
PFN_SteamAPI_ISteamNetworking_DestroyListenSocket SteamAPI_ISteamNetworking_DestroyListenSocket;
PFN_SteamAPI_ISteamNetworking_SendDataOnSocket SteamAPI_ISteamNetworking_SendDataOnSocket;
PFN_SteamAPI_ISteamNetworking_IsDataAvailableOnSocket SteamAPI_ISteamNetworking_IsDataAvailableOnSocket;
PFN_SteamAPI_ISteamNetworking_RetrieveDataFromSocket SteamAPI_ISteamNetworking_RetrieveDataFromSocket;
PFN_SteamAPI_ISteamNetworking_IsDataAvailable SteamAPI_ISteamNetworking_IsDataAvailable;
PFN_SteamAPI_ISteamNetworking_RetrieveData SteamAPI_ISteamNetworking_RetrieveData;
PFN_SteamAPI_ISteamNetworking_GetSocketInfo SteamAPI_ISteamNetworking_GetSocketInfo;
PFN_SteamAPI_ISteamNetworking_GetListenSocketInfo SteamAPI_ISteamNetworking_GetListenSocketInfo;
PFN_SteamAPI_ISteamNetworking_GetSocketConnectionType SteamAPI_ISteamNetworking_GetSocketConnectionType;
PFN_SteamAPI_ISteamNetworking_GetMaxPacketSize SteamAPI_ISteamNetworking_GetMaxPacketSize;
PFN_SteamAPI_ISteamScreenshots_WriteScreenshot SteamAPI_ISteamScreenshots_WriteScreenshot;
PFN_SteamAPI_ISteamScreenshots_AddScreenshotToLibrary SteamAPI_ISteamScreenshots_AddScreenshotToLibrary;
PFN_SteamAPI_ISteamScreenshots_TriggerScreenshot SteamAPI_ISteamScreenshots_TriggerScreenshot;
PFN_SteamAPI_ISteamScreenshots_HookScreenshots SteamAPI_ISteamScreenshots_HookScreenshots;
PFN_SteamAPI_ISteamScreenshots_SetLocation SteamAPI_ISteamScreenshots_SetLocation;
PFN_SteamAPI_ISteamScreenshots_TagUser SteamAPI_ISteamScreenshots_TagUser;
PFN_SteamAPI_ISteamScreenshots_TagPublishedFile SteamAPI_ISteamScreenshots_TagPublishedFile;
PFN_SteamAPI_ISteamScreenshots_IsScreenshotsHooked SteamAPI_ISteamScreenshots_IsScreenshotsHooked;
PFN_SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary;
PFN_SteamAPI_ISteamMusic_BIsEnabled SteamAPI_ISteamMusic_BIsEnabled;
PFN_SteamAPI_ISteamMusic_BIsPlaying SteamAPI_ISteamMusic_BIsPlaying;
PFN_SteamAPI_ISteamMusic_GetPlaybackStatus SteamAPI_ISteamMusic_GetPlaybackStatus;
PFN_SteamAPI_ISteamMusic_Play SteamAPI_ISteamMusic_Play;
PFN_SteamAPI_ISteamMusic_Pause SteamAPI_ISteamMusic_Pause;
PFN_SteamAPI_ISteamMusic_PlayPrevious SteamAPI_ISteamMusic_PlayPrevious;
PFN_SteamAPI_ISteamMusic_PlayNext SteamAPI_ISteamMusic_PlayNext;
PFN_SteamAPI_ISteamMusic_SetVolume SteamAPI_ISteamMusic_SetVolume;
PFN_SteamAPI_ISteamMusic_GetVolume SteamAPI_ISteamMusic_GetVolume;
PFN_SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote;
PFN_SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote;
PFN_SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote;
PFN_SteamAPI_ISteamMusicRemote_BActivationSuccess SteamAPI_ISteamMusicRemote_BActivationSuccess;
PFN_SteamAPI_ISteamMusicRemote_SetDisplayName SteamAPI_ISteamMusicRemote_SetDisplayName;
PFN_SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64 SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64;
PFN_SteamAPI_ISteamMusicRemote_EnablePlayPrevious SteamAPI_ISteamMusicRemote_EnablePlayPrevious;
PFN_SteamAPI_ISteamMusicRemote_EnablePlayNext SteamAPI_ISteamMusicRemote_EnablePlayNext;
PFN_SteamAPI_ISteamMusicRemote_EnableShuffled SteamAPI_ISteamMusicRemote_EnableShuffled;
PFN_SteamAPI_ISteamMusicRemote_EnableLooped SteamAPI_ISteamMusicRemote_EnableLooped;
PFN_SteamAPI_ISteamMusicRemote_EnableQueue SteamAPI_ISteamMusicRemote_EnableQueue;
PFN_SteamAPI_ISteamMusicRemote_EnablePlaylists SteamAPI_ISteamMusicRemote_EnablePlaylists;
PFN_SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus;
PFN_SteamAPI_ISteamMusicRemote_UpdateShuffled SteamAPI_ISteamMusicRemote_UpdateShuffled;
PFN_SteamAPI_ISteamMusicRemote_UpdateLooped SteamAPI_ISteamMusicRemote_UpdateLooped;
PFN_SteamAPI_ISteamMusicRemote_UpdateVolume SteamAPI_ISteamMusicRemote_UpdateVolume;
PFN_SteamAPI_ISteamMusicRemote_CurrentEntryWillChange SteamAPI_ISteamMusicRemote_CurrentEntryWillChange;
PFN_SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable;
PFN_SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText;
PFN_SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds;
PFN_SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt;
PFN_SteamAPI_ISteamMusicRemote_CurrentEntryDidChange SteamAPI_ISteamMusicRemote_CurrentEntryDidChange;
PFN_SteamAPI_ISteamMusicRemote_QueueWillChange SteamAPI_ISteamMusicRemote_QueueWillChange;
PFN_SteamAPI_ISteamMusicRemote_ResetQueueEntries SteamAPI_ISteamMusicRemote_ResetQueueEntries;
PFN_SteamAPI_ISteamMusicRemote_SetQueueEntry SteamAPI_ISteamMusicRemote_SetQueueEntry;
PFN_SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry;
PFN_SteamAPI_ISteamMusicRemote_QueueDidChange SteamAPI_ISteamMusicRemote_QueueDidChange;
PFN_SteamAPI_ISteamMusicRemote_PlaylistWillChange SteamAPI_ISteamMusicRemote_PlaylistWillChange;
PFN_SteamAPI_ISteamMusicRemote_ResetPlaylistEntries SteamAPI_ISteamMusicRemote_ResetPlaylistEntries;
PFN_SteamAPI_ISteamMusicRemote_SetPlaylistEntry SteamAPI_ISteamMusicRemote_SetPlaylistEntry;
PFN_SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry;
PFN_SteamAPI_ISteamMusicRemote_PlaylistDidChange SteamAPI_ISteamMusicRemote_PlaylistDidChange;
PFN_SteamAPI_ISteamHTTP_CreateHTTPRequest SteamAPI_ISteamHTTP_CreateHTTPRequest;
PFN_SteamAPI_ISteamHTTP_SetHTTPRequestContextValue SteamAPI_ISteamHTTP_SetHTTPRequestContextValue;
PFN_SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout;
PFN_SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue;
PFN_SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter;
PFN_SteamAPI_ISteamHTTP_SendHTTPRequest SteamAPI_ISteamHTTP_SendHTTPRequest;
PFN_SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse;
PFN_SteamAPI_ISteamHTTP_DeferHTTPRequest SteamAPI_ISteamHTTP_DeferHTTPRequest;
PFN_SteamAPI_ISteamHTTP_PrioritizeHTTPRequest SteamAPI_ISteamHTTP_PrioritizeHTTPRequest;
PFN_SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize;
PFN_SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue;
PFN_SteamAPI_ISteamHTTP_GetHTTPResponseBodySize SteamAPI_ISteamHTTP_GetHTTPResponseBodySize;
PFN_SteamAPI_ISteamHTTP_GetHTTPResponseBodyData SteamAPI_ISteamHTTP_GetHTTPResponseBodyData;
PFN_SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData;
PFN_SteamAPI_ISteamHTTP_ReleaseHTTPRequest SteamAPI_ISteamHTTP_ReleaseHTTPRequest;
PFN_SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct;
PFN_SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody;
PFN_SteamAPI_ISteamHTTP_CreateCookieContainer SteamAPI_ISteamHTTP_CreateCookieContainer;
PFN_SteamAPI_ISteamHTTP_ReleaseCookieContainer SteamAPI_ISteamHTTP_ReleaseCookieContainer;
PFN_SteamAPI_ISteamHTTP_SetCookie SteamAPI_ISteamHTTP_SetCookie;
PFN_SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer;
PFN_SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo;
PFN_SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate;
PFN_SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS;
PFN_SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut;
PFN_SteamAPI_ISteamController_Init SteamAPI_ISteamController_Init;
PFN_SteamAPI_ISteamController_Shutdown SteamAPI_ISteamController_Shutdown;
PFN_SteamAPI_ISteamController_RunFrame SteamAPI_ISteamController_RunFrame;
PFN_SteamAPI_ISteamController_GetConnectedControllers SteamAPI_ISteamController_GetConnectedControllers;
PFN_SteamAPI_ISteamController_ShowBindingPanel SteamAPI_ISteamController_ShowBindingPanel;
PFN_SteamAPI_ISteamController_GetActionSetHandle SteamAPI_ISteamController_GetActionSetHandle;
PFN_SteamAPI_ISteamController_ActivateActionSet SteamAPI_ISteamController_ActivateActionSet;
PFN_SteamAPI_ISteamController_GetCurrentActionSet SteamAPI_ISteamController_GetCurrentActionSet;
PFN_SteamAPI_ISteamController_ActivateActionSetLayer SteamAPI_ISteamController_ActivateActionSetLayer;
PFN_SteamAPI_ISteamController_DeactivateActionSetLayer SteamAPI_ISteamController_DeactivateActionSetLayer;
PFN_SteamAPI_ISteamController_DeactivateAllActionSetLayers SteamAPI_ISteamController_DeactivateAllActionSetLayers;
PFN_SteamAPI_ISteamController_GetActiveActionSetLayers SteamAPI_ISteamController_GetActiveActionSetLayers;
PFN_SteamAPI_ISteamController_GetDigitalActionHandle SteamAPI_ISteamController_GetDigitalActionHandle;
PFN_SteamAPI_ISteamController_GetDigitalActionData SteamAPI_ISteamController_GetDigitalActionData;
PFN_SteamAPI_ISteamController_GetDigitalActionOrigins SteamAPI_ISteamController_GetDigitalActionOrigins;
PFN_SteamAPI_ISteamController_GetAnalogActionHandle SteamAPI_ISteamController_GetAnalogActionHandle;
PFN_SteamAPI_ISteamController_GetAnalogActionData SteamAPI_ISteamController_GetAnalogActionData;
PFN_SteamAPI_ISteamController_GetAnalogActionOrigins SteamAPI_ISteamController_GetAnalogActionOrigins;
PFN_SteamAPI_ISteamController_StopAnalogActionMomentum SteamAPI_ISteamController_StopAnalogActionMomentum;
PFN_SteamAPI_ISteamController_TriggerHapticPulse SteamAPI_ISteamController_TriggerHapticPulse;
PFN_SteamAPI_ISteamController_TriggerRepeatedHapticPulse SteamAPI_ISteamController_TriggerRepeatedHapticPulse;
PFN_SteamAPI_ISteamController_TriggerVibration SteamAPI_ISteamController_TriggerVibration;
PFN_SteamAPI_ISteamController_SetLEDColor SteamAPI_ISteamController_SetLEDColor;
PFN_SteamAPI_ISteamController_GetGamepadIndexForController SteamAPI_ISteamController_GetGamepadIndexForController;
PFN_SteamAPI_ISteamController_GetControllerForGamepadIndex SteamAPI_ISteamController_GetControllerForGamepadIndex;
PFN_SteamAPI_ISteamController_GetMotionData SteamAPI_ISteamController_GetMotionData;
PFN_SteamAPI_ISteamController_ShowDigitalActionOrigins SteamAPI_ISteamController_ShowDigitalActionOrigins;
PFN_SteamAPI_ISteamController_ShowAnalogActionOrigins SteamAPI_ISteamController_ShowAnalogActionOrigins;
PFN_SteamAPI_ISteamController_GetStringForActionOrigin SteamAPI_ISteamController_GetStringForActionOrigin;
PFN_SteamAPI_ISteamController_GetGlyphForActionOrigin SteamAPI_ISteamController_GetGlyphForActionOrigin;
PFN_SteamAPI_ISteamController_GetInputTypeForHandle SteamAPI_ISteamController_GetInputTypeForHandle;
PFN_SteamAPI_ISteamUGC_CreateQueryUserUGCRequest SteamAPI_ISteamUGC_CreateQueryUserUGCRequest;
PFN_SteamAPI_ISteamUGC_CreateQueryAllUGCRequest SteamAPI_ISteamUGC_CreateQueryAllUGCRequest;
PFN_SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest;
PFN_SteamAPI_ISteamUGC_SendQueryUGCRequest SteamAPI_ISteamUGC_SendQueryUGCRequest;
PFN_SteamAPI_ISteamUGC_GetQueryUGCResult SteamAPI_ISteamUGC_GetQueryUGCResult;
PFN_SteamAPI_ISteamUGC_GetQueryUGCPreviewURL SteamAPI_ISteamUGC_GetQueryUGCPreviewURL;
PFN_SteamAPI_ISteamUGC_GetQueryUGCMetadata SteamAPI_ISteamUGC_GetQueryUGCMetadata;
PFN_SteamAPI_ISteamUGC_GetQueryUGCChildren SteamAPI_ISteamUGC_GetQueryUGCChildren;
PFN_SteamAPI_ISteamUGC_GetQueryUGCStatistic SteamAPI_ISteamUGC_GetQueryUGCStatistic;
PFN_SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews;
PFN_SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview;
PFN_SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags;
PFN_SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag;
PFN_SteamAPI_ISteamUGC_ReleaseQueryUGCRequest SteamAPI_ISteamUGC_ReleaseQueryUGCRequest;
PFN_SteamAPI_ISteamUGC_AddRequiredTag SteamAPI_ISteamUGC_AddRequiredTag;
PFN_SteamAPI_ISteamUGC_AddExcludedTag SteamAPI_ISteamUGC_AddExcludedTag;
PFN_SteamAPI_ISteamUGC_SetReturnOnlyIDs SteamAPI_ISteamUGC_SetReturnOnlyIDs;
PFN_SteamAPI_ISteamUGC_SetReturnKeyValueTags SteamAPI_ISteamUGC_SetReturnKeyValueTags;
PFN_SteamAPI_ISteamUGC_SetReturnLongDescription SteamAPI_ISteamUGC_SetReturnLongDescription;
PFN_SteamAPI_ISteamUGC_SetReturnMetadata SteamAPI_ISteamUGC_SetReturnMetadata;
PFN_SteamAPI_ISteamUGC_SetReturnChildren SteamAPI_ISteamUGC_SetReturnChildren;
PFN_SteamAPI_ISteamUGC_SetReturnAdditionalPreviews SteamAPI_ISteamUGC_SetReturnAdditionalPreviews;
PFN_SteamAPI_ISteamUGC_SetReturnTotalOnly SteamAPI_ISteamUGC_SetReturnTotalOnly;
PFN_SteamAPI_ISteamUGC_SetReturnPlaytimeStats SteamAPI_ISteamUGC_SetReturnPlaytimeStats;
PFN_SteamAPI_ISteamUGC_SetLanguage SteamAPI_ISteamUGC_SetLanguage;
PFN_SteamAPI_ISteamUGC_SetAllowCachedResponse SteamAPI_ISteamUGC_SetAllowCachedResponse;
PFN_SteamAPI_ISteamUGC_SetCloudFileNameFilter SteamAPI_ISteamUGC_SetCloudFileNameFilter;
PFN_SteamAPI_ISteamUGC_SetMatchAnyTag SteamAPI_ISteamUGC_SetMatchAnyTag;
PFN_SteamAPI_ISteamUGC_SetSearchText SteamAPI_ISteamUGC_SetSearchText;
PFN_SteamAPI_ISteamUGC_SetRankedByTrendDays SteamAPI_ISteamUGC_SetRankedByTrendDays;
PFN_SteamAPI_ISteamUGC_AddRequiredKeyValueTag SteamAPI_ISteamUGC_AddRequiredKeyValueTag;
PFN_SteamAPI_ISteamUGC_RequestUGCDetails SteamAPI_ISteamUGC_RequestUGCDetails;
PFN_SteamAPI_ISteamUGC_CreateItem SteamAPI_ISteamUGC_CreateItem;
PFN_SteamAPI_ISteamUGC_StartItemUpdate SteamAPI_ISteamUGC_StartItemUpdate;
PFN_SteamAPI_ISteamUGC_SetItemTitle SteamAPI_ISteamUGC_SetItemTitle;
PFN_SteamAPI_ISteamUGC_SetItemDescription SteamAPI_ISteamUGC_SetItemDescription;
PFN_SteamAPI_ISteamUGC_SetItemUpdateLanguage SteamAPI_ISteamUGC_SetItemUpdateLanguage;
PFN_SteamAPI_ISteamUGC_SetItemMetadata SteamAPI_ISteamUGC_SetItemMetadata;
PFN_SteamAPI_ISteamUGC_SetItemVisibility SteamAPI_ISteamUGC_SetItemVisibility;
PFN_SteamAPI_ISteamUGC_SetItemTags SteamAPI_ISteamUGC_SetItemTags;
PFN_SteamAPI_ISteamUGC_SetItemContent SteamAPI_ISteamUGC_SetItemContent;
PFN_SteamAPI_ISteamUGC_SetItemPreview SteamAPI_ISteamUGC_SetItemPreview;
PFN_SteamAPI_ISteamUGC_RemoveItemKeyValueTags SteamAPI_ISteamUGC_RemoveItemKeyValueTags;
PFN_SteamAPI_ISteamUGC_AddItemKeyValueTag SteamAPI_ISteamUGC_AddItemKeyValueTag;
PFN_SteamAPI_ISteamUGC_AddItemPreviewFile SteamAPI_ISteamUGC_AddItemPreviewFile;
PFN_SteamAPI_ISteamUGC_AddItemPreviewVideo SteamAPI_ISteamUGC_AddItemPreviewVideo;
PFN_SteamAPI_ISteamUGC_UpdateItemPreviewFile SteamAPI_ISteamUGC_UpdateItemPreviewFile;
PFN_SteamAPI_ISteamUGC_UpdateItemPreviewVideo SteamAPI_ISteamUGC_UpdateItemPreviewVideo;
PFN_SteamAPI_ISteamUGC_RemoveItemPreview SteamAPI_ISteamUGC_RemoveItemPreview;
PFN_SteamAPI_ISteamUGC_SubmitItemUpdate SteamAPI_ISteamUGC_SubmitItemUpdate;
PFN_SteamAPI_ISteamUGC_GetItemUpdateProgress SteamAPI_ISteamUGC_GetItemUpdateProgress;
PFN_SteamAPI_ISteamUGC_SetUserItemVote SteamAPI_ISteamUGC_SetUserItemVote;
PFN_SteamAPI_ISteamUGC_GetUserItemVote SteamAPI_ISteamUGC_GetUserItemVote;
PFN_SteamAPI_ISteamUGC_AddItemToFavorites SteamAPI_ISteamUGC_AddItemToFavorites;
PFN_SteamAPI_ISteamUGC_RemoveItemFromFavorites SteamAPI_ISteamUGC_RemoveItemFromFavorites;
PFN_SteamAPI_ISteamUGC_SubscribeItem SteamAPI_ISteamUGC_SubscribeItem;
PFN_SteamAPI_ISteamUGC_UnsubscribeItem SteamAPI_ISteamUGC_UnsubscribeItem;
PFN_SteamAPI_ISteamUGC_GetNumSubscribedItems SteamAPI_ISteamUGC_GetNumSubscribedItems;
PFN_SteamAPI_ISteamUGC_GetSubscribedItems SteamAPI_ISteamUGC_GetSubscribedItems;
PFN_SteamAPI_ISteamUGC_GetItemState SteamAPI_ISteamUGC_GetItemState;
PFN_SteamAPI_ISteamUGC_GetItemInstallInfo SteamAPI_ISteamUGC_GetItemInstallInfo;
PFN_SteamAPI_ISteamUGC_GetItemDownloadInfo SteamAPI_ISteamUGC_GetItemDownloadInfo;
PFN_SteamAPI_ISteamUGC_DownloadItem SteamAPI_ISteamUGC_DownloadItem;
PFN_SteamAPI_ISteamUGC_BInitWorkshopForGameServer SteamAPI_ISteamUGC_BInitWorkshopForGameServer;
PFN_SteamAPI_ISteamUGC_SuspendDownloads SteamAPI_ISteamUGC_SuspendDownloads;
PFN_SteamAPI_ISteamUGC_StartPlaytimeTracking SteamAPI_ISteamUGC_StartPlaytimeTracking;
PFN_SteamAPI_ISteamUGC_StopPlaytimeTracking SteamAPI_ISteamUGC_StopPlaytimeTracking;
PFN_SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems;
PFN_SteamAPI_ISteamUGC_AddDependency SteamAPI_ISteamUGC_AddDependency;
PFN_SteamAPI_ISteamUGC_RemoveDependency SteamAPI_ISteamUGC_RemoveDependency;
PFN_SteamAPI_ISteamUGC_AddAppDependency SteamAPI_ISteamUGC_AddAppDependency;
PFN_SteamAPI_ISteamUGC_RemoveAppDependency SteamAPI_ISteamUGC_RemoveAppDependency;
PFN_SteamAPI_ISteamUGC_GetAppDependencies SteamAPI_ISteamUGC_GetAppDependencies;
PFN_SteamAPI_ISteamUGC_DeleteItem SteamAPI_ISteamUGC_DeleteItem;
PFN_SteamAPI_ISteamAppList_GetNumInstalledApps SteamAPI_ISteamAppList_GetNumInstalledApps;
PFN_SteamAPI_ISteamAppList_GetInstalledApps SteamAPI_ISteamAppList_GetInstalledApps;
PFN_SteamAPI_ISteamAppList_GetAppName SteamAPI_ISteamAppList_GetAppName;
PFN_SteamAPI_ISteamAppList_GetAppInstallDir SteamAPI_ISteamAppList_GetAppInstallDir;
PFN_SteamAPI_ISteamAppList_GetAppBuildId SteamAPI_ISteamAppList_GetAppBuildId;
PFN_SteamAPI_ISteamHTMLSurface_DestructISteamHTMLSurface SteamAPI_ISteamHTMLSurface_DestructISteamHTMLSurface;
PFN_SteamAPI_ISteamHTMLSurface_Init SteamAPI_ISteamHTMLSurface_Init;
PFN_SteamAPI_ISteamHTMLSurface_Shutdown SteamAPI_ISteamHTMLSurface_Shutdown;
PFN_SteamAPI_ISteamHTMLSurface_CreateBrowser SteamAPI_ISteamHTMLSurface_CreateBrowser;
PFN_SteamAPI_ISteamHTMLSurface_RemoveBrowser SteamAPI_ISteamHTMLSurface_RemoveBrowser;
PFN_SteamAPI_ISteamHTMLSurface_LoadURL SteamAPI_ISteamHTMLSurface_LoadURL;
PFN_SteamAPI_ISteamHTMLSurface_SetSize SteamAPI_ISteamHTMLSurface_SetSize;
PFN_SteamAPI_ISteamHTMLSurface_StopLoad SteamAPI_ISteamHTMLSurface_StopLoad;
PFN_SteamAPI_ISteamHTMLSurface_Reload SteamAPI_ISteamHTMLSurface_Reload;
PFN_SteamAPI_ISteamHTMLSurface_GoBack SteamAPI_ISteamHTMLSurface_GoBack;
PFN_SteamAPI_ISteamHTMLSurface_GoForward SteamAPI_ISteamHTMLSurface_GoForward;
PFN_SteamAPI_ISteamHTMLSurface_AddHeader SteamAPI_ISteamHTMLSurface_AddHeader;
PFN_SteamAPI_ISteamHTMLSurface_ExecuteJavascript SteamAPI_ISteamHTMLSurface_ExecuteJavascript;
PFN_SteamAPI_ISteamHTMLSurface_SetHorizontalScroll SteamAPI_ISteamHTMLSurface_SetHorizontalScroll;
PFN_SteamAPI_ISteamHTMLSurface_SetVerticalScroll SteamAPI_ISteamHTMLSurface_SetVerticalScroll;
PFN_SteamAPI_ISteamHTMLSurface_SetKeyFocus SteamAPI_ISteamHTMLSurface_SetKeyFocus;
PFN_SteamAPI_ISteamHTMLSurface_ViewSource SteamAPI_ISteamHTMLSurface_ViewSource;
PFN_SteamAPI_ISteamHTMLSurface_CopyToClipboard SteamAPI_ISteamHTMLSurface_CopyToClipboard;
PFN_SteamAPI_ISteamHTMLSurface_PasteFromClipboard SteamAPI_ISteamHTMLSurface_PasteFromClipboard;
PFN_SteamAPI_ISteamHTMLSurface_Find SteamAPI_ISteamHTMLSurface_Find;
PFN_SteamAPI_ISteamHTMLSurface_StopFind SteamAPI_ISteamHTMLSurface_StopFind;
PFN_SteamAPI_ISteamHTMLSurface_GetLinkAtPosition SteamAPI_ISteamHTMLSurface_GetLinkAtPosition;
PFN_SteamAPI_ISteamHTMLSurface_SetCookie SteamAPI_ISteamHTMLSurface_SetCookie;
PFN_SteamAPI_ISteamHTMLSurface_SetPageScaleFactor SteamAPI_ISteamHTMLSurface_SetPageScaleFactor;
PFN_SteamAPI_ISteamHTMLSurface_SetBackgroundMode SteamAPI_ISteamHTMLSurface_SetBackgroundMode;
PFN_SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor;
PFN_SteamAPI_ISteamHTMLSurface_AllowStartRequest SteamAPI_ISteamHTMLSurface_AllowStartRequest;
PFN_SteamAPI_ISteamHTMLSurface_JSDialogResponse SteamAPI_ISteamHTMLSurface_JSDialogResponse;
PFN_SteamAPI_ISteamInventory_GetResultStatus SteamAPI_ISteamInventory_GetResultStatus;
PFN_SteamAPI_ISteamInventory_GetResultItems SteamAPI_ISteamInventory_GetResultItems;
PFN_SteamAPI_ISteamInventory_GetResultItemProperty SteamAPI_ISteamInventory_GetResultItemProperty;
PFN_SteamAPI_ISteamInventory_GetResultTimestamp SteamAPI_ISteamInventory_GetResultTimestamp;
PFN_SteamAPI_ISteamInventory_CheckResultSteamID SteamAPI_ISteamInventory_CheckResultSteamID;
PFN_SteamAPI_ISteamInventory_DestroyResult SteamAPI_ISteamInventory_DestroyResult;
PFN_SteamAPI_ISteamInventory_GetAllItems SteamAPI_ISteamInventory_GetAllItems;
PFN_SteamAPI_ISteamInventory_GetItemsByID SteamAPI_ISteamInventory_GetItemsByID;
PFN_SteamAPI_ISteamInventory_SerializeResult SteamAPI_ISteamInventory_SerializeResult;
PFN_SteamAPI_ISteamInventory_DeserializeResult SteamAPI_ISteamInventory_DeserializeResult;
PFN_SteamAPI_ISteamInventory_GenerateItems SteamAPI_ISteamInventory_GenerateItems;
PFN_SteamAPI_ISteamInventory_GrantPromoItems SteamAPI_ISteamInventory_GrantPromoItems;
PFN_SteamAPI_ISteamInventory_AddPromoItem SteamAPI_ISteamInventory_AddPromoItem;
PFN_SteamAPI_ISteamInventory_AddPromoItems SteamAPI_ISteamInventory_AddPromoItems;
PFN_SteamAPI_ISteamInventory_ConsumeItem SteamAPI_ISteamInventory_ConsumeItem;
PFN_SteamAPI_ISteamInventory_ExchangeItems SteamAPI_ISteamInventory_ExchangeItems;
PFN_SteamAPI_ISteamInventory_TransferItemQuantity SteamAPI_ISteamInventory_TransferItemQuantity;
PFN_SteamAPI_ISteamInventory_SendItemDropHeartbeat SteamAPI_ISteamInventory_SendItemDropHeartbeat;
PFN_SteamAPI_ISteamInventory_TriggerItemDrop SteamAPI_ISteamInventory_TriggerItemDrop;
PFN_SteamAPI_ISteamInventory_TradeItems SteamAPI_ISteamInventory_TradeItems;
PFN_SteamAPI_ISteamInventory_LoadItemDefinitions SteamAPI_ISteamInventory_LoadItemDefinitions;
PFN_SteamAPI_ISteamInventory_GetItemDefinitionIDs SteamAPI_ISteamInventory_GetItemDefinitionIDs;
PFN_SteamAPI_ISteamInventory_GetItemDefinitionProperty SteamAPI_ISteamInventory_GetItemDefinitionProperty;
PFN_SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs;
PFN_SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs;
PFN_SteamAPI_ISteamInventory_StartPurchase SteamAPI_ISteamInventory_StartPurchase;
PFN_SteamAPI_ISteamInventory_RequestPrices SteamAPI_ISteamInventory_RequestPrices;
PFN_SteamAPI_ISteamInventory_GetNumItemsWithPrices SteamAPI_ISteamInventory_GetNumItemsWithPrices;
PFN_SteamAPI_ISteamInventory_GetItemsWithPrices SteamAPI_ISteamInventory_GetItemsWithPrices;
PFN_SteamAPI_ISteamInventory_GetItemPrice SteamAPI_ISteamInventory_GetItemPrice;
PFN_SteamAPI_ISteamInventory_StartUpdateProperties SteamAPI_ISteamInventory_StartUpdateProperties;
PFN_SteamAPI_ISteamInventory_RemoveProperty SteamAPI_ISteamInventory_RemoveProperty;
PFN_SteamAPI_ISteamInventory_SetProperty SteamAPI_ISteamInventory_SetProperty;
PFN_SteamAPI_ISteamInventory_SetProperty0 SteamAPI_ISteamInventory_SetProperty0;
PFN_SteamAPI_ISteamInventory_SetProperty1 SteamAPI_ISteamInventory_SetProperty1;
PFN_SteamAPI_ISteamInventory_SetProperty2 SteamAPI_ISteamInventory_SetProperty2;
PFN_SteamAPI_ISteamInventory_SubmitUpdateProperties SteamAPI_ISteamInventory_SubmitUpdateProperties;
PFN_SteamAPI_ISteamVideo_GetVideoURL SteamAPI_ISteamVideo_GetVideoURL;
PFN_SteamAPI_ISteamVideo_IsBroadcasting SteamAPI_ISteamVideo_IsBroadcasting;
PFN_SteamAPI_ISteamVideo_GetOPFSettings SteamAPI_ISteamVideo_GetOPFSettings;
PFN_SteamAPI_ISteamVideo_GetOPFStringForApp SteamAPI_ISteamVideo_GetOPFStringForApp;
PFN_SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled;
PFN_SteamAPI_ISteamParentalSettings_BIsParentalLockLocked SteamAPI_ISteamParentalSettings_BIsParentalLockLocked;
PFN_SteamAPI_ISteamParentalSettings_BIsAppBlocked SteamAPI_ISteamParentalSettings_BIsAppBlocked;
PFN_SteamAPI_ISteamParentalSettings_BIsAppInBlockList SteamAPI_ISteamParentalSettings_BIsAppInBlockList;
PFN_SteamAPI_ISteamParentalSettings_BIsFeatureBlocked SteamAPI_ISteamParentalSettings_BIsFeatureBlocked;
PFN_SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList;
PFN_SteamAPI_ISteamGameServer_InitGameServer SteamAPI_ISteamGameServer_InitGameServer;
PFN_SteamAPI_ISteamGameServer_SetProduct SteamAPI_ISteamGameServer_SetProduct;
PFN_SteamAPI_ISteamGameServer_SetGameDescription SteamAPI_ISteamGameServer_SetGameDescription;
PFN_SteamAPI_ISteamGameServer_SetModDir SteamAPI_ISteamGameServer_SetModDir;
PFN_SteamAPI_ISteamGameServer_SetDedicatedServer SteamAPI_ISteamGameServer_SetDedicatedServer;
PFN_SteamAPI_ISteamGameServer_LogOn SteamAPI_ISteamGameServer_LogOn;
PFN_SteamAPI_ISteamGameServer_LogOnAnonymous SteamAPI_ISteamGameServer_LogOnAnonymous;
PFN_SteamAPI_ISteamGameServer_LogOff SteamAPI_ISteamGameServer_LogOff;
PFN_SteamAPI_ISteamGameServer_BLoggedOn SteamAPI_ISteamGameServer_BLoggedOn;
PFN_SteamAPI_ISteamGameServer_BSecure SteamAPI_ISteamGameServer_BSecure;
PFN_SteamAPI_ISteamGameServer_GetSteamID SteamAPI_ISteamGameServer_GetSteamID;
PFN_SteamAPI_ISteamGameServer_WasRestartRequested SteamAPI_ISteamGameServer_WasRestartRequested;
PFN_SteamAPI_ISteamGameServer_SetMaxPlayerCount SteamAPI_ISteamGameServer_SetMaxPlayerCount;
PFN_SteamAPI_ISteamGameServer_SetBotPlayerCount SteamAPI_ISteamGameServer_SetBotPlayerCount;
PFN_SteamAPI_ISteamGameServer_SetServerName SteamAPI_ISteamGameServer_SetServerName;
PFN_SteamAPI_ISteamGameServer_SetMapName SteamAPI_ISteamGameServer_SetMapName;
PFN_SteamAPI_ISteamGameServer_SetPasswordProtected SteamAPI_ISteamGameServer_SetPasswordProtected;
PFN_SteamAPI_ISteamGameServer_SetSpectatorPort SteamAPI_ISteamGameServer_SetSpectatorPort;
PFN_SteamAPI_ISteamGameServer_SetSpectatorServerName SteamAPI_ISteamGameServer_SetSpectatorServerName;
PFN_SteamAPI_ISteamGameServer_ClearAllKeyValues SteamAPI_ISteamGameServer_ClearAllKeyValues;
PFN_SteamAPI_ISteamGameServer_SetKeyValue SteamAPI_ISteamGameServer_SetKeyValue;
PFN_SteamAPI_ISteamGameServer_SetGameTags SteamAPI_ISteamGameServer_SetGameTags;
PFN_SteamAPI_ISteamGameServer_SetGameData SteamAPI_ISteamGameServer_SetGameData;
PFN_SteamAPI_ISteamGameServer_SetRegion SteamAPI_ISteamGameServer_SetRegion;
PFN_SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate;
PFN_SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection;
PFN_SteamAPI_ISteamGameServer_SendUserDisconnect SteamAPI_ISteamGameServer_SendUserDisconnect;
PFN_SteamAPI_ISteamGameServer_BUpdateUserData SteamAPI_ISteamGameServer_BUpdateUserData;
PFN_SteamAPI_ISteamGameServer_GetAuthSessionTicket SteamAPI_ISteamGameServer_GetAuthSessionTicket;
PFN_SteamAPI_ISteamGameServer_BeginAuthSession SteamAPI_ISteamGameServer_BeginAuthSession;
PFN_SteamAPI_ISteamGameServer_EndAuthSession SteamAPI_ISteamGameServer_EndAuthSession;
PFN_SteamAPI_ISteamGameServer_CancelAuthTicket SteamAPI_ISteamGameServer_CancelAuthTicket;
PFN_SteamAPI_ISteamGameServer_UserHasLicenseForApp SteamAPI_ISteamGameServer_UserHasLicenseForApp;
PFN_SteamAPI_ISteamGameServer_RequestUserGroupStatus SteamAPI_ISteamGameServer_RequestUserGroupStatus;
PFN_SteamAPI_ISteamGameServer_GetGameplayStats SteamAPI_ISteamGameServer_GetGameplayStats;
PFN_SteamAPI_ISteamGameServer_GetServerReputation SteamAPI_ISteamGameServer_GetServerReputation;
PFN_SteamAPI_ISteamGameServer_GetPublicIP SteamAPI_ISteamGameServer_GetPublicIP;
PFN_SteamAPI_ISteamGameServer_HandleIncomingPacket SteamAPI_ISteamGameServer_HandleIncomingPacket;
PFN_SteamAPI_ISteamGameServer_GetNextOutgoingPacket SteamAPI_ISteamGameServer_GetNextOutgoingPacket;
PFN_SteamAPI_ISteamGameServer_EnableHeartbeats SteamAPI_ISteamGameServer_EnableHeartbeats;
PFN_SteamAPI_ISteamGameServer_SetHeartbeatInterval SteamAPI_ISteamGameServer_SetHeartbeatInterval;
PFN_SteamAPI_ISteamGameServer_ForceHeartbeat SteamAPI_ISteamGameServer_ForceHeartbeat;
PFN_SteamAPI_ISteamGameServer_AssociateWithClan SteamAPI_ISteamGameServer_AssociateWithClan;
PFN_SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility;
PFN_SteamAPI_ISteamGameServerStats_RequestUserStats SteamAPI_ISteamGameServerStats_RequestUserStats;
PFN_SteamAPI_ISteamGameServerStats_GetUserStat SteamAPI_ISteamGameServerStats_GetUserStat;
PFN_SteamAPI_ISteamGameServerStats_GetUserStat0 SteamAPI_ISteamGameServerStats_GetUserStat0;
PFN_SteamAPI_ISteamGameServerStats_GetUserAchievement SteamAPI_ISteamGameServerStats_GetUserAchievement;
PFN_SteamAPI_ISteamGameServerStats_SetUserStat SteamAPI_ISteamGameServerStats_SetUserStat;
PFN_SteamAPI_ISteamGameServerStats_SetUserStat0 SteamAPI_ISteamGameServerStats_SetUserStat0;
PFN_SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat;
PFN_SteamAPI_ISteamGameServerStats_SetUserAchievement SteamAPI_ISteamGameServerStats_SetUserAchievement;
PFN_SteamAPI_ISteamGameServerStats_ClearUserAchievement SteamAPI_ISteamGameServerStats_ClearUserAchievement;
PFN_SteamAPI_ISteamGameServerStats_StoreUserStats SteamAPI_ISteamGameServerStats_StoreUserStats;

void* steam_lib;
ICE_STEAM_API  void*           ICE_STEAM_CALLCONV  ice_steam_load(void);
ICE_STEAM_API  void*           ICE_STEAM_CALLCONV  ice_steam_proc(char* name);
ICE_STEAM_API  ice_steam_bool  ICE_STEAM_CALLCONV  ice_steam_close(void);
ICE_STEAM_API  ice_steam_bool  ICE_STEAM_CALLCONV  ice_steam_init(void);

#if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#if defined(_WIN32) || defined(WIN32)
const char * steamworks_libname = "steam_api.dll";

#elif defined(_WIN64) || defined(WIN64)
const char * steamworks_libname = "steam_api64.dll";

#endif

#elif defined(__APPLE__) || defined(__MACH__) || defined(__DARWIN__) || defined(__darwin__) || defined(__DARWIN) || defined(_DARWIN)
const char * steamworks_libname = "libsteam_api.dylib";

#else
const char * steamworks_libname = "libsteam_api.so";

#endif

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_steam IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_STEAM_IMPL)
#include <stdio.h>

#if defined(ICE_STEAM_MICROSOFT)
#  include <windows.h>
#elif defined(ICE_STEAM_BEOS)
#  include <image.h>
#elif defined(ICE_STEAM_UNIX)
#  include <dlfcn.h>
#endif

ICE_STEAM_API void* ICE_STEAM_CALLCONV ice_steam_load(void) {
#if defined(ICE_STEAM_MICROSOFT)
return (HMODULE)LoadLibraryA(steamworks_libname);

#elif defined(ICE_STEAM_BEOS)
return (image_id)load_add_on(steamworks_libname);

#elif defined(ICE_STEAM_UNIX)
return dlopen(steamworks_libname, RTLD_LAZY | RTLD_GLOBAL);

#endif
}

ICE_STEAM_API void* ICE_STEAM_CALLCONV ice_steam_proc(char* name) {
#if defined(ICE_STEAM_MICROSOFT)
return GetProcAddress((HMODULE)steam_lib, name);

#elif defined(ICE_STEAM_BEOS)
void* addr;

if (get_image_symbol((image_id)steam_lib, name, B_SYMBOL_TYPE_ANY, &addr) == B_OK) {
    return addr;
}

#elif defined(ICE_STEAM_UNIX)
return dlsym(steam_lib, name);

#endif
}

ICE_STEAM_API ice_steam_bool ICE_STEAM_CALLCONV ice_steam_close(void) {
#if defined(ICE_STEAM_MICROSOFT)
return (FreeLibrary((HMODULE)steam_lib) == TRUE) ? ICE_STEAM_TRUE : ICE_STEAM_FALSE;

#elif defined(ICE_STEAM_BEOS)
return (unload_add_on((image_id)steam_lib) == B_OK) ? ICE_STEAM_TRUE : ICE_STEAM_FALSE;

#elif defined(ICE_STEAM_UNIX)
return (dlclose(steam_lib) == 0) ? ICE_STEAM_TRUE : ICE_STEAM_FALSE;

#else
return ICE_STEAM_FALSE;

#endif
}

ICE_STEAM_API ice_steam_bool ICE_STEAM_CALLCONV ice_steam_init(void) {
    steam_lib = ice_steam_load();
    if (steam_lib == NULL) return ICE_STEAM_FALSE;
    
    SteamAPI_Init = (PFN_SteamAPI_Init) ice_steam_proc("SteamAPI_Init");
    SteamAPI_Shutdown = (PFN_SteamAPI_Shutdown) ice_steam_proc("SteamAPI_Shutdown");
    SteamAPI_RestartAppIfNecessary = (PFN_SteamAPI_RestartAppIfNecessary) ice_steam_proc("SteamAPI_RestartAppIfNecessary");
    SteamAPI_ReleaseCurrentThreadMemory = (PFN_SteamAPI_ReleaseCurrentThreadMemory) ice_steam_proc("SteamAPI_ReleaseCurrentThreadMemory");
    SteamAPI_WriteMiniDump = (PFN_SteamAPI_WriteMiniDump) ice_steam_proc("SteamAPI_WriteMiniDump");
    SteamAPI_SetMiniDumpComment = (PFN_SteamAPI_SetMiniDumpComment) ice_steam_proc("SteamAPI_SetMiniDumpComment");
    SteamClient = (PFN_SteamClient) ice_steam_proc("SteamClient");
    SteamAPI_ISteamClient_CreateSteamPipe = (PFN_SteamAPI_ISteamClient_CreateSteamPipe) ice_steam_proc("SteamAPI_ISteamClient_CreateSteamPipe");
    SteamAPI_ISteamClient_BReleaseSteamPipe = (PFN_SteamAPI_ISteamClient_BReleaseSteamPipe) ice_steam_proc("SteamAPI_ISteamClient_BReleaseSteamPipe");
    SteamAPI_ISteamClient_ConnectToGlobalUser = (PFN_SteamAPI_ISteamClient_ConnectToGlobalUser) ice_steam_proc("SteamAPI_ISteamClient_ConnectToGlobalUser");
    SteamAPI_ISteamClient_CreateLocalUser = (PFN_SteamAPI_ISteamClient_CreateLocalUser) ice_steam_proc("SteamAPI_ISteamClient_CreateLocalUser");
    SteamAPI_ISteamClient_ReleaseUser = (PFN_SteamAPI_ISteamClient_ReleaseUser) ice_steam_proc("SteamAPI_ISteamClient_ReleaseUser");
    SteamAPI_ISteamClient_GetISteamUser = (PFN_SteamAPI_ISteamClient_GetISteamUser) ice_steam_proc("SteamAPI_ISteamClient_GetISteamUser");
    SteamAPI_ISteamClient_GetISteamGameServer = (PFN_SteamAPI_ISteamClient_GetISteamGameServer) ice_steam_proc("SteamAPI_ISteamClient_GetISteamGameServer");
    SteamAPI_ISteamClient_SetLocalIPBinding = (PFN_SteamAPI_ISteamClient_SetLocalIPBinding) ice_steam_proc("SteamAPI_ISteamClient_SetLocalIPBinding");
    SteamAPI_ISteamClient_GetISteamFriends = (PFN_SteamAPI_ISteamClient_GetISteamFriends) ice_steam_proc("SteamAPI_ISteamClient_GetISteamFriends");
    SteamAPI_ISteamClient_GetISteamUtils = (PFN_SteamAPI_ISteamClient_GetISteamUtils) ice_steam_proc("SteamAPI_ISteamClient_GetISteamUtils");
    SteamAPI_ISteamClient_GetISteamMatchmaking = (PFN_SteamAPI_ISteamClient_GetISteamMatchmaking) ice_steam_proc("SteamAPI_ISteamClient_GetISteamMatchmaking");
    SteamAPI_ISteamClient_GetISteamMatchmakingServers = (PFN_SteamAPI_ISteamClient_GetISteamMatchmakingServers) ice_steam_proc("SteamAPI_ISteamClient_GetISteamMatchmakingServers");
    SteamAPI_ISteamClient_GetISteamGenericInterface = (PFN_SteamAPI_ISteamClient_GetISteamGenericInterface) ice_steam_proc("SteamAPI_ISteamClient_GetISteamGenericInterface");
    SteamAPI_ISteamClient_GetISteamUserStats = (PFN_SteamAPI_ISteamClient_GetISteamUserStats) ice_steam_proc("SteamAPI_ISteamClient_GetISteamUserStats");
    SteamAPI_ISteamClient_GetISteamGameServerStats = (PFN_SteamAPI_ISteamClient_GetISteamGameServerStats) ice_steam_proc("SteamAPI_ISteamClient_GetISteamGameServerStats");
    SteamAPI_ISteamClient_GetISteamApps = (PFN_SteamAPI_ISteamClient_GetISteamApps) ice_steam_proc("SteamAPI_ISteamClient_GetISteamApps");
    SteamAPI_ISteamClient_GetISteamNetworking = (PFN_SteamAPI_ISteamClient_GetISteamNetworking) ice_steam_proc("SteamAPI_ISteamClient_GetISteamNetworking");
    SteamAPI_ISteamClient_GetISteamRemoteStorage = (PFN_SteamAPI_ISteamClient_GetISteamRemoteStorage) ice_steam_proc("SteamAPI_ISteamClient_GetISteamRemoteStorage");
    SteamAPI_ISteamClient_GetISteamScreenshots = (PFN_SteamAPI_ISteamClient_GetISteamScreenshots) ice_steam_proc("SteamAPI_ISteamClient_GetISteamScreenshots");
    SteamAPI_ISteamClient_GetIPCCallCount = (PFN_SteamAPI_ISteamClient_GetIPCCallCount) ice_steam_proc("SteamAPI_ISteamClient_GetIPCCallCount");
    SteamAPI_ISteamClient_SetWarningMessageHook = (PFN_SteamAPI_ISteamClient_SetWarningMessageHook) ice_steam_proc("SteamAPI_ISteamClient_SetWarningMessageHook");
    SteamAPI_ISteamClient_BShutdownIfAllPipesClosed = (PFN_SteamAPI_ISteamClient_BShutdownIfAllPipesClosed) ice_steam_proc("SteamAPI_ISteamClient_BShutdownIfAllPipesClosed");
    SteamAPI_ISteamClient_GetISteamHTTP = (PFN_SteamAPI_ISteamClient_GetISteamHTTP) ice_steam_proc("SteamAPI_ISteamClient_GetISteamHTTP");
    SteamAPI_ISteamClient_GetISteamController = (PFN_SteamAPI_ISteamClient_GetISteamController) ice_steam_proc("SteamAPI_ISteamClient_GetISteamController");
    SteamAPI_ISteamClient_GetISteamUGC = (PFN_SteamAPI_ISteamClient_GetISteamUGC) ice_steam_proc("SteamAPI_ISteamClient_GetISteamUGC");
    SteamAPI_ISteamClient_GetISteamAppList = (PFN_SteamAPI_ISteamClient_GetISteamAppList) ice_steam_proc("SteamAPI_ISteamClient_GetISteamAppList");
    SteamAPI_ISteamClient_GetISteamMusic = (PFN_SteamAPI_ISteamClient_GetISteamMusic) ice_steam_proc("SteamAPI_ISteamClient_GetISteamMusic");
    SteamAPI_ISteamClient_GetISteamMusicRemote = (PFN_SteamAPI_ISteamClient_GetISteamMusicRemote) ice_steam_proc("SteamAPI_ISteamClient_GetISteamMusicRemote");
    SteamAPI_ISteamClient_GetISteamHTMLSurface = (PFN_SteamAPI_ISteamClient_GetISteamHTMLSurface) ice_steam_proc("SteamAPI_ISteamClient_GetISteamHTMLSurface");
    SteamAPI_ISteamClient_GetISteamInventory = (PFN_SteamAPI_ISteamClient_GetISteamInventory) ice_steam_proc("SteamAPI_ISteamClient_GetISteamInventory");
    SteamAPI_ISteamClient_GetISteamVideo = (PFN_SteamAPI_ISteamClient_GetISteamVideo) ice_steam_proc("SteamAPI_ISteamClient_GetISteamVideo");
    SteamAPI_ISteamClient_GetISteamParentalSettings = (PFN_SteamAPI_ISteamClient_GetISteamParentalSettings) ice_steam_proc("SteamAPI_ISteamClient_GetISteamParentalSettings");
    SteamAPI_ISteamUser_GetHSteamUser = (PFN_SteamAPI_ISteamUser_GetHSteamUser) ice_steam_proc("SteamAPI_ISteamUser_GetHSteamUser");
    SteamAPI_ISteamUser_BLoggedOn = (PFN_SteamAPI_ISteamUser_BLoggedOn) ice_steam_proc("SteamAPI_ISteamUser_BLoggedOn");
    SteamAPI_ISteamUser_GetSteamID = (PFN_SteamAPI_ISteamUser_GetSteamID) ice_steam_proc("SteamAPI_ISteamUser_GetSteamID");
    SteamAPI_ISteamUser_InitiateGameConnection = (PFN_SteamAPI_ISteamUser_InitiateGameConnection) ice_steam_proc("SteamAPI_ISteamUser_InitiateGameConnection");
    SteamAPI_ISteamUser_TerminateGameConnection = (PFN_SteamAPI_ISteamUser_TerminateGameConnection) ice_steam_proc("SteamAPI_ISteamUser_TerminateGameConnection");
    SteamAPI_ISteamUser_TrackAppUsageEvent = (PFN_SteamAPI_ISteamUser_TrackAppUsageEvent) ice_steam_proc("SteamAPI_ISteamUser_TrackAppUsageEvent");
    SteamAPI_ISteamUser_GetUserDataFolder = (PFN_SteamAPI_ISteamUser_GetUserDataFolder) ice_steam_proc("SteamAPI_ISteamUser_GetUserDataFolder");
    SteamAPI_ISteamUser_StartVoiceRecording = (PFN_SteamAPI_ISteamUser_StartVoiceRecording) ice_steam_proc("SteamAPI_ISteamUser_StartVoiceRecording");
    SteamAPI_ISteamUser_StopVoiceRecording = (PFN_SteamAPI_ISteamUser_StopVoiceRecording) ice_steam_proc("SteamAPI_ISteamUser_StopVoiceRecording");
    SteamAPI_ISteamUser_GetAvailableVoice = (PFN_SteamAPI_ISteamUser_GetAvailableVoice) ice_steam_proc("SteamAPI_ISteamUser_GetAvailableVoice");
    SteamAPI_ISteamUser_GetVoice = (PFN_SteamAPI_ISteamUser_GetVoice) ice_steam_proc("SteamAPI_ISteamUser_GetVoice");
    SteamAPI_ISteamUser_DecompressVoice = (PFN_SteamAPI_ISteamUser_DecompressVoice) ice_steam_proc("SteamAPI_ISteamUser_DecompressVoice");
    SteamAPI_ISteamUser_GetVoiceOptimalSampleRate = (PFN_SteamAPI_ISteamUser_GetVoiceOptimalSampleRate) ice_steam_proc("SteamAPI_ISteamUser_GetVoiceOptimalSampleRate");
    SteamAPI_ISteamUser_GetAuthSessionTicket = (PFN_SteamAPI_ISteamUser_GetAuthSessionTicket) ice_steam_proc("SteamAPI_ISteamUser_GetAuthSessionTicket");
    SteamAPI_ISteamUser_BeginAuthSession = (PFN_SteamAPI_ISteamUser_BeginAuthSession) ice_steam_proc("SteamAPI_ISteamUser_BeginAuthSession");
    SteamAPI_ISteamUser_EndAuthSession = (PFN_SteamAPI_ISteamUser_EndAuthSession) ice_steam_proc("SteamAPI_ISteamUser_EndAuthSession");
    SteamAPI_ISteamUser_CancelAuthTicket = (PFN_SteamAPI_ISteamUser_CancelAuthTicket) ice_steam_proc("SteamAPI_ISteamUser_CancelAuthTicket");
    SteamAPI_ISteamUser_UserHasLicenseForApp = (PFN_SteamAPI_ISteamUser_UserHasLicenseForApp) ice_steam_proc("SteamAPI_ISteamUser_UserHasLicenseForApp");
    SteamAPI_ISteamUser_BIsBehindNAT = (PFN_SteamAPI_ISteamUser_BIsBehindNAT) ice_steam_proc("SteamAPI_ISteamUser_BIsBehindNAT");
    SteamAPI_ISteamUser_AdvertiseGame = (PFN_SteamAPI_ISteamUser_AdvertiseGame) ice_steam_proc("SteamAPI_ISteamUser_AdvertiseGame");
    SteamAPI_ISteamUser_RequestEncryptedAppTicket = (PFN_SteamAPI_ISteamUser_RequestEncryptedAppTicket) ice_steam_proc("SteamAPI_ISteamUser_RequestEncryptedAppTicket");
    SteamAPI_ISteamUser_GetEncryptedAppTicket = (PFN_SteamAPI_ISteamUser_GetEncryptedAppTicket) ice_steam_proc("SteamAPI_ISteamUser_GetEncryptedAppTicket");
    SteamAPI_ISteamUser_GetGameBadgeLevel = (PFN_SteamAPI_ISteamUser_GetGameBadgeLevel) ice_steam_proc("SteamAPI_ISteamUser_GetGameBadgeLevel");
    SteamAPI_ISteamUser_GetPlayerSteamLevel = (PFN_SteamAPI_ISteamUser_GetPlayerSteamLevel) ice_steam_proc("SteamAPI_ISteamUser_GetPlayerSteamLevel");
    SteamAPI_ISteamUser_RequestStoreAuthURL = (PFN_SteamAPI_ISteamUser_RequestStoreAuthURL) ice_steam_proc("SteamAPI_ISteamUser_RequestStoreAuthURL");
    SteamAPI_ISteamUser_BIsPhoneVerified = (PFN_SteamAPI_ISteamUser_BIsPhoneVerified) ice_steam_proc("SteamAPI_ISteamUser_BIsPhoneVerified");
    SteamAPI_ISteamUser_BIsTwoFactorEnabled = (PFN_SteamAPI_ISteamUser_BIsTwoFactorEnabled) ice_steam_proc("SteamAPI_ISteamUser_BIsTwoFactorEnabled");
    SteamAPI_ISteamUser_BIsPhoneIdentifying = (PFN_SteamAPI_ISteamUser_BIsPhoneIdentifying) ice_steam_proc("SteamAPI_ISteamUser_BIsPhoneIdentifying");
    SteamAPI_ISteamUser_BIsPhoneRequiringVerification = (PFN_SteamAPI_ISteamUser_BIsPhoneRequiringVerification) ice_steam_proc("SteamAPI_ISteamUser_BIsPhoneRequiringVerification");
    SteamAPI_ISteamFriends_GetPersonaName = (PFN_SteamAPI_ISteamFriends_GetPersonaName) ice_steam_proc("SteamAPI_ISteamFriends_GetPersonaName");
    SteamAPI_ISteamFriends_SetPersonaName = (PFN_SteamAPI_ISteamFriends_SetPersonaName) ice_steam_proc("SteamAPI_ISteamFriends_SetPersonaName");
    SteamAPI_ISteamFriends_GetPersonaState = (PFN_SteamAPI_ISteamFriends_GetPersonaState) ice_steam_proc("SteamAPI_ISteamFriends_GetPersonaState");
    SteamAPI_ISteamFriends_GetFriendCount = (PFN_SteamAPI_ISteamFriends_GetFriendCount) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendCount");
    SteamAPI_ISteamFriends_GetFriendByIndex = (PFN_SteamAPI_ISteamFriends_GetFriendByIndex) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendByIndex");
    SteamAPI_ISteamFriends_GetFriendRelationship = (PFN_SteamAPI_ISteamFriends_GetFriendRelationship) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendRelationship");
    SteamAPI_ISteamFriends_GetFriendPersonaState = (PFN_SteamAPI_ISteamFriends_GetFriendPersonaState) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendPersonaState");
    SteamAPI_ISteamFriends_GetFriendPersonaName = (PFN_SteamAPI_ISteamFriends_GetFriendPersonaName) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendPersonaName");
    SteamAPI_ISteamFriends_GetFriendGamePlayed = (PFN_SteamAPI_ISteamFriends_GetFriendGamePlayed) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendGamePlayed");
    SteamAPI_ISteamFriends_GetFriendPersonaNameHistory = (PFN_SteamAPI_ISteamFriends_GetFriendPersonaNameHistory) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendPersonaNameHistory");
    SteamAPI_ISteamFriends_GetFriendSteamLevel = (PFN_SteamAPI_ISteamFriends_GetFriendSteamLevel) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendSteamLevel");
    SteamAPI_ISteamFriends_GetPlayerNickname = (PFN_SteamAPI_ISteamFriends_GetPlayerNickname) ice_steam_proc("SteamAPI_ISteamFriends_GetPlayerNickname");
    SteamAPI_ISteamFriends_GetFriendsGroupCount = (PFN_SteamAPI_ISteamFriends_GetFriendsGroupCount) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendsGroupCount");
    SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex = (PFN_SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex");
    SteamAPI_ISteamFriends_GetFriendsGroupName = (PFN_SteamAPI_ISteamFriends_GetFriendsGroupName) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendsGroupName");
    SteamAPI_ISteamFriends_GetFriendsGroupMembersCount = (PFN_SteamAPI_ISteamFriends_GetFriendsGroupMembersCount) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendsGroupMembersCount");
    SteamAPI_ISteamFriends_GetFriendsGroupMembersList = (PFN_SteamAPI_ISteamFriends_GetFriendsGroupMembersList) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendsGroupMembersList");
    SteamAPI_ISteamFriends_HasFriend = (PFN_SteamAPI_ISteamFriends_HasFriend) ice_steam_proc("SteamAPI_ISteamFriends_HasFriend");
    SteamAPI_ISteamFriends_GetClanCount = (PFN_SteamAPI_ISteamFriends_GetClanCount) ice_steam_proc("SteamAPI_ISteamFriends_GetClanCount");
    SteamAPI_ISteamFriends_GetClanByIndex = (PFN_SteamAPI_ISteamFriends_GetClanByIndex) ice_steam_proc("SteamAPI_ISteamFriends_GetClanByIndex");
    SteamAPI_ISteamFriends_GetClanName = (PFN_SteamAPI_ISteamFriends_GetClanName) ice_steam_proc("SteamAPI_ISteamFriends_GetClanName");
    SteamAPI_ISteamFriends_GetClanTag = (PFN_SteamAPI_ISteamFriends_GetClanTag) ice_steam_proc("SteamAPI_ISteamFriends_GetClanTag");
    SteamAPI_ISteamFriends_GetClanActivityCounts = (PFN_SteamAPI_ISteamFriends_GetClanActivityCounts) ice_steam_proc("SteamAPI_ISteamFriends_GetClanActivityCounts");
    SteamAPI_ISteamFriends_DownloadClanActivityCounts = (PFN_SteamAPI_ISteamFriends_DownloadClanActivityCounts) ice_steam_proc("SteamAPI_ISteamFriends_DownloadClanActivityCounts");
    SteamAPI_ISteamFriends_GetFriendCountFromSource = (PFN_SteamAPI_ISteamFriends_GetFriendCountFromSource) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendCountFromSource");
    SteamAPI_ISteamFriends_GetFriendFromSourceByIndex = (PFN_SteamAPI_ISteamFriends_GetFriendFromSourceByIndex) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendFromSourceByIndex");
    SteamAPI_ISteamFriends_IsUserInSource = (PFN_SteamAPI_ISteamFriends_IsUserInSource) ice_steam_proc("SteamAPI_ISteamFriends_IsUserInSource");
    SteamAPI_ISteamFriends_SetInGameVoiceSpeaking = (PFN_SteamAPI_ISteamFriends_SetInGameVoiceSpeaking) ice_steam_proc("SteamAPI_ISteamFriends_SetInGameVoiceSpeaking");
    SteamAPI_ISteamFriends_ActivateGameOverlay = (PFN_SteamAPI_ISteamFriends_ActivateGameOverlay) ice_steam_proc("SteamAPI_ISteamFriends_ActivateGameOverlay");
    SteamAPI_ISteamFriends_ActivateGameOverlayToUser = (PFN_SteamAPI_ISteamFriends_ActivateGameOverlayToUser) ice_steam_proc("SteamAPI_ISteamFriends_ActivateGameOverlayToUser");
    SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage = (PFN_SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage) ice_steam_proc("SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage");
    SteamAPI_ISteamFriends_ActivateGameOverlayToStore = (PFN_SteamAPI_ISteamFriends_ActivateGameOverlayToStore) ice_steam_proc("SteamAPI_ISteamFriends_ActivateGameOverlayToStore");
    SteamAPI_ISteamFriends_SetPlayedWith = (PFN_SteamAPI_ISteamFriends_SetPlayedWith) ice_steam_proc("SteamAPI_ISteamFriends_SetPlayedWith");
    SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog = (PFN_SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog) ice_steam_proc("SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog");
    SteamAPI_ISteamFriends_GetSmallFriendAvatar = (PFN_SteamAPI_ISteamFriends_GetSmallFriendAvatar) ice_steam_proc("SteamAPI_ISteamFriends_GetSmallFriendAvatar");
    SteamAPI_ISteamFriends_GetMediumFriendAvatar = (PFN_SteamAPI_ISteamFriends_GetMediumFriendAvatar) ice_steam_proc("SteamAPI_ISteamFriends_GetMediumFriendAvatar");
    SteamAPI_ISteamFriends_GetLargeFriendAvatar = (PFN_SteamAPI_ISteamFriends_GetLargeFriendAvatar) ice_steam_proc("SteamAPI_ISteamFriends_GetLargeFriendAvatar");
    SteamAPI_ISteamFriends_RequestUserInformation = (PFN_SteamAPI_ISteamFriends_RequestUserInformation) ice_steam_proc("SteamAPI_ISteamFriends_RequestUserInformation");
    SteamAPI_ISteamFriends_RequestClanOfficerList = (PFN_SteamAPI_ISteamFriends_RequestClanOfficerList) ice_steam_proc("SteamAPI_ISteamFriends_RequestClanOfficerList");
    SteamAPI_ISteamFriends_GetClanOwner = (PFN_SteamAPI_ISteamFriends_GetClanOwner) ice_steam_proc("SteamAPI_ISteamFriends_GetClanOwner");
    SteamAPI_ISteamFriends_GetClanOfficerCount = (PFN_SteamAPI_ISteamFriends_GetClanOfficerCount) ice_steam_proc("SteamAPI_ISteamFriends_GetClanOfficerCount");
    SteamAPI_ISteamFriends_GetClanOfficerByIndex = (PFN_SteamAPI_ISteamFriends_GetClanOfficerByIndex) ice_steam_proc("SteamAPI_ISteamFriends_GetClanOfficerByIndex");
    SteamAPI_ISteamFriends_GetUserRestrictions = (PFN_SteamAPI_ISteamFriends_GetUserRestrictions) ice_steam_proc("SteamAPI_ISteamFriends_GetUserRestrictions");
    SteamAPI_ISteamFriends_SetRichPresence = (PFN_SteamAPI_ISteamFriends_SetRichPresence) ice_steam_proc("SteamAPI_ISteamFriends_SetRichPresence");
    SteamAPI_ISteamFriends_ClearRichPresence = (PFN_SteamAPI_ISteamFriends_ClearRichPresence) ice_steam_proc("SteamAPI_ISteamFriends_ClearRichPresence");
    SteamAPI_ISteamFriends_GetFriendRichPresence = (PFN_SteamAPI_ISteamFriends_GetFriendRichPresence) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendRichPresence");
    SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount = (PFN_SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount");
    SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex = (PFN_SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex");
    SteamAPI_ISteamFriends_RequestFriendRichPresence = (PFN_SteamAPI_ISteamFriends_RequestFriendRichPresence) ice_steam_proc("SteamAPI_ISteamFriends_RequestFriendRichPresence");
    SteamAPI_ISteamFriends_InviteUserToGame = (PFN_SteamAPI_ISteamFriends_InviteUserToGame) ice_steam_proc("SteamAPI_ISteamFriends_InviteUserToGame");
    SteamAPI_ISteamFriends_GetCoplayFriendCount = (PFN_SteamAPI_ISteamFriends_GetCoplayFriendCount) ice_steam_proc("SteamAPI_ISteamFriends_GetCoplayFriendCount");
    SteamAPI_ISteamFriends_GetCoplayFriend = (PFN_SteamAPI_ISteamFriends_GetCoplayFriend) ice_steam_proc("SteamAPI_ISteamFriends_GetCoplayFriend");
    SteamAPI_ISteamFriends_GetFriendCoplayTime = (PFN_SteamAPI_ISteamFriends_GetFriendCoplayTime) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendCoplayTime");
    SteamAPI_ISteamFriends_GetFriendCoplayGame = (PFN_SteamAPI_ISteamFriends_GetFriendCoplayGame) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendCoplayGame");
    SteamAPI_ISteamFriends_JoinClanChatRoom = (PFN_SteamAPI_ISteamFriends_JoinClanChatRoom) ice_steam_proc("SteamAPI_ISteamFriends_JoinClanChatRoom");
    SteamAPI_ISteamFriends_LeaveClanChatRoom = (PFN_SteamAPI_ISteamFriends_LeaveClanChatRoom) ice_steam_proc("SteamAPI_ISteamFriends_LeaveClanChatRoom");
    SteamAPI_ISteamFriends_GetClanChatMemberCount = (PFN_SteamAPI_ISteamFriends_GetClanChatMemberCount) ice_steam_proc("SteamAPI_ISteamFriends_GetClanChatMemberCount");
    SteamAPI_ISteamFriends_GetChatMemberByIndex = (PFN_SteamAPI_ISteamFriends_GetChatMemberByIndex) ice_steam_proc("SteamAPI_ISteamFriends_GetChatMemberByIndex");
    SteamAPI_ISteamFriends_SendClanChatMessage = (PFN_SteamAPI_ISteamFriends_SendClanChatMessage) ice_steam_proc("SteamAPI_ISteamFriends_SendClanChatMessage");
    SteamAPI_ISteamFriends_GetClanChatMessage = (PFN_SteamAPI_ISteamFriends_GetClanChatMessage) ice_steam_proc("SteamAPI_ISteamFriends_GetClanChatMessage");
    SteamAPI_ISteamFriends_IsClanChatAdmin = (PFN_SteamAPI_ISteamFriends_IsClanChatAdmin) ice_steam_proc("SteamAPI_ISteamFriends_IsClanChatAdmin");
    SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam = (PFN_SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam) ice_steam_proc("SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam");
    SteamAPI_ISteamFriends_OpenClanChatWindowInSteam = (PFN_SteamAPI_ISteamFriends_OpenClanChatWindowInSteam) ice_steam_proc("SteamAPI_ISteamFriends_OpenClanChatWindowInSteam");
    SteamAPI_ISteamFriends_CloseClanChatWindowInSteam = (PFN_SteamAPI_ISteamFriends_CloseClanChatWindowInSteam) ice_steam_proc("SteamAPI_ISteamFriends_CloseClanChatWindowInSteam");
    SteamAPI_ISteamFriends_SetListenForFriendsMessages = (PFN_SteamAPI_ISteamFriends_SetListenForFriendsMessages) ice_steam_proc("SteamAPI_ISteamFriends_SetListenForFriendsMessages");
    SteamAPI_ISteamFriends_ReplyToFriendMessage = (PFN_SteamAPI_ISteamFriends_ReplyToFriendMessage) ice_steam_proc("SteamAPI_ISteamFriends_ReplyToFriendMessage");
    SteamAPI_ISteamFriends_GetFriendMessage = (PFN_SteamAPI_ISteamFriends_GetFriendMessage) ice_steam_proc("SteamAPI_ISteamFriends_GetFriendMessage");
    SteamAPI_ISteamFriends_GetFollowerCount = (PFN_SteamAPI_ISteamFriends_GetFollowerCount) ice_steam_proc("SteamAPI_ISteamFriends_GetFollowerCount");
    SteamAPI_ISteamFriends_IsFollowing = (PFN_SteamAPI_ISteamFriends_IsFollowing) ice_steam_proc("SteamAPI_ISteamFriends_IsFollowing");
    SteamAPI_ISteamFriends_EnumerateFollowingList = (PFN_SteamAPI_ISteamFriends_EnumerateFollowingList) ice_steam_proc("SteamAPI_ISteamFriends_EnumerateFollowingList");
    SteamAPI_ISteamFriends_IsClanPublic = (PFN_SteamAPI_ISteamFriends_IsClanPublic) ice_steam_proc("SteamAPI_ISteamFriends_IsClanPublic");
    SteamAPI_ISteamFriends_IsClanOfficialGameGroup = (PFN_SteamAPI_ISteamFriends_IsClanOfficialGameGroup) ice_steam_proc("SteamAPI_ISteamFriends_IsClanOfficialGameGroup");
    SteamAPI_ISteamUtils_GetSecondsSinceAppActive = (PFN_SteamAPI_ISteamUtils_GetSecondsSinceAppActive) ice_steam_proc("SteamAPI_ISteamUtils_GetSecondsSinceAppActive");
    SteamAPI_ISteamUtils_GetSecondsSinceComputerActive = (PFN_SteamAPI_ISteamUtils_GetSecondsSinceComputerActive) ice_steam_proc("SteamAPI_ISteamUtils_GetSecondsSinceComputerActive");
    SteamAPI_ISteamUtils_GetConnectedUniverse = (PFN_SteamAPI_ISteamUtils_GetConnectedUniverse) ice_steam_proc("SteamAPI_ISteamUtils_GetConnectedUniverse");
    SteamAPI_ISteamUtils_GetServerRealTime = (PFN_SteamAPI_ISteamUtils_GetServerRealTime) ice_steam_proc("SteamAPI_ISteamUtils_GetServerRealTime");
    SteamAPI_ISteamUtils_GetIPCountry = (PFN_SteamAPI_ISteamUtils_GetIPCountry) ice_steam_proc("SteamAPI_ISteamUtils_GetIPCountry");
    SteamAPI_ISteamUtils_GetImageSize = (PFN_SteamAPI_ISteamUtils_GetImageSize) ice_steam_proc("SteamAPI_ISteamUtils_GetImageSize");
    SteamAPI_ISteamUtils_GetImageRGBA = (PFN_SteamAPI_ISteamUtils_GetImageRGBA) ice_steam_proc("SteamAPI_ISteamUtils_GetImageRGBA");
    SteamAPI_ISteamUtils_GetCSERIPPort = (PFN_SteamAPI_ISteamUtils_GetCSERIPPort) ice_steam_proc("SteamAPI_ISteamUtils_GetCSERIPPort");
    SteamAPI_ISteamUtils_GetCurrentBatteryPower = (PFN_SteamAPI_ISteamUtils_GetCurrentBatteryPower) ice_steam_proc("SteamAPI_ISteamUtils_GetCurrentBatteryPower");
    SteamAPI_ISteamUtils_GetAppID = (PFN_SteamAPI_ISteamUtils_GetAppID) ice_steam_proc("SteamAPI_ISteamUtils_GetAppID");
    SteamAPI_ISteamUtils_SetOverlayNotificationPosition = (PFN_SteamAPI_ISteamUtils_SetOverlayNotificationPosition) ice_steam_proc("SteamAPI_ISteamUtils_SetOverlayNotificationPosition");
    SteamAPI_ISteamUtils_IsAPICallCompleted = (PFN_SteamAPI_ISteamUtils_IsAPICallCompleted) ice_steam_proc("SteamAPI_ISteamUtils_IsAPICallCompleted");
    SteamAPI_ISteamUtils_GetAPICallFailureReason = (PFN_SteamAPI_ISteamUtils_GetAPICallFailureReason) ice_steam_proc("SteamAPI_ISteamUtils_GetAPICallFailureReason");
    SteamAPI_ISteamUtils_GetAPICallResult = (PFN_SteamAPI_ISteamUtils_GetAPICallResult) ice_steam_proc("SteamAPI_ISteamUtils_GetAPICallResult");
    SteamAPI_ISteamUtils_GetIPCCallCount = (PFN_SteamAPI_ISteamUtils_GetIPCCallCount) ice_steam_proc("SteamAPI_ISteamUtils_GetIPCCallCount");
    SteamAPI_ISteamUtils_SetWarningMessageHook = (PFN_SteamAPI_ISteamUtils_SetWarningMessageHook) ice_steam_proc("SteamAPI_ISteamUtils_SetWarningMessageHook");
    SteamAPI_ISteamUtils_IsOverlayEnabled = (PFN_SteamAPI_ISteamUtils_IsOverlayEnabled) ice_steam_proc("SteamAPI_ISteamUtils_IsOverlayEnabled");
    SteamAPI_ISteamUtils_BOverlayNeedsPresent = (PFN_SteamAPI_ISteamUtils_BOverlayNeedsPresent) ice_steam_proc("SteamAPI_ISteamUtils_BOverlayNeedsPresent");
    SteamAPI_ISteamUtils_CheckFileSignature = (PFN_SteamAPI_ISteamUtils_CheckFileSignature) ice_steam_proc("SteamAPI_ISteamUtils_CheckFileSignature");
    SteamAPI_ISteamUtils_ShowGamepadTextInput = (PFN_SteamAPI_ISteamUtils_ShowGamepadTextInput) ice_steam_proc("SteamAPI_ISteamUtils_ShowGamepadTextInput");
    SteamAPI_ISteamUtils_GetEnteredGamepadTextLength = (PFN_SteamAPI_ISteamUtils_GetEnteredGamepadTextLength) ice_steam_proc("SteamAPI_ISteamUtils_GetEnteredGamepadTextLength");
    SteamAPI_ISteamUtils_GetEnteredGamepadTextInput = (PFN_SteamAPI_ISteamUtils_GetEnteredGamepadTextInput) ice_steam_proc("SteamAPI_ISteamUtils_GetEnteredGamepadTextInput");
    SteamAPI_ISteamUtils_GetSteamUILanguage = (PFN_SteamAPI_ISteamUtils_GetSteamUILanguage) ice_steam_proc("SteamAPI_ISteamUtils_GetSteamUILanguage");
    SteamAPI_ISteamUtils_IsSteamRunningInVR = (PFN_SteamAPI_ISteamUtils_IsSteamRunningInVR) ice_steam_proc("SteamAPI_ISteamUtils_IsSteamRunningInVR");
    SteamAPI_ISteamUtils_SetOverlayNotificationInset = (PFN_SteamAPI_ISteamUtils_SetOverlayNotificationInset) ice_steam_proc("SteamAPI_ISteamUtils_SetOverlayNotificationInset");
    SteamAPI_ISteamUtils_IsSteamInBigPictureMode = (PFN_SteamAPI_ISteamUtils_IsSteamInBigPictureMode) ice_steam_proc("SteamAPI_ISteamUtils_IsSteamInBigPictureMode");
    SteamAPI_ISteamUtils_StartVRDashboard = (PFN_SteamAPI_ISteamUtils_StartVRDashboard) ice_steam_proc("SteamAPI_ISteamUtils_StartVRDashboard");
    SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled = (PFN_SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled) ice_steam_proc("SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled");
    SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled = (PFN_SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled) ice_steam_proc("SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled");
    SteamAPI_ISteamMatchmaking_GetFavoriteGameCount = (PFN_SteamAPI_ISteamMatchmaking_GetFavoriteGameCount) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetFavoriteGameCount");
    SteamAPI_ISteamMatchmaking_GetFavoriteGame = (PFN_SteamAPI_ISteamMatchmaking_GetFavoriteGame) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetFavoriteGame");
    SteamAPI_ISteamMatchmaking_AddFavoriteGame = (PFN_SteamAPI_ISteamMatchmaking_AddFavoriteGame) ice_steam_proc("SteamAPI_ISteamMatchmaking_AddFavoriteGame");
    SteamAPI_ISteamMatchmaking_RemoveFavoriteGame = (PFN_SteamAPI_ISteamMatchmaking_RemoveFavoriteGame) ice_steam_proc("SteamAPI_ISteamMatchmaking_RemoveFavoriteGame");
    SteamAPI_ISteamMatchmaking_RequestLobbyList = (PFN_SteamAPI_ISteamMatchmaking_RequestLobbyList) ice_steam_proc("SteamAPI_ISteamMatchmaking_RequestLobbyList");
    SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter = (PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter) ice_steam_proc("SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter");
    SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter = (PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter) ice_steam_proc("SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter");
    SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter = (PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter) ice_steam_proc("SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter");
    SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable = (PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable) ice_steam_proc("SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable");
    SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter = (PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter) ice_steam_proc("SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter");
    SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter = (PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter) ice_steam_proc("SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter");
    SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter = (PFN_SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter) ice_steam_proc("SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter");
    SteamAPI_ISteamMatchmaking_GetLobbyByIndex = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyByIndex) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyByIndex");
    SteamAPI_ISteamMatchmaking_CreateLobby = (PFN_SteamAPI_ISteamMatchmaking_CreateLobby) ice_steam_proc("SteamAPI_ISteamMatchmaking_CreateLobby");
    SteamAPI_ISteamMatchmaking_JoinLobby = (PFN_SteamAPI_ISteamMatchmaking_JoinLobby) ice_steam_proc("SteamAPI_ISteamMatchmaking_JoinLobby");
    SteamAPI_ISteamMatchmaking_LeaveLobby = (PFN_SteamAPI_ISteamMatchmaking_LeaveLobby) ice_steam_proc("SteamAPI_ISteamMatchmaking_LeaveLobby");
    SteamAPI_ISteamMatchmaking_InviteUserToLobby = (PFN_SteamAPI_ISteamMatchmaking_InviteUserToLobby) ice_steam_proc("SteamAPI_ISteamMatchmaking_InviteUserToLobby");
    SteamAPI_ISteamMatchmaking_GetNumLobbyMembers = (PFN_SteamAPI_ISteamMatchmaking_GetNumLobbyMembers) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetNumLobbyMembers");
    SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex");
    SteamAPI_ISteamMatchmaking_GetLobbyData = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyData) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyData");
    SteamAPI_ISteamMatchmaking_SetLobbyData = (PFN_SteamAPI_ISteamMatchmaking_SetLobbyData) ice_steam_proc("SteamAPI_ISteamMatchmaking_SetLobbyData");
    SteamAPI_ISteamMatchmaking_GetLobbyDataCount = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyDataCount) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyDataCount");
    SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex");
    SteamAPI_ISteamMatchmaking_DeleteLobbyData = (PFN_SteamAPI_ISteamMatchmaking_DeleteLobbyData) ice_steam_proc("SteamAPI_ISteamMatchmaking_DeleteLobbyData");
    SteamAPI_ISteamMatchmaking_GetLobbyMemberData = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyMemberData) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyMemberData");
    SteamAPI_ISteamMatchmaking_SetLobbyMemberData = (PFN_SteamAPI_ISteamMatchmaking_SetLobbyMemberData) ice_steam_proc("SteamAPI_ISteamMatchmaking_SetLobbyMemberData");
    SteamAPI_ISteamMatchmaking_SendLobbyChatMsg = (PFN_SteamAPI_ISteamMatchmaking_SendLobbyChatMsg) ice_steam_proc("SteamAPI_ISteamMatchmaking_SendLobbyChatMsg");
    SteamAPI_ISteamMatchmaking_GetLobbyChatEntry = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyChatEntry) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyChatEntry");
    SteamAPI_ISteamMatchmaking_RequestLobbyData = (PFN_SteamAPI_ISteamMatchmaking_RequestLobbyData) ice_steam_proc("SteamAPI_ISteamMatchmaking_RequestLobbyData");
    SteamAPI_ISteamMatchmaking_SetLobbyGameServer = (PFN_SteamAPI_ISteamMatchmaking_SetLobbyGameServer) ice_steam_proc("SteamAPI_ISteamMatchmaking_SetLobbyGameServer");
    SteamAPI_ISteamMatchmaking_GetLobbyGameServer = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyGameServer) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyGameServer");
    SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit = (PFN_SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit) ice_steam_proc("SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit");
    SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit");
    SteamAPI_ISteamMatchmaking_SetLobbyType = (PFN_SteamAPI_ISteamMatchmaking_SetLobbyType) ice_steam_proc("SteamAPI_ISteamMatchmaking_SetLobbyType");
    SteamAPI_ISteamMatchmaking_SetLobbyJoinable = (PFN_SteamAPI_ISteamMatchmaking_SetLobbyJoinable) ice_steam_proc("SteamAPI_ISteamMatchmaking_SetLobbyJoinable");
    SteamAPI_ISteamMatchmaking_GetLobbyOwner = (PFN_SteamAPI_ISteamMatchmaking_GetLobbyOwner) ice_steam_proc("SteamAPI_ISteamMatchmaking_GetLobbyOwner");
    SteamAPI_ISteamMatchmaking_SetLobbyOwner = (PFN_SteamAPI_ISteamMatchmaking_SetLobbyOwner) ice_steam_proc("SteamAPI_ISteamMatchmaking_SetLobbyOwner");
    SteamAPI_ISteamMatchmaking_SetLinkedLobby = (PFN_SteamAPI_ISteamMatchmaking_SetLinkedLobby) ice_steam_proc("SteamAPI_ISteamMatchmaking_SetLinkedLobby");
    SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded = (PFN_SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded) ice_steam_proc("SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded");
    SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond = (PFN_SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond) ice_steam_proc("SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond");
    SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete = (PFN_SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete) ice_steam_proc("SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete");
    SteamAPI_ISteamMatchmakingPingResponse_ServerResponded = (PFN_SteamAPI_ISteamMatchmakingPingResponse_ServerResponded) ice_steam_proc("SteamAPI_ISteamMatchmakingPingResponse_ServerResponded");
    SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond = (PFN_SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond) ice_steam_proc("SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond");
    SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList = (PFN_SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList) ice_steam_proc("SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList");
    SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond = (PFN_SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond) ice_steam_proc("SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond");
    SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete = (PFN_SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete) ice_steam_proc("SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete");
    SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded = (PFN_SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded) ice_steam_proc("SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded");
    SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond = (PFN_SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond) ice_steam_proc("SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond");
    SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete = (PFN_SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete) ice_steam_proc("SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete");
    SteamAPI_ISteamMatchmakingServers_RequestInternetServerList = (PFN_SteamAPI_ISteamMatchmakingServers_RequestInternetServerList) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_RequestInternetServerList");
    SteamAPI_ISteamMatchmakingServers_RequestLANServerList = (PFN_SteamAPI_ISteamMatchmakingServers_RequestLANServerList) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_RequestLANServerList");
    SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList = (PFN_SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList");
    SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList = (PFN_SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList");
    SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList = (PFN_SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList");
    SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList = (PFN_SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList");
    SteamAPI_ISteamMatchmakingServers_ReleaseRequest = (PFN_SteamAPI_ISteamMatchmakingServers_ReleaseRequest) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_ReleaseRequest");
    SteamAPI_ISteamMatchmakingServers_GetServerDetails = (PFN_SteamAPI_ISteamMatchmakingServers_GetServerDetails) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_GetServerDetails");
    SteamAPI_ISteamMatchmakingServers_CancelQuery = (PFN_SteamAPI_ISteamMatchmakingServers_CancelQuery) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_CancelQuery");
    SteamAPI_ISteamMatchmakingServers_RefreshQuery = (PFN_SteamAPI_ISteamMatchmakingServers_RefreshQuery) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_RefreshQuery");
    SteamAPI_ISteamMatchmakingServers_IsRefreshing = (PFN_SteamAPI_ISteamMatchmakingServers_IsRefreshing) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_IsRefreshing");
    SteamAPI_ISteamMatchmakingServers_GetServerCount = (PFN_SteamAPI_ISteamMatchmakingServers_GetServerCount) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_GetServerCount");
    SteamAPI_ISteamMatchmakingServers_RefreshServer = (PFN_SteamAPI_ISteamMatchmakingServers_RefreshServer) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_RefreshServer");
    SteamAPI_ISteamMatchmakingServers_PingServer = (PFN_SteamAPI_ISteamMatchmakingServers_PingServer) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_PingServer");
    SteamAPI_ISteamMatchmakingServers_PlayerDetails = (PFN_SteamAPI_ISteamMatchmakingServers_PlayerDetails) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_PlayerDetails");
    SteamAPI_ISteamMatchmakingServers_ServerRules = (PFN_SteamAPI_ISteamMatchmakingServers_ServerRules) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_ServerRules");
    SteamAPI_ISteamMatchmakingServers_CancelServerQuery = (PFN_SteamAPI_ISteamMatchmakingServers_CancelServerQuery) ice_steam_proc("SteamAPI_ISteamMatchmakingServers_CancelServerQuery");
    SteamAPI_ISteamRemoteStorage_FileWrite = (PFN_SteamAPI_ISteamRemoteStorage_FileWrite) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileWrite");
    SteamAPI_ISteamRemoteStorage_FileRead = (PFN_SteamAPI_ISteamRemoteStorage_FileRead) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileRead");
    SteamAPI_ISteamRemoteStorage_FileWriteAsync = (PFN_SteamAPI_ISteamRemoteStorage_FileWriteAsync) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileWriteAsync");
    SteamAPI_ISteamRemoteStorage_FileReadAsync = (PFN_SteamAPI_ISteamRemoteStorage_FileReadAsync) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileReadAsync");
    SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete = (PFN_SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete");
    SteamAPI_ISteamRemoteStorage_FileForget = (PFN_SteamAPI_ISteamRemoteStorage_FileForget) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileForget");
    SteamAPI_ISteamRemoteStorage_FileDelete = (PFN_SteamAPI_ISteamRemoteStorage_FileDelete) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileDelete");
    SteamAPI_ISteamRemoteStorage_FileShare = (PFN_SteamAPI_ISteamRemoteStorage_FileShare) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileShare");
    SteamAPI_ISteamRemoteStorage_SetSyncPlatforms = (PFN_SteamAPI_ISteamRemoteStorage_SetSyncPlatforms) ice_steam_proc("SteamAPI_ISteamRemoteStorage_SetSyncPlatforms");
    SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen = (PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen");
    SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk = (PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk");
    SteamAPI_ISteamRemoteStorage_FileWriteStreamClose = (PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamClose) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileWriteStreamClose");
    SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel = (PFN_SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel");
    SteamAPI_ISteamRemoteStorage_FileExists = (PFN_SteamAPI_ISteamRemoteStorage_FileExists) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FileExists");
    SteamAPI_ISteamRemoteStorage_FilePersisted = (PFN_SteamAPI_ISteamRemoteStorage_FilePersisted) ice_steam_proc("SteamAPI_ISteamRemoteStorage_FilePersisted");
    SteamAPI_ISteamRemoteStorage_GetFileSize = (PFN_SteamAPI_ISteamRemoteStorage_GetFileSize) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetFileSize");
    SteamAPI_ISteamRemoteStorage_GetFileTimestamp = (PFN_SteamAPI_ISteamRemoteStorage_GetFileTimestamp) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetFileTimestamp");
    SteamAPI_ISteamRemoteStorage_GetSyncPlatforms = (PFN_SteamAPI_ISteamRemoteStorage_GetSyncPlatforms) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetSyncPlatforms");
    SteamAPI_ISteamRemoteStorage_GetFileCount = (PFN_SteamAPI_ISteamRemoteStorage_GetFileCount) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetFileCount");
    SteamAPI_ISteamRemoteStorage_GetFileNameAndSize = (PFN_SteamAPI_ISteamRemoteStorage_GetFileNameAndSize) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetFileNameAndSize");
    SteamAPI_ISteamRemoteStorage_GetQuota = (PFN_SteamAPI_ISteamRemoteStorage_GetQuota) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetQuota");
    SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount = (PFN_SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount) ice_steam_proc("SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount");
    SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp = (PFN_SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp) ice_steam_proc("SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp");
    SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp = (PFN_SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp) ice_steam_proc("SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp");
    SteamAPI_ISteamRemoteStorage_UGCDownload = (PFN_SteamAPI_ISteamRemoteStorage_UGCDownload) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UGCDownload");
    SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress = (PFN_SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress");
    SteamAPI_ISteamRemoteStorage_GetUGCDetails = (PFN_SteamAPI_ISteamRemoteStorage_GetUGCDetails) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetUGCDetails");
    SteamAPI_ISteamRemoteStorage_UGCRead = (PFN_SteamAPI_ISteamRemoteStorage_UGCRead) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UGCRead");
    SteamAPI_ISteamRemoteStorage_GetCachedUGCCount = (PFN_SteamAPI_ISteamRemoteStorage_GetCachedUGCCount) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetCachedUGCCount");
    SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle = (PFN_SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle");
    SteamAPI_ISteamRemoteStorage_PublishWorkshopFile = (PFN_SteamAPI_ISteamRemoteStorage_PublishWorkshopFile) ice_steam_proc("SteamAPI_ISteamRemoteStorage_PublishWorkshopFile");
    SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest = (PFN_SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest) ice_steam_proc("SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest");
    SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile = (PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile");
    SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile = (PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile");
    SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle = (PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle");
    SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription = (PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription");
    SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility = (PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility");
    SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags = (PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags");
    SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate = (PFN_SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate) ice_steam_proc("SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate");
    SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails = (PFN_SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails");
    SteamAPI_ISteamRemoteStorage_DeletePublishedFile = (PFN_SteamAPI_ISteamRemoteStorage_DeletePublishedFile) ice_steam_proc("SteamAPI_ISteamRemoteStorage_DeletePublishedFile");
    SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles = (PFN_SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles) ice_steam_proc("SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles");
    SteamAPI_ISteamRemoteStorage_SubscribePublishedFile = (PFN_SteamAPI_ISteamRemoteStorage_SubscribePublishedFile) ice_steam_proc("SteamAPI_ISteamRemoteStorage_SubscribePublishedFile");
    SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles = (PFN_SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles) ice_steam_proc("SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles");
    SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile = (PFN_SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile");
    SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription = (PFN_SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription");
    SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails = (PFN_SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails");
    SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote = (PFN_SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote");
    SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails = (PFN_SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails) ice_steam_proc("SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails");
    SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles = (PFN_SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles) ice_steam_proc("SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles");
    SteamAPI_ISteamRemoteStorage_PublishVideo = (PFN_SteamAPI_ISteamRemoteStorage_PublishVideo) ice_steam_proc("SteamAPI_ISteamRemoteStorage_PublishVideo");
    SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction = (PFN_SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction) ice_steam_proc("SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction");
    SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction = (PFN_SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction) ice_steam_proc("SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction");
    SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles = (PFN_SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles) ice_steam_proc("SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles");
    SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation = (PFN_SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation) ice_steam_proc("SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation");
    SteamAPI_ISteamUserStats_RequestCurrentStats = (PFN_SteamAPI_ISteamUserStats_RequestCurrentStats) ice_steam_proc("SteamAPI_ISteamUserStats_RequestCurrentStats");
    SteamAPI_ISteamUserStats_GetStat = (PFN_SteamAPI_ISteamUserStats_GetStat) ice_steam_proc("SteamAPI_ISteamUserStats_GetStat");
    SteamAPI_ISteamUserStats_GetStat0 = (PFN_SteamAPI_ISteamUserStats_GetStat0) ice_steam_proc("SteamAPI_ISteamUserStats_GetStat0");
    SteamAPI_ISteamUserStats_SetStat = (PFN_SteamAPI_ISteamUserStats_SetStat) ice_steam_proc("SteamAPI_ISteamUserStats_SetStat");
    SteamAPI_ISteamUserStats_SetStat0 = (PFN_SteamAPI_ISteamUserStats_SetStat0) ice_steam_proc("SteamAPI_ISteamUserStats_SetStat0");
    SteamAPI_ISteamUserStats_UpdateAvgRateStat = (PFN_SteamAPI_ISteamUserStats_UpdateAvgRateStat) ice_steam_proc("SteamAPI_ISteamUserStats_UpdateAvgRateStat");
    SteamAPI_ISteamUserStats_GetAchievement = (PFN_SteamAPI_ISteamUserStats_GetAchievement) ice_steam_proc("SteamAPI_ISteamUserStats_GetAchievement");
    SteamAPI_ISteamUserStats_SetAchievement = (PFN_SteamAPI_ISteamUserStats_SetAchievement) ice_steam_proc("SteamAPI_ISteamUserStats_SetAchievement");
    SteamAPI_ISteamUserStats_ClearAchievement = (PFN_SteamAPI_ISteamUserStats_ClearAchievement) ice_steam_proc("SteamAPI_ISteamUserStats_ClearAchievement");
    SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime = (PFN_SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime) ice_steam_proc("SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime");
    SteamAPI_ISteamUserStats_StoreStats = (PFN_SteamAPI_ISteamUserStats_StoreStats) ice_steam_proc("SteamAPI_ISteamUserStats_StoreStats");
    SteamAPI_ISteamUserStats_GetAchievementIcon = (PFN_SteamAPI_ISteamUserStats_GetAchievementIcon) ice_steam_proc("SteamAPI_ISteamUserStats_GetAchievementIcon");
    SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute = (PFN_SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute) ice_steam_proc("SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute");
    SteamAPI_ISteamUserStats_IndicateAchievementProgress = (PFN_SteamAPI_ISteamUserStats_IndicateAchievementProgress) ice_steam_proc("SteamAPI_ISteamUserStats_IndicateAchievementProgress");
    SteamAPI_ISteamUserStats_GetNumAchievements = (PFN_SteamAPI_ISteamUserStats_GetNumAchievements) ice_steam_proc("SteamAPI_ISteamUserStats_GetNumAchievements");
    SteamAPI_ISteamUserStats_GetAchievementName = (PFN_SteamAPI_ISteamUserStats_GetAchievementName) ice_steam_proc("SteamAPI_ISteamUserStats_GetAchievementName");
    SteamAPI_ISteamUserStats_RequestUserStats = (PFN_SteamAPI_ISteamUserStats_RequestUserStats) ice_steam_proc("SteamAPI_ISteamUserStats_RequestUserStats");
    SteamAPI_ISteamUserStats_GetUserStat = (PFN_SteamAPI_ISteamUserStats_GetUserStat) ice_steam_proc("SteamAPI_ISteamUserStats_GetUserStat");
    SteamAPI_ISteamUserStats_GetUserStat0 = (PFN_SteamAPI_ISteamUserStats_GetUserStat0) ice_steam_proc("SteamAPI_ISteamUserStats_GetUserStat0");
    SteamAPI_ISteamUserStats_GetUserAchievement = (PFN_SteamAPI_ISteamUserStats_GetUserAchievement) ice_steam_proc("SteamAPI_ISteamUserStats_GetUserAchievement");
    SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime = (PFN_SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime) ice_steam_proc("SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime");
    SteamAPI_ISteamUserStats_ResetAllStats = (PFN_SteamAPI_ISteamUserStats_ResetAllStats) ice_steam_proc("SteamAPI_ISteamUserStats_ResetAllStats");
    SteamAPI_ISteamUserStats_FindOrCreateLeaderboard = (PFN_SteamAPI_ISteamUserStats_FindOrCreateLeaderboard) ice_steam_proc("SteamAPI_ISteamUserStats_FindOrCreateLeaderboard");
    SteamAPI_ISteamUserStats_FindLeaderboard = (PFN_SteamAPI_ISteamUserStats_FindLeaderboard) ice_steam_proc("SteamAPI_ISteamUserStats_FindLeaderboard");
    SteamAPI_ISteamUserStats_GetLeaderboardName = (PFN_SteamAPI_ISteamUserStats_GetLeaderboardName) ice_steam_proc("SteamAPI_ISteamUserStats_GetLeaderboardName");
    SteamAPI_ISteamUserStats_GetLeaderboardEntryCount = (PFN_SteamAPI_ISteamUserStats_GetLeaderboardEntryCount) ice_steam_proc("SteamAPI_ISteamUserStats_GetLeaderboardEntryCount");
    SteamAPI_ISteamUserStats_GetLeaderboardSortMethod = (PFN_SteamAPI_ISteamUserStats_GetLeaderboardSortMethod) ice_steam_proc("SteamAPI_ISteamUserStats_GetLeaderboardSortMethod");
    SteamAPI_ISteamUserStats_GetLeaderboardDisplayType = (PFN_SteamAPI_ISteamUserStats_GetLeaderboardDisplayType) ice_steam_proc("SteamAPI_ISteamUserStats_GetLeaderboardDisplayType");
    SteamAPI_ISteamUserStats_DownloadLeaderboardEntries = (PFN_SteamAPI_ISteamUserStats_DownloadLeaderboardEntries) ice_steam_proc("SteamAPI_ISteamUserStats_DownloadLeaderboardEntries");
    SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers = (PFN_SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers) ice_steam_proc("SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers");
    SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry = (PFN_SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry) ice_steam_proc("SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry");
    SteamAPI_ISteamUserStats_UploadLeaderboardScore = (PFN_SteamAPI_ISteamUserStats_UploadLeaderboardScore) ice_steam_proc("SteamAPI_ISteamUserStats_UploadLeaderboardScore");
    SteamAPI_ISteamUserStats_AttachLeaderboardUGC = (PFN_SteamAPI_ISteamUserStats_AttachLeaderboardUGC) ice_steam_proc("SteamAPI_ISteamUserStats_AttachLeaderboardUGC");
    SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers = (PFN_SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers) ice_steam_proc("SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers");
    SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages = (PFN_SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages) ice_steam_proc("SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages");
    SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo = (PFN_SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo) ice_steam_proc("SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo");
    SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo = (PFN_SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo) ice_steam_proc("SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo");
    SteamAPI_ISteamUserStats_GetAchievementAchievedPercent = (PFN_SteamAPI_ISteamUserStats_GetAchievementAchievedPercent) ice_steam_proc("SteamAPI_ISteamUserStats_GetAchievementAchievedPercent");
    SteamAPI_ISteamUserStats_RequestGlobalStats = (PFN_SteamAPI_ISteamUserStats_RequestGlobalStats) ice_steam_proc("SteamAPI_ISteamUserStats_RequestGlobalStats");
    SteamAPI_ISteamUserStats_GetGlobalStat = (PFN_SteamAPI_ISteamUserStats_GetGlobalStat) ice_steam_proc("SteamAPI_ISteamUserStats_GetGlobalStat");
    SteamAPI_ISteamUserStats_GetGlobalStat0 = (PFN_SteamAPI_ISteamUserStats_GetGlobalStat0) ice_steam_proc("SteamAPI_ISteamUserStats_GetGlobalStat0");
    SteamAPI_ISteamUserStats_GetGlobalStatHistory = (PFN_SteamAPI_ISteamUserStats_GetGlobalStatHistory) ice_steam_proc("SteamAPI_ISteamUserStats_GetGlobalStatHistory");
    SteamAPI_ISteamUserStats_GetGlobalStatHistory0 = (PFN_SteamAPI_ISteamUserStats_GetGlobalStatHistory0) ice_steam_proc("SteamAPI_ISteamUserStats_GetGlobalStatHistory0");
    SteamAPI_ISteamApps_BIsSubscribed = (PFN_SteamAPI_ISteamApps_BIsSubscribed) ice_steam_proc("SteamAPI_ISteamApps_BIsSubscribed");
    SteamAPI_ISteamApps_BIsLowViolence = (PFN_SteamAPI_ISteamApps_BIsLowViolence) ice_steam_proc("SteamAPI_ISteamApps_BIsLowViolence");
    SteamAPI_ISteamApps_BIsCybercafe = (PFN_SteamAPI_ISteamApps_BIsCybercafe) ice_steam_proc("SteamAPI_ISteamApps_BIsCybercafe");
    SteamAPI_ISteamApps_BIsVACBanned = (PFN_SteamAPI_ISteamApps_BIsVACBanned) ice_steam_proc("SteamAPI_ISteamApps_BIsVACBanned");
    SteamAPI_ISteamApps_GetCurrentGameLanguage = (PFN_SteamAPI_ISteamApps_GetCurrentGameLanguage) ice_steam_proc("SteamAPI_ISteamApps_GetCurrentGameLanguage");
    SteamAPI_ISteamApps_GetAvailableGameLanguages = (PFN_SteamAPI_ISteamApps_GetAvailableGameLanguages) ice_steam_proc("SteamAPI_ISteamApps_GetAvailableGameLanguages");
    SteamAPI_ISteamApps_BIsSubscribedApp = (PFN_SteamAPI_ISteamApps_BIsSubscribedApp) ice_steam_proc("SteamAPI_ISteamApps_BIsSubscribedApp");
    SteamAPI_ISteamApps_BIsDlcInstalled = (PFN_SteamAPI_ISteamApps_BIsDlcInstalled) ice_steam_proc("SteamAPI_ISteamApps_BIsDlcInstalled");
    SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime = (PFN_SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime) ice_steam_proc("SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime");
    SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend = (PFN_SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend) ice_steam_proc("SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend");
    SteamAPI_ISteamApps_GetDLCCount = (PFN_SteamAPI_ISteamApps_GetDLCCount) ice_steam_proc("SteamAPI_ISteamApps_GetDLCCount");
    SteamAPI_ISteamApps_BGetDLCDataByIndex = (PFN_SteamAPI_ISteamApps_BGetDLCDataByIndex) ice_steam_proc("SteamAPI_ISteamApps_BGetDLCDataByIndex");
    SteamAPI_ISteamApps_InstallDLC = (PFN_SteamAPI_ISteamApps_InstallDLC) ice_steam_proc("SteamAPI_ISteamApps_InstallDLC");
    SteamAPI_ISteamApps_UninstallDLC = (PFN_SteamAPI_ISteamApps_UninstallDLC) ice_steam_proc("SteamAPI_ISteamApps_UninstallDLC");
    SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey = (PFN_SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey) ice_steam_proc("SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey");
    SteamAPI_ISteamApps_GetCurrentBetaName = (PFN_SteamAPI_ISteamApps_GetCurrentBetaName) ice_steam_proc("SteamAPI_ISteamApps_GetCurrentBetaName");
    SteamAPI_ISteamApps_MarkContentCorrupt = (PFN_SteamAPI_ISteamApps_MarkContentCorrupt) ice_steam_proc("SteamAPI_ISteamApps_MarkContentCorrupt");
    SteamAPI_ISteamApps_GetInstalledDepots = (PFN_SteamAPI_ISteamApps_GetInstalledDepots) ice_steam_proc("SteamAPI_ISteamApps_GetInstalledDepots");
    SteamAPI_ISteamApps_GetAppInstallDir = (PFN_SteamAPI_ISteamApps_GetAppInstallDir) ice_steam_proc("SteamAPI_ISteamApps_GetAppInstallDir");
    SteamAPI_ISteamApps_BIsAppInstalled = (PFN_SteamAPI_ISteamApps_BIsAppInstalled) ice_steam_proc("SteamAPI_ISteamApps_BIsAppInstalled");
    SteamAPI_ISteamApps_GetAppOwner = (PFN_SteamAPI_ISteamApps_GetAppOwner) ice_steam_proc("SteamAPI_ISteamApps_GetAppOwner");
    SteamAPI_ISteamApps_GetLaunchQueryParam = (PFN_SteamAPI_ISteamApps_GetLaunchQueryParam) ice_steam_proc("SteamAPI_ISteamApps_GetLaunchQueryParam");
    SteamAPI_ISteamApps_GetDlcDownloadProgress = (PFN_SteamAPI_ISteamApps_GetDlcDownloadProgress) ice_steam_proc("SteamAPI_ISteamApps_GetDlcDownloadProgress");
    SteamAPI_ISteamApps_GetAppBuildId = (PFN_SteamAPI_ISteamApps_GetAppBuildId) ice_steam_proc("SteamAPI_ISteamApps_GetAppBuildId");
    SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys = (PFN_SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys) ice_steam_proc("SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys");
    SteamAPI_ISteamApps_GetFileDetails = (PFN_SteamAPI_ISteamApps_GetFileDetails) ice_steam_proc("SteamAPI_ISteamApps_GetFileDetails");
    SteamAPI_ISteamNetworking_SendP2PPacket = (PFN_SteamAPI_ISteamNetworking_SendP2PPacket) ice_steam_proc("SteamAPI_ISteamNetworking_SendP2PPacket");
    SteamAPI_ISteamNetworking_IsP2PPacketAvailable = (PFN_SteamAPI_ISteamNetworking_IsP2PPacketAvailable) ice_steam_proc("SteamAPI_ISteamNetworking_IsP2PPacketAvailable");
    SteamAPI_ISteamNetworking_ReadP2PPacket = (PFN_SteamAPI_ISteamNetworking_ReadP2PPacket) ice_steam_proc("SteamAPI_ISteamNetworking_ReadP2PPacket");
    SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser = (PFN_SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser) ice_steam_proc("SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser");
    SteamAPI_ISteamNetworking_CloseP2PSessionWithUser = (PFN_SteamAPI_ISteamNetworking_CloseP2PSessionWithUser) ice_steam_proc("SteamAPI_ISteamNetworking_CloseP2PSessionWithUser");
    SteamAPI_ISteamNetworking_CloseP2PChannelWithUser = (PFN_SteamAPI_ISteamNetworking_CloseP2PChannelWithUser) ice_steam_proc("SteamAPI_ISteamNetworking_CloseP2PChannelWithUser");
    SteamAPI_ISteamNetworking_GetP2PSessionState = (PFN_SteamAPI_ISteamNetworking_GetP2PSessionState) ice_steam_proc("SteamAPI_ISteamNetworking_GetP2PSessionState");
    SteamAPI_ISteamNetworking_AllowP2PPacketRelay = (PFN_SteamAPI_ISteamNetworking_AllowP2PPacketRelay) ice_steam_proc("SteamAPI_ISteamNetworking_AllowP2PPacketRelay");
    SteamAPI_ISteamNetworking_CreateListenSocket = (PFN_SteamAPI_ISteamNetworking_CreateListenSocket) ice_steam_proc("SteamAPI_ISteamNetworking_CreateListenSocket");
    SteamAPI_ISteamNetworking_CreateP2PConnectionSocket = (PFN_SteamAPI_ISteamNetworking_CreateP2PConnectionSocket) ice_steam_proc("SteamAPI_ISteamNetworking_CreateP2PConnectionSocket");
    SteamAPI_ISteamNetworking_CreateConnectionSocket = (PFN_SteamAPI_ISteamNetworking_CreateConnectionSocket) ice_steam_proc("SteamAPI_ISteamNetworking_CreateConnectionSocket");
    SteamAPI_ISteamNetworking_DestroySocket = (PFN_SteamAPI_ISteamNetworking_DestroySocket) ice_steam_proc("SteamAPI_ISteamNetworking_DestroySocket");
    SteamAPI_ISteamNetworking_DestroyListenSocket = (PFN_SteamAPI_ISteamNetworking_DestroyListenSocket) ice_steam_proc("SteamAPI_ISteamNetworking_DestroyListenSocket");
    SteamAPI_ISteamNetworking_SendDataOnSocket = (PFN_SteamAPI_ISteamNetworking_SendDataOnSocket) ice_steam_proc("SteamAPI_ISteamNetworking_SendDataOnSocket");
    SteamAPI_ISteamNetworking_IsDataAvailableOnSocket = (PFN_SteamAPI_ISteamNetworking_IsDataAvailableOnSocket) ice_steam_proc("SteamAPI_ISteamNetworking_IsDataAvailableOnSocket");
    SteamAPI_ISteamNetworking_RetrieveDataFromSocket = (PFN_SteamAPI_ISteamNetworking_RetrieveDataFromSocket) ice_steam_proc("SteamAPI_ISteamNetworking_RetrieveDataFromSocket");
    SteamAPI_ISteamNetworking_IsDataAvailable = (PFN_SteamAPI_ISteamNetworking_IsDataAvailable) ice_steam_proc("SteamAPI_ISteamNetworking_IsDataAvailable");
    SteamAPI_ISteamNetworking_RetrieveData = (PFN_SteamAPI_ISteamNetworking_RetrieveData) ice_steam_proc("SteamAPI_ISteamNetworking_RetrieveData");
    SteamAPI_ISteamNetworking_GetSocketInfo = (PFN_SteamAPI_ISteamNetworking_GetSocketInfo) ice_steam_proc("SteamAPI_ISteamNetworking_GetSocketInfo");
    SteamAPI_ISteamNetworking_GetListenSocketInfo = (PFN_SteamAPI_ISteamNetworking_GetListenSocketInfo) ice_steam_proc("SteamAPI_ISteamNetworking_GetListenSocketInfo");
    SteamAPI_ISteamNetworking_GetSocketConnectionType = (PFN_SteamAPI_ISteamNetworking_GetSocketConnectionType) ice_steam_proc("SteamAPI_ISteamNetworking_GetSocketConnectionType");
    SteamAPI_ISteamNetworking_GetMaxPacketSize = (PFN_SteamAPI_ISteamNetworking_GetMaxPacketSize) ice_steam_proc("SteamAPI_ISteamNetworking_GetMaxPacketSize");
    SteamAPI_ISteamScreenshots_WriteScreenshot = (PFN_SteamAPI_ISteamScreenshots_WriteScreenshot) ice_steam_proc("SteamAPI_ISteamScreenshots_WriteScreenshot");
    SteamAPI_ISteamScreenshots_AddScreenshotToLibrary = (PFN_SteamAPI_ISteamScreenshots_AddScreenshotToLibrary) ice_steam_proc("SteamAPI_ISteamScreenshots_AddScreenshotToLibrary");
    SteamAPI_ISteamScreenshots_TriggerScreenshot = (PFN_SteamAPI_ISteamScreenshots_TriggerScreenshot) ice_steam_proc("SteamAPI_ISteamScreenshots_TriggerScreenshot");
    SteamAPI_ISteamScreenshots_HookScreenshots = (PFN_SteamAPI_ISteamScreenshots_HookScreenshots) ice_steam_proc("SteamAPI_ISteamScreenshots_HookScreenshots");
    SteamAPI_ISteamScreenshots_SetLocation = (PFN_SteamAPI_ISteamScreenshots_SetLocation) ice_steam_proc("SteamAPI_ISteamScreenshots_SetLocation");
    SteamAPI_ISteamScreenshots_TagUser = (PFN_SteamAPI_ISteamScreenshots_TagUser) ice_steam_proc("SteamAPI_ISteamScreenshots_TagUser");
    SteamAPI_ISteamScreenshots_TagPublishedFile = (PFN_SteamAPI_ISteamScreenshots_TagPublishedFile) ice_steam_proc("SteamAPI_ISteamScreenshots_TagPublishedFile");
    SteamAPI_ISteamScreenshots_IsScreenshotsHooked = (PFN_SteamAPI_ISteamScreenshots_IsScreenshotsHooked) ice_steam_proc("SteamAPI_ISteamScreenshots_IsScreenshotsHooked");
    SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary = (PFN_SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary) ice_steam_proc("SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary");
    SteamAPI_ISteamMusic_BIsEnabled = (PFN_SteamAPI_ISteamMusic_BIsEnabled) ice_steam_proc("SteamAPI_ISteamMusic_BIsEnabled");
    SteamAPI_ISteamMusic_BIsPlaying = (PFN_SteamAPI_ISteamMusic_BIsPlaying) ice_steam_proc("SteamAPI_ISteamMusic_BIsPlaying");
    SteamAPI_ISteamMusic_GetPlaybackStatus = (PFN_SteamAPI_ISteamMusic_GetPlaybackStatus) ice_steam_proc("SteamAPI_ISteamMusic_GetPlaybackStatus");
    SteamAPI_ISteamMusic_Play = (PFN_SteamAPI_ISteamMusic_Play) ice_steam_proc("SteamAPI_ISteamMusic_Play");
    SteamAPI_ISteamMusic_Pause = (PFN_SteamAPI_ISteamMusic_Pause) ice_steam_proc("SteamAPI_ISteamMusic_Pause");
    SteamAPI_ISteamMusic_PlayPrevious = (PFN_SteamAPI_ISteamMusic_PlayPrevious) ice_steam_proc("SteamAPI_ISteamMusic_PlayPrevious");
    SteamAPI_ISteamMusic_PlayNext = (PFN_SteamAPI_ISteamMusic_PlayNext) ice_steam_proc("SteamAPI_ISteamMusic_PlayNext");
    SteamAPI_ISteamMusic_SetVolume = (PFN_SteamAPI_ISteamMusic_SetVolume) ice_steam_proc("SteamAPI_ISteamMusic_SetVolume");
    SteamAPI_ISteamMusic_GetVolume = (PFN_SteamAPI_ISteamMusic_GetVolume) ice_steam_proc("SteamAPI_ISteamMusic_GetVolume");
    SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote = (PFN_SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote) ice_steam_proc("SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote");
    SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote = (PFN_SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote) ice_steam_proc("SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote");
    SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote = (PFN_SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote) ice_steam_proc("SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote");
    SteamAPI_ISteamMusicRemote_BActivationSuccess = (PFN_SteamAPI_ISteamMusicRemote_BActivationSuccess) ice_steam_proc("SteamAPI_ISteamMusicRemote_BActivationSuccess");
    SteamAPI_ISteamMusicRemote_SetDisplayName = (PFN_SteamAPI_ISteamMusicRemote_SetDisplayName) ice_steam_proc("SteamAPI_ISteamMusicRemote_SetDisplayName");
    SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64 = (PFN_SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64) ice_steam_proc("SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64");
    SteamAPI_ISteamMusicRemote_EnablePlayPrevious = (PFN_SteamAPI_ISteamMusicRemote_EnablePlayPrevious) ice_steam_proc("SteamAPI_ISteamMusicRemote_EnablePlayPrevious");
    SteamAPI_ISteamMusicRemote_EnablePlayNext = (PFN_SteamAPI_ISteamMusicRemote_EnablePlayNext) ice_steam_proc("SteamAPI_ISteamMusicRemote_EnablePlayNext");
    SteamAPI_ISteamMusicRemote_EnableShuffled = (PFN_SteamAPI_ISteamMusicRemote_EnableShuffled) ice_steam_proc("SteamAPI_ISteamMusicRemote_EnableShuffled");
    SteamAPI_ISteamMusicRemote_EnableLooped = (PFN_SteamAPI_ISteamMusicRemote_EnableLooped) ice_steam_proc("SteamAPI_ISteamMusicRemote_EnableLooped");
    SteamAPI_ISteamMusicRemote_EnableQueue = (PFN_SteamAPI_ISteamMusicRemote_EnableQueue) ice_steam_proc("SteamAPI_ISteamMusicRemote_EnableQueue");
    SteamAPI_ISteamMusicRemote_EnablePlaylists = (PFN_SteamAPI_ISteamMusicRemote_EnablePlaylists) ice_steam_proc("SteamAPI_ISteamMusicRemote_EnablePlaylists");
    SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus = (PFN_SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus) ice_steam_proc("SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus");
    SteamAPI_ISteamMusicRemote_UpdateShuffled = (PFN_SteamAPI_ISteamMusicRemote_UpdateShuffled) ice_steam_proc("SteamAPI_ISteamMusicRemote_UpdateShuffled");
    SteamAPI_ISteamMusicRemote_UpdateLooped = (PFN_SteamAPI_ISteamMusicRemote_UpdateLooped) ice_steam_proc("SteamAPI_ISteamMusicRemote_UpdateLooped");
    SteamAPI_ISteamMusicRemote_UpdateVolume = (PFN_SteamAPI_ISteamMusicRemote_UpdateVolume) ice_steam_proc("SteamAPI_ISteamMusicRemote_UpdateVolume");
    SteamAPI_ISteamMusicRemote_CurrentEntryWillChange = (PFN_SteamAPI_ISteamMusicRemote_CurrentEntryWillChange) ice_steam_proc("SteamAPI_ISteamMusicRemote_CurrentEntryWillChange");
    SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable = (PFN_SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable) ice_steam_proc("SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable");
    SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText = (PFN_SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText) ice_steam_proc("SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText");
    SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds = (PFN_SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds) ice_steam_proc("SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds");
    SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt = (PFN_SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt) ice_steam_proc("SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt");
    SteamAPI_ISteamMusicRemote_CurrentEntryDidChange = (PFN_SteamAPI_ISteamMusicRemote_CurrentEntryDidChange) ice_steam_proc("SteamAPI_ISteamMusicRemote_CurrentEntryDidChange");
    SteamAPI_ISteamMusicRemote_QueueWillChange = (PFN_SteamAPI_ISteamMusicRemote_QueueWillChange) ice_steam_proc("SteamAPI_ISteamMusicRemote_QueueWillChange");
    SteamAPI_ISteamMusicRemote_ResetQueueEntries = (PFN_SteamAPI_ISteamMusicRemote_ResetQueueEntries) ice_steam_proc("SteamAPI_ISteamMusicRemote_ResetQueueEntries");
    SteamAPI_ISteamMusicRemote_SetQueueEntry = (PFN_SteamAPI_ISteamMusicRemote_SetQueueEntry) ice_steam_proc("SteamAPI_ISteamMusicRemote_SetQueueEntry");
    SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry = (PFN_SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry) ice_steam_proc("SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry");
    SteamAPI_ISteamMusicRemote_QueueDidChange = (PFN_SteamAPI_ISteamMusicRemote_QueueDidChange) ice_steam_proc("SteamAPI_ISteamMusicRemote_QueueDidChange");
    SteamAPI_ISteamMusicRemote_PlaylistWillChange = (PFN_SteamAPI_ISteamMusicRemote_PlaylistWillChange) ice_steam_proc("SteamAPI_ISteamMusicRemote_PlaylistWillChange");
    SteamAPI_ISteamMusicRemote_ResetPlaylistEntries = (PFN_SteamAPI_ISteamMusicRemote_ResetPlaylistEntries) ice_steam_proc("SteamAPI_ISteamMusicRemote_ResetPlaylistEntries");
    SteamAPI_ISteamMusicRemote_SetPlaylistEntry = (PFN_SteamAPI_ISteamMusicRemote_SetPlaylistEntry) ice_steam_proc("SteamAPI_ISteamMusicRemote_SetPlaylistEntry");
    SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry = (PFN_SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry) ice_steam_proc("SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry");
    SteamAPI_ISteamMusicRemote_PlaylistDidChange = (PFN_SteamAPI_ISteamMusicRemote_PlaylistDidChange) ice_steam_proc("SteamAPI_ISteamMusicRemote_PlaylistDidChange");
    SteamAPI_ISteamHTTP_CreateHTTPRequest = (PFN_SteamAPI_ISteamHTTP_CreateHTTPRequest) ice_steam_proc("SteamAPI_ISteamHTTP_CreateHTTPRequest");
    SteamAPI_ISteamHTTP_SetHTTPRequestContextValue = (PFN_SteamAPI_ISteamHTTP_SetHTTPRequestContextValue) ice_steam_proc("SteamAPI_ISteamHTTP_SetHTTPRequestContextValue");
    SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout = (PFN_SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout) ice_steam_proc("SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout");
    SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue = (PFN_SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue) ice_steam_proc("SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue");
    SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter = (PFN_SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter) ice_steam_proc("SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter");
    SteamAPI_ISteamHTTP_SendHTTPRequest = (PFN_SteamAPI_ISteamHTTP_SendHTTPRequest) ice_steam_proc("SteamAPI_ISteamHTTP_SendHTTPRequest");
    SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse = (PFN_SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse) ice_steam_proc("SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse");
    SteamAPI_ISteamHTTP_DeferHTTPRequest = (PFN_SteamAPI_ISteamHTTP_DeferHTTPRequest) ice_steam_proc("SteamAPI_ISteamHTTP_DeferHTTPRequest");
    SteamAPI_ISteamHTTP_PrioritizeHTTPRequest = (PFN_SteamAPI_ISteamHTTP_PrioritizeHTTPRequest) ice_steam_proc("SteamAPI_ISteamHTTP_PrioritizeHTTPRequest");
    SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize = (PFN_SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize) ice_steam_proc("SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize");
    SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue = (PFN_SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue) ice_steam_proc("SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue");
    SteamAPI_ISteamHTTP_GetHTTPResponseBodySize = (PFN_SteamAPI_ISteamHTTP_GetHTTPResponseBodySize) ice_steam_proc("SteamAPI_ISteamHTTP_GetHTTPResponseBodySize");
    SteamAPI_ISteamHTTP_GetHTTPResponseBodyData = (PFN_SteamAPI_ISteamHTTP_GetHTTPResponseBodyData) ice_steam_proc("SteamAPI_ISteamHTTP_GetHTTPResponseBodyData");
    SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData = (PFN_SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData) ice_steam_proc("SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData");
    SteamAPI_ISteamHTTP_ReleaseHTTPRequest = (PFN_SteamAPI_ISteamHTTP_ReleaseHTTPRequest) ice_steam_proc("SteamAPI_ISteamHTTP_ReleaseHTTPRequest");
    SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct = (PFN_SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct) ice_steam_proc("SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct");
    SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody = (PFN_SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody) ice_steam_proc("SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody");
    SteamAPI_ISteamHTTP_CreateCookieContainer = (PFN_SteamAPI_ISteamHTTP_CreateCookieContainer) ice_steam_proc("SteamAPI_ISteamHTTP_CreateCookieContainer");
    SteamAPI_ISteamHTTP_ReleaseCookieContainer = (PFN_SteamAPI_ISteamHTTP_ReleaseCookieContainer) ice_steam_proc("SteamAPI_ISteamHTTP_ReleaseCookieContainer");
    SteamAPI_ISteamHTTP_SetCookie = (PFN_SteamAPI_ISteamHTTP_SetCookie) ice_steam_proc("SteamAPI_ISteamHTTP_SetCookie");
    SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer = (PFN_SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer) ice_steam_proc("SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer");
    SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo = (PFN_SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo) ice_steam_proc("SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo");
    SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate = (PFN_SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate) ice_steam_proc("SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate");
    SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS = (PFN_SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS) ice_steam_proc("SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS");
    SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut = (PFN_SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut) ice_steam_proc("SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut");
    SteamAPI_ISteamController_Init = (PFN_SteamAPI_ISteamController_Init) ice_steam_proc("SteamAPI_ISteamController_Init");
    SteamAPI_ISteamController_Shutdown = (PFN_SteamAPI_ISteamController_Shutdown) ice_steam_proc("SteamAPI_ISteamController_Shutdown");
    SteamAPI_ISteamController_RunFrame = (PFN_SteamAPI_ISteamController_RunFrame) ice_steam_proc("SteamAPI_ISteamController_RunFrame");
    SteamAPI_ISteamController_GetConnectedControllers = (PFN_SteamAPI_ISteamController_GetConnectedControllers) ice_steam_proc("SteamAPI_ISteamController_GetConnectedControllers");
    SteamAPI_ISteamController_ShowBindingPanel = (PFN_SteamAPI_ISteamController_ShowBindingPanel) ice_steam_proc("SteamAPI_ISteamController_ShowBindingPanel");
    SteamAPI_ISteamController_GetActionSetHandle = (PFN_SteamAPI_ISteamController_GetActionSetHandle) ice_steam_proc("SteamAPI_ISteamController_GetActionSetHandle");
    SteamAPI_ISteamController_ActivateActionSet = (PFN_SteamAPI_ISteamController_ActivateActionSet) ice_steam_proc("SteamAPI_ISteamController_ActivateActionSet");
    SteamAPI_ISteamController_GetCurrentActionSet = (PFN_SteamAPI_ISteamController_GetCurrentActionSet) ice_steam_proc("SteamAPI_ISteamController_GetCurrentActionSet");
    SteamAPI_ISteamController_ActivateActionSetLayer = (PFN_SteamAPI_ISteamController_ActivateActionSetLayer) ice_steam_proc("SteamAPI_ISteamController_ActivateActionSetLayer");
    SteamAPI_ISteamController_DeactivateActionSetLayer = (PFN_SteamAPI_ISteamController_DeactivateActionSetLayer) ice_steam_proc("SteamAPI_ISteamController_DeactivateActionSetLayer");
    SteamAPI_ISteamController_DeactivateAllActionSetLayers = (PFN_SteamAPI_ISteamController_DeactivateAllActionSetLayers) ice_steam_proc("SteamAPI_ISteamController_DeactivateAllActionSetLayers");
    SteamAPI_ISteamController_GetActiveActionSetLayers = (PFN_SteamAPI_ISteamController_GetActiveActionSetLayers) ice_steam_proc("SteamAPI_ISteamController_GetActiveActionSetLayers");
    SteamAPI_ISteamController_GetDigitalActionHandle = (PFN_SteamAPI_ISteamController_GetDigitalActionHandle) ice_steam_proc("SteamAPI_ISteamController_GetDigitalActionHandle");
    SteamAPI_ISteamController_GetDigitalActionData = (PFN_SteamAPI_ISteamController_GetDigitalActionData) ice_steam_proc("SteamAPI_ISteamController_GetDigitalActionData");
    SteamAPI_ISteamController_GetDigitalActionOrigins = (PFN_SteamAPI_ISteamController_GetDigitalActionOrigins) ice_steam_proc("SteamAPI_ISteamController_GetDigitalActionOrigins");
    SteamAPI_ISteamController_GetAnalogActionHandle = (PFN_SteamAPI_ISteamController_GetAnalogActionHandle) ice_steam_proc("SteamAPI_ISteamController_GetAnalogActionHandle");
    SteamAPI_ISteamController_GetAnalogActionData = (PFN_SteamAPI_ISteamController_GetAnalogActionData) ice_steam_proc("SteamAPI_ISteamController_GetAnalogActionData");
    SteamAPI_ISteamController_GetAnalogActionOrigins = (PFN_SteamAPI_ISteamController_GetAnalogActionOrigins) ice_steam_proc("SteamAPI_ISteamController_GetAnalogActionOrigins");
    SteamAPI_ISteamController_StopAnalogActionMomentum = (PFN_SteamAPI_ISteamController_StopAnalogActionMomentum) ice_steam_proc("SteamAPI_ISteamController_StopAnalogActionMomentum");
    SteamAPI_ISteamController_TriggerHapticPulse = (PFN_SteamAPI_ISteamController_TriggerHapticPulse) ice_steam_proc("SteamAPI_ISteamController_TriggerHapticPulse");
    SteamAPI_ISteamController_TriggerRepeatedHapticPulse = (PFN_SteamAPI_ISteamController_TriggerRepeatedHapticPulse) ice_steam_proc("SteamAPI_ISteamController_TriggerRepeatedHapticPulse");
    SteamAPI_ISteamController_TriggerVibration = (PFN_SteamAPI_ISteamController_TriggerVibration) ice_steam_proc("SteamAPI_ISteamController_TriggerVibration");
    SteamAPI_ISteamController_SetLEDColor = (PFN_SteamAPI_ISteamController_SetLEDColor) ice_steam_proc("SteamAPI_ISteamController_SetLEDColor");
    SteamAPI_ISteamController_GetGamepadIndexForController = (PFN_SteamAPI_ISteamController_GetGamepadIndexForController) ice_steam_proc("SteamAPI_ISteamController_GetGamepadIndexForController");
    SteamAPI_ISteamController_GetControllerForGamepadIndex = (PFN_SteamAPI_ISteamController_GetControllerForGamepadIndex) ice_steam_proc("SteamAPI_ISteamController_GetControllerForGamepadIndex");
    SteamAPI_ISteamController_GetMotionData = (PFN_SteamAPI_ISteamController_GetMotionData) ice_steam_proc("SteamAPI_ISteamController_GetMotionData");
    SteamAPI_ISteamController_ShowDigitalActionOrigins = (PFN_SteamAPI_ISteamController_ShowDigitalActionOrigins) ice_steam_proc("SteamAPI_ISteamController_ShowDigitalActionOrigins");
    SteamAPI_ISteamController_ShowAnalogActionOrigins = (PFN_SteamAPI_ISteamController_ShowAnalogActionOrigins) ice_steam_proc("SteamAPI_ISteamController_ShowAnalogActionOrigins");
    SteamAPI_ISteamController_GetStringForActionOrigin = (PFN_SteamAPI_ISteamController_GetStringForActionOrigin) ice_steam_proc("SteamAPI_ISteamController_GetStringForActionOrigin");
    SteamAPI_ISteamController_GetGlyphForActionOrigin = (PFN_SteamAPI_ISteamController_GetGlyphForActionOrigin) ice_steam_proc("SteamAPI_ISteamController_GetGlyphForActionOrigin");
    SteamAPI_ISteamController_GetInputTypeForHandle = (PFN_SteamAPI_ISteamController_GetInputTypeForHandle) ice_steam_proc("SteamAPI_ISteamController_GetInputTypeForHandle");
    SteamAPI_ISteamUGC_CreateQueryUserUGCRequest = (PFN_SteamAPI_ISteamUGC_CreateQueryUserUGCRequest) ice_steam_proc("SteamAPI_ISteamUGC_CreateQueryUserUGCRequest");
    SteamAPI_ISteamUGC_CreateQueryAllUGCRequest = (PFN_SteamAPI_ISteamUGC_CreateQueryAllUGCRequest) ice_steam_proc("SteamAPI_ISteamUGC_CreateQueryAllUGCRequest");
    SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest = (PFN_SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest) ice_steam_proc("SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest");
    SteamAPI_ISteamUGC_SendQueryUGCRequest = (PFN_SteamAPI_ISteamUGC_SendQueryUGCRequest) ice_steam_proc("SteamAPI_ISteamUGC_SendQueryUGCRequest");
    SteamAPI_ISteamUGC_GetQueryUGCResult = (PFN_SteamAPI_ISteamUGC_GetQueryUGCResult) ice_steam_proc("SteamAPI_ISteamUGC_GetQueryUGCResult");
    SteamAPI_ISteamUGC_GetQueryUGCPreviewURL = (PFN_SteamAPI_ISteamUGC_GetQueryUGCPreviewURL) ice_steam_proc("SteamAPI_ISteamUGC_GetQueryUGCPreviewURL");
    SteamAPI_ISteamUGC_GetQueryUGCMetadata = (PFN_SteamAPI_ISteamUGC_GetQueryUGCMetadata) ice_steam_proc("SteamAPI_ISteamUGC_GetQueryUGCMetadata");
    SteamAPI_ISteamUGC_GetQueryUGCChildren = (PFN_SteamAPI_ISteamUGC_GetQueryUGCChildren) ice_steam_proc("SteamAPI_ISteamUGC_GetQueryUGCChildren");
    SteamAPI_ISteamUGC_GetQueryUGCStatistic = (PFN_SteamAPI_ISteamUGC_GetQueryUGCStatistic) ice_steam_proc("SteamAPI_ISteamUGC_GetQueryUGCStatistic");
    SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews = (PFN_SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews) ice_steam_proc("SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews");
    SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview = (PFN_SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview) ice_steam_proc("SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview");
    SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags = (PFN_SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags) ice_steam_proc("SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags");
    SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag = (PFN_SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag) ice_steam_proc("SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag");
    SteamAPI_ISteamUGC_ReleaseQueryUGCRequest = (PFN_SteamAPI_ISteamUGC_ReleaseQueryUGCRequest) ice_steam_proc("SteamAPI_ISteamUGC_ReleaseQueryUGCRequest");
    SteamAPI_ISteamUGC_AddRequiredTag = (PFN_SteamAPI_ISteamUGC_AddRequiredTag) ice_steam_proc("SteamAPI_ISteamUGC_AddRequiredTag");
    SteamAPI_ISteamUGC_AddExcludedTag = (PFN_SteamAPI_ISteamUGC_AddExcludedTag) ice_steam_proc("SteamAPI_ISteamUGC_AddExcludedTag");
    SteamAPI_ISteamUGC_SetReturnOnlyIDs = (PFN_SteamAPI_ISteamUGC_SetReturnOnlyIDs) ice_steam_proc("SteamAPI_ISteamUGC_SetReturnOnlyIDs");
    SteamAPI_ISteamUGC_SetReturnKeyValueTags = (PFN_SteamAPI_ISteamUGC_SetReturnKeyValueTags) ice_steam_proc("SteamAPI_ISteamUGC_SetReturnKeyValueTags");
    SteamAPI_ISteamUGC_SetReturnLongDescription = (PFN_SteamAPI_ISteamUGC_SetReturnLongDescription) ice_steam_proc("SteamAPI_ISteamUGC_SetReturnLongDescription");
    SteamAPI_ISteamUGC_SetReturnMetadata = (PFN_SteamAPI_ISteamUGC_SetReturnMetadata) ice_steam_proc("SteamAPI_ISteamUGC_SetReturnMetadata");
    SteamAPI_ISteamUGC_SetReturnChildren = (PFN_SteamAPI_ISteamUGC_SetReturnChildren) ice_steam_proc("SteamAPI_ISteamUGC_SetReturnChildren");
    SteamAPI_ISteamUGC_SetReturnAdditionalPreviews = (PFN_SteamAPI_ISteamUGC_SetReturnAdditionalPreviews) ice_steam_proc("SteamAPI_ISteamUGC_SetReturnAdditionalPreviews");
    SteamAPI_ISteamUGC_SetReturnTotalOnly = (PFN_SteamAPI_ISteamUGC_SetReturnTotalOnly) ice_steam_proc("SteamAPI_ISteamUGC_SetReturnTotalOnly");
    SteamAPI_ISteamUGC_SetReturnPlaytimeStats = (PFN_SteamAPI_ISteamUGC_SetReturnPlaytimeStats) ice_steam_proc("SteamAPI_ISteamUGC_SetReturnPlaytimeStats");
    SteamAPI_ISteamUGC_SetLanguage = (PFN_SteamAPI_ISteamUGC_SetLanguage) ice_steam_proc("SteamAPI_ISteamUGC_SetLanguage");
    SteamAPI_ISteamUGC_SetAllowCachedResponse = (PFN_SteamAPI_ISteamUGC_SetAllowCachedResponse) ice_steam_proc("SteamAPI_ISteamUGC_SetAllowCachedResponse");
    SteamAPI_ISteamUGC_SetCloudFileNameFilter = (PFN_SteamAPI_ISteamUGC_SetCloudFileNameFilter) ice_steam_proc("SteamAPI_ISteamUGC_SetCloudFileNameFilter");
    SteamAPI_ISteamUGC_SetMatchAnyTag = (PFN_SteamAPI_ISteamUGC_SetMatchAnyTag) ice_steam_proc("SteamAPI_ISteamUGC_SetMatchAnyTag");
    SteamAPI_ISteamUGC_SetSearchText = (PFN_SteamAPI_ISteamUGC_SetSearchText) ice_steam_proc("SteamAPI_ISteamUGC_SetSearchText");
    SteamAPI_ISteamUGC_SetRankedByTrendDays = (PFN_SteamAPI_ISteamUGC_SetRankedByTrendDays) ice_steam_proc("SteamAPI_ISteamUGC_SetRankedByTrendDays");
    SteamAPI_ISteamUGC_AddRequiredKeyValueTag = (PFN_SteamAPI_ISteamUGC_AddRequiredKeyValueTag) ice_steam_proc("SteamAPI_ISteamUGC_AddRequiredKeyValueTag");
    SteamAPI_ISteamUGC_RequestUGCDetails = (PFN_SteamAPI_ISteamUGC_RequestUGCDetails) ice_steam_proc("SteamAPI_ISteamUGC_RequestUGCDetails");
    SteamAPI_ISteamUGC_CreateItem = (PFN_SteamAPI_ISteamUGC_CreateItem) ice_steam_proc("SteamAPI_ISteamUGC_CreateItem");
    SteamAPI_ISteamUGC_StartItemUpdate = (PFN_SteamAPI_ISteamUGC_StartItemUpdate) ice_steam_proc("SteamAPI_ISteamUGC_StartItemUpdate");
    SteamAPI_ISteamUGC_SetItemTitle = (PFN_SteamAPI_ISteamUGC_SetItemTitle) ice_steam_proc("SteamAPI_ISteamUGC_SetItemTitle");
    SteamAPI_ISteamUGC_SetItemDescription = (PFN_SteamAPI_ISteamUGC_SetItemDescription) ice_steam_proc("SteamAPI_ISteamUGC_SetItemDescription");
    SteamAPI_ISteamUGC_SetItemUpdateLanguage = (PFN_SteamAPI_ISteamUGC_SetItemUpdateLanguage) ice_steam_proc("SteamAPI_ISteamUGC_SetItemUpdateLanguage");
    SteamAPI_ISteamUGC_SetItemMetadata = (PFN_SteamAPI_ISteamUGC_SetItemMetadata) ice_steam_proc("SteamAPI_ISteamUGC_SetItemMetadata");
    SteamAPI_ISteamUGC_SetItemVisibility = (PFN_SteamAPI_ISteamUGC_SetItemVisibility) ice_steam_proc("SteamAPI_ISteamUGC_SetItemVisibility");
    SteamAPI_ISteamUGC_SetItemTags = (PFN_SteamAPI_ISteamUGC_SetItemTags) ice_steam_proc("SteamAPI_ISteamUGC_SetItemTags");
    SteamAPI_ISteamUGC_SetItemContent = (PFN_SteamAPI_ISteamUGC_SetItemContent) ice_steam_proc("SteamAPI_ISteamUGC_SetItemContent");
    SteamAPI_ISteamUGC_SetItemPreview = (PFN_SteamAPI_ISteamUGC_SetItemPreview) ice_steam_proc("SteamAPI_ISteamUGC_SetItemPreview");
    SteamAPI_ISteamUGC_RemoveItemKeyValueTags = (PFN_SteamAPI_ISteamUGC_RemoveItemKeyValueTags) ice_steam_proc("SteamAPI_ISteamUGC_RemoveItemKeyValueTags");
    SteamAPI_ISteamUGC_AddItemKeyValueTag = (PFN_SteamAPI_ISteamUGC_AddItemKeyValueTag) ice_steam_proc("SteamAPI_ISteamUGC_AddItemKeyValueTag");
    SteamAPI_ISteamUGC_AddItemPreviewFile = (PFN_SteamAPI_ISteamUGC_AddItemPreviewFile) ice_steam_proc("SteamAPI_ISteamUGC_AddItemPreviewFile");
    SteamAPI_ISteamUGC_AddItemPreviewVideo = (PFN_SteamAPI_ISteamUGC_AddItemPreviewVideo) ice_steam_proc("SteamAPI_ISteamUGC_AddItemPreviewVideo");
    SteamAPI_ISteamUGC_UpdateItemPreviewFile = (PFN_SteamAPI_ISteamUGC_UpdateItemPreviewFile) ice_steam_proc("SteamAPI_ISteamUGC_UpdateItemPreviewFile");
    SteamAPI_ISteamUGC_UpdateItemPreviewVideo = (PFN_SteamAPI_ISteamUGC_UpdateItemPreviewVideo) ice_steam_proc("SteamAPI_ISteamUGC_UpdateItemPreviewVideo");
    SteamAPI_ISteamUGC_RemoveItemPreview = (PFN_SteamAPI_ISteamUGC_RemoveItemPreview) ice_steam_proc("SteamAPI_ISteamUGC_RemoveItemPreview");
    SteamAPI_ISteamUGC_SubmitItemUpdate = (PFN_SteamAPI_ISteamUGC_SubmitItemUpdate) ice_steam_proc("SteamAPI_ISteamUGC_SubmitItemUpdate");
    SteamAPI_ISteamUGC_GetItemUpdateProgress = (PFN_SteamAPI_ISteamUGC_GetItemUpdateProgress) ice_steam_proc("SteamAPI_ISteamUGC_GetItemUpdateProgress");
    SteamAPI_ISteamUGC_SetUserItemVote = (PFN_SteamAPI_ISteamUGC_SetUserItemVote) ice_steam_proc("SteamAPI_ISteamUGC_SetUserItemVote");
    SteamAPI_ISteamUGC_GetUserItemVote = (PFN_SteamAPI_ISteamUGC_GetUserItemVote) ice_steam_proc("SteamAPI_ISteamUGC_GetUserItemVote");
    SteamAPI_ISteamUGC_AddItemToFavorites = (PFN_SteamAPI_ISteamUGC_AddItemToFavorites) ice_steam_proc("SteamAPI_ISteamUGC_AddItemToFavorites");
    SteamAPI_ISteamUGC_RemoveItemFromFavorites = (PFN_SteamAPI_ISteamUGC_RemoveItemFromFavorites) ice_steam_proc("SteamAPI_ISteamUGC_RemoveItemFromFavorites");
    SteamAPI_ISteamUGC_SubscribeItem = (PFN_SteamAPI_ISteamUGC_SubscribeItem) ice_steam_proc("SteamAPI_ISteamUGC_SubscribeItem");
    SteamAPI_ISteamUGC_UnsubscribeItem = (PFN_SteamAPI_ISteamUGC_UnsubscribeItem) ice_steam_proc("SteamAPI_ISteamUGC_UnsubscribeItem");
    SteamAPI_ISteamUGC_GetNumSubscribedItems = (PFN_SteamAPI_ISteamUGC_GetNumSubscribedItems) ice_steam_proc("SteamAPI_ISteamUGC_GetNumSubscribedItems");
    SteamAPI_ISteamUGC_GetSubscribedItems = (PFN_SteamAPI_ISteamUGC_GetSubscribedItems) ice_steam_proc("SteamAPI_ISteamUGC_GetSubscribedItems");
    SteamAPI_ISteamUGC_GetItemState = (PFN_SteamAPI_ISteamUGC_GetItemState) ice_steam_proc("SteamAPI_ISteamUGC_GetItemState");
    SteamAPI_ISteamUGC_GetItemInstallInfo = (PFN_SteamAPI_ISteamUGC_GetItemInstallInfo) ice_steam_proc("SteamAPI_ISteamUGC_GetItemInstallInfo");
    SteamAPI_ISteamUGC_GetItemDownloadInfo = (PFN_SteamAPI_ISteamUGC_GetItemDownloadInfo) ice_steam_proc("SteamAPI_ISteamUGC_GetItemDownloadInfo");
    SteamAPI_ISteamUGC_DownloadItem = (PFN_SteamAPI_ISteamUGC_DownloadItem) ice_steam_proc("SteamAPI_ISteamUGC_DownloadItem");
    SteamAPI_ISteamUGC_BInitWorkshopForGameServer = (PFN_SteamAPI_ISteamUGC_BInitWorkshopForGameServer) ice_steam_proc("SteamAPI_ISteamUGC_BInitWorkshopForGameServer");
    SteamAPI_ISteamUGC_SuspendDownloads = (PFN_SteamAPI_ISteamUGC_SuspendDownloads) ice_steam_proc("SteamAPI_ISteamUGC_SuspendDownloads");
    SteamAPI_ISteamUGC_StartPlaytimeTracking = (PFN_SteamAPI_ISteamUGC_StartPlaytimeTracking) ice_steam_proc("SteamAPI_ISteamUGC_StartPlaytimeTracking");
    SteamAPI_ISteamUGC_StopPlaytimeTracking = (PFN_SteamAPI_ISteamUGC_StopPlaytimeTracking) ice_steam_proc("SteamAPI_ISteamUGC_StopPlaytimeTracking");
    SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems = (PFN_SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems) ice_steam_proc("SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems");
    SteamAPI_ISteamUGC_AddDependency = (PFN_SteamAPI_ISteamUGC_AddDependency) ice_steam_proc("SteamAPI_ISteamUGC_AddDependency");
    SteamAPI_ISteamUGC_RemoveDependency = (PFN_SteamAPI_ISteamUGC_RemoveDependency) ice_steam_proc("SteamAPI_ISteamUGC_RemoveDependency");
    SteamAPI_ISteamUGC_AddAppDependency = (PFN_SteamAPI_ISteamUGC_AddAppDependency) ice_steam_proc("SteamAPI_ISteamUGC_AddAppDependency");
    SteamAPI_ISteamUGC_RemoveAppDependency = (PFN_SteamAPI_ISteamUGC_RemoveAppDependency) ice_steam_proc("SteamAPI_ISteamUGC_RemoveAppDependency");
    SteamAPI_ISteamUGC_GetAppDependencies = (PFN_SteamAPI_ISteamUGC_GetAppDependencies) ice_steam_proc("SteamAPI_ISteamUGC_GetAppDependencies");
    SteamAPI_ISteamUGC_DeleteItem = (PFN_SteamAPI_ISteamUGC_DeleteItem) ice_steam_proc("SteamAPI_ISteamUGC_DeleteItem");
    SteamAPI_ISteamAppList_GetNumInstalledApps = (PFN_SteamAPI_ISteamAppList_GetNumInstalledApps) ice_steam_proc("SteamAPI_ISteamAppList_GetNumInstalledApps");
    SteamAPI_ISteamAppList_GetInstalledApps = (PFN_SteamAPI_ISteamAppList_GetInstalledApps) ice_steam_proc("SteamAPI_ISteamAppList_GetInstalledApps");
    SteamAPI_ISteamAppList_GetAppName = (PFN_SteamAPI_ISteamAppList_GetAppName) ice_steam_proc("SteamAPI_ISteamAppList_GetAppName");
    SteamAPI_ISteamAppList_GetAppInstallDir = (PFN_SteamAPI_ISteamAppList_GetAppInstallDir) ice_steam_proc("SteamAPI_ISteamAppList_GetAppInstallDir");
    SteamAPI_ISteamAppList_GetAppBuildId = (PFN_SteamAPI_ISteamAppList_GetAppBuildId) ice_steam_proc("SteamAPI_ISteamAppList_GetAppBuildId");
    SteamAPI_ISteamHTMLSurface_DestructISteamHTMLSurface = (PFN_SteamAPI_ISteamHTMLSurface_DestructISteamHTMLSurface) ice_steam_proc("SteamAPI_ISteamHTMLSurface_DestructISteamHTMLSurface");
    SteamAPI_ISteamHTMLSurface_Init = (PFN_SteamAPI_ISteamHTMLSurface_Init) ice_steam_proc("SteamAPI_ISteamHTMLSurface_Init");
    SteamAPI_ISteamHTMLSurface_Shutdown = (PFN_SteamAPI_ISteamHTMLSurface_Shutdown) ice_steam_proc("SteamAPI_ISteamHTMLSurface_Shutdown");
    SteamAPI_ISteamHTMLSurface_CreateBrowser = (PFN_SteamAPI_ISteamHTMLSurface_CreateBrowser) ice_steam_proc("SteamAPI_ISteamHTMLSurface_CreateBrowser");
    SteamAPI_ISteamHTMLSurface_RemoveBrowser = (PFN_SteamAPI_ISteamHTMLSurface_RemoveBrowser) ice_steam_proc("SteamAPI_ISteamHTMLSurface_RemoveBrowser");
    SteamAPI_ISteamHTMLSurface_LoadURL = (PFN_SteamAPI_ISteamHTMLSurface_LoadURL) ice_steam_proc("SteamAPI_ISteamHTMLSurface_LoadURL");
    SteamAPI_ISteamHTMLSurface_SetSize = (PFN_SteamAPI_ISteamHTMLSurface_SetSize) ice_steam_proc("SteamAPI_ISteamHTMLSurface_SetSize");
    SteamAPI_ISteamHTMLSurface_StopLoad = (PFN_SteamAPI_ISteamHTMLSurface_StopLoad) ice_steam_proc("SteamAPI_ISteamHTMLSurface_StopLoad");
    SteamAPI_ISteamHTMLSurface_Reload = (PFN_SteamAPI_ISteamHTMLSurface_Reload) ice_steam_proc("SteamAPI_ISteamHTMLSurface_Reload");
    SteamAPI_ISteamHTMLSurface_GoBack = (PFN_SteamAPI_ISteamHTMLSurface_GoBack) ice_steam_proc("SteamAPI_ISteamHTMLSurface_GoBack");
    SteamAPI_ISteamHTMLSurface_GoForward = (PFN_SteamAPI_ISteamHTMLSurface_GoForward) ice_steam_proc("SteamAPI_ISteamHTMLSurface_GoForward");
    SteamAPI_ISteamHTMLSurface_AddHeader = (PFN_SteamAPI_ISteamHTMLSurface_AddHeader) ice_steam_proc("SteamAPI_ISteamHTMLSurface_AddHeader");
    SteamAPI_ISteamHTMLSurface_ExecuteJavascript = (PFN_SteamAPI_ISteamHTMLSurface_ExecuteJavascript) ice_steam_proc("SteamAPI_ISteamHTMLSurface_ExecuteJavascript");
    SteamAPI_ISteamHTMLSurface_SetHorizontalScroll = (PFN_SteamAPI_ISteamHTMLSurface_SetHorizontalScroll) ice_steam_proc("SteamAPI_ISteamHTMLSurface_SetHorizontalScroll");
    SteamAPI_ISteamHTMLSurface_SetVerticalScroll = (PFN_SteamAPI_ISteamHTMLSurface_SetVerticalScroll) ice_steam_proc("SteamAPI_ISteamHTMLSurface_SetVerticalScroll");
    SteamAPI_ISteamHTMLSurface_SetKeyFocus = (PFN_SteamAPI_ISteamHTMLSurface_SetKeyFocus) ice_steam_proc("SteamAPI_ISteamHTMLSurface_SetKeyFocus");
    SteamAPI_ISteamHTMLSurface_ViewSource = (PFN_SteamAPI_ISteamHTMLSurface_ViewSource) ice_steam_proc("SteamAPI_ISteamHTMLSurface_ViewSource");
    SteamAPI_ISteamHTMLSurface_CopyToClipboard = (PFN_SteamAPI_ISteamHTMLSurface_CopyToClipboard) ice_steam_proc("SteamAPI_ISteamHTMLSurface_CopyToClipboard");
    SteamAPI_ISteamHTMLSurface_PasteFromClipboard = (PFN_SteamAPI_ISteamHTMLSurface_PasteFromClipboard) ice_steam_proc("SteamAPI_ISteamHTMLSurface_PasteFromClipboard");
    SteamAPI_ISteamHTMLSurface_Find = (PFN_SteamAPI_ISteamHTMLSurface_Find) ice_steam_proc("SteamAPI_ISteamHTMLSurface_Find");
    SteamAPI_ISteamHTMLSurface_StopFind = (PFN_SteamAPI_ISteamHTMLSurface_StopFind) ice_steam_proc("SteamAPI_ISteamHTMLSurface_StopFind");
    SteamAPI_ISteamHTMLSurface_GetLinkAtPosition = (PFN_SteamAPI_ISteamHTMLSurface_GetLinkAtPosition) ice_steam_proc("SteamAPI_ISteamHTMLSurface_GetLinkAtPosition");
    SteamAPI_ISteamHTMLSurface_SetCookie = (PFN_SteamAPI_ISteamHTMLSurface_SetCookie) ice_steam_proc("SteamAPI_ISteamHTMLSurface_SetCookie");
    SteamAPI_ISteamHTMLSurface_SetPageScaleFactor = (PFN_SteamAPI_ISteamHTMLSurface_SetPageScaleFactor) ice_steam_proc("SteamAPI_ISteamHTMLSurface_SetPageScaleFactor");
    SteamAPI_ISteamHTMLSurface_SetBackgroundMode = (PFN_SteamAPI_ISteamHTMLSurface_SetBackgroundMode) ice_steam_proc("SteamAPI_ISteamHTMLSurface_SetBackgroundMode");
    SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor = (PFN_SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor) ice_steam_proc("SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor");
    SteamAPI_ISteamHTMLSurface_AllowStartRequest = (PFN_SteamAPI_ISteamHTMLSurface_AllowStartRequest) ice_steam_proc("SteamAPI_ISteamHTMLSurface_AllowStartRequest");
    SteamAPI_ISteamHTMLSurface_JSDialogResponse = (PFN_SteamAPI_ISteamHTMLSurface_JSDialogResponse) ice_steam_proc("SteamAPI_ISteamHTMLSurface_JSDialogResponse");
    SteamAPI_ISteamInventory_GetResultStatus = (PFN_SteamAPI_ISteamInventory_GetResultStatus) ice_steam_proc("SteamAPI_ISteamInventory_GetResultStatus");
    SteamAPI_ISteamInventory_GetResultItems = (PFN_SteamAPI_ISteamInventory_GetResultItems) ice_steam_proc("SteamAPI_ISteamInventory_GetResultItems");
    SteamAPI_ISteamInventory_GetResultItemProperty = (PFN_SteamAPI_ISteamInventory_GetResultItemProperty) ice_steam_proc("SteamAPI_ISteamInventory_GetResultItemProperty");
    SteamAPI_ISteamInventory_GetResultTimestamp = (PFN_SteamAPI_ISteamInventory_GetResultTimestamp) ice_steam_proc("SteamAPI_ISteamInventory_GetResultTimestamp");
    SteamAPI_ISteamInventory_CheckResultSteamID = (PFN_SteamAPI_ISteamInventory_CheckResultSteamID) ice_steam_proc("SteamAPI_ISteamInventory_CheckResultSteamID");
    SteamAPI_ISteamInventory_DestroyResult = (PFN_SteamAPI_ISteamInventory_DestroyResult) ice_steam_proc("SteamAPI_ISteamInventory_DestroyResult");
    SteamAPI_ISteamInventory_GetAllItems = (PFN_SteamAPI_ISteamInventory_GetAllItems) ice_steam_proc("SteamAPI_ISteamInventory_GetAllItems");
    SteamAPI_ISteamInventory_GetItemsByID = (PFN_SteamAPI_ISteamInventory_GetItemsByID) ice_steam_proc("SteamAPI_ISteamInventory_GetItemsByID");
    SteamAPI_ISteamInventory_SerializeResult = (PFN_SteamAPI_ISteamInventory_SerializeResult) ice_steam_proc("SteamAPI_ISteamInventory_SerializeResult");
    SteamAPI_ISteamInventory_DeserializeResult = (PFN_SteamAPI_ISteamInventory_DeserializeResult) ice_steam_proc("SteamAPI_ISteamInventory_DeserializeResult");
    SteamAPI_ISteamInventory_GenerateItems = (PFN_SteamAPI_ISteamInventory_GenerateItems) ice_steam_proc("SteamAPI_ISteamInventory_GenerateItems");
    SteamAPI_ISteamInventory_GrantPromoItems = (PFN_SteamAPI_ISteamInventory_GrantPromoItems) ice_steam_proc("SteamAPI_ISteamInventory_GrantPromoItems");
    SteamAPI_ISteamInventory_AddPromoItem = (PFN_SteamAPI_ISteamInventory_AddPromoItem) ice_steam_proc("SteamAPI_ISteamInventory_AddPromoItem");
    SteamAPI_ISteamInventory_AddPromoItems = (PFN_SteamAPI_ISteamInventory_AddPromoItems) ice_steam_proc("SteamAPI_ISteamInventory_AddPromoItems");
    SteamAPI_ISteamInventory_ConsumeItem = (PFN_SteamAPI_ISteamInventory_ConsumeItem) ice_steam_proc("SteamAPI_ISteamInventory_ConsumeItem");
    SteamAPI_ISteamInventory_ExchangeItems = (PFN_SteamAPI_ISteamInventory_ExchangeItems) ice_steam_proc("SteamAPI_ISteamInventory_ExchangeItems");
    SteamAPI_ISteamInventory_TransferItemQuantity = (PFN_SteamAPI_ISteamInventory_TransferItemQuantity) ice_steam_proc("SteamAPI_ISteamInventory_TransferItemQuantity");
    SteamAPI_ISteamInventory_SendItemDropHeartbeat = (PFN_SteamAPI_ISteamInventory_SendItemDropHeartbeat) ice_steam_proc("SteamAPI_ISteamInventory_SendItemDropHeartbeat");
    SteamAPI_ISteamInventory_TriggerItemDrop = (PFN_SteamAPI_ISteamInventory_TriggerItemDrop) ice_steam_proc("SteamAPI_ISteamInventory_TriggerItemDrop");
    SteamAPI_ISteamInventory_TradeItems = (PFN_SteamAPI_ISteamInventory_TradeItems) ice_steam_proc("SteamAPI_ISteamInventory_TradeItems");
    SteamAPI_ISteamInventory_LoadItemDefinitions = (PFN_SteamAPI_ISteamInventory_LoadItemDefinitions) ice_steam_proc("SteamAPI_ISteamInventory_LoadItemDefinitions");
    SteamAPI_ISteamInventory_GetItemDefinitionIDs = (PFN_SteamAPI_ISteamInventory_GetItemDefinitionIDs) ice_steam_proc("SteamAPI_ISteamInventory_GetItemDefinitionIDs");
    SteamAPI_ISteamInventory_GetItemDefinitionProperty = (PFN_SteamAPI_ISteamInventory_GetItemDefinitionProperty) ice_steam_proc("SteamAPI_ISteamInventory_GetItemDefinitionProperty");
    SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs = (PFN_SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs) ice_steam_proc("SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs");
    SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs = (PFN_SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs) ice_steam_proc("SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs");
    SteamAPI_ISteamInventory_StartPurchase = (PFN_SteamAPI_ISteamInventory_StartPurchase) ice_steam_proc("SteamAPI_ISteamInventory_StartPurchase");
    SteamAPI_ISteamInventory_RequestPrices = (PFN_SteamAPI_ISteamInventory_RequestPrices) ice_steam_proc("SteamAPI_ISteamInventory_RequestPrices");
    SteamAPI_ISteamInventory_GetNumItemsWithPrices = (PFN_SteamAPI_ISteamInventory_GetNumItemsWithPrices) ice_steam_proc("SteamAPI_ISteamInventory_GetNumItemsWithPrices");
    SteamAPI_ISteamInventory_GetItemsWithPrices = (PFN_SteamAPI_ISteamInventory_GetItemsWithPrices) ice_steam_proc("SteamAPI_ISteamInventory_GetItemsWithPrices");
    SteamAPI_ISteamInventory_GetItemPrice = (PFN_SteamAPI_ISteamInventory_GetItemPrice) ice_steam_proc("SteamAPI_ISteamInventory_GetItemPrice");
    SteamAPI_ISteamInventory_StartUpdateProperties = (PFN_SteamAPI_ISteamInventory_StartUpdateProperties) ice_steam_proc("SteamAPI_ISteamInventory_StartUpdateProperties");
    SteamAPI_ISteamInventory_RemoveProperty = (PFN_SteamAPI_ISteamInventory_RemoveProperty) ice_steam_proc("SteamAPI_ISteamInventory_RemoveProperty");
    SteamAPI_ISteamInventory_SetProperty = (PFN_SteamAPI_ISteamInventory_SetProperty) ice_steam_proc("SteamAPI_ISteamInventory_SetProperty");
    SteamAPI_ISteamInventory_SetProperty0 = (PFN_SteamAPI_ISteamInventory_SetProperty0) ice_steam_proc("SteamAPI_ISteamInventory_SetProperty0");
    SteamAPI_ISteamInventory_SetProperty1 = (PFN_SteamAPI_ISteamInventory_SetProperty1) ice_steam_proc("SteamAPI_ISteamInventory_SetProperty1");
    SteamAPI_ISteamInventory_SetProperty2 = (PFN_SteamAPI_ISteamInventory_SetProperty2) ice_steam_proc("SteamAPI_ISteamInventory_SetProperty2");
    SteamAPI_ISteamInventory_SubmitUpdateProperties = (PFN_SteamAPI_ISteamInventory_SubmitUpdateProperties) ice_steam_proc("SteamAPI_ISteamInventory_SubmitUpdateProperties");
    SteamAPI_ISteamVideo_GetVideoURL = (PFN_SteamAPI_ISteamVideo_GetVideoURL) ice_steam_proc("SteamAPI_ISteamVideo_GetVideoURL");
    SteamAPI_ISteamVideo_IsBroadcasting = (PFN_SteamAPI_ISteamVideo_IsBroadcasting) ice_steam_proc("SteamAPI_ISteamVideo_IsBroadcasting");
    SteamAPI_ISteamVideo_GetOPFSettings = (PFN_SteamAPI_ISteamVideo_GetOPFSettings) ice_steam_proc("SteamAPI_ISteamVideo_GetOPFSettings");
    SteamAPI_ISteamVideo_GetOPFStringForApp = (PFN_SteamAPI_ISteamVideo_GetOPFStringForApp) ice_steam_proc("SteamAPI_ISteamVideo_GetOPFStringForApp");
    SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled = (PFN_SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled) ice_steam_proc("SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled");
    SteamAPI_ISteamParentalSettings_BIsParentalLockLocked = (PFN_SteamAPI_ISteamParentalSettings_BIsParentalLockLocked) ice_steam_proc("SteamAPI_ISteamParentalSettings_BIsParentalLockLocked");
    SteamAPI_ISteamParentalSettings_BIsAppBlocked = (PFN_SteamAPI_ISteamParentalSettings_BIsAppBlocked) ice_steam_proc("SteamAPI_ISteamParentalSettings_BIsAppBlocked");
    SteamAPI_ISteamParentalSettings_BIsAppInBlockList = (PFN_SteamAPI_ISteamParentalSettings_BIsAppInBlockList) ice_steam_proc("SteamAPI_ISteamParentalSettings_BIsAppInBlockList");
    SteamAPI_ISteamParentalSettings_BIsFeatureBlocked = (PFN_SteamAPI_ISteamParentalSettings_BIsFeatureBlocked) ice_steam_proc("SteamAPI_ISteamParentalSettings_BIsFeatureBlocked");
    SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList = (PFN_SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList) ice_steam_proc("SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList");
    SteamAPI_ISteamGameServer_InitGameServer = (PFN_SteamAPI_ISteamGameServer_InitGameServer) ice_steam_proc("SteamAPI_ISteamGameServer_InitGameServer");
    SteamAPI_ISteamGameServer_SetProduct = (PFN_SteamAPI_ISteamGameServer_SetProduct) ice_steam_proc("SteamAPI_ISteamGameServer_SetProduct");
    SteamAPI_ISteamGameServer_SetGameDescription = (PFN_SteamAPI_ISteamGameServer_SetGameDescription) ice_steam_proc("SteamAPI_ISteamGameServer_SetGameDescription");
    SteamAPI_ISteamGameServer_SetModDir = (PFN_SteamAPI_ISteamGameServer_SetModDir) ice_steam_proc("SteamAPI_ISteamGameServer_SetModDir");
    SteamAPI_ISteamGameServer_SetDedicatedServer = (PFN_SteamAPI_ISteamGameServer_SetDedicatedServer) ice_steam_proc("SteamAPI_ISteamGameServer_SetDedicatedServer");
    SteamAPI_ISteamGameServer_LogOn = (PFN_SteamAPI_ISteamGameServer_LogOn) ice_steam_proc("SteamAPI_ISteamGameServer_LogOn");
    SteamAPI_ISteamGameServer_LogOnAnonymous = (PFN_SteamAPI_ISteamGameServer_LogOnAnonymous) ice_steam_proc("SteamAPI_ISteamGameServer_LogOnAnonymous");
    SteamAPI_ISteamGameServer_LogOff = (PFN_SteamAPI_ISteamGameServer_LogOff) ice_steam_proc("SteamAPI_ISteamGameServer_LogOff");
    SteamAPI_ISteamGameServer_BLoggedOn = (PFN_SteamAPI_ISteamGameServer_BLoggedOn) ice_steam_proc("SteamAPI_ISteamGameServer_BLoggedOn");
    SteamAPI_ISteamGameServer_BSecure = (PFN_SteamAPI_ISteamGameServer_BSecure) ice_steam_proc("SteamAPI_ISteamGameServer_BSecure");
    SteamAPI_ISteamGameServer_GetSteamID = (PFN_SteamAPI_ISteamGameServer_GetSteamID) ice_steam_proc("SteamAPI_ISteamGameServer_GetSteamID");
    SteamAPI_ISteamGameServer_WasRestartRequested = (PFN_SteamAPI_ISteamGameServer_WasRestartRequested) ice_steam_proc("SteamAPI_ISteamGameServer_WasRestartRequested");
    SteamAPI_ISteamGameServer_SetMaxPlayerCount = (PFN_SteamAPI_ISteamGameServer_SetMaxPlayerCount) ice_steam_proc("SteamAPI_ISteamGameServer_SetMaxPlayerCount");
    SteamAPI_ISteamGameServer_SetBotPlayerCount = (PFN_SteamAPI_ISteamGameServer_SetBotPlayerCount) ice_steam_proc("SteamAPI_ISteamGameServer_SetBotPlayerCount");
    SteamAPI_ISteamGameServer_SetServerName = (PFN_SteamAPI_ISteamGameServer_SetServerName) ice_steam_proc("SteamAPI_ISteamGameServer_SetServerName");
    SteamAPI_ISteamGameServer_SetMapName = (PFN_SteamAPI_ISteamGameServer_SetMapName) ice_steam_proc("SteamAPI_ISteamGameServer_SetMapName");
    SteamAPI_ISteamGameServer_SetPasswordProtected = (PFN_SteamAPI_ISteamGameServer_SetPasswordProtected) ice_steam_proc("SteamAPI_ISteamGameServer_SetPasswordProtected");
    SteamAPI_ISteamGameServer_SetSpectatorPort = (PFN_SteamAPI_ISteamGameServer_SetSpectatorPort) ice_steam_proc("SteamAPI_ISteamGameServer_SetSpectatorPort");
    SteamAPI_ISteamGameServer_SetSpectatorServerName = (PFN_SteamAPI_ISteamGameServer_SetSpectatorServerName) ice_steam_proc("SteamAPI_ISteamGameServer_SetSpectatorServerName");
    SteamAPI_ISteamGameServer_ClearAllKeyValues = (PFN_SteamAPI_ISteamGameServer_ClearAllKeyValues) ice_steam_proc("SteamAPI_ISteamGameServer_ClearAllKeyValues");
    SteamAPI_ISteamGameServer_SetKeyValue = (PFN_SteamAPI_ISteamGameServer_SetKeyValue) ice_steam_proc("SteamAPI_ISteamGameServer_SetKeyValue");
    SteamAPI_ISteamGameServer_SetGameTags = (PFN_SteamAPI_ISteamGameServer_SetGameTags) ice_steam_proc("SteamAPI_ISteamGameServer_SetGameTags");
    SteamAPI_ISteamGameServer_SetGameData = (PFN_SteamAPI_ISteamGameServer_SetGameData) ice_steam_proc("SteamAPI_ISteamGameServer_SetGameData");
    SteamAPI_ISteamGameServer_SetRegion = (PFN_SteamAPI_ISteamGameServer_SetRegion) ice_steam_proc("SteamAPI_ISteamGameServer_SetRegion");
    SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate = (PFN_SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate) ice_steam_proc("SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate");
    SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection = (PFN_SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection) ice_steam_proc("SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection");
    SteamAPI_ISteamGameServer_SendUserDisconnect = (PFN_SteamAPI_ISteamGameServer_SendUserDisconnect) ice_steam_proc("SteamAPI_ISteamGameServer_SendUserDisconnect");
    SteamAPI_ISteamGameServer_BUpdateUserData = (PFN_SteamAPI_ISteamGameServer_BUpdateUserData) ice_steam_proc("SteamAPI_ISteamGameServer_BUpdateUserData");
    SteamAPI_ISteamGameServer_GetAuthSessionTicket = (PFN_SteamAPI_ISteamGameServer_GetAuthSessionTicket) ice_steam_proc("SteamAPI_ISteamGameServer_GetAuthSessionTicket");
    SteamAPI_ISteamGameServer_BeginAuthSession = (PFN_SteamAPI_ISteamGameServer_BeginAuthSession) ice_steam_proc("SteamAPI_ISteamGameServer_BeginAuthSession");
    SteamAPI_ISteamGameServer_EndAuthSession = (PFN_SteamAPI_ISteamGameServer_EndAuthSession) ice_steam_proc("SteamAPI_ISteamGameServer_EndAuthSession");
    SteamAPI_ISteamGameServer_CancelAuthTicket = (PFN_SteamAPI_ISteamGameServer_CancelAuthTicket) ice_steam_proc("SteamAPI_ISteamGameServer_CancelAuthTicket");
    SteamAPI_ISteamGameServer_UserHasLicenseForApp = (PFN_SteamAPI_ISteamGameServer_UserHasLicenseForApp) ice_steam_proc("SteamAPI_ISteamGameServer_UserHasLicenseForApp");
    SteamAPI_ISteamGameServer_RequestUserGroupStatus = (PFN_SteamAPI_ISteamGameServer_RequestUserGroupStatus) ice_steam_proc("SteamAPI_ISteamGameServer_RequestUserGroupStatus");
    SteamAPI_ISteamGameServer_GetGameplayStats = (PFN_SteamAPI_ISteamGameServer_GetGameplayStats) ice_steam_proc("SteamAPI_ISteamGameServer_GetGameplayStats");
    SteamAPI_ISteamGameServer_GetServerReputation = (PFN_SteamAPI_ISteamGameServer_GetServerReputation) ice_steam_proc("SteamAPI_ISteamGameServer_GetServerReputation");
    SteamAPI_ISteamGameServer_GetPublicIP = (PFN_SteamAPI_ISteamGameServer_GetPublicIP) ice_steam_proc("SteamAPI_ISteamGameServer_GetPublicIP");
    SteamAPI_ISteamGameServer_HandleIncomingPacket = (PFN_SteamAPI_ISteamGameServer_HandleIncomingPacket) ice_steam_proc("SteamAPI_ISteamGameServer_HandleIncomingPacket");
    SteamAPI_ISteamGameServer_GetNextOutgoingPacket = (PFN_SteamAPI_ISteamGameServer_GetNextOutgoingPacket) ice_steam_proc("SteamAPI_ISteamGameServer_GetNextOutgoingPacket");
    SteamAPI_ISteamGameServer_EnableHeartbeats = (PFN_SteamAPI_ISteamGameServer_EnableHeartbeats) ice_steam_proc("SteamAPI_ISteamGameServer_EnableHeartbeats");
    SteamAPI_ISteamGameServer_SetHeartbeatInterval = (PFN_SteamAPI_ISteamGameServer_SetHeartbeatInterval) ice_steam_proc("SteamAPI_ISteamGameServer_SetHeartbeatInterval");
    SteamAPI_ISteamGameServer_ForceHeartbeat = (PFN_SteamAPI_ISteamGameServer_ForceHeartbeat) ice_steam_proc("SteamAPI_ISteamGameServer_ForceHeartbeat");
    SteamAPI_ISteamGameServer_AssociateWithClan = (PFN_SteamAPI_ISteamGameServer_AssociateWithClan) ice_steam_proc("SteamAPI_ISteamGameServer_AssociateWithClan");
    SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility = (PFN_SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility) ice_steam_proc("SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility");
    SteamAPI_ISteamGameServerStats_RequestUserStats = (PFN_SteamAPI_ISteamGameServerStats_RequestUserStats) ice_steam_proc("SteamAPI_ISteamGameServerStats_RequestUserStats");
    SteamAPI_ISteamGameServerStats_GetUserStat = (PFN_SteamAPI_ISteamGameServerStats_GetUserStat) ice_steam_proc("SteamAPI_ISteamGameServerStats_GetUserStat");
    SteamAPI_ISteamGameServerStats_GetUserStat0 = (PFN_SteamAPI_ISteamGameServerStats_GetUserStat0) ice_steam_proc("SteamAPI_ISteamGameServerStats_GetUserStat0");
    SteamAPI_ISteamGameServerStats_GetUserAchievement = (PFN_SteamAPI_ISteamGameServerStats_GetUserAchievement) ice_steam_proc("SteamAPI_ISteamGameServerStats_GetUserAchievement");
    SteamAPI_ISteamGameServerStats_SetUserStat = (PFN_SteamAPI_ISteamGameServerStats_SetUserStat) ice_steam_proc("SteamAPI_ISteamGameServerStats_SetUserStat");
    SteamAPI_ISteamGameServerStats_SetUserStat0 = (PFN_SteamAPI_ISteamGameServerStats_SetUserStat0) ice_steam_proc("SteamAPI_ISteamGameServerStats_SetUserStat0");
    SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat = (PFN_SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat) ice_steam_proc("SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat");
    SteamAPI_ISteamGameServerStats_SetUserAchievement = (PFN_SteamAPI_ISteamGameServerStats_SetUserAchievement) ice_steam_proc("SteamAPI_ISteamGameServerStats_SetUserAchievement");
    SteamAPI_ISteamGameServerStats_ClearUserAchievement = (PFN_SteamAPI_ISteamGameServerStats_ClearUserAchievement) ice_steam_proc("SteamAPI_ISteamGameServerStats_ClearUserAchievement");
    SteamAPI_ISteamGameServerStats_StoreUserStats = (PFN_SteamAPI_ISteamGameServerStats_StoreUserStats) ice_steam_proc("SteamAPI_ISteamGameServerStats_StoreUserStats");
    
    return ICE_STEAM_TRUE;
}

#endif  // ICE_STEAM_IMPL
#endif  // ICE_STEAM_H
