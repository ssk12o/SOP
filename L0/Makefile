all: prog1 prog1b

prog1: prog1.c
	gcc -Wall -g -fsanitize=address,undefined -o prog1 prog1.c

prog1b: prog1b.c
	gcc -Wall -g -fsanitize=address,undefined -o prog1b prog1b.c

.PHONY: clean
clean:
	rm -rf prog1
	clear