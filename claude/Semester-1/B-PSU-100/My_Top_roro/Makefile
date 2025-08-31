##
## EPITECH PROJECT, 2024
## My_Top
## File description:
## Makefile for my_top project
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -std=c99

NAME = my_top

SRCDIR = src
INCDIR = include
TESTDIR = tests

SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/arguments.c \
          $(SRCDIR)/system_info.c \
          $(SRCDIR)/processes.c \
          $(SRCDIR)/display.c \
          $(SRCDIR)/input.c \
          $(SRCDIR)/main_loop.c

OBJECTS = $(SOURCES:.c=.o)

LIBS = -lncurses

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
	@echo "Running tests for my_top..."
	@gcc -o test_my_top $(TESTDIR)/test_main.c $(SRCDIR)/arguments.c $(SRCDIR)/system_info.c $(SRCDIR)/processes.c -I$(INCDIR)
	@./test_my_top
	@rm -f test_my_top

.PHONY: all clean fclean re tests_run