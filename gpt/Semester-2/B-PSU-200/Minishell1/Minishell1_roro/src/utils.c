/*
** EPITECH PROJECT, 2025
** Minishell1
** File description:
** Utils: split/free
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int count_words(const char *s)
{
    int n;
    int in;
    int i;

    n = 0;
    in = 0;
    i = 0;
    while (s[i] != '\0') {
        if (isspace((unsigned char)s[i]))
            in = 0;
        else if (!in) {
            in = 1;
            n = n + 1;
        }
        i = i + 1;
    }
    return n;
}

char **split_words(const char *s)
{
    int n;
    char **w;
    int i;
    int j;
    int k;

    n = count_words(s);
    w = malloc(sizeof(char *) * (n + 1));
    if (!w)
        return NULL;
    i = 0;
    j = 0;
    while (s[i] != '\0') {
        while (isspace((unsigned char)s[i]))
            i = i + 1;
        if (s[i] == '\0')
            break;
        k = i;
        while (s[i] != '\0' && !isspace((unsigned char)s[i]))
            i = i + 1;
        w[j] = strndup(s + k, (size_t)(i - k));
        if (!w[j])
            return NULL;
        j = j + 1;
    }
    w[j] = NULL;
    return w;
}

void free_words(char **w)
{
    int i;

    if (!w)
        return;
    i = 0;
    while (w[i]) {
        free(w[i]);
        i = i + 1;
    }
    free(w);
}

