/*
** EPITECH PROJECT, 2024
** game_management.c
** File description:
** Game management functions for Push Swap
*/

#include <stdlib.h>
#include "../include/push_swap.h"

game_t *game_init(void)
{
    game_t *game = malloc(sizeof(game_t));

    if (game == NULL)
        return NULL;
    game->l_a = NULL;
    game->l_b = NULL;
    game->operations = malloc(sizeof(char *) * 1000);
    if (game->operations == NULL) {
        free(game);
        return NULL;
    }
    game->op_count = 0;
    game->op_capacity = 1000;
    return game;
}

void game_free(game_t *game)
{
    int i = 0;

    if (game == NULL)
        return;
    list_free(game->l_a);
    list_free(game->l_b);
    if (game->operations) {
        while (i < game->op_count) {
            if (game->operations[i])
                free(game->operations[i]);
            i++;
        }
        free(game->operations);
    }
    free(game);
}

static char *my_strdup(char const *str)
{
    int len = 0;
    char *dup;
    int i = 0;

    if (str == NULL)
        return NULL;
    while (str[len])
        len++;
    dup = malloc(len + 1);
    if (dup == NULL)
        return NULL;
    while (i < len) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

void game_add_operation(game_t *game, char const *op)
{
    if (game == NULL || op == NULL || game->op_count >= game->op_capacity)
        return;
    game->operations[game->op_count] = my_strdup(op);
    game->op_count++;
}

void game_print_operations(game_t *game)
{
    int i = 0;

    if (game == NULL || game->op_count == 0)
        return;
    while (i < game->op_count) {
        my_putstr(game->operations[i]);
        if (i < game->op_count - 1)
            my_putchar(' ');
        i++;
    }
    my_putchar('\n');
}