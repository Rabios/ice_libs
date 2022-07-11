/*

ice_fs.h, Single-Header Cross-Platform C library to work with files and directories and paths!


================================== Full Overview ==================================

ice_fs.h is Single-Header Cross-Platform C library to work with files and directories and paths, It provides functionality to work with them...

To use it #define ICE_FS_IMPL then #include "ice_fs.h" in your C/C++ code!

Check out "Linking Flags" to know which libs required to link for compilation depending on each platform...


================================== Usage Example ==================================

// Define the implementation of the library and include it
#define ICE_FS_IMPL 1
#include "ice_fs.h"

#include <stdio.h>

// Helper
#define trace(fname, str) (void) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(void) {
    // Struct that contains modification date information
    ice_fs_date mod_date;

    // To store result of called functions
    ice_fs_bool res;

    // Create a directory of name "surprise" if does not exists
    res = ice_fs_create("surprise", ICE_FS_OBJECT_TYPE_DIR);
    
    // If the function failed to create the directory, Trace error then terminate the program
    if (res == ICE_FS_FALSE) {
        trace("ice_fs_create", "ERROR: failed to create a directory!");
        return -1;
    }

    // Create a file with content written with no append (overwrite)
    // res = ice_fs_file_write("surprise/iCe_SeCrEt_MeSsAgE.txt", "ice_libs makes C more enjoyable! :)", ICE_FS_FALSE);
    
    // If the function failed to create the file, Trace error then terminate the program
    if (res == ICE_FS_FALSE) {
        trace("ice_fs_file_write", "ERROR: failed to create a file!");
        return -1;
    }

    // Rename the created file to another name in same path
    res = ice_fs_rename("surprise/iCe_SeCrEt_MeSsAgE.txt", "surprise/ice_secret_message.txt");
    
    // If the function failed to rename the file, Trace error then terminate the program
    if (res == ICE_FS_FALSE) {
        trace("ice_fs_rename", "ERROR: failed to rename the created file!");
        return -1;
    }

    // Get modification date of the created file
    res = ice_fs_get_date("surprise/ice_secret_message.txt", ICE_FS_LAST_MODIFICATION_DATE, &mod_date);
    
    // If the function failed to retrieve modification date of the created file, Trace error then terminate the program
    if (res == ICE_FS_FALSE) {
        trace("ice_fs_get_date", "ERROR: failed to retrieve modification date of the created file!");
        return -1;
    }

    // Print the modification date of the created file
    (void) printf("modification date of surprise/ice_secret_message.txt: %s\n", mod_date.str);

    return 0;
}


=================================== Library API ===================================

// Custom Memory Allocators (Can be customized, Defaults to [malloc, calloc, realloc, free])
// To change them: #define ICE_FS_CUSTOM_MEMORY_ALLOCATORS and #define each one to use desired function, Plus including header that declares those memory functions in your code...
#define ICE_FS_MALLOC(sz)
#define ICE_FS_CALLOC(n, sz)
#define ICE_FS_REALLOC(ptr, sz)
#define ICE_FS_FREE(ptr)

// Boolean Enum, To avoid including stdbool.h
typedef enum ice_fs_bool {
    ICE_FS_FALSE    = -1,
    ICE_FS_TRUE     = 0
} ice_fs_bool;

// Type of object in path (File, Folder, etc...)
typedef enum ice_fs_object_type {
    ICE_FS_OBJECT_TYPE_NONE = -1,   // Given if path does not exist
    ICE_FS_OBJECT_TYPE_FILE,        // File
    ICE_FS_OBJECT_TYPE_DIR          // Directory
} ice_fs_object_type;

// FileSystem Object, Contains information of object in specific path
typedef struct ice_fs_object {
    const char *name;               // Name of object
    ice_fs_object_type type;        // Type of object (File, Folder, etc...)
} ice_fs_object;

// Directory
typedef struct ice_fs_dir {
    ice_fs_object *items;           // List of items in the directory (Files, Folders, etc...)
    unsigned long items_count;      // Number of the items in the directory
} ice_fs_dir;

// Enumeration for week days
typedef enum ice_fs_date_day {
    ICE_FS_DATE_DAY_UNKNOWN = 0,
    ICE_FS_DATE_DAY_SUNDAY,
    ICE_FS_DATE_DAY_MONDAY,
    ICE_FS_DATE_DAY_TUESDAY,
    ICE_FS_DATE_DAY_WEDNESDAY,
    ICE_FS_DATE_DAY_THURSDAY,
    ICE_FS_DATE_DAY_FRIDAY,
    ICE_FS_DATE_DAY_SATURDAY
} ice_fs_date_day;

// Enumeration for year months
typedef enum ice_fs_date_month {
    ICE_FS_DATE_MONTH_UNKNOWN = 0,
    ICE_FS_DATE_MONTH_JANUARY,
    ICE_FS_DATE_MONTH_FEBRUARY,
    ICE_FS_DATE_MONTH_MARCH,
    ICE_FS_DATE_MONTH_APRIL,
    ICE_FS_DATE_MONTH_MAY,
    ICE_FS_DATE_MONTH_JUNE,
    ICE_FS_DATE_MONTH_JULY,
    ICE_FS_DATE_MONTH_AUGUST,
    ICE_FS_DATE_MONTH_SEPTEMBER,
    ICE_FS_DATE_MONTH_OCTOBER,
    ICE_FS_DATE_MONTH_NOVEMBER,
    ICE_FS_DATE_MONTH_DECEMBER
} ice_fs_date_month;

// Enumeration for seasons
typedef enum ice_fs_date_season {
    ICE_FS_DATE_SEASON_UNKNOWN = 0,
    ICE_FS_DATE_SEASON_WINTER,
    ICE_FS_DATE_SEASON_SPRING,
    ICE_FS_DATE_SEASON_SUMMER,
    ICE_FS_DATE_SEASON_AUTUMN
} ice_fs_date_season;

// Struct that contains date info for file/directory
typedef struct ice_fs_date {
    const char *str;                // Time as string
    unsigned long epoch;            // Unix timestamp
    unsigned seconds;
    unsigned minutes;
    unsigned hour;
    ice_fs_date_day week_day;       // (ICE_FS_DATE_DAY_SUNDAY - ICE_FS_DATE_DAY_SATURDAY)
    unsigned month_day;             // (1 - Month last day number)
    unsigned year_day;              // (1 - 365)
    ice_fs_date_month month;        // (ICE_FS_DATE_MONTH_JANUARY - ICE_FS_DATE_MONTH_DECEMBER)
    ice_fs_date_season season;      // (ICE_FS_DATE_SEASON_WINTER - ICE_FS_DATE_SEASON_AUTUMN)
    unsigned year;
} ice_fs_date;

// Enumeration for dates for file/directory (Which can be retrieved)
typedef enum ice_fs_date_type {
    ICE_FS_LAST_ACCESS_DATE = 0,    // Last access date of file/directory
    ICE_FS_LAST_MODIFICATION_DATE,  // Last modification date of file/directory
    ICE_FS_LAST_STATUS_CHANGE_DATE  // Last status change date of file/directory
} ice_fs_date_type;

// [INTERNAL] Returns length of string
unsigned long ice_fs_str_len(const char *str);

// [INTERNAL] Returns ICE_FS_TRUE if string str starts with slash or backslash, Or ICE_FS_FALSE if not
ice_fs_bool ice_fs_str_starts_with_slash(const char *str);

// [INTERNAL] Returns ICE_FS_TRUE if string str ends with slash or backslash, Or ICE_FS_FALSE if not
ice_fs_bool ice_fs_str_ends_with_slash(const char *str);

// [INTERNAL] Returns count of slashes in string
unsigned long ice_fs_str_slashes(const char *str);

// [INTERNAL] Returns count of dots in string
unsigned long ice_fs_str_dots(const char *str);

// [INTERNAL] Returns ICE_FS_TRUE if string str1 is same to string str2 or ICE_FS_FALSE if not
ice_fs_bool ice_fs_str_same(const char *str1, const char *str2);

// [INTERNAL] Converts char to string and returns result on allocation success or NULL on allocation failure
char* ice_fs_str_char_to_str(char ch);

// [INTERNAL] Returns substring of string from index from_idx to index to_idx on allocation success or NULL on allocation failure
char* ice_fs_str_sub(const char *str, unsigned long from_idx, unsigned long to_idx);

// [INTERNAL] Returns allocated copy of string on allocation success or NULL on allocation failure
char* ice_fs_str_copy(const char *str);

// [INTERNAL] Splits string into array of strings for each delimiter and returns it on allocation success or NULL on allocation failure, arrlen is pointer to unsigned long integer to store length of resulted array
char** ice_fs_str_split(const char *str, char delim, unsigned long *arrlen);

// [INTERNAL] Same like ice_fs_str_split but uses new line character '\n' as delimiter
char** ice_fs_str_splitlines(const char *str, unsigned long *arrlen);

// [INTERNAL] Returns number of string str2 matches in string str1, idxs can be pointer to array of unsigned long integers (To be Dynamically-Allocated) to store the matching indexes
unsigned long ice_fs_str_matches(const char *str1, const char *str2, unsigned long **idxs);

// Frees/Deallocates a String
void ice_fs_free_str(char *str);

// Frees array of strings, arrlen should be set to array length
void ice_fs_free_strarr(char **strs, unsigned long arrlen);

// Returns root of a path on allocation success or NULL on failure
char* ice_fs_root(const char *path);

// Returns ICE_FS_TRUE if the path is root or ICE_FS_FALSE if not
ice_fs_bool ice_fs_is_root(const char *path);

// Concats 2 paths and returns result path on allocation success or NULL on failure
char* ice_fs_concat_path(const char *path1, const char *path2);

// Returns file name with/without extension from path on allocation success or NULL on failure
char* ice_fs_filename(const char *path, ice_fs_bool with_ext);

// Returns file extension from path on allocation success or NULL on failure
char* ice_fs_ext(const char *path);

// Returns ICE_FS_TRUE if extension of the path is ext or ICE_FS_FALSE if not
ice_fs_bool ice_fs_is_ext(const char *path, const char *ext);

// Returns previous parent of a path on allocation success or NULL on failure
char* ice_fs_prev_path(const char *path);

// Returns parents of path in array on allocation success or NULL on failure
char** ice_fs_path_parents(const char *path, unsigned long *results);

// Returns ICE_FS_TRUE if path exists or ICE_FS_FALSE if not
ice_fs_bool ice_fs_path_exists(const char *path);

// Returns path of current working directory on allocation success or NULL on failure
char* ice_fs_cwd(void);

// Returns path of home on allocation success or NULL on failure
char* ice_fs_home(void);

// Returns formatted path of a path depending on platform on allocation success or NULL on failure
char* ice_fs_format_path(const char *path);

// Returns full path of a path on allocation success or NULL on failure
char* ice_fs_fullpath(const char *path);

// Creates symbolic/hard link for object in path1 at path2, Retruns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_link(const char *path1, const char *path2, ice_fs_bool hard_link);

// Reads value from symbolic link file at specific path, Returns value on allocation success or NULL on failure
char* ice_fs_readlink(const char *path);

// Returns type of object in specific path, Returns ICE_FS_OBJECT_TYPE_NONE on failure if path does not exist or returns any of values does ice_fs_object_type enumeration has
ice_fs_object_type ice_fs_type(const char *path);

// Reads content of file and returns the content on allocation success or NULL on failure, file_size is pointer to unsigned long integer that will store number of chars (bytes) the file has
char* ice_fs_file_content(const char *path, unsigned long *file_size);

// Creates file in path with content if doesn't exist or Appends to/Overwrites content of file in specific path if exists, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_file_write(const char *path, const char *content, ice_fs_bool append);

// Reads content of file, Returns the content in array of strings for each line on allocation success or NULL on failure, lines should be pointer to unsigned long integer to store count of lines the file has
char** ice_fs_file_lines(const char *path, unsigned long *lines);

// Changes current directory in the running program to another directory in path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_chdir(const char *path);

// Returns directory informations with list of contents in path on success or NULL on failure
ice_fs_dir ice_fs_dir_content(const char *path);

// Frees/Deallocates a directory information struct, dir should be pointer to the directory information struct that will be freed
void ice_fs_free_dir_content(ice_fs_dir *dir);

// Searches in contents of directory for a specific file/directory by string, Returns array of strings that contains full path of founded items on allocation success or NULL on failure, results should be pointer to unsigned long integer that stores number of founded items
char** ice_fs_dir_search(const char *path, const char *str, unsigned long *results);

// Creates file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_create(const char *path, ice_fs_object_type type);

// Removes file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_remove(const char *path);

// Clears content of file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_clear(const char *path);

// Copies file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_copy(const char *path1, const char *path2);

// Moves file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_move(const char *path1, const char *path2);

// Renames file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_rename(const char *path1, const char *path2);

// Returns ICE_FS_TRUE if file/folder in specific path is empty or ICE_FS_FALSE if not empty
ice_fs_bool ice_fs_is_empty(const char *path);

// Retrieves [last modification, last status change, last access] date of file/directory and stores info in info struct by pointing to, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure
ice_fs_bool ice_fs_get_date(const char *path, ice_fs_date_type date_type, ice_fs_date *info);


================================== Linking Flags ==================================

1. Microsoft Windows    => -lkernel32
2. Other                => -lc

// NOTES:
// 1. When using MSVC on Microsoft Windows, Required static libraries are automatically linked via #pragma preprocessor
// 2. Required headers and linking flags may vary on each Unix/Unix-like system...


================================= Usable #define(s) ===============================

// Define the implementation, This should be #defined before including ice_fs.h in the code...
#define ICE_FS_IMPL


// #### Define one of these to set functions call convention of the library (Optional) #### //

#define ICE_FS_VECTORCALL       // vectorcall (NOTE: GNU C compilers doesn't offer vectorcall yet)
#define ICE_FS_FASTCALL         // fastcall
#define ICE_FS_STDCALL          // stdcall
#define ICE_FS_CDECL            // cdecl


// #### Define one of these to set implementation platform (Optional) #### //

#define ICE_FS_MICROSOFT        // Microsoft platforms
#define ICE_FS_UNIX             // Unix and Unix-like platforms

// Automatically defined when no platform is set manually, When this defined it detects platform automatically...
#define ICE_FS_PLATFORM_AUTODETECTED


// #### Define one of these on Microsoft platforms to work with shared libraries (Optional) #### //

#define ICE_FS_DLLEXPORT        // Export the symbols to build as shared library
#define ICE_FS_DLLIMPORT        // Use the symbols from built shared library


// #### Define one of these to inline/extern/static library's functions (Optional) #### //

#define ICE_FS_INLINE           // inlines library functions (Only works on C99 Standard and above)
#define ICE_FS_EXTERN           // externs library functions
#define ICE_FS_STATIC           // statics library functions

// NOTE: You cannot #define both ICE_FS_EXTERN and ICE_FS_STATIC together in the code...

// Define this to customize ICE_FS_MALLOC, ICE_FS_CALLOC, ICE_FS_REALLOC, ICE_FS_FREE
#define ICE_FS_CUSTOM_MEMORY_ALLOCATORS


============================== Implementation Resources ===========================

1. https://docs.microsoft.com/en-us/windows/desktop/FileIO/listing-the-files-in-a-directory
2. https://docs.microsoft.com/en-us/windows/desktop/FileIO/file-management-functions
3. https://docs.microsoft.com/en-us/windows/desktop/FileIO/symbolic-links
4. https://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/dirent.h
5. https://pubs.opengroup.org/onlinepubs/7908799/xsh/fcntl.h.html
6. https://en.wikipedia.org/wiki/Unistd.h
7. https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdio.h.html
8. https://en.cppreference.com/w/c/chrono


================================= Support ice_libs ================================

ice_fs.h is one of libraries that ice_libs project provide...

You can support or contribute to ice_libs project by possibly one of following things:

1. Test libraries on each platform and provide feedback!
2. Add support to more platforms and backends!
3. Request to add more possible features!
4. Fix bugs/problems in the library!
5. Use it in one of your projects!
6. Star (and/or fork) the repo on GitHub: https://github.com/Rabios/ice_libs
7. Share ice_libs Everywhere!
8. Join the Discord Server: https://discord.gg/KfkwXjCW


*/

