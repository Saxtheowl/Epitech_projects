/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Main function for sokoban game
*/

#include "sokoban.h"

static void game_loop(game_t *game, const char *map_file)
{
    int key;

    while (game->is_running) {
        if (check_terminal_size(game->map) == 0) {
            display_resize_message();
            usleep(100000);
            continue;
        }
        
        display_map(game->map);
        key = getch();
        
        switch (key) {
            case KEY_UP:
                move_player(game, 0, -1);
                break;
            case KEY_DOWN:
                move_player(game, 0, 1);
                break;
            case KEY_LEFT:
                move_player(game, -1, 0);
                break;
            case KEY_RIGHT:
                move_player(game, 1, 0);
                break;
            case ' ':
                reset_game(game, map_file);
                break;
            case 'q':
            case 'Q':
                game->is_running = false;
                break;
        }
        
        if (check_win_condition(game->map)) {
            display_map(game->map);
            game->is_running = false;
            game->game_state = WIN_EXIT_CODE;
        } else if (check_lose_condition(game->map)) {
            display_map(game->map);
            game->is_running = false;
            game->game_state = LOSE_EXIT_CODE;
        }
    }
}

int main(int ac, char **av)
{
    game_t *game;
    int exit_code;

    if (ac != 2) {
        print_usage();
        return MY_EXIT_FAILURE;
    }
    
    if (my_strcmp(av[1], "-h") == 0) {
        display_help();
        return MY_EXIT_SUCCESS;
    }
    
    game = init_game(av[1]);
    if (game == NULL)
        return MY_EXIT_FAILURE;
    
    signal(SIGWINCH, handle_resize);
    init_display();
    
    game_loop(game, av[1]);
    
    exit_code = game->game_state;
    cleanup_display();
    free_game(game);
    
    return exit_code;
}