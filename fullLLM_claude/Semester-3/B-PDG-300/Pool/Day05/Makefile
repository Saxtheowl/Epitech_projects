##
## EPITECH PROJECT, 2024
## Day05 PDG - Makefile
## File description:
## Makefile for libstring.a static library
##

CC = gcc
CFLAGS = -std=gnu17 -Wall -Wextra -Werror

SRC_DIR = src
INCLUDE_DIR = include

SRC = $(SRC_DIR)/string_init.c \
      $(SRC_DIR)/string_destroy.c

OBJ = $(SRC:.c=.o)

NAME = libstring.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test_string: test_main.c $(NAME)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) test_main.c -L. -lstring -o test_string

tests_run: test_string
	@echo "Running unit tests..."
	./test_string

.PHONY: all clean fclean re tests_run