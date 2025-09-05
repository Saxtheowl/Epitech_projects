/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** save and load functionality
*/

#include "fridge.h"

int save_fridge(fridge_t *fridge)
{
    int fd = open(".save", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int i = 0;
    char *qty_str = NULL;

    if (fd == -1)
        return 1;
    for (i = 0; i < fridge->count; i++) {
        write(fd, fridge->ingredients[i].name, 
            my_strlen(fridge->ingredients[i].name));
        write(fd, ":", 1);
        qty_str = my_itoa(fridge->ingredients[i].quantity);
        if (qty_str) {
            write(fd, qty_str, my_strlen(qty_str));
            free(qty_str);
        }
        write(fd, "\n", 1);
    }
    close(fd);
    return 0;
}

static char *read_line(int fd)
{
    char buffer[MAX_LINE_LENGTH];
    char c;
    int i = 0;
    int bytes_read;

    while (i < MAX_LINE_LENGTH - 1) {
        bytes_read = read(fd, &c, 1);
        if (bytes_read <= 0 || c == '\n')
            break;
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    if (i == 0 && bytes_read <= 0)
        return NULL;
    return my_strdup(buffer);
}

static int parse_ingredient_line(char *line, char **name, int *quantity)
{
    int i = 0;
    int colon_pos = -1;

    while (line[i]) {
        if (line[i] == ':') {
            colon_pos = i;
            break;
        }
        i++;
    }
    if (colon_pos == -1)
        return 1;
    *name = malloc(sizeof(char) * (colon_pos + 1));
    if (!*name)
        return 1;
    for (i = 0; i < colon_pos; i++)
        (*name)[i] = line[i];
    (*name)[colon_pos] = '\0';
    *quantity = my_atoi(&line[colon_pos + 1]);
    return 0;
}

int load_fridge(fridge_t *fridge)
{
    int fd = open(".save", O_RDONLY);
    char *line = NULL;
    char *ingredient_name = NULL;
    int quantity = 0;
    int index = 0;

    if (fd == -1)
        return 1;
    while ((line = read_line(fd)) != NULL) {
        if (parse_ingredient_line(line, &ingredient_name, &quantity) == 0) {
            index = find_ingredient(fridge, ingredient_name);
            if (index != -1)
                fridge->ingredients[index].quantity = quantity;
            free(ingredient_name);
        }
        free(line);
    }
    close(fd);
    return 0;
}