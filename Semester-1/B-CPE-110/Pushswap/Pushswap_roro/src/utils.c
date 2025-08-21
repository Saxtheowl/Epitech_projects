/*
** EPITECH PROJECT, 2024
** Pushswap
** File description:
** Utility functions
*/

#include "../include/push_swap.h"

int my_atoi(char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (!str)
        return 0;
    
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}

int my_strlen(char *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    
    while (str[len])
        len++;
    
    return len;
}

void my_putstr(char *str)
{
    int i = 0;
    
    if (!str)
        return;
    
    while (str[i]) {
        write(1, &str[i], 1);
        i++;
    }
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

int is_valid_number(char *str)
{
    int i = 0;
    
    if (!str || str[0] == '\0')
        return 0;
    
    if (str[i] == '-' || str[i] == '+')
        i++;
    
    if (str[i] == '\0')
        return 0;
    
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    
    return 1;
}

void add_operation(game_t *game, char *op)
{
    int op_len;
    int new_len;
    char *new_operations;
    int i;
    int j;
    
    if (!game || !op)
        return;
    
    op_len = my_strlen(op);
    
    if (!game->operations) {
        game->operations = malloc(op_len + 1);
        if (!game->operations)
            return;
        
        for (i = 0; i < op_len; i++)
            game->operations[i] = op[i];
        game->operations[op_len] = '\0';
        game->op_count = 1;
        game->op_capacity = op_len + 1;
        return;
    }
    
    new_len = my_strlen(game->operations) + op_len + 2;
    
    if (new_len > game->op_capacity) {
        new_operations = malloc(new_len);
        if (!new_operations)
            return;
        
        for (i = 0; game->operations[i]; i++)
            new_operations[i] = game->operations[i];
        
        new_operations[i] = ' ';
        i++;
        
        for (j = 0; j < op_len; j++, i++)
            new_operations[i] = op[j];
        
        new_operations[i] = '\0';
        
        free(game->operations);
        game->operations = new_operations;
        game->op_capacity = new_len;
    } else {
        i = my_strlen(game->operations);
        game->operations[i] = ' ';
        i++;
        
        for (j = 0; j < op_len; j++, i++)
            game->operations[i] = op[j];
        
        game->operations[i] = '\0';
    }
    
    game->op_count++;
}