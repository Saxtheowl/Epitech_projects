/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Command line argument parsing
*/

#include "server.h"

static int parse_teams(char **argv, int *i, server_t *server)
{
    int team_count = 0;

    while (argv[*i] && argv[*i][0] != '-' && team_count < MAX_TEAMS) {
        strncpy(server->teams[team_count].name, argv[*i], MAX_TEAM_NAME - 1);
        server->teams[team_count].name[MAX_TEAM_NAME - 1] = '\0';
        server->teams[team_count].max_clients = server->max_clients_per_team;
        server->teams[team_count].connected_clients = 0;
        server->teams[team_count].available_slots = server->max_clients_per_team;
        team_count++;
        (*i)++;
    }
    (*i)--;
    server->team_count = team_count;
    return team_count > 0 ? 0 : -1;
}

int parse_arguments(int argc, char **argv, server_t *server)
{
    int i;
    int has_port = 0, has_width = 0, has_height = 0, has_names = 0, has_clients = 0;

    // Default values
    server->freq = 100;
    server->max_clients_per_team = 1;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            server->port = atoi(argv[++i]);
            has_port = 1;
        } else if (strcmp(argv[i], "-x") == 0 && i + 1 < argc) {
            server->width = atoi(argv[++i]);
            has_width = 1;
        } else if (strcmp(argv[i], "-y") == 0 && i + 1 < argc) {
            server->height = atoi(argv[++i]);
            has_height = 1;
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            i++;
            if (parse_teams(argv, &i, server) != 0)
                return -1;
            has_names = 1;
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            server->max_clients_per_team = atoi(argv[++i]);
            has_clients = 1;
            // Update all teams with new client count
            for (int j = 0; j < server->team_count; j++) {
                server->teams[j].max_clients = server->max_clients_per_team;
                server->teams[j].available_slots = server->max_clients_per_team;
            }
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            server->freq = atoi(argv[++i]);
        } else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            return -1;
        }
    }

    if (!has_port || !has_width || !has_height || !has_names || !has_clients) {
        fprintf(stderr, "Missing required arguments\n");
        return -1;
    }

    if (server->port <= 0 || server->width <= 0 || server->height <= 0 ||
        server->max_clients_per_team <= 0 || server->freq <= 0) {
        fprintf(stderr, "Invalid argument values\n");
        return -1;
    }

    return 0;
}