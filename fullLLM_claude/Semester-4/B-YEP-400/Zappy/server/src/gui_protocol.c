/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** GUI protocol implementation
*/

#include "server.h"

void gui_msz(server_t *server, client_t *client)
{
    char response[128];
    snprintf(response, sizeof(response), "msz %d %d\n", server->width, server->height);
    send_response(client->fd, response);
}

void gui_bct(server_t *server, client_t *client, int x, int y)
{
    if (x < 0 || x >= server->width || y < 0 || y >= server->height) {
        send_response(client->fd, "sbp\n");
        return;
    }

    char response[256];
    tile_t *tile = &server->map[y][x];
    snprintf(response, sizeof(response), "bct %d %d %d %d %d %d %d %d %d\n",
             x, y,
             tile->quantities[RESOURCE_FOOD],
             tile->quantities[RESOURCE_LINEMATE],
             tile->quantities[RESOURCE_DERAUMERE],
             tile->quantities[RESOURCE_SIBUR],
             tile->quantities[RESOURCE_MENDIANE],
             tile->quantities[RESOURCE_PHIRAS],
             tile->quantities[RESOURCE_THYSTAME]);
    send_response(client->fd, response);
}

void gui_mct(server_t *server, client_t *client)
{
    for (int y = 0; y < server->height; y++) {
        for (int x = 0; x < server->width; x++) {
            gui_bct(server, client, x, y);
        }
    }
}

void gui_tna(server_t *server, client_t *client)
{
    for (int i = 0; i < server->team_count; i++) {
        char response[128];
        snprintf(response, sizeof(response), "tna %s\n", server->teams[i].name);
        send_response(client->fd, response);
    }
}

void gui_pnw(server_t *server, client_t *client, player_t *player)
{
    (void)server;
    char response[256];
    snprintf(response, sizeof(response), "pnw #%d %d %d %d %d %s\n",
             player->player_id, player->x, player->y,
             player->orientation, player->level, player->team_name);
    send_response(client->fd, response);
}

void gui_ppo(server_t *server, client_t *client, int player_id)
{
    player_t *player = find_player_by_id(server, player_id);
    if (!player) {
        send_response(client->fd, "sbp\n");
        return;
    }

    char response[128];
    snprintf(response, sizeof(response), "ppo %d %d %d %d\n",
             player->player_id, player->x, player->y, player->orientation);
    send_response(client->fd, response);
}

void gui_plv(server_t *server, client_t *client, int player_id)
{
    player_t *player = find_player_by_id(server, player_id);
    if (!player) {
        send_response(client->fd, "sbp\n");
        return;
    }

    char response[64];
    snprintf(response, sizeof(response), "plv %d %d\n", player->player_id, player->level);
    send_response(client->fd, response);
}

void gui_pin(server_t *server, client_t *client, int player_id)
{
    player_t *player = find_player_by_id(server, player_id);
    if (!player) {
        send_response(client->fd, "sbp\n");
        return;
    }

    char response[256];
    snprintf(response, sizeof(response), "pin %d %d %d %d %d %d %d %d %d %d\n",
             player->player_id, player->x, player->y,
             player->inventory[RESOURCE_FOOD],
             player->inventory[RESOURCE_LINEMATE],
             player->inventory[RESOURCE_DERAUMERE],
             player->inventory[RESOURCE_SIBUR],
             player->inventory[RESOURCE_MENDIANE],
             player->inventory[RESOURCE_PHIRAS],
             player->inventory[RESOURCE_THYSTAME]);
    send_response(client->fd, response);
}