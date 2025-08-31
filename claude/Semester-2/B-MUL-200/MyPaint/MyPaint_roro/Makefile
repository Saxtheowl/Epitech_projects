##
## EPITECH PROJECT, 2024
## MyPaint
## File description:
## Makefile for picture editor
##

NAME = my_paint

CC = gcc

SRCDIR = src
INCDIR = include

SOURCES = $(SRCDIR)/main.c \
		$(SRCDIR)/core.c \
		$(SRCDIR)/canvas.c \
		$(SRCDIR)/layers.c \
		$(SRCDIR)/tools.c \
		$(SRCDIR)/drawing.c \
		$(SRCDIR)/ui.c \
		$(SRCDIR)/buttons.c \
		$(SRCDIR)/menu.c \
		$(SRCDIR)/file_operations.c \
		$(SRCDIR)/edit_operations.c \
		$(SRCDIR)/dialogs.c \
		$(SRCDIR)/utils.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -std=c99 -I$(INCDIR)
LDFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -lm

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