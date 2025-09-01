/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Data management implementation
*/

#include "myteams.h"

void generate_uuid(char *uuid_str)
{
    static int counter = 1000;
    srand(time(NULL) + counter);
    snprintf(uuid_str, 37, "%08x-%04x-%04x-%04x-%08x%04x", 
             rand(), rand() % 0xFFFF, rand() % 0xFFFF, rand() % 0xFFFF,
             rand(), counter++);
}

user_t *create_user(const char *name)
{
    user_t *user = malloc(sizeof(user_t));
    if (!user)
        return NULL;
    generate_uuid(user->uuid);
    strncpy(user->name, name, MAX_NAME_LENGTH);
    user->name[MAX_NAME_LENGTH] = '\0';
    user->is_logged_in = 0;
    user->next = NULL;
    return user;
}

team_t *create_team(const char *name, const char *description)
{
    team_t *team = malloc(sizeof(team_t));
    if (!team)
        return NULL;
    generate_uuid(team->uuid);
    strncpy(team->name, name, MAX_NAME_LENGTH);
    team->name[MAX_NAME_LENGTH] = '\0';
    strncpy(team->description, description, MAX_DESCRIPTION_LENGTH);
    team->description[MAX_DESCRIPTION_LENGTH] = '\0';
    team->next = NULL;
    return team;
}

channel_t *create_channel(const char *name, const char *description,
                         const char *team_uuid)
{
    channel_t *channel = malloc(sizeof(channel_t));
    if (!channel)
        return NULL;
    generate_uuid(channel->uuid);
    strncpy(channel->name, name, MAX_NAME_LENGTH);
    channel->name[MAX_NAME_LENGTH] = '\0';
    strncpy(channel->description, description, MAX_DESCRIPTION_LENGTH);
    channel->description[MAX_DESCRIPTION_LENGTH] = '\0';
    strcpy(channel->team_uuid, team_uuid);
    channel->next = NULL;
    return channel;
}

thread_t *create_thread(const char *title, const char *message,
                       const char *user_uuid, const char *channel_uuid)
{
    thread_t *thread = malloc(sizeof(thread_t));
    if (!thread)
        return NULL;
    generate_uuid(thread->uuid);
    strncpy(thread->title, title, MAX_NAME_LENGTH);
    thread->title[MAX_NAME_LENGTH] = '\0';
    strncpy(thread->message, message, MAX_BODY_LENGTH);
    thread->message[MAX_BODY_LENGTH] = '\0';
    strcpy(thread->user_uuid, user_uuid);
    strcpy(thread->channel_uuid, channel_uuid);
    thread->timestamp = time(NULL);
    thread->next = NULL;
    return thread;
}

comment_t *create_comment(const char *body, const char *user_uuid,
                         const char *thread_uuid)
{
    comment_t *comment = malloc(sizeof(comment_t));
    if (!comment)
        return NULL;
    generate_uuid(comment->uuid);
    strncpy(comment->body, body, MAX_BODY_LENGTH);
    comment->body[MAX_BODY_LENGTH] = '\0';
    strcpy(comment->user_uuid, user_uuid);
    strcpy(comment->thread_uuid, thread_uuid);
    comment->timestamp = time(NULL);
    comment->next = NULL;
    return comment;
}

message_t *create_message(const char *body, const char *sender_uuid,
                         const char *receiver_uuid)
{
    message_t *message = malloc(sizeof(message_t));
    if (!message)
        return NULL;
    generate_uuid(message->uuid);
    strncpy(message->body, body, MAX_BODY_LENGTH);
    message->body[MAX_BODY_LENGTH] = '\0';
    strcpy(message->sender_uuid, sender_uuid);
    strcpy(message->receiver_uuid, receiver_uuid);
    message->timestamp = time(NULL);
    message->next = NULL;
    return message;
}

user_t *get_user_by_uuid(server_t *server, const char *uuid)
{
    user_t *user = server->users;
    while (user) {
        if (strcmp(user->uuid, uuid) == 0)
            return user;
        user = user->next;
    }
    return NULL;
}

user_t *get_user_by_name(server_t *server, const char *name)
{
    user_t *user = server->users;
    while (user) {
        if (strcmp(user->name, name) == 0)
            return user;
        user = user->next;
    }
    return NULL;
}

client_t *get_client_by_uuid(server_t *server, const char *uuid)
{
    for (int i = 0; i < server->nb_clients; i++) {
        if (strcmp(server->clients[i].uuid, uuid) == 0)
            return &server->clients[i];
    }
    return NULL;
}