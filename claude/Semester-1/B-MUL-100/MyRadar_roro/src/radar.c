/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Main radar simulation logic
*/

#include "../include/my_radar.h"

static void main_loop(radar_t *radar)
{
    while (sfRenderWindow_isOpen(radar->window)) {
        handle_events(radar);
        if (!radar->simulation_running)
            break;
        update_simulation(radar);
        render_simulation(radar);
    }
}

static int check_all_aircrafts_finished(radar_t *radar)
{
    int i;

    for (i = 0; i < radar->aircraft_count; i++) {
        if (radar->aircrafts[i].state == AIRCRAFT_WAITING ||
            radar->aircrafts[i].state == AIRCRAFT_FLYING) {
            return 0;
        }
    }
    return 1;
}

static void check_simulation_end(radar_t *radar)
{
    if (check_all_aircrafts_finished(radar)) {
        radar->simulation_running = 0;
    }
}

int my_radar(char *script_path)
{
    radar_t *radar;
    struct stat st;

    if (stat(script_path, &st) == -1) {
        fprintf(stderr, "Error: Script file not found or incorrect\n");
        return 84;
    }
    radar = init_radar();
    if (!radar)
        return 84;
    if (load_script(radar, script_path) == -1) {
        cleanup_radar(radar);
        return 84;
    }
    main_loop(radar);
    cleanup_radar(radar);
    return 0;
}

void update_simulation(radar_t *radar)
{
    update_aircrafts(radar);
    check_collisions(radar);
    update_timer(radar);
    check_simulation_end(radar);
}