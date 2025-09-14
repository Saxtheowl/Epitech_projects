/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Game logic for MyHunter project
*/

#include "my_hunter.h"

int init_game(game_t *game)
{
    if (create_window(game) != 0)
        return 84;

    game->game_clock = sfClock_create();
    if (!game->game_clock)
        return 84;

    game->score = 0;
    game->nb_ducks = 0;

    // Initialize font and score text
    game->font = sfFont_createFromFile("assets/arial.ttf");
    if (!game->font) {
        // Use default font if custom font not available
        game->font = NULL;
    }

    game->score_text = sfText_create();
    if (game->score_text) {
        if (game->font)
            sfText_setFont(game->score_text, game->font);
        sfText_setString(game->score_text, "Score: 0");
        sfText_setCharacterSize(game->score_text, 24);
        sfText_setFillColor(game->score_text, sfWhite);
        sfText_setPosition(game->score_text, (sfVector2f){10, 10});
    }

    // Initialize background
    game->background_texture = sfTexture_createFromFile("assets/background.png", NULL);
    if (game->background_texture) {
        game->background_sprite = sfSprite_create();
        sfSprite_setTexture(game->background_sprite, game->background_texture, sfTrue);
    } else {
        game->background_sprite = NULL;
    }

    if (init_ducks(game) != 0)
        return 84;

    return 0;
}

int game_loop(game_t *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        handle_events(game);
        
        update_ducks(game);
        
        // Clear window
        sfRenderWindow_clear(game->window, sfBlack);
        
        // Draw background
        if (game->background_sprite)
            sfRenderWindow_drawSprite(game->window, game->background_sprite, NULL);
        
        // Draw ducks
        draw_ducks(game);
        
        // Draw UI
        if (game->score_text) {
            char score_str[32];
            snprintf(score_str, sizeof(score_str), "Score: %d", game->score);
            sfText_setString(game->score_text, score_str);
            sfRenderWindow_drawText(game->window, game->score_text, NULL);
        }
        
        // Display everything
        sfRenderWindow_display(game->window);
    }
    
    return 0;
}

void cleanup_game(game_t *game)
{
    // Cleanup ducks
    for (int i = 0; i < MAX_DUCKS; i++) {
        if (game->ducks[i].sprite)
            sfSprite_destroy(game->ducks[i].sprite);
        if (game->ducks[i].texture)
            sfTexture_destroy(game->ducks[i].texture);
        if (game->ducks[i].animation_clock)
            sfClock_destroy(game->ducks[i].animation_clock);
    }

    // Cleanup UI
    if (game->score_text)
        sfText_destroy(game->score_text);
    if (game->font)
        sfFont_destroy(game->font);

    // Cleanup background
    if (game->background_sprite)
        sfSprite_destroy(game->background_sprite);
    if (game->background_texture)
        sfTexture_destroy(game->background_texture);

    // Cleanup game objects
    if (game->game_clock)
        sfClock_destroy(game->game_clock);
    
    if (game->window)
        sfRenderWindow_destroy(game->window);
}