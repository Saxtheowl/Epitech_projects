/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Utility functions implementation
*/

#include "myteams.h"

void send_response(int fd, const char *response)
{
    write(fd, response, strlen(response));
}

char **parse_command(const char *command)
{
    char **args = malloc(sizeof(char *) * 10);
    char *cmd_copy = strdup(command);
    char *token;
    int i = 0;
    int in_quotes = 0;
    char *start = cmd_copy;
    char *current = cmd_copy;

    if (!args || !cmd_copy) {
        free(args);
        free(cmd_copy);
        return NULL;
    }
    memset(args, 0, sizeof(char *) * 10);
    while (*current && i < 9) {
        if (*current == '"' && (current == cmd_copy || *(current - 1) == ' ')) {
            in_quotes = !in_quotes;
            if (in_quotes) {
                start = current + 1;
            } else {
                *current = '\0';
                args[i] = strdup(start);
                i++;
                start = current + 1;
            }
        } else if (*current == ' ' && !in_quotes) {
            if (current > start) {
                *current = '\0';
                args[i] = strdup(start);
                i++;
            }
            start = current + 1;
        }
        current++;
    }
    if (current > start && i < 9) {
        if (in_quotes && *(current - 1) == '"') {
            *(current - 1) = '\0';
        }
        args[i] = strdup(start);
    }
    free(cmd_copy);
    return args;
}

void free_command_args(char **args)
{
    if (!args)
        return;
    for (int i = 0; i < 10 && args[i]; i++) {
        free(args[i]);
    }
    free(args);
}

void save_data(server_t *server)
{
    FILE *file = fopen("myteams_data.save", "w");
    if (!file) {
        perror("Cannot save data");
        return;
    }
    fprintf(file, "USERS\n");
    user_t *user = server->users;
    while (user) {
        fprintf(file, "%s|%s\n", user->uuid, user->name);
        user = user->next;
    }
    fprintf(file, "TEAMS\n");
    team_t *team = server->teams;
    while (team) {
        fprintf(file, "%s|%s|%s\n", team->uuid, team->name, 
                team->description);
        team = team->next;
    }
    fprintf(file, "CHANNELS\n");
    channel_t *channel = server->channels;
    while (channel) {
        fprintf(file, "%s|%s|%s|%s\n", channel->uuid, channel->name,
                channel->description, channel->team_uuid);
        channel = channel->next;
    }
    fprintf(file, "MESSAGES\n");
    message_t *message = server->messages;
    while (message) {
        fprintf(file, "%s|%s|%s|%s|%ld\n", message->uuid, message->body,
                message->sender_uuid, message->receiver_uuid, 
                message->timestamp);
        message = message->next;
    }
    fclose(file);
    printf("Data saved successfully\n");
}

void load_data(server_t *server)
{
    FILE *file = fopen("myteams_data.save", "r");
    char line[BUFFER_SIZE * 2];
    char section[32] = "";

    if (!file) {
        printf("No save file found, starting fresh\n");
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, "USERS") == 0 || strcmp(line, "TEAMS") == 0 ||
            strcmp(line, "CHANNELS") == 0 || strcmp(line, "MESSAGES") == 0) {
            strcpy(section, line);
            continue;
        }
        if (strcmp(section, "USERS") == 0) {
            char *uuid = strtok(line, "|");
            char *name = strtok(NULL, "|");
            if (uuid && name) {
                user_t *user = malloc(sizeof(user_t));
                strcpy(user->uuid, uuid);
                strcpy(user->name, name);
                user->is_logged_in = 0;
                user->next = server->users;
                server->users = user;
            }
        }
    }
    fclose(file);
    printf("Data loaded successfully\n");
}