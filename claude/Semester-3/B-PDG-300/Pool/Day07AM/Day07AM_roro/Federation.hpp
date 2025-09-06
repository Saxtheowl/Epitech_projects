/*
** EPITECH PROJECT, 2025
** Day07AM - Federation
** File description:
** Federation namespace with nested Starfleet namespace
*/

#pragma once

#include <string>

namespace Federation {
    namespace Starfleet {
        class Ship {
        private:
            const int _length;
            const int _width;
            const std::string _name;
            const short _maxWarp;

        public:
            Ship(int length, int width, std::string name, short maxWarp);
        };
    }
}