#if !defined(ICE_FS_H)
#define ICE_FS_H 1

/* Disable security warnings for MSVC compiler to not force usage of secure versions of various C functions (Which requires C11) */
#if defined(_MSC_VER)
#  define _CRT_SECURE_NO_DEPRECATE 1
#  define _CRT_SECURE_NO_WARNINGS 1
#  pragma warning(disable:4996)
#endif

/* Allow to use calling conventions if desired... */
#if defined(ICE_FS_VECTORCALL)
#  if defined(_MSC_VER)
#    define ICE_FS_CALLCONV __vectorcall
#  elif defined(__clang)
#    define ICE_FS_CALLCONV __attribute__((vectorcall))
#  elif defined(__GNUC__) || defined(__GNUG__)
#    error "vectorcall calling convention is not supported by GNU C/C++ compilers yet!" 
#  endif
#elif defined(ICE_FS_FASTCALL)
#  if defined(_MSC_VER)
#    define ICE_FS_CALLCONV __fastcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_FS_CALLCONV __attribute__((fastcall))
#  endif
#elif defined(ICE_FS_STDCALL)
#  if defined(_MSC_VER)
#    define ICE_FS_CALLCONV __stdcall
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_FS_CALLCONV __attribute__((stdcall))
#  endif
#elif defined(ICE_FS_CDECL)
#  if defined(_MSC_VER)
#    define ICE_FS_CALLCONV __cdecl
#  elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang)
#    define ICE_FS_CALLCONV __attribute__((cdecl))
#  endif
#else
#  define ICE_FS_CALLCONV
#endif

#if !(defined(ICE_FS_MICROSOFT) || defined(ICE_FS_UNIX))
#  define ICE_FS_PLATFORM_AUTODETECTED 1
#endif

/* Platform Detection */
#if defined(ICE_FS_PLATFORM_AUTODETECTED)
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_X360) || defined(__XBOX360__) || defined(_XBOX) || defined(_XBOX_ONE) || defined(_DURANGO)
#    if (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP))
#      error "ice_fs.h doesn't support UWP due to some limitations :("
#    else
#      define ICE_FS_MICROSOFT 1
#    endif
#  elif defined(unix) || defined(__unix__) || defined(__unix)
#    define ICE_FS_UNIX 1
#  else
#    error "ice_fs.h does not support this platform yet! :("
#  endif
#endif

/*
Allow to use them as extern functions if desired!

NOTE: extern functions cannot be static so we disable static keyword.
*/
#if !(defined(ICE_FS_EXTERN) && defined(ICE_FS_STATIC))
#  define ICE_FS_EXTERN 1
#else
#  error "static functions cannot be externed!"
#endif

#if defined(ICE_FS_EXTERN)
#  define ICE_FS_APIDEF extern
#elif defined(ICE_FS_STATIC)
#  define ICE_FS_APIDEF static
#endif

