/*
** EPITECH PROJECT, 2025
** Minishell2
** File description:
** Integration tests for conditionals and pipelines
*/

#include <criterion/criterion.h>
#include "mysh2.h"

Test(exec, conditionals_true_false)
{
    char *fake_env[] = {"PATH=/bin:/usr/bin", NULL};
    env_t *e = env_create(fake_env);
    int code;

    code = run_line(e, "/bin/true && /bin/false");
    cr_assert_eq(code, 1);

    code = run_line(e, "/bin/false || /bin/true");
    cr_assert_eq(code, 0);

    env_destroy(e);
}

Test(exec, pipeline_simple)
{
    char *fake_env[] = {"PATH=/bin:/usr/bin", NULL};
    env_t *e = env_create(fake_env);
    int code = run_line(e, "/bin/echo hi | /bin/grep h");
    cr_assert_eq(code, 0);
    env_destroy(e);
}

