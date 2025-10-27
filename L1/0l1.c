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

#define PATHBUFF 256

// #define ZAD1
// #define ZAD2
#define ZAD3

int funkcjaZliczająca(const char* charF, const struct stat* statF, int intF, struct FTW* ftwF) { return EXIT_SUCCESS; }

int numberOfDifferentFilesInCurrentDirPrintf()
{
    int files = 0, directories = 0, symlinks = 0, others = 0;
    DIR* directory = opendir(".");
    struct dirent* direntpointer;
    struct stat filestat;
    if (directories)
    {
        ERR("opening dir");
    }
    do
    {
        errno = 0;
        if ((direntpointer = readdir(directory)) != NULL)
        {
            if (lstat(direntpointer->d_name, &filestat))
            {
                ERR("filestat");
            }
            if (S_ISREG(filestat.st_mode))
            {
                files++;
            }
            else if (S_ISDIR(filestat.st_mode))
            {
                directories++;
            }
            else if (S_ISLNK(filestat.st_mode))
            {
                symlinks++;
            }
            else
            {
                others++;
            }
        }
    } while (direntpointer != NULL);
    if (errno != 0)
    {
        ERR("readdir");
    }
    if (closedir(directory))
    {
        ERR("closedir");
    }
    printf("files %d directories %d symlinks %d others %d\n", files, directories, symlinks, others);
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
/* ---------------------------- Etap 1 -------------------------*/
#ifdef ZAD1
    if (numberOfDifferentFilesInCurrentDirPrintf())
    {
        ERR("numberOfDifferentFilesInCurrentDirPrintf()");
    }
#endif

/* ---------------------------- Etap 2 -------------------------*/
#ifdef ZAD2
    if (argc < 2)
    {
        ERR("not enough args");
    }
    char originalDirPath[PATHBUFF];
    getcwd(originalDirPath, PATHBUFF);
    for (int i = 1; i < argc; i++)
    {
        if (chdir(argv[i]))
        {
            printf("dir doesn't exist %s\n", argv[i]);
            continue;
            // ERR("directory dosent exitst");
        }
        if (numberOfDifferentFilesInCurrentDirPrintf())
        {
            ERR("number of diff");
        }
        printf("dir name: %s:\n", argv[i]);
        if (chdir(originalDirPath))
        {
            ERR("chdir to original");
        }
    }

#endif

/* ---------------------------- Etap 3 -------------------------*/
#ifdef ZAD3
#define MAX_DESCR 20
    if (argc < 2)
    {
        ERR("not enough args");
    }
    for (int i = 1; i < argc; i++)
    {
        nftw(argv[i], funkcjaZliczająca, MAX_DESCR, FTW_PHYS);
    }

#endif
    return EXIT_SUCCESS;
}
