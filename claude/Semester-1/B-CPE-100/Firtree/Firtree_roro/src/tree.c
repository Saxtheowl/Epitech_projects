/*
** EPITECH PROJECT, 2024
** tree.c
** File description:
** main tree function implementation
*/

#include "../include/tree.h"

void my_putchar(char c);

static void print_tree_section(int section, int total_size, int max_width)
{
    int lines_in_section = 3 + section;
    int start_stars = 1;
    int i = 0;
    int stars = 0;
    int spaces = 0;

    if (section > 0) {
        start_stars = 3 + (section - 1) * 2;
        lines_in_section = 3 + section;
    }

    for (i = 0; i < lines_in_section; i++) {
        stars = start_stars + i * 2;
        spaces = (max_width - stars) / 2;
        print_spaces(spaces);
        print_stars(stars);
        my_putchar('\n');
    }
}

void tree(int size)
{
    int max_width = 0;
    int i = 0;

    if (size <= 0)
        return;
    
    max_width = calculate_max_width(size);
    
    if (size == 1) {
        print_spaces((max_width - 1) / 2);
        print_stars(1);
        my_putchar('\n');
        print_spaces((max_width - 3) / 2);
        print_stars(3);
        my_putchar('\n');
        print_spaces((max_width - 5) / 2);
        print_stars(5);
        my_putchar('\n');
        print_spaces((max_width - 7) / 2);
        print_stars(7);
        my_putchar('\n');
        print_trunk(1, max_width);
        return;
    }

    for (i = 0; i < size; i++)
        print_tree_section(i, size, max_width);
    
    print_trunk(size, max_width);
}