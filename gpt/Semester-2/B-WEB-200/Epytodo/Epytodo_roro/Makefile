##
## EPITECH PROJECT, 2025
## Epytodo - Makefile
## File description:
## Minimal web project scaffolding
##

.PHONY: all clean fclean re tests_run run

NAME	=	epytodo

SRC	=	src/app.py

all:
	@echo "$(NAME): nothing to build"

run:
	python3 $(SRC)

tests_run:
	@echo "Running syntax check"
	python3 -m py_compile $(SRC)
	@echo "OK"

clean:
	@true

fclean: clean
	@true

re: all

