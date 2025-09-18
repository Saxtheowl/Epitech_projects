/*
** EPITECH PROJECT, 2024
** Day07AM PDG - RESISTANCE IS FUTILE
** File description:
** Federation namespace and Starfleet::Ship class
*/

#ifndef FEDERATION_HPP_
#define FEDERATION_HPP_

#include <string>

namespace Federation
{
    namespace Starfleet
    {
        class Ship
        {
        private:
            int _length;
            int _width;
            std::string _name;
            short _maxWarp;

        public:
            Ship(int length, int width, std::string name, short maxWarp);
            ~Ship() = default;
        };
    }
}

#endif /* !FEDERATION_HPP_ */