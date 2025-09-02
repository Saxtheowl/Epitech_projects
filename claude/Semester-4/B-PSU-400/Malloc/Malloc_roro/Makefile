##
## EPITECH PROJECT, 2025
## Malloc
## File description:
## Makefile
##

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -std=c99 -fPIC -I./include

SRCDIR	= src
INCDIR	= include
OBJDIR	= obj

SOURCES	= $(SRCDIR)/malloc.c \
		  $(SRCDIR)/free.c \
		  $(SRCDIR)/calloc.c \
		  $(SRCDIR)/realloc.c \
		  $(SRCDIR)/heap.c \
		  $(SRCDIR)/block_management.c \
		  $(SRCDIR)/utils.c

OBJECTS	= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NAME	= libmy_malloc.so

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -shared -o $(NAME) $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all