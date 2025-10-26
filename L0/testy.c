

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
int printenvvars()
{
    extern char** environ;
    size_t i = 0;
    while (*(environ + i) != NULL)
    {
        printf("zmienna środowiskowa nr: %zu, val: %s\n", i, *(environ + i));
        i++;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    const char command[] = "ls -l";
    system(command);
    // printenvvars();
    return EXIT_SUCCESS;
}
