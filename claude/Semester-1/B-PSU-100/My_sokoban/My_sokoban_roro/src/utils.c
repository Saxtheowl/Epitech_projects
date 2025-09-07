/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Utility functions
*/

#include "sokoban.h"
#include <stdio.h>

void print_usage(void)
{
    printf("USAGE\n");
    printf("\t./my_sokoban map\n");
    printf("DESCRIPTION\n");
    printf("\tmap\tfile representing the warehouse map, containing '#' for walls,\n");
    printf("\t\t'P' for the player, 'X' for boxes and 'O' for storage locations.\n");
}

int my_strlen(const char *str)
{
    int len = 0;
    
    if (str == NULL)
        return 0;
    
    while (str[len] != '\0')
        len++;
    
    return len;
}

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    
    if (s1 == NULL || s2 == NULL)
        return -1;
    
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    
    return (s1[i] - s2[i]);
}

char *my_strdup(const char *str)
{
    char *copy;
    int len, i = 0;
    
    if (str == NULL)
        return NULL;
    
    len = my_strlen(str);
    copy = malloc(sizeof(char) * (len + 1));
    
    if (copy == NULL)
        return NULL;
    
    while (str[i] != '\0') {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    
    return copy;
}