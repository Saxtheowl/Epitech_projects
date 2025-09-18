/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 1
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
    Picture(const Picture& other);              // Copy constructor
    Picture& operator=(const Picture& other);   // Assignment operator
    ~Picture();                                 // Destructor

    bool getPictureFromFile(const std::string& file);
};

#endif /* !PICTURE_HPP_ */