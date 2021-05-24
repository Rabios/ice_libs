// Written by Rabia Alhaffar in 14/April/2021
// ice_fs.h
// Single-Header Cross-Platform C library for working with filesystems (File, Dir, etc...)
// Updated: 25/May/2021

// Special thanks to Toni Ronkko for Windows version of dirent.h

///////////////////////////////////////////////////////////////////////////////////////////
// ice_fs.h (FULL OVERVIEW)
///////////////////////////////////////////////////////////////////////////////////////////
/*
[1] BRIEF:
ice_fs is cross-platform single-header C library for working with filesystems.

[2] USAGE:
Define ICE_FS_IMPL Then include ice_fs.h in your C/C++ code!
*/

///////////////////////////////////////////////////////////////////////////////////////////
// SUPPORT OR CONTRIBUTE TO ice_fs
///////////////////////////////////////////////////////////////////////////////////////////
// You could support or contribute ice_fs by possibly one of following things:
//
// 1. Test ice_fs on each platform!
// 2. Add support to more platforms and backends!
// 3. Request or add more possible features!
// 4. Fix bugs/problems in the library!
// 5. Use it in one of your projects!
// 6. Star the repo on GitHub -> https://github.com/Rabios/ice_libs
//

///////////////////////////////////////////////////////////////////////////////////////////
// ice_fs LICENSE
///////////////////////////////////////////////////////////////////////////////////////////
/*
ice_fs is dual-licensed, Choose the one you prefer!

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

#ifndef ICE_FS_H
#define ICE_FS_H

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

// Allow to use calling conventions if desired...
#if defined(__GNUC__) || defined(__GNUG__)
#  if defined(ICE_FS_CALLCONV_VECTORCALL)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!"
#  elif defined(ICE_FS_CALLCONV_FASTCALL)
#    define ICE_FS_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_FS_CALLCONV_STDCALL)
#    define ICE_FS_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_FS_CALLCONV_CDECL)
#    define ICE_FS_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_FS_CALLCONV
#  endif
#elif defined(__clang)
#  if defined(ICE_FS_CALLCONV_VECTORCALL)
#    define ICE_FS_CALLCONV __attribute__((vectorcall))
#  elif defined(ICE_FS_CALLCONV_FASTCALL)
#    define ICE_FS_CALLCONV __attribute__((fastcall))
#  elif defined(ICE_FS_CALLCONV_STDCALL)
#    define ICE_FS_CALLCONV __attribute__((stdcall))
#  elif defined(ICE_FS_CALLCONV_CDECL)
#    define ICE_FS_CALLCONV __attribute__((cdecl))
#  else
#    define ICE_FS_CALLCONV
#  endif
#elif defined(_MSC_VER)
#  if defined(ICE_FS_CALLCONV_VECTORCALL)
#    define ICE_FS_CALLCONV __vectorcall
#  elif defined(ICE_FS_CALLCONV_FASTCALL)
#    define ICE_FS_CALLCONV __fastcall
#  elif defined(ICE_FS_CALLCONV_STDCALL)
#    define ICE_FS_CALLCONV __stdcall
#  elif defined(ICE_FS_CALLCONV_CDECL)
#    define ICE_FS_CALLCONV __cdecl
#  else
#    define ICE_FS_CALLCONV
#  endif
#else
#  define ICE_FS_CALLCONV
#endif

// If no platform defined, This definition will define itself!
#if !(defined(ICE_FS_MICROSOFT) || defined(ICE_FS_UNIX))
#  define ICE_FS_PLATFORM_AUTODETECTED
#endif

// Platform detection
#if defined(ICE_FS_PLATFORM_AUTODETECTED)
#  if defined(__WIN) || defined(_WIN32_) || defined(_WIN64_) || defined(WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64__) || defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_MSC_VER) || defined(__WINDOWS__) || defined(_X360) || defined(XBOX360) || defined(__X360) || defined(__X360__) || defined(_XBOXONE) || defined(XBONE) || defined(XBOX) || defined(__XBOX__) || defined(__XBOX) || defined(__xbox__) || defined(__xbox) || defined(_XBOX) || defined(xbox) || ((defined(_XBOX_ONE) || defined(_DURANGO)) && defined(_TITLE))
#    define ICE_FS_MICROSOFT
#  else
#    define ICE_FS_UNIX
#  endif
#endif

// Allow to use them as extern functions if desired!
// NOTE: extern functions cannot be static so we disable static keyword.
#if !(defined(ICE_FS_EXTERN) && defined(ICE_FS_STATIC))
#  define ICE_FS_EXTERN
#endif

#if defined(ICE_FS_EXTERN)
#  define ICE_FS_APIDEF extern
#elif defined(ICE_FS_STATIC)
#  define ICE_FS_APIDEF static
#endif

// If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!
// NOTE: Use ICE_FS_INLINE to enable inline functionality.
#if defined(ICE_FS_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_FS_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_FS_INLINEDEF inline
#  endif
#else
#  define ICE_FS_INLINEDEF
#endif

// Allow to build DLL via ICE_FS_DLLEXPORT or ICE_FS_DLLIMPORT if desired!
// Else, Just define API as extern C code!
#if defined(ICE_FS_MICROSOFT)
#  if defined(ICE_FS_DLLEXPORT)
#    define ICE_FS_API __declspec(dllexport) ICE_FS_INLINEDEF
#  elif defined(ICE_FS_DLLIMPORT)
#    define ICE_FS_API __declspec(dllimport) ICE_FS_INLINEDEF
#  else
#    define ICE_FS_API ICE_FS_APIDEF ICE_FS_INLINEDEF
#  endif
#else
#  define ICE_FS_API ICE_FS_APIDEF ICE_FS_INLINEDEF
#endif

// Custom memory allocators
#ifndef ICE_FS_MALLOC
#  define ICE_FS_MALLOC(sz) malloc(sz)
#endif
#ifndef ICE_FS_CALLOC
#  define ICE_FS_CALLOC(n, sz) calloc(n, sz)
#endif
#ifndef ICE_FS_REALLOC
#  define ICE_FS_REALLOC(ptr, sz) realloc(ptr, sz)
#endif
#ifndef ICE_FS_FREE
#  define ICE_FS_FREE(ptr) free(ptr)
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_fs DEFINITIONS
//////////////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ICE_FS_TRUE    = 0,
    ICE_FS_FALSE   = -1,
} ice_fs_bool;

///////////////////////////////////////////////////////////////////////////////////////////
// ice_fs FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_home(void);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_root(char* f);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_current_dir(void);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_previous_dir(char* dir);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_file_dir(char* dir);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_change_dir(char* dir);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_remove_dir(char* dir);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_copy_dir(char* d1, char* d2);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_remove_file(char* dir);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_rename_file(char* d1, char* d2);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_rename_dir(char* d1, char* d2);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_copy_file(char* d1, char* d2);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_dir(char* dir);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_join_dir(char* d1, char* d2);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_join_dirs(char** dirs);
ICE_FS_API  char**       ICE_FS_CALLCONV  ice_fs_split_dir(char* dir, char delim);
ICE_FS_API  char**       ICE_FS_CALLCONV  ice_fs_dir_list(char* dir);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_dir_exists(char* dir);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_create_dir(char* dir);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_is_file(char* dir);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_is_dir(char* dir);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_create_file(char* name);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_write(char* name, char* content);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_clear(char* name);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_file_exists(char* fname);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_full_file_path(char* fname);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_is_file_ext(char* fname, char* ext);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_file_ext(char* fname);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_file_name(char* dir);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_dir_name(char* dir);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_name_no_ext(char* fname);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_get_line(char* fname, int l);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_edit_line(char* fname, int l, char* content);
ICE_FS_API  ice_fs_bool  ICE_FS_CALLCONV  ice_fs_remove_line(char* fname, int l);
ICE_FS_API  char**       ICE_FS_CALLCONV  ice_fs_lines(char* fname);
ICE_FS_API  int          ICE_FS_CALLCONV  ice_fs_lines_count(char* fname);
ICE_FS_API  char*        ICE_FS_CALLCONV  ice_fs_file_content(char* fname);

#if defined(__cplusplus)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////
// ice_fs IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////
#if defined(ICE_FS_IMPL)
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <limits.h>

#if defined(ICE_FS_MICROSOFT)
#  include <windows.h>

/*
 * Dirent interface for Microsoft Visual Studio
 *
 * Copyright (C) 1998-2019 Toni Ronkko
 * This file is part of dirent.  Dirent may be freely distributed
 * under the MIT license.  For all details and documentation, see
 * https://github.com/tronkko/dirent
 */
