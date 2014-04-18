grepfs
======

fuse pseudo filesystem that searches a single file 

RATIONALE
======

I often grep the same files over and over.


USAGE
======

```sh
grepfs [fuse options] [file] [mountpoint]

# search [file] for thing
cat [mountpoint]/thing
```

LICENSE
=======

MIT
