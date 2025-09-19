/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Command processing and implementation
*/

#include "server.h"

static const char *resource_names[NUM_RESOURCES] __attribute__((unused)) = {
    "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"
};

int process_command(server_t *server, client_t *client, char *command)
{
    char *cmd = strtok(command, " \t\n");
    if (!cmd) {
        return 0;
    }

    // Handle initial team assignment for AI clients
    if (client->type == CLIENT_UNASSIGNED) {
        if (strcmp(cmd, "GRAPHIC") == 0) {
            // GUI client
            client->type = CLIENT_GUI;
            send_response(client->fd, "WELCOME\n");
            return 0;
        } else {
            // AI client trying to join team
            team_t *team = find_team(server, cmd);
            if (!team) {
                send_response(client->fd, "ko\n");
                return -1;
            }

            if (team->available_slots <= 0) {
                send_response(client->fd, "ko\n");
                return -1;
            }

            player_t *player = create_player(server, cmd, client->fd);
            if (!player) {
                send_response(client->fd, "ko\n");
                return -1;
            }

            client->type = CLIENT_AI;
            client->player = player;

            // Send connection response
            char response[256];
            snprintf(response, sizeof(response), "%d\n%d %d\n",
                     team->available_slots, server->width, server->height);
            send_response(client->fd, response);
            return 0;
        }
    }

    // Handle AI commands
    if (client->type == CLIENT_AI && client->player) {
        if (strcmp(cmd, "Forward") == 0) {
            cmd_forward(server, client->player);
        } else if (strcmp(cmd, "Right") == 0) {
            cmd_right(server, client->player);
        } else if (strcmp(cmd, "Left") == 0) {
            cmd_left(server, client->player);
        } else if (strcmp(cmd, "Look") == 0) {
            cmd_look(server, client->player);
        } else if (strcmp(cmd, "Inventory") == 0) {
            cmd_inventory(server, client->player);
        } else if (strcmp(cmd, "Broadcast") == 0) {
            char *message = strtok(NULL, "\n");
            cmd_broadcast(server, client->player, message ? message : "");
        } else if (strcmp(cmd, "Connect_nbr") == 0) {
            cmd_connect_nbr(server, client->player);
        } else if (strcmp(cmd, "Fork") == 0) {
            cmd_fork(server, client->player);
        } else if (strcmp(cmd, "Eject") == 0) {
            cmd_eject(server, client->player);
        } else if (strcmp(cmd, "Take") == 0) {
            char *object = strtok(NULL, " \t\n");
            cmd_take_object(server, client->player, object);
        } else if (strcmp(cmd, "Set") == 0) {
            char *object = strtok(NULL, " \t\n");
            cmd_set_object(server, client->player, object);
        } else if (strcmp(cmd, "Incantation") == 0) {
            cmd_incantation(server, client->player);
        } else {
            send_response(client->fd, "ko\n");
        }
    }
    // Handle GUI commands
    else if (client->type == CLIENT_GUI) {
        if (strcmp(cmd, "msz") == 0) {
            gui_msz(server, client);
        } else if (strcmp(cmd, "bct") == 0) {
            char *x_str = strtok(NULL, " \t");
            char *y_str = strtok(NULL, " \t");
            if (x_str && y_str) {
                gui_bct(server, client, atoi(x_str), atoi(y_str));
            }
        } else if (strcmp(cmd, "mct") == 0) {
            gui_mct(server, client);
        } else if (strcmp(cmd, "tna") == 0) {
            gui_tna(server, client);
        } else if (strcmp(cmd, "ppo") == 0) {
            char *player_str = strtok(NULL, " \t");
            if (player_str && player_str[0] == '#') {
                gui_ppo(server, client, atoi(player_str + 1));
            }
        } else if (strcmp(cmd, "plv") == 0) {
            char *player_str = strtok(NULL, " \t");
            if (player_str && player_str[0] == '#') {
                gui_plv(server, client, atoi(player_str + 1));
            }
        } else if (strcmp(cmd, "pin") == 0) {
            char *player_str = strtok(NULL, " \t");
            if (player_str && player_str[0] == '#') {
                gui_pin(server, client, atoi(player_str + 1));
            }
        } else if (strcmp(cmd, "sgt") == 0) {
            char response[64];
            snprintf(response, sizeof(response), "sgt %d\n", server->freq);
            send_response(client->fd, response);
        } else if (strcmp(cmd, "sst") == 0) {
            char *freq_str = strtok(NULL, " \t");
            if (freq_str) {
                server->freq = atoi(freq_str);
                char response[64];
                snprintf(response, sizeof(response), "sst %d\n", server->freq);
                send_response(client->fd, response);
            }
        } else {
            send_response(client->fd, "suc\n");
        }
    }

    return 0;
}

void cmd_forward(server_t *server, player_t *player)
{
    int new_x = player->x;
    int new_y = player->y;

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

    player->x = new_x;
    player->y = new_y;

    send_response(player->fd, "ok\n");

    // Notify GUIs
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "ppo %d %d %d %d\n",
             player->player_id, player->x, player->y, player->orientation);
    send_to_all_guis(server, gui_msg);
}

void cmd_right(server_t *server, player_t *player)
{
    player->orientation++;
    if (player->orientation > ORIENTATION_WEST) {
        player->orientation = ORIENTATION_NORTH;
    }

    send_response(player->fd, "ok\n");

    // Notify GUIs
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "ppo %d %d %d %d\n",
             player->player_id, player->x, player->y, player->orientation);
    send_to_all_guis(server, gui_msg);
}

void cmd_left(server_t *server, player_t *player)
{
    player->orientation--;
    if (player->orientation < ORIENTATION_NORTH) {
        player->orientation = ORIENTATION_WEST;
    }

    send_response(player->fd, "ok\n");

    // Notify GUIs
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "ppo %d %d %d %d\n",
             player->player_id, player->x, player->y, player->orientation);
    send_to_all_guis(server, gui_msg);
}

void cmd_inventory(server_t *server, player_t *player)
{
    (void)server;
    char response[512];
    snprintf(response, sizeof(response),
             "[ food %d, linemate %d, deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d ]\n",
             player->inventory[0], player->inventory[1], player->inventory[2],
             player->inventory[3], player->inventory[4], player->inventory[5],
             player->inventory[6]);
    send_response(player->fd, response);
}

void cmd_connect_nbr(server_t *server, player_t *player)
{
    team_t *team = find_team(server, player->team_name);
    char response[64];
    snprintf(response, sizeof(response), "%d\n", team ? team->available_slots : 0);
    send_response(player->fd, response);
}