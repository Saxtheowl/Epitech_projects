/*
** EPITECH PROJECT, 2024
** commands.c
** File description:
** Shell command implementations for workshop management
*/

#include "../include/organized.h"
#include "../include/shell.h"
#include <stdlib.h>
#include <unistd.h>

int add(void *data, char **args)
{
    workshop_t *workshop = (workshop_t*)data;
    char **parsed_args;
    material_type_t type;
    material_t *material;
    int i = 0;
    int j = 1;

    if (!workshop || !args)
        return EXIT_ERROR;
    
    if (args[1]) {
        parsed_args = parse_command_args(args[1]);
        if (!parsed_args)
            return EXIT_ERROR;
        
        while (parsed_args[i] && parsed_args[i + 1]) {
            if (parse_material_type(parsed_args[i], &type) == -1) {
                free_command_args(parsed_args);
                return EXIT_ERROR;
            }
            
            material = material_create(workshop->next_id++, type, parsed_args[i + 1]);
            if (!material) {
                free_command_args(parsed_args);
                return EXIT_ERROR;
            }
            
            material_add_to_list(workshop, material);
            print_material_added(material);
            
            i += 2;
        }
        
        free_command_args(parsed_args);
    } else {
        while (args[j] && args[j + 1]) {
            if (parse_material_type(args[j], &type) == -1)
                return EXIT_ERROR;
            
            material = material_create(workshop->next_id++, type, args[j + 1]);
            if (!material)
                return EXIT_ERROR;
            
            material_add_to_list(workshop, material);
            print_material_added(material);
            
            j += 2;
        }
    }
    
    return EXIT_SUCCESS;
}

int del(void *data, char **args)
{
    workshop_t *workshop = (workshop_t*)data;
    int id;
    int i = 1;

    if (!workshop || !args)
        return EXIT_ERROR;
    
    while (args[i]) {
        id = my_atoi(args[i]);
        if (material_delete_from_list(workshop, id) == -1)
            return EXIT_ERROR;
        i++;
    }
    
    return EXIT_SUCCESS;
}

int disp(void *data, char **args)
{
    workshop_t *workshop = (workshop_t*)data;
    material_t *current;

    (void)args;
    
    if (!workshop)
        return EXIT_ERROR;
    
    current = workshop->materials;
    while (current) {
        print_material_display(current);
        current = current->next;
    }
    
    return EXIT_SUCCESS;
}

int sort(void *data, char **args)
{
    workshop_t *workshop = (workshop_t*)data;
    sort_params_t params = {0};

    if (!workshop || !args)
        return EXIT_ERROR;
    
    if (parse_sort_args(args, &params) == -1) {
        free_sort_params(&params);
        return EXIT_ERROR;
    }
    
    workshop_sort(workshop, &params);
    free_sort_params(&params);
    
    return EXIT_SUCCESS;
}