/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Client implementation
*/

#include "myteams.h"

int connect_to_server(const char *ip, int port)
{
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }
    return sock;
}

void handle_server_message(int server_fd)
{
    char buffer[BUFFER_SIZE] = {0};
    int valread = read(server_fd, buffer, BUFFER_SIZE);
    
    if (valread > 0) {
        printf("%s", buffer);
        fflush(stdout);
    }
}

void handle_user_input(int server_fd)
{
    char input[BUFFER_SIZE];
    
    if (fgets(input, sizeof(input), stdin)) {
        write(server_fd, input, strlen(input));
    }
}

void client_loop(int server_fd)
{
    fd_set readfds;
    int activity;
    
    printf("Connected to server. Type /help for commands.\n");
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        
        activity = select(server_fd + 1, &readfds, NULL, NULL, NULL);
        
        if (activity < 0) {
            perror("select error");
            break;
        }
        if (FD_ISSET(server_fd, &readfds)) {
            handle_server_message(server_fd);
        }
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            handle_user_input(server_fd);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "USAGE: %s ip port\n", argv[0]);
        fprintf(stderr, "       ip   is the server ip address on which the server socket listens\n");
        fprintf(stderr, "       port is the port number on which the server socket listens\n");
        return 84;
    }
    
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        return 84;
    }
    
    int server_fd = connect_to_server(ip, port);
    if (server_fd == -1) {
        return 84;
    }
    
    client_loop(server_fd);
    
    close(server_fd);
    return 0;
}