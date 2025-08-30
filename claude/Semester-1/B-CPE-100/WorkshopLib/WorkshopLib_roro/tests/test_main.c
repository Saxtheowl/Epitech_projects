/*
** EPITECH PROJECT, 2024
** test_main.c
** File description:
** simple test for libmy functions
*/

#include "../include/my.h"

int main(void)
{
    char buffer[100] = "hello";
    int tab[] = {5, 2, 8, 1, 9};
    
    my_putstr("=== LIBMY TEST SUITE ===\n");
    
    my_putstr("Testing my_strlen: ");
    my_put_nbr(my_strlen("hello"));
    my_putstr(" (expected: 5)\n");
    
    my_putstr("Testing my_strcmp: ");
    my_put_nbr(my_strcmp("abc", "abc"));
    my_putstr(" (expected: 0)\n");
    
    my_putstr("Testing my_is_prime(7): ");
    my_put_nbr(my_is_prime(7));
    my_putstr(" (expected: 1)\n");
    
    my_putstr("Testing my_compute_power_rec(2, 3): ");
    my_put_nbr(my_compute_power_rec(2, 3));
    my_putstr(" (expected: 8)\n");
    
    my_sort_int_array(tab, 5);
    my_putstr("Testing my_sort_int_array: ");
    for (int i = 0; i < 5; i++) {
        my_put_nbr(tab[i]);
        my_putchar(' ');
    }
    my_putstr("(expected: 1 2 5 8 9)\n");
    
    my_strupcase(buffer);
    my_putstr("Testing my_strupcase: ");
    my_putstr(buffer);
    my_putstr(" (expected: HELLO)\n");
    
    my_putstr("=== ALL TESTS COMPLETED ===\n");
    return 0;
}