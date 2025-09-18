/*
** EPITECH PROJECT, 2024
** Day10 PDG - Exercise 0
** File description:
** ABerry abstract class implementation
*/

#include "ABerry.hpp"

ABerry::ABerry(const std::string& name, unsigned int vitamins)
    : AFruit(name, vitamins)
{
    // Berries are always peeled
    peeled = true;
}

bool ABerry::isPeeled() const
{
    // Berries are always considered peeled
    return true;
}

void ABerry::peel()
{
    // Berries don't need to be peeled, they're always peeled
    // No action needed
}