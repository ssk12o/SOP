#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

int printDirContents(char dirAddressName[])
{
    int files = 0, links = 0, dirs = 0, others = 0;

    DIR* dirp;
    struct stat filestat;
    struct dirent* dp;

    if ((dirp = opendir(dirAddressName)) == NULL)
    {
        ERR("couldn't open directory");
    }

    do
    {
        errno = 0;
        if ((dp = readdir(dirp)) != NULL)
        {
            if (lstat(dp->d_name, &filestat))
            {
                ERR("lstat");
            }
            if (S_ISDIR(filestat.st_mode))
            {
                dirs++;
            }
            else if (S_ISLNK(filestat.st_mode))
            {
                links++;
            }
            else if (S_ISREG(filestat.st_mode))
            {
                files++;
            }
            else
            {
                others++;
            }
        }
    } while (dp != NULL);

    if (errno != 0)
    {
        ERR("readdir");
    }
    if (closedir(dirp))
    {
        ERR("closedir");
    }
    printf("regf: %d, linkf: %d, dirf: %d, other: %d\n", files, links, dirs, others);
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    if (printDirContents("."))
    {
        ERR("printdircontstns");
    }
    return EXIT_SUCCESS;
}
