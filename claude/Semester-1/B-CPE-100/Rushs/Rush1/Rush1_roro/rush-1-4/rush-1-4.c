/*
** EPITECH PROJECT, 2025
** Rush1 - Assignment 4
** File description:
** rush function that displays squares with A, B, C pattern (symmetric)
*/

#include <unistd.h>

void my_putchar(char c);

static void print_top_bottom_line(int x)
{
    int i = 0;

    if (x == 1) {
        my_putchar('B');
        my_putchar('\n');
        return;
    }
    my_putchar('A');
    while (i < x - 2) {
        my_putchar('B');
        i++;
    }
    my_putchar('C');
    my_putchar('\n');
}

static void print_middle_line(int x)
{
    int i = 0;

    if (x == 1) {
        my_putchar('B');
        my_putchar('\n');
        return;
    }
    my_putchar('B');
    while (i < x - 2) {
        my_putchar(' ');
        i++;
    }
    my_putchar('B');
    my_putchar('\n');
}

static void print_full_bs(int x)
{
    int i = 0;

    while (i < x) {
        my_putchar('B');
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
    if (y == 1) {
        print_full_bs(x);
        return;
    }
    while (i < y) {
        if (i == 0 || i == y - 1)
            print_top_bottom_line(x);
        else
            print_middle_line(x);
        i++;
    }
}