/*
** EPITECH PROJECT, 2025
** Fridge
** File description:
** recipes
*/

#include "fridge.h"

static int check_pizza_ingredients(fridge_t *fridge)
{
    int tomato_idx = find_ingredient(fridge, "tomato");
    int dough_idx = find_ingredient(fridge, "dough");
    int onion_idx = find_ingredient(fridge, "onion");
    int olive_idx = find_ingredient(fridge, "olive");
    int pepper_idx = find_ingredient(fridge, "pepper");
    int ham_idx = find_ingredient(fridge, "ham");
    int cheese_idx = find_ingredient(fridge, "cheese");

    if (fridge->ingredients[tomato_idx].quantity < 5 ||
        fridge->ingredients[dough_idx].quantity < 1 ||
        fridge->ingredients[onion_idx].quantity < 3 ||
        fridge->ingredients[olive_idx].quantity < 8 ||
        fridge->ingredients[pepper_idx].quantity < 8 ||
        fridge->ingredients[ham_idx].quantity < 4 ||
        fridge->ingredients[cheese_idx].quantity < 3)
        return 0;
    return 1;
}

static void consume_pizza_ingredients(fridge_t *fridge)
{
    int tomato_idx = find_ingredient(fridge, "tomato");
    int dough_idx = find_ingredient(fridge, "dough");
    int onion_idx = find_ingredient(fridge, "onion");
    int olive_idx = find_ingredient(fridge, "olive");
    int pepper_idx = find_ingredient(fridge, "pepper");
    int ham_idx = find_ingredient(fridge, "ham");
    int cheese_idx = find_ingredient(fridge, "cheese");

    fridge->ingredients[tomato_idx].quantity -= 5;
    fridge->ingredients[dough_idx].quantity -= 1;
    fridge->ingredients[onion_idx].quantity -= 3;
    fridge->ingredients[olive_idx].quantity -= 8;
    fridge->ingredients[pepper_idx].quantity -= 8;
    fridge->ingredients[ham_idx].quantity -= 4;
    fridge->ingredients[cheese_idx].quantity -= 3;
}

int make_pizza(fridge_t *fridge)
{
    if (!check_pizza_ingredients(fridge)) {
        my_putstr("Not enough ingredients for pizza\n");
        return 1;
    }
    consume_pizza_ingredients(fridge);
    my_putstr("Pizza made!\n");
    return 0;
}

static int check_pasta_ingredients(fridge_t *fridge)
{
    int tomato_idx = find_ingredient(fridge, "tomato");
    int pasta_idx = find_ingredient(fridge, "pasta");
    int olive_idx = find_ingredient(fridge, "olive");
    int cheese_idx = find_ingredient(fridge, "cheese");
    int ham_idx = find_ingredient(fridge, "ham");

    if (fridge->ingredients[tomato_idx].quantity < 5 ||
        fridge->ingredients[pasta_idx].quantity < 2 ||
        fridge->ingredients[olive_idx].quantity < 6 ||
        fridge->ingredients[cheese_idx].quantity < 3 ||
        fridge->ingredients[ham_idx].quantity < 4)
        return 0;
    return 1;
}

static void consume_pasta_ingredients(fridge_t *fridge)
{
    int tomato_idx = find_ingredient(fridge, "tomato");
    int pasta_idx = find_ingredient(fridge, "pasta");
    int olive_idx = find_ingredient(fridge, "olive");
    int cheese_idx = find_ingredient(fridge, "cheese");
    int ham_idx = find_ingredient(fridge, "ham");

    fridge->ingredients[tomato_idx].quantity -= 5;
    fridge->ingredients[pasta_idx].quantity -= 2;
    fridge->ingredients[olive_idx].quantity -= 6;
    fridge->ingredients[cheese_idx].quantity -= 3;
    fridge->ingredients[ham_idx].quantity -= 4;
}

int make_pasta(fridge_t *fridge)
{
    if (!check_pasta_ingredients(fridge)) {
        my_putstr("Not enough ingredients for pasta\n");
        return 1;
    }
    consume_pasta_ingredients(fridge);
    my_putstr("Pasta made!\n");
    return 0;
}