##
## EPITECH PROJECT, 2024
## 42sh
## File description:
## Makefile for 42sh advanced shell
##

NAME		= 42sh

SRC_DIR		= src/
INCLUDE_DIR	= include/
LIB_DIR		= lib/

SRC		= $(SRC_DIR)main.c \
		  $(SRC_DIR)shell.c \
		  $(SRC_DIR)lexer.c \
		  $(SRC_DIR)parser.c \
		  $(SRC_DIR)executor.c \
		  $(SRC_DIR)builtins.c \
		  $(SRC_DIR)env.c \
		  $(SRC_DIR)aliases.c \
		  $(SRC_DIR)history.c \
		  $(SRC_DIR)globbing.c \
		  $(SRC_DIR)jobs.c \
		  $(SRC_DIR)variables.c \
		  $(SRC_DIR)redirections.c \
		  $(SRC_DIR)signals.c \
		  $(SRC_DIR)utils.c \
		  $(SRC_DIR)line_editing.c

OBJ		= $(SRC:.c=.o)

CFLAGS		= -Wall -Wextra -I$(INCLUDE_DIR) -g
LDFLAGS		=

CC		= gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re