##
## EPITECH PROJECT, 2025
## My_sudo
## File description:
## Makefile for sudo implementation
##

NAME	=	my_sudo

SRC	=	src/main.c		\
		src/args.c		\
		src/sudoers.c		\
		src/auth.c		\
		src/execute.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c99 -pedantic -I./include

LDFLAGS	=	-lcrypt

CC	=	gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run:
	@echo "No automated tests for my_sudo - manual testing required"

.PHONY: all clean fclean re tests_run