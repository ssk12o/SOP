// #include <bits/getopt_core.h>
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PLOTEK (fprintf(stderr, "\n##############################################################\n"))

#define ERR(source) \
    (PLOTEK, perror(source), fprintf(stderr, "filename: %s\tline: %d\n\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

#define STRBUFFSIZE 1024

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

int writeToOutput(char* from, int toFile, int outputFileID)
{
    if (!toFile)
    {
        printf("%s", from);
    }
    else
    {
        printf("%s", from);
        if (bulk_write(outputFileID, from, strlen(from)) == -1)
        {
            ERR("bulk write");
        }
    }

    return EXIT_SUCCESS;
}

int getContentsOfDir(char* path, int doPliku, int outputFileID)
{
    char stringbuffor[STRBUFFSIZE];

    if (chdir(path))
    {
        ERR("chdir");
    }
    DIR* directory = opendir(".");
    if (!directory)
    {
        ERR("opendir(const char *name)");
    }

    if (!getcwd(stringbuffor, STRBUFFSIZE))
    {
        ERR("getcwd");
    }

    writeToOutput("Directory:\n", doPliku, outputFileID);
    writeToOutput(stringbuffor, doPliku, outputFileID);
    writeToOutput("Files:\n", doPliku, outputFileID);

    struct dirent* dp;
    struct stat filestat;

    do
    {
        errno = 0;
        if ((dp = readdir(directory)) != NULL)
        {
            if (lstat(dp->d_name, &filestat))
            {
                ERR("filestat");
            }

            snprintf(stringbuffor, STRBUFFSIZE, "%s \t\t %ld\n", dp->d_name, filestat.st_size);
            writeToOutput(stringbuffor, doPliku, outputFileID);
        }
    } while (dp);

    if (errno != 0)
    {
        ERR("readdir");
    }

    if (closedir(directory))
    {
        ERR("closedir");
    }

    writeToOutput("End of dir;\n\n\n", doPliku, outputFileID);

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        ERR("not enough arguments");
    }

    // przyjmujemy argumenty
    int c;
    int doPliku = 0;
    char* outputFileName = NULL;
    int numberOfPaths = 0;
    char** pathsToDirs = malloc((argc - 1) * sizeof(char*));

    if (!pathsToDirs)
    {
        ERR("malloc");
    }

    while ((c = getopt(argc, argv, "o:p:")) != -1)
    {
        switch (c)
        {
            case 'o':
                doPliku = 1;
                outputFileName = strdup(optarg);
                break;
            case 'p':
                pathsToDirs[numberOfPaths++] = strdup(optarg);
                break;
            default:
                ERR("invalid option arg");
        }
    }

    int outputFileID = -1;
    if (doPliku)
    {
        printf("name of output file: %s\n", outputFileName);
        outputFileID = open(outputFileName, O_RDWR | O_EXCL, 0777);
        if (outputFileID == -1)
        {
            ERR("fileopen");
        }
    }

    char originalDirPath[STRBUFFSIZE];
    if (!getcwd(originalDirPath, STRBUFFSIZE))
    {
        ERR("get cwd");
    }

    for (int i = 0; i < numberOfPaths; i++)
    {
        getContentsOfDir(pathsToDirs[i], doPliku, outputFileID);
        if (chdir(originalDirPath))
        {
            ERR("chdir");
        }
        free(pathsToDirs[i]);
    }

    free(pathsToDirs);
    if (doPliku)
    {
        if (close(outputFileID))
        {
            ERR("close end");
        }
        free(outputFileName);
    }

    return EXIT_SUCCESS;
}
