/*
** EPITECH PROJECT, 2025
** Bootstrap A-MAZE-D
** File description:
** Step 5: Build the graph from the PDF diagram
*/

#include "graph.h"

link_t *build_my_graph(void)
{
    link_t *node_42 = create_link(42);
    link_t *node_60012 = create_link(60012);
    link_t *node_48 = create_link(48);
    link_t *node_30012 = create_link(30012);
    link_t *node_50012 = create_link(50012);
    link_t *node_3 = create_link(3);
    link_t *node_98 = create_link(98);
    link_t *node_8 = create_link(8);

    if (!node_42 || !node_60012 || !node_48 || !node_30012 ||
        !node_50012 || !node_3 || !node_98 || !node_8)
        return NULL;

    // Connect according to the diagram
    connect_links(node_42, node_60012);
    connect_links(node_42, node_48);
    connect_links(node_60012, node_30012);
    connect_links(node_48, node_50012);
    connect_links(node_50012, node_3);
    connect_links(node_3, node_98);
    connect_links(node_3, node_8);

    return node_42; // Return the root node
}