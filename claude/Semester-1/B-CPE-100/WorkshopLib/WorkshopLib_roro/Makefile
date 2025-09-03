##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for libmy library
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRCDIR = lib/my
INCDIR = include

SOURCES = $(SRCDIR)/basic_io.c \
          $(SRCDIR)/string_basic.c \
          $(SRCDIR)/math_functions.c \
          $(SRCDIR)/utilities.c \
          $(SRCDIR)/string_advanced.c \
          $(SRCDIR)/string_transform.c \
          $(SRCDIR)/string_checks.c \
          $(SRCDIR)/string_extra.c

OBJECTS = $(SOURCES:.c=.o)

LIBMY = $(SRCDIR)/libmy.a

all: $(LIBMY)

$(LIBMY): $(OBJECTS)
	ar rc $(LIBMY) $(OBJECTS)
	ranlib $(LIBMY)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(LIBMY)

re: fclean all

test: $(LIBMY)
	$(CC) $(CFLAGS) -o test tests/test_main.c -L$(SRCDIR) -lmy
	./test

tests_run: $(LIBMY)
	$(CC) $(CFLAGS) -o tests_run tests/test_libmy.c -L$(SRCDIR) -lmy
	./tests_run

.PHONY: all clean fclean re test tests_run