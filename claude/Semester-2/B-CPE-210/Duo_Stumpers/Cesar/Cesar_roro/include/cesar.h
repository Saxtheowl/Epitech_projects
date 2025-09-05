/*
** EPITECH PROJECT, 2025
** Cesar
** File description:
** cesar header
*/

#ifndef CESAR_H_
    #define CESAR_H_

    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_BUFFER_SIZE 4096

    int my_strlen(char *str);
    char *my_strcpy(char *dest, char *src);
    int my_strcmp(char *s1, char *s2);
    char *my_strdup(char *src);
    int my_atoi(char *str);
    void my_putstr(char *str);
    void my_putchar(char c);

    char caesar_encrypt_char(char c, int key);
    char *caesar_encrypt_string(char *str, int key);
    char *read_file_content(char *filename);
    int encrypt_file(char *filename, int key);
    int encrypt_string(char *str, int key);
    int parse_args(int argc, char **argv, char **target, int *key, int *is_file);
    int cesar_main(int argc, char **argv);

#endif