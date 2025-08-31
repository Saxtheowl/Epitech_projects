/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** Header file for mysh minishell
*/

#ifndef MYSH_H_
#define MYSH_H_

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

#define MAX_PATH_LENGTH 1024
#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

typedef struct env_s {
    char *name;
    char *value;
    struct env_s *next;
} env_t;

typedef struct shell_s {
    env_t *env_list;
    char **environ_copy;
    int last_status;
    int running;
} shell_t;

/* Environment management */
env_t *create_env_node(const char *name, const char *value);
void add_env_var(shell_t *shell, const char *name, const char *value);
char *get_env_var(shell_t *shell, const char *name);
void remove_env_var(shell_t *shell, const char *name);
void init_environment(shell_t *shell, char **environ);
void cleanup_environment(shell_t *shell);
char **env_list_to_array(shell_t *shell);

/* Built-in commands */
int builtin_cd(shell_t *shell, char **args);
int builtin_env(shell_t *shell, char **args);
int builtin_setenv(shell_t *shell, char **args);
int builtin_unsetenv(shell_t *shell, char **args);
int builtin_exit(shell_t *shell, char **args);

/* Command execution */
int execute_command(shell_t *shell, char **args);
int execute_builtin(shell_t *shell, char **args);
int is_builtin(const char *command);
char *find_command_path(shell_t *shell, const char *command);

/* Command parsing */
char **parse_command(char *line);
void free_args(char **args);

/* Shell loop */
void shell_loop(shell_t *shell);
void display_prompt(void);

/* Utility functions */
void print_error(const char *command, const char *message);
int my_strcmp(const char *s1, const char *s2);
char *my_strdup(const char *s);
char *my_strcat(char *dest, const char *src);
int my_strlen(const char *s);

#endif /* !MYSH_H_ */