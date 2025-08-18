#ifndef MY_LS_H
#define MY_LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#define OPT_LONG    0x01
#define OPT_ALL     0x02
#define OPT_RECUR   0x04
#define OPT_DIR     0x08
#define OPT_REV     0x10
#define OPT_TIME    0x20

typedef struct file_info_s {
    char *name;
    char *path;
    struct stat st;
    struct file_info_s *next;
} file_info_t;

typedef struct options_s {
    int flags;
    char **files;
    int file_count;
} options_t;

int my_putchar(char c);
int my_putstr(char *str);
int my_strlen(char *str);
char *my_strdup(char *str);
int my_strcmp(char *s1, char *s2);

options_t *parse_options(int ac, char **av);
void free_options(options_t *opts);

file_info_t *create_file_info(char *name, char *path);
void free_file_list(file_info_t *list);
file_info_t *add_file_to_list(file_info_t *list, file_info_t *new_file);

int list_directory(char *path, options_t *opts);
int list_file(char *path, options_t *opts);

file_info_t *sort_files(file_info_t *list, options_t *opts);

void print_long_format(file_info_t *file);
void print_simple_format(file_info_t *list, options_t *opts);

void print_permissions(mode_t mode);
char get_file_type(mode_t mode);
void print_number(long n);

#endif