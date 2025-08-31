/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Game initialization functions
*/

#include "../include/my_hunter.h"

static sfTexture *create_simple_texture(int width, int height, sfColor color)
{
    sfTexture *texture;
    sfImage *image;
    int x, y;

    image = sfImage_create(width, height, sfBlack);
    if (!image)
        return NULL;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            sfImage_setPixel(image, x, y, color);
        }
    }
    texture = sfTexture_createFromImage(image, NULL);
    sfImage_destroy(image);
    return texture;
}

static int init_graphics(game_t *game)
{
    game->bg_texture = create_simple_texture(WINDOW_WIDTH, WINDOW_HEIGHT,
        (sfColor){135, 206, 250, 255});
    if (!game->bg_texture)
        return -1;
    game->background = sfSprite_create();
    sfSprite_setTexture(game->background, game->bg_texture, sfTrue);
    game->crosshair_texture = create_simple_texture(32, 32,
        (sfColor){255, 0, 0, 255});
    if (!game->crosshair_texture)
        return -1;
    game->crosshair = sfSprite_create();
    sfSprite_setTexture(game->crosshair, game->crosshair_texture, sfTrue);
    return 0;
}

static int init_text(game_t *game)
{
    game->font = sfFont_createFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    if (!game->font)
        game->font = sfFont_createFromFile("/System/Library/Fonts/Arial.ttf");
    if (!game->font)
        return -1;
    game->score_text = sfText_create();
    sfText_setFont(game->score_text, game->font);
    sfText_setCharacterSize(game->score_text, 24);
    sfText_setFillColor(game->score_text, sfWhite);
    sfText_setPosition(game->score_text, (sfVector2f){10, 10});
    game->ammo_text = sfText_create();
    sfText_setFont(game->ammo_text, game->font);
    sfText_setCharacterSize(game->ammo_text, 24);
    sfText_setFillColor(game->ammo_text, sfWhite);
    sfText_setPosition(game->ammo_text, (sfVector2f){10, 40});
    return 0;
}

game_t *init_game(void)
{
    game_t *game = malloc(sizeof(game_t));
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};

    if (!game)
        return NULL;
    game->window = sfRenderWindow_create(mode, "MyHunter", 
        sfResize | sfClose, NULL);
    if (!game->window) {
        free(game);
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(game->window, FRAME_RATE);
    game->game_clock = sfClock_create();
    game->score = 0;
    game->ammo = 10;
    game->active_ducks = 0;
    game->game_over = 0;
    if (init_graphics(game) == -1 || init_text(game) == -1) {
        cleanup_game(game);
        return NULL;
    }
    init_ducks(game);
    return game;
}