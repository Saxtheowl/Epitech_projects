#include "organized.h"

static int my_atoi(char const *str)
{
    int result = 0;
    int i = 0;
    
    if (!str)
        return -1;
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    if (str[i] != '\0')
        return -1;
    
    return result;
}

int add(void *data, char **args)
{
    workshop_t *workshop = (workshop_t *)data;
    char **items;
    int i = 0;
    
    if (!workshop || !args || !args[0])
        return 84;
    
    items = split_string(args[0], ',');
    if (!items)
        return 84;
    
    while (items[i]) {
        char **parts = split_string(items[i], ' ');
        if (!parts || count_args(parts) != 2) {
            free_string_array(parts);
            free_string_array(items);
            return 84;
        }
        
        material_type_t type;
        if (get_material_type(parts[0], &type) == -1) {
            free_string_array(parts);
            free_string_array(items);
            return 84;
        }
        
        material_t *material = create_material(workshop->next_id, parts[1], type);
        if (!material) {
            free_string_array(parts);
            free_string_array(items);
            return 84;
        }
        
        add_material_to_workshop(workshop, material);
        
        my_putstr(get_type_string(type));
        my_putstr(" n°");
        my_put_nbr(workshop->next_id);
        my_putstr(" - \"");
        my_putstr(parts[1]);
        my_putstr("\" added.\n");
        
        workshop->next_id++;
        
        free_string_array(parts);
        i++;
    }
    
    free_string_array(items);
    return 0;
}

int del(void *data, char **args)
{
    workshop_t *workshop = (workshop_t *)data;
    char **ids;
    int i = 0;
    
    if (!workshop || !args || !args[0])
        return 84;
    
    ids = split_string(args[0], ',');
    if (!ids)
        return 84;
    
    while (ids[i]) {
        int id = my_atoi(ids[i]);
        if (id < 0) {
            free_string_array(ids);
            return 84;
        }
        
        material_t *material = find_material_by_id(workshop, id);
        if (!material) {
            free_string_array(ids);
            return 84;
        }
        
        my_putstr(get_type_string(material->type));
        my_putstr(" n°");
        my_put_nbr(id);
        my_putstr(" - \"");
        my_putstr(material->name);
        my_putstr("\" deleted.\n");
        
        remove_material_from_workshop(workshop, id);
        i++;
    }
    
    free_string_array(ids);
    return 0;
}

int disp(void *data, char **args)
{
    workshop_t *workshop = (workshop_t *)data;
    material_t *current;
    
    (void)args;
    
    if (!workshop)
        return 84;
    
    current = workshop->materials;
    while (current) {
        my_putstr(get_type_string(current->type));
        my_putstr(" n°");
        my_put_nbr(current->id);
        my_putstr(" - \"");
        my_putstr(current->name);
        my_putstr("\"\n");
        current = current->next;
    }
    
    return 0;
}