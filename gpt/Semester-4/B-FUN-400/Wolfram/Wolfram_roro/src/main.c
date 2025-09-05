/*
** EPITECH PROJECT, 2025
** Wolfram_roro
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "wolfram.h"

int main(int ac, char **av)
{
    Config cfg;
    Cells cur;
    Cells nxt;
    int i;

    if (parse_args(ac, av, &cfg) == 84)
        return 84;
    cells_init_single(&cur);
    nxt.pos = NULL; nxt.len = 0; nxt.cap = 0;
    for (i = 0; i < cfg.start; ++i) {
        cells_step(&cur, &nxt, cfg.rule);
        free(cur.pos);
        cur = nxt; nxt.pos = NULL; nxt.len = 0; nxt.cap = 0;
    }
    if (cfg.move != 0 && cur.len > 0) {
        for (i = 0; i < cur.len; ++i)
            cur.pos[i] += cfg.move;
    }
    if (cfg.lines == -1) {
        for (;;) {
            print_window(&cur, cfg.window, 0);
            cells_step(&cur, &nxt, cfg.rule);
            free(cur.pos);
            cur = nxt; nxt.pos = NULL; nxt.len = 0; nxt.cap = 0;
        }
    } else {
        for (i = 0; i < cfg.lines; ++i) {
            print_window(&cur, cfg.window, 0);
            cells_step(&cur, &nxt, cfg.rule);
            free(cur.pos);
            cur = nxt; nxt.pos = NULL; nxt.len = 0; nxt.cap = 0;
        }
    }
    cells_free(&cur);
    cells_free(&nxt);
    return 0;
}

