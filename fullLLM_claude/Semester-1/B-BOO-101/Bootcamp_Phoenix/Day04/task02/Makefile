##
## EPITECH PROJECT, 2024
## Day04 - Bootcamp Phoenix
## File description:
## Makefile for task02
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L../lib/phoenix -lphoenix
INCLUDES = -I../includes

SOURCES = concat_parameters.c main.c

OBJECTS = $(SOURCES:.c=.o)

NAME = concat_parameters

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C ../lib/phoenix
	$(CC) -o $(NAME) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re