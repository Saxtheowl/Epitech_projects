/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Duck management functions
*/

#include "../include/my_hunter.h"

static sfTexture *create_duck_texture(void)
{
    sfTexture *texture;
    sfImage *image;
    int x, y;
    int duck_width = 64;
    int duck_height = 64;

    image = sfImage_create(duck_width * 3, duck_height, sfTransparent);
    if (!image)
        return NULL;
    for (int frame = 0; frame < 3; frame++) {
        for (y = 20; y < 44; y++) {
            for (x = frame * duck_width + 10; x < frame * duck_width + 54; x++) {
                sfImage_setPixel(image, x, y, (sfColor){139, 69, 19, 255});
            }
        }
        for (y = 15; y < 25; y++) {
            for (x = frame * duck_width + 15; x < frame * duck_width + 25; x++) {
                sfImage_setPixel(image, x, y, (sfColor){255, 140, 0, 255});
            }
        }
        if (frame == 1) {
            for (y = 10; y < 30; y++) {
                for (x = frame * duck_width + 5; x < frame * duck_width + 15; x++) {
                    sfImage_setPixel(image, x, y, (sfColor){139, 69, 19, 255});
                }
            }
        }
    }
    texture = sfTexture_createFromImage(image, NULL);
    sfImage_destroy(image);
    return texture;
}

void spawn_duck(game_t *game, int index)
{
    duck_t *duck = &game->ducks[index];
    int side = rand() % 2;
    float angle = (rand() % 60 - 30) * M_PI / 180.0f;

    if (side == 0) {
        duck->position.x = -64;
        duck->position.y = rand() % (WINDOW_HEIGHT - 200) + 100;
        duck->velocity.x = DUCK_SPEED * cos(angle);
    } else {
        duck->position.x = WINDOW_WIDTH;
        duck->position.y = rand() % (WINDOW_HEIGHT - 200) + 100;
        duck->velocity.x = -DUCK_SPEED * cos(angle);
    }
    duck->velocity.y = DUCK_SPEED * sin(angle);
    duck->state = DUCK_FLYING;
    duck->alive = 1;
    duck->frame = 0;
    duck->max_frames = 3;
    sfSprite_setPosition(duck->sprite, duck->position);
    sfClock_restart(duck->anim_clock);
}

void init_ducks(game_t *game)
{
    int i;

    for (i = 0; i < MAX_DUCKS; i++) {
        game->ducks[i].texture = create_duck_texture();
        game->ducks[i].sprite = sfSprite_create();
        game->ducks[i].anim_clock = sfClock_create();
        game->ducks[i].rect = create_rect(0, 0, 64, 64);
        game->ducks[i].alive = 0;
        if (game->ducks[i].texture) {
            sfSprite_setTexture(game->ducks[i].sprite, 
                game->ducks[i].texture, sfTrue);
            sfSprite_setTextureRect(game->ducks[i].sprite, game->ducks[i].rect);
        }
    }
    spawn_duck(game, 0);
    game->active_ducks = 1;
}

void update_duck_animation(duck_t *duck)
{
    sfTime time;
    float elapsed;

    time = sfClock_getElapsedTime(duck->anim_clock);
    elapsed = sfTime_asSeconds(time);
    if (elapsed > ANIMATION_SPEED) {
        duck->frame = (duck->frame + 1) % duck->max_frames;
        duck->rect.left = duck->frame * 64;
        sfSprite_setTextureRect(duck->sprite, duck->rect);
        sfClock_restart(duck->anim_clock);
    }
}