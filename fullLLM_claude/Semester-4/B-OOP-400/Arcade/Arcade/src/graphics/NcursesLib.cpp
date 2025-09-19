/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCurses graphics library implementation
*/

#include "graphics/NcursesLib.hpp"
#include <iostream>

namespace arcade {
    NcursesLib::NcursesLib() : _initialized(false), _width(80), _height(24) {}

    NcursesLib::~NcursesLib() {
        if (_initialized) {
            close();
        }
    }

    bool NcursesLib::init() {
        if (_initialized) return true;

        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);

        if (has_colors()) {
            start_color();
            initColors();
        }

        getmaxyx(stdscr, _height, _width);
        _initialized = true;
        return true;
    }

    void NcursesLib::close() {
        if (_initialized) {
            endwin();
            _initialized = false;
        }
    }

    void NcursesLib::clear() {
        if (_initialized) {
            ::clear();
        }
    }

    void NcursesLib::display() {
        if (_initialized) {
            refresh();
        }
    }

    Key NcursesLib::getKey() {
        if (!_initialized) return Key::UNKNOWN;

        int ch = getch();
        return translateKey(ch);
    }

    bool NcursesLib::isOpen() {
        return _initialized;
    }

    void NcursesLib::drawPixel(const DisplayChar &pixel) {
        if (!_initialized) return;

        if (pixel.position.x >= 0 && pixel.position.x < _width &&
            pixel.position.y >= 0 && pixel.position.y < _height) {

            if (has_colors()) {
                int colorPair = colorToNcurses(pixel.color) + 1;
                attron(COLOR_PAIR(colorPair));
            }

            mvaddch(pixel.position.y, pixel.position.x, pixel.character);

            if (has_colors()) {
                int colorPair = colorToNcurses(pixel.color) + 1;
                attroff(COLOR_PAIR(colorPair));
            }
        }
    }

    void NcursesLib::drawText(const std::string &text, Position pos, Color color) {
        if (!_initialized) return;

        if (pos.y >= 0 && pos.y < _height) {
            if (has_colors()) {
                int colorPair = colorToNcurses(color) + 1;
                attron(COLOR_PAIR(colorPair));
            }

            mvprintw(pos.y, pos.x, "%s", text.c_str());

            if (has_colors()) {
                int colorPair = colorToNcurses(color) + 1;
                attroff(COLOR_PAIR(colorPair));
            }
        }
    }

    void NcursesLib::drawRect(Position pos, int width, int height, Color color) {
        if (!_initialized) return;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                DisplayChar pixel;
                pixel.position = Position(pos.x + x, pos.y + y);
                pixel.character = (y == 0 || y == height - 1 || x == 0 || x == width - 1) ? '#' : ' ';
                pixel.color = color;
                drawPixel(pixel);
            }
        }
    }

    int NcursesLib::getWidth() const {
        return _width;
    }

    int NcursesLib::getHeight() const {
        return _height;
    }

    std::string NcursesLib::getName() const {
        return "NCurses";
    }

    void NcursesLib::initColors() {
        init_pair(1, COLOR_BLACK, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_CYAN, COLOR_BLACK);
        init_pair(8, COLOR_WHITE, COLOR_BLACK);
    }

    int NcursesLib::colorToNcurses(Color color) const {
        switch (color) {
            case Color::BLACK: return 0;
            case Color::RED: return 1;
            case Color::GREEN: return 2;
            case Color::YELLOW: return 3;
            case Color::BLUE: return 4;
            case Color::MAGENTA: return 5;
            case Color::CYAN: return 6;
            case Color::WHITE: return 7;
            default: return 7;
        }
    }

    Key NcursesLib::translateKey(int ch) const {
        switch (ch) {
            case ERR: return Key::UNKNOWN;
            case KEY_UP: return Key::UP;
            case KEY_DOWN: return Key::DOWN;
            case KEY_LEFT: return Key::LEFT;
            case KEY_RIGHT: return Key::RIGHT;
            case ' ': return Key::SPACE;
            case 27: return Key::ESCAPE;
            case '\n': case '\r': return Key::ENTER;
            case 'a': case 'A': return Key::A;
            case 'b': case 'B': return Key::B;
            case 'c': case 'C': return Key::C;
            case 'd': case 'D': return Key::D;
            case 'e': case 'E': return Key::E;
            case 'f': case 'F': return Key::F;
            case 'g': case 'G': return Key::G;
            case 'h': case 'H': return Key::H;
            case 'i': case 'I': return Key::I;
            case 'j': case 'J': return Key::J;
            case 'k': case 'K': return Key::K;
            case 'l': case 'L': return Key::L;
            case 'm': case 'M': return Key::M;
            case 'n': case 'N': return Key::N;
            case 'o': case 'O': return Key::O;
            case 'p': case 'P': return Key::P;
            case 'q': case 'Q': return Key::Q;
            case 'r': case 'R': return Key::R;
            case 's': case 'S': return Key::S;
            case 't': case 'T': return Key::T;
            case 'u': case 'U': return Key::U;
            case 'v': case 'V': return Key::V;
            case 'w': case 'W': return Key::W;
            case 'x': case 'X': return Key::X;
            case 'y': case 'Y': return Key::Y;
            case 'z': case 'Z': return Key::Z;
            default: return Key::UNKNOWN;
        }
    }
}

extern "C" {
    arcade::IDisplayModule* createDisplay() {
        return new arcade::NcursesLib();
    }

    void destroyDisplay(arcade::IDisplayModule* module) {
        delete module;
    }
}