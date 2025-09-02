##
## EPITECH PROJECT, 2025
## Arcade
## File description:
## Makefile for Arcade project
##

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -fno-gnu-unique -I include
LDFLAGS = -ldl

# Directories
SRC_DIR = src
CORE_SRC_DIR = $(SRC_DIR)/core
GAMES_SRC_DIR = $(SRC_DIR)/games
GRAPHICS_SRC_DIR = $(SRC_DIR)/graphics
LIB_DIR = lib

# Core files
CORE_SRCFILES = $(CORE_SRC_DIR)/main.cpp \
                $(CORE_SRC_DIR)/Core.cpp \
                $(CORE_SRC_DIR)/DLLoader.cpp

CORE_OBJFILES = $(CORE_SRCFILES:.cpp=.o)

# Game libraries
NIBBLER_SRCFILES = $(GAMES_SRC_DIR)/Nibbler.cpp
PACMAN_SRCFILES = $(GAMES_SRC_DIR)/Pacman.cpp

# Graphics libraries  
NCURSES_SRCFILES = $(GRAPHICS_SRC_DIR)/NCurses.cpp
SDL2_SRCFILES = $(GRAPHICS_SRC_DIR)/SDL2.cpp
SFML_SRCFILES = $(GRAPHICS_SRC_DIR)/SFML.cpp

# Targets
NAME = arcade

# Library names
NIBBLER_LIB = $(LIB_DIR)/arcade_nibbler.so
PACMAN_LIB = $(LIB_DIR)/arcade_pacman.so
NCURSES_LIB = $(LIB_DIR)/arcade_ncurses.so
SDL2_LIB = $(LIB_DIR)/arcade_sdl2.so
SFML_LIB = $(LIB_DIR)/arcade_sfml.so

GAMES_LIBS = $(NIBBLER_LIB) $(PACMAN_LIB)
GRAPHICS_LIBS = $(NCURSES_LIB)
OPTIONAL_GRAPHICS_LIBS = $(SDL2_LIB) $(SFML_LIB)

# Rules
all: $(NAME) games graphicals

$(NAME): $(CORE_OBJFILES) | $(LIB_DIR)
	$(CXX) -o $(NAME) $(CORE_OBJFILES) $(LDFLAGS)

core: $(NAME)

games: $(GAMES_LIBS)

graphicals: $(GRAPHICS_LIBS)

optional-graphicals: $(OPTIONAL_GRAPHICS_LIBS)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Game libraries compilation
$(NIBBLER_LIB): $(NIBBLER_SRCFILES:.cpp=.o) | $(LIB_DIR)
	$(CXX) -shared -fPIC -o $@ $^ $(CXXFLAGS)

$(PACMAN_LIB): $(PACMAN_SRCFILES:.cpp=.o) | $(LIB_DIR)
	$(CXX) -shared -fPIC -o $@ $^ $(CXXFLAGS)

# Graphics libraries compilation
$(NCURSES_LIB): $(NCURSES_SRCFILES:.cpp=.o) | $(LIB_DIR)
	$(CXX) -shared -fPIC -o $@ $^ $(CXXFLAGS) -lncurses

$(SDL2_LIB): $(SDL2_SRCFILES:.cpp=.o) | $(LIB_DIR)
	$(CXX) -shared -fPIC -o $@ $^ $(CXXFLAGS) -lSDL2

$(SFML_LIB): $(SFML_SRCFILES:.cpp=.o) | $(LIB_DIR)
	$(CXX) -shared -fPIC -o $@ $^ $(CXXFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

# Object files compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

clean:
	$(RM) $(CORE_OBJFILES)
	$(RM) $(NIBBLER_SRCFILES:.cpp=.o)
	$(RM) $(PACMAN_SRCFILES:.cpp=.o)
	$(RM) $(NCURSES_SRCFILES:.cpp=.o)
	$(RM) $(SDL2_SRCFILES:.cpp=.o)
	$(RM) $(SFML_SRCFILES:.cpp=.o)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(LIB_DIR)

re: fclean all

.PHONY: all core games graphicals clean fclean re