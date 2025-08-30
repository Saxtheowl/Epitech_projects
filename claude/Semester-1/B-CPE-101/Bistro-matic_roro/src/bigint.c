/*
** EPITECH PROJECT, 2024
** bigint.c
** File description:
** big integer arithmetic operations
*/

#include <stdlib.h>
#include "../include/bistromatic.h"

static char *reverse_string(char *str)
{
    int len = my_strlen(str);
    int i = 0;
    char temp;

    while (i < len / 2) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
        i++;
    }
    return str;
}

static char *add_positive(char const *nb1, char const *nb2)
{
    int len1 = my_strlen(nb1);
    int len2 = my_strlen(nb2);
    int max_len = (len1 > len2) ? len1 : len2;
    char *result = malloc(max_len + 2);
    int carry = 0;
    int i = 0;

    if (result == NULL)
        return NULL;
    while (i < max_len || carry > 0) {
        int digit1 = (i < len1) ? nb1[len1 - 1 - i] - '0' : 0;
        int digit2 = (i < len2) ? nb2[len2 - 1 - i] - '0' : 0;
        int sum = digit1 + digit2 + carry;

        result[i] = (sum % 10) + '0';
        carry = sum / 10;
        i++;
    }
    result[i] = '\0';
    return reverse_string(result);
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