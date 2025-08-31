/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** Prototypes
*/

#ifndef FRIDGE_H
    #define FRIDGE_H

typedef struct {
    char name[64];
    int qty;
} item_t;

int parse_list(const char *s, item_t *items, int max);
int can_prepare(const item_t *inv, int n_inv, const item_t *rec, int n_rec);

#endif /* FRIDGE_H */

