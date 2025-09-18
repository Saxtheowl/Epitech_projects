/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 3
** File description:
** Woody class implementation
*/

#include "Woody.hpp"
#include <iostream>

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

void Woody::speak(const std::string& statement)
{
    std::cout << "WOODY: " << getName() << " \"" << statement << "\"" << std::endl;
}