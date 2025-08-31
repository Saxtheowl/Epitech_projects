/*
** EPITECH PROJECT, 2025
** Pokemon
** File description:
** Main and logic
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pokemon.h"

static int eq_ci(const char *a, const char *b)
{
    int i;

    i = 0;
    while (a[i] && b[i]) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i]))
            return 0;
        i = i + 1;
    }
    return a[i] == '\0' && b[i] == '\0';
}

effectiveness_t effectiveness(const char *att, const char *def)
{
    if ((eq_ci(att, "fire") && eq_ci(def, "grass")) ||
        (eq_ci(att, "water") && eq_ci(def, "fire")) ||
        (eq_ci(att, "grass") && eq_ci(def, "water")) ||
        (eq_ci(att, "electric") && eq_ci(def, "water")))
        return EFF_SUPER;
    if ((eq_ci(att, "fire") && eq_ci(def, "water")) ||
        (eq_ci(att, "water") && eq_ci(def, "grass")) ||
        (eq_ci(att, "grass") && eq_ci(def, "fire")) ||
        (eq_ci(att, "electric") && (eq_ci(def, "grass") || eq_ci(def, "ground"))))
        return EFF_NOT;
    return EFF_NEUTRAL;
}

int main(int argc, char **argv)
{
    effectiveness_t e;

    if (argc != 3)
        return 84;
    e = effectiveness(argv[1], argv[2]);
    if (e == EFF_SUPER)
        printf("super effective\n");
    else if (e == EFF_NOT)
        printf("not very effective\n");
    else
        printf("neutral\n");
    return 0;
}

