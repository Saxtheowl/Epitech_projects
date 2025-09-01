##
## EPITECH PROJECT, 2025
## Malloc
## File description:
## Makefile for libmy_malloc.so
##

NAME	= libmy_malloc.so

SRC	=	src/malloc.c		\
		src/free.c		\
		src/calloc.c		\
		src/realloc.c		\
		src/reallocarray.c	\
		src/utils.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -fPIC -g3

all: $(NAME)

$(NAME): $(OBJ)
	gcc -shared -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re