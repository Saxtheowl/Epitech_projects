##
## EPITECH PROJECT, 2024
## Day03 - Bootcamp Phoenix
## File description:
## Makefile for task05
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L../lib/phoenix -lphoenix
INCLUDES = -I../includes

SOURCES = sorted_params.c

OBJECTS = $(SOURCES:.c=.o)

NAME = sorted_params

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re