/*
If using ANSI C, Disable inline keyword usage so you can use library with ANSI C if possible!

NOTE: Use ICE_FS_INLINE to enable inline functionality.
*/
#if defined(ICE_FS_INLINE)
#  if !defined(__STDC_VERSION__)
#    define ICE_FS_INLINEDEF
#  elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define ICE_FS_INLINEDEF inline
#  endif
#else
#  define ICE_FS_INLINEDEF
#endif

/*
Allow to build DLL via ICE_FS_DLLEXPORT or ICE_FS_DLLIMPORT if desired!
Else, Just define API as extern C code!
*/
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

/*
Custom Memory Allocators (Can be customized, Defaults to [malloc, calloc, realloc, free])

To change them: #define ICE_FS_CUSTOM_MEMORY_ALLOCATORS and #define each one to use desired function, Plus including header that declares those memory functions in your code...
*/
#if !defined(ICE_FS_CUSTOM_MEMORY_ALLOCATORS)
#  if !defined(ICE_FS_MALLOC)
#    define ICE_FS_MALLOC(sz) malloc(sz)
#  endif
#  if !defined(ICE_FS_CALLOC)
#    define ICE_FS_CALLOC(n, sz) calloc(n, sz)
#  endif
#  if !defined(ICE_FS_REALLOC)
#    define ICE_FS_REALLOC(ptr, sz) realloc(ptr, sz)
#  endif
#  if !defined(ICE_FS_FREE)
#    define ICE_FS_FREE(ptr) free(ptr)
#  endif
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_fs_bool {
    ICE_FS_FALSE    = -1,
    ICE_FS_TRUE     = 0
} ice_fs_bool;

/* Type of object in path (File, Folder, etc...) */
typedef enum ice_fs_object_type {
    ICE_FS_OBJECT_TYPE_NONE = -1,   /* Given if path does not exist */
    ICE_FS_OBJECT_TYPE_FILE,        /* File */
    ICE_FS_OBJECT_TYPE_DIR          /* Directory */
} ice_fs_object_type;

/* FileSystem Object, Contains information of object in specific path */
typedef struct ice_fs_object {
    const char *name;               /* Name of object */
    ice_fs_object_type type;        /* Type of object (File, Folder, etc...) */
} ice_fs_object;

/* Directory */
typedef struct ice_fs_dir {
    ice_fs_object *items;           /* List of items in the directory (Files, Folders, etc...) */
    unsigned long items_count;      /* Number of the items in the directory */
} ice_fs_dir;

/* Enumeration for week days */
typedef enum ice_fs_date_day {
    ICE_FS_DATE_DAY_UNKNOWN = 0,
    ICE_FS_DATE_DAY_SUNDAY,
    ICE_FS_DATE_DAY_MONDAY,
    ICE_FS_DATE_DAY_TUESDAY,
    ICE_FS_DATE_DAY_WEDNESDAY,
    ICE_FS_DATE_DAY_THURSDAY,
    ICE_FS_DATE_DAY_FRIDAY,
    ICE_FS_DATE_DAY_SATURDAY
} ice_fs_date_day;

/* Enumeration for year months */
typedef enum ice_fs_date_month {
    ICE_FS_DATE_MONTH_UNKNOWN = 0,
    ICE_FS_DATE_MONTH_JANUARY,
    ICE_FS_DATE_MONTH_FEBRUARY,
    ICE_FS_DATE_MONTH_MARCH,
    ICE_FS_DATE_MONTH_APRIL,
    ICE_FS_DATE_MONTH_MAY,
    ICE_FS_DATE_MONTH_JUNE,
    ICE_FS_DATE_MONTH_JULY,
    ICE_FS_DATE_MONTH_AUGUST,
    ICE_FS_DATE_MONTH_SEPTEMBER,
    ICE_FS_DATE_MONTH_OCTOBER,
    ICE_FS_DATE_MONTH_NOVEMBER,
    ICE_FS_DATE_MONTH_DECEMBER
} ice_fs_date_month;

/* Enumeration for seasons */
typedef enum ice_fs_date_season {
    ICE_FS_DATE_SEASON_UNKNOWN = 0,
    ICE_FS_DATE_SEASON_WINTER,
    ICE_FS_DATE_SEASON_SPRING,
    ICE_FS_DATE_SEASON_SUMMER,
    ICE_FS_DATE_SEASON_AUTUMN
} ice_fs_date_season;

/* Struct that contains date info for file/directory */
typedef struct ice_fs_date {
    const char *str;                    /* Time as string */
    unsigned long epoch;                /* Unix timestamp */
    unsigned seconds;
    unsigned minutes;
    unsigned hour;
    ice_fs_date_day week_day;           /* (ICE_FS_DATE_DAY_SUNDAY - ICE_FS_DATE_DAY_SATURDAY) */
    unsigned month_day;                 /* (1 - Month last day number) */
    unsigned year_day;                  /* (1 - 365) */
    ice_fs_date_month month;            /* (ICE_FS_DATE_MONTH_JANUARY - ICE_FS_DATE_MONTH_DECEMBER) */
    ice_fs_date_season season;          /* (ICE_FS_DATE_SEASON_WINTER - ICE_FS_DATE_SEASON_AUTUMN) */
    unsigned year;
} ice_fs_date;

/* Enumeration for dates for file/directory (Which can be retrieved) */
typedef enum ice_fs_date_type {
    ICE_FS_LAST_ACCESS_DATE = 0,        /* Last access date of file/directory */
    ICE_FS_LAST_MODIFICATION_DATE,      /* Last modification date of file/directory */
    ICE_FS_LAST_STATUS_CHANGE_DATE      /* Last status change date of file/directory */
} ice_fs_date_type;

/* ============================== Functions ============================== */

/* [INTERNAL] Returns length of string */
ICE_FS_API unsigned long ICE_FS_CALLCONV ice_fs_str_len(const char *str);

/* [INTERNAL] Returns ICE_FS_TRUE if string str starts with slash or backslash, Or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_str_starts_with_slash(const char *str);

/* [INTERNAL] Returns ICE_FS_TRUE if string str ends with slash or backslash, Or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_str_ends_with_slash(const char *str);

/* [INTERNAL] Returns count of slashes in string */
ICE_FS_API unsigned long ICE_FS_CALLCONV ice_fs_str_slashes(const char *str);

/* [INTERNAL] Returns count of dots in string */
ICE_FS_API unsigned long ICE_FS_CALLCONV ice_fs_str_dots(const char *str);

/* [INTERNAL] Returns ICE_FS_TRUE if string str1 is same to string str2 or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_str_same(const char *str1, const char *str2);

/* [INTERNAL] Converts char to string and returns result on allocation success or NULL on allocation failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_str_char_to_str(char ch);

/* [INTERNAL] Returns substring of string from index from_idx to index to_idx on allocation success or NULL on allocation failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_str_sub(const char *str, unsigned long from_idx, unsigned long to_idx);

/* [INTERNAL] Returns allocated copy of string on allocation success or NULL on allocation failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_str_copy(const char *str);

/* [INTERNAL] Splits string into array of strings for each delimiter and returns it on allocation success or NULL on allocation failure, arrlen is pointer to unsigned long integer to store length of resulted array */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_str_split(const char *str, char delim, unsigned long *arrlen);

/* [INTERNAL] Same like ice_fs_str_split but uses new line character '\n' as delimiter */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_str_splitlines(const char *str, unsigned long *arrlen);

/* [INTERNAL] Returns number of string str2 matches in string str1, idxs can be pointer to array of unsigned long integers (To be Dynamically-Allocated) to store the matching indexes */
ICE_FS_API unsigned long ICE_FS_CALLCONV ice_fs_str_matches(const char *str1, const char *str2, unsigned long **idxs);

/* Frees/Deallocates a String */
ICE_FS_API void ICE_FS_CALLCONV ice_fs_free_str(char *str);

/* Frees array of strings, arrlen should be set to array length */
ICE_FS_API void ICE_FS_CALLCONV ice_fs_free_strarr(char **strs, unsigned long arrlen);

/* Returns root of a path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_root(const char *path);

/* Returns ICE_FS_TRUE if the path is root or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_is_root(const char *path);

/* Concats 2 paths and returns result path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_concat_path(const char *path1, const char *path2);

/* Returns file name with/without extension from path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_filename(const char *path, ice_fs_bool with_ext);

/* Returns file extension from path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_ext(const char *path);

/* Returns ICE_FS_TRUE if extension of the path is ext or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_is_ext(const char *path, const char *ext);

/* Returns previous parent of a path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_prev_path(const char *path);

/* Returns parents of path in array on allocation success or NULL on failure */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_path_parents(const char *path, unsigned long *results);

/* Returns ICE_FS_TRUE if path exists or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_path_exists(const char *path);

/* Returns path of current working directory on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_cwd(void);

/* Returns path of home on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_home(void);

/* Returns formatted path of a path depending on platform on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_format_path(const char *path);

/* Returns full path of a path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_fullpath(const char *path);

/* Creates symbolic/hard link for object in path1 at path2, Retruns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_link(const char *path1, const char *path2, ice_fs_bool hard_link);

/* Reads value from symbolic link file at specific path, Returns value on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_readlink(const char *path);

/* Returns type of object in specific path, Returns ICE_FS_OBJECT_TYPE_NONE on failure if path does not exist or returns any of values does ice_fs_object_type enumeration has */
ICE_FS_API ice_fs_object_type ICE_FS_CALLCONV ice_fs_type(const char *path);

