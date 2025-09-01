/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   CLI arguments parsing
*/

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include "plazza.hpp"

static int parse_double(const char *s, double &out)
{
    char *end = nullptr;
    errno = 0;
    double v = std::strtod(s, &end);
    if (errno != 0 || end == s || *end != '\0')
        return -1;
    out = v;
    return 0;
}

static int parse_int(const char *s, int &out)
{
    char *end = nullptr;
    errno = 0;
    long v = std::strtol(s, &end, 10);
    if (errno != 0 || end == s || *end != '\0' || v <= 0 || v > 1000000)
        return -1;
    out = static_cast<int>(v);
    return 0;
}

int parse_args(int ac, char **av, Args &out)
{
    if (ac != 4)
        return -1;
    if (parse_double(av[1], out.multiplier) != 0)
        return -1;
    if (parse_int(av[2], out.cooks_per_kitchen) != 0)
        return -1;
    if (parse_int(av[3], out.refill_ms) != 0)
        return -1;
    return 0;
}

