##
## EPITECH PROJECT, 2024
## MyDefender
## File description:
## Makefile for tower defense game
##

NAME = my_defender

CC = gcc

SRCDIR = src
INCDIR = include

SOURCES = $(SRCDIR)/main.c \
		$(SRCDIR)/game.c \
		$(SRCDIR)/scenes.c \
		$(SRCDIR)/building_system.c \
		$(SRCDIR)/enemy_system.c \
		$(SRCDIR)/combat_system.c \
		$(SRCDIR)/wave_system.c \
		$(SRCDIR)/ui_system.c \
		$(SRCDIR)/button_callbacks.c \
		$(SRCDIR)/utils.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -std=c99 -I$(INCDIR)
LDFLAGS = -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re