#ifndef DIRENT_H
#define DIRENT_H

/* Hide warnings about unreferenced local functions */
#if defined(__clang__)
#	pragma clang diagnostic ignored "-Wunused-function"
#elif defined(_MSC_VER)
#	pragma warning(disable:4505)
#elif defined(__GNUC__)
#	pragma GCC diagnostic ignored "-Wunused-function"
#endif

/*
 * Include windows.h without Windows Sockets 1.1 to prevent conflicts with
 * Windows Sockets 2.0.
 */
#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

/* Indicates that d_type field is available in dirent structure */
#define _DIRENT_HAVE_D_TYPE

/* Indicates that d_namlen field is available in dirent structure */
#define _DIRENT_HAVE_D_NAMLEN

/* Entries missing from MSVC 6.0 */
#if !defined(FILE_ATTRIBUTE_DEVICE)
#	define FILE_ATTRIBUTE_DEVICE 0x40
#endif

/* File type and permission flags for stat(), general mask */
#if !defined(S_IFMT)
#	define S_IFMT _S_IFMT
#endif

/* Directory bit */
#if !defined(S_IFDIR)
#	define S_IFDIR _S_IFDIR
#endif

/* Character device bit */
#if !defined(S_IFCHR)
#	define S_IFCHR _S_IFCHR
#endif

/* Pipe bit */
#if !defined(S_IFFIFO)
#	define S_IFFIFO _S_IFFIFO
#endif

/* Regular file bit */
#if !defined(S_IFREG)
#	define S_IFREG _S_IFREG
#endif

/* Read permission */
#if !defined(S_IREAD)
#	define S_IREAD _S_IREAD
#endif

/* Write permission */
#if !defined(S_IWRITE)
#	define S_IWRITE _S_IWRITE
#endif

/* Execute permission */
#if !defined(S_IEXEC)
#	define S_IEXEC _S_IEXEC
#endif

/* Pipe */
#if !defined(S_IFIFO)
#	define S_IFIFO _S_IFIFO
#endif

/* Block device */
#if !defined(S_IFBLK)
#	define S_IFBLK 0
#endif

/* Link */
#if !defined(S_IFLNK)
#	define S_IFLNK 0
#endif

/* Socket */
#if !defined(S_IFSOCK)
#	define S_IFSOCK 0
#endif

/* Read user permission */
#if !defined(S_IRUSR)
#	define S_IRUSR S_IREAD
#endif

/* Write user permission */
#if !defined(S_IWUSR)
#	define S_IWUSR S_IWRITE
#endif

/* Execute user permission */
#if !defined(S_IXUSR)
#	define S_IXUSR 0
#endif

/* Read group permission */
#if !defined(S_IRGRP)
#	define S_IRGRP 0
#endif

/* Write group permission */
#if !defined(S_IWGRP)
#	define S_IWGRP 0
#endif

/* Execute group permission */
#if !defined(S_IXGRP)
#	define S_IXGRP 0
#endif

/* Read others permission */
#if !defined(S_IROTH)
#	define S_IROTH 0
#endif

/* Write others permission */
#if !defined(S_IWOTH)
#	define S_IWOTH 0
#endif

/* Execute others permission */
#if !defined(S_IXOTH)
#	define S_IXOTH 0
#endif

/* Maximum length of file name */
#if !defined(PATH_MAX)
#	define PATH_MAX MAX_PATH
#endif
#if !defined(FILENAME_MAX)
#	define FILENAME_MAX MAX_PATH
#endif
#if !defined(NAME_MAX)
#	define NAME_MAX FILENAME_MAX
#endif

/* File type flags for d_type */
#define DT_UNKNOWN 0
#define DT_REG S_IFREG
#define DT_DIR S_IFDIR
#define DT_FIFO S_IFIFO
#define DT_SOCK S_IFSOCK
#define DT_CHR S_IFCHR
#define DT_BLK S_IFBLK
#define DT_LNK S_IFLNK

/* Macros for converting between st_mode and d_type */
#define IFTODT(mode) ((mode) & S_IFMT)
#define DTTOIF(type) (type)

