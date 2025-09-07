/*
** EPITECH PROJECT, 2025
** Rtype_roro
** File description:
**   CLI utilities
*/

#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

bool is_help(int ac, char **av);
bool parse_port(const std::string &s, int &out);

#endif /* UTIL_HPP */

