/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** fridge header
*/

#ifndef FRIDGE_H_
    #define FRIDGE_H_

    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_INGREDIENTS 8
    #define MAX_LINE_LENGTH 1024

    typedef struct {
        char name[20];
        int quantity;
    } ingredient_t;

    typedef struct {
        ingredient_t ingredients[MAX_INGREDIENTS];
        int count;
    } fridge_t;

    int my_strlen(char *str);
    char *my_strcpy(char *dest, char *src);
    int my_strcmp(char *s1, char *s2);
    char *my_strdup(char *src);
    int my_atoi(char *str);
    char *my_itoa(int n);
    void my_putstr(char *str);
    void my_putchar(char c);

    void init_fridge(fridge_t *fridge);
    int load_fridge(fridge_t *fridge);
    int save_fridge(fridge_t *fridge);
    void display_fridge(fridge_t *fridge);
    int add_to_fridge(fridge_t *fridge, char *ingredient, int quantity);
    int find_ingredient(fridge_t *fridge, char *name);
    int make_pizza(fridge_t *fridge);
    int make_pasta(fridge_t *fridge);
    int parse_command(char *line, char **cmd, char **arg1, char **arg2);
    int fridge_main(void);

#endif