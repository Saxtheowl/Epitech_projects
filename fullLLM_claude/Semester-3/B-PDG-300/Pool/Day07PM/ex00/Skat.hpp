/*
** EPITECH PROJECT, 2024
** Day07 PDG - Exercise 0
** File description:
** Skat class header
*/

#ifndef SKAT_HPP_
#define SKAT_HPP_

#include <string>

class Skat
{
public:
    Skat(const std::string &name = "bob", int stimPaks = 15);
    ~Skat();

    int &stimPaks();
    const std::string &name();
    void shareStimPaks(int number, int &stock);
    void addStimPaks(unsigned int number);
    void useStimPaks();
    void status() const;

private:
    std::string _name;
    int _stimPaks;
};

#endif /* !SKAT_HPP_ */