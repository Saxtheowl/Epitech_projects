/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Switch detection and aberration tracking
*/

#include "groundhog.h"

switch_detection_t *init_switch_detection(void)
{
    switch_detection_t *detection = malloc(sizeof(switch_detection_t));

    if (!detection)
        return NULL;
    detection->aberrations = malloc(sizeof(double) * 1000);
    if (!detection->aberrations) {
        free(detection);
        return NULL;
    }
    detection->total_switches = 0;
    detection->aberrations_count = 0;
    detection->aberrations_capacity = 1000;
    detection->last_trend = 0;
    return detection;
}

void free_switch_detection(switch_detection_t *detection)
{
    if (!detection)
        return;
    if (detection->aberrations)
        free(detection->aberrations);
    free(detection);
}

int detect_switch(temperature_data_t *data, switch_detection_t *detection,
    int period)
{
    double current_increase = 0.0;
    int current_trend = 0;
    int half_period = period / 2 + 1;

    if (!data || !detection || data->count < period + half_period)
        return 0;
    current_increase = calculate_temperature_increase_average(data, period);
    if (isnan(current_increase))
        return 0;
    current_trend = (current_increase > 0.5) ? 1 : -1;
    if (detection->last_trend != 0 && detection->last_trend != current_trend) {
        detection->total_switches++;
        detection->last_trend = current_trend;
        return 1;
    }
    if (detection->last_trend == 0)
        detection->last_trend = current_trend;
    return 0;
}

void add_aberration(switch_detection_t *detection, double value)
{
    double *new_aberrations = NULL;

    if (!detection)
        return;
    if (detection->aberrations_count >= detection->aberrations_capacity) {
        detection->aberrations_capacity *= 2;
        new_aberrations = realloc(detection->aberrations,
            sizeof(double) * detection->aberrations_capacity);
        if (!new_aberrations)
            return;
        detection->aberrations = new_aberrations;
    }
    detection->aberrations[detection->aberrations_count++] = value;
}

static int compare_doubles(const void *a, const void *b)
{
    double da = *(const double *)a;
    double db = *(const double *)b;

    if (da > db) return -1;
    if (da < db) return 1;
    return 0;
}

void display_final_results(switch_detection_t *detection)
{
    int i = 0;
    int count = 0;

    if (!detection)
        return;
    printf("Global tendency switched %d times\n", detection->total_switches);
    qsort(detection->aberrations, detection->aberrations_count,
        sizeof(double), compare_doubles);
    count = (detection->aberrations_count < 5) ?
        detection->aberrations_count : 5;
    printf("5 weirdest values are [");
    for (i = 0; i < count; i++) {
        printf("%.1f", detection->aberrations[i]);
        if (i < count - 1)
            printf(", ");
    }
    printf("]\n");
}