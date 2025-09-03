/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Command processing and execution
*/

#include "zappy_server.h"

static void cmd_forward(server_t *server, client_t *client)
{
    player_t *player = client->player;
    int new_x = player->x;
    int new_y = player->y;

    if (!player) {
        send_to_client(client, "ko\n");
        return;
    }
    switch (player->orientation) {
        case 1:
            new_y = (new_y - 1 + server->height) % server->height;
            break;
        case 2:
            new_x = (new_x + 1) % server->width;
            break;
        case 3:
            new_y = (new_y + 1) % server->height;
            break;
        case 4:
            new_x = (new_x - 1 + server->width) % server->width;
            break;
    }
    player->x = new_x;
    player->y = new_y;
    send_to_client(client, "ok\n");
}

static void cmd_right(server_t *server, client_t *client)
{
    player_t *player = client->player;

    (void)server;
    if (!player) {
        send_to_client(client, "ko\n");
        return;
    }
    player->orientation = (player->orientation % 4) + 1;
    send_to_client(client, "ok\n");
}

static void cmd_left(server_t *server, client_t *client)
{
    player_t *player = client->player;

    (void)server;
    if (!player) {
        send_to_client(client, "ko\n");
        return;
    }
    player->orientation = ((player->orientation - 2 + 4) % 4) + 1;
    send_to_client(client, "ok\n");
}

static void cmd_look(server_t *server, client_t *client)
{
    player_t *player = client->player;
    char response[BUFFER_SIZE] = "[";
    int x = 0;
    int y = 0;
    int distance = 0;
    char tile_content[256];

    if (!player) {
        send_to_client(client, "ko\n");
        return;
    }
    for (distance = 0; distance <= player->level; distance++) {
        for (int i = -distance; i <= distance; i++) {
            x = player->x;
            y = player->y;
            switch (player->orientation) {
                case 1:
                    y = (y - distance + server->height) % server->height;
                    x = (x + i + server->width) % server->width;
                    break;
                case 2:
                    x = (x + distance) % server->width;
                    y = (y + i + server->height) % server->height;
                    break;
                case 3:
                    y = (y + distance) % server->height;
                    x = (x - i + server->width) % server->width;
                    break;
                case 4:
                    x = (x - distance + server->width) % server->width;
                    y = (y - i + server->height) % server->height;
                    break;
            }
            snprintf(tile_content, sizeof(tile_content), "%s",
                distance == 0 && i == 0 ? "player" : "");
            for (int res = 0; res < NB_RESOURCES; res++) {
                for (int count = 0; count < server->world[y][x].resources[res];
                    count++) {
                    if (strlen(tile_content) > 0)
                        strcat(tile_content, " ");
                    switch (res) {
                        case FOOD: strcat(tile_content, "food"); break;
                        case LINEMATE: strcat(tile_content, "linemate"); break;
                        case DERAUMERE: strcat(tile_content, "deraumere"); break;
                        case SIBUR: strcat(tile_content, "sibur"); break;
                        case MENDIANE: strcat(tile_content, "mendiane"); break;
                        case PHIRAS: strcat(tile_content, "phiras"); break;
                        case THYSTAME: strcat(tile_content, "thystame"); break;
                    }
                }
            }
            if (strlen(response) > 1)
                strcat(response, ",");
            strcat(response, tile_content);
        }
    }
    strcat(response, "]\n");
    send_to_client(client, response);
}

static void cmd_inventory(server_t *server, client_t *client)
{
    player_t *player = client->player;
    char response[BUFFER_SIZE];

    (void)server;
    if (!player) {
        send_to_client(client, "ko\n");
        return;
    }
    snprintf(response, sizeof(response),
        "[food %d,linemate %d,deraumere %d,sibur %d,mendiane %d,phiras %d,thystame %d]\n",
        player->inventory[FOOD], player->inventory[LINEMATE],
        player->inventory[DERAUMERE], player->inventory[SIBUR],
        player->inventory[MENDIANE], player->inventory[PHIRAS],
        player->inventory[THYSTAME]);
    send_to_client(client, response);
}

