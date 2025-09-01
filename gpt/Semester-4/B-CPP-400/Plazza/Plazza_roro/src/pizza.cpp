/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Pizza helpers
*/

#include <map>
#include <chrono>
#include "plazza.hpp"

static const std::map<PizzaType,int> base_time = {
    {PizzaType::Margarita, 1}, {PizzaType::Regina, 2},
    {PizzaType::Americana, 2}, {PizzaType::Fantasia, 4}
};

int pizza_cook_time_ms(PizzaType t, double mult)
{
    auto it = base_time.find(t);
    int s = (it == base_time.end()) ? 1 : it->second;
    int ms = (int)(s * mult * 1000.0);
    return ms < 1 ? 1 : ms;
}

static const char *ING[] = {
    "doe","tomato","gruyere","ham","mushrooms","steak","eggplant","goat","love"
};

const char **plz_ingredients()
{
    return ING;
}

int plz_ingredients_count()
{
    return (int)(sizeof(ING)/sizeof(ING[0]));
}

const char *plz_type_name(PizzaType t)
{
    switch (t) {
        case PizzaType::Margarita: return "Margarita";
        case PizzaType::Regina: return "Regina";
        case PizzaType::Americana: return "Americana";
        case PizzaType::Fantasia: return "Fantasia";
    }
    return "Unknown";
}

const char *plz_size_name(PizzaSize s)
{
    switch (s) {
        case PizzaSize::S: return "S";
        case PizzaSize::M: return "M";
        case PizzaSize::L: return "L";
        case PizzaSize::XL: return "XL";
        case PizzaSize::XXL: return "XXL";
    }
    return "?";
}
