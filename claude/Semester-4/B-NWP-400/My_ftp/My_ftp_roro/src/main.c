/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** Main entry point for FTP server
*/

#include "myftp.h"

void display_help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("    port is the port number on which the server socket listens\n");
    printf("    path is the path to the home directory for the Anonymous user\n");
}

static int validate_arguments(int argc, char **argv)
{
    int port;
    struct stat st;

    if (argc != 3) {
        display_help();
        return -1;
    }

    port = atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Error: Invalid port number\n");
        return -1;
    }

    if (stat(argv[2], &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: Invalid directory path\n");
        return -1;
    }

    return port;
}

int main(int argc, char **argv)
{
    server_t server;
    int port;

    if (argc == 2 && strcmp(argv[1], "help") == 0) {
        display_help();
        return 0;
    }

    port = validate_arguments(argc, argv);
    if (port < 0)
        return 84;

    if (init_server(&server, port, argv[2]) < 0) {
        fprintf(stderr, "Error: Failed to initialize server\n");
        return 84;
    }

    printf("FTP server listening on port %d\n", port);
    printf("Root directory: %s\n", argv[2]);

    if (run_server(&server) < 0) {
        fprintf(stderr, "Error: Server failed\n");
        cleanup_server(&server);
        return 84;
    }

    cleanup_server(&server);
    return 0;
}