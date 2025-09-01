/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   Public interfaces
*/

#ifndef PLAZZA_HPP
#define PLAZZA_HPP

#include <string>
#include <vector>

struct Args {
    double multiplier;
    int cooks_per_kitchen;
    int refill_ms;
};

struct OrderItem {
    std::string type;
    std::string size; /* S,M,L,XL,XXL */
    int count;
};

int parse_args(int ac, char **av, Args &out);
std::vector<OrderItem> parse_orders_line(const std::string &line,
    bool &ok);

int plazza_main(int ac, char **av);

#endif /* PLAZZA_HPP */

