/*
** EPITECH PROJECT, 2024
** Day03 - Bootcamp Phoenix
** File description:
** sorted_params.c
*/

#include "../includes/phoenix.h"

static void sort_strings(char **arr, int size)
{
    int i, j;
    char *temp;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (my_strncmp(arr[j], arr[j + 1], 1000) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char **argv)
{
    int i = 0;

    sort_strings(argv, argc);

    while (i < argc) {
        show_string(argv[i]);
        my_putchar('\n');
        i++;
    }

    return 0;
}