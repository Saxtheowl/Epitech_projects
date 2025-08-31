/*
** EPITECH PROJECT, 2024
** print.c
** File description:
** Print functions for material information display
*/

#include "../include/organized.h"
#include <unistd.h>

static void print_string(const char *str)
{
    if (str)
        write(STDOUT_FILENO, str, my_strlen(str));
}

static void print_number(int num)
{
    char buffer[12];
    int i = 0;
    int is_negative = 0;

    if (num == 0) {
        write(STDOUT_FILENO, "0", 1);
        return;
    }
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    if (is_negative)
        buffer[i++] = '-';
    
    while (i > 0) {
        i--;
        write(STDOUT_FILENO, &buffer[i], 1);
    }
}

void print_material_added(material_t *material)
{
    if (!material)
        return;
    
    print_string(material_type_to_string(material->type));
    print_string(" n°");
    print_number(material->id);
    print_string(" - \"");
    print_string(material->name);
    print_string("\" added.\n");
}

void print_material_deleted(material_t *material)
{
    if (!material)
        return;
    
    print_string(material_type_to_string(material->type));
    print_string(" n°");
    print_number(material->id);
    print_string(" - \"");
    print_string(material->name);
    print_string("\" deleted.\n");
}

void print_material_display(material_t *material)
{
    if (!material)
        return;
    
    print_string(material_type_to_string(material->type));
    print_string(" n°");
    print_number(material->id);
    print_string(" - \"");
    print_string(material->name);
    print_string("\"\n");
}