/*
** EPITECH PROJECT, 2024
** match.c
** File description:
** match function implementation
*/

#include <stddef.h>

static int match_recursive(char const *s1, char const *s2)
{
    if (*s2 == '\0')
        return (*s1 == '\0') ? 1 : 0;
    
    if (*s2 == '*') {
        while (*s1 != '\0') {
            if (match_recursive(s1, s2 + 1))
                return 1;
            s1++;
        }
        return match_recursive(s1, s2 + 1);
    }
    
    if (*s1 == '\0' || *s1 != *s2)
        return 0;
    
    return match_recursive(s1 + 1, s2 + 1);
}

int match(char const *s1, char const *s2)
{
    if (s1 == NULL || s2 == NULL)
        return 0;
    
    return match_recursive(s1, s2);
}