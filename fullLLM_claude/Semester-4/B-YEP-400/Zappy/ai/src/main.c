/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Main AI client entry point
*/

#include "ai.h"

int main(int argc, char **argv)
{
    ai_client_t ai = {0};

    if (parse_ai_arguments(argc, argv, &ai) != 0) {
        print_ai_usage(argv[0]);
        return 84;
    }

    if (connect_to_server(&ai) != 0) {
        fprintf(stderr, "Failed to connect to server\n");
        return 84;
    }

    printf("AI connected to server %s:%d as team %s\n",
           ai.server_ip, ai.server_port, ai.team_name);

    run_ai_client(&ai);
    cleanup_ai_client(&ai);

    return 0;
}

int parse_ai_arguments(int argc, char **argv, ai_client_t *ai)
{
    if (argc != 7) {
        return -1;
    }

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-p") == 0) {
            ai->server_port = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-n") == 0) {
            ai->team_name = strdup(argv[i + 1]);
        } else if (strcmp(argv[i], "-h") == 0) {
            ai->server_ip = strdup(argv[i + 1]);
        } else {
            return -1;
        }
    }

    if (!ai->server_ip || ai->server_port <= 0 || !ai->team_name) {
        return -1;
    }

    // Initialize AI state
    ai->level = 1;
    ai->orientation = ORIENTATION_NORTH;
    ai->state = STATE_CONNECTING;
    ai->inventory[RESOURCE_FOOD] = 10; // Start with 10 food
    ai->life_units = 1260;

    return 0;
}

void print_ai_usage(char *program_name)
{
    printf("USAGE: %s -p port -n name -h machine\n", program_name);
    printf("\tport\tis the port number\n");
    printf("\tname\tis the name of the team\n");
    printf("\tmachine\tis the name of the machine; localhost by default\n");
}