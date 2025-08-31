##
## EPITECH PROJECT, 2024
## My_sokoban
## File description:
## Makefile for my_sokoban project
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

NAME = my_sokoban

SRCDIR = src
INCDIR = include
TESTDIR = tests

SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/arguments.c \
          $(SRCDIR)/map_loader.c \
          $(SRCDIR)/map_validator.c \
          $(SRCDIR)/game.c \
          $(SRCDIR)/input.c \
          $(SRCDIR)/movement.c \
          $(SRCDIR)/game_logic.c \
          $(SRCDIR)/ncurses_utils.c \
          $(SRCDIR)/utils.c

OBJECTS = $(SOURCES:.c=.o)

LIBS = -lncurses

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	@echo "Running tests for my_sokoban..."
	@gcc -o test_my_sokoban $(TESTDIR)/test_main.c $(SRCDIR)/arguments.c $(SRCDIR)/map_loader.c $(SRCDIR)/map_validator.c $(SRCDIR)/movement.c $(SRCDIR)/game_logic.c $(SRCDIR)/utils.c -I$(INCDIR)
	@./test_my_sokoban
	@rm -f test_my_sokoban

.PHONY: all clean fclean re tests_run