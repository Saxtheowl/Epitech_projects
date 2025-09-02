/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Main groundhog logic
*/

#include "groundhog.h"

void add_aberration(groundhog_t *groundhog, double temp)
{
    groundhog->aberrations = realloc(groundhog->aberrations, 
                                   sizeof(temperature_t*) * (groundhog->aberration_count + 1));
    if (!groundhog->aberrations)
        return;
    
    temperature_t *aberration = malloc(sizeof(temperature_t));
    if (!aberration)
        return;
    
    aberration->value = temp;
    aberration->next = NULL;
    
    groundhog->aberrations[groundhog->aberration_count] = aberration;
    groundhog->aberration_count++;
}

static int compare_aberrations(const void *a, const void *b)
{
    temperature_t **temp_a = (temperature_t**)a;
    temperature_t **temp_b = (temperature_t**)b;
    
    // Sort by absolute deviation from mean (simple weirdness metric)
    double diff_a = fabs((*temp_a)->value - 30.0); // Assume 30°C as baseline
    double diff_b = fabs((*temp_b)->value - 30.0);
    
    if (diff_a < diff_b) return 1;
    if (diff_a > diff_b) return -1;
    return 0;
}

void display_final_results(groundhog_t *groundhog)
{
    printf("Global tendency switched %d times\n", groundhog->tendency_switches);
    
    if (groundhog->aberration_count > 0) {
        // Sort aberrations by weirdness
        qsort(groundhog->aberrations, groundhog->aberration_count, 
              sizeof(temperature_t*), compare_aberrations);
        
        printf("5 weirdest values are [");
        int limit = groundhog->aberration_count < 5 ? groundhog->aberration_count : 5;
        for (int i = 0; i < limit; i++) {
            if (i > 0) printf(", ");
            printf("%.1f", groundhog->aberrations[i]->value);
        }
        printf("]\n");
    } else {
        printf("5 weirdest values are []\n");
    }
}

int groundhog_main(int period)
{
    groundhog_t groundhog = {
        .period = period,
        .temperatures = NULL,
        .aberrations = NULL,
        .aberration_count = 0,
        .tendency_switches = 0,
        .current_tendency = 0,
        .data_count = 0
    };
    
    char line[256];
    while (fgets(line, sizeof(line), stdin)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        if (strcmp(line, "STOP") == 0)
            break;
        
        double temp = atof(line);
        groundhog.temperatures = add_temperature(groundhog.temperatures, temp);
        groundhog.data_count++;
        
        // Add to aberrations list for final analysis
        add_aberration(&groundhog, temp);
        
        // Print the temperature first
        printf("%.1f\n", temp);
        fflush(stdout);
        
        // Calculate indicators
        double g = calculate_increase_average(groundhog.temperatures, period);
        double r = calculate_relative_evolution(groundhog.temperatures, period);
        double s = calculate_standard_deviation(groundhog.temperatures, period);
        
        // Detect tendency switch
        int switch_detected = detect_tendency_switch(&groundhog, g, r);
        
        print_indicators(g, r, s, switch_detected);
        fflush(stdout);
    }
    
    display_final_results(&groundhog);
    
    // Cleanup
    free_temperatures(groundhog.temperatures);
    for (int i = 0; i < groundhog.aberration_count; i++) {
        free(groundhog.aberrations[i]);
    }
    free(groundhog.aberrations);
    
    return 0;
}