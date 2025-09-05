/*
** EPITECH PROJECT, 2025
** Tree
** File description:
** test_tree
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "tree.h"

Test(tree, parse_options_basic)
{
    char *argv[] = {"tree", "-a", "-d"};
    options_t opts;
    char *path;
    
    int result = parse_options(3, argv, &opts, &path);
    cr_assert_eq(result, 0);
    cr_assert_eq(opts.show_all, 1);
    cr_assert_eq(opts.dirs_only, 1);
}

Test(tree, parse_options_max_depth)
{
    char *argv[] = {"tree", "-L", "2"};
    options_t opts;
    char *path;
    
    int result = parse_options(3, argv, &opts, &path);
    cr_assert_eq(result, 0);
    cr_assert_eq(opts.max_depth, 2);
}

Test(tree, utils_my_strlen)
{
    cr_assert_eq(my_strlen("hello"), 5);
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen(NULL), 0);
}

Test(tree, utils_is_hidden)
{
    cr_assert_eq(is_hidden(".hidden"), 1);
    cr_assert_eq(is_hidden("normal"), 0);
    cr_assert_eq(is_hidden("."), 0);
}