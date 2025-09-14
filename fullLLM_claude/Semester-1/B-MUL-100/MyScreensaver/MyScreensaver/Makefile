##
## EPITECH PROJECT, 2024
## MyScreensaver
## File description:
## Makefile for MyScreensaver project
##

NAME	= my_screensaver

SRCDIR	= src
INCDIR	= include

SOURCES	= $(SRCDIR)/main.c \
	  $(SRCDIR)/screensaver.c \
	  $(SRCDIR)/window.c \
	  $(SRCDIR)/framebuffer.c \
	  $(SRCDIR)/animations.c \
	  $(SRCDIR)/animation_1.c \
	  $(SRCDIR)/animation_2.c \
	  $(SRCDIR)/animation_3.c \
	  $(SRCDIR)/animation_4.c \
	  $(SRCDIR)/animation_5.c \
	  $(SRCDIR)/utils.c

OBJECTS	= $(SOURCES:.c=.o)

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -I$(INCDIR)
LDFLAGS	= -lcsfml-graphics -lcsfml-window -lcsfml-system -lm

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re