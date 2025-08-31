/*
** EPITECH PROJECT, 2024
** Tetris
** File description:
** Main entry point for ncurses-based Tetris game
*/

#include "../include/tetris.h"

int main(int argc, char **argv)
{
    game_t game = {0};

    srand(time(NULL));
    
    init_default_config(&game.config);
    
    if (parse_arguments(argc, argv, &game.config) != 0) {
        return 84;
    }

    if (load_tetriminos(&game) != 0) {
        print_error("Failed to load tetriminos");
        cleanup_game(&game);
        return 84;
    }

    if (game.config.debug_mode) {
        debug_mode(&game);
        getchar();
    }

    init_ncurses();
    
    if (check_terminal_size(&game) != 0) {
        cleanup_ncurses();
        cleanup_game(&game);
        print_error("Terminal too small. Please enlarge your terminal.");
        return 84;
    }

    init_game_state(&game);
    
    if (spawn_new_piece(&game) != 0) {
        cleanup_ncurses();
        cleanup_game(&game);
        return 84;
    }

    game_loop(&game);

    cleanup_ncurses();
    cleanup_game(&game);
    
    return 0;
}