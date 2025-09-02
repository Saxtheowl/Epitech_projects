/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Temperature data management
*/

#include "groundhog.h"

temperature_data_t *init_temperature_data(void)
{
    temperature_data_t *data = malloc(sizeof(temperature_data_t));

    if (!data)
        return NULL;
    data->values = malloc(sizeof(double) * 1000);
    if (!data->values) {
        free(data);
        return NULL;
    }
    data->count = 0;
    data->capacity = 1000;
    return data;
}

void free_temperature_data(temperature_data_t *data)
{
    if (!data)
        return;
    if (data->values)
        free(data->values);
    free(data);
}

int add_temperature(temperature_data_t *data, double temp)
{
    double *new_values = NULL;

    if (!data)
        return -1;
    if (data->count >= data->capacity) {
        data->capacity *= 2;
        new_values = realloc(data->values, sizeof(double) * data->capacity);
        if (!new_values)
            return -1;
        data->values = new_values;
    }
    data->values[data->count++] = temp;
    return 0;
}