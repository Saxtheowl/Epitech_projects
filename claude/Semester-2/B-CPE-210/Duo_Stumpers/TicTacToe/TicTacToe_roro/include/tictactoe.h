/*
** EPITECH PROJECT, 2025
** TicTacToe
** File description:
** tictactoe
*/

#ifndef TICTACTOE_H_
    #define TICTACTOE_H_

    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct game_s {
        char **grid;
        int size;
        char player1_char;
        char player2_char;
        int current_player;
    } game_t;

    typedef struct args_s {
        char player1_char;
        char player2_char;
        int grid_size;
    } args_t;

    int tictactoe(int argc, char **argv);
    int parse_arguments(int argc, char **argv, args_t *args);
    game_t *init_game(args_t *args);
    void display_grid(game_t *game);
    int get_player_move(game_t *game, int *x, int *y);
    int make_move(game_t *game, int x, int y);
    int check_win(game_t *game);
    int is_grid_full(game_t *game);
    void free_game(game_t *game);
    int my_atoi(char *str);
    int my_strlen(char *str);

#endif /* !TICTACTOE_H_ */