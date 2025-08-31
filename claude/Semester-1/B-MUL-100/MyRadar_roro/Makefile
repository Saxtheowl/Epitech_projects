##
## EPITECH PROJECT, 2024
## MyRadar
## File description:
## Makefile for my_radar air traffic control simulation
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

NAME = my_radar

SRCDIR = src
INCDIR = include
TESTDIR = tests

SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/radar.c \
          $(SRCDIR)/init.c \
          $(SRCDIR)/script.c \
          $(SRCDIR)/aircraft.c \
          $(SRCDIR)/collision.c \
          $(SRCDIR)/render.c \
          $(SRCDIR)/events.c \
          $(SRCDIR)/graphics.c

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
	@echo "Running tests for my_radar..."
	@gcc -o test_my_radar $(TESTDIR)/test_main.c $(SRCDIR)/script.c $(SRCDIR)/collision.c $(SRCDIR)/graphics.c -I$(INCDIR) $(LIBS)
	@./test_my_radar
	@rm -f test_my_radar

.PHONY: all clean fclean re tests_run