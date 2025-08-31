/*
** EPITECH PROJECT, 2024
** test_organized.c
** File description:
** Unit tests for Organized workshop management project
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/organized.h"
#include "../include/shell.h"

static void test_material_functions(void)
{
    material_type_t type;
    material_t *material;
    
    printf("Testing material functions...\n");
    
    printf("parse_material_type(\"WIRE\"): %d (expected: 0)\n",
           parse_material_type("WIRE", &type));
    printf("Parsed type: %d (expected: %d)\n", type, WIRE);
    
    material = material_create(0, WIRE, "usb");
    printf("material_create result: %s\n", material ? "SUCCESS" : "FAILED");
    
    if (material) {
        printf("Material ID: %d, Type: %s, Name: %s\n",
               material->id, material_type_to_string(material->type), 
               material->name);
        material_free(material);
    }
    
    printf("PASS\n\n");
}

static void test_workshop_functions(void)
{
    workshop_t *workshop;
    material_t *material;
    
    printf("Testing workshop functions...\n");
    
    workshop = workshop_create();
    printf("workshop_create result: %s\n", workshop ? "SUCCESS" : "FAILED");
    
    if (workshop) {
        printf("Initial next_id: %d (expected: 0)\n", workshop->next_id);
        
        material = material_create(0, WIRE, "usb");
        if (material) {
            material_add_to_list(workshop, material);
            printf("After adding material, list head: %s\n",
                   workshop->materials ? "NOT NULL" : "NULL");
        }
        
        workshop_free(workshop);
    }
    
    printf("PASS\n\n");
}

static void test_parsing_functions(void)
{
    char **args;
    sort_params_t params = {0};
    
    printf("Testing parsing functions...\n");
    
    args = parse_command_args("WIRE usb, ACTUATOR button");
    if (args) {
        printf("Parsed args count: ");
        int i = 0;
        while (args[i]) {
            printf("%s ", args[i]);
            i++;
        }
        printf("(count: %d)\n", i);
        free_command_args(args);
    }
    
    char *sort_test[] = {"sort", "NAME", "-r", "ID", NULL};
    if (parse_sort_args(sort_test, &params) == 0) {
        printf("Sort criteria count: %d\n", params.count);
        printf("First criterion: %d, reverse: %d\n", 
               params.criteria[0], params.reverse_flags[0]);
        free_sort_params(&params);
    }
    
    printf("PASS\n\n");
}

int main(void)
{
    printf("Running Organized unit tests...\n\n");
    
    test_material_functions();
    test_workshop_functions();
    test_parsing_functions();
    
    printf("All tests completed!\n");
    return 0;
}