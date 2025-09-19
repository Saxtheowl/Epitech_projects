/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** Utility functions for FTP server
*/

#include "myftp.h"

void send_response(int socket, char *response)
{
    write(socket, response, strlen(response));
    printf("Response: %s", response);
}

int is_valid_path(char *base, char *path)
{
    char *real_base, *real_path;
    int result = 0;

    if (!base || !path) {
        return 0;
    }

    real_base = realpath(base, NULL);
    real_path = realpath(path, NULL);

    if (real_base && real_path) {
        if (strncmp(real_path, real_base, strlen(real_base)) == 0) {
            result = 1;
        }
    }

    if (real_base) free(real_base);
    if (real_path) free(real_path);

    return result;
}

char *get_absolute_path(char *base, char *path)
{
    char *result;

    if (!base || !path) {
        return NULL;
    }

    if (path[0] == '/') {
        result = strdup(path);
    } else {
        result = malloc(strlen(base) + strlen(path) + 2);
        if (result) {
            sprintf(result, "%s/%s", base, path);
        }
    }

    return result;
}