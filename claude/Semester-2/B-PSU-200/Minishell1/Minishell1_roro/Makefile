##
## EPITECH PROJECT, 2024
## Minishell1
## File description:
## Makefile for mysh minishell
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

NAME = mysh

SRCDIR = src
INCDIR = include
TESTDIR = tests

SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/shell_loop.c \
          $(SRCDIR)/environment.c \
          $(SRCDIR)/command_parser.c \
          $(SRCDIR)/command_execution.c \
          $(SRCDIR)/builtins.c \
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
	@echo "Running tests for mysh..."
	@gcc -o test_mysh $(TESTDIR)/test_main.c $(SRCDIR)/environment.c $(SRCDIR)/command_parser.c $(SRCDIR)/builtins.c $(SRCDIR)/utils.c -I$(INCDIR)
	@./test_mysh
	@rm -f test_mysh

.PHONY: all clean fclean re tests_run