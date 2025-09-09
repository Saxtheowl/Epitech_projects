##
## EPITECH PROJECT, 2024
## antman
## File description:
## Makefile for antman
##

NAME	= antman

SRC	= antman.c \
	  ../utils.c \
	  ../dictionary.c \
	  ../compress.c \
	  ../decompress.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -I..

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re