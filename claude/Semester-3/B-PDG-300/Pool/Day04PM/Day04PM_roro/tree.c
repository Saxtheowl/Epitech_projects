#include <stdlib.h>
#include "../tree.h"

bool tree_is_empty(tree_t tree)
{
    return tree == NULL;
}

void tree_node_dump(tree_node_t *tree_node, dump_func_t dump_func)
{
    node_t *current;

    if (tree_node == NULL || dump_func == NULL)
        return;

    dump_func(tree_node->data);

    current = tree_node->children;
    while (current != NULL) {
        tree_node_dump((tree_node_t *)current->value, dump_func);
        current = current->next;
    }
}

bool init_tree(tree_t *tree_ptr, void *data)
{
    tree_node_t *new_tree;

    if (tree_ptr == NULL)
        return false;

    new_tree = malloc(sizeof(tree_node_t));
    if (new_tree == NULL)
        return false;

    new_tree->data = data;
    new_tree->parent = NULL;
    new_tree->children = NULL;

    *tree_ptr = new_tree;
    return true;
}

tree_node_t *tree_add_child(tree_node_t *tree_node, void *data)
{
    tree_node_t *new_child;

    if (tree_node == NULL)
        return NULL;

    new_child = malloc(sizeof(tree_node_t));
    if (new_child == NULL)
        return NULL;

    new_child->data = data;
    new_child->parent = tree_node;
    new_child->children = NULL;

    if (!list_add_elem_at_front(&tree_node->children, new_child)) {
        free(new_child);
        return NULL;
    }

    return new_child;
}

static void destroy_tree_recursive(tree_node_t *tree_node)
{
    node_t *current;
    node_t *next;

    if (tree_node == NULL)
        return;

    current = tree_node->children;
    while (current != NULL) {
        next = current->next;
        destroy_tree_recursive((tree_node_t *)current->value);
        free(current);
        current = next;
    }

    free(tree_node);
}

bool tree_destroy(tree_t *tree_ptr)
{
    if (tree_ptr == NULL || *tree_ptr == NULL)
        return false;

    destroy_tree_recursive(*tree_ptr);
    *tree_ptr = NULL;
    return true;
}

void tree_traversal(tree_t tree, container_t *container, dump_func_t dump_func)
{
    tree_node_t *current_node;
    node_t *child_node;

    if (tree == NULL || container == NULL || dump_func == NULL)
        return;
    
    if (container->push_func == NULL || container->pop_func == NULL)
        return;

    container->push_func(container->container, tree);

    while ((current_node = (tree_node_t *)container->pop_func(container->container)) != NULL) {
        dump_func(current_node->data);

        child_node = current_node->children;
        while (child_node != NULL) {
            container->push_func(container->container, child_node->value);
            child_node = child_node->next;
        }
    }
}