/*
** EPITECH PROJECT, 2025
** FazzBizz
** File description:
** Main logic for fazzbizz
*/

#include "fazzbizz.h"

void print_number_or_special(int num)
{
    if (num % 90 == 0)
        printf("FazzBizz\n");
    else if (num % 10 == 0)
        printf("Fazz\n");
    else if (num % 9 == 0)
        printf("Bizz\n");
    else
        printf("%d\n", num);
}

int fazzbizz(int start, int end)
{
    int i;

    for (i = start; i <= end; i++)
        print_number_or_special(i);
    return 0;
}