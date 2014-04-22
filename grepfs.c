#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "grepfs.h"

#define CWD_BUF_SIZE 1024

// real path of "mounted" file
const char *help = "missing arguments\n";

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("%s", help);
        return 1;
    }

    char *mountpoint = argv[argc-1];
    char *file = argv[argc-2];

    if (file == NULL || strlen(file) == 1 || mountpoint == NULL) {
        printf("%s", help);
        return 1;
    }

    argv[argc-2] = argv[argc-1];
    argc--;

    // not an absolute path
    if (file[0] != '/') {
        char* fbuf = malloc(CWD_BUF_SIZE);
        char* path = getcwd(fbuf, CWD_BUF_SIZE);
        if (path == NULL) {
            return 1;
        }

        // alloc path + file + /
        path = realloc(path, strlen(file) + strlen(path) + 1);
        path = strcat(path, "/");
        file = strcat(path, file);
    }

    printf("mounting %s at %s\n", file, mountpoint);

    return grepfs_main(argc, argv, file);
}

