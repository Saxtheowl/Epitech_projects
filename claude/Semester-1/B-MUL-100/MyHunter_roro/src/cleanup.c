/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Cleanup and utility functions
*/

#include "../include/my_hunter.h"

void cleanup_game(game_t *game)
{
    int i;

    if (!game)
        return;
    for (i = 0; i < MAX_DUCKS; i++) {
        if (game->ducks[i].sprite)
            sfSprite_destroy(game->ducks[i].sprite);
        if (game->ducks[i].texture)
            sfTexture_destroy(game->ducks[i].texture);
        if (game->ducks[i].anim_clock)
            sfClock_destroy(game->ducks[i].anim_clock);
    }
    if (game->background)
        sfSprite_destroy(game->background);
    if (game->bg_texture)
        sfTexture_destroy(game->bg_texture);
    if (game->crosshair)
        sfSprite_destroy(game->crosshair);
    if (game->crosshair_texture)
        sfTexture_destroy(game->crosshair_texture);
    if (game->score_text)
        sfText_destroy(game->score_text);
    if (game->ammo_text)
        sfText_destroy(game->ammo_text);
    if (game->font)
        sfFont_destroy(game->font);
    if (game->game_clock)
        sfClock_destroy(game->game_clock);
    if (game->window)
        sfRenderWindow_destroy(game->window);
    free(game);
}

sfIntRect create_rect(int left, int top, int width, int height)
{
    sfIntRect rect;

    rect.left = left;
    rect.top = top;
    rect.width = width;
    rect.height = height;
    return rect;
}