/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Team-related command implementations
*/

#include "myteams.h"

void cmd_subscribe(server_t *server, client_t *client, const char *team_uuid)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    team_t *team = find_team_by_uuid(server, team_uuid);
    if (!team) {
        send_error(client->socket_fd, "Team not found");
        return;
    }

    if (is_user_subscribed(server, client->user_uuid, team_uuid)) {
        send_error(client->socket_fd, "Already subscribed to team");
        return;
    }

    if (server->subscription_count >= MAX_CLIENTS * 10) {
        send_error(client->socket_fd, "Subscription storage full");
        return;
    }

    // Add subscription
    subscription_t *sub = &server->subscriptions[server->subscription_count];
    strcpy(sub->user_uuid, client->user_uuid);
    strcpy(sub->team_uuid, team_uuid);
    server->subscription_count++;

    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "SUBSCRIBED %s %s", team_uuid, team->name);
    send_response(client->socket_fd, response);
}

void cmd_subscribed(server_t *server, client_t *client, const char *team_uuid)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    if (team_uuid == NULL) {
        // List all teams user is subscribed to
        char response[BUFFER_SIZE];
        strcpy(response, "SUBSCRIBED_TEAMS");

        for (int i = 0; i < server->subscription_count; i++) {
            if (strcmp(server->subscriptions[i].user_uuid, client->user_uuid) == 0) {
                team_t *team = find_team_by_uuid(server, server->subscriptions[i].team_uuid);
                if (team) {
                    char team_info[256];
                    snprintf(team_info, sizeof(team_info), " %s:%s", team->uuid, team->name);
                    strcat(response, team_info);
                }
            }
        }
        send_response(client->socket_fd, response);
    } else {
        // List members of specific team
        team_t *team = find_team_by_uuid(server, team_uuid);
        if (!team) {
            send_error(client->socket_fd, "Team not found");
            return;
        }

        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response), "TEAM_MEMBERS %s", team_uuid);

        for (int i = 0; i < server->subscription_count; i++) {
            if (strcmp(server->subscriptions[i].team_uuid, team_uuid) == 0) {
                user_t *user = find_user_by_uuid(server, server->subscriptions[i].user_uuid);
                if (user) {
                    char user_info[256];
                    snprintf(user_info, sizeof(user_info), " %s:%s", user->uuid, user->name);
                    strcat(response, user_info);
                }
            }
        }
        send_response(client->socket_fd, response);
    }
}

void cmd_unsubscribe(server_t *server, client_t *client, const char *team_uuid)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    // Find and remove subscription
    for (int i = 0; i < server->subscription_count; i++) {
        if (strcmp(server->subscriptions[i].user_uuid, client->user_uuid) == 0 &&
            strcmp(server->subscriptions[i].team_uuid, team_uuid) == 0) {

            // Remove subscription by shifting array
            for (int j = i; j < server->subscription_count - 1; j++) {
                server->subscriptions[j] = server->subscriptions[j + 1];
            }
            server->subscription_count--;

            send_response(client->socket_fd, "UNSUBSCRIBED");
            return;
        }
    }

    send_error(client->socket_fd, "Not subscribed to team");
}

void cmd_use(server_t *server, client_t *client, const char *team_uuid, const char *channel_uuid, const char *thread_uuid)
{
    (void)server;

    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    // Reset context
    client->context.type = CONTEXT_NONE;
    memset(client->context.team_uuid, 0, UUID_STR_LEN);
    memset(client->context.channel_uuid, 0, UUID_STR_LEN);
    memset(client->context.thread_uuid, 0, UUID_STR_LEN);

    if (team_uuid) {
        strcpy(client->context.team_uuid, team_uuid);
        client->context.type = CONTEXT_TEAM;

        if (channel_uuid) {
            strcpy(client->context.channel_uuid, channel_uuid);
            client->context.type = CONTEXT_CHANNEL;

            if (thread_uuid) {
                strcpy(client->context.thread_uuid, thread_uuid);
                client->context.type = CONTEXT_THREAD;
            }
        }
    }

    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "CONTEXT_SET %d %s %s %s",
             client->context.type,
             client->context.team_uuid,
             client->context.channel_uuid,
             client->context.thread_uuid);
    send_response(client->socket_fd, response);
}

