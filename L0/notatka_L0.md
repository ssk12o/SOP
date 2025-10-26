# Laboratorium L0

## Biblioteczka

#### man 3p stdin
stderr, stdin, stdout — standard I/O streams

#include <stdio.h>

Zbuforowane trzy strumienie tworzone dla każdego pliku: input output i error (kolejno 0 1 2).

#### man 3p fprintf
dprintf, fprintf, printf, snprintf, sprintf — print formatted output

#include <stdio.h>

int printf(const char *restrict format, ...); -- print formatted at standard output

int fprintf(FILE *restrict stream, const char *restrict format, ...); -- print formatted at said stream

#### man stdlib.h
biblioteka standardowa c
#### man make
buildsystem i tyle no
#### man 3p fscanf
fscanf, scanf, sscanf — convert formatted input

#include <stdio.h>

int fscanf(FILE *restrict stream, const char *restrict format, ...);

int scanf(const char *restrict format, ...);

int sscanf(const char *restrict s, const char *restrict format, ...);

#### man 3p perror
perror — write error messages to standard error

#include <stdio.h>

void perror(const char *s);
#### man 3p fgets
gets — get a string from a stdin stream

#include <stdio.h>

char *gets(char *s);
#### man 1 xargs
#### man 3p exit
exit — terminate a process

#include <stdlib.h>

void exit(int status);
#### man 3p atoi
       atoi — convert a string to an integer

SYNOPSIS
       #include <stdlib.h>

       int atoi(const char *str);
#### man 3p strtol
strtol, strtoll — convert a string to a long integer

#include <stdlib.h>

long strtol(const char *restrict nptr, char **restrict endptr, int base);

long long strtoll(const char *restrict nptr, char **restrict endptr, int base)
#### man 3p environ
#### man 7 environ
extern char **environ;

pointer to list of env var, NULL terminated

#### man 3p getenv
getenv — get value of an environment variable

#include <stdlib.h>

char *getenv(const char *name);
#### man 3p putenv 
putenv — change or add a value to an environment
BAD!! it uses just the pointer, it dosent copy env

#include <stdlib.h>

int putenv(char *string);
#### man 3p setenv
setenv — add or change environment variable

#include <stdlib.h>

int setenv(const char *envname, const char *envval, int overwrite);
#### man 3 system (3p) jest trochę mniej czytelny
system — issue a command

#include <stdlib.h>

int system(const char *command);
#### man 3p errno




## Istotne libki
A żeby niczego nam nie zabrakło:
stdio.h
stdlib.h

## Make, kompilator i jego flagi
GCC := gcc
GCC_FLAGS := -g -Wall -fsanitize=address,undefined -o prog1 prog1.c


600 vs 800 -- hui/