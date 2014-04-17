#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <string.h>
#include <fcntl.h>

static int grepfs_getattr(const char *path, struct stat *stbuf)
{
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else {
        stbuf->st_mode = S_IFREG | 0600;
        stbuf->st_nlink = 1;
        stbuf->st_size = 0;
    }

    return 0;
}

static int grepfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    const char *str = "hello world\n";
    memcpy(buf, str, strlen(str));
    return strlen(str);
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

int main(int argc, char *argv[])
{
    fuse_main(argc, argv, &grepfs_fuse, NULL);
    return 0;
}
