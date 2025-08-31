/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Mock main for testing without CSFML dependencies
*/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define MAX_AIRCRAFTS 100
#define MAX_TOWERS 50
#define AIRCRAFT_SIZE 20

typedef enum {
    AIRCRAFT_WAITING,
    AIRCRAFT_FLYING,
    AIRCRAFT_LANDED,
    AIRCRAFT_DESTROYED
} aircraft_state_t;

typedef struct {
    float x;
    float y;
} sfVector2f;

typedef struct aircraft_s {
    int id;
    sfVector2f start_pos;
    sfVector2f end_pos;
    sfVector2f current_pos;
    sfVector2f velocity;
    int speed;
    int delay;
    aircraft_state_t state;
    float spawn_time;
    int active;
} aircraft_t;

typedef struct tower_s {
    int id;
    sfVector2f position;
    int radius;
    int active;
} tower_t;

typedef struct radar_s {
    aircraft_t aircrafts[MAX_AIRCRAFTS];
    tower_t towers[MAX_TOWERS];
    int aircraft_count;
    int tower_count;
    float simulation_time;
    int running;
} radar_t;

void print_usage(void)
{
    printf("Air traffic simulation panel\n");
    printf("USAGE\n    ./my_radar [OPTIONS] path_to_script\n");
    printf("OPTIONS\n");
    printf("    -h    print the usage and quit\n");
}

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
    aircraft->spawn_time = -1.0f;
    aircraft->active = 1;
    
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

float calculate_distance(sfVector2f pos1, sfVector2f pos2)
{
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    return sqrt(dx * dx + dy * dy);
}

int load_script(const char *filename, radar_t *radar)
{
    FILE *file;
    char line[256];
    int aircraft_id = 1, tower_id = 1;

    file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open script file '%s'\n", filename);
        return -1;
    }
    
    radar->aircraft_count = 0;
    radar->tower_count = 0;
    
    while (fgets(line, sizeof(line), file) && 
           radar->aircraft_count < MAX_AIRCRAFTS && 
           radar->tower_count < MAX_TOWERS) {
        if (line[0] == 'A' && radar->aircraft_count < MAX_AIRCRAFTS) {
            if (parse_aircraft_line(line, &radar->aircrafts[radar->aircraft_count], 
                                  aircraft_id++) == 0) {
                radar->aircraft_count++;
            }
        } else if (line[0] == 'T' && radar->tower_count < MAX_TOWERS) {
            if (parse_tower_line(line, &radar->towers[radar->tower_count], 
                               tower_id++) == 0) {
                radar->tower_count++;
            }
        }
    }
    
    fclose(file);
    printf("Loaded %d aircrafts and %d towers from script\n", 
           radar->aircraft_count, radar->tower_count);
    return 0;
}

int is_in_control_area(aircraft_t *aircraft, radar_t *radar)
{
    int i;

    for (i = 0; i < radar->tower_count; i++) {
        tower_t *tower = &radar->towers[i];
        if (!tower->active)
            continue;
        float distance = calculate_distance(aircraft->current_pos, tower->position);
        if (distance <= tower->radius)
            return 1;
    }
    return 0;
}

void update_aircraft(radar_t *radar, float delta_time)
{
    int i;

    for (i = 0; i < radar->aircraft_count; i++) {
        aircraft_t *aircraft = &radar->aircrafts[i];
        
        if (!aircraft->active)
            continue;
            
        if (aircraft->state == AIRCRAFT_WAITING) {
            if (radar->simulation_time >= aircraft->delay) {
                aircraft->state = AIRCRAFT_FLYING;
                aircraft->spawn_time = radar->simulation_time;
                printf("[%.1fs] Aircraft %d spawned at (%.0f, %.0f)\n",
                       radar->simulation_time, aircraft->id, 
                       aircraft->current_pos.x, aircraft->current_pos.y);
            }
        } else if (aircraft->state == AIRCRAFT_FLYING) {
            aircraft->current_pos.x += aircraft->velocity.x * delta_time;
            aircraft->current_pos.y += aircraft->velocity.y * delta_time;
            
            float distance_to_end = calculate_distance(aircraft->current_pos, 
                                                     aircraft->end_pos);
            if (distance_to_end < 5.0f) {
                aircraft->state = AIRCRAFT_LANDED;
                aircraft->current_pos = aircraft->end_pos;
                printf("[%.1fs] Aircraft %d landed at (%.0f, %.0f)\n",
                       radar->simulation_time, aircraft->id, 
                       aircraft->current_pos.x, aircraft->current_pos.y);
            }
        }
    }
}

