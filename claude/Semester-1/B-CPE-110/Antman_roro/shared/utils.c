/*
** EPITECH PROJECT, 2024
** utils.c
** File description:
** Utility functions for string manipulation and conversions
*/

#include "compression.h"
#include <stdlib.h>

int my_strcmp(const char *s1, const char *s2)
{
    if (!s1 || !s2)
        return (s1 == s2) ? 0 : (s1 ? 1 : -1);
    
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

char *my_strdup(const char *str)
{
    char *dup;
    int len;
    int i;

    if (!str)
        return NULL;
    
    len = my_strlen(str);
    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    
    for (i = 0; i <= len; i++)
        dup[i] = str[i];
    return dup;
}

int my_strlen(const char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (!str)
        return 0;
    
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

char *my_itoa(int value, char *buffer)
{
    int i = 0;
    int is_negative = 0;
    int temp;

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return buffer;
    }
    
    if (value < 0) {
        is_negative = 1;
        value = -value;
    }
    
    while (value > 0) {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }
    
    if (is_negative)
        buffer[i++] = '-';
    buffer[i] = '\0';
    
    for (int j = 0; j < i / 2; j++) {
        temp = buffer[j];
        buffer[j] = buffer[i - 1 - j];
        buffer[i - 1 - j] = temp;
    }
    return buffer;
}

int is_word_char(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || c == '\'' || c == '-');
}