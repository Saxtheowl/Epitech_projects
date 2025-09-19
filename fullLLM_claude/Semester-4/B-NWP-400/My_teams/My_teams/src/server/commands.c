/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Command implementations
*/

#include "myteams.h"

void cmd_login(server_t *server, client_t *client, const char *username)
{
    if (client->is_authenticated) {
        send_error(client->socket_fd, "Already logged in");
        return;
    }

    if (strlen(username) >= MAX_NAME_LENGTH) {
        send_error(client->socket_fd, "Username too long");
        return;
    }

    // Check if user exists
    user_t *existing_user = find_user_by_name(server, username);
    if (existing_user) {
        if (existing_user->is_connected) {
            send_error(client->socket_fd, "User already connected");
            return;
        }
        // Reconnect existing user
        strcpy(client->user_uuid, existing_user->uuid);
        existing_user->is_connected = true;
        existing_user->socket_fd = client->socket_fd;
    } else {
        // Create new user
        if (server->user_count >= MAX_CLIENTS) {
            send_error(client->socket_fd, "Server full");
            return;
        }

        user_t *new_user = &server->users[server->user_count];
        generate_uuid(new_user->uuid);
        strcpy(new_user->name, username);
        new_user->is_connected = true;
        new_user->socket_fd = client->socket_fd;

        strcpy(client->user_uuid, new_user->uuid);
        server->user_count++;
    }

    client->is_authenticated = true;

    // Send login confirmation
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "LOGIN_SUCCESS %s %s", client->user_uuid, username);
    send_response(client->socket_fd, response);

    printf("User %s logged in\n", username);
}

void cmd_logout(server_t *server, client_t *client)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    user_t *user = find_user_by_uuid(server, client->user_uuid);
    if (user) {
        user->is_connected = false;
        printf("User %s logged out\n", user->name);
    }

    client->is_authenticated = false;
    memset(client->user_uuid, 0, UUID_STR_LEN);

    send_response(client->socket_fd, "LOGOUT_SUCCESS");
}

void cmd_users(server_t *server, client_t *client)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    char response[BUFFER_SIZE];
    strcpy(response, "USERS_LIST");

    for (int i = 0; i < server->user_count; i++) {
        if (server->users[i].is_connected) {
            char user_info[256];
            snprintf(user_info, sizeof(user_info), " %s:%s",
                     server->users[i].uuid, server->users[i].name);
            strcat(response, user_info);
        }
    }

    send_response(client->socket_fd, response);
}

void cmd_user(server_t *server, client_t *client, const char *user_uuid)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    user_t *user = find_user_by_uuid(server, user_uuid);
    if (!user) {
        send_error(client->socket_fd, "User not found");
        return;
    }

    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "USER_INFO %s %s %s",
             user->uuid, user->name, user->is_connected ? "online" : "offline");
    send_response(client->socket_fd, response);
}

void cmd_send(server_t *server, client_t *client, const char *user_uuid, const char *message_body)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    if (strlen(message_body) >= MAX_BODY_LENGTH) {
        send_error(client->socket_fd, "Message too long");
        return;
    }

    user_t *recipient = find_user_by_uuid(server, user_uuid);
    if (!recipient) {
        send_error(client->socket_fd, "User not found");
        return;
    }

    // Store message
    if (server->message_count >= MAX_CLIENTS * 1000) {
        send_error(client->socket_fd, "Message storage full");
        return;
    }

    message_t *msg = &server->messages[server->message_count];
    generate_uuid(msg->uuid);
    strcpy(msg->sender_uuid, client->user_uuid);
    strcpy(msg->receiver_uuid, user_uuid);
    strcpy(msg->body, message_body);
    msg->timestamp = time(NULL);
    server->message_count++;

    // Send to recipient if online
    if (recipient->is_connected) {
        char notification[BUFFER_SIZE];
        user_t *sender = find_user_by_uuid(server, client->user_uuid);
        snprintf(notification, sizeof(notification), "MESSAGE_RECEIVED %s %s \"%s\"",
                 sender->uuid, sender->name, message_body);
        send_response(recipient->socket_fd, notification);
    }

    send_response(client->socket_fd, "MESSAGE_SENT");
}

void cmd_messages(server_t *server, client_t *client, const char *user_uuid)
{
    if (!client->is_authenticated) {
        send_error(client->socket_fd, "Not logged in");
        return;
    }

    user_t *other_user = find_user_by_uuid(server, user_uuid);
    if (!other_user) {
        send_error(client->socket_fd, "User not found");
        return;
    }

    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "MESSAGES_LIST %s", user_uuid);
    send_response(client->socket_fd, response);

    // Send all messages between the two users
    for (int i = 0; i < server->message_count; i++) {
        message_t *msg = &server->messages[i];
        if ((strcmp(msg->sender_uuid, client->user_uuid) == 0 &&
             strcmp(msg->receiver_uuid, user_uuid) == 0) ||
            (strcmp(msg->sender_uuid, user_uuid) == 0 &&
             strcmp(msg->receiver_uuid, client->user_uuid) == 0)) {

            char msg_info[BUFFER_SIZE];
            snprintf(msg_info, sizeof(msg_info), "MESSAGE %s %s %ld \"%s\"",
                     msg->uuid, msg->sender_uuid, msg->timestamp, msg->body);
            send_response(client->socket_fd, msg_info);
        }
    }

    send_response(client->socket_fd, "MESSAGES_END");
}

void cmd_help(server_t *server, client_t *client)
{
    (void)server;

    const char *help_text =
        "HELP\n"
        "/help: Show this help\n"
        "/login \"username\": Login with username\n"
        "/logout: Logout from server\n"
        "/users: List all connected users\n"
        "/user \"uuid\": Show user information\n"
        "/send \"uuid\" \"message\": Send private message\n"
        "/messages \"uuid\": Show message history with user\n"
        "/subscribe \"uuid\": Subscribe to team\n"
        "/subscribed [\"uuid\"]: List subscriptions or team members\n"
        "/unsubscribe \"uuid\": Unsubscribe from team\n"
        "/use [\"team\"] [\"channel\"] [\"thread\"]: Set context\n"
        "/create: Create resource based on context\n"
        "/list: List resources based on context\n"
        "/info: Show information based on context";

    send_response(client->socket_fd, help_text);
}