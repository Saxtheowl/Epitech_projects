/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 4
** File description:
** Paladin class implementation (multiple inheritance)
*/

#include "Paladin.hpp"

Paladin::Paladin(const std::string &name, int power) : Peasant(name, power), Knight(name, power), Priest(name, power)
{
    std::cout << name << " fights for the light." << std::endl;
}

Paladin::~Paladin()
{
    std::cout << name << " is blessed." << std::endl;
}

int Paladin::attack()
{
    return Knight::attack();
}

int Paladin::special()
{
    return Priest::special();
}

void Paladin::rest()
{
    Priest::rest();
}