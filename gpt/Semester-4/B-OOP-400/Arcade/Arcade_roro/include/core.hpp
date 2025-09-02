/*
** EPITECH PROJECT, 2025
** Arcade_roro
** File description:
**   Core interfaces
*/

#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include <string>

struct IGame {
    virtual ~IGame() = default;
    virtual const char *name() const = 0;
    virtual void tick() = 0;
};

struct IGraph {
    virtual ~IGraph() = default;
    virtual const char *name() const = 0;
    virtual void draw_text(const std::string &s) = 0;
};

class Core {
public:
    int run(const std::string &graphPath, const std::string &gamePath);
};

#endif /* ARCADE_CORE_HPP */

