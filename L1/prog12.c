#include <asm-generic/errno-base.h>
#include <sys/types.h>
#define _XOPEN_SOURCE 500

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define PLOTEK (fprintf(stderr, "\n##############################################################\n"))

#define ERR(source) \
    (perror(source), PLOTEK, fprintf(stderr, "\nfilename: %s\tline: %d\n\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

void usage(char* pname)
{
    fprintf(stderr, "USAGE:%s -n Name -p OCTAL -s SIZE\n", pname);
    exit(EXIT_FAILURE);
}

#define STRLEN 1024

int createNewFileAndFill(char* name, mode_t perms, ssize_t size)
{
    int percent = 10;
    FILE* s1;
    int i;
    umask(~perms & 0777);
    if (((s1 = fopen(name, "w+"))) == NULL)
    {
        ERR("fopen");
    }
    for (int i = 0; i < (size * percent) / 100; i++)
    {
        if (fseek(s1, rand() % size, SEEK_SET))
        {
            ERR("fseek");
        }
        fprintf(s1, "%c", 'A' + i % ('Z' - 'A' + 1));
    }
    if (fclose(s1))
    {
        ERR("file close");
    }
    return EXIT_SUCCESS;
};

int main(int argc, char** argv)
{
    int c;
    char* name = NULL;
    mode_t perms = -1;
    ssize_t size = -1;

    while ((c = getopt(argc, argv, "p:n:s")) != -1)
    {
        switch (c)
        {
            case 'p':
                perms = strtol(optarg, NULL, 8);
                break;
            case 'n':
                name = optarg;
                break;
            case 's':
                size = strtol(optarg, NULL, 10);
                break;
            default:
                ERR("optarg");
                break;
        }
    }
    if (perms == -1 || name == NULL || size == -1)
    {
        ERR("wrong args");
    }

    if (unlink(name) && errno != ENOENT)
    {
        ERR("unlinks");
    }

    srand(time(NULL));
    createNewFileAndFill(name, perms, size);

    return EXIT_SUCCESS;
}
