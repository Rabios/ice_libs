/* Define the implementation of the library and include it */
#define ICE_FS_IMPL 1
#include "ice_fs.h"

#include <stdio.h>

/* Helper */
#define trace(fname, str) (void) printf("[%s : line %d] %s() => %s\n", __FILE__, __LINE__, fname, str);

int main(void) {
    /* Struct that contains modification date information */
    ice_fs_date mod_date;

    /* To store result of called functions */
    ice_fs_bool res;

    /* Create a directory of name "surprise" if does not exists */
    res = ice_fs_create("surprise", ICE_FS_OBJECT_TYPE_DIR);
    
    /* If the function failed to create the directory, Trace error then terminate the program */
    if (res == ICE_FS_FALSE) {
        trace("ice_fs_create", "ERROR: failed to create a directory!");
        return -1;
    }

    /* Create a file with content written with no append (overwrite) */
    res = ice_fs_file_write("surprise/iCe_SeCrEt_MeSsAgE.txt", "ice_libs makes C more enjoyable! :)", ICE_FS_FALSE);
    
    /* If the function failed to create the file, Trace error then terminate the program */
    if (res == ICE_FS_FALSE) {
        trace("ice_fs_file_write", "ERROR: failed to create a file!");
        return -1;
    }

    /* Rename the created file to another name in same path */
    res = ice_fs_rename("surprise/iCe_SeCrEt_MeSsAgE.txt", "surprise/ice_secret_message.txt");
    
    /* If the function failed to rename the file, Trace error then terminate the program */
    if (res == ICE_FS_FALSE) {
        trace("ice_fs_rename", "ERROR: failed to rename the created file!");
        return -1;
    }

    /* Get modification date of the created file */
    res = ice_fs_get_date("surprise/ice_secret_message.txt", ICE_FS_LAST_MODIFICATION_DATE, &mod_date);
    
    /* If the function failed to retrieve modification date of the created file, Trace error then terminate the program */
    if (res == ICE_FS_FALSE) {
        trace("ice_fs_get_date", "ERROR: failed to retrieve modification date of the created file!");
        return -1;
    }

    /* Print the modification date of the created file */
    (void) printf("modification date of surprise/ice_secret_message.txt: %s\n", mod_date.str);

    return 0;
}
