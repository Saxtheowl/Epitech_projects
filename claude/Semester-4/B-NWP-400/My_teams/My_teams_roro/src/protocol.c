/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Protocol handling implementation
*/

#include "myteams.h"

void process_command(server_t *server, int client_idx, char *command)
{
    char **args = parse_command(command);
    
    if (!args || !args[0]) {
        send_response(server->clients[client_idx].fd, "ERROR: Invalid command\n");
        free_command_args(args);
        return;
    }
    if (strcmp(args[0], "/help") == 0) {
        send_response(server->clients[client_idx].fd, 
                     "/help: show help\n/login [\"user_name\"]: login\n"
                     "/logout: logout\n/users: list users\n"
                     "/user [\"user_uuid\"]: user info\n"
                     "/send [\"user_uuid\"] [\"message\"]: send message\n"
                     "/messages [\"user_uuid\"]: list messages\n"
                     "/subscribe [\"team_uuid\"]: subscribe to team\n"
                     "/unsubscribe [\"team_uuid\"]: unsubscribe from team\n"
                     "/subscribed [\"team_uuid\"]: list subscriptions\n"
                     "/create: create resource\n/list: list resources\n"
                     "/info: show info\n");
    } else if (strcmp(args[0], "/login") == 0 && args[1]) {
        cmd_login(server, client_idx, args[1]);
    } else if (strcmp(args[0], "/logout") == 0) {
        cmd_logout(server, client_idx);
    } else if (strcmp(args[0], "/users") == 0) {
        cmd_users(server, client_idx);
    } else if (strcmp(args[0], "/user") == 0 && args[1]) {
        cmd_user(server, client_idx, args[1]);
    } else if (strcmp(args[0], "/send") == 0 && args[1] && args[2]) {
        cmd_send(server, client_idx, args[1], args[2]);
    } else if (strcmp(args[0], "/messages") == 0 && args[1]) {
        cmd_messages(server, client_idx, args[1]);
    } else if (strcmp(args[0], "/subscribe") == 0 && args[1]) {
        cmd_subscribe(server, client_idx, args[1]);
    } else if (strcmp(args[0], "/unsubscribe") == 0 && args[1]) {
        cmd_unsubscribe(server, client_idx, args[1]);
    } else if (strcmp(args[0], "/subscribed") == 0) {
        cmd_subscribed(server, client_idx, args[1]);
    } else if (strcmp(args[0], "/create") == 0) {
        cmd_create(server, client_idx, &args[1]);
    } else if (strcmp(args[0], "/list") == 0) {
        cmd_list(server, client_idx);
    } else if (strcmp(args[0], "/info") == 0) {
        cmd_info(server, client_idx);
    } else {
        send_response(server->clients[client_idx].fd, "ERROR: Unknown command\n");
    }
    free_command_args(args);
}

void cmd_login(server_t *server, int client_idx, char *username)
{
    if (server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Already logged in\n");
        return;
    }
    if (strlen(username) > MAX_NAME_LENGTH) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Username too long\n");
        return;
    }
    user_t *user = get_user_by_name(server, username);
    if (!user) {
        user = create_user(username);
        if (!user) {
            send_response(server->clients[client_idx].fd, 
                         "ERROR: Cannot create user\n");
            return;
        }
        user->next = server->users;
        server->users = user;
    }
    server->clients[client_idx].logged_in = 1;
    strcpy(server->clients[client_idx].name, username);
    strcpy(server->clients[client_idx].uuid, user->uuid);
    user->is_logged_in = 1;
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "OK: Logged in as %s (%s)\n", 
             username, user->uuid);
    send_response(server->clients[client_idx].fd, response);
}

void cmd_logout(server_t *server, int client_idx)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    user_t *user = get_user_by_name(server, server->clients[client_idx].name);
    if (user)
        user->is_logged_in = 0;
    server->clients[client_idx].logged_in = 0;
    memset(server->clients[client_idx].name, 0, MAX_NAME_LENGTH + 1);
    memset(server->clients[client_idx].uuid, 0, 37);
    send_response(server->clients[client_idx].fd, "OK: Logged out\n");
}

void cmd_users(server_t *server, int client_idx)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    char response[BUFFER_SIZE * 10] = "Users:\n";
    user_t *user = server->users;
    while (user) {
        char user_info[256];
        snprintf(user_info, sizeof(user_info), "- %s (%s) %s\n", 
                user->name, user->uuid, 
                user->is_logged_in ? "[online]" : "[offline]");
        strcat(response, user_info);
        user = user->next;
    }
    send_response(server->clients[client_idx].fd, response);
}

void cmd_user(server_t *server, int client_idx, char *user_uuid)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    user_t *user = get_user_by_uuid(server, user_uuid);
    if (!user) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: User not found\n");
        return;
    }
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), 
             "User: %s (%s) %s\n", user->name, user->uuid,
             user->is_logged_in ? "[online]" : "[offline]");
    send_response(server->clients[client_idx].fd, response);
}

void cmd_send(server_t *server, int client_idx, char *user_uuid, char *message)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    user_t *recipient = get_user_by_uuid(server, user_uuid);
    if (!recipient) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: User not found\n");
        return;
    }
    message_t *msg = create_message(message, 
                                   server->clients[client_idx].uuid,
                                   user_uuid);
    if (!msg) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Cannot create message\n");
        return;
    }
    msg->next = server->messages;
    server->messages = msg;
    send_response(server->clients[client_idx].fd, "OK: Message sent\n");
}