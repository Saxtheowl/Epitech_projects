/*
** EPITECH PROJECT, 2025
** Cesar
** File description:
** file handling functions
*/

#include "cesar.h"

char *read_file_content(char *filename)
{
    int fd;
    struct stat file_stat;
    char *content;
    int bytes_read;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        write(STDERR_FILENO, "cesar: ", 7);
        write(STDERR_FILENO, filename, my_strlen(filename));
        write(STDERR_FILENO, ": No such file or directory\n", 28);
        return NULL;
    }
    if (stat(filename, &file_stat) == -1) {
        close(fd);
        write(STDERR_FILENO, "cesar: cannot get file size\n", 29);
        return NULL;
    }
    content = malloc(sizeof(char) * (file_stat.st_size + 1));
    if (!content) {
        close(fd);
        write(STDERR_FILENO, "cesar: memory allocation failed\n", 33);
        return NULL;
    }
    bytes_read = read(fd, content, file_stat.st_size);
    if (bytes_read == -1) {
        free(content);
        close(fd);
        write(STDERR_FILENO, "cesar: cannot read file\n", 25);
        return NULL;
    }
    content[bytes_read] = '\0';
    close(fd);
    return content;
}

int encrypt_file(char *filename, int key)
{
    char *content = read_file_content(filename);
    char *encrypted;
    int fd;

    if (!content)
        return 84;
    encrypted = caesar_encrypt_string(content, key);
    free(content);
    if (!encrypted) {
        write(STDERR_FILENO, "cesar: encryption failed\n", 26);
        return 84;
    }
    fd = open("crypt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        free(encrypted);
        write(STDERR_FILENO, "cesar: cannot create crypt file\n", 33);
        return 84;
    }
    write(fd, encrypted, my_strlen(encrypted));
    close(fd);
    if (chmod("crypt", 0400) == -1) {
        free(encrypted);
        write(STDERR_FILENO, "cesar: cannot set read-only permissions\n", 41);
        return 84;
    }
    free(encrypted);
    return 0;
}

int encrypt_string(char *str, int key)
{
    char *encrypted = caesar_encrypt_string(str, key);
    int fd;

    if (!encrypted) {
        write(STDERR_FILENO, "cesar: encryption failed\n", 26);
        return 84;
    }
    fd = open("crypt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        free(encrypted);
        write(STDERR_FILENO, "cesar: cannot create crypt file\n", 33);
        return 84;
    }
    write(fd, encrypted, my_strlen(encrypted));
    close(fd);
    if (chmod("crypt", 0400) == -1) {
        free(encrypted);
        write(STDERR_FILENO, "cesar: cannot set read-only permissions\n", 41);
        return 84;
    }
    free(encrypted);
    return 0;
}