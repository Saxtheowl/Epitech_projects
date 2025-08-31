/*
** EPITECH PROJECT, 2025
** Minishell2
** File description:
** Prototypes
*/

#ifndef MYSH2_H
    #define MYSH2_H

typedef struct env_s {
    char **vars;
} env_t;

env_t *env_create(char **envp);
void env_destroy(env_t *e);
char *env_get(env_t *e, const char *name);
int env_set(env_t *e, const char *name, const char *value);
int env_unset(env_t *e, const char *name);

char **split_words(const char *s);
char **split_commands(const char *s);
char **split_pipeline(const char *s);
void free_words(char **w);

int run_command(env_t *env, char **argv);
int run_line(env_t *env, const char *line);
int run_pipeline(env_t *env, char **segments);
int filter_redirections(char **argv, char **infile, char **outfile, int *append);
char *expand_vars(env_t *env, const char *s);

#endif /* MYSH2_H */
