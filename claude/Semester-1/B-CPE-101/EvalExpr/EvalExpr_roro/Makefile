##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for eval_expr project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_FILES = src/main.c \
            src/eval_expr.c \
            lib/my/my_putchar.c \
            lib/my/my_put_nbr.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = eval_expr

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

test: $(NAME)
	./$(NAME) "(3+2)*5"
	./$(NAME) "10+5*2"
	./$(NAME) "(10+5)*2"

.PHONY: all clean fclean re test