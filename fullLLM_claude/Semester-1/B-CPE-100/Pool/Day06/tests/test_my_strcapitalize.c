/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** test_my_strcapitalize.c
*/

#include <criterion/criterion.h>
#include <string.h>

char *my_strcapitalize(char *str);

Test(my_strcapitalize, simple_sentence)
{
    char str[] = "hello world";
    my_strcapitalize(str);
    cr_assert_str_eq(str, "Hello World");
}

Test(my_strcapitalize, empty_string)
{
    char str[] = "";
    my_strcapitalize(str);
    cr_assert_str_eq(str, "");
}

Test(my_strcapitalize, complex_example)
{
    char str[] = "hey, how are you? 42WORds forty-two; fifty+one";
    my_strcapitalize(str);
    cr_assert_str_eq(str, "Hey, How Are You? 42words Forty-Two; Fifty+One");
}

Test(my_strcapitalize, only_numbers)
{
    char str[] = "123 456";
    my_strcapitalize(str);
    cr_assert_str_eq(str, "123 456");
}

Test(my_strcapitalize, mixed_case)
{
    char str[] = "hELLo WoRLD";
    my_strcapitalize(str);
    cr_assert_str_eq(str, "Hello World");
}

Test(my_strcapitalize, punctuation_separators)
{
    char str[] = "word1,word2;word3.word4";
    my_strcapitalize(str);
    cr_assert_str_eq(str, "Word1,Word2;Word3.Word4");
}