/*
 * File type macros.  Note that block devices, sockets and links cannot be
 * distinguished on Windows and the macros S_ISBLK, S_ISSOCK and S_ISLNK are
 * only defined for compatibility.  These macros should always return false
 * on Windows.
 */
#if !defined(S_ISFIFO)
#	define S_ISFIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#endif
#if !defined(S_ISDIR)
#	define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#endif
#if !defined(S_ISREG)
#	define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISLNK)
#	define S_ISLNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#endif
#if !defined(S_ISSOCK)
#	define S_ISSOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#endif
#if !defined(S_ISCHR)
#	define S_ISCHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#endif
#if !defined(S_ISBLK)
#	define S_ISBLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#endif

/* Return the exact length of the file name without zero terminator */
#define _D_EXACT_NAMLEN(p) ((p)->d_namlen)

/* Return the maximum size of a file name */
#define _D_ALLOC_NAMLEN(p) ((PATH_MAX)+1)


#ifdef __cplusplus
extern "C" {
#endif


/* Wide-character version */
struct _wdirent {
	/* Always zero */
	long d_ino;

	/* File position within stream */
	long d_off;

	/* Structure size */
	unsigned short d_reclen;

	/* Length of name without \0 */
	size_t d_namlen;

	/* File type */
	int d_type;

	/* File name */
	wchar_t d_name[PATH_MAX+1];
};
typedef struct _wdirent _wdirent;

struct _WDIR {
	/* Current directory entry */
	struct _wdirent ent;

	/* Private file data */
	WIN32_FIND_DATAW data;

	/* True if data is valid */
	int cached;

	/* Win32 search handle */
	HANDLE handle;

	/* Initial directory name */
	wchar_t *patt;
};
typedef struct _WDIR _WDIR;

/* Multi-byte character version */
struct dirent {
	/* Always zero */
	long d_ino;

	/* File position within stream */
	long d_off;

	/* Structure size */
	unsigned short d_reclen;

	/* Length of name without \0 */
	size_t d_namlen;

	/* File type */
	int d_type;

	/* File name */
	char d_name[PATH_MAX+1];
};
typedef struct dirent dirent;

struct DIR {
	struct dirent ent;
	struct _WDIR *wdirp;
};
typedef struct DIR DIR;


/* Dirent functions */
static DIR *opendir(const char *dirname);
static _WDIR *_wopendir(const wchar_t *dirname);

static struct dirent *readdir(DIR *dirp);
static struct _wdirent *_wreaddir(_WDIR *dirp);

static int readdir_r(
	DIR *dirp, struct dirent *entry, struct dirent **result);
static int _wreaddir_r(
	_WDIR *dirp, struct _wdirent *entry, struct _wdirent **result);

static int closedir(DIR *dirp);
static int _wclosedir(_WDIR *dirp);

static void rewinddir(DIR* dirp);
static void _wrewinddir(_WDIR* dirp);

static int scandir(const char *dirname, struct dirent ***namelist,
	int (*filter)(const struct dirent*),
	int (*compare)(const struct dirent**, const struct dirent**));

static int alphasort(const struct dirent **a, const struct dirent **b);

static int versionsort(const struct dirent **a, const struct dirent **b);

static int strverscmp(const char *a, const char *b);

/* For compatibility with Symbian */
#define wdirent _wdirent
#define WDIR _WDIR
#define wopendir _wopendir
#define wreaddir _wreaddir
#define wclosedir _wclosedir
#define wrewinddir _wrewinddir

/* Compatibility with older Microsoft compilers and non-Microsoft compilers */
#if !defined(_MSC_VER) || _MSC_VER < 1400
#	define wcstombs_s dirent_wcstombs_s
#	define mbstowcs_s dirent_mbstowcs_s
#endif

/* Optimize dirent_set_errno() away on modern Microsoft compilers */
#if defined(_MSC_VER) && _MSC_VER >= 1400
#	define dirent_set_errno _set_errno
#endif


/* Internal utility functions */
static WIN32_FIND_DATAW *dirent_first(_WDIR *dirp);
static WIN32_FIND_DATAW *dirent_next(_WDIR *dirp);

#if !defined(_MSC_VER) || _MSC_VER < 1400
static int dirent_mbstowcs_s(
	size_t *pReturnValue, wchar_t *wcstr, size_t sizeInWords,
	const char *mbstr, size_t count);
#endif

#if !defined(_MSC_VER) || _MSC_VER < 1400
static int dirent_wcstombs_s(
	size_t *pReturnValue, char *mbstr, size_t sizeInBytes,
	const wchar_t *wcstr, size_t count);
#endif

#if !defined(_MSC_VER) || _MSC_VER < 1400
static void dirent_set_errno(int error);
#endif


/*
 * Open directory stream DIRNAME for read and return a pointer to the
 * internal working area that is used to retrieve individual directory
 * entries.
 */
static _WDIR *_wopendir(const wchar_t *dirname)
{
	wchar_t *p;

	/* Must have directory name */
	if (dirname == NULL || dirname[0] == '\0') {
		dirent_set_errno(ENOENT);
		return NULL;
	}

	/* Allocate new _WDIR structure */
	_WDIR *dirp = (_WDIR*) ICE_FS_MALLOC(sizeof(struct _WDIR));
	if (!dirp)
		return NULL;

	/* Reset _WDIR structure */
	dirp->handle = INVALID_HANDLE_VALUE;
	dirp->patt = NULL;
	dirp->cached = 0;

	/*
	 * Compute the length of full path plus zero terminator
	 *
	 * Note that on WinRT there's no way to convert relative paths
	 * into absolute paths, so just assume it is an absolute path.
	 */
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
	/* Desktop */
	DWORD n = GetFullPathNameW(dirname, 0, NULL, NULL);
#else
	/* WinRT */
	size_t n = wcslen(dirname);
#endif

	/* Allocate room for absolute directory name and search pattern */
	dirp->patt = (wchar_t*) ICE_FS_MALLOC(sizeof(wchar_t) * n + 16);
	if (dirp->patt == NULL)
		goto exit_closedir;

	/*
	 * Convert relative directory name to an absolute one.  This
	 * allows rewinddir() to function correctly even when current
	 * working directory is changed between opendir() and rewinddir().
	 *
	 * Note that on WinRT there's no way to convert relative paths
	 * into absolute paths, so just assume it is an absolute path.
	 */
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
	/* Desktop */
	n = GetFullPathNameW(dirname, n, dirp->patt, NULL);
	if (n <= 0)
		goto exit_closedir;
#else
	/* WinRT */
	wcsncpy_s(dirp->patt, n+1, dirname, n);
#endif

	/* Append search pattern \* to the directory name */
	p = dirp->patt + n;
	switch (p[-1]) {
	case '\\':
	case '/':
	case ':':
		/* Directory ends in path separator, e.g. c:\temp\ */
		/*NOP*/;
		break;

	default:
		/* Directory name doesn't end in path separator */
		*p++ = '\\';
	}
	*p++ = '*';
	*p = '\0';

	/* Open directory stream and retrieve the first entry */
	if (!dirent_first(dirp))
		goto exit_closedir;

	/* Success */
	return dirp;

	/* Failure */
exit_closedir:
	_wclosedir(dirp);
	return NULL;
}

/*
 * Read next directory entry.
 *
 * Returns pointer to static directory entry which may be overwritten by
 * subsequent calls to _wreaddir().
 */
static struct _wdirent *_wreaddir(_WDIR *dirp)
{
	/*
	 * Read directory entry to buffer.  We can safely ignore the return
	 * value as entry will be set to NULL in case of error.
	 */
	struct _wdirent *entry;
	(void) _wreaddir_r(dirp, &dirp->ent, &entry);

	/* Return pointer to statically allocated directory entry */
	return entry;
}

/*
 * Read next directory entry.
 *
 * Returns zero on success.  If end of directory stream is reached, then sets
 * result to NULL and returns zero.
 */
static int _wreaddir_r(
	_WDIR *dirp, struct _wdirent *entry, struct _wdirent **result)
{
	/* Read next directory entry */
	WIN32_FIND_DATAW *datap = dirent_next(dirp);
	if (!datap) {
		/* Return NULL to indicate end of directory */
		*result = NULL;
		return /*OK*/0;
	}

	/*
	 * Copy file name as wide-character string.  If the file name is too
	 * long to fit in to the destination buffer, then truncate file name
	 * to PATH_MAX characters and zero-terminate the buffer.
	 */
	size_t n = 0;
	while (n < PATH_MAX && datap->cFileName[n] != 0) {
		entry->d_name[n] = datap->cFileName[n];
		n++;
	}
	entry->d_name[n] = 0;

	/* Length of file name excluding zero terminator */
	entry->d_namlen = n;

	/* File type */
	DWORD attr = datap->dwFileAttributes;
	if ((attr & FILE_ATTRIBUTE_DEVICE) != 0)
		entry->d_type = DT_CHR;
	else if ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0)
		entry->d_type = DT_DIR;
	else
		entry->d_type = DT_REG;

	/* Reset dummy fields */
	entry->d_ino = 0;
	entry->d_off = 0;
	entry->d_reclen = sizeof(struct _wdirent);

	/* Set result address */
	*result = entry;
	return /*OK*/0;
}

