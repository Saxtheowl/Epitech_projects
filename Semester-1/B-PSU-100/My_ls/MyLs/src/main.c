/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Entry point and high-level flow.
*/
#include "my_ls.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

static void init_opts(options_t *o)
{
    o->opt_a = false;
    o->opt_l = false;
    o->opt_R = false;
    o->opt_d = false;
    o->opt_r = false;
    o->opt_t = false;
}

int main(int ac, char **av)
{
    options_t opts;
    int first_path = 0;
    int ret;

    init_opts(&opts);
    ret = parse_options(ac, av, &opts, &first_path);
    if (ret != 0) {
        return 84;
    }
    if (list_paths(ac, av, first_path, &opts) != 0) {
        return 84;
    }
    return 0;
}
