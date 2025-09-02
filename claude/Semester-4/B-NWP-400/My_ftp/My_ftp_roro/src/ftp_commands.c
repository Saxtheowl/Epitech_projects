/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** FTP command implementations
*/

#include "myftp.h"

void cmd_user(server_t *server, int client_index, const char *args)
{
    client_t *client = &server->clients[client_index];
    int fd = server->fds[client_index].fd;

    if (!args) {
        send_response(fd, 501, "USERNAME required");
        return;
    }

    if (strcasecmp(args, "anonymous") == 0) {
        strncpy(client->username, "anonymous", sizeof(client->username) - 1);
        send_response(fd, 331, "User name okay, need password");
    } else {
        send_response(fd, 530, "Only anonymous login is supported");
    }
}

void cmd_pass(server_t *server, int client_index, const char *args)
{
    client_t *client = &server->clients[client_index];
    int fd = server->fds[client_index].fd;

    (void)args;

    if (strlen(client->username) == 0) {
        send_response(fd, 503, "Login with USER first");
        return;
    }

    if (strcmp(client->username, "anonymous") == 0) {
        client->state = CLIENT_AUTHENTICATED;
        send_response(fd, 230, "User logged in, proceed");
    } else {
        send_response(fd, 530, "Login incorrect");
    }
}

void cmd_pwd(server_t *server, int client_index, const char *args)
{
    client_t *client = &server->clients[client_index];
    int fd = server->fds[client_index].fd;
    char response[BUFFER_SIZE];

    (void)args;

    if (client->state != CLIENT_AUTHENTICATED) {
        send_response(fd, 530, "Please login with USER and PASS");
        return;
    }

    snprintf(response, sizeof(response), "\"%s\" is current directory", 
             client->current_dir);
    send_response(fd, 257, response);
}

