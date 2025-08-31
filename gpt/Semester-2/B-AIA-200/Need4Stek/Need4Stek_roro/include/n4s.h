/*
** EPITECH PROJECT, 2025
** Need4Stek
** File description:
** Prototypes
*/

#ifndef N4S_H
    #define N4S_H

int parse_lidar(const char *line, double *out, int max);
void compute_controls(const double *lidar, int n, double *speed, double *steer);
int ai_loop(void);

#endif /* N4S_H */

