##
## EPITECH PROJECT, 2024
## Day04PM - Marvin's List
## File description:
## Makefile for Day04PM
##

NAME        = test_int_list

SRC         = int_list.c \
              test_int_list.c \
              list.c \
              stack.c \
              queue.c \
              map.c \
              tree.c

OBJ         = $(SRC:.c=.o)

CC          = gcc
CFLAGS      = -std=gnu17 -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run: $(NAME)
	@echo "Running unit tests..."
	./$(NAME)

.PHONY: all clean fclean re tests_run