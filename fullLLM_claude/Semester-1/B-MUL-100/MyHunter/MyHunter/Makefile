##
## EPITECH PROJECT, 2024
## MyHunter
## File description:
## Makefile for MyHunter project
##

NAME	= my_hunter

SRCDIR	= src
INCDIR	= include

SOURCES	= $(SRCDIR)/main.c \
	  $(SRCDIR)/game.c \
	  $(SRCDIR)/window.c \
	  $(SRCDIR)/duck.c \
	  $(SRCDIR)/events.c \
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