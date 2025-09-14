/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Window management functions for MyRadar project
*/

#include "my_radar.h"

int create_window(simulation_t *sim)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    
    sim->window = sfRenderWindow_create(mode, WINDOW_TITLE, sfResize | sfClose, NULL);
    if (!sim->window)
        return -1;
        
    sfRenderWindow_setFramerateLimit(sim->window, 60);
    
    return 0;
}

void handle_events(simulation_t *sim)
{
    while (sfRenderWindow_pollEvent(sim->window, &sim->event)) {
        switch (sim->event.type) {
            case sfEvtClosed:
                sfRenderWindow_close(sim->window);
                break;
            case sfEvtKeyPressed:
                switch (sim->event.key.code) {
                    case sfKeyEscape:
                        sfRenderWindow_close(sim->window);
                        break;
                    case sfKeyL:
                        sim->show_hitboxes = !sim->show_hitboxes;
                        break;
                    case sfKeyS:
                        sim->show_sprites = !sim->show_sprites;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void render_simulation(simulation_t *sim)
{
    char timer_str[64];
    
    sfRenderWindow_clear(sim->window, sfBlack);
    
    // Draw towers
    draw_towers(sim);
    
    // Draw aircrafts
    draw_aircrafts(sim);
    
    // Update and draw timer
    sim->elapsed_time += sfTime_asSeconds(sfClock_restart(sim->main_clock));
    snprintf(timer_str, sizeof(timer_str), "%.1f", sim->elapsed_time);
    sfText_setString(sim->timer_text, timer_str);
    
    // Position timer at top-right corner
    sfVector2f timer_pos = {WINDOW_WIDTH - 100, 20};
    sfText_setPosition(sim->timer_text, timer_pos);
    sfRenderWindow_drawText(sim->window, sim->timer_text, NULL);
    
    sfRenderWindow_display(sim->window);
}