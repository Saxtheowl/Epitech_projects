/*
** EPITECH PROJECT, 2025
** Rtype_roro
** File description:
**   CLI utilities
*/

#include "util.hpp"
#include <cctype>

static bool all_digit(const std::string &s)
{
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return !s.empty();
}

bool is_help(int ac, char **av)
{
    return ac == 2 && std::string(av[1]) == "-h";
}

bool parse_port(const std::string &s, int &out)
{
    if (!all_digit(s))
        return false;
    out = std::stoi(s);
    return out > 0 && out <= 65535;
}

