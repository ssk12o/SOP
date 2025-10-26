GCC := gcc
GCC_FLAGS := -g -Wall -fsanitize=address,undefined

all: testy.out l11.out l12.out 0l1.out


testy.out: testy.c
	${GCC} ${GCC_FLAGS} -o $@ $^
# 	./$@

l11.out: l1-1.c 
	${GCC} ${GCC_FLAGS} -o $@ $^
# 	./$@

l12.out: l1-2.c 
	${GCC} ${GCC_FLAGS} -o $@ $^
# 	./$@

0l1.out: 0l1.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@


.PHONY=clean
clean:
	rm *.out
	clear