/* Reads content of file and returns the content on allocation success or NULL on failure, file_size is pointer to unsigned long integer that will store number of chars (bytes) the file has */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_file_content(const char *path, unsigned long *file_size);

/* Creates file in path with content if doesn't exist or Appends to/Overwrites content of file in specific path if exists, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_file_write(const char *path, const char *content, ice_fs_bool append);

/* Reads content of file, Returns the content in array of strings for each line on allocation success or NULL on failure, lines should be pointer to unsigned long integer to store count of lines the file has */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_file_lines(const char *path, unsigned long *lines);

/* Changes current directory in the running program to another directory in path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_chdir(const char *path);

/* Returns directory informations with list of contents in path on success or NULL on failure */
ICE_FS_API ice_fs_dir ICE_FS_CALLCONV ice_fs_dir_content(const char *path);

/* Frees/Deallocates a directory information struct, dir should be pointer to the directory information struct that will be freed */
ICE_FS_API void ICE_FS_CALLCONV ice_fs_free_dir_content(ice_fs_dir *dir);

/* Searches in contents of directory for a specific file/directory by string, Returns array of strings that contains full path of founded items on allocation success or NULL on failure, results should be pointer to unsigned long integer that stores number of founded items */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_dir_search(const char *path, const char *str, unsigned long *results);

/* Creates file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_create(const char *path, ice_fs_object_type type);

/* Removes file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_remove(const char *path);

/* Clears content of file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_clear(const char *path);

/* Copies file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_copy(const char *path1, const char *path2);

/* Moves file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_move(const char *path1, const char *path2);

/* Renames file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_rename(const char *path1, const char *path2);

/* Returns ICE_FS_TRUE if file/folder in specific path is empty or ICE_FS_FALSE if not empty */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_is_empty(const char *path);

/* Retrieves [last modification, last status change, last access] date of file/directory and stores info in info struct by pointing to, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_get_date(const char *path, ice_fs_date_type date_type, ice_fs_date *info);

#if defined(__cplusplus)
}
#endif

#if defined(ICE_FS_IMPL)

#if defined(ICE_FS_MICROSOFT)
#  undef NO_OLDNAMES
#  define _CRT_INTERNAL_NONSTDC_NAMES 1
#  define _CRT_DECLARE_NONSTDC_NAMES 1
#  define _WIN32_WINNT 0x600
#elif defined(ICE_FS_UNIX)
#  define _POSIX_SOURCE 1
#  define _GNU_SOURCE 1
#endif

#if defined(ICE_FS_MICROSOFT) || defined(ICE_FS_UNIX)
#  include <time.h>
#  include <stdlib.h>
#  include <stdio.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#  if defined(ICE_FS_MICROSOFT)
#    include <direct.h>
#    include <io.h>
#    include <fcntl.h>
#    if defined(_MSC_VER)
#      include <windows.h>
#      pragma comment(lib, "kernel32.lib")
#    else
#      include <windef.h>
#      include <winbase.h>
#      include <fileapi.h>
#    endif
#    define ice_fs_open(path, flags)  open(path, flags)
#    define ice_fs_mkdir(path)        mkdir(path)
#  elif defined(ICE_FS_UNIX)
#    include <unistd.h>
#    include <sys/fcntl.h>
#    include <sys/io.h>
#    include <dirent.h>
#    define ice_fs_open(path, flags)  open(path, flags, 666)
#    define ice_fs_mkdir(path)        mkdir(path, 0777)
#  endif
#endif

/* [INTERNAL] Returns length of string */
ICE_FS_APIDEF unsigned long ICE_FS_CALLCONV ice_fs_str_len(const char *str) {
    unsigned long res = 0;
    if (str == 0) return 0;
    while (str[res] != 0) res++;
    return res;
}

/* [INTERNAL] Returns ICE_FS_TRUE if string str starts with slash or backslash, Or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_str_starts_with_slash(const char *str) {
    unsigned long lenstr = ice_fs_str_len(str);
    char ch = 0;

    if (lenstr == 0) return ICE_FS_FALSE;

    ch = str[0];
    return ((ch == '\\') || (ch == '/')) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

/* [INTERNAL] Returns ICE_FS_TRUE if string str ends with slash or backslash, Or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_str_ends_with_slash(const char *str) {
    unsigned long lenstr = ice_fs_str_len(str);
    char ch = 0;

    if (lenstr == 0) return ICE_FS_FALSE;

    ch = str[lenstr - 1];
    return ((ch == '\\') || (ch == '/')) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

/* [INTERNAL] Returns count of slashes in string */
ICE_FS_API unsigned long ICE_FS_CALLCONV ice_fs_str_slashes(const char *str) {
    unsigned long slashes = 0,
                  lenstr = ice_fs_str_len(str),
                  i;

    if (lenstr == 0) return 0;

    for (i = 0; i < lenstr; i++) {
        char ch = str[i];
        if ((ch == '/') || (ch == '\\')) slashes++;
    }

    return slashes;
}

/* [INTERNAL] Returns count of dots in string */
ICE_FS_API unsigned long ICE_FS_CALLCONV ice_fs_str_dots(const char *str) {
    unsigned long dots = 0,
                  lenstr = ice_fs_str_len(str),
                  i;

    if (lenstr == 0) return 0;

    for (i = 0; i < lenstr; i++) {
        char ch = str[i];
        if (ch == '.') dots++;
    }

    return dots;
}

/* [INTERNAL] Returns ICE_FS_TRUE if string str1 is same to string str2 or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_str_same(const char *str1, const char *str2) {
    unsigned long len1 = ice_fs_str_len(str1),
                  len2 = ice_fs_str_len(str2),
                  count = 0, i;
    
    if ((len1 != len2) || (len1 == 0) || (len2 == 0)) return ICE_FS_FALSE;

    for (i = 0; i < len1; i++) {
        if (str1[i] == str2[i]) count++;
    }
    
    return (count == len1) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

/* [INTERNAL] Converts char to string and returns result on allocation success or NULL on allocation failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_str_char_to_str(char ch) {
    unsigned alloc_size = (2 * sizeof(char));
    char *res = 0;

    if (ch == 0) return 0;

    res = ICE_FS_MALLOC(alloc_size);
    if (res == 0) return 0;
    
    res[0] = ch;
    res[1] = 0;
    
    return res;
}

/* [INTERNAL] Returns substring of string from index from_idx to index to_idx on allocation success or NULL on allocation failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_str_sub(const char *str, unsigned long from_idx, unsigned long to_idx) {
    unsigned long i = 0,
                  count = 0,
                  lenstr = ice_fs_str_len(str),
                  len,
                  alloc_size;
    ice_fs_bool backwards = (to_idx < from_idx) ? ICE_FS_TRUE : ICE_FS_FALSE;
    char *res = 0;

    if ((str == 0) || ((to_idx >= lenstr) && (backwards == ICE_FS_FALSE))) return 0;
    
    len = (backwards == ICE_FS_TRUE) ? ((from_idx - to_idx) + 2) :
                                        ((to_idx - from_idx) + 2);
    alloc_size = (len * sizeof(char));

    if (from_idx == to_idx) {
        res = ice_fs_str_char_to_str(str[to_idx]);
        return res;
    }
    
    res = ICE_FS_MALLOC(alloc_size);
    if (res == 0) return 0;
    
    if (backwards == ICE_FS_TRUE) {
        for (i = to_idx; i <= from_idx; i++) {
            res[from_idx - i] = str[i];
            count++;
        }
    } else {
        for (i = from_idx; i <= to_idx; i++) {
            res[count] = str[i];
            count++;
        }
    }
    
    res[count] = 0;
    
    return res;
}

/* [INTERNAL] Returns allocated copy of string on allocation success or NULL on allocation failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_str_copy(const char *str) {
    unsigned long i, len = ice_fs_str_len(str);
    char* res = 0;
    
    if (len == 0) return 0;

    res = ICE_FS_MALLOC((len + 1) * sizeof(char));
    if (res == 0) return 0;

    for (i = 0; i < len; i++) res[i] = str[i];
    res[i] = 0;

    return res;
}

/* [INTERNAL] Splits string into array of strings for each delimiter and returns it on allocation success or NULL on allocation failure, arrlen is pointer to unsigned long integer to store length of resulted array */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_str_split(const char *str, char delim, unsigned long *arrlen) {
    unsigned long len = ice_fs_str_len(str),
                  arr_len = 0, repeat_count = 0, count = 0,
                  i1 = 0, i2 = 0, sets = 0,
                  i, alloc_size;
    char **res;

    if (len == 0) return 0;
    
    for (i = 0; i < len; i++) {
        unsigned long j = 0;
        
        if (str[i] == delim) {
            if (i == 0) {
                while (str[i] == delim) i++;
                i1 = i;
                while (str[i] != delim) i++;
            }
            
            while ((i < len - 1) && (str[i + j++] == delim)) {
                repeat_count++;
            }
            
            i += repeat_count;
            arr_len++;
            repeat_count = 0;
        }
    }
    
    if (arr_len == 0) return 0;
    if (str[len - 1] != delim) arr_len++;

    alloc_size = (arr_len * sizeof(char*));

    res = ICE_FS_MALLOC(alloc_size);
    if (res == 0) return 0;
    
    for (i = 0; i < len; i++) {
        if (str[i] == delim) {
            if (i == 0) {
                while (str[i] == delim) i++;
                i1 = i;
                while (str[i] != delim) i++;
            }
            
            i2 = i - 1;
            
            res[count] = ice_fs_str_sub(str, i1, i2);
            
            while (str[i] == delim) i++;
            i1 = i;
            
            sets++;
            count++;
        }
    }
    
    if (sets < arr_len) {
        res[count] = ice_fs_str_sub(str, i1, len - 1);
    }
    
    if (arrlen != 0) *arrlen = arr_len;
    
    return res;
}

