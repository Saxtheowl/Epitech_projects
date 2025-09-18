/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 2
** File description:
** Buzz class implementation
*/

#include "Buzz.hpp"

Buzz::Buzz(const std::string& name)
    : Toy(BUZZ, name, "buzz.txt")
{
}

Buzz::Buzz(const std::string& name, const std::string& filename)
    : Toy(BUZZ, name, filename)
{
}

Buzz::~Buzz()
{
}