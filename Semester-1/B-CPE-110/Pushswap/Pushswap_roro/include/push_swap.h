/*
** EPITECH PROJECT, 2024
** Pushswap
** File description:
** Header file for push_swap program
*/

#ifndef PUSH_SWAP_H_
    #define PUSH_SWAP_H_

    #include <stdlib.h>
    #include <unistd.h>

typedef struct node_s {
    int value;
    struct node_s *next;
} node_t;

typedef struct {
    node_t *head;
    int size;
} list_t;

typedef struct {
    list_t *l_a;
    list_t *l_b;
    char *operations;
    int op_count;
    int op_capacity;
} game_t;

/* List operations */
list_t *create_list(void);
void free_list(list_t *list);
void push_front(list_t *list, int value);
int pop_front(list_t *list);
int is_empty(list_t *list);
int is_sorted(list_t *list);

/* Game operations */
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

/* Algorithm functions */
void add_operation(game_t *game, char *op);
void solve_pushswap(game_t *game);
void sort_small(game_t *game);
void sort_three(game_t *game);
void sort_large(game_t *game);
int find_min_position(list_t *list);
int find_max_position(list_t *list);

/* Utility functions */
int my_atoi(char *str);
int my_strlen(char *str);
void my_putstr(char *str);
void my_putchar(char c);
int is_valid_number(char *str);

/* Game management */
game_t *init_game(void);
void free_game(game_t *game);
int parse_arguments(game_t *game, int ac, char **av);

#endif /* !PUSH_SWAP_H_ */