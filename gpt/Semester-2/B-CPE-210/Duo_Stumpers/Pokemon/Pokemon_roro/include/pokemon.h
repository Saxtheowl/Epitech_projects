/*
** EPITECH PROJECT, 2025
** Pokemon
** File description:
** Prototypes
*/

#ifndef POKEMON_H
    #define POKEMON_H

typedef enum { EFF_NOT, EFF_NEUTRAL, EFF_SUPER } effectiveness_t;

effectiveness_t effectiveness(const char *att, const char *def);

#endif /* POKEMON_H */

