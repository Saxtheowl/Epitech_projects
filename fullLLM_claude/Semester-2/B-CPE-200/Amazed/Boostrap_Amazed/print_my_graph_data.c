/*
** EPITECH PROJECT, 2025
** Bootstrap A-MAZE-D
** File description:
** Step 6: Print all data values in the graph
*/

#include "graph.h"

static void print_graph_recursive(link_t *node, link_t **visited, int *visited_count, int max_nodes)
{
    link_list_t *current;
    int i;

    if (!node || *visited_count >= max_nodes)
        return;

    // Check if node already visited
    for (i = 0; i < *visited_count; i++) {
        if (visited[i] == node)
            return;
    }

    // Mark as visited and print
    visited[(*visited_count)++] = node;
    printf("%d\n", node->data);

    // Recursively visit connected nodes
    current = node->connections;
    while (current) {
        print_graph_recursive(current->link, visited, visited_count, max_nodes);
        current = current->next;
    }
}

void print_my_graph_data(link_t *graph)
{
    link_t *visited[1000]; // Assuming max 1000 nodes
    int visited_count = 0;

    if (!graph)
        return;

    print_graph_recursive(graph, visited, &visited_count, 1000);
}