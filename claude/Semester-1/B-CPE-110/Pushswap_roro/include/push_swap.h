/*
** EPITECH PROJECT, 2024
** push_swap.h
** File description:
** Header file for Push Swap project
*/

#ifndef PUSH_SWAP_H_
    #define PUSH_SWAP_H_

#include <stddef.h>

#define EXIT_ERROR 84
#define EXIT_SUCCESS 0

typedef struct list_s {
    int value;
    struct list_s *next;
} list_t;

typedef struct game_s {
    list_t *l_a;
    list_t *l_b;
    char **operations;
    int op_count;
    int op_capacity;
} game_t;

/* List operations */
list_t *list_create(int value);
void list_push_front(list_t **list, int value);
int list_pop_front(list_t **list);
int list_size(list_t *list);
void list_free(list_t *list);
int list_is_sorted(list_t *list);

/* Stack operations */
void sa(game_t *game);
void sb(game_t *game);
void sc(game_t *game);
void pa(game_t *game);
void pb(game_t *game);
void ra(game_t *game);
void rb(game_t *game);
void rr(game_t *game);
void rra(game_t *game);
void rrb(game_t *game);
void rrr(game_t *game);

/* Game management */
game_t *game_init(void);
void game_free(game_t *game);
void game_add_operation(game_t *game, char const *op);
void game_print_operations(game_t *game);

/* Sorting algorithms */
void sort_small(game_t *game);
void sort_medium(game_t *game);
void sort_large(game_t *game);
void choose_sort_algorithm(game_t *game);

/* Utility functions */
int my_atoi(char const *str);
void my_putstr(char const *str);
void my_putchar(char c);
int is_valid_number(char const *str);
int parse_arguments(int ac, char **av, game_t *game);

#endif /* !PUSH_SWAP_H_ */