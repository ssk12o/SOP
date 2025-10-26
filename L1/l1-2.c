#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define PLOTEK(j) (fprintf(stderr, "\n##############################################################\n"))

#define ERR(source)                                                                                    \
    (perror(source), PLOTEK(100), fprintf(stderr, "\nfilename: %s\tline: %d\n\n", __FILE__, __LINE__), \
     exit(EXIT_FAILURE))

#define PATHNAME_LEN 600

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

    char cwd[PATHNAME_LEN];
    getcwd(cwd, PATHNAME_LEN);
    printf("int dir: %s\n", cwd);
    printf("regf: %d, linkf: %d, dirf: %d, other: %d\n", files, links, dirs, others);
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        ERR("no dirs specified");
    }
    int numberOfDirsToCheck = argc - 1;
    char original_pwd[PATHNAME_LEN];
    if (getcwd(original_pwd, PATHNAME_LEN) == NULL)
    {
        ERR("getcwd current");
    }

    for (int i = 1; i <= numberOfDirsToCheck; i++)
    {
        if (chdir(argv[i]))
        {
            ERR("chdir");
        }
        if (printDirContents("."))
        {
            ERR("print dir contents");
        }
        if (chdir(original_pwd))
        {
            ERR("chdir to home");
        }
    }

    return EXIT_SUCCESS;
}
