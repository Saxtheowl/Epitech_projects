/*
** EPITECH PROJECT, 2025
** Tetris
** File description:
** Tests for board functions
*/

#include <criterion/criterion.h>
#include "tetris.h"

Test(tetris, place_and_clear)
{
    board_t *b = board_create(4, 4);
    piece_t p;

    piece_init_I(&p);
    p.x = 0; p.y = 0; p.w = 4; p.h = 1;
    cr_assert(piece_can_place(b, &p));
    board_solidify(b, &p);
    cr_assert_eq(board_clear_lines(b), 1);
    board_destroy(b);
}

Test(tetris, rotate_I)
{
    piece_t p;
    piece_init_I(&p);
    cr_assert_eq(p.w, 4);
    cr_assert_eq(p.h, 1);
    piece_rotate(&p);
    cr_assert_eq(p.w, 1);
    cr_assert_eq(p.h, 4);
}
