
all:
	gcc -Wall -g grepfs_fuse.c grepfs.c `pkg-config fuse --cflags --libs` -o grepfs

