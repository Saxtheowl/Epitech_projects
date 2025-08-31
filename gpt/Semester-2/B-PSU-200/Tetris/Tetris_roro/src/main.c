/*
** EPITECH PROJECT, 2025
** Tetris
** File description:
** Simple ASCII Tetris loop (minimal)
*/

#include <stdio.h>
#include <string.h>
#include "tetris.h"

static void print_help(void)
{
    puts("Commands: a=left, d=right, s=down, w=rotate, q=quit");
}

int main(void)
{
    board_t *b;
    piece_t p;
    char cmd[32];

    b = board_create(10, 20);
    if (!b)
        return 84;
    piece_init_I(&p);
    print_help();
    while (1) {
        if (!piece_can_place(b, &p))
            break;
        board_print(b, &p);
        if (!fgets(cmd, sizeof(cmd), stdin))
            break;
        if (cmd[0] == 'q')
            break;
        if (cmd[0] == 'a') {
            piece_t t = p;
            piece_move(&t, -1, 0);
            if (piece_can_place(b, &t))
                p = t;
        } else if (cmd[0] == 'd') {
            piece_t t = p;
            piece_move(&t, +1, 0);
            if (piece_can_place(b, &t))
                p = t;
        } else if (cmd[0] == 'w') {
            piece_t t = p;
            piece_rotate(&t);
            if (piece_can_place(b, &t))
                p = t;
        } else if (cmd[0] == 's') {
            piece_t t = p;
            piece_move(&t, 0, +1);
            if (piece_can_place(b, &t))
                p = t;
            else {
                board_solidify(b, &p);
                board_clear_lines(b);
                piece_init_I(&p);
            }
        }
    }
    board_destroy(b);
    return 0;
}

