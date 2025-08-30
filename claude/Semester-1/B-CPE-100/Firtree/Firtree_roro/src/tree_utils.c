/*
** EPITECH PROJECT, 2024
** tree_utils.c
** File description:
** utility functions for fir tree
*/

#include "../include/tree.h"

void my_putchar(char c);

void print_spaces(int count)
{
    int i = 0;

    for (i = 0; i < count; i++)
        my_putchar(' ');
}

void print_stars(int count)
{
    int i = 0;

    for (i = 0; i < count; i++)
        my_putchar('*');
}

void print_trunk(int size, int max_width)
{
    int i = 0;
    int j = 0;
    int trunk_width = size;
    int spaces = (max_width - trunk_width) / 2;

    for (i = 0; i < size; i++) {
        print_spaces(spaces);
        for (j = 0; j < trunk_width; j++)
            my_putchar('|');
        my_putchar('\n');
    }
}

int calculate_max_width(int size)
{
    if (size <= 0)
        return 0;
    if (size == 1)
        return 7;
    return 2 * (size + 1) * 4 - 1;
}