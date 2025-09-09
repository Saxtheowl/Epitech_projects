#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct list_s {
    int value;
    struct list_s *next;
} list_t;

typedef struct stack_s {
    list_t *l_a;
    list_t *l_b;
    char *operations;
    int ops_size;
    int ops_capacity;
} stack_t;

/* Stack operations */
list_t *create_node(int value);
void push_front(list_t **list, int value);
int pop_front(list_t **list);
int list_size(list_t *list);
int is_sorted(list_t *list);
void free_list(list_t *list);

/* Stack management */
stack_t *init_stack(void);
void free_stack(stack_t *stack);
void add_operation(stack_t *stack, const char *op);
void print_operations(stack_t *stack);

/* Push swap operations */
void sa(stack_t *stack);
void sb(stack_t *stack);
void sc(stack_t *stack);
void pa(stack_t *stack);
void pb(stack_t *stack);
void ra(stack_t *stack);
void rb(stack_t *stack);
void rr(stack_t *stack);
void rra(stack_t *stack);
void rrb(stack_t *stack);
void rrr(stack_t *stack);

/* Sorting algorithm */
void sort_small(stack_t *stack, int size);
void sort_large(stack_t *stack);
int find_min_position(list_t *list);
int find_max_position(list_t *list);

/* Utils */
int my_atoi(const char *str);
int is_valid_number(const char *str);

#endif