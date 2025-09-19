/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Client main entry point
*/

#include "myteams.h"

void print_client_usage(char *program_name)
{
    printf("USAGE: %s ip port\n", program_name);
    printf("\tip\tis the server ip address\n");
    printf("\tport\tis the server port\n");
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        print_client_usage(argv[0]);
        return 84;
    }

    int port = atoi(argv[2]);
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        return 84;
    }

    int server_fd = init_client(argv[1], port);
    if (server_fd < 0) {
        fprintf(stderr, "Failed to connect to server\n");
        return 84;
    }

    printf("Connected to server %s:%d\n", argv[1], port);
    printf("Type /help for available commands\n");

    run_client(server_fd);
    cleanup_client(server_fd);

    return 0;
}