/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Main function for MyRunner project
*/

#include "my_runner.h"

int main(int ac, char **av)
{
    game_t game;
    char *map_path = NULL;
    int infinity_mode = 0;
    int result;

    if (parse_arguments(ac, av, &map_path, &infinity_mode) != 0)
        return 84;

    if (map_path == NULL && !infinity_mode)
        return 84;

    srand(time(NULL));

    if (init_game(&game) != 0) {
        fprintf(stderr, "Error: Failed to initialize game\n");
        return 84;
    }

    game.infinity_mode = infinity_mode;

    if (!infinity_mode && load_map(&game, map_path) != 0) {
        cleanup_game(&game);
        return 84;
    }

    result = run_game(&game);
    cleanup_game(&game);

    return result;
}