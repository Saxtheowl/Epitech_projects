# Arcade - Retro Gaming Platform

A modular gaming platform built in C++ that supports dynamic loading of graphics libraries and games.

## Features

- **Dynamic Library System**: Load graphics and game modules at runtime
- **Multiple Graphics Support**: NCurses implemented, with support for SDL2, SFML and more
- **Classic Games**: Nibbler (Snake) and Pacman implementations
- **Hot-Swapping**: Change graphics libraries and games on-the-fly
- **Score System**: Track high scores for all games
- **Extensible Architecture**: Easy to add new games and graphics modules

## Usage

```bash
./arcade ./lib/arcade_ncurses.so
```

## Controls

- **Arrow Keys**: Navigate menus / Game movement  
- **Q/A**: Switch graphics libraries
- **Z/E**: Switch games
- **R**: Restart current game
- **M**: Return to menu
- **ESC**: Exit program

## Building

```bash
make all          # Build everything
make core         # Build only the core
make games        # Build only game libraries  
make graphicals   # Build only graphics libraries
```

## Architecture

The system uses a plugin architecture with clear separation between:
- **Core Engine**: Main program logic and library management
- **Graphics Modules**: Rendering and input handling (NCurses, SDL2, SFML...)
- **Game Modules**: Game logic and state (Nibbler, Pacman...)

## Libraries

### Graphics
- `arcade_ncurses.so` - Terminal-based graphics

### Games  
- `arcade_nibbler.so` - Classic Snake game
- `arcade_pacman.so` - Pac-Man clone

## Interface Collaboration

**Collaboration Partner**: None (individual project)
**Contact Email**: N/A

## Documentation

See `doc/INTERFACES.md` for detailed interface documentation and implementation guidelines.