/*
** EPITECH PROJECT, 2024
** Day13 PDG - Exercise 4
** File description:
** Command class header
*/

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <string>
#include <map>
#include <functional>
#include <exception>

class Command
{
public:
    class Error : public std::exception
    {
    private:
        const char* message;
        
    public:
        Error(const char* msg) : message(msg) {}
        const char* what() const noexcept override
        {
            return message;
        }
    };

private:
    std::map<std::string, std::function<void()>> commands;

public:
    Command() = default;
    ~Command() = default;

    void registerCommand(const std::string& name, const std::function<void()>& function);
    void executeCommand(const std::string& name);
};

#endif /* !COMMAND_HPP_ */