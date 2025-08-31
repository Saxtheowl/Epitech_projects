/*
** EPITECH PROJECT, 2025
** Connect4
** File description:
** Main and logic
*/

#include <stdio.h>
#include <string.h>
#include "connect4.h"

#define ROWS 6
#define COLS 7

static int idx(int r, int c)
{
    return r * COLS + c;
}

static int in_bounds(int r, int c)
{
    return r >= 0 && r < ROWS && c >= 0 && c < COLS;
}

static int four_in_a_row(const char *b, int r, int c, int dr, int dc)
{
    char ch;
    int i;

    ch = b[idx(r, c)];
    if (ch != 'R' && ch != 'Y')
        return 0;
    i = 1;
    while (i < 4) {
        r = r + dr;
        c = c + dc;
        if (!in_bounds(r, c) || b[idx(r, c)] != ch)
            return 0;
        i = i + 1;
    }
    return 1;
}

char check_winner(const char *b)
{
    int r;
    int c;

    r = 0;
    while (r < ROWS) {
        c = 0;
        while (c < COLS) {
            if (four_in_a_row(b, r, c, 0, 1))
                return b[idx(r, c)];
            if (four_in_a_row(b, r, c, 1, 0))
                return b[idx(r, c)];
            if (four_in_a_row(b, r, c, 1, 1))
                return b[idx(r, c)];
            if (four_in_a_row(b, r, c, 1, -1))
                return b[idx(r, c)];
            c = c + 1;
        }
        r = r + 1;
    }
    return 0;
}

static int column_valid(const char *b, int c)
{
    int r;
    int seen_empty;

    seen_empty = 0;
    r = ROWS - 1;
    while (r >= 0) {
        if (b[idx(r, c)] == '.')
            seen_empty = 1;
        else if (seen_empty)
            return 0;
        r = r - 1;
    }
    return 1;
}

int validate_board(const char *b)
{
    int r;
    int c;
    int count_r;
    int count_y;
    char w;

    if (strlen(b) != ROWS * COLS)
        return 0;
    count_r = 0;
    count_y = 0;
    r = 0;
    while (r < ROWS) {
        c = 0;
        while (c < COLS) {
            char ch = b[idx(r, c)];
            if (ch == 'R')
                count_r = count_r + 1;
            else if (ch == 'Y')
                count_y = count_y + 1;
            else if (ch != '.')
                return 0;
            c = c + 1;
        }
        r = r + 1;
    }
    if (!(count_r == count_y || count_r == count_y + 1))
        return 0;
    c = 0;
    while (c < COLS) {
        if (!column_valid(b, c))
            return 0;
        c = c + 1;
    }
    w = check_winner(b);
    if (w == 'R' && count_r != count_y + 1)
        return 0;
    if (w == 'Y' && count_r != count_y)
        return 0;
    return 1;
}

int main(int argc, char **argv)
{
    char w;

    if (argc != 2 || !validate_board(argv[1]))
        return 84;
    w = check_winner(argv[1]);
    if (w == 'R' || w == 'Y')
        printf("%c\n", w);
    else
        printf("Draw\n");
    return 0;
}

