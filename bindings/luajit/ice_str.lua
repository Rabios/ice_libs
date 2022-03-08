local ffi = require("ffi")
local ffi_load = ffi.load
local ffi_cdef = ffi.cdef

ffi_cdef([[
/* ============================== Data Types ============================== */

/* Boolean Enum, To avoid including stdbool.h */
typedef enum ice_str_bool {
    ICE_STR_FALSE   = -1,
    ICE_STR_TRUE    = 0
} ice_str_bool;

/* ============================== Functions ============================== */

/* Returns string length */
unsigned long ice_str_len(const char *str);

/* Returns substring of string from index from_idx to index to_idx on allocation success or NULL on allocation failure */
char* ice_str_sub(const char *str, unsigned long from_idx, unsigned long to_idx);

/* Concats 2 strings and returns resulted string on allocation success or NULL on allocation failure */
char* ice_str_concat(const char *str1, const char *str2);

/* Returns string consists of string str2 inserted in string str1 at index idx on allocation success or NULL on allocation failure */
char* ice_str_insert(const char *str1, const char *str2, unsigned long idx);

/* Returns number of string str2 matches in string str1, idxs can be pointer to array of unsigned long integers (To be Dynamically-Allocated) to store the matching indexes */
unsigned long ice_str_matches(const char *str1, const char *str2, unsigned long **idxs);

/* Replaces string str1 in string str with string str2 and returns result string on allocation success or NULL on allocation failure */
char* ice_str_rep(const char *str, const char *str1, const char *str2);

/* Returns string repeated multiple times on allocation success or NULL on allocation failure */
char* ice_str_dup(const char *str, unsigned long times);

/* Returns copy of string but malloc-ed on allocation success or NULL on allocation failure */
char* ice_str_copy(const char *str);

/* Returns reverse of string on allocation success or NULL on allocation failure */
char* ice_str_rev(const char *str);

/* Converts char to string and returns result on allocation success or NULL on allocation failure */
char* ice_str_char_to_str(char ch);

/* Returns ICE_STR_TRUE if str1 is same as str2, Else returns ICE_STR_FALSE */
ice_str_bool ice_str_same(const char *str1, const char *str2);

/* Returns uppercased version of string on allocation success or NULL on allocation failure */
char* ice_str_upper(const char *str);

/* Returns lowercased version of string on allocation success or NULL on allocation failure */
char* ice_str_lower(const char *str);

/* Returns capital case version of string on allocation success or NULL on allocation failure */
char* ice_str_cap(const char *str);

/* Splits string into array of strings for each delimiter and returns it on allocation success or NULL on allocation failure, arrlen is pointer to unsigned long integer to store length of resulted array */
char** ice_str_split(const char *str, char delim, unsigned long *arrlen);

/* Same like ice_str_split but uses new line character '\n' as delimiter */
char** ice_str_splitlines(const char *str, unsigned long *arrlen);

/* Returns string which is concat of all strings from array strs on allocation success or NULL on allocation failure, arrlen should be defined for the iteration over the array and delimiter can be used to join each string with (Though it can be NULL as optional parameter) */
char* ice_str_join(const char **strs, unsigned long arrlen, char delim);

/* Returns ICE_STR_TRUE if string str1 starts with string str2, Else returns ICE_STR_FALSE */
ice_str_bool ice_str_begins(const char *str1, const char *str2);

/* Returns ICE_STR_TRUE if string str1 ends with string str2, Else returns ICE_STR_FALSE */
ice_str_bool ice_str_ends(const char *str1, const char *str2);

/* Returns ICE_STR_TRUE if string str ends with char ch, Else returns ICE_STR_FALSE */
ice_str_bool ice_str_last_char(const char *str, char ch);

/* Returns char codes of the string as allocated array on allocation success or NULL on allocation failure, arrlen is pointer to unsigned long integer to store length of integer array (Though you can NULL it if you know the length) */
int* ice_str_to_bytes(const char *str, unsigned long *arrlen);

/* Returns string from char codes on allocation success or NULL on allocation failure, arrlen should be set to array length */
char* ice_str_from_bytes(const int *chars, unsigned long arrlen);

/* Frees a String */
void ice_str_free(char *str);

/* Frees array of char codes */
void ice_str_free_bytes(int *bytes);

/* Frees array of strings, arrlen should be set to array length */
void ice_str_free_arr(char **arr, unsigned long arrlen);
]])

return ffi_load("ice_str")
