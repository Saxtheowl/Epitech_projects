/*
** EPITECH PROJECT, 2024
** Test for stack, queue, map implementations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h" 
#include "map.h"

int string_comparator(void *first_key, void *second_key)
{
    return strcmp((char*)first_key, (char*)second_key);
}

void test_stack(void)
{
    printf("=== Stack Test ===\n");
    stack_t stack = NULL;
    
    int a = 1, b = 2, c = 3;
    
    printf("Empty: %s\n", stack_is_empty(stack) ? "true" : "false");
    
    stack_push(&stack, &a);
    stack_push(&stack, &b);
    stack_push(&stack, &c);
    
    printf("Size: %u\n", stack_get_size(stack));
    printf("Top: %d\n", *(int*)stack_top(stack));
    
    stack_pop(&stack);
    printf("After pop, top: %d\n", *(int*)stack_top(stack));
    
    stack_clear(&stack);
    printf("After clear, size: %u\n", stack_get_size(stack));
    printf("\n");
}

void test_queue(void)
{
    printf("=== Queue Test ===\n");
    queue_t queue = NULL;
    
    int a = 1, b = 2, c = 3;
    
    printf("Empty: %s\n", queue_is_empty(queue) ? "true" : "false");
    
    queue_push(&queue, &a);
    queue_push(&queue, &b);
    queue_push(&queue, &c);
    
    printf("Size: %u\n", queue_get_size(queue));
    printf("Front: %d\n", *(int*)queue_front(queue));
    
    queue_pop(&queue);
    printf("After pop, front: %d\n", *(int*)queue_front(queue));
    
    queue_clear(&queue);
    printf("After clear, size: %u\n", queue_get_size(queue));
    printf("\n");
}

void test_map(void)
{
    printf("=== Map Test ===\n");
    map_t map = NULL;
    
    char *key1 = "apple", *key2 = "banana";
    int val1 = 10, val2 = 20;
    
    printf("Empty: %s\n", map_is_empty(map) ? "true" : "false");
    
    map_add_elem(&map, key1, &val1, string_comparator);
    map_add_elem(&map, key2, &val2, string_comparator);
    
    printf("Size: %u\n", map_get_size(map));
    
    int *result = (int*)map_get_elem(map, key1, string_comparator);
    printf("apple -> %d\n", result ? *result : -1);
    
    result = (int*)map_get_elem(map, key2, string_comparator);
    printf("banana -> %d\n", result ? *result : -1);
    
    map_clear(&map);
    printf("After clear, size: %u\n", map_get_size(map));
    printf("\n");
}

int main(void)
{
    test_stack();
    test_queue();
    test_map();
    
    printf("All tests completed!\n");
    return 0;
}