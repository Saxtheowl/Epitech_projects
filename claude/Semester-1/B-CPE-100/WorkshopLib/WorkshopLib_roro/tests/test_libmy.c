/*
** EPITECH PROJECT, 2024
** test_libmy.c  
** File description:
** Unit tests for libmy library
*/

#include "../include/my.h"

static int test_count = 0;
static int test_passed = 0;

void assert_eq(int actual, int expected, const char *test_name)
{
    test_count++;
    if (actual == expected) {
        test_passed++;
        my_putstr("[PASS] ");
    } else {
        my_putstr("[FAIL] ");
    }
    my_putstr(test_name);
    my_putstr(" - Expected: ");
    my_put_nbr(expected);
    my_putstr(", Got: ");
    my_put_nbr(actual);
    my_putchar('\n');
}

void assert_str_eq(char *actual, char *expected, const char *test_name)
{
    test_count++;
    if (my_strcmp(actual, expected) == 0) {
        test_passed++;
        my_putstr("[PASS] ");
    } else {
        my_putstr("[FAIL] ");
    }
    my_putstr(test_name);
    my_putstr(" - Expected: '");
    my_putstr(expected);
    my_putstr("', Got: '");
    my_putstr(actual);
    my_putstr("'\n");
}

void test_my_strlen(void)
{
    my_putstr("\n=== Testing my_strlen ===\n");
    assert_eq(my_strlen("hello"), 5, "my_strlen(\"hello\")");
    assert_eq(my_strlen(""), 0, "my_strlen(\"\")");
    assert_eq(my_strlen("a"), 1, "my_strlen(\"a\")");
}

void test_my_strcmp(void)
{
    my_putstr("\n=== Testing my_strcmp ===\n");
    assert_eq(my_strcmp("abc", "abc"), 0, "my_strcmp(\"abc\", \"abc\")");
    assert_eq(my_strcmp("abc", "def") < 0 ? 1 : 0, 1, "my_strcmp(\"abc\", \"def\") < 0");
    assert_eq(my_strcmp("def", "abc") > 0 ? 1 : 0, 1, "my_strcmp(\"def\", \"abc\") > 0");
}

void test_my_is_prime(void)
{
    my_putstr("\n=== Testing my_is_prime ===\n");
    assert_eq(my_is_prime(2), 1, "my_is_prime(2)");
    assert_eq(my_is_prime(7), 1, "my_is_prime(7)");
    assert_eq(my_is_prime(11), 1, "my_is_prime(11)");
    assert_eq(my_is_prime(4), 0, "my_is_prime(4)");
    assert_eq(my_is_prime(9), 0, "my_is_prime(9)");
    assert_eq(my_is_prime(1), 0, "my_is_prime(1)");
    assert_eq(my_is_prime(0), 0, "my_is_prime(0)");
}

void test_my_compute_power_rec(void)
{
    my_putstr("\n=== Testing my_compute_power_rec ===\n");
    assert_eq(my_compute_power_rec(2, 3), 8, "my_compute_power_rec(2, 3)");
    assert_eq(my_compute_power_rec(5, 2), 25, "my_compute_power_rec(5, 2)");
    assert_eq(my_compute_power_rec(10, 0), 1, "my_compute_power_rec(10, 0)");
    assert_eq(my_compute_power_rec(0, 5), 0, "my_compute_power_rec(0, 5)");
}

void test_my_sort_int_array(void)
{
    my_putstr("\n=== Testing my_sort_int_array ===\n");
    int tab[] = {5, 2, 8, 1, 9};
    int expected[] = {1, 2, 5, 8, 9};
    int all_correct = 1;
    
    my_sort_int_array(tab, 5);
    for (int i = 0; i < 5; i++) {
        if (tab[i] != expected[i]) {
            all_correct = 0;
            break;
        }
    }
    assert_eq(all_correct, 1, "my_sort_int_array sorting");
}

void test_my_strupcase(void)
{
    my_putstr("\n=== Testing my_strupcase ===\n");
    char str1[] = "hello";
    char *result1 = my_strupcase(str1);
    assert_str_eq(result1, "HELLO", "my_strupcase(\"hello\")");
    
    char str2[] = "Hello World!";
    char *result2 = my_strupcase(str2);
    assert_str_eq(result2, "HELLO WORLD!", "my_strupcase(\"Hello World!\")");
}

void test_my_getnbr(void)
{
    my_putstr("\n=== Testing my_getnbr ===\n");
    assert_eq(my_getnbr("123"), 123, "my_getnbr(\"123\")");
    assert_eq(my_getnbr("-456"), -456, "my_getnbr(\"-456\")");
    assert_eq(my_getnbr("0"), 0, "my_getnbr(\"0\")");
    assert_eq(my_getnbr("42abc"), 42, "my_getnbr(\"42abc\")");
}

int main(void)
{
    my_putstr("=== LIBMY UNIT TESTS ===\n");
    
    test_my_strlen();
    test_my_strcmp(); 
    test_my_is_prime();
    test_my_compute_power_rec();
    test_my_sort_int_array();
    test_my_strupcase();
    test_my_getnbr();
    
    my_putstr("\n=== TEST SUMMARY ===\n");
    my_putstr("Tests passed: ");
    my_put_nbr(test_passed);
    my_putstr("/");
    my_put_nbr(test_count);
    my_putchar('\n');
    
    if (test_passed == test_count) {
        my_putstr("ALL TESTS PASSED!\n");
        return 0;
    } else {
        my_putstr("SOME TESTS FAILED!\n");
        return 1;
    }
}