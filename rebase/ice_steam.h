/*
ice_steam.h, Single-Header Cross-Platform C library for working with SteamWorks SDK!

TODO: Continue (In line 3732, Starting with SteamNetConnectionInfo_t from steamnetworkingtypes.h)
TODO: bool type fallback


================================== Full Overview ==================================

ice_steam.h, Single-Header Cross-Platform C library for working with SteamWorks SDK!

It works as SteamWorks SDK API loader that allows to use SteamWorks SDK API from shared libraries...

To use it #define ICE_STEAM_IMPL then #include "ice_steam.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

TODO: Add

=================================== Library API ===================================

// Handle, Type definition for void* for symbols loaded from shared libs
typedef void* ice_steam_handle;

// Boolean Enum, To avoid including stdbool.h
typedef enum ice_steam_bool {
    ICE_STEAM_FALSE = -1,
    ICE_STEAM_TRUE = 0
} ice_steam_bool;

// [INTERNAL] Loads symbol from loaded SteamWorks shared library, Which can be casted to a function to call
ice_steam_handle ice_steam_proc(const char* symbol);

// Loads SteamWorks API from shared library path (eg. steam_api.dll on Windows), Returns ICE_STEAM_TRUE on success or ICE_STEAM_FALSE on failure
ice_steam_bool ice_steam_load(const char* path);

// Unloads SteamWorks API, Returns ICE_STEAM_TRUE on success or ICE_STEAM_FALSE on failure
ice_steam_bool ice_steam_unload(void);

================================== Linking Flags ==================================

1. Microsoft Windows    => -lkernel32
2. Linux                => -ldl

// NOTE: When using MSVC on Microsoft Windows, static libraries automatically linked via #pragmas


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_steam.h in the code...
#define ICE_STEAM_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_STEAM_VECTORCALL    // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_STEAM_FASTCALL      // fastcall
#define ICE_STEAM_STDCALL       // stdcall
#define ICE_STEAM_CDECL         // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_STEAM_MICROSOFT     // Microsoft platforms
#define ICE_STEAM_BEOS          // BeOS and Haiku
#define ICE_STEAM_UNIX          // Unix and Unix-like (Unix/Linux and anything else based on these)


// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_STEAM_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_STEAM_DLLEXPORT     // Export the symbols to build as shared library
#define ICE_STEAM_DLLIMPORT     // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_STEAM_INLINE        // inlines library functions (Only works on C99 Standard and above)
#define ICE_STEAM_EXTERN        // externs library functions
#define ICE_STEAM_STATIC        // statics library functions

// NOTES:
// 1. ICE_STEAM_EXTERN and ICE_STEAM_STATIC cannot be #defined together in the code...
// 2. The definitions ONLY affects the SteamWorks SDK loader API


================================= Support ice_libs ================================

ice_steam.h is one of libraries that ice_libs project provide...

You could support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs


*/

#ifndef ICE_STEAM_H
#define ICE_STEAM_H

/* Disable security warnings for MSVC compiler, We don't want to force using C11! */
#ifdef _MSC_VER
#  ifndef _CRT_SECURE_NO_DEPRECATE
#    define _CRT_SECURE_NO_DEPRECATE
#  endif
#  ifndef _CRT_SECURE_NO_WARNINGS
#    define _CRT_SECURE_NO_WARNINGS
#  endif
#  pragma warning(disable:4996)
#endif

/* Define C interface for Windows libraries! ;) */
#ifndef CINTERFACE
#  define CINTERFACE
#endif

/* Allow to use calling conventions if desired... */
#if defined(ICE_STEAM_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_STEAM_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_STEAM_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_STEAM_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_STEAM_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_STEAM_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_STEAM_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_STEAM_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_STEAM_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_STEAM_CDECL)
#  if defined(_MSC_VER)
#    define ICE_STEAM_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_STEAM_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_STEAM_CALLCONV
#endif

/* If no platform defined, This definition will define itself! */
#if !(defined(ICE_STEAM_MICROSOFT) || defined(ICE_STEAM_UNIX) || defined(ICE_STEAM_BEOS))
#  define ICE_STEAM_PLATFORM_AUTODETECTED
#endif

/* Platform detection */
#if defined(ICE_STEAM_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    define ICE_STEAM_MICROSOFT
#  elif defined(__HAIKU__) || defined(__BEOS__)
#    define ICE_STEAM_BEOS
#  elif defined(__unix__) || defined(__unix)
#    define ICE_STEAM_UNIX
#  else
#    error "ice_steam.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_STEAM_EXTERN) && defined(ICE_STEAM_STATIC))
#  define ICE_STEAM_EXTERN
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_STEAM_EXTERN)
#  define ICE_STEAM_APIDEF extern
#elif defined(ICE_STEAM_STATIC)
#  define ICE_STEAM_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_STEAM_INLINE to enable inline functionality.
*/
#if defined(ICE_STEAM_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_STEAM_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_STEAM_INLINEDEF inline
#  endif
#else
#  define ICE_STEAM_INLINEDEF
#endif

/*
Allow to build DLL via ICE_STEAM_DLLEXPORT or ICE_STEAM_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
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

/* SteamWorks SDK version that ice_steam loads */
#define ice_steam_steamworks_sdk_ver "v1.52"

/* [INTERNAL] Macro to ease definition of functions */
#define ice_steam_def_func(return_type, name, args) \
    typedef return_type (*PFN_##name) args;         \
    PFN_##name name;                                \

/* [INTERNAL] Macro to ease definition of opaque types */
#define ice_steam_def_opaque_type(t) typedef struct t t;

/* [INTERNAL] Macro to ease loading symbols */
#define ICE_STEAM_LOAD_PROC(sym)                    \
    sym = (PFN_##sym) ice_al_proc(#sym);            \

/* [INTERNAL] Macro to ease unloading symbols */
#define ICE_STEAM_UNLOAD_PROC(sym) sym = NULL;

#define S_CALLTYPE __cdecl

/* Steam-specific types. Defined here so this header file can be included in other code bases. */
#ifndef WCHARTYPES_H
typedef unsigned char uint8;
#endif

#if defined( __GNUC__ ) && !defined(_WIN32) && !defined(POSIX)
	#if __GNUC__ < 4
		#error "Steamworks requires GCC 4.X (4.2 or 4.4 have been tested)"
	#endif
	#define POSIX 1
#endif

#if defined(__LP64__) || defined(__x86_64__) || defined(_WIN64) || defined(__aarch64__) || defined(__s390x__)
#define X64BITS
#endif

#if !defined(VALVE_BIG_ENDIAN)
#if defined(_PS3)
/* Make sure VALVE_BIG_ENDIAN gets set on PS3, may already be set previously in Valve internal code. */
#define VALVE_BIG_ENDIAN 1
#endif
#if defined( __GNUC__ ) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define VALVE_BIG_ENDIAN 1
#endif
#endif

typedef unsigned char uint8;
typedef signed char int8;

#if defined( _WIN32 ) && !defined( __GNUC__ )

typedef __int16 int16;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;

typedef int64 lint64;
typedef uint64 ulint64;

#ifdef X64BITS
typedef __int64 intp;				/* intp is an integer that can accomodate a pointer */
typedef unsigned __int64 uintp;		/* (ie, sizeof(intp) >= sizeof(int) && sizeof(intp) >= sizeof(void *) */
#else
typedef __int32 intp;
typedef unsigned __int32 uintp;
#endif

#else /* _WIN32 */

typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

/*
[u]int64 are actually defined as 'long long' and gcc 64-bit
doesn't automatically consider them the same as 'long int'.
Changing the types for [u]int64 is complicated by
there being many definitions, so we just
define a 'long int' here and use it in places that would
otherwise confuse the compiler.
*/
typedef long int lint64;
typedef unsigned long int ulint64;

#ifdef X64BITS
typedef long long intp;
typedef unsigned long long uintp;
#else
typedef int intp;
typedef unsigned int uintp;
#endif

#endif /* else _WIN32 */

typedef uint32 AppId_t;
const AppId_t k_uAppIdInvalid = 0x0;

/* AppIds and DepotIDs also presently share the same namespace */
typedef uint32 DepotId_t;
const DepotId_t k_uDepotIdInvalid = 0x0;

/* RTime32.  Seconds elapsed since Jan 1 1970, i.e. unix timestamp. */
/* It's the same as time_t, but it is always 32-bit and unsigned.   */
typedef uint32 RTime32;

/* handle to a Steam API call */
typedef uint64 SteamAPICall_t;
const SteamAPICall_t k_uAPICallInvalid = 0x0;

typedef uint32 AccountID_t;

/* Party Beacon ID */
typedef uint64 PartyBeaconID_t;
const PartyBeaconID_t k_ulPartyBeaconIdInvalid = 0;

enum ESteamIPType
{
	k_ESteamIPTypeIPv4 = 0,
	k_ESteamIPTypeIPv6 = 1,
};

ice_steam_def_opaque_type(SteamIPAddress_t)

/* Steam universes.  Each universe is a self-contained Steam instance. */
enum EUniverse
{
	k_EUniverseInvalid = 0,
	k_EUniversePublic = 1,
	k_EUniverseBeta = 2,
	k_EUniverseInternal = 3,
	k_EUniverseDev = 4,
	/* k_EUniverseRC = 5, */				/* no such universe anymore */
	k_EUniverseMax
};

/* General result codes */
enum EResult
{
	k_EResultNone = 0,							/* no result */
	k_EResultOK	= 1,							/* success */
	k_EResultFail = 2,							/* generic failure  */
	k_EResultNoConnection = 3,					/* no/failed network connection */
/*	k_EResultNoConnectionRetry = 4, */			/* OBSOLETE - removed */
	k_EResultInvalidPassword = 5,				/* password/ticket is invalid */
	k_EResultLoggedInElsewhere = 6,				/* same user logged in elsewhere */
	k_EResultInvalidProtocolVer = 7,			/* protocol version is incorrect */
	k_EResultInvalidParam = 8,					/* a parameter is incorrect */
	k_EResultFileNotFound = 9,					/* file was not found */
	k_EResultBusy = 10,							/* called method busy - action not taken */
	k_EResultInvalidState = 11,					/* called object was in an invalid state */
	k_EResultInvalidName = 12,					/* name is invalid */
	k_EResultInvalidEmail = 13,					/* email is invalid */
	k_EResultDuplicateName = 14,				/* name is not unique */
	k_EResultAccessDenied = 15,					/* access is denied */
	k_EResultTimeout = 16,						/* operation timed out */
	k_EResultBanned = 17,						/* VAC2 banned */
	k_EResultAccountNotFound = 18,				/* account not found */
	k_EResultInvalidSteamID = 19,				/* steamID is invalid */
	k_EResultServiceUnavailable = 20,			/* The requested service is currently unavailable */
	k_EResultNotLoggedOn = 21,					/* The user is not logged on */
	k_EResultPending = 22,						/* Request is pending (may be in process, or waiting on third party) */
	k_EResultEncryptionFailure = 23,			/* Encryption or Decryption failed */
	k_EResultInsufficientPrivilege = 24,		/* Insufficient privilege */
	k_EResultLimitExceeded = 25,				/* Too much of a good thing */
	k_EResultRevoked = 26,						/* Access has been revoked (used for revoked guest passes) */
	k_EResultExpired = 27,						/* License/Guest pass the user is trying to access is expired */
	k_EResultAlreadyRedeemed = 28,				/* Guest pass has already been redeemed by account, cannot be acked again */
	k_EResultDuplicateRequest = 29,				/* The request is a duplicate and the action has already occurred in the past, ignored this time */
	k_EResultAlreadyOwned = 30,					/* All the games in this guest pass redemption request are already owned by the user */
	k_EResultIPNotFound = 31,					/* IP address not found */
	k_EResultPersistFailed = 32,				/* failed to write change to the data store */
	k_EResultLockingFailed = 33,				/* failed to acquire access lock for this operation */
	k_EResultLogonSessionReplaced = 34,
	k_EResultConnectFailed = 35,
	k_EResultHandshakeFailed = 36,
	k_EResultIOFailure = 37,
	k_EResultRemoteDisconnect = 38,
	k_EResultShoppingCartNotFound = 39,			/* failed to find the shopping cart requested */
	k_EResultBlocked = 40,						/* a user didn't allow it */
	k_EResultIgnored = 41,						/* target is ignoring sender */
	k_EResultNoMatch = 42,						/* nothing matching the request found */
	k_EResultAccountDisabled = 43,
	k_EResultServiceReadOnly = 44,				/* this service is not accepting content changes right now */
	k_EResultAccountNotFeatured = 45,			/* account doesn't have value, so this feature isn't available */
	k_EResultAdministratorOK = 46,				/* allowed to take this action, but only because requester is admin */
	k_EResultContentVersion = 47,				/* A Version mismatch in content transmitted within the Steam protocol. */
	k_EResultTryAnotherCM = 48,					/* The current CM can't service the user making a request, user should try another. */
	k_EResultPasswordRequiredToKickSession = 49,/* You are already logged in elsewhere, this cached credential login has failed. */
	k_EResultAlreadyLoggedInElsewhere = 50,		/* You are already logged in elsewhere, you must wait */
	k_EResultSuspended = 51,					/* Long running operation (content download) suspended/paused */
	k_EResultCancelled = 52,					/* Operation canceled (typically by user: content download) */
	k_EResultDataCorruption = 53,				/* Operation canceled because data is ill formed or unrecoverable */
	k_EResultDiskFull = 54,						/* Operation canceled - not enough disk space. */
	k_EResultRemoteCallFailed = 55,				/* an remote call or IPC call failed */
	k_EResultPasswordUnset = 56,				/* Password could not be verified as it's unset server side */
	k_EResultExternalAccountUnlinked = 57,		/* External account (PSN, Facebook...) is not linked to a Steam account */
	k_EResultPSNTicketInvalid = 58,				/* PSN ticket was invalid */
	k_EResultExternalAccountAlreadyLinked = 59,	/* External account (PSN, Facebook...) is already linked to some other account, must explicitly request to replace/delete the link first */
	k_EResultRemoteFileConflict = 60,			/* The sync cannot resume due to a conflict between the local and remote files */
	k_EResultIllegalPassword = 61,				/* The requested new password is not legal */
	k_EResultSameAsPreviousValue = 62,			/* new value is the same as the old one ( secret question and answer ) */
	k_EResultAccountLogonDenied = 63,			/* account login denied due to 2nd factor authentication failure */
	k_EResultCannotUseOldPassword = 64,			/* The requested new password is not legal */
	k_EResultInvalidLoginAuthCode = 65,			/* account login denied due to auth code invalid */
	k_EResultAccountLogonDeniedNoMail = 66,		/* account login denied due to 2nd factor auth failure - and no mail has been sent */
	k_EResultHardwareNotCapableOfIPT = 67,		/* */
	k_EResultIPTInitError = 68,					/* */
	k_EResultParentalControlRestricted = 69,	/* operation failed due to parental control restrictions for current user */
	k_EResultFacebookQueryError = 70,			/* Facebook query returned an error */
	k_EResultExpiredLoginAuthCode = 71,			/* account login denied due to auth code expired */
	k_EResultIPLoginRestrictionFailed = 72,
	k_EResultAccountLockedDown = 73,
	k_EResultAccountLogonDeniedVerifiedEmailRequired = 74,
	k_EResultNoMatchingURL = 75,
	k_EResultBadResponse = 76,					/* parse failure, missing field, etc. */
	k_EResultRequirePasswordReEntry = 77,		/* The user cannot complete the action until they re-enter their password */
	k_EResultValueOutOfRange = 78,				/* the value entered is outside the acceptable range */
	k_EResultUnexpectedError = 79,				/* something happened that we didn't expect to ever happen */
	k_EResultDisabled = 80,						/* The requested service has been configured to be unavailable */
	k_EResultInvalidCEGSubmission = 81,			/* The set of files submitted to the CEG server are not valid ! */
	k_EResultRestrictedDevice = 82,				/* The device being used is not allowed to perform this action */
	k_EResultRegionLocked = 83,					/* The action could not be complete because it is region restricted */
	k_EResultRateLimitExceeded = 84,			/* Temporary rate limit exceeded, try again later, different from k_EResultLimitExceeded which may be permanent */
	k_EResultAccountLoginDeniedNeedTwoFactor = 85,	/* Need two-factor code to login */
	k_EResultItemDeleted = 86,					/* The thing we're trying to access has been deleted */
	k_EResultAccountLoginDeniedThrottle = 87,	/* login attempt failed, try to throttle response to possible attacker */
	k_EResultTwoFactorCodeMismatch = 88,		/* two factor code mismatch */
	k_EResultTwoFactorActivationCodeMismatch = 89,	/* activation code for two-factor didn't match */
	k_EResultAccountAssociatedToMultiplePartners = 90,	/* account has been associated with multiple partners */
	k_EResultNotModified = 91,					/* data not modified */
	k_EResultNoMobileDevice = 92,				/* the account does not have a mobile device associated with it */
	k_EResultTimeNotSynced = 93,				/* the time presented is out of range or tolerance */
	k_EResultSmsCodeFailed = 94,				/* SMS code failure (no match, none pending, etc.) */
	k_EResultAccountLimitExceeded = 95,			/* Too many accounts access this resource */
	k_EResultAccountActivityLimitExceeded = 96,	/* Too many changes to this account */
	k_EResultPhoneActivityLimitExceeded = 97,	/* Too many changes to this phone */
	k_EResultRefundToWallet = 98,				/* Cannot refund to payment method, must use wallet */
	k_EResultEmailSendFailure = 99,				/* Cannot send an email */
	k_EResultNotSettled = 100,					/* Can't perform operation till payment has settled */
	k_EResultNeedCaptcha = 101,					/* Needs to provide a valid captcha */
	k_EResultGSLTDenied = 102,					/* a game server login token owned by this token's owner has been banned */
	k_EResultGSOwnerDenied = 103,				/* game server owner is denied for other reason (account lock, community ban, vac ban, missing phone) */
	k_EResultInvalidItemType = 104,				/* the type of thing we were requested to act on is invalid */
	k_EResultIPBanned = 105,					/* the ip address has been banned from taking this action */
	k_EResultGSLTExpired = 106,					/* this token has expired from disuse; can be reset for use */
	k_EResultInsufficientFunds = 107,			/* user doesn't have enough wallet funds to complete the action */
	k_EResultTooManyPending = 108,				/* There are too many of this thing pending already */
	k_EResultNoSiteLicensesFound = 109,			/* No site licenses found */
	k_EResultWGNetworkSendExceeded = 110,		/* the WG couldn't send a response because we exceeded max network send size */
	k_EResultAccountNotFriends = 111,			/* the user is not mutually friends */
	k_EResultLimitedUserAccount = 112,			/* the user is limited */
	k_EResultCantRemoveItem = 113,				/* item can't be removed */
	k_EResultAccountDeleted = 114,				/* account has been deleted */
	k_EResultExistingUserCancelledLicense = 115,	/* A license for this already exists, but cancelled */
	k_EResultCommunityCooldown = 116,			/* access is denied because of a community cooldown (probably from support profile data resets) */
	k_EResultNoLauncherSpecified = 117,			/* No launcher was specified, but a launcher was needed to choose correct realm for operation. */
	k_EResultMustAgreeToSSA = 118,				/* User must agree to china SSA or global SSA before login */
	k_EResultLauncherMigrated = 119,			/* The specified launcher type is no longer supported; the user should be directed elsewhere */
	k_EResultSteamRealmMismatch = 120,			/* The user's realm does not match the realm of the requested resource */
	k_EResultInvalidSignature = 121,			/* signature check did not match */
	k_EResultParseFailure = 122,				/* Failed to parse input */
};

/* Error codes for use with the voice functions */
enum EVoiceResult
{
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

};

/* Result codes to GSHandleClientDeny/Kick */
enum EDenyReason
{
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
};

/* return type of GetAuthSessionTicket */
typedef uint32 HAuthTicket;
const HAuthTicket k_HAuthTicketInvalid = 0;

/* results from BeginAuthSession */
enum EBeginAuthSessionResult
{
	k_EBeginAuthSessionResultOK = 0,						/* Ticket is valid for this game and this steamID. */
	k_EBeginAuthSessionResultInvalidTicket = 1,				/* Ticket is not valid. */
	k_EBeginAuthSessionResultDuplicateRequest = 2,			/* A ticket has already been submitted for this steamID */
	k_EBeginAuthSessionResultInvalidVersion = 3,			/* Ticket is from an incompatible interface version */
	k_EBeginAuthSessionResultGameMismatch = 4,				/* Ticket is not for this game */
	k_EBeginAuthSessionResultExpiredTicket = 5,				/* Ticket has expired */
};

/* Callback values for callback ValidateAuthTicketResponse_t which is a response to BeginAuthSession */
enum EAuthSessionResponse
{
	k_EAuthSessionResponseOK = 0,							/* Steam has verified the user is online, the ticket is valid and ticket has not been reused. */
	k_EAuthSessionResponseUserNotConnectedToSteam = 1,		/* The user in question is not connected to steam */
	k_EAuthSessionResponseNoLicenseOrExpired = 2,			/* The license has expired. */
	k_EAuthSessionResponseVACBanned = 3,					/* The user is VAC banned for this game. */
	k_EAuthSessionResponseLoggedInElseWhere = 4,			/* The user account has logged in elsewhere and the session containing the game instance has been disconnected. */
	k_EAuthSessionResponseVACCheckTimedOut = 5,				/* VAC has been unable to perform anti-cheat checks on this user */
	k_EAuthSessionResponseAuthTicketCanceled = 6,			/* The ticket has been canceled by the issuer */
	k_EAuthSessionResponseAuthTicketInvalidAlreadyUsed = 7,	/* This ticket has already been used, it is not valid. */
	k_EAuthSessionResponseAuthTicketInvalid = 8,			/* This ticket is not from a user instance currently connected to steam. */
	k_EAuthSessionResponsePublisherIssuedBan = 9,			/* The user is banned for this game. The ban came via the web api and not VAC */
};

/* results from UserHasLicenseForApp */
enum EUserHasLicenseForAppResult
{
	k_EUserHasLicenseResultHasLicense = 0,					/* User has a license for specified app */
	k_EUserHasLicenseResultDoesNotHaveLicense = 1,			/* User does not have a license for the specified app */
	k_EUserHasLicenseResultNoAuth = 2,						/* User has not been authenticated */
};


/* Steam account types */
enum EAccountType
{
	k_EAccountTypeInvalid = 0,			
	k_EAccountTypeIndividual = 1,		/* single user account */
	k_EAccountTypeMultiseat = 2,		/* multiseat (e.g. cybercafe) account */
	k_EAccountTypeGameServer = 3,		/* game server account */
	k_EAccountTypeAnonGameServer = 4,	/* anonymous game server account */
	k_EAccountTypePending = 5,			/* pending */
	k_EAccountTypeContentServer = 6,	/* content server */
	k_EAccountTypeClan = 7,
	k_EAccountTypeChat = 8,
	k_EAccountTypeConsoleUser = 9,		/* Fake SteamID for local PSN account on PS3 or Live account on 360, etc. */
	k_EAccountTypeAnonUser = 10,

	/* Max of 16 items in this field */
	k_EAccountTypeMax
};



/*-----------------------------------------------------------------------------*/
/* Purpose: Chat Entry Types (previously was only friend-to-friend message types) */
/*-----------------------------------------------------------------------------*/
enum EChatEntryType
{
	k_EChatEntryTypeInvalid = 0, 
	k_EChatEntryTypeChatMsg = 1,		/* Normal text message from another user */
	k_EChatEntryTypeTyping = 2,			/* Another user is typing (not used in multi-user chat) */
	k_EChatEntryTypeInviteGame = 3,		/* Invite from other user into that users current game */
	k_EChatEntryTypeEmote = 4,			/* text emote message (deprecated, should be treated as ChatMsg) */
	/*k_EChatEntryTypeLobbyGameStart = 5,*/	/* lobby game is starting (dead - listen for LobbyGameCreated_t callback instead) */
	k_EChatEntryTypeLeftConversation = 6, /* user has left the conversation ( closed chat window ) */
	/* Above are previous FriendMsgType entries, now merged into more generic chat entry types */
	k_EChatEntryTypeEntered = 7,		/* user has entered the conversation (used in multi-user chat and group chat) */
	k_EChatEntryTypeWasKicked = 8,		/* user was kicked (data: 64-bit steamid of actor performing the kick) */
	k_EChatEntryTypeWasBanned = 9,		/* user was banned (data: 64-bit steamid of actor performing the ban) */
	k_EChatEntryTypeDisconnected = 10,	/* user disconnected */
	k_EChatEntryTypeHistoricalChat = 11,	/* a chat message from user's chat history or offilne message */
	/*k_EChatEntryTypeReserved1 = 12,*/ /* No longer used */
	/*k_EChatEntryTypeReserved2 = 13,*/ /* No longer used */
	k_EChatEntryTypeLinkBlocked = 14, /* a link was removed by the chat filter. */
};


/*----------------------------------------------------------------------------- */
/* Purpose: Chat Room Enter Responses */
/*----------------------------------------------------------------------------- */
enum EChatRoomEnterResponse
{
	k_EChatRoomEnterResponseSuccess = 1,		/* Success */
	k_EChatRoomEnterResponseDoesntExist = 2,	/* Chat doesn't exist (probably closed) */
	k_EChatRoomEnterResponseNotAllowed = 3,		/* General Denied - You don't have the permissions needed to join the chat */
	k_EChatRoomEnterResponseFull = 4,			/* Chat room has reached its maximum size */
	k_EChatRoomEnterResponseError = 5,			/* Unexpected Error */
	k_EChatRoomEnterResponseBanned = 6,			/* You are banned from this chat room and may not join */
	k_EChatRoomEnterResponseLimited = 7,		/* Joining this chat is not allowed because you are a limited user (no value on account) */
	k_EChatRoomEnterResponseClanDisabled = 8,	/* Attempt to join a clan chat when the clan is locked or disabled */
	k_EChatRoomEnterResponseCommunityBan = 9,	/* Attempt to join a chat when the user has a community lock on their account */
	k_EChatRoomEnterResponseMemberBlockedYou = 10, /* Join failed - some member in the chat has blocked you from joining */
	k_EChatRoomEnterResponseYouBlockedMember = 11, /* Join failed - you have blocked some member already in the chat */
	/* k_EChatRoomEnterResponseNoRankingDataLobby = 12, */  /* No longer used */
	/* k_EChatRoomEnterResponseNoRankingDataUser = 13, */  /*  No longer used */
	/* k_EChatRoomEnterResponseRankOutOfRange = 14, */ /*  No longer used */
	k_EChatRoomEnterResponseRatelimitExceeded = 15, /* Join failed - to many join attempts in a very short period of time */
};


const unsigned int k_unSteamAccountIDMask = 0xFFFFFFFF;
const unsigned int k_unSteamAccountInstanceMask = 0x000FFFFF;
const unsigned int k_unSteamUserDefaultInstance	= 1; /* fixed instance for all individual users */

/* Special flags for Chat accounts - they go in the top 8 bits */
/* of the steam ID's "instance", leaving 12 for the actual instances */
enum EChatSteamIDInstanceFlags
{
	k_EChatAccountInstanceMask = 0x00000FFF, /* top 8 bits are flags */

	k_EChatInstanceFlagClan = ( k_unSteamAccountInstanceMask + 1 ) >> 1,	/* top bit */
	k_EChatInstanceFlagLobby = ( k_unSteamAccountInstanceMask + 1 ) >> 2,	/* next one down, etc */
	k_EChatInstanceFlagMMSLobby = ( k_unSteamAccountInstanceMask + 1 ) >> 3,	/* next one down, etc */

	/* Max of 8 flags */
};


/*----------------------------------------------------------------------------- */
/* Purpose: Possible positions to tell the overlay to show notifications in */
/*----------------------------------------------------------------------------- */
enum ENotificationPosition
{
	k_EPositionTopLeft = 0,
	k_EPositionTopRight = 1,
	k_EPositionBottomLeft = 2,
	k_EPositionBottomRight = 3,
};


/*----------------------------------------------------------------------------- */
/* Purpose: Broadcast upload result details */
/*----------------------------------------------------------------------------- */
enum EBroadcastUploadResult
{
	k_EBroadcastUploadResultNone = 0,	/* broadcast state unknown */
	k_EBroadcastUploadResultOK = 1,		/* broadcast was good, no problems */
	k_EBroadcastUploadResultInitFailed = 2,	/* broadcast init failed */
	k_EBroadcastUploadResultFrameFailed = 3,	/* broadcast frame upload failed */
	k_EBroadcastUploadResultTimeout = 4,	/* broadcast upload timed out */
	k_EBroadcastUploadResultBandwidthExceeded = 5,	/* broadcast send too much data */
	k_EBroadcastUploadResultLowFPS = 6,	/* broadcast FPS too low */
	k_EBroadcastUploadResultMissingKeyFrames = 7,	/* broadcast sending not enough key frames */
	k_EBroadcastUploadResultNoConnection = 8,	/* broadcast client failed to connect to relay */
	k_EBroadcastUploadResultRelayFailed = 9,	/* relay dropped the upload */
	k_EBroadcastUploadResultSettingsChanged = 10,	/* the client changed broadcast settings */
	k_EBroadcastUploadResultMissingAudio = 11,	/* client failed to send audio data */
	k_EBroadcastUploadResultTooFarBehind = 12,	/* clients was too slow uploading */
	k_EBroadcastUploadResultTranscodeBehind = 13,	/* server failed to keep up with transcode */
	k_EBroadcastUploadResultNotAllowedToPlay = 14, /* Broadcast does not have permissions to play game */
	k_EBroadcastUploadResultBusy = 15, /* RTMP host to busy to take new broadcast stream, choose another */
	k_EBroadcastUploadResultBanned = 16, /* Account banned from community broadcast */
	k_EBroadcastUploadResultAlreadyActive = 17, /* We already already have an stream running. */
	k_EBroadcastUploadResultForcedOff = 18, /* We explicitly shutting down a broadcast */
	k_EBroadcastUploadResultAudioBehind = 19, /* Audio stream was too far behind video */
	k_EBroadcastUploadResultShutdown = 20,	/* Broadcast Server was shut down */
	k_EBroadcastUploadResultDisconnect = 21,	/* broadcast uploader TCP disconnected */ 
	k_EBroadcastUploadResultVideoInitFailed = 22,	/* invalid video settings  */
	k_EBroadcastUploadResultAudioInitFailed = 23,	/* invalid audio settings */
};


/*
-----------------------------------------------------------------------------
   Purpose: Reasons a user may not use the Community Market.
            Used in MarketEligibilityResponse_t.
-----------------------------------------------------------------------------
*/
enum EMarketNotAllowedReasonFlags
{
	k_EMarketNotAllowedReason_None = 0,

	/* A back-end call failed or something that might work again on retry */
	k_EMarketNotAllowedReason_TemporaryFailure = (1 << 0),

	/* Disabled account */
	k_EMarketNotAllowedReason_AccountDisabled = (1 << 1),

	/* Locked account */
	k_EMarketNotAllowedReason_AccountLockedDown = (1 << 2),

	/* Limited account (no purchases) */
	k_EMarketNotAllowedReason_AccountLimited = (1 << 3),

	/* The account is banned from trading items */
	k_EMarketNotAllowedReason_TradeBanned = (1 << 4),

	/* Wallet funds aren't tradable because the user has had no purchase
	   activity in the last year or has had no purchases prior to last month */
	k_EMarketNotAllowedReason_AccountNotTrusted = (1 << 5),

	/* The user doesn't have Steam Guard enabled */
	k_EMarketNotAllowedReason_SteamGuardNotEnabled = (1 << 6),

	/* The user has Steam Guard, but it hasn't been enabled for the required number of days */
	k_EMarketNotAllowedReason_SteamGuardOnlyRecentlyEnabled = (1 << 7),

	/* The user has recently forgotten their password and reset it */
	k_EMarketNotAllowedReason_RecentPasswordReset = (1 << 8),

	/* The user has recently funded his or her wallet with a new payment method */
	k_EMarketNotAllowedReason_NewPaymentMethod = (1 << 9),

	/* An invalid cookie was sent by the user */
	k_EMarketNotAllowedReason_InvalidCookie = (1 << 10),

	/* The user has Steam Guard, but is using a new computer or web browser */
	k_EMarketNotAllowedReason_UsingNewDevice = (1 << 11),

	/* The user has recently refunded a store purchase by his or herself */
	k_EMarketNotAllowedReason_RecentSelfRefund = (1 << 12),

	/* The user has recently funded his or her wallet with a new payment method that cannot be verified */
	k_EMarketNotAllowedReason_NewPaymentMethodCannotBeVerified = (1 << 13),

	/* Not only is the account not trusted, but they have no recent purchases at all */
	k_EMarketNotAllowedReason_NoRecentPurchases = (1 << 14),

	/* User accepted a wallet gift that was recently purchased */
	k_EMarketNotAllowedReason_AcceptedWalletGift = (1 << 15),
};


/*
  describes XP / progress restrictions to apply for games with duration control /
  anti-indulgence enabled for minor Steam China users.
*/
/* WARNING: DO NOT RENUMBER */
enum EDurationControlProgress
{
	k_EDurationControlProgress_Full = 0,	/* Full progress */
	k_EDurationControlProgress_Half = 1,	/* deprecated - XP or persistent rewards should be halved */
	k_EDurationControlProgress_None = 2,	/* deprecated - XP or persistent rewards should be stopped */

	k_EDurationControl_ExitSoon_3h = 3,		/* allowed 3h time since 5h gap/break has elapsed, game should exit - steam will terminate the game soon */
	k_EDurationControl_ExitSoon_5h = 4,		/* allowed 5h time in calendar day has elapsed, game should exit - steam will terminate the game soon */
	k_EDurationControl_ExitSoon_Night = 5,	/* game running after day period, game should exit - steam will terminate the game soon */
};


/* describes which notification timer has expired, for steam china duration control feature */
/* WARNING: DO NOT RENUMBER */
enum EDurationControlNotification
{
	k_EDurationControlNotification_None = 0,		/* just informing you about progress, no notification to show */
	k_EDurationControlNotification_1Hour = 1,		/* "you've been playing for N hours" */
	
	k_EDurationControlNotification_3Hours = 2,		/* deprecated - "you've been playing for 3 hours; take a break" */
	k_EDurationControlNotification_HalfProgress = 3,/* deprecated - "your XP / progress is half normal" */
	k_EDurationControlNotification_NoProgress = 4,	/* deprecated - "your XP / progress is zero" */
	
	k_EDurationControlNotification_ExitSoon_3h = 5,	/* allowed 3h time since 5h gap/break has elapsed, game should exit - steam will terminate the game soon */
	k_EDurationControlNotification_ExitSoon_5h = 6,	/* allowed 5h time in calendar day has elapsed, game should exit - steam will terminate the game soon */
	k_EDurationControlNotification_ExitSoon_Night = 7,/* game running after day period, game should exit - steam will terminate the game soon */
};

/*
Specifies a game's online state in relation to duration control
*/
enum EDurationControlOnlineState
{
	k_EDurationControlOnlineState_Invalid = 0,				/* nil value */
	k_EDurationControlOnlineState_Offline = 1,				/* currently in offline play - single-player, offline co-op, etc. */
	k_EDurationControlOnlineState_Online = 2,				/* currently in online play */
	k_EDurationControlOnlineState_OnlineHighPri = 3,		/* currently in online play and requests not to be interrupted */
};

const int k_cchGameExtraInfoMax = 64;

/*
-----------------------------------------------------------------------------
Purpose: Passed as argument to SteamAPI_UseBreakpadCrashHandler to enable optional callback
just before minidump file is captured after a crash has occurred.  (Allows app to append additional comment data to the dump, etc.)
-----------------------------------------------------------------------------
*/
typedef void (*PFNPreMinidumpCallback)(void *context);

enum EGameSearchErrorCode_t
{
	k_EGameSearchErrorCode_OK = 1,
	k_EGameSearchErrorCode_Failed_Search_Already_In_Progress = 2,
	k_EGameSearchErrorCode_Failed_No_Search_In_Progress = 3,
	k_EGameSearchErrorCode_Failed_Not_Lobby_Leader = 4, /* if not the lobby leader can not call SearchForGameWithLobby */
	k_EGameSearchErrorCode_Failed_No_Host_Available = 5, /* no host is available that matches those search params */
	k_EGameSearchErrorCode_Failed_Search_Params_Invalid = 6, /* search params are invalid */
	k_EGameSearchErrorCode_Failed_Offline = 7, /* offline, could not communicate with server */
	k_EGameSearchErrorCode_Failed_NotAuthorized = 8, /* either the user or the application does not have priveledges to do this */
	k_EGameSearchErrorCode_Failed_Unknown_Error = 9, /* unknown error */
};

enum EPlayerResult_t
{
	k_EPlayerResultFailedToConnect = 1, /* failed to connect after confirming */
	k_EPlayerResultAbandoned = 2,		/* quit game without completing it */
	k_EPlayerResultKicked = 3,			/* kicked by other players/moderator/server rules */
	k_EPlayerResultIncomplete = 4,		/* player stayed to end but game did not conclude successfully ( nofault to player ) */
	k_EPlayerResultCompleted = 5,		/* player completed game */
};


enum ESteamIPv6ConnectivityProtocol
{
	k_ESteamIPv6ConnectivityProtocol_Invalid = 0,
	k_ESteamIPv6ConnectivityProtocol_HTTP = 1,		/* because a proxy may make this different than other protocols */
	k_ESteamIPv6ConnectivityProtocol_UDP = 2,		/* test UDP connectivity. Uses a port that is commonly needed for other Steam stuff. If UDP works, TCP probably works.  */
};

/* For the above transport protocol, what do we think the local machine's connectivity to the internet over ipv6 is like */
enum ESteamIPv6ConnectivityState
{
	k_ESteamIPv6ConnectivityState_Unknown = 0,	/* We haven't run a test yet */
	k_ESteamIPv6ConnectivityState_Good = 1,		/* We have recently been able to make a request on ipv6 for the given protocol */
	k_ESteamIPv6ConnectivityState_Bad = 2,		/* We failed to make a request, either because this machine has no ipv6 address assigned, or it has no upstream connectivity */
};


/* Define compile time assert macros to let us validate the structure sizes. */
#define VALVE_COMPILE_TIME_ASSERT( pred ) typedef char compile_time_assert_type[(pred) ? 1 : -1];

typedef struct ValvePackingSentinel_t
{
    uint32 m_u32;
    uint64 m_u64;
    uint16 m_u16;
    double m_d;
} ValvePackingSentinel_t;

#define CSTEAMID_DEFINED
ice_steam_def_opaque_type(CSteamID)
ice_steam_def_opaque_type(CGameID)

/* S_API defines the linkage and calling conventions for steam_api.dll exports */
#if defined( _WIN32 ) && !defined( _X360 )
	#if defined( STEAM_API_EXPORTS )
	#define S_API extern "C" __declspec( dllexport ) 
	#elif defined( STEAM_API_NODLL )
	#define S_API extern "C"
	#else
	#define S_API extern "C" __declspec( dllimport ) 
	#endif /* STEAM_API_EXPORTS */
#elif defined( GNUC )
	#if defined( STEAM_API_EXPORTS )
	#define S_API extern "C" __attribute__ ((visibility("default"))) 
	#else
	#define S_API extern "C" 
	#endif /* STEAM_API_EXPORTS */
#else /* !WIN32 */
	#if defined( STEAM_API_EXPORTS )
	#define S_API extern "C"  
	#else
	#define S_API extern "C" 
	#endif /* STEAM_API_EXPORTS */
#endif

#if ( defined(STEAM_API_EXPORTS) || defined(STEAM_API_NODLL) ) && !defined(API_GEN)
#define STEAM_PRIVATE_API( ... ) __VA_ARGS__
#elif defined(STEAM_API_EXPORTS) && defined(API_GEN)
#define STEAM_PRIVATE_API( ... )
#else
#define STEAM_PRIVATE_API( ... ) protected: __VA_ARGS__ public:
#endif

/* Macros used to annotate various Steamworks interfaces to generate the flat API */
#ifdef API_GEN
# define STEAM_CLANG_ATTR(ATTR) __attribute__((annotate( ATTR )))
#else
# define STEAM_CLANG_ATTR(ATTR)
#endif

/* handle to a communication pipe to the Steam client */
typedef int32 HSteamPipe;
/* handle to single instance of a steam user */
typedef int32 HSteamUser;

typedef void (__cdecl *SteamAPIWarningMessageHook_t)(int, const char *);
typedef uint32 ( *SteamAPI_CheckCallbackRegistered_t )(int iCallbackNum);

/* Dispatch all queued Steamworks callbacks. */
/*
This is safe to call from multiple threads simultaneously,
but if you choose to do this, callback code could be executed on any thread.
One alternative is to call SteamAPI_RunCallbacks from the main thread only,
and call SteamAPI_ReleaseCurrentThreadMemory regularly on other threads.
*/
ice_steam_def_func(void, SteamAPI_RunCallbacks, ())

/*
Declares a callback member function plus a helper member variable which
registers the callback on object creation and unregisters on destruction.
The optional fourth 'var' param exists only for backwards-compatibility and can be ignored.
*/
#define STEAM_CALLBACK( thisclass, func, .../*callback_type, [deprecated] var*/ ) \
	_STEAM_CALLBACK_SELECT( ( __VA_ARGS__, 4, 3 ), ( /**/, thisclass, func, __VA_ARGS__ ) )

/*
Dispatch callbacks relevant to the gameserver client and interfaces.
To register for these, you need to use STEAM_GAMESERVER_CALLBACK.
(Or call SetGameserverFlag on your CCallbackBase object.)
*/
ice_steam_def_func(void, SteamGameServer_RunCallbacks, ())

ice_steam_def_opaque_type(CCallbackBase)
ice_steam_def_opaque_type(CCallbackImpl)
ice_steam_def_opaque_type(CCallResult)
ice_steam_def_opaque_type(CCallback)
ice_steam_def_opaque_type(CCallbackManual)

/* Internal functions used to locate/create interfaces */
ice_steam_def_func(HSteamPipe, SteamAPI_GetHSteamPipe, ())
ice_steam_def_func(HSteamUser, SteamAPI_GetHSteamUser, ())
ice_steam_def_func(HSteamPipe, SteamGameServer_GetHSteamPipe, ())
ice_steam_def_func(HSteamUser, SteamGameServer_GetHSteamUser, ())
ice_steam_def_func(void*, SteamInternal_ContextInit, (void* pContextInitData))
ice_steam_def_func(void*, SteamInternal_CreateInterface, (const char* var))
ice_steam_def_func(void*, SteamInternal_FindOrCreateUserInterface, (HSteamUser hSteamUser, const char *pszVersion))
ice_steam_def_func(void*, SteamInternal_FindOrCreateGameServerInterface, (HSteamUser hSteamUser, const char *pszVersion))

/*
Macro used to define a type-safe accessor that will always return the version
of the interface of the *header file* you are compiling with!  We also bounce
through a safety function that checks for interfaces being created or destroyed.
*/

/*
SteamInternal_ContextInit takes a base pointer for the equivalent of
struct { void (*pFn)(void* pCtx); uintptr_t counter; void *ptr; }
*/

/* Do not change layout or add non-pointer aligned data! */
#define STEAM_DEFINE_INTERFACE_ACCESSOR(type, name, expr, kind, version ) \
	void SteamInternal_Init_##name(type *p) { *p = (type)(expr); } \
	STEAM_CLANG_ATTR("interface_accessor_kind:" kind ";interface_accessor_version:" version ";") \
	type name() { \
		static void* s_CallbackCounterAndContext[ 3 ] = { (void*)&SteamInternal_Init_ ## name, 0, 0 }; \
		return *(type*)SteamInternal_ContextInit(s_CallbackCounterAndContext); \
	}

#define STEAM_DEFINE_USER_INTERFACE_ACCESSOR(type, name, version) \
	STEAM_DEFINE_INTERFACE_ACCESSOR(type, name, SteamInternal_FindOrCreateUserInterface(SteamAPI_GetHSteamUser(), version), "user", version)
#define STEAM_DEFINE_GAMESERVER_INTERFACE_ACCESSOR(type, name, version) \
	STEAM_DEFINE_INTERFACE_ACCESSOR(type, name, SteamInternal_FindOrCreateGameServerInterface(SteamGameServer_GetHSteamUser(), version), "gameserver", version)

struct CallbackMsg_t
{
	HSteamUser m_hSteamUser; /* Specific user to whom this callback applies. */
	int m_iCallback; /* Callback identifier.  (Corresponds to the k_iCallback enum in the callback structure.) */
	uint8 *m_pubParam; /* Points to the callback structure */
	int m_cubParam; /* Size of the data pointed to by m_pubParam */
};

/* Macros to define steam callback structures.  Used internally for debugging */
#ifdef STEAM_CALLBACK_INSPECTION_ENABLED
	#include "../../clientdll/steam_api_callback_inspection.h"
#else
	#define STEAM_CALLBACK_BEGIN(callbackname, callbackid)	struct callbackname { enum { k_iCallback = callbackid };
	#define STEAM_CALLBACK_MEMBER(varidx, vartype, varname)	vartype varname; 
	#define STEAM_CALLBACK_MEMBER_ARRAY(varidx, vartype, varname, varcount) vartype varname [varcount];
	#define STEAM_CALLBACK_END(nArgs) };
#endif

/* Forward declare all of the Steam interfaces.  (Do we really need to do this?) */
ice_steam_def_opaque_type(ISteamClient)
ice_steam_def_opaque_type(ISteamUser)
ice_steam_def_opaque_type(ISteamGameServer)
ice_steam_def_opaque_type(ISteamFriends)
ice_steam_def_opaque_type(ISteamUtils)
ice_steam_def_opaque_type(ISteamMatchmaking)
ice_steam_def_opaque_type(ISteamContentServer)
ice_steam_def_opaque_type(ISteamMatchmakingServers)
ice_steam_def_opaque_type(ISteamUserStats)
ice_steam_def_opaque_type(ISteamApps)
ice_steam_def_opaque_type(ISteamNetworking)
ice_steam_def_opaque_type(ISteamRemoteStorage)
ice_steam_def_opaque_type(ISteamScreenshots)
ice_steam_def_opaque_type(ISteamMusic)
ice_steam_def_opaque_type(ISteamMusicRemote)
ice_steam_def_opaque_type(ISteamGameServerStats)
ice_steam_def_opaque_type(ISteamPS3OverlayRender)
ice_steam_def_opaque_type(ISteamHTTP)
ice_steam_def_opaque_type(ISteamController)
ice_steam_def_opaque_type(ISteamUGC)
ice_steam_def_opaque_type(ISteamAppList)
ice_steam_def_opaque_type(ISteamHTMLSurface)
ice_steam_def_opaque_type(ISteamInventory)
ice_steam_def_opaque_type(ISteamVideo)
ice_steam_def_opaque_type(ISteamParentalSettings)
ice_steam_def_opaque_type(ISteamGameSearch)
ice_steam_def_opaque_type(ISteamInput)
ice_steam_def_opaque_type(ISteamParties)
ice_steam_def_opaque_type(ISteamRemotePlay)

/*
-----------------------------------------------------------------------------
 Purpose: Base values for callback identifiers, each callback must
			have a unique ID.
-----------------------------------------------------------------------------
*/
enum { k_iSteamUserCallbacks = 100 };
enum { k_iSteamGameServerCallbacks = 200 };
enum { k_iSteamFriendsCallbacks = 300 };
enum { k_iSteamBillingCallbacks = 400 };
enum { k_iSteamMatchmakingCallbacks = 500 };
enum { k_iSteamContentServerCallbacks = 600 };
enum { k_iSteamUtilsCallbacks = 700 };
enum { k_iClientFriendsCallbacks = 800 };
enum { k_iClientUserCallbacks = 900 };
enum { k_iSteamAppsCallbacks = 1000 };
enum { k_iSteamUserStatsCallbacks = 1100 };
enum { k_iSteamNetworkingCallbacks = 1200 };
enum { k_iSteamNetworkingSocketsCallbacks = 1220 };
enum { k_iSteamNetworkingMessagesCallbacks = 1250 };
enum { k_iSteamNetworkingUtilsCallbacks = 1280 };
enum { k_iClientRemoteStorageCallbacks = 1300 };
enum { k_iClientDepotBuilderCallbacks = 1400 };
enum { k_iSteamGameServerItemsCallbacks = 1500 };
enum { k_iClientUtilsCallbacks = 1600 };
enum { k_iSteamGameCoordinatorCallbacks = 1700 };
enum { k_iSteamGameServerStatsCallbacks = 1800 };
enum { k_iSteam2AsyncCallbacks = 1900 };
enum { k_iSteamGameStatsCallbacks = 2000 };
enum { k_iClientHTTPCallbacks = 2100 };
enum { k_iClientScreenshotsCallbacks = 2200 };
enum { k_iSteamScreenshotsCallbacks = 2300 };
enum { k_iClientAudioCallbacks = 2400 };
enum { k_iClientUnifiedMessagesCallbacks = 2500 };
enum { k_iSteamStreamLauncherCallbacks = 2600 };
enum { k_iClientControllerCallbacks = 2700 };
enum { k_iSteamControllerCallbacks = 2800 };
enum { k_iClientParentalSettingsCallbacks = 2900 };
enum { k_iClientDeviceAuthCallbacks = 3000 };
enum { k_iClientNetworkDeviceManagerCallbacks = 3100 };
enum { k_iClientMusicCallbacks = 3200 };
enum { k_iClientRemoteClientManagerCallbacks = 3300 };
enum { k_iClientUGCCallbacks = 3400 };
enum { k_iSteamStreamClientCallbacks = 3500 };
enum { k_IClientProductBuilderCallbacks = 3600 };
enum { k_iClientShortcutsCallbacks = 3700 };
enum { k_iClientRemoteControlManagerCallbacks = 3800 };
enum { k_iSteamAppListCallbacks = 3900 };
enum { k_iSteamMusicCallbacks = 4000 };
enum { k_iSteamMusicRemoteCallbacks = 4100 };
enum { k_iClientVRCallbacks = 4200 };
enum { k_iClientGameNotificationCallbacks = 4300 }; 
enum { k_iSteamGameNotificationCallbacks = 4400 }; 
enum { k_iSteamHTMLSurfaceCallbacks = 4500 };
enum { k_iClientVideoCallbacks = 4600 };
enum { k_iClientInventoryCallbacks = 4700 };
enum { k_iClientBluetoothManagerCallbacks = 4800 };
enum { k_iClientSharedConnectionCallbacks = 4900 };
enum { k_ISteamParentalSettingsCallbacks = 5000 };
enum { k_iClientShaderCallbacks = 5100 };
enum { k_iSteamGameSearchCallbacks = 5200 };
enum { k_iSteamPartiesCallbacks = 5300 };
enum { k_iClientPartiesCallbacks = 5400 };
enum { k_iSteamSTARCallbacks = 5500 };
enum { k_iClientSTARCallbacks = 5600 };
enum { k_iSteamRemotePlayCallbacks = 5700 };
enum { k_iClientCompatCallbacks = 5800 };
enum { k_iSteamChatCallbacks = 5900 };
enum { k_iClientNetworkingUtilsCallbacks = 6000 };
enum { k_iClientSystemManagerCallbacks = 6100 };
enum { k_iClientStorageDeviceManagerCallbacks = 6200 };

#define STEAM_OUT_STRUCT() STEAM_CLANG_ATTR( "out_struct: ;" )
#define STEAM_OUT_STRING() STEAM_CLANG_ATTR( "out_string: ;" )
#define STEAM_OUT_ARRAY_CALL(COUNTER,FUNCTION,PARAMS) STEAM_CLANG_ATTR( "out_array_call:" #COUNTER "," #FUNCTION "," #PARAMS ";" )
#define STEAM_OUT_ARRAY_COUNT(COUNTER, DESC) STEAM_CLANG_ATTR( "out_array_count:" #COUNTER  ";desc:" #DESC )
#define STEAM_ARRAY_COUNT(COUNTER) STEAM_CLANG_ATTR( "array_count:" #COUNTER ";" )
#define STEAM_ARRAY_COUNT_D(COUNTER, DESC) STEAM_CLANG_ATTR( "array_count:" #COUNTER ";desc:" #DESC )
#define STEAM_BUFFER_COUNT(COUNTER) STEAM_CLANG_ATTR( "buffer_count:" #COUNTER ";" )
#define STEAM_OUT_BUFFER_COUNT(COUNTER) STEAM_CLANG_ATTR( "out_buffer_count:" #COUNTER ";" )
#define STEAM_OUT_STRING_COUNT(COUNTER) STEAM_CLANG_ATTR( "out_string_count:" #COUNTER ";" )
#define STEAM_DESC(DESC) STEAM_CLANG_ATTR("desc:" #DESC ";")
#define STEAM_CALL_RESULT(RESULT_TYPE) STEAM_CLANG_ATTR("callresult:" #RESULT_TYPE ";")
#define STEAM_CALL_BACK(RESULT_TYPE) STEAM_CLANG_ATTR("callback:" #RESULT_TYPE ";")
#define STEAM_FLAT_NAME(NAME) STEAM_CLANG_ATTR("flat_name:" #NAME ";")

ice_steam_def_opaque_type(CSteamAPIContext)
ice_steam_def_opaque_type(CSteamGameServerAPIContext)

#define STEAMCLIENT_INTERFACE_VERSION "SteamClient020"

ice_steam_def_func(ISteamClient*, SteamClient, ())
ice_steam_def_func(ISteamClient*, SteamGameServerClient, ())

/*STEAM_DEFINE_INTERFACE_ACCESSOR(ISteamClient *, SteamClient, SteamInternal_CreateInterface( STEAMCLIENT_INTERFACE_VERSION ), "global", STEAMCLIENT_INTERFACE_VERSION);*/

#define STEAMUSER_INTERFACE_VERSION "SteamUser021"

ice_steam_def_func(ISteamUser*, SteamUser, ())

/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR(ISteamUser *, SteamUser, STEAMUSER_INTERFACE_VERSION);*/

enum EFriendRelationship
{
	k_EFriendRelationshipNone = 0,
	k_EFriendRelationshipBlocked = 1,			/* this doesn't get stored; the user has just done an Ignore on an friendship invite */
	k_EFriendRelationshipRequestRecipient = 2,
	k_EFriendRelationshipFriend = 3,
	k_EFriendRelationshipRequestInitiator = 4,
	k_EFriendRelationshipIgnored = 5,			/* this is stored; the user has explicit blocked this other user from comments/chat/etc */
	k_EFriendRelationshipIgnoredFriend = 6,
	k_EFriendRelationshipSuggested_DEPRECATED = 7,		/* was used by the original implementation of the facebook linking feature, but now unused. */

	/* keep this updated */
	k_EFriendRelationshipMax = 8,
};

/* maximum length of friend group name (not including terminating nul!) */
const int k_cchMaxFriendsGroupName = 64;

/* maximum number of groups a single user is allowed */
const int k_cFriendsGroupLimit = 100;

/* friends group identifier type */
typedef int16 FriendsGroupID_t;

/* invalid friends group identifier constant */
const FriendsGroupID_t k_FriendsGroupID_Invalid = -1;

const int k_cEnumerateFollowersMax = 50;

/*
-----------------------------------------------------------------------------
Purpose: list of states a friend can be in
-----------------------------------------------------------------------------
*/
enum EPersonaState
{
	k_EPersonaStateOffline = 0,			/* friend is not currently logged on */
	k_EPersonaStateOnline = 1,			/* friend is logged on */
	k_EPersonaStateBusy = 2,			/* user is on, but busy */
	k_EPersonaStateAway = 3,			/* auto-away feature */
	k_EPersonaStateSnooze = 4,			/* auto-away for a long time */
	k_EPersonaStateLookingToTrade = 5,	/* Online, trading */
	k_EPersonaStateLookingToPlay = 6,	/* Online, wanting to play */
	k_EPersonaStateInvisible = 7,		/* Online, but appears offline to friends.  This status is never published to clients. */
	k_EPersonaStateMax,
};

/*
-----------------------------------------------------------------------------
Purpose: flags for enumerating friends list, or quickly checking a the relationship between users
-----------------------------------------------------------------------------
*/
enum EFriendFlags
{
	k_EFriendFlagNone			= 0x00,
	k_EFriendFlagBlocked		= 0x01,
	k_EFriendFlagFriendshipRequested	= 0x02,
	k_EFriendFlagImmediate		= 0x04,			/* "regular" friend */
	k_EFriendFlagClanMember		= 0x08,
	k_EFriendFlagOnGameServer	= 0x10,	
	/* k_EFriendFlagHasPlayedWith	= 0x20,	*/ /* not currently used */
	/* k_EFriendFlagFriendOfFriend	= 0x40, */ /* not currently used */
	k_EFriendFlagRequestingFriendship = 0x80,
	k_EFriendFlagRequestingInfo = 0x100,
	k_EFriendFlagIgnored		= 0x200,
	k_EFriendFlagIgnoredFriend	= 0x400,
	/* k_EFriendFlagSuggested		= 0x800, */	/* not used */
	k_EFriendFlagChatMember		= 0x1000,
	k_EFriendFlagAll			= 0xFFFF,
};

ice_steam_def_opaque_type(FriendGameInfo_t)
/*
struct FriendGameInfo_t
{
	CGameID m_gameID;
	uint32 m_unGameIP;
	uint16 m_usGamePort;
	uint16 m_usQueryPort;
	CSteamID m_steamIDLobby;
};
*/

/*
maximum number of characters in a user's name. Two flavors; one for UTF-8 and one for UTF-16.
The UTF-8 version has to be very generous to accomodate characters that get large when encoded in UTF-8.
*/
enum
{
	k_cchPersonaNameMax = 128,
	k_cwchPersonaNameMax = 32,
};

/*
-----------------------------------------------------------------------------
Purpose: user restriction flags
-----------------------------------------------------------------------------
*/
enum EUserRestriction
{
	k_nUserRestrictionNone		= 0,	/* no known chat/content restriction */
	k_nUserRestrictionUnknown	= 1,	/* we don't know yet (user offline) */
	k_nUserRestrictionAnyChat	= 2,	/* user is not allowed to (or can't) send/recv any chat */
	k_nUserRestrictionVoiceChat	= 4,	/* user is not allowed to (or can't) send/recv voice chat */
	k_nUserRestrictionGroupChat	= 8,	/* user is not allowed to (or can't) send/recv group chat */
	k_nUserRestrictionRating	= 16,	/* user is too young according to rating in current region */
	k_nUserRestrictionGameInvites	= 32,	/* user cannot send or recv game invites (e.g. mobile) */
	k_nUserRestrictionTrading	= 64,	/* user cannot participate in trading (console, mobile) */
};

/* size limit on chat room or member metadata */
const uint32 k_cubChatMetadataMax = 8192;

/* size limits on Rich Presence data */
enum { k_cchMaxRichPresenceKeys = 30 };
enum { k_cchMaxRichPresenceKeyLength = 64 };
enum { k_cchMaxRichPresenceValueLength = 256 };

/* These values are passed as parameters to the store */
enum EOverlayToStoreFlag
{
	k_EOverlayToStoreFlag_None = 0,
	k_EOverlayToStoreFlag_AddToCart = 1,
	k_EOverlayToStoreFlag_AddToCartAndShow = 2,
};

/*
-----------------------------------------------------------------------------
Purpose: Tells Steam where to place the browser window inside the overlay
-----------------------------------------------------------------------------
*/
enum EActivateGameOverlayToWebPageMode
{
	k_EActivateGameOverlayToWebPageMode_Default = 0,		/* Browser will open next to all other windows that the user has open in the overlay. */
															/* The window will remain open, even if the user closes then re-opens the overlay. */

	k_EActivateGameOverlayToWebPageMode_Modal = 1			/* Browser will be opened in a special overlay configuration which hides all other windows */
															/* that the user has open in the overlay. When the user closes the overlay, the browser window */
															/* will also close. When the user closes the browser window, the overlay will automatically close. */
};

#define STEAMFRIENDS_INTERFACE_VERSION "SteamFriends017"

ice_steam_def_func(ISteamFriends*, SteamFriends, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamFriends *, SteamFriends, STEAMFRIENDS_INTERFACE_VERSION );*/

/* Steam API call failure results */
enum ESteamAPICallFailure
{
	k_ESteamAPICallFailureNone = -1,			/* no failure */
	k_ESteamAPICallFailureSteamGone = 0,		/* the local Steam process has gone away */
	k_ESteamAPICallFailureNetworkFailure = 1,	/* the network connection to Steam has been broken, or was already broken */
	/* SteamServersDisconnected_t callback will be sent around the same time */
	/* SteamServersConnected_t will be sent when the client is able to talk to the Steam servers again */
	k_ESteamAPICallFailureInvalidHandle = 2,	/* the SteamAPICall_t handle passed in no longer exists */
	k_ESteamAPICallFailureMismatchedCallback = 3,/* GetAPICallResult() was called with the wrong callback type for this API call */
};


/* Input modes for the Big Picture gamepad text entry */
enum EGamepadTextInputMode
{
	k_EGamepadTextInputModeNormal = 0,
	k_EGamepadTextInputModePassword = 1
};


/* Controls number of allowed lines for the Big Picture gamepad text entry */
enum EGamepadTextInputLineMode
{
	k_EGamepadTextInputLineModeSingleLine = 0,
	k_EGamepadTextInputLineModeMultipleLines = 1
};

enum EFloatingGamepadTextInputMode
{
	k_EFloatingGamepadTextInputModeModeSingleLine = 0, /* Enter dismisses the keyboard */
	k_EFloatingGamepadTextInputModeModeMultipleLines = 1, /* User needs to explictly close the keyboard */
	k_EFloatingGamepadTextInputModeModeEmail = 2,
	k_EFloatingGamepadTextInputModeModeNumeric = 3,
};

/* The context where text filtering is being done */
enum ETextFilteringContext
{
	k_ETextFilteringContextUnknown = 0,	/* Unknown context
	k_ETextFilteringContextGameContent = 1,	/* Game content, only legally required filtering is performed */
	k_ETextFilteringContextChat = 2,	/* Chat from another player */
	k_ETextFilteringContextName = 3,	/* Character or item name */
};

typedef void (*SteamAPIWarningMessageHook_t)(int, const char *);

#define STEAMUTILS_INTERFACE_VERSION "SteamUtils010"

ice_steam_def_func(ISteamUtils*, SteamUtils, ())
/*STEAM_DEFINE_INTERFACE_ACCESSOR( ISteamUtils *, SteamUtils, SteamInternal_FindOrCreateUserInterface( 0, STEAMUTILS_INTERFACE_VERSION ), "user", STEAMUTILS_INTERFACE_VERSION );*/

ice_steam_def_func(ISteamUtils*, SteamGameServerUtils, ())
/*STEAM_DEFINE_INTERFACE_ACCESSOR( ISteamUtils *, SteamGameServerUtils, SteamInternal_FindOrCreateGameServerInterface( 0, STEAMUTILS_INTERFACE_VERSION ), "gameserver", STEAMUTILS_INTERFACE_VERSION );*/

/*
Max size (in bytes of UTF-8 data, not in characters) of server fields, including null terminator.
WARNING: These cannot be changed easily, without breaking clients using old interfaces.
*/
const int k_cbMaxGameServerGameDir = 32;
const int k_cbMaxGameServerMapName = 32;
const int k_cbMaxGameServerGameDescription = 64;
const int k_cbMaxGameServerName = 64;
const int k_cbMaxGameServerTags = 128;
const int k_cbMaxGameServerGameData = 2048;

ice_steam_def_opaque_type(MatchMakingKeyValuePair_t)

enum EMatchMakingServerResponse
{
	eServerResponded = 0,
	eServerFailedToRespond,
	eNoServersListedOnMasterServer /* for the Internet query type, returned in response callback if no servers of this type match */
};

ice_steam_def_opaque_type(servernetadr_t)
ice_steam_def_opaque_type(gameserveritem_t)

/* lobby type description */
enum ELobbyType
{
	k_ELobbyTypePrivate = 0,		/* only way to join the lobby is to invite to someone else */
	k_ELobbyTypeFriendsOnly = 1,	/* shows for friends or invitees, but not in lobby list */
	k_ELobbyTypePublic = 2,			/* visible for friends and in lobby list */
	k_ELobbyTypeInvisible = 3,		/* returned by search, but not visible to other friends */
									/*    useful if you want a user in two lobbies, for example matching groups together */
									/*	  a user can be in only one regular lobby, and up to two invisible lobbies */
	k_ELobbyTypePrivateUnique = 4,	/* private, unique and does not delete when empty - only one of these may exist per unique keypair set */
									/* can only create from webapi */
};

/* lobby search filter tools */
enum ELobbyComparison
{
	k_ELobbyComparisonEqualToOrLessThan = -2,
	k_ELobbyComparisonLessThan = -1,
	k_ELobbyComparisonEqual = 0,
	k_ELobbyComparisonGreaterThan = 1,
	k_ELobbyComparisonEqualToOrGreaterThan = 2,
	k_ELobbyComparisonNotEqual = 3,
};

/* lobby search distance. Lobby results are sorted from closest to farthest. */
enum ELobbyDistanceFilter
{
	k_ELobbyDistanceFilterClose,		/* only lobbies in the same immediate region will be returned */
	k_ELobbyDistanceFilterDefault,		/* only lobbies in the same region or near by regions */
	k_ELobbyDistanceFilterFar,			/* for games that don't have many latency requirements, will return lobbies about half-way around the globe */
	k_ELobbyDistanceFilterWorldwide,	/* no filtering, will match lobbies as far as India to NY (not recommended, expect multiple seconds of latency between the clients) */
};

/* maximum number of characters a lobby metadata key can be */
#define k_nMaxLobbyKeyLength 255


#define STEAMMATCHMAKING_INTERFACE_VERSION "SteamMatchMaking009"

ice_steam_def_func(ISteamMatchmaking*, SteamMatchmaking, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamMatchmaking *, SteamMatchmaking, STEAMMATCHMAKING_INTERFACE_VERSION );*/

typedef void* HServerListRequest;

ice_steam_def_opaque_type(ISteamMatchmakingServerListResponse)
ice_steam_def_opaque_type(ISteamMatchmakingPingResponse)
ice_steam_def_opaque_type(ISteamMatchmakingPlayersResponse)
ice_steam_def_opaque_type(ISteamMatchmakingRulesResponse)

typedef int HServerQuery;
const int HSERVERQUERY_INVALID = 0xffffffff;

ice_steam_def_opaque_type(ISteamMatchmakingServers)

#define STEAMMATCHMAKINGSERVERS_INTERFACE_VERSION "SteamMatchMakingServers002"

ice_steam_def_func(ISteamMatchmakingServers*, SteamMatchmakingServers, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamMatchmakingServers *, SteamMatchmakingServers, STEAMMATCHMAKINGSERVERS_INTERFACE_VERSION );*/

/* game server flags */
const uint32 k_unFavoriteFlagNone			= 0x00;
const uint32 k_unFavoriteFlagFavorite		= 0x01; /* this game favorite entry is for the favorites list */
const uint32 k_unFavoriteFlagHistory		= 0x02; /* this game favorite entry is for the history list */

/*
-----------------------------------------------------------------------------
Purpose: Used in ChatInfo messages - fields specific to a chat member - must fit in a uint32
-----------------------------------------------------------------------------
*/
enum EChatMemberStateChange
{
	/* Specific to joining / leaving the chatroom */
	k_EChatMemberStateChangeEntered			= 0x0001,		/* This user has joined or is joining the chat room */
	k_EChatMemberStateChangeLeft			= 0x0002,		/* This user has left or is leaving the chat room */
	k_EChatMemberStateChangeDisconnected	= 0x0004,		/* User disconnected without leaving the chat first */
	k_EChatMemberStateChangeKicked			= 0x0008,		/* User kicked */
	k_EChatMemberStateChangeBanned			= 0x0010,		/* User kicked and banned */
};

/* returns true of the flags indicate that a user has been removed from the chat */
#define BChatMemberStateChangeRemoved( rgfChatMemberStateChangeFlags ) ( rgfChatMemberStateChangeFlags & ( k_EChatMemberStateChangeDisconnected | k_EChatMemberStateChangeLeft | k_EChatMemberStateChangeKicked | k_EChatMemberStateChangeBanned ) )

#define STEAMGAMESEARCH_INTERFACE_VERSION "SteamMatchGameSearch001"

ice_steam_def_func(ISteamGameSearch*, SteamGameSearch, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamGameSearch *, SteamGameSearch, STEAMGAMESEARCH_INTERFACE_VERSION );*/

enum ESteamPartyBeaconLocationType
{
	k_ESteamPartyBeaconLocationType_Invalid = 0,
	k_ESteamPartyBeaconLocationType_ChatGroup = 1,

	k_ESteamPartyBeaconLocationType_Max,
};

struct SteamPartyBeaconLocation_t
{
	ESteamPartyBeaconLocationType m_eType;
	uint64 m_ulLocationID;
};

enum ESteamPartyBeaconLocationData
{
	k_ESteamPartyBeaconLocationDataInvalid = 0,
	k_ESteamPartyBeaconLocationDataName = 1,
	k_ESteamPartyBeaconLocationDataIconURLSmall = 2,
	k_ESteamPartyBeaconLocationDataIconURLMedium = 3,
	k_ESteamPartyBeaconLocationDataIconURLLarge = 4,
};

#define STEAMPARTIES_INTERFACE_VERSION "SteamParties002"

ice_steam_def_func(ISteamParties*, SteamParties, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamParties *, SteamParties, STEAMPARTIES_INTERFACE_VERSION );*/


/*
-----------------------------------------------------------------------------
Purpose: Defines the largest allowed file size. Cloud files cannot be written in a single chunk over 100MB (and cannot be over 200MB total.)
-----------------------------------------------------------------------------
*/
const uint32 k_unMaxCloudFileChunkSize = 100 * 1024 * 1024;

/*
-----------------------------------------------------------------------------
Purpose: Structure that contains an array of const char * strings and the number of those strings
-----------------------------------------------------------------------------
*/
struct SteamParamStringArray_t
{
	const char ** m_ppStrings;
	int32 m_nNumStrings;
};

/* A handle to a piece of user generated content */
typedef uint64 UGCHandle_t;
typedef uint64 PublishedFileUpdateHandle_t;
typedef uint64 PublishedFileId_t;
const PublishedFileId_t k_PublishedFileIdInvalid = 0;
const UGCHandle_t k_UGCHandleInvalid = 0xffffffffffffffffull;
const PublishedFileUpdateHandle_t k_PublishedFileUpdateHandleInvalid = 0xffffffffffffffffull;

/* Handle for writing to Steam Cloud */
typedef uint64 UGCFileWriteStreamHandle_t;
const UGCFileWriteStreamHandle_t k_UGCFileStreamHandleInvalid = 0xffffffffffffffffull;

const uint32 k_cchPublishedDocumentTitleMax = 128 + 1;
const uint32 k_cchPublishedDocumentDescriptionMax = 8000;
const uint32 k_cchPublishedDocumentChangeDescriptionMax = 8000;
const uint32 k_unEnumeratePublishedFilesMaxResults = 50;
const uint32 k_cchTagListMax = 1024 + 1;
const uint32 k_cchFilenameMax = 260;
const uint32 k_cchPublishedFileURLMax = 256;


enum ERemoteStoragePlatform
{
	k_ERemoteStoragePlatformNone		= 0,
	k_ERemoteStoragePlatformWindows		= (1 << 0),
	k_ERemoteStoragePlatformOSX			= (1 << 1),
	k_ERemoteStoragePlatformPS3			= (1 << 2),
	k_ERemoteStoragePlatformLinux		= (1 << 3),
	k_ERemoteStoragePlatformSwitch		= (1 << 4),
	k_ERemoteStoragePlatformAndroid		= (1 << 5),
	k_ERemoteStoragePlatformIOS			= (1 << 6),
	/* NB we get one more before we need to widen some things */

	k_ERemoteStoragePlatformAll = 0xffffffff
};

enum ERemoteStoragePublishedFileVisibility
{
	k_ERemoteStoragePublishedFileVisibilityPublic = 0,
	k_ERemoteStoragePublishedFileVisibilityFriendsOnly = 1,
	k_ERemoteStoragePublishedFileVisibilityPrivate = 2,
	k_ERemoteStoragePublishedFileVisibilityUnlisted = 3,
};


enum EWorkshopFileType
{
	k_EWorkshopFileTypeFirst = 0,

	k_EWorkshopFileTypeCommunity			  = 0,		/* normal Workshop item that can be subscribed to */
	k_EWorkshopFileTypeMicrotransaction		  = 1,		/* Workshop item that is meant to be voted on for the purpose of selling in-game */
	k_EWorkshopFileTypeCollection			  = 2,		/* a collection of Workshop or Greenlight items */
	k_EWorkshopFileTypeArt					  = 3,		/* artwork */
	k_EWorkshopFileTypeVideo				  = 4,		/* external video */
	k_EWorkshopFileTypeScreenshot			  = 5,		/* screenshot */
	k_EWorkshopFileTypeGame					  = 6,		/* Greenlight game entry */
	k_EWorkshopFileTypeSoftware				  = 7,		/* Greenlight software entry */
	k_EWorkshopFileTypeConcept				  = 8,		/* Greenlight concept */
	k_EWorkshopFileTypeWebGuide				  = 9,		/* Steam web guide */
	k_EWorkshopFileTypeIntegratedGuide		  = 10,		/* application integrated guide */
	k_EWorkshopFileTypeMerch				  = 11,		/* Workshop merchandise meant to be voted on for the purpose of being sold */
	k_EWorkshopFileTypeControllerBinding	  = 12,		/* Steam Controller bindings */
	k_EWorkshopFileTypeSteamworksAccessInvite = 13,		/* internal */
	k_EWorkshopFileTypeSteamVideo			  = 14,		/* Steam video */
	k_EWorkshopFileTypeGameManagedItem		  = 15,		/* managed completely by the game, not the user, and not shown on the web */

	/* Update k_EWorkshopFileTypeMax if you add values. */
	k_EWorkshopFileTypeMax = 16
	
};

enum EWorkshopVote
{
	k_EWorkshopVoteUnvoted = 0,
	k_EWorkshopVoteFor = 1,
	k_EWorkshopVoteAgainst = 2,
	k_EWorkshopVoteLater = 3,
};

enum EWorkshopFileAction
{
	k_EWorkshopFileActionPlayed = 0,
	k_EWorkshopFileActionCompleted = 1,
};

enum EWorkshopEnumerationType
{
	k_EWorkshopEnumerationTypeRankedByVote = 0,
	k_EWorkshopEnumerationTypeRecent = 1,
	k_EWorkshopEnumerationTypeTrending = 2,
	k_EWorkshopEnumerationTypeFavoritesOfFriends = 3,
	k_EWorkshopEnumerationTypeVotedByFriends = 4,
	k_EWorkshopEnumerationTypeContentByFriends = 5,
	k_EWorkshopEnumerationTypeRecentFromFollowedUsers = 6,
};

enum EWorkshopVideoProvider
{
	k_EWorkshopVideoProviderNone = 0,
	k_EWorkshopVideoProviderYoutube = 1
};

enum EUGCReadAction
{
	/*
	Keeps the file handle open unless the last byte is read.  You can use this when reading large files (over 100MB) in sequential chunks.
	If the last byte is read, this will behave the same as k_EUGCRead_Close.  Otherwise, it behaves the same as k_EUGCRead_ContinueReading.
	This value maintains the same behavior as before the EUGCReadAction parameter was introduced.
	*/
	k_EUGCRead_ContinueReadingUntilFinished = 0,

	/*
	Keeps the file handle open.  Use this when using UGCRead to seek to different parts of the file.
	When you are done seeking around the file, make a final call with k_EUGCRead_Close to close it.
	*/
	k_EUGCRead_ContinueReading = 1,

	/*
	Frees the file handle.  Use this when you're done reading the content.  
	To read the file from Steam again you will need to call UGCDownload again.
	*/
	k_EUGCRead_Close = 2,	
};

enum ERemoteStorageLocalFileChange
{
	k_ERemoteStorageLocalFileChange_Invalid = 0,

	/* The file was updated from another device */
	k_ERemoteStorageLocalFileChange_FileUpdated = 1,

	/* The file was deleted by another device */
	k_ERemoteStorageLocalFileChange_FileDeleted = 2,
};

enum ERemoteStorageFilePathType
{
	k_ERemoteStorageFilePathType_Invalid = 0,
	
	/* The file is directly accessed by the game and this is the full path */
	k_ERemoteStorageFilePathType_Absolute = 1,

	/* The file is accessed via the ISteamRemoteStorage API and this is the filename */
	k_ERemoteStorageFilePathType_APIFilename = 2,
};

#define STEAMREMOTESTORAGE_INTERFACE_VERSION "STEAMREMOTESTORAGE_INTERFACE_VERSION016"

ice_steam_def_func(ISteamRemoteStorage*, SteamRemoteStorage, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamRemoteStorage *, SteamRemoteStorage, STEAMREMOTESTORAGE_INTERFACE_VERSION );*/

/* size limit on stat or achievement name (UTF-8 encoded) */
enum { k_cchStatNameMax = 128 };

/* maximum number of bytes for a leaderboard name (UTF-8 encoded) */
enum { k_cchLeaderboardNameMax = 128 };

/* maximum number of details int32's storable for a single leaderboard entry */
enum { k_cLeaderboardDetailsMax = 64 };

/* handle to a single leaderboard */
typedef uint64 SteamLeaderboard_t;

/* handle to a set of downloaded entries in a leaderboard */
typedef uint64 SteamLeaderboardEntries_t;

/* type of data request, when downloading leaderboard entries */
enum ELeaderboardDataRequest
{
	k_ELeaderboardDataRequestGlobal = 0,
	k_ELeaderboardDataRequestGlobalAroundUser = 1,
	k_ELeaderboardDataRequestFriends = 2,
	k_ELeaderboardDataRequestUsers = 3
};

/* the sort order of a leaderboard */
enum ELeaderboardSortMethod
{
	k_ELeaderboardSortMethodNone = 0,
	k_ELeaderboardSortMethodAscending = 1,	/* top-score is lowest number */
	k_ELeaderboardSortMethodDescending = 2,	/* top-score is highest number */
};

/* the display type (used by the Steam Community web site) for a leaderboard */
enum ELeaderboardDisplayType
{
	k_ELeaderboardDisplayTypeNone = 0, 
	k_ELeaderboardDisplayTypeNumeric = 1,			/* simple numerical score */
	k_ELeaderboardDisplayTypeTimeSeconds = 2,		/* the score represents a time, in seconds */
	k_ELeaderboardDisplayTypeTimeMilliSeconds = 3,	/* the score represents a time, in milliseconds */
};

enum ELeaderboardUploadScoreMethod
{
	k_ELeaderboardUploadScoreMethodNone = 0,
	k_ELeaderboardUploadScoreMethodKeepBest = 1,	/* Leaderboard will keep user's best score */
	k_ELeaderboardUploadScoreMethodForceUpdate = 2,	/* Leaderboard will always replace score with specified */
};

ice_steam_def_opaque_type(LeaderboardEntry_t)
/*
struct LeaderboardEntry_t
{
	CSteamID m_steamIDUser;
	int32 m_nGlobalRank;
	int32 m_nScore;
	int32 m_cDetails;
	UGCHandle_t m_hUGC;
};
*/

#define STEAMUSERSTATS_INTERFACE_VERSION "STEAMUSERSTATS_INTERFACE_VERSION012"

ice_steam_def_func(ISteamUserStats*, SteamUserStats, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamUserStats *, SteamUserStats, STEAMUSERSTATS_INTERFACE_VERSION );*/

const int k_cubAppProofOfPurchaseKeyMax = 240;			/* max supported length of a legacy cd key  */

#define STEAMAPPS_INTERFACE_VERSION "STEAMAPPS_INTERFACE_VERSION008"

ice_steam_def_func(ISteamApps*, SteamApps, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamApps *, SteamApps, STEAMAPPS_INTERFACE_VERSION );*/

/* list of possible errors returned by SendP2PPacket() API */
/* these will be posted in the P2PSessionConnectFail_t callback */
enum EP2PSessionError
{
	k_EP2PSessionErrorNone = 0,
	k_EP2PSessionErrorNoRightsToApp = 2,			/* local user doesn't own the app that is running */
	k_EP2PSessionErrorTimeout = 4,					/* target isn't responding, perhaps not calling AcceptP2PSessionWithUser() */
													/* corporate firewalls can also block this (NAT traversal is not firewall traversal) */
													/* make sure that UDP ports 3478, 4379, and 4380 are open in an outbound direction */

	/* The following error codes were removed and will never be sent. */
	/* For privacy reasons, there is no reply if the user is offline or playing another game. */
	k_EP2PSessionErrorNotRunningApp_DELETED = 1,
	k_EP2PSessionErrorDestinationNotLoggedIn_DELETED = 3,

	k_EP2PSessionErrorMax = 5
};

/* SendP2PPacket() send types */
/* Typically k_EP2PSendUnreliable is what you want for UDP-like packets, k_EP2PSendReliable for TCP-like packets */
enum EP2PSend
{
	/*
	Basic UDP send. Packets can't be bigger than 1200 bytes (your typical MTU size). Can be lost, or arrive out of order (rare).
	The sending API does have some knowledge of the underlying connection, so if there is no NAT-traversal accomplished or
	there is a recognized adjustment happening on the connection, the packet will be batched until the connection is open again.
	*/
	k_EP2PSendUnreliable = 0,

	/*
	As above, but if the underlying p2p connection isn't yet established the packet will just be thrown away. Using this on the first
	packet sent to a remote host almost guarantees the packet will be dropped.
	This is only really useful for kinds of data that should never buffer up, i.e. voice payload packets
	*/
	k_EP2PSendUnreliableNoDelay = 1,

	/*
	Reliable message send. Can send up to 1MB of data in a single message. 
	Does fragmentation/re-assembly of messages under the hood, as well as a sliding window for efficient sends of large chunks of data. 
	*/
	k_EP2PSendReliable = 2,

	/*
	As above, but applies the Nagle algorithm to the send - sends will accumulate 
	until the current MTU size (typically ~1200 bytes, but can change) or ~200ms has passed (Nagle algorithm). 
	Useful if you want to send a set of smaller messages but have the coalesced into a single packet
	Since the reliable stream is all ordered, you can do several small message sends with k_EP2PSendReliableWithBuffering and then
	do a normal k_EP2PSendReliable to force all the buffered data to be sent.
	*/
	k_EP2PSendReliableWithBuffering = 3,
};

struct P2PSessionState_t
{
	uint8 m_bConnectionActive;		/* true if we've got an active open connection */
	uint8 m_bConnecting;			/* true if we're currently trying to establish a connection */
	uint8 m_eP2PSessionError;		/* last error recorded (see enum above) */
	uint8 m_bUsingRelay;			/* true if it's going through a relay server (TURN) */
	int32 m_nBytesQueuedForSend;
	int32 m_nPacketsQueuedForSend;
	uint32 m_nRemoteIP;				/* potential IP:Port of remote host. Could be TURN server. */
	uint16 m_nRemotePort;			/* Only exists for compatibility with older authentication api's */
};

/* handle to a socket */
typedef uint32 SNetSocket_t;		/* CreateP2PConnectionSocket() */
typedef uint32 SNetListenSocket_t;	/* CreateListenSocket() */

/* connection progress indicators, used by CreateP2PConnectionSocket() */
enum ESNetSocketState
{
	k_ESNetSocketStateInvalid = 0,						

	/* communication is valid */
	k_ESNetSocketStateConnected = 1,				
	
	/* states while establishing a connection */
	k_ESNetSocketStateInitiated = 10,				/* the connection state machine has started */

	/* p2p connections */
	k_ESNetSocketStateLocalCandidatesFound = 11,	/* we've found our local IP info */
	k_ESNetSocketStateReceivedRemoteCandidates = 12,/* we've received information from the remote machine, via the Steam back-end, about their IP info */

	/* direct connections */
	k_ESNetSocketStateChallengeHandshake = 15,		/* we've received a challenge packet from the server */

	/* failure states */
	k_ESNetSocketStateDisconnecting = 21,			/* the API shut it down, and we're in the process of telling the other end */
	k_ESNetSocketStateLocalDisconnect = 22,			/* the API shut it down, and we've completed shutdown */
	k_ESNetSocketStateTimeoutDuringConnect = 23,	/* we timed out while trying to creating the connection */
	k_ESNetSocketStateRemoteEndDisconnected = 24,	/* the remote end has disconnected from us */
	k_ESNetSocketStateConnectionBroken = 25,		/* connection has been broken; either the other end has disappeared or our local network connection has broke */
};

/* describes how the socket is currently connected */
enum ESNetSocketConnectionType
{
	k_ESNetSocketConnectionTypeNotConnected = 0,
	k_ESNetSocketConnectionTypeUDP = 1,
	k_ESNetSocketConnectionTypeUDPRelay = 2,
};

#define STEAMNETWORKING_INTERFACE_VERSION "SteamNetworking006"

ice_steam_def_func(ISteamNetworking*, SteamNetworking, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamNetworking *, SteamNetworking, STEAMNETWORKING_INTERFACE_VERSION );*/

ice_steam_def_func(ISteamNetworking*, SteamGameServerNetworking, ())
/*STEAM_DEFINE_GAMESERVER_INTERFACE_ACCESSOR( ISteamNetworking *, SteamGameServerNetworking, STEAMNETWORKING_INTERFACE_VERSION );*/

const uint32 k_nScreenshotMaxTaggedUsers = 32;
const uint32 k_nScreenshotMaxTaggedPublishedFiles = 32;
const int k_cubUFSTagTypeMax = 255;
const int k_cubUFSTagValueMax = 255;

/* Required with of a thumbnail provided to AddScreenshotToLibrary.  If you do not provide a thumbnail one will be generated. */
const int k_ScreenshotThumbWidth = 200;

/* Handle is valid for the lifetime of your process and no longer */
typedef uint32 ScreenshotHandle; 
#define INVALID_SCREENSHOT_HANDLE 0

enum EVRScreenshotType
{
	k_EVRScreenshotType_None			= 0,
	k_EVRScreenshotType_Mono			= 1,
	k_EVRScreenshotType_Stereo			= 2,
	k_EVRScreenshotType_MonoCubemap		= 3,
	k_EVRScreenshotType_MonoPanorama	= 4,
	k_EVRScreenshotType_StereoPanorama	= 5
};

#define STEAMSCREENSHOTS_INTERFACE_VERSION "STEAMSCREENSHOTS_INTERFACE_VERSION003"

ice_steam_def_func(ISteamScreenshots*, SteamScreenshots, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamScreenshots *, SteamScreenshots, STEAMSCREENSHOTS_INTERFACE_VERSION );*/

enum AudioPlayback_Status
{
	AudioPlayback_Undefined = 0, 
	AudioPlayback_Playing = 1,
	AudioPlayback_Paused = 2,
	AudioPlayback_Idle = 3
};

#define STEAMMUSIC_INTERFACE_VERSION "STEAMMUSIC_INTERFACE_VERSION001"

ice_steam_def_func(ISteamMusic*, SteamMusic, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamMusic *, SteamMusic, STEAMMUSIC_INTERFACE_VERSION );*/

#define k_SteamMusicNameMaxLength 255
#define k_SteamMusicPNGMaxLength 65535

#define STEAMMUSICREMOTE_INTERFACE_VERSION "STEAMMUSICREMOTE_INTERFACE_VERSION001"

ice_steam_def_func(ISteamMusicRemote*, SteamMusicRemote, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamMusicRemote *, SteamMusicRemote, STEAMMUSICREMOTE_INTERFACE_VERSION );*/

/* HTTP related types */

/* This enum is used in client API methods, do not re-number existing values. */
enum EHTTPMethod
{
	k_EHTTPMethodInvalid = 0,
	k_EHTTPMethodGET,
	k_EHTTPMethodHEAD,
	k_EHTTPMethodPOST,
	k_EHTTPMethodPUT,
	k_EHTTPMethodDELETE,
	k_EHTTPMethodOPTIONS,
	k_EHTTPMethodPATCH,

	/* The remaining HTTP methods are not yet supported, per rfc2616 section 5.1.1 only GET and HEAD are required for a compliant general purpose server.  We'll likely add more as we find uses for them. */

	/*
	k_EHTTPMethodTRACE,
	k_EHTTPMethodCONNECT
	*/
};

/* HTTP Status codes that the server can send in response to a request, see rfc2616 section 10.3 for descriptions of each of these. */
enum EHTTPStatusCode
{
	/* Invalid status code (this isn't defined in HTTP, used to indicate unset in our code) */
	k_EHTTPStatusCodeInvalid =					0,

	/* Informational codes */
	k_EHTTPStatusCode100Continue =				100,
	k_EHTTPStatusCode101SwitchingProtocols =	101,

	/* Success codes */
	k_EHTTPStatusCode200OK =					200,
	k_EHTTPStatusCode201Created =				201,
	k_EHTTPStatusCode202Accepted =				202,
	k_EHTTPStatusCode203NonAuthoritative =		203,
	k_EHTTPStatusCode204NoContent =				204,
	k_EHTTPStatusCode205ResetContent =			205,
	k_EHTTPStatusCode206PartialContent =		206,

	/* Redirection codes */
	k_EHTTPStatusCode300MultipleChoices =		300,
	k_EHTTPStatusCode301MovedPermanently =		301,
	k_EHTTPStatusCode302Found =					302,
	k_EHTTPStatusCode303SeeOther =				303,
	k_EHTTPStatusCode304NotModified =			304,
	k_EHTTPStatusCode305UseProxy =				305,
	/*k_EHTTPStatusCode306Unused =				306, (used in old HTTP spec, now unused in 1.1) */
	k_EHTTPStatusCode307TemporaryRedirect =		307,

	/* Error codes */
	k_EHTTPStatusCode400BadRequest =			400,
	k_EHTTPStatusCode401Unauthorized =			401, /* You probably want 403 or something else. 401 implies you're sending a WWW-Authenticate header and the client can sent an Authorization header in response. */
	k_EHTTPStatusCode402PaymentRequired =		402, /* This is reserved for future HTTP specs, not really supported by clients */
	k_EHTTPStatusCode403Forbidden =				403,
	k_EHTTPStatusCode404NotFound =				404,
	k_EHTTPStatusCode405MethodNotAllowed =		405,
	k_EHTTPStatusCode406NotAcceptable =			406,
	k_EHTTPStatusCode407ProxyAuthRequired =		407,
	k_EHTTPStatusCode408RequestTimeout =		408,
	k_EHTTPStatusCode409Conflict =				409,
	k_EHTTPStatusCode410Gone =					410,
	k_EHTTPStatusCode411LengthRequired =		411,
	k_EHTTPStatusCode412PreconditionFailed =	412,
	k_EHTTPStatusCode413RequestEntityTooLarge =	413,
	k_EHTTPStatusCode414RequestURITooLong =		414,
	k_EHTTPStatusCode415UnsupportedMediaType =	415,
	k_EHTTPStatusCode416RequestedRangeNotSatisfiable = 416,
	k_EHTTPStatusCode417ExpectationFailed =		417,
	k_EHTTPStatusCode4xxUnknown = 				418, /* 418 is reserved, so we'll use it to mean unknown */
	k_EHTTPStatusCode429TooManyRequests	=		429,
	k_EHTTPStatusCode444ConnectionClosed =		444, /* nginx only? */

	/* Server error codes */
	k_EHTTPStatusCode500InternalServerError =	500,
	k_EHTTPStatusCode501NotImplemented =		501,
	k_EHTTPStatusCode502BadGateway =			502,
	k_EHTTPStatusCode503ServiceUnavailable =	503,
	k_EHTTPStatusCode504GatewayTimeout =		504,
	k_EHTTPStatusCode505HTTPVersionNotSupported = 505,
	k_EHTTPStatusCode5xxUnknown =				599,
};

/* Handle to a HTTP Request handle */
typedef uint32 HTTPRequestHandle;
#define INVALID_HTTPREQUEST_HANDLE		0

typedef uint32 HTTPCookieContainerHandle;
#define INVALID_HTTPCOOKIE_HANDLE		0

#define STEAMHTTP_INTERFACE_VERSION "STEAMHTTP_INTERFACE_VERSION003"

ice_steam_def_func(ISteamHTTP*, SteamHTTP, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamHTTP *, SteamHTTP, STEAMHTTP_INTERFACE_VERSION );*/

ice_steam_def_func(ISteamHTTP*, SteamGameServerHTTP, ())
/*STEAM_DEFINE_GAMESERVER_INTERFACE_ACCESSOR( ISteamHTTP *, SteamGameServerHTTP, STEAMHTTP_INTERFACE_VERSION );*/

#define STEAM_INPUT_MAX_COUNT 16
#define STEAM_INPUT_MAX_ANALOG_ACTIONS 16
#define STEAM_INPUT_MAX_DIGITAL_ACTIONS 128
#define STEAM_INPUT_MAX_ORIGINS 8
#define STEAM_INPUT_MAX_ACTIVE_LAYERS 16

/* When sending an option to a specific controller handle, you can send to all devices via this command */
#define STEAM_INPUT_HANDLE_ALL_CONTROLLERS UINT64_MAX

#define STEAM_INPUT_MIN_ANALOG_ACTION_DATA -1.0f
#define STEAM_INPUT_MAX_ANALOG_ACTION_DATA 1.0f

enum EInputSourceMode
{
	k_EInputSourceMode_None,
	k_EInputSourceMode_Dpad,
	k_EInputSourceMode_Buttons,
	k_EInputSourceMode_FourButtons,
	k_EInputSourceMode_AbsoluteMouse,
	k_EInputSourceMode_RelativeMouse,
	k_EInputSourceMode_JoystickMove,
	k_EInputSourceMode_JoystickMouse,
	k_EInputSourceMode_JoystickCamera,
	k_EInputSourceMode_ScrollWheel,
	k_EInputSourceMode_Trigger,
	k_EInputSourceMode_TouchMenu,
	k_EInputSourceMode_MouseJoystick,
	k_EInputSourceMode_MouseRegion,
	k_EInputSourceMode_RadialMenu,
	k_EInputSourceMode_SingleButton,
	k_EInputSourceMode_Switches
};

/*
Note: Please do not use action origins as a way to identify controller types. There is no guarantee that they will be added in a contiguous manner - use GetInputTypeForHandle instead.
Versions of Steam that add new controller types in the future will extend this enum so if you're using a lookup table please check the bounds of any origins returned by Steam.
*/
enum EInputActionOrigin
{
	/* Steam Controller */
	k_EInputActionOrigin_None,
	k_EInputActionOrigin_SteamController_A,
	k_EInputActionOrigin_SteamController_B,
	k_EInputActionOrigin_SteamController_X,
	k_EInputActionOrigin_SteamController_Y,
	k_EInputActionOrigin_SteamController_LeftBumper,
	k_EInputActionOrigin_SteamController_RightBumper,
	k_EInputActionOrigin_SteamController_LeftGrip,
	k_EInputActionOrigin_SteamController_RightGrip,
	k_EInputActionOrigin_SteamController_Start,
	k_EInputActionOrigin_SteamController_Back,
	k_EInputActionOrigin_SteamController_LeftPad_Touch,
	k_EInputActionOrigin_SteamController_LeftPad_Swipe,
	k_EInputActionOrigin_SteamController_LeftPad_Click,
	k_EInputActionOrigin_SteamController_LeftPad_DPadNorth,
	k_EInputActionOrigin_SteamController_LeftPad_DPadSouth,
	k_EInputActionOrigin_SteamController_LeftPad_DPadWest,
	k_EInputActionOrigin_SteamController_LeftPad_DPadEast,
	k_EInputActionOrigin_SteamController_RightPad_Touch,
	k_EInputActionOrigin_SteamController_RightPad_Swipe,
	k_EInputActionOrigin_SteamController_RightPad_Click,
	k_EInputActionOrigin_SteamController_RightPad_DPadNorth,
	k_EInputActionOrigin_SteamController_RightPad_DPadSouth,
	k_EInputActionOrigin_SteamController_RightPad_DPadWest,
	k_EInputActionOrigin_SteamController_RightPad_DPadEast,
	k_EInputActionOrigin_SteamController_LeftTrigger_Pull,
	k_EInputActionOrigin_SteamController_LeftTrigger_Click,
	k_EInputActionOrigin_SteamController_RightTrigger_Pull,
	k_EInputActionOrigin_SteamController_RightTrigger_Click,
	k_EInputActionOrigin_SteamController_LeftStick_Move,
	k_EInputActionOrigin_SteamController_LeftStick_Click,
	k_EInputActionOrigin_SteamController_LeftStick_DPadNorth,
	k_EInputActionOrigin_SteamController_LeftStick_DPadSouth,
	k_EInputActionOrigin_SteamController_LeftStick_DPadWest,
	k_EInputActionOrigin_SteamController_LeftStick_DPadEast,
	k_EInputActionOrigin_SteamController_Gyro_Move,
	k_EInputActionOrigin_SteamController_Gyro_Pitch,
	k_EInputActionOrigin_SteamController_Gyro_Yaw,
	k_EInputActionOrigin_SteamController_Gyro_Roll,
	k_EInputActionOrigin_SteamController_Reserved0,
	k_EInputActionOrigin_SteamController_Reserved1,
	k_EInputActionOrigin_SteamController_Reserved2,
	k_EInputActionOrigin_SteamController_Reserved3,
	k_EInputActionOrigin_SteamController_Reserved4,
	k_EInputActionOrigin_SteamController_Reserved5,
	k_EInputActionOrigin_SteamController_Reserved6,
	k_EInputActionOrigin_SteamController_Reserved7,
	k_EInputActionOrigin_SteamController_Reserved8,
	k_EInputActionOrigin_SteamController_Reserved9,
	k_EInputActionOrigin_SteamController_Reserved10,
	
	/* PS4 Dual Shock */
	k_EInputActionOrigin_PS4_X,
	k_EInputActionOrigin_PS4_Circle,
	k_EInputActionOrigin_PS4_Triangle,
	k_EInputActionOrigin_PS4_Square,
	k_EInputActionOrigin_PS4_LeftBumper,
	k_EInputActionOrigin_PS4_RightBumper,
	k_EInputActionOrigin_PS4_Options,	/* Start */
	k_EInputActionOrigin_PS4_Share,		/* Back */
	k_EInputActionOrigin_PS4_LeftPad_Touch,
	k_EInputActionOrigin_PS4_LeftPad_Swipe,
	k_EInputActionOrigin_PS4_LeftPad_Click,
	k_EInputActionOrigin_PS4_LeftPad_DPadNorth,
	k_EInputActionOrigin_PS4_LeftPad_DPadSouth,
	k_EInputActionOrigin_PS4_LeftPad_DPadWest,
	k_EInputActionOrigin_PS4_LeftPad_DPadEast,
	k_EInputActionOrigin_PS4_RightPad_Touch,
	k_EInputActionOrigin_PS4_RightPad_Swipe,
	k_EInputActionOrigin_PS4_RightPad_Click,
	k_EInputActionOrigin_PS4_RightPad_DPadNorth,
	k_EInputActionOrigin_PS4_RightPad_DPadSouth,
	k_EInputActionOrigin_PS4_RightPad_DPadWest,
	k_EInputActionOrigin_PS4_RightPad_DPadEast,
	k_EInputActionOrigin_PS4_CenterPad_Touch,
	k_EInputActionOrigin_PS4_CenterPad_Swipe,
	k_EInputActionOrigin_PS4_CenterPad_Click,
	k_EInputActionOrigin_PS4_CenterPad_DPadNorth,
	k_EInputActionOrigin_PS4_CenterPad_DPadSouth,
	k_EInputActionOrigin_PS4_CenterPad_DPadWest,
	k_EInputActionOrigin_PS4_CenterPad_DPadEast,
	k_EInputActionOrigin_PS4_LeftTrigger_Pull,
	k_EInputActionOrigin_PS4_LeftTrigger_Click,
	k_EInputActionOrigin_PS4_RightTrigger_Pull,
	k_EInputActionOrigin_PS4_RightTrigger_Click,
	k_EInputActionOrigin_PS4_LeftStick_Move,
	k_EInputActionOrigin_PS4_LeftStick_Click,
	k_EInputActionOrigin_PS4_LeftStick_DPadNorth,
	k_EInputActionOrigin_PS4_LeftStick_DPadSouth,
	k_EInputActionOrigin_PS4_LeftStick_DPadWest,
	k_EInputActionOrigin_PS4_LeftStick_DPadEast,
	k_EInputActionOrigin_PS4_RightStick_Move,
	k_EInputActionOrigin_PS4_RightStick_Click,
	k_EInputActionOrigin_PS4_RightStick_DPadNorth,
	k_EInputActionOrigin_PS4_RightStick_DPadSouth,
	k_EInputActionOrigin_PS4_RightStick_DPadWest,
	k_EInputActionOrigin_PS4_RightStick_DPadEast,
	k_EInputActionOrigin_PS4_DPad_North,
	k_EInputActionOrigin_PS4_DPad_South,
	k_EInputActionOrigin_PS4_DPad_West,
	k_EInputActionOrigin_PS4_DPad_East,
	k_EInputActionOrigin_PS4_Gyro_Move,
	k_EInputActionOrigin_PS4_Gyro_Pitch,
	k_EInputActionOrigin_PS4_Gyro_Yaw,
	k_EInputActionOrigin_PS4_Gyro_Roll,
	k_EInputActionOrigin_PS4_DPad_Move,
	k_EInputActionOrigin_PS4_Reserved1,
	k_EInputActionOrigin_PS4_Reserved2,
	k_EInputActionOrigin_PS4_Reserved3,
	k_EInputActionOrigin_PS4_Reserved4,
	k_EInputActionOrigin_PS4_Reserved5,
	k_EInputActionOrigin_PS4_Reserved6,
	k_EInputActionOrigin_PS4_Reserved7,
	k_EInputActionOrigin_PS4_Reserved8,
	k_EInputActionOrigin_PS4_Reserved9,
	k_EInputActionOrigin_PS4_Reserved10,

	/* XBox One */
	k_EInputActionOrigin_XBoxOne_A,
	k_EInputActionOrigin_XBoxOne_B,
	k_EInputActionOrigin_XBoxOne_X,
	k_EInputActionOrigin_XBoxOne_Y,
	k_EInputActionOrigin_XBoxOne_LeftBumper,
	k_EInputActionOrigin_XBoxOne_RightBumper,
	k_EInputActionOrigin_XBoxOne_Menu,  /* Start */
	k_EInputActionOrigin_XBoxOne_View,  /* Back */
	k_EInputActionOrigin_XBoxOne_LeftTrigger_Pull,
	k_EInputActionOrigin_XBoxOne_LeftTrigger_Click,
	k_EInputActionOrigin_XBoxOne_RightTrigger_Pull,
	k_EInputActionOrigin_XBoxOne_RightTrigger_Click,
	k_EInputActionOrigin_XBoxOne_LeftStick_Move,
	k_EInputActionOrigin_XBoxOne_LeftStick_Click,
	k_EInputActionOrigin_XBoxOne_LeftStick_DPadNorth,
	k_EInputActionOrigin_XBoxOne_LeftStick_DPadSouth,
	k_EInputActionOrigin_XBoxOne_LeftStick_DPadWest,
	k_EInputActionOrigin_XBoxOne_LeftStick_DPadEast,
	k_EInputActionOrigin_XBoxOne_RightStick_Move,
	k_EInputActionOrigin_XBoxOne_RightStick_Click,
	k_EInputActionOrigin_XBoxOne_RightStick_DPadNorth,
	k_EInputActionOrigin_XBoxOne_RightStick_DPadSouth,
	k_EInputActionOrigin_XBoxOne_RightStick_DPadWest,
	k_EInputActionOrigin_XBoxOne_RightStick_DPadEast,
	k_EInputActionOrigin_XBoxOne_DPad_North,
	k_EInputActionOrigin_XBoxOne_DPad_South,
	k_EInputActionOrigin_XBoxOne_DPad_West,
	k_EInputActionOrigin_XBoxOne_DPad_East,
	k_EInputActionOrigin_XBoxOne_DPad_Move,
	k_EInputActionOrigin_XBoxOne_LeftGrip_Lower,
	k_EInputActionOrigin_XBoxOne_LeftGrip_Upper,
	k_EInputActionOrigin_XBoxOne_RightGrip_Lower,
	k_EInputActionOrigin_XBoxOne_RightGrip_Upper,
	k_EInputActionOrigin_XBoxOne_Share, /* Xbox Series X controllers only */
	k_EInputActionOrigin_XBoxOne_Reserved6,
	k_EInputActionOrigin_XBoxOne_Reserved7,
	k_EInputActionOrigin_XBoxOne_Reserved8,
	k_EInputActionOrigin_XBoxOne_Reserved9,
	k_EInputActionOrigin_XBoxOne_Reserved10,

	/* XBox 360 */
	k_EInputActionOrigin_XBox360_A,
	k_EInputActionOrigin_XBox360_B,
	k_EInputActionOrigin_XBox360_X,
	k_EInputActionOrigin_XBox360_Y,
	k_EInputActionOrigin_XBox360_LeftBumper,
	k_EInputActionOrigin_XBox360_RightBumper,
	k_EInputActionOrigin_XBox360_Start,		/* Start */
	k_EInputActionOrigin_XBox360_Back,		/* Back */
	k_EInputActionOrigin_XBox360_LeftTrigger_Pull,
	k_EInputActionOrigin_XBox360_LeftTrigger_Click,
	k_EInputActionOrigin_XBox360_RightTrigger_Pull,
	k_EInputActionOrigin_XBox360_RightTrigger_Click,
	k_EInputActionOrigin_XBox360_LeftStick_Move,
	k_EInputActionOrigin_XBox360_LeftStick_Click,
	k_EInputActionOrigin_XBox360_LeftStick_DPadNorth,
	k_EInputActionOrigin_XBox360_LeftStick_DPadSouth,
	k_EInputActionOrigin_XBox360_LeftStick_DPadWest,
	k_EInputActionOrigin_XBox360_LeftStick_DPadEast,
	k_EInputActionOrigin_XBox360_RightStick_Move,
	k_EInputActionOrigin_XBox360_RightStick_Click,
	k_EInputActionOrigin_XBox360_RightStick_DPadNorth,
	k_EInputActionOrigin_XBox360_RightStick_DPadSouth,
	k_EInputActionOrigin_XBox360_RightStick_DPadWest,
	k_EInputActionOrigin_XBox360_RightStick_DPadEast,
	k_EInputActionOrigin_XBox360_DPad_North,
	k_EInputActionOrigin_XBox360_DPad_South,
	k_EInputActionOrigin_XBox360_DPad_West,
	k_EInputActionOrigin_XBox360_DPad_East,	
	k_EInputActionOrigin_XBox360_DPad_Move,
	k_EInputActionOrigin_XBox360_Reserved1,
	k_EInputActionOrigin_XBox360_Reserved2,
	k_EInputActionOrigin_XBox360_Reserved3,
	k_EInputActionOrigin_XBox360_Reserved4,
	k_EInputActionOrigin_XBox360_Reserved5,
	k_EInputActionOrigin_XBox360_Reserved6,
	k_EInputActionOrigin_XBox360_Reserved7,
	k_EInputActionOrigin_XBox360_Reserved8,
	k_EInputActionOrigin_XBox360_Reserved9,
	k_EInputActionOrigin_XBox360_Reserved10,


	/* Switch - Pro or Joycons used as a single input device. */
	/* This does not apply to a single joycon */
	k_EInputActionOrigin_Switch_A,
	k_EInputActionOrigin_Switch_B,
	k_EInputActionOrigin_Switch_X,
	k_EInputActionOrigin_Switch_Y,
	k_EInputActionOrigin_Switch_LeftBumper,
	k_EInputActionOrigin_Switch_RightBumper,
	k_EInputActionOrigin_Switch_Plus,	/* Start */
	k_EInputActionOrigin_Switch_Minus,	/* Back */
	k_EInputActionOrigin_Switch_Capture,
	k_EInputActionOrigin_Switch_LeftTrigger_Pull,
	k_EInputActionOrigin_Switch_LeftTrigger_Click,
	k_EInputActionOrigin_Switch_RightTrigger_Pull,
	k_EInputActionOrigin_Switch_RightTrigger_Click,
	k_EInputActionOrigin_Switch_LeftStick_Move,
	k_EInputActionOrigin_Switch_LeftStick_Click,
	k_EInputActionOrigin_Switch_LeftStick_DPadNorth,
	k_EInputActionOrigin_Switch_LeftStick_DPadSouth,
	k_EInputActionOrigin_Switch_LeftStick_DPadWest,
	k_EInputActionOrigin_Switch_LeftStick_DPadEast,
	k_EInputActionOrigin_Switch_RightStick_Move,
	k_EInputActionOrigin_Switch_RightStick_Click,
	k_EInputActionOrigin_Switch_RightStick_DPadNorth,
	k_EInputActionOrigin_Switch_RightStick_DPadSouth,
	k_EInputActionOrigin_Switch_RightStick_DPadWest,
	k_EInputActionOrigin_Switch_RightStick_DPadEast,
	k_EInputActionOrigin_Switch_DPad_North,
	k_EInputActionOrigin_Switch_DPad_South,
	k_EInputActionOrigin_Switch_DPad_West,
	k_EInputActionOrigin_Switch_DPad_East,
	k_EInputActionOrigin_Switch_ProGyro_Move,  /* Primary Gyro in Pro Controller, or Right JoyCon */
	k_EInputActionOrigin_Switch_ProGyro_Pitch,  /* Primary Gyro in Pro Controller, or Right JoyCon */
	k_EInputActionOrigin_Switch_ProGyro_Yaw,  /* Primary Gyro in Pro Controller, or Right JoyCon */
	k_EInputActionOrigin_Switch_ProGyro_Roll,  /* Primary Gyro in Pro Controller, or Right JoyCon */
	k_EInputActionOrigin_Switch_DPad_Move,
	k_EInputActionOrigin_Switch_Reserved1,
	k_EInputActionOrigin_Switch_Reserved2,
	k_EInputActionOrigin_Switch_Reserved3,
	k_EInputActionOrigin_Switch_Reserved4,
	k_EInputActionOrigin_Switch_Reserved5,
	k_EInputActionOrigin_Switch_Reserved6,
	k_EInputActionOrigin_Switch_Reserved7,
	k_EInputActionOrigin_Switch_Reserved8,
	k_EInputActionOrigin_Switch_Reserved9,
	k_EInputActionOrigin_Switch_Reserved10,

	/* Switch JoyCon Specific */
	k_EInputActionOrigin_Switch_RightGyro_Move,  /* Right JoyCon Gyro generally should correspond to Pro's single gyro */
	k_EInputActionOrigin_Switch_RightGyro_Pitch,  /* Right JoyCon Gyro generally should correspond to Pro's single gyro */
	k_EInputActionOrigin_Switch_RightGyro_Yaw,  /* Right JoyCon Gyro generally should correspond to Pro's single gyro */
	k_EInputActionOrigin_Switch_RightGyro_Roll,  /* Right JoyCon Gyro generally should correspond to Pro's single gyro */
	k_EInputActionOrigin_Switch_LeftGyro_Move,
	k_EInputActionOrigin_Switch_LeftGyro_Pitch,
	k_EInputActionOrigin_Switch_LeftGyro_Yaw,
	k_EInputActionOrigin_Switch_LeftGyro_Roll,
	k_EInputActionOrigin_Switch_LeftGrip_Lower, /* Left JoyCon SR Button */
	k_EInputActionOrigin_Switch_LeftGrip_Upper, /* Left JoyCon SL Button */
	k_EInputActionOrigin_Switch_RightGrip_Lower,  /* Right JoyCon SL Button */
	k_EInputActionOrigin_Switch_RightGrip_Upper,  /* Right JoyCon SR Button */
	k_EInputActionOrigin_Switch_Reserved11,
	k_EInputActionOrigin_Switch_Reserved12,
	k_EInputActionOrigin_Switch_Reserved13,
	k_EInputActionOrigin_Switch_Reserved14,
	k_EInputActionOrigin_Switch_Reserved15,
	k_EInputActionOrigin_Switch_Reserved16,
	k_EInputActionOrigin_Switch_Reserved17,
	k_EInputActionOrigin_Switch_Reserved18,
	k_EInputActionOrigin_Switch_Reserved19,
	k_EInputActionOrigin_Switch_Reserved20,
	
	/* Added in SDK 1.51 */
	k_EInputActionOrigin_PS5_X,
	k_EInputActionOrigin_PS5_Circle,
	k_EInputActionOrigin_PS5_Triangle,
	k_EInputActionOrigin_PS5_Square,
	k_EInputActionOrigin_PS5_LeftBumper,
	k_EInputActionOrigin_PS5_RightBumper,
	k_EInputActionOrigin_PS5_Option,	/* Start */
	k_EInputActionOrigin_PS5_Create,	/* Back */
	k_EInputActionOrigin_PS5_Mute,
	k_EInputActionOrigin_PS5_LeftPad_Touch,
	k_EInputActionOrigin_PS5_LeftPad_Swipe,
	k_EInputActionOrigin_PS5_LeftPad_Click,
	k_EInputActionOrigin_PS5_LeftPad_DPadNorth,
	k_EInputActionOrigin_PS5_LeftPad_DPadSouth,
	k_EInputActionOrigin_PS5_LeftPad_DPadWest,
	k_EInputActionOrigin_PS5_LeftPad_DPadEast,
	k_EInputActionOrigin_PS5_RightPad_Touch,
	k_EInputActionOrigin_PS5_RightPad_Swipe,
	k_EInputActionOrigin_PS5_RightPad_Click,
	k_EInputActionOrigin_PS5_RightPad_DPadNorth,
	k_EInputActionOrigin_PS5_RightPad_DPadSouth,
	k_EInputActionOrigin_PS5_RightPad_DPadWest,
	k_EInputActionOrigin_PS5_RightPad_DPadEast,
	k_EInputActionOrigin_PS5_CenterPad_Touch,
	k_EInputActionOrigin_PS5_CenterPad_Swipe,
	k_EInputActionOrigin_PS5_CenterPad_Click,
	k_EInputActionOrigin_PS5_CenterPad_DPadNorth,
	k_EInputActionOrigin_PS5_CenterPad_DPadSouth,
	k_EInputActionOrigin_PS5_CenterPad_DPadWest,
	k_EInputActionOrigin_PS5_CenterPad_DPadEast,
	k_EInputActionOrigin_PS5_LeftTrigger_Pull,
	k_EInputActionOrigin_PS5_LeftTrigger_Click,
	k_EInputActionOrigin_PS5_RightTrigger_Pull,
	k_EInputActionOrigin_PS5_RightTrigger_Click,
	k_EInputActionOrigin_PS5_LeftStick_Move,
	k_EInputActionOrigin_PS5_LeftStick_Click,
	k_EInputActionOrigin_PS5_LeftStick_DPadNorth,
	k_EInputActionOrigin_PS5_LeftStick_DPadSouth,
	k_EInputActionOrigin_PS5_LeftStick_DPadWest,
	k_EInputActionOrigin_PS5_LeftStick_DPadEast,
	k_EInputActionOrigin_PS5_RightStick_Move,
	k_EInputActionOrigin_PS5_RightStick_Click,
	k_EInputActionOrigin_PS5_RightStick_DPadNorth,
	k_EInputActionOrigin_PS5_RightStick_DPadSouth,
	k_EInputActionOrigin_PS5_RightStick_DPadWest,
	k_EInputActionOrigin_PS5_RightStick_DPadEast,
	k_EInputActionOrigin_PS5_DPad_North,
	k_EInputActionOrigin_PS5_DPad_South,
	k_EInputActionOrigin_PS5_DPad_West,
	k_EInputActionOrigin_PS5_DPad_East,
	k_EInputActionOrigin_PS5_Gyro_Move,
	k_EInputActionOrigin_PS5_Gyro_Pitch,
	k_EInputActionOrigin_PS5_Gyro_Yaw,
	k_EInputActionOrigin_PS5_Gyro_Roll,
	k_EInputActionOrigin_PS5_DPad_Move,
	k_EInputActionOrigin_PS5_Reserved1,
	k_EInputActionOrigin_PS5_Reserved2,
	k_EInputActionOrigin_PS5_Reserved3,
	k_EInputActionOrigin_PS5_Reserved4,
	k_EInputActionOrigin_PS5_Reserved5,
	k_EInputActionOrigin_PS5_Reserved6,
	k_EInputActionOrigin_PS5_Reserved7,
	k_EInputActionOrigin_PS5_Reserved8,
	k_EInputActionOrigin_PS5_Reserved9,
	k_EInputActionOrigin_PS5_Reserved10,
	k_EInputActionOrigin_PS5_Reserved11,
	k_EInputActionOrigin_PS5_Reserved12,
	k_EInputActionOrigin_PS5_Reserved13,
	k_EInputActionOrigin_PS5_Reserved14,
	k_EInputActionOrigin_PS5_Reserved15,
	k_EInputActionOrigin_PS5_Reserved16,
	k_EInputActionOrigin_PS5_Reserved17,
	k_EInputActionOrigin_PS5_Reserved18,
	k_EInputActionOrigin_PS5_Reserved19,
	k_EInputActionOrigin_PS5_Reserved20,

	k_EInputActionOrigin_Count, /* If Steam has added support for new controllers origins will go here. */
	k_EInputActionOrigin_MaximumPossibleValue = 32767, /* Origins are currently a maximum of 16 bits. */
};

enum EXboxOrigin
{
	k_EXboxOrigin_A,
	k_EXboxOrigin_B,
	k_EXboxOrigin_X,
	k_EXboxOrigin_Y,
	k_EXboxOrigin_LeftBumper,
	k_EXboxOrigin_RightBumper,
	k_EXboxOrigin_Menu,  /* Start */
	k_EXboxOrigin_View,  /* Back */
	k_EXboxOrigin_LeftTrigger_Pull,
	k_EXboxOrigin_LeftTrigger_Click,
	k_EXboxOrigin_RightTrigger_Pull,
	k_EXboxOrigin_RightTrigger_Click,
	k_EXboxOrigin_LeftStick_Move,
	k_EXboxOrigin_LeftStick_Click,
	k_EXboxOrigin_LeftStick_DPadNorth,
	k_EXboxOrigin_LeftStick_DPadSouth,
	k_EXboxOrigin_LeftStick_DPadWest,
	k_EXboxOrigin_LeftStick_DPadEast,
	k_EXboxOrigin_RightStick_Move,
	k_EXboxOrigin_RightStick_Click,
	k_EXboxOrigin_RightStick_DPadNorth,
	k_EXboxOrigin_RightStick_DPadSouth,
	k_EXboxOrigin_RightStick_DPadWest,
	k_EXboxOrigin_RightStick_DPadEast,
	k_EXboxOrigin_DPad_North,
	k_EXboxOrigin_DPad_South,
	k_EXboxOrigin_DPad_West,
	k_EXboxOrigin_DPad_East,
	k_EXboxOrigin_Count,
};

enum ESteamControllerPad
{
	k_ESteamControllerPad_Left,
	k_ESteamControllerPad_Right
};

enum EControllerHapticLocation
{
	k_EControllerHapticLocation_Left = ( 1 << k_ESteamControllerPad_Left ),
	k_EControllerHapticLocation_Right = ( 1 << k_ESteamControllerPad_Right ),
	k_EControllerHapticLocation_Both = ( 1 << k_ESteamControllerPad_Left | 1 << k_ESteamControllerPad_Right ),
};

enum EControllerHapticType
{
	k_EControllerHapticType_Off,
	k_EControllerHapticType_Tick,
	k_EControllerHapticType_Click,
};

enum ESteamInputType
{
	k_ESteamInputType_Unknown,
	k_ESteamInputType_SteamController,
	k_ESteamInputType_XBox360Controller,
	k_ESteamInputType_XBoxOneController,
	k_ESteamInputType_GenericGamepad,		/* DirectInput controllers */
	k_ESteamInputType_PS4Controller,
	k_ESteamInputType_AppleMFiController,	/* Unused */
	k_ESteamInputType_AndroidController,	/* Unused */
	k_ESteamInputType_SwitchJoyConPair,		/* Unused */
	k_ESteamInputType_SwitchJoyConSingle,	/* Unused */
	k_ESteamInputType_SwitchProController,
	k_ESteamInputType_MobileTouch,			/* Steam Link App On-screen Virtual Controller */
	k_ESteamInputType_PS3Controller,		/* Currently uses PS4 Origins */
	k_ESteamInputType_PS5Controller,		/* Added in SDK 151 */
	k_ESteamInputType_Count,
	k_ESteamInputType_MaximumPossibleValue = 255,
};

/* Individual values are used by the GetSessionInputConfigurationSettings bitmask */
enum ESteamInputConfigurationEnableType
{
	k_ESteamInputConfigurationEnableType_None			= 0x0000,
	k_ESteamInputConfigurationEnableType_Playstation	= 0x0001,
	k_ESteamInputConfigurationEnableType_Xbox			= 0x0002,
	k_ESteamInputConfigurationEnableType_Generic		= 0x0004,
	k_ESteamInputConfigurationEnableType_Switch			= 0x0008,
};

/* These values are passed into SetLEDColor */
enum ESteamInputLEDFlag
{
	k_ESteamInputLEDFlag_SetColor,
	/* Restore the LED color to the user's preference setting as set in the controller personalization menu. */
	/* This also happens automatically on exit of your game. */
	k_ESteamInputLEDFlag_RestoreUserDefault 
};

/* These values are passed into GetGlyphPNGForActionOrigin */
enum ESteamInputGlyphSize
{
	k_ESteamInputGlyphSize_Small,
	k_ESteamInputGlyphSize_Medium,
	k_ESteamInputGlyphSize_Large,
};

enum ESteamInputActionEventType
{
	ESteamInputActionEventType_DigitalAction,
	ESteamInputActionEventType_AnalogAction,
};

/* InputHandle_t is used to refer to a specific controller. */
/* This handle will consistently identify a controller, even if it is disconnected and re-connected */
typedef uint64 InputHandle_t;

/* These handles are used to refer to a specific in-game action or action set */
/* All action handles should be queried during initialization for performance reasons */
typedef uint64 InputActionSetHandle_t;
typedef uint64 InputDigitalActionHandle_t;
typedef uint64 InputAnalogActionHandle_t;

struct InputAnalogActionData_t
{
	/* Type of data coming from this action, this will match what got specified in the action set */
	EInputSourceMode eMode;
	
	/* The current state of this action; will be delta updates for mouse actions */
	float x, y;
	
	/* Whether or not this action is currently available to be bound in the active action set */
	bool bActive;
};

struct InputDigitalActionData_t
{
	/* The current state of this action; will be true if currently pressed */
	bool bState;
	
	/* Whether or not this action is currently available to be bound in the active action set */
	bool bActive;
};

struct InputMotionData_t
{
	/* Sensor-fused absolute rotation; will drift in heading */
	float rotQuatX;
	float rotQuatY;
	float rotQuatZ;
	float rotQuatW;
	
	/* Positional acceleration */
	float posAccelX;
	float posAccelY;
	float posAccelZ;

	/* Angular velocity */
	float rotVelX;
	float rotVelY;
	float rotVelZ;
};

/* FIXME: Is this required? */
/*
-----------------------------------------------------------------------------
Purpose: when callbacks are enabled this fires each time a controller action state changes
-----------------------------------------------------------------------------
*/

struct SteamInputActionEvent_t
{
	InputHandle_t controllerHandle;
	ESteamInputActionEventType eEventType;
	union action_union { /* FIXME: Does keeping name from top of struct/union here work? */
		struct analogAction {
			InputAnalogActionHandle_t actionHandle;
			InputAnalogActionData_t analogActionData;
		} analogAction;
		struct digitalAction {
			InputDigitalActionHandle_t actionHandle;
			InputDigitalActionData_t digitalActionData;
		} digitalAction;
	};
};

typedef void (*SteamInputActionEventCallbackPointer)(SteamInputActionEvent_t*);

#define STEAMINPUT_INTERFACE_VERSION "SteamInput005"

ice_steam_def_func(ISteamInput*, SteamInput, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamInput *, SteamInput, STEAMINPUT_INTERFACE_VERSION );*/

#define STEAM_CONTROLLER_MAX_COUNT 16
#define STEAM_CONTROLLER_MAX_ANALOG_ACTIONS 16
#define STEAM_CONTROLLER_MAX_DIGITAL_ACTIONS 128
#define STEAM_CONTROLLER_MAX_ORIGINS 8
#define STEAM_CONTROLLER_MAX_ACTIVE_LAYERS 16

/* When sending an option to a specific controller handle, you can send to all controllers via this command */
#define STEAM_CONTROLLER_HANDLE_ALL_CONTROLLERS UINT64_MAX
#define STEAM_CONTROLLER_MIN_ANALOG_ACTION_DATA -1.0f
#define STEAM_CONTROLLER_MAX_ANALOG_ACTION_DATA 1.0f

enum ESteamControllerPad
{
	k_ESteamControllerPad_Left,
	k_ESteamControllerPad_Right
};

/* Note: Please do not use action origins as a way to identify controller types. There is no guarantee that they will be added in a contiguous manner - use GetInputTypeForHandle instead */
/* Versions of Steam that add new controller types in the future will extend this enum if you're using a lookup table please check the bounds of any origins returned by Steam. */
enum EControllerActionOrigin
{
	/* Steam Controller */
	k_EControllerActionOrigin_None,
	k_EControllerActionOrigin_A,
	k_EControllerActionOrigin_B,
	k_EControllerActionOrigin_X,
	k_EControllerActionOrigin_Y,
	k_EControllerActionOrigin_LeftBumper,
	k_EControllerActionOrigin_RightBumper,
	k_EControllerActionOrigin_LeftGrip,
	k_EControllerActionOrigin_RightGrip,
	k_EControllerActionOrigin_Start,
	k_EControllerActionOrigin_Back,
	k_EControllerActionOrigin_LeftPad_Touch,
	k_EControllerActionOrigin_LeftPad_Swipe,
	k_EControllerActionOrigin_LeftPad_Click,
	k_EControllerActionOrigin_LeftPad_DPadNorth,
	k_EControllerActionOrigin_LeftPad_DPadSouth,
	k_EControllerActionOrigin_LeftPad_DPadWest,
	k_EControllerActionOrigin_LeftPad_DPadEast,
	k_EControllerActionOrigin_RightPad_Touch,
	k_EControllerActionOrigin_RightPad_Swipe,
	k_EControllerActionOrigin_RightPad_Click,
	k_EControllerActionOrigin_RightPad_DPadNorth,
	k_EControllerActionOrigin_RightPad_DPadSouth,
	k_EControllerActionOrigin_RightPad_DPadWest,
	k_EControllerActionOrigin_RightPad_DPadEast,
	k_EControllerActionOrigin_LeftTrigger_Pull,
	k_EControllerActionOrigin_LeftTrigger_Click,
	k_EControllerActionOrigin_RightTrigger_Pull,
	k_EControllerActionOrigin_RightTrigger_Click,
	k_EControllerActionOrigin_LeftStick_Move,
	k_EControllerActionOrigin_LeftStick_Click,
	k_EControllerActionOrigin_LeftStick_DPadNorth,
	k_EControllerActionOrigin_LeftStick_DPadSouth,
	k_EControllerActionOrigin_LeftStick_DPadWest,
	k_EControllerActionOrigin_LeftStick_DPadEast,
	k_EControllerActionOrigin_Gyro_Move,
	k_EControllerActionOrigin_Gyro_Pitch,
	k_EControllerActionOrigin_Gyro_Yaw,
	k_EControllerActionOrigin_Gyro_Roll,
	
	/* PS4 Dual Shock */
	k_EControllerActionOrigin_PS4_X,
	k_EControllerActionOrigin_PS4_Circle,
	k_EControllerActionOrigin_PS4_Triangle,
	k_EControllerActionOrigin_PS4_Square,
	k_EControllerActionOrigin_PS4_LeftBumper,
	k_EControllerActionOrigin_PS4_RightBumper,
	k_EControllerActionOrigin_PS4_Options,  /* Start */
	k_EControllerActionOrigin_PS4_Share,	/* Back */
	k_EControllerActionOrigin_PS4_LeftPad_Touch,
	k_EControllerActionOrigin_PS4_LeftPad_Swipe,
	k_EControllerActionOrigin_PS4_LeftPad_Click,
	k_EControllerActionOrigin_PS4_LeftPad_DPadNorth,
	k_EControllerActionOrigin_PS4_LeftPad_DPadSouth,
	k_EControllerActionOrigin_PS4_LeftPad_DPadWest,
	k_EControllerActionOrigin_PS4_LeftPad_DPadEast,
	k_EControllerActionOrigin_PS4_RightPad_Touch,
	k_EControllerActionOrigin_PS4_RightPad_Swipe,
	k_EControllerActionOrigin_PS4_RightPad_Click,
	k_EControllerActionOrigin_PS4_RightPad_DPadNorth,
	k_EControllerActionOrigin_PS4_RightPad_DPadSouth,
	k_EControllerActionOrigin_PS4_RightPad_DPadWest,
	k_EControllerActionOrigin_PS4_RightPad_DPadEast,
	k_EControllerActionOrigin_PS4_CenterPad_Touch,
	k_EControllerActionOrigin_PS4_CenterPad_Swipe,
	k_EControllerActionOrigin_PS4_CenterPad_Click,
	k_EControllerActionOrigin_PS4_CenterPad_DPadNorth,
	k_EControllerActionOrigin_PS4_CenterPad_DPadSouth,
	k_EControllerActionOrigin_PS4_CenterPad_DPadWest,
	k_EControllerActionOrigin_PS4_CenterPad_DPadEast,
	k_EControllerActionOrigin_PS4_LeftTrigger_Pull,
	k_EControllerActionOrigin_PS4_LeftTrigger_Click,
	k_EControllerActionOrigin_PS4_RightTrigger_Pull,
	k_EControllerActionOrigin_PS4_RightTrigger_Click,
	k_EControllerActionOrigin_PS4_LeftStick_Move,
	k_EControllerActionOrigin_PS4_LeftStick_Click,
	k_EControllerActionOrigin_PS4_LeftStick_DPadNorth,
	k_EControllerActionOrigin_PS4_LeftStick_DPadSouth,
	k_EControllerActionOrigin_PS4_LeftStick_DPadWest,
	k_EControllerActionOrigin_PS4_LeftStick_DPadEast,
	k_EControllerActionOrigin_PS4_RightStick_Move,
	k_EControllerActionOrigin_PS4_RightStick_Click,
	k_EControllerActionOrigin_PS4_RightStick_DPadNorth,
	k_EControllerActionOrigin_PS4_RightStick_DPadSouth,
	k_EControllerActionOrigin_PS4_RightStick_DPadWest,
	k_EControllerActionOrigin_PS4_RightStick_DPadEast,
	k_EControllerActionOrigin_PS4_DPad_North,
	k_EControllerActionOrigin_PS4_DPad_South,
	k_EControllerActionOrigin_PS4_DPad_West,
	k_EControllerActionOrigin_PS4_DPad_East,
	k_EControllerActionOrigin_PS4_Gyro_Move,
	k_EControllerActionOrigin_PS4_Gyro_Pitch,
	k_EControllerActionOrigin_PS4_Gyro_Yaw,
	k_EControllerActionOrigin_PS4_Gyro_Roll,

	/* XBox One */
	k_EControllerActionOrigin_XBoxOne_A,
	k_EControllerActionOrigin_XBoxOne_B,
	k_EControllerActionOrigin_XBoxOne_X,
	k_EControllerActionOrigin_XBoxOne_Y,
	k_EControllerActionOrigin_XBoxOne_LeftBumper,
	k_EControllerActionOrigin_XBoxOne_RightBumper,
	k_EControllerActionOrigin_XBoxOne_Menu,  /* Start */
	k_EControllerActionOrigin_XBoxOne_View,  /* Back */
	k_EControllerActionOrigin_XBoxOne_LeftTrigger_Pull,
	k_EControllerActionOrigin_XBoxOne_LeftTrigger_Click,
	k_EControllerActionOrigin_XBoxOne_RightTrigger_Pull,
	k_EControllerActionOrigin_XBoxOne_RightTrigger_Click,
	k_EControllerActionOrigin_XBoxOne_LeftStick_Move,
	k_EControllerActionOrigin_XBoxOne_LeftStick_Click,
	k_EControllerActionOrigin_XBoxOne_LeftStick_DPadNorth,
	k_EControllerActionOrigin_XBoxOne_LeftStick_DPadSouth,
	k_EControllerActionOrigin_XBoxOne_LeftStick_DPadWest,
	k_EControllerActionOrigin_XBoxOne_LeftStick_DPadEast,
	k_EControllerActionOrigin_XBoxOne_RightStick_Move,
	k_EControllerActionOrigin_XBoxOne_RightStick_Click,
	k_EControllerActionOrigin_XBoxOne_RightStick_DPadNorth,
	k_EControllerActionOrigin_XBoxOne_RightStick_DPadSouth,
	k_EControllerActionOrigin_XBoxOne_RightStick_DPadWest,
	k_EControllerActionOrigin_XBoxOne_RightStick_DPadEast,
	k_EControllerActionOrigin_XBoxOne_DPad_North,
	k_EControllerActionOrigin_XBoxOne_DPad_South,
	k_EControllerActionOrigin_XBoxOne_DPad_West,
	k_EControllerActionOrigin_XBoxOne_DPad_East,

	/* XBox 360 */
	k_EControllerActionOrigin_XBox360_A,
	k_EControllerActionOrigin_XBox360_B,
	k_EControllerActionOrigin_XBox360_X,
	k_EControllerActionOrigin_XBox360_Y,
	k_EControllerActionOrigin_XBox360_LeftBumper,
	k_EControllerActionOrigin_XBox360_RightBumper,
	k_EControllerActionOrigin_XBox360_Start,  /* Start */
	k_EControllerActionOrigin_XBox360_Back,  /* Back */
	k_EControllerActionOrigin_XBox360_LeftTrigger_Pull,
	k_EControllerActionOrigin_XBox360_LeftTrigger_Click,
	k_EControllerActionOrigin_XBox360_RightTrigger_Pull,
	k_EControllerActionOrigin_XBox360_RightTrigger_Click,
	k_EControllerActionOrigin_XBox360_LeftStick_Move,
	k_EControllerActionOrigin_XBox360_LeftStick_Click,
	k_EControllerActionOrigin_XBox360_LeftStick_DPadNorth,
	k_EControllerActionOrigin_XBox360_LeftStick_DPadSouth,
	k_EControllerActionOrigin_XBox360_LeftStick_DPadWest,
	k_EControllerActionOrigin_XBox360_LeftStick_DPadEast,
	k_EControllerActionOrigin_XBox360_RightStick_Move,
	k_EControllerActionOrigin_XBox360_RightStick_Click,
	k_EControllerActionOrigin_XBox360_RightStick_DPadNorth,
	k_EControllerActionOrigin_XBox360_RightStick_DPadSouth,
	k_EControllerActionOrigin_XBox360_RightStick_DPadWest,
	k_EControllerActionOrigin_XBox360_RightStick_DPadEast,
	k_EControllerActionOrigin_XBox360_DPad_North,
	k_EControllerActionOrigin_XBox360_DPad_South,
	k_EControllerActionOrigin_XBox360_DPad_West,
	k_EControllerActionOrigin_XBox360_DPad_East,	

	/* SteamController V2 */
	k_EControllerActionOrigin_SteamV2_A,
	k_EControllerActionOrigin_SteamV2_B,
	k_EControllerActionOrigin_SteamV2_X,
	k_EControllerActionOrigin_SteamV2_Y,
	k_EControllerActionOrigin_SteamV2_LeftBumper,
	k_EControllerActionOrigin_SteamV2_RightBumper,
	k_EControllerActionOrigin_SteamV2_LeftGrip_Lower,
	k_EControllerActionOrigin_SteamV2_LeftGrip_Upper,
	k_EControllerActionOrigin_SteamV2_RightGrip_Lower,
	k_EControllerActionOrigin_SteamV2_RightGrip_Upper,
	k_EControllerActionOrigin_SteamV2_LeftBumper_Pressure,
	k_EControllerActionOrigin_SteamV2_RightBumper_Pressure,
	k_EControllerActionOrigin_SteamV2_LeftGrip_Pressure,
	k_EControllerActionOrigin_SteamV2_RightGrip_Pressure,
	k_EControllerActionOrigin_SteamV2_LeftGrip_Upper_Pressure,
	k_EControllerActionOrigin_SteamV2_RightGrip_Upper_Pressure,
	k_EControllerActionOrigin_SteamV2_Start,
	k_EControllerActionOrigin_SteamV2_Back,
	k_EControllerActionOrigin_SteamV2_LeftPad_Touch,
	k_EControllerActionOrigin_SteamV2_LeftPad_Swipe,
	k_EControllerActionOrigin_SteamV2_LeftPad_Click,
	k_EControllerActionOrigin_SteamV2_LeftPad_Pressure,
	k_EControllerActionOrigin_SteamV2_LeftPad_DPadNorth,
	k_EControllerActionOrigin_SteamV2_LeftPad_DPadSouth,
	k_EControllerActionOrigin_SteamV2_LeftPad_DPadWest,
	k_EControllerActionOrigin_SteamV2_LeftPad_DPadEast,
	k_EControllerActionOrigin_SteamV2_RightPad_Touch,
	k_EControllerActionOrigin_SteamV2_RightPad_Swipe,
	k_EControllerActionOrigin_SteamV2_RightPad_Click,
	k_EControllerActionOrigin_SteamV2_RightPad_Pressure,
	k_EControllerActionOrigin_SteamV2_RightPad_DPadNorth,
	k_EControllerActionOrigin_SteamV2_RightPad_DPadSouth,
	k_EControllerActionOrigin_SteamV2_RightPad_DPadWest,
	k_EControllerActionOrigin_SteamV2_RightPad_DPadEast,
	k_EControllerActionOrigin_SteamV2_LeftTrigger_Pull,
	k_EControllerActionOrigin_SteamV2_LeftTrigger_Click,
	k_EControllerActionOrigin_SteamV2_RightTrigger_Pull,
	k_EControllerActionOrigin_SteamV2_RightTrigger_Click,
	k_EControllerActionOrigin_SteamV2_LeftStick_Move,
	k_EControllerActionOrigin_SteamV2_LeftStick_Click,
	k_EControllerActionOrigin_SteamV2_LeftStick_DPadNorth,
	k_EControllerActionOrigin_SteamV2_LeftStick_DPadSouth,
	k_EControllerActionOrigin_SteamV2_LeftStick_DPadWest,
	k_EControllerActionOrigin_SteamV2_LeftStick_DPadEast,
	k_EControllerActionOrigin_SteamV2_Gyro_Move,
	k_EControllerActionOrigin_SteamV2_Gyro_Pitch,
	k_EControllerActionOrigin_SteamV2_Gyro_Yaw,
	k_EControllerActionOrigin_SteamV2_Gyro_Roll,

	/* Switch - Pro or Joycons used as a single input device. */
	/* This does not apply to a single joycon */
	k_EControllerActionOrigin_Switch_A,
	k_EControllerActionOrigin_Switch_B,
	k_EControllerActionOrigin_Switch_X,
	k_EControllerActionOrigin_Switch_Y,
	k_EControllerActionOrigin_Switch_LeftBumper,
	k_EControllerActionOrigin_Switch_RightBumper,
	k_EControllerActionOrigin_Switch_Plus,  /* Start */
	k_EControllerActionOrigin_Switch_Minus,	/* Back */
	k_EControllerActionOrigin_Switch_Capture,
	k_EControllerActionOrigin_Switch_LeftTrigger_Pull,
	k_EControllerActionOrigin_Switch_LeftTrigger_Click,
	k_EControllerActionOrigin_Switch_RightTrigger_Pull,
	k_EControllerActionOrigin_Switch_RightTrigger_Click,
	k_EControllerActionOrigin_Switch_LeftStick_Move,
	k_EControllerActionOrigin_Switch_LeftStick_Click,
	k_EControllerActionOrigin_Switch_LeftStick_DPadNorth,
	k_EControllerActionOrigin_Switch_LeftStick_DPadSouth,
	k_EControllerActionOrigin_Switch_LeftStick_DPadWest,
	k_EControllerActionOrigin_Switch_LeftStick_DPadEast,
	k_EControllerActionOrigin_Switch_RightStick_Move,
	k_EControllerActionOrigin_Switch_RightStick_Click,
	k_EControllerActionOrigin_Switch_RightStick_DPadNorth,
	k_EControllerActionOrigin_Switch_RightStick_DPadSouth,
	k_EControllerActionOrigin_Switch_RightStick_DPadWest,
	k_EControllerActionOrigin_Switch_RightStick_DPadEast,
	k_EControllerActionOrigin_Switch_DPad_North,
	k_EControllerActionOrigin_Switch_DPad_South,
	k_EControllerActionOrigin_Switch_DPad_West,
	k_EControllerActionOrigin_Switch_DPad_East,
	k_EControllerActionOrigin_Switch_ProGyro_Move,  /* Primary Gyro in Pro Controller, or Right JoyCon */
	k_EControllerActionOrigin_Switch_ProGyro_Pitch,  /* Primary Gyro in Pro Controller, or Right JoyCon */
	k_EControllerActionOrigin_Switch_ProGyro_Yaw,  /* Primary Gyro in Pro Controller, or Right JoyCon */
	k_EControllerActionOrigin_Switch_ProGyro_Roll,  /* Primary Gyro in Pro Controller, or Right JoyCon */
	/* Switch JoyCon Specific */
	k_EControllerActionOrigin_Switch_RightGyro_Move,  /* Right JoyCon Gyro generally should correspond to Pro's single gyro */
	k_EControllerActionOrigin_Switch_RightGyro_Pitch,  /* Right JoyCon Gyro generally should correspond to Pro's single gyro */
	k_EControllerActionOrigin_Switch_RightGyro_Yaw,  /* Right JoyCon Gyro generally should correspond to Pro's single gyro */
	k_EControllerActionOrigin_Switch_RightGyro_Roll,  /* Right JoyCon Gyro generally should correspond to Pro's single gyro */
	k_EControllerActionOrigin_Switch_LeftGyro_Move,
	k_EControllerActionOrigin_Switch_LeftGyro_Pitch,
	k_EControllerActionOrigin_Switch_LeftGyro_Yaw,
	k_EControllerActionOrigin_Switch_LeftGyro_Roll,
	k_EControllerActionOrigin_Switch_LeftGrip_Lower, /* Left JoyCon SR Button */
	k_EControllerActionOrigin_Switch_LeftGrip_Upper, /* Left JoyCon SL Button */
	k_EControllerActionOrigin_Switch_RightGrip_Lower,  /* Right JoyCon SL Button */
	k_EControllerActionOrigin_Switch_RightGrip_Upper,  /* Right JoyCon SR Button */

	/* Added in SDK 1.45 */
	k_EControllerActionOrigin_PS4_DPad_Move,
	k_EControllerActionOrigin_XBoxOne_DPad_Move,
	k_EControllerActionOrigin_XBox360_DPad_Move,
	k_EControllerActionOrigin_Switch_DPad_Move,

	/* Added in SDK 1.51 */
	k_EControllerActionOrigin_PS5_X,
	k_EControllerActionOrigin_PS5_Circle,
	k_EControllerActionOrigin_PS5_Triangle,
	k_EControllerActionOrigin_PS5_Square,
	k_EControllerActionOrigin_PS5_LeftBumper,
	k_EControllerActionOrigin_PS5_RightBumper,
	k_EControllerActionOrigin_PS5_Option,  /* Start */
	k_EControllerActionOrigin_PS5_Create,	/* Back */
	k_EControllerActionOrigin_PS5_Mute,
	k_EControllerActionOrigin_PS5_LeftPad_Touch,
	k_EControllerActionOrigin_PS5_LeftPad_Swipe,
	k_EControllerActionOrigin_PS5_LeftPad_Click,
	k_EControllerActionOrigin_PS5_LeftPad_DPadNorth,
	k_EControllerActionOrigin_PS5_LeftPad_DPadSouth,
	k_EControllerActionOrigin_PS5_LeftPad_DPadWest,
	k_EControllerActionOrigin_PS5_LeftPad_DPadEast,
	k_EControllerActionOrigin_PS5_RightPad_Touch,
	k_EControllerActionOrigin_PS5_RightPad_Swipe,
	k_EControllerActionOrigin_PS5_RightPad_Click,
	k_EControllerActionOrigin_PS5_RightPad_DPadNorth,
	k_EControllerActionOrigin_PS5_RightPad_DPadSouth,
	k_EControllerActionOrigin_PS5_RightPad_DPadWest,
	k_EControllerActionOrigin_PS5_RightPad_DPadEast,
	k_EControllerActionOrigin_PS5_CenterPad_Touch,
	k_EControllerActionOrigin_PS5_CenterPad_Swipe,
	k_EControllerActionOrigin_PS5_CenterPad_Click,
	k_EControllerActionOrigin_PS5_CenterPad_DPadNorth,
	k_EControllerActionOrigin_PS5_CenterPad_DPadSouth,
	k_EControllerActionOrigin_PS5_CenterPad_DPadWest,
	k_EControllerActionOrigin_PS5_CenterPad_DPadEast,
	k_EControllerActionOrigin_PS5_LeftTrigger_Pull,
	k_EControllerActionOrigin_PS5_LeftTrigger_Click,
	k_EControllerActionOrigin_PS5_RightTrigger_Pull,
	k_EControllerActionOrigin_PS5_RightTrigger_Click,
	k_EControllerActionOrigin_PS5_LeftStick_Move,
	k_EControllerActionOrigin_PS5_LeftStick_Click,
	k_EControllerActionOrigin_PS5_LeftStick_DPadNorth,
	k_EControllerActionOrigin_PS5_LeftStick_DPadSouth,
	k_EControllerActionOrigin_PS5_LeftStick_DPadWest,
	k_EControllerActionOrigin_PS5_LeftStick_DPadEast,
	k_EControllerActionOrigin_PS5_RightStick_Move,
	k_EControllerActionOrigin_PS5_RightStick_Click,
	k_EControllerActionOrigin_PS5_RightStick_DPadNorth,
	k_EControllerActionOrigin_PS5_RightStick_DPadSouth,
	k_EControllerActionOrigin_PS5_RightStick_DPadWest,
	k_EControllerActionOrigin_PS5_RightStick_DPadEast,
	k_EControllerActionOrigin_PS5_DPad_Move,
	k_EControllerActionOrigin_PS5_DPad_North,
	k_EControllerActionOrigin_PS5_DPad_South,
	k_EControllerActionOrigin_PS5_DPad_West,
	k_EControllerActionOrigin_PS5_DPad_East,
	k_EControllerActionOrigin_PS5_Gyro_Move,
	k_EControllerActionOrigin_PS5_Gyro_Pitch,
	k_EControllerActionOrigin_PS5_Gyro_Yaw,
	k_EControllerActionOrigin_PS5_Gyro_Roll,

	k_EControllerActionOrigin_XBoxOne_LeftGrip_Lower, 
	k_EControllerActionOrigin_XBoxOne_LeftGrip_Upper, 
	k_EControllerActionOrigin_XBoxOne_RightGrip_Lower,
	k_EControllerActionOrigin_XBoxOne_RightGrip_Upper,
	k_EControllerActionOrigin_XBoxOne_Share,

	k_EControllerActionOrigin_Count, /* If Steam has added support for new controllers origins will go here. */
	k_EControllerActionOrigin_MaximumPossibleValue = 32767, /* Origins are currently a maximum of 16 bits. */
};

enum ESteamControllerLEDFlag
{
	k_ESteamControllerLEDFlag_SetColor,
	k_ESteamControllerLEDFlag_RestoreUserDefault
};

/* ControllerHandle_t is used to refer to a specific controller. */
/* This handle will consistently identify a controller, even if it is disconnected and re-connected */
typedef uint64 ControllerHandle_t;

/* These handles are used to refer to a specific in-game action or action set *?
/* All action handles should be queried during initialization for performance reasons */
typedef uint64 ControllerActionSetHandle_t;
typedef uint64 ControllerDigitalActionHandle_t;
typedef uint64 ControllerAnalogActionHandle_t;

#define ControllerAnalogActionData_t InputAnalogActionData_t
#define ControllerDigitalActionData_t InputDigitalActionData_t
#define ControllerMotionData_t InputMotionData_t

#define STEAMCONTROLLER_INTERFACE_VERSION "SteamController008"

ice_steam_def_func(ISteamController*, SteamController, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamController *, SteamController, STEAMCONTROLLER_INTERFACE_VERSION );*/

typedef uint64 UGCQueryHandle_t;
typedef uint64 UGCUpdateHandle_t;

const UGCQueryHandle_t k_UGCQueryHandleInvalid = 0xffffffffffffffffull;
const UGCUpdateHandle_t k_UGCUpdateHandleInvalid = 0xffffffffffffffffull;

/* Matching UGC types for queries */
enum EUGCMatchingUGCType
{
	k_EUGCMatchingUGCType_Items				 = 0,		/* both mtx items and ready-to-use items */
	k_EUGCMatchingUGCType_Items_Mtx			 = 1,
	k_EUGCMatchingUGCType_Items_ReadyToUse	 = 2,
	k_EUGCMatchingUGCType_Collections		 = 3,
	k_EUGCMatchingUGCType_Artwork			 = 4,
	k_EUGCMatchingUGCType_Videos			 = 5,
	k_EUGCMatchingUGCType_Screenshots		 = 6,
	k_EUGCMatchingUGCType_AllGuides			 = 7,		/* both web guides and integrated guides */
	k_EUGCMatchingUGCType_WebGuides			 = 8,
	k_EUGCMatchingUGCType_IntegratedGuides	 = 9,
	k_EUGCMatchingUGCType_UsableInGame		 = 10,		/* ready-to-use items and integrated guides */
	k_EUGCMatchingUGCType_ControllerBindings = 11,
	k_EUGCMatchingUGCType_GameManagedItems	 = 12,		/* game managed items (not managed by users) */
	k_EUGCMatchingUGCType_All				 = ~0,		/* @note: will only be valid for CreateQueryUserUGCRequest requests */
};

/* Different lists of published UGC for a user. */
/* If the current logged in user is different than the specified user, then some options may not be allowed. */
enum EUserUGCList
{
	k_EUserUGCList_Published,
	k_EUserUGCList_VotedOn,
	k_EUserUGCList_VotedUp,
	k_EUserUGCList_VotedDown,
	k_EUserUGCList_WillVoteLater,
	k_EUserUGCList_Favorited,
	k_EUserUGCList_Subscribed,
	k_EUserUGCList_UsedOrPlayed,
	k_EUserUGCList_Followed,
};

/* Sort order for user published UGC lists (defaults to creation order descending) */
enum EUserUGCListSortOrder
{
	k_EUserUGCListSortOrder_CreationOrderDesc,
	k_EUserUGCListSortOrder_CreationOrderAsc,
	k_EUserUGCListSortOrder_TitleAsc,
	k_EUserUGCListSortOrder_LastUpdatedDesc,
	k_EUserUGCListSortOrder_SubscriptionDateDesc,
	k_EUserUGCListSortOrder_VoteScoreDesc,
	k_EUserUGCListSortOrder_ForModeration,
};

/* Combination of sorting and filtering for queries across all UGC */
enum EUGCQuery
{
	k_EUGCQuery_RankedByVote								  = 0,
	k_EUGCQuery_RankedByPublicationDate						  = 1,
	k_EUGCQuery_AcceptedForGameRankedByAcceptanceDate		  = 2,
	k_EUGCQuery_RankedByTrend								  = 3,
	k_EUGCQuery_FavoritedByFriendsRankedByPublicationDate	  = 4,
	k_EUGCQuery_CreatedByFriendsRankedByPublicationDate		  = 5,
	k_EUGCQuery_RankedByNumTimesReported					  = 6,
	k_EUGCQuery_CreatedByFollowedUsersRankedByPublicationDate = 7,
	k_EUGCQuery_NotYetRated									  = 8,
	k_EUGCQuery_RankedByTotalVotesAsc						  = 9,
	k_EUGCQuery_RankedByVotesUp								  = 10,
	k_EUGCQuery_RankedByTextSearch							  = 11,
	k_EUGCQuery_RankedByTotalUniqueSubscriptions			  = 12,
	k_EUGCQuery_RankedByPlaytimeTrend						  = 13,
	k_EUGCQuery_RankedByTotalPlaytime						  = 14,
	k_EUGCQuery_RankedByAveragePlaytimeTrend				  = 15,
	k_EUGCQuery_RankedByLifetimeAveragePlaytime				  = 16,
	k_EUGCQuery_RankedByPlaytimeSessionsTrend				  = 17,
	k_EUGCQuery_RankedByLifetimePlaytimeSessions			  = 18,
	k_EUGCQuery_RankedByLastUpdatedDate						  = 19,
};

enum EItemUpdateStatus
{
	k_EItemUpdateStatusInvalid 				= 0, /* The item update handle was invalid, job might be finished, listen too SubmitItemUpdateResult_t */
	k_EItemUpdateStatusPreparingConfig 		= 1, /* The item update is processing configuration data */
	k_EItemUpdateStatusPreparingContent		= 2, /* The item update is reading and processing content files */
	k_EItemUpdateStatusUploadingContent		= 3, /* The item update is uploading content changes to Steam */
	k_EItemUpdateStatusUploadingPreviewFile	= 4, /* The item update is uploading new preview file image */
	k_EItemUpdateStatusCommittingChanges	= 5  /* The item update is committing all changes */
};

enum EItemState
{
	k_EItemStateNone			= 0,	/* item not tracked on client */
	k_EItemStateSubscribed		= 1,	/* current user is subscribed to this item. Not just cached. */
	k_EItemStateLegacyItem		= 2,	/* item was created with ISteamRemoteStorage */
	k_EItemStateInstalled		= 4,	/* item is installed and usable (but maybe out of date) */
	k_EItemStateNeedsUpdate		= 8,	/* items needs an update. Either because it's not installed yet or creator updated content */
	k_EItemStateDownloading		= 16,	/* item update is currently downloading */
	k_EItemStateDownloadPending	= 32,	/* DownloadItem() was called for this item, content isn't available until DownloadItemResult_t is fired */
};

enum EItemStatistic
{
	k_EItemStatistic_NumSubscriptions					 = 0,
	k_EItemStatistic_NumFavorites						 = 1,
	k_EItemStatistic_NumFollowers						 = 2,
	k_EItemStatistic_NumUniqueSubscriptions				 = 3,
	k_EItemStatistic_NumUniqueFavorites					 = 4,
	k_EItemStatistic_NumUniqueFollowers					 = 5,
	k_EItemStatistic_NumUniqueWebsiteViews				 = 6,
	k_EItemStatistic_ReportScore						 = 7,
	k_EItemStatistic_NumSecondsPlayed					 = 8,
	k_EItemStatistic_NumPlaytimeSessions				 = 9,
	k_EItemStatistic_NumComments						 = 10,
	k_EItemStatistic_NumSecondsPlayedDuringTimePeriod	 = 11,
	k_EItemStatistic_NumPlaytimeSessionsDuringTimePeriod = 12,
};

enum EItemPreviewType
{
	k_EItemPreviewType_Image							= 0,	/* standard image file expected (e.g. jpg, png, gif, etc.) */
	k_EItemPreviewType_YouTubeVideo						= 1,	/* video id is stored */
	k_EItemPreviewType_Sketchfab						= 2,	/* model id is stored */
	k_EItemPreviewType_EnvironmentMap_HorizontalCross	= 3,	/* standard image file expected - cube map in the layout */
																/* +---+---+-------+ */
																/* |   |Up |       | */
																/* +---+---+---+---+ */
																/* | L | F | R | B | */
																/* +---+---+---+---+ */
																/* |   |Dn |       | */
																/* +---+---+---+---+ */
	k_EItemPreviewType_EnvironmentMap_LatLong			= 4,	/* standard image file expected */
	k_EItemPreviewType_ReservedMax						= 255,	/* you can specify your own types above this value */
};

const uint32 kNumUGCResultsPerPage = 50;
const uint32 k_cchDeveloperMetadataMax = 5000;

/* Details for a single published file/UGC */
struct SteamUGCDetails_t
{
	PublishedFileId_t m_nPublishedFileId;
	EResult m_eResult;												/* The result of the operation.	*/
	EWorkshopFileType m_eFileType;									/* Type of the file */
	AppId_t m_nCreatorAppID;										/* ID of the app that created this file. */
	AppId_t m_nConsumerAppID;										/* ID of the app that will consume this file. */
	/* char m_rgchTitle[k_cchPublishedDocumentTitleMax]; */				/* title of document */
	/* char m_rgchDescription[k_cchPublishedDocumentDescriptionMax]; */	/* description of document */
	char m_rgchTitle[129];			                                /* title of document */
	char m_rgchDescription[8000];	                                /* description of document */
	uint64 m_ulSteamIDOwner;										/* Steam ID of the user who created this content. */
	uint32 m_rtimeCreated;											/* time when the published file was created */
	uint32 m_rtimeUpdated;											/* time when the published file was last updated  */
	uint32 m_rtimeAddedToUserList;									/* time when the user added the published file to their list (not always applicable) */
	ERemoteStoragePublishedFileVisibility m_eVisibility;			/* visibility */
	bool m_bBanned;													/* whether the file was banned */
	bool m_bAcceptedForUse;											/* developer has specifically flagged this item as accepted in the Workshop */
	bool m_bTagsTruncated;											/* whether the list of tags was too long to be returned in the provided buffer */
	/*char m_rgchTags[k_cchTagListMax];	*/							/* comma separated list of all tags associated with this file	 */
	char m_rgchTags[1025];								            /* comma separated list of all tags associated with this file	 */
	/* file/url information */
	UGCHandle_t m_hFile;											/* The handle of the primary file */
	UGCHandle_t m_hPreviewFile;										/* The handle of the preview file */
	/* char m_pchFileName[k_cchFilenameMax]; */						/* The cloud filename of the primary file */
	char m_pchFileName[260];							            /* The cloud filename of the primary file */
	int32 m_nFileSize;												/* Size of the primary file */
	int32 m_nPreviewFileSize;										/* Size of the preview file */
	/* char m_rgchURL[k_cchPublishedFileURLMax]; */					/* URL (for a video or a website) */
	char m_rgchURL[256];								            /* URL (for a video or a website) */
	/* voting information */
	uint32 m_unVotesUp;												/* number of votes up */
	uint32 m_unVotesDown;											/* number of votes down */
	float m_flScore;												/* calculated score */
	/* collection details */
	uint32 m_unNumChildren;							
};

#define STEAMUGC_INTERFACE_VERSION "STEAMUGC_INTERFACE_VERSION015"

ice_steam_def_func(ISteamUGC*, SteamUGC, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamUGC *, SteamUGC, STEAMUGC_INTERFACE_VERSION );*/

ice_steam_def_func(ISteamUGC*, SteamGameServerUGC, ())
/*STEAM_DEFINE_GAMESERVER_INTERFACE_ACCESSOR( ISteamUGC *, SteamGameServerUGC, STEAMUGC_INTERFACE_VERSION );*/

#define STEAMAPPLIST_INTERFACE_VERSION "STEAMAPPLIST_INTERFACE_VERSION001"

ice_steam_def_func(ISteamAppList*, SteamAppList, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamAppList *, SteamAppList, STEAMAPPLIST_INTERFACE_VERSION );*/

typedef uint32 HHTMLBrowser;
const uint32 INVALID_HTMLBROWSER = 0;

#define STEAMHTMLSURFACE_INTERFACE_VERSION "STEAMHTMLSURFACE_INTERFACE_VERSION_005"

ice_steam_def_func(ISteamHTMLSurface*, SteamHTMLSurface, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamHTMLSurface *, SteamHTMLSurface, STEAMHTMLSURFACE_INTERFACE_VERSION );*/

/* Every individual instance of an item has a globally-unique ItemInstanceID.
/* This ID is unique to the combination of (player, specific item instance) and will not be transferred to another player or re-used for another item. */
typedef uint64 SteamItemInstanceID_t;

static const SteamItemInstanceID_t k_SteamItemInstanceIDInvalid = (SteamItemInstanceID_t)~0;

/* Types of items in your game are identified by a 32-bit "item definition number".
/* Valid definition numbers are between 1 and 999999999; numbers less than or equal to zero are invalid, and numbers greater than or equal to one billion (1x10^9) are reserved for internal Steam use. */
typedef int32 SteamItemDef_t;

enum ESteamItemFlags
{
	/* Item status flags - these flags are permanently attached to specific item instances */
	k_ESteamItemNoTrade = 1 << 0, /* This item is account-locked and cannot be traded or given away. */

	/* Action confirmation flags - these flags are set one time only, as part of a result set */
	k_ESteamItemRemoved = 1 << 8,	/* The item has been destroyed, traded away, expired, or otherwise invalidated */
	k_ESteamItemConsumed = 1 << 9,	/* The item quantity has been decreased by 1 via ConsumeItem API. */

	/* All other flag bits are currently reserved for internal Steam use at this time. */
	/* Do not assume anything about the state of other flags which are not defined here. */
};

struct SteamItemDetails_t
{
	SteamItemInstanceID_t m_itemId;
	SteamItemDef_t m_iDefinition;
	uint16 m_unQuantity;
	uint16 m_unFlags; /* see ESteamItemFlags */
};

typedef int32 SteamInventoryResult_t;

static const SteamInventoryResult_t k_SteamInventoryResultInvalid = -1;

typedef uint64 SteamInventoryUpdateHandle_t;
const SteamInventoryUpdateHandle_t k_SteamInventoryUpdateHandleInvalid = 0xffffffffffffffffull;

#define STEAMINVENTORY_INTERFACE_VERSION "STEAMINVENTORY_INTERFACE_V003"

ice_steam_def_func(ISteamInventory*, SteamInventory, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamInventory *, SteamInventory, STEAMINVENTORY_INTERFACE_VERSION );*/

ice_steam_def_func(ISteamInventory*, SteamGameServerInventory, ())
/*STEAM_DEFINE_GAMESERVER_INTERFACE_ACCESSOR( ISteamInventory *, SteamGameServerInventory, STEAMINVENTORY_INTERFACE_VERSION );*/

#define STEAMVIDEO_INTERFACE_VERSION "STEAMVIDEO_INTERFACE_V002"

ice_steam_def_func(ISteamVideo*, SteamVideo, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamVideo *, SteamVideo, STEAMVIDEO_INTERFACE_VERSION );*/

/* Feature types for parental settings */
enum EParentalFeature
{
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
	k_EFeatureSiteLicense = 13,
	k_EFeatureMax
};

#define STEAMPARENTALSETTINGS_INTERFACE_VERSION "STEAMPARENTALSETTINGS_INTERFACE_VERSION001"

ice_steam_def_func(ISteamParentalSettings*, SteamParentalSettings, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamParentalSettings *, SteamParentalSettings, STEAMPARENTALSETTINGS_INTERFACE_VERSION );*/

/*
-----------------------------------------------------------------------------
Purpose: The form factor of a device
-----------------------------------------------------------------------------
*/
enum ESteamDeviceFormFactor
{
	k_ESteamDeviceFormFactorUnknown		= 0,
	k_ESteamDeviceFormFactorPhone		= 1,
	k_ESteamDeviceFormFactorTablet		= 2,
	k_ESteamDeviceFormFactorComputer	= 3,
	k_ESteamDeviceFormFactorTV			= 4,
};

/* Steam Remote Play session ID */
typedef uint32 RemotePlaySessionID_t;

#define STEAMREMOTEPLAY_INTERFACE_VERSION "STEAMREMOTEPLAY_INTERFACE_VERSION001"

ice_steam_def_func(ISteamRemotePlay*, SteamRemotePlay, ())
/*STEAM_DEFINE_USER_INTERFACE_ACCESSOR( ISteamRemotePlay *, SteamRemotePlay, STEAMREMOTEPLAY_INTERFACE_VERSION );*/

/*-----------------------------------------------------------------------------*/
/* SteamNetworkingSockets config. */
/* #define STEAMNETWORKINGSOCKETS_STANDALONELIB */ /* Comment this in to support compiling/linking with the standalone library / gamenetworkingsockets opensource */
/* #define STEAMNETWORKINGSOCKETS_STEAMAPI /* Compiling/link with steam_api.h and Steamworks SDK */
/*-----------------------------------------------------------------------------*/

#if !defined( STEAMNETWORKINGSOCKETS_OPENSOURCE ) && !defined( STEAMNETWORKINGSOCKETS_STREAMINGCLIENT )
#  define STEAMNETWORKINGSOCKETS_STEAM
#endif
#ifdef NN_NINTENDO_SDK /* We always static link on Nintendo */
#  define STEAMNETWORKINGSOCKETS_STATIC_LINK
#endif
#if defined( STEAMNETWORKINGSOCKETS_STATIC_LINK )
#  define STEAMNETWORKINGSOCKETS_INTERFACE extern "C"
#elif defined(STEAMNETWORKINGSOCKETS_FOREXPORT)
#  ifdef _WIN32
#    define STEAMNETWORKINGSOCKETS_INTERFACE extern "C" __declspec( dllexport )
#  else
#    define STEAMNETWORKINGSOCKETS_INTERFACE extern "C" __attribute__((visibility("default")))
#  endif
#else
#  ifdef _WIN32
#    define STEAMNETWORKINGSOCKETS_INTERFACE extern "C" __declspec( dllimport )
#  else
#    define STEAMNETWORKINGSOCKETS_INTERFACE extern "C"
#  endif
#endif

ice_steam_def_opaque_type(SteamDatagramRelayAuthTicket)
ice_steam_def_opaque_type(SteamDatagramHostedAddress)
ice_steam_def_opaque_type(SteamDatagramGameCoordinatorServerLogin)
ice_steam_def_opaque_type(SteamNetConnectionStatusChangedCallback_t)
ice_steam_def_opaque_type(SteamNetAuthenticationStatus_t)
ice_steam_def_opaque_type(SteamRelayNetworkStatus_t)
ice_steam_def_opaque_type(SteamNetworkingMessagesSessionRequest_t)
ice_steam_def_opaque_type(SteamNetworkingMessagesSessionFailed_t)

typedef void (*FnSteamNetConnectionStatusChanged)(SteamNetConnectionStatusChangedCallback_t*);
typedef void (*FnSteamNetAuthenticationStatusChanged)(SteamNetAuthenticationStatus_t*);
typedef void (*FnSteamRelayNetworkStatusChanged)(SteamRelayNetworkStatus_t*);
typedef void (*FnSteamNetworkingMessagesSessionRequest)(SteamNetworkingMessagesSessionRequest_t*);
typedef void (*FnSteamNetworkingMessagesSessionFailed)(SteamNetworkingMessagesSessionFailed_t*);

/* Handle used to identify a connection to a remote host. */
typedef uint32 HSteamNetConnection;
const HSteamNetConnection k_HSteamNetConnection_Invalid = 0;

/* Handle used to identify a "listen socket".  Unlike traditional Berkeley sockets, a listen socket and a connection are two different abstractions. */
typedef uint32 HSteamListenSocket;
const HSteamListenSocket k_HSteamListenSocket_Invalid = 0;

/* Handle used to identify a poll group, used to query many connections at once efficiently. */
typedef uint32 HSteamNetPollGroup;
const HSteamNetPollGroup k_HSteamNetPollGroup_Invalid = 0;

/* Max length of diagnostic error message */
const int k_cchMaxSteamNetworkingErrMsg = 1024;

/* Used to return English-language diagnostic error messages to caller. */
/* (For debugging or spewing to a console, etc.  Not intended for UI.) */
typedef char SteamNetworkingErrMsg[ k_cchMaxSteamNetworkingErrMsg ];

/* Identifier used for a network location point of presence.  (E.g. a Valve data center.) */
/* Typically you won't need to directly manipulate these. */
typedef uint32 SteamNetworkingPOPID;

/*
A local timestamp.
You can subtract two timestamps to get the number of elapsed microseconds.
This is guaranteed to increase over time during the lifetime of a process, but not globally across runs.
You don't need to worry about the value wrapping around.
Note that the underlying clock might not actually have microsecond resolution.
*/
typedef int64 SteamNetworkingMicroseconds;

/* Describe the status of a particular network resource */
enum ESteamNetworkingAvailability
{
	/* Negative values indicate a problem. */

	/*
	In general, we will not automatically retry unless you take some action that
	depends on of requests this resource, such as querying the status, attempting
	to initiate a connection, receive a connection, etc.  If you do not take any
	action at all, we do not automatically retry in the background.
	*/
	k_ESteamNetworkingAvailability_CannotTry = -102,	/* A dependent resource is missing, so this service is unavailable.  (E.g. we cannot talk to routers because Internet is down or we don't have the network config.) */
	k_ESteamNetworkingAvailability_Failed = -101,		/* We have tried for enough time that we would expect to have been successful by now.  We have never been successful */
	k_ESteamNetworkingAvailability_Previously = -100,	/* We tried and were successful at one time, but now it looks like we have a problem */

	k_ESteamNetworkingAvailability_Retrying = -10,		/* We previously failed and are currently retrying */

	// Not a problem, but not ready either
	k_ESteamNetworkingAvailability_NeverTried = 1,		/* We don't know because we haven't ever checked/tried */
	k_ESteamNetworkingAvailability_Waiting = 2,			/* We're waiting on a dependent resource to be acquired.  (E.g. we cannot obtain a cert until we are logged into Steam.  We cannot measure latency to relays until we have the network config.) */
	k_ESteamNetworkingAvailability_Attempting = 3,		/* We're actively trying now, but are not yet successful. */

	k_ESteamNetworkingAvailability_Current = 100,		/* Resource is online/available */


	k_ESteamNetworkingAvailability_Unknown = 0,			/* Internal dummy/sentinel, or value is not applicable in this context */
	k_ESteamNetworkingAvailability__Force32bit = 0x7fffffff,
};

/* Describing network hosts */

/* Different methods of describing the identity of a network host */
enum ESteamNetworkingIdentityType
{
	/*
	Dummy/empty/invalid.
	Please note that if we parse a string that we don't recognize
	but that appears reasonable, we will NOT use this type.  Instead
	we'll use k_ESteamNetworkingIdentityType_UnknownType.
	*/
	k_ESteamNetworkingIdentityType_Invalid = 0,

	/* Basic platform-specific identifiers. */
	k_ESteamNetworkingIdentityType_SteamID = 16, /* 64-bit CSteamID */

	/* Special identifiers. */

	/*
	Use their IP address (and port) as their "identity".
	These types of identities are always unauthenticated.
	They are useful for porting plain sockets code, and other
	situations where you don't care about authentication.  In this
	case, the local identity will be "localhost",
	and the remote address will be their network address.
	*/

	/*
	We use the same type for either IPv4 or IPv6, and
	the address is always store as IPv6.  We use IPv4
	mapped addresses to handle IPv4.
	*/
	k_ESteamNetworkingIdentityType_IPAddress = 1,

	/*
	Generic string/binary blobs.  It's up to your app to interpret this.
	This library can tell you if the remote host presented a certificate
	signed by somebody you have chosen to trust, with this identity on it.
	It's up to you to ultimately decide what this identity means.
	*/
	k_ESteamNetworkingIdentityType_GenericString = 2,
	k_ESteamNetworkingIdentityType_GenericBytes = 3,

	/*
	This identity type is used when we parse a string that looks like is a
	valid identity, just of a kind that we don't recognize.  In this case, we
	can often still communicate with the peer!  Allowing such identities
	for types we do not recognize useful is very useful for forward compatibility.
	*/
	k_ESteamNetworkingIdentityType_UnknownType = 4,

	/* Make sure this enum is stored in an int. */
	k_ESteamNetworkingIdentityType__Force32bit = 0x7fffffff,
};

ice_steam_def_opaque_type(SteamNetworkingIPAddr)
ice_steam_def_opaque_type(SteamNetworkingIdentity)

/* Connection status */

/// High level connection status
enum ESteamNetworkingConnectionState
{

	/*
	Dummy value used to indicate an error condition in the API.
	Specified connection doesn't exist or has already been closed.
	*/
	k_ESteamNetworkingConnectionState_None = 0,

	/*
	We are trying to establish whether peers can talk to each other,
	whether they WANT to talk to each other, perform basic auth,
	and exchange crypt keys.
	
	 - For connections on the "client" side (initiated locally):
	   We're in the process of trying to establish a connection.
	   Depending on the connection type, we might not know who they are.
	   Note that it is not possible to tell if we are waiting on the
	   network to complete handshake packets, or for the application layer
	   to accept the connection.
	
	 - For connections on the "server" side (accepted through listen socket):
	   We have completed some basic handshake and the client has presented
	   some proof of identity.  The connection is ready to be accepted
	   using AcceptConnection().
	
	In either case, any unreliable packets sent now are almost certain
	to be dropped.  Attempts to receive packets are guaranteed to fail.
	You may send messages if the send mode allows for them to be queued.
	but if you close the connection before the connection is actually
	established, any queued messages will be discarded immediately.
	(We will not attempt to flush the queue and confirm delivery to the
	remote host, which ordinarily happens when a connection is closed.)
	*/
	k_ESteamNetworkingConnectionState_Connecting = 1,

	/*
	Some connection types use a back channel or trusted 3rd party
	for earliest communication.  If the server accepts the connection,
	then these connections switch into the rendezvous state.  During this
	state, we still have not yet established an end-to-end route (through
	the relay network), and so if you send any messages unreliable, they
	are going to be discarded.
	*/
	k_ESteamNetworkingConnectionState_FindingRoute = 2,

	/*
	We've received communications from our peer (and we know
	who they are) and are all good.  If you close the connection now,
	we will make our best effort to flush out any reliable sent data that
	has not been acknowledged by the peer.  (But note that this happens
	from within the application process, so unlike a TCP connection, you are
	not totally handing it off to the operating system to deal with it.)
	*/
	k_ESteamNetworkingConnectionState_Connected = 3,

	/*
	Connection has been closed by our peer, but not closed locally.
	The connection still exists from an API perspective.  You must close the
	handle to free up resources.  If there are any messages in the inbound queue,
	you may retrieve them.  Otherwise, nothing may be done with the connection
	except to close it.
	*/
	/* This stats is similar to CLOSE_WAIT in the TCP state machine. */
	k_ESteamNetworkingConnectionState_ClosedByPeer = 4,

	/*
	A disruption in the connection has been detected locally.  (E.g. timeout,
	local internet connection disrupted, etc.)
	*/
	/*
	The connection still exists from an API perspective.  You must close the
	handle to free up resources.
	*/
	/* Attempts to send further messages will fail.  Any remaining received messages in the queue are available. */
	k_ESteamNetworkingConnectionState_ProblemDetectedLocally = 5,

/*
The following values are used internally and will not be returned by any API.
We document them here to provide a little insight into the state machine that is used
under the hood.
*/

	/*
	We've disconnected on our side, and from an API perspective the connection is closed.
	No more data may be sent or received.  All reliable data has been flushed, or else
	we've given up and discarded it.  We do not yet know for sure that the peer knows
	the connection has been closed, however, so we're just hanging around so that if we do
	get a packet from them, we can send them the appropriate packets so that they can
	know why the connection was closed (and not have to rely on a timeout, which makes
	it appear as if something is wrong).
	*/
	k_ESteamNetworkingConnectionState_FinWait = -1,

	/*
	We've disconnected on our side, and from an API perspective the connection is closed.
	No more data may be sent or received.  From a network perspective, however, on the wire,
	we have not yet given any indication to the peer that the connection is closed.
	We are in the process of flushing out the last bit of reliable data.  Once that is done,
	we will inform the peer that the connection has been closed, and transition to the
	FinWait state.
	*/
	/*
	Note that no indication is given to the remote host that we have closed the connection,
	until the data has been flushed.  If the remote host attempts to send us data, we will
	do whatever is necessary to keep the connection alive until it can be closed properly.
	But in fact the data will be discarded, since there is no way for the application to
	read it back.  Typically this is not a problem, as application protocols that utilize
	the lingering functionality are designed for the remote host to wait for the response
	before sending any more data.
	*/
	k_ESteamNetworkingConnectionState_Linger = -2, 

	/* Connection is completely inactive and ready to be destroyed */
	k_ESteamNetworkingConnectionState_Dead = -3,

	k_ESteamNetworkingConnectionState__Force32Bit = 0x7fffffff
};

/* Enumerate various causes of connection termination.  These are designed to work similar to HTTP error codes: the numeric range gives you a rough classification as to the source of the problem. */
enum ESteamNetConnectionEnd
{
	/* Invalid/sentinel value */
	k_ESteamNetConnectionEnd_Invalid = 0,

	/*
	Application codes.  These are the values you will pass to
	ISteamNetworkingSockets::CloseConnection.  You can use these codes if
	you want to plumb through application-specific reason codes.  If you don't
	need this facility, feel free to always pass
	k_ESteamNetConnectionEnd_App_Generic.
	*/
	/*
	The distinction between "normal" and "exceptional" termination is
	one you may use if you find useful, but it's not necessary for you
	to do so.  The only place where we distinguish between normal and
	exceptional is in connection analytics.  If a significant
	proportion of connections terminates in an exceptional manner,
	this can trigger an alert.
	*/

	/*
	1xxx: Application ended the connection in a "usual" manner.
	E.g.: user intentionally disconnected from the server, gameplay ended normally, etc
	*/
	k_ESteamNetConnectionEnd_App_Min = 1000,
	k_ESteamNetConnectionEnd_App_Generic = k_ESteamNetConnectionEnd_App_Min,
	/* Use codes in this range for "normal" disconnection */
	k_ESteamNetConnectionEnd_App_Max = 1999,

	/*
	2xxx: Application ended the connection in some sort of exceptional or unusual manner that might indicate a bug or configuration issue.
	*/
	k_ESteamNetConnectionEnd_AppException_Min = 2000,
	k_ESteamNetConnectionEnd_AppException_Generic = k_ESteamNetConnectionEnd_AppException_Min,
	/* Use codes in this range for "unusual" disconnection */
	k_ESteamNetConnectionEnd_AppException_Max = 2999,

	/*
	System codes.  These will be returned by the system when
	the connection state is k_ESteamNetworkingConnectionState_ClosedByPeer
	or k_ESteamNetworkingConnectionState_ProblemDetectedLocally.  It is
	illegal to pass a code in this range to ISteamNetworkingSockets::CloseConnection
	*/

	/* 3xxx: Connection failed or ended because of problem with the local host or their connection to the Internet. */
	k_ESteamNetConnectionEnd_Local_Min = 3000,

		/* You cannot do what you want to do because you're running in offline mode. */
		k_ESteamNetConnectionEnd_Local_OfflineMode = 3001,

		/*
		We're having trouble contacting many (perhaps all) relays.
		Since it's unlikely that they all went offline at once, the best
		explanation is that we have a problem on our end.  Note that we don't
		bother distinguishing between "many" and "all", because in practice,
		it takes time to detect a connection problem, and by the time
		the connection has timed out, we might not have been able to
		actively probe all of the relay clusters, even if we were able to
		contact them at one time.  So this code just means that:
		*/
		/* * We don't have any recent successful communication with any relay. */
		/* * We have evidence of recent failures to communicate with multiple relays. */
		k_ESteamNetConnectionEnd_Local_ManyRelayConnectivity = 3002,

		/*
		A hosted server is having trouble talking to the relay
		that the client was using, so the problem is most likely
		on our end
		*/
		k_ESteamNetConnectionEnd_Local_HostedServerPrimaryRelay = 3003,

		/*
		We're not able to get the SDR network config.  This is
		*almost* always a local issue, since the network config
		comes from the CDN, which is pretty darn reliable.
		*/
		k_ESteamNetConnectionEnd_Local_NetworkConfig = 3004,

		/* Steam rejected our request because we don't have rights to do this. */
		k_ESteamNetConnectionEnd_Local_Rights = 3005,

		/* ICE P2P rendezvous failed because we were not able to determine our "public" address (e.g. reflexive address via STUN) */

		/*
		If relay fallback is available (it always is on Steam), then
		this is only used internally and will not be returned as a high level failure.
		*/
		k_ESteamNetConnectionEnd_Local_P2P_ICE_NoPublicAddresses = 3006,

	k_ESteamNetConnectionEnd_Local_Max = 3999,

	/*
	4xxx: Connection failed or ended, and it appears that the
	      cause does NOT have to do with the local host or their
	      connection to the Internet.  It could be caused by the
	      remote host, or it could be somewhere in between.
    */
	k_ESteamNetConnectionEnd_Remote_Min = 4000,

		/*
		The connection was lost, and as far as we can tell our connection
		to relevant services (relays) has not been disrupted.  This doesn't
		mean that the problem is "their fault", it just means that it doesn't
		appear that we are having network issues on our end.
		*/
		k_ESteamNetConnectionEnd_Remote_Timeout = 4001,

		/*
		Something was invalid with the cert or crypt handshake
		info you gave me, I don't understand or like your key types,
		etc.
		*/
		k_ESteamNetConnectionEnd_Remote_BadCrypt = 4002,

		/*
		You presented me with a cert that was I was able to parse
		and *technically* we could use encrypted communication.
		But there was a problem that prevents me from checking your identity
		or ensuring that somebody int he middle can't observe our communication.
		E.g.: - the CA key was missing (and I don't accept unsigned certs)
		  - The CA key isn't one that I trust,
		  - The cert doesn't was appropriately restricted by app, user, time, data center, etc.
		  - The cert wasn't issued to you.
		  - etc
		*/
		k_ESteamNetConnectionEnd_Remote_BadCert = 4003,

		/* These will never be returned */
 		/* k_ESteamNetConnectionEnd_Remote_NotLoggedIn_DEPRECATED = 4004, */
		/* k_ESteamNetConnectionEnd_Remote_NotRunningApp_DEPRECATED = 4005, */

		/* Something wrong with the protocol version you are using. (Probably the code you are running is too old.) */
		k_ESteamNetConnectionEnd_Remote_BadProtocolVersion = 4006,

		/*
		NAT punch failed failed because we never received any public
		addresses from the remote host.  (But we did receive some
		signals form them.)
		*/

		/*
		If relay fallback is available (it always is on Steam), then
		this is only used internally and will not be returned as a high
		level failure.
		*/
		k_ESteamNetConnectionEnd_Remote_P2P_ICE_NoPublicAddresses = 4007,

	k_ESteamNetConnectionEnd_Remote_Max = 4999,

	/* 5xxx: Connection failed for some other reason. */
	k_ESteamNetConnectionEnd_Misc_Min = 5000,

		/*
		A failure that isn't necessarily the result of a software bug,
		but that should happen rarely enough that it isn't worth specifically
		writing UI or making a localized message for.
		The debug string should contain further details.
		*/
		k_ESteamNetConnectionEnd_Misc_Generic = 5001,

		/* Generic failure that is most likely a software bug. */
		k_ESteamNetConnectionEnd_Misc_InternalError = 5002,

		/*
		The connection to the remote host timed out, but we
		don't know if the problem is on our end, in the middle,
		or on their end.
		*/
		k_ESteamNetConnectionEnd_Misc_Timeout = 5003,

		/* k_ESteamNetConnectionEnd_Misc_RelayConnectivity_DEPRECATED = 5004, */

		/* There's some trouble talking to Steam. */
		k_ESteamNetConnectionEnd_Misc_SteamConnectivity = 5005,

		/*
		A server in a dedicated hosting situation has no relay sessions
		active with which to talk back to a client.  (It's the client's
		job to open and maintain those sessions.)
		*/
		k_ESteamNetConnectionEnd_Misc_NoRelaySessionsToClient = 5006,

		/*
		While trying to initiate a connection, we never received
		*any* communication from the peer.
		*/
		/* k_ESteamNetConnectionEnd_Misc_ServerNeverReplied = 5007, */

		/* P2P rendezvous failed in a way that we don't have more specific information */
		k_ESteamNetConnectionEnd_Misc_P2P_Rendezvous = 5008,

		/* NAT punch failed, probably due to NAT/firewall configuration. */

		/*
		If relay fallback is available (it always is on Steam), then
		this is only used internally and will not be returned as a high
		level failure.
		*/
		k_ESteamNetConnectionEnd_Misc_P2P_NAT_Firewall = 5009,

		/*
		Our peer replied that it has no record of the connection.
		This should not happen ordinarily, but can happen in a few
		exception cases:

		  - This is an old connection, and the peer has already cleaned
		    up and forgotten about it.  (Perhaps it timed out and they
		    closed it and were not able to communicate this to us.)
		  
		  - A bug or internal protocol error has caused us to try to
		    talk to the peer about the connection before we received
		    confirmation that the peer has accepted the connection.
		  
		  - The peer thinks that we have closed the connection for some
		    reason (perhaps a bug), and believes that is it is
		    acknowledging our closure.
		*/
		k_ESteamNetConnectionEnd_Misc_PeerSentNoConnection = 5010,

	k_ESteamNetConnectionEnd_Misc_Max = 5999,

	k_ESteamNetConnectionEnd__Force32Bit = 0x7fffffff
};

/* Max length, in bytes (including null terminator) of the reason string when a connection is closed. */
const int k_cchSteamNetworkingMaxConnectionCloseReason = 128;

/* Max length, in bytes (include null terminator) of debug description of a connection. */
const int k_cchSteamNetworkingMaxConnectionDescription = 128;

/* #CHECKPOINT */


ice_steam_def_opaque_type(ISteamNetworkingMessages)

#define STEAMNETWORKINGMESSAGES_INTERFACE_VERSION "SteamNetworkingMessages002"

ice_steam_def_func(ISteamNetworkingMessages*, SteamNetworkingMessages, ())
ice_steam_def_func(ISteamNetworkingMessages*, SteamGameServerNetworkingMessages, ())

ice_steam_def_opaque_type(SteamNetAuthenticationStatus_t)
ice_steam_def_opaque_type(ISteamNetworkingSockets)

#define STEAMNETWORKINGSOCKETS_INTERFACE_VERSION "SteamNetworkingSockets009"

ice_steam_def_func(ISteamNetworkingSockets*, SteamNetworkingSockets, ())
ice_steam_def_func(ISteamNetworkingSockets*, SteamGameServerNetworkingSockets, ())

ice_steam_def_opaque_type(SteamDatagramRelayAuthTicket)
ice_steam_def_opaque_type(SteamRelayNetworkStatus_t)
ice_steam_def_opaque_type(ISteamNetworkingUtils)

#define STEAMNETWORKINGUTILS_INTERFACE_VERSION "SteamNetworkingUtils003"

ice_steam_def_func(ISteamNetworkingUtils*, SteamNetworkingUtils, ())

/* list of possible return values from the ISteamGameCoordinator API */
enum EGCResults
{
	k_EGCResultOK = 0,
	k_EGCResultNoMessage = 1,			/* There is no message in the queue */
	k_EGCResultBufferTooSmall = 2,		/* The buffer is too small for the requested message */
	k_EGCResultNotLoggedOn = 3,			/* The client is not logged onto Steam */
	k_EGCResultInvalidMessage = 4,		/* Something was wrong with the message being sent with SendMessage */
};

ice_steam_def_opaque_type(ISteamGameCoordinator)

#define STEAMGAMECOORDINATOR_INTERFACE_VERSION "SteamGameCoordinator001"

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
	PlayStation 3 initialization parameters
	The following structure must be passed to when loading steam_api_ps3.prx
----------------------------------------------------------------------------------------------------------------------------------------------------------
*/
#define STEAM_PS3_PATH_MAX 1055
#define STEAM_PS3_SERVICE_ID_MAX 32
#define STEAM_PS3_COMMUNICATION_ID_MAX 10
#define STEAM_PS3_COMMUNICATION_SIG_MAX 160
#define STEAM_PS3_LANGUAGE_MAX 64
#define STEAM_PS3_REGION_CODE_MAX 16
#define STEAM_PS3_CURRENT_PARAMS_VER 2

struct SteamPS3Params_t
{
	uint32 m_unVersion;										/* set to STEAM_PS3_CURRENT_PARAMS_VER */
	
	void *pReserved;
	uint32 m_nAppId;										/* set to your game's appid */

	char m_rgchInstallationPath[ STEAM_PS3_PATH_MAX ];		/* directory containing latest steam prx's and sdata. Can be read only (BDVD) */
	char m_rgchSystemCache[ STEAM_PS3_PATH_MAX ];			/* temp working cache, not persistent */
	char m_rgchGameData[ STEAM_PS3_PATH_MAX ];				/* persistent game data path for storing user data */
	char m_rgchNpServiceID[ STEAM_PS3_SERVICE_ID_MAX ];
	char m_rgchNpCommunicationID[ STEAM_PS3_COMMUNICATION_ID_MAX ];
	char m_rgchNpCommunicationSig[ STEAM_PS3_COMMUNICATION_SIG_MAX ];

	/* Language should be one of the following. must be zero terminated */
	/*
	danish
	dutch
	english
	finnish
	french
	german
	italian
	korean
	norwegian
	polish
	portuguese
	russian
	schinese
	spanish
	swedish
	tchinese
	*/
	char m_rgchSteamLanguage[ STEAM_PS3_LANGUAGE_MAX ];

	/* region codes are "SCEA", "SCEE", "SCEJ". must be zero terminated */
	char m_rgchRegionCode[ STEAM_PS3_REGION_CODE_MAX ];

	/*
	Should be SYS_TTYP3 through SYS_TTYP10, if it's 0 then Steam won't spawn a 
	thread to read console input at all.  Using this let's you use Steam console commands
	like: profile_on, profile_off, profile_dump, mem_stats, mem_validate.
	*/
	unsigned int m_cSteamInputTTY;

	struct Ps3netInit_t
	{
		bool m_bNeedInit;
		void *m_pMemory;
		int m_nMemorySize;
		int m_flags;
	} m_sysNetInitInfo;

	struct Ps3jpgInit_t
	{
		bool m_bNeedInit;
	} m_sysJpgInitInfo;

	struct Ps3pngInit_t
	{
		bool m_bNeedInit;
	} m_sysPngInitInfo;
	
	struct Ps3sysutilUserInfo_t
	{
		bool m_bNeedInit;
	} m_sysSysUtilUserInfo;

	bool m_bIncludeNewsPage;
};


/*
----------------------------------------------------------------------------------------------------------------------------------------------------------//
PlayStation 3 memory structure
----------------------------------------------------------------------------------------------------------------------------------------------------------//
*/
#define STEAMPS3_MALLOC_INUSE 0x53D04A51
#define STEAMPS3_MALLOC_SYSTEM 0x0D102C48
#define STEAMPS3_MALLOC_OK 0xFFD04A51
struct SteamPS3Memory_t
{
	bool m_bSingleAllocation;		/* If true, Steam will request one 6MB allocation and use the returned memory for all future allocations */
									/* If false, Steam will make call malloc for each allocation */

	/* required function pointers */
	void* (*m_pfMalloc)(size_t);
	void* (*m_pfRealloc)(void *, size_t);
	void (*m_pfFree)(void *);
	size_t (*m_pUsable_size)(void*);
};

/*
-----------------------------------------------------------------------------
Purpose: Enum for supported gradient directions
-----------------------------------------------------------------------------
*/
enum EOverlayGradientDirection
{
	k_EOverlayGradientHorizontal = 1,
	k_EOverlayGradientVertical = 2,
	k_EOverlayGradientNone = 3,
};

/* Helpers for fetching individual color components from ARGB packed DWORD colors Steam PS3 overlay renderer uses. */
#define STEAM_COLOR_RED( color ) \
	(int)(((color)>>16)&0xff)

#define STEAM_COLOR_GREEN( color ) \
	(int)(((color)>>8)&0xff)

#define STEAM_COLOR_BLUE( color ) \
	(int)((color)&0xff)

#define STEAM_COLOR_ALPHA( color ) \
	(int)(((color)>>24)&0xff)

ice_steam_def_opaque_type(ISteamPS3OverlayRenderHost)
ice_steam_def_opaque_type(ISteamPS3OverlayRender)

static const int k_nSteamEncryptedAppTicketSymmetricKeyLen = 32;				

ice_steam_def_func(bool, SteamEncryptedAppTicket_BDecryptTicket, (const uint8 *rgubTicketEncrypted, uint32 cubTicketEncrypted, uint8 *rgubTicketDecrypted, uint32 *pcubTicketDecrypted, const uint8 rgubKey[k_nSteamEncryptedAppTicketSymmetricKeyLen], int cubKey))
ice_steam_def_func(bool, SteamEncryptedAppTicket_BIsTicketForApp, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, AppId_t nAppID))
ice_steam_def_func(RTime32, SteamEncryptedAppTicket_GetTicketIssueTime, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted))
ice_steam_def_func(void, SteamEncryptedAppTicket_GetTicketSteamID, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, CSteamID *psteamID))
ice_steam_def_func(AppId_t, SteamEncryptedAppTicket_GetTicketAppID, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted))
ice_steam_def_func(bool, SteamEncryptedAppTicket_BUserOwnsAppInTicket, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, AppId_t nAppID))
ice_steam_def_func(bool, SteamEncryptedAppTicket_BUserIsVacBanned, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted))
ice_steam_def_func(bool, SteamEncryptedAppTicket_BGetAppDefinedValue, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, uint32 *pValue))
ice_steam_def_func(const uint8*, SteamEncryptedAppTicket_GetUserVariableData, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, uint32 *pcubUserData))
ice_steam_def_func(bool, SteamEncryptedAppTicket_BIsTicketSigned, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted, const uint8 *pubRSAKey, uint32 cubRSAKey))
ice_steam_def_func(bool, SteamEncryptedAppTicket_BIsLicenseBorrowed, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted))
ice_steam_def_func(bool, SteamEncryptedAppTicket_BIsLicenseTemporary, (uint8 *rgubTicketDecrypted, uint32 cubTicketDecrypted))

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
	Steam API setup & shutdown

	These functions manage loading, initializing and shutdown of the steamclient.dll

----------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* SteamAPI_Init must be called before using any other API functions. */
/* If it fails, an error message will be output to the debugger (or stderr) with further information. */
ice_steam_def_func(bool, SteamAPI_Init, ())

/* SteamAPI_Shutdown should be called during process shutdown if possible. */
ice_steam_def_func(void, SteamAPI_Shutdown, ())

/* SteamAPI_RestartAppIfNecessary ensures that your executable was launched through Steam. */
/*
  Returns true if the current process should terminate. Steam is now re-launching your application.

  Returns false if no action needs to be taken. This means that your executable was started through
  the Steam client, or a steam_appid.txt file is present in your game's directory (for development).
  Your current process should continue if false is returned.

   NOTE: If you use the Steam DRM wrapper on your primary executable file, this check is unnecessary
   since the DRM wrapper will ensure that your application was launched properly through Steam.
*/
ice_steam_def_func(bool, SteamAPI_RestartAppIfNecessary, (uint32 unOwnAppID))

/*
Many Steam API functions allocate a small amount of thread-local memory for parameter storage.
SteamAPI_ReleaseCurrentThreadMemory() will free API memory associated with the calling thread.
This function is also called automatically by SteamAPI_RunCallbacks(), so a single-threaded
program never needs to explicitly call this function.
*/
ice_steam_def_func(void, SteamAPI_ReleaseCurrentThreadMemory, ())

/* crash dump recording functions */
ice_steam_def_func(void, SteamAPI_WriteMiniDump, (uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID))
ice_steam_def_func(void, SteamAPI_SetMiniDumpComment, (const char* pchMsg))

/*
----------------------------------------------------------------------------------------------------------------------------------------------------------
	steamclient.dll private wrapper functions

	The following functions are part of abstracting API access to the steamclient.dll, but should only be used in very specific cases
----------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/* SteamAPI_IsSteamRunning() returns true if Steam is currently running */
ice_steam_def_func(bool, SteamAPI_IsSteamRunning, ())

/*
returns the filename path of the current running Steam process, used if you need to load an explicit steam dll by name.
DEPRECATED - implementation is Windows only, and the path returned is a UTF-8 string which must be converted to UTF-16 for use with Win32 APIs
*/
ice_steam_def_func(const char*, SteamAPI_GetSteamInstallPath, ())

/* sets whether or not Steam_RunCallbacks() should do a try {} catch (...) {} around calls to issuing callbacks */
/* This is ignored if you are using the manual callback dispatch method */
ice_steam_def_func(void, SteamAPI_SetTryCatchCallbacks, (bool bTryCatchCallbacks))

/*#if defined( VERSION_SAFE_STEAM_API_INTERFACES )*/
/* exists only for backwards compat with code written against older SDKs */
ice_steam_def_func(bool, SteamAPI_InitSafe, ())
/*#endif*/

/*#if defined(USE_BREAKPAD_HANDLER) || defined(STEAM_API_EXPORTS)*/
/*
this should be called before the game initialized the steam APIs

pchDate should be of the format "Mmm dd yyyy" (such as from the __ DATE __ macro )
pchTime should be of the format "hh:mm:ss" (such as from the __ TIME __ macro )
bFullMemoryDumps (Win32 only) -- writes out a uuid-full.dmp in the client/dumps folder
pvContext-- can be NULL, will be the void * context passed into m_pfnPreMinidumpCallback
PFNPreMinidumpCallback m_pfnPreMinidumpCallback   -- optional callback which occurs just before a .dmp file is written during a crash.  Applications can hook this to allow adding additional information into the .dmp comment stream.
*/

ice_steam_def_func(void, SteamAPI_UseBreakpadCrashHandler, (char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback))
ice_steam_def_func(void, SteamAPI_SetBreakpadAppID, (uint32 unAppID))

/*#endif*/

/* Inform the API that you wish to use manual event dispatch.  This must be called after SteamAPI_Init, but before you use any of the other manual dispatch functions below. */
ice_steam_def_func(void, SteamAPI_ManualDispatch_Init, ())

/* Perform certain periodic actions that need to be performed. */
ice_steam_def_func(void, SteamAPI_ManualDispatch_RunFrame, (HSteamPipe hSteamPipe))

/*
Fetch the next pending callback on the given pipe, if any.  If a callback is available, true is returned
and the structure is populated.  In this case, you MUST call SteamAPI_ManualDispatch_FreeLastCallback
(after dispatching the callback) before calling SteamAPI_ManualDispatch_GetNextCallback again.
*/
ice_steam_def_func(bool, SteamAPI_ManualDispatch_GetNextCallback, (HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg))

/* You must call this after dispatching the callback, if SteamAPI_ManualDispatch_GetNextCallback returns true. */
ice_steam_def_func(void, SteamAPI_ManualDispatch_FreeLastCallback, (HSteamPipe hSteamPipe))

/* Return the call result for the specified call on the specified pipe.  You really should only call this in a handler for SteamAPICallCompleted_t callback. */
ice_steam_def_func(bool, SteamAPI_ManualDispatch_GetAPICallResult, (HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed))

#define STEAMGAMESERVER_INTERFACE_VERSION "SteamGameServer014"

ice_steam_def_func(ISteamGameServer*, SteamGameServer, ())
/*STEAM_DEFINE_GAMESERVER_INTERFACE_ACCESSOR( ISteamGameServer *, SteamGameServer, STEAMGAMESERVER_INTERFACE_VERSION );*/

#define STEAMGAMESERVERSTATS_INTERFACE_VERSION "SteamGameServerStats001"

ice_steam_def_func(ISteamGameServerStats*, SteamGameServerStats, ())
/*STEAM_DEFINE_GAMESERVER_INTERFACE_ACCESSOR( ISteamGameServerStats *, SteamGameServerStats, STEAMGAMESERVERSTATS_INTERFACE_VERSION );*/

typedef uint64 uint64_steamid; /* Used when passing or returning CSteamID */
typedef uint64 uint64_gameid;  /* Used when passing or return CGameID */

ice_steam_def_func(HSteamPipe, SteamAPI_ISteamClient_CreateSteamPipe, ( ISteamClient* self ))
ice_steam_def_func(bool, SteamAPI_ISteamClient_BReleaseSteamPipe, ( ISteamClient* self, HSteamPipe hSteamPipe ))
ice_steam_def_func(HSteamUser, SteamAPI_ISteamClient_ConnectToGlobalUser, ( ISteamClient* self, HSteamPipe hSteamPipe ))
ice_steam_def_func(HSteamUser, SteamAPI_ISteamClient_CreateLocalUser, ( ISteamClient* self, HSteamPipe* phSteamPipe, EAccountType eAccountType ))
ice_steam_def_func(void, SteamAPI_ISteamClient_ReleaseUser, ( ISteamClient* self, HSteamPipe hSteamPipe, HSteamUser hUser ))
ice_steam_def_func(ISteamUser*, SteamAPI_ISteamClient_GetISteamUser, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamGameServer*, SteamAPI_ISteamClient_GetISteamGameServer, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(void, SteamAPI_ISteamClient_SetLocalIPBinding, ( ISteamClient* self, const SteamIPAddress_t & unIP, uint16 usPort ))
ice_steam_def_func(ISteamFriends*, SteamAPI_ISteamClient_GetISteamFriends, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamUtils*, SteamAPI_ISteamClient_GetISteamUtils, ( ISteamClient* self, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamMatchmaking*, SteamAPI_ISteamClient_GetISteamMatchmaking, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamMatchmakingServers*, SteamAPI_ISteamClient_GetISteamMatchmakingServers, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(void*, SteamAPI_ISteamClient_GetISteamGenericInterface, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamUserStats*, SteamAPI_ISteamClient_GetISteamUserStats, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamGameServerStats*, SteamAPI_ISteamClient_GetISteamGameServerStats, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamApps*, SteamAPI_ISteamClient_GetISteamApps, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamNetworking*, SteamAPI_ISteamClient_GetISteamNetworking, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamRemoteStorage*, SteamAPI_ISteamClient_GetISteamRemoteStorage, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamScreenshots*, SteamAPI_ISteamClient_GetISteamScreenshots, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamGameSearch*, SteamAPI_ISteamClient_GetISteamGameSearch, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(uint32, SteamAPI_ISteamClient_GetIPCCallCount, ( ISteamClient* self ))
ice_steam_def_func(void, SteamAPI_ISteamClient_SetWarningMessageHook, ( ISteamClient* self, SteamAPIWarningMessageHook_t pFunction ))
ice_steam_def_func(bool, SteamAPI_ISteamClient_BShutdownIfAllPipesClosed, ( ISteamClient* self ))
ice_steam_def_func(ISteamHTTP*, SteamAPI_ISteamClient_GetISteamHTTP, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamController*, SteamAPI_ISteamClient_GetISteamController, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamUGC*, SteamAPI_ISteamClient_GetISteamUGC, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamAppList*, SteamAPI_ISteamClient_GetISteamAppList, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamMusic*, SteamAPI_ISteamClient_GetISteamMusic, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamMusicRemote*, SteamAPI_ISteamClient_GetISteamMusicRemote, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamHTMLSurface*, SteamAPI_ISteamClient_GetISteamHTMLSurface, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamInventory*, SteamAPI_ISteamClient_GetISteamInventory, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamVideo*, SteamAPI_ISteamClient_GetISteamVideo, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamParentalSettings*, SteamAPI_ISteamClient_GetISteamParentalSettings, ( ISteamClient* self, HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamInput*, SteamAPI_ISteamClient_GetISteamInput, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamParties*, SteamAPI_ISteamClient_GetISteamParties, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamRemotePlay*, SteamAPI_ISteamClient_GetISteamRemotePlay, ( ISteamClient* self, HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char* pchVersion ))
ice_steam_def_func(ISteamUser*, SteamAPI_SteamUser_v021, ())
ice_steam_def_func(HSteamUser, SteamAPI_ISteamUser_GetHSteamUser, ( ISteamUser* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUser_BLoggedOn, ( ISteamUser* self ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamUser_GetSteamID, ( ISteamUser* self ))
ice_steam_def_func(int, SteamAPI_ISteamUser_InitiateGameConnection_DEPRECATED, ( ISteamUser* self, void* pAuthBlob, int cbMaxAuthBlob, uint64_steamid steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure ))
ice_steam_def_func(void, SteamAPI_ISteamUser_TerminateGameConnection_DEPRECATED, ( ISteamUser* self, uint32 unIPServer, uint16 usPortServer ))
ice_steam_def_func(void, SteamAPI_ISteamUser_TrackAppUsageEvent, ( ISteamUser* self, uint64_gameid gameID, int eAppUsageEvent, const char* pchExtraInfo ))
ice_steam_def_func(bool, SteamAPI_ISteamUser_GetUserDataFolder, ( ISteamUser* self, char* pchBuffer, int cubBuffer ))
ice_steam_def_func(void, SteamAPI_ISteamUser_StartVoiceRecording, ( ISteamUser* self ))
ice_steam_def_func(void, SteamAPI_ISteamUser_StopVoiceRecording, ( ISteamUser* self ))
ice_steam_def_func(EVoiceResult, SteamAPI_ISteamUser_GetAvailableVoice, ( ISteamUser* self, uint32* pcbCompressed, uint32* pcbUncompressed_Deprecated, uint32 nUncompressedVoiceDesiredSampleRate_Deprecated ))
ice_steam_def_func(EVoiceResult, SteamAPI_ISteamUser_GetVoice, ( ISteamUser* self, bool bWantCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, bool bWantUncompressed_Deprecated, void* pUncompressedDestBuffer_Deprecated, uint32 cbUncompressedDestBufferSize_Deprecated, uint32* nUncompressBytesWritten_Deprecated, uint32 nUncompressedVoiceDesiredSampleRate_Deprecated ))
ice_steam_def_func(EVoiceResult, SteamAPI_ISteamUser_DecompressVoice, ( ISteamUser* self, const void* pCompressed, uint32 cbCompressed, void* pDestBuffer, uint32 cbDestBufferSize, uint32* nBytesWritten, uint32 nDesiredSampleRate ))
ice_steam_def_func(uint32, SteamAPI_ISteamUser_GetVoiceOptimalSampleRate, ( ISteamUser* self ))
ice_steam_def_func(HAuthTicket, SteamAPI_ISteamUser_GetAuthSessionTicket, ( ISteamUser* self, void* pTicket, int cbMaxTicket, uint32* pcbTicket ))
ice_steam_def_func(EBeginAuthSessionResult, SteamAPI_ISteamUser_BeginAuthSession, ( ISteamUser* self, const void* pAuthTicket, int cbAuthTicket, uint64_steamid steamID ))
ice_steam_def_func(void, SteamAPI_ISteamUser_EndAuthSession, ( ISteamUser* self, uint64_steamid steamID ))
ice_steam_def_func(void, SteamAPI_ISteamUser_CancelAuthTicket, ( ISteamUser* self, HAuthTicket hAuthTicket ))
ice_steam_def_func(EUserHasLicenseForAppResult, SteamAPI_ISteamUser_UserHasLicenseForApp, ( ISteamUser* self, uint64_steamid steamID, AppId_t appID ))
ice_steam_def_func(bool, SteamAPI_ISteamUser_BIsBehindNAT, ( ISteamUser* self ))
ice_steam_def_func(void, SteamAPI_ISteamUser_AdvertiseGame, ( ISteamUser* self, uint64_steamid steamIDGameServer, uint32 unIPServer, uint16 usPortServer ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUser_RequestEncryptedAppTicket, ( ISteamUser* self, void* pDataToInclude, int cbDataToInclude ))
ice_steam_def_func(bool, SteamAPI_ISteamUser_GetEncryptedAppTicket, ( ISteamUser* self, void* pTicket, int cbMaxTicket, uint32* pcbTicket ))
ice_steam_def_func(int, SteamAPI_ISteamUser_GetGameBadgeLevel, ( ISteamUser* self, int nSeries, bool bFoil ))
ice_steam_def_func(int, SteamAPI_ISteamUser_GetPlayerSteamLevel, ( ISteamUser* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUser_RequestStoreAuthURL, ( ISteamUser* self, const char* pchRedirectURL ))
ice_steam_def_func(bool, SteamAPI_ISteamUser_BIsPhoneVerified, ( ISteamUser* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUser_BIsTwoFactorEnabled, ( ISteamUser* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUser_BIsPhoneIdentifying, ( ISteamUser* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUser_BIsPhoneRequiringVerification, ( ISteamUser* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUser_GetMarketEligibility, ( ISteamUser* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUser_GetDurationControl, ( ISteamUser* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUser_BSetDurationControlOnlineState, ( ISteamUser* self, EDurationControlOnlineState eNewState ))
ice_steam_def_func(ISteamFriends*, SteamAPI_SteamFriends_v017, ())
ice_steam_def_func(const char *, SteamAPI_ISteamFriends_GetPersonaName, ( ISteamFriends* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamFriends_SetPersonaName, ( ISteamFriends* self, const char* pchPersonaName ))
ice_steam_def_func(EPersonaState, SteamAPI_ISteamFriends_GetPersonaState, ( ISteamFriends* self ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetFriendCount, ( ISteamFriends* self, int iFriendFlags ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamFriends_GetFriendByIndex, ( ISteamFriends* self, int iFriend, int iFriendFlags ))
ice_steam_def_func(EFriendRelationship, SteamAPI_ISteamFriends_GetFriendRelationship, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(EPersonaState, SteamAPI_ISteamFriends_GetFriendPersonaState, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(const char *, SteamAPI_ISteamFriends_GetFriendPersonaName, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_GetFriendGamePlayed, ( ISteamFriends* self, uint64_steamid steamIDFriend, FriendGameInfo_t* pFriendGameInfo ))
ice_steam_def_func(const char *, SteamAPI_ISteamFriends_GetFriendPersonaNameHistory, ( ISteamFriends* self, uint64_steamid steamIDFriend, int iPersonaName ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetFriendSteamLevel, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(const char *, SteamAPI_ISteamFriends_GetPlayerNickname, ( ISteamFriends* self, uint64_steamid steamIDPlayer ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetFriendsGroupCount, ( ISteamFriends* self ))
ice_steam_def_func(FriendsGroupID_t, SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex, ( ISteamFriends* self, int iFG ))
ice_steam_def_func(const char *, SteamAPI_ISteamFriends_GetFriendsGroupName, ( ISteamFriends* self, FriendsGroupID_t friendsGroupID ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetFriendsGroupMembersCount, ( ISteamFriends* self, FriendsGroupID_t friendsGroupID ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_GetFriendsGroupMembersList, ( ISteamFriends* self, FriendsGroupID_t friendsGroupID, CSteamID* pOutSteamIDMembers, int nMembersCount ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_HasFriend, ( ISteamFriends* self, uint64_steamid steamIDFriend, int iFriendFlags ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetClanCount, ( ISteamFriends* self ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamFriends_GetClanByIndex, ( ISteamFriends* self, int iClan ))
ice_steam_def_func(const char *, SteamAPI_ISteamFriends_GetClanName, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(const char *, SteamAPI_ISteamFriends_GetClanTag, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_GetClanActivityCounts, ( ISteamFriends* self, uint64_steamid steamIDClan, int* pnOnline, int* pnInGame, int* pnChatting ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamFriends_DownloadClanActivityCounts, ( ISteamFriends* self, CSteamID* psteamIDClans, int cClansToRequest ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetFriendCountFromSource, ( ISteamFriends* self, uint64_steamid steamIDSource ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamFriends_GetFriendFromSourceByIndex, ( ISteamFriends* self, uint64_steamid steamIDSource, int iFriend ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_IsUserInSource, ( ISteamFriends* self, uint64_steamid steamIDUser, uint64_steamid steamIDSource ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_SetInGameVoiceSpeaking, ( ISteamFriends* self, uint64_steamid steamIDUser, bool bSpeaking ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_ActivateGameOverlay, ( ISteamFriends* self, const char* pchDialog ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_ActivateGameOverlayToUser, ( ISteamFriends* self, const char* pchDialog, uint64_steamid steamID ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_ActivateGameOverlayToWebPage, ( ISteamFriends* self, const char* pchURL, EActivateGameOverlayToWebPageMode eMode ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_ActivateGameOverlayToStore, ( ISteamFriends* self, AppId_t nAppID, EOverlayToStoreFlag eFlag ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_SetPlayedWith, ( ISteamFriends* self, uint64_steamid steamIDUserPlayedWith ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialog, ( ISteamFriends* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetSmallFriendAvatar, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetMediumFriendAvatar, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetLargeFriendAvatar, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_RequestUserInformation, ( ISteamFriends* self, uint64_steamid steamIDUser, bool bRequireNameOnly ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamFriends_RequestClanOfficerList, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamFriends_GetClanOwner, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetClanOfficerCount, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamFriends_GetClanOfficerByIndex, ( ISteamFriends* self, uint64_steamid steamIDClan, int iOfficer ))
ice_steam_def_func(uint32, SteamAPI_ISteamFriends_GetUserRestrictions, ( ISteamFriends* self ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_SetRichPresence, ( ISteamFriends* self, const char* pchKey, const char* pchValue ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_ClearRichPresence, ( ISteamFriends* self ))
ice_steam_def_func(const char *, SteamAPI_ISteamFriends_GetFriendRichPresence, ( ISteamFriends* self, uint64_steamid steamIDFriend, const char* pchKey ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(const char *, SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex, ( ISteamFriends* self, uint64_steamid steamIDFriend, int iKey ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_RequestFriendRichPresence, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_InviteUserToGame, ( ISteamFriends* self, uint64_steamid steamIDFriend, const char* pchConnectString ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetCoplayFriendCount, ( ISteamFriends* self ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamFriends_GetCoplayFriend, ( ISteamFriends* self, int iCoplayFriend ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetFriendCoplayTime, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(AppId_t, SteamAPI_ISteamFriends_GetFriendCoplayGame, ( ISteamFriends* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamFriends_JoinClanChatRoom, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_LeaveClanChatRoom, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetClanChatMemberCount, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamFriends_GetChatMemberByIndex, ( ISteamFriends* self, uint64_steamid steamIDClan, int iUser ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_SendClanChatMessage, ( ISteamFriends* self, uint64_steamid steamIDClanChat, const char* pchText ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetClanChatMessage, ( ISteamFriends* self, uint64_steamid steamIDClanChat, int iMessage, void* prgchText, int cchTextMax, EChatEntryType* peChatEntryType, CSteamID* psteamidChatter ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_IsClanChatAdmin, ( ISteamFriends* self, uint64_steamid steamIDClanChat, uint64_steamid steamIDUser ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam, ( ISteamFriends* self, uint64_steamid steamIDClanChat ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_OpenClanChatWindowInSteam, ( ISteamFriends* self, uint64_steamid steamIDClanChat ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_CloseClanChatWindowInSteam, ( ISteamFriends* self, uint64_steamid steamIDClanChat ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_SetListenForFriendsMessages, ( ISteamFriends* self, bool bInterceptEnabled ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_ReplyToFriendMessage, ( ISteamFriends* self, uint64_steamid steamIDFriend, const char* pchMsgToSend ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetFriendMessage, ( ISteamFriends* self, uint64_steamid steamIDFriend, int iMessageID, void* pvData, int cubData, EChatEntryType* peChatEntryType ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamFriends_GetFollowerCount, ( ISteamFriends* self, uint64_steamid steamID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamFriends_IsFollowing, ( ISteamFriends* self, uint64_steamid steamID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamFriends_EnumerateFollowingList, ( ISteamFriends* self, uint32 unStartIndex ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_IsClanPublic, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_IsClanOfficialGameGroup, ( ISteamFriends* self, uint64_steamid steamIDClan ))
ice_steam_def_func(int, SteamAPI_ISteamFriends_GetNumChatsWithUnreadPriorityMessages, ( ISteamFriends* self ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_ActivateGameOverlayRemotePlayTogetherInviteDialog, ( ISteamFriends* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(bool, SteamAPI_ISteamFriends_RegisterProtocolInOverlayBrowser, ( ISteamFriends* self, const char* pchProtocol ))
ice_steam_def_func(void, SteamAPI_ISteamFriends_ActivateGameOverlayInviteDialogConnectString, ( ISteamFriends* self, const char* pchConnectString ))
ice_steam_def_func(ISteamUtils*, SteamAPI_SteamUtils_v010, ())
ice_steam_def_func(ISteamUtils*, SteamAPI_SteamGameServerUtils_v010, ())
ice_steam_def_func(uint32, SteamAPI_ISteamUtils_GetSecondsSinceAppActive, ( ISteamUtils* self ))
ice_steam_def_func(uint32, SteamAPI_ISteamUtils_GetSecondsSinceComputerActive, ( ISteamUtils* self ))
ice_steam_def_func(EUniverse, SteamAPI_ISteamUtils_GetConnectedUniverse, ( ISteamUtils* self ))
ice_steam_def_func(uint32, SteamAPI_ISteamUtils_GetServerRealTime, ( ISteamUtils* self ))
ice_steam_def_func(const char *, SteamAPI_ISteamUtils_GetIPCountry, ( ISteamUtils* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_GetImageSize, ( ISteamUtils* self, int iImage, uint32* pnWidth, uint32* pnHeight ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_GetImageRGBA, ( ISteamUtils* self, int iImage, uint8* pubDest, int nDestBufferSize ))
ice_steam_def_func(uint8, SteamAPI_ISteamUtils_GetCurrentBatteryPower, ( ISteamUtils* self ))
ice_steam_def_func(uint32, SteamAPI_ISteamUtils_GetAppID, ( ISteamUtils* self ))
ice_steam_def_func(void, SteamAPI_ISteamUtils_SetOverlayNotificationPosition, ( ISteamUtils* self, ENotificationPosition eNotificationPosition ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_IsAPICallCompleted, ( ISteamUtils* self, SteamAPICall_t hSteamAPICall, bool* pbFailed ))
ice_steam_def_func(ESteamAPICallFailure, SteamAPI_ISteamUtils_GetAPICallFailureReason, ( ISteamUtils* self, SteamAPICall_t hSteamAPICall ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_GetAPICallResult, ( ISteamUtils* self, SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed ))
ice_steam_def_func(uint32, SteamAPI_ISteamUtils_GetIPCCallCount, ( ISteamUtils* self ))
ice_steam_def_func(void, SteamAPI_ISteamUtils_SetWarningMessageHook, ( ISteamUtils* self, SteamAPIWarningMessageHook_t pFunction ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_IsOverlayEnabled, ( ISteamUtils* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_BOverlayNeedsPresent, ( ISteamUtils* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUtils_CheckFileSignature, ( ISteamUtils* self, const char* szFileName ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_ShowGamepadTextInput, ( ISteamUtils* self, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32 unCharMax, const char* pchExistingText ))
ice_steam_def_func(uint32, SteamAPI_ISteamUtils_GetEnteredGamepadTextLength, ( ISteamUtils* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_GetEnteredGamepadTextInput, ( ISteamUtils* self, char* pchText, uint32 cchText ))
ice_steam_def_func(const char *, SteamAPI_ISteamUtils_GetSteamUILanguage, ( ISteamUtils* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_IsSteamRunningInVR, ( ISteamUtils* self ))
ice_steam_def_func(void, SteamAPI_ISteamUtils_SetOverlayNotificationInset, ( ISteamUtils* self, int nHorizontalInset, int nVerticalInset ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_IsSteamInBigPictureMode, ( ISteamUtils* self ))
ice_steam_def_func(void, SteamAPI_ISteamUtils_StartVRDashboard, ( ISteamUtils* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled, ( ISteamUtils* self ))
ice_steam_def_func(void, SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled, ( ISteamUtils* self, bool bEnabled ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_IsSteamChinaLauncher, ( ISteamUtils* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_InitFilterText, ( ISteamUtils* self, uint32 unFilterOptions ))
ice_steam_def_func(int, SteamAPI_ISteamUtils_FilterText, ( ISteamUtils* self, ETextFilteringContext eContext, uint64_steamid sourceSteamID, const char* pchInputMessage, char* pchOutFilteredText, uint32 nByteSizeOutFilteredText ))
ice_steam_def_func(ESteamIPv6ConnectivityState, SteamAPI_ISteamUtils_GetIPv6ConnectivityState, ( ISteamUtils* self, ESteamIPv6ConnectivityProtocol eProtocol ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_IsSteamRunningOnSteamDeck, ( ISteamUtils* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUtils_ShowModalGamepadTextInput, ( ISteamUtils* self, EGamepadTextInputLineMode eLineInputMode ))
ice_steam_def_func(void, SteamAPI_ISteamUtils_SetGameLauncherMode, ( ISteamUtils* self, bool bLauncherMode ))
ice_steam_def_func(ISteamMatchmaking*, SteamAPI_SteamMatchmaking_v009, ())
ice_steam_def_func(int, SteamAPI_ISteamMatchmaking_GetFavoriteGameCount, ( ISteamMatchmaking* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_GetFavoriteGame, ( ISteamMatchmaking* self, int iGame, AppId_t* pnAppID, uint32* pnIP, uint16* pnConnPort, uint16* pnQueryPort, uint32* punFlags, uint32* pRTime32LastPlayedOnServer ))
ice_steam_def_func(int, SteamAPI_ISteamMatchmaking_AddFavoriteGame, ( ISteamMatchmaking* self, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_RemoveFavoriteGame, ( ISteamMatchmaking* self, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamMatchmaking_RequestLobbyList, ( ISteamMatchmaking* self ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter, ( ISteamMatchmaking* self, const char* pchKeyToMatch, const char* pchValueToMatch, ELobbyComparison eComparisonType ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter, ( ISteamMatchmaking* self, const char* pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter, ( ISteamMatchmaking* self, const char* pchKeyToMatch, int nValueToBeCloseTo ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable, ( ISteamMatchmaking* self, int nSlotsAvailable ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter, ( ISteamMatchmaking* self, ELobbyDistanceFilter eLobbyDistanceFilter ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter, ( ISteamMatchmaking* self, int cMaxResults ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamMatchmaking_GetLobbyByIndex, ( ISteamMatchmaking* self, int iLobby ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamMatchmaking_CreateLobby, ( ISteamMatchmaking* self, ELobbyType eLobbyType, int cMaxMembers ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamMatchmaking_JoinLobby, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_LeaveLobby, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_InviteUserToLobby, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint64_steamid steamIDInvitee ))
ice_steam_def_func(int, SteamAPI_ISteamMatchmaking_GetNumLobbyMembers, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, int iMember ))
ice_steam_def_func(const char *, SteamAPI_ISteamMatchmaking_GetLobbyData, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, const char* pchKey ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_SetLobbyData, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, const char* pchKey, const char* pchValue ))
ice_steam_def_func(int, SteamAPI_ISteamMatchmaking_GetLobbyDataCount, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, int iLobbyData, char* pchKey, int cchKeyBufferSize, char* pchValue, int cchValueBufferSize ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_DeleteLobbyData, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, const char* pchKey ))
ice_steam_def_func(const char *, SteamAPI_ISteamMatchmaking_GetLobbyMemberData, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint64_steamid steamIDUser, const char* pchKey ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_SetLobbyMemberData, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, const char* pchKey, const char* pchValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_SendLobbyChatMsg, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, const void* pvMsgBody, int cubMsgBody ))
ice_steam_def_func(int, SteamAPI_ISteamMatchmaking_GetLobbyChatEntry, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, int iChatID, CSteamID* pSteamIDUser, void* pvData, int cubData, EChatEntryType* peChatEntryType ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_RequestLobbyData, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmaking_SetLobbyGameServer, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, uint64_steamid steamIDGameServer ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_GetLobbyGameServer, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint32* punGameServerIP, uint16* punGameServerPort, CSteamID* psteamIDGameServer ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, int cMaxMembers ))
ice_steam_def_func(int, SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_SetLobbyType, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, ELobbyType eLobbyType ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_SetLobbyJoinable, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, bool bLobbyJoinable ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamMatchmaking_GetLobbyOwner, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_SetLobbyOwner, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint64_steamid steamIDNewOwner ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmaking_SetLinkedLobby, ( ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint64_steamid steamIDLobbyDependent ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded, ( ISteamMatchmakingServerListResponse* self, HServerListRequest hRequest, int iServer ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond, ( ISteamMatchmakingServerListResponse* self, HServerListRequest hRequest, int iServer ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete, ( ISteamMatchmakingServerListResponse* self, HServerListRequest hRequest, EMatchMakingServerResponse response ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingPingResponse_ServerResponded, ( ISteamMatchmakingPingResponse* self, gameserveritem_t & server ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond, ( ISteamMatchmakingPingResponse* self ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList, ( ISteamMatchmakingPlayersResponse* self, const char* pchName, int nScore, float flTimePlayed ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond, ( ISteamMatchmakingPlayersResponse* self ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete, ( ISteamMatchmakingPlayersResponse* self ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded, ( ISteamMatchmakingRulesResponse* self, const char* pchRule, const char* pchValue ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond, ( ISteamMatchmakingRulesResponse* self ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete, ( ISteamMatchmakingRulesResponse* self ))
ice_steam_def_func(ISteamMatchmakingServers*, SteamAPI_SteamMatchmakingServers_v002, ())
ice_steam_def_func(HServerListRequest, SteamAPI_ISteamMatchmakingServers_RequestInternetServerList, ( ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t* * ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse ))
ice_steam_def_func(HServerListRequest, SteamAPI_ISteamMatchmakingServers_RequestLANServerList, ( ISteamMatchmakingServers* self, AppId_t iApp, ISteamMatchmakingServerListResponse* pRequestServersResponse ))
ice_steam_def_func(HServerListRequest, SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList, ( ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t* * ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse ))
ice_steam_def_func(HServerListRequest, SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList, ( ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t* * ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse ))
ice_steam_def_func(HServerListRequest, SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList, ( ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t* * ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse ))
ice_steam_def_func(HServerListRequest, SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList, ( ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t* * ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingServers_ReleaseRequest, ( ISteamMatchmakingServers* self, HServerListRequest hServerListRequest ))
ice_steam_def_func(gameserveritem_t*, SteamAPI_ISteamMatchmakingServers_GetServerDetails, ( ISteamMatchmakingServers* self, HServerListRequest hRequest, int iServer ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingServers_CancelQuery, ( ISteamMatchmakingServers* self, HServerListRequest hRequest ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingServers_RefreshQuery, ( ISteamMatchmakingServers* self, HServerListRequest hRequest ))
ice_steam_def_func(bool, SteamAPI_ISteamMatchmakingServers_IsRefreshing, ( ISteamMatchmakingServers* self, HServerListRequest hRequest ))
ice_steam_def_func(int, SteamAPI_ISteamMatchmakingServers_GetServerCount, ( ISteamMatchmakingServers* self, HServerListRequest hRequest ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingServers_RefreshServer, ( ISteamMatchmakingServers* self, HServerListRequest hRequest, int iServer ))
ice_steam_def_func(HServerQuery, SteamAPI_ISteamMatchmakingServers_PingServer, ( ISteamMatchmakingServers* self, uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse* pRequestServersResponse ))
ice_steam_def_func(HServerQuery, SteamAPI_ISteamMatchmakingServers_PlayerDetails, ( ISteamMatchmakingServers* self, uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse* pRequestServersResponse ))
ice_steam_def_func(HServerQuery, SteamAPI_ISteamMatchmakingServers_ServerRules, ( ISteamMatchmakingServers* self, uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse* pRequestServersResponse ))
ice_steam_def_func(void, SteamAPI_ISteamMatchmakingServers_CancelServerQuery, ( ISteamMatchmakingServers* self, HServerQuery hServerQuery ))
ice_steam_def_func(ISteamGameSearch*, SteamAPI_SteamGameSearch_v001, ())
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_AddGameSearchParams, ( ISteamGameSearch* self, const char* pchKeyToFind, const char* pchValuesToFind ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_SearchForGameWithLobby, ( ISteamGameSearch* self, uint64_steamid steamIDLobby, int nPlayerMin, int nPlayerMax ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_SearchForGameSolo, ( ISteamGameSearch* self, int nPlayerMin, int nPlayerMax ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_AcceptGame, ( ISteamGameSearch* self ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_DeclineGame, ( ISteamGameSearch* self ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_RetrieveConnectionDetails, ( ISteamGameSearch* self, uint64_steamid steamIDHost, char* pchConnectionDetails, int cubConnectionDetails ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_EndGameSearch, ( ISteamGameSearch* self ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_SetGameHostParams, ( ISteamGameSearch* self, const char* pchKey, const char* pchValue ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_SetConnectionDetails, ( ISteamGameSearch* self, const char* pchConnectionDetails, int cubConnectionDetails ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_RequestPlayersForGame, ( ISteamGameSearch* self, int nPlayerMin, int nPlayerMax, int nMaxTeamSize ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_HostConfirmGameStart, ( ISteamGameSearch* self, uint64 ullUniqueGameID ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_CancelRequestPlayersForGame, ( ISteamGameSearch* self ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_SubmitPlayerResult, ( ISteamGameSearch* self, uint64 ullUniqueGameID, uint64_steamid steamIDPlayer, EPlayerResult_t EPlayerResult ))
ice_steam_def_func(EGameSearchErrorCode_t, SteamAPI_ISteamGameSearch_EndGame, ( ISteamGameSearch* self, uint64 ullUniqueGameID ))
ice_steam_def_func(ISteamParties*, SteamAPI_SteamParties_v002, ())
ice_steam_def_func(uint32, SteamAPI_ISteamParties_GetNumActiveBeacons, ( ISteamParties* self ))
ice_steam_def_func(PartyBeaconID_t, SteamAPI_ISteamParties_GetBeaconByIndex, ( ISteamParties* self, uint32 unIndex ))
ice_steam_def_func(bool, SteamAPI_ISteamParties_GetBeaconDetails, ( ISteamParties* self, PartyBeaconID_t ulBeaconID, CSteamID* pSteamIDBeaconOwner, SteamPartyBeaconLocation_t* pLocation, char* pchMetadata, int cchMetadata ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamParties_JoinParty, ( ISteamParties* self, PartyBeaconID_t ulBeaconID ))
ice_steam_def_func(bool, SteamAPI_ISteamParties_GetNumAvailableBeaconLocations, ( ISteamParties* self, uint32* puNumLocations ))
ice_steam_def_func(bool, SteamAPI_ISteamParties_GetAvailableBeaconLocations, ( ISteamParties* self, SteamPartyBeaconLocation_t* pLocationList, uint32 uMaxNumLocations ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamParties_CreateBeacon, ( ISteamParties* self, uint32 unOpenSlots, SteamPartyBeaconLocation_t* pBeaconLocation, const char* pchConnectString, const char* pchMetadata ))
ice_steam_def_func(void, SteamAPI_ISteamParties_OnReservationCompleted, ( ISteamParties* self, PartyBeaconID_t ulBeacon, uint64_steamid steamIDUser ))
ice_steam_def_func(void, SteamAPI_ISteamParties_CancelReservation, ( ISteamParties* self, PartyBeaconID_t ulBeacon, uint64_steamid steamIDUser ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamParties_ChangeNumOpenSlots, ( ISteamParties* self, PartyBeaconID_t ulBeacon, uint32 unOpenSlots ))
ice_steam_def_func(bool, SteamAPI_ISteamParties_DestroyBeacon, ( ISteamParties* self, PartyBeaconID_t ulBeacon ))
ice_steam_def_func(bool, SteamAPI_ISteamParties_GetBeaconLocationData, ( ISteamParties* self, SteamPartyBeaconLocation_t BeaconLocation, ESteamPartyBeaconLocationData eData, char* pchDataStringOut, int cchDataStringOut ))
ice_steam_def_func(ISteamRemoteStorage*, SteamAPI_SteamRemoteStorage_v016, ())
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_FileWrite, ( ISteamRemoteStorage* self, const char* pchFile, const void* pvData, int32 cubData ))
ice_steam_def_func(int32, SteamAPI_ISteamRemoteStorage_FileRead, ( ISteamRemoteStorage* self, const char* pchFile, void* pvData, int32 cubDataToRead ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_FileWriteAsync, ( ISteamRemoteStorage* self, const char* pchFile, const void* pvData, uint32 cubData ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_FileReadAsync, ( ISteamRemoteStorage* self, const char* pchFile, uint32 nOffset, uint32 cubToRead ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_FileReadAsyncComplete, ( ISteamRemoteStorage* self, SteamAPICall_t hReadCall, void* pvBuffer, uint32 cubToRead ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_FileForget, ( ISteamRemoteStorage* self, const char* pchFile ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_FileDelete, ( ISteamRemoteStorage* self, const char* pchFile ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_FileShare, ( ISteamRemoteStorage* self, const char* pchFile ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_SetSyncPlatforms, ( ISteamRemoteStorage* self, const char* pchFile, ERemoteStoragePlatform eRemoteStoragePlatform ))
ice_steam_def_func(UGCFileWriteStreamHandle_t, SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen, ( ISteamRemoteStorage* self, const char* pchFile ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk, ( ISteamRemoteStorage* self, UGCFileWriteStreamHandle_t writeHandle, const void* pvData, int32 cubData ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_FileWriteStreamClose, ( ISteamRemoteStorage* self, UGCFileWriteStreamHandle_t writeHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel, ( ISteamRemoteStorage* self, UGCFileWriteStreamHandle_t writeHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_FileExists, ( ISteamRemoteStorage* self, const char* pchFile ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_FilePersisted, ( ISteamRemoteStorage* self, const char* pchFile ))
ice_steam_def_func(int32, SteamAPI_ISteamRemoteStorage_GetFileSize, ( ISteamRemoteStorage* self, const char* pchFile ))
ice_steam_def_func(int64, SteamAPI_ISteamRemoteStorage_GetFileTimestamp, ( ISteamRemoteStorage* self, const char* pchFile ))
ice_steam_def_func(ERemoteStoragePlatform, SteamAPI_ISteamRemoteStorage_GetSyncPlatforms, ( ISteamRemoteStorage* self, const char* pchFile ))
ice_steam_def_func(int32, SteamAPI_ISteamRemoteStorage_GetFileCount, ( ISteamRemoteStorage* self ))
ice_steam_def_func(const char *, SteamAPI_ISteamRemoteStorage_GetFileNameAndSize, ( ISteamRemoteStorage* self, int iFile, int32* pnFileSizeInBytes ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_GetQuota, ( ISteamRemoteStorage* self, uint64* pnTotalBytes, uint64* puAvailableBytes ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_IsCloudEnabledForAccount, ( ISteamRemoteStorage* self ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_IsCloudEnabledForApp, ( ISteamRemoteStorage* self ))
ice_steam_def_func(void, SteamAPI_ISteamRemoteStorage_SetCloudEnabledForApp, ( ISteamRemoteStorage* self, bool bEnabled ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_UGCDownload, ( ISteamRemoteStorage* self, UGCHandle_t hContent, uint32 unPriority ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress, ( ISteamRemoteStorage* self, UGCHandle_t hContent, int32* pnBytesDownloaded, int32* pnBytesExpected ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_GetUGCDetails, ( ISteamRemoteStorage* self, UGCHandle_t hContent, AppId_t* pnAppID, char* * ppchName, int32* pnFileSizeInBytes, CSteamID* pSteamIDOwner ))
ice_steam_def_func(int32, SteamAPI_ISteamRemoteStorage_UGCRead, ( ISteamRemoteStorage* self, UGCHandle_t hContent, void* pvData, int32 cubDataToRead, uint32 cOffset, EUGCReadAction eAction ))
ice_steam_def_func(int32, SteamAPI_ISteamRemoteStorage_GetCachedUGCCount, ( ISteamRemoteStorage* self ))
ice_steam_def_func(UGCHandle_t, SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle, ( ISteamRemoteStorage* self, int32 iCachedContent ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_PublishWorkshopFile, ( ISteamRemoteStorage* self, const char* pchFile, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags, EWorkshopFileType eWorkshopFileType ))
ice_steam_def_func(PublishedFileUpdateHandle_t, SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest, ( ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile, ( ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char* pchFile ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile, ( ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char* pchPreviewFile ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle, ( ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char* pchTitle ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription, ( ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char* pchDescription ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility, ( ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, ERemoteStoragePublishedFileVisibility eVisibility ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags, ( ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, SteamParamStringArray_t* pTags ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate, ( ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails, ( ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId, uint32 unMaxSecondsOld ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_DeletePublishedFile, ( ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles, ( ISteamRemoteStorage* self, uint32 unStartIndex ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_SubscribePublishedFile, ( ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles, ( ISteamRemoteStorage* self, uint32 unStartIndex ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile, ( ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription, ( ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char* pchChangeDescription ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails, ( ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote, ( ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId, bool bVoteUp ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails, ( ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles, ( ISteamRemoteStorage* self, uint64_steamid steamId, uint32 unStartIndex, SteamParamStringArray_t* pRequiredTags, SteamParamStringArray_t* pExcludedTags ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_PublishVideo, ( ISteamRemoteStorage* self, EWorkshopVideoProvider eVideoProvider, const char* pchVideoAccount, const char* pchVideoIdentifier, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction, ( ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction, ( ISteamRemoteStorage* self, EWorkshopFileAction eAction, uint32 unStartIndex ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles, ( ISteamRemoteStorage* self, EWorkshopEnumerationType eEnumerationType, uint32 unStartIndex, uint32 unCount, uint32 unDays, SteamParamStringArray_t* pTags, SteamParamStringArray_t* pUserTags ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation, ( ISteamRemoteStorage* self, UGCHandle_t hContent, const char* pchLocation, uint32 unPriority ))
ice_steam_def_func(int32, SteamAPI_ISteamRemoteStorage_GetLocalFileChangeCount, ( ISteamRemoteStorage* self ))
ice_steam_def_func(const char *, SteamAPI_ISteamRemoteStorage_GetLocalFileChange, ( ISteamRemoteStorage* self, int iFile, ERemoteStorageLocalFileChange* pEChangeType, ERemoteStorageFilePathType* pEFilePathType ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_BeginFileWriteBatch, ( ISteamRemoteStorage* self ))
ice_steam_def_func(bool, SteamAPI_ISteamRemoteStorage_EndFileWriteBatch, ( ISteamRemoteStorage* self ))
ice_steam_def_func(ISteamUserStats*, SteamAPI_SteamUserStats_v012, ())
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_RequestCurrentStats, ( ISteamUserStats* self ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetStatInt32, ( ISteamUserStats* self, const char* pchName, int32* pData ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetStatFloat, ( ISteamUserStats* self, const char* pchName, float* pData ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_SetStatInt32, ( ISteamUserStats* self, const char* pchName, int32 nData ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_SetStatFloat, ( ISteamUserStats* self, const char* pchName, float fData ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_UpdateAvgRateStat, ( ISteamUserStats* self, const char* pchName, float flCountThisSession, double dSessionLength ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetAchievement, ( ISteamUserStats* self, const char* pchName, bool* pbAchieved ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_SetAchievement, ( ISteamUserStats* self, const char* pchName ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_ClearAchievement, ( ISteamUserStats* self, const char* pchName ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime, ( ISteamUserStats* self, const char* pchName, bool* pbAchieved, uint32* punUnlockTime ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_StoreStats, ( ISteamUserStats* self ))
ice_steam_def_func(int, SteamAPI_ISteamUserStats_GetAchievementIcon, ( ISteamUserStats* self, const char* pchName ))
ice_steam_def_func(const char *, SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute, ( ISteamUserStats* self, const char* pchName, const char* pchKey ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_IndicateAchievementProgress, ( ISteamUserStats* self, const char* pchName, uint32 nCurProgress, uint32 nMaxProgress ))
ice_steam_def_func(uint32, SteamAPI_ISteamUserStats_GetNumAchievements, ( ISteamUserStats* self ))
ice_steam_def_func(const char *, SteamAPI_ISteamUserStats_GetAchievementName, ( ISteamUserStats* self, uint32 iAchievement ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_RequestUserStats, ( ISteamUserStats* self, uint64_steamid steamIDUser ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetUserStatInt32, ( ISteamUserStats* self, uint64_steamid steamIDUser, const char* pchName, int32* pData ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetUserStatFloat, ( ISteamUserStats* self, uint64_steamid steamIDUser, const char* pchName, float* pData ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetUserAchievement, ( ISteamUserStats* self, uint64_steamid steamIDUser, const char* pchName, bool* pbAchieved ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime, ( ISteamUserStats* self, uint64_steamid steamIDUser, const char* pchName, bool* pbAchieved, uint32* punUnlockTime ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_ResetAllStats, ( ISteamUserStats* self, bool bAchievementsToo ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_FindOrCreateLeaderboard, ( ISteamUserStats* self, const char* pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_FindLeaderboard, ( ISteamUserStats* self, const char* pchLeaderboardName ))
ice_steam_def_func(const char *, SteamAPI_ISteamUserStats_GetLeaderboardName, ( ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard ))
ice_steam_def_func(int, SteamAPI_ISteamUserStats_GetLeaderboardEntryCount, ( ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard ))
ice_steam_def_func(ELeaderboardSortMethod, SteamAPI_ISteamUserStats_GetLeaderboardSortMethod, ( ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard ))
ice_steam_def_func(ELeaderboardDisplayType, SteamAPI_ISteamUserStats_GetLeaderboardDisplayType, ( ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_DownloadLeaderboardEntries, ( ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers, ( ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard, CSteamID* prgUsers, int cUsers ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry, ( ISteamUserStats* self, SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t* pLeaderboardEntry, int32* pDetails, int cDetailsMax ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_UploadLeaderboardScore, ( ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32* pScoreDetails, int cScoreDetailsCount ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_AttachLeaderboardUGC, ( ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers, ( ISteamUserStats* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages, ( ISteamUserStats* self ))
ice_steam_def_func(int, SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo, ( ISteamUserStats* self, char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved ))
ice_steam_def_func(int, SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo, ( ISteamUserStats* self, int iIteratorPrevious, char* pchName, uint32 unNameBufLen, float* pflPercent, bool* pbAchieved ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetAchievementAchievedPercent, ( ISteamUserStats* self, const char* pchName, float* pflPercent ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUserStats_RequestGlobalStats, ( ISteamUserStats* self, int nHistoryDays ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetGlobalStatInt64, ( ISteamUserStats* self, const char* pchStatName, int64* pData ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetGlobalStatDouble, ( ISteamUserStats* self, const char* pchStatName, double* pData ))
ice_steam_def_func(int32, SteamAPI_ISteamUserStats_GetGlobalStatHistoryInt64, ( ISteamUserStats* self, const char* pchStatName, int64* pData, uint32 cubData ))
ice_steam_def_func(int32, SteamAPI_ISteamUserStats_GetGlobalStatHistoryDouble, ( ISteamUserStats* self, const char* pchStatName, double* pData, uint32 cubData ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetAchievementProgressLimitsInt32, ( ISteamUserStats* self, const char* pchName, int32* pnMinProgress, int32* pnMaxProgress ))
ice_steam_def_func(bool, SteamAPI_ISteamUserStats_GetAchievementProgressLimitsFloat, ( ISteamUserStats* self, const char* pchName, float* pfMinProgress, float* pfMaxProgress ))
ice_steam_def_func(ISteamApps*, SteamAPI_SteamApps_v008, ())
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsSubscribed, ( ISteamApps* self ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsLowViolence, ( ISteamApps* self ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsCybercafe, ( ISteamApps* self ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsVACBanned, ( ISteamApps* self ))
ice_steam_def_func(const char *, SteamAPI_ISteamApps_GetCurrentGameLanguage, ( ISteamApps* self ))
ice_steam_def_func(const char *, SteamAPI_ISteamApps_GetAvailableGameLanguages, ( ISteamApps* self ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsSubscribedApp, ( ISteamApps* self, AppId_t appID ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsDlcInstalled, ( ISteamApps* self, AppId_t appID ))
ice_steam_def_func(uint32, SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime, ( ISteamApps* self, AppId_t nAppID ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend, ( ISteamApps* self ))
ice_steam_def_func(int, SteamAPI_ISteamApps_GetDLCCount, ( ISteamApps* self ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BGetDLCDataByIndex, ( ISteamApps* self, int iDLC, AppId_t* pAppID, bool* pbAvailable, char* pchName, int cchNameBufferSize ))
ice_steam_def_func(void, SteamAPI_ISteamApps_InstallDLC, ( ISteamApps* self, AppId_t nAppID ))
ice_steam_def_func(void, SteamAPI_ISteamApps_UninstallDLC, ( ISteamApps* self, AppId_t nAppID ))
ice_steam_def_func(void, SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey, ( ISteamApps* self, AppId_t nAppID ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_GetCurrentBetaName, ( ISteamApps* self, char* pchName, int cchNameBufferSize ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_MarkContentCorrupt, ( ISteamApps* self, bool bMissingFilesOnly ))
ice_steam_def_func(uint32, SteamAPI_ISteamApps_GetInstalledDepots, ( ISteamApps* self, AppId_t appID, DepotId_t* pvecDepots, uint32 cMaxDepots ))
ice_steam_def_func(uint32, SteamAPI_ISteamApps_GetAppInstallDir, ( ISteamApps* self, AppId_t appID, char* pchFolder, uint32 cchFolderBufferSize ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsAppInstalled, ( ISteamApps* self, AppId_t appID ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamApps_GetAppOwner, ( ISteamApps* self ))
ice_steam_def_func(const char *, SteamAPI_ISteamApps_GetLaunchQueryParam, ( ISteamApps* self, const char* pchKey ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_GetDlcDownloadProgress, ( ISteamApps* self, AppId_t nAppID, uint64* punBytesDownloaded, uint64* punBytesTotal ))
ice_steam_def_func(int, SteamAPI_ISteamApps_GetAppBuildId, ( ISteamApps* self ))
ice_steam_def_func(void, SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys, ( ISteamApps* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamApps_GetFileDetails, ( ISteamApps* self, const char* pszFileName ))
ice_steam_def_func(int, SteamAPI_ISteamApps_GetLaunchCommandLine, ( ISteamApps* self, char* pszCommandLine, int cubCommandLine ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsSubscribedFromFamilySharing, ( ISteamApps* self ))
ice_steam_def_func(bool, SteamAPI_ISteamApps_BIsTimedTrial, ( ISteamApps* self, uint32* punSecondsAllowed, uint32* punSecondsPlayed ))
ice_steam_def_func(ISteamNetworking*, SteamAPI_SteamNetworking_v006, ())
ice_steam_def_func(ISteamNetworking*, SteamAPI_SteamGameServerNetworking_v006, ())
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_SendP2PPacket, ( ISteamNetworking* self, uint64_steamid steamIDRemote, const void* pubData, uint32 cubData, EP2PSend eP2PSendType, int nChannel ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_IsP2PPacketAvailable, ( ISteamNetworking* self, uint32* pcubMsgSize, int nChannel ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_ReadP2PPacket, ( ISteamNetworking* self, void* pubDest, uint32 cubDest, uint32* pcubMsgSize, CSteamID* psteamIDRemote, int nChannel ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser, ( ISteamNetworking* self, uint64_steamid steamIDRemote ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_CloseP2PSessionWithUser, ( ISteamNetworking* self, uint64_steamid steamIDRemote ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_CloseP2PChannelWithUser, ( ISteamNetworking* self, uint64_steamid steamIDRemote, int nChannel ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_GetP2PSessionState, ( ISteamNetworking* self, uint64_steamid steamIDRemote, P2PSessionState_t* pConnectionState ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_AllowP2PPacketRelay, ( ISteamNetworking* self, bool bAllow ))
ice_steam_def_func(SNetListenSocket_t, SteamAPI_ISteamNetworking_CreateListenSocket, ( ISteamNetworking* self, int nVirtualP2PPort, SteamIPAddress_t nIP, uint16 nPort, bool bAllowUseOfPacketRelay ))
ice_steam_def_func(SNetSocket_t, SteamAPI_ISteamNetworking_CreateP2PConnectionSocket, ( ISteamNetworking* self, uint64_steamid steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay ))
ice_steam_def_func(SNetSocket_t, SteamAPI_ISteamNetworking_CreateConnectionSocket, ( ISteamNetworking* self, SteamIPAddress_t nIP, uint16 nPort, int nTimeoutSec ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_DestroySocket, ( ISteamNetworking* self, SNetSocket_t hSocket, bool bNotifyRemoteEnd ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_DestroyListenSocket, ( ISteamNetworking* self, SNetListenSocket_t hSocket, bool bNotifyRemoteEnd ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_SendDataOnSocket, ( ISteamNetworking* self, SNetSocket_t hSocket, void* pubData, uint32 cubData, bool bReliable ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_IsDataAvailableOnSocket, ( ISteamNetworking* self, SNetSocket_t hSocket, uint32* pcubMsgSize ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_RetrieveDataFromSocket, ( ISteamNetworking* self, SNetSocket_t hSocket, void* pubDest, uint32 cubDest, uint32* pcubMsgSize ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_IsDataAvailable, ( ISteamNetworking* self, SNetListenSocket_t hListenSocket, uint32* pcubMsgSize, SNetSocket_t* phSocket ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_RetrieveData, ( ISteamNetworking* self, SNetListenSocket_t hListenSocket, void* pubDest, uint32 cubDest, uint32* pcubMsgSize, SNetSocket_t* phSocket ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_GetSocketInfo, ( ISteamNetworking* self, SNetSocket_t hSocket, CSteamID* pSteamIDRemote, int* peSocketStatus, SteamIPAddress_t* punIPRemote, uint16* punPortRemote ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworking_GetListenSocketInfo, ( ISteamNetworking* self, SNetListenSocket_t hListenSocket, SteamIPAddress_t* pnIP, uint16* pnPort ))
ice_steam_def_func(ESNetSocketConnectionType, SteamAPI_ISteamNetworking_GetSocketConnectionType, ( ISteamNetworking* self, SNetSocket_t hSocket ))
ice_steam_def_func(int, SteamAPI_ISteamNetworking_GetMaxPacketSize, ( ISteamNetworking* self, SNetSocket_t hSocket ))
ice_steam_def_func(ISteamScreenshots*, SteamAPI_SteamScreenshots_v003, ())
ice_steam_def_func(ScreenshotHandle, SteamAPI_ISteamScreenshots_WriteScreenshot, ( ISteamScreenshots* self, void* pubRGB, uint32 cubRGB, int nWidth, int nHeight ))
ice_steam_def_func(ScreenshotHandle, SteamAPI_ISteamScreenshots_AddScreenshotToLibrary, ( ISteamScreenshots* self, const char* pchFilename, const char* pchThumbnailFilename, int nWidth, int nHeight ))
ice_steam_def_func(void, SteamAPI_ISteamScreenshots_TriggerScreenshot, ( ISteamScreenshots* self ))
ice_steam_def_func(void, SteamAPI_ISteamScreenshots_HookScreenshots, ( ISteamScreenshots* self, bool bHook ))
ice_steam_def_func(bool, SteamAPI_ISteamScreenshots_SetLocation, ( ISteamScreenshots* self, ScreenshotHandle hScreenshot, const char* pchLocation ))
ice_steam_def_func(bool, SteamAPI_ISteamScreenshots_TagUser, ( ISteamScreenshots* self, ScreenshotHandle hScreenshot, uint64_steamid steamID ))
ice_steam_def_func(bool, SteamAPI_ISteamScreenshots_TagPublishedFile, ( ISteamScreenshots* self, ScreenshotHandle hScreenshot, PublishedFileId_t unPublishedFileID ))
ice_steam_def_func(bool, SteamAPI_ISteamScreenshots_IsScreenshotsHooked, ( ISteamScreenshots* self ))
ice_steam_def_func(ScreenshotHandle, SteamAPI_ISteamScreenshots_AddVRScreenshotToLibrary, ( ISteamScreenshots* self, EVRScreenshotType eType, const char* pchFilename, const char* pchVRFilename ))
ice_steam_def_func(ISteamMusic*, SteamAPI_SteamMusic_v001, ())
ice_steam_def_func(bool, SteamAPI_ISteamMusic_BIsEnabled, ( ISteamMusic* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusic_BIsPlaying, ( ISteamMusic* self ))
ice_steam_def_func(AudioPlayback_Status, SteamAPI_ISteamMusic_GetPlaybackStatus, ( ISteamMusic* self ))
ice_steam_def_func(void, SteamAPI_ISteamMusic_Play, ( ISteamMusic* self ))
ice_steam_def_func(void, SteamAPI_ISteamMusic_Pause, ( ISteamMusic* self ))
ice_steam_def_func(void, SteamAPI_ISteamMusic_PlayPrevious, ( ISteamMusic* self ))
ice_steam_def_func(void, SteamAPI_ISteamMusic_PlayNext, ( ISteamMusic* self ))
ice_steam_def_func(void, SteamAPI_ISteamMusic_SetVolume, ( ISteamMusic* self, float flVolume ))
ice_steam_def_func(float, SteamAPI_ISteamMusic_GetVolume, ( ISteamMusic* self ))
ice_steam_def_func(ISteamMusicRemote*, SteamAPI_SteamMusicRemote_v001, ())
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote, ( ISteamMusicRemote* self, const char* pchName ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote, ( ISteamMusicRemote* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote, ( ISteamMusicRemote* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_BActivationSuccess, ( ISteamMusicRemote* self, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_SetDisplayName, ( ISteamMusicRemote* self, const char* pchDisplayName ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64, ( ISteamMusicRemote* self, void* pvBuffer, uint32 cbBufferLength ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_EnablePlayPrevious, ( ISteamMusicRemote* self, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_EnablePlayNext, ( ISteamMusicRemote* self, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_EnableShuffled, ( ISteamMusicRemote* self, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_EnableLooped, ( ISteamMusicRemote* self, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_EnableQueue, ( ISteamMusicRemote* self, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_EnablePlaylists, ( ISteamMusicRemote* self, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus, ( ISteamMusicRemote* self, AudioPlayback_Status nStatus ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_UpdateShuffled, ( ISteamMusicRemote* self, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_UpdateLooped, ( ISteamMusicRemote* self, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_UpdateVolume, ( ISteamMusicRemote* self, float flValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_CurrentEntryWillChange, ( ISteamMusicRemote* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable, ( ISteamMusicRemote* self, bool bAvailable ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText, ( ISteamMusicRemote* self, const char* pchText ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds, ( ISteamMusicRemote* self, int nValue ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt, ( ISteamMusicRemote* self, void* pvBuffer, uint32 cbBufferLength ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_CurrentEntryDidChange, ( ISteamMusicRemote* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_QueueWillChange, ( ISteamMusicRemote* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_ResetQueueEntries, ( ISteamMusicRemote* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_SetQueueEntry, ( ISteamMusicRemote* self, int nID, int nPosition, const char* pchEntryText ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry, ( ISteamMusicRemote* self, int nID ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_QueueDidChange, ( ISteamMusicRemote* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_PlaylistWillChange, ( ISteamMusicRemote* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_ResetPlaylistEntries, ( ISteamMusicRemote* self ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_SetPlaylistEntry, ( ISteamMusicRemote* self, int nID, int nPosition, const char* pchEntryText ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry, ( ISteamMusicRemote* self, int nID ))
ice_steam_def_func(bool, SteamAPI_ISteamMusicRemote_PlaylistDidChange, ( ISteamMusicRemote* self ))
ice_steam_def_func(ISteamHTTP*, SteamAPI_SteamHTTP_v003, ())
ice_steam_def_func(ISteamHTTP*, SteamAPI_SteamGameServerHTTP_v003, ())
ice_steam_def_func(HTTPRequestHandle, SteamAPI_ISteamHTTP_CreateHTTPRequest, ( ISteamHTTP* self, EHTTPMethod eHTTPRequestMethod, const char* pchAbsoluteURL ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetHTTPRequestContextValue, ( ISteamHTTP* self, HTTPRequestHandle hRequest, uint64 ulContextValue ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout, ( ISteamHTTP* self, HTTPRequestHandle hRequest, uint32 unTimeoutSeconds ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue, ( ISteamHTTP* self, HTTPRequestHandle hRequest, const char* pchHeaderName, const char* pchHeaderValue ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter, ( ISteamHTTP* self, HTTPRequestHandle hRequest, const char* pchParamName, const char* pchParamValue ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SendHTTPRequest, ( ISteamHTTP* self, HTTPRequestHandle hRequest, SteamAPICall_t* pCallHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse, ( ISteamHTTP* self, HTTPRequestHandle hRequest, SteamAPICall_t* pCallHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_DeferHTTPRequest, ( ISteamHTTP* self, HTTPRequestHandle hRequest ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_PrioritizeHTTPRequest, ( ISteamHTTP* self, HTTPRequestHandle hRequest ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize, ( ISteamHTTP* self, HTTPRequestHandle hRequest, const char* pchHeaderName, uint32* unResponseHeaderSize ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue, ( ISteamHTTP* self, HTTPRequestHandle hRequest, const char* pchHeaderName, uint8* pHeaderValueBuffer, uint32 unBufferSize ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_GetHTTPResponseBodySize, ( ISteamHTTP* self, HTTPRequestHandle hRequest, uint32* unBodySize ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_GetHTTPResponseBodyData, ( ISteamHTTP* self, HTTPRequestHandle hRequest, uint8* pBodyDataBuffer, uint32 unBufferSize ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData, ( ISteamHTTP* self, HTTPRequestHandle hRequest, uint32 cOffset, uint8* pBodyDataBuffer, uint32 unBufferSize ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_ReleaseHTTPRequest, ( ISteamHTTP* self, HTTPRequestHandle hRequest ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct, ( ISteamHTTP* self, HTTPRequestHandle hRequest, float* pflPercentOut ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody, ( ISteamHTTP* self, HTTPRequestHandle hRequest, const char* pchContentType, uint8* pubBody, uint32 unBodyLen ))
ice_steam_def_func(HTTPCookieContainerHandle, SteamAPI_ISteamHTTP_CreateCookieContainer, ( ISteamHTTP* self, bool bAllowResponsesToModify ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_ReleaseCookieContainer, ( ISteamHTTP* self, HTTPCookieContainerHandle hCookieContainer ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetCookie, ( ISteamHTTP* self, HTTPCookieContainerHandle hCookieContainer, const char* pchHost, const char* pchUrl, const char* pchCookie ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer, ( ISteamHTTP* self, HTTPRequestHandle hRequest, HTTPCookieContainerHandle hCookieContainer ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo, ( ISteamHTTP* self, HTTPRequestHandle hRequest, const char* pchUserAgentInfo ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate, ( ISteamHTTP* self, HTTPRequestHandle hRequest, bool bRequireVerifiedCertificate ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS, ( ISteamHTTP* self, HTTPRequestHandle hRequest, uint32 unMilliseconds ))
ice_steam_def_func(bool, SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut, ( ISteamHTTP* self, HTTPRequestHandle hRequest, bool* pbWasTimedOut ))
ice_steam_def_func(ISteamInput*, SteamAPI_SteamInput_v005, ())
ice_steam_def_func(bool, SteamAPI_ISteamInput_Init, ( ISteamInput* self, bool bExplicitlyCallRunFrame ))
ice_steam_def_func(bool, SteamAPI_ISteamInput_Shutdown, ( ISteamInput* self ))
ice_steam_def_func(bool, SteamAPI_ISteamInput_SetInputActionManifestFilePath, ( ISteamInput* self, const char* pchInputActionManifestAbsolutePath ))
ice_steam_def_func(void, SteamAPI_ISteamInput_RunFrame, ( ISteamInput* self, bool bReservedValue ))
ice_steam_def_func(bool, SteamAPI_ISteamInput_BWaitForData, ( ISteamInput* self, bool bWaitForever, uint32 unTimeout ))
ice_steam_def_func(bool, SteamAPI_ISteamInput_BNewDataAvailable, ( ISteamInput* self ))
ice_steam_def_func(int, SteamAPI_ISteamInput_GetConnectedControllers, ( ISteamInput* self, InputHandle_t* handlesOut ))
ice_steam_def_func(void, SteamAPI_ISteamInput_EnableDeviceCallbacks, ( ISteamInput* self ))
ice_steam_def_func(void, SteamAPI_ISteamInput_EnableActionEventCallbacks, ( ISteamInput* self, SteamInputActionEventCallbackPointer pCallback ))
ice_steam_def_func(InputActionSetHandle_t, SteamAPI_ISteamInput_GetActionSetHandle, ( ISteamInput* self, const char* pszActionSetName ))
ice_steam_def_func(void, SteamAPI_ISteamInput_ActivateActionSet, ( ISteamInput* self, InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle ))
ice_steam_def_func(InputActionSetHandle_t, SteamAPI_ISteamInput_GetCurrentActionSet, ( ISteamInput* self, InputHandle_t inputHandle ))
ice_steam_def_func(void, SteamAPI_ISteamInput_ActivateActionSetLayer, ( ISteamInput* self, InputHandle_t inputHandle, InputActionSetHandle_t actionSetLayerHandle ))
ice_steam_def_func(void, SteamAPI_ISteamInput_DeactivateActionSetLayer, ( ISteamInput* self, InputHandle_t inputHandle, InputActionSetHandle_t actionSetLayerHandle ))
ice_steam_def_func(void, SteamAPI_ISteamInput_DeactivateAllActionSetLayers, ( ISteamInput* self, InputHandle_t inputHandle ))
ice_steam_def_func(int, SteamAPI_ISteamInput_GetActiveActionSetLayers, ( ISteamInput* self, InputHandle_t inputHandle, InputActionSetHandle_t* handlesOut ))
ice_steam_def_func(InputDigitalActionHandle_t, SteamAPI_ISteamInput_GetDigitalActionHandle, ( ISteamInput* self, const char* pszActionName ))
ice_steam_def_func(InputDigitalActionData_t, SteamAPI_ISteamInput_GetDigitalActionData, ( ISteamInput* self, InputHandle_t inputHandle, InputDigitalActionHandle_t digitalActionHandle ))
ice_steam_def_func(int, SteamAPI_ISteamInput_GetDigitalActionOrigins, ( ISteamInput* self, InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle, InputDigitalActionHandle_t digitalActionHandle, EInputActionOrigin* originsOut ))
ice_steam_def_func(const char *, SteamAPI_ISteamInput_GetStringForDigitalActionName, ( ISteamInput* self, InputDigitalActionHandle_t eActionHandle ))
ice_steam_def_func(InputAnalogActionHandle_t, SteamAPI_ISteamInput_GetAnalogActionHandle, ( ISteamInput* self, const char* pszActionName ))
ice_steam_def_func(InputAnalogActionData_t, SteamAPI_ISteamInput_GetAnalogActionData, ( ISteamInput* self, InputHandle_t inputHandle, InputAnalogActionHandle_t analogActionHandle ))
ice_steam_def_func(int, SteamAPI_ISteamInput_GetAnalogActionOrigins, ( ISteamInput* self, InputHandle_t inputHandle, InputActionSetHandle_t actionSetHandle, InputAnalogActionHandle_t analogActionHandle, EInputActionOrigin* originsOut ))
ice_steam_def_func(const char *, SteamAPI_ISteamInput_GetGlyphPNGForActionOrigin, ( ISteamInput* self, EInputActionOrigin eOrigin, ESteamInputGlyphSize eSize, uint32 unFlags ))
ice_steam_def_func(const char *, SteamAPI_ISteamInput_GetGlyphSVGForActionOrigin, ( ISteamInput* self, EInputActionOrigin eOrigin, uint32 unFlags ))
ice_steam_def_func(const char *, SteamAPI_ISteamInput_GetGlyphForActionOrigin_Legacy, ( ISteamInput* self, EInputActionOrigin eOrigin ))
ice_steam_def_func(const char *, SteamAPI_ISteamInput_GetStringForActionOrigin, ( ISteamInput* self, EInputActionOrigin eOrigin ))
ice_steam_def_func(const char *, SteamAPI_ISteamInput_GetStringForAnalogActionName, ( ISteamInput* self, InputAnalogActionHandle_t eActionHandle ))
ice_steam_def_func(void, SteamAPI_ISteamInput_StopAnalogActionMomentum, ( ISteamInput* self, InputHandle_t inputHandle, InputAnalogActionHandle_t eAction ))
ice_steam_def_func(InputMotionData_t, SteamAPI_ISteamInput_GetMotionData, ( ISteamInput* self, InputHandle_t inputHandle ))
ice_steam_def_func(void, SteamAPI_ISteamInput_TriggerVibration, ( ISteamInput* self, InputHandle_t inputHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed ))
ice_steam_def_func(void, SteamAPI_ISteamInput_TriggerVibrationExtended, ( ISteamInput* self, InputHandle_t inputHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed, unsigned short usLeftTriggerSpeed, unsigned short usRightTriggerSpeed ))
ice_steam_def_func(void, SteamAPI_ISteamInput_TriggerSimpleHapticEvent, ( ISteamInput* self, InputHandle_t inputHandle, EControllerHapticLocation eHapticLocation, uint8 nIntensity, char nGainDB, uint8 nOtherIntensity, char nOtherGainDB ))
ice_steam_def_func(void, SteamAPI_ISteamInput_SetLEDColor, ( ISteamInput* self, InputHandle_t inputHandle, uint8 nColorR, uint8 nColorG, uint8 nColorB, unsigned int nFlags ))
ice_steam_def_func(void, SteamAPI_ISteamInput_Legacy_TriggerHapticPulse, ( ISteamInput* self, InputHandle_t inputHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec ))
ice_steam_def_func(void, SteamAPI_ISteamInput_Legacy_TriggerRepeatedHapticPulse, ( ISteamInput* self, InputHandle_t inputHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags ))
ice_steam_def_func(bool, SteamAPI_ISteamInput_ShowBindingPanel, ( ISteamInput* self, InputHandle_t inputHandle ))
ice_steam_def_func(ESteamInputType, SteamAPI_ISteamInput_GetInputTypeForHandle, ( ISteamInput* self, InputHandle_t inputHandle ))
ice_steam_def_func(InputHandle_t, SteamAPI_ISteamInput_GetControllerForGamepadIndex, ( ISteamInput* self, int nIndex ))
ice_steam_def_func(int, SteamAPI_ISteamInput_GetGamepadIndexForController, ( ISteamInput* self, InputHandle_t ulinputHandle ))
ice_steam_def_func(const char *, SteamAPI_ISteamInput_GetStringForXboxOrigin, ( ISteamInput* self, EXboxOrigin eOrigin ))
ice_steam_def_func(const char *, SteamAPI_ISteamInput_GetGlyphForXboxOrigin, ( ISteamInput* self, EXboxOrigin eOrigin ))
ice_steam_def_func(EInputActionOrigin, SteamAPI_ISteamInput_GetActionOriginFromXboxOrigin, ( ISteamInput* self, InputHandle_t inputHandle, EXboxOrigin eOrigin ))
ice_steam_def_func(EInputActionOrigin, SteamAPI_ISteamInput_TranslateActionOrigin, ( ISteamInput* self, ESteamInputType eDestinationInputType, EInputActionOrigin eSourceOrigin ))
ice_steam_def_func(bool, SteamAPI_ISteamInput_GetDeviceBindingRevision, ( ISteamInput* self, InputHandle_t inputHandle, int* pMajor, int* pMinor ))
ice_steam_def_func(uint32, SteamAPI_ISteamInput_GetRemotePlaySessionID, ( ISteamInput* self, InputHandle_t inputHandle ))
ice_steam_def_func(uint16, SteamAPI_ISteamInput_GetSessionInputConfigurationSettings, ( ISteamInput* self ))
ice_steam_def_func(ISteamController*, SteamAPI_SteamController_v008, ())
ice_steam_def_func(bool, SteamAPI_ISteamController_Init, ( ISteamController* self ))
ice_steam_def_func(bool, SteamAPI_ISteamController_Shutdown, ( ISteamController* self ))
ice_steam_def_func(void, SteamAPI_ISteamController_RunFrame, ( ISteamController* self ))
ice_steam_def_func(int, SteamAPI_ISteamController_GetConnectedControllers, ( ISteamController* self, ControllerHandle_t* handlesOut ))
ice_steam_def_func(ControllerActionSetHandle_t, SteamAPI_ISteamController_GetActionSetHandle, ( ISteamController* self, const char* pszActionSetName ))
ice_steam_def_func(void, SteamAPI_ISteamController_ActivateActionSet, ( ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle ))
ice_steam_def_func(ControllerActionSetHandle_t, SteamAPI_ISteamController_GetCurrentActionSet, ( ISteamController* self, ControllerHandle_t controllerHandle ))
ice_steam_def_func(void, SteamAPI_ISteamController_ActivateActionSetLayer, ( ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle ))
ice_steam_def_func(void, SteamAPI_ISteamController_DeactivateActionSetLayer, ( ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle ))
ice_steam_def_func(void, SteamAPI_ISteamController_DeactivateAllActionSetLayers, ( ISteamController* self, ControllerHandle_t controllerHandle ))
ice_steam_def_func(int, SteamAPI_ISteamController_GetActiveActionSetLayers, ( ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t* handlesOut ))
ice_steam_def_func(ControllerDigitalActionHandle_t, SteamAPI_ISteamController_GetDigitalActionHandle, ( ISteamController* self, const char* pszActionName ))
ice_steam_def_func(InputDigitalActionData_t, SteamAPI_ISteamController_GetDigitalActionData, ( ISteamController* self, ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle ))
ice_steam_def_func(int, SteamAPI_ISteamController_GetDigitalActionOrigins, ( ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerDigitalActionHandle_t digitalActionHandle, EControllerActionOrigin* originsOut ))
ice_steam_def_func(ControllerAnalogActionHandle_t, SteamAPI_ISteamController_GetAnalogActionHandle, ( ISteamController* self, const char* pszActionName ))
ice_steam_def_func(InputAnalogActionData_t, SteamAPI_ISteamController_GetAnalogActionData, ( ISteamController* self, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle ))
ice_steam_def_func(int, SteamAPI_ISteamController_GetAnalogActionOrigins, ( ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerAnalogActionHandle_t analogActionHandle, EControllerActionOrigin* originsOut ))
ice_steam_def_func(const char *, SteamAPI_ISteamController_GetGlyphForActionOrigin, ( ISteamController* self, EControllerActionOrigin eOrigin ))
ice_steam_def_func(const char *, SteamAPI_ISteamController_GetStringForActionOrigin, ( ISteamController* self, EControllerActionOrigin eOrigin ))
ice_steam_def_func(void, SteamAPI_ISteamController_StopAnalogActionMomentum, ( ISteamController* self, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t eAction ))
ice_steam_def_func(InputMotionData_t, SteamAPI_ISteamController_GetMotionData, ( ISteamController* self, ControllerHandle_t controllerHandle ))
ice_steam_def_func(void, SteamAPI_ISteamController_TriggerHapticPulse, ( ISteamController* self, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec ))
ice_steam_def_func(void, SteamAPI_ISteamController_TriggerRepeatedHapticPulse, ( ISteamController* self, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags ))
ice_steam_def_func(void, SteamAPI_ISteamController_TriggerVibration, ( ISteamController* self, ControllerHandle_t controllerHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed ))
ice_steam_def_func(void, SteamAPI_ISteamController_SetLEDColor, ( ISteamController* self, ControllerHandle_t controllerHandle, uint8 nColorR, uint8 nColorG, uint8 nColorB, unsigned int nFlags ))
ice_steam_def_func(bool, SteamAPI_ISteamController_ShowBindingPanel, ( ISteamController* self, ControllerHandle_t controllerHandle ))
ice_steam_def_func(ESteamInputType, SteamAPI_ISteamController_GetInputTypeForHandle, ( ISteamController* self, ControllerHandle_t controllerHandle ))
ice_steam_def_func(ControllerHandle_t, SteamAPI_ISteamController_GetControllerForGamepadIndex, ( ISteamController* self, int nIndex ))
ice_steam_def_func(int, SteamAPI_ISteamController_GetGamepadIndexForController, ( ISteamController* self, ControllerHandle_t ulControllerHandle ))
ice_steam_def_func(const char *, SteamAPI_ISteamController_GetStringForXboxOrigin, ( ISteamController* self, EXboxOrigin eOrigin ))
ice_steam_def_func(const char *, SteamAPI_ISteamController_GetGlyphForXboxOrigin, ( ISteamController* self, EXboxOrigin eOrigin ))
ice_steam_def_func(EControllerActionOrigin, SteamAPI_ISteamController_GetActionOriginFromXboxOrigin, ( ISteamController* self, ControllerHandle_t controllerHandle, EXboxOrigin eOrigin ))
ice_steam_def_func(EControllerActionOrigin, SteamAPI_ISteamController_TranslateActionOrigin, ( ISteamController* self, ESteamInputType eDestinationInputType, EControllerActionOrigin eSourceOrigin ))
ice_steam_def_func(bool, SteamAPI_ISteamController_GetControllerBindingRevision, ( ISteamController* self, ControllerHandle_t controllerHandle, int* pMajor, int* pMinor ))
ice_steam_def_func(ISteamUGC*, SteamAPI_SteamUGC_v015, ())
ice_steam_def_func(ISteamUGC*, SteamAPI_SteamGameServerUGC_v015, ())
ice_steam_def_func(UGCQueryHandle_t, SteamAPI_ISteamUGC_CreateQueryUserUGCRequest, ( ISteamUGC* self, AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage ))
ice_steam_def_func(UGCQueryHandle_t, SteamAPI_ISteamUGC_CreateQueryAllUGCRequestPage, ( ISteamUGC* self, EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage ))
ice_steam_def_func(UGCQueryHandle_t, SteamAPI_ISteamUGC_CreateQueryAllUGCRequestCursor, ( ISteamUGC* self, EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, const char* pchCursor ))
ice_steam_def_func(UGCQueryHandle_t, SteamAPI_ISteamUGC_CreateQueryUGCDetailsRequest, ( ISteamUGC* self, PublishedFileId_t* pvecPublishedFileID, uint32 unNumPublishedFileIDs ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_SendQueryUGCRequest, ( ISteamUGC* self, UGCQueryHandle_t handle ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryUGCResult, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t* pDetails ))
ice_steam_def_func(uint32, SteamAPI_ISteamUGC_GetQueryUGCNumTags, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryUGCTag, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, uint32 indexTag, char* pchValue, uint32 cchValueSize ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryUGCTagDisplayName, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, uint32 indexTag, char* pchValue, uint32 cchValueSize ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryUGCPreviewURL, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, char* pchURL, uint32 cchURLSize ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryUGCMetadata, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, char* pchMetadata, uint32 cchMetadatasize ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryUGCChildren, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryUGCStatistic, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, EItemStatistic eStatType, uint64* pStatValue ))
ice_steam_def_func(uint32, SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, uint32 previewIndex, char* pchURLOrVideoID, uint32 cchURLSize, char* pchOriginalFileName, uint32 cchOriginalFileNameSize, EItemPreviewType* pPreviewType ))
ice_steam_def_func(uint32, SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, uint32 keyValueTagIndex, char* pchKey, uint32 cchKeySize, char* pchValue, uint32 cchValueSize ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetQueryFirstUGCKeyValueTag, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, const char* pchKey, char* pchValue, uint32 cchValueSize ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_ReleaseQueryUGCRequest, ( ISteamUGC* self, UGCQueryHandle_t handle ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_AddRequiredTag, ( ISteamUGC* self, UGCQueryHandle_t handle, const char* pTagName ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_AddRequiredTagGroup, ( ISteamUGC* self, UGCQueryHandle_t handle, const SteamParamStringArray_t* pTagGroups ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_AddExcludedTag, ( ISteamUGC* self, UGCQueryHandle_t handle, const char* pTagName ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetReturnOnlyIDs, ( ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnOnlyIDs ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetReturnKeyValueTags, ( ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnKeyValueTags ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetReturnLongDescription, ( ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnLongDescription ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetReturnMetadata, ( ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnMetadata ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetReturnChildren, ( ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnChildren ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetReturnAdditionalPreviews, ( ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnAdditionalPreviews ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetReturnTotalOnly, ( ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnTotalOnly ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetReturnPlaytimeStats, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 unDays ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetLanguage, ( ISteamUGC* self, UGCQueryHandle_t handle, const char* pchLanguage ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetAllowCachedResponse, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 unMaxAgeSeconds ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetCloudFileNameFilter, ( ISteamUGC* self, UGCQueryHandle_t handle, const char* pMatchCloudFileName ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetMatchAnyTag, ( ISteamUGC* self, UGCQueryHandle_t handle, bool bMatchAnyTag ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetSearchText, ( ISteamUGC* self, UGCQueryHandle_t handle, const char* pSearchText ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetRankedByTrendDays, ( ISteamUGC* self, UGCQueryHandle_t handle, uint32 unDays ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_AddRequiredKeyValueTag, ( ISteamUGC* self, UGCQueryHandle_t handle, const char* pKey, const char* pValue ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_RequestUGCDetails, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_CreateItem, ( ISteamUGC* self, AppId_t nConsumerAppId, EWorkshopFileType eFileType ))
ice_steam_def_func(UGCUpdateHandle_t, SteamAPI_ISteamUGC_StartItemUpdate, ( ISteamUGC* self, AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetItemTitle, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pchTitle ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetItemDescription, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pchDescription ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetItemUpdateLanguage, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pchLanguage ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetItemMetadata, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pchMetaData ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetItemVisibility, ( ISteamUGC* self, UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetItemTags, ( ISteamUGC* self, UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t* pTags ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetItemContent, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pszContentFolder ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetItemPreview, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pszPreviewFile ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_SetAllowLegacyUpload, ( ISteamUGC* self, UGCUpdateHandle_t handle, bool bAllowLegacyUpload ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_RemoveAllItemKeyValueTags, ( ISteamUGC* self, UGCUpdateHandle_t handle ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_RemoveItemKeyValueTags, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pchKey ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_AddItemKeyValueTag, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pchKey, const char* pchValue ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_AddItemPreviewFile, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pszPreviewFile, EItemPreviewType type ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_AddItemPreviewVideo, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pszVideoID ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_UpdateItemPreviewFile, ( ISteamUGC* self, UGCUpdateHandle_t handle, uint32 index, const char* pszPreviewFile ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_UpdateItemPreviewVideo, ( ISteamUGC* self, UGCUpdateHandle_t handle, uint32 index, const char* pszVideoID ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_RemoveItemPreview, ( ISteamUGC* self, UGCUpdateHandle_t handle, uint32 index ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_SubmitItemUpdate, ( ISteamUGC* self, UGCUpdateHandle_t handle, const char* pchChangeNote ))
ice_steam_def_func(EItemUpdateStatus, SteamAPI_ISteamUGC_GetItemUpdateProgress, ( ISteamUGC* self, UGCUpdateHandle_t handle, uint64* punBytesProcessed, uint64* punBytesTotal ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_SetUserItemVote, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID, bool bVoteUp ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_GetUserItemVote, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_AddItemToFavorites, ( ISteamUGC* self, AppId_t nAppId, PublishedFileId_t nPublishedFileID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_RemoveItemFromFavorites, ( ISteamUGC* self, AppId_t nAppId, PublishedFileId_t nPublishedFileID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_SubscribeItem, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_UnsubscribeItem, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID ))
ice_steam_def_func(uint32, SteamAPI_ISteamUGC_GetNumSubscribedItems, ( ISteamUGC* self ))
ice_steam_def_func(uint32, SteamAPI_ISteamUGC_GetSubscribedItems, ( ISteamUGC* self, PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries ))
ice_steam_def_func(uint32, SteamAPI_ISteamUGC_GetItemState, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetItemInstallInfo, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID, uint64* punSizeOnDisk, char* pchFolder, uint32 cchFolderSize, uint32* punTimeStamp ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_GetItemDownloadInfo, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID, uint64* punBytesDownloaded, uint64* punBytesTotal ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_DownloadItem, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID, bool bHighPriority ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_BInitWorkshopForGameServer, ( ISteamUGC* self, DepotId_t unWorkshopDepotID, const char* pszFolder ))
ice_steam_def_func(void, SteamAPI_ISteamUGC_SuspendDownloads, ( ISteamUGC* self, bool bSuspend ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_StartPlaytimeTracking, ( ISteamUGC* self, PublishedFileId_t* pvecPublishedFileID, uint32 unNumPublishedFileIDs ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_StopPlaytimeTracking, ( ISteamUGC* self, PublishedFileId_t* pvecPublishedFileID, uint32 unNumPublishedFileIDs ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems, ( ISteamUGC* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_AddDependency, ( ISteamUGC* self, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_RemoveDependency, ( ISteamUGC* self, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_AddAppDependency, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID, AppId_t nAppID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_RemoveAppDependency, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID, AppId_t nAppID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_GetAppDependencies, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_DeleteItem, ( ISteamUGC* self, PublishedFileId_t nPublishedFileID ))
ice_steam_def_func(bool, SteamAPI_ISteamUGC_ShowWorkshopEULA, ( ISteamUGC* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamUGC_GetWorkshopEULAStatus, ( ISteamUGC* self ))
ice_steam_def_func(ISteamAppList*, SteamAPI_SteamAppList_v001, ())
ice_steam_def_func(uint32, SteamAPI_ISteamAppList_GetNumInstalledApps, ( ISteamAppList* self ))
ice_steam_def_func(uint32, SteamAPI_ISteamAppList_GetInstalledApps, ( ISteamAppList* self, AppId_t* pvecAppID, uint32 unMaxAppIDs ))
ice_steam_def_func(int, SteamAPI_ISteamAppList_GetAppName, ( ISteamAppList* self, AppId_t nAppID, char* pchName, int cchNameMax ))
ice_steam_def_func(int, SteamAPI_ISteamAppList_GetAppInstallDir, ( ISteamAppList* self, AppId_t nAppID, char* pchDirectory, int cchNameMax ))
ice_steam_def_func(int, SteamAPI_ISteamAppList_GetAppBuildId, ( ISteamAppList* self, AppId_t nAppID ))
ice_steam_def_func(ISteamHTMLSurface*, SteamAPI_SteamHTMLSurface_v005, ())
ice_steam_def_func(bool, SteamAPI_ISteamHTMLSurface_Init, ( ISteamHTMLSurface* self ))
ice_steam_def_func(bool, SteamAPI_ISteamHTMLSurface_Shutdown, ( ISteamHTMLSurface* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamHTMLSurface_CreateBrowser, ( ISteamHTMLSurface* self, const char* pchUserAgent, const char* pchUserCSS ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_RemoveBrowser, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_LoadURL, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, const char* pchURL, const char* pchPostData ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_SetSize, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, uint32 unWidth, uint32 unHeight ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_StopLoad, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_Reload, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_GoBack, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_GoForward, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_AddHeader, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, const char* pchKey, const char* pchValue ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_ExecuteJavascript, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, const char* pchScript ))

/* FIXME: No C Equivalents?! */
/*
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_MouseUp, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, ISteamHTMLSurface::EHTMLMouseButton eMouseButton ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_MouseDown, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, ISteamHTMLSurface::EHTMLMouseButton eMouseButton ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_MouseDoubleClick, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, ISteamHTMLSurface::EHTMLMouseButton eMouseButton ))
*/

ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_MouseMove, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, int x, int y ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_MouseWheel, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, int32 nDelta ))

/* FIXME: No C Equivalents?! */
/*
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_KeyDown, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, ISteamHTMLSurface::EHTMLKeyModifiers eHTMLKeyModifiers, bool bIsSystemKey ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_KeyUp, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, ISteamHTMLSurface::EHTMLKeyModifiers eHTMLKeyModifiers ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_KeyChar, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, uint32 cUnicodeChar, ISteamHTMLSurface::EHTMLKeyModifiers eHTMLKeyModifiers ))
*/

ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_SetHorizontalScroll, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_SetVerticalScroll, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_SetKeyFocus, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, bool bHasKeyFocus ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_ViewSource, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_CopyToClipboard, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_PasteFromClipboard, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_Find, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, const char* pchSearchStr, bool bCurrentlyInFind, bool bReverse ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_StopFind, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_GetLinkAtPosition, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, int x, int y ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_SetCookie, ( ISteamHTMLSurface* self, const char* pchHostname, const char* pchKey, const char* pchValue, const char* pchPath, RTime32 nExpires, bool bSecure, bool bHTTPOnly ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_SetPageScaleFactor, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, float flZoom, int nPointX, int nPointY ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_SetBackgroundMode, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, bool bBackgroundMode ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, float flDPIScaling ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_OpenDeveloperTools, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_AllowStartRequest, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, bool bAllowed ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_JSDialogResponse, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, bool bResult ))
ice_steam_def_func(void, SteamAPI_ISteamHTMLSurface_FileLoadDialogResponse, ( ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, const char* * pchSelectedFiles ))
ice_steam_def_func(ISteamInventory*, SteamAPI_SteamInventory_v003, ())
ice_steam_def_func(ISteamInventory*, SteamAPI_SteamGameServerInventory_v003, ())
ice_steam_def_func(EResult, SteamAPI_ISteamInventory_GetResultStatus, ( ISteamInventory* self, SteamInventoryResult_t resultHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GetResultItems, ( ISteamInventory* self, SteamInventoryResult_t resultHandle, SteamItemDetails_t* pOutItemsArray, uint32* punOutItemsArraySize ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GetResultItemProperty, ( ISteamInventory* self, SteamInventoryResult_t resultHandle, uint32 unItemIndex, const char* pchPropertyName, char* pchValueBuffer, uint32* punValueBufferSizeOut ))
ice_steam_def_func(uint32, SteamAPI_ISteamInventory_GetResultTimestamp, ( ISteamInventory* self, SteamInventoryResult_t resultHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_CheckResultSteamID, ( ISteamInventory* self, SteamInventoryResult_t resultHandle, uint64_steamid steamIDExpected ))
ice_steam_def_func(void, SteamAPI_ISteamInventory_DestroyResult, ( ISteamInventory* self, SteamInventoryResult_t resultHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GetAllItems, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GetItemsByID, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, const SteamItemInstanceID_t* pInstanceIDs, uint32 unCountInstanceIDs ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_SerializeResult, ( ISteamInventory* self, SteamInventoryResult_t resultHandle, void* pOutBuffer, uint32* punOutBufferSize ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_DeserializeResult, ( ISteamInventory* self, SteamInventoryResult_t* pOutResultHandle, const void* pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GenerateItems, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayItemDefs, const uint32* punArrayQuantity, uint32 unArrayLength ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GrantPromoItems, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_AddPromoItem, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, SteamItemDef_t itemDef ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_AddPromoItems, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayItemDefs, uint32 unArrayLength ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_ConsumeItem, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, SteamItemInstanceID_t itemConsume, uint32 unQuantity ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_ExchangeItems, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayGenerate, const uint32* punArrayGenerateQuantity, uint32 unArrayGenerateLength, const SteamItemInstanceID_t* pArrayDestroy, const uint32* punArrayDestroyQuantity, uint32 unArrayDestroyLength ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_TransferItemQuantity, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, SteamItemInstanceID_t itemIdSource, uint32 unQuantity, SteamItemInstanceID_t itemIdDest ))
ice_steam_def_func(void, SteamAPI_ISteamInventory_SendItemDropHeartbeat, ( ISteamInventory* self ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_TriggerItemDrop, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, SteamItemDef_t dropListDefinition ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_TradeItems, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, uint64_steamid steamIDTradePartner, const SteamItemInstanceID_t* pArrayGive, const uint32* pArrayGiveQuantity, uint32 nArrayGiveLength, const SteamItemInstanceID_t* pArrayGet, const uint32* pArrayGetQuantity, uint32 nArrayGetLength ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_LoadItemDefinitions, ( ISteamInventory* self ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GetItemDefinitionIDs, ( ISteamInventory* self, SteamItemDef_t* pItemDefIDs, uint32* punItemDefIDsArraySize ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GetItemDefinitionProperty, ( ISteamInventory* self, SteamItemDef_t iDefinition, const char* pchPropertyName, char* pchValueBuffer, uint32* punValueBufferSizeOut ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs, ( ISteamInventory* self, uint64_steamid steamID ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs, ( ISteamInventory* self, uint64_steamid steamID, SteamItemDef_t* pItemDefIDs, uint32* punItemDefIDsArraySize ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamInventory_StartPurchase, ( ISteamInventory* self, const SteamItemDef_t* pArrayItemDefs, const uint32* punArrayQuantity, uint32 unArrayLength ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamInventory_RequestPrices, ( ISteamInventory* self ))
ice_steam_def_func(uint32, SteamAPI_ISteamInventory_GetNumItemsWithPrices, ( ISteamInventory* self ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GetItemsWithPrices, ( ISteamInventory* self, SteamItemDef_t* pArrayItemDefs, uint64* pCurrentPrices, uint64* pBasePrices, uint32 unArrayLength ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_GetItemPrice, ( ISteamInventory* self, SteamItemDef_t iDefinition, uint64* pCurrentPrice, uint64* pBasePrice ))
ice_steam_def_func(SteamInventoryUpdateHandle_t, SteamAPI_ISteamInventory_StartUpdateProperties, ( ISteamInventory* self ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_RemoveProperty, ( ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_SetPropertyString, ( ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, const char* pchPropertyValue ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_SetPropertyBool, ( ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, bool bValue ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_SetPropertyInt64, ( ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, int64 nValue ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_SetPropertyFloat, ( ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, float flValue ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_SubmitUpdateProperties, ( ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamInventoryResult_t* pResultHandle ))
ice_steam_def_func(bool, SteamAPI_ISteamInventory_InspectItem, ( ISteamInventory* self, SteamInventoryResult_t* pResultHandle, const char* pchItemToken ))
ice_steam_def_func(ISteamVideo*, SteamAPI_SteamVideo_v002, ())
ice_steam_def_func(void, SteamAPI_ISteamVideo_GetVideoURL, ( ISteamVideo* self, AppId_t unVideoAppID ))
ice_steam_def_func(bool, SteamAPI_ISteamVideo_IsBroadcasting, ( ISteamVideo* self, int* pnNumViewers ))
ice_steam_def_func(void, SteamAPI_ISteamVideo_GetOPFSettings, ( ISteamVideo* self, AppId_t unVideoAppID ))
ice_steam_def_func(bool, SteamAPI_ISteamVideo_GetOPFStringForApp, ( ISteamVideo* self, AppId_t unVideoAppID, char* pchBuffer, int32* pnBufferSize ))
ice_steam_def_func(ISteamParentalSettings*, SteamAPI_SteamParentalSettings_v001, ())
ice_steam_def_func(bool, SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled, ( ISteamParentalSettings* self ))
ice_steam_def_func(bool, SteamAPI_ISteamParentalSettings_BIsParentalLockLocked, ( ISteamParentalSettings* self ))
ice_steam_def_func(bool, SteamAPI_ISteamParentalSettings_BIsAppBlocked, ( ISteamParentalSettings* self, AppId_t nAppID ))
ice_steam_def_func(bool, SteamAPI_ISteamParentalSettings_BIsAppInBlockList, ( ISteamParentalSettings* self, AppId_t nAppID ))
ice_steam_def_func(bool, SteamAPI_ISteamParentalSettings_BIsFeatureBlocked, ( ISteamParentalSettings* self, EParentalFeature eFeature ))
ice_steam_def_func(bool, SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList, ( ISteamParentalSettings* self, EParentalFeature eFeature ))
ice_steam_def_func(ISteamRemotePlay*, SteamAPI_SteamRemotePlay_v001, ())
ice_steam_def_func(uint32, SteamAPI_ISteamRemotePlay_GetSessionCount, ( ISteamRemotePlay* self ))
ice_steam_def_func(RemotePlaySessionID_t, SteamAPI_ISteamRemotePlay_GetSessionID, ( ISteamRemotePlay* self, int iSessionIndex ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamRemotePlay_GetSessionSteamID, ( ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID ))
ice_steam_def_func(const char *, SteamAPI_ISteamRemotePlay_GetSessionClientName, ( ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID ))
ice_steam_def_func(ESteamDeviceFormFactor, SteamAPI_ISteamRemotePlay_GetSessionClientFormFactor, ( ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID ))
ice_steam_def_func(bool, SteamAPI_ISteamRemotePlay_BGetSessionClientResolution, ( ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID, int* pnResolutionX, int* pnResolutionY ))
ice_steam_def_func(bool, SteamAPI_ISteamRemotePlay_BSendRemotePlayTogetherInvite, ( ISteamRemotePlay* self, uint64_steamid steamIDFriend ))
ice_steam_def_func(ISteamNetworkingMessages*, SteamAPI_SteamNetworkingMessages_SteamAPI_v002, ())
ice_steam_def_func(ISteamNetworkingMessages*, SteamAPI_SteamGameServerNetworkingMessages_SteamAPI_v002, ())
ice_steam_def_func(EResult, SteamAPI_ISteamNetworkingMessages_SendMessageToUser, ( ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote, const void* pubData, uint32 cubData, int nSendFlags, int nRemoteChannel ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingMessages_ReceiveMessagesOnChannel, ( ISteamNetworkingMessages* self, int nLocalChannel, SteamNetworkingMessage_t* * ppOutMessages, int nMaxMessages ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingMessages_AcceptSessionWithUser, ( ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingMessages_CloseSessionWithUser, ( ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingMessages_CloseChannelWithUser, ( ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote, int nLocalChannel ))
ice_steam_def_func(ESteamNetworkingConnectionState, SteamAPI_ISteamNetworkingMessages_GetSessionConnectionInfo, ( ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote, SteamNetConnectionInfo_t* pConnectionInfo, SteamNetworkingQuickConnectionStatus* pQuickStatus ))
ice_steam_def_func(ISteamNetworkingSockets*, SteamAPI_SteamNetworkingSockets_SteamAPI_v011, ())
ice_steam_def_func(ISteamNetworkingSockets*, SteamAPI_SteamGameServerNetworkingSockets_SteamAPI_v011, ())
ice_steam_def_func(HSteamListenSocket, SteamAPI_ISteamNetworkingSockets_CreateListenSocketIP, ( ISteamNetworkingSockets* self, const SteamNetworkingIPAddr & localAddress, int nOptions, const SteamNetworkingConfigValue_t* pOptions ))
ice_steam_def_func(HSteamNetConnection, SteamAPI_ISteamNetworkingSockets_ConnectByIPAddress, ( ISteamNetworkingSockets* self, const SteamNetworkingIPAddr & address, int nOptions, const SteamNetworkingConfigValue_t* pOptions ))
ice_steam_def_func(HSteamListenSocket, SteamAPI_ISteamNetworkingSockets_CreateListenSocketP2P, ( ISteamNetworkingSockets* self, int nLocalVirtualPort, int nOptions, const SteamNetworkingConfigValue_t* pOptions ))
ice_steam_def_func(HSteamNetConnection, SteamAPI_ISteamNetworkingSockets_ConnectP2P, ( ISteamNetworkingSockets* self, const SteamNetworkingIdentity & identityRemote, int nRemoteVirtualPort, int nOptions, const SteamNetworkingConfigValue_t* pOptions ))
ice_steam_def_func(EResult, SteamAPI_ISteamNetworkingSockets_AcceptConnection, ( ISteamNetworkingSockets* self, HSteamNetConnection hConn ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_CloseConnection, ( ISteamNetworkingSockets* self, HSteamNetConnection hPeer, int nReason, const char* pszDebug, bool bEnableLinger ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_CloseListenSocket, ( ISteamNetworkingSockets* self, HSteamListenSocket hSocket ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_SetConnectionUserData, ( ISteamNetworkingSockets* self, HSteamNetConnection hPeer, int64 nUserData ))
ice_steam_def_func(int64, SteamAPI_ISteamNetworkingSockets_GetConnectionUserData, ( ISteamNetworkingSockets* self, HSteamNetConnection hPeer ))
ice_steam_def_func(void, SteamAPI_ISteamNetworkingSockets_SetConnectionName, ( ISteamNetworkingSockets* self, HSteamNetConnection hPeer, const char* pszName ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_GetConnectionName, ( ISteamNetworkingSockets* self, HSteamNetConnection hPeer, char* pszName, int nMaxLen ))
ice_steam_def_func(EResult, SteamAPI_ISteamNetworkingSockets_SendMessageToConnection, ( ISteamNetworkingSockets* self, HSteamNetConnection hConn, const void* pData, uint32 cbData, int nSendFlags, int64* pOutMessageNumber ))
ice_steam_def_func(void, SteamAPI_ISteamNetworkingSockets_SendMessages, ( ISteamNetworkingSockets* self, int nMessages, SteamNetworkingMessage_t* const* pMessages, int64* pOutMessageNumberOrResult ))
ice_steam_def_func(EResult, SteamAPI_ISteamNetworkingSockets_FlushMessagesOnConnection, ( ISteamNetworkingSockets* self, HSteamNetConnection hConn ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingSockets_ReceiveMessagesOnConnection, ( ISteamNetworkingSockets* self, HSteamNetConnection hConn, SteamNetworkingMessage_t* * ppOutMessages, int nMaxMessages ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_GetConnectionInfo, ( ISteamNetworkingSockets* self, HSteamNetConnection hConn, SteamNetConnectionInfo_t* pInfo ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_GetQuickConnectionStatus, ( ISteamNetworkingSockets* self, HSteamNetConnection hConn, SteamNetworkingQuickConnectionStatus* pStats ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingSockets_GetDetailedConnectionStatus, ( ISteamNetworkingSockets* self, HSteamNetConnection hConn, char* pszBuf, int cbBuf ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_GetListenSocketAddress, ( ISteamNetworkingSockets* self, HSteamListenSocket hSocket, SteamNetworkingIPAddr* address ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_CreateSocketPair, ( ISteamNetworkingSockets* self, HSteamNetConnection* pOutConnection1, HSteamNetConnection* pOutConnection2, bool bUseNetworkLoopback, const SteamNetworkingIdentity* pIdentity1, const SteamNetworkingIdentity* pIdentity2 ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_GetIdentity, ( ISteamNetworkingSockets* self, SteamNetworkingIdentity* pIdentity ))
ice_steam_def_func(ESteamNetworkingAvailability, SteamAPI_ISteamNetworkingSockets_InitAuthentication, ( ISteamNetworkingSockets* self ))
ice_steam_def_func(ESteamNetworkingAvailability, SteamAPI_ISteamNetworkingSockets_GetAuthenticationStatus, ( ISteamNetworkingSockets* self, SteamNetAuthenticationStatus_t* pDetails ))
ice_steam_def_func(HSteamNetPollGroup, SteamAPI_ISteamNetworkingSockets_CreatePollGroup, ( ISteamNetworkingSockets* self ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_DestroyPollGroup, ( ISteamNetworkingSockets* self, HSteamNetPollGroup hPollGroup ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_SetConnectionPollGroup, ( ISteamNetworkingSockets* self, HSteamNetConnection hConn, HSteamNetPollGroup hPollGroup ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingSockets_ReceiveMessagesOnPollGroup, ( ISteamNetworkingSockets* self, HSteamNetPollGroup hPollGroup, SteamNetworkingMessage_t* * ppOutMessages, int nMaxMessages ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_ReceivedRelayAuthTicket, ( ISteamNetworkingSockets* self, const void* pvTicket, int cbTicket, SteamDatagramRelayAuthTicket* pOutParsedTicket ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingSockets_FindRelayAuthTicketForServer, ( ISteamNetworkingSockets* self, const SteamNetworkingIdentity & identityGameServer, int nRemoteVirtualPort, SteamDatagramRelayAuthTicket* pOutParsedTicket ))
ice_steam_def_func(HSteamNetConnection, SteamAPI_ISteamNetworkingSockets_ConnectToHostedDedicatedServer, ( ISteamNetworkingSockets* self, const SteamNetworkingIdentity & identityTarget, int nRemoteVirtualPort, int nOptions, const SteamNetworkingConfigValue_t* pOptions ))
ice_steam_def_func(uint16, SteamAPI_ISteamNetworkingSockets_GetHostedDedicatedServerPort, ( ISteamNetworkingSockets* self ))
ice_steam_def_func(SteamNetworkingPOPID, SteamAPI_ISteamNetworkingSockets_GetHostedDedicatedServerPOPID, ( ISteamNetworkingSockets* self ))
ice_steam_def_func(EResult, SteamAPI_ISteamNetworkingSockets_GetHostedDedicatedServerAddress, ( ISteamNetworkingSockets* self, SteamDatagramHostedAddress* pRouting ))
ice_steam_def_func(HSteamListenSocket, SteamAPI_ISteamNetworkingSockets_CreateHostedDedicatedServerListenSocket, ( ISteamNetworkingSockets* self, int nLocalVirtualPort, int nOptions, const SteamNetworkingConfigValue_t* pOptions ))
ice_steam_def_func(EResult, SteamAPI_ISteamNetworkingSockets_GetGameCoordinatorServerLogin, ( ISteamNetworkingSockets* self, SteamDatagramGameCoordinatorServerLogin* pLoginInfo, int* pcbSignedBlob, void* pBlob ))
ice_steam_def_func(HSteamNetConnection, SteamAPI_ISteamNetworkingSockets_ConnectP2PCustomSignaling, ( ISteamNetworkingSockets* self, ISteamNetworkingConnectionSignaling* pSignaling, const SteamNetworkingIdentity* pPeerIdentity, int nRemoteVirtualPort, int nOptions, const SteamNetworkingConfigValue_t* pOptions ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_ReceivedP2PCustomSignal, ( ISteamNetworkingSockets* self, const void* pMsg, int cbMsg, ISteamNetworkingSignalingRecvContext* pContext ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_GetCertificateRequest, ( ISteamNetworkingSockets* self, int* pcbBlob, void* pBlob, SteamNetworkingErrMsg & errMsg ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingSockets_SetCertificate, ( ISteamNetworkingSockets* self, const void* pCertificate, int cbCertificate, SteamNetworkingErrMsg & errMsg ))
ice_steam_def_func(void, SteamAPI_ISteamNetworkingSockets_ResetIdentity, ( ISteamNetworkingSockets* self, const SteamNetworkingIdentity* pIdentity ))
ice_steam_def_func(void, SteamAPI_ISteamNetworkingSockets_RunCallbacks, ( ISteamNetworkingSockets* self ))
ice_steam_def_func(ISteamNetworkingUtils*, SteamAPI_SteamNetworkingUtils_SteamAPI_v004, ())
ice_steam_def_func(SteamNetworkingMessage_t*, SteamAPI_ISteamNetworkingUtils_AllocateMessage, ( ISteamNetworkingUtils* self, int cbAllocateBuffer ))
ice_steam_def_func(void, SteamAPI_ISteamNetworkingUtils_InitRelayNetworkAccess, ( ISteamNetworkingUtils* self ))
ice_steam_def_func(ESteamNetworkingAvailability, SteamAPI_ISteamNetworkingUtils_GetRelayNetworkStatus, ( ISteamNetworkingUtils* self, SteamRelayNetworkStatus_t* pDetails ))
ice_steam_def_func(float, SteamAPI_ISteamNetworkingUtils_GetLocalPingLocation, ( ISteamNetworkingUtils* self, SteamNetworkPingLocation_t & result ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingUtils_EstimatePingTimeBetweenTwoLocations, ( ISteamNetworkingUtils* self, const SteamNetworkPingLocation_t & location1, const SteamNetworkPingLocation_t & location2 ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingUtils_EstimatePingTimeFromLocalHost, ( ISteamNetworkingUtils* self, const SteamNetworkPingLocation_t & remoteLocation ))
ice_steam_def_func(void, SteamAPI_ISteamNetworkingUtils_ConvertPingLocationToString, ( ISteamNetworkingUtils* self, const SteamNetworkPingLocation_t & location, char* pszBuf, int cchBufSize ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_ParsePingLocationString, ( ISteamNetworkingUtils* self, const char* pszString, SteamNetworkPingLocation_t & result ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_CheckPingDataUpToDate, ( ISteamNetworkingUtils* self, float flMaxAgeSeconds ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingUtils_GetPingToDataCenter, ( ISteamNetworkingUtils* self, SteamNetworkingPOPID popID, SteamNetworkingPOPID* pViaRelayPoP ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingUtils_GetDirectPingToPOP, ( ISteamNetworkingUtils* self, SteamNetworkingPOPID popID ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingUtils_GetPOPCount, ( ISteamNetworkingUtils* self ))
ice_steam_def_func(int, SteamAPI_ISteamNetworkingUtils_GetPOPList, ( ISteamNetworkingUtils* self, SteamNetworkingPOPID* list, int nListSz ))
ice_steam_def_func(SteamNetworkingMicroseconds, SteamAPI_ISteamNetworkingUtils_GetLocalTimestamp, ( ISteamNetworkingUtils* self ))
ice_steam_def_func(void, SteamAPI_ISteamNetworkingUtils_SetDebugOutputFunction, ( ISteamNetworkingUtils* self, ESteamNetworkingSocketsDebugOutputType eDetailLevel, FSteamNetworkingSocketsDebugOutput pfnFunc ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetGlobalConfigValueInt32, ( ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, int32 val ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetGlobalConfigValueFloat, ( ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, float val ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetGlobalConfigValueString, ( ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, const char* val ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetGlobalConfigValuePtr, ( ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, void* val ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetConnectionConfigValueInt32, ( ISteamNetworkingUtils* self, HSteamNetConnection hConn, ESteamNetworkingConfigValue eValue, int32 val ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetConnectionConfigValueFloat, ( ISteamNetworkingUtils* self, HSteamNetConnection hConn, ESteamNetworkingConfigValue eValue, float val ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetConnectionConfigValueString, ( ISteamNetworkingUtils* self, HSteamNetConnection hConn, ESteamNetworkingConfigValue eValue, const char* val ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_SteamNetConnectionStatusChanged, ( ISteamNetworkingUtils* self, FnSteamNetConnectionStatusChanged fnCallback ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_SteamNetAuthenticationStatusChanged, ( ISteamNetworkingUtils* self, FnSteamNetAuthenticationStatusChanged fnCallback ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_SteamRelayNetworkStatusChanged, ( ISteamNetworkingUtils* self, FnSteamRelayNetworkStatusChanged fnCallback ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_MessagesSessionRequest, ( ISteamNetworkingUtils* self, FnSteamNetworkingMessagesSessionRequest fnCallback ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_MessagesSessionFailed, ( ISteamNetworkingUtils* self, FnSteamNetworkingMessagesSessionFailed fnCallback ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetConfigValue, ( ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, ESteamNetworkingConfigScope eScopeType, intptr_t scopeObj, ESteamNetworkingConfigDataType eDataType, const void* pArg ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SetConfigValueStruct, ( ISteamNetworkingUtils* self, const SteamNetworkingConfigValue_t & opt, ESteamNetworkingConfigScope eScopeType, intptr_t scopeObj ))
ice_steam_def_func(ESteamNetworkingGetConfigValueResult, SteamAPI_ISteamNetworkingUtils_GetConfigValue, ( ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, ESteamNetworkingConfigScope eScopeType, intptr_t scopeObj, ESteamNetworkingConfigDataType* pOutDataType, void* pResult, size_t* cbResult ))
ice_steam_def_func(const char *, SteamAPI_ISteamNetworkingUtils_GetConfigValueInfo, ( ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, ESteamNetworkingConfigDataType* pOutDataType, ESteamNetworkingConfigScope* pOutScope ))
ice_steam_def_func(ESteamNetworkingConfigValue, SteamAPI_ISteamNetworkingUtils_IterateGenericEditableConfigValues, ( ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eCurrent, bool bEnumerateDevVars ))
ice_steam_def_func(void, SteamAPI_ISteamNetworkingUtils_SteamNetworkingIPAddr_ToString, ( ISteamNetworkingUtils* self, const SteamNetworkingIPAddr & addr, char* buf, uint32 cbBuf, bool bWithPort ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SteamNetworkingIPAddr_ParseString, ( ISteamNetworkingUtils* self, SteamNetworkingIPAddr* pAddr, const char* pszStr ))
ice_steam_def_func(void, SteamAPI_ISteamNetworkingUtils_SteamNetworkingIdentity_ToString, ( ISteamNetworkingUtils* self, const SteamNetworkingIdentity & identity, char* buf, uint32 cbBuf ))
ice_steam_def_func(bool, SteamAPI_ISteamNetworkingUtils_SteamNetworkingIdentity_ParseString, ( ISteamNetworkingUtils* self, SteamNetworkingIdentity* pIdentity, const char* pszStr ))
ice_steam_def_func(ISteamGameServer*, SteamAPI_SteamGameServer_v014, ())
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetProduct, ( ISteamGameServer* self, const char* pszProduct ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetGameDescription, ( ISteamGameServer* self, const char* pszGameDescription ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetModDir, ( ISteamGameServer* self, const char* pszModDir ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetDedicatedServer, ( ISteamGameServer* self, bool bDedicated ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_LogOn, ( ISteamGameServer* self, const char* pszToken ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_LogOnAnonymous, ( ISteamGameServer* self ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_LogOff, ( ISteamGameServer* self ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServer_BLoggedOn, ( ISteamGameServer* self ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServer_BSecure, ( ISteamGameServer* self ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamGameServer_GetSteamID, ( ISteamGameServer* self ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServer_WasRestartRequested, ( ISteamGameServer* self ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetMaxPlayerCount, ( ISteamGameServer* self, int cPlayersMax ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetBotPlayerCount, ( ISteamGameServer* self, int cBotplayers ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetServerName, ( ISteamGameServer* self, const char* pszServerName ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetMapName, ( ISteamGameServer* self, const char* pszMapName ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetPasswordProtected, ( ISteamGameServer* self, bool bPasswordProtected ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetSpectatorPort, ( ISteamGameServer* self, uint16 unSpectatorPort ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetSpectatorServerName, ( ISteamGameServer* self, const char* pszSpectatorServerName ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_ClearAllKeyValues, ( ISteamGameServer* self ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetKeyValue, ( ISteamGameServer* self, const char* pKey, const char* pValue ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetGameTags, ( ISteamGameServer* self, const char* pchGameTags ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetGameData, ( ISteamGameServer* self, const char* pchGameData ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetRegion, ( ISteamGameServer* self, const char* pszRegion ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SetAdvertiseServerActive, ( ISteamGameServer* self, bool bActive ))
ice_steam_def_func(HAuthTicket, SteamAPI_ISteamGameServer_GetAuthSessionTicket, ( ISteamGameServer* self, void* pTicket, int cbMaxTicket, uint32* pcbTicket ))
ice_steam_def_func(EBeginAuthSessionResult, SteamAPI_ISteamGameServer_BeginAuthSession, ( ISteamGameServer* self, const void* pAuthTicket, int cbAuthTicket, uint64_steamid steamID ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_EndAuthSession, ( ISteamGameServer* self, uint64_steamid steamID ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_CancelAuthTicket, ( ISteamGameServer* self, HAuthTicket hAuthTicket ))
ice_steam_def_func(EUserHasLicenseForAppResult, SteamAPI_ISteamGameServer_UserHasLicenseForApp, ( ISteamGameServer* self, uint64_steamid steamID, AppId_t appID ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServer_RequestUserGroupStatus, ( ISteamGameServer* self, uint64_steamid steamIDUser, uint64_steamid steamIDGroup ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_GetGameplayStats, ( ISteamGameServer* self ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamGameServer_GetServerReputation, ( ISteamGameServer* self ))
ice_steam_def_func(SteamIPAddress_t, SteamAPI_ISteamGameServer_GetPublicIP, ( ISteamGameServer* self ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServer_HandleIncomingPacket, ( ISteamGameServer* self, const void* pData, int cbData, uint32 srcIP, uint16 srcPort ))
ice_steam_def_func(int, SteamAPI_ISteamGameServer_GetNextOutgoingPacket, ( ISteamGameServer* self, void* pOut, int cbMaxOut, uint32* pNetAdr, uint16* pPort ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamGameServer_AssociateWithClan, ( ISteamGameServer* self, uint64_steamid steamIDClan ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility, ( ISteamGameServer* self, uint64_steamid steamIDNewPlayer ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate_DEPRECATED, ( ISteamGameServer* self, uint32 unIPClient, const void* pvAuthBlob, uint32 cubAuthBlobSize, CSteamID* pSteamIDUser ))
ice_steam_def_func(uint64_steamid, SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection, ( ISteamGameServer* self ))
ice_steam_def_func(void, SteamAPI_ISteamGameServer_SendUserDisconnect_DEPRECATED, ( ISteamGameServer* self, uint64_steamid steamIDUser ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServer_BUpdateUserData, ( ISteamGameServer* self, uint64_steamid steamIDUser, const char* pchPlayerName, uint32 uScore ))
ice_steam_def_func(ISteamGameServerStats*, SteamAPI_SteamGameServerStats_v001, ())
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamGameServerStats_RequestUserStats, ( ISteamGameServerStats* self, uint64_steamid steamIDUser ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServerStats_GetUserStatInt32, ( ISteamGameServerStats* self, uint64_steamid steamIDUser, const char* pchName, int32* pData ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServerStats_GetUserStatFloat, ( ISteamGameServerStats* self, uint64_steamid steamIDUser, const char* pchName, float* pData ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServerStats_GetUserAchievement, ( ISteamGameServerStats* self, uint64_steamid steamIDUser, const char* pchName, bool* pbAchieved ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServerStats_SetUserStatInt32, ( ISteamGameServerStats* self, uint64_steamid steamIDUser, const char* pchName, int32 nData ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServerStats_SetUserStatFloat, ( ISteamGameServerStats* self, uint64_steamid steamIDUser, const char* pchName, float fData ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat, ( ISteamGameServerStats* self, uint64_steamid steamIDUser, const char* pchName, float flCountThisSession, double dSessionLength ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServerStats_SetUserAchievement, ( ISteamGameServerStats* self, uint64_steamid steamIDUser, const char* pchName ))
ice_steam_def_func(bool, SteamAPI_ISteamGameServerStats_ClearUserAchievement, ( ISteamGameServerStats* self, uint64_steamid steamIDUser, const char* pchName ))
ice_steam_def_func(SteamAPICall_t, SteamAPI_ISteamGameServerStats_StoreUserStats, ( ISteamGameServerStats* self, uint64_steamid steamIDUser ))
ice_steam_def_func(bool, SteamAPI_SteamIPAddress_t_IsSet, ( SteamIPAddress_t* self ))
ice_steam_def_func(void, SteamAPI_MatchMakingKeyValuePair_t_Construct, ( MatchMakingKeyValuePair_t* self ))
ice_steam_def_func(void, SteamAPI_servernetadr_t_Construct, ( servernetadr_t* self ))
ice_steam_def_func(void, SteamAPI_servernetadr_t_Init, ( servernetadr_t* self, unsigned int ip, uint16 usQueryPort, uint16 usConnectionPort ))
ice_steam_def_func(uint16, SteamAPI_servernetadr_t_GetQueryPort, ( servernetadr_t* self ))
ice_steam_def_func(void, SteamAPI_servernetadr_t_SetQueryPort, ( servernetadr_t* self, uint16 usPort ))
ice_steam_def_func(uint16, SteamAPI_servernetadr_t_GetConnectionPort, ( servernetadr_t* self ))
ice_steam_def_func(void, SteamAPI_servernetadr_t_SetConnectionPort, ( servernetadr_t* self, uint16 usPort ))
ice_steam_def_func(uint32, SteamAPI_servernetadr_t_GetIP, ( servernetadr_t* self ))
ice_steam_def_func(void, SteamAPI_servernetadr_t_SetIP, ( servernetadr_t* self, uint32 unIP ))
ice_steam_def_func(const char *, SteamAPI_servernetadr_t_GetConnectionAddressString, ( servernetadr_t* self ))
ice_steam_def_func(const char *, SteamAPI_servernetadr_t_GetQueryAddressString, ( servernetadr_t* self ))
ice_steam_def_func(bool, SteamAPI_servernetadr_t_IsLessThan, ( servernetadr_t* self, const servernetadr_t & netadr ))
ice_steam_def_func(void, SteamAPI_servernetadr_t_Assign, ( servernetadr_t* self, const servernetadr_t & that ))
ice_steam_def_func(void, SteamAPI_gameserveritem_t_Construct, ( gameserveritem_t* self ))
ice_steam_def_func(const char *, SteamAPI_gameserveritem_t_GetName, ( gameserveritem_t* self ))
ice_steam_def_func(void, SteamAPI_gameserveritem_t_SetName, ( gameserveritem_t* self, const char* pName ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIPAddr_Clear, ( SteamNetworkingIPAddr* self ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIPAddr_IsIPv6AllZeros, ( SteamNetworkingIPAddr* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIPAddr_SetIPv6, ( SteamNetworkingIPAddr* self, const uint8* ipv6, uint16 nPort ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIPAddr_SetIPv4, ( SteamNetworkingIPAddr* self, uint32 nIP, uint16 nPort ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIPAddr_IsIPv4, ( SteamNetworkingIPAddr* self ))
ice_steam_def_func(uint32, SteamAPI_SteamNetworkingIPAddr_GetIPv4, ( SteamNetworkingIPAddr* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIPAddr_SetIPv6LocalHost, ( SteamNetworkingIPAddr* self, uint16 nPort ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIPAddr_IsLocalHost, ( SteamNetworkingIPAddr* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIPAddr_ToString, ( SteamNetworkingIPAddr* self, char* buf, uint32 cbBuf, bool bWithPort ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIPAddr_ParseString, ( SteamNetworkingIPAddr* self, const char* pszStr ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIPAddr_IsEqualTo, ( SteamNetworkingIPAddr* self, const SteamNetworkingIPAddr & x ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIdentity_Clear, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIdentity_IsInvalid, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIdentity_SetSteamID, ( SteamNetworkingIdentity* self, uint64_steamid steamID ))
ice_steam_def_func(uint64_steamid, SteamAPI_SteamNetworkingIdentity_GetSteamID, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIdentity_SetSteamID64, ( SteamNetworkingIdentity* self, uint64 steamID ))
ice_steam_def_func(uint64, SteamAPI_SteamNetworkingIdentity_GetSteamID64, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIdentity_SetXboxPairwiseID, ( SteamNetworkingIdentity* self, const char* pszString ))
ice_steam_def_func(const char *, SteamAPI_SteamNetworkingIdentity_GetXboxPairwiseID, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIdentity_SetPSNID, ( SteamNetworkingIdentity* self, uint64 id ))
ice_steam_def_func(uint64, SteamAPI_SteamNetworkingIdentity_GetPSNID, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIdentity_SetStadiaID, ( SteamNetworkingIdentity* self, uint64 id ))
ice_steam_def_func(uint64, SteamAPI_SteamNetworkingIdentity_GetStadiaID, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIdentity_SetIPAddr, ( SteamNetworkingIdentity* self, const SteamNetworkingIPAddr & addr ))
ice_steam_def_func(const SteamNetworkingIPAddr*, SteamAPI_SteamNetworkingIdentity_GetIPAddr, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIdentity_SetLocalHost, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIdentity_IsLocalHost, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIdentity_SetGenericString, ( SteamNetworkingIdentity* self, const char* pszString ))
ice_steam_def_func(const char *, SteamAPI_SteamNetworkingIdentity_GetGenericString, ( SteamNetworkingIdentity* self ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIdentity_SetGenericBytes, ( SteamNetworkingIdentity* self, const void* data, uint32 cbLen ))
ice_steam_def_func(const uint8 *, SteamAPI_SteamNetworkingIdentity_GetGenericBytes, ( SteamNetworkingIdentity* self, int & cbLen ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIdentity_IsEqualTo, ( SteamNetworkingIdentity* self, const SteamNetworkingIdentity & x ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingIdentity_ToString, ( SteamNetworkingIdentity* self, char* buf, uint32 cbBuf ))
ice_steam_def_func(bool, SteamAPI_SteamNetworkingIdentity_ParseString, ( SteamNetworkingIdentity* self, const char* pszStr ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingMessage_t_Release, ( SteamNetworkingMessage_t* self ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingConfigValue_t_SetInt32, ( SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, int32_t data ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingConfigValue_t_SetInt64, ( SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, int64_t data ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingConfigValue_t_SetFloat, ( SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, float data ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingConfigValue_t_SetPtr, ( SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, void* data ))
ice_steam_def_func(void, SteamAPI_SteamNetworkingConfigValue_t_SetString, ( SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, const char* data ))
ice_steam_def_func(const char *, SteamAPI_SteamNetworkingPOPIDRender_c_str, ( SteamNetworkingPOPIDRender* self ))
ice_steam_def_func(const char *, SteamAPI_SteamNetworkingIdentityRender_c_str, ( SteamNetworkingIdentityRender* self ))
ice_steam_def_func(const char *, SteamAPI_SteamNetworkingIPAddrRender_c_str, ( SteamNetworkingIPAddrRender* self ))
ice_steam_def_func(void, SteamAPI_SteamDatagramHostedAddress_Clear, ( SteamDatagramHostedAddress* self ))
ice_steam_def_func(SteamNetworkingPOPID, SteamAPI_SteamDatagramHostedAddress_GetPopID, ( SteamDatagramHostedAddress* self ))
ice_steam_def_func(void, SteamAPI_SteamDatagramHostedAddress_SetDevAddress, ( SteamDatagramHostedAddress* self, uint32 nIP, uint16 nPort, SteamNetworkingPOPID popid ))
ice_steam_def_func(bool, SteamAPI_Init, ())
ice_steam_def_func(void, SteamAPI_Shutdown, ())
ice_steam_def_func(bool, SteamAPI_RestartAppIfNecessary, ( uint32 unOwnAppID ))
ice_steam_def_func(void, SteamAPI_ReleaseCurrentThreadMemory, ())
ice_steam_def_func(void, SteamAPI_WriteMiniDump, ( uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID ))
ice_steam_def_func(void, SteamAPI_SetMiniDumpComment, ( const char *pchMsg ))
ice_steam_def_func(bool, SteamAPI_IsSteamRunning, ())
ice_steam_def_func(const char *, SteamAPI_GetSteamInstallPath, ())
ice_steam_def_func(void, SteamAPI_SetTryCatchCallbacks, ( bool bTryCatchCallbacks ))
ice_steam_def_func(bool, SteamAPI_InitSafe, ())
ice_steam_def_func(void, SteamAPI_UseBreakpadCrashHandler, ( char const *pchVersion, char const *pchDate, char const *pchTime, bool bFullMemoryDumps, void *pvContext, PFNPreMinidumpCallback m_pfnPreMinidumpCallback ))
ice_steam_def_func(void, SteamAPI_SetBreakpadAppID, ( uint32 unAppID ))
ice_steam_def_func(void, SteamAPI_ManualDispatch_Init, ())
ice_steam_def_func(void, SteamAPI_ManualDispatch_RunFrame, ( HSteamPipe hSteamPipe ))
ice_steam_def_func(bool, SteamAPI_ManualDispatch_GetNextCallback, ( HSteamPipe hSteamPipe, CallbackMsg_t *pCallbackMsg ))
ice_steam_def_func(void, SteamAPI_ManualDispatch_FreeLastCallback, ( HSteamPipe hSteamPipe ))
ice_steam_def_func(bool, SteamAPI_ManualDispatch_GetAPICallResult, ( HSteamPipe hSteamPipe, SteamAPICall_t hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed ))

/* Handle, Type definition for void* for symbols loaded from shared libs */
typedef void* ice_steam_handle;

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_steam_bool {
    ICE_STEAM_FALSE = -1,
    ICE_STEAM_TRUE = 0
} ice_steam_bool;

/* [INTERNAL] Loads symbol from loaded SteamWorks SDK shared library, Which can be casted to a function to call */
ICE_STEAM_API ice_steam_handle ICE_STEAM_CALLCONV ice_steam_proc(const char* symbol);

/* Loads SteamWorks API from shared library path (eg. steam_api.dll on Windows), Returns ICE_STEAM_TRUE on success or ICE_STEAM_FALSE on failure */
ICE_STEAM_API ice_steam_bool ICE_STEAM_CALLCONV ice_steam_load(const char* path);

/* Unloads SteamWorks API, Returns ICE_STEAM_TRUE on success or ICE_STEAM_FALSE on failure */
ICE_STEAM_API ice_steam_bool ICE_STEAM_CALLCONV ice_steam_unload(void);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_STEAM_IMPL)

#include <assert.h>

#if defined(ICE_STEAM_MICROSOFT)
#  if defined(_MSC_VER)
#    include <windows.h>
#    pragma comment(lib, "kernel32.lib")
#  else
#    include <libloaderapi.h>
#  endif
#elif defined(ICE_STEAM_BEOS)
#  include <be/kernel/image.h>
#elif defined(ICE_STEAM_UNIX)
#  include <dlfcn.h>
#endif

static ice_steam_handle ice_steam_lib;

/* [INTERNAL] Loads symbol from loaded SteamWorks SDK shared library, Which can be casted to a function to call */
ICE_STEAM_API ice_steam_handle ICE_STEAM_CALLCONV ice_steam_proc(const char* symbol) {
    ice_steam_handle sym = NULL;
#if defined(ICE_STEAM_MICROSOFT)
    sym = GetProcAddress(ice_steam_lib, symbol);
#elif defined(ICE_STEAM_BEOS)
    if (get_image_symbol((isize) ice_steam_lib, symbol, B_SYMBOL_TYPE_ANY, &sym) != B_OK) {
        sym = NULL;
    }
#elif defined(ICE_STEAM_UNIX)
    sym = dlsym(ice_steam_lib, symbol);
#endif
    assert((ice_steam_handle) sym != NULL);
    return sym;
}

#endif  /* ICE_STEAM_IMPL */
#endif  /* ICE_STEAM_H */


/*
ice_steam.h is dual-licensed, Choose the one you prefer!

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
Copyright (c) 2021 - 2022 Rabia Alhaffar

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
