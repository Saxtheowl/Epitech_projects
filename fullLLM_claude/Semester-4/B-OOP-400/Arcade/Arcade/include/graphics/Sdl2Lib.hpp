/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SDL2 graphics library implementation
*/

#pragma once

#include "core/IDisplayModule.hpp"
#include <memory>

// Forward declarations to avoid including SDL headers
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
union SDL_Event;

namespace arcade {
    class Sdl2Lib : public IDisplayModule {
    public:
        Sdl2Lib();
        ~Sdl2Lib() override;

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
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        bool _initialized;
        int _width;
        int _height;
        int _cellWidth;
        int _cellHeight;

        void setDrawColor(Color color);
        Key translateKey(int key) const;
    };
}

extern "C" {
    arcade::IDisplayModule* createDisplay();
    void destroyDisplay(arcade::IDisplayModule* module);
}