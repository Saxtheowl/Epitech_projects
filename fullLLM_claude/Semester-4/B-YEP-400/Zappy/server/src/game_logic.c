/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Game logic and map management
*/

#include "server.h"

static const double resource_densities[NUM_RESOURCES] = {
    0.5,   // FOOD
    0.3,   // LINEMATE
    0.15,  // DERAUMERE
    0.1,   // SIBUR
    0.1,   // MENDIANE
    0.08,  // PHIRAS
    0.05   // THYSTAME
};

void init_map(server_t *server)
{
    // Allocate map
    server->map = malloc(server->height * sizeof(tile_t *));
    for (int y = 0; y < server->height; y++) {
        server->map[y] = malloc(server->width * sizeof(tile_t));
        for (int x = 0; x < server->width; x++) {
            memset(&server->map[y][x], 0, sizeof(tile_t));
        }
    }
}

void spawn_resources(server_t *server)
{
    int total_tiles = server->width * server->height;

    // Calculate resource quantities based on map size and density
    for (int resource = 0; resource < NUM_RESOURCES; resource++) {
        int quantity = (int)(total_tiles * resource_densities[resource]);

        // Ensure at least one of each resource exists
        if (quantity < 1) {
            quantity = 1;
        }

        // Distribute resources randomly across the map
        for (int i = 0; i < quantity; i++) {
            int x, y;
            int attempts = 0;

            do {
                x = rand() % server->width;
                y = rand() % server->height;
                attempts++;
            } while (attempts < 1000); // Avoid infinite loop

            server->map[y][x].quantities[resource]++;
        }
    }
}

void update_game_state(server_t *server)
{
    time_t current_time = time(NULL);

    // Spawn resources every 20 time units
    double time_unit = 1.0 / server->freq;
    if (current_time - server->last_resource_spawn >= (20 * time_unit)) {
        spawn_resources(server);
        server->last_resource_spawn = current_time;
    }

    // Update player life units
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->players[i]) {
            update_player_life(server, server->players[i]);
        }
    }

    // Check for game end condition
    for (int i = 0; i < server->team_count; i++) {
        int level_8_players = 0;
        for (int j = 0; j < MAX_CLIENTS; j++) {
            if (server->players[j] &&
                strcmp(server->players[j]->team_name, server->teams[i].name) == 0 &&
                server->players[j]->level >= 8) {
                level_8_players++;
            }
        }

        if (level_8_players >= 6) {
            // Team wins
            char end_msg[256];
            snprintf(end_msg, sizeof(end_msg), "seg %s\n", server->teams[i].name);
            send_to_all_guis(server, end_msg);
            printf("Game ended: Team %s wins!\n", server->teams[i].name);
            server->running = 0;
            return;
        }
    }

    // Update eggs (hatching)
    for (int i = 0; i < server->egg_count; i++) {
        if (current_time >= server->eggs[i].hatch_time) {
            // Egg ready to hatch
            team_t *team = find_team(server, server->eggs[i].team_name);
            if (team && team->available_slots > 0) {
                char gui_msg[256];
                snprintf(gui_msg, sizeof(gui_msg), "eht %d\n", i);
                send_to_all_guis(server, gui_msg);
            }
        }
    }
}

player_t *create_player(server_t *server, char *team_name, int fd)
{
    team_t *team = find_team(server, team_name);
    if (!team || team->available_slots <= 0) {
        return NULL;
    }

    // Find available player slot
    int slot = -1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->players[i] == NULL) {
            slot = i;
            break;
        }
    }

    if (slot == -1) {
        return NULL;
    }

    player_t *player = malloc(sizeof(player_t));
    if (!player) {
        return NULL;
    }

    // Initialize player
    memset(player, 0, sizeof(player_t));
    player->x = rand() % server->width;
    player->y = rand() % server->height;
    player->level = 1;
    player->orientation = ORIENTATION_NORTH + (rand() % 4);
    player->life_units = 10;
    player->fd = fd;
    player->player_id = slot;
    player->last_action = time(NULL);
    player->incantating = 0;
    strncpy(player->team_name, team_name, MAX_TEAM_NAME - 1);

    // Give initial food
    player->inventory[RESOURCE_FOOD] = 10;

    // Update team
    team->connected_clients++;
    team->available_slots--;

    // Add to server
    server->players[slot] = player;
    server->player_count++;

    // Notify GUIs
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "pnw #%d %d %d %d %d %s\n",
             player->player_id, player->x, player->y,
             player->orientation, player->level, player->team_name);
    send_to_all_guis(server, gui_msg);

    return player;
}

void update_player_life(server_t *server, player_t *player)
{
    time_t current_time = time(NULL);
    double time_unit = 1.0 / server->freq;

    // Each life unit lasts 126 time units
    if (current_time - player->last_action >= (126 * time_unit)) {
        if (player->inventory[RESOURCE_FOOD] > 0) {
            player->inventory[RESOURCE_FOOD]--;
            player->life_units = 10; // Reset life units
        } else {
            player->life_units--;
            if (player->life_units <= 0) {
                // Player dies
                char gui_msg[256];
                snprintf(gui_msg, sizeof(gui_msg), "pdi %d\n", player->player_id);
                send_to_all_guis(server, gui_msg);

                disconnect_client(server, player->fd);
            }
        }
        player->last_action = current_time;
    }
}

team_t *find_team(server_t *server, const char *name)
{
    for (int i = 0; i < server->team_count; i++) {
        if (strcmp(server->teams[i].name, name) == 0) {
            return &server->teams[i];
        }
    }
    return NULL;
}

player_t *find_player_by_id(server_t *server, int player_id)
{
    if (player_id >= 0 && player_id < MAX_CLIENTS) {
        return server->players[player_id];
    }
    return NULL;
}