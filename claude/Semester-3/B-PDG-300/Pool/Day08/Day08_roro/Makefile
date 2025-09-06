##
## EPITECH PROJECT, 2025
## Day08 - Makefile
## File description:
## Makefile for Day08 exercises
##

SRC_EX00 = ex00/Droid.cpp

OBJ_EX00 = $(SRC_EX00:.cpp=.o)

CXXFLAGS = -std=c++20 -Wall -Wextra -Werror

all: $(OBJ_EX00)

clean:
	rm -f $(OBJ_EX00)

fclean: clean

re: fclean all

tests_run:
	g++ -std=c++20 tests/test_droid.cpp ex00/Droid.cpp -lcriterion -o test_droid && ./test_droid

.PHONY: all clean fclean re tests_run