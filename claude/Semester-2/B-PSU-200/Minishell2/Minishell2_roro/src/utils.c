/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Utility functions
*/

#include "../include/mysh.h"

void print_error(const char *command, const char *message)
{
    write(STDERR_FILENO, command, my_strlen(command));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, message, my_strlen(message));
    write(STDERR_FILENO, "\n", 1);
}

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return -1;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;

    return s1[i] - s2[i];
}

char *my_strdup(const char *s)
{
    int len, i = 0;
    char *dup;

    if (!s)
        return NULL;

    len = my_strlen(s);
    dup = malloc(len + 1);
    if (!dup)
        return NULL;

    while (i <= len) {
        dup[i] = s[i];
        i++;
    }

    return dup;
}

char *my_strcat(char *dest, const char *src)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    while (src[i]) {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';

    return dest;
}

int my_strlen(const char *s)
{
    int len = 0;

    if (!s)
        return 0;

    while (s[len])
        len++;

    return len;
}