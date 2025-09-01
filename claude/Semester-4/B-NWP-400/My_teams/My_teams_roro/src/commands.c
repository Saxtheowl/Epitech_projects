/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Additional command implementations
*/

#include "myteams.h"

void cmd_messages(server_t *server, int client_idx, char *user_uuid)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    char current_user_uuid[37];
    strcpy(current_user_uuid, server->clients[client_idx].uuid);
    
    char response[BUFFER_SIZE * 10] = "Messages:\n";
    message_t *message = server->messages;
    
    while (message) {
        if ((strcmp(message->sender_uuid, current_user_uuid) == 0 &&
             strcmp(message->receiver_uuid, user_uuid) == 0) ||
            (strcmp(message->sender_uuid, user_uuid) == 0 &&
             strcmp(message->receiver_uuid, current_user_uuid) == 0)) {
            char msg_info[512];
            snprintf(msg_info, sizeof(msg_info), 
                    "- %s: %s\n", 
                    strcmp(message->sender_uuid, current_user_uuid) == 0 ? 
                    "You" : "Them", message->body);
            strcat(response, msg_info);
        }
        message = message->next;
    }
    send_response(server->clients[client_idx].fd, response);
}

void cmd_subscribe(server_t *server, int client_idx, char *team_uuid)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    subscription_t *sub = malloc(sizeof(subscription_t));
    if (!sub) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Memory allocation failed\n");
        return;
    }
    strcpy(sub->user_uuid, server->clients[client_idx].uuid);
    strcpy(sub->team_uuid, team_uuid);
    sub->next = server->subscriptions;
    server->subscriptions = sub;
    send_response(server->clients[client_idx].fd, 
                 "OK: Subscribed to team\n");
}

void cmd_unsubscribe(server_t *server, int client_idx, char *team_uuid)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    subscription_t *prev = NULL;
    subscription_t *current = server->subscriptions;
    
    while (current) {
        if (strcmp(current->user_uuid, server->clients[client_idx].uuid) == 0 &&
            strcmp(current->team_uuid, team_uuid) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                server->subscriptions = current->next;
            }
            free(current);
            send_response(server->clients[client_idx].fd, 
                         "OK: Unsubscribed from team\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    send_response(server->clients[client_idx].fd, 
                 "ERROR: Not subscribed to this team\n");
}

void cmd_subscribed(server_t *server, int client_idx, char *team_uuid)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    char response[BUFFER_SIZE * 10] = "Subscriptions:\n";
    subscription_t *sub = server->subscriptions;
    
    if (!team_uuid) {
        // List all teams user is subscribed to
        while (sub) {
            if (strcmp(sub->user_uuid, server->clients[client_idx].uuid) == 0) {
                char sub_info[128];
                snprintf(sub_info, sizeof(sub_info), "- Team: %s\n", 
                        sub->team_uuid);
                strcat(response, sub_info);
            }
            sub = sub->next;
        }
    } else {
        // List all users subscribed to this team
        while (sub) {
            if (strcmp(sub->team_uuid, team_uuid) == 0) {
                user_t *user = get_user_by_uuid(server, sub->user_uuid);
                if (user) {
                    char sub_info[128];
                    snprintf(sub_info, sizeof(sub_info), "- User: %s\n", 
                            user->name);
                    strcat(response, sub_info);
                }
            }
            sub = sub->next;
        }
    }
    send_response(server->clients[client_idx].fd, response);
}

void cmd_create(server_t *server, int client_idx, char **args)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    if (!args[0] || !args[1]) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Missing arguments\n");
        return;
    }
    team_t *new_team = create_team(args[0], args[1]);
    if (!new_team) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Cannot create team\n");
        return;
    }
    new_team->next = server->teams;
    server->teams = new_team;
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), 
             "OK: Team created (%s)\n", new_team->uuid);
    send_response(server->clients[client_idx].fd, response);
}

void cmd_list(server_t *server, int client_idx)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    char response[BUFFER_SIZE * 10] = "Teams:\n";
    team_t *team = server->teams;
    
    while (team) {
        char team_info[512];
        snprintf(team_info, sizeof(team_info), 
                "- %s (%s): %s\n", 
                team->name, team->uuid, team->description);
        strcat(response, team_info);
        team = team->next;
    }
    send_response(server->clients[client_idx].fd, response);
}

void cmd_info(server_t *server, int client_idx)
{
    if (!server->clients[client_idx].logged_in) {
        send_response(server->clients[client_idx].fd, 
                     "ERROR: Not logged in\n");
        return;
    }
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), 
             "User: %s (%s)\n", 
             server->clients[client_idx].name,
             server->clients[client_idx].uuid);
    send_response(server->clients[client_idx].fd, response);
}