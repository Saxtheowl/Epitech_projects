/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 2
** File description:
** Woody class implementation
*/

#include "Woody.hpp"

Woody::Woody(const std::string& name)
    : Toy(WOODY, name, "woody.txt")
{
}

Woody::Woody(const std::string& name, const std::string& filename)
    : Toy(WOODY, name, filename)
{
}

Woody::~Woody()
{
}