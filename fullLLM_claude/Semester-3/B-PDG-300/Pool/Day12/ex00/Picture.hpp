/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 0
** File description:
** Picture class header
*/

#ifndef PICTURE_HPP_
#define PICTURE_HPP_

#include <string>

class Picture
{
public:
    std::string data;

    Picture();
    Picture(const std::string& file);
    ~Picture() = default;

    bool getPictureFromFile(const std::string& file);
};

#endif /* !PICTURE_HPP_ */