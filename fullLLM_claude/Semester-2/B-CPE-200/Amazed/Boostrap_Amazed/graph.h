/*
** EPITECH PROJECT, 2025
** Bootstrap A-MAZE-D
** File description:
** Header file containing graph structure declarations
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct link_list_s {
    struct link_s *link;
    struct link_list_s *next;
} link_list_t;

typedef struct link_s {
    int data;
    link_list_t *connections;
} link_t;

// Function prototypes
link_t *create_link(int data);
void print_link(link_t *link);
void connect_links(link_t *link1, link_t *link2);
void print_data_of_connected_links(link_t *link);
link_t *build_my_graph(void);
void print_my_graph_data(link_t *graph);

#endif /* !GRAPH_H_ */