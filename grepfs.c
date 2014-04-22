#include <string.h>
#include <stdio.h>

#include "grepfs.h"

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

    return grepfs_main(argc, argv, file);
}