/*
 * Close directory stream opened by opendir() function.  This invalidates the
 * DIR structure as well as any directory entry read previously by
 * _wreaddir().
 */
static int _wclosedir(_WDIR *dirp)
{
	if (!dirp) {
		dirent_set_errno(EBADF);
		return /*failure*/-1;
	}

	/* Release search handle */
	if (dirp->handle != INVALID_HANDLE_VALUE)
		FindClose(dirp->handle);

	/* Release search pattern */
	ICE_FS_FREE(dirp->patt);

	/* Release directory structure */
	ICE_FS_FREE(dirp);
	return /*success*/0;
}

/*
 * Rewind directory stream such that _wreaddir() returns the very first
 * file name again.
 */
static void _wrewinddir(_WDIR* dirp)
{
	if (!dirp)
		return;

	/* Release existing search handle */
	if (dirp->handle != INVALID_HANDLE_VALUE)
		FindClose(dirp->handle);

	/* Open new search handle */
	dirent_first(dirp);
}

/* Get first directory entry */
static WIN32_FIND_DATAW *dirent_first(_WDIR *dirp)
{
	if (!dirp)
		return NULL;

	/* Open directory and retrieve the first entry */
	dirp->handle = FindFirstFileExW(
		dirp->patt, FindExInfoStandard, &dirp->data,
		FindExSearchNameMatch, NULL, 0);
	if (dirp->handle == INVALID_HANDLE_VALUE)
		goto error;

	/* A directory entry is now waiting in memory */
	dirp->cached = 1;
	return &dirp->data;

error:
	/* Failed to open directory: no directory entry in memory */
	dirp->cached = 0;

	/* Set error code */
	DWORD errorcode = GetLastError();
	switch (errorcode) {
	case ERROR_ACCESS_DENIED:
		/* No read access to directory */
		dirent_set_errno(EACCES);
		break;

	case ERROR_DIRECTORY:
		/* Directory name is invalid */
		dirent_set_errno(ENOTDIR);
		break;

	case ERROR_PATH_NOT_FOUND:
	default:
		/* Cannot find the file */
		dirent_set_errno(ENOENT);
	}
	return NULL;
}

/* Get next directory entry */
static WIN32_FIND_DATAW *dirent_next(_WDIR *dirp)
{
	/* Is the next directory entry already in cache? */
	if (dirp->cached) {
		/* Yes, a valid directory entry found in memory */
		dirp->cached = 0;
		return &dirp->data;
	}

	/* No directory entry in cache */
	if (dirp->handle == INVALID_HANDLE_VALUE)
		return NULL;

	/* Read the next directory entry from stream */
	if (FindNextFileW(dirp->handle, &dirp->data) == FALSE)
		goto exit_close;

	/* Success */
	return &dirp->data;

	/* Failure */
exit_close:
	FindClose(dirp->handle);
	dirp->handle = INVALID_HANDLE_VALUE;
	return NULL;
}

