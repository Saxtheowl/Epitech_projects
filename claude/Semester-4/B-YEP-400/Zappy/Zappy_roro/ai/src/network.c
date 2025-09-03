/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Network communication functions
*/

#include "zappy_ai.h"

int connect_to_server(ai_t *ai)
{
    struct sockaddr_in server_addr;

    ai->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ai->socket_fd == -1) {
        perror("socket");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(ai->port);
    
    if (inet_pton(AF_INET, ai->server_name, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(ai->socket_fd);
        return -1;
    }

    if (connect(ai->socket_fd, (struct sockaddr *)&server_addr, 
        sizeof(server_addr)) == -1) {
        perror("connect");
        close(ai->socket_fd);
        return -1;
    }

    return 0;
}

void send_command(ai_t *ai, const char *command)
{
    if (ai->socket_fd != -1 && command) {
        write(ai->socket_fd, command, strlen(command));
        write(ai->socket_fd, "\n", 1);
    }
}

char *receive_response(ai_t *ai)
{
    char buffer[BUFFER_SIZE];
    int bytes_read = 0;
    
    bytes_read = read(ai->socket_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read <= 0)
        return NULL;
    
    buffer[bytes_read] = '\0';
    return strdup(buffer);
}

void process_welcome(ai_t *ai)
{
    char *response = receive_response(ai);
    
    if (response && strstr(response, "WELCOME")) {
        free(response);
        send_command(ai, ai->team_name);
        
        response = receive_response(ai);
        if (response) {
            sscanf(response, "%d", &ai->slots_available);
            free(response);
            
            response = receive_response(ai);
            if (response) {
                sscanf(response, "%d %d", &ai->world_width, &ai->world_height);
                free(response);
            }
        }
    } else {
        free(response);
    }
}