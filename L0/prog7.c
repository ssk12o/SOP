
#include <stdio.h>
#include <stdlib.h>
#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

#define NAME_LEN 20
#define TIME_VAR "TIMES"

int printHelloEnv()
{
    char* envVariable = getenv(TIME_VAR);
    int numberOfRepetitions;
    if (!envVariable)
    {
        numberOfRepetitions = 1;
    }
    else
    {
        numberOfRepetitions = atoi(envVariable);
    }

    char name[NAME_LEN + 2];
    while (fgets(name, NAME_LEN + 2, stdin))
    {
        for (int i = 0; i < numberOfRepetitions; i++)
        {
            printf("%s", name);
        }
    }
    if (putenv("RESULT=done"))
    {
        fprintf(stderr, "erroe in putting env done");
        return EXIT_FAILURE;
    }
    printf("%s\n", getenv("RESULT"));
    if (system("env | grep RESULT") != 0)
    {
        fprintf(stderr, "env not found in set\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main()
{
    printHelloEnv();
    return EXIT_SUCCESS;
}
