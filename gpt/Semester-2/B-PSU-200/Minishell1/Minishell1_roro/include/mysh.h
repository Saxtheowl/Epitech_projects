/*
** EPITECH PROJECT, 2025
** Minishell1
** File description:
** Prototypes and structures
*/

#ifndef MYSH_H
    #define MYSH_H

typedef struct env_s {
    char **vars;
} env_t;

int mysh_loop(env_t *env);
env_t *env_create(char **envp);
void env_destroy(env_t *e);
char *env_get(env_t *e, const char *name);
int env_set(env_t *e, const char *name, const char *value);
int env_unset(env_t *e, const char *name);
int run_command(env_t *env, char **argv);
char **split_words(const char *s);
void free_words(char **w);

#endif /* MYSH_H */

