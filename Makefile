
all:
	gcc -Wall grepfs.c `pkg-config fuse --cflags --libs` -o grepfs

