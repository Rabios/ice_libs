/* Define the implementation of the library and include it! */
#define ICE_FS_IMPL 1
#include "ice_fs.h"

/* Include the "Standard C I/O Library" */
#include <stdio.h>

/* Where magic happens... ;) */
void tree(const char *path, int indent) {
    unsigned long i;
    ice_fs_dir d = ice_fs_dir_content(path);
    
    /* If no items in path then break, Else iterate... */
    if (d.items_count == 0) return;
    
    for (i = 0; i < d.items_count; i++) {
        ice_fs_object o = d.items[i];
        
        char *curr_path = ice_fs_concat_path(path, o.name),
             *file_path;
        
        /* If failed to concat paths then break, Else continue with listing directory items... */
        if (curr_path == 0) {
            (void) printf("tree: failed to process directory info!\n");
            return;
        }
        
        /* Fetch the filename with extension from result path, If failed then break, Else continue with listing the item */
        file_path = ice_fs_filename(curr_path, ICE_FS_TRUE);
        
        if (file_path == 0) {
            (void) printf("tree: failed to process directory info!\n");
            return;
        }
        
        /* Get type of the concat result path and list item with name and type, Also if the path is directory then iterate over it... */
        (void) printf("%*s<%s> %s\n", indent, "", ((o.type == ICE_FS_OBJECT_TYPE_DIR) ? "DIR" : "FILE"), file_path);
        
        if (o.type == ICE_FS_OBJECT_TYPE_DIR) tree(curr_path, indent + 4);
        
        /* Free allocated strings as we no longer using them. */
        ice_fs_free_str(file_path);
        ice_fs_free_str(curr_path);
    }
    
    /* Free directory content as we no longer deal with it. */
    ice_fs_free_dir_content(&d);
}

/* Entry point of our program */
int main(int argc, char **argv) {
    /* We have to determine if path is passed and it's for a directory... */
    ice_fs_object_type t;
    
    /* If no path argument passed, Then terminate the program. */
    if (argc < 2) {
        (void) printf("tree: Directory path not passed!\n");
        return -1;
    }
    
    /* Else, check the type of the path and if it's directory then tree and iterate! */
    t = ice_fs_type(argv[1]);
    
    if (t != ICE_FS_OBJECT_TYPE_DIR) {
        (void) printf("tree: Path does not exist, Or path passed is not for a directory!\n");
        return -1;
    }
    
    (void) printf("<DIR> %s\n", argv[1]);
    
    tree(argv[1], 4);
    
    return 0;
}
