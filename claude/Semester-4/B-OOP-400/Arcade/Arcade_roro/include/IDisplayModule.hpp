/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Interface for display/graphics modules
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <vector>
#include <string>

namespace arcade {
    enum class Key {
        UNKNOWN = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE,
        ENTER,
        ESCAPE,
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
        PREV_GRAPH,    // Previous graphics library
        NEXT_GRAPH,    // Next graphics library  
        PREV_GAME,     // Previous game
        NEXT_GAME,     // Next game
        RESTART,       // Restart game
        MENU,          // Go to menu
        EXIT           // Exit program
    };

    enum class Color {
        BLACK = 0,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    struct Vector2f {
        float x;
        float y;
        Vector2f(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
    };

    struct Vector2i {
        int x;
        int y;
        Vector2i(int x = 0, int y = 0) : x(x), y(y) {}
        
        bool operator==(const Vector2i &other) const {
            return x == other.x && y == other.y;
        }
        
        bool operator!=(const Vector2i &other) const {
            return !(*this == other);
        }
    };

    class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;

        // Window management
        virtual bool init(const std::string &windowName = "Arcade") = 0;
        virtual void destroy() = 0;
        virtual bool isOpen() const = 0;

        // Events
        virtual Key getLastKey() = 0;
        virtual bool hasEvent() const = 0;
        virtual void clearEvents() = 0;

        // Drawing
        virtual void clear() = 0;
        virtual void display() = 0;
        
        // Primitives
        virtual void drawPixel(const Vector2i &pos, Color color) = 0;
        virtual void drawText(const Vector2i &pos, const std::string &text, Color color) = 0;
        virtual void drawRectangle(const Vector2i &pos, const Vector2i &size, Color color) = 0;

        // Module info
        virtual std::string getName() const = 0;
    };
}

// C-style factory functions for dynamic loading
extern "C" {
    arcade::IDisplayModule *createDisplayModule();
    void destroyDisplayModule(arcade::IDisplayModule *module);
}

#endif /* !IDISPLAYMODULE_HPP_ */