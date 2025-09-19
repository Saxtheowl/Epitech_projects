/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SFML graphics library implementation
*/

#include "graphics/SfmlLib.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace arcade {
    SfmlLib::SfmlLib()
        : _initialized(false), _width(800), _height(600), _cellWidth(20), _cellHeight(20) {}

    SfmlLib::~SfmlLib() {
        if (_initialized) {
            close();
        }
    }

    bool SfmlLib::init() {
        if (_initialized) return true;

        try {
            _window = std::make_unique<sf::RenderWindow>(
                sf::VideoMode(_width, _height),
                "Arcade - SFML",
                sf::Style::Close
            );
            _window->setFramerateLimit(60);

            _font = std::make_unique<sf::Font>();
            loadFont();

            _initialized = true;
            return true;
        } catch (const std::exception &e) {
            std::cerr << "SFML initialization error: " << e.what() << std::endl;
            return false;
        }
    }

    void SfmlLib::close() {
        if (_initialized && _window) {
            _window->close();
            _window.reset();
            _font.reset();
            _initialized = false;
        }
    }

    void SfmlLib::clear() {
        if (_window) {
            _window->clear(sf::Color::Black);
        }
    }

    void SfmlLib::display() {
        if (_window) {
            _window->display();
        }
    }

    Key SfmlLib::getKey() {
        if (!_window) return Key::UNKNOWN;

        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return Key::ESCAPE;
            }
            if (event.type == sf::Event::KeyPressed) {
                return translateKey(event.key.code);
            }
        }
        return Key::UNKNOWN;
    }

    bool SfmlLib::isOpen() {
        return _initialized && _window && _window->isOpen();
    }

    void SfmlLib::drawPixel(const DisplayChar &pixel) {
        if (!_window || !_font) return;

        sf::Text text;
        text.setFont(*_font);
        text.setString(pixel.character);
        text.setCharacterSize(_cellHeight - 2);
        text.setFillColor(colorToSfml(pixel.color));
        text.setPosition(
            pixel.position.x * _cellWidth,
            pixel.position.y * _cellHeight
        );

        _window->draw(text);
    }

    void SfmlLib::drawText(const std::string &text, Position pos, Color color) {
        if (!_window || !_font) return;

        sf::Text sfText;
        sfText.setFont(*_font);
        sfText.setString(text);
        sfText.setCharacterSize(_cellHeight - 2);
        sfText.setFillColor(colorToSfml(color));
        sfText.setPosition(
            pos.x * _cellWidth,
            pos.y * _cellHeight
        );

        _window->draw(sfText);
    }

    void SfmlLib::drawRect(Position pos, int width, int height, Color color) {
        if (!_window) return;

        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(width * _cellWidth, height * _cellHeight));
        rect.setPosition(pos.x * _cellWidth, pos.y * _cellHeight);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(1);
        rect.setOutlineColor(colorToSfml(color));

        _window->draw(rect);
    }

    int SfmlLib::getWidth() const {
        return _width / _cellWidth;
    }

    int SfmlLib::getHeight() const {
        return _height / _cellHeight;
    }

    std::string SfmlLib::getName() const {
        return "SFML";
    }

    sf::Color SfmlLib::colorToSfml(Color color) const {
        switch (color) {
            case Color::BLACK: return sf::Color::Black;
            case Color::RED: return sf::Color::Red;
            case Color::GREEN: return sf::Color::Green;
            case Color::YELLOW: return sf::Color::Yellow;
            case Color::BLUE: return sf::Color::Blue;
            case Color::MAGENTA: return sf::Color::Magenta;
            case Color::CYAN: return sf::Color::Cyan;
            case Color::WHITE: return sf::Color::White;
            default: return sf::Color::White;
        }
    }

    Key SfmlLib::translateKey(int key) const {
        switch (key) {
            case sf::Keyboard::Up: return Key::UP;
            case sf::Keyboard::Down: return Key::DOWN;
            case sf::Keyboard::Left: return Key::LEFT;
            case sf::Keyboard::Right: return Key::RIGHT;
            case sf::Keyboard::Space: return Key::SPACE;
            case sf::Keyboard::Escape: return Key::ESCAPE;
            case sf::Keyboard::Enter: return Key::ENTER;
            case sf::Keyboard::A: return Key::A;
            case sf::Keyboard::B: return Key::B;
            case sf::Keyboard::C: return Key::C;
            case sf::Keyboard::D: return Key::D;
            case sf::Keyboard::E: return Key::E;
            case sf::Keyboard::F: return Key::F;
            case sf::Keyboard::G: return Key::G;
            case sf::Keyboard::H: return Key::H;
            case sf::Keyboard::I: return Key::I;
            case sf::Keyboard::J: return Key::J;
            case sf::Keyboard::K: return Key::K;
            case sf::Keyboard::L: return Key::L;
            case sf::Keyboard::M: return Key::M;
            case sf::Keyboard::N: return Key::N;
            case sf::Keyboard::O: return Key::O;
            case sf::Keyboard::P: return Key::P;
            case sf::Keyboard::Q: return Key::Q;
            case sf::Keyboard::R: return Key::R;
            case sf::Keyboard::S: return Key::S;
            case sf::Keyboard::T: return Key::T;
            case sf::Keyboard::U: return Key::U;
            case sf::Keyboard::V: return Key::V;
            case sf::Keyboard::W: return Key::W;
            case sf::Keyboard::X: return Key::X;
            case sf::Keyboard::Y: return Key::Y;
            case sf::Keyboard::Z: return Key::Z;
            default: return Key::UNKNOWN;
        }
    }

    void SfmlLib::loadFont() {
        // Try to load a default system font, fallback to built-in if needed
        if (!_font->loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf")) {
            if (!_font->loadFromFile("/System/Library/Fonts/Monaco.ttf")) {
                // Create a minimal font manually if no system font available
                std::cerr << "Warning: Could not load system font, using default" << std::endl;
            }
        }
    }
}

extern "C" {
    arcade::IDisplayModule* createDisplay() {
        return new arcade::SfmlLib();
    }

    void destroyDisplay(arcade::IDisplayModule* module) {
        delete module;
    }
}