/*
** EPITECH PROJECT, 2025
** My_teams_roro
** File description:
**   Server entry
*/

#include <stdio.h>
#include <stdlib.h>
#include "myteams.h"

int main(int ac, char **av)
{
    int port = 0;
    if (ac == 2 && ((my_strlen(av[1]) == 6 && av[1][0] == '-' && av[1][1] == '-' && av[1][2] == 'h')
        || (av[1][0] == '-' && av[1][1] == '-' && av[1][2] == 'h' && av[1][3] == 'e' && av[1][4] == 'l' && av[1][5] == 'p' && av[1][6] == '\0'))) {
        printf("USAGE: ./myteams_server port\n\n");
        printf("port is the port number on which the server socket listens.\n");
        return 0;
    }
    if (ac != 2 || parse_int(av[1], &port) != 0)
        return 84;
    if (run_server(port) != 0)
        return 84;
    return 0;
}
