all: prog1 prog1b prog2 prog3 prog4

CC=gcc
CFLAGS=-Wall -g -fsanitize=address,undefined
LDFLAGS=-fsanitize=address,undefined


prog1: prog1.c
	gcc -Wall -g -fsanitize=address,undefined -o $@ $<

prog1b: prog1b.c
	gcc -Wall -g -fsanitize=address,undefined -o $@ $<

prog2: prog2.c
	gcc -Wall -g -fsanitize=address,undefined -o $@ $<

prog3: prog3.c
	gcc -Wall -g -fsanitize=address,undefined -o $@ $<

prog4: prog4.c
	${CC} ${CFLAGS} -o $@ $<


.PHONY: clean
clean:
	rm -rf prog1 prog1b prog2 prog3
	clear