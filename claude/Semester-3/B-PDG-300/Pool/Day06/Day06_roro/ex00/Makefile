##
## EPITECH PROJECT, 2025
## Day06 - Exercise 0
## File description:
## Makefile for Z program
##

NAME        = Z

SRC         = Z.cpp

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

.PHONY: all clean fclean re