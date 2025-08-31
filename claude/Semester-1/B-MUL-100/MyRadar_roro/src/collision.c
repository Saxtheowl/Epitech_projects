/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Collision detection functions
*/

#include "../include/my_radar.h"

float calculate_distance(sfVector2f pos1, sfVector2f pos2)
{
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;

    return sqrt(dx * dx + dy * dy);
}

int check_aircraft_collision(aircraft_t *a1, aircraft_t *a2)
{
    float distance;

    if (a1->state != AIRCRAFT_FLYING || a2->state != AIRCRAFT_FLYING)
        return 0;
    distance = calculate_distance(a1->current_pos, a2->current_pos);
    return distance < AIRCRAFT_SIZE;
}

int is_in_control_area(aircraft_t *aircraft, tower_t *tower)
{
    float distance;

    if (aircraft->state != AIRCRAFT_FLYING)
        return 0;
    distance = calculate_distance(aircraft->current_pos, tower->position);
    return distance <= tower->radius;
}

static int aircraft_in_any_control_area(radar_t *radar, int aircraft_idx)
{
    int i;

    for (i = 0; i < radar->tower_count; i++) {
        if (radar->towers[i].active && 
            is_in_control_area(&radar->aircrafts[aircraft_idx], 
                &radar->towers[i])) {
            return 1;
        }
    }
    return 0;
}

void check_collisions(radar_t *radar)
{
    int i, j;
    int aircraft1_protected, aircraft2_protected;

    for (i = 0; i < radar->aircraft_count; i++) {
        for (j = i + 1; j < radar->aircraft_count; j++) {
            if (radar->aircrafts[i].active && 
                radar->aircrafts[j].active &&
                check_aircraft_collision(&radar->aircrafts[i], 
                    &radar->aircrafts[j])) {
                aircraft1_protected = aircraft_in_any_control_area(radar, i);
                aircraft2_protected = aircraft_in_any_control_area(radar, j);
                if (!aircraft1_protected && !aircraft2_protected) {
                    radar->aircrafts[i].state = AIRCRAFT_DESTROYED;
                    radar->aircrafts[j].state = AIRCRAFT_DESTROYED;
                }
            }
        }
    }
}