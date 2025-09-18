##
## EPITECH PROJECT, 2024
## Day10 - do_op Makefile
## File description:
## Makefile for do_op calculator - Task 02
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = do_op.c

OBJ = $(SRC:.c=.o)

NAME = do_op

LIBPATH = ../lib/

INCPATH = ../include/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBPATH) -lmy

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCPATH) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re