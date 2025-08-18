/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Parse CLI options according to subject (-a -l -R -d -r -t).
*/
#include "my_ls.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

static void print_usage_error(const char *bad)
{
    my_putstr_fd(2, "my_ls: invalid option -- '");
    my_putstr_fd(2, bad);
    my_putstr_fd(2, "'\n");
}

int parse_options(int ac, char **av, options_t *opts, int *first_path_idx)
{
    int i = 1;

    for (; i < ac; ++i) {
        if (av[i][0] != '-' || av[i][1] == '\0')
            break;
        if (strcmp(av[i], "--") == 0) {
            ++i;
            break;
        }
        for (int j = 1; av[i][j] != '\0'; ++j) {
            char c = av[i][j];
            if (c == 'a') opts->opt_a = true;
            else if (c == 'l') opts->opt_l = true;
            else if (c == 'R') opts->opt_R = true;
            else if (c == 'd') opts->opt_d = true;
            else if (c == 'r') opts->opt_r = true;
            else if (c == 't') opts->opt_t = true;
            else {
                char bad[2] = {c, 0};
                print_usage_error(bad);
                return -1;
            }
        }
    }
    *first_path_idx = i;
    return 0;
}
