GCC := gcc
GCC_FLAGS := -g -Wall -fsanitize=address,undefined

testy.out: testy.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@

p1.out: prog1.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@
p2.out: prog2.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@

p3.out: prog3.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@

p4.out: prog4.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@ 4 janek
	
p6.out: prog6.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@ 

p7.out: prog7.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@ 

p8.out: prog8.c
	${GCC} ${GCC_FLAGS} -o $@ $^
	./$@ 


.PHONY=clean
clean:
	rm *.out
	clear