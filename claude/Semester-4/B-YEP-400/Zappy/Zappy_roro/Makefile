##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Main Makefile for all Zappy components
##

SERVER_DIR = server
AI_DIR = ai
GUI_DIR = gui

all: zappy_server zappy_ai zappy_gui

zappy_server:
	$(MAKE) -C $(SERVER_DIR)

zappy_ai:
	$(MAKE) -C $(AI_DIR)

zappy_gui:
	$(MAKE) -C $(GUI_DIR)

clean:
	$(MAKE) -C $(SERVER_DIR) clean
	$(MAKE) -C $(AI_DIR) clean
	$(MAKE) -C $(GUI_DIR) clean

fclean:
	$(MAKE) -C $(SERVER_DIR) fclean
	$(MAKE) -C $(AI_DIR) fclean
	$(MAKE) -C $(GUI_DIR) fclean

re: fclean all

tests_run:
	$(MAKE) -C $(SERVER_DIR) tests_run

.PHONY: all zappy_server zappy_ai zappy_gui clean fclean re tests_run