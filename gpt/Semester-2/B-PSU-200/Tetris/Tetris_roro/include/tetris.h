/*
** EPITECH PROJECT, 2025
** Tetris
** File description:
** Prototypes
*/

#ifndef TETRIS_H
    #define TETRIS_H

typedef struct {
    int w;
    int h;
    char *grid;
} board_t;

typedef struct {
    int w;
    int h;
    char data[4][4];
    int x;
    int y;
} piece_t;

board_t *board_create(int w, int h);
void board_destroy(board_t *b);
void board_print(const board_t *b, const piece_t *p);
int board_solidify(board_t *b, const piece_t *p);
int board_clear_lines(board_t *b);

void piece_init_I(piece_t *p);
int piece_can_place(const board_t *b, const piece_t *p);
void piece_move(piece_t *p, int dx, int dy);
void piece_rotate(piece_t *p);

#endif /* TETRIS_H */

