/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** fridge core functions
*/

#include "fridge.h"

void init_fridge(fridge_t *fridge)
{
    char ingredients[MAX_INGREDIENTS][20] = {
        "tomato", "dough", "onion", "pasta", 
        "olive", "pepper", "ham", "cheese"
    };
    int i = 0;

    fridge->count = MAX_INGREDIENTS;
    for (i = 0; i < MAX_INGREDIENTS; i++) {
        my_strcpy(fridge->ingredients[i].name, ingredients[i]);
        fridge->ingredients[i].quantity = 0;
    }
}

int find_ingredient(fridge_t *fridge, char *name)
{
    int i = 0;

    for (i = 0; i < fridge->count; i++) {
        if (my_strcmp(fridge->ingredients[i].name, name) == 0)
            return i;
    }
    return -1;
}

void display_fridge(fridge_t *fridge)
{
    int i = 0;
    char *qty_str = NULL;

    my_putstr("Fridge:\n");
    for (i = 0; i < fridge->count; i++) {
        my_putstr("- ");
        my_putstr(fridge->ingredients[i].name);
        my_putstr(": ");
        qty_str = my_itoa(fridge->ingredients[i].quantity);
        if (qty_str) {
            my_putstr(qty_str);
            free(qty_str);
        }
        my_putchar('\n');
    }
}

int add_to_fridge(fridge_t *fridge, char *ingredient, int quantity)
{
    int index = find_ingredient(fridge, ingredient);

    if (index == -1) {
        my_putstr("Unknown ingredient: ");
        my_putstr(ingredient);
        my_putchar('\n');
        return 1;
    }
    fridge->ingredients[index].quantity += quantity;
    return 0;
}