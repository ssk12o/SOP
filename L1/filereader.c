#define _XOPEN_SOURCE 500

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define PLOTEK (fprintf(stderr, "\n##############################################################\n"))

#define ERR(source) \
    (perror(source), PLOTEK, fprintf(stderr, "\nfilename: %s\tline: %d\n\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

int main(int argc, char** argv)
{
    int c;
    int number;
    char** paths = malloc((argc) * sizeof(char*));

    int numberOfPaths = 0;
    while ((c = getopt(argc, argv, "n:p:")) != -1)
    {
        switch (c)
        {
            case 'p':
                paths[numberOfPaths++] = strdup(optarg);
                break;
            case 'n':
                number = strtol(optarg, NULL, 10);
                break;
            default:
                ERR("wrong arg");
        }
    }

    printf("n ma wartość: %d\n", number);
    for (int i = 0; i < numberOfPaths; i++)
    {
        printf("\tpath number %d: %s\n", i + 1, paths[i]);
    }

    for (int i = 0; i < numberOfPaths; i++)
    {
        free(paths[i]);
    }
    free(paths);
    return EXIT_SUCCESS;
}
