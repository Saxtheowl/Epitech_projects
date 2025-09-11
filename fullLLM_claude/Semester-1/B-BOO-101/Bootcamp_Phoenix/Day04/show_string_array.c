/*
** EPITECH PROJECT, 2024
** Day04 - Bootcamp Phoenix
** File description:
** show_string_array.c
*/

#include <stddef.h>
#include "phoenix.h"

int show_string_array(char * const *array)
{
    int i = 0;

    while (array[i] != NULL) {
        show_string(array[i]);
        my_putchar('\n');
        i++;
    }

    return 0;
}