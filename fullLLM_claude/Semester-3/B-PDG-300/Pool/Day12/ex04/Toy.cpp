/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 4
** File description:
** Toy class implementation
*/

#include "Toy.hpp"
#include <iostream>

Toy::Toy()
    : type(BASIC_TOY), name("toy"), picture()
{
}

Toy::Toy(ToyType type, const std::string& name, const std::string& filename)
    : type(type), name(name), picture(filename)
{
}

// Getters
Toy::ToyType Toy::getType() const
{
    return type;
}

std::string Toy::getName() const
{
    return name;
}

std::string Toy::getAscii() const
{
    return picture.data;
}

// Setters
void Toy::setName(const std::string& name)
{
    this->name = name;
}

bool Toy::setAscii(const std::string& filename)
{
    return picture.getPictureFromFile(filename);
}

// Copy constructor
Toy::Toy(const Toy& other)
    : type(other.type), name(other.name), picture(other.picture)
{
}

// Assignment operator
Toy& Toy::operator=(const Toy& other)
{
    if (this != &other) {
        type = other.type;
        name = other.name;
        picture = other.picture;
    }
    return *this;
}

// Destructor
Toy::~Toy()
{
}

// Speak method
void Toy::speak(const std::string& statement)
{
    std::cout << name << " \"" << statement << "\"" << std::endl;
}

// Operator << for Toy and string (replaces toy's picture)
void Toy::operator<<(const std::string& str)
{
    picture.data = str;
}

// Operator << for ostream and Toy (prints name and picture)
std::ostream& operator<<(std::ostream& os, const Toy& toy)
{
    os << toy.getName() << std::endl;
    os << toy.getAscii() << std::endl;
    return os;
}