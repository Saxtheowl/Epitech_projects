/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** Core system initialization and main loop
*/

#include "../include/my_world.h"

world_t *init_world(void)
{
    world_t *world = malloc(sizeof(world_t));
    
    if (!world)
        return NULL;
    
    world->window = sfRenderWindow_create(
        (sfVideoMode){WINDOW_WIDTH, WINDOW_HEIGHT, 32},
        "MyWorld - Terrain Editor", sfResize | sfClose, NULL);
    
    if (!world->window) {
        free(world);
        return NULL;
    }
    
    world->clock = sfClock_create();
    world->running = 1;
    world->mouse_pressed = 0;
    world->current_tool = TOOL_RAISE;
    world->selection_mode = SELECT_TILES;
    
    for (int i = 0; i < 5; i++) {
        world->textures[i] = NULL;
        world->sounds[i] = NULL;
    }
    
    init_camera(world);
    init_ui(world);
    
    return world;
}

void destroy_world(world_t *world)
{
    if (!world)
        return;
    
    destroy_map(&world->map);
    destroy_ui(&world->ui);
    
    for (int i = 0; i < 5; i++) {
        if (world->textures[i])
            sfTexture_destroy(world->textures[i]);
        if (world->sounds[i])
            sfSound_destroy(world->sounds[i]);
    }
    
    if (world->clock)
        sfClock_destroy(world->clock);
    if (world->window)
        sfRenderWindow_destroy(world->window);
    
    free(world);
}

int run_world(world_t *world)
{
    if (!world)
        return 84;
    
    while (world->running && sfRenderWindow_isOpen(world->window)) {
        sfTime time = sfClock_getElapsedTime(world->clock);
        world->delta_time = sfTime_asSeconds(time);
        sfClock_restart(world->clock);
        
        handle_events(world);
        update_camera(world);
        update_ui(world);
        
        sfRenderWindow_clear(world->window, sfColor_fromRGB(40, 40, 40));
        
        render_map(world);
        render_ui(world);
        
        sfRenderWindow_display(world->window);
    }
    
    return 0;
}