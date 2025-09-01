/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Public interfaces
*/

#ifndef PLAZZA_HPP
#define PLAZZA_HPP

#include <string>
#include <vector>
#include <optional>

enum class PizzaType { Regina=1, Margarita=2, Americana=4, Fantasia=8 };
enum class PizzaSize { S=1, M=2, L=4, XL=8, XXL=16 };

struct Args {
    double multiplier;
    int cooks;
    int restock_ms;
};

bool parse_args(int ac, char **av, Args &out);

struct OrderItem { PizzaType type; PizzaSize size; int count; };
std::optional<std::vector<OrderItem>> parse_order_line(const std::string &line);

int run_reception(const Args &args);

int pizza_cook_time_ms(PizzaType t, double mult);

// Ingredients list (shared between reception and kitchens)
const char **plz_ingredients();
int plz_ingredients_count();

// Stringifiers
const char *plz_type_name(PizzaType t);
const char *plz_size_name(PizzaSize s);

#endif