void check_collisions(radar_t *radar)
{
    int i, j;

    for (i = 0; i < radar->aircraft_count; i++) {
        aircraft_t *aircraft1 = &radar->aircrafts[i];
        
        if (aircraft1->state != AIRCRAFT_FLYING)
            continue;
            
        for (j = i + 1; j < radar->aircraft_count; j++) {
            aircraft_t *aircraft2 = &radar->aircrafts[j];
            
            if (aircraft2->state != AIRCRAFT_FLYING)
                continue;
                
            float distance = calculate_distance(aircraft1->current_pos, 
                                              aircraft2->current_pos);
            if (distance < AIRCRAFT_SIZE) {
                int aircraft1_protected = is_in_control_area(aircraft1, radar);
                int aircraft2_protected = is_in_control_area(aircraft2, radar);
                
                if (!aircraft1_protected && !aircraft2_protected) {
                    aircraft1->state = AIRCRAFT_DESTROYED;
                    aircraft2->state = AIRCRAFT_DESTROYED;
                    printf("[%.1fs] COLLISION: Aircraft %d and %d destroyed at (%.0f, %.0f)\n",
                           radar->simulation_time, aircraft1->id, aircraft2->id,
                           (aircraft1->current_pos.x + aircraft2->current_pos.x) / 2,
                           (aircraft1->current_pos.y + aircraft2->current_pos.y) / 2);
                }
            }
        }
    }
}

void print_status(radar_t *radar)
{
    int i, flying = 0, waiting = 0, landed = 0, destroyed = 0;

    for (i = 0; i < radar->aircraft_count; i++) {
        switch (radar->aircrafts[i].state) {
            case AIRCRAFT_WAITING: waiting++; break;
            case AIRCRAFT_FLYING: flying++; break;
            case AIRCRAFT_LANDED: landed++; break;
            case AIRCRAFT_DESTROYED: destroyed++; break;
        }
    }
    
    printf("\r[%.1fs] Flying: %d, Waiting: %d, Landed: %d, Destroyed: %d", 
           radar->simulation_time, flying, waiting, landed, destroyed);
    fflush(stdout);
}

int run_simulation(radar_t *radar)
{
    const float time_step = 0.1f;
    const float simulation_duration = 60.0f;
    
    radar->simulation_time = 0.0f;
    radar->running = 1;
    
    printf("Starting air traffic simulation...\n");
    printf("Simulation area: %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("Duration: %.0f seconds\n\n", simulation_duration);
    
    while (radar->simulation_time < simulation_duration && radar->running) {
        update_aircraft(radar, time_step);
        check_collisions(radar);
        print_status(radar);
        
        radar->simulation_time += time_step;
        sleep(1);
    }
    
    printf("\n\nSimulation completed after %.1f seconds\n", radar->simulation_time);
    return 0;
}

int main(int argc, char **argv)
{
    radar_t radar = {0};

    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    
    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments\n");
        print_usage();
        return 84;
    }
    
    if (load_script(argv[1], &radar) != 0)
        return 84;
        
    if (radar.aircraft_count == 0 && radar.tower_count == 0) {
        fprintf(stderr, "Error: No valid data in script file\n");
        return 84;
    }
    
    return run_simulation(&radar);
}