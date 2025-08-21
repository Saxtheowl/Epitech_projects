##
## EPITECH PROJECT, 2024
## Antman
## File description:
## Makefile for giantman binary
##

NAME	= giantman

SRC	= giantman.c \
	  ../shared/file_operations.c \
	  ../shared/utils.c \
	  ../shared/decompression_algorithms.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -I../shared

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re