##
## EPITECH PROJECT, 2024
## Day03 - Bootcamp Phoenix
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = my_putchar.c \
          show_number.c \
          show_string.c \
          reverse_string.c \
          to_number.c \
          is_prime_number.c \
          my_strcpy.c \
          my_strncmp.c \
          my_strstr.c

OBJECTS = $(SOURCES:.c=.o)

NAME = libphoenix.a

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re