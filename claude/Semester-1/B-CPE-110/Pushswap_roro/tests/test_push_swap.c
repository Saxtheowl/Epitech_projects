/*
** EPITECH PROJECT, 2024
** test_push_swap.c
** File description:
** Unit tests for Push Swap project
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/push_swap.h"

static void test_list_operations(void)
{
    list_t *list = NULL;
    
    printf("Testing list operations...\n");
    
    list_push_front(&list, 1);
    list_push_front(&list, 2);
    list_push_front(&list, 3);
    
    printf("List size: %d (expected: 3)\n", list_size(list));
    printf("Is sorted: %d (expected: 0)\n", list_is_sorted(list));
    
    int value = list_pop_front(&list);
    printf("Popped value: %d (expected: 3)\n", value);
    printf("New size: %d (expected: 2)\n", list_size(list));
    
    list_free(list);
    printf("PASS\n\n");
}

static void test_sorting_check(void)
{
    list_t *list = NULL;
    
    printf("Testing sorting check...\n");
    
    list_push_front(&list, 3);
    list_push_front(&list, 2);
    list_push_front(&list, 1);
    
    printf("List 1-2-3 is sorted: %d (expected: 1)\n", list_is_sorted(list));
    
    list_free(list);
    list = NULL;
    
    list_push_front(&list, 1);
    list_push_front(&list, 3);
    list_push_front(&list, 2);
    
    printf("List 2-3-1 is sorted: %d (expected: 0)\n", list_is_sorted(list));
    
    list_free(list);
    printf("PASS\n\n");
}

static void test_game_operations(void)
{
    game_t *game = game_init();
    
    printf("Testing game operations...\n");
    
    list_push_front(&game->l_a, 1);
    list_push_front(&game->l_a, 2);
    
    printf("Before sa: l_a = 2-1\n");
    sa(game);
    printf("After sa: l_a = 1-2\n");
    
    pb(game);
    printf("After pb: l_a = 2, l_b = 1\n");
    
    pa(game);
    printf("After pa: l_a = 1-2, l_b = empty\n");
    
    printf("Operations count: %d (expected: 3)\n", game->op_count);
    
    game_free(game);
    printf("PASS\n\n");
}

int main(void)
{
    printf("Running Push Swap unit tests...\n\n");
    test_list_operations();
    test_sorting_check();
    test_game_operations();
    printf("All tests completed!\n");
    return 0;
}