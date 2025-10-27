GCC := gcc
GCC_FLAGS := -g -Wall -fsanitize=address,undefined

all: testy.out l11.out l12.out 0l1.out l0.out filereader.out pisaniedopliku.out Zadanie2.out


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
# 	./$@

l0.out: l0.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@

filereader.out: filereader.c
	${GCC} ${GCC_FLAGS} -o $@ $^

Zadanie1.out: Zadanie1.c 
	${GCC} ${GCC_FLAGS} -o $@ $^
	clear
	./Zadanie1.out -p directory/ -o tmp.log


Zadanie2.out: Zadanie2.c 
	${GCC} ${GCC_FLAGS} -o $@ $^
# 	clear

pisaniedopliku.out: pisaniedopliku.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	clear
	./pisaniedopliku.out plik.txt

.PHONY=clean
clean:
	rm *.out
	clear