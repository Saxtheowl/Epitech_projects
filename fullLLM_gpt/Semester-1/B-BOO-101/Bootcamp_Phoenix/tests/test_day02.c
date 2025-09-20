#include "framework.h"
#include "phoenix.h"

Test(iterative_factorial, handles_negative)
{
    cr_assert_eq(iterative_factorial(-3), 0);
}

Test(iterative_factorial, computes_factorial)
{
    cr_assert_eq(iterative_factorial(5), 120);
}

Test(recursive_power, handles_zero_power)
{
    cr_assert_eq(recursive_power(3, 0), 1);
}

Test(recursive_power, handles_negative_power)
{
    cr_assert_eq(recursive_power(3, -1), 0);
}

Test(is_prime_number, identifies_primes)
{
    cr_assert_eq(is_prime_number(29), 1);
    cr_assert_eq(is_prime_number(1), 0);
    cr_assert_eq(is_prime_number(25), 0);
}

Test(my_strcpy, copies_basic_string)
{
    char destination[16];

    my_strcpy(destination, "Hello");
    cr_assert_str_eq(destination, "Hello");
}

Test(my_strcpy, handles_null_destination)
{
    cr_assert_null(my_strcpy(NULL, "data"));
}

Test(my_strcpy, handles_null_source)
{
    char destination[16] = {0};

    cr_assert_eq(my_strcpy(destination, NULL), destination);
    cr_assert_eq(destination[0], '\0');
}

Test(my_strncmp, handles_zero_length)
{
    cr_assert_eq(my_strncmp("abcd", "abce", 0), 0);
}

Test(my_strncmp, detects_null_inputs)
{
    cr_assert_lt(my_strncmp(NULL, "abc", 3), 0);
    cr_assert_gt(my_strncmp("abc", NULL, 3), 0);
}

Test(my_strncmp, detects_difference)
{
    cr_assert_lt(my_strncmp("abc", "abd", 3), 0);
}

Test(my_strncmp, considers_length_limit)
{
    cr_assert_eq(my_strncmp("abcdef", "abcxyz", 3), 0);
}

Test(my_strncmp, compares_full_strings)
{
    cr_assert_gt(my_strncmp("abd", "abc", 4), 0);
}

Test(my_strstr, finds_substring)
{
    char sample[] = "The quick brown fox";

    cr_assert_str_eq(my_strstr(sample, "quick"), sample + 4);
    cr_assert_null(my_strstr(sample, "wolf"));
}

Test(my_strupcase, converts_letters)
{
    char buffer[] = "Mixed123";

    cr_assert_str_eq(my_strupcase(buffer), "MIXED123");
}

Test(my_strcapitalize, capitalizes_words)
{
    char buffer[] = "hey, how are you? 42WORds forty-two; fifty+one";

    cr_assert_str_eq(my_strcapitalize(buffer), "Hey, How Are You? 42words Forty-Two; Fifty+One");
}
