# MyDefender - Tower Defense Game

A complete tower defense game implementation using CSFML graphics library.

## Project Overview
MyDefender is a tower defense game where players must defend their castle against waves of enemies by strategically placing buildings on a grid-based map.

## Features

### Mandatory Features
- ✅ Window event handling (close, keyboard, mouse)
- ✅ Animated sprites with frame-rate independent animations
- ✅ Clock-based timing for all movements and animations
- ✅ Starting menu with play and quit buttons
- ✅ Escape key pause functionality
- ✅ Pause menu with resume, main menu, and quit options
- ✅ 4 different building types (Wall, Basic Tower, Slow Tower, Heavy Tower)
- ✅ Building menu with prices and descriptions
- ✅ Sound effects and background music support

### Building Types
1. **Wall ($50)** - Blocks enemies, 200 HP
2. **Basic Tower ($100)** - Fast attack, medium damage (25), 3-tile range
3. **Slow Tower ($150)** - Slows enemies, lower damage (15), 4-tile range
4. **Heavy Tower ($200)** - High damage (50), shorter range (2.5 tiles)

### Enemy Types
1. **Basic Enemy** - 50 HP, medium speed, 25 gold reward
2. **Fast Enemy** - 25 HP, high speed, 30 gold reward
3. **Tank Enemy** - 150 HP, slow speed, 50 gold reward

### Game Systems
- **Wave System**: Progressive difficulty with increasing enemy counts
- **Combat System**: Real-time tower shooting with projectiles
- **Economy System**: Earn money by defeating enemies
- **Grid-based Building**: 25x20 tile playing field

## Controls
- **Mouse**: Click to place buildings, navigate menus
- **Keyboard**: 
  - `1-4`: Select building types
  - `Space`: Deselect building
  - `Escape`: Pause/resume game

## Installation

### Dependencies
Install CSFML development libraries:
```bash
# Ubuntu/Debian
sudo apt-get install libcsfml-dev

# Arch Linux
sudo pacman -S csfml

# macOS (with Homebrew)
brew install csfml
```

### Building
```bash
make
```

### Running
```bash
./my_defender
```

## Project Structure
```
MyDefender_roro/
├── src/
│   ├── main.c               # Entry point
│   ├── game.c              # Core game loop and initialization
│   ├── scenes.c            # Scene management (menu, game, pause)
│   ├── building_system.c   # Building placement and management
│   ├── enemy_system.c      # Enemy spawning and movement
│   ├── combat_system.c     # Tower combat and projectiles
│   ├── wave_system.c       # Enemy wave management
│   ├── ui_system.c         # User interface and HUD
│   ├── button_callbacks.c  # Button event handlers
│   └── utils.c             # Utility functions
├── include/
│   └── my_defender.h       # Main header file
├── assets/
│   ├── sprites/            # Game sprites
│   ├── sounds/             # Sound effects
│   └── music/              # Background music
├── Makefile
└── README.md
```

## Technical Details

### Architecture
- **Scene-based System**: Separate handling for menu, game, and pause states
- **Entity Component System**: Modular building and enemy systems
- **Event-driven UI**: Button system with hover and click states
- **Real-time Combat**: Projectile physics with collision detection

### Performance Features
- Frame-rate independent animations using SFML clocks
- Efficient linked list management for dynamic entities
- Optimized collision detection for combat systems
- Memory management with proper cleanup

### Asset Requirements
- Textures: Building sprites, enemy sprites, projectile sprites
- Audio: Background music (looping), sound effects (shooting, enemy death, damage)
- Fonts: System fonts for UI text rendering

## Game Balance
- Starting money: $500
- Castle HP: 100
- Wave progression: +2 enemies per wave
- Enemy damage to castle: 10 HP
- Wave bonus: $100 between waves

## Error Handling
- Graceful fallbacks for missing assets
- Memory allocation failure handling
- Invalid input validation
- Window close event handling

## Epitech Compliance
- No forbidden functions used
- Proper memory management
- Standard Epitech coding style
- Error code 84 for failures
- Repository size optimization (&lt;15MB)

This implementation provides a complete tower defense experience with all mandatory features and several optional enhancements for improved gameplay.