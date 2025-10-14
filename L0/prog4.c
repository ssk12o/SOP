#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        printf("arg no. %d: %s\n", i, argv[i]);
    }

    return EXIT_SUCCESS;
}
