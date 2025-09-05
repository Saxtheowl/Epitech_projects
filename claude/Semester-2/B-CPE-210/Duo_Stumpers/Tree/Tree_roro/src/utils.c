/*
** EPITECH PROJECT, 2025
** Tree
** File description:
** utils
*/

#include "tree.h"

int my_strlen(char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_atoi(char *str)
{
    int result = 0;
    int i = 0;

    if (!str)
        return -1;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return -1;
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

void my_strcpy(char *dest, char *src)
{
    int i = 0;

    if (!dest || !src)
        return;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

char *my_strdup(char *str)
{
    char *dup = NULL;
    int len = 0;
    int i = 0;

    if (!str)
        return NULL;
    len = my_strlen(str);
    dup = malloc((len + 1) * sizeof(char));
    if (!dup)
        return NULL;
    for (i = 0; i <= len; i++)
        dup[i] = str[i];
    return dup;
}

int is_hidden(char *name)
{
    return (name && name[0] == '.' && name[1] != '\0');
}

char *join_path(char *dir, char *name)
{
    char *path = NULL;
    int dir_len = my_strlen(dir);
    int name_len = my_strlen(name);
    int i = 0;
    int j = 0;

    if (!dir || !name)
        return NULL;
    path = malloc((dir_len + name_len + 2) * sizeof(char));
    if (!path)
        return NULL;
    for (i = 0; i < dir_len; i++)
        path[i] = dir[i];
    if (dir_len > 0 && dir[dir_len - 1] != '/') {
        path[i] = '/';
        i++;
    }
    for (j = 0; j < name_len; j++)
        path[i + j] = name[j];
    path[i + j] = '\0';
    return path;
}