/* [INTERNAL] Same like ice_fs_str_split but uses new line character '\n' as delimiter */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_str_splitlines(const char *str, unsigned long *arrlen) {
    return ice_fs_str_split(str, '\n', arrlen);
}

/* [INTERNAL] Returns number of string str2 matches in string str1, idxs can be pointer to array of unsigned long integers (To be Dynamically-Allocated) to store the matching indexes */
ICE_FS_API unsigned long ICE_FS_CALLCONV ice_fs_str_matches(const char *str1, const char *str2, unsigned long **idxs) {
    unsigned long len1 = ice_fs_str_len(str1),
                  len2 = ice_fs_str_len(str2),
                  char_matches = 0,
                  matches = 0,
                  alloc_size,
                  i;

    if ((len1 == 0) || (len2 == 0)) return 0;

    for (i = 0; i < len1; i++) {
        if ((str1[i] == str2[0]) && ((i + (len2 - 1)) < len1)) {
            unsigned long j;

            for (j = 0; j < len2; j++) {
                if (str1[i + j] == str2[j]) {
                    char_matches++;
                }
            }

            if (char_matches == len2) {
                matches++;
                char_matches = 0;
                i += len2;
            }
        }
    }
    
    if (idxs != 0) {
        unsigned long count = 0, *matches_idxs;
        
        alloc_size = (matches * sizeof(unsigned long));
        matches_idxs = ICE_FS_MALLOC(alloc_size);

        if (matches_idxs == 0) return 0;

        for (i = 0; i < len1; i++) {
            if ((str1[i] == str2[0]) && ((i + (len2 - 1)) < len1)) {
                unsigned long j;
                
                for (j = 0; j < len2; j++) {
                    if (str1[i + j] == str2[j]) {
                        char_matches++;
                    }
                }
                
                if (char_matches == len2) {
                    char_matches = 0;
                    matches_idxs[count] = i;
                    i += len2;
                }
                
                count++;
            }
        }
        
        *idxs = matches_idxs;
    }

    return matches;
}

/* Frees/Deallocates a String */
ICE_FS_API void ICE_FS_CALLCONV ice_fs_free_str(char *str) {
    ICE_FS_FREE(str);
    str = 0;
}

/* Frees array of strings, arrlen should be set to array length */
ICE_FS_API void ICE_FS_CALLCONV ice_fs_free_strarr(char **strs, unsigned long arrlen) {
    unsigned long i;

    if ((strs == 0) && (arrlen > 0)) return;
    
    for (i = 0; i < arrlen; i++) {
        ICE_FS_FREE(strs[i]);
        strs[i] = 0;
    }

    ICE_FS_FREE(strs);
    strs = 0;
}

/* Returns root of a path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_root(const char *path) {
    unsigned long i,
                  limit = 0,
                  alloc_size = 0,
                  len = ice_fs_str_len(path),
                  slashes = ice_fs_str_slashes(path);
    
    int win_special_case = 0;
    char *res = 0;

    if (len == 0) return 0;

    for (i = 0; i < len; i++) {
        char ch = path[i];
        
        if ((ch == '\\') || (ch == '/')) {
            limit = i + 1;
            break;
        }
    }
    
    win_special_case = (((slashes == 0) && (len == 2) && (path[len - 1] == ':')) ? 1 : 0);
    
    if (win_special_case == 1) limit = 2;
    if (limit == 0) return 0;
    
    alloc_size = limit;
    
    if (win_special_case == 0) {
        res = ICE_FS_MALLOC((alloc_size + 1) * sizeof(char));
    } else if (win_special_case == 1) {
        res = ICE_FS_MALLOC((alloc_size + 2) * sizeof(char));
    }
    
    if (res == 0) return 0;
    
    for (i = 0; i < alloc_size; i++) {
        res[i] = path[i];
    }
    
    if (win_special_case == 0) {
        res[i] = 0;
    } else if (win_special_case == 1) {
        res[i] = '\\';
        res[i + 1] = 0;
    }

    return res;
}

/* Returns ICE_FS_TRUE if the path is root or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_is_root(const char *path) {
    ice_fs_bool res;

    char *root_path = ice_fs_root(path);
    if (root_path == 0) return ICE_FS_FALSE;

    res = ice_fs_str_same(path, root_path);
    ice_fs_free_str(root_path);

    return res;
}

/* Concats 2 paths and returns result path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_concat_path(const char *path1, const char *path2) {
    unsigned long i,
                  alloc_size,
                  len1 = ice_fs_str_len(path1),
                  len2 = ice_fs_str_len(path2),
                  count = 0;
    ice_fs_bool end1, start2;
    char *res = 0;
    
    if (path1 == 0) {
        return 0;
    } else {
        end1 = ice_fs_str_ends_with_slash(path1);
    }
    
    if (path2 == 0) goto special_case;
    
    start2 = ice_fs_str_starts_with_slash(path2);
    
    alloc_size = len1 + len2 + 1;
    
    if ((end1 == ICE_FS_FALSE) && (start2 == ICE_FS_FALSE)) {
        alloc_size++;
    } else if ((end1 == ICE_FS_TRUE) && (start2 == ICE_FS_TRUE)) {
        alloc_size = alloc_size - 1;
    }
    
    res = ICE_FS_MALLOC(alloc_size * sizeof(char));
    if (res == 0) return 0;
    
    for (i = 0; i < len1; i++) {
        char ch = path1[i];
        
        if ((end1 == ICE_FS_TRUE) && (start2 == ICE_FS_TRUE) && (i == len1 - 1)) break;
        
        if ((ch == '\\') || (ch == '/')) {
#if defined(ICE_FS_MICROSOFT)
            res[count] = '\\';
#else
            res[count] = '/';
#endif
        } else {
            res[count] = ch;
        }
        
        count++;
    }
    
    if (end1 == start2) {
#if defined(ICE_FS_MICROSOFT)
        res[count] = '\\';
#else
        res[count] = '/';
#endif
        count++;
    }
    
    i = ((end1 == ICE_FS_TRUE) && (start2 == ICE_FS_TRUE)) ? 1 : 0;
    
    while (i < len2) {
        char ch = path2[i];
        
        if ((ch == '\\') || (ch == '/')) {
#if defined(ICE_FS_MICROSOFT)
            res[count] = '\\';
#else
            res[count] = '/';
#endif
        } else if (!((ch == '\\') || (ch == '/'))) {
            res[count] = ch;
        }
        
        count++;
        i++;
    }
    
    res[count] = 0;
    
    return res;

special_case:
    alloc_size = len1 + 1;
    
    res = ICE_FS_MALLOC(alloc_size * sizeof(char));
    if (res == 0) return 0;
    
    for (i = 0; i < len1; i++) {
        char ch = path1[i];
        
        if ((ch == '\\') || (ch == '/')) {
#if defined(ICE_FS_MICROSOFT)
            res[count] = '\\';
#else
            res[count] = '/';
#endif
        } else {
            res[count] = ch;
        }
        
        count++;
    }
    
    res[count] = 0;
    
    return res;
}

/* Returns file name with/without extension from path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_filename(const char *path, ice_fs_bool with_ext) {
    unsigned long i,
                  limit = 0,
                  limit_end = 0,
                  len = ice_fs_str_len(path),
                  dots_count = 0, dots = ice_fs_str_dots(path),
                  slashes_count = 0, slashes = ice_fs_str_slashes(path);

    if (len == 0) return 0;
    
    for (i = 0; i < len; i++) {
        char ch = path[i];
        
        if ((ch == '\\') || (ch == '/')) {
            slashes_count++;
            
            if (slashes_count == slashes) {
                limit = i + 1;
                break;
            }
        }
    }
    
    if (with_ext == ICE_FS_TRUE) {
        limit_end = len - 1;
    } else if (with_ext == ICE_FS_FALSE) {
        for (i = limit; i < len; i++) {
            char ch = path[i];
            
            if (ch == '.') {
                dots_count++;
                
                if (dots_count == dots) {
                    limit_end = i - 1;
                    break;
                }
            }
        }
    }
    
    return ice_fs_str_sub(path, limit, limit_end);
}

/* Returns file extension from path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_ext(const char *path) {
    unsigned long i,
                  alloc_size,
                  count = 0, limit = 0, len = ice_fs_str_len(path),
                  dots_count = 0, dots = ice_fs_str_dots(path);
    char *res = 0;

    if (len == 0) return 0;

    for (i = 0; i < len; i++) {
        if (path[i] == '.') {
            dots_count++;

            if (dots_count == dots) {
                limit = i + 1;
                break;
            }
        }
    }

    if (limit == 0) return 0;
    
    alloc_size = len - limit;
    res = ICE_FS_MALLOC((alloc_size + 1) * sizeof(char));
    if (res == 0) return 0;
    
    for (i = limit; i < len; i++) {
        res[count] = path[i];
        count++;
    }

    res[count] = 0;

    return res;
}

/* Returns ICE_FS_TRUE if extension of the path is ext or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_is_ext(const char *path, const char *ext) {
    ice_fs_bool res = ICE_FS_FALSE;
    char *path_ext = 0;
    
    if (path == 0) return res;
    
    path_ext = ice_fs_ext(path);
    if ((path_ext == 0) && (ext == 0)) return ICE_FS_TRUE;
    
    res = ice_fs_str_same(path_ext, ext);
    ice_fs_free_str(path_ext);

    return res;
}

/* Returns previous parent of a path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_prev_path(const char *path) {
    unsigned long i,
                  limit = 0, len = ice_fs_str_len(path),
                  slashes_count = 0, slashes = ice_fs_str_slashes(path);
    ice_fs_bool ends_with_slash;
    
    if ((len == 0) || (slashes == 0)) return 0;
    
    ends_with_slash = ice_fs_str_ends_with_slash(path);
    if (ends_with_slash == ICE_FS_TRUE) slashes_count++;

    for (i = 0; i < len; i++) {
        char ch = path[i];
        
        if ((ch == '\\') || (ch == '/')) {
            slashes_count++;
            
            if (slashes_count == slashes) {
                limit = i;
                break;
            }
        }
    }

    return ice_fs_str_sub(path, 0, limit);
}

/* Returns parents of path in array on allocation success or NULL on failure */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_path_parents(const char *path, unsigned long *results) {
    unsigned long i, slashes_count = ice_fs_str_slashes(path);
    char **res = 0;
    ice_fs_bool ends_with_slash = ice_fs_str_ends_with_slash(path);

    if (!(slashes_count > 1)) {
        if (results != 0) *results = 0;
        return res;
    }

    if (ends_with_slash == ICE_FS_TRUE) slashes_count = slashes_count - 1;
    res = ICE_FS_MALLOC(slashes_count * sizeof(char*));
    if (res == 0) return 0;

    for (i = 0; i < slashes_count; i++) {
        res[i] = ice_fs_prev_path(((i == 0) ? path : res[i - 1]));
    }
    
    if (results != 0) *results = slashes_count;

    return res;
}

