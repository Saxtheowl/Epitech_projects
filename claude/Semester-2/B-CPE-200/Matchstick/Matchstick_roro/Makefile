##
## EPITECH PROJECT, 2024
## Matchstick
## File description:
## Makefile for matchstick game
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

NAME = matchstick

SRCDIR = src
INCDIR = include
TESTDIR = tests

SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/game_init.c \
          $(SRCDIR)/display.c \
          $(SRCDIR)/game_logic.c \
          $(SRCDIR)/player_input.c \
          $(SRCDIR)/ai_logic.c \
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
	@echo "Running tests for matchstick..."
	@gcc -o test_matchstick $(TESTDIR)/test_main.c $(SRCDIR)/game_init.c $(SRCDIR)/game_logic.c $(SRCDIR)/ai_logic.c $(SRCDIR)/utils.c -I$(INCDIR)
	@./test_matchstick
	@rm -f test_matchstick

.PHONY: all clean fclean re tests_run