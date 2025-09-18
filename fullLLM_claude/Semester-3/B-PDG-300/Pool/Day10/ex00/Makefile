##
## EPITECH PROJECT, 2024
## Day10 PDG - Exercise 0
## File description:
## Makefile for fruit hierarchy
##

NAME        = test_fruits

SRC         = AFruit.cpp \
              ACitrus.cpp \
              ABerry.cpp \
              ANut.cpp \
              Lemon.cpp \
              Orange.cpp \
              Strawberry.cpp \
              Almond.cpp \
              test_fruits.cpp

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