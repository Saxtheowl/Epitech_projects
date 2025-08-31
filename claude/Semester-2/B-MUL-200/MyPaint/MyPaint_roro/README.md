# MyPaint - Picture Editor

A complete paint application with graphical user interface built using CSFML.

## Project Overview
MyPaint is a picture editor that provides drawing tools, layer management, and file operations in a user-friendly GUI environment.

## Features

### Mandatory Features (MUST)
- ✅ **Window Management**: Minimize, maximize, resize, and close functionality
- ✅ **Drawing Tools**: Pencil and eraser with customizable settings
- ✅ **Button States**: Hover, pressed, and clicked visual feedback
- ✅ **Menu Bar**: File, Edit, and Help dropdown menus
  - **File Menu**: New, Open, Save, Save As
  - **Edit Menu**: Tool selection, Copy, Cut, Paste
  - **Help Menu**: About (displays login: roro), Help instructions
- ✅ **Tool Settings Panel**: Side menu for tool customization
  - **Pencil**: Line thickness adjustment
  - **Eraser**: Shape (circle/square) and size selection
- ✅ **Mouse Drawing**: Click and drag to draw with selected tools
- ✅ **Image Saving**: Default JPG format with file dialog

### Additional Features (SHOULD)
- ✅ **Layer Management**: Multiple drawing layers with opacity control
- ✅ **Color Palette**: 16-color palette for pencil tool
- ✅ **Multiple Formats**: Save as JPG, PNG, BMP
- ✅ **Basic Shapes**: Rectangle and circle drawing tools
- ✅ **Selection Tool**: Rectangle-based area selection
- ✅ **Edit Operations**: Copy/Cut/Paste on selected areas
- ✅ **File Dialog**: Interactive filename input

## Tools Available

### 1. Pencil Tool
- **Function**: Free-hand drawing
- **Settings**: Adjustable line thickness (1-20 pixels)
- **Color**: Selectable from color palette
- **Usage**: Click and drag to draw continuous lines

### 2. Eraser Tool  
- **Function**: Remove drawn content
- **Settings**: 
  - Shape: Circle or Square
  - Size: Adjustable (5-50 pixels)
- **Usage**: Click and drag to erase areas

### 3. Rectangle Tool
- **Function**: Draw geometric rectangles
- **Settings**: Line thickness, fill/outline mode
- **Usage**: Click and drag to define rectangle bounds

### 4. Circle Tool
- **Function**: Draw geometric circles
- **Settings**: Line thickness, fill/outline mode  
- **Usage**: Click and drag from center to define radius

### 5. Selection Tool
- **Function**: Select rectangular areas for copy/cut/paste
- **Usage**: Click and drag to define selection area
- **Operations**: Use Edit menu for copy/cut/paste

## User Interface

### Menu Bar
- **File**: New file, Open image, Save, Save As
- **Edit**: Tool selection, clipboard operations
- **Help**: Usage instructions and about dialog

### Toolbar (Left Panel)
- Tool selection buttons with visual feedback
- Currently selected tool highlighted
- Tool-specific settings panel below

### Color Palette (Right Panel) 
- 16 predefined colors in 4x4 grid
- Click to select drawing color
- Current color applied to pencil tool

### Canvas Area
- 800x600 pixel drawing surface
- Grid guidelines for precise drawing
- Layer composition display

### Status Bar
- Current layer information
- Active tool display
- Zoom level indicator

## Controls
- **Mouse**: Primary interaction for drawing and UI
- **Left Click**: Draw, select tools, activate buttons
- **Click + Drag**: Continuous drawing, selection areas
- **Escape**: Cancel selection, close dialogs
- **Enter**: Confirm dialog inputs

## File Operations

### Supported Formats
- **JPG**: Default format, lossy compression
- **PNG**: Lossless with transparency support  
- **BMP**: Uncompressed bitmap format

### File Management
- **New**: Clear canvas and reset layers
- **Open**: Load existing image files
- **Save**: Quick save to current filename
- **Save As**: Choose new filename and location

## Layer System
- **Multiple Layers**: Up to 10 drawing layers
- **Layer Visibility**: Show/hide individual layers
- **Opacity Control**: Adjust layer transparency
- **Layer Merging**: Combine layers for export
- **Current Layer**: Active layer for drawing operations

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
./my_paint
```

## Project Structure
```
MyPaint_roro/
├── src/
│   ├── main.c              # Entry point
│   ├── core.c              # Application initialization and main loop
│   ├── canvas.c            # Canvas management and coordinate system
│   ├── layers.c            # Layer system implementation
│   ├── tools.c             # Drawing tools (pencil, eraser, shapes)
│   ├── drawing.c           # Low-level drawing functions
│   ├── ui.c                # User interface rendering
│   ├── buttons.c           # Button creation and interaction
│   ├── menu.c              # Menu system and dropdowns
│   ├── file_operations.c   # File loading and saving
│   ├── edit_operations.c   # Edit menu functions
│   ├── dialogs.c           # Dialog windows (file, help, about)
│   └── utils.c             # Utility functions and asset loading
├── include/
│   └── my_paint.h          # Main header file
├── assets/
│   ├── icons/              # Tool icons
│   └── textures/           # UI textures
├── saves/                  # Default save directory
├── Makefile
└── README.md
```

## Technical Architecture

### Core Systems
- **Event-Driven**: SFML event handling for user input
- **State Management**: Tool states, layer states, dialog states
- **Rendering Pipeline**: Layered rendering with transparency
- **Memory Management**: Dynamic allocation with proper cleanup

### Drawing System
- **Pixel-Level Operations**: Direct pixel manipulation for precise drawing
- **Anti-Aliasing**: Smooth line rendering using Bresenham's algorithm
- **Layer Composition**: Alpha blending for transparent layers
- **Real-Time Rendering**: 60 FPS smooth drawing experience

### UI Framework
- **Component-Based**: Modular UI elements (buttons, menus, dialogs)
- **State Feedback**: Visual feedback for all interactive elements
- **Responsive Layout**: Adaptive to window resizing
- **Dialog System**: Modal dialogs for file operations and help

## Error Handling
- Graceful degradation when assets fail to load
- Input validation for file operations
- Memory allocation failure recovery
- Invalid tool state handling

## Performance Features
- Efficient rendering using render textures
- Minimal redraws for static UI elements
- Optimized layer composition
- Fast pixel-level operations

## Epitech Compliance
- Standard Epitech coding style
- No forbidden functions used
- Error code 84 for failures
- Proper memory management
- Repository size optimization

This implementation provides a complete paint application with professional-level features including layer management, multiple tools, file operations, and a polished user interface suitable for digital art creation.