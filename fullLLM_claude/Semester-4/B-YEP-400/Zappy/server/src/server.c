/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Core server functionality
*/

#include "server.h"

int init_server(server_t *server)
{
    // Initialize file descriptor sets
    FD_ZERO(&server->master_fds);
    FD_ZERO(&server->read_fds);

    // Setup socket
    if (setup_socket(server) != 0) {
        return -1;
    }

    // Initialize map and game state
    init_map(server);

    // Initialize timing
    server->game_start = time(NULL);
    server->last_resource_spawn = server->game_start;
    server->running = 1;

    // Initialize client array
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i].fd = -1;
        server->clients[i].type = CLIENT_UNASSIGNED;
        server->players[i] = NULL;
    }

    server->player_count = 0;
    server->egg_count = 0;

    // Spawn initial resources
    spawn_resources(server);

    return 0;
}

void run_server(server_t *server)
{
    struct timeval timeout;
    time_t last_update = time(NULL);

    while (server->running) {
        server->read_fds = server->master_fds;

        // Set timeout for select
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; // 100ms

        int activity = select(server->max_fd + 1, &server->read_fds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR) {
            perror("select error");
            break;
        }

        // Handle new connections
        if (FD_ISSET(server->server_fd, &server->read_fds)) {
            handle_new_connection(server);
        }

        // Handle client data
        for (int i = 0; i <= server->max_fd; i++) {
            if (i != server->server_fd && FD_ISSET(i, &server->read_fds)) {
                handle_client_data(server, i);
            }
        }

        // Update game state periodically
        time_t current_time = time(NULL);
        if (current_time - last_update >= 1) { // Update every second
            update_game_state(server);
            last_update = current_time;
        }
    }
}

void cleanup_server(server_t *server)
{
    // Close all client connections
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd != -1) {
            close(server->clients[i].fd);
        }
        if (server->players[i]) {
            free(server->players[i]);
        }
    }

    // Close server socket
    if (server->server_fd != -1) {
        close(server->server_fd);
    }

    // Free map
    if (server->map) {
        for (int y = 0; y < server->height; y++) {
            free(server->map[y]);
        }
        free(server->map);
    }

    printf("Server shutdown complete\n");
}