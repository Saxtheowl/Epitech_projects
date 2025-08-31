/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Main game logic for my_hunter
*/

#include "../include/my_hunter.h"

static void game_loop(game_t *game)
{
    sfVector2i mouse_pos;

    while (sfRenderWindow_isOpen(game->window)) {
        handle_events(game);
        if (game->game_over)
            break;
        update_ducks(game);
        update_hud(game);
        mouse_pos = sfMouse_getPositionRenderWindow(game->window);
        sfSprite_setPosition(game->crosshair, 
            (sfVector2f){mouse_pos.x - 16, mouse_pos.y - 16});
        sfRenderWindow_clear(game->window, sfBlack);
        sfRenderWindow_drawSprite(game->window, game->background, NULL);
        draw_ducks(game);
        draw_hud(game);
        sfRenderWindow_drawSprite(game->window, game->crosshair, NULL);
        sfRenderWindow_display(game->window);
    }
}

int my_hunter(void)
{
    game_t *game;

    srand(time(NULL));
    game = init_game();
    if (!game)
        return 84;
    game_loop(game);
    cleanup_game(game);
    return 0;
}