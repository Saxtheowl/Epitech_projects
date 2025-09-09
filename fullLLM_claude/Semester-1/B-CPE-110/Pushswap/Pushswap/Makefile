##
## EPITECH PROJECT, 2024
## Push Swap
## File description:
## Makefile
##

NAME	= push_swap

SRC	= main.c \
	  list_operations.c \
	  stack_management.c \
	  operations.c \
	  rotate_operations.c \
	  sorting.c \
	  utils.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re