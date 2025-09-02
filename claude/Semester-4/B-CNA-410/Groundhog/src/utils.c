/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Utility functions
*/

#include "groundhog.h"

int is_nan_double(double value)
{
    return value != value;
}

void print_indicators(double g, double r, double s, int switch_detected)
{
    if (is_nan_double(g))
        printf("g=nan ");
    else
        printf("g=%.2f ", g);
    
    if (is_nan_double(r))
        printf("r=nan%% ");
    else
        printf("r=%d%% ", (int)round(r));
    
    if (is_nan_double(s))
        printf("s=nan");
    else
        printf("s=%.2f", s);
    
    if (switch_detected)
        printf(" a switch occurs");
    
    printf("\n");
}

temperature_t *add_temperature(temperature_t *list, double value)
{
    temperature_t *new_temp = malloc(sizeof(temperature_t));
    if (!new_temp)
        return list;
    
    new_temp->value = value;
    new_temp->next = list;
    return new_temp;
}

void free_temperatures(temperature_t *list)
{
    while (list) {
        temperature_t *next = list->next;
        free(list);
        list = next;
    }
}

double get_nth_temperature(temperature_t *list, int n)
{
    int i = 0;
    while (list && i < n) {
        list = list->next;
        i++;
    }
    return list ? list->value : 0.0;
}

int count_temperatures(temperature_t *list)
{
    int count = 0;
    while (list) {
        count++;
        list = list->next;
    }
    return count;
}