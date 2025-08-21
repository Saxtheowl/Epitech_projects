# MyHunter - Game Design Document

## Overview
MyHunter is a Duck Hunt-inspired shooting game built with CSFML. Players shoot ducks that fly across the screen to earn points.

## Game Mechanics

### Core Gameplay Loop
1. **Duck Spawning**: Ducks spawn from the left or right side of the screen every 2 seconds
2. **Movement**: Ducks fly across the screen with random trajectories
3. **Shooting**: Players click on ducks to shoot them
4. **Scoring**: Each duck shot awards 10 points
5. **Progression**: Every 10 ducks killed increases the level

### Duck Behavior
- **Spawn Logic**: Ducks appear from random sides with random Y positions
- **Movement**: Horizontal movement with slight vertical variation
- **Animation**: 4-frame sprite animation for flying effect
- **Collision**: Simple distance-based collision detection (32 pixel radius)

### Game Features
- **Score System**: Current score and high score tracking
- **Level Progression**: Visual level counter increases with kills
- **Persistent High Score**: Saved to file between sessions
- **Smooth Animation**: Frame-rate independent movement using delta time
- **Mouse Crosshair**: Visual targeting cursor

## Technical Implementation

### Architecture
- **Modular Design**: Separated into logical modules (init, loop, duck management, utilities)
- **Game State**: Centralized game_t structure containing all game data
- **Event Handling**: Proper SFML event processing for window and mouse events
- **Memory Management**: Proper resource cleanup on exit

### Performance
- **60 FPS Limit**: Prevents excessive CPU usage
- **Delta Time**: Ensures consistent movement regardless of frame rate
- **Efficient Collision**: Simple distance calculations for hit detection
- **Sprite Batching**: Minimal draw calls per frame

### Controls
- **Mouse**: Left click to shoot
- **Keyboard**: ESC to exit
- **Window**: Close button to exit
- **Command Line**: -h flag for help

## Assets Requirements
- **Duck Sprite Sheet**: 4 frames of duck animation (64x64 each)
- **Background Texture**: Sky/field background
- **Crosshair Sprite**: Small targeting reticle (32x32)
- **Font**: For score display (can use system default)

## Future Enhancements
- Sound effects for shooting and duck calls
- Multiple duck types with different point values
- Power-ups and special weapons
- Multiple levels with different backgrounds
- Particle effects for hits and misses