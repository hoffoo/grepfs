#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "grepfs.h"

// default filesize for getattr
#define FSIZE 100

// real path of "mounted" file
char *fpath = NULL;

// match line in file
char* match(const char* regex, FILE* f)
{
    char* buf = NULL;
    size_t len = 0;
    size_t read = getline(&buf, &len, f);

    if (read == -1 || buf == NULL) {
        free(buf);
        return NULL;
    }
    
    int match = strlen(regex);
    int k = 0;
    int i = 0;
    for(; k < len; k++) {
        for (; i < match; i++) {
            if (regex[i] != buf[k]) {
                break;
            }

            if (i == match - 1) {
                return buf;
            }
        }
    }

    free(buf);
    return "";
}

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
    // remove leading /
    path++;
    FILE *f = fopen(fpath, "r");
    if (f == NULL) {
        return 0;
    }

    char* res; 
    while ((res = match(path, f)) != NULL) {
        if (strlen(res) > 0) {
            buf = realloc(buf, strlen(res)+1);
            memcpy(buf, res, strlen(res)+1);
            break; // found a match, break
        }
    }

    fclose(f);

    return strlen(buf);
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
