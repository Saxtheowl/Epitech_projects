#include "mysh.h"

char *find_command_in_path(char *cmd)
{
    char *path_env;
    char *path_copy;
    char *dir;
    char *full_path;
    struct stat st;

    if (!cmd || strchr(cmd, '/')) {
        return NULL;
    }

    path_env = get_env_var("PATH");
    if (!path_env) {
        return NULL;
    }

    path_copy = malloc(strlen(path_env) + 1);
    if (!path_copy) {
        return NULL;
    }
    strcpy(path_copy, path_env);

    dir = strtok(path_copy, ":");
    while (dir) {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        if (!full_path) {
            free(path_copy);
            return NULL;
        }
        
        sprintf(full_path, "%s/%s", dir, cmd);
        
        if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && 
            (st.st_mode & S_IXUSR)) {
            free(path_copy);
            return full_path;
        }
        
        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

void print_error(char *msg)
{
    if (msg) {
        fprintf(stderr, "%s\n", msg);
    }
}