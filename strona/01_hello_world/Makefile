all: hello hello32 hello64 fizzbuzz_buffered fizzbuzz_direct

hello: hello.c
	gcc -o hello -Wall hello.c

hello32: hello32.asm
	nasm -f elf32 hello32.asm -o hello32.o
	gcc -m32 -o hello32 -nostartfiles -nostdlib -nodefaultlibs -nolibc -static -OS hello32.o

hello64: hello64.asm
	nasm -f elf64 hello64.asm -o hello64.o
	gcc -o hello64 -nostartfiles -nostdlib -nodefaultlibs -nolibc -static -OS hello64.o

fizzbuzz_buffered: fizzbuzz_buffered.c
	gcc -o fizzbuzz_buffered -O2 fizzbuzz_buffered.c

fizzbuzz_direct: fizzbuzz_direct.c
	gcc -o fizzbuzz_direct -O2 fizzbuzz_direct.c

clean:
	rm -f hello hello32.o hello32 hello64.o hello64 fizzbuzz_buffered fizzbuzz_direct

