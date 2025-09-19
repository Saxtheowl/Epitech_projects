/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface for display modules (graphics libraries)
*/

#pragma once

#include <memory>
#include <vector>
#include <string>

namespace arcade {
    enum class Key {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE,
        ESCAPE,
        ENTER,
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        UNKNOWN
    };

    enum class Color {
        BLACK = 0,
        RED = 1,
        GREEN = 2,
        YELLOW = 3,
        BLUE = 4,
        MAGENTA = 5,
        CYAN = 6,
        WHITE = 7
    };

    struct Position {
        int x;
        int y;
        Position(int x = 0, int y = 0) : x(x), y(y) {}
    };

    struct DisplayChar {
        char character;
        Color color;
        Color background;
        Position position;

        DisplayChar(char c = ' ', Color fg = Color::WHITE, Color bg = Color::BLACK, Position pos = Position())
            : character(c), color(fg), background(bg), position(pos) {}
    };

    class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;

        virtual bool init() = 0;
        virtual void close() = 0;
        virtual void clear() = 0;
        virtual void display() = 0;
        virtual Key getKey() = 0;
        virtual bool isOpen() = 0;

        virtual void drawPixel(const DisplayChar &pixel) = 0;
        virtual void drawText(const std::string &text, Position pos, Color color = Color::WHITE) = 0;
        virtual void drawRect(Position pos, int width, int height, Color color = Color::WHITE) = 0;

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual std::string getName() const = 0;
    };
}