#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PLOTEK (fprintf(stderr, "\n##############################################################\n"))

#define ERR(source) \
    (perror(source), PLOTEK, fprintf(stderr, "filename: %s\tline: %d\n\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

void usage(char* pname)
{
    fprintf(stderr, "USAGE:%s -n Name -p OCTAL -s SIZE\n", pname);
    exit(EXIT_FAILURE);
}

ssize_t bulk_read(int fd, char* buf, size_t count)
{
    ssize_t c;
    ssize_t len = 0;
    do
    {
        c = TEMP_FAILURE_RETRY(read(fd, buf, count));
        if (c < 0)
            return c;
        if (c == 0)
            return len;  // EOF
        buf += c;
        len += c;
        count -= c;
    } while (count > 0);
    return len;
}

ssize_t bulk_write(int fd, char* buf, size_t count)
{
    ssize_t c;
    ssize_t len = 0;
    do
    {
        c = TEMP_FAILURE_RETRY(write(fd, buf, count));
        if (c < 0)
            return c;
        buf += c;
        len += c;
        count -= c;
    } while (count > 0);
    return len;
}
int menu(int argc, char** argv)
{
    int c;

    int i = 0, remove;
    char *package, *new_env_name, **ex_env_name;

    while ((c = getopt(argc, argv, "c:v:i:r")) != -1)
    {
        switch (c)
        {
            case 'c':
                new_env_name = optarg;
                break;
            case 'v':
                ex_env_name[i++] = optarg;
                break;
            case 'i':
                package = optarg;
                break;
            case 'r':
                remove = true;
                break;
            case '?':
                fprintf(stderr, "Wrong arguments");
                exit(EXIT_FAILURE);
            default:
                continue;
        }
    }
}

// snprintf();
//     strcpy();
//     strcat();
