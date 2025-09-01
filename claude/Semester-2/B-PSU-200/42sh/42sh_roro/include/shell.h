/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Header file for 42sh advanced shell
*/

#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <glob.h>
#include <ctype.h>

#define MAX_ARGS 1024
#define MAX_PATH 4096
#define MAX_ALIAS 256
#define MAX_HISTORY 1000
#define MAX_JOBS 100
#define MAX_VARIABLES 256

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_APPEND,
    TOKEN_REDIRECT_ERR,
    TOKEN_BACKGROUND,
    TOKEN_SEMICOLON,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_LPAR,
    TOKEN_RPAR,
    TOKEN_BACKTICK,
    TOKEN_EOF
} token_type_t;

typedef struct token_s {
    token_type_t type;
    char *value;
    struct token_s *next;
} token_t;

typedef struct cmd_s {
    char **args;
    char *input_file;
    char *output_file;
    int append_output;
    int background;
    struct cmd_s *next;
} cmd_t;

typedef struct pipeline_s {
    cmd_t *commands;
    int background;
    struct pipeline_s *next;
} pipeline_t;

typedef struct alias_s {
    char *name;
    char *value;
    struct alias_s *next;
} alias_t;

typedef struct var_s {
    char *name;
    char *value;
    struct var_s *next;
} var_t;

typedef struct job_s {
    int id;
    pid_t pgid;
    char *command;
    int status;
    struct job_s *next;
} job_t;

typedef struct shell_s {
    char **env;
    alias_t *aliases;
    var_t *variables;
    job_t *jobs;
    char **history;
    int history_count;
    int exit_status;
    int interactive;
    char *prompt;
    char cwd[MAX_PATH];
} shell_t;

extern shell_t *g_shell;

// Shell main functions
int init_shell(shell_t *shell, char **env);
void cleanup_shell(shell_t *shell);
void shell_loop(shell_t *shell);
char *read_line(void);
int execute_line(shell_t *shell, char *line);

// Lexer functions
token_t *tokenize(char *line);
void free_tokens(token_t *tokens);
token_t *create_token(token_type_t type, char *value);

// Parser functions
pipeline_t *parse_pipeline(token_t **tokens);
cmd_t *parse_command(token_t **tokens);
void free_pipeline(pipeline_t *pipeline);
void free_command(cmd_t *cmd);

// Executor functions
int execute_pipeline(shell_t *shell, pipeline_t *pipeline);
int execute_command(shell_t *shell, cmd_t *cmd);
int execute_builtin(shell_t *shell, cmd_t *cmd);

// Builtin functions
int builtin_exit(shell_t *shell, char **args);
int builtin_cd(shell_t *shell, char **args);
int builtin_echo(shell_t *shell, char **args);
int builtin_env(shell_t *shell, char **args);
int builtin_setenv(shell_t *shell, char **args);
int builtin_unsetenv(shell_t *shell, char **args);
int builtin_alias(shell_t *shell, char **args);
int builtin_unalias(shell_t *shell, char **args);
int builtin_history(shell_t *shell, char **args);
int builtin_jobs(shell_t *shell, char **args);
int builtin_fg(shell_t *shell, char **args);
int builtin_bg(shell_t *shell, char **args);
int builtin_set(shell_t *shell, char **args);
int builtin_unset(shell_t *shell, char **args);

// Environment functions
char **copy_env(char **env);
char *get_env_var(shell_t *shell, char *name);
int set_env_var(shell_t *shell, char *name, char *value);
int unset_env_var(shell_t *shell, char *name);

// Alias functions
int add_alias(shell_t *shell, char *name, char *value);
char *get_alias(shell_t *shell, char *name);
int remove_alias(shell_t *shell, char *name);
void print_aliases(shell_t *shell);

// Variable functions
int set_variable(shell_t *shell, char *name, char *value);
char *get_variable(shell_t *shell, char *name);
int unset_variable(shell_t *shell, char *name);
void print_variables(shell_t *shell);

// History functions
void add_history_entry(shell_t *shell, char *line);
void print_history(shell_t *shell);
void load_history(shell_t *shell);
void save_history(shell_t *shell);

// Globbing functions
char **expand_glob(char *pattern);
void free_glob_result(char **result);

// Job control functions
int add_job(shell_t *shell, pid_t pgid, char *command);
void remove_job(shell_t *shell, int job_id);
void update_jobs(shell_t *shell);
void print_jobs(shell_t *shell);
job_t *get_job(shell_t *shell, int job_id);

// Signal handling
void setup_signals(void);
void sigchld_handler(int sig);
void sigint_handler(int sig);

// Utility functions
char *my_strdup(char *str);
char **my_strtok(char *str, char *delim);
void free_array(char **array);
int count_array(char **array);
char *expand_variables(shell_t *shell, char *str);
char *get_prompt(shell_t *shell);

// Line editing functions
char *line_editing_read(shell_t *shell);
void setup_readline(shell_t *shell);

#endif /* !SHELL_H_ */