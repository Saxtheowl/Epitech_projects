/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Protocol handling and command processing
*/

#include "myteams.h"

static command_type_t parse_command_type(const char *cmd_str)
{
    if (strncmp(cmd_str, "/login", 6) == 0) return CMD_LOGIN;
    if (strncmp(cmd_str, "/logout", 7) == 0) return CMD_LOGOUT;
    if (strncmp(cmd_str, "/users", 6) == 0) return CMD_USERS;
    if (strncmp(cmd_str, "/user", 5) == 0) return CMD_USER;
    if (strncmp(cmd_str, "/send", 5) == 0) return CMD_SEND;
    if (strncmp(cmd_str, "/messages", 9) == 0) return CMD_MESSAGES;
    if (strncmp(cmd_str, "/subscribe", 10) == 0) return CMD_SUBSCRIBE;
    if (strncmp(cmd_str, "/subscribed", 11) == 0) return CMD_SUBSCRIBED;
    if (strncmp(cmd_str, "/unsubscribe", 12) == 0) return CMD_UNSUBSCRIBE;
    if (strncmp(cmd_str, "/use", 4) == 0) return CMD_USE;
    if (strncmp(cmd_str, "/create", 7) == 0) return CMD_CREATE;
    if (strncmp(cmd_str, "/list", 5) == 0) return CMD_LIST;
    if (strncmp(cmd_str, "/info", 5) == 0) return CMD_INFO;
    if (strncmp(cmd_str, "/help", 5) == 0) return CMD_HELP;
    return CMD_UNKNOWN;
}

static char **parse_quoted_args(const char *command, int *argc)
{
    char **args = malloc(sizeof(char*) * 10);
    *argc = 0;

    char *cmd_copy = strdup(command);
    char *ptr = cmd_copy;

    // Skip command part
    while (*ptr && *ptr != ' ') ptr++;
    while (*ptr && *ptr == ' ') ptr++;

    while (*ptr && *argc < 9) {
        if (*ptr == '"') {
            ptr++; // Skip opening quote
            char *start = ptr;

            // Find closing quote
            while (*ptr && *ptr != '"') ptr++;

            if (*ptr == '"') {
                *ptr = '\0';
                args[*argc] = strdup(start);
                (*argc)++;
                ptr++; // Skip closing quote

                // Skip spaces
                while (*ptr && *ptr == ' ') ptr++;
            } else {
                break; // Malformed quote
            }
        } else {
            // Skip non-quoted arguments for now
            while (*ptr && *ptr != ' ') ptr++;
            while (*ptr && *ptr == ' ') ptr++;
        }
    }

    args[*argc] = NULL;
    free(cmd_copy);
    return args;
}

static void free_args(char **args, int argc)
{
    for (int i = 0; i < argc; i++) {
        free(args[i]);
    }
    free(args);
}

void process_command(server_t *server, client_t *client, const char *command)
{
    command_type_t cmd_type = parse_command_type(command);
    int argc;
    char **args = parse_quoted_args(command, &argc);

    switch (cmd_type) {
        case CMD_LOGIN:
            if (argc >= 1) {
                cmd_login(server, client, args[0]);
            } else {
                send_error(client->socket_fd, "Missing username");
            }
            break;
        case CMD_LOGOUT:
            cmd_logout(server, client);
            break;
        case CMD_USERS:
            cmd_users(server, client);
            break;
        case CMD_USER:
            if (argc >= 1) {
                cmd_user(server, client, args[0]);
            } else {
                send_error(client->socket_fd, "Missing user UUID");
            }
            break;
        case CMD_SEND:
            if (argc >= 2) {
                cmd_send(server, client, args[0], args[1]);
            } else {
                send_error(client->socket_fd, "Missing user UUID or message");
            }
            break;
        case CMD_MESSAGES:
            if (argc >= 1) {
                cmd_messages(server, client, args[0]);
            } else {
                send_error(client->socket_fd, "Missing user UUID");
            }
            break;
        case CMD_SUBSCRIBE:
            if (argc >= 1) {
                cmd_subscribe(server, client, args[0]);
            } else {
                send_error(client->socket_fd, "Missing team UUID");
            }
            break;
        case CMD_SUBSCRIBED:
            cmd_subscribed(server, client, argc > 0 ? args[0] : NULL);
            break;
        case CMD_UNSUBSCRIBE:
            if (argc >= 1) {
                cmd_unsubscribe(server, client, args[0]);
            } else {
                send_error(client->socket_fd, "Missing team UUID");
            }
            break;
        case CMD_USE:
            cmd_use(server, client,
                argc > 0 ? args[0] : NULL,
                argc > 1 ? args[1] : NULL,
                argc > 2 ? args[2] : NULL);
            break;
        case CMD_CREATE:
            cmd_create(server, client, args);
            break;
        case CMD_LIST:
            cmd_list(server, client);
            break;
        case CMD_INFO:
            cmd_info(server, client);
            break;
        case CMD_HELP:
            cmd_help(server, client);
            break;
        default:
            send_error(client->socket_fd, "Unknown command");
            break;
    }

    free_args(args, argc);
}

void send_response(int fd, const char *response)
{
    send(fd, response, strlen(response), 0);
    send(fd, "\n", 1, 0);
}

void send_error(int fd, const char *error_msg)
{
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "ERROR: %s", error_msg);
    send_response(fd, response);
}