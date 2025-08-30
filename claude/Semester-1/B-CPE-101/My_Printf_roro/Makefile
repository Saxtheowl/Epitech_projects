##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for my_printf library
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_FILES = src/my_printf.c \
            src/my_putchar.c \
            src/my_putstr.c \
            src/my_strlen.c \
            src/my_put_nbr.c \
            src/my_put_unsigned_nbr.c \
            src/my_put_nbr_base.c \
            src/my_strcpy.c \
            src/format_handlers.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = libmy.a

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $(NAME) $(OBJ_FILES)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: $(NAME)
	gcc -Wall -Wextra -I./include tests/test_printf.c -L. -lmy -o test_printf
	./test_printf

.PHONY: all clean fclean re tests_run