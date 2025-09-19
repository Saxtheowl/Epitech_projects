/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** FTP commands implementation
*/

#include "myftp.h"

void handle_user(client_t *client, char *arg)
{
    if (!arg) {
        send_response(client->socket, "501 Syntax error in parameters.\r\n");
        return;
    }

    if (strcasecmp(arg, "anonymous") == 0) {
        client->user_valid = 1;
        client->authenticated = 0;
        send_response(client->socket, "331 Please specify the password.\r\n");
    } else {
        send_response(client->socket, "530 Login incorrect.\r\n");
    }
}

void handle_pass(client_t *client, char *arg)
{
    if (client->user_valid == 1 && client->authenticated == 0) {
        client->authenticated = 1;
        send_response(client->socket, "230 Login successful.\r\n");
    } else {
        send_response(client->socket, "503 Login with USER first.\r\n");
    }
}

void handle_pwd(client_t *client)
{
    char response[BUFFER_SIZE];

    if (!client->authenticated) {
        send_response(client->socket, "530 Please login with USER and PASS.\r\n");
        return;
    }

    snprintf(response, sizeof(response), "257 \"%s\" is the current directory.\r\n",
             client->current_dir);
    send_response(client->socket, response);
}

void handle_cwd(client_t *client, char *path)
{
    char *new_path;
    struct stat st;

    if (!client->authenticated) {
        send_response(client->socket, "530 Please login with USER and PASS.\r\n");
        return;
    }

    if (!path) {
        send_response(client->socket, "501 Syntax error in parameters.\r\n");
        return;
    }

    new_path = get_absolute_path(client->current_dir, path);
    if (!new_path || !is_valid_path(client->home_dir, new_path)) {
        send_response(client->socket, "550 Failed to change directory.\r\n");
        if (new_path) free(new_path);
        return;
    }

    if (stat(new_path, &st) == -1 || !S_ISDIR(st.st_mode)) {
        send_response(client->socket, "550 Failed to change directory.\r\n");
        free(new_path);
        return;
    }

    strcpy(client->current_dir, new_path);
    send_response(client->socket, "250 Directory successfully changed.\r\n");
    free(new_path);
}

void handle_list(client_t *client, char *path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char full_path[1024];
    char list_path[1024];
    int data_socket;

    if (!client->authenticated) {
        send_response(client->socket, "530 Please login with USER and PASS.\r\n");
        return;
    }

    if (client->passive_socket == -1) {
        send_response(client->socket, "425 Use PASV first.\r\n");
        return;
    }

    strcpy(list_path, path ? path : client->current_dir);
    if (path && path[0] != '/') {
        snprintf(list_path, sizeof(list_path), "%s/%s", client->current_dir, path);
    }

    data_socket = accept(client->passive_socket, NULL, NULL);
    if (data_socket == -1) {
        send_response(client->socket, "425 Failed to establish connection.\r\n");
        return;
    }

    send_response(client->socket, "150 Here comes the directory listing.\r\n");

    dir = opendir(list_path);
    if (dir) {
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            snprintf(full_path, sizeof(full_path), "%s/%s", list_path, entry->d_name);
            if (stat(full_path, &st) == 0) {
                char line[1024];
                char perms[11] = "----------";
                if (S_ISDIR(st.st_mode)) perms[0] = 'd';
                if (st.st_mode & S_IRUSR) perms[1] = 'r';
                if (st.st_mode & S_IWUSR) perms[2] = 'w';
                if (st.st_mode & S_IXUSR) perms[3] = 'x';
                if (st.st_mode & S_IRGRP) perms[4] = 'r';
                if (st.st_mode & S_IWGRP) perms[5] = 'w';
                if (st.st_mode & S_IXGRP) perms[6] = 'x';
                if (st.st_mode & S_IROTH) perms[7] = 'r';
                if (st.st_mode & S_IWOTH) perms[8] = 'w';
                if (st.st_mode & S_IXOTH) perms[9] = 'x';

                snprintf(line, sizeof(line), "%s 1 owner group %8ld Jan  1 00:00 %s\r\n",
                         perms, st.st_size, entry->d_name);
                write(data_socket, line, strlen(line));
            }
        }
        closedir(dir);
    }

    close(data_socket);
    close(client->passive_socket);
    client->passive_socket = -1;
    send_response(client->socket, "226 Directory send OK.\r\n");
}

void handle_pasv(client_t *client)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    int port;
    char response[BUFFER_SIZE];

    if (!client->authenticated) {
        send_response(client->socket, "530 Please login with USER and PASS.\r\n");
        return;
    }

    client->passive_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->passive_socket == -1) {
        send_response(client->socket, "425 Can't open passive connection.\r\n");
        return;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0;

    if (bind(client->passive_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(client->passive_socket);
        client->passive_socket = -1;
        send_response(client->socket, "425 Can't open passive connection.\r\n");
        return;
    }

    if (listen(client->passive_socket, 1) == -1) {
        close(client->passive_socket);
        client->passive_socket = -1;
        send_response(client->socket, "425 Can't open passive connection.\r\n");
        return;
    }

    if (getsockname(client->passive_socket, (struct sockaddr *)&addr, &addr_len) == -1) {
        close(client->passive_socket);
        client->passive_socket = -1;
        send_response(client->socket, "425 Can't open passive connection.\r\n");
        return;
    }

    port = ntohs(addr.sin_port);
    snprintf(response, sizeof(response),
             "227 Entering Passive Mode (127,0,0,1,%d,%d).\r\n",
             port / 256, port % 256);
    send_response(client->socket, response);
}

void handle_quit(client_t *client)
{
    send_response(client->socket, "221 Goodbye.\r\n");
}