##
## EPITECH PROJECT, 2024
## My_Printf
## File description:
## Makefile for libmy.a
##

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g
AR      = ar
ARFLAGS = rc
NAME    = libmy.a

SRC     = my_printf.c \
          parser.c \
          handler.c \
          flags.c \
          basic_funcs.c \
          numbers.c \
          numbers_long.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

libmy.a: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmy.a