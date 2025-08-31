/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Prototypes
*/

#ifndef SH_H
    #define SH_H

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
char *expand_vars(env_t *env, const char *s);

int run_command(env_t *env, char **argv);
int run_pipeline(env_t *env, char **segments);
int run_line(env_t *env, const char *line);

#endif /* SH_H */

