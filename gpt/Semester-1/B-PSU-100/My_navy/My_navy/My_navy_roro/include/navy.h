/*
** EPITECH PROJECT, 2025
** My_navy_roro
** File description:
** Prototypes for navy
*/

#ifndef NAVY_H
    #define NAVY_H

    #include <sys/types.h>

    #define ERR_CODE 84

    typedef struct board_s {
        char cells[8][8];
    } board_t;

    typedef struct game_s {
        pid_t self_pid;
        pid_t enemy_pid;
        board_t my;
        board_t enemy;
        int is_player2;
        int my_hits;
        int enemy_hits;
    } game_t;

    #define TOTAL_SHIP_CELLS 14

    int load_map(const char *path, board_t *b);
    void print_boards(const game_t *g);
    int run_game(game_t *g);
    int start_connection(game_t *g, const char *pid_arg);

#endif /* NAVY_H */
