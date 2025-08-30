/*
** EPITECH PROJECT, 2024
** utilities.c
** File description:
** utility functions
*/

#include "../../include/my.h"

void my_swap(int *a, int *b)
{
    int temp = 0;

    if (a == NULL || b == NULL)
        return;
    temp = *a;
    *a = *b;
    *b = temp;
}

int my_getnbr(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str == NULL)
        return 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

void my_sort_int_array(int *tab, int size)
{
    int i = 0;
    int j = 0;

    if (tab == NULL || size <= 0)
        return;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                my_swap(&tab[j], &tab[j + 1]);
            }
        }
    }
}