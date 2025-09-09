#ifndef MY_LS_H
#define MY_LS_H

#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

typedef struct {
    int all;        // -a
    int long_format; // -l
    int recursive;   // -R
    int directory;   // -d
    int reverse;     // -r
    int sort_time;   // -t
} options_t;

typedef struct {
    char *name;
    struct stat stat;
    char *path;
} file_info_t;

int my_strlen(char const *str);
int my_strcmp(char const *s1, char const *s2);
char *my_strdup(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
void my_putchar(char c);
void my_putstr(char const *str);
void my_put_nbr(int nb);

options_t parse_options(int argc, char **argv, char ***files, int *file_count);
int list_directory(char const *path, options_t options);
int list_file(char const *path, options_t options);
void print_long_format(file_info_t *file);
void print_permissions(mode_t mode);
int compare_files(file_info_t *a, file_info_t *b, options_t options);
void sort_files(file_info_t *files, int count, options_t options);
void free_file_info(file_info_t *files, int count);

#endif