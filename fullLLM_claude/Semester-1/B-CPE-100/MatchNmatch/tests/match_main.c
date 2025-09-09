#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int match(char const *s1, char const *s2);

void test_match_case(char const *s1, char const *s2, int expected)
{
    int result = match(s1, s2);
    my_putstr("match(\"");
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
    my_putstr("=== MATCH TESTS ===\n");
    
    test_match_case("main.c", "*.c", 1);
    test_match_case("main.c", "main.*", 1);
    test_match_case("main.c", "*.*", 1);
    test_match_case("main.c", "test.c", 0);
    test_match_case("abc", "a*c", 1);
    test_match_case("abc", "a*b*c", 1);
    test_match_case("abc", "*", 1);
    test_match_case("", "*", 1);
    test_match_case("", "", 1);
    test_match_case("a", "", 0);
    test_match_case("", "a", 0);
    
    return 0;
}