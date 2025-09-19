/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Server core functionality
*/

#include "myteams.h"

int init_server(server_t *server, int port)
{
    struct sockaddr_in addr;
    int opt = 1;

    memset(server, 0, sizeof(server_t));
    server->port = port;
    server->running = true;

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
    addr.sin_port = htons(port);

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

    // Initialize file descriptor sets
    FD_ZERO(&server->master_fds);
    FD_SET(server->server_fd, &server->master_fds);
    server->max_fd = server->server_fd;

    // Initialize client array
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i].socket_fd = -1;
        server->clients[i].is_authenticated = false;
        memset(server->clients[i].user_uuid, 0, UUID_STR_LEN);
    }

    return 0;
}

void run_server(server_t *server)
{
    struct timeval timeout;

    while (server->running) {
        server->read_fds = server->master_fds;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int activity = select(server->max_fd + 1, &server->read_fds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR) {
            perror("select error");
            break;
        }

        if (activity > 0) {
            // Check for new connection
            if (FD_ISSET(server->server_fd, &server->read_fds)) {
                handle_new_connection(server);
            }

            // Check existing clients for data
            for (int fd = 0; fd <= server->max_fd; fd++) {
                if (fd != server->server_fd && FD_ISSET(fd, &server->read_fds)) {
                    handle_client_data(server, fd);
                }
            }
        }
    }
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

    // Find available client slot
    int slot = -1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd == -1) {
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
    server->clients[slot].socket_fd = client_fd;
    server->clients[slot].is_authenticated = false;
    server->clients[slot].buffer_pos = 0;
    server->clients[slot].context.type = CONTEXT_NONE;
    memset(server->clients[slot].user_uuid, 0, UUID_STR_LEN);
    memset(server->clients[slot].context.team_uuid, 0, UUID_STR_LEN);
    memset(server->clients[slot].context.channel_uuid, 0, UUID_STR_LEN);
    memset(server->clients[slot].context.thread_uuid, 0, UUID_STR_LEN);

    // Add to master set
    FD_SET(client_fd, &server->master_fds);
    if (client_fd > server->max_fd) {
        server->max_fd = client_fd;
    }

    printf("New client connected (fd: %d)\n", client_fd);
}

void handle_client_data(server_t *server, int client_fd)
{
    client_t *client = find_client_by_fd(server, client_fd);
    if (!client) {
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes_read <= 0) {
        if (bytes_read == 0) {
            printf("Client disconnected (fd: %d)\n", client_fd);
        } else {
            perror("recv failed");
        }
        disconnect_client(server, client_fd);
        return;
    }

    buffer[bytes_read] = '\0';

    // Add to client buffer
    int remaining = BUFFER_SIZE - client->buffer_pos - 1;
    if (bytes_read > remaining) {
        bytes_read = remaining;
    }

    strncat(client->buffer + client->buffer_pos, buffer, bytes_read);
    client->buffer_pos += bytes_read;

    // Process complete commands (lines ending with \n)
    char *line_start = client->buffer;
    char *line_end;

    while ((line_end = strchr(line_start, '\n')) != NULL) {
        *line_end = '\0';

        if (strlen(line_start) > 0) {
            process_command(server, client, line_start);
        }

        line_start = line_end + 1;
    }

    // Move remaining data to beginning of buffer
    if (line_start != client->buffer) {
        memmove(client->buffer, line_start, strlen(line_start) + 1);
        client->buffer_pos = strlen(client->buffer);
    }
}

void disconnect_client(server_t *server, int client_fd)
{
    client_t *client = find_client_by_fd(server, client_fd);
    if (client && client->is_authenticated) {
        // Mark user as disconnected
        user_t *user = find_user_by_uuid(server, client->user_uuid);
        if (user) {
            user->is_connected = false;
        }
    }

    // Remove from master set
    FD_CLR(client_fd, &server->master_fds);
    close(client_fd);

    // Clear client slot
    if (client) {
        client->socket_fd = -1;
        client->is_authenticated = false;
        memset(client->user_uuid, 0, UUID_STR_LEN);
    }

    // Update max_fd if necessary
    if (client_fd == server->max_fd) {
        for (int i = server->max_fd - 1; i >= 0; i--) {
            if (FD_ISSET(i, &server->master_fds)) {
                server->max_fd = i;
                break;
            }
        }
    }
}

void cleanup_server(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd != -1) {
            close(server->clients[i].socket_fd);
        }
    }

    if (server->server_fd != -1) {
        close(server->server_fd);
    }
}