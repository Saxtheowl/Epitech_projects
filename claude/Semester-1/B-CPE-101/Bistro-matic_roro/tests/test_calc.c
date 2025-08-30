/*
** EPITECH PROJECT, 2024
** test_calc.c
** File description:
** Unit tests for bistromatic calculator
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/bistromatic.h"

static int test_passed = 0;
static int test_total = 0;

static void test_eval(char const *base, char const *ops, char const *expr,
    char const *expected)
{
    char *result = eval_expr(base, ops, expr, my_strlen(expr));
    int len_result = my_strlen(result);
    int len_expected = my_strlen(expected);
    int i = 0;
    int match = 1;

    test_total++;
    if (len_result != len_expected) {
        match = 0;
    } else {
        while (i < len_result) {
            if (result[i] != expected[i]) {
                match = 0;
                break;
            }
            i++;
        }
    }
    if (match) {
        printf("PASS: %s = %s\n", expr, result);
        test_passed++;
    } else {
        printf("FAIL: %s = %s (expected %s)\n", expr, result, expected);
    }
    if (result)
        free(result);
}

int main(void)
{
    printf("Running bistromatic calculator tests...\n");
    test_eval("0123456789", "()+-*/%", "3+6", "9");
    test_eval("0123456789", "{}vwxyz", "3v6", "9");
    test_eval("0123456789", "()+-*/%", "2*3", "6");
    test_eval("0123456789", "()+-*/%", "(2+3)*4", "20");
    test_eval("0123456789", "()+-*/%", "10-5", "5");
    test_eval("0123456789", "()+-*/%", "8/2", "4");
    test_eval("0123456789", "()+-*/%", "7%3", "1");
    printf("\nResults: %d/%d tests passed\n", test_passed, test_total);
    return (test_passed == test_total) ? 0 : 1;
}