void cmd_create(server_t *server, client_t *client, char **args)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    switch (client->context.type) {
        case CONTEXT_NONE:
            // Create team
            if (!args[0] || !args[1]) {
                send_error(client->socket_fd, "Missing team name or description");
                return;
            }
            if (server->team_count >= MAX_CLIENTS) {
                send_error(client->socket_fd, "Team storage full");
                return;
            }

            team_t *new_team = &server->teams[server->team_count];
            generate_uuid(new_team->uuid);
            strncpy(new_team->name, args[0], MAX_NAME_LENGTH - 1);
            strncpy(new_team->description, args[1], MAX_DESCRIPTION_LENGTH - 1);
            strcpy(new_team->creator_uuid, client->user_uuid);
            new_team->created_at = time(NULL);
            server->team_count++;

            char team_response[BUFFER_SIZE];
            snprintf(team_response, sizeof(team_response), "TEAM_CREATED %s %s", new_team->uuid, new_team->name);
            send_response(client->socket_fd, team_response);
            break;

        case CONTEXT_TEAM:
            // Create channel
            if (!args[0] || !args[1]) {
                send_error(client->socket_fd, "Missing channel name or description");
                return;
            }
            if (server->channel_count >= MAX_CLIENTS * 10) {
                send_error(client->socket_fd, "Channel storage full");
                return;
            }

            channel_t *new_channel = &server->channels[server->channel_count];
            generate_uuid(new_channel->uuid);
            strncpy(new_channel->name, args[0], MAX_NAME_LENGTH - 1);
            strncpy(new_channel->description, args[1], MAX_DESCRIPTION_LENGTH - 1);
            strcpy(new_channel->team_uuid, client->context.team_uuid);
            strcpy(new_channel->creator_uuid, client->user_uuid);
            new_channel->created_at = time(NULL);
            server->channel_count++;

            char channel_response[BUFFER_SIZE];
            snprintf(channel_response, sizeof(channel_response), "CHANNEL_CREATED %s %s", new_channel->uuid, new_channel->name);
            send_response(client->socket_fd, channel_response);
            break;

        default:
            send_error(client->socket_fd, "Create not implemented for this context");
            break;
    }
}

void cmd_list(server_t *server, client_t *client)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    switch (client->context.type) {
        case CONTEXT_NONE:
            // List all teams
            send_response(client->socket_fd, "TEAMS_LIST");
            for (int i = 0; i < server->team_count; i++) {
                char team_info[BUFFER_SIZE];
                snprintf(team_info, sizeof(team_info), "TEAM %s %s \"%s\"",
                         server->teams[i].uuid, server->teams[i].name, server->teams[i].description);
                send_response(client->socket_fd, team_info);
            }
            send_response(client->socket_fd, "TEAMS_END");
            break;

        case CONTEXT_TEAM:
            // List channels in team
            send_response(client->socket_fd, "CHANNELS_LIST");
            for (int i = 0; i < server->channel_count; i++) {
                if (strcmp(server->channels[i].team_uuid, client->context.team_uuid) == 0) {
                    char channel_info[BUFFER_SIZE];
                    snprintf(channel_info, sizeof(channel_info), "CHANNEL %s %s \"%s\"",
                             server->channels[i].uuid, server->channels[i].name, server->channels[i].description);
                    send_response(client->socket_fd, channel_info);
                }
            }
            send_response(client->socket_fd, "CHANNELS_END");
            break;

        default:
            send_error(client->socket_fd, "List not implemented for this context");
            break;
    }
}

void cmd_info(server_t *server, client_t *client)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    switch (client->context.type) {
        case CONTEXT_NONE:
            // Show current user info
            user_t *user = find_user_by_uuid(server, client->user_uuid);
            if (user) {
                char response[BUFFER_SIZE];
                snprintf(response, sizeof(response), "USER_INFO %s %s %s",
                         user->uuid, user->name, user->is_connected ? "online" : "offline");
                send_response(client->socket_fd, response);
            }
            break;

        case CONTEXT_TEAM:
            // Show team info
            team_t *team = find_team_by_uuid(server, client->context.team_uuid);
            if (team) {
                char response[BUFFER_SIZE];
                snprintf(response, sizeof(response), "TEAM_INFO %s %s \"%s\"",
                         team->uuid, team->name, team->description);
                send_response(client->socket_fd, response);
            } else {
                send_error(client->socket_fd, "Team not found");
            }
            break;

        default:
            send_error(client->socket_fd, "Info not implemented for this context");
            break;
    }
}