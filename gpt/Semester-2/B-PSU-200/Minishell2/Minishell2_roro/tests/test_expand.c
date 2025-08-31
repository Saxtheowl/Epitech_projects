/*
** EPITECH PROJECT, 2025
** Minishell2
** File description:
** Tests for variable expansion and redirection filtering
*/

#include <criterion/criterion.h>
#include "mysh2.h"

Test(expand, basic)
{
    char *fake_env[] = {"FOO=bar", "HOME=/home/user", NULL};
    env_t *e = env_create(fake_env);
    char *s = expand_vars(e, "echo $FOO $HOME");
    cr_assert_str_eq(s, "echo bar /home/user");
    free(s);
    env_destroy(e);
}

Test(redir, filter)
{
    char *args_buf[] = {"cat", "<", "in.txt", ">>", "out.txt", NULL};
    char **args = args_buf; /* static buffer ok for test */
    char *in = NULL; char *out = NULL; int app = 0;
    int changed = filter_redirections(args, &in, &out, &app);
    cr_assert(changed);
    cr_assert_str_eq(in, "in.txt");
    cr_assert_str_eq(out, "out.txt");
    cr_assert_eq(app, 1);
    cr_assert_str_eq(args[0], "cat");
    cr_assert_null(args[1]);
}

