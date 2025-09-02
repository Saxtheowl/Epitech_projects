/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Unit tests
*/

#include <criterion/criterion.h>
#include "groundhog.h"

Test(temperature_data, init_and_add)
{
    temperature_data_t *data = init_temperature_data();
    
    cr_assert_not_null(data);
    cr_assert_eq(data->count, 0);
    cr_assert_eq(add_temperature(data, 25.5), 0);
    cr_assert_eq(data->count, 1);
    cr_assert_float_eq(data->values[0], 25.5, 0.01);
    
    free_temperature_data(data);
}

Test(indicators, standard_deviation)
{
    temperature_data_t *data = init_temperature_data();
    double result = 0.0;
    
    add_temperature(data, 20.0);
    add_temperature(data, 22.0);
    add_temperature(data, 24.0);
    add_temperature(data, 26.0);
    add_temperature(data, 28.0);
    
    result = calculate_standard_deviation(data, 5);
    cr_assert_float_eq(result, 2.83, 0.1);
    
    free_temperature_data(data);
}

Test(switch_detection, init)
{
    switch_detection_t *detection = init_switch_detection();
    
    cr_assert_not_null(detection);
    cr_assert_eq(detection->total_switches, 0);
    cr_assert_eq(detection->aberrations_count, 0);
    
    free_switch_detection(detection);
}

Test(args, parse_valid_period)
{
    char *argv[] = {"groundhog", "7"};
    int result = parse_arguments(2, argv);
    
    cr_assert_eq(result, 7);
}

Test(args, parse_invalid_period)
{
    char *argv[] = {"groundhog", "0"};
    int result = parse_arguments(2, argv);
    
    cr_assert_eq(result, -1);
}