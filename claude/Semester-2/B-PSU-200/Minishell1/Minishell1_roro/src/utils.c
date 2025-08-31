/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** Utility functions
*/

#include "../include/mysh.h"

void print_error(const char *command, const char *message)
{
    write(2, command, my_strlen(command));
    write(2, ": ", 2);
    write(2, message, my_strlen(message));
    write(2, "\n", 1);
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