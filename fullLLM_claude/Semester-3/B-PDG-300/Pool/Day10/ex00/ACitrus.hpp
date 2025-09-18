/*
** EPITECH PROJECT, 2024
** Day10 PDG - Exercise 0
** File description:
** ACitrus abstract class - for citrus fruits
*/

#ifndef ACITRUS_HPP_
#define ACITRUS_HPP_

#include "AFruit.hpp"

class ACitrus : public AFruit
{
public:
    ACitrus(const std::string& name, unsigned int vitamins);
    virtual ~ACitrus() = default;
};

#endif /* !ACITRUS_HPP_ */