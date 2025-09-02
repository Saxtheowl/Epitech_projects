/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** Client connection management
*/

#include "myftp.h"

int accept_new_client(server_t *server)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_fd;
    int index;

    if (server->client_count >= MAX_CLIENTS) {
        fprintf(stderr, "Warning: Maximum clients reached\n");
        return -1;
    }

    client_fd = accept(server->socket_fd, 
                      (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd < 0) {
        perror("accept");
        return -1;
    }

    index = server->client_count++;
    server->fds[index].fd = client_fd;
    server->fds[index].events = POLLIN;
    
    memset(&server->clients[index], 0, sizeof(client_t));
    server->clients[index].socket_fd = client_fd;
    server->clients[index].state = CLIENT_CONNECTED;
    server->clients[index].data_fd = -1;
    strcpy(server->clients[index].root_dir, server->root_path);
    strcpy(server->clients[index].current_dir, "/");
    server->clients[index].mode = MODE_ACTIVE;

    printf("New client connected from %s:%d\n", 
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    send_response(client_fd, 220, "Welcome to My FTP Server");
    return 0;
}

void disconnect_client(server_t *server, int index)
{
    if (index <= 0 || index >= server->client_count)
        return;

    printf("Client disconnected\n");

    close(server->fds[index].fd);
    if (server->clients[index].data_fd >= 0)
        close(server->clients[index].data_fd);

    for (int i = index; i < server->client_count - 1; i++) {
        server->fds[i] = server->fds[i + 1];
        server->clients[i] = server->clients[i + 1];
    }

    server->client_count--;
}

int handle_client_data(server_t *server, int index)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    char *line_end;
    int client_fd = server->fds[index].fd;
    client_t *client = &server->clients[index];

    bytes_received = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_received <= 0) {
        if (bytes_received == 0) {
            printf("Client disconnected\n");
        } else {
            perror("read");
        }
        return -1;
    }

    buffer[bytes_received] = '\0';
    
    if (client->buffer_pos + bytes_received >= BUFFER_SIZE - 1) {
        send_response(client_fd, 500, "Command line too long");
        client->buffer_pos = 0;
        return 0;
    }

    memcpy(client->buffer + client->buffer_pos, buffer, bytes_received);
    client->buffer_pos += bytes_received;
    client->buffer[client->buffer_pos] = '\0';

    while ((line_end = strstr(client->buffer, "\r\n")) != NULL) {
        *line_end = '\0';
        
        printf("Received command: %s\n", client->buffer);
        
        if (execute_command(server, index, client->buffer) < 0)
            return -1;

        int processed_len = line_end - client->buffer + 2;
        client->buffer_pos -= processed_len;
        memmove(client->buffer, line_end + 2, client->buffer_pos);
        client->buffer[client->buffer_pos] = '\0';
    }

    return 0;
}