/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** World and resource management
*/

#include "zappy_server.h"

static double resource_densities[NB_RESOURCES] = {
    FOOD_DENSITY,
    LINEMATE_DENSITY,
    DERAUMERE_DENSITY,
    SIBUR_DENSITY,
    MENDIANE_DENSITY,
    PHIRAS_DENSITY,
    THYSTAME_DENSITY
};

void spawn_resources(server_t *server)
{
    int total_tiles = server->width * server->height;
    int resource_count = 0;
    int x = 0;
    int y = 0;
    int attempts = 0;

    srand(time(NULL));
    
    for (int res = 0; res < NB_RESOURCES; res++) {
        resource_count = (int)(total_tiles * resource_densities[res]);
        if (resource_count == 0)
            resource_count = 1;
        
        for (int i = 0; i < resource_count; i++) {
            attempts = 0;
            do {
                x = rand() % server->width;
                y = rand() % server->height;
                attempts++;
            } while (attempts < 100 && 
                server->world[y][x].resources[res] > 0);
            
            server->world[y][x].resources[res]++;
        }
    }
}

double get_current_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}