/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Header file for Groundhog weather analysis
*/

#ifndef GROUNDHOG_H_
#define GROUNDHOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

typedef struct temperature_s {
    double value;
    struct temperature_s *next;
} temperature_t;

typedef struct groundhog_s {
    int period;
    temperature_t *temperatures;
    temperature_t **aberrations;
    int aberration_count;
    int tendency_switches;
    int current_tendency;
    int data_count;
} groundhog_t;

// Main functions
int groundhog_main(int period);
void display_help(void);

// Calculations
double calculate_increase_average(temperature_t *temps, int period);
double calculate_relative_evolution(temperature_t *temps, int period);
double calculate_standard_deviation(temperature_t *temps, int period);
int detect_tendency_switch(groundhog_t *groundhog, double g, double r);

// Temperature management
temperature_t *add_temperature(temperature_t *list, double value);
void free_temperatures(temperature_t *list);
double get_nth_temperature(temperature_t *list, int n);
int count_temperatures(temperature_t *list);

// Aberrations
void add_aberration(groundhog_t *groundhog, double temp);
void display_final_results(groundhog_t *groundhog);

// Utils
int is_nan_double(double value);
void print_indicators(double g, double r, double s, int switch_detected);

#endif /* !GROUNDHOG_H_ */