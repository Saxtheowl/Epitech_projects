##
## EPITECH PROJECT, 2024
## Day10 - libmy Makefile 
## File description:
## Makefile for libmy - Task 01
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

NAME = libmy.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	cp $(NAME) ../../lib/
	cp my.h ../../include/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../../lib/$(NAME)
	rm -f ../../include/my.h

re: fclean all

.PHONY: all clean fclean re