##
## EPITECH PROJECT, 2025
## FazzBizz
## File description:
## Makefile for fazzbizz project
##

NAME	= fazzbizz

SRCDIR	= src
INCDIR	= include
TESTDIR	= tests

SRCFILES = main.c \
           fazzbizz.c \
           utils.c

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