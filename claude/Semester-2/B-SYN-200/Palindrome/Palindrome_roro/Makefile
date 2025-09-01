##
## EPITECH PROJECT, 2025
## Palindrome
## File description:
## Makefile for palindrome project
##

SOURCES = main.c \
          parser.c \
          palindrome.c \
          utils.c \
          requirement.c

OBJECTS = $(SOURCES:.c=.o)

NAME = palindrome

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = 

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

test: $(NAME)
	@echo "Testing palindrome with examples from PDF..."
	@echo "Test 1: ./palindrome -n 4782 -b 10"
	@./$(NAME) -n 4782 -b 10
	@echo "Test 2: ./palindrome -n 64 -b 2"
	@./$(NAME) -n 64 -b 2
	@echo "Test 3: ./palindrome -h"
	@./$(NAME) -h

.PHONY: all clean fclean re debug test