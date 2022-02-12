# Lab: Exploring Directories in UNIX

In this lab, we will be using the POSIX interface to explore the directory structure of a UNIX machine. Let's see how `man` pages can help us figure out what the provided code is doing.

`DIR` is simply a type that represents a directory stream. 

### `opendir`
```
       #include <sys/types.h>
       #include <dirent.h>

       DIR *opendir(const char *name);
       
DESCRIPTION:       
       The opendir() function opens a directory stream corresponding to
       the directory name, and returns a pointer to the directory
       stream.  The stream is positioned at the first entry in the
       directory.
```

### `dirent`
The main data structure in POSIX for representating a directory is the `dirent` struct, defined as follows.

```
struct dirent {
    ino_t          d_ino;       /* inode number */
    off_t          d_off;       /* offset to the next dirent */
    unsigned short d_reclen;    /* length of this record */
    unsigned char  d_type;      /* type of file; not supported
                                   by all file system types */
    char           d_name[256]; /* filename */
};
```
The two fields of the `dirent` struct that are important to us are `d_name` and `d_type`, described below.
```
      d_type This field contains a value indicating the file type,
              making it possible to avoid the expense of calling
              lstat(2) if further actions depend on the type of the
              file.

              When a suitable feature test macro is defined
              (_DEFAULT_SOURCE on glibc versions since 2.19, or
              _BSD_SOURCE on glibc versions 2.19 and earlier), glibc
              defines the following macro constants for the value
              returned in d_type:

              DT_BLK This is a block device.

              DT_CHR This is a character device.

              DT_DIR This is a directory.

              DT_FIFO
                     This is a named pipe (FIFO).

              DT_LNK This is a symbolic link.

              DT_REG This is a regular file.

              DT_SOCK
                     This is a UNIX domain socket.

              DT_UNKNOWN
                     The file type could not be determined.

              Currently, only some filesystems (among them: Btrfs, ext2,
              ext3, and ext4) have full support for returning the file
              type in d_type.  All applications must properly handle a
              return of DT_UNKNOWN.

       d_name This field contains the null terminated filename.  See
              NOTES.

       The data returned by readdir() may be overwritten by subsequent
       calls to readdir() for the same directory stream.
```
Most of the files that we encounter are files of type `DT_REG`. i.e., files that we would conventionally call a file, and `DT_DIR`, i.e., files that are <i>directories</i> (or "folders" if this was Windows).
### `readdir`
```
       #include <dirent.h>
       
       struct dirent *readdir(DIR *dirp);

DESCRIPTION:
       The readdir() function returns a pointer to a dirent structure
       representing the next directory entry in the directory stream
       pointed to by dirp.  It returns NULL on reaching the end of the
       directory stream or if an error occurred.
```



Notice that all of this information needed to understand the provided code was obtained by simply consulting the `man` pages. You are more than welcome to use online resources, but you are encouraged to consult the `man` pages first. In future labs, you will be responsible for visiting the `man` pages.
## Your Task

Your task is to modify the provided code so that it prints the relative path names of all the regular files within the directory specified by `argv[1]`. You might find it useful to revisit your data-structure notes, namely, [<i>queues</i>](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)) and [<i>breadth-first search</i>](https://en.wikipedia.org/wiki/Breadth-first_search).
