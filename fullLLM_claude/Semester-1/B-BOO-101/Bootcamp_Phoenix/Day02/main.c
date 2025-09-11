/*
** EPITECH PROJECT, 2024
** Day02 - Bootcamp Phoenix
** File description:
** main.c - Test file
*/

#include <stdio.h>
#include <string.h>

// Function prototypes
int iterative_factorial(int nb);
int recursive_power(int nb, int p);
int is_prime_number(int nb);
char *my_strcpy(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strstr(char *str, char const *to_find);
char *my_strupcase(char *str);
char *my_strcapitalize(char *str);

void my_putchar(char c) {
    printf("%c", c);
}

int main(void)
{
    char test[100];
    char *result;

    printf("=== Day02 Tests ===\n\n");

    // Test iterative_factorial
    printf("iterative_factorial(5): %d\n", iterative_factorial(5));
    printf("iterative_factorial(0): %d\n", iterative_factorial(0));
    printf("iterative_factorial(-5): %d\n", iterative_factorial(-5));

    // Test recursive_power
    printf("\nrecursive_power(2, 3): %d\n", recursive_power(2, 3));
    printf("recursive_power(5, 0): %d\n", recursive_power(5, 0));
    printf("recursive_power(2, -1): %d\n", recursive_power(2, -1));

    // Test is_prime_number
    printf("\nis_prime_number(7): %d\n", is_prime_number(7));
    printf("is_prime_number(4): %d\n", is_prime_number(4));
    printf("is_prime_number(1): %d\n", is_prime_number(1));

    // Test my_strcpy
    strcpy(test, "original");
    my_strcpy(test, "hello");
    printf("\nmy_strcpy result: %s\n", test);

    // Test my_strncmp
    printf("my_strncmp(\"hello\", \"hello\", 5): %d\n", my_strncmp("hello", "hello", 5));
    printf("my_strncmp(\"hello\", \"world\", 5): %d\n", my_strncmp("hello", "world", 5));

    // Test my_strstr
    result = my_strstr("hello world", "world");
    printf("my_strstr(\"hello world\", \"world\"): %s\n", result ? result : "NULL");

    // Test my_strupcase
    strcpy(test, "hello world");
    my_strupcase(test);
    printf("my_strupcase result: %s\n", test);

    // Test my_strcapitalize
    strcpy(test, "hey, how are you? 42words forty-two; fifty+one");
    my_strcapitalize(test);
    printf("my_strcapitalize result: %s\n", test);

    return 0;
}