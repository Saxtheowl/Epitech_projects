##
## EPITECH PROJECT, 2025
## Malloc
## File description:
## Makefile for custom malloc implementation
##

NAME = libmy_malloc.so

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -fPIC
LDFLAGS = -shared

SRC = malloc.c \
      debug.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Test targets
test: $(NAME) test_program
	LD_PRELOAD=./$(NAME) ./test_program

test_program: test_program.c
	$(CC) -o test_program test_program.c

.PHONY: all clean fclean re test