/*
** EPITECH PROJECT, 2025
** Plazza_roro
** File description:
**   Order line parser (grammar from subject)
*/

#include <cctype>
#include <cstring>
#include "plazza.hpp"

static void skip_spaces(const std::string &s, std::size_t &i)
{
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i])))
        i++;
}

static bool parse_type(const std::string &s, std::size_t &i, std::string &out)
{
    std::size_t start = i;
    while (i < s.size() && std::isalpha(static_cast<unsigned char>(s[i])))
        i++;
    if (i == start)
        return false;
    out = s.substr(start, i - start);
    return true;
}

static bool parse_size(const std::string &s, std::size_t &i, std::string &out)
{
    static const char *SIZES[] = {"S","M","L","XL","XXL"};
    for (const char *cand : SIZES) {
        std::size_t n = std::strlen(cand);
        if (i + n <= s.size() && s.compare(i, n, cand) == 0) {
            out = cand;
            i += n;
            return true;
        }
    }
    return false;
}

static bool parse_number(const std::string &s, std::size_t &i, int &count)
{
    if (i >= s.size() || s[i] != 'x')
        return false;
    i++;
    if (i >= s.size() || s[i] < '1' || s[i] > '9')
        return false;
    long v = s[i++] - '0';
    while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i]))) {
        v = v * 10 + (s[i++] - '0');
        if (v > 1000000)
            return false;
    }
    count = static_cast<int>(v);
    return true;
}

std::vector<OrderItem> parse_orders_line(const std::string &s, bool &ok)
{
    std::vector<OrderItem> items;
    std::size_t i = 0;
    ok = true;
    while (1) {
        skip_spaces(s, i);
        std::string type, size;
        int count = 0;
        if (!parse_type(s, i, type)) { ok = false; break; }
        skip_spaces(s, i);
        if (!parse_size(s, i, size)) { ok = false; break; }
        skip_spaces(s, i);
        if (!parse_number(s, i, count)) { ok = false; break; }
        items.push_back({type, size, count});
        skip_spaces(s, i);
        if (i >= s.size()) break;
        if (s[i] != ';') { ok = false; break; }
        i++;
    }
    return items;
}
