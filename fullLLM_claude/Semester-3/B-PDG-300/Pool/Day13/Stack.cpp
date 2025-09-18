/*
** EPITECH PROJECT, 2024
** Day13 PDG - Exercise 2
** File description:
** Stack class implementation
*/

#include "Stack.hpp"

void Stack::push(double value)
{
    stack.push(value);
}

double Stack::pop()
{
    if (stack.empty()) {
        throw Error("Empty stack");
    }
    double value = stack.top();
    stack.pop();
    return value;
}

double Stack::top() const
{
    if (stack.empty()) {
        throw Error("Empty stack");
    }
    return stack.top();
}

void Stack::add()
{
    if (stack.size() < 2) {
        throw Error("Not enough operands");
    }
    double b = pop();
    double a = pop();
    push(a + b);
}

void Stack::sub()
{
    if (stack.size() < 2) {
        throw Error("Not enough operands");
    }
    double b = pop();
    double a = pop();
    push(a - b);
}

void Stack::mul()
{
    if (stack.size() < 2) {
        throw Error("Not enough operands");
    }
    double b = pop();
    double a = pop();
    push(a * b);
}

void Stack::div()
{
    if (stack.size() < 2) {
        throw Error("Not enough operands");
    }
    double b = pop();
    double a = pop();
    push(a / b);
}