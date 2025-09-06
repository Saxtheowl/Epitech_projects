##
## EPITECH PROJECT, 2025
## Day06 - Main Makefile
## File description:
## Main Makefile for Day06 exercises
##

all:
	$(MAKE) -C ex00

clean:
	$(MAKE) -C ex00 clean

fclean:
	$(MAKE) -C ex00 fclean

re:
	$(MAKE) -C ex00 re

tests_run:
	$(MAKE) -C ex00
	g++ -std=c++20 tests/test_Z.cpp -lcriterion -o test_Z && ./test_Z

.PHONY: all clean fclean re tests_run