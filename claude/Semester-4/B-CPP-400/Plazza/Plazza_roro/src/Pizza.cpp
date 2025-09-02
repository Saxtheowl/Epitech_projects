/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
** Pizza implementation
*/

#include "Pizza.hpp"
#include <sstream>
#include <regex>
#include <algorithm>
#include <stdexcept>

Pizza::Pizza(PizzaType type, PizzaSize size) : _type(type), _size(size) {
    initializeIngredients();
    setCookingTime();
}

void Pizza::initializeIngredients() {
    _ingredients.clear();
    
    switch (_type) {
        case Margarita:
            _ingredients = {Doe, Tomato, Gruyere};
            break;
        case Regina:
            _ingredients = {Doe, Tomato, Gruyere, Ham, Mushrooms};
            break;
        case Americana:
            _ingredients = {Doe, Tomato, Gruyere, Steak};
            break;
        case Fantasia:
            _ingredients = {Doe, Tomato, Eggplant, GoatCheese, ChiefLove};
            break;
    }
}

void Pizza::setCookingTime() {
    switch (_type) {
        case Margarita: _cookingTime = 1; break;
        case Regina: _cookingTime = 2; break;
        case Americana: _cookingTime = 2; break;
        case Fantasia: _cookingTime = 4; break;
    }
}

std::string Pizza::getTypeName() const {
    switch (_type) {
        case Regina: return "Regina";
        case Margarita: return "Margarita";
        case Americana: return "Americana";
        case Fantasia: return "Fantasia";
        default: return "Unknown";
    }
}

std::string Pizza::getSizeName() const {
    switch (_size) {
        case S: return "S";
        case M: return "M";
        case L: return "L";
        case XL: return "XL";
        case XXL: return "XXL";
        default: return "Unknown";
    }
}

void Pizza::pack(std::string& buffer) const {
    buffer = std::to_string(static_cast<int>(_type)) + ";" + std::to_string(static_cast<int>(_size));
}

Pizza Pizza::unpack(const std::string& buffer) {
    std::stringstream ss(buffer);
    std::string typeStr, sizeStr;
    
    if (std::getline(ss, typeStr, ';') && std::getline(ss, sizeStr)) {
        PizzaType type = static_cast<PizzaType>(std::stoi(typeStr));
        PizzaSize size = static_cast<PizzaSize>(std::stoi(sizeStr));
        return Pizza(type, size);
    }
    
    throw std::runtime_error("Failed to unpack pizza data");
}

PizzaOrder::PizzaOrder(const std::string& line) : _valid(true) {
    try {
        parseLine(line);
    } catch (const std::exception&) {
        _valid = false;
        _pizzas.clear();
    }
}

void PizzaOrder::parseLine(const std::string& line) {
    std::regex orderRegex(R"(\s*([a-zA-Z]+)\s+(S|M|L|XL|XXL)\s+x(\d+)\s*(?:;|$))");
    std::sregex_iterator iter(line.begin(), line.end(), orderRegex);
    std::sregex_iterator end;

    if (iter == end) {
        throw std::runtime_error("Invalid order format");
    }

    while (iter != end) {
        std::smatch match = *iter;
        std::string type = match[1].str();
        std::string size = match[2].str();
        int quantity = std::stoi(match[3].str());

        PizzaType pizzaType = parseType(type);
        PizzaSize pizzaSize = parseSize(size);

        for (int i = 0; i < quantity; ++i) {
            _pizzas.emplace_back(pizzaType, pizzaSize);
        }
        
        ++iter;
    }
}

PizzaType PizzaOrder::parseType(const std::string& typeStr) {
    std::string lower = typeStr;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    
    if (lower == "regina") return Regina;
    if (lower == "margarita") return Margarita;
    if (lower == "americana") return Americana;
    if (lower == "fantasia") return Fantasia;
    
    throw std::runtime_error("Unknown pizza type: " + typeStr);
}

PizzaSize PizzaOrder::parseSize(const std::string& sizeStr) {
    if (sizeStr == "S") return S;
    if (sizeStr == "M") return M;
    if (sizeStr == "L") return L;
    if (sizeStr == "XL") return XL;
    if (sizeStr == "XXL") return XXL;
    
    throw std::runtime_error("Unknown pizza size: " + sizeStr);
}