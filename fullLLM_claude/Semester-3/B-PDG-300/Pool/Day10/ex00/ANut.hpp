/*
** EPITECH PROJECT, 2024
** Day10 PDG - Exercise 0
** File description:
** ANut abstract class - for nuts
*/

#ifndef ANUT_HPP_
#define ANUT_HPP_

#include "AFruit.hpp"

class ANut : public AFruit
{
public:
    ANut(const std::string& name, unsigned int vitamins);
    virtual ~ANut() = default;
};

#endif /* !ANUT_HPP_ */