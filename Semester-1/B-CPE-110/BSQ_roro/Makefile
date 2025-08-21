##
## EPITECH PROJECT, 2024
## BSQ
## File description:
## Makefile for BSQ - find the Biggest SQuare
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/file_operations.c \
      $(SRC_DIR)/board_parser.c \
      $(SRC_DIR)/board_manager.c \
      $(SRC_DIR)/bsq_algorithm.c \
      $(SRC_DIR)/utils.c

OBJ = $(SRC:.c=.o)
NAME = bsq

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	python3 tests_env/runner.py

.PHONY: all clean fclean re tests_run