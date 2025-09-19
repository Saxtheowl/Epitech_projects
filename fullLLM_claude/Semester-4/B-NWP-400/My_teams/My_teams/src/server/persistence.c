/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Data persistence functions
*/

#include "myteams.h"

void save_data(server_t *server)
{
    FILE *file = fopen("myteams_data.dat", "wb");
    if (!file) {
        perror("Failed to open data file for writing");
        return;
    }

    // Write counts
    fwrite(&server->user_count, sizeof(int), 1, file);
    fwrite(&server->team_count, sizeof(int), 1, file);
    fwrite(&server->channel_count, sizeof(int), 1, file);
    fwrite(&server->thread_count, sizeof(int), 1, file);
    fwrite(&server->comment_count, sizeof(int), 1, file);
    fwrite(&server->message_count, sizeof(int), 1, file);
    fwrite(&server->subscription_count, sizeof(int), 1, file);

    // Write data arrays
    fwrite(server->users, sizeof(user_t), server->user_count, file);
    fwrite(server->teams, sizeof(team_t), server->team_count, file);
    fwrite(server->channels, sizeof(channel_t), server->channel_count, file);
    fwrite(server->threads, sizeof(thread_t), server->thread_count, file);
    fwrite(server->comments, sizeof(comment_t), server->comment_count, file);
    fwrite(server->messages, sizeof(message_t), server->message_count, file);
    fwrite(server->subscriptions, sizeof(subscription_t), server->subscription_count, file);

    fclose(file);
    printf("Data saved successfully\n");
}

void load_data(server_t *server)
{
    FILE *file = fopen("myteams_data.dat", "rb");
    if (!file) {
        printf("No existing data file found, starting fresh\n");
        return;
    }

    // Read counts
    if (fread(&server->user_count, sizeof(int), 1, file) != 1 ||
        fread(&server->team_count, sizeof(int), 1, file) != 1 ||
        fread(&server->channel_count, sizeof(int), 1, file) != 1 ||
        fread(&server->thread_count, sizeof(int), 1, file) != 1 ||
        fread(&server->comment_count, sizeof(int), 1, file) != 1 ||
        fread(&server->message_count, sizeof(int), 1, file) != 1 ||
        fread(&server->subscription_count, sizeof(int), 1, file) != 1) {
        printf("Error reading data file header\n");
        fclose(file);
        return;
    }

    // Read data arrays
    fread(server->users, sizeof(user_t), server->user_count, file);
    fread(server->teams, sizeof(team_t), server->team_count, file);
    fread(server->channels, sizeof(channel_t), server->channel_count, file);
    fread(server->threads, sizeof(thread_t), server->thread_count, file);
    fread(server->comments, sizeof(comment_t), server->comment_count, file);
    fread(server->messages, sizeof(message_t), server->message_count, file);
    fread(server->subscriptions, sizeof(subscription_t), server->subscription_count, file);

    fclose(file);

    // Mark all users as disconnected on startup
    for (int i = 0; i < server->user_count; i++) {
        server->users[i].is_connected = false;
    }

    printf("Data loaded successfully: %d users, %d teams, %d channels\n",
           server->user_count, server->team_count, server->channel_count);
}