/*
** EPITECH PROJECT, 2025
** Minishell2
** File description:
** Split tests
*/

#include <criterion/criterion.h>
#include "mysh2.h"

Test(split, words_and_commands)
{
    char **cmds = split_commands("ls -l; echo hi");
    cr_assert_not_null(cmds);
    cr_assert_str_eq(cmds[0], "ls -l");
    cr_assert_str_eq(cmds[1], " echo hi");
    cr_assert_null(cmds[2]);
}

Test(split, pipeline)
{
    char **segs = split_pipeline("ls -l | grep .c | wc -l");
    cr_assert_not_null(segs);
    cr_assert_str_eq(segs[0], "ls -l ");
    cr_assert_str_eq(segs[1], " grep .c ");
    cr_assert_str_eq(segs[2], " wc -l");
    cr_assert_null(segs[3]);
}
