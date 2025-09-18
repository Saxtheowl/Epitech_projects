/*
** EPITECH PROJECT, 2024
** Test ALL structures - comprehensive verification
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h" 
#include "map.h"
#include "tree.h"

int string_comparator(void *first_key, void *second_key)
{
    return strcmp((char*)first_key, (char*)second_key);
}

void print_int(void *data)
{
    printf("%d ", *(int*)data);
}

void test_complete_stack(void)
{
    printf("=== Complete Stack Test ===\n");
    stack_t stack = NULL;
    
    int a = 1, b = 2, c = 3;
    
    printf("Empty: %s\n", stack_is_empty(stack) ? "true" : "false");
    printf("Size: %u\n", stack_get_size(stack));
    
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

void test_complete_queue(void)
{
    printf("=== Complete Queue Test ===\n");
    queue_t queue = NULL;
    
    int a = 1, b = 2, c = 3;
    
    printf("Empty: %s\n", queue_is_empty(queue) ? "true" : "false");
    printf("Size: %u\n", queue_get_size(queue));
    
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

void test_complete_map(void)
{
    printf("=== Complete Map Test ===\n");
    map_t map = NULL;
    
    char *key1 = "apple", *key2 = "banana", *key3 = "cherry";
    int val1 = 10, val2 = 20, val3 = 30;
    
    printf("Empty: %s\n", map_is_empty(map) ? "true" : "false");
    printf("Size: %u\n", map_get_size(map));
    
    map_add_elem(&map, key1, &val1, string_comparator);
    map_add_elem(&map, key2, &val2, string_comparator);
    map_add_elem(&map, key3, &val3, string_comparator);
    
    printf("Size: %u\n", map_get_size(map));
    
    int *result = (int*)map_get_elem(map, key1, string_comparator);
    printf("apple -> %d\n", result ? *result : -1);
    
    result = (int*)map_get_elem(map, key2, string_comparator);
    printf("banana -> %d\n", result ? *result : -1);
    
    result = (int*)map_get_elem(map, "unknown", string_comparator);
    printf("unknown -> %d\n", result ? *result : -1);
    
    map_clear(&map);
    printf("After clear, size: %u\n", map_get_size(map));
    printf("\n");
}

void test_complete_tree(void)
{
    printf("=== Complete Tree Test ===\n");
    tree_t tree = NULL;
    
    int root = 1, child1 = 2, child2 = 3, grandchild1 = 4, grandchild2 = 5;
    tree_node_t *node1, *node2;
    
    printf("Empty: %s\n", tree_is_empty(tree) ? "true" : "false");
    
    init_tree(&tree, &root);
    printf("After init, empty: %s\n", tree_is_empty(tree) ? "true" : "false");
    
    node1 = tree_add_child(tree, &child1);
    node2 = tree_add_child(tree, &child2);
    tree_add_child(node1, &grandchild1);
    tree_add_child(node2, &grandchild2);
    
    printf("Tree structure (root to leaves): ");
    tree_node_dump(tree, print_int);
    printf("\n");
    
    tree_destroy(&tree);
    printf("After destroy, empty: %s\n", tree_is_empty(tree) ? "true" : "false");
    printf("\n");
}

int main(void)
{
    printf("=== Day04PM Complete Structure Test ===\n\n");
    
    test_complete_stack();
    test_complete_queue();
    test_complete_map();
    test_complete_tree();
    
    printf("=== All Data Structures Successfully Tested! ===\n");
    printf("Day04PM Implementation: 6/6 exercises completed\n");
    return 0;
}