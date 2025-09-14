/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Window management functions for MyRunner project
*/

#include "my_runner.h"

int create_window(game_t *game)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    
    game->window = sfRenderWindow_create(mode, WINDOW_TITLE, sfResize | sfClose, NULL);
    if (!game->window)
        return -1;
        
    sfRenderWindow_setFramerateLimit(game->window, 60);
    
    return 0;
}

void handle_events(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        switch (game->event.type) {
            case sfEvtClosed:
                sfRenderWindow_close(game->window);
                break;
            case sfEvtKeyPressed:
                switch (game->event.key.code) {
                    case sfKeyEscape:
                        sfRenderWindow_close(game->window);
                        break;
                    case sfKeySpace:
                        if (!game->game_over)
                            player_jump(game);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void render_game(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    
    // Draw parallax background
    draw_parallax(game);
    
    // Draw map
    draw_map(game);
    
    // Draw player
    if (!game->game_over)
        draw_player(game);
    
    // Draw enemies
    draw_enemies(game);
    
    // Draw UI elements
    sfVector2f score_pos = {20, 20};
    sfText_setPosition(game->score_text, score_pos);
    sfRenderWindow_drawText(game->window, game->score_text, NULL);
    
    // Draw game over text if needed
    if (game->game_over) {
        sfVector2f game_over_pos = {
            WINDOW_WIDTH / 2 - 150,
            WINDOW_HEIGHT / 2 - 50
        };
        sfText_setPosition(game->game_over_text, game_over_pos);
        sfRenderWindow_drawText(game->window, game->game_over_text, NULL);
        
        sfVector2f final_score_pos = {
            WINDOW_WIDTH / 2 - 100,
            WINDOW_HEIGHT / 2 + 20
        };
        sfText_setPosition(game->score_text, final_score_pos);
        sfRenderWindow_drawText(game->window, game->score_text, NULL);
    }
    
    sfRenderWindow_display(game->window);
}