/*
** EPITECH PROJECT, 2024
** string_extra.c
** File description:
** extra string functions
*/

#include "../../include/my.h"

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int j = 0;

    if (str == NULL || to_find == NULL)
        return NULL;
    if (to_find[0] == '\0')
        return str;
    while (str[i] != '\0') {
        j = 0;
        while (str[i + j] == to_find[j] && to_find[j] != '\0')
            j++;
        if (to_find[j] == '\0')
            return &str[i];
        i++;
    }
    return NULL;
}

int my_showstr(char const *str)
{
    int i = 0;
    int count = 0;

    if (str == NULL)
        return 0;
    while (str[i] != '\0') {
        if (str[i] >= 32 && str[i] <= 126) {
            my_putchar(str[i]);
        } else {
            my_putchar('\\');
            if (str[i] < 8) {
                my_putchar('0');
                my_putchar('0');
                my_putchar('0' + str[i]);
            } else if (str[i] < 64) {
                my_putchar('0');
                my_putchar('0' + str[i] / 8);
                my_putchar('0' + str[i] % 8);
            } else {
                my_putchar('0' + str[i] / 64);
                my_putchar('0' + (str[i] % 64) / 8);
                my_putchar('0' + str[i] % 8);
            }
        }
        i++;
        count++;
    }
    return count;
}

int my_showmem(char const *str, int size)
{
    int i = 0;
    
    if (str == NULL || size <= 0)
        return 0;
    while (i < size) {
        if (str[i] >= 32 && str[i] <= 126)
            my_putchar(str[i]);
        else
            my_putchar('.');
        i++;
    }
    return size;
}