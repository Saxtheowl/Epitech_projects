/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** Utility functions
*/

#include "../include/tetris.h"

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

int my_strlen(const char *s)
{
    int len = 0;

    if (!s)
        return 0;

    while (s[len])
        len++;

    return len;
}

void print_error(const char *message)
{
    fprintf(stderr, "tetris: %s\n", message);
}

char *format_time(time_t seconds)
{
    char *time_str = malloc(16);
    int minutes = seconds / 60;
    int secs = seconds % 60;

    if (!time_str)
        return NULL;

    snprintf(time_str, 16, "%02d:%02d", minutes, secs);
    return time_str;
}