/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Main server loop and client handling
*/

#include "zappy_server.h"

void send_to_client(client_t *client, const char *message)
{
    if (client->fd != -1 && message) {
        write(client->fd, message, strlen(message));
    }
}

static void setup_fd_sets(server_t *server)
{
    FD_ZERO(&server->read_fds);
    FD_SET(server->server_fd, &server->read_fds);
    server->max_fd = server->server_fd;
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd != -1) {
            FD_SET(server->clients[i].fd, &server->read_fds);
            if (server->clients[i].fd > server->max_fd)
                server->max_fd = server->clients[i].fd;
        }
    }
}

void handle_new_connection(server_t *server)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_fd = 0;
    int i = 0;
    
    client_fd = accept(server->server_fd, (struct sockaddr *)&client_addr, 
        &addr_len);
    if (client_fd == -1)
        return;
    
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd == -1) {
            server->clients[i].fd = client_fd;
            server->clients[i].buffer_len = 0;
            server->clients[i].player = NULL;
            server->clients[i].commands = NULL;
            server->clients[i].nb_commands = 0;
            send_to_client(&server->clients[i], "WELCOME\n");
            return;
        }
    }
    close(client_fd);
}

void handle_client_data(server_t *server, int client_idx)
{
    char buffer[BUFFER_SIZE];
    int bytes_read = 0;
    client_t *client = &server->clients[client_idx];
    
    bytes_read = read(client->fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read <= 0) {
        close(client->fd);
        client->fd = -1;
        if (client->player) {
            cleanup_player(server, client->player);
            client->player = NULL;
        }
        return;
    }
    
    buffer[bytes_read] = '\0';
    if (client->buffer_len + bytes_read < BUFFER_SIZE) {
        strcat(client->buffer + client->buffer_len, buffer);
        client->buffer_len += bytes_read;
    }
    
    process_client_commands(server, client_idx);
}

int run_server(server_t *server)
{
    struct timeval timeout;
    int activity = 0;
    
    server->current_time = get_current_time();
    
    while (server->running) {
        setup_fd_sets(server);
        
        timeout.tv_sec = 0;
        timeout.tv_usec = 10000;
        
        activity = select(server->max_fd + 1, &server->read_fds, NULL, NULL, 
            &timeout);
        
        if (activity < 0 && errno != EINTR)
            return -1;
        
        server->current_time = get_current_time();
        
        if (FD_ISSET(server->server_fd, &server->read_fds))
            handle_new_connection(server);
        
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (server->clients[i].fd != -1 && 
                FD_ISSET(server->clients[i].fd, &server->read_fds))
                handle_client_data(server, i);
        }
        
        process_all_commands(server);
    }
    return 0;
}