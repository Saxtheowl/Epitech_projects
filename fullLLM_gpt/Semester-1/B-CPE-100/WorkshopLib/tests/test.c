#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "my.h"

static void test_strlen(void)
{
    assert(my_strlen("hello") == 5);
    assert(my_strlen("") == 0);
    assert(my_strlen(NULL) == 0);
}

static void test_isneg(void)
{
    assert(my_isneg(-1) == 1);
    assert(my_isneg(0) == 0);
    assert(my_isneg(42) == 0);
}

static void test_swap_sort(void)
{
    int a = 3;
    int b = 1;
    my_swap(&a, &b);
    assert(a == 1 && b == 3);
    int tab[5] = {4, 1, 3, 2, 0};
    my_sort_int_array(tab, 5);
    int expected[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; ++i)
        assert(tab[i] == expected[i]);
}

static void test_power_sqrt_prime(void)
{
    assert(my_compute_power_rec(2, 0) == 1);
    assert(my_compute_power_rec(2, 10) == 1024);
    assert(my_compute_power_rec(2, -1) == 0);
    assert(my_compute_square_root(16) == 4);
    assert(my_compute_square_root(17) == 0);
    assert(my_is_prime(2) == 1);
    assert(my_is_prime(15) == 0);
    assert(my_find_prime_sup(14) == 17);
}

static void test_strings_copy(void)
{
    char buffer[32];
    my_strcpy(buffer, "test");
    assert(strcmp(buffer, "test") == 0);
    my_strncpy(buffer, "abcdef", 3);
    buffer[3] = '\0';
    assert(strcmp(buffer, "abc") == 0);
    char rev[] = "abcde";
    assert(strcmp(my_revstr(rev), "edcba") == 0);
    char str[] = "hello world";
    assert(my_strstr(str, "world") == str + 6);
    assert(my_strstr(str, "xyz") == NULL);
    assert(my_strcmp("abc", "abd") < 0);
    assert(my_strncmp("abcdef", "abcxyz", 3) == 0);
}

static void test_case_helpers(void)
{
    char up[] = "abcD";
    assert(strcmp(my_strupcase(up), "ABCD") == 0);
    char low[] = "ABcd";
    assert(strcmp(my_strlowcase(low), "abcd") == 0);
    char cap[] = "hello, world! 42TEST";
    assert(strcmp(my_strcapitalize(cap), "Hello, World! 42test") == 0);
}

static void test_classification(void)
{
    assert(my_str_isalpha("AbCd") == 1);
    assert(my_str_isalpha("abc123") == 0);
    assert(my_str_isnum("123") == 1);
    assert(my_str_isnum("12a3") == 0);
    assert(my_str_islower("abc") == 1);
    assert(my_str_islower("abC") == 0);
    assert(my_str_isupper("ABC") == 1);
    assert(my_str_isupper("ABc") == 0);
    assert(my_str_isprintable("Hello") == 1);
    assert(my_str_isprintable("He\x01") == 0);
}

static void test_getnbr(void)
{
    assert(my_getnbr("42") == 42);
    assert(my_getnbr("   -42abc") == -42);
    assert(my_getnbr("2147483647") == 2147483647);
    assert(my_getnbr("-2147483648") == -2147483648);
    assert(my_getnbr("999999999999999") == 0);
}

static void test_concat(void)
{
    char dest[32] = "Hello";
    my_strcat(dest, " World");
    assert(strcmp(dest, "Hello World") == 0);
    my_strncat(dest, "!!!", 2);
    assert(strcmp(dest, "Hello World!!") == 0);
}

static void test_outputs(void)
{
    my_putstr("Test");
    my_putchar('\n');
    my_put_nbr(-12345);
    my_putchar('\n');
    my_showstr("Hi\n");
    my_putchar('\n');
    my_showmem("Hello, World!", 13);
}

int main(void)
{
    test_strlen();
    test_isneg();
    test_swap_sort();
    test_power_sqrt_prime();
    test_strings_copy();
    test_case_helpers();
    test_classification();
    test_getnbr();
    test_concat();
    test_outputs();
    return 0;
}
