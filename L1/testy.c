#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int pliki()
{
    DIR* dir = opendir("directory");
    struct dirent* dirread;
    struct stat stats;
    stat("directory", &stats);
    printf("dir is director %d\n", S_ISDIR(stats.st_mode));
    while ((dirread = readdir(dir)) != NULL)
    {
        printf("%s\n", dirread->d_name);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    printf(argv[2]);
    // char name[400];
    // printf("%s\n\n", getcwd(name, 400));
    // pliki();
    return EXIT_SUCCESS;
}