/* Open directory stream using plain old C-string */
static DIR *opendir(const char *dirname)
{
	/* Must have directory name */
	if (dirname == NULL || dirname[0] == '\0') {
		dirent_set_errno(ENOENT);
		return NULL;
	}

	/* Allocate memory for DIR structure */
	struct DIR *dirp = (DIR*) ICE_FS_MALLOC(sizeof(struct DIR));
	if (!dirp)
		return NULL;

	/* Convert directory name to wide-character string */
	wchar_t wname[PATH_MAX + 1];
	size_t n;
	int error = mbstowcs_s(&n, wname, PATH_MAX + 1, dirname, PATH_MAX+1);
	if (error)
		goto exit_failure;

	/* Open directory stream using wide-character name */
	dirp->wdirp = _wopendir(wname);
	if (!dirp->wdirp)
		goto exit_failure;

	/* Success */
	return dirp;

	/* Failure */
exit_failure:
	ICE_FS_FREE(dirp);
	return NULL;
}

/* Read next directory entry */
static struct dirent *readdir(DIR *dirp)
{
	/*
	 * Read directory entry to buffer.  We can safely ignore the return
	 * value as entry will be set to NULL in case of error.
	 */
	struct dirent *entry;
	(void) readdir_r(dirp, &dirp->ent, &entry);

	/* Return pointer to statically allocated directory entry */
	return entry;
}

/*
 * Read next directory entry into called-allocated buffer.
 *
 * Returns zero on success.  If the end of directory stream is reached, then
 * sets result to NULL and returns zero.
 */
static int readdir_r(
	DIR *dirp, struct dirent *entry, struct dirent **result)
{
	/* Read next directory entry */
	WIN32_FIND_DATAW *datap = dirent_next(dirp->wdirp);
	if (!datap) {
		/* No more directory entries */
		*result = NULL;
		return /*OK*/0;
	}

	/* Attempt to convert file name to multi-byte string */
	size_t n;
	int error = wcstombs_s(
		&n, entry->d_name, PATH_MAX + 1,
		datap->cFileName, PATH_MAX + 1);

	/*
	 * If the file name cannot be represented by a multi-byte string, then
	 * attempt to use old 8+3 file name.  This allows the program to
	 * access files although file names may seem unfamiliar to the user.
	 *
	 * Be ware that the code below cannot come up with a short file name
	 * unless the file system provides one.  At least VirtualBox shared
	 * folders fail to do this.
	 */
	if (error && datap->cAlternateFileName[0] != '\0') {
		error = wcstombs_s(
			&n, entry->d_name, PATH_MAX + 1,
			datap->cAlternateFileName, PATH_MAX + 1);
	}

	if (!error) {
		/* Length of file name excluding zero terminator */
		entry->d_namlen = n - 1;

		/* File attributes */
		DWORD attr = datap->dwFileAttributes;
		if ((attr & FILE_ATTRIBUTE_DEVICE) != 0)
			entry->d_type = DT_CHR;
		else if ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0)
			entry->d_type = DT_DIR;
		else
			entry->d_type = DT_REG;

		/* Reset dummy fields */
		entry->d_ino = 0;
		entry->d_off = 0;
		entry->d_reclen = sizeof(struct dirent);
	} else {
		/*
		 * Cannot convert file name to multi-byte string so construct
		 * an erroneous directory entry and return that.  Note that
		 * we cannot return NULL as that would stop the processing
		 * of directory entries completely.
		 */
		entry->d_name[0] = '?';
		entry->d_name[1] = '\0';
		entry->d_namlen = 1;
		entry->d_type = DT_UNKNOWN;
		entry->d_ino = 0;
		entry->d_off = -1;
		entry->d_reclen = 0;
	}

	/* Return pointer to directory entry */
	*result = entry;
	return /*OK*/0;
}

/* Close directory stream */
static int closedir(DIR *dirp)
{
	int ok;

	if (!dirp)
		goto exit_failure;

	/* Close wide-character directory stream */
	ok = _wclosedir(dirp->wdirp);
	dirp->wdirp = NULL;

	/* Release multi-byte character version */
	ICE_FS_FREE(dirp);
	return ok;

exit_failure:
	/* Invalid directory stream */
	dirent_set_errno(EBADF);
	return /*failure*/-1;
}

/* Rewind directory stream to beginning */
static void rewinddir(DIR* dirp)
{
	if (!dirp)
		return;

	/* Rewind wide-character string directory stream */
	_wrewinddir(dirp->wdirp);
}

/* Scan directory for entries */
static int scandir(
	const char *dirname, struct dirent ***namelist,
	int (*filter)(const struct dirent*),
	int (*compare)(const struct dirent**, const struct dirent**))
{
	int result;

	/* Open directory stream */
	DIR *dir = opendir(dirname);
	if (!dir) {
		/* Cannot open directory */
		return /*Error*/ -1;
	}

	/* Read directory entries to memory */
	struct dirent *tmp = NULL;
	struct dirent **files = NULL;
	size_t size = 0;
	size_t allocated = 0;
	while (1) {
		/* Allocate room for a temporary directory entry */
		if (!tmp) {
			tmp = (struct dirent*) ICE_FS_MALLOC(sizeof(struct dirent));
			if (!tmp)
				goto exit_failure;
		}

		/* Read directory entry to temporary area */
		struct dirent *entry;
		if (readdir_r(dir, tmp, &entry) != /*OK*/0)
			goto exit_failure;

		/* Stop if we already read the last directory entry */
		if (entry == NULL)
			goto exit_success;

		/* Determine whether to include the entry in results */
		if (filter && !filter(tmp))
			continue;

		/* Enlarge pointer table to make room for another pointer */
		if (size >= allocated) {
			/* Compute number of entries in the new table */
			size_t num_entries = size * 2 + 16;

			/* Allocate new pointer table or enlarge existing */
			void *p = ICE_FS_REALLOC(files, sizeof(void*) * num_entries);
			if (!p)
				goto exit_failure;

			/* Got the memory */
			files = (dirent**) p;
			allocated = num_entries;
		}

		/* Store the temporary entry to ptr table */
		files[size++] = tmp;
		tmp = NULL;
	}

exit_failure:
	/* Release allocated file entries */
	for (size_t i = 0; i < size; i++) {
		ICE_FS_FREE(files[i]);
	}

	/* Release the pointer table */
	ICE_FS_FREE(files);
	files = NULL;

	/* Exit with error code */
	result = /*error*/ -1;
	goto exit_status;

exit_success:
	/* Sort directory entries */
	qsort(files, size, sizeof(void*),
		(int (*) (const void*, const void*)) compare);

	/* Pass pointer table to caller */
	if (namelist)
		*namelist = files;

	/* Return the number of directory entries read */
	result = (int) size;

exit_status:
	/* Release temporary directory entry, if we had one */
	ICE_FS_FREE(tmp);

	/* Close directory stream */
	closedir(dir);
	return result;
}

