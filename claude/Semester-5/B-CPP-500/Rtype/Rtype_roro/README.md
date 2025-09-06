# R-Type Advanced

A multiplayer implementation of the classic R-Type game using a custom game engine with Entity-Component-System (ECS) architecture.

## Features

- **Custom Game Engine**: Built from scratch with ECS architecture
- **Multiplayer Support**: UDP-based networking with client-server architecture
- **Cross-Platform**: Works on Windows and Linux
- **Real-time Gameplay**: 60 FPS gameplay with network synchronization
- **Modular Design**: Separate engine, server, and client components

## Requirements

### Build Requirements
- CMake 3.16 or higher
- C++17 compatible compiler (GCC, Clang, MSVC)
- SFML 2.5+ (for client)

### Runtime Requirements
- Operating System: Windows 10+ or Linux (Ubuntu 18.04+)
- Network: UDP connectivity for multiplayer

## Building

### Linux
```bash
mkdir build
cd build
cmake ..
make
```

### Windows (Visual Studio)
```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

## Usage

### Starting the Server
```bash
./r-type_server [port]
```
Default port is 4242.

### Starting the Client
```bash
./r-type_client [server_ip] [port] [player_name]
```
- Default server IP: 127.0.0.1
- Default port: 4242  
- Default player name: Player

### Controls
- **Arrow Keys**: Move player ship
- **Space**: Shoot bullets
- **ESC**: Quit game

## Architecture

### Engine Components
- **ECS System**: Entity-Component-System for game object management
- **Rendering System**: SFML-based graphics rendering
- **Physics System**: Basic collision detection and movement
- **Network System**: UDP-based client-server communication

### Network Protocol
- **Binary Protocol**: Optimized UDP packet format
- **Message Types**: Connect, player movement, shooting, game state sync
- **Server Authority**: Server validates all game state changes

### Project Structure
```
Rtype_roro/
├── include/           # Header files
├── src/
│   ├── engine/        # Game engine implementation
│   ├── server/        # Server implementation  
│   ├── client/        # Client implementation
│   └── common/        # Shared utilities
├── tests/             # Unit tests
├── assets/            # Game assets
└── CMakeLists.txt     # Build configuration
```

## Game Features

### Implemented
- Player movement and shooting
- Enemy spawning and AI
- Collision detection
- Basic multiplayer synchronization
- Health system

### Planned Extensions
- Power-ups and weapon upgrades
- Multiple enemy types and bosses
- Level progression system
- Enhanced graphics and sound
- Lag compensation techniques

## Testing

Run unit tests:
```bash
make test
# or
./rtype_tests
```

## Documentation

- **Network Protocol**: See `docs/protocol.md` for packet format details
- **ECS Architecture**: See `docs/architecture.md` for system design
- **API Reference**: Generated with Doxygen (run `make docs`)

## Contributing

1. Follow Epitech coding standards
2. Add unit tests for new features
3. Update documentation for API changes
4. Ensure cross-platform compatibility

## License

This project is part of the Epitech curriculum.

## Authors

- Claude AI (Implementation)
- Epitech (Project specifications)