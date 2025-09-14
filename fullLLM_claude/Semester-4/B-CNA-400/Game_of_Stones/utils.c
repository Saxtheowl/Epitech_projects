/*
** EPITECH PROJECT, 2024
** Game of Stones
** File description:
** Utility functions
*/

#include "game_of_stones.h"

int compare_persons(const void *a, const void *b)
{
    const person_t *person_a = *(const person_t **)a;
    const person_t *person_b = *(const person_t **)b;
    
    return strcmp(person_a->name, person_b->name);
}

void sort_persons(graph_t *graph)
{
    if (!graph || graph->person_count <= 1)
        return;
    
    person_t **persons_array = malloc(graph->person_count * sizeof(person_t *));
    if (!persons_array)
        return;
    
    // Convert linked list to array
    person_t *current = graph->persons;
    int index = 0;
    while (current && index < graph->person_count) {
        persons_array[index++] = current;
        current = current->next;
    }
    
    // Sort the array
    qsort(persons_array, graph->person_count, sizeof(person_t *), compare_persons);
    
    // Rebuild the linked list
    graph->persons = persons_array[0];
    for (int i = 0; i < graph->person_count - 1; i++) {
        persons_array[i]->next = persons_array[i + 1];
    }
    persons_array[graph->person_count - 1]->next = NULL;
    
    free(persons_array);
}