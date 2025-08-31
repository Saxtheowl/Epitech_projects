/*
** EPITECH PROJECT, 2024
** My_ls
** File description:
** Header file for my_ls command implementation
*/

#ifndef MY_LS_H
    #define MY_LS_H

    #define _GNU_SOURCE

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <pwd.h>
    #include <grp.h>
    #include <time.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <errno.h>
    #include <string.h>

typedef struct options_s {
    int a_flag;
    int l_flag;
    int R_flag;
    int d_flag;
    int r_flag;
    int t_flag;
} options_t;

typedef struct file_info_s {
    char *name;
    char *full_path;
    struct stat stat_info;
    struct file_info_s *next;
} file_info_t;

int parse_options(int argc, char **argv, options_t *opts);
int my_ls(options_t *opts, char **files, int file_count);
int list_directory(char *path, options_t *opts);
file_info_t *get_file_list(char *path, options_t *opts);
void sort_files(file_info_t **files, options_t *opts);
void print_files(file_info_t *files, options_t *opts, char *dir_path);
void print_long_format(file_info_t *file, options_t *opts);
void free_file_list(file_info_t *files);
int my_strcmp(const char *s1, const char *s2);
int my_strlen(const char *str);
void my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);
char *my_strdup(const char *src);
void my_putchar(char c);
void my_putstr(const char *str);
void my_putnbr(int nb);

#endif