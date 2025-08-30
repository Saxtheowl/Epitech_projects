##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for bistromatic project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_FILES = src/main.c \
            src/utils.c \
            src/string_utils.c \
            src/base_conversion.c \
            src/bigint.c \
            src/operations.c \
            src/eval_expr.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = calc

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -o $(NAME) $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: $(NAME)
	echo '3+6' | ./$(NAME) 0123456789 '()+-*/%' 3
	echo '3v6' | ./$(NAME) 0123456789 '{}vwxyz' 3

.PHONY: all clean fclean re tests_run