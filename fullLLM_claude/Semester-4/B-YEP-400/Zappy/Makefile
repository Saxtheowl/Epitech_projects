##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Main Makefile for all three components
##

all: zappy_server zappy_ai zappy_gui

zappy_server:
	$(MAKE) -C server

zappy_ai:
	$(MAKE) -C ai

zappy_gui:
	$(MAKE) -C gui

clean:
	$(MAKE) -C server clean
	$(MAKE) -C ai clean
	$(MAKE) -C gui clean

fclean:
	$(MAKE) -C server fclean
	$(MAKE) -C ai fclean
	$(MAKE) -C gui fclean

re: fclean all

.PHONY: all zappy_server zappy_ai zappy_gui clean fclean re