/* Alphabetical sorting */
static int alphasort(const struct dirent **a, const struct dirent **b)
{
	return strcoll((*a)->d_name, (*b)->d_name);
}

/* Sort versions */
static int versionsort(const struct dirent **a, const struct dirent **b)
{
	return strverscmp((*a)->d_name, (*b)->d_name);
}

/* Compare strings */
static int strverscmp(const char *a, const char *b)
{
	size_t i = 0;
	size_t j;

	/* Find first difference */
	while (a[i] == b[i]) {
		if (a[i] == '\0') {
			/* No difference */
			return 0;
		}
		++i;
	}

	/* Count backwards and find the leftmost digit */
	j = i;
	while (j > 0 && isdigit(a[j-1])) {
		--j;
	}

	/* Determine mode of comparison */
	if (a[j] == '0' || b[j] == '0') {
		/* Find the next non-zero digit */
		while (a[j] == '0' && a[j] == b[j]) {
			j++;
		}

		/* String with more digits is smaller, e.g 002 < 01 */
		if (isdigit(a[j])) {
			if (!isdigit(b[j])) {
				return -1;
			}
		} else if (isdigit(b[j])) {
			return 1;
		}
	} else if (isdigit(a[j]) && isdigit(b[j])) {
		/* Numeric comparison */
		size_t k1 = j;
		size_t k2 = j;

		/* Compute number of digits in each string */
		while (isdigit(a[k1])) {
			k1++;
		}
		while (isdigit(b[k2])) {
			k2++;
		}

		/* Number with more digits is bigger, e.g 999 < 1000 */
		if (k1 < k2)
			return -1;
		else if (k1 > k2)
			return 1;
	}

	/* Alphabetical comparison */
	return (int) ((unsigned char) a[i]) - ((unsigned char) b[i]);
}

/* Convert multi-byte string to wide character string */
#if !defined(_MSC_VER) || _MSC_VER < 1400
static int dirent_mbstowcs_s(
	size_t *pReturnValue, wchar_t *wcstr,
	size_t sizeInWords, const char *mbstr, size_t count)
{
	/* Older Visual Studio or non-Microsoft compiler */
	size_t n = mbstowcs(wcstr, mbstr, sizeInWords);
	if (wcstr && n >= count)
		return /*error*/ 1;

	/* Zero-terminate output buffer */
	if (wcstr && sizeInWords) {
		if (n >= sizeInWords)
			n = sizeInWords - 1;
		wcstr[n] = 0;
	}

	/* Length of multi-byte string with zero terminator */
	if (pReturnValue) {
		*pReturnValue = n + 1;
	}

	/* Success */
	return 0;
}
#endif

/* Convert wide-character string to multi-byte string */
#if !defined(_MSC_VER) || _MSC_VER < 1400
static int dirent_wcstombs_s(
	size_t *pReturnValue, char *mbstr,
	size_t sizeInBytes, const wchar_t *wcstr, size_t count)
{
	/* Older Visual Studio or non-Microsoft compiler */
	size_t n = wcstombs(mbstr, wcstr, sizeInBytes);
	if (mbstr && n >= count)
		return /*error*/1;

	/* Zero-terminate output buffer */
	if (mbstr && sizeInBytes) {
		if (n >= sizeInBytes) {
			n = sizeInBytes - 1;
		}
		mbstr[n] = '\0';
	}

	/* Length of resulting multi-bytes string WITH zero-terminator */
	if (pReturnValue) {
		*pReturnValue = n + 1;
	}

	/* Success */
	return 0;
}
#endif

/* Set errno variable */
#if !defined(_MSC_VER) || _MSC_VER < 1400
static void dirent_set_errno(int error)
{
	/* Non-Microsoft compiler or older Microsoft compiler */
	errno = error;
}
#endif

#ifdef __cplusplus
}
#endif
#endif /*DIRENT_H*/

#else
#  include <dirent.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#endif

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_strfrom(char* str, int from, int to) {
    char* res = (char*) ICE_FS_MALLOC((to - from) * sizeof(char));
    int count = 0;
    
    for (int i = from; i <= to; i++) {
        res[count] = str[i];
        count++;
    }
    
    return res;
}

ICE_FS_API int ICE_FS_CALLCONV ice_fs_count_backslashes(char* str) {
    int count = 0;
    size_t lenstr = strlen(str);
    
    for (int i = 0; i < lenstr; i++) {
        if (str[i] == '\\' || str[i] == '/') count++;
    }
    
    return count;
}

