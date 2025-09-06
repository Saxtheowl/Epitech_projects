##
## EPITECH PROJECT, 2025
## Day05 - String Module
## File description:
## Makefile for string library
##

SRC = string_init.c \
      string_destroy.c

OBJ = $(SRC:.c=.o)

NAME = libstring.a

CC = gcc
CFLAGS = -std=gnu17 -Wall -Wextra
AR = ar
ARFLAGS = rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re