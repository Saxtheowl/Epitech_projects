/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Control tower functions for MyRadar project
*/

#include "my_radar.h"

int init_towers(simulation_t *sim)
{
    for (int i = 0; i < sim->nb_towers; i++) {
        tower_t *tower = &sim->towers[i];
        
        // Create sprite and texture
        tower->texture = sfTexture_createFromFile("tower.png", NULL);
        if (!tower->texture) {
            // Create a simple colored rectangle if texture fails
            tower->texture = sfTexture_create(30, 30);
        }
        
        tower->sprite = sfSprite_create();
        if (!tower->sprite)
            return -1;
        sfSprite_setTexture(tower->sprite, tower->texture, sfTrue);
        sfSprite_setPosition(tower->sprite, tower->position);
        
        // Create control area circle
        tower->control_area = sfCircleShape_create();
        if (!tower->control_area)
            return -1;
            
        sfCircleShape_setRadius(tower->control_area, tower->radius);
        sfCircleShape_setFillColor(tower->control_area, sfTransparent);
        sfCircleShape_setOutlineThickness(tower->control_area, 2);
        sfCircleShape_setOutlineColor(tower->control_area, sfGreen);
        
        // Center the circle on the tower position
        sfVector2f circle_pos = {
            tower->position.x - tower->radius,
            tower->position.y - tower->radius
        };
        sfCircleShape_setPosition(tower->control_area, circle_pos);
    }
    
    return 0;
}

void draw_towers(simulation_t *sim)
{
    for (int i = 0; i < sim->nb_towers; i++) {
        tower_t *tower = &sim->towers[i];
        
        if (sim->show_sprites)
            sfRenderWindow_drawSprite(sim->window, tower->sprite, NULL);
            
        if (sim->show_hitboxes)
            sfRenderWindow_drawCircleShape(sim->window, tower->control_area, NULL);
    }
}