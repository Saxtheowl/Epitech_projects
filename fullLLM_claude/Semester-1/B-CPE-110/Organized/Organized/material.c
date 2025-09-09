#include "organized.h"

int get_material_type(char const *type_str, material_type_t *type)
{
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

char const *get_type_string(material_type_t type)
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
    }
    return "UNKNOWN";
}

material_t *create_material(int id, char const *name, material_type_t type)
{
    material_t *material = malloc(sizeof(material_t));
    
    if (!material)
        return 0;
    
    material->id = id;
    material->name = my_strdup(name);
    material->type = type;
    material->next = 0;
    
    if (!material->name) {
        free(material);
        return 0;
    }
    
    return material;
}

void free_material(material_t *material)
{
    if (!material)
        return;
    
    if (material->name)
        free(material->name);
    free(material);
}

void add_material_to_workshop(workshop_t *workshop, material_t *material)
{
    if (!workshop || !material)
        return;
    
    material->next = workshop->materials;
    workshop->materials = material;
}

material_t *find_material_by_id(workshop_t *workshop, int id)
{
    material_t *current;
    
    if (!workshop)
        return 0;
    
    current = workshop->materials;
    while (current) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    
    return 0;
}

void remove_material_from_workshop(workshop_t *workshop, int id)
{
    material_t *current, *prev = 0;
    
    if (!workshop)
        return;
    
    current = workshop->materials;
    while (current) {
        if (current->id == id) {
            if (prev)
                prev->next = current->next;
            else
                workshop->materials = current->next;
            
            free_material(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}