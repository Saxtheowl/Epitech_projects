/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** Client management for FTP server
*/

#include "myftp.h"

int handle_new_client(server_t *server)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_socket;
    int client_idx;

    if (server->client_count >= MAX_CLIENTS) {
        return -1;
    }

    client_socket = accept(server->socket, (struct sockaddr *)&client_addr, &addr_len);
    if (client_socket == -1) {
        perror("accept");
        return -1;
    }

    client_idx = server->client_count;
    server->clients[client_idx].socket = client_socket;
    server->clients[client_idx].data_socket = -1;
    server->clients[client_idx].passive_socket = -1;
    server->clients[client_idx].authenticated = 0;
    server->clients[client_idx].user_valid = 0;
    server->clients[client_idx].passive_mode = 0;
    strcpy(server->clients[client_idx].home_dir, server->home_path);
    strcpy(server->clients[client_idx].current_dir, server->home_path);

    server->poll_fds[client_idx + 1].fd = client_socket;
    server->poll_fds[client_idx + 1].events = POLLIN;
    server->client_count++;

    send_response(client_socket, "220 FTP server ready.\r\n");
    printf("New client connected from %s\n", inet_ntoa(client_addr.sin_addr));

    return 0;
}

void handle_client_command(server_t *server, int client_idx)
{
    char buffer[BUFFER_SIZE];
    char command[CMD_SIZE];
    char *arg;
    int bytes_read;
    client_t *client = &server->clients[client_idx];

    bytes_read = read(client->socket, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        disconnect_client(server, client_idx);
        return;
    }

    buffer[bytes_read] = '\0';

    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }
    if (buffer[strlen(buffer) - 1] == '\r') {
        buffer[strlen(buffer) - 1] = '\0';
    }

    sscanf(buffer, "%s", command);
    arg = strchr(buffer, ' ');
    if (arg) {
        arg++;
    }

    printf("Client %d: %s\n", client_idx, buffer);
    printf("Command: '%s', Arg: '%s'\n", command, arg ? arg : "NULL");

    if (strcasecmp(command, "USER") == 0) {
        handle_user(client, arg);
    } else if (strcasecmp(command, "PASS") == 0) {
        handle_pass(client, arg);
    } else if (strcasecmp(command, "PWD") == 0) {
        handle_pwd(client);
    } else if (strcasecmp(command, "CWD") == 0) {
        handle_cwd(client, arg);
    } else if (strcasecmp(command, "LIST") == 0) {
        handle_list(client, arg);
    } else if (strcasecmp(command, "PASV") == 0) {
        handle_pasv(client);
    } else if (strcasecmp(command, "QUIT") == 0) {
        handle_quit(client);
        disconnect_client(server, client_idx);
    } else {
        send_response(client->socket, "502 Command not implemented.\r\n");
    }
}

void disconnect_client(server_t *server, int client_idx)
{
    printf("Client %d disconnected\n", client_idx);

    if (server->clients[client_idx].socket != -1) {
        close(server->clients[client_idx].socket);
    }
    if (server->clients[client_idx].data_socket != -1) {
        close(server->clients[client_idx].data_socket);
    }
    if (server->clients[client_idx].passive_socket != -1) {
        close(server->clients[client_idx].passive_socket);
    }

    for (int i = client_idx; i < server->client_count - 1; i++) {
        server->clients[i] = server->clients[i + 1];
        server->poll_fds[i + 1] = server->poll_fds[i + 2];
    }

    server->client_count--;
    server->poll_fds[server->client_count + 1].fd = -1;
}