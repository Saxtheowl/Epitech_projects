/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SFML graphics library implementation
*/

#pragma once

#include "core/IDisplayModule.hpp"
#include <memory>

// Forward declarations to avoid including SFML headers
namespace sf {
    class RenderWindow;
    class Event;
    class Font;
    class Text;
    class RectangleShape;
}

namespace arcade {
    class SfmlLib : public IDisplayModule {
    public:
        SfmlLib();
        ~SfmlLib() override;

        bool init() override;
        void close() override;
        void clear() override;
        void display() override;
        Key getKey() override;
        bool isOpen() override;

        void drawPixel(const DisplayChar &pixel) override;
        void drawText(const std::string &text, Position pos, Color color = Color::WHITE) override;
        void drawRect(Position pos, int width, int height, Color color = Color::WHITE) override;

        int getWidth() const override;
        int getHeight() const override;
        std::string getName() const override;

    private:
        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<sf::Font> _font;
        bool _initialized;
        int _width;
        int _height;
        int _cellWidth;
        int _cellHeight;

        sf::Color colorToSfml(Color color) const;
        Key translateKey(int key) const;
        void loadFont();
    };
}

extern "C" {
    arcade::IDisplayModule* createDisplay();
    void destroyDisplay(arcade::IDisplayModule* module);
}