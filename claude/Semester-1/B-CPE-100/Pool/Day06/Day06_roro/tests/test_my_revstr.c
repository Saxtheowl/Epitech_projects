#include <criterion/criterion.h>

char *my_revstr(char *str);

Test(my_revstr, reverse_simple_string)
{
    char str[] = "hello";
    my_revstr(str);
    cr_assert_str_eq(str, "olleh");
}

Test(my_revstr, reverse_empty_string)
{
    char str[] = "";
    my_revstr(str);
    cr_assert_str_eq(str, "");
}

Test(my_revstr, reverse_single_char)
{
    char str[] = "a";
    my_revstr(str);
    cr_assert_str_eq(str, "a");
}

Test(my_revstr, reverse_palindrome)
{
    char str[] = "racecar";
    my_revstr(str);
    cr_assert_str_eq(str, "racecar");
}

Test(my_revstr, reverse_even_length)
{
    char str[] = "abcd";
    my_revstr(str);
    cr_assert_str_eq(str, "dcba");
}