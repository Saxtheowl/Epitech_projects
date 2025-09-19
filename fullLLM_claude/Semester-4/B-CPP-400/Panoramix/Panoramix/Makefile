##
## EPITECH PROJECT, 2025
## Panoramix
## File description:
## Makefile for panoramix project
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lpthread

NAME = panoramix

SRC = main.c \
      villager.c \
      druid.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ -Wall -Wextra -Werror

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re