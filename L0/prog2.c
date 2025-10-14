#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX_LEN 20
#define ERR(source) (perror(source), fprintf(stderr, "%s%d", __FILE__, __LINE__), exit(EXIT_FAILURE))

int main(int argc, char** argv)
{
    printf("tell me your name:\n");
    char name[NAME_MAX_LEN + 2];

    scanf("%20s", name);
    if (strlen(name) > NAME_MAX_LEN)
        ERR("Name too long my friend!\n");
    printf("Hello %s\n", name);

    return EXIT_SUCCESS;
}
