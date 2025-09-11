/*
** EPITECH PROJECT, 2024
** Day08 - B-CPE-100
** File description:
** my_strdup.c - TASK 01
*/

#include <stdlib.h>
#include <stddef.h>

int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);

char *my_strdup(char const *src)
{
    int len;
    char *dest;
    
    if (src == NULL)
        return NULL;
    
    len = my_strlen(src);
    dest = malloc(sizeof(char) * (len + 1));
    
    if (dest == NULL)
        return NULL;
    
    my_strcpy(dest, src);
    return dest;
}