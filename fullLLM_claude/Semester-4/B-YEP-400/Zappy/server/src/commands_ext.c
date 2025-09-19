/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Extended command implementations
*/

#include "server.h"

void cmd_look(server_t *server, player_t *player)
{
    char response[2048] = "[ ";

    // Simple look implementation - just current tile for now
    int x = player->x;
    int y = player->y;

    // Add player to response
    strcat(response, "player");

    // Add resources on current tile
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (server->map[y][x].quantities[i] > 0) {
            switch (i) {
                case RESOURCE_FOOD: strcat(response, " food"); break;
                case RESOURCE_LINEMATE: strcat(response, " linemate"); break;
                case RESOURCE_DERAUMERE: strcat(response, " deraumere"); break;
                case RESOURCE_SIBUR: strcat(response, " sibur"); break;
                case RESOURCE_MENDIANE: strcat(response, " mendiane"); break;
                case RESOURCE_PHIRAS: strcat(response, " phiras"); break;
                case RESOURCE_THYSTAME: strcat(response, " thystame"); break;
            }
        }
    }

    strcat(response, " ]\n");
    send_response(player->fd, response);
}

void cmd_broadcast(server_t *server, player_t *player, char *message)
{
    char broadcast_msg[1024];

    // Send broadcast to all players
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->players[i] && server->players[i] != player) {
            int direction = calculate_sound_direction(
                player->x, player->y,
                server->players[i]->x, server->players[i]->y,
                server->width, server->height
            );

            snprintf(broadcast_msg, sizeof(broadcast_msg), "message %d, %s\n",
                     direction, message ? message : "");
            send_response(server->players[i]->fd, broadcast_msg);
        }
    }

    // Notify GUIs
    snprintf(broadcast_msg, sizeof(broadcast_msg), "pbc %d %s\n",
             player->player_id, message ? message : "");
    send_to_all_guis(server, broadcast_msg);

    send_response(player->fd, "ok\n");
}

void cmd_fork(server_t *server, player_t *player)
{
    if (server->egg_count < MAX_CLIENTS) {
        egg_t *egg = &server->eggs[server->egg_count];
        egg->x = player->x;
        egg->y = player->y;
        egg->player_id = player->player_id;
        egg->hatch_time = time(NULL) + (600 / server->freq); // 600/f seconds
        strncpy(egg->team_name, player->team_name, MAX_TEAM_NAME - 1);

        // Notify GUIs
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "enw %d %d %d %d\n",
                 server->egg_count, player->player_id, egg->x, egg->y);
        send_to_all_guis(server, gui_msg);

        // Notify GUIs about fork
        snprintf(gui_msg, sizeof(gui_msg), "pfk %d\n", player->player_id);
        send_to_all_guis(server, gui_msg);

        server->egg_count++;
    }

    send_response(player->fd, "ok\n");
}

void cmd_eject(server_t *server, player_t *player)
{
    int ejected = 0;

    // Eject all players on same tile
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->players[i] && server->players[i] != player &&
            server->players[i]->x == player->x && server->players[i]->y == player->y) {

            // Move player in direction of ejector
            int new_x = server->players[i]->x;
            int new_y = server->players[i]->y;

            switch (player->orientation) {
                case ORIENTATION_NORTH: new_y--; break;
                case ORIENTATION_EAST: new_x++; break;
                case ORIENTATION_SOUTH: new_y++; break;
                case ORIENTATION_WEST: new_x--; break;
            }

            // Handle wrapping
            if (new_x < 0) new_x = server->width - 1;
            if (new_x >= server->width) new_x = 0;
            if (new_y < 0) new_y = server->height - 1;
            if (new_y >= server->height) new_y = 0;

            server->players[i]->x = new_x;
            server->players[i]->y = new_y;

            // Notify ejected player
            char eject_msg[64];
            snprintf(eject_msg, sizeof(eject_msg), "eject: %d\n", player->orientation);
            send_response(server->players[i]->fd, eject_msg);

            ejected = 1;
        }
    }

    // Notify GUIs
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "pex %d\n", player->player_id);
    send_to_all_guis(server, gui_msg);

    send_response(player->fd, ejected ? "ok\n" : "ko\n");
}

static int get_resource_type(const char *object)
{
    if (!object) return -1;
    if (strcmp(object, "food") == 0) return RESOURCE_FOOD;
    if (strcmp(object, "linemate") == 0) return RESOURCE_LINEMATE;
    if (strcmp(object, "deraumere") == 0) return RESOURCE_DERAUMERE;
    if (strcmp(object, "sibur") == 0) return RESOURCE_SIBUR;
    if (strcmp(object, "mendiane") == 0) return RESOURCE_MENDIANE;
    if (strcmp(object, "phiras") == 0) return RESOURCE_PHIRAS;
    if (strcmp(object, "thystame") == 0) return RESOURCE_THYSTAME;
    return -1;
}

void cmd_take_object(server_t *server, player_t *player, char *object)
{
    int resource_type = get_resource_type(object);

    if (resource_type >= 0 &&
        server->map[player->y][player->x].quantities[resource_type] > 0) {

        server->map[player->y][player->x].quantities[resource_type]--;
        player->inventory[resource_type]++;

        // Notify GUIs
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "pgt %d %d\n", player->player_id, resource_type);
        send_to_all_guis(server, gui_msg);

        send_response(player->fd, "ok\n");
    } else {
        send_response(player->fd, "ko\n");
    }
}

void cmd_set_object(server_t *server, player_t *player, char *object)
{
    int resource_type = get_resource_type(object);

    if (resource_type >= 0 && player->inventory[resource_type] > 0) {
        player->inventory[resource_type]--;
        server->map[player->y][player->x].quantities[resource_type]++;

        // Notify GUIs
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "pdr %d %d\n", player->player_id, resource_type);
        send_to_all_guis(server, gui_msg);

        send_response(player->fd, "ok\n");
    } else {
        send_response(player->fd, "ko\n");
    }
}

void cmd_incantation(server_t *server, player_t *player)
{
    // Simple incantation - just level up for now
    player->level++;

    // Notify GUIs
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "pic %d %d %d %d\n",
             player->x, player->y, player->level - 1, player->player_id);
    send_to_all_guis(server, gui_msg);

    snprintf(gui_msg, sizeof(gui_msg), "pie %d %d 1\n", player->x, player->y);
    send_to_all_guis(server, gui_msg);

    char response[128];
    snprintf(response, sizeof(response), "Elevation underway\nCurrent level: %d\n", player->level);
    send_response(player->fd, response);
}

int calculate_sound_direction(int px, int py, int sx, int sy, int width, int height)
{
    (void)width; (void)height; // Simple implementation

    int dx = sx - px;
    int dy = sy - py;

    if (dx == 0 && dy == 0) return 0;
    if (dy < 0 && abs(dy) >= abs(dx)) return 1; // North
    if (dx > 0 && abs(dx) >= abs(dy)) return 2; // East
    if (dy > 0 && abs(dy) >= abs(dx)) return 3; // South
    if (dx < 0 && abs(dx) >= abs(dy)) return 4; // West

    return 1; // Default
}