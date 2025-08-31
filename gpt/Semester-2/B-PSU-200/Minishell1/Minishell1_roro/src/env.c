/*
** EPITECH PROJECT, 2025
** Minishell1
** File description:
** Env helpers
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mysh.h"

static size_t count_env(char **envp)
{
    size_t n;

    n = 0;
    while (envp && envp[n])
        n = n + 1;
    return n;
}

env_t *env_create(char **envp)
{
    env_t *e;
    size_t n;
    size_t i;

    e = malloc(sizeof(env_t));
    if (!e)
        return NULL;
    n = count_env(envp);
    e->vars = malloc(sizeof(char *) * (n + 1));
    if (!e->vars) {
        free(e);
        return NULL;
    }
    i = 0;
    while (i < n) {
        e->vars[i] = strdup(envp[i]);
        i = i + 1;
    }
    e->vars[n] = NULL;
    return e;
}

void env_destroy(env_t *e)
{
    size_t i;

    if (!e)
        return;
    i = 0;
    while (e->vars && e->vars[i]) {
        free(e->vars[i]);
        i = i + 1;
    }
    free(e->vars);
    free(e);
}

char *env_get(env_t *e, const char *name)
{
    size_t len;
    size_t i;

    len = strlen(name);
    i = 0;
    while (e->vars && e->vars[i]) {
        if (strncmp(e->vars[i], name, len) == 0 && e->vars[i][len] == '=')
            return e->vars[i] + len + 1;
        i = i + 1;
    }
    return NULL;
}

static int replace_or_add(env_t *e, const char *name, const char *value)
{
    size_t len;
    size_t i;
    char *nv;

    len = strlen(name);
    i = 0;
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
        i = i + 1;
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

int env_set(env_t *e, const char *name, const char *value)
{
    if (!name || !value)
        return 0;
    return replace_or_add(e, name, value);
}

int env_unset(env_t *e, const char *name)
{
    size_t len;
    size_t i;
    size_t j;

    len = strlen(name);
    i = 0;
    while (e->vars && e->vars[i]) {
        if (strncmp(e->vars[i], name, len) == 0 && e->vars[i][len] == '=')
            break;
        i = i + 1;
    }
    if (!e->vars || !e->vars[i])
        return 1;
    free(e->vars[i]);
    j = i;
    while (e->vars[j]) {
        e->vars[j] = e->vars[j + 1];
        j = j + 1;
    }
    return 1;
}

