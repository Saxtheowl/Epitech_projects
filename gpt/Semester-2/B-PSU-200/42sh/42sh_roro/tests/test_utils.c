/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Utils tests
*/

#include <criterion/criterion.h>
#include "sh.h"

Test(utils, split_pipeline)
{
    char **segs = split_pipeline("echo hi | wc -c | cat");
    cr_assert_not_null(segs);
    cr_assert_str_eq(segs[0], "echo hi ");
    cr_assert_str_eq(segs[1], " wc -c ");
    cr_assert_str_eq(segs[2], " cat");
    cr_assert_null(segs[3]);
    free_words(segs);
}

Test(utils, expand_vars)
{
    char *fake_env[] = {"USER=roro", NULL};
    env_t *e = env_create(fake_env);
    char *s = expand_vars(e, "hello $USER");
    cr_assert_str_eq(s, "hello roro");
    free(s);
    env_destroy(e);
}

