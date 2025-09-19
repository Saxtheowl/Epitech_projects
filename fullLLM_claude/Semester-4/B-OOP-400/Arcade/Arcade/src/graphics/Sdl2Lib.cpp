/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SDL2 graphics library implementation (minimal for testing)
*/

#include "graphics/Sdl2Lib.hpp"
#include <iostream>

// Minimal SDL2 stubs for compilation without actual SDL2
struct SDL_Window { int dummy; };
struct SDL_Renderer { int dummy; };
union SDL_Event { int type; };

namespace arcade {
    Sdl2Lib::Sdl2Lib()
        : _window(nullptr), _renderer(nullptr), _initialized(false),
          _width(800), _height(600), _cellWidth(20), _cellHeight(20) {}

    Sdl2Lib::~Sdl2Lib() {
        if (_initialized) {
            close();
        }
    }

    bool Sdl2Lib::init() {
        if (_initialized) return true;

        std::cout << "SDL2 Library initialized (stub)" << std::endl;
        _initialized = true;
        return true;
    }

    void Sdl2Lib::close() {
        if (_initialized) {
            std::cout << "SDL2 Library closed" << std::endl;
            _initialized = false;
        }
    }

    void Sdl2Lib::clear() {
        // Stub implementation
    }

    void Sdl2Lib::display() {
        // Stub implementation
    }

    Key Sdl2Lib::getKey() {
        // Stub implementation - return no key
        return Key::UNKNOWN;
    }

    bool Sdl2Lib::isOpen() {
        return _initialized;
    }

    void Sdl2Lib::drawPixel(const DisplayChar &pixel) {
        // Stub implementation
        (void)pixel;
    }

    void Sdl2Lib::drawText(const std::string &text, Position pos, Color color) {
        // Stub implementation
        (void)text; (void)pos; (void)color;
    }

    void Sdl2Lib::drawRect(Position pos, int width, int height, Color color) {
        // Stub implementation
        (void)pos; (void)width; (void)height; (void)color;
    }

    int Sdl2Lib::getWidth() const {
        return _width / _cellWidth;
    }

    int Sdl2Lib::getHeight() const {
        return _height / _cellHeight;
    }

    std::string Sdl2Lib::getName() const {
        return "SDL2";
    }

    void Sdl2Lib::setDrawColor(Color color) {
        (void)color;
    }

    Key Sdl2Lib::translateKey(int key) const {
        (void)key;
        return Key::UNKNOWN;
    }
}

extern "C" {
    arcade::IDisplayModule* createDisplay() {
        return new arcade::Sdl2Lib();
    }

    void destroyDisplay(arcade::IDisplayModule* module) {
        delete module;
    }
}