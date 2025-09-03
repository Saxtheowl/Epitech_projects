##
## EPITECH PROJECT, 2025
## Secured
## File description:
## Makefile for hashtable library
##

NAME	=	libhashtable.a

SRC	=	src/hash_function.c		\
		src/hashtable_create.c		\
		src/hashtable_operations.c	\
		src/hashtable_dump.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c99 -pedantic -I./include

CC	=	gcc

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run:
	@echo "No automated tests for libhashtable - manual testing required"

.PHONY: all clean fclean re tests_run