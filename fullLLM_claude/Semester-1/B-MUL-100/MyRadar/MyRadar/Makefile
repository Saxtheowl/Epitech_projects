##
## EPITECH PROJECT, 2024
## MyRadar
## File description:
## Makefile for MyRadar project
##

NAME	= my_radar

SRCDIR	= src
INCDIR	= include

SOURCES	= $(SRCDIR)/main.c \
	  $(SRCDIR)/radar.c \
	  $(SRCDIR)/window.c \
	  $(SRCDIR)/aircraft.c \
	  $(SRCDIR)/tower.c \
	  $(SRCDIR)/parser.c \
	  $(SRCDIR)/simulation.c \
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