/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 3
** File description:
** Buzz class implementation
*/

#include "Buzz.hpp"
#include <iostream>

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

void Buzz::speak(const std::string& statement)
{
    std::cout << "BUZZ: " << getName() << " \"" << statement << "\"" << std::endl;
}