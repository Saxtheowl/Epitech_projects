/*
** EPITECH PROJECT, 2024
** test_main.c
** File description:
** test for match and nmatch functions
*/

#include "../include/match.h"
#include "../include/my.h"

static void test_match_basic(void)
{
    my_putstr("Testing match function:\n");
    
    my_putstr("match(\"main.c\", \"*.c\"): ");
    my_putnbr(match("main.c", "*.c"));
    my_putstr(" (expected: 1)\n");
    
    my_putstr("match(\"hello\", \"world\"): ");
    my_putnbr(match("hello", "world"));
    my_putstr(" (expected: 0)\n");
    
    my_putstr("match(\"hello\", \"hello\"): ");
    my_putnbr(match("hello", "hello"));
    my_putstr(" (expected: 1)\n");
    
    my_putstr("match(\"\", \"*\"): ");
    my_putnbr(match("", "*"));
    my_putstr(" (expected: 1)\n");
}

static void test_nmatch_basic(void)
{
    my_putstr("\nTesting nmatch function:\n");
    
    my_putstr("nmatch(\"abcbd\", \"*b*\"): ");
    my_putnbr(nmatch("abcbd", "*b*"));
    my_putstr(" (expected: 2)\n");
    
    my_putstr("nmatch(\"abc\", \"a**\"): ");
    my_putnbr(nmatch("abc", "a**"));
    my_putstr(" (expected: 3)\n");
    
    my_putstr("nmatch(\"hello\", \"h*o\"): ");
    my_putnbr(nmatch("hello", "h*o"));
    my_putstr(" (expected: 1)\n");
    
    my_putstr("nmatch(\"test\", \"no\"): ");
    my_putnbr(nmatch("test", "no"));
    my_putstr(" (expected: 0)\n");
}

int main(void)
{
    test_match_basic();
    test_nmatch_basic();
    my_putstr("\nTest completed.\n");
    return 0;
}