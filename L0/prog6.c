#include <stdio.h>
#include <stdlib.h>

extern char** environ;

int printAllEnv()
{
    int i = 0;
    while (*(environ + i))
    {
        printf("%s\n", *(environ + i++));
    }
    return EXIT_SUCCESS;
}

int main()
{
    printAllEnv();
    return EXIT_SUCCESS;
}
