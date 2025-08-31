/*
** EPITECH PROJECT, 2024
** material.c
** File description:
** Material management functions for workshop organization
*/

#include "../include/organized.h"
#include <stdlib.h>
#include <unistd.h>

int parse_material_type(const char *type_str, material_type_t *type)
{
    if (!type_str || !type)
        return -1;
    
    if (my_strcmp(type_str, "ACTUATOR") == 0) {
        *type = ACTUATOR;
        return 0;
    }
    if (my_strcmp(type_str, "DEVICE") == 0) {
        *type = DEVICE;
        return 0;
    }
    if (my_strcmp(type_str, "PROCESSOR") == 0) {
        *type = PROCESSOR;
        return 0;
    }
    if (my_strcmp(type_str, "SENSOR") == 0) {
        *type = SENSOR;
        return 0;
    }
    if (my_strcmp(type_str, "WIRE") == 0) {
        *type = WIRE;
        return 0;
    }
    return -1;
}

const char *material_type_to_string(material_type_t type)
{
    switch (type) {
        case ACTUATOR:
            return "ACTUATOR";
        case DEVICE:
            return "DEVICE";
        case PROCESSOR:
            return "PROCESSOR";
        case SENSOR:
            return "SENSOR";
        case WIRE:
            return "WIRE";
        default:
            return "UNKNOWN";
    }
}

material_t *material_create(int id, material_type_t type, const char *name)
{
    material_t *material;

    if (!name)
        return NULL;
    
    material = malloc(sizeof(material_t));
    if (!material)
        return NULL;
    
    material->id = id;
    material->type = type;
    material->name = my_strdup(name);
    material->next = NULL;
    
    if (!material->name) {
        free(material);
        return NULL;
    }
    
    return material;
}

void material_free(material_t *material)
{
    if (!material)
        return;
    
    free(material->name);
    free(material);
}

void material_add_to_list(workshop_t *workshop, material_t *material)
{
    if (!workshop || !material)
        return;
    
    material->next = workshop->materials;
    workshop->materials = material;
}

int material_delete_from_list(workshop_t *workshop, int id)
{
    material_t *current;
    material_t *previous;

    if (!workshop)
        return -1;
    
    current = workshop->materials;
    previous = NULL;
    
    while (current) {
        if (current->id == id) {
            if (previous)
                previous->next = current->next;
            else
                workshop->materials = current->next;
            
            print_material_deleted(current);
            material_free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}

material_t *material_find_by_id(workshop_t *workshop, int id)
{
    material_t *current;

    if (!workshop)
        return NULL;
    
    current = workshop->materials;
    while (current) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}