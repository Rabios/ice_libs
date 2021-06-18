local ffi = require("ffi")

ffi.cdef([[
typedef enum {
    ICE_STR_TRUE    = 0,
    ICE_STR_FALSE   = -1,
} ice_str_bool;

int          ice_str_len(char* str);                                // Returns length of string.
int          ice_str_arr_len(char** arr);                           // Returns length of array of strings.
char*        ice_str_sub(char* str, int from, int to);              // Returns substring from (from -> to) index.
char*        ice_str_strdup(char* str);                             // Returns NULL-terminates string?
char*        ice_str_concat(char* s1, char* s2);                    // Joins 2 strings in one and returns result.
char*        ice_str_rep(char* str, int count);                     // Returns string repeated multiple times.
char*        ice_str_char(char* str, int index);                    // Returns char at index as string.
ice_str_bool ice_str_match(char* s1, char* s2);                     // Returns ICE_STR_TRUE if 2 strings are same or ICE_STR_FALSE if not.
char*        ice_str_upper(char* str);                              // Returns uppercased string of str.
char*        ice_str_lower(char* str);                              // Returns lowercased string of str.
char*        ice_str_capitalize(char* str);                         // Returns capitalized string of str.
char**       ice_str_split(char* str, char delim);                  // Split string into array by delimiter/separator (char) and return result.
char**       ice_str_splitlines(char* str);                         // Split string into array by newline char and return the array.
char*        ice_str_join(char** strs);                             // Joins strings from array into one string and returns it.
char*        ice_str_join_with_delim(char** strs, char delim);      // Joins strings from array into one string and returns it.
ice_str_bool ice_str_begin(char* s1, char* s2);                     // Returns ICE_STR_TRUE if string s1 starts with string s2 or ICE_STR_FALSE if not.
ice_str_bool ice_str_end(char* s1, char* s2);                       // Returns ICE_STR_TRUE if string s1 ends with string s2 or ICE_STR_FALSE if not.
ice_str_bool ice_str_end_char(char* str, char ch);                  // Returns ICE_STR_TRUE if string ends with character or ICE_STR_FALSE if not.
char*        ice_str_rev(char* str);                                // Returns reversed string of str.
void         ice_str_free(char* str);                               // Frees the string.
void         ice_str_arr_free(char** arr);                          // Frees array of strings.
]])

local lib = ffi.load("ice_str")

for k, v in pairs(lib) do
  _G[k] = lib[k]
end
