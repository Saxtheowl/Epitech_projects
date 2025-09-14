##
## EPITECH PROJECT, 2024
## MyRunner
## File description:
## Makefile for MyRunner project
##

NAME	= my_runner

SRCDIR	= src
INCDIR	= include

SOURCES	= $(SRCDIR)/main.c \
	  $(SRCDIR)/game.c \
	  $(SRCDIR)/window.c \
	  $(SRCDIR)/player.c \
	  $(SRCDIR)/map.c \
	  $(SRCDIR)/physics.c \
	  $(SRCDIR)/parallax.c \
	  $(SRCDIR)/enemies.c \
	  $(SRCDIR)/utils.c

OBJECTS	= $(SOURCES:.c=.o)

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -I$(INCDIR)
LDFLAGS	= -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re