/*
** EPITECH PROJECT, 2024
** Day12 PDG - Test Exercise 0
** File description:
** Test for Picture and Toy classes
*/

#include "Toy.hpp"
#include <iostream>

int main()
{
    Toy toto;
    Toy ET(Toy::ALIEN, "green", "./alien.txt");

    toto.setName("TOTO !");

    if (toto.getType() == Toy::BASIC_TOY)
        std::cout << "basic toy: " << toto.getName() << std::endl
                  << toto.getAscii() << std::endl;

    if (ET.getType() == Toy::ALIEN)
        std::cout << "this alien is: " << ET.getName() << std::endl
                  << ET.getAscii() << std::endl;

    return 0;
}