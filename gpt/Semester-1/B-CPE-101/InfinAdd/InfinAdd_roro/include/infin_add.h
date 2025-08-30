/*
** EPITECH PROJECT, 2025
** InfinAdd_roro
** File description:
** Prototypes
*/

#ifndef INFIN_ADD_H
    #define INFIN_ADD_H

    #define ERR_CODE 84

    char *infin_add(const char *a, const char *b);

    int is_number(const char *s);
    void trim_sign(const char *s, const char **digits, int *neg);

#endif /* INFIN_ADD_H */
