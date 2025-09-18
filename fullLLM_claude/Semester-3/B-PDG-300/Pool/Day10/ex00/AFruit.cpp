/*
** EPITECH PROJECT, 2024
** Day10 PDG - Exercise 0
** File description:
** AFruit abstract class implementation
*/

#include "AFruit.hpp"

AFruit::AFruit(const std::string& name, unsigned int vitamins)
    : name(name), vitamins(vitamins), peeled(false)
{
}

std::string AFruit::getName() const
{
    return name;
}

unsigned int AFruit::getVitamins() const
{
    return peeled ? vitamins : 0;
}

bool AFruit::isPeeled() const
{
    return peeled;
}

void AFruit::peel()
{
    peeled = true;
}

std::ostream& operator<<(std::ostream& os, const IFruit& fruit)
{
    os << fruit.getName();
    return os;
}