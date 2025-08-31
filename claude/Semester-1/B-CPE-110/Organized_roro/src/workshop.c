/*
** EPITECH PROJECT, 2024
** workshop.c
** File description:
** Workshop management and initialization functions
*/

#include "../include/organized.h"
#include <stdlib.h>

workshop_t *workshop_create(void)
{
    workshop_t *workshop;

    workshop = malloc(sizeof(workshop_t));
    if (!workshop)
        return NULL;
    
    workshop->materials = NULL;
    workshop->next_id = 0;
    
    return workshop;
}

void workshop_free(workshop_t *workshop)
{
    material_t *current;
    material_t *next;

    if (!workshop)
        return;
    
    current = workshop->materials;
    while (current) {
        next = current->next;
        material_free(current);
        current = next;
    }
    
    free(workshop);
}