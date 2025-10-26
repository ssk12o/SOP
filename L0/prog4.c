#include <stdio.h>
#include <stdlib.h>
#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        ERR("not enough arguments\n");
    }
    else if (argc > 3)
    {
        ERR("too many arguments");
    }
    int numberOfTimes = atoi(argv[1]);
    for (int i = 0; i < numberOfTimes; i++)
    {
        printf("%s\n", argv[2]);
    }
    // lubie
}
