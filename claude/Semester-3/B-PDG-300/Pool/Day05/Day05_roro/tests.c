/*
** EPITECH PROJECT, 2025
** Day05 - String Module
** File description:
** Unit tests for string module
*/

#include <criterion/criterion.h>
#include "string.h"

Test(string_init, basic_init)
{
    string_t s;
    
    string_init(&s, "Hello World");
    cr_assert_str_eq(s.str, "Hello World");
    string_destroy(&s);
}

Test(string_init, empty_string)
{
    string_t s;
    
    string_init(&s, "");
    cr_assert_str_eq(s.str, "");
    string_destroy(&s);
}

Test(string_init, null_pointer)
{
    string_t s;
    
    string_init(&s, NULL);
    cr_assert_null(s.str);
}

Test(string_init, null_this)
{
    string_init(NULL, "test");
    /* Should not crash */
}

Test(string_destroy, basic_destroy)
{
    string_t s;
    
    string_init(&s, "Test");
    string_destroy(&s);
    cr_assert_null(s.str);
}

Test(string_destroy, null_this)
{
    string_destroy(NULL);
    /* Should not crash */
}