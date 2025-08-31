/*
** EPITECH PROJECT, 2025
** Minishell2
** File description:
** Split helpers
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mysh2.h"

char **split_words(const char *s)
{
    int count = 0;
    int in = 0;
    int i = 0;
    int j = 0;
    char **w;

    while (s[i]) {
        if (isspace((unsigned char)s[i]))
            in = 0;
        else if (!in) {
            in = 1;
            count++;
        }
        i++;
    }
    w = malloc(sizeof(char *) * (count + 1));
    if (!w)
        return NULL;
    i = 0;
    while (s[i]) {
        while (isspace((unsigned char)s[i]))
            i++;
        if (!s[i])
            break;
        int k = i;
        while (s[i] && !isspace((unsigned char)s[i]))
            i++;
        w[j] = strndup(s + k, (size_t)(i - k));
        if (!w[j])
            return NULL;
        j++;
    }
    w[j] = NULL;
    return w;
}

char **split_commands(const char *s)
{
    int count = 1;
    int i = 0;
    int j = 0;
    char **arr;

    while (s[i])
        count += (s[i++] == ';');
    arr = malloc(sizeof(char *) * (count + 1));
    if (!arr)
        return NULL;
    i = 0;
    int start = 0;
    while (1) {
        if (s[i] == ';' || s[i] == '\0') {
            arr[j] = strndup(s + start, (size_t)(i - start));
            if (!arr[j])
                return NULL;
            j++;
            start = i + 1;
        }
        if (s[i] == '\0')
            break;
        i++;
    }
    arr[j] = NULL;
    return arr;
}

static int count_char(const char *s, char c)
{
    int n = 0; int i = 0;
    while (s[i]) { if (s[i] == c) n++; i++; }
    return n;
}

/* split a command line into pipeline segments (by '|') */
char **split_pipeline(const char *s)
{
    int count = count_char(s, '|') + 1;
    char **arr = malloc(sizeof(char*) * (count + 1));
    int i = 0; int j = 0; int start = 0;
    if (!arr) return NULL;
    while (1) {
        if (s[i] == '|' || s[i] == '\0') {
            arr[j] = strndup(s + start, (size_t)(i - start));
            if (!arr[j]) return NULL;
            j++; start = i + 1;
        }
        if (s[i] == '\0') break;
        i++;
    }
    arr[j] = NULL; return arr;
}

void free_words(char **w)
{
    int i = 0;
    if (!w)
        return;
    while (w[i]) {
        free(w[i]);
        i++;
    }
    free(w);
}

static int is_name_start(char c)
{
    return isalpha((unsigned char)c) || c == '_';
}

static int is_name_char(char c)
{
    return isalnum((unsigned char)c) || c == '_';
}

char *expand_vars(env_t *env, const char *s)
{
    size_t cap = strlen(s) + 1;
    char *out = malloc(cap);
    size_t k = 0;
    size_t i = 0;
    if (!out) return NULL;
    while (s[i] != '\0') {
        if (s[i] == '$' && is_name_start(s[i + 1])) {
            size_t j = i + 1;
            while (is_name_char(s[j])) j++;
            char *name = strndup(s + i + 1, j - (i + 1));
            const char *val = env_get(env, name);
            size_t need = val ? strlen(val) : 0;
            while (k + need + 1 > cap) { cap *= 2; out = realloc(out, cap); }
            if (val) { memcpy(out + k, val, need); k += need; }
            free(name);
            i = j;
            continue;
        }
        if (k + 2 > cap) { cap *= 2; out = realloc(out, cap); }
        out[k++] = s[i++];
    }
    out[k] = '\0';
    return out;
}
