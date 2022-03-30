local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef

ffi_cdef([[
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
unsigned long ice_fs_str_len(const char *str);

/* [INTERNAL] Returns ICE_FS_TRUE if string str starts with slash or backslash, Or ICE_FS_FALSE if not */
ice_fs_bool ice_fs_str_starts_with_slash(const char *str);

/* [INTERNAL] Returns ICE_FS_TRUE if string str ends with slash or backslash, Or ICE_FS_FALSE if not */
ice_fs_bool ice_fs_str_ends_with_slash(const char *str);

/* [INTERNAL] Returns count of slashes in string */
unsigned long ice_fs_str_slashes(const char *str);

/* [INTERNAL] Returns count of dots in string */
unsigned long ice_fs_str_dots(const char *str);

/* [INTERNAL] Returns ICE_FS_TRUE if string str1 is same to string str2 or ICE_FS_FALSE if not */
ice_fs_bool ice_fs_str_same(const char *str1, const char *str2);

/* [INTERNAL] Returns substring of string from index from_idx to index to_idx on allocation success or NULL on allocation failure */
char* ice_fs_str_sub(const char *str, unsigned long from_idx, unsigned long to_idx);

/* [INTERNAL] Returns allocated copy of string on allocation success or NULL on allocation failure */
char* ice_fs_str_copy(const char *str);

/* [INTERNAL] Splits string into array of strings for each delimiter and returns it on allocation success or NULL on allocation failure, arrlen is pointer to unsigned long integer to store length of resulted array */
char** ice_fs_str_split(const char *str, char delim, unsigned long *arrlen);

/* [INTERNAL] Same like ice_fs_str_split but uses new line character '\n' as delimiter */
char** ice_fs_str_splitlines(const char *str, unsigned long *arrlen);

/* [INTERNAL] Returns number of string str2 matches in string str1, idxs can be pointer to array of unsigned long integers (To be Dynamically-Allocated) to store the matching indexes */
unsigned long ice_fs_str_matches(const char *str1, const char *str2, unsigned long **idxs);

/* Frees/Deallocates a String */
void ice_fs_free_str(char *str);

/* Frees array of strings, arrlen should be set to array length */
void ice_fs_free_strarr(char **strs, unsigned long arrlen);

/* Returns root of a path on allocation success or NULL on failure */
char* ice_fs_root(const char *path);

/* Returns ICE_FS_TRUE if the path is root or ICE_FS_FALSE if not */
ice_fs_bool ice_fs_is_root(const char *path);

/* Concats 2 paths and returns result path on allocation success or NULL on failure */
char* ice_fs_concat_path(const char *path1, const char *path2);

/* Returns file name with/without extension from path on allocation success or NULL on failure */
char* ice_fs_filename(const char *path, ice_fs_bool with_ext);

/* Returns file extension from path on allocation success or NULL on failure */
char* ice_fs_ext(const char *path);

/* Returns ICE_FS_TRUE if extension of the path is ext or ICE_FS_FALSE if not */
ice_fs_bool ice_fs_is_ext(const char *path, const char *ext);

/* Returns previous parent of a path on allocation success or NULL on failure */
char* ice_fs_prev_path(const char *path);

/* Returns parents of path in array on allocation success or NULL on failure */
char** ice_fs_path_parents(const char *path, unsigned long *results);

/* Returns ICE_FS_TRUE if path exists or ICE_FS_FALSE if not */
ice_fs_bool ice_fs_path_exists(const char *path);

/* Returns path of current working directory on allocation success or NULL on failure */
char* ice_fs_cwd(void);

/* Returns path of home on allocation success or NULL on failure */
char* ice_fs_home(void);

/* Returns formatted path of a path depending on platform on allocation success or NULL on failure */
char* ice_fs_format_path(const char *path);

/* Returns full path of a path on allocation success or NULL on failure */
char* ice_fs_fullpath(const char *path);

/* Creates symbolic/hard link for object in path1 at path2, Retruns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_link(const char *path1, const char *path2, ice_fs_bool hard_link);

/* Reads value from symbolic link file at specific path, Returns value on allocation success or NULL on failure */
char* ice_fs_readlink(const char *path);

/* Returns type of object in specific path, Returns ICE_FS_OBJECT_TYPE_NONE on failure if path does not exist or returns any of values does ice_fs_object_type enumeration has */
ice_fs_object_type ice_fs_type(const char *path);

/* Reads content of file and returns the content on allocation success or NULL on failure, file_size is pointer to unsigned long integer that will store number of chars (bytes) the file has */
char* ice_fs_file_content(const char *path, unsigned long *file_size);

/* Creates file in path with content if doesn't exist or Appends to/Overwrites content of file in specific path if exists, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_file_write(const char *path, const char *content, ice_fs_bool append);

/* Reads content of file, Returns the content in array of strings for each line on allocation success or NULL on failure, lines should be pointer to unsigned long integer to store count of lines the file has */
char** ice_fs_file_lines(const char *path, unsigned long *lines);

/* Changes current directory in the running program to another directory in path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_chdir(const char *path);

/* Returns directory informations with list of contents in path on success or NULL on failure */
ice_fs_dir ice_fs_dir_content(const char *path);

/* Frees/Deallocates a directory information struct, dir should be pointer to the directory information struct that will be freed */
void ice_fs_free_dir_content(ice_fs_dir *dir);

/* Searches in contents of directory for a specific file/directory by string, Returns array of strings that contains full path of founded items on allocation success or NULL on failure, results should be pointer to unsigned long integer that stores number of founded items */
char** ice_fs_dir_search(const char *path, const char *str, unsigned long *results);

/* Creates file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_create(const char *path, ice_fs_object_type type);

/* Removes file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_remove(const char *path);

/* Clears content of file/folder in specific path, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_clear(const char *path);

/* Copies file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_copy(const char *path1, const char *path2);

/* Moves file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_move(const char *path1, const char *path2);

/* Renames file/folder from path1 to path2, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_rename(const char *path1, const char *path2);

/* Returns ICE_FS_TRUE if file/folder in specific path is empty or ICE_FS_FALSE if not empty */
ice_fs_bool ice_fs_is_empty(const char *path);

/* Retrieves [last modification, last status change, last access] date of file/directory and stores info in info struct by pointing to, Returns ICE_FS_TRUE on success or ICE_FS_FALSE on failure */
ice_fs_bool ice_fs_get_date(const char *path, ice_fs_date_type date_type, ice_fs_date *info);
]])

return ffi_load("ice_fs")
