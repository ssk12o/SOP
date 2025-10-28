# Lecture 2 & 3 - Filesystem

---

## POSIX file permissions

```shell
echo "hello" > /tmp/hello.txt
stat /tmp/hello.txt
```

```shell
chmod 0700 /tmp/hello.txt
stat /tmp/hello.txt
```

## Linux file types

##### Regular files

```shell
echo "test" > /tmp/test.txt
stat /tmp/test.txt
```

```shell
cat /tmp/test.txt
```

```shell
echo "something" > /tmp/test.txt
```

##### Directories

```shell
mkdir /tmp/test.dir
stat /tmp/test.dir
```

```shell
cat /tmp/test.dir
```

```shell
strace cat /tmp/test.dir > /dev/null
```

```shell
echo "something" > /tmp/test.dir
```

##### Symbolic links

```shell
ln -sf /tmp/test.txt /tmp/test.txt.link
stat /tmp/test.txt.link
ll /tmp/test*
```

```shell
cat /tmp/test.txt.link
```

```shell
echo "linkwrite" > /tmp/test.txt.link
```

##### Character devices

```shell
ll /proc/$$/fd
```

```shell
stat /dev/pts/1
```

```shell
cat /dev/pts/1 # Run from a different terminal
```

```shell
echo "something" > /dev/pts/1 # Run from a different terminal
```

##### Block devices

```shell
lsblk
```

```shell
stat /dev/nvme0n1p1
```

```shell
sudo cat /dev/nvme0n1p1
```

```shell
sudo xxd -l512 /dev/nvme0n1p1
```

_No write testing as I like my disk structure :)_

##### Sockets

```shell
stat /run/docker.sock
```

```shell
cat /run/docker.sock 
```

```shell
echo "something" > /run/docker.sock
```

##### FIFOs

```shell
mkfifo /tmp/test.fifo
stat /tmp/test.fifo
```

```shell
cat /tmp/test.fifo
```

```shell
echo "something" > /tmp/test.fifo # Run in different terminal
```

## Filesystem mounting

```shell
mount
```

```shell
df
```

## Linux kernel structures

Per-process pointer to descriptor table:
https://elixir.bootlin.com/linux/v6.11.3/source/include/linux/sched.h#L1121

Pointers to open files:
https://elixir.bootlin.com/linux/v6.11.3/source/include/linux/fdtable.h#L46

Open file structure:
https://elixir.bootlin.com/linux/v6.11.3/source/include/linux/fs.h#L996

I-node pointee:
https://elixir.bootlin.com/linux/v6.11.3/source/include/linux/fs.h#L1019

## Low-level syscalls

### open() syscall

```shell
gcc -o /tmp/open -g open.c
rm -f /tmp/no_such_file.txt
/tmp/open /tmp/no_such_file.txt
```

```shell
gcc -o /tmp/open -g open.c
echo "hello" > /tmp/there_is_such_file.txt
/tmp/open /tmp/there_is_such_file.txt
```

```shell
cat /tmp/there_is_such_file.txt
```

```shell
gcc -o /tmp/append -g append.c
echo "hello" > /tmp/append.txt
/tmp/append /tmp/append.txt
```

Create file which doesn't exist:

```shell
gcc -o /tmp/create_file -g create_file.c
rm -f /tmp/create_file.txt
/tmp/create_file /tmp/create_file.txt
ls -l /tmp/create_file.txt
```

_Try to remove last open() argument and see what happens_

Try to re-create with different perm:

```shell
gcc -DMODE=0666 -o /tmp/create_file -g create_file.c
/tmp/create_file /tmp/create_file.txt
ls -l /tmp/create_file.txt
```

Remove the file and re-run the creation:

```shell
rm -f /tmp/create_file.txt
/tmp/create_file /tmp/create_file.txt
ls -l /tmp/create_file.txt
```

```shell
umask
```

```shell
rm -f /tmp/create_file.txt
gcc -DUMASK=0000 -DMODE=0666 -o /tmp/create_file -g create_file.c
/tmp/create_file /tmp/create_file.txt
ls -l /tmp/create_file.txt
```

Exclusive open

```shell
gcc -o /tmp/excl -g excl.c
/tmp/excl /tmp/lock.txt
```

Descriptor limit

```shell
gcc -o /tmp/descriptor_limit -g descriptor_limit.c
/tmp/descriptor_limit
```

```shell
ulimit -a
```

### read()/write() syscalls

Standard FDS

```shell
gcc -o /tmp/standard_fds -g -fsanitize=address standard_fds.c
/tmp/standard_fds
```

File sequential access

```shell
echo "test" > /tmp/test.txt
gcc -o /tmp/byteread -g byteread.c
/tmp/byteread /tmp/test.txt
```

