# Laboratorium L0

## Biblioteczka

#### man 3p fdopendir
fdopendir, opendir — open directory associated with file descriptor

#include <dirent.h>

DIR *fdopendir(int fd);

DIR *opendir(const char *dirname);

#### man 3p readdir
readdir, readdir_r — read a directory

#include <dirent.h>

struct dirent *readdir(DIR *dirp);
int readdir_r(DIR *restrict dirp, struct dirent *restrict entry, struct dirent **restrict result);

#### closedir


#### man 3p fstat
fstatat, lstat, stat — get file status

#include <fcntl.h>
#include <sys/stat.h>

int fstatat(int fd, const char *restrict path, struct stat *restrict buf, int flag);

int lstat(const char *restrict path, struct stat *restrict buf);

int stat(const char *restrict path, struct stat *restrict buf);

#### man sys_stat.h
stats filetype macros

man 3p fdopendir (tylko opis opendir)
man 3p closedir
man 3p readdir
#### man 0p dirent.h

man 3p fstatat (tylko opis stat i lstat)
man sys_stat.h
man 7 inode (pierwsza połowa sekcji "The file type and mode")

#### man 3p getcwd
getcwd — get the pathname of the current working directory

#include <unistd.h>

char *getcwd(char *buf, size_t size);

#### man 3p chdir
chdir — change working directory

#include <unistd.h>

int chdir(const char *path);

#### man 3p nftw
nftw — walk a file tree with said function

#include <ftw.h>

int nftw(const char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int fd_limit, int flags);

#### man 3p fopen
fopen — open a stream

#include <stdio.h>

FILE *fopen(const char *restrict pathname, const char *restrict mode);

       r or rb              Open file for reading.

       w or wb              Truncate to zero length or create file for writing.

       a or ab              Append; open or create file for writing at end-of-file.

       r+ or rb+ or r+b     Open file for update (reading and writing).

       w+ or wb+ or w+b     Truncate to zero length or create file for update.

       a+ or ab+ or a+b     Append; open or create file for update, writing at end-of-file.


#### man 3p fclose
fclose — close a stream

#include <stdio.h>

int fclose(FILE *stream);

The fclose() function shall cause the stream pointed to by stream to be flushed and the associated file to be closed. Any unwritten buffered data for the stream shall be written  to  the file; any unread buffered data shall be discarded



#### man 3p fseek
fseek, fseeko — reposition a file-position indicator in a stream

#include <stdio.h>

int fseek(FILE *stream, long offset, int whence);

int fseeko(FILE *stream, off_t offset, int whence);


#### man 3p rand

rand, rand_r, srand — pseudo-random number generator

#include <stdlib.h>

int rand(void);

int rand_r(unsigned *seed);

void srand(unsigned seed);


#### man 3p unlink




#### man 3p umask




<fcntl.h> i <unistd.h>



#### man 3p open
open, openat — open file

#include <sys/stat.h>

#include <fcntl.h>

int open(const char *path, int oflag, ...);

int openat(int fd, const char *path, int oflag, ...);



#### man 3p close
close — close a file descriptor

#include <unistd.h>

int close(int fildes);


#### man 3p read
pread, read — read from a file

#include <unistd.h>

ssize_t pread(int fildes, void *buf, size_t nbyte, off_t offset);

ssize_t read(int fildes, void *buf, size_t nbyte);




#### man 3p write
pwrite, write — write on a file

#include <unistd.h>

ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset);

ssize_t write(int fildes, const void *buf, size_t nbyte);




#### man 3p mknod



 
#### opis makra TEMP_FAILURE_RETRY




#### man 0p sys_uio.h


#### man 3p writev


#### man 3p getopt
getopt, optarg, opterr, optind, optopt — command option parsing

#include <unistd.h>

int getopt(int argc, char * const argv[], const char *optstring);

extern char *optarg;

extern int opterr, optind, optopt;

#### man 3p strtol
strtol, strtoll — convert a string to a long integer

#include <stdlib.h>

long strtol(const char *restrict nptr, char **restrict endptr, int base);

long long strtoll(const char *restrict nptr, char **restrict endptr, int base)



## misc
#### never ever use printf(argv[i]) !!!!