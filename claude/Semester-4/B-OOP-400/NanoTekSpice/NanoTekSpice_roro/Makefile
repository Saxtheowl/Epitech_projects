##
## EPITECH PROJECT, 2025
## NanoTekSpice
## File description:
## Makefile for NanoTekSpice logic simulator
##

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -I include

# Directories
SRC_DIR = src
INCLUDE_DIR = include

# Source files
SRCFILES = $(SRC_DIR)/main.cpp \
           $(SRC_DIR)/AComponent.cpp \
           $(SRC_DIR)/SpecialComponents.cpp \
           $(SRC_DIR)/LogicGates.cpp \
           $(SRC_DIR)/ComponentFactory.cpp \
           $(SRC_DIR)/Parser.cpp \
           $(SRC_DIR)/Simulator.cpp

OBJFILES = $(SRCFILES:.cpp=.o)

# Target
NAME = nanotekspice

# Rules
all: $(NAME)

$(NAME): $(OBJFILES)
	$(CXX) -o $(NAME) $(OBJFILES) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re