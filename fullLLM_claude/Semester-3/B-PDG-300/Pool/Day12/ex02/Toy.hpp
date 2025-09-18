/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 1
** File description:
** Toy class header
*/

#ifndef TOY_HPP_
#define TOY_HPP_

#include "Picture.hpp"
#include <string>

class Toy
{
public:
    enum ToyType {
        BASIC_TOY,
        ALIEN,
        BUZZ,
        WOODY
    };

private:
    ToyType type;
    std::string name;
    Picture picture;

public:
    Toy();
    Toy(ToyType type, const std::string& name, const std::string& filename);
    Toy(const Toy& other);              // Copy constructor
    Toy& operator=(const Toy& other);   // Assignment operator
    ~Toy();                             // Destructor

    // Getters
    ToyType getType() const;
    std::string getName() const;
    std::string getAscii() const;

    // Setters
    void setName(const std::string& name);
    bool setAscii(const std::string& filename);
};

#endif /* !TOY_HPP_ */