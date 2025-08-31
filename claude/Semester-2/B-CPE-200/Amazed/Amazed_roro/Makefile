##
## EPITECH PROJECT, 2024
## Amazed
## File description:
## Makefile for amazed maze solver
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

NAME = amazed

SRCDIR = src
INCDIR = include
TESTDIR = tests

SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/maze.c \
          $(SRCDIR)/parser.c \
          $(SRCDIR)/pathfinding.c \
          $(SRCDIR)/solver.c \
          $(SRCDIR)/output.c \
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
	@echo "Running tests for amazed..."
	@gcc -o test_amazed $(TESTDIR)/test_main.c $(SRCDIR)/maze.c $(SRCDIR)/parser.c $(SRCDIR)/pathfinding.c $(SRCDIR)/utils.c -I$(INCDIR)
	@./test_amazed
	@rm -f test_amazed

.PHONY: all clean fclean re tests_run