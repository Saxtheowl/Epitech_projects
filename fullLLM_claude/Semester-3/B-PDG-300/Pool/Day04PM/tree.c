/*
** EPITECH PROJECT, 2024
** Paradigms Seminar - Tree Implementation
** File description:
** Generic tree data structure using lists
*/

#include <stdlib.h>
#include "tree.h"

bool tree_is_empty(tree_t tree)
{
    return (tree == NULL);
}

bool init_tree(tree_t *tree_ptr, void *data)
{
    tree_node_t *node;

    if (!tree_ptr)
        return false;
    
    node = malloc(sizeof(tree_node_t));
    if (!node)
        return false;
    
    node->data = data;
    node->parent = NULL;
    node->children = NULL;
    
    *tree_ptr = node;
    return true;
}

tree_node_t *tree_add_child(tree_node_t *tree_node, void *data)
{
    tree_node_t *child;

    if (!tree_node)
        return NULL;
    
    child = malloc(sizeof(tree_node_t));
    if (!child)
        return NULL;
    
    child->data = data;
    child->parent = tree_node;
    child->children = NULL;
    
    if (!list_add_elem_at_back(&tree_node->children, child)) {
        free(child);
        return NULL;
    }
    
    return child;
}

bool tree_destroy(tree_t *tree_ptr)
{
    tree_node_t *node;

    if (!tree_ptr || !*tree_ptr)
        return false;
    
    node = *tree_ptr;
    
    while (!list_is_empty(node->children)) {
        tree_node_t *child = (tree_node_t *)list_get_elem_at_front(node->children);
        tree_destroy((tree_t *)&child);
        list_del_elem_at_front(&node->children);
    }
    
    list_clear(&node->children);
    free(node);
    *tree_ptr = NULL;
    return true;
}

void tree_node_dump(tree_node_t *tree_node, dump_func_t dump_func)
{
    unsigned int i;
    unsigned int size;

    if (!tree_node || !dump_func)
        return;
    
    dump_func(tree_node->data);
    
    if (!list_is_empty(tree_node->children)) {
        size = list_get_size(tree_node->children);
        for (i = 0; i < size; i++) {
            tree_node_t *child = (tree_node_t *)list_get_elem_at_position(tree_node->children, i);
            tree_node_dump(child, dump_func);
        }
    }
}

void tree_traversal(tree_t tree, container_t *container, dump_func_t dump_func)
{
    tree_node_t *current;

    if (!tree || !container || !dump_func)
        return;
    
    if (!container->push_func(container->container, tree))
        return;
    
    while ((current = (tree_node_t *)container->pop_func(container->container)) != NULL) {
        dump_func(current->data);
        
        if (!list_is_empty(current->children)) {
            unsigned int size = list_get_size(current->children);
            for (unsigned int i = 0; i < size; i++) {
                tree_node_t *child = (tree_node_t *)list_get_elem_at_position(current->children, i);
                container->push_func(container->container, child);
            }
        }
    }
}