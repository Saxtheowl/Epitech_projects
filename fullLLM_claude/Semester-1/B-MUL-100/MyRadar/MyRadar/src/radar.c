/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Main radar simulation functions for MyRadar project
*/

#include "my_radar.h"

int init_simulation(simulation_t *sim)
{
    // Initialize simulation structure
    sim->window = NULL;
    sim->main_clock = NULL;
    sim->timer_text = NULL;
    sim->font = NULL;
    sim->aircrafts = NULL;
    sim->towers = NULL;
    sim->nb_aircrafts = 0;
    sim->nb_towers = 0;
    sim->show_hitboxes = 1;
    sim->show_sprites = 1;
    sim->elapsed_time = 0.0f;
    
    // Create main clock
    sim->main_clock = sfClock_create();
    if (!sim->main_clock)
        return -1;
    
    // Create window
    if (create_window(sim) != 0)
        return -1;
        
    // Load font for timer (try to load a system font)
    sim->font = sfFont_createFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    if (!sim->font) {
        // Try alternative font paths
        sim->font = sfFont_createFromFile("/System/Library/Fonts/Arial.ttf");
        if (!sim->font) {
            sim->font = sfFont_createFromFile("/usr/share/fonts/TTF/arial.ttf");
        }
    }
    
    // Create timer text
    sim->timer_text = sfText_create();
    if (!sim->timer_text)
        return -1;
        
    if (sim->font)
        sfText_setFont(sim->timer_text, sim->font);
    sfText_setCharacterSize(sim->timer_text, 24);
    sfText_setFillColor(sim->timer_text, sfWhite);
    sfText_setString(sim->timer_text, "0.0");
    
    return 0;
}

void cleanup_simulation(simulation_t *sim)
{
    // Cleanup aircrafts
    if (sim->aircrafts) {
        for (int i = 0; i < sim->nb_aircrafts; i++) {
            if (sim->aircrafts[i].sprite)
                sfSprite_destroy(sim->aircrafts[i].sprite);
            if (sim->aircrafts[i].texture)
                sfTexture_destroy(sim->aircrafts[i].texture);
            if (sim->aircrafts[i].hitbox)
                sfRectangleShape_destroy(sim->aircrafts[i].hitbox);
            if (sim->aircrafts[i].delay_clock)
                sfClock_destroy(sim->aircrafts[i].delay_clock);
        }
        free(sim->aircrafts);
    }
    
    // Cleanup towers
    if (sim->towers) {
        for (int i = 0; i < sim->nb_towers; i++) {
            if (sim->towers[i].sprite)
                sfSprite_destroy(sim->towers[i].sprite);
            if (sim->towers[i].texture)
                sfTexture_destroy(sim->towers[i].texture);
            if (sim->towers[i].control_area)
                sfCircleShape_destroy(sim->towers[i].control_area);
        }
        free(sim->towers);
    }
    
    // Cleanup other resources
    if (sim->timer_text)
        sfText_destroy(sim->timer_text);
    if (sim->font)
        sfFont_destroy(sim->font);
    if (sim->main_clock)
        sfClock_destroy(sim->main_clock);
    if (sim->window)
        sfRenderWindow_destroy(sim->window);
}

int check_simulation_end(simulation_t *sim)
{
    for (int i = 0; i < sim->nb_aircrafts; i++) {
        if (sim->aircrafts[i].alive)
            return 0;
    }
    return 1;
}

int run_simulation(simulation_t *sim)
{
    // Initialize aircrafts and towers
    if (init_aircrafts(sim) != 0) {
        fprintf(stderr, "Error: Failed to initialize aircrafts\n");
        return 84;
    }
    
    if (init_towers(sim) != 0) {
        fprintf(stderr, "Error: Failed to initialize towers\n");
        return 84;
    }
    
    // Main simulation loop
    while (sfRenderWindow_isOpen(sim->window)) {
        handle_events(sim);
        update_aircrafts(sim);
        render_simulation(sim);
        
        // Check if simulation should end (all aircrafts landed/destroyed)
        if (check_simulation_end(sim)) {
            // Wait a bit before closing
            usleep(2000000); // 2 seconds
            break;
        }
    }
    
    return 0;
}