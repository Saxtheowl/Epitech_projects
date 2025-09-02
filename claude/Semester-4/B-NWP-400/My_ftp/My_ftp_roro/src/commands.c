/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** Command parsing and execution
*/

#include "myftp.h"

typedef struct command_s {
    const char *name;
    void (*handler)(server_t *server, int client_index, const char *args);
} command_t;

static const command_t commands[] = {
    {"USER", cmd_user},
    {"PASS", cmd_pass},
    {"PWD", cmd_pwd},
    {"CWD", cmd_cwd},
    {"LIST", cmd_list},
    {"RETR", cmd_retr},
    {"STOR", cmd_stor},
    {"QUIT", cmd_quit},
    {"PORT", cmd_port},
    {"PASV", cmd_pasv},
    {"TYPE", cmd_type},
    {"MODE", cmd_mode},
    {"STRU", cmd_stru},
    {"NOOP", cmd_noop},
    {NULL, NULL}
};

void send_response(int fd, int code, const char *message)
{
    char response[BUFFER_SIZE];
    
    snprintf(response, sizeof(response), "%d %s\r\n", code, message);
    write(fd, response, strlen(response));
    printf("Sent: %d %s\n", code, message);
}

int execute_command(server_t *server, int client_index, const char *command)
{
    char cmd_copy[MAX_COMMAND_SIZE];
    char *cmd_name;
    char *args;
    int i;

    if (!command || strlen(command) == 0) {
        send_response(server->fds[client_index].fd, 500, "Empty command");
        return 0;
    }

    strncpy(cmd_copy, command, MAX_COMMAND_SIZE - 1);
    cmd_copy[MAX_COMMAND_SIZE - 1] = '\0';

    cmd_name = strtok(cmd_copy, " ");
    args = strtok(NULL, "");

    if (!cmd_name) {
        send_response(server->fds[client_index].fd, 500, "Invalid command");
        return 0;
    }

    for (i = 0; commands[i].name; i++) {
        if (strcasecmp(cmd_name, commands[i].name) == 0) {
            commands[i].handler(server, client_index, args);
            return 0;
        }
    }

    send_response(server->fds[client_index].fd, 500, "Unknown command");
    return 0;
}