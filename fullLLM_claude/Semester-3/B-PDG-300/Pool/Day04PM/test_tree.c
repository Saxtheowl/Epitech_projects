/*
** EPITECH PROJECT, 2024
** Test for Tree implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "stack.h"
#include "queue.h"

void print_int(void *data)
{
    printf("%d ", *(int*)data);
}

bool stack_push_wrapper(void *container, void *data)
{
    return stack_push((stack_t*)container, data);
}

void *stack_pop_wrapper(void *container)
{
    stack_t *stack = (stack_t*)container;
    void *data = stack_top(*stack);
    if (data) {
        stack_pop(stack);
    }
    return data;
}

bool queue_push_wrapper(void *container, void *data)
{
    return queue_push((queue_t*)container, data);
}

void *queue_pop_wrapper(void *container)
{
    queue_t *queue = (queue_t*)container;
    void *data = queue_front(*queue);
    if (data) {
        queue_pop(queue);
    }
    return data;
}

int main(void)
{
    tree_t tree = NULL;
    int root = 1, child1 = 2, child2 = 3, grandchild = 4;
    tree_node_t *node1, *node2;
    stack_t stack = NULL;
    queue_t queue = NULL;
    container_t stack_container, queue_container;

    printf("=== Tree Test ===\n");
    
    printf("Empty: %s\n", tree_is_empty(tree) ? "true" : "false");
    
    if (!init_tree(&tree, &root)) {
        printf("Failed to init tree\n");
        return 1;
    }
    
    printf("After init, empty: %s\n", tree_is_empty(tree) ? "true" : "false");
    
    node1 = tree_add_child(tree, &child1);
    node2 = tree_add_child(tree, &child2);
    tree_add_child(node1, &grandchild);
    
    printf("Tree dump: ");
    tree_node_dump(tree, print_int);
    printf("\n");
    
    printf("Stack traversal: ");
    stack_container.container = &stack;
    stack_container.push_func = stack_push_wrapper;
    stack_container.pop_func = stack_pop_wrapper;
    tree_traversal(tree, &stack_container, print_int);
    printf("\n");
    
    printf("Queue traversal: ");
    queue_container.container = &queue;
    queue_container.push_func = queue_push_wrapper;
    queue_container.pop_func = queue_pop_wrapper;
    tree_traversal(tree, &queue_container, print_int);
    printf("\n");
    
    tree_destroy(&tree);
    printf("After destroy, empty: %s\n", tree_is_empty(tree) ? "true" : "false");
    
    stack_clear(&stack);
    queue_clear(&queue);
    
    printf("Tree test completed!\n");
    return 0;
}