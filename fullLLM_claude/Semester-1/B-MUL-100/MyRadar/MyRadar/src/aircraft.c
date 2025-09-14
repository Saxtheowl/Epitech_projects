/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Aircraft management functions for MyRadar project
*/

#include "my_radar.h"

int init_aircrafts(simulation_t *sim)
{
    for (int i = 0; i < sim->nb_aircrafts; i++) {
        aircraft_t *aircraft = &sim->aircrafts[i];
        
        // Create sprite and texture
        aircraft->texture = sfTexture_createFromFile("plane.png", NULL);
        if (!aircraft->texture) {
            // Create a simple colored rectangle if texture fails
            aircraft->texture = sfTexture_create(AIRCRAFT_HITBOX_SIZE, AIRCRAFT_HITBOX_SIZE);
        }
        
        aircraft->sprite = sfSprite_create();
        if (!aircraft->sprite)
            return -1;
        sfSprite_setTexture(aircraft->sprite, aircraft->texture, sfTrue);
        
        // Create hitbox
        aircraft->hitbox = sfRectangleShape_create();
        if (!aircraft->hitbox)
            return -1;
        
        sfVector2f size = {AIRCRAFT_HITBOX_SIZE, AIRCRAFT_HITBOX_SIZE};
        sfRectangleShape_setSize(aircraft->hitbox, size);
        sfRectangleShape_setFillColor(aircraft->hitbox, sfRed);
        sfRectangleShape_setOutlineThickness(aircraft->hitbox, 1);
        sfRectangleShape_setOutlineColor(aircraft->hitbox, sfWhite);
        
        // Create delay clock
        aircraft->delay_clock = sfClock_create();
        if (!aircraft->delay_clock)
            return -1;
    }
    
    return 0;
}

void update_aircrafts(simulation_t *sim)
{
    float delta_time = sfTime_asSeconds(sfClock_getElapsedTime(sim->main_clock));
    
    for (int i = 0; i < sim->nb_aircrafts; i++) {
        aircraft_t *aircraft = &sim->aircrafts[i];
        
        if (!aircraft->alive)
            continue;
            
        // Check if aircraft should take off
        if (!aircraft->departed) {
            float delay_time = sfTime_asSeconds(sfClock_getElapsedTime(aircraft->delay_clock));
            if (delay_time >= aircraft->delay) {
                aircraft->departed = 1;
            } else {
                continue;
            }
        }
        
        // Update position
        aircraft->current_pos.x += aircraft->velocity.x * delta_time;
        aircraft->current_pos.y += aircraft->velocity.y * delta_time;
        
        // Check if aircraft has reached destination
        float dist_to_end = distance(aircraft->current_pos, aircraft->end_pos);
        if (dist_to_end < 5.0f) {
            aircraft->alive = 0;
            continue;
        }
        
        // Update sprite and hitbox positions
        sfSprite_setPosition(aircraft->sprite, aircraft->current_pos);
        
        sfVector2f hitbox_pos = {
            aircraft->current_pos.x - AIRCRAFT_HITBOX_SIZE / 2,
            aircraft->current_pos.y - AIRCRAFT_HITBOX_SIZE / 2
        };
        sfRectangleShape_setPosition(aircraft->hitbox, hitbox_pos);
        
        // Check collisions with other aircrafts
        for (int j = i + 1; j < sim->nb_aircrafts; j++) {
            aircraft_t *other = &sim->aircrafts[j];
            if (!other->alive || !other->departed)
                continue;
                
            // Check if both aircrafts are in a tower control area
            int aircraft_protected = 0;
            int other_protected = 0;
            
            for (int k = 0; k < sim->nb_towers; k++) {
                if (check_aircraft_in_tower_area(aircraft, &sim->towers[k]))
                    aircraft_protected = 1;
                if (check_aircraft_in_tower_area(other, &sim->towers[k]))
                    other_protected = 1;
            }
            
            if (aircraft_protected && other_protected)
                continue;
                
            if (check_aircraft_collision(aircraft, other)) {
                aircraft->alive = 0;
                other->alive = 0;
            }
        }
    }
    
    sfClock_restart(sim->main_clock);
}

void draw_aircrafts(simulation_t *sim)
{
    for (int i = 0; i < sim->nb_aircrafts; i++) {
        aircraft_t *aircraft = &sim->aircrafts[i];
        
        if (!aircraft->alive || !aircraft->departed)
            continue;
            
        if (sim->show_sprites)
            sfRenderWindow_drawSprite(sim->window, aircraft->sprite, NULL);
            
        if (sim->show_hitboxes)
            sfRenderWindow_drawRectangleShape(sim->window, aircraft->hitbox, NULL);
    }
}

int check_aircraft_collision(aircraft_t *a1, aircraft_t *a2)
{
    float dist = distance(a1->current_pos, a2->current_pos);
    return dist < AIRCRAFT_HITBOX_SIZE;
}

int check_aircraft_in_tower_area(aircraft_t *aircraft, tower_t *tower)
{
    float dist = distance(aircraft->current_pos, tower->position);
    return dist <= tower->radius;
}