Observe contents of `/proc/<pid>/fd` and `/proc/<pid>/fdinfo` during runtime.

Read Without O_NONBLOCK

From short file

```shell
echo -ne "x" > /tmp/short.txt
gcc -o /tmp/read -g read.c
/tmp/read /tmp/short.txt
```

From longer file

```shell
echo -ne "abcdefghijk" > /tmp/short.txt
gcc -o /tmp/read -g read.c
/tmp/read /tmp/short.txt
```

From STDIN

```shell
gcc -o /tmp/read -g read.c
/tmp/read stdin
```

From FIFO

From other terminal:
```shell
mkfifo /tmp/nonblock.fifo
cat > /tmp/nonblock.fifo
```

```shell
gcc -o /tmp/read -g read.c
/tmp/read /tmp/nonblock.fifo
```

Read With O_NONBLOCK

From short file

```shell
echo -ne "x" > /tmp/short.txt
gcc -o /tmp/read -g read.c -DNONBLOCK
/tmp/read /tmp/short.txt
```

From longer file

```shell
echo -ne "abcdefghijk" > /tmp/short.txt
gcc -o /tmp/read -g read.c -DNONBLOCK
/tmp/read /tmp/short.txt
```

From STDIN

```shell
gcc -o /tmp/read -g read.c -DNONBLOCK
/tmp/read stdin
```

From FIFO

From other terminal:
```shell
mkfifo /tmp/nonblock.fifo
cat > /tmp/nonblock.fifo
```

```shell
gcc -o /tmp/read -g read.c -DNONBLOCK
/tmp/read /tmp/nonblock.fifo
```

writev syscall

```shell
gcc -o /tmp/writev -g writev.c
/tmp/writev /tmp/writev.txt
```

### stat() syscall

```shell
gcc -o /tmp/stat -g stat.c
/tmp/stat /usr/bin/gcc
```

### lseek() syscall

```shell
echo -ne "abcdefgh" > /tmp/lseek.txt
gcc -o /tmp/lseek -g lseek.c
/tmp/lseek /tmp/lseek.txt
```

_Question: how to query current file position using lseek()?_

### Overlapping file descriptors

#### dup()

```shell
echo -ne > /tmp/dup.txt
gcc -o /tmp/dup_write -g dup_write.c
/tmp/dup_write /tmp/dup.txt aaa bbb
```

From other terminal:
```shell
watch -n0.1 cat /tmp/dup.txt
```

### Directory operations

```shell
gcc -o /tmp/readdir -g readdir.c
/tmp/readdir .
```

```shell
strace /tmp/readdir . > /dev/null
```

### Hardlinks

```shell
ln /tmp/test.txt /tmp/test2.txt
stat /tmp/test.txt
stat /tmp/test2.txt
```

```shell
cat /tmp/test2.txt
```

## C File streams

```shell
gcc -o /tmp/fileno -g fileno.c
/tmp/fileno
```

```shell
gcc -o /tmp/api_mixing -g api_mixing.c
/tmp/api_mixing
```

```shell
gcc -o /tmp/fopen -g fopen.c
/tmp/fopen
```

### Stream buffering

Default stdout buffering - line

```shell
gcc -DBUFF_MODE=_IOLBF -o /tmp/stream_buffering -g stream_buffering.c
/tmp/stream_buffering
```

```shell
strace --trace=write /tmp/stream_buffering > /dev/null
```

Change to nonbuffered:

```shell
gcc -DBUFF_MODE=_IONBF -o /tmp/stream_buffering -g stream_buffering.c
/tmp/stream_buffering
```

```shell
strace --trace=write /tmp/stream_buffering > /dev/null
```

Change to fully buffered:

```shell
gcc -DBUFF_MODE=_IOFBF -o /tmp/stream_buffering -g stream_buffering.c
/tmp/stream_buffering
```

```shell
strace --trace=write /tmp/stream_buffering > /dev/null
```

### EOF testing

Read from stdin:

```shell
gcc -o /tmp/eof -g eof.c
/tmp/eof
```

Read from file:

```shell
echo "I" >> /tmp/eof.txt
echo "like" >> /tmp/eof.txt
echo "OPS" >> /tmp/eof.txt
/tmp/eof /tmp/eof.txt
```

What if we call scanf() on a stream with EOF indicator set but file has grown in the meantime?

### Input errors

```shell
gcc -o /tmp/scanf_error -g scanf_error.c
/tmp/scanf_error
```

### Stream position

```shell
gcc -o /tmp/ftell ftell.c
/tmp/ftell
```

```shell
/tmp/ftell /tmp/ftell.txt # Observe contents of /tmp/ftell.txt during run 
```
