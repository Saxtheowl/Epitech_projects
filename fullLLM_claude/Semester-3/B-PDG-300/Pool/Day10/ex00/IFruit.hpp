/*
** EPITECH PROJECT, 2024
** Day10 PDG - Exercise 0
** File description:
** IFruit interface - pure virtual fruit interface
*/

#ifndef IFRUIT_HPP_
#define IFRUIT_HPP_

#include <string>

class IFruit
{
public:
    virtual ~IFruit() = default;

    virtual unsigned int getVitamins() const = 0;  // Returns vitamins when peeled, 0 otherwise
    virtual std::string getName() const = 0;       // Returns fruit name
    virtual bool isPeeled() const = 0;             // Returns peeling status
    virtual void peel() = 0;                       // Peels the fruit (not peeled by default)
};

#endif /* !IFRUIT_HPP_ */