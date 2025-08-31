##
## EPITECH PROJECT, 2024
## My_ls
## File description:
## Makefile for my_ls project
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

NAME = my_ls

SRCDIR = src
INCDIR = include
TESTDIR = tests

SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/options.c \
          $(SRCDIR)/my_ls.c \
          $(SRCDIR)/directory.c \
          $(SRCDIR)/sort.c \
          $(SRCDIR)/print.c \
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
	@echo "Running tests for my_ls..."
	@gcc -o test_my_ls $(TESTDIR)/test_main.c $(SRCDIR)/options.c $(SRCDIR)/my_ls.c $(SRCDIR)/directory.c $(SRCDIR)/sort.c $(SRCDIR)/print.c $(SRCDIR)/utils.c -I$(INCDIR)
	@./test_my_ls
	@rm -f test_my_ls

.PHONY: all clean fclean re tests_run