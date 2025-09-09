##
## EPITECH PROJECT, 2024
## InfinAdd
## File description:
## Makefile
##

NAME	= infin_add

SRC	= main.c \
	  infin_add.c \
	  operations.c \
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