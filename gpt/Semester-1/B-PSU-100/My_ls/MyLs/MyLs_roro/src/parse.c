/*
** EPITECH PROJECT, 2025
** MyLs_roro
** File description:
** Parse flags
*/

#include <string.h>
#include "my_ls.h"

static void init_flags(flags_t *f)
{
    f->a = 0;
    f->l = 0;
    f->r = 0;
    f->t = 0;
    f->d = 0;
    f->R = 0;
}

static int parse_group(const char *s, flags_t *f)
{
    int i;

    for (i = 1; s[i]; ++i) {
        if (s[i] == 'a') f->a = 1;
        else if (s[i] == 'l') f->l = 1;
        else if (s[i] == 'r') f->r = 1;
        else if (s[i] == 't') f->t = 1;
        else if (s[i] == 'd') f->d = 1;
        else if (s[i] == 'R') f->R = 1;
        else return -1;
    }
    return 0;
}

int parse_flags(int ac, char **av, int *idx, flags_t *f)
{
    int i;

    init_flags(f);
    for (i = 1; i < ac; ++i) {
        if (av[i][0] != '-')
            break;
        if (av[i][1] == '\0')
            break;
        if (parse_group(av[i], f) != 0)
            return -1;
    }
    *idx = i;
    return 0;
}
