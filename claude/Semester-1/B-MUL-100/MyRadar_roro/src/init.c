/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Radar initialization functions
*/

#include "../include/my_radar.h"

static int init_graphics(radar_t *radar)
{
    radar->aircraft_texture = create_aircraft_texture();
    radar->tower_texture = create_tower_texture();
    if (!radar->aircraft_texture || !radar->tower_texture)
        return -1;
    return 0;
}

static int init_text(radar_t *radar)
{
    radar->font = sfFont_createFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    if (!radar->font)
        radar->font = sfFont_createFromFile("/System/Library/Fonts/Arial.ttf");
    if (!radar->font)
        return -1;
    radar->timer_text = sfText_create();
    sfText_setFont(radar->timer_text, radar->font);
    sfText_setCharacterSize(radar->timer_text, 24);
    sfText_setFillColor(radar->timer_text, sfWhite);
    sfText_setPosition(radar->timer_text, 
        (sfVector2f){WINDOW_WIDTH - 150, 20});
    return 0;
}

radar_t *init_radar(void)
{
    radar_t *radar = malloc(sizeof(radar_t));
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};

    if (!radar)
        return NULL;
    radar->window = sfRenderWindow_create(mode, "MyRadar", 
        sfResize | sfClose, NULL);
    if (!radar->window) {
        free(radar);
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(radar->window, FRAME_RATE);
    radar->game_clock = sfClock_create();
    radar->aircraft_count = 0;
    radar->tower_count = 0;
    radar->show_hitboxes = 1;
    radar->show_sprites = 1;
    radar->simulation_running = 1;
    if (init_graphics(radar) == -1 || init_text(radar) == -1) {
        cleanup_radar(radar);
        return NULL;
    }
    return radar;
}