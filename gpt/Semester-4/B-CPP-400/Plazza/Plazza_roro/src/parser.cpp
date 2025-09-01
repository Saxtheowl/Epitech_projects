/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Order line parser
*/

#include <sstream>
#include <algorithm>
#include "plazza.hpp"

static std::string trim(const std::string &s)
{
    size_t i = 0, j = s.size();
    while (i < j && std::isspace((unsigned char)s[i])) i++;
    while (j > i && std::isspace((unsigned char)s[j-1])) j--;
    return s.substr(i, j - i);
}

static bool parse_type(const std::string &t, PizzaType &out)
{
    std::string s = t; std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (s == "regina") { out = PizzaType::Regina; return true; }
    if (s == "margarita") { out = PizzaType::Margarita; return true; }
    if (s == "americana") { out = PizzaType::Americana; return true; }
    if (s == "fantasia") { out = PizzaType::Fantasia; return true; }
    return false;
}

static bool parse_size(const std::string &t, PizzaSize &out)
{
    if (t == "S" || t == "s") { out = PizzaSize::S; return true; }
    if (t == "M" || t == "m") { out = PizzaSize::M; return true; }
    if (t == "L" || t == "l") { out = PizzaSize::L; return true; }
    if (t == "XL" || t == "xl") { out = PizzaSize::XL; return true; }
    if (t == "XXL" || t == "xxl") { out = PizzaSize::XXL; return true; }
    return false;
}

std::optional<std::vector<OrderItem>> parse_order_line(const std::string &line)
{
    std::vector<OrderItem> items;
    std::stringstream ss(line);
    std::string part;
    while (std::getline(ss, part, ';')) {
        part = trim(part);
        if (part.empty()) continue;
        std::stringstream ps(part);
        std::string a,b,c;
        if (!(ps >> a >> b >> c)) return std::nullopt;
        PizzaType pt; PizzaSize sz; int cnt = 0;
        if (!parse_type(a, pt) || !parse_size(b, sz)) return std::nullopt;
        if (c.size() < 2 || c[0] != 'x') return std::nullopt;
        cnt = std::atoi(c.c_str() + 1);
        if (cnt <= 0) return std::nullopt;
        items.push_back({pt, sz, cnt});
    }
    if (items.empty()) return std::nullopt;
    return items;
}

