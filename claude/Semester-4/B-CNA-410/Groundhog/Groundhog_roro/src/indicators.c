/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Technical indicators calculation
*/

#include "groundhog.h"

indicators_t calculate_indicators(temperature_data_t *data, int period)
{
    indicators_t indicators;

    indicators.g = calculate_temperature_increase_average(data, period);
    indicators.r = calculate_relative_evolution(data, period);
    indicators.s = calculate_standard_deviation(data, period);
    return indicators;
}

double calculate_temperature_increase_average(temperature_data_t *data,
    int period)
{
    double sum = 0.0;
    int count = 0;
    int start = 0;
    int i = 0;

    if (!data || data->count < period)
        return NAN;
    start = (data->count > period) ? data->count - period : 0;
    for (i = start + 1; i < data->count; i++) {
        if (data->values[i] > data->values[i - 1]) {
            sum += data->values[i] - data->values[i - 1];
            count++;
        }
    }
    return (count > 0) ? sum / count : 0.0;
}

double calculate_relative_evolution(temperature_data_t *data, int period)
{
    double current = 0.0;
    double past = 0.0;

    if (!data || data->count < period)
        return NAN;
    current = data->values[data->count - 1];
    past = data->values[data->count - period];
    if (past == 0.0)
        return NAN;
    return ((current - past) / past) * 100.0;
}

double calculate_standard_deviation(temperature_data_t *data, int period)
{
    double mean = 0.0;
    double sum = 0.0;
    double variance = 0.0;
    int start = 0;
    int count = 0;
    int i = 0;

    if (!data || data->count < period)
        return NAN;
    start = (data->count >= period) ? data->count - period : 0;
    count = data->count - start;
    for (i = start; i < data->count; i++)
        sum += data->values[i];
    mean = sum / count;
    sum = 0.0;
    for (i = start; i < data->count; i++)
        sum += pow(data->values[i] - mean, 2);
    variance = sum / count;
    return sqrt(variance);
}