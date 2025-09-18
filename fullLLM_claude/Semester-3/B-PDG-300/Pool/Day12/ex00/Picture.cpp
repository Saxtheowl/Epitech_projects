/*
** EPITECH PROJECT, 2024
** Day12 PDG - Exercise 0
** File description:
** Picture class implementation
*/

#include "Picture.hpp"
#include <fstream>
#include <sstream>

Picture::Picture()
    : data("")
{
}

Picture::Picture(const std::string& file)
    : data("")
{
    if (!getPictureFromFile(file)) {
        data = "ERROR";
    }
}

bool Picture::getPictureFromFile(const std::string& file)
{
    std::ifstream infile(file);
    if (!infile.is_open()) {
        data = "ERROR";
        return false;
    }

    std::stringstream buffer;
    buffer << infile.rdbuf();
    data = buffer.str();
    infile.close();
    return true;
}