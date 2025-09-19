/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCurses graphics library implementation
*/

#pragma once

#include "core/IDisplayModule.hpp"
#include <ncurses.h>

namespace arcade {
    class NcursesLib : public IDisplayModule {
    public:
        NcursesLib();
        ~NcursesLib() override;

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
        bool _initialized;
        int _width;
        int _height;

        void initColors();
        int colorToNcurses(Color color) const;
        Key translateKey(int ch) const;
    };
}

extern "C" {
    arcade::IDisplayModule* createDisplay();
    void destroyDisplay(arcade::IDisplayModule* module);
}