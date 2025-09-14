##
## EPITECH PROJECT, 2024
## Palindrome
## File description:
## Makefile for palindrome project
##

NAME = palindrome

SRC = main.c \
      args.c \
      palindrome.c

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