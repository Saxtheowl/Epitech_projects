/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Calculation functions for weather analysis
*/

#include "groundhog.h"

double calculate_increase_average(temperature_t *temps, int period)
{
    if (!temps || count_temperatures(temps) < period)
        return NAN;
    
    double sum = 0.0;
    int increases = 0;
    temperature_t *current = temps;
    
    for (int i = 0; i < period - 1 && current && current->next; i++) {
        double diff = current->value - current->next->value;
        if (diff > 0) {
            sum += diff;
            increases++;
        }
        current = current->next;
    }
    
    return increases > 0 ? sum / increases : 0.0;
}

double calculate_relative_evolution(temperature_t *temps, int period)
{
    if (!temps || count_temperatures(temps) < period)
        return NAN;
    
    double current_temp = temps->value;
    double old_temp = get_nth_temperature(temps, period - 1);
    
    if (old_temp == 0.0)
        return NAN;
    
    return ((current_temp - old_temp) / old_temp) * 100.0;
}

double calculate_standard_deviation(temperature_t *temps, int period)
{
    if (!temps || count_temperatures(temps) < period)
        return NAN;
    
    double sum = 0.0;
    double mean;
    temperature_t *current = temps;
    
    // Calculate mean
    for (int i = 0; i < period && current; i++) {
        sum += current->value;
        current = current->next;
    }
    mean = sum / period;
    
    // Calculate variance
    double variance_sum = 0.0;
    current = temps;
    for (int i = 0; i < period && current; i++) {
        double diff = current->value - mean;
        variance_sum += diff * diff;
        current = current->next;
    }
    
    return sqrt(variance_sum / period);
}

int detect_tendency_switch(groundhog_t *groundhog, double g, double r)
{
    if (is_nan_double(g) || is_nan_double(r))
        return 0;
    
    int new_tendency;
    
    // Determine current tendency based on indicators
    if (g > 0.5 && r > 5)
        new_tendency = 1;  // Increasing
    else if (g < 0.3 && r < -5)
        new_tendency = -1; // Decreasing
    else
        new_tendency = 0;  // Stable
    
    // Check for switch
    if (groundhog->current_tendency != 0 && new_tendency != 0 && 
        groundhog->current_tendency != new_tendency) {
        groundhog->tendency_switches++;
        groundhog->current_tendency = new_tendency;
        return 1;
    }
    
    if (new_tendency != 0)
        groundhog->current_tendency = new_tendency;
    
    return 0;
}