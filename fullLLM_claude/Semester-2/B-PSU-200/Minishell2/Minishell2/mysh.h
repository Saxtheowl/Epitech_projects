#ifndef MYSH_H_
#define MYSH_H_

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
#define MAX_PIPES 32

typedef struct cmd_s {
    char **args;
    char *input_redirect;
    char *output_redirect;
    int append_output;
    struct cmd_s *next;
} cmd_t;

typedef struct pipeline_s {
    cmd_t *commands;
    struct pipeline_s *next;
} pipeline_t;

extern char **environ;

int main_shell_loop(char **env);
char *get_line(void);
pipeline_t *parse_line(char *line);
int execute_pipeline(pipeline_t *pipeline, char **env);
void free_pipeline(pipeline_t *pipeline);

cmd_t *parse_command(char *cmd_str);
void free_command(cmd_t *cmd);
int count_pipes(char *str);
char **split_by_pipes(char *str);
char **tokenize_command(char *cmd_str);

int handle_builtin(char **args, char **env);
int builtin_cd(char **args);
int builtin_env(char **env);
int builtin_setenv(char **args, char ***env);
int builtin_unsetenv(char **args, char ***env);
int builtin_exit(char **args);

int execute_command(cmd_t *cmd, char **env);
int setup_redirections(cmd_t *cmd);
char *find_command_path(char *command, char **env);
void handle_child_process(cmd_t *cmd, char **env, int input_fd, int output_fd);
int execute_single_pipeline(cmd_t *commands, char **env);
void parse_redirections(cmd_t *cmd);

void print_error(char *message);
int is_builtin(char *command);
char *my_strdup(char *str);
char **copy_env(char **env);
void free_env(char **env);

#endif