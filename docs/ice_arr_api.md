# ice_arr.h Documentation

### Enums

```c
typedef enum ice_arr_bool {
    ICE_ARR_TRUE = 0,
    ICE_ARR_FALSE = -1,
} ice_arr_bool;
```

### Definitions

```c
// Typedefs
typedef void (*ice_arr_iter_func)(double n);            // Function to be used by ice_arr_foreach to iterate over array nums.
typedef int (*ice_arr_res_func)(double a, double b);    // Comparison function for sort, returns 1 on true and 0 on false.

// Array struct
typedef struct ice_arr_array {
    double* arr;    // Array content which contains numbers (Allocated by ICE_ARR_MALLOC)
    int len;        // Array length
    int real_len;   // Real allocation length (x1.5 array length, Increases when pushing elements if array's length bigger than real_len)
} ice_arr_array;

// Definitions
// Implements ice_arr source code, Works same as #pragma once
#define ICE_ARR_IMPL

#define ICE_ARR_EXTERN  // Extern functions of the library with extern keyword (Enabled by default) (Enabled by default)
#define ICE_ARR_STATIC  // Makes functions of the library static with static keyword
#define ICE_ARR_INLINE  // Inline functions of the library with inline keyword

// Call conventions (You could define one of these to set compiler calling convention)
#define ICE_ARR_CALLCONV_VECTORCALL
#define ICE_ARR_CALLCONV_FASTCALL
#define ICE_ARR_CALLCONV_STDCALL
#define ICE_ARR_CALLCONV_CDECL

// Platforms could be defined (But not forced to...)
#define ICE_ARR_MICROSOFT      // Microsoft platforms (Not autodefined -> using Unix)

// If no platform defined, This definition will define itself
// This definition sets platform depending on platform-specified C compiler definitions
#define ICE_ARR_PLATFORM_AUTODETECTED

// In case you want to build DLL on Microsoft Windows!
#define ICE_ARR_DLLEXPORT
#define ICE_ARR_DLLIMPORT

// Custom memory allocators
#define ICE_ARR_MALLOC(sz)              // malloc(sz)
#define ICE_ARR_CALLOC(n, sz)           // calloc(n, sz)
#define ICE_ARR_REALLOC(ptr, sz)        // realloc(ptr, sz)
#define ICE_ARR_FREE(ptr)               // free(ptr)
```

### Functions

```c
ice_arr_array  ice_arr_new(int len);                                                    // Creates empty array with length defined.
double         ice_arr_get(ice_arr_array arr, int index);                               // Gets element from index of array, Returns double.
void           ice_arr_set(ice_arr_array* arr, int index, double val);                  // Sets element in indexo f array to double value.
int            ice_arr_len(ice_arr_array arr);                                          // Returns length of array, Same as arr.len
void           ice_arr_pop(ice_arr_array* arr);                                         // Removes last element of array and zeroing it.
void           ice_arr_shift(ice_arr_array* arr);                                       // Removes first array element.
void           ice_arr_push(ice_arr_array* arr, double val);                            // Adds element to end of array.
void           ice_arr_rev(ice_arr_array* arr);                                         // Reverses array.
void           ice_arr_free(ice_arr_array arr);                                         // Frees array content, Freeing memory.
void           ice_arr_fill(ice_arr_array* arr, double val);                            // Fills all array with one value.
void           ice_arr_clear(ice_arr_array* arr);                                       // Fills all array with 0.
double         ice_arr_sum(ice_arr_array arr);                                          // Returns sum of all array elements as double.
ice_arr_array  ice_arr_first(ice_arr_array arr, int elems);                             // Returns first array elements by count as new array.
ice_arr_array  ice_arr_last(ice_arr_array arr, int elems);                              // Returns last array elements by count as new array.
ice_arr_array  ice_arr_concat(ice_arr_array a1, ice_arr_array a2);                      // Returns new array from combining first and second array.
ice_arr_bool   ice_arr_match(ice_arr_array a1, ice_arr_array a2);                       // If elements of first array matches elements of second array and also matches in length, Returns ICE_ARR_TRUE if true of ICE_ARR_FALSE if false.
ice_arr_array  ice_arr_sub(ice_arr_array arr, int from, int to);                        // Returns Subarray (Array of elements from index from to index to).
ice_arr_bool   ice_arr_includes(ice_arr_array arr, double val);                         // If array includes number val then returns ICE_ARR_TRUE, Else returns ICE_ARR_FALSE.
int            ice_arr_matches(ice_arr_array arr, double val);                          // Returns number of matches val exists in array.
void           ice_arr_rem(ice_arr_array* arr, int index);                              // Removes element of array at index
ice_arr_array  ice_arr_without(ice_arr_array arr, double val);                          // Returns array of arr elements but without numbers with value val if exists in array.
ice_arr_array  ice_arr_clone(ice_arr_array arr, int n);                                 // Returns array cloned by times into array, Ex. if n is 3 for array [1, 0], That means [1, 0, 1, 0, 1, 0]
ice_arr_array  ice_arr_rest(ice_arr_array arr, int index);                              // Returns array of arr elements but without element at index. 
ice_arr_array  ice_arr_unique(ice_arr_array arr);                                       // Returns array of unique elements that isn't repeated.
int            ice_arr_first_index(ice_arr_array arr, double val);                      // Returns first index where element with value val exists.
int            ice_arr_last_index(ice_arr_array arr, double val);                       // Returns last index where element with value val exists.
ice_arr_array  ice_arr_unshift(ice_arr_array arr, double val);                          // Pushes element with value val from beginning of array.
ice_arr_array  ice_arr_diff(ice_arr_array a1, ice_arr_array a2);                        // Returns array containing differences of elements of 2 arrays.
ice_arr_array  ice_arr_range(int i);                                                    // Returns array containing elements with values from 0 to i
double         ice_arr_min(ice_arr_array arr);                                          // Returns smaller number in array.
double         ice_arr_max(ice_arr_array arr);                                          // Returns biggest number in array.
ice_arr_array  ice_arr_compact(ice_arr_array arr);                                      // Returns array of array arr elements but without 0 values.
ice_arr_array  ice_arr_tail(ice_arr_array arr);                                         // Returns array of arr elements but without first element.
ice_arr_array  ice_arr_intersect(ice_arr_array a1, ice_arr_array a2);                   // Returns array of elements that intersects by both 2 arrays.
void           ice_arr_foreach(ice_arr_array arr, ice_arr_iter_func f);                 // Iterates over arr by elements, And executes f for each element in array.
ice_arr_array  ice_arr_union(ice_arr_array a1, ice_arr_array a2);                       // Similar to ice_arr_intersect but also with elements that does not exist in one of arrays.
void           ice_arr_rotate(ice_arr_array* arr, int times);                           // Rotates array to left by times.
void           ice_arr_sort(ice_arr_array* arr);                                        // Sorts array from smaller to bigger via Quicksort.
void           ice_arr_sort_ex(ice_arr_array* arr, ice_arr_res_func f);                 // Sorts array but using function that compares between 2 elements of array.
void           ice_arr_move(ice_arr_array* a1, int from_index, int elems_count, int to_index, ice_arr_array* a2);   // Move elements with count of elems_count of a2 to a1 from from_index to to_index.
```
