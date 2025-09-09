#ifndef ORGANIZED_H
#define ORGANIZED_H

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

typedef enum {
    ACTUATOR,
    DEVICE,
    PROCESSOR,
    SENSOR,
    WIRE
} material_type_t;

typedef struct material {
    int id;
    char *name;
    material_type_t type;
    struct material *next;
} material_t;

typedef struct {
    material_t *materials;
    int next_id;
} workshop_t;

int my_strlen(char const *str);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strdup(char const *str);
void my_putstr(char const *str);
void my_putchar(char c);
void my_put_nbr(int nb);

char **split_string(char const *str, char sep);
void free_string_array(char **array);
int count_args(char **args);

int get_material_type(char const *type_str, material_type_t *type);
char const *get_type_string(material_type_t type);
material_t *create_material(int id, char const *name, material_type_t type);
void free_material(material_t *material);
void add_material_to_workshop(workshop_t *workshop, material_t *material);
material_t *find_material_by_id(workshop_t *workshop, int id);
void remove_material_from_workshop(workshop_t *workshop, int id);

void sort_materials(workshop_t *workshop, char **args);
int compare_materials(material_t *a, material_t *b, char **sort_criteria);

#endif