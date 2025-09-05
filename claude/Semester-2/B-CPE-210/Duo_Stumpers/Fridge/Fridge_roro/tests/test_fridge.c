/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** test_fridge
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "fridge.h"

Test(fridge, init_fridge_test)
{
    fridge_t fridge;
    
    init_fridge(&fridge);
    cr_assert_eq(fridge.count, MAX_INGREDIENTS);
    cr_assert_str_eq(fridge.ingredients[0].name, "tomato");
    cr_assert_eq(fridge.ingredients[0].quantity, 0);
}

Test(fridge, find_ingredient_test)
{
    fridge_t fridge;
    
    init_fridge(&fridge);
    cr_assert_eq(find_ingredient(&fridge, "tomato"), 0);
    cr_assert_eq(find_ingredient(&fridge, "cheese"), 7);
    cr_assert_eq(find_ingredient(&fridge, "unknown"), -1);
}

Test(fridge, add_to_fridge_test)
{
    fridge_t fridge;
    
    init_fridge(&fridge);
    cr_assert_eq(add_to_fridge(&fridge, "tomato", 5), 0);
    cr_assert_eq(fridge.ingredients[0].quantity, 5);
    cr_assert_eq(add_to_fridge(&fridge, "unknown", 1), 1);
}

Test(fridge, utils_my_strlen)
{
    cr_assert_eq(my_strlen("hello"), 5);
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen(NULL), 0);
}

Test(fridge, utils_my_atoi)
{
    cr_assert_eq(my_atoi("123"), 123);
    cr_assert_eq(my_atoi("0"), 0);
    cr_assert_eq(my_atoi("-5"), -5);
}