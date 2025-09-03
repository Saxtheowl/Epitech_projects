/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Command line arguments parsing
*/

#include "zappy_server.h"

void display_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height");
    printf(" -n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\t\tis the port number\n");
    printf("\twidth\t\tis the width of the world\n");
    printf("\theight\t\tis the height of the world\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\t\tis the reciprocal of time unit for execution of actions\n");
}

static int parse_teams(char **argv, int *i, server_t *server)
{
    int team_idx = 0;

    while (argv[*i] && argv[*i][0] != '-' && team_idx < MAX_TEAMS) {
        strncpy(server->teams[team_idx].name, argv[*i], MAX_NAME_LEN - 1);
        server->teams[team_idx].name[MAX_NAME_LEN - 1] = '\0';
        team_idx++;
        (*i)++;
    }
    server->nb_teams = team_idx;
    (*i)--;
    return (team_idx > 0) ? 0 : -1;
}

static int set_team_clients(server_t *server, int clients_nb)
{
    int i = 0;

    for (i = 0; i < server->nb_teams; i++) {
        server->teams[i].max_clients = clients_nb;
        server->teams[i].connected_clients = 0;
        server->teams[i].players = NULL;
    }
    return 0;
}

int parse_arguments(int argc, char **argv, server_t *server)
{
    int i = 1;
    int clients_nb = 0;

    if (argc < 2 || (argc == 2 && strcmp(argv[1], "-help") == 0)) {
        display_help();
        return -1;
    }
    server->freq = DEFAULT_FREQ;
    while (i < argc) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc)
            server->port = atoi(argv[++i]);
        else if (strcmp(argv[i], "-x") == 0 && i + 1 < argc)
            server->width = atoi(argv[++i]);
        else if (strcmp(argv[i], "-y") == 0 && i + 1 < argc)
            server->height = atoi(argv[++i]);
        else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            i++;
            if (parse_teams(argv, &i, server) != 0)
                return -1;
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
            clients_nb = atoi(argv[++i]);
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
            server->freq = atoi(argv[++i]);
        i++;
    }
    if (server->port <= 0 || server->width <= 0 || server->height <= 0 ||
        server->nb_teams == 0 || clients_nb <= 0)
        return -1;
    return set_team_clients(server, clients_nb);
}