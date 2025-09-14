/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Script parsing functions for MyRadar project
*/

#include "my_radar.h"

int parse_aircraft_line(char *line, aircraft_t *aircraft)
{
    int start_x, start_y, end_x, end_y, speed, delay;
    
    if (sscanf(line, "A %d %d %d %d %d %d", &start_x, &start_y, 
               &end_x, &end_y, &speed, &delay) != 6)
        return -1;

    aircraft->start_pos.x = start_x;
    aircraft->start_pos.y = start_y;
    aircraft->end_pos.x = end_x;
    aircraft->end_pos.y = end_y;
    aircraft->current_pos = aircraft->start_pos;
    aircraft->speed = speed;
    aircraft->delay = delay;
    aircraft->alive = 1;
    aircraft->departed = 0;

    // Calculate velocity direction
    sfVector2f direction = {
        aircraft->end_pos.x - aircraft->start_pos.x,
        aircraft->end_pos.y - aircraft->start_pos.y
    };
    direction = normalize_vector(direction);
    aircraft->velocity.x = direction.x * speed;
    aircraft->velocity.y = direction.y * speed;

    return 0;
}

int parse_tower_line(char *line, tower_t *tower)
{
    int x, y, radius;
    
    if (sscanf(line, "T %d %d %d", &x, &y, &radius) != 3)
        return -1;

    tower->position.x = x;
    tower->position.y = y;
    tower->radius = radius;

    return 0;
}

int parse_script_file(const char *filepath, simulation_t *sim)
{
    FILE *file = fopen(filepath, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int aircraft_count = 0;
    int tower_count = 0;

    if (!file) {
        fprintf(stderr, "Error: Cannot open script file %s\n", filepath);
        return -1;
    }

    // Allocate memory for entities
    sim->aircrafts = malloc(sizeof(aircraft_t) * MAX_AIRCRAFTS);
    sim->towers = malloc(sizeof(tower_t) * MAX_TOWERS);
    
    if (!sim->aircrafts || !sim->towers) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return -1;
    }

    // Parse each line
    while ((read = getline(&line, &len, file)) != -1) {
        if (line[0] == 'A' && aircraft_count < MAX_AIRCRAFTS) {
            if (parse_aircraft_line(line, &sim->aircrafts[aircraft_count]) == 0)
                aircraft_count++;
        } else if (line[0] == 'T' && tower_count < MAX_TOWERS) {
            if (parse_tower_line(line, &sim->towers[tower_count]) == 0)
                tower_count++;
        }
    }

    sim->nb_aircrafts = aircraft_count;
    sim->nb_towers = tower_count;

    free(line);
    fclose(file);
    
    if (aircraft_count == 0 && tower_count == 0) {
        fprintf(stderr, "Error: No valid entities found in script\n");
        return -1;
    }

    return 0;
}