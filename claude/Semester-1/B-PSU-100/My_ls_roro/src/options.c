/*
** EPITECH PROJECT, 2024
** My_ls
** File description:
** Command line options parsing for my_ls
*/

#include "../include/my_ls.h"

static int is_option(char c)
{
    return (c == 'a' || c == 'l' || c == 'R' || c == 'd' ||
            c == 'r' || c == 't');
}

static int parse_option_string(char *str, options_t *opts)
{
    int i = 1;

    while (str[i]) {
        if (!is_option(str[i]))
            return -1;
        if (str[i] == 'a')
            opts->a_flag = 1;
        if (str[i] == 'l')
            opts->l_flag = 1;
        if (str[i] == 'R')
            opts->R_flag = 1;
        if (str[i] == 'd')
            opts->d_flag = 1;
        if (str[i] == 'r')
            opts->r_flag = 1;
        if (str[i] == 't')
            opts->t_flag = 1;
        i++;
    }
    return 0;
}

int parse_options(int argc, char **argv, options_t *opts)
{
    int i = 1;

    while (i < argc && argv[i][0] == '-' && argv[i][1]) {
        if (parse_option_string(argv[i], opts) == -1)
            return -1;
        i++;
    }
    return i;
}