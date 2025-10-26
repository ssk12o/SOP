
#include <stdio.h>
#include <stdlib.h>
#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))
#define LINELEN 20
int main()
{
    char lineBuf[LINELEN + 2];
    while (fgets(lineBuf, LINELEN, stdin) != NULL)
    {
        printf("hello %s", lineBuf);
    }
    return EXIT_SUCCESS;
}
