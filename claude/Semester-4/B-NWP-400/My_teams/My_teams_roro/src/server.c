/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Server implementation
*/

#include "myteams.h"

static server_t server_instance;
static volatile sig_atomic_t server_running = 1;

void signal_handler(int sig)
{
    if (sig == SIGINT || sig == SIGTERM) {
        printf("\nServer shutting down...\n");
        save_data(&server_instance);
        server_running = 0;
    }
}

int init_server(int port)
{
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        return -1;
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return -1;
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }
    return server_fd;
}

void handle_new_connection(server_t *server)
{
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    new_socket = accept(server->socket, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept");
        return;
    }
    if (server->nb_clients >= MAX_CLIENTS) {
        close(new_socket);
        return;
    }
    server->clients[server->nb_clients].fd = new_socket;
    server->clients[server->nb_clients].logged_in = 0;
    server->clients[server->nb_clients].addr = address;
    memset(server->clients[server->nb_clients].uuid, 0, 37);
    memset(server->clients[server->nb_clients].name, 0, MAX_NAME_LENGTH + 1);
    server->nb_clients++;
}

void handle_client_message(server_t *server, int client_idx)
{
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(server->clients[client_idx].fd, buffer, BUFFER_SIZE);

    if (valread <= 0) {
        disconnect_client(server, client_idx);
        return;
    }
    buffer[valread - 1] = '\0';  // Remove newline
    process_command(server, client_idx, buffer);
}

void disconnect_client(server_t *server, int client_idx)
{
    if (server->clients[client_idx].logged_in) {
        user_t *user = get_user_by_name(server, server->clients[client_idx].name);
        if (user)
            user->is_logged_in = 0;
    }
    close(server->clients[client_idx].fd);
    for (int i = client_idx; i < server->nb_clients - 1; i++) {
        server->clients[i] = server->clients[i + 1];
    }
    server->nb_clients--;
}

void handle_clients(server_t *server)
{
    fd_set readfds;
    int max_sd, activity;
    struct timeval timeout;

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    while (server_running) {
        FD_ZERO(&readfds);
        FD_SET(server->socket, &readfds);
        max_sd = server->socket;
        for (int i = 0; i < server->nb_clients; i++) {
            int sd = server->clients[i].fd;
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd)
                max_sd = sd;
        }
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);
        if ((activity < 0) && (errno != EINTR)) {
            perror("select error");
        }
        if (FD_ISSET(server->socket, &readfds)) {
            handle_new_connection(server);
        }
        for (int i = 0; i < server->nb_clients; i++) {
            int sd = server->clients[i].fd;
            if (FD_ISSET(sd, &readfds)) {
                handle_client_message(server, i);
                break;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s port\n", argv[0]);
        fprintf(stderr, "       port is the port number on which the server socket listens.\n");
        return 84;
    }
    int port = atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        return 84;
    }
    memset(&server_instance, 0, sizeof(server_t));
    server_instance.socket = init_server(port);
    if (server_instance.socket == -1) {
        return 84;
    }
    load_data(&server_instance);
    printf("Server listening on port %d\n", port);
    handle_clients(&server_instance);
    close(server_instance.socket);
    return 0;
}