/*
** EPITECH PROJECT, 2024
** organized.h
** File description:
** Header file for Organized workshop management system
*/

#ifndef ORGANIZED_H_
#define ORGANIZED_H_

#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_ERROR 84

typedef enum {
    ACTUATOR,
    DEVICE,
    PROCESSOR,
    SENSOR,
    WIRE
} material_type_t;

typedef struct material_s {
    int id;
    material_type_t type;
    char *name;
    struct material_s *next;
} material_t;

typedef struct workshop_s {
    material_t *materials;
    int next_id;
} workshop_t;

typedef enum {
    SORT_TYPE,
    SORT_NAME,
    SORT_ID
} sort_criterion_t;

typedef struct sort_params_s {
    sort_criterion_t *criteria;
    int *reverse_flags;
    int count;
} sort_params_t;

workshop_t *workshop_create(void);
void workshop_free(workshop_t *workshop);

material_t *material_create(int id, material_type_t type, const char *name);
void material_free(material_t *material);

int parse_material_type(const char *type_str, material_type_t *type);
const char *material_type_to_string(material_type_t type);

void material_add_to_list(workshop_t *workshop, material_t *material);
int material_delete_from_list(workshop_t *workshop, int id);
material_t *material_find_by_id(workshop_t *workshop, int id);

void workshop_sort(workshop_t *workshop, sort_params_t *params);
int compare_materials(material_t *a, material_t *b, sort_params_t *params);

char **parse_command_args(const char *input);
void free_command_args(char **args);
int parse_sort_args(char **args, sort_params_t *params);
void free_sort_params(sort_params_t *params);

int my_strcmp(const char *s1, const char *s2);
char *my_strdup(const char *str);
int my_strlen(const char *str);
int my_atoi(const char *str);

void print_material_added(material_t *material);
void print_material_deleted(material_t *material);
void print_material_display(material_t *material);

#endif /* !ORGANIZED_H_ */