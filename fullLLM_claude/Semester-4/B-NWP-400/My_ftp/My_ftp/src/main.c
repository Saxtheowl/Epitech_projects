/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** Main function for FTP server
*/

#include "myftp.h"

void print_usage(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory for the Anonymous user\n");
}

int main(int argc, char **argv)
{
    server_t server;
    int port;

    if (argc == 2 && strcmp(argv[1], "help") == 0) {
        print_usage();
        return 0;
    }

    if (argc != 3) {
        print_usage();
        return 84;
    }

    port = atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        return 84;
    }

    if (init_server(&server, port, argv[2]) == -1) {
        return 84;
    }

    printf("FTP Server started on port %d\n", port);
    printf("Home directory: %s\n", argv[2]);

    if (run_server(&server) == -1) {
        cleanup_server(&server);
        return 84;
    }

    cleanup_server(&server);
    return 0;
}