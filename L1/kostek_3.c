#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_VENV_UPDATES 10
#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

void remove_package(char* venv, char* package)
{
    char* full_env_path = (char*)calloc(strlen(venv) + 4 + strlen(package), sizeof(char));
    if (full_env_path == NULL)
        ERR("calloc");
    strcpy(full_env_path, "./");
    strcat(full_env_path, venv);
    strcat(full_env_path, "/");
    strcat(full_env_path, package);
    FILE* fp_pack = fopen(full_env_path, "r");
    if (fp_pack == NULL)
    {
        fprintf(stderr, "package doesn't exist");
        exit(EXIT_FAILURE);
    }
    if (fclose(fp_pack) == -1)
        ERR("fclose");
    if (unlink(full_env_path) == -1)
        ERR("unlink");
    free(full_env_path);
    full_env_path = NULL;
    char* req_path = (char*)calloc(strlen(venv) + 3 + strlen("/requirements.txt"), sizeof(char));
    if (req_path == NULL)
        ERR("calloc");
    strcpy(req_path, "./");
    strcat(req_path, venv);
    strcat(req_path, "/requirements.txt");
    FILE* fp_req = fopen(req_path, "r");
    struct stat stat_st;
    if (stat(req_path, &stat_st) == -1)
        ERR("stat");
    char f[40];
    char v[20];
    char* buf = (char*)malloc(stat_st.st_size);
    while (fscanf(fp_req, "%s %s", f, v) == 2)
    {
        if (strcmp(f, package) != 0)
        {
            strcat(buf, f);
            strcat(buf, " ");
            strcat(buf, v);
            strcat(buf, "\n");
        }
    }
    if (fclose(fp_req) == -1)
        ERR("fclose");
    FILE* fp_req2 = fopen(req_path, "w");
    fprintf(fp_req2, buf);
    free(buf);
    free(req_path);
    if (fclose(fp_req2) == -1)
        ERR("fclose");
}
char* get_package(char* package)
{
    char* name = (char*)calloc(100, sizeof(char));
    if (name == NULL)
        ERR("calloc");
    int i = 0;
    while (package[i] != '\0')
    {
        if (package[i] == '=')
        {
            break;
        }
        name[i] = package[i];
        i++;
    }
    name = (char*)realloc(name, 1 + i * sizeof(char));
    if (name == NULL)
        ERR("realloc");
    return name;
}

char* get_package_line(char* package)
{
    char* name = (char*)calloc(100, sizeof(char));
    if (name == NULL)
        ERR("calloc");
    int i = 0;
    int j = 0;
    while (package[i] != '\0')
    {
        if (package[i] == '=')
        {
            if (name[j - 1] == ' ')
            {
                i++;
                continue;
            }
            name[j] = ' ';
            i++;
            j++;
            continue;
        }
        name[j] = package[i];
        i++;
        j++;
    }
    name = (char*)realloc(name, 1 + j * sizeof(char));
    if (name == NULL)
        ERR("realloc");
    return name;
}
void install_package(char* env_path, char* package)
{
    char* full_env_path = (char*)calloc(strlen(env_path) + 4 + strlen("requirements.txt"), sizeof(char));
    strcpy(full_env_path, "./");
    strcat(full_env_path, env_path);
    strcat(full_env_path, "/requirements.txt");
    FILE* fp = fopen(full_env_path, "a");
    if (fp == NULL)
        ERR("opendir");
    char* package_line = get_package_line(package);
    char* package_name = get_package(package);
    char* full_package_path = (char*)calloc(strlen(env_path) + 5 + strlen(package_name), sizeof(char));
    strcpy(full_package_path, "./");
    strcat(full_package_path, env_path);
    strcat(full_package_path, "/");
    strcat(full_package_path, package_name);
    FILE* fp_pack = fopen(full_package_path, "r");
    if (fp_pack != NULL)
    {
        fprintf(stderr, "package already exists");
        free(package_line);
        free(package_name);
        free(full_env_path);
        free(full_package_path);
        fclose(fp);
        fclose(fp_pack);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%s\n", package_line);
    int fd = open(full_package_path, O_CREAT, 0440);
    close(fd);
    fclose(fp);
    free(package_line);
    free(package_name);
    free(full_env_path);
    free(full_package_path);
}

void create_venv(char* env_name)
{
    DIR* dp = opendir(".");
    if (dp == NULL)
        ERR("opendir");
    errno = 0;
    int res = mkdir(env_name, 0777);
    if (errno == EEXIST)
    {
        fprintf(stderr, "The virtual environment already exists");
        exit(EXIT_FAILURE);
    }
    if (res == -1)
        ERR("mkdir");
    char* new_env_path = (char*)calloc(3 + strlen(env_name) + strlen("requirements.txt"), sizeof(char));
    strcpy(new_env_path, "./");
    strcat(new_env_path, env_name);
    strcat(new_env_path, "/requirements.txt");
    FILE* file = fopen(new_env_path, "w+");

    if (file == NULL)
        ERR("fopen");
    if (fclose(file) == -1)
        ERR("fclose");
    if (closedir(dp) == -1)
        ERR("closedir");
    free(new_env_path);
}

int main(int argc, char** argv)
{
    int c;
    char* new_env_name = NULL;
    char* ex_env_name[MAX_VENV_UPDATES];
    int i = 0;
    char* package = NULL;
    bool remove = false;
    // char* pname = "python==1.0.2";
    // get_package_line(pname);
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
    if (new_env_name != NULL && ex_env_name[0] == NULL && !remove && package == NULL)
    {
        create_venv(new_env_name);
    }
    else if (new_env_name == NULL && package != NULL && ex_env_name[0] != NULL && !remove)
    {
        for (int j = 0; j < i; j++)
        {
            install_package(ex_env_name[j], package);
        }
    }
    else if (remove && ex_env_name[0] != NULL && new_env_name == NULL && package != NULL)
    {
        remove_package(ex_env_name[0], package);
    }
    else
    {
        fprintf(stderr, "Wrong arguments");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
