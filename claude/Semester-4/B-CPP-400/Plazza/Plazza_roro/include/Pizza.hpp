/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Pizza classes and enums
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <string>
#include <vector>
#include <chrono>

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

enum IngredientType {
    Doe,
    Tomato,
    Gruyere,
    Ham,
    Mushrooms,
    Steak,
    Eggplant,
    GoatCheese,
    ChiefLove
};

class Pizza {
public:
    Pizza(PizzaType type, PizzaSize size);
    ~Pizza() = default;

    PizzaType getType() const { return _type; }
    PizzaSize getSize() const { return _size; }
    const std::vector<IngredientType>& getIngredients() const { return _ingredients; }
    int getCookingTime() const { return _cookingTime; }
    std::string getTypeName() const;
    std::string getSizeName() const;

    void pack(std::string& buffer) const;
    static Pizza unpack(const std::string& buffer);

private:
    PizzaType _type;
    PizzaSize _size;
    std::vector<IngredientType> _ingredients;
    int _cookingTime;

    void initializeIngredients();
    void setCookingTime();
};

class PizzaOrder {
public:
    PizzaOrder(const std::string& line);
    ~PizzaOrder() = default;

    const std::vector<Pizza>& getPizzas() const { return _pizzas; }
    bool isValid() const { return _valid; }

private:
    std::vector<Pizza> _pizzas;
    bool _valid;

    void parseLine(const std::string& line);
    Pizza parsePizza(const std::string& pizzaStr);
    PizzaType parseType(const std::string& typeStr);
    PizzaSize parseSize(const std::string& sizeStr);
};

#endif /* !PIZZA_HPP_ */