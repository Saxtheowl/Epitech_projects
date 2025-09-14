##
## EPITECH PROJECT, 2024
## Dante
## File description:
## Root Makefile for Dante project
##

all: solver generator

solver:
	make -C solver

generator:
	make -C generator

clean:
	make -C solver clean
	make -C generator clean

fclean: clean
	make -C solver fclean
	make -C generator fclean

re: fclean all

.PHONY: all solver generator clean fclean re