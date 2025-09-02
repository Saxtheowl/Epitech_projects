# Arcade - Interface Documentation

## How to Implement New Libraries

This document explains how to create compatible graphics and game libraries for the Arcade platform.

## Graphics Libraries

### Interface: IDisplayModule

Your graphics library must implement the `IDisplayModule` interface:

```cpp
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
    
    virtual std::string getName() const = 0;
};
```

### Factory Functions

You must provide C-style factory functions:

```cpp
extern "C" {
    arcade::IDisplayModule *createDisplayModule();
    void destroyDisplayModule(arcade::IDisplayModule *module);
}
```

### Key Mapping

Map your library's keys to the arcade Key enum:
- Arrow keys (UP, DOWN, LEFT, RIGHT)
- Letters A-Z and numbers 0-9
- Special keys: SPACE, ENTER, ESCAPE
- Arcade controls: PREV_GRAPH, NEXT_GRAPH, PREV_GAME, NEXT_GAME, RESTART, MENU, EXIT

### Color System

Support the standard Color enum: BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE

## Game Libraries

### Interface: IGameModule

Your game must implement the `IGameModule` interface:

```cpp
class IGameModule {
public:
    virtual ~IGameModule() = default;
    
    // Game lifecycle
    virtual bool init() = 0;
    virtual void destroy() = 0;
    virtual void reset() = 0;
    
    // Game loop
    virtual void update(float deltaTime) = 0;
    virtual void handleInput(Key key) = 0;
    
    // Game data
    virtual const GameData &getGameData() const = 0;
    virtual GameState getGameState() const = 0;
    virtual bool isGameOver() const = 0;
    
    // Game info
    virtual std::string getName() const = 0;
    virtual int getScore() const = 0;
    virtual Vector2i getMapSize() const = 0;
    
    // Player
    virtual void setPlayerName(const std::string &name) = 0;
    virtual std::string getPlayerName() const = 0;
};
```

### Game Data Structure

Use the GameData structure to communicate with the graphics:

```cpp
struct GameObject {
    Vector2i position;
    char character;
    Color color;
};

struct GameData {
    std::vector<GameObject> objects;
    int score;
    int lives;
    int level;
    GameState state;
    std::string statusText;
};
```

### Factory Functions

Provide C-style factory functions:

```cpp
extern "C" {
    arcade::IGameModule *createGameModule();
    void destroyGameModule(arcade::IGameModule *module);
}
```

## Compilation Requirements

### Shared Library Flags
- Use `-shared -fPIC` for dynamic libraries
- Add `-fno-gnu-unique` for proper dlclose behavior
- Link with required libraries (e.g., `-lncurses`, `-lsfml-graphics`)

### Library Naming
- Graphics: `arcade_<name>.so` (e.g., `arcade_ncurses.so`)
- Games: `arcade_<name>.so` (e.g., `arcade_nibbler.so`)
- Place all libraries in `./lib/` directory

### Example Makefile Rules

```makefile
lib/arcade_mygame.so: src/MyGame.o
	$(CXX) -shared -fPIC -o $@ $^ $(CXXFLAGS)

lib/arcade_mygraphics.so: src/MyGraphics.o
	$(CXX) -shared -fPIC -o $@ $^ $(CXXFLAGS) -lmygraphicslib
```

## Tips for Implementation

1. **Keep it Simple**: Focus on the interface requirements
2. **Error Handling**: Return false from init() if setup fails
3. **Resource Management**: Clean up in destroy()
4. **Threading**: Libraries should be thread-safe
5. **Performance**: Update/render efficiently for smooth gameplay
6. **Testing**: Test with different games/graphics combinations

## Example Implementation Structure

```
src/
├── games/
│   └── MyGame.cpp          # Implements IGameModule
└── graphics/
    └── MyGraphics.cpp      # Implements IDisplayModule
```

This modular approach ensures compatibility with the Arcade platform while allowing creative freedom in implementation.