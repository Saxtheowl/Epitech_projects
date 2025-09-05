##
## EPITECH PROJECT, 2025
## GeekNameFormatter
## File description:
## Makefile for geek name formatter
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I./include

SRCDIR = src
OBJDIR = obj
TESTDIR = tests

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TEST_SOURCES = $(wildcard $(TESTDIR)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:$(TESTDIR)/%.c=$(OBJDIR)/%.o)

MAIN_SOURCES = $(filter-out $(SRCDIR)/main.c, $(SOURCES))
MAIN_OBJECTS = $(MAIN_SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NAME = geekNameFormatter

all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

tests_run: $(MAIN_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(MAIN_OBJECTS) $(TEST_OBJECTS) -lcriterion --coverage -o test_$(NAME)
	./test_$(NAME)
	gcovr --exclude tests/

clean:
	rm -rf $(OBJDIR)
	rm -f *.gcno *.gcda

fclean: clean
	rm -f $(NAME)
	rm -f test_$(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run