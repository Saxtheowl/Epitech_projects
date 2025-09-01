/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   Entry point
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "ftp.h"

static int parse_args(int ac, char **av, int *port, char *home, size_t cap)
{
    struct stat st;

    if (ac != 3) {
        fprintf(stdout, "USAGE: ./myftp port path\n");
        fprintf(stdout, "port is the port number on which the server socket listens\n");
        fprintf(stdout, "path is the path to the home directory for the Anonymous user\n");
        return -1;
    }
    *port = atoi(av[1]);
    if (*port <= 0)
        return -1;
    if (stat(av[2], &st) != 0 || !S_ISDIR(st.st_mode))
        return -1;
    my_strcpy(home, av[2], cap);
    return 0;
}

int main(int ac, char **av)
{
    int port = 0;
    char home[512];
    server_t srv;

    if (parse_args(ac, av, &port, home, sizeof(home)) != 0)
        return 84;
    if (server_init(&srv, port, home) != 0)
        return 84;
    server_run(&srv);
    server_close(&srv);
    return 0;
}
