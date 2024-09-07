#include "./littlefs/lfs.h"
#include "./bd/lfs_filebd.h"

// variables used by the filesystem
lfs_t lfs;
lfs_file_t file;

// configuration of the filesystem is provided by this struct
const struct lfs_config cfg = {
    // block device operations
    .read  = lfs_filebd_read,
    .prog  = lfs_filebd_prog,
    .erase = lfs_filebd_erase,
    .sync  = lfs_filebd_sync,

    // block device configuration
    .read_size = 16,
    .prog_size = 16,
    .block_size = 4096,
    .block_count = 128,
    .block_cycles = 500,
    .cache_size = 16,
    .lookahead_size = 16,
    .compact_thresh = -1
};


// entry point
int main(void) {
    // Return variables
    int status = 0; // Errors
    uint32_t boot_count = 0; // Boot Count

    // Mount Files
    status = lfs_mount(&lfs, &cfg);
    if (status != 0) {\

        status = lfs_format(&lfs, &cfg);
        if(status != 0){
            printf("Error Formating File, Error Code : %d", status);
            return status;
        }


        status = lfs_mount(&lfs, &cfg);
        if(status != 0){
            printf("Error Mounting File, Error Code : %d", status);
            return status;
        }
    }

    // Open File
    status = lfs_file_open(&lfs, &file, "boot_count.txt", LFS_O_RDWR | LFS_O_CREAT);
    if(status != 0){
        printf("Error Opening File, Error Code : %d", status);
        return status;
    }

    /*
    // Read File
    status = lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));
    if(status != 0){
        printf("Error Reading File, Error Code : %d", status);
        return status;
    }
    */

    // update boot count
    boot_count += 1;


    /*
    // Rewind File
    status = lfs_file_rewind(&lfs, &file);
    if(status != 0){
        printf("Error Rewind File, Error Code : %d", status);
        return status;
    }
    */

    // Write File
    status = lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));
    if(status != 0){
        printf("Error Writing File, Error Code : %d", status);
        return status;
    }
    
    // Close File
    status = lfs_file_close(&lfs, &file);
    if(status != 0){
        printf("Error Rewind File, Error Code : %d", status);
        return status;
    }

    // Unmount File
    status = lfs_unmount(&lfs);
    if(status != 0){
        printf("Error Writing File, Error Code : %d", status);
        return status;
    }

    // print the boot count
    printf("boot_count: %d\n", boot_count);
}