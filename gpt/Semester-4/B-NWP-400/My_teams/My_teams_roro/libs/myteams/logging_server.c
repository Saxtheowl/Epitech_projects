/*
** EPITECH PROJECT, 2025
** myteams logging (stub)
** File description:
**   Server logging API stubs (no output). Replace with official lib.
*/

#include "logging_server.h"

void server_event_user_created(const char *user_uuid, const char *user_name) { (void)user_uuid; (void)user_name; }
void server_event_user_logged_in(const char *user_uuid) { (void)user_uuid; }
void server_event_user_logged_out(const char *user_uuid) { (void)user_uuid; }

void server_event_team_created(const char *team_uuid, const char *team_name, const char *user_uuid) { (void)team_uuid; (void)team_name; (void)user_uuid; }
void server_event_channel_created(const char *team_uuid, const char *channel_uuid, const char *channel_name) { (void)team_uuid; (void)channel_uuid; (void)channel_name; }
void server_event_thread_created(const char *channel_uuid, const char *thread_uuid, const char *user_uuid, const char *thread_title, const char *thread_body) { (void)channel_uuid; (void)thread_uuid; (void)user_uuid; (void)thread_title; (void)thread_body; }
void server_event_reply_created(const char *thread_uuid, const char *user_uuid, const char *reply_body) { (void)thread_uuid; (void)user_uuid; (void)reply_body; }

void server_event_team_subscribed(const char *team_uuid, const char *user_uuid) { (void)team_uuid; (void)user_uuid; }
void server_event_team_unsubscribed(const char *team_uuid, const char *user_uuid) { (void)team_uuid; (void)user_uuid; }

void server_event_private_message_sended(const char *sender_uuid, const char *receiver_uuid, const char *message_body) { (void)sender_uuid; (void)receiver_uuid; (void)message_body; }

