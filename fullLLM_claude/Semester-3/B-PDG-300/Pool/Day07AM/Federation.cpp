/*
** EPITECH PROJECT, 2024
** Day07AM PDG - RESISTANCE IS FUTILE
** File description:
** Federation namespace implementation
*/

#include "Federation.hpp"
#include <iostream>

namespace Federation
{
    namespace Starfleet
    {
        Ship::Ship(int length, int width, std::string name, short maxWarp)
            : _length(length), _width(width), _name(name), _maxWarp(maxWarp)
        {
            std::cout << "The ship USS " << _name << " has been finished." << std::endl;
            std::cout << "It is " << _length << " m in length and " << _width << " m in width." << std::endl;
            std::cout << "It can go to Warp " << _maxWarp << "!" << std::endl;
        }
    }
}