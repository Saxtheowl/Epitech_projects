/*
** EPITECH PROJECT, 2024
** Day13 PDG - Exercise 0
** File description:
** Algorithm template functions
*/

#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_

template<typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
const T& min(const T& a, const T& b)
{
    return (a < b) ? a : b;
}

template<typename T>
const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

template<typename T>
const T& clamp(const T& value, const T& min_val, const T& max_val)
{
    if (value < min_val) {
        return min_val;
    }
    if (max_val < value) {
        return max_val;
    }
    return value;
}

#endif /* !ALGORITHM_HPP_ */