/* Returns ICE_FS_TRUE if path exists or ICE_FS_FALSE if not */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_path_exists(const char *path) {
    struct stat info;
    int stat_res = stat(path, &info);

    return (stat_res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

/* Returns path of current working directory on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_cwd(void) {
    return getcwd(0, 0);
}

/* Returns path of home on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_home(void) {
#if defined(ICE_FS_MICROSOFT)
    const char *homedrive = getenv("HOMEDRIVE"),
               *homepath = getenv("HOMEPATH");

    return ice_fs_concat_path(homedrive, homepath);

#elif defined(ICE_FS_UNIX)
    const char *home = getenv("HOME");
    return ice_fs_str_copy(home);
#endif
}

/* Returns formatted path of a path depending on platform on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_format_path(const char *path) {
    unsigned long i, lenstr = ice_fs_str_len(path);
    char *res = 0;
    
    if (lenstr == 0) return 0;
    
    res = ICE_FS_MALLOC((lenstr + 1) * sizeof(char));
    if (res == 0) return 0;

    for (i = 0; i < lenstr; i++) {
        if ((path[i] == '\\') || (path[i] == '/')) {
#if defined(ICE_FS_MICROSOFT)
            res[i] = '\\';
#else
            res[i] = '/';
#endif
        } else {
            res[i] = path[i];
        }
    }

    res[i] = 0;

    return res;
}

/* Returns full path of a path on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_fullpath(const char *path) {
    ice_fs_object_type t = ice_fs_type(path);
    char *res = 0;
    ice_fs_bool is_cwd; 
#if defined(ICE_FS_MICROSOFT)
    unsigned long lenstr, alloc_add = 0, len = 0;
#endif
    if (path == 0) return 0;

    is_cwd = ice_fs_str_same(path, ".");
    if (is_cwd == ICE_FS_TRUE) return ice_fs_cwd();
    
#if defined(ICE_FS_MICROSOFT)
    len = (unsigned long)(GetFullPathNameA(path, 0, 0, 0));
    if (len == 0) return 0;
    
    alloc_add = ((unsigned long)(t + 1));
    
    res = ICE_FS_MALLOC((len + alloc_add) * sizeof(char));
    if (res == 0) return 0;
    
    lenstr = GetFullPathNameA(path, len, res, 0);
    if (lenstr == 0) {
        ice_fs_free_str(res);
        return 0;
    }
    
    res[len] = 0;
    
#elif defined(ICE_FS_UNIX)
    res = realpath(path, 0);
#endif
    
    return res;
}

/* Creates symbolic/hard link for object in path1 at path2, Retruns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_link(const char *path1, const char *path2, ice_fs_bool hard_link) {
    int link_res = 0;

#if defined(ICE_FS_MICROSOFT)
    ice_fs_object_type path_type;
    int type;
#endif

    if ((path1 == 0) || (path2 == 0)) return ICE_FS_FALSE;

#if defined(ICE_FS_MICROSOFT)
    path_type = ice_fs_type(path1);
    if (path_type == ICE_FS_OBJECT_TYPE_NONE) return ICE_FS_FALSE;

    type = ((path_type == ICE_FS_OBJECT_TYPE_DIR) ? 0x1 : 0x0);
    
    if (hard_link == ICE_FS_TRUE) {
        link_res = CreateHardLinkA(path1, path2, 0);
    } else if (hard_link == ICE_FS_FALSE) {
        link_res = CreateSymbolicLinkA(path1, path2, type);
    }

    return ((link_res != 0) ? ICE_FS_TRUE : ICE_FS_FALSE);

#elif defined(ICE_FS_UNIX)
    if (hard_link == ICE_FS_TRUE) {
        link_res = link(path1, path2);
    } else if (hard_link == ICE_FS_FALSE) {
        link_res = symlink(path1, path2);
    }

    return ((link_res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE);
#endif
}

/* Reads value from symbolic link file at specific path, Returns value on allocation success or NULL on failure */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_readlink(const char *path) {
#if defined(ICE_FS_MICROSOFT)
    void *h;
    unsigned long lenstr, len;
    char *res = 0, *read = 0;
    int close_res;

    if (path == 0) return 0;

    h = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (h == INVALID_HANDLE_VALUE) return 0;

    len = (unsigned long) GetFinalPathNameByHandleA(h, 0, 0, FILE_NAME_OPENED);
    if (len == 0) goto failure;

    read = ICE_FS_MALLOC((len + 2) * sizeof(char));
    if (read == 0) goto failure;
    read[len + 1] = 0;

    lenstr = (unsigned long) GetFinalPathNameByHandleA(h, read, len + 1, FILE_NAME_OPENED);
    if (lenstr == 0) {
        ice_fs_free_str(read);
        goto failure;
    }
    
    res = ice_fs_str_sub(read, 4, len + 2);
    if (res == 0) {
        ice_fs_free_str(read);
        goto failure;
    }
    
    close_res = CloseHandle(h);
    if (close_res == 0) {
        ice_fs_free_str(read);
        ice_fs_free_str(res);

        goto failure;
    }

    return res;

failure:
    (void) CloseHandle(h);
    return 0;

#elif defined(ICE_FS_UNIX)
    struct stat info;
    ssize_t len;
    char *res = 0;
    int call_res;

    if (path == 0) return 0;

    call_res = stat(path, &info);
    if (call_res == -1) return 0;
    
    len = info.st_size;
    res = ICE_FS_MALLOC((len + 1) * sizeof(char));
    if (res == 0) return 0;

    call_res = readlink(path, res, len);

    if (call_res == -1) {
        ice_fs_free_str(res);
        return 0;
    }

    res[len] = 0;

    return res;
#endif
}

/* Returns type of object in specific path, Returns ICE_FS_OBJECT_TYPE_NONE on failure if path does not exist or returns any of values does ice_fs_object_type enumeration has */
ICE_FS_API ice_fs_object_type ICE_FS_CALLCONV ice_fs_type(const char *path) {
    struct stat info;
    int res;

    if (path == 0) return ICE_FS_OBJECT_TYPE_NONE;
    
    res = stat(path, &info);
    if (res == -1) return ICE_FS_OBJECT_TYPE_NONE;

    return ((int)((info.st_mode & S_IFMT) == S_IFDIR)) ? ICE_FS_OBJECT_TYPE_DIR : ICE_FS_OBJECT_TYPE_FILE;
}

/* Reads content of file and returns the content on allocation success or NULL on failure, file_size is pointer to unsigned long integer that will store number of chars (bytes) the file has */
ICE_FS_API char* ICE_FS_CALLCONV ice_fs_file_content(const char *path, unsigned long *file_size) {
    struct stat info;
    ice_fs_bool alloc_done = ICE_FS_FALSE;
    int fd = -1, posixcall_res;
    off_t len;
#if defined(ICE_FS_MICROSOFT)
    __int64 read_size;
#elif defined(ICE_FS_UNIX)
    ssize_t read_size;
#endif
    char *res = 0;

    if (path == 0) return 0;
    
    posixcall_res = stat(path, &info);
    if (posixcall_res == -1) return 0;

    fd = ice_fs_open(path, O_RDONLY);
    if (fd == -1) return 0;
    
    len = info.st_size;

    res = ICE_FS_MALLOC((len + 1) * sizeof(char));
    if (res == 0) goto failure;
    alloc_done = ICE_FS_TRUE;

    read_size = read(fd, res, len);
    if (read_size == -1) goto failure;
    res[read_size] = 0;
    
    posixcall_res = close(fd);
    if (posixcall_res == -1) goto failure;

    if (file_size != 0) *file_size = len;
    
    return res;

failure:
    (void) close(fd);
    if (alloc_done == ICE_FS_TRUE) ice_fs_free_str(res);
    if (file_size != 0) *file_size = 0;

    return 0;
}

/* Creates file in path with content if doesn't exist or Appends to/Overwrites content of file in specific path if exists, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_file_write(const char *path, const char *content, ice_fs_bool append) {
    ice_fs_bool file_created;
    unsigned long len = ice_fs_str_len(content);
    int fd = 0, write_res, close_res;

    if ((path == 0) || (content == 0)) return ICE_FS_FALSE;

    file_created = ice_fs_create(path, ICE_FS_OBJECT_TYPE_FILE);
    if (file_created == ICE_FS_FALSE) return ICE_FS_FALSE;

    if (append == ICE_FS_TRUE) {
        fd = ice_fs_open(path, O_APPEND | O_WRONLY);
    } else if (append == ICE_FS_FALSE) {
        fd = ice_fs_open(path, O_TRUNC | O_APPEND | O_WRONLY);
    }
    
    if (fd == -1) return ICE_FS_FALSE;

    write_res = write(fd, content, len);
    if (write_res == -1) return ICE_FS_FALSE;

    close_res = close(fd);

    return (close_res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

/* Reads content of file, Returns the content in array of strings for each line on allocation success or NULL on failure, lines should be pointer to unsigned long integer to store count of lines the file has */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_file_lines(const char *path, unsigned long *lines) {
    unsigned long lines_count;
    char **res = 0, *file_content = 0;

    if (path == 0) return 0;
    
    file_content = ice_fs_file_content(path, 0);
    if (file_content == 0) {
        if (lines != 0) *lines = 0;
        return 0;
    }
    
    res = ice_fs_str_splitlines(file_content, &lines_count);
    ice_fs_free_str(file_content);
    
    if (lines != 0) *lines = lines_count;

    return res;
}

/* Changes current directory in the running program to another directory in path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_chdir(const char *path) {
    int res;
    
    if (path == 0) return ICE_FS_FALSE;

    res = chdir(path);
    return (res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

/* Returns directory informations with list of contents in path on success or NULL on failure */
ICE_FS_API ice_fs_dir ICE_FS_CALLCONV ice_fs_dir_content(const char *path) {
    ice_fs_dir res;
    unsigned lookup_state = 0;
    unsigned long items_count = 0;
    int close_res;

#if defined(ICE_FS_MICROSOFT)
    char *search_path = 0;
    ice_fs_bool ends_with_slash = ice_fs_str_ends_with_slash(path);
    WIN32_FIND_DATAA find_data;
    HANDLE find_handle = INVALID_HANDLE_VALUE;
    
    unsigned long i, len_add, len_search = ice_fs_str_len(path);
    ice_fs_bool alloc = ICE_FS_FALSE;
    
    if (path == 0) goto failure;

    len_add = ((ends_with_slash == ICE_FS_FALSE) ? 3 : 2);
    
    search_path = ICE_FS_MALLOC((len_search + len_add) * sizeof(char));
    if (search_path == 0) goto failure;
    alloc = ICE_FS_TRUE;
    
    for (i = 0; i < len_search; i++) search_path[i] = path[i];
    
    search_path[i] = ((len_add == 3) ? '\\' : '*');
    search_path[i + 1] = ((len_add == 3) ? '*' : 0);
    if (len_add == 3) search_path[i + 2] = 0;
    
    goto find;

find:
    find_handle = FindFirstFileA(search_path, &find_data);
    if (find_handle == INVALID_HANDLE_VALUE) goto failure;
    
    while (FindNextFileA(find_handle, &find_data) != 0) {
        ice_fs_bool cd = ice_fs_str_same(find_data.cFileName, ".");
        ice_fs_bool pd = ice_fs_str_same(find_data.cFileName, "..");
        
        if ((cd == ICE_FS_FALSE) && (pd == ICE_FS_FALSE)) {
            items_count++;
        
            if (lookup_state == 1) {
                unsigned long idx;
                idx = items_count - 1;
            
                res.items[idx].name = ice_fs_str_copy(find_data.cFileName);
            
                if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
                    res.items[idx].type = ICE_FS_OBJECT_TYPE_DIR;
                } else {
                    res.items[idx].type = ICE_FS_OBJECT_TYPE_FILE;
                }
            }
        }
    }
    
    close_res = FindClose(find_handle);
    if (close_res == 0) goto failure;

    goto checkout;

#elif defined(ICE_FS_UNIX)
    DIR *d;
    struct dirent *dir;
    
    if (path == 0) goto failure;

find:
    d = opendir(path);
    
    if (d != 0) {
        while ((dir = readdir(d)) != 0) {
            ice_fs_bool cd = ice_fs_str_same(dir->d_name, ".");
            ice_fs_bool pd = ice_fs_str_same(dir->d_name, "..");
            
            if ((cd == ICE_FS_FALSE) && (pd == ICE_FS_FALSE)) {
                items_count++;
                
                if (lookup_state == 1) {
                    unsigned long idx = items_count - 1;
                    char *path = 0;
                    
                    path = realpath(dir->d_name, 0);
                    if (path == 0) goto failure;
                    
                    res.items[idx].name = ice_fs_str_copy(dir->d_name);
                    res.items[idx].type = ice_fs_type(path);
                    
                    ice_fs_free_str(path);
                }
            }
        }

        close_res = closedir(d);
        if (close_res == -1) goto failure;
    } else {
        goto failure;
    }

    goto checkout;
#endif

checkout:
    if (lookup_state == 0) {
        res.items = ICE_FS_MALLOC(items_count * sizeof(ice_fs_object));
        if (res.items == 0) goto failure;
    }

    lookup_state++;

    if (lookup_state == 2) {
        res.items_count = items_count;
#if defined(ICE_FS_MICROSOFT)
        if (alloc == ICE_FS_TRUE) ice_fs_free_str(search_path);
#endif
        return res;
    }

    items_count = 0;
    goto find;

failure:
    res.items = 0;
    res.items_count = 0;
    
    return res;
}

/* Frees/Deallocates a directory information struct, dir should be pointer to the directory information struct that will be freed */
ICE_FS_API void ICE_FS_CALLCONV ice_fs_free_dir_content(ice_fs_dir *dir) {
    unsigned long i;

    if (dir == 0) return;

    for (i = 0; i < dir->items_count; i++) {
        ice_fs_free_str((char*)(dir->items[i].name));
    }

    ICE_FS_FREE(dir->items);
    dir->items = 0;
    dir->items_count = 0;
}

/* Searches in contents of directory for a specific file/directory by string, Returns array of strings that contains full path of founded items on allocation success or NULL on failure, results should be pointer to unsigned long integer that stores number of founded items */
ICE_FS_API char** ICE_FS_CALLCONV ice_fs_dir_search(const char *path, const char *str, unsigned long *results) {
    char **res = 0;
    unsigned long i, items_count = 0, lookup_state = 0, count = 0;
    ice_fs_dir d;

    if (path == 0) return 0;

    d = ice_fs_dir_content(path);
    if (d.items_count == 0) goto end;
    
    goto lookup;

lookup:
    for (i = 0; i < d.items_count; i++) {
        ice_fs_object_type t = d.items[i].type;
        char *fullpath = ice_fs_str_copy(d.items[i].name);
        unsigned long matches = ice_fs_str_matches(fullpath, str, 0);
        
        if (matches > 0) {
            items_count++;
            
            if (lookup_state == 1) {
                res[count] = ice_fs_concat_path(path, d.items[i].name);
                count++;
            }
        }
        
        if (t == ICE_FS_OBJECT_TYPE_DIR) {
            unsigned long found = 0;
            char **add = ice_fs_dir_search(fullpath, str, &found);
            items_count += found;
            
            if (lookup_state == 1) {
                unsigned long j;
                
                for (j = 0; j < found; j++) {
                    res[count] = ice_fs_str_copy(add[j]);
                    count++;
                }
            }
            
            ice_fs_free_strarr(add, found);
        }
        
        ice_fs_free_str(fullpath);
    }
    
    lookup_state++;
    
    if (lookup_state == 1) {
        res = ICE_FS_MALLOC(items_count * sizeof(char*));
        if (res == 0) goto end;
    }
    
    if (lookup_state == 2) {
        if (d.items_count > 0) ice_fs_free_dir_content(&d);
        if (results != 0) *results = items_count;
        
        return res;
    }
    
    items_count = 0;
    
    goto lookup;

end:
    if (d.items_count > 0) ice_fs_free_dir_content(&d);
    if (results != 0) *results = 0;
    return 0;
}

/* Creates file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_create(const char *path, ice_fs_object_type type) {
    ice_fs_bool res = ICE_FS_FALSE, exists;

    if ((path == 0) || (type == ICE_FS_OBJECT_TYPE_NONE)) return ICE_FS_FALSE;

    exists = ice_fs_path_exists(path);
    if (exists == ICE_FS_TRUE) goto done;
    
    if (type == ICE_FS_OBJECT_TYPE_FILE) {
        int fd, close_res;
        
        fd = ice_fs_open(path, O_CREAT);
        res = (fd == -1) ? ICE_FS_FALSE : ICE_FS_TRUE;
        
        close_res = close(fd);
        res = (close_res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
    
    } else if (type == ICE_FS_OBJECT_TYPE_DIR) {
        int call_res = ice_fs_mkdir(path);
        res = ((call_res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE);

        call_res = chmod(path, 0777);
        res = ((call_res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE);

    }
    
    return res;

done:
    res = ICE_FS_TRUE;
    return res;
}

/* Removes file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_remove(const char *path) {
    int res = -1;
    ice_fs_object_type type;

    if (path == 0) return ICE_FS_FALSE;

    type = ice_fs_type(path);

    if (type == ICE_FS_OBJECT_TYPE_FILE) {
        res = unlink(path);
    } else if (type == ICE_FS_OBJECT_TYPE_DIR) {
        res = rmdir(path);
    }

    return (res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
}

/* Clears content of file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_clear(const char *path) {
    ice_fs_object_type type;
    ice_fs_bool res = ICE_FS_FALSE;

    if (path == 0) return 0;

    type = ice_fs_type(path);

    if (type == ICE_FS_OBJECT_TYPE_FILE) {
        res = ice_fs_path_exists(path);
        if (res == ICE_FS_FALSE) return ICE_FS_FALSE;
        
        res = ice_fs_file_write(path, 0, ICE_FS_FALSE);

    } else if (type == ICE_FS_OBJECT_TYPE_DIR) {
        unsigned long i;
        ice_fs_dir d = ice_fs_dir_content(path);
        
        if (d.items_count == 0) return res;
        
        for (i = 0; i < d.items_count; i++) {
            ice_fs_object_type t = d.items[i].type;
            char *fullpath = ice_fs_concat_path(path, d.items[i].name);
            
            if (t == ICE_FS_OBJECT_TYPE_FILE) {
                res = ice_fs_remove(fullpath);
            } else if (t == ICE_FS_OBJECT_TYPE_DIR) {
                res = ice_fs_clear(fullpath);
            }
            
            ice_fs_free_str(fullpath);
            if (res == ICE_FS_FALSE) break;
        }
        
        ice_fs_free_dir_content(&d);
    }

    return res;
}

/* Copies file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_copy(const char *path1, const char *path2) {
    ice_fs_object_type t1, t2;
    
    if ((path1 == 0) || (path2 == 0)) return ICE_FS_FALSE;

    t1 = ice_fs_type(path1);
    t2 = ice_fs_type(path2);
    
    if ((t1 == ICE_FS_OBJECT_TYPE_DIR) && (t2 == ICE_FS_OBJECT_TYPE_DIR)) {
        unsigned long i;
        ice_fs_dir d = ice_fs_dir_content(path1);
        ice_fs_bool cp = ICE_FS_FALSE;
        
        if (d.items_count == 0) return cp;
        
        for (i = 0; i < d.items_count; i++) {
            char *fullpath1 = 0;
            char *fullpath2 = 0;
            ice_fs_object_type t = d.items[i].type;
            
            fullpath1 = ice_fs_concat_path(path1, d.items[i].name);
            fullpath2 = ice_fs_concat_path(path2, d.items[i].name);
            
            cp = ice_fs_create(fullpath2, t);
            
            if (t == ICE_FS_OBJECT_TYPE_FILE) {
                char *content = ice_fs_file_content(fullpath1, 0);
                cp = ice_fs_file_write(fullpath2, content, ICE_FS_FALSE);
                ice_fs_free_str(content);
            } else if (t == ICE_FS_OBJECT_TYPE_DIR) {
                cp = ice_fs_copy(fullpath1, fullpath2);
            }
            
            ice_fs_free_str(fullpath1);
            ice_fs_free_str(fullpath2);
            
            if (cp == ICE_FS_FALSE) break;
        }
        
        ice_fs_free_dir_content(&d);
        
        return cp;
        
    } else if ((t1 == ICE_FS_OBJECT_TYPE_FILE) && (t2 == ICE_FS_OBJECT_TYPE_FILE || t2 == ICE_FS_OBJECT_TYPE_NONE)) {
        char *content = ice_fs_file_content(path1, 0);
        ice_fs_bool write_res = ice_fs_file_write(path2, content, ICE_FS_FALSE);
        
        ice_fs_free_str(content);
        
        return write_res;
        
    } else if ((t1 == ICE_FS_OBJECT_TYPE_FILE) && (t2 == ICE_FS_OBJECT_TYPE_DIR)) {
        ice_fs_bool write_res;
        char *content, *filename, *path;
        
        content = ice_fs_file_content(path1, 0);
        filename = ice_fs_filename(path1, ICE_FS_TRUE);
        path = ice_fs_concat_path(path2, filename);
        
        write_res = ice_fs_file_write(path, content, ICE_FS_FALSE);
        
        ice_fs_free_str(content);
        ice_fs_free_str(filename);
        ice_fs_free_str(path);
        
        return write_res;
    }
    
    return ICE_FS_FALSE;
}

/* Moves file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_move(const char *path1, const char *path2) {
    int move_res;

    if ((path1 == 0) || (path2 == 0)) return ICE_FS_FALSE;

#if defined(ICE_FS_MICROSOFT)
    move_res = MoveFileA(path1, path2);
    return (move_res != 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
#elif defined(ICE_FS_UNIX)
    move_res = rename(path1, path2);
    return (move_res == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
#endif
}

/* Renames file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_rename(const char *path1, const char *path2) {
    return ice_fs_move(path1, path2);
}

/* Returns ICE_FS_TRUE if file/folder in specific path is empty or ICE_FS_FALSE if not empty */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_is_empty(const char *path) {
    ice_fs_object_type type;

    if (path == 0) return ICE_FS_FALSE;
    type = ice_fs_type(path);
    
    if (type == ICE_FS_OBJECT_TYPE_FILE) {
        struct stat info;
        int stat_res = stat(path, &info);
        if (stat_res == -1) return ICE_FS_FALSE;
        return (info.st_size == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
        
    } else if (type == ICE_FS_OBJECT_TYPE_DIR) {
        unsigned long items_count = 0;
        int close_res;

#if defined(ICE_FS_MICROSOFT)
        WIN32_FIND_DATAA find_data;
        HANDLE find_handle = INVALID_HANDLE_VALUE;
    
        unsigned long i, len_search = ice_fs_str_len(path);
        
        char *search_path = ICE_FS_MALLOC((len_search + 3) * sizeof(char));
        if (search_path == 0) return ICE_FS_FALSE;
        
        for (i = 0; i < len_search; i++) search_path[i] = path[i];
        
        search_path[i] = '\\';
        search_path[i + 1] = '*';
        search_path[i + 2] = 0;
        
        find_handle = FindFirstFileA(search_path, &find_data);
        ice_fs_free_str(search_path);

        if (find_handle == INVALID_HANDLE_VALUE) return ICE_FS_FALSE;
        
        while (FindNextFileA(find_handle, &find_data) != 0) {
            ice_fs_bool cd = ice_fs_str_same(find_data.cFileName, ".");
            ice_fs_bool pd = ice_fs_str_same(find_data.cFileName, "..");
            
            if ((cd == ICE_FS_FALSE) && (pd == ICE_FS_FALSE)) {
                items_count++;
            }
        }
        
        close_res = FindClose(find_handle);
        if (close_res == 0) return ICE_FS_FALSE;
        
#elif defined(ICE_FS_UNIX)
        DIR *d;
        struct dirent *dir;
    
        d = opendir(path);
    
        if (d != 0) {
            while ((dir = readdir(d)) != 0) {
                ice_fs_bool cd = ice_fs_str_same(dir->d_name, ".");
                ice_fs_bool pd = ice_fs_str_same(dir->d_name, "..");
            
                if ((cd == ICE_FS_FALSE) && (pd == ICE_FS_FALSE)) {
                    items_count++;
                }
            }

            close_res = closedir(d);
            if (close_res == -1) return ICE_FS_FALSE;
        } else return ICE_FS_FALSE;
#endif
        return (items_count == 0) ? ICE_FS_TRUE : ICE_FS_FALSE;
    }
    
    return ICE_FS_FALSE;
}

/* Retrieves [last modification, last status change, last access] date of file/directory and stores info in info struct by pointing to, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ICE_FS_API ice_fs_bool ICE_FS_CALLCONV ice_fs_get_date(const char *path, ice_fs_date_type date_type, ice_fs_date *info) {
    struct stat pinfo;
    time_t t;
    struct tm *pt;
    int call_res = -1;

    ice_fs_date_season season;
    ice_fs_date_month month;

    if ((path == 0) || (info == 0)) return ICE_FS_FALSE;

    call_res = stat(path, &pinfo);
    if (call_res == -1) return ICE_FS_FALSE;

    if (date_type == ICE_FS_LAST_ACCESS_DATE) t = pinfo.st_atime;
    else if (date_type == ICE_FS_LAST_MODIFICATION_DATE) t = pinfo.st_mtime;
    else if (date_type == ICE_FS_LAST_STATUS_CHANGE_DATE) t = pinfo.st_ctime;
    else return ICE_FS_FALSE;

    pt = localtime(&t);
    
    month = pt->tm_mon + 1;
    
    if (month == 12 || month == 1 || month == 2) {
        season = ICE_FS_DATE_SEASON_WINTER;
    } else if (month == 3 || month == 4 || month == 5) {
        season = ICE_FS_DATE_SEASON_SPRING;
    } else if (month == 6 || month == 7 || month == 8) {
        season = ICE_FS_DATE_SEASON_SUMMER;
    } else if (month == 9 || month == 10 || month == 11) {
        season = ICE_FS_DATE_SEASON_AUTUMN;
    } else {
        season = ICE_FS_DATE_SEASON_UNKNOWN;
    }

    info->str = ctime(&t);
    info->epoch = (unsigned long) t;
    info->seconds = pt->tm_sec;
    info->minutes = pt->tm_min;
    info->hour = pt->tm_hour;
    info->week_day = pt->tm_wday + 1;
    info->month_day = pt->tm_mday;
    info->year_day = pt->tm_yday;
    info->month = month;
    info->season = season;
    info->year = (pt->tm_year + 1900);

    return ICE_FS_TRUE;
}

#endif  /* ICE_FS_IMPL */
#endif  /* ICE_FS_H */

/*
ice_fs.h is dual-licensed, Choose the one you prefer!

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
