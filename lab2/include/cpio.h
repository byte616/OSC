#ifndef __CPIO_H
#define __CPIO_H

#define CPIO_BASE 0x20000000
#define HEADER_SIZE 110 
# define ALIGN4(x) (((x) + 3) & ~3)

typedef struct cpio_newc_header {
    char c_magic[6];    // set to "070701" (newc format CPIO)
    char c_ino[8];      // inode
    char c_mode[8];     // permission
    char c_uid[8];      // owner ID
    char c_gid[8];      // group ID
    char c_nlink[8];    // number of links to this file
    char c_mtime[8];    // final revise timestamp
    char c_filesize[8]; // file length
    char c_devmajor[8]; 
    char c_devminor[8];
    char c_rdevmajor[8];
    char c_rdevminor[8];
    char c_namesize[8]; // pathname length (including null)
    char c_check[8];    // can ignore
} cpio_header;

void cpio_ls();
void cpio_cat();

#endif
