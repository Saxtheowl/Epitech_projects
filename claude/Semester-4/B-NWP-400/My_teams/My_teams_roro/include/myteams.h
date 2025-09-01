/*
** EPITECH PROJECT, 2025
** My_teams
** File description:
** Main header file for my teams application
*/

#ifndef MYTEAMS_H_
    #define MYTEAMS_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/select.h>
    // #include <uuid/uuid.h> // Not available, using custom UUID
    #include <time.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <signal.h>

    #define MAX_CLIENTS 100
    #define BUFFER_SIZE 1024
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

    typedef struct client_s {
        int fd;
        char uuid[37];
        char name[MAX_NAME_LENGTH + 1];
        int logged_in;
        struct sockaddr_in addr;
    } client_t;

    typedef struct team_s {
        char uuid[37];
        char name[MAX_NAME_LENGTH + 1];
        char description[MAX_DESCRIPTION_LENGTH + 1];
        struct team_s *next;
    } team_t;

    typedef struct channel_s {
        char uuid[37];
        char name[MAX_NAME_LENGTH + 1];
        char description[MAX_DESCRIPTION_LENGTH + 1];
        char team_uuid[37];
        struct channel_s *next;
    } channel_t;

    typedef struct thread_s {
        char uuid[37];
        char title[MAX_NAME_LENGTH + 1];
        char message[MAX_BODY_LENGTH + 1];
        char user_uuid[37];
        char channel_uuid[37];
        time_t timestamp;
        struct thread_s *next;
    } thread_t;

    typedef struct comment_s {
        char uuid[37];
        char body[MAX_BODY_LENGTH + 1];
        char user_uuid[37];
        char thread_uuid[37];
        time_t timestamp;
        struct comment_s *next;
    } comment_t;

    typedef struct message_s {
        char uuid[37];
        char body[MAX_BODY_LENGTH + 1];
        char sender_uuid[37];
        char receiver_uuid[37];
        time_t timestamp;
        struct message_s *next;
    } message_t;

    typedef struct user_s {
        char uuid[37];
        char name[MAX_NAME_LENGTH + 1];
        int is_logged_in;
        struct user_s *next;
    } user_t;

    typedef struct subscription_s {
        char user_uuid[37];
        char team_uuid[37];
        struct subscription_s *next;
    } subscription_t;

    typedef struct server_s {
        int socket;
        client_t clients[MAX_CLIENTS];
        int nb_clients;
        user_t *users;
        team_t *teams;
        channel_t *channels;
        thread_t *threads;
        comment_t *comments;
        message_t *messages;
        subscription_t *subscriptions;
    } server_t;

    // Server functions
    int init_server(int port);
    void handle_clients(server_t *server);
    void handle_new_connection(server_t *server);
    void handle_client_message(server_t *server, int client_idx);
    void disconnect_client(server_t *server, int client_idx);

    // Protocol functions
    void process_command(server_t *server, int client_idx, char *command);
    void cmd_login(server_t *server, int client_idx, char *username);
    void cmd_logout(server_t *server, int client_idx);
    void cmd_users(server_t *server, int client_idx);
    void cmd_user(server_t *server, int client_idx, char *user_uuid);
    void cmd_send(server_t *server, int client_idx, char *user_uuid, 
                  char *message);
    void cmd_messages(server_t *server, int client_idx, char *user_uuid);
    void cmd_subscribe(server_t *server, int client_idx, char *team_uuid);
    void cmd_unsubscribe(server_t *server, int client_idx, char *team_uuid);
    void cmd_subscribed(server_t *server, int client_idx, char *team_uuid);
    void cmd_create(server_t *server, int client_idx, char **args);
    void cmd_list(server_t *server, int client_idx);
    void cmd_info(server_t *server, int client_idx);

    // Data management
    user_t *create_user(const char *name);
    team_t *create_team(const char *name, const char *description);
    channel_t *create_channel(const char *name, const char *description,
                              const char *team_uuid);
    thread_t *create_thread(const char *title, const char *message,
                            const char *user_uuid, const char *channel_uuid);
    comment_t *create_comment(const char *body, const char *user_uuid,
                              const char *thread_uuid);
    message_t *create_message(const char *body, const char *sender_uuid,
                              const char *receiver_uuid);

    // Helper functions
    void generate_uuid(char *uuid_str);
    void send_response(int fd, const char *response);
    char **parse_command(const char *command);
    void free_command_args(char **args);
    client_t *get_client_by_uuid(server_t *server, const char *uuid);
    user_t *get_user_by_uuid(server_t *server, const char *uuid);
    user_t *get_user_by_name(server_t *server, const char *name);

    // Persistence
    void save_data(server_t *server);
    void load_data(server_t *server);

    // Client functions
    int connect_to_server(const char *ip, int port);
    void client_loop(int server_fd);
    void handle_server_message(int server_fd);
    void handle_user_input(int server_fd);

#endif /* !MYTEAMS_H_ */