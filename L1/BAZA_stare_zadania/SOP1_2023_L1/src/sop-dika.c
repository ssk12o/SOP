#include <asm-generic/errno-base.h>
#define _GNU_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define ERR(source)                                                                                                   \
    (fprintf(stderr, "##########################################################################\n"), perror(source), \
     fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))
#define STRING_BUFF_SIZE 1024
#define DESCRIPTORS_DEPTH 2000
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

void show_stage2(const char* const path, const struct stat* const stat_buf)
{
    if (S_ISDIR(stat_buf->st_mode))
    {
        // dirka
        DIR* directory = NULL;
        if ((directory = opendir(path)) == NULL)
        {
            ERR("opendir");
        }
        struct dirent* dp;
        printf("\n");
        do
        {
            errno = 0;
            if ((dp = readdir(directory)) != NULL)
            {
                fprintf(stdout, "%s\n", dp->d_name);
            }
        } while (dp != NULL);

        if (errno != 0)
            ERR("readdir");
        if (closedir(directory))
            ERR("closedir");
    }
    else if (S_ISREG(stat_buf->st_mode))
    {
        // regular file
        printf("\n");
        printf("size: %ld\ncontent:\n", stat_buf->st_size);
        char strbuf[STRING_BUFF_SIZE];
        int fileID = open(path, O_RDONLY);
        if (fileID == -1)
        {
            ERR("file open");
        }
        int readSize = 1;
        strbuf[0] = '\0';
        while (readSize > 0)
        {
            fprintf(stdout, "%s", strbuf);
            readSize = bulk_read(fileID, strbuf, STRING_BUFF_SIZE);
            if (readSize == -1)
            {
                ERR("READ");
            }
        }
        printf("koniec tresci\n");
        if (close(fileID) == -1)
        {
            ERR("close dir");
        }
    }
    else
    {
        fprintf(stderr, "file has unknown format\n");
        return;
    }
}

void write_stage3(const char* const path, const struct stat* const stat_buf)
{
    // regular file
    printf("\n");
    char strbuf[STRING_BUFF_SIZE];
    int fileID = open(path, O_RDONLY);
    if (fileID == -1)
    {
        ERR("file open");
    }
    int readSize = 1;
    strbuf[0] = '\0';
    while (readSize > 0)
    {
        fprintf(stdout, "%s", strbuf);
        readSize = bulk_read(fileID, strbuf, STRING_BUFF_SIZE);
        if (readSize == -1)
        {
            ERR("READ");
        }
    }
    printf("\n");
    if (close(fileID) == -1)
    {
        ERR("closefile");
    }

    if (open(path, O_WRONLY | O_APPEND) == -1)
    {
        ERR("open");
    }
    do
    {
        if (fgets(strbuf, STRING_BUFF_SIZE, stdin) == NULL)
        {
            ERR("fgets");
        }
        if (bulk_write(fileID, strbuf, strlen(strbuf)) < 0)
        {
            ERR("bulk write");
        }
    } while (strbuf[0] != '\n');
}
// int nftw(const char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int fd_limit, int flags);
int walk(const char* charW, const struct stat* statW, int intW, struct FTW* FTWW)
{
    printf("%s\t", charW);
    if (intW == FTW_D || intW == FTW_DNR)
    {
        printf("DIR\n");
    }
    else if (intW == FTW_F)
    {
        printf("REG\n");
    }
    else
    {
        printf("OTH\n");
    }
    return EXIT_SUCCESS;
}

void walk_stage4(const char* const path, const struct stat* const stat_buf)
{
    nftw(path, walk, DESCRIPTORS_DEPTH, FTW_PHYS);
}

int interface_stage1()
{
    if (printf("1. show\n2. write\n3. walk\n4. exit\n") < 0)
    {
        ERR("printf");
    }

    char option;
    char pathToFile[STRING_BUFF_SIZE];
    // to get a option
    if (!fgets(pathToFile, STRING_BUFF_SIZE, stdin))
    {
        ERR("fgets");
    }
    option = pathToFile[0];

    switch (option)
    {
        case '1':
        case '2':
        case '3':
            break;
        case '4':
            return 0;
            break;
        default:
            fprintf(stderr, "wrong option in menu");
            return 1;
    }

    // now we get path
    if (!fgets(pathToFile, STRING_BUFF_SIZE, stdin))
    {
        ERR("fgets");
    }

    // newline terminated
    pathToFile[strlen(pathToFile) - 1] = '\0';
    printf("%s", pathToFile);

    struct stat fileStat;
    errno = 0;
    if (stat(pathToFile, &fileStat))
    {
        if (errno == ENOENT)
        {
            fprintf(stderr, "file dosent exist\n");
            return 1;
        }
        else
        {
            ERR("fstat");
        }
    }

    switch (option)
    {
            // show
        case '1':
            show_stage2(pathToFile, &fileStat);
            break;
            // write
        case '2':
            write_stage3(pathToFile, &fileStat);
            break;
            // walk
        case '3':
            walk_stage4(pathToFile, &fileStat);
            break;
            // exit
        case '4':
            return 0;
            break;
        default:
            fprintf(stderr, "wrong option in menu");
            return 1;
    }

    return 1;
}

int main()
{
    while (interface_stage1())
        ;
    return EXIT_SUCCESS;
}
