/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Header file for enhanced mysh minishell with pipes and redirections
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
#define MAX_PIPES 16
#define MAX_REDIRECTS 8

typedef enum {
    TOKEN_COMMAND,
    TOKEN_PIPE,
    TOKEN_SEMICOLON,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_APPEND,
    TOKEN_REDIRECT_HEREDOC,
    TOKEN_END
} token_type_t;

typedef struct token_s {
    token_type_t type;
    char *value;
    struct token_s *next;
} token_t;

typedef struct redirect_s {
    int type;
    char *file;
    int fd;
} redirect_t;

typedef struct command_s {
    char **args;
    int arg_count;
    redirect_t *redirects;
    int redirect_count;
    struct command_s *next;
} command_t;

typedef struct pipeline_s {
    command_t *commands;
    int command_count;
    struct pipeline_s *next;
} pipeline_t;

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

/* Advanced execution */
int execute_pipeline(shell_t *shell, pipeline_t *pipeline);
int execute_simple_command(shell_t *shell, command_t *cmd);
int setup_redirects(command_t *cmd, int *saved_fds);
void restore_redirects(int *saved_fds);

/* Parsing */
token_t *tokenize_line(char *line);
pipeline_t *parse_tokens(token_t *tokens);
command_t *parse_command_tokens(token_t **tokens);
void free_tokens(token_t *tokens);
void free_pipeline(pipeline_t *pipeline);
void free_command(command_t *command);

/* Token utilities */
token_t *create_token(token_type_t type, const char *value);
void add_token(token_t **head, token_t *token);
int is_redirect_token(token_type_t type);

/* Shell loop */
void shell_loop(shell_t *shell);
void display_prompt(void);
int process_line(shell_t *shell, char *line);

/* Utility functions */
void print_error(const char *command, const char *message);
int my_strcmp(const char *s1, const char *s2);
char *my_strdup(const char *s);
char *my_strcat(char *dest, const char *src);
int my_strlen(const char *s);

#endif /* !MYSH_H_ */