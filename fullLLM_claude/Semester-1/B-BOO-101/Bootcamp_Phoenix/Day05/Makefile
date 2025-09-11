##
## EPITECH PROJECT, 2024
## Day05 - Bootcamp Phoenix
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = main.c star.c

OBJECTS = $(SOURCES:.c=.o)

NAME = star

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re