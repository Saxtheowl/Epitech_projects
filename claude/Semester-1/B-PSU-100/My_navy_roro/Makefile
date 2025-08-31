##
## EPITECH PROJECT, 2024
## My_navy
## File description:
## Makefile for my_navy project
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

NAME = my_navy

SRCDIR = src
INCDIR = include
TESTDIR = tests

SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/arguments.c \
          $(SRCDIR)/parser.c \
          $(SRCDIR)/validator.c \
          $(SRCDIR)/board.c \
          $(SRCDIR)/signals.c \
          $(SRCDIR)/game.c \
          $(SRCDIR)/game_start.c \
          $(SRCDIR)/utils.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	@echo "Running tests for my_navy..."
	@gcc -o test_my_navy $(TESTDIR)/test_main.c $(SRCDIR)/arguments.c $(SRCDIR)/parser.c $(SRCDIR)/validator.c $(SRCDIR)/board.c $(SRCDIR)/signals.c $(SRCDIR)/game.c $(SRCDIR)/game_start.c $(SRCDIR)/utils.c -I$(INCDIR)
	@./test_my_navy
	@rm -f test_my_navy

.PHONY: all clean fclean re tests_run