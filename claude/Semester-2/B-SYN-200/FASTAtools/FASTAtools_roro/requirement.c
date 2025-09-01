/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Required function for FASTAtools project
*/

#include <stdlib.h>

static int is_alphanumeric(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

static int is_alpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

char *my_strcapitalize_synthesis(char *str)
{
    int i;
    int capitalize_next = 1;
    
    if (!str)
        return str;
    
    for (i = 0; str[i]; i++) {
        if (is_alpha(str[i])) {
            if (capitalize_next) {
                str[i] = to_upper(str[i]);
                capitalize_next = 0;
            } else {
                if (str[i] >= 'A' && str[i] <= 'Z')
                    str[i] = str[i] - 'A' + 'a';
            }
        } else if (!is_alphanumeric(str[i])) {
            capitalize_next = 1;
        }
    }
    
    return str;
}