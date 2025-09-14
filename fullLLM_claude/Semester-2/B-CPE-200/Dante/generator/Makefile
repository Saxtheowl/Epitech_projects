##
## EPITECH PROJECT, 2024
## Dante - Generator
## File description:
## Makefile for maze generator
##

NAME = generator

SRC = main.c \
      maze_generator.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re