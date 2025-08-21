# MyHunter - Duck Hunt Legacy

## Description
A classic duck hunting game where you shoot ducks that fly across the screen. Built with CSFML.

## Requirements
This project requires CSFML (C Simple and Fast Multimedia Library) to be installed.

### Installing CSFML on Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install libcsfml-dev
```

### Installing CSFML on other systems:
- **Arch Linux**: `sudo pacman -S csfml`
- **Fedora**: `sudo dnf install CSFML-devel`
- **macOS**: `brew install csfml`

## Compilation
```bash
make
```

## Usage
```bash
./my_hunter           # Start the game
./my_hunter -h        # Display help
```

## Controls
- **Left Click**: Shoot at ducks
- **ESC**: Exit game
- **Close Window**: Exit game

## Gameplay
- Ducks appear from the sides and fly across the screen
- Click on them to shoot and earn points
- Try to achieve the highest score possible
- Each duck shot awards 10 points
- Every 10 ducks killed increases the level

## Project Structure
- `src/`: Source files
- `include/`: Header files
- `assets/`: Game assets (sprites, sounds)
- `tests_env/`: Test environment
- `docs/`: Documentation

## Features
- ✓ Animated duck sprites with spritesheet
- ✓ Mouse-based shooting mechanics
- ✓ Score system with persistent high scores
- ✓ Level progression
- ✓ Smooth frame-rate independent animation
- ✓ Event-driven window management
- ✓ Command-line help option

## Technical Details
- **Language**: C
- **Graphics**: CSFML
- **Window Size**: 1200x800 pixels
- **Frame Rate**: 60 FPS
- **Animation**: Delta-time based movement