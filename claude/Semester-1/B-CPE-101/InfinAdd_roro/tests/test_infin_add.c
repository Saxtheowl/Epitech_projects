/*
** EPITECH PROJECT, 2024
** test_infin_add.c
** File description:
** Unit tests for infinite addition
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/infin_add.h"

static int test_passed = 0;
static int test_total = 0;

static void test_case(char const *nb1, char const *nb2, char const *expected)
{
    char *result = infin_add(nb1, nb2);
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
        printf("PASS: %s + %s = %s\n", nb1, nb2, result);
        test_passed++;
    } else {
        printf("FAIL: %s + %s = %s (expected %s)\n", nb1, nb2, result, expected);
    }
    if (result)
        free(result);
}

int main(void)
{
    printf("Running infinite addition tests...\n");
    test_case("123", "456", "579");
    test_case("-876435", "987143265", "986266830");
    test_case("-807965", "-34532", "-842497");
    test_case("0", "0", "0");
    test_case("999", "1", "1000");
    test_case("-999", "999", "0");
    test_case("123456789", "987654321", "1111111110");
    printf("\nResults: %d/%d tests passed\n", test_passed, test_total);
    return (test_passed == test_total) ? 0 : 1;
}