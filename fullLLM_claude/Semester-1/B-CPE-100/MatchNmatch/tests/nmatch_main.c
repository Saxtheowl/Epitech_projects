#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int nmatch(char const *s1, char const *s2);

void test_nmatch_case(char const *s1, char const *s2, int expected)
{
    int result = nmatch(s1, s2);
    my_putstr("nmatch(\"");
    my_putstr((char*)s1);
    my_putstr("\", \"");
    my_putstr((char*)s2);
    my_putstr("\") = ");
    my_put_nbr(result);
    my_putstr(" (expected: ");
    my_put_nbr(expected);
    my_putstr(") ");
    if (result == expected) {
        my_putstr("✓\n");
    } else {
        my_putstr("✗\n");
    }
}

int main(void)
{
    my_putstr("=== NMATCH TESTS ===\n");
    
    test_nmatch_case("abcbd", "*b*", 2);
    test_nmatch_case("abc", "a**", 3);
    test_nmatch_case("main.c", "*.c", 1);
    test_nmatch_case("abc", "*", 1);
    test_nmatch_case("", "*", 1);
    test_nmatch_case("", "", 1);
    test_nmatch_case("a", "", 0);
    test_nmatch_case("", "a", 0);
    test_nmatch_case("aba", "*a*", 2);
    
    return 0;
}