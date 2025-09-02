/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCurses graphics module implementation
*/

#include <ncurses.h>
#include <string>
#include <map>
#include "IDisplayModule.hpp"

namespace arcade {
    class NCursesModule : public IDisplayModule {
    private:
        bool _initialized;
        Key _lastKey;
        bool _hasEvent;
        std::map<int, Key> _keyMap;
        
        void initKeyMap() {
            _keyMap[KEY_UP] = Key::UP;
            _keyMap[KEY_DOWN] = Key::DOWN;
            _keyMap[KEY_LEFT] = Key::LEFT;
            _keyMap[KEY_RIGHT] = Key::RIGHT;
            _keyMap[' '] = Key::SPACE;
            _keyMap['\n'] = Key::ENTER;
            _keyMap[KEY_ENTER] = Key::ENTER;
            _keyMap[27] = Key::ESCAPE; // ESC
            
            // Letters
            for (int i = 0; i < 26; ++i) {
                _keyMap['a' + i] = static_cast<Key>(static_cast<int>(Key::A) + i);
                _keyMap['A' + i] = static_cast<Key>(static_cast<int>(Key::A) + i);
            }
            
            // Numbers
            for (int i = 0; i < 10; ++i) {
                _keyMap['0' + i] = static_cast<Key>(static_cast<int>(Key::NUM_0) + i);
            }
            
            // Special arcade keys
            _keyMap['q'] = Key::PREV_GRAPH;
            _keyMap['a'] = Key::NEXT_GRAPH;
            _keyMap['z'] = Key::PREV_GAME;
            _keyMap['e'] = Key::NEXT_GAME;
            _keyMap['r'] = Key::RESTART;
            _keyMap['m'] = Key::MENU;
            _keyMap['x'] = Key::EXIT;
        }

    public:
        NCursesModule() : _initialized(false), _lastKey(Key::UNKNOWN), _hasEvent(false) {
            initKeyMap();
        }
        
        ~NCursesModule() {
            destroy();
        }

        bool init(const std::string &windowName) override {
            (void)windowName; // Unused parameter
            if (_initialized) return true;
            
            initscr();
            cbreak();
            noecho();
            keypad(stdscr, TRUE);
            nodelay(stdscr, TRUE);
            curs_set(0);
            
            if (has_colors()) {
                start_color();
                init_pair(1, COLOR_BLACK, COLOR_BLACK);
                init_pair(2, COLOR_RED, COLOR_BLACK);
                init_pair(3, COLOR_GREEN, COLOR_BLACK);
                init_pair(4, COLOR_YELLOW, COLOR_BLACK);
                init_pair(5, COLOR_BLUE, COLOR_BLACK);
                init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
                init_pair(7, COLOR_CYAN, COLOR_BLACK);
                init_pair(8, COLOR_WHITE, COLOR_BLACK);
            }
            
            _initialized = true;
            return true;
        }

        void destroy() override {
            if (_initialized) {
                endwin();
                _initialized = false;
            }
        }

        bool isOpen() const override {
            return _initialized;
        }

        Key getLastKey() override {
            Key key = _lastKey;
            _lastKey = Key::UNKNOWN;
            _hasEvent = false;
            return key;
        }

        bool hasEvent() const override {
            if (!_initialized) return false;
            
            const_cast<NCursesModule*>(this)->pollEvents();
            return _hasEvent;
        }
        
        void pollEvents() {
            if (!_initialized) return;
            
            int ch = getch();
            if (ch != ERR) {
                auto it = _keyMap.find(ch);
                if (it != _keyMap.end()) {
                    _lastKey = it->second;
                    _hasEvent = true;
                } else {
                    _lastKey = Key::UNKNOWN;
                    _hasEvent = true;
                }
            }
        }

        void clearEvents() override {
            _hasEvent = false;
            _lastKey = Key::UNKNOWN;
            while (getch() != ERR); // Clear input buffer
        }

        void clear() override {
            if (_initialized) {
                erase();
            }
        }

        void display() override {
            if (_initialized) {
                refresh();
            }
        }

        void drawPixel(const Vector2i &pos, Color color) override {
            if (!_initialized) return;
            
            attron(COLOR_PAIR(static_cast<int>(color) + 1));
            mvaddch(pos.y, pos.x, ' ');
            attroff(COLOR_PAIR(static_cast<int>(color) + 1));
        }

        void drawText(const Vector2i &pos, const std::string &text, Color color) override {
            if (!_initialized) return;
            
            attron(COLOR_PAIR(static_cast<int>(color) + 1));
            mvprintw(pos.y, pos.x, "%s", text.c_str());
            attroff(COLOR_PAIR(static_cast<int>(color) + 1));
        }

        void drawRectangle(const Vector2i &pos, const Vector2i &size, Color color) override {
            if (!_initialized) return;
            
            attron(COLOR_PAIR(static_cast<int>(color) + 1));
            for (int y = 0; y < size.y; ++y) {
                for (int x = 0; x < size.x; ++x) {
                    mvaddch(pos.y + y, pos.x + x, ' ');
                }
            }
            attroff(COLOR_PAIR(static_cast<int>(color) + 1));
        }

        std::string getName() const override {
            return "NCurses";
        }
    };
}

// C-style factory functions
extern "C" {
    arcade::IDisplayModule *createDisplayModule() {
        return new arcade::NCursesModule();
    }

    void destroyDisplayModule(arcade::IDisplayModule *module) {
        delete module;
    }
}