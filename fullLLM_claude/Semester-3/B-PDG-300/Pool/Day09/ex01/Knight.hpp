/*
** EPITECH PROJECT, 2024
** Day09 PDG - Exercise 1
** File description:
** Knight class header
*/

#ifndef KNIGHT_HPP_
#define KNIGHT_HPP_

#include "Peasant.hpp"

class Knight : public Peasant {
public:
    Knight(const std::string &name, int power);
    ~Knight();

    int attack() override;
    int special() override;
    void rest() override;
};

#endif /* !KNIGHT_HPP_ */