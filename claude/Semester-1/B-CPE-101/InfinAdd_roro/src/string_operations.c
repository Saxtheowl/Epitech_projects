/*
** EPITECH PROJECT, 2024
** string_operations.c
** File description:
** string operations for infinite addition
*/

#include <stdlib.h>
#include "../include/infin_add.h"

char *remove_leading_zeros(char *str)
{
    int i = 0;
    int len = my_strlen(str);
    int start = 0;

    if (str == NULL || len == 0)
        return str;
    if (str[0] == '-') {
        start = 1;
        i = 1;
    }
    while (str[i] == '0' && i < len - 1)
        i++;
    if (i > start) {
        while (str[i]) {
            str[start] = str[i];
            start++;
            i++;
        }
        str[start] = '\0';
    }
    return str;
}

int compare_absolute(char const *nb1, char const *nb2)
{
    int start1 = (nb1[0] == '-') ? 1 : 0;
    int start2 = (nb2[0] == '-') ? 1 : 0;
    int len1 = my_strlen(nb1) - start1;
    int len2 = my_strlen(nb2) - start2;
    int i = 0;

    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;
    while (nb1[start1 + i] && nb2[start2 + i]) {
        if (nb1[start1 + i] > nb2[start2 + i])
            return 1;
        if (nb1[start1 + i] < nb2[start2 + i])
            return -1;
        i++;
    }
    return 0;
}