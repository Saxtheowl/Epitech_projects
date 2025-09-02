/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SDL2 graphics module implementation
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include "IDisplayModule.hpp"

namespace arcade {
    class SDL2Module : public IDisplayModule {
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        TTF_Font *_font;
        bool _initialized;
        Key _lastKey;
        bool _hasEvent;
        std::map<SDL_Keycode, Key> _keyMap;
        
        void initKeyMap() {
            _keyMap[SDLK_UP] = Key::UP;
            _keyMap[SDLK_DOWN] = Key::DOWN;
            _keyMap[SDLK_LEFT] = Key::LEFT;
            _keyMap[SDLK_RIGHT] = Key::RIGHT;
            _keyMap[SDLK_SPACE] = Key::SPACE;
            _keyMap[SDLK_RETURN] = Key::ENTER;
            _keyMap[SDLK_ESCAPE] = Key::ESCAPE;
            
            // Letters
            for (int i = 0; i < 26; ++i) {
                _keyMap[SDLK_a + i] = static_cast<Key>(static_cast<int>(Key::A) + i);
            }
            
            // Numbers
            for (int i = 0; i < 10; ++i) {
                _keyMap[SDLK_0 + i] = static_cast<Key>(static_cast<int>(Key::NUM_0) + i);
            }
            
            // Special arcade keys
            _keyMap[SDLK_q] = Key::PREV_GRAPH;
            _keyMap[SDLK_a] = Key::NEXT_GRAPH;
            _keyMap[SDLK_z] = Key::PREV_GAME;
            _keyMap[SDLK_e] = Key::NEXT_GAME;
            _keyMap[SDLK_r] = Key::RESTART;
            _keyMap[SDLK_m] = Key::MENU;
            _keyMap[SDLK_x] = Key::EXIT;
        }
        
        SDL_Color getSDLColor(Color color) const {
            switch (color) {
                case Color::BLACK: return {0, 0, 0, 255};
                case Color::RED: return {255, 0, 0, 255};
                case Color::GREEN: return {0, 255, 0, 255};
                case Color::YELLOW: return {255, 255, 0, 255};
                case Color::BLUE: return {0, 0, 255, 255};
                case Color::MAGENTA: return {255, 0, 255, 255};
                case Color::CYAN: return {0, 255, 255, 255};
                case Color::WHITE: return {255, 255, 255, 255};
                default: return {255, 255, 255, 255};
            }
        }

    public:
        SDL2Module() : _window(nullptr), _renderer(nullptr), _font(nullptr),
                      _initialized(false), _lastKey(Key::UNKNOWN), _hasEvent(false) {
            initKeyMap();
        }
        
        ~SDL2Module() {
            destroy();
        }

        bool init(const std::string &windowName) override {
            if (_initialized) return true;
            
            if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                return false;
            }
            
            if (TTF_Init() < 0) {
                SDL_Quit();
                return false;
            }
            
            _window = SDL_CreateWindow(windowName.c_str(),
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     800, 600,
                                     SDL_WINDOW_SHOWN);
            
            if (!_window) {
                TTF_Quit();
                SDL_Quit();
                return false;
            }
            
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
            if (!_renderer) {
                SDL_DestroyWindow(_window);
                TTF_Quit();
                SDL_Quit();
                return false;
            }
            
            _font = TTF_OpenFont("/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf", 16);
            if (!_font) {
                _font = TTF_OpenFont("/System/Library/Fonts/Monaco.ttf", 16);
            }
            if (!_font) {
                _font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSansMono.ttf", 16);
            }
            
            _initialized = true;
            return true;
        }

        void destroy() override {
            if (_font) {
                TTF_CloseFont(_font);
                _font = nullptr;
            }
            if (_renderer) {
                SDL_DestroyRenderer(_renderer);
                _renderer = nullptr;
            }
            if (_window) {
                SDL_DestroyWindow(_window);
                _window = nullptr;
            }
            if (_initialized) {
                TTF_Quit();
                SDL_Quit();
                _initialized = false;
            }
        }

        bool isOpen() const override {
            return _initialized && _window;
        }

        Key getLastKey() override {
            Key key = _lastKey;
            _lastKey = Key::UNKNOWN;
            _hasEvent = false;
            return key;
        }

        bool hasEvent() const override {
            if (!_initialized) return false;
            
            const_cast<SDL2Module*>(this)->pollEvents();
            return _hasEvent;
        }
        
        void pollEvents() {
            if (!_initialized) return;
            
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    _lastKey = Key::EXIT;
                    _hasEvent = true;
                    return;
                } else if (event.type == SDL_KEYDOWN) {
                    auto it = _keyMap.find(event.key.keysym.sym);
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
            SDL_Event event;
            while (SDL_PollEvent(&event));
        }

        void clear() override {
            if (_initialized && _renderer) {
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
                SDL_RenderClear(_renderer);
            }
        }

        void display() override {
            if (_initialized && _renderer) {
                SDL_RenderPresent(_renderer);
            }
        }

        void drawPixel(const Vector2i &pos, Color color) override {
            if (!_initialized || !_renderer) return;
            
            SDL_Color sdlColor = getSDLColor(color);
            SDL_SetRenderDrawColor(_renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
            SDL_RenderDrawPoint(_renderer, pos.x * 10, pos.y * 20);
        }

        void drawText(const Vector2i &pos, const std::string &text, Color color) override {
            if (!_initialized || !_renderer || !_font || text.empty()) return;
            
            SDL_Color sdlColor = getSDLColor(color);
            SDL_Surface *textSurface = TTF_RenderText_Solid(_font, text.c_str(), sdlColor);
            if (!textSurface) return;
            
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
            SDL_FreeSurface(textSurface);
            if (!textTexture) return;
            
            int textWidth, textHeight;
            SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
            
            SDL_Rect dstRect = {pos.x * 10, pos.y * 20, textWidth, textHeight};
            SDL_RenderCopy(_renderer, textTexture, nullptr, &dstRect);
            
            SDL_DestroyTexture(textTexture);
        }

        void drawRectangle(const Vector2i &pos, const Vector2i &size, Color color) override {
            if (!_initialized || !_renderer) return;
            
            SDL_Color sdlColor = getSDLColor(color);
            SDL_SetRenderDrawColor(_renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
            
            SDL_Rect rect = {pos.x * 10, pos.y * 20, size.x * 10, size.y * 20};
            SDL_RenderFillRect(_renderer, &rect);
        }

        std::string getName() const override {
            return "SDL2";
        }
    };
}

// C-style factory functions
extern "C" {
    arcade::IDisplayModule *createDisplayModule() {
        return new arcade::SDL2Module();
    }

    void destroyDisplayModule(arcade::IDisplayModule *module) {
        delete module;
    }
}