/*
** EPITECH PROJECT, 2025
** myteams logging (stub)
** File description:
**   Client logging API (stubs)
*/

#ifndef LOGGING_CLIENT_H
#define LOGGING_CLIENT_H

void client_print_users(const char *uuid, const char *name, int status);
void client_print_user(const char *uuid, const char *name, int status);
void client_print_message(const char *sender_uuid, const char *message_body);

void client_print_teams(const char *team_uuid, const char *name, const char *desc);
void client_print_channels(const char *channel_uuid, const char *name, const char *desc);
void client_print_threads(const char *thread_uuid, const char *title, const char *message);
void client_print_reply(const char *reply_uuid, const char *author_uuid, const char *body);

void client_print_team(const char *team_uuid, const char *name, const char *desc);
void client_print_channel(const char *channel_uuid, const char *name, const char *desc);
void client_print_thread(const char *thread_uuid, const char *title, const char *message);

void client_print_subscribed_team(const char *team_uuid, const char *team_name);
void client_print_subscribed_user(const char *user_uuid, const char *user_name);

#endif /* LOGGING_CLIENT_H */

