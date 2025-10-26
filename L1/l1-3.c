#define _XOPEN_SOURCE 500

#include <dirent.h>
#include <errno.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define PLOTEK (fprintf(stderr, "\n##############################################################\n"))

#define ERR(source) \
    (perror(source), PLOTEK, fprintf(stderr, "\nfilename: %s\tline: %d\n\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

int getDirContentsCount(char dir[])
{
    int regf = 0, regl = 0, regdir = 0, others = 0;
    DIR* directory = opendir(dir);
    if (directory)
    {
        ERR("opening dir");
    }
    struct dirent* dp;
    struct stat fstat;
    do
    {
        errno = 0;
        if ((dp = readdir(directory)))
        {
            ERR("reading directory");
        }
        if (lstat(dp->d_name, &fstat))
        {
            ERR("lstat");
        }
        if (S_ISDIR(fstat.st_mode))
        {
            regdir++;
        }
        else if (S_ISREG(fstat.st_mode))
        {
            regf++;
        }
        else if (S_ISLNK(fstat.st_mode))
        {
            regl++;
        }
        else
        {
            others++;
        }

    } while (dp != NULL);
    if (errno != 0)
    {
        ERR("readdir");
    }
    if (closedir(directory))
    {
        ERR("closing dir");
    }
    printf("%d %d %d %d", regdir, regf, regl, others);
    return EXIT_SUCCESS;
}

int scanRecursivelyFromDir(char dir[])
{
    int stat = 1;
    while (stat)
    {
    }
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        ERR("not enough arguments");
    }

    return EXIT_SUCCESS;
}
