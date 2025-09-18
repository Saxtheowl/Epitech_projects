/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 2
** File description:
** Woody class header
*/

#ifndef WOODY_HPP_
#define WOODY_HPP_

#include "Toy.hpp"

class Woody : public Toy
{
public:
    Woody(const std::string& name);
    Woody(const std::string& name, const std::string& filename);
    ~Woody();
};

#endif /* !WOODY_HPP_ */