static void cmd_take(server_t *server, client_t *client, char *object)
{
    player_t *player = client->player;
    int resource_type = -1;
    tile_t *tile = NULL;

    if (!player || !object) {
        send_to_client(client, "ko\n");
        return;
    }
    if (strcmp(object, "food") == 0) resource_type = FOOD;
    else if (strcmp(object, "linemate") == 0) resource_type = LINEMATE;
    else if (strcmp(object, "deraumere") == 0) resource_type = DERAUMERE;
    else if (strcmp(object, "sibur") == 0) resource_type = SIBUR;
    else if (strcmp(object, "mendiane") == 0) resource_type = MENDIANE;
    else if (strcmp(object, "phiras") == 0) resource_type = PHIRAS;
    else if (strcmp(object, "thystame") == 0) resource_type = THYSTAME;
    if (resource_type == -1) {
        send_to_client(client, "ko\n");
        return;
    }
    tile = &server->world[player->y][player->x];
    if (tile->resources[resource_type] > 0) {
        tile->resources[resource_type]--;
        player->inventory[resource_type]++;
        send_to_client(client, "ok\n");
    } else {
        send_to_client(client, "ko\n");
    }
}

static void cmd_set(server_t *server, client_t *client, char *object)
{
    player_t *player = client->player;
    int resource_type = -1;
    tile_t *tile = NULL;

    if (!player || !object) {
        send_to_client(client, "ko\n");
        return;
    }
    if (strcmp(object, "food") == 0) resource_type = FOOD;
    else if (strcmp(object, "linemate") == 0) resource_type = LINEMATE;
    else if (strcmp(object, "deraumere") == 0) resource_type = DERAUMERE;
    else if (strcmp(object, "sibur") == 0) resource_type = SIBUR;
    else if (strcmp(object, "mendiane") == 0) resource_type = MENDIANE;
    else if (strcmp(object, "phiras") == 0) resource_type = PHIRAS;
    else if (strcmp(object, "thystame") == 0) resource_type = THYSTAME;
    if (resource_type == -1) {
        send_to_client(client, "ko\n");
        return;
    }
    tile = &server->world[player->y][player->x];
    if (player->inventory[resource_type] > 0) {
        player->inventory[resource_type]--;
        tile->resources[resource_type]++;
        send_to_client(client, "ok\n");
    } else {
        send_to_client(client, "ko\n");
    }
}

void execute_command(server_t *server, client_t *client, char *command)
{
    char *cmd = strtok(command, " \n");
    char *arg = strtok(NULL, " \n");

    if (!cmd)
        return;
    if (strcmp(cmd, "Forward") == 0)
        cmd_forward(server, client);
    else if (strcmp(cmd, "Right") == 0)
        cmd_right(server, client);
    else if (strcmp(cmd, "Left") == 0)
        cmd_left(server, client);
    else if (strcmp(cmd, "Look") == 0)
        cmd_look(server, client);
    else if (strcmp(cmd, "Inventory") == 0)
        cmd_inventory(server, client);
    else if (strcmp(cmd, "Take") == 0)
        cmd_take(server, client, arg);
    else if (strcmp(cmd, "Set") == 0)
        cmd_set(server, client, arg);
    else if (!client->player && server->nb_teams > 0) {
        team_t *team = find_team(server, cmd);
        if (team && team->connected_clients < team->max_clients) {
            client->player = create_player(cmd, client->fd);
            if (client->player) {
                add_player_to_team(server, client->player);
                char response[64];
                snprintf(response, sizeof(response), "%d\n%d %d\n",
                    team->max_clients - team->connected_clients,
                    server->width, server->height);
                send_to_client(client, response);
            } else {
                send_to_client(client, "ko\n");
            }
        } else {
            send_to_client(client, "ko\n");
        }
    } else {
        send_to_client(client, "ko\n");
    }
}