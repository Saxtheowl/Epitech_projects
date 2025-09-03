/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Player management functions
*/

#include "zappy_server.h"

static int generate_player_id(void)
{
    static int next_id = 1;
    
    return next_id++;
}

player_t *create_player(const char *team_name, int client_fd)
{
    player_t *player = malloc(sizeof(player_t));

    if (!player)
        return NULL;
    player->client_fd = client_fd;
    player->x = rand() % g_server->width;
    player->y = rand() % g_server->height;
    player->orientation = (rand() % 4) + 1;
    player->level = 1;
    player->life_units = 1260.0;
    player->team_name = strdup(team_name);
    player->id = generate_player_id();
    player->next = NULL;
    memset(player->inventory, 0, sizeof(player->inventory));
    player->inventory[FOOD] = 10;
    return player;
}

void add_player_to_team(server_t *server, player_t *player)
{
    team_t *team = find_team(server, player->team_name);

    if (!team)
        return;
    player->next = team->players;
    team->players = player;
    team->connected_clients++;
}

team_t *find_team(server_t *server, const char *team_name)
{
    int i = 0;

    for (i = 0; i < server->nb_teams; i++) {
        if (strcmp(server->teams[i].name, team_name) == 0)
            return &server->teams[i];
    }
    return NULL;
}

static void remove_player_from_team(server_t *server, player_t *player)
{
    team_t *team = find_team(server, player->team_name);
    player_t *current = NULL;
    player_t *prev = NULL;

    if (!team || !team->players)
        return;
    if (team->players == player) {
        team->players = player->next;
        team->connected_clients--;
        return;
    }
    prev = team->players;
    current = team->players->next;
    while (current) {
        if (current == player) {
            prev->next = current->next;
            team->connected_clients--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void cleanup_player(server_t *server, player_t *player)
{
    if (!player)
        return;
    remove_player_from_team(server, player);
    free(player->team_name);
    free(player);
}