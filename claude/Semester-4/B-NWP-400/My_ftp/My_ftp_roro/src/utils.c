/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
** Utility functions for path handling and file operations
*/

#include "myftp.h"

char *get_absolute_path(const char *root, const char *current, const char *target)
{
    char *result;
    char temp_path[PATH_SIZE];
    char *token;
    char *saveptr;
    int depth = 0;
    char *parts[256];

    if (!root || !current || !target)
        return NULL;

    result = malloc(PATH_SIZE);
    if (!result)
        return NULL;

    if (target[0] == '/') {
        strcpy(temp_path, target);
    } else {
        snprintf(temp_path, sizeof(temp_path), "%s/%s", current, target);
    }

    token = strtok_r(temp_path, "/", &saveptr);
    while (token && depth < 256) {
        if (strcmp(token, ".") == 0) {
            continue;
        } else if (strcmp(token, "..") == 0) {
            if (depth > 0)
                depth--;
        } else {
            parts[depth++] = token;
        }
        token = strtok_r(NULL, "/", &saveptr);
    }

    strcpy(result, root);
    for (int i = 0; i < depth; i++) {
        strcat(result, "/");
        strcat(result, parts[i]);
    }

    return result;
}

int is_valid_path(const char *root, const char *path)
{
    if (!root || !path)
        return 0;

    if (strncmp(path, root, strlen(root)) != 0)
        return 0;

    if (strstr(path, "..") != NULL)
        return 0;

    return 1;
}

void format_file_list(char *buffer, const char *path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char full_path[PATH_SIZE];
    char perms[11];
    char time_str[20];
    struct tm *tm_info;

    buffer[0] = '\0';

    dir = opendir(path);
    if (!dir) {
        strcat(buffer, "total 0\r\n");
        return;
    }

    strcat(buffer, "total 0\r\n");

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        if (stat(full_path, &st) != 0)
            continue;

        memset(perms, 0, sizeof(perms));
        perms[0] = S_ISDIR(st.st_mode) ? 'd' : '-';
        perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
        perms[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
        perms[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
        perms[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
        perms[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
        perms[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
        perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
        perms[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
        perms[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
        perms[10] = '\0';

        tm_info = localtime(&st.st_mtime);
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", tm_info);

        snprintf(buffer + strlen(buffer), BUFFER_SIZE - strlen(buffer),
                "%s    1 ftp      ftp      %8ld %s %s\r\n",
                perms, st.st_size, time_str, entry->d_name);
    }

    closedir(dir);
}