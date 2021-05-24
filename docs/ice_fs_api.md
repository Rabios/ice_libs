# ice_fs.h Documentation

### Enums

```c
typedef enum {
    ICE_FS_TRUE    = 0,
    ICE_FS_FALSE   = -1,
} ice_fs_bool;
```

### Definitions

```c
// Implements ice_fs source code, Works same as #pragma once
#define ICE_FS_IMPL

#define ICE_FS_EXTERN  // Extern functions of the library with extern keyword (Enabled by default)
#define ICE_FS_STATIC  // Makes functions of the library static with static keyword
#define ICE_FS_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_FS_CALLCONV_VECTORCALL
#define ICE_FS_CALLCONV_FASTCALL
#define ICE_FS_CALLCONV_STDCALL
#define ICE_FS_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_FS_MICROSOFT       // Microsoft platforms
#define ICE_FS_UNIX            // Elsewhere

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_FS_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
#define ICE_FS_DLLEXPORT
#define ICE_FS_DLLIMPORT

// Custom memory allocators
#define ICE_FS_MALLOC(sz)           // malloc(sz)
#define ICE_FS_CALLOC(n, sz)        // calloc(n, sz)
#define ICE_FS_REALLOC(ptr, sz)     // realloc(ptr, sz)
#define ICE_FS_FREE(ptr)            // free(ptr)
```

### Functions

```c
char*       ice_fs_home(void);                                      // Returns home directory.
char*       ice_fs_root(char* f);                                   // Returns root directory.
char*       ice_fs_current_dir(void);                               // Returns current directory program running from.
char*       ice_fs_previous_dir(char* dir);                         // Returns previous directory.
char*       ice_fs_file_dir(char* dir);                             // Returns directory of file from path.
ice_fs_bool ice_fs_change_dir(char* dir);                           // Changes directory, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_remove_dir(char* dir);                           // Removes directory, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_copy_dir(char* d1, char* d2);                    // Copies directory from directory to another, , Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_remove_file(char* dir);                          // Removes file, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_rename_file(char* d1, char* d2);                 // Renames file, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_rename_dir(char* d1, char* d2);                  // Renames directory, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_copy_file(char* d1, char* d2);                   // Copies file from path to another, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
char*       ice_fs_dir(char* dir);                                  // Returns directory formatted depending on Operating System.
char*       ice_fs_join_dir(char* d1, char* d2);                    // Returns merge of 2 directories.
char*       ice_fs_join_dirs(char** dirs);                          // Returns result of joining all dirs.
char**      ice_fs_split_dir(char* dir, char delim);                // Returns array of directories splitted depending on delimiter.
char**      ice_fs_dir_list(char* dir);                             // Returns list of available directories/files in directory.
ice_fs_bool ice_fs_dir_exists(char* dir);                           // Returns ICE_FS_TRUE if directory exists or ICE_FS_FALSE if not.
ice_fs_bool ice_fs_create_dir(char* dir);                           // Creates directory if not exist, Returns ICE_FS_TRUE if directory exists/created or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_is_file(char* dir);                              // Returns ICE_FS_TRUE if path is file or ICE_FS_FALSE if not.
ice_fs_bool ice_fs_is_dir(char* dir);                               // Returns ICE_FS_TRUE if path is directory or ICE_FS_FALSE if not.
ice_fs_bool ice_fs_create_file(char* name);                         // Creates empty file with name in append mode and closes it, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_write(char* name, char* content);                // Writes string to file with name, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_clear(char* name);                               // Clears content of file, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_file_exists(char* fname);                        // Returns ICE_FS_TRUE if file exists or ICE_FS_FALSE if not.
char*       ice_fs_full_file_path(char* fname);                     // Returns full file path of file with name.
ice_fs_bool ice_fs_is_file_ext(char* fname, char* ext);             // Returns ICE_FS_TRUE if file extension is ext or ICE_FS_FALSE if not.
char*       ice_fs_file_ext(char* fname);                           // Returns file extension.
char*       ice_fs_file_name(char* dir);                            // Returns file name from path with extension.
char*       ice_fs_dir_name(char* dir);                             // Returns last directory name from path.
char*       ice_fs_name_no_ext(char* fname);                        // Returns file name from path without extension.
char*       ice_fs_get_line(char* fname, int l);                    // Returns line from file with name (Lines index starts from 0).
ice_fs_bool ice_fs_edit_line(char* fname, int l, char* content);    // Changes line of file with name (Lines index starts from 0), Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
ice_fs_bool ice_fs_remove_line(char* fname, int l);                 // Removes line of file with name (Lines index starts from 0), Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure.
char**      ice_fs_lines(char* fname);                              // Returns lines of file with name in array.
int         ice_fs_lines_count(char* fname);                        // Returns count of lines in file.
char*       ice_fs_file_content(char* fname);                       // Returns all content of file.
```
