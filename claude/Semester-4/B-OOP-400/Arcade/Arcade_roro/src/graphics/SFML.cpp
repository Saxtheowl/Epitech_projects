/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SFML graphics module implementation
*/

#include <SFML/Graphics.hpp>
#include <map>
#include "IDisplayModule.hpp"

namespace arcade {
    class SFMLModule : public IDisplayModule {
    private:
        sf::RenderWindow _window;
        sf::Font _font;
        bool _initialized;
        Key _lastKey;
        bool _hasEvent;
        std::map<sf::Keyboard::Key, Key> _keyMap;
        
        void initKeyMap() {
            _keyMap[sf::Keyboard::Up] = Key::UP;
            _keyMap[sf::Keyboard::Down] = Key::DOWN;
            _keyMap[sf::Keyboard::Left] = Key::LEFT;
            _keyMap[sf::Keyboard::Right] = Key::RIGHT;
            _keyMap[sf::Keyboard::Space] = Key::SPACE;
            _keyMap[sf::Keyboard::Return] = Key::ENTER;
            _keyMap[sf::Keyboard::Escape] = Key::ESCAPE;
            
            // Letters
            for (int i = 0; i < 26; ++i) {
                _keyMap[static_cast<sf::Keyboard::Key>(sf::Keyboard::A + i)] = 
                    static_cast<Key>(static_cast<int>(Key::A) + i);
            }
            
            // Numbers
            for (int i = 0; i < 10; ++i) {
                _keyMap[static_cast<sf::Keyboard::Key>(sf::Keyboard::Num0 + i)] = 
                    static_cast<Key>(static_cast<int>(Key::NUM_0) + i);
            }
            
            // Special arcade keys
            _keyMap[sf::Keyboard::Q] = Key::PREV_GRAPH;
            _keyMap[sf::Keyboard::A] = Key::NEXT_GRAPH;
            _keyMap[sf::Keyboard::Z] = Key::PREV_GAME;
            _keyMap[sf::Keyboard::E] = Key::NEXT_GAME;
            _keyMap[sf::Keyboard::R] = Key::RESTART;
            _keyMap[sf::Keyboard::M] = Key::MENU;
            _keyMap[sf::Keyboard::X] = Key::EXIT;
        }
        
        sf::Color getSFMLColor(Color color) const {
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

    public:
        SFMLModule() : _initialized(false), _lastKey(Key::UNKNOWN), _hasEvent(false) {
            initKeyMap();
        }
        
        ~SFMLModule() {
            destroy();
        }

        bool init(const std::string &windowName) override {
            if (_initialized) return true;
            
            _window.create(sf::VideoMode(800, 600), windowName);
            if (!_window.isOpen()) {
                return false;
            }
            
            // Try to load a default font
            if (!_font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf")) {
                if (!_font.loadFromFile("/System/Library/Fonts/Monaco.ttf")) {
                    if (!_font.loadFromFile("/usr/share/fonts/TTF/DejaVuSansMono.ttf")) {
                        // Use default font if none found
                    }
                }
            }
            
            _initialized = true;
            return true;
        }

        void destroy() override {
            if (_initialized && _window.isOpen()) {
                _window.close();
                _initialized = false;
            }
        }

        bool isOpen() const override {
            return _initialized && _window.isOpen();
        }

        Key getLastKey() override {
            Key key = _lastKey;
            _lastKey = Key::UNKNOWN;
            _hasEvent = false;
            return key;
        }

        bool hasEvent() const override {
            if (!_initialized) return false;
            
            const_cast<SFMLModule*>(this)->pollEvents();
            return _hasEvent;
        }
        
        void pollEvents() {
            if (!_initialized) return;
            
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _lastKey = Key::EXIT;
                    _hasEvent = true;
                    return;
                } else if (event.type == sf::Event::KeyPressed) {
                    auto it = _keyMap.find(event.key.code);
                    if (it != _keyMap.end()) {
                        _lastKey = it->second;
                        _hasEvent = true;
                    }
                }
            }
        }

        void clearEvents() override {
            _hasEvent = false;
            _lastKey = Key::UNKNOWN;
            sf::Event event;
            while (_window.pollEvent(event));
        }

        void clear() override {
            if (_initialized && _window.isOpen()) {
                _window.clear(sf::Color::Black);
            }
        }

        void display() override {
            if (_initialized && _window.isOpen()) {
                _window.display();
            }
        }

        void drawPixel(const Vector2i &pos, Color color) override {
            if (!_initialized || !_window.isOpen()) return;
            
            sf::RectangleShape pixel(sf::Vector2f(10, 20));
            pixel.setPosition(pos.x * 10, pos.y * 20);
            pixel.setFillColor(getSFMLColor(color));
            _window.draw(pixel);
        }

        void drawText(const Vector2i &pos, const std::string &text, Color color) override {
            if (!_initialized || !_window.isOpen() || text.empty()) return;
            
            sf::Text sfText;
            sfText.setFont(_font);
            sfText.setString(text);
            sfText.setCharacterSize(16);
            sfText.setFillColor(getSFMLColor(color));
            sfText.setPosition(pos.x * 10, pos.y * 20);
            
            _window.draw(sfText);
        }

        void drawRectangle(const Vector2i &pos, const Vector2i &size, Color color) override {
            if (!_initialized || !_window.isOpen()) return;
            
            sf::RectangleShape rectangle(sf::Vector2f(size.x * 10, size.y * 20));
            rectangle.setPosition(pos.x * 10, pos.y * 20);
            rectangle.setFillColor(getSFMLColor(color));
            _window.draw(rectangle);
        }

        std::string getName() const override {
            return "SFML";
        }
    };
}

// C-style factory functions
extern "C" {
    arcade::IDisplayModule *createDisplayModule() {
        return new arcade::SFMLModule();
    }

    void destroyDisplayModule(arcade::IDisplayModule *module) {
        delete module;
    }
}