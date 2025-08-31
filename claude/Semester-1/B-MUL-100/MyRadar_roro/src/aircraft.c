/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Aircraft management functions
*/

#include "../include/my_radar.h"

void spawn_aircraft(aircraft_t *aircraft)
{
    aircraft->sprite = sfSprite_create();
    aircraft->hitbox = sfRectangleShape_create();
    sfRectangleShape_setSize(aircraft->hitbox, 
        (sfVector2f){AIRCRAFT_SIZE, AIRCRAFT_SIZE});
    sfRectangleShape_setFillColor(aircraft->hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(aircraft->hitbox, sfRed);
    sfRectangleShape_setOutlineThickness(aircraft->hitbox, 2.0f);
    aircraft->current_pos = aircraft->start_pos;
    aircraft->state = AIRCRAFT_FLYING;
    sfSprite_setPosition(aircraft->sprite, aircraft->current_pos);
    sfRectangleShape_setPosition(aircraft->hitbox, aircraft->current_pos);
}

static void update_aircraft_position(aircraft_t *aircraft, float dt)
{
    float dx, dy, distance;

    aircraft->current_pos.x += aircraft->velocity.x * dt;
    aircraft->current_pos.y += aircraft->velocity.y * dt;
    dx = aircraft->end_pos.x - aircraft->current_pos.x;
    dy = aircraft->end_pos.y - aircraft->current_pos.y;
    distance = sqrt(dx * dx + dy * dy);
    if (distance < 5.0f) {
        aircraft->state = AIRCRAFT_LANDED;
        aircraft->current_pos = aircraft->end_pos;
    }
    sfSprite_setPosition(aircraft->sprite, aircraft->current_pos);
    sfRectangleShape_setPosition(aircraft->hitbox, aircraft->current_pos);
}

void update_aircrafts(radar_t *radar)
{
    int i;
    float dt = 1.0f / FRAME_RATE;
    sfTime elapsed;

    for (i = 0; i < radar->aircraft_count; i++) {
        aircraft_t *aircraft = &radar->aircrafts[i];
        if (!aircraft->active)
            continue;
        if (aircraft->state == AIRCRAFT_WAITING) {
            elapsed = sfClock_getElapsedTime(aircraft->spawn_clock);
            if (sfTime_asSeconds(elapsed) >= aircraft->delay) {
                spawn_aircraft(aircraft);
            }
        } else if (aircraft->state == AIRCRAFT_FLYING) {
            update_aircraft_position(aircraft, dt);
            if (aircraft->current_pos.x < -AIRCRAFT_SIZE || 
                aircraft->current_pos.x > WINDOW_WIDTH ||
                aircraft->current_pos.y < -AIRCRAFT_SIZE || 
                aircraft->current_pos.y > WINDOW_HEIGHT) {
                aircraft->state = AIRCRAFT_LANDED;
            }
        }
    }
}