/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Rendering functions for radar simulation
*/

#include "../include/my_radar.h"

static void render_aircrafts(radar_t *radar)
{
    int i;

    for (i = 0; i < radar->aircraft_count; i++) {
        aircraft_t *aircraft = &radar->aircrafts[i];
        if (!aircraft->active || 
            aircraft->state == AIRCRAFT_WAITING ||
            aircraft->state == AIRCRAFT_LANDED ||
            aircraft->state == AIRCRAFT_DESTROYED)
            continue;
        if (radar->show_sprites && aircraft->sprite) {
            sfRenderWindow_drawSprite(radar->window, aircraft->sprite, NULL);
        }
        if (radar->show_hitboxes && aircraft->hitbox) {
            sfRenderWindow_drawRectangleShape(radar->window, 
                aircraft->hitbox, NULL);
        }
    }
}

static void render_towers(radar_t *radar)
{
    int i;

    for (i = 0; i < radar->tower_count; i++) {
        tower_t *tower = &radar->towers[i];
        if (!tower->active)
            continue;
        if (radar->show_sprites && tower->sprite) {
            sfRenderWindow_drawSprite(radar->window, tower->sprite, NULL);
        }
        if (radar->show_hitboxes && tower->control_area) {
            sfRenderWindow_drawCircleShape(radar->window, 
                tower->control_area, NULL);
        }
    }
}

void update_timer(radar_t *radar)
{
    sfTime elapsed = sfClock_getElapsedTime(radar->game_clock);
    int seconds = (int)sfTime_asSeconds(elapsed);
    char timer_str[32];

    snprintf(timer_str, sizeof(timer_str), "Time: %02d:%02d", 
        seconds / 60, seconds % 60);
    sfText_setString(radar->timer_text, timer_str);
}

void render_simulation(radar_t *radar)
{
    sfRenderWindow_clear(radar->window, sfBlack);
    render_towers(radar);
    render_aircrafts(radar);
    sfRenderWindow_drawText(radar->window, radar->timer_text, NULL);
    sfRenderWindow_display(radar->window);
}