ICE_FS_API int ICE_FS_CALLCONV ice_fs_count_dots(char* str) {
    int count = 0;
    
    for (int i = 0; i < lenstr; i++) {
        if (str[i] == '.') count++;
    }
    
    return count;
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_home(void) {
    
#if !defined(ICE_FS_MICROSOFT)

#if (!(defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android)))
    return "/home";

#else
    return "/storage/emulated/0";

#endif

#else
    char* var;
    size_t reqsize;

    getenv_s(&reqsize, NULL, 0, "USERPROFILE");
    var = (char*) ICE_FS_MALLOC(reqsize * sizeof(char));
    getenv_s(&reqsize, var, reqsize, "USERPROFILE");
    
    return var;
    
#endif

}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_root(char* f) {

#if !defined(ICE_FS_MICROSOFT)

#if (!(defined(__ANDROID__) || defined(__android__) || defined(ANDROID) || defined(__ANDROID) || defined(__android) || defined(android) || defined(_ANDROID) || defined(_android)))
    return "/root";

#else
    return "/system";
    
#endif

#else
    char* var;
    size_t reqsize;

    getenv_s(&reqsize, NULL, 0, "SystemDrive");
    var = (char*) ICE_FS_MALLOC(reqsize * sizeof(char));
    getenv_s(&reqsize, var, reqsize, "SystemDrive");
    
    return var;
    
#endif

}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_current_dir(void) {
    char path[1024];
    getcwd(path, 1024);
    return path;
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_previous_dir(char* dir) {
    size_t lenstr = strlen(dir);
    int bscount = ice_fs_count_backslashes(dir);
    int count = 0;
    int loccur = 0;
    
    for (int i = 0; i < lenstr; i++) {
        if (count == bscount - 2) {
            loccur = i;
            break;
        }
        if (dir[i] == '\\' || dir[i] == '/') count++;
    }
    
    return ice_fs_strfrom(dir, 0, loccur);
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_file_dir(char* dir) {
    size_t lenstr = strlen(dir);
    int bscount = ice_fs_count_backslashes(dir);
    int count = 0;
    int loccur = 0;
    
    for (int i = 0; i < lenstr; i++) {
        if (count == bscount - 1) {
            loccur = i;
            break;
        }
        if (dir[i] == '\\' || dir[i] == '/') count++;
    }
    
    return ice_fs_strfrom(dir, 0, loccur);
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_change_dir(char* dir) {
    return (chdir(dir) < 0) ? ICE_FS_FALSE : ICE_FS_TRUE;
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_remove_dir(char* dir) {
    return (rmdir(dir) < 0) ? ICE_FS_FALSE : ICE_FS_TRUE;
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_copy_dir(char* d1, char* d2) {
    char res[512];
    
#if defined(ICE_FS_MICROSOFT)
    sprintf(res, "xcopy %s %s\\%s /E /H /C /I\0", d1, d2, ice_fs_dir_name(d1));

#else
    sprintf(res, "cp %s %s\0", d1, d2);

#endif

    return (system(res) == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;    
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_remove_file(char* dir) {
    return (remove(dir) < 0) ? ICE_FS_FALSE : ICE_FS_TRUE;
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_rename_file(char* d1, char* d2) {
    return (rename(d1, d2) < 0) ? ICE_FS_FALSE : ICE_FS_TRUE;
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_copy_file(char* d1, char* d2) {

#if defined(ICE_FS_MICROSOFT)
    return (CopyFileA(d1, d2, TRUE)) ? ICE_FS_TRUE : ICE_FS_FALSE;
    
#else
    return (system(d1, ice_fs_file_dir(d2)) == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;

#endif

}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_rename_dir(char* d1, char* d2) {
    return (rename(d1, d2) < 0) ? ICE_FS_FALSE : ICE_FS_TRUE;
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_dir(char* dir) {
    size_t lenstr = strlen(dir);
    char* res = (char*) ICE_FS_MALLOC(lenstr * sizeof(char));
    
    for (int i = 0; i < lenstr; i++) {
        if (dir[i] == '\\' || dir[i] == '/') {

#if defined(ICE_FS_MICROSOFT)
            res[i] = '\\';
#else
            res[i] = '/';
#endif

        } else {
            res[i] = dir[i];
        }
    }
    
    return res;
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_join_dir(char* d1, char* d2) {
    size_t lenstr1 = strlen(d1);
    size_t lenstr2 = strlen(d2);
    char* res = (char*) ICE_FS_MALLOC((lenstr1 + lenstr2 + 2) * sizeof(char));
    
    for (int i = 0; i < lenstr1; i++) {
        res[i] = d1[i];
    }

#if defined(ICE_FS_MICROSOFT)
    res[lenstr1] = '\\';
    
#else
    res[lenstr1] = '/';

#endif

    for (int i = 0; i < lenstr2; i++) {
        res[lenstr1 + 1 + i] = d2[i];
    }
    
    res[lenstr1 + lenstr2] = '\0';
    return res;
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_join_dirs(char** dirs) {
    size_t dirs_size = 0;
    int dirs_count = 0;
    
    for (int i = 0; i < 512; i++) {
        if (dirs[i] != NULL) {
            dirs_size += strlen(dirs[i]);
            dirs_count++;
        } else {
            break;
        }
    }
    
    char* res = (char*) ICE_FS_MALLOC((dirs_size + (dirs_count * 2)) * sizeof(char));
    
    for (int i = 0; i < dirs_count; i++) {
        strcpy(res, dirs[i]);
        
#if defined(ICE_FS_MICROSOFT)
        strcpy(res, '\\');

#else
        strcpy(res, '/');

#endif
        
        strcpy(res, '\0');
    }
    
    
    return res;
}

ICE_FS_API char** ICE_FS_CALLCONV ice_fs_split_dir(char* dir, char delim) {
    int arrlen = 0;
    int count = 0;
    int elems = 0;
    int lenstr = strlen(dir);
    
    for (int i = 0; i < lenstr; i++) {
       if (dir[i] == delim) {
           arrlen++;
       }
    }
    
    int* arr_elem_lengths = (int*) ICE_FS_CALLOC(arrlen, sizeof(int));
    
    for (int i = 0; i < lenstr; i++) {
       count++;
       
       if (dir[i] == delim) {
           arr_elem_lengths[elems] = count;
           elems++;
       }
    }
    
    int sum = 0;
    
    for (int i = 0; i < elems; i++) {
        sum += arr_elem_lengths[i];
    }
    
    char** res = (char**) ICE_FS_CALLOC(sum, sizeof(char));
    
    for (int i = 0; i < elems; i++) {
        if (i == 0) {
            res[i] = (char*) ICE_FS_CALLOC((arr_elem_lengths[i] - 2) + 1, sizeof(char));
            int count = 0;
    
            for (int i = 0; i <= arr_elem_lengths[i] - 2; i++) {
                res[i][count] = dir[i];
                count++;
            }
    
            res[count + 1] = '\0';
        } else {
            res[i] = (char*) ICE_FS_CALLOC(((arr_elem_lengths[i] - 2) - arr_elem_lengths[i - 1]) + 1, sizeof(char));
            int count = 0;
    
            for (int i = arr_elem_lengths[i - 1]; i <= arr_elem_lengths[i] - 2; i++) {
                res[i][count] = dir[i];
                count++;
            }
    
            res[count + 1] = '\0';
        }
    }
    
    ICE_FS_FREE(arr_elem_lengths);
    return res;
}

ICE_FS_API char** ICE_FS_CALLCONV ice_fs_dir_list(char* dir) {
    char* res[512];
    DIR *d;
    struct dirent *ent;
    int count = 0;
    
    if ((d = opendir(dir)) != NULL) {
        while ((ent = readdir(d)) != NULL) {
            res[count] = ent->d_name;
            count++;
        }
        closedir(d);
    } else {
        return NULL;
    }
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_dir_exists(char* dir) {
    DIR* d = opendir(dir);
    
    if (opendir(dir) != NULL) {
        return (closedir(d) < 0) ? ICE_FS_FALSE : ICE_FS_TRUE;
    } else {
        return ICE_FS_FALSE;
    }
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_create_dir(char* dir) {
    
#if defined(ICE_FS_MICROSOFT)
    BOOL res = CreateDirectoryA(dir, NULL);
    
    if (!res) {
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            return ICE_FS_TRUE;
        } else {
            return ICE_FS_FALSE;
        }
    } else {
        return ICE_FS_TRUE;
    }
    
#else
    int res = mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return (res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
    
#endif

}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_is_file(char* dir) {
    DIR* d = opendir(dir);
    
    if (opendir(dir) == NULL) {
        return ICE_FS_TRUE;
    } else {
        return (closedir(d) > 0) ? ICE_FS_FALSE : ICE_FS_TRUE;
    }
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_is_dir(char* dir) {
    return (fopen(dir, "r") == NULL) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_create_file(char* name) {
    return (fopen(name, "rw") != NULL) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_write(char* name, char* content) {
    return (fprintf(fopen(name, "a"), content) < 0) ? ICE_FS_FALSE : ICE_FS_TRUE;
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_clear(char* name) {
    FILE* f = fopen(name, "w");
    
    if (f == NULL) {
        return ICE_FS_FALSE;
    } else {
        return (fclose(f) < 0) ? ICE_FS_FALSE : ICE_FS_TRUE;
    }
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_file_exists(char* fname) {
    return (fopen(fname, "r") == NULL) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_full_file_path(char* fname) {

#if defined(ICE_FS_MICROSOFT)
    char res[1024];
    BOOL ret = GetFullPathName(ice_fs_file_name(fname), 1024, res, NULL);
    
    if (ret == 1) {
        return res;
    }
    
    return NULL;
    
#else
    char res[1024];
    char* ptr;
    FILE* f = fopen(fname, "r");
    
    if (f == NULL) {
        f = fopen(fname, "a");
    }
    
    ptr = realpath(fname, res);
    fclose(f);
    return res;
#endif

}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_is_file_ext(char* fname, char* ext) {
    return (strcmp(ice_fs_file_ext(fname), ext) == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_file_ext(char* fname) {
    const char *dot = strrchr(fname, '.');
    if (!dot || dot == fname) return NULL;
    return (dot + 1);
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_file_name(char* dir) {
    size_t lenstr = strlen(dir);
    int bscount = ice_fs_count_backslashes(dir);
    int count = 0;
    int loccur = 0;
    
    for (int i = 0; i < lenstr; i++) {
        if (count == bscount - 1) {
            loccur = i;
            break;
        }
        if (dir[i] == '\\' || dir[i] == '/') count++;
    }
    
    return ice_fs_strfrom(dir, loccur, lenstr);
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_dir_name(char* dir) {
    size_t lenstr = strlen(dir);
    int bscount = ice_fs_count_backslashes(dir);
    int count = 0;
    int foccur = 0;
    int soccur = 0;
    
    for (int i = 0; i < lenstr; i++) {
        if (count == bscount - 2) {
            foccur = i;
        }
        if (count == bscount - 1) {
            soccur = i;
            break;
        }
        if (dir[i] == '\\' || dir[i] == '/') count++;
    }
    
    return ice_fs_strfrom(dir, foccur, soccur);
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_name_no_ext(char* fname) {
    size_t lenstr = strlen(fname);
    int bscount = ice_fs_count_backslashes(fname);
    int dotcount = ice_fs_count_dots(fname);
    int scount = 0;
    int pcount = 0;
    int loccur = 0;
    int poccur = 0;
    
    for (int i = 0; i < lenstr; i++) {
        if (pcount == dotcount) {
            poccur = i;
            break;
        }
        
        if (scount == bscount - 1) {
            loccur = i;
        }
        if (fname[i] == '\\' || fname[i] == '/') scount++;
        if (fname[i] == '.') pcount++;
    }
    
    return ice_fs_strfrom(fname, loccur, poccur);
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_get_line(char* fname, int l) {
    int count = 0;
    char line[1024];
    
    while(fgets(line, sizeof(line), fopen(fname, "r")) != NULL) {
        if (count == l) break;
        count++;
    }
    
    return line;
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_edit_line(char* fname, int l, char* content) {
    ice_fs_remove_line(fname, l);
    FILE* data = fopen(fname, "a");
    for (int i = 0; i < l; i++) fprintf(data, "\0\n");
    fprintf(data, "%s", content);
    fclose(data);
}

ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_remove_line(char* fname, int l) {
    unsigned int ctr = 0;
    char str[512];
    FILE* data = fopen(fname, "r");
    FILE* temp_data = fopen("temp", "w");
    while (!feof(data))
    {
        strcpy(str, "\0");
        fgets(str, 256, data);
        if (!feof(data)) {
            ctr++;
            if (ctr != l) fprintf(temp_data, str);
        }
    }
    fclose(data);
    fclose(temp_data);
    remove(fname);
    rename("temp", fname);
}

ICE_FS_API char** ICE_FS_CALLCONV ice_fs_lines(char* fname) {
    int count = ice_fs_lines_count(fname);
    size_t arrsize = 0;
    
    for (int i = 0; i < count; i++) {
        arrsize += strlen(ice_fs_get_line(fname, i));
    }
    
    char** lines = (char**) ICE_FS_MALLOC(arrsize * sizeof(char));
    
    for (int i = 0; i < count; i++) {
        lines[i] = ice_fs_get_line(fname, i);
    }
    
    return lines;
}

ICE_FS_API int ICE_FS_CALLCONV ice_fs_lines_count(char* fname) {
    int count = 0;
    FILE* f = fopen(fname, "r");
    char c;
    
    if (f != NULL) {
        do {
            c = fgetc(f);
            if (feof(f)) break;
            if (c == '\n') count++;
        } while (1);
        fclose(f);
    }
    
    return count;
}

ICE_FS_API char* ICE_FS_CALLCONV ice_fs_file_content(char* fname) {
    FILE* f = fopen(fname, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *string = (char*) ICE_FS_MALLOC(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);
    
    return string;
}

#endif  // ICE_FS_IMPL
#endif  // ICE_FS_H
