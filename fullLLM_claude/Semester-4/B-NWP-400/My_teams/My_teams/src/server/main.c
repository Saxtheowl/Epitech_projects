/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Server main entry point
*/

#include "myteams.h"

static server_t g_server;

void signal_handler(int sig)
{
    (void)sig;
    printf("\nSaving data and shutting down server...\n");
    save_data(&g_server);
    g_server.running = false;
}

void print_server_usage(char *program_name)
{
    printf("USAGE: %s port\n", program_name);
    printf("\tport\tis the port number for the server\n");
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        print_server_usage(argv[0]);
        return 84;
    }

    int port = atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        return 84;
    }

    // Setup signal handler for clean shutdown
    signal(SIGINT, signal_handler);

    // Initialize server
    if (init_server(&g_server, port) != 0) {
        fprintf(stderr, "Failed to initialize server\n");
        return 84;
    }

    printf("Server started on port %d\n", port);

    // Load existing data
    load_data(&g_server);

    // Run server main loop
    run_server(&g_server);

    // Cleanup
    cleanup_server(&g_server);
    return 0;
}