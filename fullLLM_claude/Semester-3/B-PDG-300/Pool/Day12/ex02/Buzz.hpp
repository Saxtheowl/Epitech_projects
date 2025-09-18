/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 2
** File description:
** Buzz class header
*/

#ifndef BUZZ_HPP_
#define BUZZ_HPP_

#include "Toy.hpp"

class Buzz : public Toy
{
public:
    Buzz(const std::string& name);
    Buzz(const std::string& name, const std::string& filename);
    ~Buzz();
};

#endif /* !BUZZ_HPP_ */