void cmd_cwd(server_t *server, int client_index, const char *args)
{
    client_t *client = &server->clients[client_index];
    int fd = server->fds[client_index].fd;
    char *new_path;
    struct stat st;

    if (client->state != CLIENT_AUTHENTICATED) {
        send_response(fd, 530, "Please login with USER and PASS");
        return;
    }

    if (!args) {
        send_response(fd, 501, "CWD command needs a directory name");
        return;
    }

    new_path = get_absolute_path(client->root_dir, client->current_dir, args);
    if (!new_path || !is_valid_path(client->root_dir, new_path)) {
        send_response(fd, 550, "Requested action not taken");
        free(new_path);
        return;
    }

    if (stat(new_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        send_response(fd, 550, "Requested action not taken");
        free(new_path);
        return;
    }

    char *relative_path = new_path + strlen(client->root_dir);
    if (*relative_path == '\0')
        relative_path = "/";
    
    strncpy(client->current_dir, relative_path, PATH_SIZE - 1);
    send_response(fd, 250, "Requested file action okay, completed");
    free(new_path);
}

void cmd_list(server_t *server, int client_index, const char *args)
{
    client_t *client = &server->clients[client_index];
    int fd = server->fds[client_index].fd;
    char buffer[BUFFER_SIZE];
    char *path;
    int data_fd = -1;

    (void)args;

    if (client->state != CLIENT_AUTHENTICATED) {
        send_response(fd, 530, "Please login with USER and PASS");
        return;
    }

    path = get_absolute_path(client->root_dir, client->current_dir, ".");
    if (!path || !is_valid_path(client->root_dir, path)) {
        send_response(fd, 550, "Requested action not taken");
        free(path);
        return;
    }

    if (client->mode == MODE_ACTIVE) {
        data_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (data_fd < 0 || connect(data_fd, (struct sockaddr*)&client->data_addr, 
                                  sizeof(client->data_addr)) < 0) {
            send_response(fd, 425, "Can't open data connection");
            if (data_fd >= 0) close(data_fd);
            free(path);
            return;
        }
    } else if (client->data_fd >= 0) {
        data_fd = accept(client->data_fd, NULL, NULL);
        close(client->data_fd);
        client->data_fd = -1;
        if (data_fd < 0) {
            send_response(fd, 425, "Can't open data connection");
            free(path);
            return;
        }
    } else {
        send_response(fd, 425, "Use PORT or PASV first");
        free(path);
        return;
    }

    send_response(fd, 150, "Here comes the directory listing");

    format_file_list(buffer, path);
    write(data_fd, buffer, strlen(buffer));
    close(data_fd);

    send_response(fd, 226, "Directory send OK");
    free(path);
}

void cmd_retr(server_t *server, int client_index, const char *args)
{
    client_t *client = &server->clients[client_index];
    int fd = server->fds[client_index].fd;

    if (client->state != CLIENT_AUTHENTICATED) {
        send_response(fd, 530, "Please login with USER and PASS");
        return;
    }

    if (!args) {
        send_response(fd, 501, "RETR command needs a filename");
        return;
    }

    send_response(fd, 550, "RETR not implemented yet");
}

void cmd_stor(server_t *server, int client_index, const char *args)
{
    client_t *client = &server->clients[client_index];
    int fd = server->fds[client_index].fd;

    if (client->state != CLIENT_AUTHENTICATED) {
        send_response(fd, 530, "Please login with USER and PASS");
        return;
    }

    if (!args) {
        send_response(fd, 501, "STOR command needs a filename");
        return;
    }

    send_response(fd, 550, "STOR not implemented yet");
}

void cmd_quit(server_t *server, int client_index, const char *args)
{
    int fd = server->fds[client_index].fd;

    (void)server;
    (void)args;

    send_response(fd, 221, "Goodbye");
}

void cmd_port(server_t *server, int client_index, const char *args)
{
    client_t *client = &server->clients[client_index];
    int fd = server->fds[client_index].fd;
    int h1, h2, h3, h4, p1, p2;
    char ip_str[16];

    if (client->state != CLIENT_AUTHENTICATED) {
        send_response(fd, 530, "Please login with USER and PASS");
        return;
    }

    if (!args || sscanf(args, "%d,%d,%d,%d,%d,%d", &h1, &h2, &h3, &h4, &p1, &p2) != 6) {
        send_response(fd, 501, "Illegal PORT command");
        return;
    }

    snprintf(ip_str, sizeof(ip_str), "%d.%d.%d.%d", h1, h2, h3, h4);
    client->data_addr.sin_family = AF_INET;
    client->data_addr.sin_addr.s_addr = inet_addr(ip_str);
    client->data_addr.sin_port = htons((p1 << 8) + p2);
    client->mode = MODE_ACTIVE;

    if (client->data_fd >= 0) {
        close(client->data_fd);
        client->data_fd = -1;
    }

    send_response(fd, 200, "PORT command successful");
}

void cmd_pasv(server_t *server, int client_index, const char *args)
{
    client_t *client = &server->clients[client_index];
    int fd = server->fds[client_index].fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    int pasv_fd;
    char response[256];
    int port;

    (void)args;

    if (client->state != CLIENT_AUTHENTICATED) {
        send_response(fd, 530, "Please login with USER and PASS");
        return;
    }

    if (client->data_fd >= 0) {
        close(client->data_fd);
        client->data_fd = -1;
    }

    pasv_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (pasv_fd < 0) {
        send_response(fd, 425, "Can't open passive connection");
        return;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0;

    if (bind(pasv_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(pasv_fd);
        send_response(fd, 425, "Can't open passive connection");
        return;
    }

    if (listen(pasv_fd, 1) < 0) {
        close(pasv_fd);
        send_response(fd, 425, "Can't open passive connection");
        return;
    }

    if (getsockname(pasv_fd, (struct sockaddr*)&addr, &addr_len) < 0) {
        close(pasv_fd);
        send_response(fd, 425, "Can't open passive connection");
        return;
    }

    port = ntohs(addr.sin_port);
    client->data_fd = pasv_fd;
    client->mode = MODE_PASSIVE;

    snprintf(response, sizeof(response), 
             "Entering Passive Mode (127,0,0,1,%d,%d)", 
             port >> 8, port & 0xff);
    send_response(fd, 227, response);
}

void cmd_type(server_t *server, int client_index, const char *args)
{
    int fd = server->fds[client_index].fd;

    (void)server;

    if (!args) {
        send_response(fd, 501, "TYPE needs an argument");
        return;
    }

    if (strcasecmp(args, "I") == 0) {
        send_response(fd, 200, "Type set to I");
    } else if (strcasecmp(args, "A") == 0) {
        send_response(fd, 200, "Type set to A");
    } else {
        send_response(fd, 504, "Type not supported");
    }
}

void cmd_mode(server_t *server, int client_index, const char *args)
{
    int fd = server->fds[client_index].fd;

    (void)server;

    if (!args || strcasecmp(args, "S") != 0) {
        send_response(fd, 504, "Mode not supported");
        return;
    }

    send_response(fd, 200, "Mode set to S");
}

void cmd_stru(server_t *server, int client_index, const char *args)
{
    int fd = server->fds[client_index].fd;

    (void)server;

    if (!args || strcasecmp(args, "F") != 0) {
        send_response(fd, 504, "Structure not supported");
        return;
    }

    send_response(fd, 200, "Structure set to F");
}

void cmd_noop(server_t *server, int client_index, const char *args)
{
    int fd = server->fds[client_index].fd;

    (void)server;
    (void)args;

    send_response(fd, 200, "NOOP command successful");
}