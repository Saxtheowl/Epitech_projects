##
## EPITECH PROJECT, 2024
## Day02 - Bootcamp Phoenix
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = iterative_factorial.c \
          recursive_power.c \
          is_prime_number.c \
          my_strcpy.c \
          my_strncmp.c \
          my_strstr.c \
          my_strupcase.c \
          my_strcapitalize.c

OBJECTS = $(SOURCES:.c=.o)

NAME = test_day02

all: $(NAME)

$(NAME): $(OBJECTS) main.o
	$(CC) -o $(NAME) $(OBJECTS) main.o

clean:
	rm -f $(OBJECTS) main.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re