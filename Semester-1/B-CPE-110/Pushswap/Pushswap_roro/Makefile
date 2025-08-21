##
## EPITECH PROJECT, 2024
## Pushswap
## File description:
## Makefile for push_swap program
##

NAME	= push_swap

SRC	= src/main.c \
	  src/list_operations.c \
	  src/game_operations.c \
	  src/rotate_operations.c \
	  src/algorithms.c \
	  src/utils.c \
	  src/game_management.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -I./include

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re