#include <stdio.h>
#include <stdlib.h>

#define ERR(source) \
    (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

#define UNUSED(x) (void)(x)

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    printf("Hello student. It's your startup code. GLHF\n");
    return EXIT_SUCCESS;
}