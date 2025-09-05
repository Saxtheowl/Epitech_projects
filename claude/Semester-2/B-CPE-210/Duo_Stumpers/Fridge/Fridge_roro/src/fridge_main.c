/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** main fridge program
*/

#include "fridge.h"

static char *read_input_line(void)
{
    char buffer[MAX_LINE_LENGTH];
    int i = 0;
    int bytes_read;
    char c;

    while (i < MAX_LINE_LENGTH - 1) {
        bytes_read = read(STDIN_FILENO, &c, 1);
        if (bytes_read <= 0)
            return NULL;
        if (c == '\n')
            break;
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    return my_strdup(buffer);
}

static int handle_command(fridge_t *fridge, char *cmd, char *arg1, char *arg2)
{
    if (my_strcmp(cmd, "exit") == 0) {
        save_fridge(fridge);
        return 1;
    }
    if (my_strcmp(cmd, "disp") == 0 && arg1 && 
        my_strcmp(arg1, "fridge") == 0) {
        display_fridge(fridge);
        return 0;
    }
    if (my_strcmp(cmd, "addToFridge") == 0 && arg1 && arg2) {
        add_to_fridge(fridge, arg1, my_atoi(arg2));
        return 0;
    }
    if (my_strcmp(cmd, "make") == 0 && arg1) {
        if (my_strcmp(arg1, "pizza") == 0) {
            make_pizza(fridge);
            return 0;
        }
        if (my_strcmp(arg1, "pasta") == 0) {
            make_pasta(fridge);
            return 0;
        }
    }
    my_putstr("Unknown command\n");
    return 0;
}

int fridge_main(void)
{
    fridge_t fridge;
    char *line = NULL;
    char *cmd = NULL;
    char *arg1 = NULL;
    char *arg2 = NULL;
    int should_exit = 0;

    init_fridge(&fridge);
    load_fridge(&fridge);
    my_putstr("Welcome to the fridge simulator!\n");
    while (!should_exit) {
        my_putstr("> ");
        line = read_input_line();
        if (!line)
            break;
        if (parse_command(line, &cmd, &arg1, &arg2) == 0) {
            should_exit = handle_command(&fridge, cmd, arg1, arg2);
        }
        if (cmd) free(cmd);
        if (arg1) free(arg1);
        if (arg2) free(arg2);
        free(line);
    }
    return 0;
}