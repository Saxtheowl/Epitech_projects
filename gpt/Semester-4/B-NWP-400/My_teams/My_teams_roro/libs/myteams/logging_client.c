/*
** EPITECH PROJECT, 2025
** myteams logging (stub)
** File description:
**   Client logging API stubs (prints to stdout). Replace with official lib.
*/

#include <stdio.h>
#include "logging_client.h"

void client_print_users(const char *uuid, const char *name, int status)
{ fprintf(stdout, "USER %s %s %s\n", uuid, name, status?"online":"offline"); }
void client_print_user(const char *uuid, const char *name, int status)
{ fprintf(stdout, "USER_INFO %s %s %s\n", uuid, name, status?"online":"offline"); }
void client_print_message(const char *sender_uuid, const char *message_body)
{ fprintf(stdout, "MESSAGE %s %s\n", sender_uuid, message_body); }

void client_print_teams(const char *team_uuid, const char *name, const char *desc)
{ fprintf(stdout, "TEAM %s %s %s\n", team_uuid, name, desc); }
void client_print_channels(const char *channel_uuid, const char *name, const char *desc)
{ fprintf(stdout, "CHANNEL %s %s %s\n", channel_uuid, name, desc); }
void client_print_threads(const char *thread_uuid, const char *title, const char *message)
{ fprintf(stdout, "THREAD %s %s %s\n", thread_uuid, title, message); }
void client_print_reply(const char *reply_uuid, const char *author_uuid, const char *body)
{ fprintf(stdout, "REPLY %s %s %s\n", reply_uuid, author_uuid, body); }

void client_print_team(const char *team_uuid, const char *name, const char *desc)
{ fprintf(stdout, "TEAM_INFO %s %s %s\n", team_uuid, name, desc); }
void client_print_channel(const char *channel_uuid, const char *name, const char *desc)
{ fprintf(stdout, "CHANNEL_INFO %s %s %s\n", channel_uuid, name, desc); }
void client_print_thread(const char *thread_uuid, const char *title, const char *message)
{ fprintf(stdout, "THREAD_INFO %s %s %s\n", thread_uuid, title, message); }

void client_print_subscribed_team(const char *team_uuid, const char *team_name)
{ fprintf(stdout, "SUB_TEAM %s %s\n", team_uuid, team_name); }
void client_print_subscribed_user(const char *user_uuid, const char *user_name)
{ fprintf(stdout, "SUB_USER %s %s\n", user_uuid, user_name); }

