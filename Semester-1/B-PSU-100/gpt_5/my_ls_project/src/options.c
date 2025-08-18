/*
** EPITECH PROJECT, 2025
** MY_LS
** File description:
** Epitech-style source file for my_ls project
*/
#include "my_ls.h"
#include <unistd.h>

static int set_flag(options_t *o, char c)
{
    if (c == 'a') o->a_opt = 1;
    else if (c == 'l') o->l_opt = 1;
    else if (c == 'R') o->R_opt = 1;
    else if (c == 'd') o->d_opt = 1;
    else if (c == 'r') o->r_opt = 1;
    else if (c == 't') o->t_opt = 1;
    else
        return -1;
    return 0;
}

int parse_options(int argc, char **argv, options_t *opts, int *first_path)
{
    int i = 1;
    int j = 1;

    opts->a_opt = 0;
    opts->l_opt = 0;
    opts->R_opt = 0;
    opts->d_opt = 0;
    opts->r_opt = 0;
    opts->t_opt = 0;
    while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0') {
        j = 1;
        while (argv[i][j] != '\0') {
            if (set_flag(opts, argv[i][j]) < 0)
                return -1;
            j++;
        }
        i++;
    }
    *first_path = i;
    return 0;
}
