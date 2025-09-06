##
## EPITECH PROJECT, 2025
## Day07AM - Makefile
## File description:
## Makefile for Day07AM exercises
##

SRC	= Federation.cpp \
	  WarpSystem.cpp

OBJ	= $(SRC:.cpp=.o)

CXXFLAGS = -std=c++20 -Wall -Wextra -Werror

all: $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean

re: fclean all

tests_run:
	g++ -std=c++20 tests/test_federation.cpp Federation.cpp WarpSystem.cpp -lcriterion -o test_federation && ./test_federation

.PHONY: all clean fclean re tests_run