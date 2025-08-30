/*
** EPITECH PROJECT, 2024
** nmatch.c
** File description:
** nmatch function implementation
*/

#include <stddef.h>

static int nmatch_recursive(char const *s1, char const *s2)
{
    int count = 0;
    
    if (*s2 == '\0')
        return (*s1 == '\0') ? 1 : 0;
    
    if (*s2 == '*') {
        while (*s1 != '\0') {
            count += nmatch_recursive(s1, s2 + 1);
            s1++;
        }
        count += nmatch_recursive(s1, s2 + 1);
        return count;
    }
    
    if (*s1 == '\0' || *s1 != *s2)
        return 0;
    
    return nmatch_recursive(s1 + 1, s2 + 1);
}

int nmatch(char const *s1, char const *s2)
{
    if (s1 == NULL || s2 == NULL)
        return 0;
    
    return nmatch_recursive(s1, s2);
}