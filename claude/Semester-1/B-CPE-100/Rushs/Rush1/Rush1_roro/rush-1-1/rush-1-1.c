/*
** EPITECH PROJECT, 2025
** Rush1 - Assignment 1
** File description:
** rush function that displays squares with o, -, | pattern
*/

#include <unistd.h>

void my_putchar(char c);

static void print_top_bottom(int x, char corner, char horizontal)
{
    int i = 0;

    while (i < x) {
        if (i == 0 || i == x - 1)
            my_putchar(corner);
        else
            my_putchar(horizontal);
        i++;
    }
    my_putchar('\n');
}

static void print_middle(int x, char vertical, char space)
{
    int i = 0;

    while (i < x) {
        if (i == 0 || i == x - 1)
            my_putchar(vertical);
        else
            my_putchar(space);
        i++;
    }
    my_putchar('\n');
}

void rush(int x, int y)
{
    int i = 0;

    if (x <= 0 || y <= 0) {
        write(2, "Invalid size\n", 13);
        return;
    }
    while (i < y) {
        if (i == 0 || i == y - 1)
            print_top_bottom(x, 'o', '-');
        else
            print_middle(x, '|', ' ');
        i++;
    }
}