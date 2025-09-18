##
## EPITECH PROJECT, 2024
## Day07AM PDG - RESISTANCE IS FUTILE
## File description:
## Makefile for Federation
##

NAME        = test_federation

SRC         = Federation.cpp \
              WarpSystem.cpp \
              test_federation.cpp

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