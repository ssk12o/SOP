#define _XOPEN_SOURCE 500

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define PLOTEK (fprintf(stderr, "\n##############################################################\n"))

#define ERR(source) \
    (perror(source), PLOTEK, fprintf(stderr, "\nfilename: %s\tline: %d\n\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

// int zad5(int argc, char** argv)
// {
//     if (argc != 3)
//     {
//         ERR("wrong amount of args");
//     }
//     int numberOfNameReps;
//     if ((numberOfNameReps = atoi(argv[2])) <= 0)
//     {
//         ERR("nan atoi");
//     }
//     // printf("%d", numberOfNameReps);
//     for (int i = 0; i < numberOfNameReps; i++)
//     {
//         (fprintf(stdout, "hello %s\n", argv[1]));
//     }
//     return EXIT_SUCCESS;
// }

// extern char** environ;
// int wypiszWszystkieZmienneSrodowiskowe(int argc, char** argv)
// {
//     int i = 0;
//     while (environ[i])
//     {
//         fprintf(stdout, "%s\n", environ[i++]);
//     }
//     return EXIT_SUCCESS;
// }

// int zmienneSrodowiskoweDwa()
// {
// #define FROM "TIMES"
// #define RESULT "RESULT"
// #define STRING_SIZE 2000
//     int numberOfThies;
//     char* envPOinter = getenv(FROM);
//     if (envPOinter)
//     {
//         numberOfThies = atoi(envPOinter);
//     }
//     else
//     {
//         numberOfThies = 1;
//     }
//     char name[STRING_SIZE + 2];

//     while (fgets(name, STRING_SIZE + 2, stdin) != NULL)
//     {
//         for (int i = 0; i < numberOfThies; i++)
//         {
//             printf("hello %s\n", name);
//         }
//     }
//     if (putenv(RESULT))
//     {
//         ERR("putenv");
//     }
//     printf("%s", getenv(RESULT));
// }

// int main(int argc, char** argv)
// {
//     // printf("---------------------- zad 5 ------------------\n");
//     // zad5(argc, argv);

//     printf("---------------------- zad 6 ------------------\n");
//     wypiszWszystkieZmienneSrodowiskowe(argc, argv);

//     return EXIT_SUCCESS;
// }

#define MAXFD 20

int dirs = 0, files = 0, links = 0, other = 0;

int walk(const char* name, const struct stat* s, int type, struct FTW* f)
{
    printf("filename(%d):", f->level);
    for (int i = 0; i < f->level; i++)
    {
        printf("%c%c", ' ', ' ');
    }
    printf("%s\n", name);
    switch (type)
    {
        case FTW_DNR:
        case FTW_D:
            dirs++;
            break;
        case FTW_F:
            files++;
            break;
        case FTW_SL:
            links++;
            break;
        default:
            other++;
    }
    return 0;
}

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (nftw(argv[i], walk, MAXFD, FTW_PHYS) == 0)
            ;
        // printf("%s:\nfiles:%d\ndirs:%d\nlinks:%d\nother:%d\n", argv[i], files, dirs, links, other);
        else
            ;
        // printf("%s: access denied\n", argv[i]);
        dirs = files = links = other = 0;
    }
    return EXIT_SUCCESS;
}
