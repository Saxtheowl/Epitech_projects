/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Command line arguments parsing for AI client
*/

#include "zappy_ai.h"

void display_help(void)
{
    printf("USAGE: ./zappy_ai -p port -n name -h machine\n");
    printf("\tport\t\tis the port number\n");
    printf("\tname\t\tis the name of the team\n");
    printf("\tmachine\t\tis the name of the machine; localhost by default\n");
}

int parse_arguments(int argc, char **argv, ai_t *ai)
{
    int i = 1;

    if (argc < 2 || (argc == 2 && strcmp(argv[1], "-help") == 0)) {
        display_help();
        return -1;
    }
    
    ai->server_name = strdup("localhost");
    ai->port = -1;
    ai->team_name = NULL;
    
    while (i < argc) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc)
            ai->port = atoi(argv[++i]);
        else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
            ai->team_name = strdup(argv[++i]);
        else if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) {
            free(ai->server_name);
            ai->server_name = strdup(argv[++i]);
        }
        i++;
    }
    
    if (ai->port <= 0 || !ai->team_name) {
        free(ai->server_name);
        free(ai->team_name);
        return -1;
    }
    
    return 0;
}