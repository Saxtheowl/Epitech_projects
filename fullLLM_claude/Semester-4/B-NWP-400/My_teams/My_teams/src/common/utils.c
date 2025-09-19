/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Utility functions
*/

#include "myteams.h"

void generate_uuid(char *uuid_str)
{
    static int counter = 0;
    counter++;
    snprintf(uuid_str, UUID_STR_LEN, "%08x-%04x-%04x-%04x-%08x%04x",
             (unsigned int)time(NULL),
             (unsigned int)(getpid() & 0xFFFF),
             (unsigned int)(counter & 0xFFFF),
             (unsigned int)(rand() & 0xFFFF),
             (unsigned int)(rand()),
             (unsigned int)(rand() & 0xFFFF));
}

user_t *find_user_by_uuid(server_t *server, const char *uuid)
{
    for (int i = 0; i < server->user_count; i++) {
        if (strcmp(server->users[i].uuid, uuid) == 0) {
            return &server->users[i];
        }
    }
    return NULL;
}

user_t *find_user_by_name(server_t *server, const char *name)
{
    for (int i = 0; i < server->user_count; i++) {
        if (strcmp(server->users[i].name, name) == 0) {
            return &server->users[i];
        }
    }
    return NULL;
}

team_t *find_team_by_uuid(server_t *server, const char *uuid)
{
    for (int i = 0; i < server->team_count; i++) {
        if (strcmp(server->teams[i].uuid, uuid) == 0) {
            return &server->teams[i];
        }
    }
    return NULL;
}

channel_t *find_channel_by_uuid(server_t *server, const char *uuid)
{
    for (int i = 0; i < server->channel_count; i++) {
        if (strcmp(server->channels[i].uuid, uuid) == 0) {
            return &server->channels[i];
        }
    }
    return NULL;
}

thread_t *find_thread_by_uuid(server_t *server, const char *uuid)
{
    for (int i = 0; i < server->thread_count; i++) {
        if (strcmp(server->threads[i].uuid, uuid) == 0) {
            return &server->threads[i];
        }
    }
    return NULL;
}

bool is_user_subscribed(server_t *server, const char *user_uuid, const char *team_uuid)
{
    for (int i = 0; i < server->subscription_count; i++) {
        if (strcmp(server->subscriptions[i].user_uuid, user_uuid) == 0 &&
            strcmp(server->subscriptions[i].team_uuid, team_uuid) == 0) {
            return true;
        }
    }
    return false;
}

client_t *find_client_by_fd(server_t *server, int fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd == fd) {
            return &server->clients[i];
        }
    }
    return NULL;
}