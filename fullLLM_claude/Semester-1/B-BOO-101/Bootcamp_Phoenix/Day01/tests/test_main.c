/*
** EPITECH PROJECT, 2024
** test_main
** File description:
** Test program for Day01 tasks
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function prototypes
int show_alphabet(void);
int show_combinations(void);
int show_number(int nb);
int show_string(char const *str);
char *reverse_string(char *str);
int to_number(char const *str);
int my_putchar(char c);

static void test_show_alphabet(void)
{
    printf("Testing show_alphabet():\n");
    show_alphabet();
    printf("\n\n");
}

static void test_show_combinations(void)
{
    printf("Testing show_combinations():\n");
    show_combinations();
    printf("\n\n");
}

static void test_show_number(void)
{
    printf("Testing show_number():\n");
    printf("show_number(42): ");
    show_number(42);
    printf("\n");
    printf("show_number(0): ");
    show_number(0);
    printf("\n");
    printf("show_number(-2147483647): ");
    show_number(-2147483647);
    printf("\n");
    printf("show_number(-2147483648): ");
    show_number(-2147483648);
    printf("\n\n");
}

static void test_show_string(void)
{
    printf("Testing show_string():\n");
    printf("show_string(\"Hello World\"): ");
    show_string("Hello World");
    printf("\n");
    printf("show_string(\"\"): ");
    show_string("");
    printf("\n\n");
}

static void test_reverse_string(void)
{
    char *test_str;
    
    printf("Testing reverse_string():\n");
    
    test_str = strdup("a");
    printf("reverse_string(\"%s\"): %s\n", "a", reverse_string(test_str));
    free(test_str);
    
    test_str = strdup("ab");
    printf("reverse_string(\"%s\"): %s\n", "ab", reverse_string(test_str));
    free(test_str);
    
    test_str = strdup("abc");
    printf("reverse_string(\"%s\"): %s\n", "abc", reverse_string(test_str));
    free(test_str);
    
    test_str = strdup("abcd");
    printf("reverse_string(\"%s\"): %s\n", "abcd", reverse_string(test_str));
    free(test_str);
    
    test_str = strdup("abcde");
    printf("reverse_string(\"%s\"): %s\n", "abcde", reverse_string(test_str));
    free(test_str);
    
    test_str = strdup("abcdef");
    printf("reverse_string(\"%s\"): %s\n", "abcdef", reverse_string(test_str));
    free(test_str);
    
    printf("\n");
}

static void test_to_number(void)
{
    printf("Testing to_number():\n");
    printf("to_number(\"42\"): %d\n", to_number("42"));
    printf("to_number(\"-42\"): %d\n", to_number("-42"));
    printf("to_number(\"   42  \"): %d\n", to_number("   42  "));
    printf("to_number(\"+---+-+---+-42\"): %d\n", to_number("+---+-+---+-42"));
    printf("to_number(\"42a43\"): %d\n", to_number("42a43"));
    printf("to_number(\"11000000000000000000000042\"): %d\n", to_number("11000000000000000000000042"));
    printf("to_number(\"-1000000000000000000000042\"): %d\n", to_number("-1000000000000000000000042"));
    printf("\n");
}

int main(void)
{
    printf("=== DAY01 TESTS ===\n\n");
    
    test_show_alphabet();
    test_show_combinations();
    test_show_number();
    test_show_string();
    test_reverse_string();
    test_to_number();
    
    printf("=== TESTS COMPLETED ===\n");
    return 0;
}