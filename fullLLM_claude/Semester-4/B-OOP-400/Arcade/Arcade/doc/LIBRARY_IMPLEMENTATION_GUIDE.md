# Arcade Library Implementation Guide

## Overview

This document explains how to implement new graphics libraries and game libraries compatible with the Arcade system.

## Graphics Library Implementation

### Interface

All graphics libraries must implement the `IDisplayModule` interface defined in `include/core/IDisplayModule.hpp`.

### Required Methods

```cpp
class MyGraphicsLib : public arcade::IDisplayModule {
public:
    bool init() override;                    // Initialize the graphics system
    void close() override;                   // Clean shutdown
    void clear() override;                   // Clear screen
    void display() override;                 // Present rendered frame
    Key getKey() override;                   // Get user input
    bool isOpen() override;                  // Check if window is open

    void drawPixel(const DisplayChar &pixel) override;    // Draw single character
    void drawText(const std::string &text, Position pos, Color color) override;
    void drawRect(Position pos, int width, int height, Color color) override;

    int getWidth() const override;
    int getHeight() const override;
    std::string getName() const override;
};
```

### Export Functions

```cpp
extern "C" {
    arcade::IDisplayModule* createDisplay();
    void destroyDisplay(arcade::IDisplayModule* module);
}
```

### Compilation

- Compile with `-fPIC` flag for shared library
- Link with appropriate graphics library (e.g., `-lncurses`, `-lSDL2`)
- Output to `./lib/arcade_[name].so`

### Key Mapping

Map platform-specific keys to the `arcade::Key` enum:
- Arrow keys, Space, Escape, Enter
- Letters A-Z

## Game Library Implementation

### Interface

All games must implement the `IGameModule` interface defined in `include/core/IGameModule.hpp`.

### Required Methods

```cpp
class MyGame : public arcade::IGameModule {
public:
    bool init() override;                    // Initialize game
    void update(float deltaTime) override;   // Update game logic
    void handleInput(Key key) override;      // Process input
    void render(IDisplayModule &display) override;  // Render to display
    void reset() override;                   // Reset game state

    GameInfo getGameInfo() const override;
    GameState getGameState() const override;
    std::string getName() const override;
    bool isGameOver() const override;
    int getScore() const override;
};
```

### Export Functions

```cpp
extern "C" {
    arcade::IGameModule* createGame();
    void destroyGame(arcade::IGameModule* module);
}
```

### Game Rules

#### For Snake-like Games
- Finite game area with boundaries
- Automatic movement with direction control
- Growth mechanism on food consumption
- Collision detection (walls and self)

#### For Maze Games
- Fixed maze layout with collectibles
- Character movement in 4 directions
- Win condition when all items collected
- Enemy AI with collision detection

### Rendering Guidelines

- Use only the provided `IDisplayModule` interface
- Do not include platform-specific graphics code
- Render using `drawPixel()`, `drawText()`, and `drawRect()`
- Support different display resolutions
- Use the predefined `Color` enum

### Compilation

- Compile with `-fPIC` flag for shared library
- No external graphics dependencies allowed
- Output to `./lib/arcade_[name].so`

## Build System Integration

### Makefile Rules

Add your library to the appropriate Makefile variables:

```makefile
# For graphics libraries
GRAPHICS_LIBS += lib/arcade_mylib.so

# For game libraries
GAME_LIBS += lib/arcade_mygame.so

# Add compilation rule
lib/arcade_mylib.so: src/graphics/MyLib.o
    $(CXX) -shared -fPIC -o $@ $< -lmylib
```

## Testing

1. Place compiled `.so` file in `./lib/` directory
2. Start Arcade with any graphics library
3. Your library should appear in the menu
4. Test switching between libraries at runtime
5. Verify all interface methods work correctly

## Common Pitfalls

- **Memory Management:** Always clean up resources in destructors
- **Thread Safety:** Libraries are not required to be thread-safe
- **Error Handling:** Return false from init() on failure
- **Namespace:** Always use the `arcade` namespace
- **Linking:** Avoid static linking of graphics libraries in game modules

## Examples

See existing implementations:
- Graphics: `src/graphics/NcursesLib.cpp`
- Games: `src/games/NibblerGame.cpp`