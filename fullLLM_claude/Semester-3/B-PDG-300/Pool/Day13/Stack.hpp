/*
** EPITECH PROJECT, 2024
** Day13 PDG - Exercise 2
** File description:
** Stack class header
*/

#ifndef STACK_HPP_
#define STACK_HPP_

#include <stack>
#include <exception>

class Stack
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
    std::stack<double> stack;

public:
    Stack() = default;
    ~Stack() = default;

    void push(double value);
    double pop();
    double top() const;
    void add();
    void sub();
    void mul();
    void div();
};

#endif /* !STACK_HPP_ */