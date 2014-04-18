#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "grepfs.h"
#include "grep.h"

// default filesize for getattr
#define FSIZE 100

// real path of "mounted" file
char *fpath = NULL;

static int grepfs_getattr(const char *path, struct stat *stbuf)
{
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else {
        stbuf->st_mode = S_IFREG | 0666;
        stbuf->st_nlink = 1;
        stbuf->st_size = FSIZE;
    }

    return 0;
}

static int grepfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    path++;
    FILE *f = fopen(fpath, "r");
    if (f == NULL) {
        memcpy(buf, "fail!!\n", 6);
        return 6;
    }

    char res = grep(buf, path, f);
    //if (buf == NULL) {
    //    memcpy(buf, "res", 3);
    //    return 3;
    //}

    fclose(f);

    memcpy(buf, &res, strlen(&res));

    return strlen(&res);
    //return 4;
}

static int grepfs_open(const char *path, struct fuse_file_info *fi)
{
    return 0;
}

static struct fuse_operations grepfs_fuse = {
    .getattr = grepfs_getattr,
    .open = grepfs_open,
    .read = grepfs_read,
};

int grepfs_main(int argc, char *argv[], char *path)
{
    fpath = path;
    return fuse_main(argc, argv, &grepfs_fuse, NULL);
}
