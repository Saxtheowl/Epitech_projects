##
## EPITECH PROJECT, 2024
## Day08 PDG - Exercise 0
## File description:
## Makefile for Droid class
##

NAME        = test_droid

SRC         = Droid.cpp \
              test_droid.cpp

OBJ         = $(SRC:.cpp=.o)

CXX         = g++
CXXFLAGS    = -std=c++20 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run:
	@echo "Running unit tests..."
	# Unit tests implementation to be added

.PHONY: all clean fclean re tests_run