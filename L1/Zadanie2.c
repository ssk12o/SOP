
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

#define STRING_BUFF_SIZE 256 * 4

int writeToOutput(char* message, int toFile, int outputFileID)
{
    if (toFile)
    {
        bulk_write(outputFileID, message, sizeof(message));
    }
    else
    {
        printf("%s", message);
    }
    return EXIT_SUCCESS;
}

int validFileNameExtention(char* filename, char* extention)
{
    if (extention == NULL)
    {
        return 1;
    }
    int filenameLen = strlen(filename);
    int extenetionLen = strlen(extention);
    for (int i = 0; i < extenetionLen; i++)
    {
        if (*(filename + filenameLen - 1 - i) != *(extention + extenetionLen - 1 - i))
        {
            return 0;
        }
    }
    if (*(filename - 1 - extenetionLen - 1) != '.')
    {
        return 0;
    }

    return 1;
}

int getThoughtSaidDir(char* directoryName, int depth, char* extenetion, int toFile, int outputFileID)
{
    if (depth == 0)
    {
        return EXIT_SUCCESS;
    }

    char string[STRING_BUFF_SIZE];

    char currentFunctionDir[STRING_BUFF_SIZE];
    if (!getcwd(currentFunctionDir, STRING_BUFF_SIZE))
    {
        ERR("getcwd");
    }

    if (chdir(directoryName))
    {
        ERR("chdir");
    }

    writeToOutput("path:\t", toFile, outputFileID);
    snprintf(string, STRING_BUFF_SIZE, "%s\n", directoryName);
    writeToOutput(string, toFile, outputFileID);

    DIR* readCurDir = opendir(".");
    if (!readCurDir)
    {
        ERR("readdir");
    }

    struct dirent* plikINdir;
    struct stat filestat;
    do
    {
        errno = 0;
        if ((plikINdir = readdir(readCurDir)) != NULL)
        {
            if (lstat(plikINdir->d_name, &filestat))
            {
                ERR("filestaat");
            }
            if (validFileNameExtention(plikINdir->d_name, extenetion))
            {
                // print file
                snprintf(string, STRING_BUFF_SIZE, "%s\t%ld\n", plikINdir->d_name, filestat.st_size);
                writeToOutput(string, toFile, outputFileID);
            }
            if (S_ISDIR(filestat.st_mode))
            {
                getThoughtSaidDir(plikINdir->d_name, depth - 1, extenetion, toFile, outputFileID);
            }
        }
    } while (plikINdir != NULL);

    if (errno != 0)
        ERR("readdir");
    if (closedir(readCurDir))
        ERR("closedir");

    if (chdir(currentFunctionDir))
    {
        ERR("chdir");
    }

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    char* fileExtension = NULL;
    char EfileExtension = -1;
    EfileExtension++;

    int depth = -1;
    // char Ddepth = 0;

    char OToFIle = 0;
    char* OToFileFilename = NULL;

    int maxNumberOfDirs = argc - 1;
    int numberOfDirs = 0;
    char** namesOfDirsToCheck = malloc((sizeof(char*)) * maxNumberOfDirs);
    if (!namesOfDirsToCheck)
    {
        ERR("malloc");
    }

    int c = 1;

    do
    {
        if ((c = getopt(argc, argv, "o:d:e:p:")) != -1)
        {
            switch (c)
            {
                case 'f':
                    EfileExtension = 1;
                    fileExtension = strdup(optarg);
                    break;
                case 'd':
                    // Ddepth = 1;
                    depth = strtol(optarg, NULL, 10);
                    break;
                case 'o':
                    OToFIle = 1;
                    break;
                case 'p':
                    namesOfDirsToCheck[numberOfDirs++] = strdup(optarg);
                    break;
                default:
                    ERR("wrong arg");
            }
        }
    } while (c != -1);

    char currentWorkingDirectory[STRING_BUFF_SIZE];
    if (!getcwd(currentWorkingDirectory, STRING_BUFF_SIZE))
    {
        ERR("getcwd");
    }
    // get name of output gile

    int outputFileID = -1;
    if (OToFIle)
    {
        outputFileID = open(OToFileFilename, O_RDWR | O_EXCL, 0666);
        if (outputFileID == -1)
        {
            ERR("openfile");
        }
    }

    for (int i = 0; i < numberOfDirs; i++)
    {
        if (getThoughtSaidDir(namesOfDirsToCheck[i], depth, fileExtension, OToFIle, outputFileID))
        {
            ERR("moloooooooooooooooooooch");
        }
        chdir(currentWorkingDirectory);
        free(namesOfDirsToCheck[i]);
    }

    if (OToFIle)
    {
        if (close(outputFileID))
        {
            ERR("closing file");
        }
    }
    free(namesOfDirsToCheck);
    return EXIT_SUCCESS;
}
