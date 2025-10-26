#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define NAME_MAX = 20

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))
int main()
{
    printf("what's your name?: ");
    char name[22];
    scanf("%21s", name);
    if (strlen(name) > 20)
    {
        ERR("name to long\n");
    }
    printf("Hello %s\n", name);
}
