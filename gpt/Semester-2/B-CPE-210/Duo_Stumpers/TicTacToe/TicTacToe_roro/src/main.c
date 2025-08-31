/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** Main and logic
*/

#include <stdio.h>
#include <string.h>
#include "tictactoe.h"

static int line_winner(const char *b, int a, int d)
{
    char c;

    c = b[a];
    if (c != 'X' && c != 'O')
        return 0;
    if (b[a + d] == c && b[a + 2 * d] == c)
        return c;
    return 0;
}

int check_winner(const char *b)
{
    int i;
    int w;

    i = 0;
    while (i < 3) {
        w = line_winner(b, i * 3, 1);
        if (w)
            return w;
        w = line_winner(b, i, 3);
        if (w)
            return w;
        i = i + 1;
    }
    w = line_winner(b, 0, 4);
    if (w)
        return w;
    w = line_winner(b, 2, 2);
    if (w)
        return w;
    return 0;
}

int validate_board(const char *b)
{
    int x;
    int o;
    int i;
    int wx;
    int wo;

    if (strlen(b) != 9)
        return 0;
    x = 0;
    o = 0;
    i = 0;
    while (i < 9) {
        if (b[i] == 'X')
            x = x + 1;
        else if (b[i] == 'O')
            o = o + 1;
        else if (b[i] != '.')
            return 0;
        i = i + 1;
    }
    if (!(x == o || x == o + 1))
        return 0;
    wx = 0;
    wo = 0;
    i = 0;
    while (i < 3) {
        if (line_winner(b, i * 3, 1) == 'X')
            wx = 1;
        if (line_winner(b, i, 3) == 'X')
            wx = 1;
        if (line_winner(b, i * 3, 1) == 'O')
            wo = 1;
        if (line_winner(b, i, 3) == 'O')
            wo = 1;
        i = i + 1;
    }
    if (line_winner(b, 0, 4) == 'X' || line_winner(b, 2, 2) == 'X')
        wx = 1;
    if (line_winner(b, 0, 4) == 'O' || line_winner(b, 2, 2) == 'O')
        wo = 1;
    if (wx && wo)
        return 0;
    if (wx && x != o + 1)
        return 0;
    if (wo && x != o)
        return 0;
    return 1;
}

int main(int argc, char **argv)
{
    char w;

    if (argc != 2 || !validate_board(argv[1]))
        return 84;
    w = (char)check_winner(argv[1]);
    if (w == 'X' || w == 'O')
        printf("%c\n", w);
    else
        printf("Draw\n");
    return 0;
}

