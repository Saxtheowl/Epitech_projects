/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Script loading and parsing functions
*/

#include "../include/my_radar.h"

int parse_aircraft_line(char *line, aircraft_t *aircraft, int id)
{
    int start_x, start_y, end_x, end_y, speed, delay;

    if (sscanf(line, "A %d %d %d %d %d %d", 
        &start_x, &start_y, &end_x, &end_y, &speed, &delay) != 6)
        return -1;
    aircraft->id = id;
    aircraft->start_pos = (sfVector2f){start_x, start_y};
    aircraft->end_pos = (sfVector2f){end_x, end_y};
    aircraft->current_pos = aircraft->start_pos;
    aircraft->speed = speed;
    aircraft->delay = delay;
    aircraft->state = AIRCRAFT_WAITING;
    aircraft->active = 1;
    aircraft->spawn_clock = sfClock_create();
    float dx = end_x - start_x;
    float dy = end_y - start_y;
    float distance = sqrt(dx * dx + dy * dy);
    if (distance > 0) {
        aircraft->velocity.x = (dx / distance) * speed;
        aircraft->velocity.y = (dy / distance) * speed;
    }
    return 0;
}

int parse_tower_line(char *line, tower_t *tower, int id)
{
    int x, y, radius;

    if (sscanf(line, "T %d %d %d", &x, &y, &radius) != 3)
        return -1;
    tower->id = id;
    tower->position = (sfVector2f){x, y};
    tower->radius = radius;
    tower->active = 1;
    return 0;
}

static int process_line(radar_t *radar, char *line)
{
    if (line[0] == 'A') {
        if (radar->aircraft_count >= MAX_AIRCRAFTS)
            return -1;
        return parse_aircraft_line(line, 
            &radar->aircrafts[radar->aircraft_count++], 
            radar->aircraft_count);
    } else if (line[0] == 'T') {
        if (radar->tower_count >= MAX_TOWERS)
            return -1;
        return parse_tower_line(line, 
            &radar->towers[radar->tower_count++], 
            radar->tower_count);
    }
    return 0;
}

int load_script(radar_t *radar, char *script_path)
{
    FILE *file = fopen(script_path, "r");
    char *line = NULL;
    size_t len = 0;
    int result = 0;

    if (!file) {
        fprintf(stderr, "Error: Cannot open script file\n");
        return -1;
    }
    while (getline(&line, &len, file) != -1 && result == 0) {
        if (strlen(line) > 1 && line[0] != '#') {
            result = process_line(radar, line);
        }
    }
    if (line)
        free(line);
    fclose(file);
    if (result == -1) {
        fprintf(stderr, "Error: Script file incorrect\n");
        return -1;
    }
    return 0;
}