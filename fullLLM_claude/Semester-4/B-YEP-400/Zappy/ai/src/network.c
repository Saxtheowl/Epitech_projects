/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Network communication functions
*/

#include "ai.h"

int connect_to_server(ai_client_t *ai)
{
    struct sockaddr_in server_addr;

    ai->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ai->socket_fd < 0) {
        perror("socket");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(ai->server_port);

    if (inet_pton(AF_INET, ai->server_ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(ai->socket_fd);
        return -1;
    }

    if (connect(ai->socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(ai->socket_fd);
        return -1;
    }

    // Send team name to join
    if (send_command(ai, ai->team_name) < 0) {
        close(ai->socket_fd);
        return -1;
    }

    // Receive welcome message
    char response[BUFFER_SIZE];
    if (receive_response(ai, response, sizeof(response)) < 0) {
        close(ai->socket_fd);
        return -1;
    }

    // Parse welcome response: "client_slots\nwidth height\n"
    char *line1 = strtok(response, "\n");
    char *line2 = strtok(NULL, "\n");

    if (line1 && line2) {
        ai->client_slots = atoi(line1);
        sscanf(line2, "%d %d", &ai->map_width, &ai->map_height);
        ai->connected = true;
        ai->state = STATE_EXPLORING;
    }

    return 0;
}

int send_command(ai_client_t *ai, const char *command)
{
    size_t len = strlen(command);
    ssize_t sent = send(ai->socket_fd, command, len, 0);
    if (sent < 0) {
        perror("send");
        return -1;
    }

    // Send newline
    sent = send(ai->socket_fd, "\n", 1, 0);
    if (sent < 0) {
        perror("send");
        return -1;
    }

    return 0;
}

int receive_response(ai_client_t *ai, char *response, size_t size)
{
    memset(response, 0, size);
    ssize_t received = recv(ai->socket_fd, response, size - 1, 0);
    if (received <= 0) {
        if (received == 0) {
            printf("Server disconnected\n");
        } else {
            perror("recv");
        }
        return -1;
    }

    // Remove trailing newline
    if (response[received - 1] == '\n') {
        response[received - 1] = '\0';
    }

    return received;
}

void handle_server_response(ai_client_t *ai, const char *response)
{
    if (strncmp(response, "ok", 2) == 0) {
        // Command successful
        return;
    }

    if (strncmp(response, "ko", 2) == 0) {
        // Command failed
        printf("Command failed\n");
        return;
    }

    if (strncmp(response, "dead", 4) == 0) {
        printf("AI died\n");
        ai->connected = false;
        return;
    }

    if (strncmp(response, "eject:", 6) == 0) {
        printf("Ejected from tile\n");
        return;
    }

    if (strncmp(response, "message", 7) == 0) {
        printf("Received broadcast: %s\n", response);
        return;
    }

    if (response[0] == '[') {
        // Look or inventory response
        if (strstr(response, "food") || strstr(response, "linemate")) {
            if (ai->state == STATE_EXPLORING) {
                parse_look_response(ai, response);
            } else {
                parse_inventory_response(ai, response);
            }
        }
        return;
    }

    // Elevation response
    if (strncmp(response, "Elevation underway", 18) == 0) {
        printf("Elevation successful!\n");
        ai->level++;
        ai->state = STATE_EXPLORING;
        return;
    }

    printf("Unknown response: %s\n", response);
}