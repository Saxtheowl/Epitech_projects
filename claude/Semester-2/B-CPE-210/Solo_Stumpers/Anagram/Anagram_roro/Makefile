##
## EPITECH PROJECT, 2025
## Anagram
## File description:
## Makefile for anagram project
##

NAME	= anagram

SRCDIR	= src
INCDIR	= include
TESTDIR	= tests

SRCFILES = main.c \
           anagram.c \
           utils.c \
           anagram_logic.c \
           output.c

SRC	= $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -I$(INCDIR)

TESTFLAGS = -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(TESTDIR)/*.o

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests

re: fclean all

tests_run: re
	gcc -o unit_tests $(filter-out $(SRCDIR)/main.o, $(OBJ)) $(TESTDIR)/*.c $(CFLAGS) $(TESTFLAGS)
	./unit_tests

.PHONY: all clean fclean re tests_run