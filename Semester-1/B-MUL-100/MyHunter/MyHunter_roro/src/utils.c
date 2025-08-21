/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Utility functions
*/

#include "../include/my_hunter.h"

float get_delta_time(sfClock *clock)
{
    sfTime time = sfClock_restart(clock);
    return sfTime_asSeconds(time);
}

void load_high_score(game_t *game)
{
    FILE *file = fopen("high_score.txt", "r");
    
    if (file) {
        fscanf(file, "%d", &game->stats.high_score);
        fclose(file);
    } else {
        game->stats.high_score = 0;
    }
}

void save_high_score(game_t *game)
{
    FILE *file = fopen("high_score.txt", "w");
    
    if (file) {
        fprintf(file, "%d", game->stats.high_score);
        fclose(file);
    }
}

void game_cleanup(game_t *game)
{
    if (game->window)
        sfRenderWindow_destroy(game->window);
    
    if (game->duck_texture)
        sfTexture_destroy(game->duck_texture);
    if (game->background_texture)
        sfTexture_destroy(game->background_texture);
    if (game->crosshair_texture)
        sfTexture_destroy(game->crosshair_texture);
    
    if (game->duck_sprite)
        sfSprite_destroy(game->duck_sprite);
    if (game->background_sprite)
        sfSprite_destroy(game->background_sprite);
    if (game->crosshair_sprite)
        sfSprite_destroy(game->crosshair_sprite);
    
    if (game->font)
        sfFont_destroy(game->font);
    if (game->score_text)
        sfText_destroy(game->score_text);
    if (game->lives_text)
        sfText_destroy(game->lives_text);
    
    if (game->game_clock)
        sfClock_destroy(game->game_clock);
    if (game->spawn_clock)
        sfClock_destroy(game->spawn_clock);
}