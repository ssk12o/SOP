#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

extern char** environ;
#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

void usage(char* pname)
{
    fprintf(stderr, "usage: %s []\n", pname);
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    if (argc % 2 != 1)
    {
        usage(argv[0]);
    }
    for (int i = 1; i <= argc; i += 2)
    {
        if (setenv(argv[i], argv[i + 1], 1))
        {
            if (EINVAL == errno)
            {
                ERR("setenv -- variable name containts =");
            }
            ERR("setenv");
        }
    }

    int index = 0;
    while (environ[index])
    {
        printf("%s\n", environ[index++]);
    }
    return EXIT_SUCCESS;
}
