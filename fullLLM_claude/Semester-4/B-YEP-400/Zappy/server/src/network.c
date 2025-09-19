/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Network handling functions
*/

#include "server.h"

int setup_socket(server_t *server)
{
    struct sockaddr_in addr;
    int opt = 1;

    // Create socket
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd == -1) {
        perror("socket failed");
        return -1;
    }

    // Set socket options
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server->server_fd);
        return -1;
    }

    // Configure address
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(server->port);

    // Bind socket
    if (bind(server->server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        close(server->server_fd);
        return -1;
    }

    // Listen for connections
    if (listen(server->server_fd, 10) < 0) {
        perror("listen failed");
        close(server->server_fd);
        return -1;
    }

    // Add server socket to master set
    FD_SET(server->server_fd, &server->master_fds);
    server->max_fd = server->server_fd;

    return 0;
}

void handle_new_connection(server_t *server)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_fd;

    client_fd = accept(server->server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd < 0) {
        perror("accept failed");
        return;
    }

    // Find available slot
    int slot = -1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd == -1) {
            slot = i;
            break;
        }
    }

    if (slot == -1) {
        printf("Server full, rejecting connection\n");
        close(client_fd);
        return;
    }

    // Initialize client
    server->clients[slot].fd = client_fd;
    server->clients[slot].type = CLIENT_UNASSIGNED;
    server->clients[slot].buffer_pos = 0;
    server->clients[slot].player = NULL;
    memset(server->clients[slot].buffer, 0, BUFFER_SIZE);

    // Add to master set
    FD_SET(client_fd, &server->master_fds);
    if (client_fd > server->max_fd) {
        server->max_fd = client_fd;
    }

    // Send welcome message
    send_response(client_fd, "WELCOME\n");

    printf("New connection from %s:%d (fd: %d)\n",
           inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port),
           client_fd);
}

void handle_client_data(server_t *server, int client_fd)
{
    client_t *client = NULL;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Find client
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd == client_fd) {
            client = &server->clients[i];
            break;
        }
    }

    if (!client) {
        return;
    }

    bytes_read = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_read <= 0) {
        disconnect_client(server, client_fd);
        return;
    }

    buffer[bytes_read] = '\0';

    // Add to client buffer
    int remaining = BUFFER_SIZE - client->buffer_pos - 1;
    if (bytes_read <= remaining) {
        strcat(client->buffer, buffer);
        client->buffer_pos += bytes_read;
    } else {
        // Buffer overflow, disconnect client
        disconnect_client(server, client_fd);
        return;
    }

    // Process complete commands (ended with \n)
    char *line;
    char *saveptr;
    char temp_buffer[BUFFER_SIZE];
    strcpy(temp_buffer, client->buffer);

    line = strtok_r(temp_buffer, "\n", &saveptr);
    int processed_length = 0;

    while (line) {
        processed_length += strlen(line) + 1;
        if (process_command(server, client, line) != 0) {
            disconnect_client(server, client_fd);
            return;
        }
        line = strtok_r(NULL, "\n", &saveptr);
    }

    // Remove processed commands from buffer
    if (processed_length > 0) {
        memmove(client->buffer, client->buffer + processed_length,
                client->buffer_pos - processed_length + 1);
        client->buffer_pos -= processed_length;
    }
}

void disconnect_client(server_t *server, int client_fd)
{
    client_t *client = NULL;

    // Find and cleanup client
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd == client_fd) {
            client = &server->clients[i];
            break;
        }
    }

    if (!client) {
        return;
    }

    printf("Client disconnected (fd: %d)\n", client_fd);

    // Cleanup player if exists
    if (client->type == CLIENT_AI && client->player) {
        // Notify GUIs about player disconnection
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "pdi %d\n", client->player->player_id);
        send_to_all_guis(server, gui_msg);

        // Free team slot
        team_t *team = find_team(server, client->player->team_name);
        if (team) {
            team->connected_clients--;
            team->available_slots++;
        }

        // Remove from players array
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (server->players[i] == client->player) {
                server->players[i] = NULL;
                break;
            }
        }

        free(client->player);
        server->player_count--;
    }

    // Remove from file descriptor sets
    FD_CLR(client_fd, &server->master_fds);
    close(client_fd);

    // Reset client slot
    client->fd = -1;
    client->type = CLIENT_UNASSIGNED;
    client->player = NULL;
    client->buffer_pos = 0;
}

void send_response(int fd, const char *response)
{
    if (fd > 0 && response) {
        send(fd, response, strlen(response), MSG_NOSIGNAL);
    }
}

void send_to_all_guis(server_t *server, const char *message)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd != -1 && server->clients[i].type == CLIENT_GUI) {
            send_response(server->clients[i].fd, message);
        }
    }
}