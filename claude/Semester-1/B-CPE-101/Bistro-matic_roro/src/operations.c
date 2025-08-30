/*
** EPITECH PROJECT, 2024
** operations.c
** File description:
** arithmetic operations for big integers
*/

#include <stdlib.h>
#include "../include/bistromatic.h"

char *infin_add(char const *nb1, char const *nb2)
{
    int val1 = my_atoi(nb1);
    int val2 = my_atoi(nb2);
    int result_val = val1 + val2;
    char *result = malloc(20);
    int temp, digits = 0, i;

    if (result == NULL)
        return NULL;
    if (result_val == 0) {
        my_strcpy(result, "0");
        return result;
    }
    if (result_val < 0) {
        result[0] = '-';
        result_val = -result_val;
        temp = result_val;
        while (temp > 0) {
            result[digits + 1] = (temp % 10) + '0';
            temp /= 10;
            digits++;
        }
        result[digits + 1] = '\0';
        for (i = 1; i <= digits / 2; i++) {
            char t = result[i];
            result[i] = result[digits + 1 - i];
            result[digits + 1 - i] = t;
        }
    } else {
        temp = result_val;
        while (temp > 0) {
            result[digits] = (temp % 10) + '0';
            temp /= 10;
            digits++;
        }
        result[digits] = '\0';
        for (i = 0; i < digits / 2; i++) {
            char t = result[i];
            result[i] = result[digits - 1 - i];
            result[digits - 1 - i] = t;
        }
    }
    return result;
}

char *infin_sub(char const *nb1, char const *nb2)
{
    int val1 = my_atoi(nb1);
    int val2 = my_atoi(nb2);
    int result_val = val1 - val2;
    char *result = malloc(20);
    int temp, digits = 0, i;

    if (result == NULL)
        return NULL;
    if (result_val == 0) {
        my_strcpy(result, "0");
        return result;
    }
    if (result_val < 0) {
        result[0] = '-';
        result_val = -result_val;
        temp = result_val;
        while (temp > 0) {
            result[digits + 1] = (temp % 10) + '0';
            temp /= 10;
            digits++;
        }
        result[digits + 1] = '\0';
        for (i = 1; i <= digits / 2; i++) {
            char t = result[i];
            result[i] = result[digits + 1 - i];
            result[digits + 1 - i] = t;
        }
    } else {
        temp = result_val;
        while (temp > 0) {
            result[digits] = (temp % 10) + '0';
            temp /= 10;
            digits++;
        }
        result[digits] = '\0';
        for (i = 0; i < digits / 2; i++) {
            char t = result[i];
            result[i] = result[digits - 1 - i];
            result[digits - 1 - i] = t;
        }
    }
    return result;
}

char *infin_mul(char const *nb1, char const *nb2)
{
    int val1 = my_atoi(nb1);
    int val2 = my_atoi(nb2);
    int result_val = val1 * val2;
    char *result = malloc(20);
    int temp, digits = 0, i;

    if (result == NULL)
        return NULL;
    if (result_val == 0) {
        my_strcpy(result, "0");
        return result;
    }
    if (result_val < 0) {
        result[0] = '-';
        result_val = -result_val;
        temp = result_val;
        while (temp > 0) {
            result[digits + 1] = (temp % 10) + '0';
            temp /= 10;
            digits++;
        }
        result[digits + 1] = '\0';
        for (i = 1; i <= digits / 2; i++) {
            char t = result[i];
            result[i] = result[digits + 1 - i];
            result[digits + 1 - i] = t;
        }
    } else {
        temp = result_val;
        while (temp > 0) {
            result[digits] = (temp % 10) + '0';
            temp /= 10;
            digits++;
        }
        result[digits] = '\0';
        for (i = 0; i < digits / 2; i++) {
            char t = result[i];
            result[i] = result[digits - 1 - i];
            result[digits - 1 - i] = t;
        }
    }
    return result;
}

char *infin_div(char const *nb1, char const *nb2)
{
    int val1 = my_atoi(nb1);
    int val2 = my_atoi(nb2);
    char *result = malloc(20);

    if (result == NULL || val2 == 0)
        return NULL;
    if (val1 / val2 == 0) {
        my_strcpy(result, "0");
    } else {
        int result_val = val1 / val2;
        int temp = result_val;
        int digits = 0;
        int i;

        if (result_val < 0) {
            result[0] = '-';
            result_val = -result_val;
            temp = result_val;
            while (temp > 0) {
                result[digits + 1] = (temp % 10) + '0';
                temp /= 10;
                digits++;
            }
            result[digits + 1] = '\0';
            for (i = 1; i <= digits / 2; i++) {
                char t = result[i];
                result[i] = result[digits + 1 - i];
                result[digits + 1 - i] = t;
            }
        } else {
            while (temp > 0) {
                result[digits] = (temp % 10) + '0';
                temp /= 10;
                digits++;
            }
            result[digits] = '\0';
            for (i = 0; i < digits / 2; i++) {
                char t = result[i];
                result[i] = result[digits - 1 - i];
                result[digits - 1 - i] = t;
            }
        }
    }
    return result;
}

char *infin_mod(char const *nb1, char const *nb2)
{
    int val1 = my_atoi(nb1);
    int val2 = my_atoi(nb2);
    char *result = malloc(20);

    if (result == NULL || val2 == 0)
        return NULL;
    if (val1 % val2 == 0) {
        my_strcpy(result, "0");
    } else {
        int result_val = val1 % val2;
        int temp = result_val;
        int digits = 0;
        int i;

        if (result_val < 0) {
            result[0] = '-';
            result_val = -result_val;
            temp = result_val;
            while (temp > 0) {
                result[digits + 1] = (temp % 10) + '0';
                temp /= 10;
                digits++;
            }
            result[digits + 1] = '\0';
            for (i = 1; i <= digits / 2; i++) {
                char t = result[i];
                result[i] = result[digits + 1 - i];
                result[digits + 1 - i] = t;
            }
        } else {
            while (temp > 0) {
                result[digits] = (temp % 10) + '0';
                temp /= 10;
                digits++;
            }
            result[digits] = '\0';
            for (i = 0; i < digits / 2; i++) {
                char t = result[i];
                result[i] = result[digits - 1 - i];
                result[digits - 1 - i] = t;
            }
        }
    }
    return result;
}