/*
** EPITECH PROJECT, 2025
** Minishell2
** File description:
** Env helpers
*/

#include <stdlib.h>
#include <string.h>
#include "mysh2.h"

static size_t count_env(char **envp)
{
    size_t n = 0;
    while (envp && envp[n])
        n++;
    return n;
}

env_t *env_create(char **envp)
{
    env_t *e = malloc(sizeof(env_t));
    size_t n;
    size_t i;

    if (!e)
        return NULL;
    n = count_env(envp);
    e->vars = malloc(sizeof(char *) * (n + 1));
    if (!e->vars) {
        free(e);
        return NULL;
    }
    for (i = 0; i < n; ++i)
        e->vars[i] = strdup(envp[i]);
    e->vars[n] = NULL;
    return e;
}

void env_destroy(env_t *e)
{
    size_t i = 0;
    if (!e)
        return;
    while (e->vars && e->vars[i]) {
        free(e->vars[i]);
        i++;
    }
    free(e->vars);
    free(e);
}

char *env_get(env_t *e, const char *name)
{
    size_t len = strlen(name);
    size_t i = 0;
    while (e->vars && e->vars[i]) {
        if (strncmp(e->vars[i], name, len) == 0 && e->vars[i][len] == '=')
            return e->vars[i] + len + 1;
        i++;
    }
    return NULL;
}

int env_set(env_t *e, const char *name, const char *value)
{
    size_t len = strlen(name);
    size_t i = 0;
    char *nv;

    while (e->vars && e->vars[i]) {
        if (strncmp(e->vars[i], name, len) == 0 && e->vars[i][len] == '=') {
            nv = malloc(len + 1 + strlen(value) + 1);
            if (!nv)
                return 0;
            memcpy(nv, name, len);
            nv[len] = '=';
            strcpy(nv + len + 1, value);
            free(e->vars[i]);
            e->vars[i] = nv;
            return 1;
        }
        i++;
    }
    e->vars = realloc(e->vars, sizeof(char *) * (i + 2));
    if (!e->vars)
        return 0;
    nv = malloc(len + 1 + strlen(value) + 1);
    if (!nv)
        return 0;
    memcpy(nv, name, len);
    nv[len] = '=';
    strcpy(nv + len + 1, value);
    e->vars[i] = nv;
    e->vars[i + 1] = NULL;
    return 1;
}

int env_unset(env_t *e, const char *name)
{
    size_t len = strlen(name);
    size_t i = 0;

    while (e->vars && e->vars[i]) {
        if (strncmp(e->vars[i], name, len) == 0 && e->vars[i][len] == '=')
            break;
        i++;
    }
    if (!e->vars || !e->vars[i])
        return 1;
    free(e->vars[i]);
    while (e->vars[i]) {
        e->vars[i] = e->vars[i + 1];
        i++;
    }
    return 1;
}

