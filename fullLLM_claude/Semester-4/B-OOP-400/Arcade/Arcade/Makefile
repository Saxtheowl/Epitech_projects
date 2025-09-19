##
## EPITECH PROJECT, 2025
## Arcade
## File description:
## Makefile for Arcade project
##

CXX				= g++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++17 -fno-gnu-unique
LDFLAGS			= -ldl

NAME			= arcade

# Core sources
CORE_SRC		= src/core/main.cpp \
				  src/core/Core.cpp \
				  src/core/LibraryLoader.cpp \
				  src/core/ScoreManager.cpp

CORE_OBJ		= $(CORE_SRC:.cpp=.o)

# Graphics libraries
GRAPHICS_LIBS	= lib/arcade_ncurses.so \
				  lib/arcade_sdl2.so

# Game libraries
GAME_LIBS		= lib/arcade_nibbler.so \
				  lib/arcade_pacman.so

# Graphics sources
NCURSES_SRC		= src/graphics/NcursesLib.cpp
SDL2_SRC		= src/graphics/Sdl2Lib.cpp
SFML_SRC		= src/graphics/SfmlLib.cpp

# Game sources
NIBBLER_SRC		= src/games/NibblerGame.cpp
PACMAN_SRC		= src/games/PacmanGame.cpp

all: $(NAME) games graphicals

$(NAME): $(CORE_OBJ)
	$(CXX) -o $(NAME) $(CORE_OBJ) $(LDFLAGS)

core: $(NAME)

games: $(GAME_LIBS)

graphicals: $(GRAPHICS_LIBS)

# Core compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

# Graphics libraries compilation
lib/arcade_ncurses.so: $(NCURSES_SRC:.cpp=.o)
	$(CXX) -shared -fPIC -o $@ $< -lncurses

lib/arcade_sdl2.so: $(SDL2_SRC:.cpp=.o)
	$(CXX) -shared -fPIC -o $@ $<

lib/arcade_sfml.so: $(SFML_SRC:.cpp=.o)
	$(CXX) -shared -fPIC -o $@ $< -lsfml-graphics -lsfml-window -lsfml-system

# Game libraries compilation
lib/arcade_nibbler.so: $(NIBBLER_SRC:.cpp=.o)
	$(CXX) -shared -fPIC -o $@ $<

lib/arcade_pacman.so: $(PACMAN_SRC:.cpp=.o)
	$(CXX) -shared -fPIC -o $@ $<

# Shared objects need -fPIC
src/graphics/%.o: src/graphics/%.cpp
	$(CXX) $(CXXFLAGS) -fPIC -Iinclude -c $< -o $@

src/games/%.o: src/games/%.cpp
	$(CXX) $(CXXFLAGS) -fPIC -Iinclude -c $< -o $@

clean:
	rm -f $(CORE_OBJ)
	rm -f src/graphics/*.o
	rm -f src/games/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(GRAPHICS_LIBS)
	rm -f $(GAME_LIBS)

re: fclean all

.PHONY: all core games graphicals clean fclean re