/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Groundhog header file
*/

#ifndef GROUNDHOG_H_
    #define GROUNDHOG_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <math.h>

    #define ERROR_EXIT 84
    #define SUCCESS_EXIT 0

typedef struct temperature_data_s {
    double *values;
    int count;
    int capacity;
} temperature_data_t;

typedef struct indicators_s {
    double g;
    double r;
    double s;
} indicators_t;

typedef struct switch_detection_s {
    int total_switches;
    double *aberrations;
    int aberrations_count;
    int aberrations_capacity;
    int last_trend;
} switch_detection_t;

int display_help(void);
int parse_arguments(int argc, char **argv);
temperature_data_t *init_temperature_data(void);
void free_temperature_data(temperature_data_t *data);
int add_temperature(temperature_data_t *data, double temp);
indicators_t calculate_indicators(temperature_data_t *data, int period);
double calculate_temperature_increase_average(temperature_data_t *data,
    int period);
double calculate_relative_evolution(temperature_data_t *data, int period);
double calculate_standard_deviation(temperature_data_t *data, int period);
int detect_switch(temperature_data_t *data, switch_detection_t *detection,
    int period);
void add_aberration(switch_detection_t *detection, double value);
void display_final_results(switch_detection_t *detection);
switch_detection_t *init_switch_detection(void);
void free_switch_detection(switch_detection_t *detection);

#endif /* !GROUNDHOG_H_ */