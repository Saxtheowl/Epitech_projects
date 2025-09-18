##
## EPITECH PROJECT, 2024
## Day09 PDG - Exercise 0 Makefile
## File description:
## Makefile for Peasant class
##

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror

SRC = Peasant.cpp

OBJ = $(SRC:.cpp=.o)

NAME = test_peasant

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re