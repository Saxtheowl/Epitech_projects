##
## EPITECH PROJECT, 2024
## MyHunter
## File description:
## Makefile for my_hunter duck hunt game
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

NAME = my_hunter

SRCDIR = src
INCDIR = include
TESTDIR = tests

SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/game.c \
          $(SRCDIR)/init.c \
          $(SRCDIR)/duck.c \
          $(SRCDIR)/update.c \
          $(SRCDIR)/events.c \
          $(SRCDIR)/cleanup.c

OBJECTS = $(SOURCES:.c=.o)

LIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

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
	@echo "Running tests for my_hunter..."
	@gcc -o test_my_hunter $(TESTDIR)/test_main.c $(SRCDIR)/duck.c $(SRCDIR)/cleanup.c -I$(INCDIR) $(LIBS)
	@./test_my_hunter
	@rm -f test_my_hunter

.PHONY: all clean fclean re tests_run