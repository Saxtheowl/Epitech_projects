/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Env tests
*/

#include <criterion/criterion.h>
#include "sh.h"

Test(env, set_get_unset)
{
    char *fake_env[] = {"PATH=/bin", NULL};
    env_t *e = env_create(fake_env);

    cr_assert_not_null(e);
    cr_assert_str_eq(env_get(e, "PATH"), "/bin");
    cr_assert(env_set(e, "FOO", "bar"));
    cr_assert_str_eq(env_get(e, "FOO"), "bar");
    cr_assert(env_unset(e, "FOO"));
    cr_assert_null(env_get(e, "FOO"));
    env_destroy(e);
}

