#ifndef MYSH_H
#define MYSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define MAX_ARGS 1024
#define MAX_PATH 4096
#define MAX_ENV 1024

typedef struct {
    char **environ;
    int env_size;
    int exit_status;
} shell_t;

extern shell_t g_shell;

int parse_command(char *line, char **args);
int execute_command(char **args);
int builtin_cd(char **args);
int builtin_setenv(char **args);
int builtin_unsetenv(char **args);
int builtin_env(char **args);
int builtin_exit(char **args);
int is_builtin(char *cmd);

char *find_command_in_path(char *cmd);
char *get_env_var(char *name);
int set_env_var(char *name, char *value);
int unset_env_var(char *name);
void init_env(char **envp);
void free_env(void);
char **copy_env(char **envp);

void print_error(char *msg);

#endif