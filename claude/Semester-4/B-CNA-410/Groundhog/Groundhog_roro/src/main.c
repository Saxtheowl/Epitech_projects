/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Main function
*/

#include "groundhog.h"

int main(int argc, char **argv)
{
    int period = 0;
    temperature_data_t *data = NULL;
    switch_detection_t *detection = NULL;
    char buffer[1024];
    double temp = 0.0;
    indicators_t indicators;

    period = parse_arguments(argc, argv);
    if (period == -1)
        return ERROR_EXIT;
    data = init_temperature_data();
    detection = init_switch_detection();
    if (!data || !detection)
        return ERROR_EXIT;
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strncmp(buffer, "STOP", 4) == 0)
            break;
        temp = atof(buffer);
        add_aberration(detection, temp);
        if (add_temperature(data, temp) == -1)
            return ERROR_EXIT;
        indicators = calculate_indicators(data, period);
        if (isnan(indicators.g))
            printf("g=nan");
        else
            printf("g=%.2f", indicators.g);
        if (isnan(indicators.r))
            printf(" r=nan%%");
        else
            printf(" r=%.0f%%", indicators.r);
        if (isnan(indicators.s))
            printf(" s=nan");
        else
            printf(" s=%.2f", indicators.s);
        if (detect_switch(data, detection, period))
            printf(" a switch occurs");
        printf("\n");
    }
    display_final_results(detection);
    free_temperature_data(data);
    free_switch_detection(detection);
    return SUCCESS_EXIT;
}