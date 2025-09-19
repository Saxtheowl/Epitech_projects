##
## EPITECH PROJECT, 2025
## My_sudo
## File description:
## Makefile for my_sudo project
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=gnu17
LDFLAGS = -lcrypt

NAME = my_sudo

SRC = main.c \
      args.c \
      sudoers.c \
      auth.c \
      execute.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re