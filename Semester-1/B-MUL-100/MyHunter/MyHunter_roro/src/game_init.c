/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Game initialization functions
*/

#include "../include/my_hunter.h"

static int load_textures(game_t *game)
{
    game->duck_texture = sfTexture_create(64, 64);
    game->background_texture = sfTexture_create(WINDOW_WIDTH, WINDOW_HEIGHT);
    game->crosshair_texture = sfTexture_create(32, 32);

    if (!game->duck_texture || !game->background_texture || 
        !game->crosshair_texture)
        return -1;

    return 0;
}

static int create_sprites(game_t *game)
{
    game->duck_sprite = sfSprite_create();
    game->background_sprite = sfSprite_create();
    game->crosshair_sprite = sfSprite_create();

    if (!game->duck_sprite || !game->background_sprite || 
        !game->crosshair_sprite)
        return -1;

    sfSprite_setTexture(game->duck_sprite, game->duck_texture, sfTrue);
    sfSprite_setTexture(game->background_sprite, game->background_texture, sfTrue);
    sfSprite_setTexture(game->crosshair_sprite, game->crosshair_texture, sfTrue);

    return 0;
}

static int create_text_elements(game_t *game)
{
    game->font = sfFont_createFromMemory(NULL, 0);
    if (!game->font)
        return -1;

    game->score_text = sfText_create();
    game->lives_text = sfText_create();

    if (!game->score_text || !game->lives_text)
        return -1;

    sfText_setFont(game->score_text, game->font);
    sfText_setFont(game->lives_text, game->font);
    sfText_setCharacterSize(game->score_text, 24);
    sfText_setCharacterSize(game->lives_text, 24);
    sfText_setColor(game->score_text, sfWhite);
    sfText_setColor(game->lives_text, sfWhite);

    return 0;
}

static void init_game_state(game_t *game)
{
    int i;

    game->stats.score = 0;
    game->stats.lives = 3;
    game->stats.level = 1;
    game->stats.ducks_killed = 0;
    game->stats.high_score = 0;
    game->running = 1;

    for (i = 0; i < MAX_DUCKS; i++) {
        game->ducks[i].alive = 0;
    }

    load_high_score(game);
}

int game_init(game_t *game)
{
    game->window = sfRenderWindow_create(
        (sfVideoMode){WINDOW_WIDTH, WINDOW_HEIGHT, 32},
        "MyHunter - Duck Hunt Legacy",
        sfResize | sfClose,
        NULL
    );

    if (!game->window)
        return -1;

    sfRenderWindow_setFramerateLimit(game->window, 60);

    if (load_textures(game) != 0)
        return -1;

    if (create_sprites(game) != 0)
        return -1;

    if (create_text_elements(game) != 0)
        return -1;

    game->game_clock = sfClock_create();
    game->spawn_clock = sfClock_create();

    if (!game->game_clock || !game->spawn_clock)
        return -1;

    init_game_state(game);

    return 0;
}