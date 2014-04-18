grepfs
======

fuse pseudo filesystem that searches a single file 

Rationale 
======

I often grep the same files over and over.


Usage
======

```sh
grepfs [fuse options] [file] [mountpoint]

# search [file] for thing
cat [mountpoint]/thing
```
