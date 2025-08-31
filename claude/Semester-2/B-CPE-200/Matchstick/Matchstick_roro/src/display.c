/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** Display functions for the game board
*/

#include "../include/matchstick.h"

void display_line_numbers(int lines)
{
    int i;

    write(1, " ", 1);
    for (i = 1; i <= lines; i++) {
        if (i < 10) {
            write(1, " ", 1);
        }
        printf("%d", i);
        if (i < lines)
            write(1, " ", 1);
    }
    write(1, "\n", 1);
}

static void print_spaces(int count)
{
    int i;

    for (i = 0; i < count; i++)
        write(1, " ", 1);
}

static void display_line(game_t *game, int line_index)
{
    int i;
    int matches_in_line = count_matches_in_line(line_index + 1);
    int spaces = game->lines - line_index - 1;

    print_spaces(spaces);
    write(1, "*", 1);
    
    for (i = 0; i < matches_in_line; i++) {
        if (game->board[line_index][i] == 1) {
            write(1, "|", 1);
        } else {
            write(1, " ", 1);
        }
    }
    
    write(1, "*\n", 2);
}

void display_board(game_t *game)
{
    int i;

    write(1, "\n", 1);
    display_line_numbers(game->lines);
    
    for (i = 0; i < game->lines; i++) {
        display_line(game, i);
    }
}