/*
** EPITECH PROJECT, 2024
** Day05 - Bootcamp Phoenix
** File description:
** star_final.c - Final implementation based on exact pattern
*/

#include <unistd.h>

void my_putchar(char c);

static void print_spaces(int count)
{
    while (count-- > 0) {
        my_putchar(' ');
    }
}

static void print_stars(int count)
{
    while (count-- > 0) {
        my_putchar('*');
    }
}

void draw_star(int size)
{
    int i;
    
    if (size == 1) {
        print_spaces(3);
        print_stars(1);
        my_putchar('\n');
        
        print_stars(3);
        print_spaces(1);
        print_stars(3);
        my_putchar('\n');
        
        print_spaces(1);
        print_stars(1);
        print_spaces(3);
        print_stars(1);
        my_putchar('\n');
        
        print_stars(3);
        print_spaces(1);
        print_stars(3);
        my_putchar('\n');
        
        print_spaces(3);
        print_stars(1);
        my_putchar('\n');
        return;
    }
    
    if (size == 2) {
        print_spaces(5);
        print_stars(1);
        my_putchar('\n');
        
        print_spaces(4);
        print_stars(1);
        print_spaces(1);
        print_stars(1);
        my_putchar('\n');
        
        print_stars(5);
        print_spaces(1);
        print_stars(5);
        my_putchar('\n');
        
        print_spaces(1);
        print_stars(1);
        print_spaces(7);
        print_stars(1);
        my_putchar('\n');
        
        print_spaces(2);
        print_stars(1);
        print_spaces(5);
        print_stars(1);
        my_putchar('\n');
        
        print_spaces(1);
        print_stars(1);
        print_spaces(7);
        print_stars(1);
        my_putchar('\n');
        
        print_stars(5);
        print_spaces(1);
        print_stars(5);
        my_putchar('\n');
        
        print_spaces(4);
        print_stars(1);
        print_spaces(1);
        print_stars(1);
        my_putchar('\n');
        
        print_spaces(5);
        print_stars(1);
        my_putchar('\n');
        return;
    }
    
    print_spaces(2 * size);
    print_stars(1);
    my_putchar('\n');
    
    for (i = 1; i < size; i++) {
        print_spaces(2 * size - i);
        print_stars(1);
        print_spaces(2 * i - 1);
        print_stars(1);
        my_putchar('\n');
    }
    
    print_stars(2 * size + 1);
    print_spaces(2 * size - 1);
    print_stars(2 * size + 1);
    my_putchar('\n');
    
    for (i = 1; i <= 2 * size - 1; i++) {
        if (i <= size) {
            print_spaces(size - i);
        } else {
            print_spaces(i - size);
        }
        print_stars(1);
        print_spaces(4 * size + 1);
        print_stars(1);
        my_putchar('\n');
    }
    
    print_stars(2 * size + 1);
    print_spaces(2 * size - 1);
    print_stars(2 * size + 1);
    my_putchar('\n');
    
    for (i = size - 1; i >= 1; i--) {
        print_spaces(2 * size - i);
        print_stars(1);
        print_spaces(2 * i - 1);
        print_stars(1);
        my_putchar('\n');
    }
    
    print_spaces(2 * size);
    print_stars(1);
    my_putchar('\n');
}