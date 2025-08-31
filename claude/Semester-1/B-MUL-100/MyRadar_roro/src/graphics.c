/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Graphics and texture creation functions
*/

#include "../include/my_radar.h"

sfTexture *create_aircraft_texture(void)
{
    sfTexture *texture;
    sfImage *image;
    int x, y;

    image = sfImage_create(AIRCRAFT_SIZE, AIRCRAFT_SIZE, sfTransparent);
    if (!image)
        return NULL;
    for (y = 5; y < 15; y++) {
        for (x = 0; x < AIRCRAFT_SIZE; x++) {
            sfImage_setPixel(image, x, y, (sfColor){0, 150, 255, 255});
        }
    }
    for (y = 8; y < 12; y++) {
        for (x = 2; x < 18; x++) {
            sfImage_setPixel(image, x, y, (sfColor){255, 255, 255, 255});
        }
    }
    texture = sfTexture_createFromImage(image, NULL);
    sfImage_destroy(image);
    return texture;
}

sfTexture *create_tower_texture(void)
{
    sfTexture *texture;
    sfImage *image;
    int x, y;
    int size = 32;

    image = sfImage_create(size, size, sfTransparent);
    if (!image)
        return NULL;
    for (y = size/2 - 8; y < size/2 + 8; y++) {
        for (x = size/2 - 3; x < size/2 + 3; x++) {
            sfImage_setPixel(image, x, y, (sfColor){100, 100, 100, 255});
        }
    }
    for (y = size/2 - 12; y < size/2 - 8; y++) {
        for (x = size/2 - 6; x < size/2 + 6; x++) {
            sfImage_setPixel(image, x, y, (sfColor){150, 150, 150, 255});
        }
    }
    texture = sfTexture_createFromImage(image, NULL);
    sfImage_destroy(image);
    return texture;
}

static void init_tower_graphics(radar_t *radar)
{
    int i;

    for (i = 0; i < radar->tower_count; i++) {
        tower_t *tower = &radar->towers[i];
        tower->sprite = sfSprite_create();
        sfSprite_setTexture(tower->sprite, radar->tower_texture, sfTrue);
        sfSprite_setPosition(tower->sprite, 
            (sfVector2f){tower->position.x - 16, tower->position.y - 16});
        tower->control_area = sfCircleShape_create();
        sfCircleShape_setRadius(tower->control_area, tower->radius);
        sfCircleShape_setFillColor(tower->control_area, sfTransparent);
        sfCircleShape_setOutlineColor(tower->control_area, 
            (sfColor){0, 255, 0, 100});
        sfCircleShape_setOutlineThickness(tower->control_area, 2.0f);
        sfCircleShape_setPosition(tower->control_area, 
            (sfVector2f){tower->position.x - tower->radius, 
            tower->position.y - tower->radius});
    }
}

static void init_aircraft_graphics(radar_t *radar)
{
    int i;

    for (i = 0; i < radar->aircraft_count; i++) {
        aircraft_t *aircraft = &radar->aircrafts[i];
        if (aircraft->state == AIRCRAFT_FLYING && aircraft->sprite) {
            sfSprite_setTexture(aircraft->sprite, 
                radar->aircraft_texture, sfTrue);
        }
    }
}

void cleanup_radar(radar_t *radar)
{
    int i;

    if (!radar)
        return;
    for (i = 0; i < radar->aircraft_count; i++) {
        if (radar->aircrafts[i].sprite)
            sfSprite_destroy(radar->aircrafts[i].sprite);
        if (radar->aircrafts[i].hitbox)
            sfRectangleShape_destroy(radar->aircrafts[i].hitbox);
        if (radar->aircrafts[i].spawn_clock)
            sfClock_destroy(radar->aircrafts[i].spawn_clock);
    }
    for (i = 0; i < radar->tower_count; i++) {
        if (radar->towers[i].sprite)
            sfSprite_destroy(radar->towers[i].sprite);
        if (radar->towers[i].control_area)
            sfCircleShape_destroy(radar->towers[i].control_area);
    }
    if (radar->aircraft_texture)
        sfTexture_destroy(radar->aircraft_texture);
    if (radar->tower_texture)
        sfTexture_destroy(radar->tower_texture);
    if (radar->timer_text)
        sfText_destroy(radar->timer_text);
    if (radar->font)
        sfFont_destroy(radar->font);
    if (radar->game_clock)
        sfClock_destroy(radar->game_clock);
    if (radar->window)
        sfRenderWindow_destroy(radar->window);
    free(radar);
}