/*
** EPITECH PROJECT, 2024
** subtraction.c
** File description:
** subtraction operations for infinite addition
*/

#include <stdlib.h>
#include "../include/infin_add.h"

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

char *subtract_positive(char const *nb1, char const *nb2)
{
    int len1 = my_strlen(nb1);
    int len2 = my_strlen(nb2);
    int max_len = (len1 > len2) ? len1 : len2;
    char *result = malloc(max_len + 2);
    int borrow = 0;
    int i = 0;
    int negative = 0;

    if (result == NULL)
        return NULL;
    if (compare_absolute(nb1, nb2) < 0) {
        char const *temp = nb1;
        nb1 = nb2;
        nb2 = temp;
        len1 = my_strlen(nb1);
        len2 = my_strlen(nb2);
        negative = 1;
    }
    while (i < len1) {
        int digit1 = nb1[len1 - 1 - i] - '0';
        int digit2 = (i < len2) ? nb2[len2 - 1 - i] - '0' : 0;
        int diff = digit1 - digit2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = diff + '0';
        i++;
    }
    result[i] = '\0';
    result = reverse_string(result);
    result = remove_leading_zeros(result);
    if (negative && my_strlen(result) > 0 && result[0] != '0') {
        char *neg_result = malloc(my_strlen(result) + 2);
        if (neg_result == NULL) {
            free(result);
            return NULL;
        }
        neg_result[0] = '-';
        my_strcpy(neg_result + 1, result);
        free(result);
        return neg_result;
    }
    return result;
}