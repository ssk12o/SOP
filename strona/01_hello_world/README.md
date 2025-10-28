# Lecture 1 - Introduction

### interrupts

```shell
watch -n0.1 "cat /proc/interrupts | tail -n25"
```

### syscalls and strace

Compile hello world executable:

```shell
gcc -o helloC -g -Wall hello.c
./helloC
```

Run it under `strace`:

```shell
strace ./helloC > /dev/null
```

Compile 32 bit assembly version:

```shell
nasm -f elf32 hello32.asm -o hello32.o
gcc -m32 -o hello32 -nostartfiles -nostdlib -nodefaultlibs -nolibc -static -OS hello32.o
./hello32
```

Run it under `strace`:

```shell
strace ./hello32 > /dev/null
```

Compile 64 bit assembly version:

```shell
nasm -f elf64 hello64.asm -o hello64.o
gcc -o hello64 -nostartfiles -nostdlib -nodefaultlibs -nolibc -static -OS hello64.o
./hello64
```

Run it under `strace`:

```shell
strace ./hello64 > /dev/null
```

Compile two fizzbuzz versions:
```shell
gcc -o fizzbuzz_buffered -O2 fizzbuzz_buffered.c
gcc -o fizzbuzz_direct -O2 fizzbuzz_direct.c
```

Run two versions and compare execution time (run in system terminal):
```shell
time ./fizzbuzz_buffered > /dev/null
```

```shell
time ./fizzbuzz_direct > /dev/null
```

Compare strace logs:

```shell
strace ./fizzbuzz_buffered > /dev/null
```

```shell
strace ./fizzbuzz_direct > /dev/null
```
