/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Client implementation
*/

#include "myteams.h"

int init_client(const char *ip, int port)
{
    int server_fd;
    struct sockaddr_in server_addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        close(server_fd);
        return -1;
    }

    if (connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(server_fd);
        return -1;
    }

    return server_fd;
}

void handle_server_response(const char *response)
{
    printf("Server: %s\n", response);
}

void run_client(int server_fd)
{
    fd_set read_fds;
    char input_buffer[BUFFER_SIZE];
    char server_buffer[BUFFER_SIZE];

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(server_fd, &read_fds);

        int max_fd = server_fd > STDIN_FILENO ? server_fd : STDIN_FILENO;

        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            if (errno == EINTR) continue;
            perror("select failed");
            break;
        }

        // Handle user input
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
                break;
            }

            // Remove newline if present
            size_t len = strlen(input_buffer);
            if (len > 0 && input_buffer[len - 1] == '\n') {
                input_buffer[len - 1] = '\0';
            }

            // Exit command
            if (strcmp(input_buffer, "/quit") == 0 || strcmp(input_buffer, "/exit") == 0) {
                break;
            }

            // Send command to server
            if (send(server_fd, input_buffer, strlen(input_buffer), 0) < 0) {
                perror("send failed");
                break;
            }
            if (send(server_fd, "\n", 1, 0) < 0) {
                perror("send failed");
                break;
            }
        }

        // Handle server response
        if (FD_ISSET(server_fd, &read_fds)) {
            ssize_t bytes_received = recv(server_fd, server_buffer, sizeof(server_buffer) - 1, 0);
            if (bytes_received <= 0) {
                if (bytes_received == 0) {
                    printf("Server disconnected\n");
                } else {
                    perror("recv failed");
                }
                break;
            }

            server_buffer[bytes_received] = '\0';

            // Handle multiple lines in response
            char *line = strtok(server_buffer, "\n");
            while (line != NULL) {
                handle_server_response(line);
                line = strtok(NULL, "\n");
            }
        }
    }
}

void cleanup_client(int server_fd)
{
    if (server_fd >= 0) {
        close(server_fd);
    }
}