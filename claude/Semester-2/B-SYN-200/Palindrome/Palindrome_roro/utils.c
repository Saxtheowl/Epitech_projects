/*
** EPITECH PROJECT, 2025
** Palindrome
** File description:
** Utility functions
*/

#include "palindrome.h"

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
    int sign = 1;
    int i = 0;
    
    if (!str)
        return 0;
    
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    } else if (str[0] == '+') {
        i = 1;
    }
    
    while (str[i] && str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}

int is_valid_number(char *str)
{
    int i = 0;
    
    if (!str || my_strlen(str) == 0)
        return 0;
    
    if (str[0] == '-' || str[0] == '+')
        i = 1;
    
    if (str[i] == '\0')
        return 0;
    
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    
    return 1;
}